// Written by Jared Bruni
// www.lostsidedead.com
// for planetsourcecode
// subclassing a child control in win32

// include widnows.h
#include <windows.h>

// callback functions
LRESULT APIENTRY MainProc(HWND,UINT,WPARAM,LPARAM);
LRESULT APIENTRY EditProc(HWND,UINT,WPARAM,LPARAM);
// misc functions
void Init();

// variables
HINSTANCE hInst; // instance of the application
HWND main;// main window handle
HWND edit;// edit handle
WNDPROC xMainProc; // pointer to main message process


// winmain entry point
int APIENTRY WinMain(HINSTANCE hInstx,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	hInst = hInstx;// set the instance
	Init();// init

	MSG msg;// message loop
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

// init
void Init()
{
	WNDCLASS wc;// window class structure
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpfnWndProc = (WNDPROC) MainProc;
	wc.lpszClassName = "Master";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);// register class structure

	// create & show the window
	main = CreateWindow("Master","Jared's Example",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,250,90,0,0,hInst,0);
	ShowWindow(main,SW_SHOW);
	UpdateWindow(main);
}

// mainwindow callback function
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
			st = CreateWindow("Static","Type something then press enter",WS_CHILD | WS_VISIBLE,5,5,250,20,hwnd,0,hInst,0);
			edit = CreateWindowEx(WS_EX_STATICEDGE,"Edit",NULL,WS_CHILD | WS_VISIBLE ,5,25,150,20,hwnd,0,hInst,0);

			// subclass the edit
			xMainProc = (WNDPROC)SetWindowLong(edit,GWL_WNDPROC,(LONG)EditProc); 
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

// subclassed edit callback function
LRESULT APIENTRY EditProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case 13:
				{
					int tlen;
					tlen = SendMessage(hwnd,WM_GETTEXTLENGTH,0,0) + 1;
					char* buffer;
					buffer = new char[tlen];
					SendMessage(hwnd,WM_GETTEXT,tlen,(LPARAM)(LPCSTR)buffer);
					MessageBox(0,buffer,"You said",0);
					SendMessage(hwnd,WM_SETTEXT,1,(LPARAM)(LPCSTR)"");
					delete [] buffer;
					buffer = 0;
				}
				break;
			}
		}
		break;

	default: return CallWindowProc(xMainProc,hwnd,msg,wParam,lParam);
	}
	
	return 0;
}