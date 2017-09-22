/* Sample Driver written by Jared Bruni
   www.LostSideDead.com
   "Open Source, Open Mind"
*/


#include "masterx.h"


MasterXHWND mxhwnd;
MasterGraphicEx intro;


RECT clip_rect;
float scale_factor = 10.0;
bool size_go = true;
bool bg_color = true;





void render(int screen);
long _stdcall event(struct HWND__* hwnd,unsigned int msg, unsigned int wparam, long lparam);
inline void cleanup();
inline void init();


int _stdcall MasterMain(struct HINSTANCE__* hInst,char* line)
{
	if(mxhwnd.CreateMasterX("MxSkeleton",640,480,COLOR_DEFAULT,event,hInst,NULL,NULL))
	{
		init();
		return (mxhwnd.InitLoop(render));
	}

	return (0);
}


inline void init()
{
	mxhwnd.HideCursor();
	mxhwnd.LoadGraphic(&intro,"intro.bmp");
	
    clip_rect.left = 640/30; 
	clip_rect.top = 480/30;
	clip_rect.right = clip_rect.left + 640 - (640/15);
	clip_rect.bottom = clip_rect.top + 480 - (480/15);


}

inline void cleanup()
{
	mxhwnd.Kill();
}



long _stdcall event(struct HWND__* hwnd,unsigned int msg, unsigned int wparam, long lparam)
{
	switch(msg)
	{
	case WM_ACTIVATEAPP:
		mxhwnd.activeapp = wparam;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		{
			switch(wparam)
			{
			case VK_ESCAPE:
				{
					cleanup();
				}
				break;
			}

		}
		break;

	default: return DefWindowProc(hwnd,msg,wparam,lparam);
	}

	return (0);
}

void render(int screen)
{
	int scale_width = int(640*scale_factor);
	int scale_height = int(480*scale_factor);

	bg_color = !bg_color;
	if(bg_color == true)
	{
		mxhwnd.paint.mxdrawrect(0,0,640,480,RGB(255,255,255),RGB(255,255,255));
	}
	else
	{
		mxhwnd.paint.mxdrawrect(0,0,640,480,RGB(0,0,0),RGB(0,0,0));
	}

	//draw the graphic
	intro.DisplayGraphic_scale_clip ((640>>1) - (scale_width>>1), (480>>1) - (scale_height>>1), 	scale_width, scale_height,&clip_rect );

	if(size_go == true)
	{
		scale_factor -= .5;
		if(scale_factor <= 1.0f)
		{
			scale_factor = 1.0f;
			size_go = false;
		}
	}
	else
	{
		scale_factor += .5;
		if(scale_factor >= 10.0f)
		{
			scale_factor = 10.0f;
			size_go = true;
		}
	}

}
