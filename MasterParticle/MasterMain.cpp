// mastermain.cpp 
// written by jared bruni
// www.lostsidedead.com
// this is the main entry point

#include "thehead.h"

MasterXHWND mxhwnd;
MasterParticle particle;
MasterIntro intro;


HFONT mfont = MakeFont("Arial",14);

// mastermain entry point
int XSTD MasterMain(HINSTANCE hInst,LPSTR line)
{
	srand(time(NULL));

	if(mxhwnd.CreateMasterX("MasterParticle",640,480,COLOR_DEFAULT,MasterProc,hInst,NULL,NULL))
	{
		mxhwnd.SetScreen(ID_INTRO);
		mxhwnd.HideCursor();
		mxhwnd.InitTimer(1,1);
		intro.load();
		particle.load();
		return mxhwnd.InitLoop(update);
	}

	return 0;
}

// masterproc, callback function
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

// update callback function
void update(MASTERSCREEN screen)
{
	mxhwnd.SetTimeFlag();
	switch(screen)
	{
	case ID_INTRO:
		intro.update();
		break;
	case ID_PARTICLE:
		particle.update();
		break;
	}
	mxhwnd.text.setfont(mfont);
	mxhwnd.text.settextcolor(0xFFFFFF);
	mxhwnd.text.setbkcolor(0x000000);
	mxhwnd.text.printtext("Press Escape to Exit..",10,10);
}