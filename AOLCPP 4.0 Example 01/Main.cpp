// AOLCPP4  Example #1 how to make a Simple Bot


#include <windows.h>
#include "aolcpp4.h"

// windows call back function
LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void chatscan(char* sn,char* msg); // chat scan call back function
void randfort(char* buff);// random fourtne



int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	if(aol4.GetChatWindow() == 0)
	{
		MessageBox(0,"please enter a chat room.. then load this program",0,0);
		return 0;
	}

	HWND hwnd;
	WNDCLASS wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = "Master";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	hwnd = CreateWindow("Master","AOLCPP4 - Example #1 - How to make a Simple Chat Bot",WS_OVERLAPPEDWINDOW,0,0,640,480,0,0,hInst,0);
	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);

	
	aol4.SetChatComScan(chatscan); // set the chat scan call back function

	SetTimer(hwnd,1,1,NULL);

	aol4.SendText(" - aolcpp4 example #1 - (simple bot)");
	aol4.SendText(" - aol C++ at its best, - Master on LSD");
	aol4.SendText(" - type /fourtne to get your fourtne");
	
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
		aol4.SendText("- AOLCPP4 bot example shutting down..");
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		{
			aol4.ChatComScan();// update the chatscan
		}
		break;
	
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

// process new lines of text
void chatscan(char* sn,char* msg)
{
	char mysn[100];
	aol4.GetScreenName(mysn);
	if(mstrcmp(sn,mysn) == true)
	{
		return;
	}

	if(findstr(msg,"/fourtne") != -1)
	{
		char respond[200];
		strcpy(respond," - ");
		strcat(respond,sn);
		strcat(respond,"  ");
		char fourt[100];
		randfort(fourt);
		strcat(respond,fourt);
		aol4.SendText(respond);

	}
}
// get there random fourtne
void randfort(char* buff)
{
	switch(rand()%10)
	{
	case 0:
		strcpy(buff,", your going to join the army");
		break;
	case 1:
		strcpy(buff,", you will grow a third testicle");
		break;
	case 2:
		strcpy(buff, " you will be abducted by aliens");
		break;
	case 3:
		strcpy(buff, " you will meet your long lost cousin forest gump");
		break;
	case 4:
		strcpy(buff, " you will get to have sex with a monkey");
		break;
	case 5:
		strcpy(buff, " there everywere, and there lookin for you");
		break;
	case 6:
		strcpy(buff, " you will marry an african princess");
		break;
	case 7:
		strcpy(buff, " the world is a vampire, and its going to bite u");
		break;
	case 8:
		strcpy(buff, " you will be arrested by the FBI in 2 weeks..");
		break;
	case 9:
		strcpy(buff, " you are going to have to give me all your money..");
		break;
	case 10:
		strcpy(buff, " yeah isnt this a simple example? ");
		break;
	}
}