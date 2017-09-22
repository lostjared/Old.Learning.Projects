// about window
// jared bruni
#include "winhead.h"

HWND button;
enum { ID_BUTTON1 = 420 };


// about window proccess
LRESULT APIENTRY AboutProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_CLOSE:
		ShowWindow(hwnd,SW_HIDE);
		break;
	case WM_CREATE:
		{
			HWND st;
			HWND bt;
			st = CreateWindow("Static","Win32 C++ Platform SDK",WS_CHILD|WS_VISIBLE,5,5,100,100,hwnd,0,g_hInst,0);
			bt = CreateWindow("Button","Ok!",WS_CHILD|WS_VISIBLE|WS_BORDER,5,300-50,100,25,hwnd,(HMENU)ID_BUTTON1,g_hInst,0);

		}
		break;
	case WM_COMMAND:
		{
			switch(HIWORD(wParam))
			{
			case BN_CLICKED:
				{
					switch(LOWORD(wParam))
					{
					case ID_BUTTON1:
						{
							ShowWindow(hwnd,SW_HIDE);
						}
						break;
					}				
				}
				break;
			}
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}