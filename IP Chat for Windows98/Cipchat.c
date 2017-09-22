/*

Lost Side Dead Software 
Example of a IP Chat using Pure C
Jared Bruni Lost Side Dead Software Head Programmer

  This Source Code is provided as is, for free to demonstrate
  my ability to code in C.

  
	www.lostsidedead-software.com

  jared@lostsidedead-software.com


*/

#include <windows.h>
#include <string.h>
#include <richedit.h>
#include <winsock.h>
#include "resource.h"

#define OPEN_IM 100
#define L_IM    99
#define CONNECT_IM 101
#define WM_SOCKET 60
#define MYSOCKET_LISTEN 1
#define MYSOCKET_CONNECT 2
#define MYSOCKET_OFF 3
#define LISTEN_OK 4
#define LISTEN_CANCEL 20


LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
LRESULT APIENTRY ChatProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
LRESULT APIENTRY ConnectProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
LRESULT APIENTRY EditProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
LRESULT APIENTRY ListenProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);


void init(HINSTANCE hInst);
void initwinsock();
void initlisten();
void SelectCharFormat(char* name, COLORREF r);
void richaddtext(char* add);
void createchat();



struct sockaddr_in addy;

HWND main;
HWND chat;
HWND chatrich;
HWND chatedit;
HWND openbutton;
HWND lbutton;
HWND imgstatic;
HWND connectwin;
HWND connectedit;
HWND connectenter;
HWND connectstatic;
HWND connectname;
HWND listenwin;
HWND listenedit;
HWND listenok;
HWND listencancel;

HWND splash2;

WNDPROC OldProc;

SOCKET listen_socket;
SOCKET connect_socket;
int mysocket = MYSOCKET_OFF;
BOOL ilisten = FALSE;

HBITMAP hbm;
HINSTANCE g_hInst;
char btn_name[100];
char mysn[100];
char ursn[100];
int x;
int y;
int w;
int h;

	
int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR l, int CmdShow)
{
	MSG msg;
	HBITMAP hbitmap2;

	strcpy(ursn,"");
	LoadLibrary("RichEd32.Dll");
	init(hInst);
	g_hInst = hInst;
	hbitmap2 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
    splash2 = CreateWindowEx(WS_EX_TOPMOST,"STATIC", "INTRO_MASTERONLSD", WS_BORDER | SS_BITMAP|WS_POPUP,1024/2,400,0,0,0,0,hInst,0);
    SendMessage(splash2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbitmap2);
    ShowWindow(splash2, SW_SHOW);
    UpdateWindow(splash2);

	main = CreateWindow("Main","C IP Chat Example",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,400,60,0,0,hInst,0);
	SetTimer(main,1,1000,NULL);
	initwinsock();
	connect_socket = socket(AF_INET,SOCK_STREAM,0);
	WSAAsyncSelect(connect_socket,main,WM_SOCKET,FD_CONNECT|FD_READ|FD_CLOSE|FD_ACCEPT);
	ShowWindow(main,SW_SHOW);
	UpdateWindow(main);

	

	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

/* initilize application */
void init(HINSTANCE hInst)
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = "Main";
	wc.lpszMenuName = NULL;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	wc.lpszClassName = "IM";
	wc.lpfnWndProc = (WNDPROC) ChatProc;

	RegisterClass(&wc);

	wc.lpszClassName = "CONNECT";
	wc.lpfnWndProc = (WNDPROC) ConnectProc;

	RegisterClass(&wc);

	wc.lpszClassName = "LISTEN";
	wc.lpfnWndProc = (WNDPROC) ListenProc;

	RegisterClass(&wc);

}

void initwinsock()
{
	
WORD wVersionRequested;
WSADATA wsaData;
int err;

wVersionRequested = MAKEWORD( 1, 1 );

err = WSAStartup( wVersionRequested, &wsaData );
if ( err != 0 ) {
  	MessageBox(main,"Error Couldnt Init Winsock!","Aborting",MB_ICONINFORMATION);
	PostQuitMessage(0);
    return;
}


if ( LOBYTE( wsaData.wVersion ) != 1 ||
         HIBYTE( wsaData.wVersion ) != 1 ) {
    WSACleanup( );
    return;   

}
}

void initlisten()
{
	if(ilisten == FALSE)
	{

	listen_socket = socket(AF_INET,SOCK_STREAM,0);
	WSAAsyncSelect(listen_socket,main,WM_SOCKET,FD_CONNECT|FD_READ|FD_CLOSE|FD_ACCEPT);
	// begin watching on port 7
  	addy.sin_family = AF_INET;
	addy.sin_port = htons(7);
	addy.sin_addr.s_addr = INADDR_ANY; //inet_addr("172.129.243.252");
   	bind(listen_socket,(struct sockaddr*)&addy,sizeof(addy));
	listen(listen_socket,5);
	ilisten = TRUE;
	}

}

