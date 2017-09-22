// ok here we go
// written by jared bruni

#include "masterx.h"


long _stdcall MasterProc(HWND,UINT,WPARAM,LPARAM);
void update(MASTERSCREEN screen);

MasterXHWND mxhwnd;

int circle_x = 0;
int circle_y = 0;
int speed = 5;
int frame_rate = 0;



int _stdcall MasterMain(HINSTANCE hInst,LPSTR line)
{
	if(mxhwnd.CreateMasterX("Hello",640,480,COLOR_DEFAULT,MasterProc,hInst,LoadIcon(NULL,IDI_APPLICATION),LoadCursor(NULL,IDC_ARROW)))
	{
		ShowCursor(false);
		return mxhwnd.InitLoop(update);
	}


	return 0;
}


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
				mxhwnd.Kill();
				break;
			}
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

// update call back
void update(MASTERSCREEN screen)
{
	mxhwnd.text.settextcolor(RGB(0,0,255));
	mxhwnd.text.printtext("Hello World",10,10);
	mxhwnd.paint.mxdrawellipse(circle_x,circle_y,circle_x+100,circle_y+100,RGB(rand()%255,rand()%255,rand()%255),RGB(rand()%255,rand()%255,rand()%255));

	if(mxhwnd.KeyCheck(DIK_RIGHT))
	{
		if(circle_x < 640-100)
		{

		circle_x = circle_x + speed;
		
		}
	}

	if(mxhwnd.KeyCheck(DIK_DOWN))
	{
		circle_y = circle_y + speed;
	}

	if(mxhwnd.KeyCheck(DIK_LEFT))
	{
		circle_x = circle_x - speed;
	}

	if(mxhwnd.KeyCheck(DIK_UP))
	{
		circle_y = circle_y - speed;
	}

	frame_rate ++;

	char frate[10];
	itoa(frame_rate,frate,10);
	char therate[100];
	strcpy(therate,"The Frame: ");
	strcat(therate,frate);

	if(frame_rate > 50)
	{
		frame_rate = 0;
	}

	mxhwnd.text.printtext(therate,10,30);

	

}