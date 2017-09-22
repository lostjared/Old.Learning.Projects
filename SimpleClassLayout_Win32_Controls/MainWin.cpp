// main window

#include  <windows.h>
#include "mbutton.h"



LRESULT APIENTRY WndProc(HWND,UINT,WPARAM,LPARAM);
LRESULT APIENTRY ButProc(HWND,UINT,WPARAM,LPARAM);


HWND hwnd;

MButton button;

WNDPROC oldProc;


int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR line,int CmdShow)
{



	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.hInstance = hInst;
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = "Master";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	

	hwnd = CreateWindow("Master","Title",WS_OVERLAPPEDWINDOW,0,0,640,480,0,0,hInst,0);
	button.CreateButton(WS_EX_STATICEDGE,"Master",WS_CHILD |WS_VISIBLE|BS_PUSHBUTTON,5,5,100,75,hwnd,hInst,420);
	oldProc = button.SubClassWindow(ButProc);

 

	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);


	MSG msg;

	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}


// the subclassed window proccess =) 
LRESULT APIENTRY ButProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_SPACE:
				{
					MessageBox(0,"you pressed space",0,0);
					button.SetText("press");
				}
				break;
			}
		}
		break;
	default: return CallWindowProc(oldProc, hwnd,msg,wParam,lParam);
	}
	return 0;
}
