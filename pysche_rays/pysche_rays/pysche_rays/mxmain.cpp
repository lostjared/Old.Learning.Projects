/* written after reading the tutorials on:
	http://www.icarusindie.com/DoItYourSelf/rtsr/
	check them out, really cool.
*/


#include "mx3d.h"
#include "errormsg.h"
#include "psyche_rays.h"

mxHwnd mxhwnd;// masterX hwnd window object
Pysche::Pysche_Ray pr;// Raycast object
HWND hwnd; // window handle for init window
bool run = true;
int window_width = 640, window_height = 480;

// the render callback function, this is called every time the screen updates
void render(int screen) {
	pr.CastRay();
	pr.CopyBuffer(&mxhwnd);// copy the buffer to the screen
}

// Raycasting mxHwnd (MasterX Window Handle) window callback
LRESULT CALLBACK RayProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {

	switch(msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_ACTIVATEAPP:
			mxhwnd.active = wParam;
			break;
		case WM_KEYDOWN:
			{
				switch(wParam) 
				{
				case VK_UP:
					pr.MovePlayer(Pysche::D_UP);
					break;
				case VK_DOWN:
					pr.MovePlayer(Pysche::D_DOWN);
					break;
				case VK_LEFT:
					pr.MovePlayer(Pysche::D_LEFT);
					break;
				case VK_RIGHT:
					pr.MovePlayer(Pysche::D_RIGHT);
					break;
				}

			}
			break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

// The Initilzation Window callback function, for setting up are screen size && color
LRESULT CALLBACK InitProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {
	static HWND combo1, combo2, hok, hcan;
	switch(msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_CREATE:
			{
				if(!(combo1 = CreateWindowEx(0,"ComboBox","",WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 10, 10, 200, 200, hwnd, 0, GetModuleHandle(0),0)))
					throw Error("Error creating combo box!");
				if(!(combo2 = CreateWindowEx(0, "ComboBox", "", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 10, 40, 200, 200, hwnd,0,GetModuleHandle(0),0)))
					throw Error("Error creating combobox!");

				if(!(hok = CreateWindowEx(0,"Button", "Go!", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100,80,100,25,hwnd,(HMENU)1,GetModuleHandle(0),0)))
					throw Error("Error creating ok! button");
				if(!(hcan = CreateWindowEx(0,"Button", "Cancel!", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 205,80,100,25,hwnd,(HMENU)2,GetModuleHandle(0),0)))
					throw Error("Error creating cancel button!");

				SendMessage(combo1,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"320x240");
				SendMessage(combo1,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"640x480");
				SendMessage(combo1,CB_SETCURSEL,1,0);
				SendMessage(combo2,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Pysche Colors");
				SendMessage(combo2,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Red");
				SendMessage(combo2,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Green");
				SendMessage(combo2,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Blue");
				SendMessage(combo2,CB_SETCURSEL,0,0);

			}
			break;
		case WM_COMMAND:
			{
				switch(HIWORD(wParam)) 
				{
				case BN_CLICKED:
					switch(LOWORD(wParam)) 
					{
					case 1:
						LRESULT pos1,pos2;
						pos1 = SendMessage(combo1,CB_GETCURSEL,0,0);
						pos2 = SendMessage(combo2,CB_GETCURSEL,0,0);
						switch(pos1) {
						case 0: window_width = 320; window_height = 240; break;
						case 1: window_width = 640; window_height = 480; break;
						}
						switch(pos2) {
						case 1: pr.SetObjectColor(D3DCOLOR_XRGB(255,0,0)); break;
						case 2: pr.SetObjectColor(D3DCOLOR_XRGB(0,255,0)); break;
						case 3: pr.SetObjectColor(D3DCOLOR_XRGB(0,0,255)); break;
						}
						DestroyWindow(hwnd);
						break;
					case 2:
						run = false;
						DestroyWindow(hwnd);
						break;
					}
					break;
				}
			}
			break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}
// Initalize are masterX HWND Object
int Init() {
	if(mxhwnd.Init("Pysche_Ray", false, 0,0,window_width,window_height,RayProc,LoadIcon(NULL,IDI_APPLICATION)) && mxhwnd.InitDX(false,32)) 
		return mxhwnd.InitLoop(render);
	throw Error("Error initalizing Direct3D!");
	return 0;
}

// Init the Start up Window
int InitWindow() {
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hIconSm = 0;
	wc.hInstance = GetModuleHandle(0);
	wc.lpfnWndProc = (WNDPROC) InitProc;
	wc.lpszClassName = "RayInit";
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if(!RegisterClassEx(&wc))
		throw Error("Error registering window class!");

	if(!(hwnd = CreateWindowEx(0,"RayInit","Raycast Demo", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, 0,0,350,150,0,0,GetModuleHandle(0),0)))
		throw Error("Error creating initalization window!");

		ShowWindow(hwnd,SW_SHOW);
		UpdateWindow(hwnd);

		MSG msg;
		while(GetMessage(&msg,0,0,0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	return 0;
}

// programs entery Point PASCAL CALLBACK APIENTRY all the same __stdcall
int PASCAL WinMain(HINSTANCE the_inst, HINSTANCE prev_inst, LPSTR line, int cmd) {


	try {
		InitWindow();
		if(run == true)
		Init();
	}
	catch(Error &e) {
		MessageBox(0,e.toString(),"Error Exception Thrown!", MB_OK | MB_ICONERROR);
	}
	catch(...) {
		MessageBox(0,"Error Unknown Exception", "Exception Thrown!", MB_OK | MB_ICONERROR);
	}
	
	return 0;
}