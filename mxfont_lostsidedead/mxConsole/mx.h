
#ifndef _MX_H_
#define _MX_H_

#include<stdio.h>
#include<stdlib.h>
#include<SDL\SDL.h>
#include<SDL\SDL_image.h>
#include<SDL\SDL_timer.h>
#include<assert.h>
#include<memory.h>
#include<fstream>
#include<stdarg.h>

inline int getRval(int x) {
    return (unsigned char) x;   
}

inline int getGval(int x) {
       return (unsigned char) (unsigned int) x >> 8;
}
inline int getBval(int x) {
       return ((unsigned char)((x)>>16));
}

// wrapper class
class mxHwnd {

	void (*renderscr)(int screen);
	void (*keyfunc)(int key);
	void (*keyfuncup)(int key);
	void (*mousemove)(int x, int y);
	void (*mousedown)(int button, int x, int y);
	void (*onevent)(SDL_Event *ievent);
	void (*key_idle)();

	int scr,exitok;
	int is_fullscreen;

public:
    int wx,hx;
	SDL_Surface *pscr;

	int setfullscreen(int fullscreen,char *title, int width, int height, int bpp)
	{
		SDL_FreeSurface(pscr);
		if(fullscreen == 0)
			pscr = SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE|SDL_ANYFORMAT|SDL_FULLSCREEN);
		else
			pscr = SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE|SDL_ANYFORMAT);

		if(!pscr)
		{
			fprintf(stderr, "Couldn't create a surface: %s\n",SDL_GetError());
			return -1;
		}
		SDL_WM_SetCaption(title, NULL);
		printf("SDL Surface Created %x\n", pscr);
		printf("Successfully initalized\n");
		scr = 0;
		is_fullscreen = fullscreen;
		return 0;
	}

	int isFullScreen() const
	{
		return is_fullscreen;
	}

	int init(char *title, int width, int height, int bpp, bool fullscreen)
	{
		if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0 )
		{
			fprintf(stderr, "Could not initialize SDL: %s\n",SDL_GetError());
			return -1;
		}
		atexit(SDL_Quit);
		if(fullscreen == true)
			pscr = SDL_SetVideoMode(width, height, bpp, SDL_ANYFORMAT|SDL_FULLSCREEN);
		else
			pscr = SDL_SetVideoMode(width, height, bpp, SDL_ANYFORMAT);

		if(!pscr)
		{
			fprintf(stderr, "Couldn't create a surface: %s\n",SDL_GetError());
			return -1;
		}
		SDL_WM_SetCaption(title, NULL);
		printf("SDL Surface Created %x\n", pscr);
		printf("Successfully initalized\n");
		scr = 0;

		keyfunc = 0,keyfuncup = 0,mousemove = 0,mousedown = 0,onevent = 0,exitok = 1,key_idle = 0;
		is_fullscreen = (int)fullscreen;
		wx = width;
		hx = height;
		SDL_EnableUNICODE(1);
		return 0;
	}

	void setKeydown(void(*keyfuncx)(int key))
	{
		keyfunc = keyfuncx;
	}
	
	void setKeyidle(void(*keyid)()) {
         key_idle = keyid;        
    }

	int getScreen() { return scr; }
	void setScreen(int scr) { this->scr = scr; }

	void setKeyup(void(*keyfuncupx)(int key))
	{
		keyfuncup = keyfuncupx;
	}

	void setMouseMove(void (*mousemovex)(int x, int y))
	{
		mousemove = mousemovex;
	}

	void setMouseDown(void(*mousedownx)(int button, int x, int y))
	{
		mousedown = mousedownx;
	}

	void setEventHandler(void (*oneventx)(SDL_Event *ievent))
	{
		onevent = oneventx;
	}

	void clear()
	{
		SDL_Rect rect = {0, 0, pscr->w, pscr->h};
		SDL_FillRect(pscr, &rect, 0);
	}

	int initLoop(void (*rendery)(int screen))
	{
		renderscr = rendery;
		SDL_Event event;

		while(exitok == 1)
		{
			clear();
			renderscr(scr);
			while(SDL_PollEvent(&event))
			{
				switch( event.type )
				{
				case SDL_QUIT:
					printf("Quit called!\n");
					exitok = 0;
					break;
				case SDL_KEYDOWN:
					if(keyfunc != 0)
					{
						keyfunc(event.key.keysym.unicode);
					}
					break;
				case SDL_KEYUP:
					if(keyfuncup != 0)
					{
						keyfuncup(event.key.keysym.sym);
					}
					break;
				case SDL_MOUSEMOTION:
					if(mousemove != 0)
						mousemove(event.motion.x,event.motion.y);
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(mousedown != 0)
						mousedown(event.button.button,event.button.x,event.button.y);
					break;
				}
				if(onevent != 0)
					onevent(&event);
				if(key_idle)
				key_idle();
			}
		}

		SDL_FreeSurface(pscr);
		SDL_Quit();

		return 1;
	}

	void kill()
	{
		exitok = 0;
	}

	void setPixel(SDL_Surface *screen, int x, int y, Uint8 r, Uint8 g, Uint8 b)
	{
		Uint8 *ubuff8;
		Uint16 *ubuff16;
		Uint32 *ubuff32;
		Uint32 color;
		char c1, c2, c3;

		/* Lock the screen, if needed */
		if(SDL_MUSTLOCK(screen)) {
			if(SDL_LockSurface(screen) < 0)
				return;
		}

		/* Get the color */
		color = SDL_MapRGB( screen->format, r, g, b );

		/* How we draw the pixel depends on the bitdepth */
		switch(screen->format->BytesPerPixel) 
		{
		case 1:
			ubuff8 = (Uint8*) screen->pixels;
			ubuff8 += (y * screen->pitch) + x;
			*ubuff8 = (Uint8) color;
			break;

		case 2:
			ubuff8 = (Uint8*) screen->pixels;
			ubuff8 += (y * screen->pitch) + (x*2);
			ubuff16 = (Uint16*) ubuff8;
			*ubuff16 = (Uint16) color;
			break;

		case 3:
			ubuff8 = (Uint8*) screen->pixels;
			ubuff8 += (y * screen->pitch) + (x*3);


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
			ubuff8 = (Uint8*) screen->pixels;
			ubuff8 += (y*screen->pitch) + (x*4);
			ubuff32 = (Uint32*)ubuff8;
			*ubuff32 = color;
			break;

		default:
			fprintf(stderr, "Error: Unknown bitdepth!\n");
		}

		/* Unlock the screen if needed */
		if(SDL_MUSTLOCK(screen)) {
			SDL_UnlockSurface(screen);
		}
	}

	void setPixel(SDL_Surface *screen, int x, int y, Uint32 color)
	{
		Uint8 *ubuff8;
		Uint16 *ubuff16;
		Uint32 *ubuff32;
		char c1, c2, c3;

		/* Lock the screen, if needed */
		if(SDL_MUSTLOCK(screen)) {
			if(SDL_LockSurface(screen) < 0)
				return;
		}

		/* Get the color */
		//color = SDL_MapRGB( screen->format, r, g, b );

		/* How we draw the pixel depends on the bitdepth */
		switch(screen->format->BytesPerPixel)
		{
		case 1:
			ubuff8 = (Uint8*) screen->pixels;
			ubuff8 += (y * screen->pitch) + x;
			*ubuff8 = (Uint8) color;
			break;

		case 2:
			ubuff8 = (Uint8*) screen->pixels;
			ubuff8 += (y * screen->pitch) + (x*2);
			ubuff16 = (Uint16*) ubuff8;
			*ubuff16 = (Uint16) color;
			break;

		case 3:
			ubuff8 = (Uint8*) screen->pixels;
			ubuff8 += (y * screen->pitch) + (x*3);


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
			ubuff8 = (Uint8*) screen->pixels;
			ubuff8 += (y*screen->pitch) + (x*4);
			ubuff32 = (Uint32*)ubuff8;
			*ubuff32 = color;
			break;

		default:
			fprintf(stderr, "Error: Unknown bitdepth!\n");
		}

		/* Unlock the screen if needed */
		if(SDL_MUSTLOCK(screen)) {
			SDL_UnlockSurface(screen);
		}
	}

	Uint32 getPixel(SDL_Surface *Surface, Sint32 X, Sint32 Y)
	{
		Uint8  *bits;
		Uint32 Bpp;

		assert(X>=0);
		assert(X<Surface->w);

		Bpp = Surface->format->BytesPerPixel;
		bits = ((Uint8 *)Surface->pixels)+Y*Surface->pitch+X*Bpp;

		// Get the pixel
		switch(Bpp) {
case 1:
	return *((Uint8 *)Surface->pixels + Y * Surface->pitch + X);
	break;
case 2:
	return *((Uint16 *)Surface->pixels + Y * Surface->pitch/2 + X);
	break;
case 3: { // Format/endian independent 
	Uint8 r, g, b;
	r = *((bits)+Surface->format->Rshift/8);
	g = *((bits)+Surface->format->Gshift/8);
	b = *((bits)+Surface->format->Bshift/8);
	return SDL_MapRGB(Surface->format, r, g, b);
		}
		break;
case 4:
	return *((Uint32 *)Surface->pixels + Y * Surface->pitch/4 + X);
	break;
		}
		return (Uint32)-1;
	}

};

