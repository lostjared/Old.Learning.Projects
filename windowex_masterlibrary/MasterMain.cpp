//   LostSideDead.com
#include "thehead.h"


MasterXHWND mxhwnd;
Window main;

long _stdcall event(struct HWND__* hwnd,unsigned int msg,unsigned int wParam,long lParam);
void render(MASTERSCREEN screen);
inline void init();


int _stdcall MasterMain(struct HINSTANCE__* hInst, char* line) 
{
	mxhwnd.HideCursor();

	if(mxhwnd.CreateMasterX("MasterX",640,480,COLOR_DEFAULT,event,hInst,NULL,NULL))
	{
		init();
		return mxhwnd.InitLoop(render);
	}

	return (0);
}

inline void init()
{
 	mxhwnd.InitTimer(1,1);
	main.load();
	main.setpos(100,100,200,200);
	main.setwindowtitle("Hello World");
	ShowCursor(true);
}




long _stdcall event(struct HWND__* hwnd,unsigned int msg,unsigned int wParam,long lParam)
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

// render to the screen in 2D
void render(MASTERSCREEN screen)
{
	mxhwnd.SetTimeFlag();// set the time flag
	main.update();
}
