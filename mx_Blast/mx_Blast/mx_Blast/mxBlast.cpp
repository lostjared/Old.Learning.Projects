#include "mxBlast.h"

mxBlast blast;


LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {

	switch(msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_ACTIVATEAPP:
			blast.active = wParam;
			break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}
