// view message source
// jared bruni
// www.lostsidedead.com
// mailme: master@lostsidedead.com

#include "thehead.h"

#define xID_OK 420

// the View Call back function

HWND st_view;
HWND st_edit;
HWND st_but;

LRESULT APIENTRY ViewProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_CLOSE:
		{
			ShowWindow(hwnd,SW_HIDE);
			break;
		}
		break;
	case WM_CREATE:
		{
			st_view = CreateWindow("Static","SN",WS_CHILD | WS_VISIBLE,5,5,200,25,hwnd,0,hInst,0);
			st_edit = CreateWindowEx(WS_EX_STATICEDGE,"Edit",NULL,WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL | ES_READONLY ,5,25,180,120,hwnd,0,hInst,0);
			SetMyFont(st_view);
			SetMyFont(st_edit);
			st_but  = CreateWindowEx(WS_EX_STATICEDGE,"Button","Ok",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,180-70,25+120+5,75,25,hwnd,(HMENU)xID_OK,hInst,0);
			SetMyFont(st_but);
		}
		break;
	case WM_COMMAND:
		{
			switch(wParam)
			{
			case xID_OK:
				{
					ShowWindow(hwnd,SW_HIDE);
				}
				break;
			}

		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}


void ShowMessage(char* sn,char* msg)
{
	SetWindowText(st_view,sn);
	SetWindowText(st_edit,msg);
	ShowWindow(FindWindow("MasterView",NULL),SW_SHOW);
}