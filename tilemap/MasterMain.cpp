// master main
// for planetosurcecode
// written by jared bruni
// www.lostsidedead.com

#include "thehead.h"

MasterXHWND mxhwnd;// master host object
Intro intro; // intro object
Game  game; // game object


// entry point
int _stdcall MasterMain(HINSTANCE hInst,LPSTR line)
{
	if(mxhwnd.CreateMasterX("TileMap",640,480,COLOR_DEFAULT,MasterProc,hInst,LoadIcon(NULL,IDI_APPLICATION),LoadCursor(NULL,IDC_ARROW)))
	{
		intro.init(&mxhwnd);
		game.init(&mxhwnd);
		intro.onload();
		game.onload();
		mxhwnd.SetScreen(INTRO);
		ShowCursor(false);
		return mxhwnd.InitLoop(update);
	}

	return 0;
}


// master proc (message proccess) callback function
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
					mxhwnd.Kill();
				}
				break;
			}
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

// screen update callback function
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

	// if we are debugging display debug information

#ifdef iDEBUG
	mxhwnd.text.setbkcolor(RGB(0,0,0));
	mxhwnd.text.setfont(d_font);
	mxhwnd.text.settextcolor(RGB(200,0,0));
	mxhwnd.text.printtext("debug mode - press escape to exit",10,10);
#endif

}
