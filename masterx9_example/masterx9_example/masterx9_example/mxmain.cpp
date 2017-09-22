#include "mx3d.h"

class Example : public mxApp {

public:
	Example() {
		init();
	}

	virtual void init() {
		if(Init("Mx3d",false,CW_USEDEFAULT,CW_USEDEFAULT,640,480,WndProc,LoadIcon(NULL,IDI_APPLICATION))) {
			if(InitDX(false,24)) {
				InitLoop();
			}
		}
		else
			ErrorMsg("Couldnt initalize DirectX 9\n");
	}

	virtual void render(int screen) {
		text.printtextf(10,10,"Hello World");
	}

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,WPARAM wParam, LPARAM lParam) {
		switch(msg) {
			case WM_ACTIVATEAPP:
				example.active = wParam;
				break;
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
		}

		return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	static Example example;
};

Example Example::example;

// only needed for compatiblity sakes
int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszLine, int nCmdShow) {
	return 0;
}