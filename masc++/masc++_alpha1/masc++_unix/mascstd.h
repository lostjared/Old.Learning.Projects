#ifndef _MASC_STD_H__
#define _MASC_STD_H__

#include "masc.h"
#include<sstream>

namespace mascstd {

	static masc::BackEnd *back;

	int file_read(masc::Symbol_Table &t) {
		std::fstream fin;
		fin.open(t.Get("file.file_name").val.c_str(),std::ios::in);
		t["file.buffer"].val = "";
		while(fin.is_open() && !fin.eof()) {
			std::string line;
			std::getline(fin,line);
			t["file.buffer"].val += line + "\n";
		}
		fin.close();
		return 0;
	}

	int file_write(masc::Symbol_Table &t) {
		std::fstream *fout = new std::fstream;
		fout->open(t["file.file_name"].val.c_str(),std::ios::out);
		if(fout->is_open()) {
			*fout << t["file.buffer"].val;
			fout->close();
		}
		else
			std::cout << "**** Error file " << t["file.file_name"].val << " Could not be opened!\n";
		delete fout;
		return 0;
	}

	int file_bread(masc::Symbol_Table &t) {
		std::fstream fin;
		fin.open(t.Get("file.file_name").val.c_str(),std::ios::in);
		t["file.char"].val = "";
		while(fin.is_open() && !fin.eof()) {
			unsigned char ch = 0;
			fin.read(reinterpret_cast<char*>(&ch),sizeof(ch));
			t["file.char"].val += ch;
		}
		std::cout << t["file.char"].val << "\n";
		fin.close();
		return 0;
	}

	int console_clear(masc::Symbol_Table &t) {
#ifdef _WIN32
		system("CLS");
#else
		system("clear");
#endif
		return 0;
	}

	int console_pause(masc::Symbol_Table &t) {
#ifdef _WIN32
		system("PAUSE");
#else
		getchar();
#endif
		return 0;
	}

	int console_input(masc::Symbol_Table &t) {
#ifndef MASC_APACHE
		std::getline(std::cin, t["console.buffer"].val);
#endif
		return 0;
	}


	int console_output(masc::Symbol_Table &t) {
		std::cout << t["console.buffer"].val;
		return 0;
	}
	int console_flush(masc::Symbol_Table &t) {
		t["console.buffer"].val = "";
		return 0;
	}

#ifdef _WIN32
#include<windows.h>
#include<memory.h>

	HDC cdc = 0;
	HBITMAP hbm = 0;

	LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {
		switch(msg) {
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			case WM_KEYDOWN:
				{
					std::ostringstream s;
					s << int(wParam);
					back->symbols.Set(masc::VAR_INTEGER,s.str(),"window.key");
					back->CallProcedure("master.key_press");
				}
				break;
			case WM_MOUSEMOVE:
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
				{
					POINT p = { LOWORD(lParam), HIWORD(lParam) };
					std::ostringstream s,ss;
					s << int(p.x);
					back->symbols.Set(masc::VAR_INTEGER,s.str(),"window.mouse_x");
					ss << int(p.y);
					back->symbols.Set(masc::VAR_INTEGER,ss.str(),"window.mouse_y");
					switch(msg) 
					{
					case WM_MOUSEMOVE:
						back->CallProcedure("master.mousemove");
						break;
					case WM_LBUTTONDOWN:
						back->CallProcedure("master.mousedown");
						break;
					case WM_LBUTTONUP:
						back->CallProcedure("master.mouseup");
						break;
					}
				}
				break;
			case WM_PAINT:
				{
					PAINTSTRUCT ps;
					HDC dc = BeginPaint(hwnd,&ps);
					RECT rc;
					GetClientRect(hwnd,&rc);
					cdc = CreateCompatibleDC(dc);
					hbm = CreateCompatibleBitmap(dc,rc.right,rc.bottom);
					SelectObject(cdc,hbm);
					back->CallProcedure("master.paint");
					BitBlt(dc,0,0,rc.right,rc.bottom,cdc,0,0,SRCCOPY);
					EndPaint(hwnd,&ps);
					DeleteDC(cdc);
					DeleteObject(hbm);
				}
				break;
			default:
				return DefWindowProc(hwnd,msg,wParam,lParam);
		}
		return 0;
	}
	static HWND hwnd;

