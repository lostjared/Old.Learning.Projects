/*  masterio for MasterConsole
written by Jared Bruni
in the C programming Language
www.LostSideDead.com

  "Open Source, Open Mind"
*/


#ifndef _MASTERIO_H_
#define _MASTERIO_H_
#define MASTER_IN WM_USER + 5
#define MASTER_OUT WM_USER + 6
#define MASTER_DONE WM_USER + 7
#define MASTER_INIT WM_USER + 8
#define MASTER_CLEAR WM_USER + 9
#define MASTER_PAUSE WM_USER + 10
#include <windows.h>
#include <stdarg.h>
#include <stdio.h>
#define true 1
#define false 0
#define bool int


/* function prototypes */
LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void Init();
void mprintf( const char *str, ... );
void mscanf(const char *str, ...);
void concat( const char *str );
void input(char* );
void mflush();
void mclear();
void mpause();
int  miint();
long milong();
double midouble();


/* global variables */
HWND hwnd;
HWND hconsole;
HWND hpipe;
char* the_line;
int mastermain(char* argument);
bool in_go;
bool pause_go;


int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	MSG msg;
	the_line = line;
	hconsole = FindWindow("MasterConsole",NULL);
	
	if( hconsole == NULL )
	{
zerror:
	MessageBox(0,"Error!\nThis application must be ran from the MasterConsole command line"," Runtime Error", MB_ICONERROR );
	return (0);
	}
	hpipe = FindWindowEx(hconsole,0,"Static",0);
	if(hpipe == NULL)
	{
		goto zerror;
	}
	
	Init();
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (0);
}


void Init()
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = NULL;
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = "master_console_app";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	
	RegisterClass(&wc);
	
	hwnd = CreateWindow("master_console_app","",WS_OVERLAPPED,0,0,0,0,0,0,GetModuleHandle(NULL),0);
	
}


LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch ( msg )
	{
		
	case WM_DESTROY:
		SendMessage(hconsole,MASTER_DONE,0,0);
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		{
			// init
			SendMessage(hconsole,MASTER_INIT,0,0);
			mastermain(the_line);
			SendMessage(hwnd,WM_CLOSE,0,0);
		}
		break;
	case MASTER_IN:
		{
			in_go = false;
		}
		break;
	case MASTER_PAUSE:
		{
			pause_go = false;
		}
		break;
		
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
		
	}
	
	return (0);
}


/* print formated text */
void mprintf( const char *str, ... )
{
	va_list list; 
	char string[5000];
	va_start(list, str); 
	vsprintf((char*)string,str,list);
	va_end(list); 	
	concat(string);
}

/* scan for input strings */
void mscanf(const char *str, ...)
{
	va_list list;
	

	va_start(list, str);
	while( *str )
	{
		switch(*str++)
		{
		case 's':// string
			{
				char* pcharacter;
			 	pcharacter = va_arg(list,char*);
				input(pcharacter);				
			}
			break;
		}
	}

	va_end(list);
}

/* concatinate data to the buffer */
void concat(const char *buffer)
{
	SendMessage(hpipe,WM_SETTEXT,strlen(buffer)+1,(LPARAM)(LPCSTR)buffer);
	SendMessage(hconsole,MASTER_OUT,0,0);	
}

// input from the buffer
void input(char* buffer)
{
	/* send the signal to do input */
	/* wait in a do events loop */
	in_go = true;
	SendMessage(hconsole, MASTER_IN, 0,0);

	/* lets wait until, its time to read in the dat */
	while( in_go == true )
	{
		MSG msg;
		int t = PeekMessage(0,0,0,0,PM_NOREMOVE);
		if(t == WM_QUIT) { break; }
		TranslateMessage(&msg); 
		DispatchMessage(&msg);
	}


	SendMessage(hpipe,WM_GETTEXT,5000,(LPARAM)(LPCSTR)buffer);
}

void mflush()
{
	SendMessage(hconsole,MASTER_CLEAR,0,0);
}

void mclear()
{
	mflush();
}

void mpause()
{
	SendMessage(hconsole,MASTER_PAUSE,0,0);

	pause_go = true;

	while(pause_go == true)
	{
		MSG msg;
		int t = PeekMessage(0,0,0,0,PM_NOREMOVE);
		if(t == WM_QUIT) { break; }
		TranslateMessage(&msg); 
		DispatchMessage(&msg);
	}
}

int  miint()
{
	char input_buffer[255];
	mscanf("%s",input_buffer);
	return (atoi(input_buffer));
}

long milong()
{
	char input_buffer[255];
	mscanf("%s",input_buffer);
	return (atol(input_buffer));
}

double midouble()
{
	char input_buffer[255];
	mscanf("%s",input_buffer);
	return (atof(input_buffer));
}



#endif