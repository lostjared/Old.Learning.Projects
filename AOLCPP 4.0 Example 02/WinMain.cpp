// winmain entry point
// written by Jared Bruni (master on lsd)
// www.lostsidedead.com
// mail me: masteronlsd@lostsidedead.com

#include <windows.h>
#include "aolcpp4.h"
#include "resource.h"


LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);// call back function
void chatscan(char* sn,char* msg);// chat scan callback function
void proccmd(char* cmd);// process a command
void loadcmdlist();// load the command list

HINSTANCE hInst;
HWND main;
HWND list1;
HWND list2;

int APIENTRY WinMain(HINSTANCE hInstx,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	hInst = hInstx;
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = "MasterCom";
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	main = CreateWindow("MasterCom","AOLCPP4 Example #2 - Simple Chat Commands (CCOM)",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,420,220,0,0,hInst,0);

	ShowWindow(main,SW_SHOW);
	UpdateWindow(main);

	aol4.SetChatComScan(chatscan);
	SetTimer(main,1,1,NULL);


	aol4.SendText(" - aolcpp4 example #2- simple chat commands");
	aol4.SendText(" - www.lostsidedead.com/aolcpp4/");
	aol4.SendText(" - masteronlsd");


		
	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		aol4.SendText(" - simple chat commands example unloaded");
		aol4.SendText(" - master on lsd");
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		{
			HWND st;
			HWND st2;
			st = CreateWindow("Static","Command List",WS_CHILD | WS_VISIBLE,5,5,100,25,hwnd,0,hInst,0);
			st2 = CreateWindow("Static","Commands Proccesed",WS_CHILD | WS_VISIBLE,5+200+5,5,200,25,hwnd,0,hInst,0);
			list1 = CreateWindowEx(WS_EX_STATICEDGE,"ListBox",NULL,WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL,5,25,200,150,hwnd,0,hInst,0);
			list2 = CreateWindowEx(WS_EX_STATICEDGE, "ListBox",NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL,5+200+5,25,200,150,hwnd,0,hInst,0);
			loadcmdlist();
		}
		break;
	case WM_TIMER:
		aol4.ChatComScan();
		break;
	case WM_COMMAND:
		{
			switch(wParam)
			{
			case ID_ABOUT:
				MessageBox(main,"AOLCPP Example #2 - Master /Jared\nThis example includes, writing a simple ccom, making windows, using incons, using menus, and using listboxs","AOLCPP4 Example #2 About",MB_OK | MB_ICONINFORMATION);
				break;
			}

		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}


// chat scan call back function process
void chatscan(char* sn,char* msg)
{
	char mysn[100];
	aol4.GetScreenName(mysn);

	// yep its me talking
	if(mstrcmp(sn,mysn) == true)
	{
		proccmd(msg);
	}

}
// process a command
void proccmd(char* cmd)
{
	if(findstr(cmd,".ghost on") != -1)
	{
		aol4.GhostOn();
		aol4.SendText(" - ghosting on");
		goto addtolist;
	}

	if(findstr(cmd,".ghost off") != -1)
	{
		aol4.GhostOff();
		aol4.SendText(" - ghosting off");
		goto addtolist;
	}

	if(findstr(cmd,".ims on") != -1)
	{
		aol4.SendInstantMessage("$IM_ON","STUFF");
		aol4.SendText(" - ims on");
		goto addtolist;
	}

	if(findstr(cmd,".ims off") != -1)
	{
		aol4.SendInstantMessage("$IM_OFF","STUFF");
		aol4.SendText("- ims off");
		goto addtolist;
	}


	return;
addtolist:
	SendMessage(list2,LB_ADDSTRING,255,(LPARAM)(LPCSTR)cmd);// was a command
}

// load the command list
void loadcmdlist()
{
	SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR)".ghost on");
	SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR)".ghost off");
	SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR)".ims on");
	SendMessage(list1,LB_ADDSTRING,255,(LPARAM)(LPCSTR)".ims off");
}