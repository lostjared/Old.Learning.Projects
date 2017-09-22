/* PSC CD The Game 2 
   written by Jared Bruni
   www.LostSideDead.com
*/


#include "thehead.h"
#define WIN2K


MasterXHWND mxhwnd;// the MasterXHWND 
MasterProgram prog;

long _stdcall event(struct HWND__* hwnd,unsigned int msg,unsigned int wParam,long lParam);
void render(MASTERSCREEN screen);
inline void init();

int _stdcall MasterMain(struct HINSTANCE__* hInst, char* line) 
{
	mxhwnd.setfullflag(false);
	if(mxhwnd.CreateMasterX("PSCCD2",640,480,COLOR_DEFAULT,event,hInst,NULL,NULL))
	{
		init();
		return mxhwnd.InitLoop(render);
	}

	return (0);
}

inline void init()
{
	prog.load();
	mxhwnd.HideCursor();

#ifndef WIN2K
	mxhwnd.InitTimer(1,1);
#else
	mxhwnd.InitTimer(1,50);
#endif

	mxhwnd.SetScreen(ID_INTRO);
}



long _stdcall event(struct HWND__* hwnd,unsigned int msg,unsigned int wParam,long lParam)
{

	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ACTIVATEAPP:
		__mxhwnd.active = wParam;
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
	case WM_TIMER:
		{
			mxhwnd.ChangeTime();// you can use whatever type of clock
			// or timer you want to change the time for the sync changes
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return (0);
}

void render(MASTERSCREEN screen)
{
	mxhwnd.SetTimeFlag();// set the time flag
	prog.update();
}