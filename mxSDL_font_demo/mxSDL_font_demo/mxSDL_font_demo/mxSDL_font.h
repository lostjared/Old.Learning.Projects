#ifndef _MXFONT_H_
#define _MXFONT_H_
#include "mxSDL_msg.h"
#include "mxSDL.h"

class mxSDL;
class mxSurface;

inline int getRval(int x) {
    return (unsigned char) x;   
}
inline int getGval(int x) {
       return (unsigned char) (unsigned int) x >> 8;
}
inline int getBval(int x) {
       return ((unsigned char)((x)>>16));
}
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

bool read_font(struct mxFont *m, const char *font_name) {
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
			zero<mxFont>(m);
			init_font(m,20,25,0x0);
			file.close();
			return false;
		}
	}

	return true;
}

class mxText  {
public:
	friend class mxSDL;
	mxText(std::string fnt_name) {
		loaded = LoadFNT(fnt_name);
		if(!(loaded))
			throw ErrorMsg(std::string("Error Couldnt load Font ") + fnt_name + "\n");
	}

	mxText() {
		loaded = false;
		zero(&m);
	}
	~mxText() {
		if(loaded == true) {
			free_font(&m);
		}
	}
	bool LoadFNT(std::string fnt_name) {
		return (loaded = read_font(&m, fnt_name.c_str()));
	}

	void FreeFNT() {
		if(loaded == true) {
			free_font(&m);
		}
	}

	void TextureMap(mxSDL &mx, mxSurface *tex) {
		this->mx = &mx, this->surf = tex;
	}

	mxFont *GetFont() { return &m; }
protected:
	mxFont m;
	mxSurface *surf;
	mxSDL *mx;
	bool loaded;
};

#endif