// base class for objects
class mxObject {

public:
	void init(mxHwnd *mx)
	{
		this->mx = mx;
	}
	mxHwnd *mx;
};

// Wrapper around SDL_Surface for bitmaps
class mxSprite : public mxObject {

public:
	SDL_Surface *sptr;

	mxSprite()
	{
		sptr = 0;
	}
	~mxSprite()
	{
		if(sptr != 0)
			SDL_FreeSurface(sptr);
		sptr = 0;
	}

	bool load(mxHwnd *mx, const char *str)
	{
		this->mx = mx;
		return load(str);
	}

	bool load(const char *str)
	{
		sptr = SDL_LoadBMP(str);
		if(sptr == 0)
		{
			fprintf(stderr, "Unable to load bitmap..%s\n",str);
			return false;
		}
		else 
			return true;
	}

	bool load(const char *str, int r, int g, int b)
	{
		sptr = SDL_LoadBMP(str);
		if(sptr == 0)
		{
			fprintf(stderr, "Unable to load bitmap ..%s", str);
			return false;
		}
		SDL_SetColorKey(sptr , SDL_SRCCOLORKEY,SDL_MapRGB(sptr->format, r,g,b));

		return true;
	}

	void display(class mxHwnd *mxhwnd, int x, int y, int x2, int y2, int w, int h)
	{
		SDL_Rect src;
		SDL_Rect dest;
		src.x = x2;
		src.y = y2;
		src.w = w;
		src.h = h;
		dest.x = x; dest.y = y;
		dest.w = h;
		dest.h = w;
		SDL_BlitSurface(sptr,&src,mxhwnd->pscr,&dest);
	}

