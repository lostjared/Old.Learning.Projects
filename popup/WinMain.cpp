// this application, makes a graphic in win32, allows it to be minimized
// to the systray
// has a popup menu when double clicked, or right clicked
// hehe:
// written by jared bruni
// www.lostsidedead.com
// support the jared bruni foundation haha
// I would like to thank everyone who downloaded this program
// it is greatly apperciated,
// you can look forward to seeing many many great C++ examples in the future



#include <windows.h>
#include "SupportJB.h"
#include "resource.h"

#define WM_SHELLNOTIFY WM_USER+5000
#define IDI_TRAY 42
#define ID_MRES 421
#define ID_MABOUT 422


NOTIFYICONDATA note;// notify icon data structure
HMENU hMaster;// handle for the menu for the popup


LRESULT APIENTRY MainProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
inline void Init();
void LoadGraphics();// load the graphics
void DestroyGraphics();// destroy the graphics
void SetBitmap(HWND hwnd,HBITMAP x); // set a bitmap to a static hwnd with flag SS_BITMAP

HWND hwnd;// windows handle
HINSTANCE hInst;// instance handle

HBITMAP hbmp; // bitmap handle

int APIENTRY WinMain(HINSTANCE hInstx,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	MSG msg;// msg handle for the message loop
	hInst = hInstx;// pass the instance to the global instance handle
	LoadGraphics();// load thegraphics
	Init();// initlize the application
	
// the programs loop
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
// initlize this program
inline void Init()
{
	// setup the window class
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpfnWndProc = (WNDPROC) MainProc;
	wc.lpszClassName = "Master";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);// register it

	// create the window
	hwnd = CreateWindow("Master","System Tray graphics, and Popup Menu",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,615,100,0,0,hInst,0);

	ShowWindow(hwnd,SW_SHOW);// show the window
	UpdateWindow(hwnd);// update the window

	// support Jared! (you can delete this line of code after you run it once)
 	//SupportJared();

}

// program callback function
LRESULT APIENTRY MainProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		Shell_NotifyIcon(NIM_DELETE,&note);// delete from systray (if its still in there)
		DestroyMenu(hMaster);
		DestroyGraphics();// delete graphics
		PostQuitMessage(0);// post quit messsage
		break;
	case WM_CREATE:
		{
			HWND st;// handle of static
			st = CreateWindow("Static",NULL,WS_CHILD | WS_VISIBLE | SS_BITMAP,0,0,0,0,hwnd,0,hInst,0);
			SetBitmap(st,hbmp);// set the bitmap

			// create are popupmenu (no resource!)

				hMaster = CreatePopupMenu();// create the popupmenu
				AppendMenu(hMaster,MF_STRING ,ID_MRES,"Restore");// append menu 
				AppendMenu(hMaster,MF_SEPARATOR,0,0);// append menu
				AppendMenu(hMaster,MF_STRING,ID_MABOUT,"About");// append menu
		}
		break;
	case WM_SIZE:
		{
			if(wParam == SIZE_MINIMIZED)
			{
				note.cbSize = sizeof(NOTIFYICONDATA);// size of
				note.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));// set the icon
				note.hWnd = hwnd;// the window handle, for the callback
				note.uCallbackMessage = WM_SHELLNOTIFY;// the callback ID
				lstrcpy(note.szTip, "Master's Tip Double Click Here");// the note
				note.uID = IDI_TRAY;// set the ID
				note.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;// flags
				ShowWindow(hwnd,SW_HIDE);// hide the window
				Shell_NotifyIcon(NIM_ADD,&note);// add are icon to the system tray
			}
		}
		break;
		case WM_SHELLNOTIFY:
			{
			
			// if they right click, or left button double click then
			if((lParam == WM_RBUTTONDOWN) || (lParam == WM_LBUTTONDBLCLK))
			{
				
				// load menu
				POINT pt;// point structure
				GetCursorPos(&pt);// get the cursors position
				SetForegroundWindow(hwnd);// set the foreground window
				TrackPopupMenu(hMaster,TPM_RIGHTALIGN,pt.x,pt.y,NULL,hwnd,NULL);// track the popup
				PostMessage(hwnd,WM_NULL,0,0);// post a null message				              
			}

			}			
			break;
		case WM_COMMAND:
			{
				switch(wParam)
				{
				case ID_MABOUT:
					{
						MessageBox(hwnd,"System Tray Example\nWritten by Jared Bruni\nAge 17\nwww.lostsidedead.com\n","Jared's Example",MB_ICONINFORMATION);// yay
						SupportJared(); // support me!
					}
					break;
				case ID_MRES:
					{
				        Shell_NotifyIcon(NIM_DELETE,&note);// delete the icon from the systray
				        ShowWindow(hwnd,SW_SHOW);// show are window
				        ShowWindow(hwnd,SW_RESTORE);// restore are window
					}
					break;
				}
			}
			break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

// loading are graphics
void LoadGraphics()
{
	hbmp = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP1)); // load are bitmap in resource
}
// destroy this bitmap
void DestroyGraphics()
{
	DeleteObject(hbmp); // delete are bitmap when programs done
}
// set the bitmap to a static hwnd
void SetBitmap(HWND hwnd,HBITMAP x)
{
	SendMessage(hwnd,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)(HBITMAP)x);
}