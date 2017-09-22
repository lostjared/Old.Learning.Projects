// example on using multiple cursors
// written by jared bruni
// www.lostsidedead.com

#include "masterx.h"

// the MasterXHWND object
MasterXHWND mxhwnd;

// variables
HCURSOR cur[4];
int colorx = 0;
bool colordir = true;
HFONT mfont = MakeFont("Arial",14);

enum GAMECURSOR { ARROW = 0, MAG, HAND };

GAMECURSOR curcursor = MAG;
GAMECURSOR mycursor = MAG;


// callback function prototypes
long XSTD EventProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void frame_update(MASTERSCREEN screen);
// other function prototypes
void loadcursors();
void setcursor(GAMECURSOR cursor);
void mousemove(int x, int y);
void leftclick(int x, int y);



// mastermain entry point
int XSTD MasterMain(HINSTANCE hInst,LPSTR line)
{
	if(mxhwnd.CreateMasterX("MULCUR",640,480,COLOR_DEFAULT,EventProc,hInst,NULL,NULL))
	{
		loadcursors();
		setcursor(MAG);
		return mxhwnd.InitLoop(frame_update);
	}

	return 0;
}

// load cursors
void loadcursors()
{
	cur[0] = LoadCursorFromFile("arrow.cur");
	cur[1] = LoadCursorFromFile("mag.cur");
	cur[2] = LoadCursorFromFile("hand.cur");
}

// set the current cursor
void setcursor(GAMECURSOR cursor)
{
	SetCapture(mxhwnd.hwnd);
	SetCursor(cur[(int)cursor]);
	curcursor = cursor;
}


// callback
long XSTD EventProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
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
				{
					mxhwnd.Kill();
					break;
				}
			case VK_RETURN:
				{
					setcursor(ARROW);
					mycursor = ARROW;
				}
				break;
			case VK_SPACE:
				{
					setcursor(MAG);
					mycursor = MAG;
				}
				break;
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			mousemove(LOWORD(lParam),HIWORD(lParam));
		}
		break;
	case WM_LBUTTONDOWN:
		{
			leftclick(LOWORD(lParam),HIWORD(lParam));
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

// frame update callback
void frame_update(MASTERSCREEN screen)
{
	COLORREF bgcolor = RGB(colorx,colorx,colorx);
	mxhwnd.paint.mxdrawrect(0,0,640,480,bgcolor,bgcolor);

	if(colordir == true)
	{

	colorx ++;
	if(colorx >= 0xFF)
	{
		colorx = 0xFF;
		colordir = false;
	}

	}
	else
	{
		colorx --;
		if(colorx <= 0)
		{
			colorx = 0;
			colordir = true;
		}
	}

	mxhwnd.text.setfont(mfont);
	mxhwnd.text.settextcolor(0xFF);
	mxhwnd.text.setbkcolor(bgcolor);
	mxhwnd.text.printtext("Press Esc to Exit",10,10);
	mxhwnd.text.printtext("Press Enter for Arrow cursor",10,25);
	mxhwnd.text.printtext("Press Space for Mag cursor",10,40);
	mxhwnd.text.printtext("Click on the link below!",10,55);

	mxhwnd.text.settextcolor(RGB(0,0,255));
	mxhwnd.text.printtextunderline("www.lostsidedead.com",10,70);
}

// mousemove callback
void mousemove(int x, int y)
{
	if(x > 10 && x < 110 && y > 70 && y < 84)
	{
		setcursor(HAND);
	}
	else
	{
		if(curcursor == HAND)
		{
			setcursor(mycursor);
		}
	}
}

// left click
void leftclick(int x, int y)
{
	if(x > 10 && x < 110 && y > 70 && y < 84)
	{
		ShowWindow(mxhwnd.hwnd,SW_MINIMIZE);
		ShellExecute(NULL,"open","http://www.lostsidedead.com",NULL,NULL,SW_SHOW);
	}
}

