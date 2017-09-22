/* Sample MasterX SDK Driver
   written by Jared Bruni
   www.LostSideDead.com

  packaged with NuclearMediaSDK by Lee Trager
*/

#include"masterx.h"


MasterXHWND mxhwnd;// masterX hwnd

// callback functions
long _stdcall event(struct HWND__* hwnd,unsigned int msg, unsigned int wparam, long lparam);
void render(int screen);

namespace mx
{
	int frame;
	MasterGraphic intro;
	void init();
	void draw();
}

// main entry point
int _stdcall MasterMain(HINSTANCE hInst,char* line)
{
	if(mxhwnd.CreateMasterX("MasterX",640,480,COLOR_DEFAULT,event,hInst,NULL,NULL))
	{
		mx::init();
		return (mxhwnd.InitLoop(render));
	}

	return (0);
}

// initlization function
void mx::init()
{
	frame = 0;
	mxhwnd.LoadGraphic(&intro,"intro.bmp");
}

// draw function
void mx::draw()
{
	if( ++frame > 100 )
	{
		frame = 0;
	}
	intro.DisplayGraphic(0,0);
	mxhwnd.text.sprinttext(10,10, " Press Escape to Exit, Frame %i ", frame);
}

// event callback
long _stdcall event(struct HWND__* hwnd,unsigned int msg, unsigned int wparam, long lparam)
{
	switch(msg)
	{
	case WM_ACTIVATEAPP:
		mxhwnd.activeapp = wparam;
		break;
	case WM_KEYDOWN:
		{
			switch(wparam)
			{
			case VK_ESCAPE:
				mxhwnd.Kill();
				break;
			}
		}
		break;
	default: return DefWindowProc(hwnd,msg,wparam,lparam);
	}

	return (0);
}

// render callback
void render(int screen)
{
	mx::draw();
}