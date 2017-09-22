// MasterX SDK 1.5 Blank Game Skeleton
// written by Jared Bruni
// www.lostsidedead.com
// please visit my site, and click on the banners



#include "masterx.h"


// comment out iDEBUG for release mode
#define iDEBUG 

// the MasterXHWND object
MasterXHWND mxhwnd;
HFONT  mFont = MakeFont("Arial",14);



// callback functions
long _stdcall MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void update(MASTERSCREEN screen);

// master main entry point
int _stdcall MasterMain(HINSTANCE hInst,LPSTR cmdline)
{
	if(mxhwnd.CreateMasterX("MasterXSkeleton",640,480,COLOR_DEFAULT,MasterProc,hInst,NULL,NULL))
	{
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

	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

// update callback function
void update(MASTERSCREEN screen)
{
	
	// after the update, print out this message, if its in debug mode that is
#ifdef iDEBUG

	mxhwnd.text.settextcolor(RGB(200,0,0));
	mxhwnd.text.setfont(mFont);
	mxhwnd.text.printtext("Current Running in Debug Mode - Press Escape to Exit",10,10);
#endif

}