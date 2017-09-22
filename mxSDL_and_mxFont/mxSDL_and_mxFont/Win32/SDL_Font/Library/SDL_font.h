#ifndef _SDL_FONT_H_
#define _SDL_FONT_H_
#include<SDL.h>
#include<iostream>
#include<fstream>
#include<string>
#include<cstdarg>

inline int SDL_getRval(int x) {
	return (unsigned char) x;   
}
inline int SDL_getGval(int x) {
	return (unsigned char) (unsigned int) x >> 8;
}
inline int SDL_getBval(int x) {
	return ((unsigned char)((x)>>16));
}


inline void SDL_SetPixel(SDL_Surface *surf, int x, int y, Uint32 the_color) {
		Uint8 *ubuff8;
		Uint16 *ubuff16;
		Uint32 *ubuff32;
		Uint32 color = the_color;
		char c1, c2, c3;
		if(SDL_MUSTLOCK(surf)) {
			if(SDL_LockSurface(surf) < 0)
				return;
		}

		switch(surf->format->BytesPerPixel)
		{
		case 1:
			ubuff8 = (Uint8*) surf->pixels;
			ubuff8 += (y * surf->pitch) + x;
			*ubuff8 = (Uint8) color;
			break;

		case 2:
			ubuff8 = (Uint8*) surf->pixels;
			ubuff8 += (y * surf->pitch) + (x*2);
			ubuff16 = (Uint16*) ubuff8;
			*ubuff16 = (Uint16) color;
			break;

		case 3:
			ubuff8 = (Uint8*) surf->pixels;
			ubuff8 += (y * surf->pitch) + (x*3);
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
			ubuff8 = (Uint8*) surf->pixels;
			ubuff8 += (y*surf->pitch) + (x*4);
			ubuff32 = (Uint32*)ubuff8;
			*ubuff32 = color;
			break;
		default:
			std::cerr << "Error Unknown BitDepth!\n";
		}
		if(SDL_MUSTLOCK(surf)) {
			SDL_UnlockSurface(surf);
		}
	}

struct SDL_Font {
	int mx;
	int my;
	int tcolor;
	struct letter {
		int **fnt_ptr;
	};
	letter letters[128];
};

inline int SDL_GetFX(SDL_Font *m,int x, int nw) {
	int xp = int((float)x * float(m->mx) / (float)nw);		
	return int(xp);
}

inline int SDL_GetFZ(SDL_Font *m, int y, int nh) {
	int yp = int((float)y * float(m->my) / (float)nh);			
	return int(yp);
}



template<class type>
void SDL_zero(type *t) {
	memset((void*)t, 0, sizeof(type));
}

void SDL_free_font(struct SDL_Font *m) {

	SDL_zero<SDL_Font>(m);
	for(int l = 0; l <= 127; l++)
		if(m->letters[l].fnt_ptr)
			for(int i = 0; i < m->mx; i++)
				delete [] m->letters[l].fnt_ptr[i];

	m->mx = 0;
	m->my = 0;
}
void SDL_init_font(SDL_Font *m, int width, int height, int color) {
	SDL_free_font(m);
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

void SDL_write_font(struct SDL_Font *m, char *font_name) {
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

bool SDL_read_font(struct SDL_Font *m, const char *font_name) {
	std::fstream file;
	int mx , my;
	SDL_free_font(m);
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
				SDL_init_font(m,20,25,0x0);
				return false;
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
			return true;
		}
		else {
			SDL_zero<SDL_Font>(m);
			SDL_init_font(m,20,25,0x0);
			file.close();
			return false;
		}
	}

	return true;
}

void SDL_PrintText(SDL_Surface *front, SDL_Font *m, int x, int y,Uint32 color,const char *str, ...) {
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
					SDL_SetPixel(front, offset_x+i, offset_y+z, color);
					width=i;
					if(height < z)
						height=z;
				}
			}       

		}
		offset_x += width;
	}
}

void SDL_PrintTextSized(SDL_Surface *front, SDL_Font *m, int x, int y, int w, int h,Uint32 color, const char *str, ...) {
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
				if(m->letters[text[p]].fnt_ptr[SDL_GetFX(m,i,w)][SDL_GetFZ(m,z,h)] != m->tcolor) {
					SDL_SetPixel(front, offset_x+i, offset_y+z, color);
					width=i;
					if(height < z)
						height=z;
				}
			}       
		}
		offset_x += width;
	}
}

class SDL_Text  {
public:
	SDL_Text(std::string fnt_name) {
		loaded = LoadFNT(fnt_name);
	}

	SDL_Text() {
		loaded = false;
		SDL_zero(&m);
	}
	~SDL_Text() {
		if(loaded == true) {
			SDL_free_font(&m);
		}
	}
	bool LoadFNT(std::string fnt_name) {
		return (loaded = SDL_read_font(&m, fnt_name.c_str()));
	}

	void FreeFNT() {
		if(loaded == true) {
			SDL_free_font(&m);
		}
	}

	SDL_Font *GetFont() { return &m; }
protected:
	SDL_Font m;
	bool loaded;
};

#endif