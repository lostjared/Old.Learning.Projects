#include"mx3d.h"
#include<string>
#include<cstdio>

namespace mx3d {

	class mxColor {
	public:
		unsigned char r,g,b;

		mxColor(unsigned char r, unsigned char g, unsigned char b) {
			this->r = r, this->g = g, this->b = b;
		}
		mxColor() {
			r = g = b = 0;
		}
		// copy color
		void operator=(mxColor &c) {
			this->r = c.r, this->g = c.g, this->b = c.b;
		}
		D3DCOLOR toD3D() {
			return D3DCOLOR_XRGB(r,g,b);
		}

		COLORREF toCol() {
			return RGB(r,g,b);
		}
	};

	class mxTexture {
	public:
		int width, height;
		

		mxTexture() {
			pbits = 0;
			color_key = 0xFF00FF;
		}
		~mxTexture() {
			if(pbits)
				delete [] pbits;
		}
		
		// Copy texture 
		void operator=(mxTexture &t) {
			if(pbits)
				delete [] pbits;
			pbits = new mxColor [t.width*t.height];
			this->width = t.width;
			this->height = t.height;
			for(int c = 0; c < t.width*t.height; c++) {
				pbits[c] = t.pbits[c];
			}
		}

		void SetPixel(int x, int y, mxColor &c) {
			pbits[y*width+x] = c;
		}

		mxColor &GetPixel(int x, int y) {
			return pbits[y*width+x];
		}

		
		bool LoadBMP(std::string source) {
			FILE *fptr = 0;
			long offset, size;
			short type, bitcount;
			if(pbits) {
				delete [] pbits;
				pbits = 0;
			}

			fptr = fopen(source.c_str(),"rb");
			if(!fptr)
				return false;
			fread(&type, sizeof(short), 1, fptr);
			if(type != 0x4D42) {
				fclose(fptr);
				return false;
			}

			fseek(fptr, 10, SEEK_SET);
			fread(&offset, sizeof(long), 1, fptr);
			fseek(fptr, 4, SEEK_CUR);
			fread(&width, sizeof(long), 1, fptr);
			fread(&height, sizeof(long), 1, fptr);
			fseek(fptr, 2, SEEK_CUR);
			fread(&bitcount, sizeof(short), 1, fptr);
			if(bitcount != 24) {
				fclose(fptr);
				return false;
			}
			fseek(fptr, 4, SEEK_CUR);
			fread(&size, sizeof(long), 1, fptr);
			fseek(fptr,16,SEEK_CUR);
			pbits = new mxColor [ width * height ];
			if(!pbits) {
				fclose(fptr);
				return false;
			}
			int i = 0;
			int x, y,q;

			for(y = height-1; y > -1; y--)
			{
				for(x = 0; x < width; x++)
				{
					q = x + y * width;
					pbits[q].b = fgetc(fptr);
					pbits[q].g = fgetc(fptr);
					pbits[q].r = fgetc(fptr);
				}
				for(i = 0; i < width % 4; i++)
					fgetc(fptr);
			}

			fclose(fptr);
			return true;
		}

		D3DCOLOR getPixel(int x, int y) {
			return pbits[x+y*width].toD3D();
		}

		void SetColorKey(D3DCOLOR color_key) {
			this->color_key = color_key;
			color_key_active = true;
		}

		void RemoveColorKey() {
			color_key = 0xFF00FF;
			color_key_active = false;
		}

		void BltBuffer(int x, int y, int w, int h, mxHwnd *mx) {
			mx->paint.Lock();
			int bx = 0, by = 0;
			if(x >= 0 && y >= 0)
			for(int i = x, bx = 0; i < w; i++, bx++)
			{
				for(int z = y, by = 0; z < h; z++, by++)
				{
					if(i < mx->w && z < mx->h ) {

						D3DCOLOR color = getPixel(bx,by);
						if(color_key_active == true && color != color_key)
						mx->paint.fast_sp(i,z,mx->paint.rect.Pitch, color);
						else if(color_key_active == false)
						mx->paint.fast_sp(i,z,mx->paint.rect.Pitch, color);

					}
				}
			}
			mx->paint.UnLock();
		}

