#include <windows.h>
// master on lsd, here list box shit
#define ID_LIST 420

HINSTANCE hInst;

LRESULT APIENTRY WindowProc(HWND,UINT,WPARAM,LPARAM);

int APIENTRY WinMain(HINSTANCE hInstx,HINSTANCE hPrev,LPSTR l,int CmdShow)
{
	hInst = hInstx;
	HWND hwnd;
	MSG msg;
	WNDCLASS wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpfnWndProc = (WNDPROC) WindowProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Master";
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	hwnd = CreateWindowEx(WS_EX_TOPMOST,"Master","Heres your Example",WS_OVERLAPPEDWINDOW,0,0,640,480,0,0,hInst,0);
	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);

	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT APIENTRY WindowProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		HWND list;
		list = CreateWindowEx(WS_EX_STATICEDGE,"ListBox",NULL,WS_CHILD | WS_VISIBLE | LBS_NOTIFY,0,0,640,480,hwnd,(HMENU)ID_LIST,hInst,0);
		SendMessage(list,LB_ADDSTRING,255,(LPARAM)(LPCSTR)"Test");
		break;
	case WM_COMMAND:

		switch(HIWORD(wParam))
		{
		case LBN_DBLCLK:
			switch(LOWORD(wParam))
			{
			case ID_LIST:
				MessageBox(hwnd,"Click",0,0);
				break;
			}
			break;
		}

		break;

	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}
