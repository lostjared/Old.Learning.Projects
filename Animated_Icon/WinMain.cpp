// animated icon , main
// written by jared bruni
// www.lostsidedead.com

// note this is not a full program, nor is it a attempt at once
// simply a interface, to demonstrate the example

#include <windows.h>
#include "resource.h"

HINSTANCE hInst;
HWND mainwindow;
HICON icons[5]; // 4 Icons
bool icon_dir = true;
int  icon_index = 0;

LRESULT APIENTRY WndProc(HWND,UINT,WPARAM,LPARAM);
inline void Init();
inline void LoadGraphics();
inline void UnLoadGraphics();
void SetMyIcon(int index);


int _stdcall WinMain(HINSTANCE hInstx,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	MSG msg;
	hInst = hInstx;
	Init();

	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

inline void Init()
{
    LoadGraphics();
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = "Master";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	mainwindow = CreateWindow("Master","Animated Icon Example",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,640,480,0,0,hInst,0);
	
	SetMyIcon(0); // 0 icon

	ShowWindow(mainwindow,SW_SHOW);
	UpdateWindow(mainwindow);

	SetTimer(mainwindow,1,10,NULL);
}

inline void LoadGraphics()
{
	icons[0] = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
	icons[1] = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON2));
	icons[2] = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON3));
	icons[3] = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON4));
	icons[4] = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON5));	
}

inline void UnLoadGraphics()
{
	for(int i = 0; i <= 4; i++)
	{
	DeleteObject(icons[i]);
	}
}

void SetMyIcon(int Index)
{
	SendMessage(mainwindow, WM_SETICON, ICON_SMALL, (LPARAM)(HICON)icons[Index]); 
}


LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		UnLoadGraphics();
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		{
			SetMyIcon(icon_index);

			if(icon_dir == true)
			{
				icon_index++;

				if(icon_index > 4)
				{
					icon_index = 4;
					icon_dir = false;
				}

			}
			else
			{
				icon_index--;
				if(icon_index < 0)
				{
					icon_index = 0;
					icon_dir = true;
				}
			}


		}
		break;
	case WM_CREATE:
		{
			HWND static_hwnd;
			static_hwnd = CreateWindow("Static","How to Animate a Icon Example by Jared Bruni\nThis Example is just to show you how you can setup something like this in your own code.\nThis is Not a full program",WS_CHILD | WS_VISIBLE,5,5,200,200,hwnd,0,hInst,0);
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}