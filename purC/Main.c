// implementation of a window in pure C
// written by jared bruni for planetsourcecode
// questions? comments? code requests? 
// emailme: master@lostsidedead.com

// if i have helped you, i would apperciate a vote or two. 
// i dont care about the contest, just looks good on resume
// thank you


#include <windows.h>
#include "resource.h"

#define ID_BUTTON 1
#define ID_EDIT  2
#define ID_STAT  3
#define ID_LIST  4
#define ID_COMBO 5


HWND hwnd;
HWND button;
HWND edit;
HWND stat;
HWND list;
HWND combo;

HINSTANCE g_hInst;

LRESULT APIENTRY WndProc(HWND,UINT,WPARAM,LPARAM);
void Init(HINSTANCE);

// application entry point
int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	MSG  msg;
	g_hInst = hInst;
	Init(hInst);
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

// initlize application
void Init(HINSTANCE hInst)
{
	WNDCLASS wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = "thisC";
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	hwnd = CreateWindow("thisC","This is C ( Jared Bruni )",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,230,220,0,0,hInst,0);

	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);
}

// main window callback function
LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		{
			edit = CreateWindow("Edit",NULL,WS_CHILD | WS_VISIBLE | WS_BORDER ,5,5,100,20,hwnd,(HMENU)ID_EDIT,g_hInst,0);
			button = CreateWindow("Button","Title",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,110,5,75,25,hwnd,(HMENU)ID_BUTTON,g_hInst,0);
			stat = CreateWindow("Static","Static Label",WS_CHILD | WS_VISIBLE,5,30,200,25,hwnd,(HMENU)ID_STAT,g_hInst,0);
			list = CreateWindow("ListBox",NULL,WS_CHILD | WS_VISIBLE | LBS_STANDARD,5,60,100,100,hwnd,(HMENU)ID_LIST,g_hInst,0);
			combo = CreateWindow("ComboBox",NULL,WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,115,60,100,20,hwnd,(HMENU)ID_COMBO,g_hInst,0);

		}
		break;
	case WM_COMMAND:
		{
			switch(wParam)
			{
			case ID_FILEEXIT:
				SendMessage(hwnd,WM_CLOSE,0,0);
				break;
			}

			switch(HIWORD(wParam))
			{
			case BN_CLICKED:
				switch(LOWORD(wParam))
				{
				case ID_BUTTON:
					MessageBox(hwnd,"You clicked the button","Yep",MB_OK | MB_ICONINFORMATION);
					break;
				}
				break;
			}


		}
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}