		void BltBuffer(int x, int y, mxHwnd *mx) {
			BltBuffer(x,y,x+width,y+height,mx);
		}

		void StretchBuffer(int x, int y, int nw, int nh, mxHwnd *mx) {

			mx->paint.Lock();
			int bx = 0, by = 0;
			if(x >= 0 && y >= 0)
			for(int i = x, bx = 0; i < nw; i++, bx++)
			{
				for(int z = y, by = 0; z < nh; z++, by++)
				{
					if(i < mx->w && z < mx->h) {
						D3DCOLOR the_color = GetStretchPixel(bx,by,nw,nh);
						if(color_key_active == true && color_key != the_color)
						mx->paint.fast_sp(i,z,mx->paint.rect.Pitch, the_color);
						else if(color_key_active == false)
						mx->paint.fast_sp(i,z,mx->paint.rect.Pitch, GetStretchPixel(bx,by,nw,nh));
					}
				}
			}
			mx->paint.UnLock();

		}
		mxColor *GetBits() {
			return pbits;
		}

		mxColor *operator[](int pos) {
			return &pbits[pos];
		}

		bool color_key_active;
		D3DCOLOR color_key;

		D3DCOLOR GetStretchPixel(int x, int y, int nw, int nh) {
			int xp = int((float)x * float(width) / (float)nw);
			int yp = int((float)y * float(height) / (float)nh);
			D3DCOLOR buffer_pos = pbits[yp*width+xp].toD3D();
			return buffer_pos;
		}
		
		mxColor &getStretchPixel(int x, int y, int nw, int nh) {
			int xp = int((float)x * float(width) / (float)nw);
			int yp = int((float)y * float(height) / (float)nh);
			return pbits[yp*width+xp];
		}

		// alpha blend this texture (assumes they are both the same size, and the back buffer is locked)
		void AlphaBlend(int x, int y,int w, int h, mxHwnd &mx, mxTexture &tex, float alpha) {
			static float fr,gr,br;
			static unsigned char r,g,b;
			static mxColor c,l;

			for(int i = 0; i < w; i++) 
				for(int z = 0; z < h; z++) {
					c = GetPixel(i,z);
					l = tex.GetPixel(i,z);
					if((fr = ( alpha * c.r ) + (( 1- alpha) * l.r)) > 255) fr = 255;
					if((gr = ( alpha * c.g ) + (( 1- alpha) * l.g)) > 255) gr = 255;
					if((br = ( alpha * c.b ) + (( 1- alpha) * l.b)) > 255) br = 255;
					r = unsigned char(fr), g = unsigned char(gr), b = unsigned char(br);
					mx.paint.fast_sp(i+x,y+z,mx.paint.rect.Pitch,D3DCOLOR_XRGB(r,g,b));
				}
		}

		void AlphaBlend(int x, int y, mxHwnd &mx, mxTexture &tex, float alpha) {
			AlphaBlend(x,y,tex.width,tex.height,mx,tex,alpha);
		}
		// add light through another texture ( assumes they are both the same size) and that the back buffer is locked
		void Light(int x, int y, int w, int h,  mxHwnd &mx, mxTexture &tex, float scale) {
			static float fr,gr,br;
			static unsigned char r,g,b;
			static mxColor c,l;
			for(int i = 0; i < w; i++)
				for(int z = 0; z < h; z++) {
					c = GetPixel(i,z);
					l = tex.GetPixel(i,z);
					if((fr = c.r + (scale * l.r)) > 255) fr = 255;
					if((gr = c.g + (scale * l.g)) > 255) gr = 255;
					if((br = c.b + (scale * l.b)) > 255) br = 255;
					r = unsigned char(fr) , g = unsigned char (gr), b = unsigned char(br);
					mx.paint.fast_sp(i+x,y+z,mx.paint.rect.Pitch, D3DCOLOR_XRGB(r,g,b));
				}
		}

		void Light(int x, int y, mxHwnd &mx, mxTexture &tex, float scale) {
			Light(x,y,tex.width,tex.height,mx,tex,scale);
		}

		mxColor *pbits;
	};


}