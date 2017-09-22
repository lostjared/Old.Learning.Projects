// written by jared bruni
// for planetsourcecode
// this was a request.
// keep your coding requests coming !


// having multiple windows, using pure C

#include <windows.h>
#define BOPEN1 1

// function prototypes
void InitApp(HINSTANCE);
LRESULT APIENTRY MainProc(HWND,UINT,WPARAM,LPARAM);
LRESULT APIENTRY OtherProc(HWND,UINT,WPARAM,LPARAM);

// variables

HWND hwnd;
HWND other;
HWND bopen;
HINSTANCE g_hInst;


// winmain entry point
int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	MSG msg;
	g_hInst = hInst;
	InitApp(hInst);

	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

// initlize application
void InitApp(HINSTANCE hInst)
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.hInstance = hInst;
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.lpfnWndProc = (WNDPROC) MainProc;
	wc.lpszClassName = "Main";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	wc.lpszClassName = "Other";
	wc.lpfnWndProc = (WNDPROC) OtherProc;

	RegisterClass(&wc);

	hwnd = CreateWindow("Main","Main Window",WS_OVERLAPPEDWINDOW,0,0,170,55,0,0,hInst,0);
	other = CreateWindow("Other","Other",WS_OVERLAPPEDWINDOW,200,200,200,200,0,0,hInst,0);

	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);
	
}

// Main Process CallBack Function
LRESULT APIENTRY MainProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		{
			bopen = CreateWindow("Button","Open Window 2",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,5,5,150,20,hwnd,(HMENU)BOPEN1,g_hInst,0);
		}
		break;
	case WM_COMMAND:
		{
			switch(HIWORD(wParam))
			{
			case BN_CLICKED:
				switch(LOWORD(wParam))
				{
				case BOPEN1:
					ShowWindow(other,SW_SHOW);
					break;
				}
				break;
			}
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}
// Other Window CallBack Function
LRESULT APIENTRY OtherProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_CLOSE:
		ShowWindow(hwnd,SW_HIDE);
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}