/************** Misc Functions ***************/
void SelectCharFormat(char* name, COLORREF r)
{


	CHARFORMAT m;
	m.crTextColor = r;
	m.cbSize = sizeof(CHARFORMAT);
	m.dwEffects = FW_NORMAL;
	m.yHeight = 10;
	strcpy(m.szFaceName, name);

	if(!SendMessage(chatrich, EM_SETCHARFORMAT, SCF_SELECTION,
		(LPARAM) &m))
	{
		MessageBoxA(main, "Error setting character format", NULL,
			MB_ICONSTOP | MB_OK);
	}

}

void richaddtext(char* add)
{
	int len;
	len = SendMessage(chatrich,WM_GETTEXTLENGTH,0,0);
	SendMessage(chatrich,EM_SETSEL,len,len);
	SendMessage(chatrich,EM_REPLACESEL,strlen(add),(LPARAM)(LPCSTR)add);
}

void createchat()
{
	chat = CreateWindowEx(WS_EX_STATICEDGE | WS_EX_TOPMOST,"IM","Instant Message",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,400,300,0,0,g_hInst,0);
	ShowWindow(chat,SW_SHOW);
	UpdateWindow(chat);
	ShowWindow(connectwin,SW_HIDE);
	ShowWindow(main,SW_HIDE);
	
}


/* Main Window Message Process*/
LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{

	switch(msg)
	{
	case WM_DESTROY:
		DeleteObject(hbm);
		WSACleanup();
		PostQuitMessage(0);
		break;
	case WM_CREATE:

		// Open a Instant Message
		openbutton = CreateWindowEx(WS_EX_STATICEDGE,"Button","Open IP IM",WS_BORDER | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,5,5,100,25,hwnd,(HMENU)OPEN_IM,g_hInst,0);
		imgstatic = CreateWindow("Static",NULL,WS_CHILD|WS_VISIBLE|SS_BITMAP,110,5,0,0,hwnd,0,g_hInst,0);
		lbutton = CreateWindowEx(WS_EX_STATICEDGE,"Button","Listen",WS_BORDER | WS_CHILD | WS_VISIBLE |BS_PUSHBUTTON,400-110,5,100,25,hwnd,(HMENU)L_IM,g_hInst,0);
		hbm = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP1));
		SendMessage(imgstatic,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hbm);


		break;

	case WM_TIMER:

		ShowWindow(splash2,SW_HIDE);
		KillTimer(hwnd,1);

		break;

	case WM_COMMAND:

		switch(HIWORD(wParam))
		{
		case BN_CLICKED:
			switch(LOWORD(wParam))
			{
			case OPEN_IM:
				SendMessage(openbutton,WM_GETTEXT,255,(LPARAM)(LPCSTR)btn_name);
				if(strstr(btn_name,"Open"))
				{
					if(connectwin != 0)
					{
						ShowWindow(connectwin,SW_SHOW);
						SetFocus(connectwin);
					}
					else
					{
						connectwin = CreateWindowEx(WS_EX_STATICEDGE,"CONNECT","Connect To Remote IP",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,215,105,0,0,g_hInst,0);
						ShowWindow(connectwin,SW_SHOW);
						UpdateWindow(connectwin);
					}
				}
				else
				{

				}		
				break;
			case L_IM:

				if(listenwin == 0)
				{

				listenwin = CreateWindowEx(WS_EX_STATICEDGE,"LISTEN","Listen Properties",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,5,5,165,100,0,0,g_hInst,0);

				}
				ShowWindow(listenwin,SW_SHOW);
				UpdateWindow(listenwin);

				break;
			}
			break;
		}
		break;

		case WM_SOCKET:

			switch(LOWORD(lParam))
			{
			case FD_ACCEPT:
			{
				char ConnectString[] = "Connection To User Established";
				struct sockaddr cli_addr;
				char sendi[50];
                int clilen;
				clilen = sizeof(cli_addr);
		     	listen_socket = accept(listen_socket,(struct sockaddr*)&cli_addr,&clilen);

			// connection made
		
			createchat();
			mysocket = MYSOCKET_LISTEN;
		
			SendMessage(chatrich,WM_SETTEXT,255,(LPARAM)(LPCSTR)ConnectString);

			strcpy(sendi,mysn);
			strcat(sendi,"å");
			send(listen_socket,sendi,strlen(sendi),0);

			
			}
				break;
			case FD_CONNECT:
			{
				char ConnectString[] = "Connected To User";
				char sendi[50];
			
				
				// were connected
				createchat();

				mysocket = MYSOCKET_CONNECT;
				SendMessage(chatrich,WM_SETTEXT,255,(LPARAM)(LPCSTR)ConnectString);

				strcpy(sendi,mysn);
			    strcat(sendi,"å");
		      	send(connect_socket,sendi,strlen(sendi),0);



			}
				break;
			case FD_READ:
			{
				switch(mysocket)
				{
				case MYSOCKET_CONNECT:
				{
					char readbuff[2000];
					int  rlen;
					int  i;

					if(recv(connect_socket,readbuff,2000,0))
					{
						if(strstr(readbuff,"å"))
						{
							strcpy(ursn,readbuff);
							rlen = strlen(ursn);
							for(i = 0; i < rlen; i++)
							{
								if(ursn[i] == 'å')
								{
									ursn[i] = 0;
									break;
								}
							}
							
					
						}
						else
						{

							char addsn[100];
							strcpy(addsn,"\r\n");
							strcat(addsn,ursn);
							strcat(addsn,":\t");
							richaddtext(addsn);
							richaddtext(readbuff);


						}
					}

				}
					break;
				case MYSOCKET_LISTEN:
				{
					char readbuff[2000];
					int rlen;
					int i;
			
					if(recv(listen_socket,readbuff,2000,0))
					{
						// command
						if(strstr(readbuff,"å"))
						{
							strcpy(ursn,readbuff);
							rlen = strlen(ursn);
							for(i = 0; i < rlen; i++)
							{
								if(ursn[i] == 'å')
								{
									ursn[i] = 0;
									break;
								}
							}						
								
						
						}
						else
						{
							char addsn[100];
							strcpy(addsn,"\r\n");
							strcat(addsn,ursn);
							strcat(addsn,":\t");
							richaddtext(addsn);
							richaddtext(readbuff);

						}
						
					}
				}
					break;
				}

			}
				break;

			case FD_CLOSE:
			{

			}

				break;
			}

			break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

