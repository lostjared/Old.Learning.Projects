// aolcpp3 example 1
// jared bruni
// aol/aim master on lsd  email: masteronlsd@lostsidedead.com

#include <windows.h>
#include "aolcpp3.h"

LRESULT APIENTRY MainProc(HWND,UINT,WPARAM,LPARAM);

AOLCPP3 aolcpp3; // aolcpp3 objects
HINSTANCE g_hInst;

int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	HWND hwnd;
	g_hInst = hInst;
	MSG  msg;
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpszClassName = "Master";
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = (WNDPROC) MainProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	hwnd = CreateWindow("Master","Title",WS_OVERLAPPEDWINDOW,0,0,640,480,0,0,hInst,0);

	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);

	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}


LRESULT APIENTRY MainProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		{
			HWND st;
			st = CreateWindow("Static","Click the Window to SendText",WS_CHILD | WS_VISIBLE,5,5,200,25,hwnd,0,g_hInst,0);

		}
		break;
	case WM_LBUTTONDOWN:
		{
			aolcpp3.chat.sendtext("AOLCPP3 Hello World");
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}