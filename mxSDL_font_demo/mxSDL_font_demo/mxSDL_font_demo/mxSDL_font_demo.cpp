#include "mxSDL.h"

class mxSDL_font_demo : public EventHandler {
public:
	mxSDL_font_demo() {
		if(!(textures[0].LoadBMP("texture1.bmp")))
			throw ErrorMsg("Error loading texture!");
		if(!(textures[1].LoadBMP("texture2.bmp")))
			throw ErrorMsg("Error loading texture!");

		if(!(fonts[0].LoadFNT("arial.mxf")))
			throw ErrorMsg("Error loading Font!");
		if(!(fonts[1].LoadFNT("serif.mxf")))
			throw ErrorMsg("Error loading Font!");
		if(!(fonts[2].LoadFNT("broadway.mxf")))
			throw ErrorMsg("Error loading Font!");
		if(!(fonts[3].LoadFNT("fixedsys.mxf")))
			throw ErrorMsg("Error loading Font!");

		fonts[0].TextureMap(*mx,&textures[0]);
		fonts[1].TextureMap(*mx,&textures[1]);
		fonts[2].TextureMap(*mx,&textures[0]);
		fonts[3].TextureMap(*mx,&textures[1]);
	}

	virtual void Render() {
		mx->PrintTexturedText(&fonts[0], 0,0, 50,50, "This is a test of\nTextured PrintText");
		mx->PrintTexturedText(&fonts[1], 0,150, 35, 35, "Test #2");
		mx->PrintTexturedText(&fonts[2], 0,250, 50, 50, "Test #3");
		mx->PrintTexturedText(&fonts[3], 0,300, 35, 35, "Test #4");
	}
protected:
	mxSurface textures[2];
	mxText fonts[4];

};

int main(int argc, char **argv) {
	try {
		mxSDL mxsdl("mxSDL_Font_Demo",640,480,0,false);
		mxsdl.SetEvents( new mxSDL_font_demo );
		mxsdl.MessagePump();
	}
	catch (ErrorMsg &e) {
		e.PrintLastError();
	}
	return 0;
}