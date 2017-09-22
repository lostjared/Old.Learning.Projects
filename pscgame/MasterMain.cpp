// psc cd - the game
// written by jared bruni
// www.lostsidedead.com

#include "thehead.h"


MasterXHWND mxhwnd;

// game objects
Intro intro;
Game game;
Over over;
Player player;
PSCParticleEmiter pscemiter;
Cannon cannon;

int _stdcall MasterMain(HINSTANCE hInst ,char* line)
{
	if(mxhwnd.CreateMasterX("PSCCD",640,480,COLOR_DEFAULT,MasterProc,hInst,NULL,NULL))
	{
		intro.load();
		game.load();
		over.load();
		pscemiter.load();
		cannon.load();

		mxhwnd.InitTimer(1,1);
		mxhwnd.HideCursor();
		mxhwnd.SetScreen (ID_INTRO);
		return mxhwnd.InitLoop(update);
	}

	return 0;
}



long XSTD MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
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
			if(wParam == VK_ESCAPE)
			{
				mxhwnd.Kill();
				break;
			}
			else
			{
			
				switch(mxhwnd.GetScreen())
				{
				case ID_INTRO:
					intro.keypress(wParam);
					break;
				case ID_GAME:
					cannon.keypress(wParam);
					break;
				case ID_OVER:
					over.keypress(wParam);
					break;
				}

			}
		}
		break;

	case WM_TIMER:
		{
			mxhwnd.ChangeTime();
		}
		break;
		
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}


void update(MASTERSCREEN screen)
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
	case ID_OVER:
		over.update();
		break;
	}
}