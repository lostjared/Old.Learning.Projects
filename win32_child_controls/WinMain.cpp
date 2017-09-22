// windows controls platform sdk
// jared bruni
// http://www.lostsidedead.com/gameprog
// email me: jared@lostsidedead.com

// win32 standard controls, via platform SDK :)

#include <windows.h> // windows header file
#include "resource.h"

// enumerated constants for the child handles
enum { ID_LABEL = 1,ID_IMAGE,ID_EDIT,ID_LIST,ID_BUTTON,ID_COMBO, ID_BUTTON2 };



// function prototypes
LRESULT APIENTRY TestWindowProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
LRESULT APIENTRY AboutWindowProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void onmenu(WPARAM);


// Application Instance Handle
HINSTANCE g_hInst;

// window handles (unsigned long)'s
HWND testwin;
HWND aboutwin;
HWND static_label;
HWND static_image;
HWND edit;
HWND list;
HWND button;
HWND combo;

// using _stdcall the winmain entry
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
	wc.lpfnWndProc = (WNDPROC) TestWindowProc;
	wc.lpszClassName = "Test:)";
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	wc.lpszMenuName = NULL;
	wc.lpszClassName = "About:)";
	wc.lpfnWndProc = (WNDPROC) AboutWindowProc;

	RegisterClass(&wc);
// this is standard example two is ex :)

	testwin = CreateWindow("Test:)","Test Window",WS_OVERLAPPEDWINDOW,0,0,640,480,0,0,hInst,0);
	aboutwin = CreateWindow("About:)","About Test", WS_OVERLAPPED | WS_SYSMENU |WS_MINIMIZEBOX,0,0,250,250,0,0,hInst,0);

	ShowWindow(testwin,SW_SHOW);
	UpdateWindow(testwin);

	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

// function def's
LRESULT APIENTRY TestWindowProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);// destroy code out of memory
		break;
	case WM_CREATE:// CREATING ALL THE CHILDREN OF THIS WINDOW
		{
			HWND stx;
			stx = CreateWindow("Static","A Random Static Label",WS_CHILD | WS_VISIBLE ,0,0,200,25,hwnd,0,g_hInst,0);
			static_label = CreateWindow("Static","This static label",WS_CHILD | WS_VISIBLE,205,0,200,25,hwnd,0,g_hInst,0);
			edit = CreateWindow("Edit","A Windows Edit Box",WS_BORDER | WS_VSCROLL | WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOHSCROLL,5,35,200,200,hwnd,(HMENU)ID_EDIT,g_hInst,0);
			list = CreateWindow("ListBox",NULL, LBS_NOTIFY | WS_CHILD | WS_VISIBLE | WS_VSCROLL|WS_BORDER,5,250,200,200,hwnd,(HMENU)ID_LIST,g_hInst,0);
			button = CreateWindow("Button","About",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE ,350,5,100,25,hwnd,(HMENU)ID_BUTTON,g_hInst,0);
			static_image = CreateWindow("Static",NULL,WS_CHILD | WS_VISIBLE | SS_BITMAP,350,40,0,0,hwnd,(HMENU)ID_IMAGE,g_hInst,0);
			SendMessage(static_image,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)(HBITMAP)LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP1)));
			combo = CreateWindow("ComboBox",NULL,WS_BORDER | CBS_DISABLENOSCROLL | WS_CHILD | CBS_DROPDOWNLIST | WS_VISIBLE,350,400,200,200,hwnd,(HMENU)ID_COMBO,g_hInst,0);
			SendMessage(combo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"addstuff");
		}
		break;
	case WM_COMMAND:
		{
			onmenu(wParam);

			// child notification messages
			switch(HIWORD(wParam))
			{
			case BN_CLICKED:
				switch(LOWORD(wParam))
				{
				case ID_BUTTON:
					{
						// code
						SendMessage(list,LB_ADDSTRING,255,(LPARAM)(LPCSTR)"You clicked the button");
						SendMessage(combo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"You clicked the button ");
						ShowWindow(aboutwin,SW_SHOW);
					}
					break;

				}
				break;

				case LBN_DBLCLK:
					{
						switch(LOWORD(wParam))
						{
						case ID_LIST:
							{

								MessageBox(hwnd,"Double Clicked the List","HAHA",MB_OK |MB_ICONINFORMATION);
							}
							break;
						}

					}
					break;
				case EN_CHANGE:
					{
						switch(LOWORD(wParam))
						{
						case ID_EDIT:
							{
								MessageBox(hwnd,"Change","Hehe",MB_OK | MB_ICONINFORMATION);
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

// on the menu command

void onmenu(WPARAM wParam)
{
	switch(wParam)
	{
	case ID_FILE_EXIT:
		{
			SendMessage(testwin,WM_CLOSE,0,0);
		}
		break;
	case ID_FILE_MSGABOUT:
		{
			MessageBox(0,"About this test program","test",MB_OK|MB_ICONINFORMATION);
		}
		break;
	case ID_FILE_WINDOWABOUT:
		{
			ShowWindow(aboutwin,SW_SHOW);
		}
		break;
	}


}



// about window process
LRESULT APIENTRY AboutWindowProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_CLOSE:
		ShowWindow(hwnd,SW_HIDE);
		break;
	case WM_CREATE:
		{
			HWND buttonx;
			buttonx = CreateWindow("Button","Ok!",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,200-55,200,100,25,hwnd,(HMENU)ID_BUTTON2,g_hInst,0);
			HWND stx;
			stx = CreateWindow("Static","Example for my friends, you can do what you need with this. :)",WS_CHILD|WS_VISIBLE,5,5,200,150,hwnd,0,g_hInst,0);

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
					case ID_BUTTON2:
						{
							SendMessage(hwnd,WM_CLOSE,0,0);
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
