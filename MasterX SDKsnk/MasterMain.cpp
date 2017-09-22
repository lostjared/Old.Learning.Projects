// MasterX SDK 1.6  Sync Logic
// written by Jared Bruni
// www.lostsidedead.com
// please visit my site, and click on the banners


// this example just does some game concepts
// this draws at the best frame rate,
// but changes based on the interval of the timer


#include "masterx.h"


// comment out iDEBUG for release mode
#define iDEBUG 

// the MasterXHWND object
MasterXHWND mxhwnd;

// the fonts
HFONT mFont = MakeFont("Arial",14);

// variables/structures
struct switchcounter {

	int x;
	bool dir;

};

switchcounter fadered;
 

 
// callback functions
long _stdcall MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void update(MASTERSCREEN screen);

// functions
void ondraw();
void onload();
void onsynclogic();
 


// master main entry point
int _stdcall MasterMain(HINSTANCE hInst,LPSTR cmdline)
{
	if(mxhwnd.CreateMasterX("MasterXSkeleton",640,480,COLOR_DEFAULT,MasterProc,hInst,NULL,NULL))
	{
		onload();
		mxhwnd.InitTimer(1,10); // Interval of 10 
		return mxhwnd.InitLoop(update);
	}
	return 0;

}

// masterproc message proccess
long _stdcall MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ACTIVATEAPP:
		{
			mxhwnd.activeapp = wParam;
		}
		break;
#ifdef iDEBUG
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
#endif
 	case WM_TIMER:
		{
			mxhwnd.ChangeTime();
		}
		break;

	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

// update callback function
void update(MASTERSCREEN screen)
{

	ondraw();
	mxhwnd.SetTimeFlag();
	if(mxhwnd.SyncChange())
	{


	onsynclogic();

	}

	
	// after the update, print out this message, if its in debug mode that is
#ifdef iDEBUG
	mxhwnd.text.setbkcolor(RGB(rand()%255,rand()%255,rand()%255));
	mxhwnd.text.settextcolor(RGB(200,0,0));
	mxhwnd.text.setfont(mFont);
	mxhwnd.text.printtext("Current Running in Debug Mode - Press Escape to Exit",10,10);
#endif

}

// on program load
void onload()
{
	fadered.x = 0;
	fadered.dir = true;
}

// on draw update
void ondraw()
{
	mxhwnd.paint.mxdrawrect(0,0,640,480,RGB(fadered.x,0,0),RGB(fadered.x,0,0));

	if(mxhwnd.KeyCheck(DIK_UP))
	{
		long x;
		long y;

		mxhwnd.GetMousePosWin(x,y);
		SetCursorPos(x,y - 2);
	}

	if(mxhwnd.KeyCheck(DIK_LEFT))
	{
		long x;
		long y;

		mxhwnd.GetMousePosWin(x,y);
		SetCursorPos(x - 2,y);
	}

	if(mxhwnd.KeyCheck(DIK_DOWN))
	{
		long x;
		long y;

		mxhwnd.GetMousePosWin(x,y);
		SetCursorPos(x,y +  2);
	}

	if(mxhwnd.KeyCheck(DIK_RIGHT))
	{
		long x;
		long y;

		mxhwnd.GetMousePosWin(x,y);
		SetCursorPos(x + 2,y);
	}

}
 
// on logic update
void onsynclogic()
{
	if(fadered.dir)
	{
		fadered.x = fadered.x + 5;
		if(fadered.x > 255)
		{
			fadered.x = 255;
			fadered.dir = false;
		}
	}
	else
	{
		fadered.x = fadered.x - 5;
		if(fadered.x < 0)
		{
			fadered.x = 0;
			fadered.dir = true;
		}
	}
}


