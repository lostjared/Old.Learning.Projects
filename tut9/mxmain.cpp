// application main source module
#include "mxhead.h"

intro introobj;
game  gameobjx;
over  overobj;

// program entry point
int _stdcall MasterMain(HINSTANCE hInst,LPSTR line)
{
	if(mxhwnd.CreateMasterX("mxhwnd",640,480,COLOR_DEFAULT,MasterProc,hInst,LoadIcon(NULL,IDI_APPLICATION),LoadCursor(NULL,IDC_ARROW)))
	{
		introobj.init(&mxhwnd);
		gameobjx.init(&mxhwnd);
		overobj.init(&mxhwnd);
		introobj.setsub(INTRO_ANI);
		mxhwnd.SetScreen(INTRO);
		ShowCursor(false);
		return mxhwnd.InitLoop(update);
	}
	return 0;
}
// window message proccess
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

// update
void update(MASTERSCREEN screen)
{

	switch(screen)
	{
	case INTRO:
		introobj.update();
		break;
	case GAME:
		gameobjx.update();
		break;
	case OVER:
		overobj.update();
		break;
	}

#ifdef iDEBUG
	mxhwnd.text.printtext("Debug - Press Escape to Exit",10,10);
#endif
}
