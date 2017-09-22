// mxmain
// jared bruni
// http://www.lostsidedead.com/gameprog/
#include "mxhead.h"

#define iDEBUG

long _stdcall MasterProc(HWND,UINT,WPARAM,LPARAM);
void update(MASTERSCREEN screen);

MasterXHWND mxhwnd;
dprog prog;

// program entry point
int _stdcall MasterMain(HINSTANCE hInst,LPSTR line)
{
	if(mxhwnd.CreateMasterX("MasterPainting",640,480,COLOR_DEFAULT,MasterProc,hInst,LoadIcon(NULL,IDI_APPLICATION),LoadCursor(NULL,IDC_ARROW)))
	{
		prog.init(&mxhwnd);
		return mxhwnd.InitLoop(update);
	}
	return 0;
}

// update callback function
void update(MASTERSCREEN screen)
{
	prog.update();
}

// the window message proccess
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

