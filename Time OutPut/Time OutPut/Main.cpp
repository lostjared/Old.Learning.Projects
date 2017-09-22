//Inc

#include <Windows.h>

#include "resource.h"

#define NTXFONTHEIGHT(PointSize, hDC)(-MulDiv((PointSize),GetDeviceCaps(hDC,LOGPIXELSY),72))

enum{ID_TIMER=1,ID_TIMER2};

char OutPutTime[100],InTimeMys0N[100],InTimeMys0N2[100],InTimeMys0N3[100],InTimeMys0N4[100],InTimeMys0N5[100];

int OurSecs,OurMins,OurHours;

HFONT hFont;

HWND main,button,static1;

static HINSTANCE g_hInst;

LRESULT APIENTRY WndProc (HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	g_hInst = hInst;
	
	MSG msg;
	
	WNDCLASS wc;
	
	wc.hbrBackground =(HBRUSH)(COLOR_WINDOW);
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpszClassName = "Inc";
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.style = CS_HREDRAW|CS_VREDRAW;
	
	RegisterClass(&wc);
	
	main=CreateWindow ("Inc","Ghett0 Cl0ck",WS_OVERLAPPED|WS_SYSMENU,200,100,270,80,0,0,hInst,0);
	
	ShowWindow(main,SW_SHOW);
	
	UpdateWindow(main);
	
	while(GetMessage(&msg,NULL,NULL,NULL))
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
		
	case WM_TIMER: 
		
		switch (wParam) 
		{ 
        case ID_TIMER: 
            if(OurSecs<10)
			{
				itoa(OurSecs,OutPutTime,10);
				strcpy(InTimeMys0N,":0");
				strcat(InTimeMys0N,OutPutTime);
				strcpy(OutPutTime,InTimeMys0N);
			}
			else
			{
				itoa(OurSecs,OutPutTime,10);
				strcpy(InTimeMys0N,":");
				strcat(InTimeMys0N,OutPutTime);
				strcpy(OutPutTime,InTimeMys0N);
			}
			if((OurMins!=0)&&(OurMins<10))
			{
				itoa(OurMins,InTimeMys0N2,10);
				strcat(InTimeMys0N2,OutPutTime);
				strcpy(InTimeMys0N3,":0");
				strcat(InTimeMys0N3,InTimeMys0N2);
				strcpy(OutPutTime,InTimeMys0N3);
			}
			else if(OurMins==0)
			{
				strcpy(InTimeMys0N2,":00");
				strcat(InTimeMys0N2,OutPutTime);
				strcpy(OutPutTime,InTimeMys0N2);
			}
			else
			{
				itoa(OurMins,InTimeMys0N2,10);
				strcat(InTimeMys0N2,OutPutTime);
				strcpy(InTimeMys0N3,":");
				strcat(InTimeMys0N3,InTimeMys0N2);
				strcpy(OutPutTime,InTimeMys0N3);
			}
			if((OurHours!=0)&&(OurHours<10))
			{
				itoa(OurHours,InTimeMys0N4,10);
				strcpy(InTimeMys0N5,"0");
				strcat(InTimeMys0N5,InTimeMys0N4);
				strcat(InTimeMys0N5,OutPutTime);
				strcpy(OutPutTime,InTimeMys0N5);
			}
			else if(OurHours==0)
			{
				strcpy(InTimeMys0N4,"00");
				strcat(InTimeMys0N4,OutPutTime);
				strcpy(OutPutTime,InTimeMys0N4);
			}
			else
			{
				itoa(OurHours,InTimeMys0N4,10);
				strcat(InTimeMys0N4,OutPutTime);
				strcpy(OutPutTime,InTimeMys0N4);
			}
			if(OurSecs>=59)//60 seconds
			{
				OurSecs=-1;
				OurMins++;
			}
			if(OurMins>=59)//60 minutes
			{
				OurMins=0;
				OurHours++;
			}
			
			SendMessage(static1, WM_SETTEXT, strlen(OutPutTime),(LPARAM)(LPCSTR)OutPutTime);OurSecs++;
			
			break;
		} 
		break;
		
		case WM_DESTROY:
			PostQuitMessage(NULL);
			break;
			
		case WM_CREATE:
			{
				
				HWND groupbox;
				
				groupbox=CreateWindowEx(NULL,"button",NULL,WS_CHILD|WS_VISIBLE|WS_OVERLAPPED|BS_GROUPBOX,7,NULL,250,50,hwnd,NULL,g_hInst,NULL);
				
				static1=CreateWindowEx(NULL,"STATIC","00:00:00",WS_CHILD|WS_VISIBLE,110,20,120,18,hwnd,NULL,g_hInst,NULL);	
				
				hFont=CreateFont(NTXFONTHEIGHT(8,GetDC(button)),NULL,NULL,NULL,400,NULL,NULL,NULL,ANSI_CHARSET,NULL,NULL,DEFAULT_QUALITY,DEFAULT_PITCH,"Arial");
				
				SendMessage(static1, WM_SETFONT,(WPARAM)hFont,NULL);
				
				SetTimer(hwnd,ID_TIMER,100,(TIMERPROC) NULL);
				
				SetWindowPos(hwnd,HWND_TOPMOST,NULL,NULL,NULL,NULL,SWP_NOMOVE|SWP_NOSIZE);
				
				break;
			}
			
		default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return NULL;
}