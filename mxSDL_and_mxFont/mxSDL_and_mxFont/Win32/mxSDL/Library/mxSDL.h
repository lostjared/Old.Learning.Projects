#ifndef _MXSDL_H__
#define _MXSDL_H__
#include"mxSDL_msg.h"
#include"mxSDL_font.h"
#include<SDL.h>

class mxSDL;

class mxSurface {
public:
	SDL_Surface *surf;
	SDL_PixelFormat *Format() { return surf->format; }
	bool LoadBMP(std::string name) {
		if((surf = SDL_LoadBMP(name.c_str())) == 0)
			return false;
		return true;
	}
	mxSurface() {
		surf = 0;
	}

	~mxSurface() {
		if(surf)
			SDL_FreeSurface(surf);
	}
};

class EventHandler {
public:
	virtual void Event(SDL_Event &e){}
	virtual void KeyDown(int key){}
	virtual void KeyUp(int key) {}
	virtual void Render() {}
	virtual void MouseMove(int x, int y) {}
	virtual void MouseDown(int x, int y, int button) {}
	void Init(mxSDL *mx) { this->mx = mx; }
protected:
	mxSDL *mx;
};



class mxRGB {
public:
	Uint8 r,g,b;
	Uint32 color;
	mxRGB(mxSurface *surf, Uint8 r, Uint8 g, Uint8 b) {
		this->r = r, this->g = g, this->b = b;
		color = SDL_MapRGB(surf->Format(), r,g,b);
	}
	mxRGB(Uint32 color) {
		this->color = color;
		r = (Uint8) color;
		g = (Uint8)( color >> 8 );
		b = (Uint8)( color >> 16 );
	}
	Uint32 GetColor() { return color; }

	Uint32 SetColor(mxSurface *surf, Uint8 r, Uint8 g, Uint8 b) {
		this->r = r, this->g = g, this->b = b;
		color = SDL_MapRGB(surf->Format(), r,g,b);
	}
};

class mxSDL {
public:
	bool active;
	int w,h;
	Message sys_msg;

	mxSDL(std::string name, int x, int y, int bpp, bool full) {
		eventz = 0;
		Init(name, x, y, bpp, full);
	}

	~mxSDL() {
		if(eventz)
			delete eventz;
	}

	virtual void Init(std::string name, int x, int y, int bpp, bool full) {
		atexit(SDL_Quit);
		if(SDL_Init(SDL_INIT_VIDEO) < 0)
			throw ErrorMsg("Error Couldnt Initalize SDL!\n");
		if((front.surf = SDL_SetVideoMode(x,y,bpp,full == true ? SDL_FULLSCREEN : 0)) == 0)
			throw ErrorMsg("Couldnt Set Display Mode!\n");
		SDL_WM_SetCaption(name.c_str(),name.c_str());
		w = x, h = y;
#ifdef MXDEBUG_MODE
		sys_msg = "mxSDL System Message";
		sys_msg << "SDL Successfully Initalized\n";
		sys_msg.DebugMessage();
#endif
	}

	void SetEvents(EventHandler *event) {
		this->eventz = event;
	}
	void PrintText(mxFont *m, int x, int y,mxRGB color,const char *str, ...) {
	    int prev_x = x;
		int offset_x = prev_x, offset_y = y;
		int width = 0, height = 0;
		char text[5000];// just enough
		va_list list;
		va_start(list, str);
		vsprintf((char*)text,str,list);
		va_end(list);

		for(unsigned int p = 0; p < strlen(text); p++) {
			if(text[p] == '\n') {
				offset_x  = prev_x;
				offset_y += height;
				continue;
			}

			for(int i = 0; i < m->mx; i++) {
				for(int z = 0; z < m->my; z++) {
					if(m->letters[text[p]].fnt_ptr[i][z] != m->tcolor) {
						SetPixel(&front, offset_x+i, offset_y+z, color);

						width=i;
						if(height < z)
							height=z;
					}
				}       

			}
			offset_x += width;
		}
	}

