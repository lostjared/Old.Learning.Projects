/* Making a Tool Window in C
   written by Jared Bruni
   www.LostSidedead.com
*/

#include<windows.h>

LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void Init();
WPARAM Loop();

HWND hwnd;

int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR line,int nShowCmd)
{
	Init();
	return Loop();
}

void Init()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = "Master";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wc);

	hwnd = CreateWindowEx(WS_EX_TOOLWINDOW,"Master","Tool Window",WS_OVERLAPPEDWINDOW,0,0,640,480,0,0,GetModuleHandle(NULL),0);

	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);
}

WPARAM Loop()
{
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
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}