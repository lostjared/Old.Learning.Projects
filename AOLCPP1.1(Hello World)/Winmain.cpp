// winmain entry point
// jared bruni
// http://www.lostsidedead.com
// http://www.lostsidedead.com/gameprog/

#include "mxhead.h"


AOLCPP aol;
// applicatin entry point
int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	g_hInst = hInst;
	MSG msg;
	WNDCLASS wc;
	wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpszClassName = "Master";
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	main = CreateWindow("Master","The Send Window",WS_OVERLAPPED |WS_SYSMENU | WS_MINIMIZEBOX,0,0,200,75,0,0,hInst,0);

	ShowWindow(main,SW_SHOW);
	UpdateWindow(main);
	aol.sendtext("-l33tr0r cpp hack0r haha loaded");

	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
// window message process
LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		{
			edit = CreateWindowEx(WS_EX_STATICEDGE,"Edit",NULL,WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,5,05,180,20,hwnd,(HMENU)ID_EDIT,g_hInst,0);
			 MainP = (WNDPROC) SetWindowLong(edit,GWL_WNDPROC,(LONG)EditProc);
	
			button = CreateWindowEx(WS_EX_STATICEDGE,"Button","Send",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,5,25,100,20,hwnd,(HMENU)ID_BUTTON,g_hInst,0);
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
					case ID_BUTTON:
						{
							// send code
							sendeditdata();
							break;
				
						}
						break;
				}
				break;
			}
			}

		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

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
					sendeditdata();
					break;
				}
				break;
			}
		}
		break;

	default: return CallWindowProc(MainP,hwnd,msg,wParam,lParam);
	}

	return 0;
}

// send edit data
void sendeditdata()
{
	if(aol.getaol())
	{

	char cbuff[200];
    SendMessage(edit,WM_GETTEXT,200,(LPARAM)(LPCSTR)cbuff);
	if(strlen(cbuff) > 2)
	{

	aol.sendtext(cbuff);

	} 
	SendMessage(edit,WM_SETTEXT,1,(LPARAM)(LPCSTR)"");

	}

}

