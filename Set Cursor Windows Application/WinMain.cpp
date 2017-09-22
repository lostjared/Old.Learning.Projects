// written by jared bruni
// example for planetsourcecode
// code request, how to load a cursor from file, without script reosurces

#include <windows.h>


LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	HWND hwnd;
	WNDCLASS wc;
	MSG msg;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.hCursor = LoadCursorFromFile("test.cur");
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = "Example";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	hwnd = CreateWindow("Example","Example load cursor from file",WS_OVERLAPPEDWINDOW,0,0,640,480,0,0,hInst,0);

	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);

	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return 0;
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