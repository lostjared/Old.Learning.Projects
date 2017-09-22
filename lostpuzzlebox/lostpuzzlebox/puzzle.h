#ifndef __PUZZLE__H_
#define __PUZZLE__H_

//#define _MXBOX_H_
#include<SDL.h>
#include<iostream>

extern void *lock(SDL_Surface *surf, Uint8 &type);
extern void unlock(SDL_Surface *surf);
inline void setpixel(void *buff, Uint32 x, Uint32 y, Uint32 color, Uint8 &type, Uint16 &pitch);
inline Uint32 getpixel(SDL_Surface *surf, int x, int y, Uint8 &type, Uint16 &pitch);

class Joystick {
public:
	Joystick(int num) {
		num_joy = SDL_NumJoysticks();
		OpenJoy(num);

	}
	~Joystick() {
		SDL_JoystickClose(joy);
	}

	void OpenJoy(int num) {
		joy = SDL_JoystickOpen(num);
		buttons = SDL_JoystickNumButtons(joy);
		SDL_JoystickEventState(SDL_ENABLE);
	}

	bool PollButton(int button) {

		if(SDL_JoystickGetButton(joy,button)) 
			return true;
		return false;

	}

	bool PollHat(int direction) {
		if(SDL_JoystickGetHat(joy,direction))
			return true;
		return false;
	}

	void Poll(SDL_Event &e) {
		if(e.type == SDL_JOYAXISMOTION) {
			if(e.jaxis.axis < 2)
			{
				axis[e.jaxis.axis] = e.jaxis.value >> 8;
			}
		}
	}

	SDL_Joystick *Get() { return joy; }

protected:
	int num_joy;
	SDL_Joystick *joy;
	int buttons;
public:
	int axis[2];

};

class PuzzleBox {
public:

	SDL_Surface *block;

	PuzzleBox(SDL_Surface *front, const char *str) {
		this->front = front;
		block = SDL_LoadBMP(str);
		if(block == 0) 
			return;


		SDL_Rect src = {0,0,640,480};
		SDL_BlitSurface(block, &src,  front, &src);
		SDL_UpdateRect(front, 0,0,640,480);
		color_dir = 0;
	}

	~PuzzleBox() {

		SDL_FreeSurface(block);

	}

	void render(void *buff, Uint8 &type, Uint16 &pitch) {
		this->buffer = buff;
		this->type = type;
		this->pitch = pitch;
		trip_it(0,0,block);
		
	}

	void sp(int x, int y, Uint32 color) {
		setpixel(buffer,x,y,color,type,pitch);
	}

	Uint32 gp(int x, int y) {
		return (getpixel(front,x,y,type,pitch));
	}

	void trip_it(unsigned int x, unsigned int y, SDL_Surface *the_surf) {

		static Uint8 type;
		static int counter = 0;
		++counter;
		static int dir = 2;

		void *data_buff = lock(the_surf, type);

		static int i = 0, z  = 0;
		for(i = 1; i < the_surf->w-1; i++) {
			for(z = 1; z < the_surf->h-1; z++) {
				Uint32 fcol = 0;

				switch(dir) {
					case 1:
						{

				Uint32 c1 = gp(i,z);
				Uint32 c2 = gp(i+1,z+1);
				Uint32 c3 = gp(i,  z+1);
				fcol = c1 + c2 + c3;
				if(fcol != 0) 
					fcol /= 3;

						}
				break;
					case 2:
						{
							Uint32 c1 = gp(i,z);
							Uint32 c2 = gp(i-1,z-1);
							Uint32 c3 = gp(i,  z-1);
							fcol = c1 + c2 + c3;
							if(fcol != 0)
							fcol /= 3;
						}
						break;
				}
				
				Uint8 cc1,cc2,cc3;
				cc1 = (fcol & 0xFF0000) >> 16;
				cc2 = (fcol & 0x00FF00) >> 8;
				cc3 = (fcol & 0x0000FF);
				

				switch(color_dir) {
				case 1:
				fcol = SDL_MapRGB(this->front->format, 0xFF,cc2,cc3);
				break;
				case 2:
				fcol = SDL_MapRGB(this->front->format, cc1,0xFF,cc3);
				break;
				case 3:
				fcol = SDL_MapRGB(this->front->format, cc1, cc2, 0xFF);
				break;
				}


				sp(i+x,z+y,fcol);
				

			}
		}

		unlock(the_surf);

		if(counter > 760 && dir == 1) {
			counter = 0;
			dir = 2;
		}

		if(counter > 250 && dir == 2)
		{
			counter = 0;
			dir = 1;
		}

	}

	void setcdir(int cdir) {
		color_dir = cdir;
	}

protected:
	SDL_Surface *front;
	void        *buffer;
	Uint8       type;
	Uint16      pitch;
	int         color_dir;
	
};


#endif
