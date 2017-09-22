// application main
// jared bruni
// www.lostsidedead.com

#include "appHead.h"
 

// entry point
int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	g_hInst = hInst;
	InitApp(hInst);
	MSG msg;
	fwd.clear();
	SetTimer(mainwindow,1,1,NULL);
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
// init application
void InitApp(HINSTANCE hInst)
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpfnWndProc = (WNDPROC) MainProc;
	wc.lpszClassName = "MailMain";
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	wc.lpszClassName = "SendMain";
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = (WNDPROC) SendProc;

	RegisterClass(&wc);

	wc.lpszClassName = "AboutMain";
	wc.lpfnWndProc = (WNDPROC) AboutProc;

	RegisterClass(&wc);

	wc.lpszClassName = "SendingMain";
	wc.lpfnWndProc = (WNDPROC) SendingProc;

	RegisterClass(&wc);


	mainwindow = CreateWindowEx(WS_EX_STATICEDGE,"MailMain","AOLCPP3 - Mail Fwder",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,420,280,0,0,hInst,0);
	sendwindow = CreateWindowEx(WS_EX_STATICEDGE | WS_EX_TOPMOST,"SendMain","AOLCPP3 - Send Mail",WS_OVERLAPPED | WS_SYSMENU |WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,300,200,0,0,hInst,0);
	aboutwindow = CreateWindowEx(WS_EX_STATICEDGE,"AboutMain","About..",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,320,365,0,0,hInst,0);
	sendingwindow = CreateWindowEx(WS_EX_STATICEDGE,"SendingMain","Sending..",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,200,85,0,0,hInst,0);

		HWND img;
			img = CreateWindow("Static",NULL,WS_CHILD | WS_VISIBLE  | WS_BORDER | SS_BITMAP,5,5,0,0,aboutwindow,0,g_hInst,0);
			SendMessage(img,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP1)));

	ShowWindow(mainwindow,SW_SHOW);
	UpdateWindow(mainwindow);

	aolcpp3.chat.sendtext("- aolcpp3 mail fwder");
	aolcpp3.chat.sendtext("- aolcpp3 http://www.lostsidedead.com/aolcpp3/");

}

// Message Proccess

LRESULT APIENTRY MainProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		{
			main_list = CreateWindowEx(WS_EX_STATICEDGE,"ListBox",NULL,WS_VSCROLL | LBS_NOTIFY | WS_CHILD|WS_BORDER|WS_VISIBLE,5,5,200,220,hwnd,(HMENU)ID_MAILLIST,g_hInst,0);
			main_send = CreateWindowEx(WS_EX_STATICEDGE,"ListBox",NULL,WS_VSCROLL | LBS_NOTIFY | WS_CHILD|WS_BORDER|WS_VISIBLE,210,5,200,220,hwnd,0,g_hInst,0);
			main_badd = CreateWindowEx(WS_EX_STATICEDGE,"Button","Add Mail",WS_CHILD|WS_VISIBLE|WS_BORDER|BS_PUSHBUTTON,5,210,100,25,hwnd,(HMENU)ID_ADDLIST,g_hInst,0);
			main_bclear = CreateWindowEx(WS_EX_STATICEDGE,"Button","Clear List",WS_CHILD|WS_VISIBLE|WS_BORDER|BS_PUSHBUTTON,210,210,100,25,hwnd,(HMENU)ID_CLEARLIST,g_hInst,0);
			main_bsend  = CreateWindowEx(WS_EX_STATICEDGE,"Button","Send",WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,210+100+5+15,210,100-20,25,hwnd,(HMENU)ID_SENDLIST,g_hInst,0);

			SetTheFont(main_bsend);
			SetTheFont(main_bclear);
			SetTheFont(main_badd);
			SetTheFont(main_send);
			SetTheFont(main_list);
		}
		break;
	case WM_TIMER:
		fwd.update();
		break;
	case WM_COMMAND:
		{
			MenuProc(wParam);

			switch(HIWORD(wParam))
			{
			case LBN_DBLCLK:
				{
					switch(LOWORD(wParam))
					{
					case ID_MAILLIST:
						{
							int cur;
							cur = SendMessage(main_list,LB_GETCURSEL,0,0);
							char mbuff[255];
							SendMessage(main_list,LB_GETTEXT,cur,(LPARAM)(LPCSTR)mbuff);
							SendMessage(main_send,LB_ADDSTRING,255,(LPARAM)(LPCSTR)mbuff);
							fwd.pushList(cur);


						}
						break;
					}
				}
				break;
			case BN_CLICKED:
				{
					switch(LOWORD(wParam))
					{
					case ID_ADDLIST:
						{
							if(aolcpp3.aolcpp_interface.aolcpp1.getmailtree())
							{
								SendMessage(main_list,LB_RESETCONTENT,0,0);
								SendMessage(main_send,LB_RESETCONTENT,0,0);
								fwd.clear();

								aolcpp3.mail.mailbox_addtolist(main_list,false);


							}
							else
							{
								MessageBox(hwnd,"Please Open your Mail Box and be on 5.0","Open Mail Box",MB_OK | MB_ICONERROR);

							}
						}
						break;
					case ID_CLEARLIST:
						{
							SendMessage(main_send,LB_RESETCONTENT,0,0);
						}
						break;
					case ID_SENDLIST:
						{
							// check
							int list_len;
							list_len = SendMessage(main_send,LB_GETCOUNT,0,0);

							if(list_len)
							{


							ShowWindow(sendwindow,SW_SHOW);

							}
							else
							{
								MessageBox(hwnd,"Please Build Send List","List Required",MB_OK | MB_ICONERROR);
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


void MenuProc(WPARAM wParam)
{
	switch(wParam)
	{
	case ID_FILEEXIT:
		SendMessage(mainwindow,WM_CLOSE,0,0);
		break;
	case ID_HELPABOUT:
		ShowWindow(aboutwindow,SW_SHOW);
		break;
	case ID_MAIL_ADD:
		{
					if(aolcpp3.aolcpp_interface.aolcpp1.getmailtree())
							{
								SendMessage(main_list,LB_RESETCONTENT,0,0);
								SendMessage(main_send,LB_RESETCONTENT,0,0);
								fwd.clear();

								aolcpp3.mail.mailbox_addtolist(main_list,false);


							}
							else
							{
								MessageBox(mainwindow,"Please Open your Mail Box and be on 5.0","Open Mail Box",MB_OK | MB_ICONERROR);

							}
		}
		break;
	case ID_MAIL_CLEAR:
		{
			SendMessage(main_send,LB_RESETCONTENT,0,0);
		}
		break;
	case ID_MAIL_SEND:
		{
				// check
							int list_len;
							list_len = SendMessage(main_send,LB_GETCOUNT,0,0);

							if(list_len)
							{


							ShowWindow(sendwindow,SW_SHOW);

							}
							else
							{
								MessageBox(mainwindow,"Please Build Send List","List Required",MB_OK | MB_ICONERROR);
							}
						
		}
		break;
	}

}

void SetTheFont(HWND hwnd)
{
	SendMessage(hwnd,WM_SETFONT,(WPARAM)(HFONT)appfont,0);
}
