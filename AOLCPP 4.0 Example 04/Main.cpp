// Written by Jared Bruni
// for planetsourcecode
// www.lostsidedead.com


#include <windows.h>
#include "aolcpp4.h"// header file for the AOL Manipulation Library  (AOLCPP4)

LRESULT APIENTRY MainProc(HWND,UINT,WPARAM,LPARAM);// callback function 
void chatscan(char* sn,char* msg); // call back function
void getanswer(char* buffer);// function to get the answer

HWND main;// handle of main window

int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	aol4.SetChatComScan(chatscan);// sets the chatscan function pointer
	// what this does, is point to the function that you want
	// to have the chat messages processed under
	aol4.SendText("-aolcpp4 example#4 - 8 ball bot ");// sends text to the room
	aol4.SendText("-www.lostsidedead.com ( jared bruni / master on lsd )");
	aol4.SendText("type /8ball and a question");

	// setting up are window
	MSG msg;
	WNDCLASS wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hInstance = hInst;
	wc.lpfnWndProc = (WNDPROC) MainProc;
	wc.lpszClassName = "Master_8BALL";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	main = CreateWindow("Master_8BALL","AOLCPP example#4",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,100,100,0,0,hInst,0);

	ShowWindow(main,SW_SHOW);
	UpdateWindow(main);

	// setting are timer
	SetTimer(main,1,1,NULL);

	// message loop
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
// callback function for are windows messages
LRESULT APIENTRY MainProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		aol4.SendText(" - goodbye 8ball off");
		aol4.SendText(" - go get your stuff somewere else!");
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		{
			// ever update, check the room, and if stuff has changed
			// we call the callback function which you pointed to
			// for the messages to be proccessed
			aol4.ChatComScan();
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

// callback for are chat messages
void chatscan(char* sn,char* msg)
{
	// find string, if it exitis
	if(findstr(msg,"/8ball") != -1)
	{
		// do string manipulation, and extract what we need
		char qu[500];
		rightcopy(msg,qu,findstr(msg,"/8ball") + 7);
		char theanswer[100];
		getanswer(theanswer);
		char thefinal[200];
		strcpy(thefinal,"q: ");
		strcat(thefinal,qu);
		strcat(thefinal," a: ");
		strcat(thefinal,theanswer);
		aol4.SendText(thefinal); // send are response to the chatroom
	}
}

// get the answer
void getanswer(char* buffer)
{
	switch(rand()%10)
	{
	case 0:
		strcpy(buffer," quite possible ");
		break;
	case 1:
		strcpy(buffer, " your answer is yes ");
		break;
	case 2:
		strcpy(buffer, " contaminted conclusion ");
		break;
	case 3:
		strcpy(buffer, " your answer is no ");
		break;
	case 4:
		strcpy(buffer, " you have bad luck, you suck! ");
		break;
	case 5:
		strcpy(buffer, " yes, this is true");
		break;
	case 6:
		strcpy(buffer, " comeon now ");
		break;
	case 7:
		strcpy(buffer, " uncertin");
		break;
	case 8:
		strcpy(buffer," yes the meaning of it all ");
		break;
	case 9:
		strcpy(buffer," the echo that is love");
		break;
	case 10:
		strcpy(buffer, " Yes this is the purpose");
		break;
	}
}