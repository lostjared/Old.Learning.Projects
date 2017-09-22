

// comment out the below line if not running in debug mode
//#define MXDEBUG_MODE
#include "mxSDL.h"

/* Example of over-riding virtual mxSDL functions to customize for your needs!
class MXSDL : public mxSDL {
public:
	MXSDL(std::string name, int w, int h, int bpp, bool full) : mxSDL(name,w,h,bpp,full) { }
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
				if(!(i >= mouse_x && i <= mouse_x + 25 && z >= mouse_y && z <= mouse_y + 25)) 
				this->SetPixel(&front, i, z, mxRGB(&front, Uint8(fr), Uint8(fg), Uint8(fb)));
				else
				this->SetPixel(&front, i, z, mxRGB(&front, rand()%255, rand()%255, rand()%255));

			}
		}
	}
};
*/
class Trippin : public EventHandler {
public:

	Trippin() {
		if(!(lsd1.LoadBMP("lsd.bmp")))
			throw ErrorMsg("Error Couldnt Load Bitmap lsd.bmp");

		if(!(lsd2.LoadBMP("lsd2.bmp")))
			throw ErrorMsg("Error Couldnt Load Bitmap lsd2.bmp");

		if(!(arial.LoadFNT("arial.mxf")))
			throw ErrorMsg("Error couldnt load mxFont arial.mxf");

	}

	virtual void Event(SDL_Event &e) {

	}
	virtual void KeyDown(int key) {
		switch(key) {
			case SDLK_ESCAPE:
				mx->Quit();
				break;
		}
	
	}
	virtual void KeyUp(int key) {
	
	}
	virtual void Render() {
		static float blend_state = 1.0f;
		mx->AlphaBlend(&lsd1, &lsd2, 0,0,640,480, blend_state);
		blend_state += 0.1f;
		mx->PrintTextSized(arial.GetFont(),0,0,25,25,mxRGB(mx->GetFront(), 0,0,0),"Alpha State %f\n Cursor Pos (%d, %d)", blend_state, mx->mouse_x, mx->mouse_y);
	}
protected:
	mxSurface lsd1, lsd2;
	mxText arial;
};



int main(int argc, char **argv) {
	try {
		mxSDL mxsdl("Trippin Alpha Blend", 640,480, 0, false);
		mxsdl.SetEvents( new Trippin );
		mxsdl.MessagePump();
	}
	catch (ErrorMsg &e) {
		e.PrintLastError();
	}
	return 0;
}
