// MasterX Skeleton
// MasterX SDK written by Jared Bruni

#include "masterx.h"

// MasterX Window Message Process Prototype
long __stdcall MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void update(MASTERSCREEN screen);

MasterXHWND mxhwnd;

// MasterX Program Entry Point
int __stdcall MasterMain(HINSTANCE hInst,LPSTR line)
{
	if(mxhwnd.CreateMasterX("MasterX_Skeleton",640,480,COLOR_DEFAULT,MasterProc,hInst,LoadIcon(NULL,IDI_APPLICATION),LoadCursor(NULL,IDC_ARROW)))
	{
		return mxhwnd.InitLoop(update);
	}
	return 0;
}

// MasterX Window Message Process Defenition Body
long __stdcall MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_ACTIVATEAPP:
		mxhwnd.activeapp = wParam;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
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
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

void update(MASTERSCREEN screen)
{
	mxhwnd.text.printtext("Hello MasterX World - Press Escape to Exit",10,10);

}