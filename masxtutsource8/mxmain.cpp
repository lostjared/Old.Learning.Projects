// mxmain.cpp
// jared bruni

#include "mxhead.h"

/*
  My Vision:

  every object while operating complety on its own, recives
  and transmits data via the MasterXHWND object. Each has a pointer
  to this object, and can switch around through it.
*/

// prototypes
long _stdcall MasterProc(HWND,UINT,WPARAM,LPARAM);
void update(MASTERSCREEN screen);

// global variables
MasterXHWND mxhwnd;
mgcintro    mxintro;
mgcgame     mxgame;
mgcover     mxover;

// master main entry point
int _stdcall MasterMain(HINSTANCE hInst,LPSTR line)
{
	if(mxhwnd.CreateMasterX("Win32_MXExample",640,480,COLOR_DEFAULT,MasterProc,hInst,LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1)),LoadCursor(hInst,MAKEINTRESOURCE(IDC_CURSOR1))))
	{
		mxintro.init(&mxhwnd);
		mxgame.init(&mxhwnd);
		mxover.init(&mxhwnd);
		mxintro.setsub(INTRO_START);
		mxover.setsub(GAME_START);
		mxgame.setsub(OVER_SCREEN);
		mxintro.loadgraphics();
		mxgame.loadgraphics();
		mxover.loadgraphics();
		mxhwnd.SetScreen(INTRO);
		return mxhwnd.InitLoop(update);
	}

	return 0;
}
// master window proccess
long _stdcall MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
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
				{
#ifdef iDEBUG
					mxhwnd.Kill();
#endif
				}
				break;
			}

		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}
// the update call back function
void update(MASTERSCREEN screen)
{
	switch(screen)
	{
	case INTRO:
		mxintro.update();
		break;
	case GAME:
		mxgame.update();
		break;
	case OVER:
		mxover.update();
		break;
	}

#ifdef iDEBUG // indebug mode
	mxhwnd.text.printtext("Working in Debug Mode",10,10);
	mxhwnd.text.printtext("http://www.lostsidedead.com/gameprog/",10,30);
	mxhwnd.text.printtext("jaredbruni",10,60);
#endif
}