	void display(class mxHwnd *mxhwnd, int x, int y)
	{
		display(mxhwnd,x,y,0,0,sptr->w,sptr->h);
	}

	// requires a call to init before use
	void display(int x, int y, int x2, int y2, int w, int h)
	{
		this->display(mx,x,y,x2,y2,w,h);
	}
	// same with this one
	void display(int x, int y)
	{
		this->display(mx,x,y);
	}

};


/*
// Wrapper around SFont
class mxFont : public mxObject {
public:
	SFont_Font* Font;

	mxFont()
	{
		Font = 0;
	}

	~mxFont()
	{
		if(Font != 0)
			SFont_FreeFont(Font);
	}

	void load(mxHwnd *mx, const char *sfont)
	{
		this->mx = mx;
		Font = SFont_InitFont(BMP_Load(sfont));
		if(!Font)
		{
			fprintf(stderr, "An error occured while loading the font.");
			exit(1);
		}

	}
	void printText(int x, int y, const char *str)
	{
		SFont_Write (mx->pscr, Font, x,y,str);
	}

};
*/

class mxPaint : public mxObject {

public:
	void drawRect(int x, int y, int x2, int y2, Uint32 color)
	{
		SDL_Rect rect = {x, y, x2, y2};
		SDL_FillRect(mx->pscr, &rect, color);
	}
};


struct mxFont {
	int mx;
	int my;
	int tcolor;
	struct letter {
	int **fnt_ptr;
	};
	letter letters[128];
};

template<class type>
void zero(type *t) {
	memset((void*)t, 0, sizeof(type));
}

