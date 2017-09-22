/* masterLibrary2 -example
   written by Jared Bruni
   www.LostSideDead.com

  here is a example on how to incorperate 
  the changes made to the variables
  which control what is being drawn on the screen
  thats all, to help who ever I can
  
	email me; master@lostsidedead.com
*/

#define Sync if(mxhwnd.SyncChange())
#define MASTERXSDK
#include "masterlibrary2.h"

MasterXHWND mxhwnd;

long _stdcall event(struct HWND__* hwnd, unsigned int msg, unsigned int wparam ,long lparam);
void render(int screen);
inline void init();
inline void draw();
inline void logic();

int rw = 0, rh = 0;

struct twistedcolor {

	int r;
	int g;
	int b;

	COLORREF getcolor()
	{
		return (RGB(r,g,b));
	}

	COLORREF getcolor2()
	{
		return RGB(b,g,r);
	}

	inline twistedcolor()
	{
		r = 0;
		g = 0;
		b = 0;
	}

	inline twist()
	{
		r += rand()%5;
		g += rand()%5;
		b += rand()%5;

		if(r >= 255)
			clear();
	}

	inline clear()
	{
		r = 0, g = 0, b = 0;
	}
};

twistedcolor mcolor;

int _stdcall MasterMain(struct HINSTANCE__* hinst, char* line)
{
	if(mxhwnd.CreateMasterX("MasterTrip",640,480,COLOR_DEFAULT,event,hinst,NULL,NULL))
	{

	init();

	return mxhwnd.InitLoop(render);

	}


	return (0);
}


inline void init()
{
	mxhwnd.HideCursor();
	mxhwnd.InitTimer(1,1);
}



long _stdcall event(struct HWND__* hwnd, unsigned int msg, unsigned int wparam ,long lparam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ACTIVATEAPP:
		mxhwnd.activeapp = wparam;
		break;
	case WM_KEYDOWN:
		{
			if(wparam == VK_ESCAPE)
				mxhwnd.Kill();
	
		}
		break;
	case WM_TIMER:
		{
			mxhwnd.ChangeTime ();
		}
		break;
	default: return DefWindowProc(hwnd,msg,wparam,lparam);
	}

	return (0);
}

void render(int screen)
{
	mxhwnd.SetTimeFlag();
	draw();
	Sync
	{
		logic();
	}


}

inline void draw()
{
	mxhwnd.paint.mxdrawrect(0,0,rw,rh,mcolor.getcolor2(),mcolor.getcolor2());
	mxhwnd.text.setbkcolor(mcolor.getcolor2());
	mxhwnd.text.settextcolor(mcolor.getcolor());
	mxhwnd.text.printtext("press escape to exit",10,10);

}


inline void logic()
{
	mcolor.twist();
	rw += 1;
	rh += 1;

	if(rw >= 640+300 || rh >= 480+300)
	{
		rw = 0;
		rh = 0;
	}
}