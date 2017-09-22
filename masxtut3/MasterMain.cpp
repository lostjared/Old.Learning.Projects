// MasterX Skeleton
// MasterX SDK written by Jared Bruni

#include "masterx.h"

// MasterX Window Message Process Prototype
long __stdcall MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void update(MASTERSCREEN screen);
void LoadGraphics();
void DrawIntro();
void DrawMain();

MasterXHWND mxhwnd;
MasterGraphic intro_graphic[4];
MasterGraphic quit_graphic;
int intro_index = 0;


enum { INTRO = 1, MAIN };

// MasterX Program Entry Point
int __stdcall MasterMain(HINSTANCE hInst,LPSTR line)
{
	if(mxhwnd.CreateMasterX("MasterX_Skeleton",640,480,COLOR_DEFAULT,MasterProc,hInst,LoadIcon(NULL,IDI_APPLICATION),LoadCursor(NULL,IDC_ARROW)))
	{
		LoadGraphics();
		mxhwnd.SetScreen(INTRO);
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

				switch(mxhwnd.GetScreen())
				{
				case INTRO:
					mxhwnd.SetScreen(MAIN);
					break;
				}

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
	switch(screen)
	{
	case INTRO:
		DrawIntro();
		break;
	case MAIN:
		DrawMain();
		break;
	}
}
// Load the Applications Graphics
void LoadGraphics()
{
	mxhwnd.LoadGraphic(&intro_graphic[0],"ani_1.bmp");
	mxhwnd.LoadGraphic(&intro_graphic[1],"ani_2.bmp");
	mxhwnd.LoadGraphic(&intro_graphic[2],"ani_3.bmp");
	mxhwnd.LoadGraphic(&intro_graphic[3],"ani_4.bmp");
	mxhwnd.LoadGraphic(&quit_graphic,"quit.bmp");
	quit_graphic.SetColorKey(RGB(255,0,255));

}

// Drawing the Intro Screen Animation
void DrawIntro()
{
	mxhwnd.text.printtext("drawing the introduction screen animation press enter to go to next screen",10,10);
	intro_graphic[intro_index].DisplayGraphic(10,30);
	

	intro_index++;

	if(intro_index > 3)
	{
		intro_index = 0;
	}
}

// Drawing the Main
void DrawMain()
{
	mxhwnd.text.printtext("drawing the main screen. press escape to exit",10,10);
	quit_graphic.DisplayGraphic(10,30);
}