void free_font(struct mxFont *m) {
	
	zero<mxFont>(m);
		for(int l = 0; l <= 127; l++)
		if(m->letters[l].fnt_ptr)
	for(int i = 0; i < m->mx; i++)
		delete [] m->letters[l].fnt_ptr[i];

		m->mx = 0;
		m->my = 0;
}
void init_font(mxFont *m, int width, int height, int color) {
	free_font(m);
	//zero<mxFont>(m);
	m->mx = width;
	m->my = height;
	for(int l = 0; l <= 127; l++) {
	m->letters[l].fnt_ptr = new int*[width];
	for(int p = 0; p < width; p++) {
		m->letters[l].fnt_ptr[p] = new int[height];
	}
	for(int i = 0; i < width; i++) {
		for(int z = 0; z < height; z++) {
			m->letters[l].fnt_ptr[i][z] = color;
		}
	}
	}

	m->tcolor = 0x0;
}

void write_font(struct mxFont *m, char *font_name) {
	std::fstream file;
	file.open(font_name, std::ios::binary | std::ios::out);
	if(file.is_open()) {
		int q = -100;
	file.write((char*)&q,sizeof(int));
	file.write((char*)&m->mx, sizeof(int));
	file.write((char*)&m->my, sizeof(int));
	file.write((char*)&m->tcolor,sizeof(int));
	for(int l = 0; l < 127; l++)
	for(int i = 0; i < m->mx; i++) 
		for(int z = 0; z < m->my; z++)
			file.write((char*)&m->letters[l].fnt_ptr[i][z], sizeof(int));
	file.close();
	}
}

void read_font(struct mxFont *m, char *font_name) {
	std::fstream file;
	int mx , my;
	free_font(m);
	file.open(font_name, std::ios::binary | std::ios::in);
	if(file.is_open() && file.good()) {
		int q = 0;
	file.read((char*)&q,sizeof(int));
	if(q == -100) {
	file.read((char*)&mx, sizeof(int));
	file.read((char*)&my, sizeof(int));
	file.read((char*)&m->tcolor, sizeof(int));
	m->mx = mx;
	m->my = my;
	if(mx < 0 || mx < 0 || mx > 250 || my > 250) {
		file.close();
		init_font(m,20,25,0x0);
		return;
	}
	for(int l = 0; l <= 127; l++) {
	m->letters[l].fnt_ptr = new int*[mx];
	for(int p = 0; p < mx; p++) {
		m->letters[l].fnt_ptr[p] = new int[my];
	}
	for(int i = 0; i < m->mx; i++)
		for(int z = 0; z < m->my; z++)
			if(!file.eof() && file.good())
	file.read((char*)&m->letters[l].fnt_ptr[i][z], sizeof(int));
	}
	file.close();
	}
	else {
		zero<mxFont>(m);
		init_font(m,20,25,0x0);
		file.close();
	}
	}
}


bool SDL_printtextf(mxFont *m, mxHwnd *mx, int x, int y, char *str, ...) {
     int prev_x = x;
     int offset_x = prev_x, offset_y = y;
     int width = 0, height = 0;
     
     char text[5000];
     va_list list;
     va_start(list, str);
     vsprintf((char*)text,str,list);
     va_end(list);
     
     for(unsigned int p = 0; p < strlen(text); p++) {
                    if(text[p] == '\n') {
                     offset_x  = prev_x;
                     offset_y += height;
                     if(offset_y+height >= mx->hx) 
                     return false;
                     continue;
                     }
                     if(offset_x >= mx->wx) {
                     offset_x = prev_x;
                     offset_y += height;
                     }
                     
                     for(int i = 0; i < m->mx; i++) {
                              for(int z = 0; z < m->my; z++) {
                     
                              if(m->letters[text[p]].fnt_ptr[i][z] != m->tcolor) {
                             mx->setPixel(mx->pscr, offset_x+i, offset_y+z,SDL_MapRGB(mx->pscr->format,getRval(m->letters[text[p]].fnt_ptr[i][z]),getGval(m->letters[text[p]].fnt_ptr[i][z]),getBval(m->letters[text[p]].fnt_ptr[i][z]))); 
                             width=i;
                             if(height < z)
                             height=z;
                    }
             }       
             
     }
     offset_x += width;
     }
     
     return true;
}



#endif
