#include "mxSDL.h"


class L : public EventHandler {
public:
	L() {
		if(!(lsd.LoadBMP("lsd.bmp")))
			throw ErrorMsg("Unable to Load Image make sure its in the directory!\n");
		dir = 0;

		reload();
	}
	virtual void Render() {

		static float random = 1.0f;

		for(unsigned int ii = 0; ii < 320; ii++) {
			for( unsigned int zz = 0; zz < 240; zz++) {
				screen[ii][zz] = screen[zz+1][ii+1];
				mx->SetPixel(mx->GetFront(), ii, zz, mxRGB(mx->GetFront(), Uint8(screen[ii][zz].r * random), Uint8(screen [ii][zz].g * random), Uint8(screen[ii][zz].b * random) ));	
				random += 0.00001f;
				if(random > 10) {
					random = 0;
				}
			}
		}

		if(dir == 1)
		mx->AlphaBlend(mx->GetFront(), &lsd, 0,0,320,240, random);
	}

	virtual void KeyDown(int key) {
		switch(key) {
			case SDLK_DOWN:
				dir = 0;
				break;
			case SDLK_UP:
				dir = 1;
				break;
		}
	}
	inline void reload() {
		
		for(unsigned int i = 0; i < 320; i++)
			for(unsigned int z = 0; z < 240; z++)
				screen[i][z] = mx->GetPixel(&lsd, i, z);
	}
protected:
	mxSurface lsd;
	int dir;
	mxRGB screen[320][240];
};

int main(int argc, char **argv) {

	try {

		mxSDL mxsdl("mxSDL_hallicunation", 320,240, 0, false);
		mxsdl.SetEvents ( new L );
		mxsdl.MessagePump();

	} catch ( ErrorMsg &e ) {
		e.PrintLastError();
	}

	return 0;
}