/***************** CHAT WINDOW PROCESS **************************************/

LRESULT APIENTRY ChatProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:

		closesocket(listen_socket);
		closesocket(connect_socket);
		
		ShowWindow(hwnd,SW_HIDE);
		SendMessage(main,WM_CLOSE,0,0);

		break;

	case WM_CREATE:

		chatrich = CreateWindowEx(WS_EX_STATICEDGE,"RICHEDIT","",
				ES_AUTOVSCROLL |
				ES_DISABLENOSCROLL |
				ES_MULTILINE |
				ES_NOHIDESEL |
				ES_SAVESEL |
				ES_SELECTIONBAR |
				ES_SUNKEN |
			    ES_READONLY | 
    			WS_BORDER |
				WS_CHILD |
				WS_VISIBLE |
				WS_VSCROLL , 10,50,50,50,hwnd,(HMENU)50,g_hInst,0);

		SendMessage(chatrich, EM_SETEVENTMASK, 0,
		ENM_SELCHANGE | ENM_CHANGE | ENM_PROTECTED | EN_DROPFILES |
		ENM_CORRECTTEXT);
		
		chatedit = CreateWindowEx(WS_EX_STATICEDGE,"Edit","", ES_AUTOHSCROLL | ES_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER,5,100,50,50,hwnd,(HMENU)24,g_hInst,0);
		OldProc = (WNDPROC) SetWindowLong(chatedit,GWL_WNDPROC,(LONG)EditProc);
	

		break;
	case WM_COMMAND:
	{
		switch(HIWORD(wParam))
		{
		case EN_CHANGE:
			switch(LOWORD(wParam))
			{
			case 24:
			{
				// autosend when to big
				char changebuff[200];
				int len;

				len = SendMessage(chatedit,WM_GETTEXTLENGTH,0,0);
				SendMessage(chatedit,WM_GETTEXT,200,(LPARAM)(LPCSTR)changebuff);

				if((len >= 200)||(strstr(changebuff,"\n")))
				{
					switch(mysocket)
					{
					case MYSOCKET_CONNECT:
						send(connect_socket,changebuff,200,0);
						SendMessage(chatedit,WM_SETTEXT,1,(LPARAM)(LPCSTR)"");
						break;
					case MYSOCKET_LISTEN:
						send(listen_socket,changebuff,200,0);
						SendMessage(chatedit,WM_SETTEXT,1,(LPARAM)(LPCSTR)"");
						break;
					}

				}

			
			}
				break;
			}

			break;
	
		}

		break;

	}

	case WM_SIZE:

		w = LOWORD(lParam);
        h = HIWORD(lParam);
		SetWindowPos(chatrich,0,5,5,w-10,h-40,WS_CHILD|WS_VISIBLE);
		SetWindowPos(chatedit,0,5,h-30,w-10,25,WS_CHILD|WS_VISIBLE);
 
 


		break;

	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

/******************** CONNECT WINDOW PROCESS**************************************/

