// MasterX SDK 1.9 Example
// using the new print function
// written by jared bruni
// www.lostsidedead.com

#include "masterx.h"

MasterXHWND mxhwnd;

HFONT fonttable[10];



long XSTD MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void update(MASTERSCREEN);

void loadtable();


int xvar = 100;


int XSTD MasterMain(HINSTANCE hInst,LPSTR line)
{
	if(mxhwnd.CreateMasterX("Test",640,480,COLOR_DEFAULT,MasterProc,hInst,0,0))
	{
		loadtable();
		mxhwnd.HideCursor();
		return mxhwnd.InitLoop(update);
	}

	return 0;
}

void loadtable()
{
	int start = 10;
	for(int i = 0; i <= 10; i++)
	{
		fonttable[i] = MakeFont("Arial",start);
		start += 5;
	}
}

long XSTD MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
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
			if(wParam == VK_ESCAPE)
			{
				mxhwnd.Kill();
			}
		}
		break;
	default:
		return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}


void update(MASTERSCREEN screen)
{

	mxhwnd.text.setbkcolor(0x0);
	mxhwnd.text.setfont(fonttable[0]);
	mxhwnd.text.settextcolor(RGB(200,0,0));
	mxhwnd.text.sprinttext(10,10,"press escape to exit %s", ":)");
	mxhwnd.text.setfont(fonttable[1]);
	mxhwnd.text.settextcolor(0xFFFFFF);
	mxhwnd.text.sprinttext(10,50,"heres a random number %i",rand()%100);
	mxhwnd.text.setfont(fonttable[rand()%10]);
	mxhwnd.text.sprinttext(10,300,"heres the magic number %i",xvar);

}