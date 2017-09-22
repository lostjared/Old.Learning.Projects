// the Send Window
// Jared Bruni

#include "appHead.h"

HWND snedit;
HWND msgedit;
HWND sendb;

enum { ID_SEND = 1};
enum { ID_STOP = 2};


HWND sendingstop;


LRESULT APIENTRY SendProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_CLOSE:
		ShowWindow(hwnd,SW_HIDE);
		break;
	case WM_CREATE:
		{
			HWND st;
			st = CreateWindow("Static","Screen Names",WS_CHILD | WS_VISIBLE,5,5,100,25,hwnd,0,g_hInst,0);
			snedit = CreateWindow("Edit","",WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | WS_VSCROLL,5,25,285,40,hwnd,0,g_hInst,0);
			SetTheFont(snedit);
			SetTheFont(st);
			HWND st2;
			st2 = CreateWindow("Static","Tag Message",WS_CHILD | WS_VISIBLE,5,70,100,25,hwnd,0,g_hInst,0);
			SetTheFont(st2);
			msgedit = CreateWindow("Edit","",WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | WS_VSCROLL,5,95,285,50,hwnd,0,g_hInst,0);
			SetTheFont(msgedit);
			sendb = CreateWindowEx(WS_EX_STATICEDGE,"Button","Send",WS_CHILD|WS_VISIBLE|WS_BORDER|BS_PUSHBUTTON,190,95+50+5,100,25,hwnd,(HMENU)ID_SEND,g_hInst,0);
			SetTheFont(sendb);
		};
		break;

	case WM_COMMAND:
		{

			switch(HIWORD(wParam))
			{
			case BN_CLICKED:
				{
					switch(LOWORD(wParam))
					{
					case ID_SEND:
						{
							char snbuff[500];
							char tagbuff[500];
							SendMessage(msgedit,WM_GETTEXT,500,(LPARAM)(LPCSTR)tagbuff);
							SendMessage(snedit,WM_GETTEXT,500,(LPARAM)(LPCSTR)snbuff);

							
							if((strlen(snbuff)) && (strlen(tagbuff)))
							{
								ShowWindow(hwnd,SW_HIDE);
								fwd.send(snbuff,tagbuff);
								fwd.on();
								fwd_send = true;
							}
							else
							{
								MessageBox(hwnd,"Please Enter valid Tag and SN List","List of SN",MB_ICONERROR);
							}
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

// the actual sending promp

LRESULT APIENTRY SendingProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_CLOSE:
		{
			ShowWindow(hwnd,SW_HIDE);
			break;
		}
		break;
	case WM_CREATE:
		{
			sendingstr = CreateWindow("Static","Sending % Done!",WS_CHILD | WS_VISIBLE ,5,5,200,25,hwnd,0,g_hInst,0);
			SetTheFont(sendingstr);
			sendingstop = CreateWindowEx(WS_EX_STATICEDGE,"Button","Stop",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,5,30,75,25,hwnd,(HMENU)ID_STOP,g_hInst,0);
			SetTheFont(sendingstop);

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
					case ID_STOP:
						{
							fwd.stop();
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