	void PrintTextSized(mxFont *m, int x, int y, int w, int h,mxRGB color, const char *str, ...) {
		int prev_x = x;
		int offset_x = prev_x, offset_y = y;
		int width = 0, height = 0;
		char text[5000];// just enough
		va_list list;
		va_start(list, str);
		vsprintf((char*)text,str,list);
		va_end(list);
		for(unsigned int p = 0; p < strlen(text); p++) {
			if(text[p] == '\n') {
				offset_x  = prev_x;
				offset_y += height;
				continue;
			}

			for(int i = 0; i < h; i++) {
				for(int z = 0; z < w; z++) {
					if(m->letters[text[p]].fnt_ptr[GetFX(m,i,w)][GetFZ(m,z,h)] != m->tcolor) {
						SetPixel(&front, offset_x+i, offset_y+z, color);
						width=i;
						if(height < z)
							height=z;
					}
				}       
			}
			offset_x += width;
		}
	}

	inline int GetFX(mxFont *m,int x, int nw) {
		int xp = int((float)x * float(m->mx) / (float)nw);		
		return int(xp);
	}

	inline int GetFZ(mxFont *m, int y, int nh) {
		int yp = int((float)y * float(m->my) / (float)nh);			
		return int(yp);
	}

	virtual void MessagePump() {
		SDL_Event e;
		active = true;
		eventz->Init(this);
		while(active == true) {
			static SDL_Rect rc = { 0,0,w,h };
			SDL_FillRect(front.surf, &rc, 0x0);
			eventz->Render();
			while(SDL_PollEvent(&e)) {
				eventz->Event(e);
#ifdef MXDEBUG_MODE
				sys_msg.clear();
				sys_msg << " SDL Message: " << int(e.type) << "\n";
				sys_msg.DebugMessage();
#endif
				switch(e.type) {
					case SDL_QUIT:
#ifdef MXDEBUG_MODE
						sys_msg.clear();
						sys_msg << " SDL Quit Message Sent \n";
						sys_msg.DebugMessage();
#endif
						active = false;
						break;
					case SDL_KEYDOWN:
#ifdef MXDEBUG_MODE
						sys_msg.clear();
						sys_msg << " SDL Keydown Message Sent Key Sym (" << e.key.keysym.sym << ") \n";
						sys_msg.DebugMessage();
#endif
						eventz->KeyDown(e.key.keysym.sym);
						break;
					case SDL_KEYUP:
#ifdef MXDEBUG_MODE
						sys_msg.clear();
						sys_msg << " SDL Keyup Message Sent Key Sym (" << e.key.keysym.sym << ") \n";
						sys_msg.DebugMessage();
#endif
						eventz->KeyUp(e.key.keysym.sym);
						break;
					case SDL_MOUSEMOTION:
#ifdef MXDEBUG_MODE
						sys_msg.clear();
						sys_msg << " SDL Mouse Move Message Sent X , Y cords ( " << e.motion.x << " , " << e.motion.y << " )\n";
						sys_msg.DebugMessage();
#endif
						mouse_x = e.motion.x;
						mouse_y = e.motion.y;
						eventz->MouseMove(mouse_x, mouse_y);
						break;
					case SDL_MOUSEBUTTONDOWN:
#ifdef MXDEBUG_MODE
						sys_msg.clear();
						sys_msg << " SDL Mouse Down Message Sent X , Y , Button ("  << e.button.x << " , " << e.button.y << " := " << e.button.button << ")\n";
						sys_msg.DebugMessage();
#endif
						mouse_x = e.button.x;
						mouse_y = e.button.y;
						mouse_b = e.button.button;
						eventz->MouseDown(mouse_x,mouse_y,mouse_b);
						break;
				
				}
			}
			SDL_UpdateRect(front.surf, 0,0,w,h);
		}
	}

