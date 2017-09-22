// introduction window
// jared bruni

#include "winhead.h"


// introduction window message process

LRESULT APIENTRY IntroProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		{
			ShowWindow(hwnd,SW_HIDE);
		}
		break;
	case WM_CREATE:
		{
			HWND st;
			st = CreateWindow("Static","Welcome to this \r\nC++ example!",WS_CHILD | WS_VISIBLE,5,5,200,100,hwnd,0,g_hInst,0);
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}