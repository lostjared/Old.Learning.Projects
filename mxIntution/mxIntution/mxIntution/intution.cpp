#include "mxIntution.h"

mxIntution in;

int PASCAL WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR lpszLine, int nCmdShow) {
	in.init();
	return 0;
}


LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {

	switch(msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_ACTIVATEAPP:
			in.active = wParam;
			break;
		case WM_KEYDOWN: {
			switch(wParam) {
		case VK_RETURN:
			in.setCircle(true);
			break;
		case VK_SPACE:
			in.setCircle(false);
			break;
			}
			}
		    break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}