// main source module

#include "thehead.h"

MasterXHWND mxhwnd;// MasterXHWND object
Intro intro;
Game  game;


// master main entry point
int _stdcall MasterMain(HINSTANCE hInst,LPSTR line)
{
	if(mxhwnd.CreateMasterX("Alien",640,480,COLOR_DEFAULT,MasterProc,hInst,LoadIcon(NULL,IDI_APPLICATION),LoadCursor(NULL,IDC_ARROW)))
	{

		intro.Init(&mxhwnd);
		game.Init(&mxhwnd);

		intro.load();
		game.load();
		ShowCursor(false);
		mxhwnd.SetScreen(INTRO);
		return mxhwnd.InitLoop(update);
	}
	return 0;
}


// master message proccess
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
				mxhwnd.Kill();
				break;
			}
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

// update proccess
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
	case OVER:
		break;
	}
}