	int window_create(masc::Symbol_Table &t) {
		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = (HBRUSH) (COLOR_3DFACE+1);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
		wc.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
		wc.hInstance = GetModuleHandle(0);
		wc.lpfnWndProc = (WNDPROC) WndProc;
		wc.lpszClassName = t["window.cls_name"].val.c_str();
		wc.lpszMenuName = 0;
		wc.style = CS_HREDRAW | CS_VREDRAW;
		RegisterClassEx(&wc);
		hwnd = CreateWindow(t["window.cls_name"].val.c_str(),t["window.win_title"].val.c_str(),
			WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX ,atoi(t["window.win_x"].val.c_str()),
			atoi(t["window.win_y"].val.c_str()),atoi(t["window.win_w"].val.c_str()),atoi(t["window.win_h"].val.c_str()),
			0,0,GetModuleHandle(0),0);
		ShowWindow(hwnd,SW_SHOW);
		UpdateWindow(hwnd);
		return 0;
	}

	static HANDLE thandle;
	DWORD thread_id = 0;

	BOOL CALLBACK MsgLoop(void *ptr) {
		MSG msg;
		while(GetMessage(&msg,0,0,0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return FALSE;
	}

	static MSG msg;
	int window_loop(masc::Symbol_Table &t) {
		if(GetMessage(&msg,0,0,0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			t["master.app_over"].val = "1";
		}
		else
			t["master.app_over"].val = "0";
		return 0;
	}

	int window_msgbox(masc::Symbol_Table &t) {
		std::string title = t.Pop().val,message = t.Pop().val;
		MessageBox(GetForegroundWindow(),message.c_str(),title.c_str(),MB_OK | MB_ICONINFORMATION);
		return 0;
	}


	int window_trans(masc::Symbol_Table &t) {
		return 0;
	}

	int window_disp(masc::Symbol_Table &t) {
		return 0;
	}
	int window_waitmsg(masc::Symbol_Table &t) {
		WaitMessage();
		return 0;
	}

	int window_drawtext(masc::Symbol_Table &t) {
		std::string text = t.Pop().val;
		HDC dc = GetDC(hwnd);
		TextOut(dc,atoi(t.Pop().val.c_str()),atoi(t.Pop().val.c_str()),text.c_str(),int(text.length()));
		DeleteDC(dc);
		return 0;
	}

	int window_redraw(masc::Symbol_Table &t) {
		InvalidateRect(hwnd,NULL,FALSE);
		return 0;
	}

#endif

	void SetStdFunc(masc::BackEnd &bend) {
		back = &bend;
		bend.AddExternal("file.read", file_read);
		bend.AddExternal("file.write", file_write);
		bend.AddExternal("file.bread", file_bread);
		bend.AddExternal("console.clear", console_clear);
		bend.AddExternal("console.pause", console_pause);
		bend.AddExternal("console.input", console_input);
		bend.AddExternal("console.output", console_output);
		bend.AddExternal("console.flush", console_flush);
#ifdef _WIN32
		bend.AddExternal("window.create", window_create);
		bend.AddExternal("window.loop", window_loop);
		bend.AddExternal("window.msgbox", window_msgbox);
		bend.AddExternal("window.waitmsg", window_waitmsg);
		bend.AddExternal("window.trans", window_trans);
		bend.AddExternal("window.disp",window_disp);
		bend.AddExternal("window.drawtext", window_drawtext);
		bend.AddExternal("window.redraw", window_redraw);
#endif

	}

}

#endif


