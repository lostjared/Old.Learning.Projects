// the main file
// written by jared bruni
// for planetsourcecode

#include "thehead.h"

MasterXHWND mxhwnd;// masterX hwnd object
Intro  intro; //  intro object
Game   game; // game object



// mastermain entry point
int _stdcall MasterMain(HINSTANCE hInst,LPSTR cmdline)
{

	// create MasterX
	if(mxhwnd.CreateMasterX("CharANI",640,480,COLOR_DEFAULT,MasterProc,hInst,LoadIcon(NULL,IDI_APPLICATION),LoadCursor(NULL,IDC_ARROW)))
	{
		intro.init(&mxhwnd);
		game.init(&mxhwnd);
		intro.load();
		game.load();
		mxhwnd.SetScreen(INTRO);
		ShowCursor(false);
		return mxhwnd.InitLoop(update);// initlize program loop
	}

	return 0;
}


// master proc windows message process
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
				mxhwnd.Kill(); // kill program (exit)
				break;
			}
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

// update callback function
void update(MASTERSCREEN screen)
{
	switch(screen)
	{
	case INTRO:
		intro.update();
		break;
	case GAME:
		game.update();
		break;
	}
}