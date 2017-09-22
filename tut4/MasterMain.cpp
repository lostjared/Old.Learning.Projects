// MasterX Skeleton
// MasterX SDK written by Jared Bruni

#include "masterx.h"
#include "resource.h"

// MasterX Window Message Process Prototype
long __stdcall MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void update(MASTERSCREEN screen);
void LoadSound();
void LoadGraphics();

MasterXHWND mxhwnd;
MasterSound mxsound;
MasterGraphic mgraphic;

int mgraphic_x = 0;
int mgraphic_y = 0;


// MasterX Program Entry Point
int __stdcall MasterMain(HINSTANCE hInst,LPSTR line)
{
	if(mxhwnd.CreateMasterX("MasterX_Skeleton",640,480,COLOR_DEFAULT,MasterProc,hInst,LoadIcon(NULL,IDI_APPLICATION),LoadCursor(NULL,IDC_ARROW)))
	{
		LoadSound();
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
			case 13:

				mxsound.Play();

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

	if(mxhwnd.KeyCheck(DIK_LEFT))
	{
		mgraphic_x--;
		if(mgraphic_x < 0)
		{
			mgraphic_x = 0;
		}
	}
	if(mxhwnd.KeyCheck(DIK_RIGHT))
	{
		mgraphic_x++;
		if(mgraphic_x > 640-mgraphic.w)
		{
			mgraphic_x = 640-mgraphic.w;
		}
	}
	if(mxhwnd.KeyCheck(DIK_DOWN))
	{
		mgraphic_y++;
		if(mgraphic_y >  480-mgraphic.h)
		{
			mgraphic_y = 480-mgraphic.h;
		}
	}

	if(mxhwnd.KeyCheck(DIK_UP))
	{
		mgraphic_y--;
		if(mgraphic_y < 0)
		{
			mgraphic_y = 0;
		}
	}



	mgraphic.DisplayGraphic(mgraphic_x,mgraphic_y);
	mxhwnd.text.printtext("Press escape to exit, and arrow keys to move the image, enter to play a sound",10,10);
}

void LoadSound()
{
	mxhwnd.LoadSound(&mxsound,MAKEINTRESOURCE(IDR_WAVE1));
}

void LoadGraphics()
{
	mxhwnd.LoadGraphic(&mgraphic,"quit.bmp");
	mgraphic.SetColorKey(RGB(255,0,255));
}
