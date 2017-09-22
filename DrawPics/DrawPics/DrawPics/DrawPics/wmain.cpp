#include"dpic.h"
#include "resource.h"
#include<string>
#include<shellapi.h>
// global variables
HWND the_wnd,cwnd,editwnd,conwnd;
COLORREF cur_color = 0x0;
int i,z;
mxSocket the_socket;



// connect callback procedure
LRESULT APIENTRY ConnectProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {
	switch(msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_CLOSE:
			ShowWindow(hwnd,SW_HIDE);
			break;
		case WM_CREATE:
			{
				editwnd = CreateWindow("Edit","[IP Address]", WS_CHILD | WS_BORDER | WS_VISIBLE,25,25,250,20,hwnd,0,GetModuleHandle(0),0);
				conwnd = CreateWindow("Button","Connect", WS_BORDER | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,25,55,100,20,hwnd,(HMENU)1,GetModuleHandle(0),0);


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
						struct sockaddr_in addy;
						SendMessage(hwnd,WM_SETTEXT,255,(LPARAM)(LPCSTR)"Connecting...");
						the_socket.port = 5001;
						SendMessage(editwnd,WM_GETTEXT,254,(LPARAM)(LPCSTR)the_socket.ip_addy);
						mxConnect(&the_socket,addy);
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
// main window procedure
LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {
	switch(msg) {
		case WM_DESTROY:
			WSACleanup();
			PostQuitMessage(0);
			break;
		case WM_MOUSEMOVE:
			{
				// add new pixels
				static int x=0,y=0;
				x = LOWORD(lParam), y = HIWORD(lParam);
					if(wParam & MK_LBUTTON && x < 640 && y < 480 && x > 0 && y > 0) {
						pixels[x][y].color = cur_color;
						pixels[x][y].on = true;
						SetPixel(GetDC(hwnd),x,y,cur_color);
						char data[256];
						sprintf(data,"%d:%d ",x,y);
						send(the_socket.s,data,int(strlen(data)),0);
					}
			}
			break;
		case WM_PAINT: // heres where we draw the screen
			{
				PAINTSTRUCT ps;
				HDC dc = BeginPaint(hwnd,&ps);
				HBITMAP hbm = CreateCompatibleBitmap(dc,640,480);
				HDC cdc = CreateCompatibleDC(dc);
				SelectObject(cdc,hbm);
				SelectObject(cdc,GetStockObject(WHITE_BRUSH));
				Rectangle(cdc,0,0,640,480);
				for(i = 0; i < 640; i++)
					for(z = 0; z < 480; z++)
						if(pixels[i][z].on == true)
							SetPixel(cdc,i,z,pixels[i][z].color);
				BitBlt(dc,0,0,640,480,cdc,0,0,SRCCOPY);
				EndPaint(hwnd, &ps);
				DeleteObject(hbm);
				DeleteDC(cdc);
				DeleteDC(dc);
			}
			break;
		case WM_COMMAND: // proccess the menu
			{
				switch(wParam) 
				{
				case ID_HELP_LOSTSIDEDEAD:
					ShellExecute(0,"open","http://www.lostsidedead.com",0,0,SW_SHOW);
					break;
				case ID_HELP_SOURCECODE:
					ShellExecute(0,"open","drawpics.chm",0,0,SW_SHOW);
					break;
				case ID_FILE_EXIT:
					SendMessage(hwnd,WM_CLOSE,0,0);
					break;
				case ID_ONLINE_CONNECT:
					ShowWindow(cwnd,SW_SHOW);
					UpdateWindow(cwnd);
					break;
				case ID_ONLINE_LISTEN:
					SendMessage(hwnd,WM_SETTEXT,255,(LPARAM)(LPCSTR)"Listening...");
					struct sockaddr_in addy;
					the_socket.port = 5001;
					mxListen(&the_socket,addy);
					break;
				}
			}
			break;
		case ON_SOCKET:// on socket message
			{
				switch (WSAGETSELECTEVENT(lParam)) 
				{
				case FD_ACCEPT:// if message is accept
					the_socket.s = accept(the_socket.s,0,0);
					SendMessage(hwnd,WM_SETTEXT,255,(LPARAM)(LPCSTR)"Start Drawing...");
					break;
				case FD_READ:  // if message is read
					{
					char data[1024];
					memset(data,0,sizeof(data));
					int len = recv(the_socket.s,data,1024,0);
					data[len] = 0;
					std::string str = data;
					std::string x = str.substr(0,str.find(":"));
					std::string y = str.substr(str.find(":")+1,str.length());
					std::string z = x + " =x y=" + y;
					OutputDebugString(z.c_str());
					OutputDebugString("\n");
					int ix = atoi(x.c_str());
					int iy = atoi(y.c_str());
					pixels[ix][iy].color = cur_color;
					pixels[ix][iy].on = true;
					SetPixel(GetDC(hwnd),ix,iy,cur_color);
					}
					break;
				case FD_CONNECT:// if message is connect
					ShowWindow(cwnd,SW_HIDE);
					SendMessage(hwnd,WM_SETTEXT,255,(LPARAM)(LPCSTR)"Start Drawing...");
					break;
				case FD_CLOSE:// if message is close
					SendMessage(hwnd,WM_SETTEXT,255,(LPARAM)(LPCSTR)"Disconnected.");
					break;
				}
			}
			break;
		case WM_CREATE:
			InitWinsock();// Init Windows sockets
			break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}
// applications entry point
int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR lpszLine, int iCmdShow) {
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.hInstance = GetModuleHandle(0);
	wc.hIcon =LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = "DrawPics";
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wc);

	wc.lpszClassName = "ConnectWin";
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc= (WNDPROC) ConnectProc;

	RegisterClassEx(&wc);

	the_wnd = CreateWindow("DrawPics","DrawPics 1.0",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,640,480,0,0,GetModuleHandle(0),0);

	cwnd = CreateWindow("ConnectWin","Connect to IP", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,300,300,0,0,GetModuleHandle(0),0);


	ShowWindow(the_wnd,SW_SHOW);
	UpdateWindow(the_wnd);

	MSG msg;
	while(GetMessage(&msg,0,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return int(msg.wParam);
}