// MasterX SDK 1.7 example
// using MasterJoystick
// written by jared bruni
// www.lostsidedead.com

#include "masterx.h"


// comment out iDEBUG for release mode
#define iDEBUG 

// the MasterXHWND object
MasterXHWND mxhwnd;

HFONT mFont = MakeFont("Arial",14);
  
// callback functions
long _stdcall MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void update(MASTERSCREEN screen);

void ondraw();
void onlogic();


enum { ID_SCREEN1 = 0, ID_SCREEN2 };

MasterJoyStick stick;// joystick data structure

int obj_x = 20;
int obj_y = 20;
int addsize = 50;



// master main entry point
int _stdcall MasterMain(HINSTANCE hInst,LPSTR cmdline)
{
	if(mxhwnd.CreateMasterX("MasterXSkeleton",640,480,COLOR_DEFAULT,MasterProc,hInst,NULL,NULL))
	{
		if(!stick.SetupJoystick())
		{
			ShowWindow(mxhwnd.hwnd,SW_HIDE);
			MessageBox(0,"Error you must have atleast 1 joystick","Error , no joystick",MB_OK | MB_ICONERROR);
			mxhwnd.Kill();
		
			return 0;
		}
		mxhwnd.HideCursor();
		mxhwnd.InitTimer(1,2);
		mxhwnd.SetScreen(ID_SCREEN1);
		return mxhwnd.InitLoop(update);
	}
	return 0;

}

// masterproc message proccess
long _stdcall MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ACTIVATEAPP:
		{
			mxhwnd.activeapp = wParam;
		}
		break;
#ifdef iDEBUG
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
#endif
	case WM_TIMER:
		{
			mxhwnd.ChangeTime();

		}
		break;
 
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

// update callback function
void update(MASTERSCREEN screen)
{
	mxhwnd.SetTimeFlag();
	ondraw();

	// after the update, print out this message, if its in debug mode that is
#ifdef iDEBUG
	mxhwnd.text.setbkcolor(RGB(rand()%255,rand()%255,rand()%255));
	mxhwnd.text.settextcolor(RGB(200,0,0));
	mxhwnd.text.setfont(mFont);
	mxhwnd.text.printtext("Current Running in Debug Mode - Press Escape to Exit",10,10);
	mxhwnd.text.printtext("use the joystick to move the square, press 1 and 2 to change size",10,25);
#endif

}


// on program draw
void ondraw()
{
	mxhwnd.paint.mxdrawrect(obj_x,obj_y,obj_x + addsize,obj_y + addsize,0xFFFFFF,0xFFFFFF);
	if(mxhwnd.SyncChange())
	{

	onlogic();

	}
}

// on program logic
void onlogic()
{
	if(stick.JoyLeft())
	{
		obj_x = obj_x - 2;
	}

	if(stick.JoyRight())
	{
		obj_x = obj_x + 2;
	}

	if(stick.JoyForward())
	{
		obj_y = obj_y - 2;
	}

	if(stick.JoyBackward())
	{
		obj_y = obj_y + 2;
	}

	int bpress;
	bpress = stick.JoyButtonDown();
	if(bpress == 0) { return ; }
	switch(bpress)
	{
	case 1:
		addsize = addsize + 10;
			break;
	case 2:
		addsize = addsize - 10;
			break;
	}
}
 