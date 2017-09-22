// AOLCPP4 example #3 - AFK BOT
// Written by Jared Bruni

#include "thehead.h"


HWND editre;// reason
HWND view;
HWND afk;
HWND list1;

enum { ID_LIST1 = 1, ID_VIEW , ID_AFK };

int stall_count = 0;

// entry point
int APIENTRY WinMain(HINSTANCE hInstx,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	
	aol4.SetChatComScan(chatscan);
	aol4.SendText(" - aolcpp4 example #3 afk bot");
	char mysn[100];
	aol4.GetScreenName(mysn);
	char xoutput[100];
	strcpy(xoutput,"- loaded by: ");
	strcat(xoutput,mysn);
	aol4.SendText(xoutput);

	hInst = hInstx;
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hInstance = hInst;
	wc.lpfnWndProc = (WNDPROC) MainProc;
	wc.lpszClassName = "MasterMain";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	wc.lpszClassName = "MasterView";
	wc.lpfnWndProc = (WNDPROC) ViewProc;

	RegisterClass(&wc);

	main = CreateWindow("MasterMain","AOLCPP Example #3 - AFK Bot",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,300,300,0,0,hInst,0);
	ShowWindow(main,SW_SHOW);
	UpdateWindow(main);

	view_win = CreateWindow("MasterView","Message View",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,200,205,0,0,hInst,0);

	SetTimer(main,1,1,NULL);

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

// CALL Back function for the mainwindow

LRESULT APIENTRY MainProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		aol4.SendText(" - aolcpp4 example #3 unloaded");
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		{
			HWND st;
			st = CreateWindow("Static","Reason for being afk..",WS_CHILD | WS_VISIBLE ,5,5,200,25,hwnd,0,hInst,0);
			editre = CreateWindowEx(WS_EX_STATICEDGE,"Edit",NULL,WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL,5,25,280,100,hwnd,0,hInst,0);
			SetMyFont(editre);
			SetMyFont(st);
			HWND st2;
			st2 = CreateWindow("Static","Recorded Messages",WS_CHILD | WS_VISIBLE,5,25+100+5,200,25,hwnd,0,hInst,0);
			SetMyFont(st2);
			list1 = CreateWindowEx(WS_EX_STATICEDGE,"ListBox",NULL,LBS_NOTIFY | WS_CHILD | WS_VISIBLE | WS_VSCROLL,5,25+100+5+20,280,100,hwnd,(HMENU)ID_LIST1,hInst,0);
			SetMyFont(list1);
			view = CreateWindowEx(WS_EX_STATICEDGE,"Button","View",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,5,+25+100+5+20+100+5-10,75,25,hwnd,(HMENU)ID_VIEW,hInst,0);
			SetMyFont(view);
			afk = CreateWindowEx(WS_EX_STATICEDGE,"Button"," Afk ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,280-70,+25+100+5+20+100+5-10,75,25,hwnd,(HMENU)ID_AFK,hInst,0);
			SetMyFont(afk);

		}
		break;
	case WM_COMMAND:
		{
			switch(HIWORD(wParam))
			{
			case LBN_DBLCLK:
				{
					goto addv;
				}
				break;

			case BN_CLICKED:
				{
					switch(LOWORD(wParam))
					{
					case ID_VIEW:
						{
							goto addv;
addv:
							char buffer[500];
							HWND list;
							list = FindWindowEx(FindWindow("MasterMain",NULL),0,"ListBox",0);
							int cursel;
							cursel = SendMessage(list,LB_GETCURSEL,0,0);

							if(cursel == -1)
							{
								break;
							}

							SendMessage(list,LB_GETTEXT,cursel,(LPARAM)(LPCSTR)buffer);
							int qpos;
							qpos = findstr(buffer,"¿");
							char themsg[500];
							char thesn[500];
							leftcopy(buffer,thesn,qpos-1);
							rightcopy(buffer,themsg,qpos+1);
							ShowMessage(thesn,themsg);
						}
						break;
					case ID_AFK:
						{
							char getafk[100];
							SendMessage(afk,WM_GETTEXT,100,(LPARAM)(LPCSTR)getafk);

							if(strstr(getafk,"Afk")) // yes
							{
								char why[100];
								SendMessage(editre,WM_GETTEXT,100,(LPARAM)(LPCSTR)why);
								if(strlen(why) == 0)
								{
									MessageBox(main,"Please fill out a reason for being afk","Give reason",MB_OK | MB_ICONINFORMATION);
									break;
								}

								strcpy(thereason,why);
								afk_on = true;
								SendMessage(afk,WM_SETTEXT,100,(LPARAM)(LPCSTR)"Back");
								aol4.SendText(" - aolcpp4 example #3 - now afk.");
								char tr[100];
								strcpy(tr,"- the reason: ");
								strcat(tr,thereason);
								aol4.SendText(tr);
								aol4.SendText(" - type /afk and a message");

							}
							else  // no
							{
								afk_on = false;
								aol4.SendText(" - no longer afk");
								SendMessage(afk,WM_SETTEXT,255,(LPARAM)(LPCSTR)"Afk");
							}

						}
						break;
					}
				}
				break;
			}
		}
		break;
	case WM_TIMER:
		{
			aol4.ChatComScan();

			if(afk_on == true)
			{
				stall_count++;

				if(stall_count > 2000)// 2min
				{
					stall_count = 0;
					aol4.SendText(" - aolcpp4 example #3 - now afk.");
					char tr[100];
					strcpy(tr,"- the reason: ");
					strcat(tr,thereason);
					aol4.SendText(tr);
					aol4.SendText(" - type /afk and a message");					
				}
			}

		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

bool isOn()
{
	return afk_on;
}


// set the font
void SetMyFont(HWND hwnd)
{
	SendMessage(hwnd,WM_SETFONT,(WPARAM)(HFONT)thefont,0);
}