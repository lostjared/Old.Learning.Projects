#include<windows.h>
#include"browser.h"

HWND hwnd;
mxBrowser b(L"http://www.lostsidedead.com/index.php3");

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {
	switch(msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_CREATE:
			break;
		case WM_LBUTTONDOWN:
			break;
		case WM_SIZE: {
			RECT rc;
			GetClientRect(hwnd,&rc);
			b.ResizeWindow(&rc);
		}
	    break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

int PASCAL WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR lpszLine, int nCmdShow) {


	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = "BrowserTest";
	wc.lpszMenuName =  NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInst;

	if(!RegisterClassEx(&wc)) { MessageBox(NULL,"Error Registering Class","Error",MB_OK | MB_ICONERROR); return 0; }



	OleInitialize(0);
	hwnd = CreateWindow("BrowserTest","Example Browser Control - Jared Bruni", WS_OVERLAPPEDWINDOW,0,0,640,480,0,0,GetModuleHandle(0),0);
	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);
	b.startBrowser();
	// b.ViewSite(L"http://google.com");
	// to view a different page
	MSG msg;
	while(GetMessage(&msg,0,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	OleUninitialize();
	return 0;
}