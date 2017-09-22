// aolcpp3 example 1
// jared bruni
// aol/aim master on lsd  email: masteronlsd@lostsidedead.com

#include <windows.h>
#include "aolcpp3.h"

enum { ID_BUTTON = 1 , ID_BUTTON1, ID_BUTTON2 };

class AOLCPP3_EX : public AOLCPP3
{
public:
	void PutMeInsideAOL(HWND);
};


LRESULT APIENTRY MainProc(HWND,UINT,WPARAM,LPARAM);

AOLCPP3 aolcpp3; // aolcpp3 object
AOLCPP3_EX aolcpp3_ex;  // my extended aolcpp object
HINSTANCE g_hInst;
HWND list;
HWND button;
HWND button1;
HWND button2;

// put me inside AOL function
void AOLCPP3_EX::PutMeInsideAOL(HWND hwnd)
{
	SetParent(hwnd,aolcpp_interface.getmdi());
}
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

	hwnd = CreateWindow("Master","AOLCPP3 Example",WS_OVERLAPPEDWINDOW,0,0,640,480,0,0,hInst,0);

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
		
			char buff[100];
		    aolcpp3.aolcpp_interface.aolcpp1.getsn(buff);
			LostString snbuff;
			snbuff = "User: ";
			snbuff += buff;
			HWND st;
			st = CreateWindow("Static",snbuff.getstr(),WS_CHILD | WS_VISIBLE,5,5,200,25,hwnd,0,g_hInst,0);
			list = CreateWindowEx(WS_EX_STATICEDGE,"ListBox",NULL,WS_CHILD | WS_VISIBLE | WS_BORDER,5,20,400,400,hwnd,0,g_hInst,0);
			button = CreateWindowEx(WS_EX_STATICEDGE,"Button","Add List",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,5,425,100,25,hwnd,(HMENU)ID_BUTTON,g_hInst,0);
			button1 = CreateWindowEx(WS_EX_STATICEDGE,"Button","Open",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,105,425,100,25,hwnd,(HMENU)ID_BUTTON1,g_hInst,0);
			button2 = CreateWindowEx(WS_EX_STATICEDGE,"Button","-> AOL",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,210,425,100,25,hwnd,(HMENU)ID_BUTTON2,g_hInst,0);
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
							aolcpp3.mail.mailbox_addtolist(list,false);
						}
						break;
					case ID_BUTTON1:
						{
							int len;
							len = SendMessage(list,LB_GETCOUNT,0,0);
							if(len)
							{
								int current;
								current = SendMessage(list,LB_GETCURSEL,0,0);
								aolcpp3.aolcpp_interface.aolcpp1.mail_open(current);
							}

						}
						break;
					case ID_BUTTON2:
						{
							aolcpp3_ex.PutMeInsideAOL(FindWindow("Master",NULL));

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