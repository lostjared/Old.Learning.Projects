#include "puzzle.h"

#include <SDL.h>
#include<iostream>




void *lock(SDL_Surface *surf, Uint8 &type) {
	if(SDL_MUSTLOCK(surf)) {
		if(SDL_LockSurface(surf) < 0)
			return 0;
	}

	type = surf->format->BitsPerPixel;

	switch(surf->format->BitsPerPixel) {
		case 1:
		case 8:
			return (Uint8*)surf->pixels;
			break;
		case 16:
		case 2:
			return (Uint16*)surf->pixels;
			break;
		case 24:
		case 3:
			return (Uint32*)surf->pixels;
			break;
		case 32:
		case 4:
			return (Uint32*)surf->pixels;
			break;
		default:
			break;
	}

	return 0;

}



void unlock(SDL_Surface *surf) {
	if(SDL_MUSTLOCK(surf)) {
		SDL_UnlockSurface(surf);
	}
}



inline void setpixel(void *buff, Uint32 x, Uint32 y, Uint32 color, Uint8 &type, Uint16 &pitch) {
	static Uint8 *ubuff8 = 0;

	switch(type) {
		case 1:
		case 8:
			{ 
				Uint8 *buf = (Uint8*)buff;
				buf += (y * pitch) + x;
				*buf = (Uint8) color;

			}
			break;
		case 2:
		case 16:
			{
				ubuff8 = (Uint8*) buff;
				ubuff8 += (y * pitch) + (x*2);
				static Uint16 *ubuff16 = 0;
				ubuff16 = (Uint16*) ubuff8;
				*ubuff16 = (Uint16) color;
			}
			break;
		case 3:
		case 24:
			{
				static char c1 = 0,c2 = 0,c3 = 0;

				ubuff8 = (Uint8*) buff;
				ubuff8 += (y * pitch) + (x*3);
				if(SDL_BYTEORDER == SDL_LIL_ENDIAN) {
					c1 = (color & 0xFF0000) >> 16;
					c2 = (color & 0x00FF00) >> 8;
					c3 = (color & 0x0000FF);
				} else {
					c3 = (color & 0xFF0000) >> 16;
					c2 = (color & 0x00FF00) >> 8;
					c1 = (color & 0x0000FF);
				}
				ubuff8[0] = c3;
				ubuff8[1] = c2;
				ubuff8[2] = c1;
			}
			break;
		case 4:
		case 32:
			{
			ubuff8 = (Uint8*) buff;
			static Uint32 *ubuff32 = 0;
			ubuff8 += (y*pitch) + (x*4);
			ubuff32 = (Uint32*)ubuff8;
			*ubuff32 = color;
			}
			break;
	}

}

inline Uint32 getpixel(SDL_Surface *surf, int x, int y, Uint8 &type, Uint16 &pitch) {
	static Uint8 *bitz = 0;
	Uint32 bpp = (Uint32) type;
	bitz = ((Uint8 *)surf->pixels)+y*pitch+x*(bpp/8);
	switch(type) {
		case 8:
		case 1:
			return *((Uint8 *)surf->pixels + y * pitch + x);
			break;
		case 16:
		case 2:
			return *((Uint16 *)surf->pixels + y * pitch/2 + x);
			break;
		case 3:
		case 24:
			{
				Uint8 r, g, b;
				r = *((bitz)+surf->format->Rshift/8);
				g = *((bitz)+surf->format->Gshift/8);
				b = *((bitz)+surf->format->Bshift/8);
				return SDL_MapRGB(surf->format,r,g,b);
			
			}
		case 32:
		case 4:
			return *((Uint32 *)surf->pixels + y * pitch/4 + x);
			break;
	}

	return 0;
}

int mx = 0, my = 0;

int main(int argc, char **argv) {

	SDL_Surface *front = 0;

	
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
		return -1;
	atexit(SDL_Quit);
	front = SDL_SetVideoMode(640,480,0,0);

	if(!front)
		return -2;

	Joystick j(0);

	SDL_Event e;
	bool active = true;
	
	char *argument = "img\\intro.bmp";
	if(argc == 2)
		argument = argv[1];

	PuzzleBox box(front,argument);

	while(active == true) {

		SDL_Rect rc = { 0,0,640,480 };
		static Uint8 type = 0;
		void *raw = lock(front,type);
		box.render(raw,type,front->pitch);
		unlock(front);

		if(j.PollButton(1))
			active = false;

		if(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					active = false;
					break;
				case SDL_JOYHATMOTION:
					switch(e.jhat.value) 
					{
					case SDL_HAT_CENTERED:
						break;
					case SDL_HAT_UP:
						box.setcdir(0);
						break;
					case SDL_HAT_RIGHT:
						box.setcdir(1);
						mx++;
						break;
					case SDL_HAT_DOWN:
						box.setcdir(2);
						my++;
						break;
					case SDL_HAT_LEFT:
						box.setcdir(3);
						mx--;
						break;
					}
					break;
				case SDL_JOYBUTTONDOWN:
					break;
			}
		}

		SDL_UpdateRect(front, 0, 0, 640,480);
	}

	SDL_FreeSurface(front);
	return 0;
}
