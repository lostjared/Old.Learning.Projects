#define MASTERXSDK
#include"masterlibrary4.h"

long _stdcall event(struct HWND__* hwnd, unsigned int msg, unsigned int wparam, long lparam);
void render(int screen);
void draw1();
void draw2();
void draw3();
 
MasterXHWND mxhwnd;

enum { ID_SCREEN1 = 1, ID_SCREEN2, ID_SCREEN3 };

int _stdcall MasterMain(struct HINSTANCE__* hInst, char* line)
{
	if(mxhwnd.CreateMasterX("MasterX",640,480,COLOR_DEFAULT,event,hInst,NULL,NULL))
	{
		mxhwnd.HideCursor();
		mxhwnd.SetScreen(ID_SCREEN1);
 		return mxhwnd.InitLoop(render);
	}

	return (0);
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

		switch(wparam)
		{
		case VK_SPACE:
			{
				switch(mxhwnd.GetScreen())
				{
				case ID_SCREEN1:
					mxhwnd.SetScreen(ID_SCREEN2);
					break;
				case ID_SCREEN2:
					mxhwnd.SetScreen(ID_SCREEN3);
					break;
				case ID_SCREEN3:
					mxhwnd.SetScreen(ID_SCREEN1);
					break;
				}
			}
			break;
		}
		break;
	default: return DefWindowProc(hwnd,msg,wparam,lparam);
	}

	return (0);
}

void render(int screen)
{
	switch(screen)
	{
	case ID_SCREEN1:
		{
			draw1();
		}
		break;
	case ID_SCREEN2:
		{
			draw2();
		}
		break;
	case ID_SCREEN3:
		{
			draw3();
		}
		break;
	}
}

void draw1()
{
	mxhwnd.text.printtext("Hello Press Space to Jump to Next Screen - (1)", 10, 10);
}

void draw2()
{
	mxhwnd.text.printtext("Press Space to Jump to Screen 3 - (2) ",10,10);
}

void draw3()
{
	mxhwnd.text.printtext("Press Space to Jump to Screen 1 - (3) ",10,10);
}