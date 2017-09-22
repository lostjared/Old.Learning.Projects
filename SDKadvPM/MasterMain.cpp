// MasterX SDK 1.5  Example on using the Mouse, and the text and paint Objects
// written by Jared Bruni
// www.lostsidedead.com
// please visit my site, and click on the banners

// this example just does some game concepts
// messes around with some of the things it can do


#include "masterx.h"


// comment out iDEBUG for release mode
#define iDEBUG 

// the MasterXHWND object
MasterXHWND mxhwnd;
HFONT  mFont = MakeFont("Arial",14);
HFONT  gFont = MakeFont("Arial",50);


// enumerated constants for Screen Id's
enum { ID_INTRO , ID_MAIN };

// program functions
void IntroUpdate();
void MainUpdate();
// other functions
void DrawDummy();
void DummyKeyCheck();


// variables
int color_fade = 0;
bool color_dir = true;
int orb_w = 50;
int orb_h = 50;
int dummy_x = 50;
int dummy_y = 50;


// callback functions
long _stdcall MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void update(MASTERSCREEN screen);

// master main entry point
int _stdcall MasterMain(HINSTANCE hInst,LPSTR cmdline)
{
	if(mxhwnd.CreateMasterX("MasterXSkeleton",640,480,COLOR_DEFAULT,MasterProc,hInst,NULL,NULL))
	{
		mxhwnd.HideCursor();
		mxhwnd.SetScreen(ID_INTRO);
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
	case WM_LBUTTONDOWN:
		{
			 
			dummy_x = LOWORD(lParam);
			dummy_y = HIWORD(lParam);
			
		}
		break;

	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

// update callback function
void update(MASTERSCREEN screen)
{

	switch(screen)
	{
	case ID_INTRO:
		IntroUpdate();
		break;
	case ID_MAIN:
		MainUpdate();
		break;
	}

	
	// after the update, print out this message, if its in debug mode that is
#ifdef iDEBUG
	mxhwnd.text.setbkcolor(0x000000);
	mxhwnd.text.settextcolor(RGB(200,0,0));
	mxhwnd.text.setfont(mFont);
	mxhwnd.text.printtext("Current Running in Debug Mode - Press Escape to Exit",10,10);
#endif

}

// do cool intro animation
// intro update
void IntroUpdate()
{

	mxhwnd.paint.mxdrawrect(0,0,640,480,RGB(color_fade,color_fade,color_fade),RGB(color_fade,color_fade,color_fade));

	if(color_dir)
	{
		color_fade++;
		orb_w++;
		orb_h++;

		if(color_fade > 255)
		{
			color_fade = 255;
			
			color_dir = false;
		}
	}
	else
	{
		color_fade--;
		orb_w--;
		orb_h--;
		if(color_fade < 0)
		{
			color_fade = 0;
			color_dir = true;
		}
	}

	mxhwnd.text.setbkcolor(RGB(color_fade,color_fade,color_fade));
	mxhwnd.text.settextcolor(RGB(200,0,0));
	mxhwnd.text.setfont(gFont);
	mxhwnd.text.printtext("Press Enter to Continue",100,300);

	mxhwnd.paint.mxdrawellipse(100,100,100+orb_w,100+orb_h,RGB(rand()%255,rand()%255,rand()%255),RGB(rand()%255,rand()%255,rand()%255));


	for(int j = 0; j < 5; j++) 
	{
		mxhwnd.paint.mxarc(rand()%640,rand()%640,rand()%640,rand()%640,rand()%640,rand()%640,rand()%640,rand()%640,RGB(rand()%255,rand()%255,rand()%255),RGB(rand()%255,rand()%255,rand()%255));
	}

	for(int i = 0; i < 200; i++)
	{
		mxhwnd.paint.mxsetpixel(rand()%640,rand()%480,RGB(rand()%255,rand()%255,rand()%255));
	}

	
	if(mxhwnd.KeyCheck(DIK_RETURN))
	{
		mxhwnd.RestoreCursor();
		mxhwnd.SetScreen(ID_MAIN);
	}

}

// main update
void MainUpdate()
{
	mxhwnd.text.setfont(mFont);
	mxhwnd.text.settextcolor(0xFFFFFF);
	mxhwnd.text.setbkcolor(0x000000);
	mxhwnd.text.printtext("use the arrow keys to move around the object, or just point and click to move it to that location",10,30);

	DrawDummy();
	DummyKeyCheck();
}

// draw the dummy
void DrawDummy()
{
	mxhwnd.paint.mxdrawellipse(dummy_x,dummy_y,dummy_x + 50,dummy_y + 50,0xFFFFFF,0xFFFFFF);
	mxhwnd.paint.mxdrawrect(dummy_x + 10,dummy_y + 20,dummy_x + 10 + 30,dummy_y + 20 + 100,0xFFFFFF,0xFFFFFF);
	mxhwnd.paint.mxdrawrect(dummy_x - 50,dummy_y + 50,dummy_x+10,dummy_y + 70,0xFFFFFF,0xFFFFFF);
	mxhwnd.paint.mxdrawrect(dummy_x + 10 + 30,dummy_y + 50,dummy_x + 10 + 30 + 60,dummy_y + 50 + 20,0xFFFFFF,0xFFFFFF);
}
// keycheck for the dummy
void DummyKeyCheck()
{
	if(mxhwnd.KeyCheck(DIK_UP))
	{
		dummy_y = dummy_y - 5;
	}
	
	if(mxhwnd.KeyCheck(DIK_DOWN))
	{
		dummy_y = dummy_y + 5;	
	}

	if(mxhwnd.KeyCheck(DIK_LEFT))
	{
		dummy_x = dummy_x - 5;
	}

	if(mxhwnd.KeyCheck(DIK_RIGHT))
	{
		dummy_x = dummy_x + 5;
	}
}
