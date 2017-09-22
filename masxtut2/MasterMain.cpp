// MasterX Skeleton
// MasterX SDK written by Jared Bruni

#include "masterx.h"

// MasterX Window Message Process Prototype
long __stdcall MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void update(MASTERSCREEN screen);
void LoadGraphics();

MasterXHWND mxhwnd;
MasterGraphic graphic;
MasterGraphic graphic_key;

// MasterX Program Entry Point
int __stdcall MasterMain(HINSTANCE hInst,LPSTR line)
{
	if(mxhwnd.CreateMasterX("MasterX_Skeleton",640,480,COLOR_DEFAULT,MasterProc,hInst,LoadIcon(NULL,IDI_APPLICATION),LoadCursor(NULL,IDC_ARROW)))
	{
		LoadGraphics();
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
	mxhwnd.text.settextcolor(RGB(0,0,255));
	mxhwnd.text.printtext("Hello MasterX World w/ Graphics- Press Escape to Exit",10,10);
	graphic.DisplayGraphic(100,100);
	graphic_key.DisplayGraphic(100,100+graphic.h);
	//note: my graphics sux, make sure your color key is constant
	// photoshop with a standard brush mess it up. i am to lazy to fix
}
// Load the Applications Graphics
void LoadGraphics()
{
	mxhwnd.LoadGraphic(&graphic,"quit.bmp");
	mxhwnd.LoadGraphic(&graphic_key,"quit.bmp");
	graphic_key.SetColorKey(RGB(255,0,255));
}