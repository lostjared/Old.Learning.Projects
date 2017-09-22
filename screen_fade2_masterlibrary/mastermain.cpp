/* Screen Fade Example #2
   written by Jared Bruni
   www.LostSideDead.com

  "Open Source, Open Mind"
 */


#define Sync if(mxhwnd.SyncChange()) 
#define MASTERXSDK
#include "masterlibrary2.h"
#include<time.h>


MasterXHWND mxhwnd;
long _stdcall event(struct HWND__* hwnd,unsigned int msg,unsigned int wParam,long lParam);
void render(MASTERSCREEN screen);
inline void init();
inline void draw();
inline void logic();

int r = 0, g = 0, b = 0;
bool dir = true;

int _stdcall MasterMain(struct HINSTANCE__* hInst, char* line) 
{
	if(mxhwnd.CreateMasterX("MasterX",640,480,COLOR_DEFAULT,event,hInst,NULL,NULL))
	{
		init();
		return mxhwnd.InitLoop(render);
	}

	return (0);
}

inline void init()
{
	srand(time(NULL));
	mxhwnd.HideCursor();
	mxhwnd.InitTimer(1,1);
}



long _stdcall event(struct HWND__* hwnd,unsigned int msg,unsigned int wParam,long lParam)
{

	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ACTIVATEAPP:
		mxhwnd.activeapp = wParam;
		break;
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_ESCAPE:
				mxhwnd.Kill();
				break;
			}
		}
		break;
	case WM_TIMER:
		{
			mxhwnd.ChangeTime();// you can use whatever type of clock
			// or timer you want to change the time for the sync changes
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return (0);
}

void render(MASTERSCREEN screen)
{
	mxhwnd.SetTimeFlag();// set the time flag
	draw();
	Sync // new defined sync keyword
	{
		logic();
	}
}

// draw
inline void draw()
{
	mxhwnd.paint.mxdrawrect(0,0,640,480,RGB(r,g,b),RGB(r,g,b));
	mxhwnd.text.setbkcolor(RGB(r,g,b));
	mxhwnd.text.settextcolor(RGB(255,0,0));
	mxhwnd.text.printtextrectf(0,0,640,480,"Screen Fade Example\nwritten by Jared Bruni\nwww.LostSideDead.com\npress escape to exit\n");
}


// example of synchrnoized logic
// with the new defined Sync keyword
inline void logic()
{
	if(dir == true)
	{

		r += rand()%5;
		g += rand()%5;
		b += rand()%5;

	if(r >= 255)
	{
		r = 255;
		g = 255;
		b = 255;
		dir = false;
	}

	}
	else
	{
	
		r -= rand()%5;
		g -= rand()%5;
		b -= rand()%5;

		if(r <= 0)
		{
			r = 0;
			g = 0;
			b = 0;
			dir = true;
		}

	}
}

