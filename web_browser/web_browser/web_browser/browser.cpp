#include<windows.h>
#include"browser.h"
#include "resource.h"
#include <comutil.h>
#include<stdio.h>
#pragma comment(lib, "comsupp.lib")

HWND hwnd;
HWND edit, back, forward, home,stop;
WNDPROC OldProc;

mxBrowser b(L"http://www.lostsidedead.com/index.php3");

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {
	switch(msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_CREATE:
			edit = CreateWindow("Edit","http://www.lostsidedead.com",WS_BORDER | WS_CHILD | WS_VISIBLE ,10,10,100,25,hwnd,0,GetModuleHandle(0),0);
			back = CreateWindow("Button","Back",BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,10,25+5,100,15,hwnd,(HMENU)1,GetModuleHandle(0),0);
			forward = CreateWindow("Button","Forward", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,110,25+5,100,15,hwnd,(HMENU)2,GetModuleHandle(0),0);
			home = CreateWindow("Button", "Home", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,220,25+5,100,20,hwnd,(HMENU)3,GetModuleHandle(0),0);
			stop = CreateWindow("Button", "Stop", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,330,25+5,100,20,hwnd,(HMENU)4,GetModuleHandle(0),0);
			break;
		case WM_LBUTTONDOWN:
			break;
		case WM_SIZE: {
			RECT rc;
			GetClientRect(hwnd,&rc);
			MoveWindow(edit,10,10,rc.right - 20,20,TRUE);
			MoveWindow(back,10,35,100,20,TRUE);
			MoveWindow(forward,110,35,100,20,TRUE);
			MoveWindow(home,110+100,35,100,20,TRUE);
			MoveWindow(stop,110+200,35,100,20,TRUE);

			rc.top = 60;
			b.ResizeWindow(&rc);
		}
	    break;
		case WM_COMMAND: {
			switch(HIWORD(wParam)) {
			case BN_CLICKED: {

				switch(LOWORD(wParam)) {
				case 1:
					b.Back();
					break;
				case 2:
					b.Forward();
					break;
				case 3:
					b.ViewSite(L"http://www.lostsidedead.com");
					break;
				case 4:
					b.Stop();
					break;
				}
				}
				break;
			}

			switch(wParam) {
			case ID_FILE_EXIT:
				PostQuitMessage(0);
			break;
			case ID_OPTIONS_EDITOPTIONS:
				MessageBox(NULL,"No Options at this time","Sorry",MB_OK | MB_ICONINFORMATION);
				break;
			case ID_HELP_ABOUT:
				MessageBox(hwnd,"Written by Jared Bruni\nwww.lostsidedead.com","About",MB_ICONINFORMATION|MB_OK);
				break;
			}
		}
	    break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

LRESULT APIENTRY EditProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {
	switch(msg) {
		case WM_KEYDOWN: {
			switch(wParam) {
			case VK_RETURN:
				char str[5000];
				SendMessage(edit,WM_GETTEXT,5000,(LPARAM)(LPCSTR)str);
				b.ViewSite(_com_util::ConvertStringToBSTR(str));
				return 0;
			break;
			}
		}
	    break;

		default: return CallWindowProc(OldProc,hwnd,msg,wParam,lParam);
	}
	return 0;
}


int PASCAL WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR lpszLine, int nCmdShow) {


	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) (COLOR_3DFACE+1);
	wc.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIconSm = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = "BrowserTest";
	wc.lpszMenuName =  MAKEINTRESOURCE(IDR_MENU1);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInst;

	if(!RegisterClassEx(&wc)) { MessageBox(NULL,"Error Registering Class","Error",MB_OK | MB_ICONERROR); return 0; }



	OleInitialize(0);
	hwnd = CreateWindow("BrowserTest","MasterZilla", WS_OVERLAPPEDWINDOW,0,0,640,480,0,0,GetModuleHandle(0),0);
	OldProc = (WNDPROC) SetWindowLong(edit,GWL_WNDPROC,(LONG)EditProc);
	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);
	b.startBrowser();
	SendMessage(hwnd,WM_SIZE,0,0);
	MSG msg;
	while(GetMessage(&msg,0,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (iBrowser)
		iBrowser->Release();	
	if (mpWebObject)
	{
		mpWebObject->Close(OLECLOSE_NOSAVE); 
		mpWebObject->Release();
	}
	OleUninitialize();
	return 0;
}