LRESULT APIENTRY ConnectProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:

		ShowWindow(hwnd,SW_HIDE);

		break;
	case WM_CREATE:

		connectstatic = CreateWindow("Static","Enter IP Address",ES_AUTOHSCROLL | ES_LEFT | WS_CHILD|WS_VISIBLE,5,5,200,20,hwnd,0,g_hInst,0);
		connectedit = CreateWindowEx(WS_EX_STATICEDGE,"Edit",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,5,25,200,20,hwnd,0,g_hInst,0);
		connectenter = CreateWindowEx(WS_EX_STATICEDGE,"Button","Connect",WS_CHILD | WS_VISIBLE | WS_BORDER ,220-90,50,75,25,hwnd,(HMENU)CONNECT_IM,g_hInst,0);
		connectname = CreateWindowEx(WS_EX_STATICEDGE,"Edit","User Anonymous", ES_AUTOHSCROLL | ES_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER,5,50,120,25,hwnd,0,g_hInst,0);




		break;

	case WM_COMMAND:

		switch(HIWORD(wParam))
		{
		case BN_CLICKED:
			switch(LOWORD(wParam))
			{
			case CONNECT_IM:
				{

				struct sockaddr_in addy2;
				char ipbuff[100];

				SendMessage(connectedit,WM_GETTEXT,100,(LPARAM)(LPCSTR)ipbuff);
				SendMessage(connectname,WM_GETTEXT,50,(LPARAM)(LPCSTR)mysn);
				mysocket = MYSOCKET_CONNECT;
				addy2.sin_family = AF_INET;
             	addy2.sin_port = htons(7);
             	addy2.sin_addr.s_addr = inet_addr(ipbuff);
            	connect(connect_socket,(struct sockaddr*)&addy2,sizeof(addy2));

				}
				break;
			}
			break;
		}

		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}
//******************** SUBCLASSED EDITBOX WINDOW PROCESS*/

LRESULT APIENTRY EditProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_KEYDOWN:
		switch(wParam)
		{
		case 13:
		{

			char buff[2000];
			char addbuff[2055];
			SendMessage(chatedit,WM_GETTEXT,2000,(LPARAM)(LPCSTR)buff);
		
			switch(mysocket)
			{
			case MYSOCKET_CONNECT:
				send(connect_socket,buff,2000,0);
				break;
			case MYSOCKET_LISTEN:
				send(listen_socket,buff,2000,0);
				break;
			}
	
			SendMessage(chatedit,WM_SETTEXT,1,(LPARAM)(LPCSTR)"");

			if(strlen(buff))
			{
  
			strcpy(addbuff,"\r\n");
			strcat(addbuff,mysn);
			strcat(addbuff,":\t");
	 		richaddtext(addbuff);
		    richaddtext(buff);

			}
		}
		break;
		}
		break;
	default: return CallWindowProc(OldProc,hwnd,msg,wParam,lParam);
	}

	return 0;
}


/********************** ENTER SCREEN NAME FOR LISTEN WINDOW PROCESS*************/

LRESULT APIENTRY ListenProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_CLOSE:
		ShowWindow(hwnd,SW_HIDE);
		break;
	case WM_CREATE:
	{
		HWND xst;

		xst = CreateWindow("Static","Enter Screen Name",WS_CHILD | WS_VISIBLE,5,5,150,20,hwnd,0,g_hInst,0);
		listenedit = CreateWindowEx(WS_EX_STATICEDGE,"Edit",NULL,ES_AUTOHSCROLL | ES_LEFT | WS_BORDER | WS_CHILD | WS_VISIBLE,5,25,150,20,hwnd,0,g_hInst,0);
		listenok = CreateWindowEx(WS_EX_STATICEDGE,"Button","Ok",WS_BORDER | WS_CHILD | WS_VISIBLE,5,45,75,25,hwnd,(HMENU)LISTEN_OK,g_hInst,0);
		listencancel = CreateWindowEx(WS_EX_STATICEDGE,"Button","Cancel",WS_BORDER | WS_CHILD | WS_VISIBLE,80,45,75,25,hwnd,(HMENU)LISTEN_CANCEL,g_hInst,0);

	}
		break;

	case WM_COMMAND:
	{

		switch(HIWORD(wParam))
		{
		case BN_CLICKED:
			switch(LOWORD(wParam))
			{
			case LISTEN_OK:
				{
					SendMessage(listenedit,WM_GETTEXT,50,(LPARAM)(LPCSTR)mysn);
					if(strlen(mysn) < 3)
					{
						MessageBox(hwnd,"Requires Atleaest 3 Characters!","Error",MB_ICONERROR);
						break;
					}

					initlisten();
					ShowWindow(hwnd,SW_HIDE);
					SendMessage(main,WM_SETTEXT,100,(LPARAM)(LPCSTR)"Now Listening For Connection...");

				}

				break;
			case LISTEN_CANCEL:
				ShowWindow(hwnd,SW_HIDE);
				break;
			}
			break;
		}
	}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}