	void SetPixel(mxSurface *surf, int x, int y, mxRGB the_color) {
		Uint8 *ubuff8;
		Uint16 *ubuff16;
		Uint32 *ubuff32;
		Uint32 color = the_color.GetColor();
		char c1, c2, c3;
		if(SDL_MUSTLOCK(front.surf)) {
			if(SDL_LockSurface(front.surf) < 0)
				return;
		}

		switch(front.surf->format->BytesPerPixel)
		{
		case 1:
			ubuff8 = (Uint8*) front.surf->pixels;
			ubuff8 += (y * front.surf->pitch) + x;
			*ubuff8 = (Uint8) color;
			break;

		case 2:
			ubuff8 = (Uint8*) front.surf->pixels;
			ubuff8 += (y * front.surf->pitch) + (x*2);
			ubuff16 = (Uint16*) ubuff8;
			*ubuff16 = (Uint16) color;
			break;

		case 3:
			ubuff8 = (Uint8*) front.surf->pixels;
			ubuff8 += (y * front.surf->pitch) + (x*3);
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
			break;
		case 4:
			ubuff8 = (Uint8*) front.surf->pixels;
			ubuff8 += (y*front.surf->pitch) + (x*4);
			ubuff32 = (Uint32*)ubuff8;
			*ubuff32 = color;
			break;
		default:
			throw ErrorMsg("Unknown BitDepth");
		}
		if(SDL_MUSTLOCK(front.surf)) {
			SDL_UnlockSurface(front.surf);
		}
	}

	mxRGB GetPixel(mxSurface *surf, int X, int Y) {
		Uint8  *bits;
		Uint32 Bpp;
		Bpp = surf->surf->format->BytesPerPixel;
		bits = ((Uint8 *)surf->surf->pixels)+Y*surf->surf->pitch+X*Bpp;
		switch(Bpp) {
		case 1:
			return mxRGB(*((Uint8 *)surf->surf->pixels + Y * surf->surf->pitch + X));
			break;
		case 2:
			return mxRGB(*((Uint16 *)surf->surf->pixels + Y * surf->surf->pitch/2 + X));
			break;
		case 3: {
			Uint8 r, g, b;
			r = *((bits)+surf->surf->format->Rshift/8);
			g = *((bits)+surf->surf->format->Gshift/8);
			b = *((bits)+surf->surf->format->Bshift/8);
			return mxRGB(surf, r,g,b);
				}
				break;
		case 4:
			return mxRGB(*((Uint32 *)surf->surf->pixels + Y * surf->surf->pitch/4 + X));
			break;
		}
		return mxRGB((Uint32)-1);
	}

	void CopySurface(mxSurface *surf, int x, int y, int w, int h, int x2, int y2, int w2, int h2) {
		SDL_Rect rc = { x,y,w,h };
		SDL_Rect rc2 = { x2,y2,w2,h2};
		SDL_BlitSurface(surf->surf, &rc, front.surf, &rc2 );
	}
	void CopySurface(mxSurface *surf, int x, int y) {
		CopySurface(surf, x,y,surf->surf->w, surf->surf->h, x,y, surf->surf->w, surf->surf->h);
	}
	void CopySurface(mxSurface *surf, int x, int y, int w, int h) {
		CopySurface(surf, x,y,w,h, x,y,w,h);
	} 

	virtual void AlphaBlend(mxSurface *one, mxSurface *two, int x, int y, int w, int h, float alpha) {
		float fr, fg, fb;
		static int i, z;
		for(i = x; i < w; i++) {
			for(z = y; z < h; z++) {
				mxRGB color = this->GetPixel(one, i,z);
				mxRGB color2 = this->GetPixel(two, i, z);
				if((fr = float ( (color.r * alpha) + (1- alpha) * color2.r)) > 255) fr = 255;
				if((fg = float ( (color.g * alpha) + (1- alpha) * color2.g)) > 255) fg = 255;
				if((fb = float ( (color.b * alpha) + (1- alpha) * color2.b)) > 255) fb = 255;
				this->SetPixel(&front, i, z, mxRGB(&front, Uint8(fr), Uint8(fg), Uint8(fb)));
			}
		}
	}
	void Quit() {
		active = false;
	}
	mxSurface *GetFront() { return &front; }
protected:
	mxSurface front;
	EventHandler *eventz;
public:
	int mouse_x, mouse_y, mouse_b;
};



#endif
