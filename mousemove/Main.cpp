// how to use mousemoves
// written by jared bruni
// www.lostsidedead.com

#include <windows.h>

LRESULT APIENTRY WndProc(HWND,UINT,WPARAM,LPARAM);
inline void Init();
void SetMyMousePos(int x, int y);

HINSTANCE hInst;
HWND      hwnd;
HWND      hwnd_static;

int APIENTRY WinMain(HINSTANCE hInstx,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	MSG msg;
	hInst = hInstx;
	Init();

	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

// initlize program
inline void Init()
{
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

	hwnd = CreateWindow("Master","MainWindow",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,640,480,0,0,hInst,0);

	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);
}

// callback function
LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	int mx = 0,my = 0;

	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		{
			hwnd_static = CreateWindow("Static",NULL,WS_CHILD | WS_VISIBLE,5,5,300,20,hwnd,0,hInst,0);
		}
		break;
	case WM_ACTIVATEAPP:
		{
			if(!wParam)
			{
				SendMessage(hwnd_static,WM_SETTEXT,15,(LPARAM)(LPCSTR)"Out of Range");
			}

		}
		break;
	case WM_MOUSEMOVE:
		{
			mx = LOWORD(lParam);
			my = HIWORD(lParam);
			SetMyMousePos(mx,my);
		}
		break;
	case WM_LBUTTONDOWN:
		{

		}
		break;
	case WM_LBUTTONUP:
		{


		}
		break;
	case WM_RBUTTONDOWN:
		{


		}
		break;
	case WM_RBUTTONUP:
		{


		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

// set my mouse pos
void SetMyMousePos(int x, int y)
{
	char data[100];
	char dx[10];
	char dy[10];
	itoa(x,dx,10);
	itoa(y,dy,10);
	strcpy(data,"Mouse Position (X: ");
	strcat(data,dx);
	strcat(data, "Y: ");
	strcat(data,dy);
	strcat(data, ") ");
	SendMessage(hwnd_static,WM_SETTEXT,strlen(data),(LPARAM)(LPCSTR)data);
}

