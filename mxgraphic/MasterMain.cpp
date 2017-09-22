#define MASTERXSDK
#include"masterlibrary4.h"

long _stdcall event(struct HWND__* hwnd, unsigned int msg, unsigned int wparam, long lparam);
void render(int screen);
inline void load();

MasterXHWND mxhwnd;
MasterGraphic logo;

int _stdcall MasterMain(struct HINSTANCE__* hInst, char* line)
{
	if(mxhwnd.CreateMasterX("MasterX",640,480,COLOR_DEFAULT,event,hInst,NULL,NULL))
	{
		load();
		return mxhwnd.InitLoop(render);
	}

	return (0);
}

inline void load()
{
	mxhwnd.LoadGraphic(&logo,"logo.bmp");
	mxhwnd.HideCursor();
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
		if(wparam == VK_ESCAPE)
		{
			mxhwnd.Kill();
		}
		break;
	default: return DefWindowProc(hwnd,msg,wparam,lparam);
	}

	return (0);
}

void render(int screen)
{
	logo.DisplayGraphic(0,0);
}
