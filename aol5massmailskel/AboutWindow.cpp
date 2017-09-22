// the About Window
// Jared Bruni

#include "appHead.h"


HWND okb;

enum { ID_OKB  = 1 };

LRESULT APIENTRY AboutProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_CLOSE:
		ShowWindow(hwnd,SW_HIDE);
		break;
	case WM_CREATE:
		{
			okb = CreateWindow("Button","Ok",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,315-75-5-3,360-5-25-20,75,25,hwnd,(HMENU)ID_OKB,g_hInst,0);
			SetTheFont(okb);

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
					case ID_OKB:
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