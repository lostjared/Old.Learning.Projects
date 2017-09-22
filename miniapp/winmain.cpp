// jared bruni
// http://www.lostsidedead.com/gameprog/

#include "winhead.h"

// enumerated constants

enum { ID_EDIT = 1 };


// child window handles
HWND edit;


// winmain entry point
int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	g_hInst = hInst;
	MSG msg;
	WNDCLASS wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpszClassName = "MasterMain";
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpfnWndProc = (WNDPROC) MainProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	wc.lpszClassName = "MasterIntro";
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = (WNDPROC) IntroProc;

	RegisterClass(&wc);

	wc.lpszClassName = "MasterAbout";
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = (WNDPROC) AboutProc;

	RegisterClass(&wc);

	main = CreateWindow("MasterMain","MainWindow",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,640,480,0,0,hInst,0);
	intro = CreateWindow("MasterIntro","intro window",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,200,200,0,0,hInst,0);
	about = CreateWindow("MasterAbout","about window",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,300,300,0,0,hInst,0);
	
	ShowWindow(main,SW_SHOW);
	UpdateWindow(main);

	ShowWindow(intro,SW_SHOW);


	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
// main window process
LRESULT APIENTRY MainProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		{
 int w; w = LOWORD(lParam);
 int h; h = HIWORD(lParam);

 SetWindowPos(edit,0,0,0,w,h,WS_CHILD | WS_VISIBLE);
 
		}
		break;

	case WM_CREATE:
		{
			edit = CreateWindowEx(WS_EX_STATICEDGE,"Edit",NULL,ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | WS_CHILD|WS_VISIBLE|WS_BORDER,0,0,640,480,hwnd,(HMENU)ID_EDIT,g_hInst,0);

		}

	case WM_COMMAND:
		{
			onmainmenu(wParam);
		}
		break;

	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}
// on main menu
void onmainmenu(WPARAM wParam)
{
	switch(wParam)
	{
	case ID_FILE_EXITZ:
		{
			SendMessage(main,WM_CLOSE,0,0);
		}
		break;
	case ID_HELP_ABOUTZ:
		{
			ShowWindow(about,SW_SHOW);
		}
		break;
	case ID_FILE_LOADDAT:
		{
			SendMessage(edit,WM_SETTEXT,255,(LPARAM)(LPCSTR)
				" welcome to my C++ win32 example\r\n"
				" my name is jared!. nice to meet you"
				" have fun with this code!");
		}
		break;
	}
}