/* MasterRPG Alpha 2 Level Editor
   written by Jared Bruni
   www.LostSideDead.com

  "Open Source, Open Mind"
*/

#include"thehead.h"

MasterXHWND mxhwnd;
Intro intro;
Game game;


inline void load();

int __stdcall MasterMain(struct HINSTANCE__* hInst, char* line)
{

	if(mxhwnd.CreateMasterX("MasterX",640,480,COLOR_DEFAULT,event,hInst,NULL,NULL))
	{
		load();
		return (mxhwnd.InitLoop(render));
	}
	return (0);
}

inline void load()
{

#ifndef WIN2K
	mxhwnd.InitTimer(1,1);
#else
	mxhwnd.InitTimer(1,50);
#endif

	ShowCursor(false);
	ShowCursor(true);

	intro.load();
	game.load();
}

long _stdcall event(struct HWND__* hwnd, unsigned int msg, unsigned int wparam, long lparam)
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

		switch(wparam)
		{
		case VK_ESCAPE:
			mxhwnd.Kill();
			break;
		}

		switch(mxhwnd.GetScreen())
		{
		case ID_GAME:
			game.keypress(wparam);
			break;
		}

		}
		break;
	case WM_TIMER:
		{
			mxhwnd.ChangeTime();
		}
		break;
	case WM_LBUTTONDOWN:
		{

			switch(mxhwnd.GetScreen())
			{
			case ID_GAME:
				game.leftclick(LOWORD(lparam),HIWORD(lparam));
				break;
			}
		}
		break;
	case WM_RBUTTONDOWN:
		{
		//	game.fill();

		}
		break;
	case WM_MOUSEMOVE:
		{
			switch(mxhwnd.GetScreen())
			{
			case ID_GAME:
				game.mousemove(LOWORD(lparam),HIWORD(lparam),wparam);
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
	mxhwnd.SetTimeFlag();
	switch(screen)
	{
	case ID_INTRO:
		intro.update();
		break;
	case ID_GAME:
		game.update();
		break;
	}
}
