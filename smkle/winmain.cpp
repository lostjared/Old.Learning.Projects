/*

  MasterKong LE (Level Editor)
  written by Jared Bruni
  www.lostsidedead.com

  open source, open mind

*/

#include "thehead.h"

HINSTANCE hInst;
HWND      mainwindow;
HWND      grid[1240];
HBITMAP   images[IMAGE_MAX];
LevelMap level;
int img_tool;
int img_index;
HWND      gcombo; 
HWND      tcombo;
HWND      ocombo;

char      filename[100];


int APIENTRY WinMain(HINSTANCE hInstx,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	strcpy(filename,"Untitled1.mxk");
	img_tool = 0;
	img_index = 1;

	MSG msg;
	hInst = hInstx;
	Init();
	updatetitle();

	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


inline void Init()
{
	LoadGraphics();
	WNDCLASS wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpfnWndProc = (WNDPROC) MainProc;
	wc.lpszMenuName= MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = "MKONGLE";
	wc.style = CS_HREDRAW | CS_VREDRAW;
	
	RegisterClass(&wc);

	level.gsp = 0;
	level.hsp = 1;

	mainwindow = CreateWindowEx(WS_EX_STATICEDGE,"MKONGLE","MasterKong LE",WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX,0,0,1024-255-150+30,800-250-100,0,0,hInst,0);

	ShowWindow(mainwindow,SW_SHOW);
	UpdateWindow(mainwindow);

}

inline void LoadGraphics()
{
	images[0] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP1));
	images[1] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP2));
	images[2] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP3));
	images[3] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP4));
	images[4] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP5));
	images[5] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP6));
	images[6] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP7));
	images[7] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP8));

}

LRESULT APIENTRY MainProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		{
			
			int bx,by;
			bx = 5; by = 5;
			int gcount = 0;
			
			
			for(int i = 0; i < 700-4+24; i++)
			{
				
				grid[i] = CreateWindow("Static",NULL, WS_CHILD | WS_VISIBLE |SS_BITMAP,bx,by,16,16,hwnd,0,hInst,0);			
				by = by + 16;
				gcount++;
				if(gcount > 23)
				{
					gcount = 0;
					by = 5;
					bx = bx + 16;
				}
				
			}
			
			reloadgrid();

			HWND xst;
			xst = CreateWindow("Static","Graphics",WS_CHILD | WS_VISIBLE,490,5,100,20,hwnd,0,hInst,0);
			gcombo = CreateWindowEx(WS_EX_STATICEDGE,"ComboBox",NULL, WS_BORDER | CBS_DISABLENOSCROLL | WS_CHILD | CBS_DROPDOWNLIST| WS_VISIBLE | WS_VSCROLL,490,20,150,200,hwnd,(HMENU)1,hInst,0);
			HWND rst;
			rst = CreateWindow("Static","Tools",WS_CHILD | WS_VISIBLE,490,50,150,50,hwnd,0,hInst,0);
			tcombo = CreateWindowEx(WS_EX_STATICEDGE,"ComboBox",NULL, WS_BORDER | CBS_DISABLENOSCROLL | WS_CHILD | CBS_DROPDOWNLIST| WS_VISIBLE | WS_VSCROLL,490,70,150,200,hwnd,(HMENU)20,hInst,0);
			HWND bst;
			bst = CreateWindow("Static","Objects ",WS_CHILD | WS_VISIBLE,490,50 + 70,100,20,hwnd,0,hInst,0);
			ocombo = CreateWindowEx(WS_EX_STATICEDGE,"ComboBox",NULL, WS_BORDER | CBS_DISABLENOSCROLL | WS_CHILD | CBS_DROPDOWNLIST| WS_VISIBLE | WS_VSCROLL,490,70 + 70,150,200,hwnd,(HMENU)30,hInst,0);
		

			SendMessage(tcombo,CB_ADDSTRING,100,(LPARAM)(LPCSTR)"Pencil");
			SendMessage(tcombo,CB_ADDSTRING,100,(LPARAM)(LPCSTR)"Square");
			SendMessage(tcombo,CB_ADDSTRING,100,(LPARAM)(LPCSTR)"Fill");
			SendMessage(tcombo,CB_ADDSTRING,100,(LPARAM)(LPCSTR)"Clear");

			SendMessage(gcombo,CB_ADDSTRING,100,(LPARAM)(LPCSTR)"Gray Brick");
			SendMessage(gcombo,CB_ADDSTRING,100,(LPARAM)(LPCSTR)"Grass");
			SendMessage(gcombo,CB_ADDSTRING,100,(LPARAM)(LPCSTR)"Blue Brick");
			SendMessage(gcombo,CB_ADDSTRING,100,(LPARAM)(LPCSTR)"Blue Sky");
			SendMessage(gcombo,CB_ADDSTRING,100,(LPARAM)(LPCSTR)"eblock");
			SendMessage(gcombo,CB_ADDSTRING,100,(LPARAM)(LPCSTR)"black");

			SendMessage(ocombo,CB_ADDSTRING,100,(LPARAM)(LPCSTR)"Grandma");
			SendMessage(ocombo,CB_ADDSTRING,100,(LPARAM)(LPCSTR)"Hero");

			SendMessage(gcombo,CB_SETCURSEL,1,0);
			SendMessage(tcombo,CB_SETCURSEL,0,0);
			SendMessage(ocombo,CB_SETCURSEL,0,0);
		}
		break;
	case WM_LBUTTONDOWN:
		setbrick(LOWORD(lParam),HIWORD(lParam));
		break;
	case WM_MOUSEMOVE:
		{
			if(wParam & MK_LBUTTON)
			{

			setbrick(LOWORD(lParam),HIWORD(lParam));

			}

			

		

		}
		break;
	case WM_RBUTTONDOWN:
		{
			
			int index = ArrayIndexByPoint(LOWORD(lParam),HIWORD(lParam));
			int xpos;
			xpos = SendMessage(ocombo,CB_GETCURSEL,0,0);
			if(xpos == 0)
			{
				level.gsp = index;
				reloadgrid();
				SendMessage(grid[index],STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)images[6]);
			}
			else // 1
			{
				level.hsp = index;
				reloadgrid();
				SendMessage(grid[index],STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)images[7]);
			}
		}
		break;
	case WM_COMMAND:
		{
			MenuProc(wParam);

			switch(LOWORD(wParam))
			{
			case CBN_SELCHANGE:
				{
					switch(HIWORD(wParam))
					{
					case 1:
						{
							img_index = SendMessage(gcombo,CB_GETCURSEL,0,0);
						}
						break;
					case 20:
						{
				
						}
						break;
					}

				}
				break;
			}


		}
		break;
	case WM_CLOSE:
		{
			if(MessageBox(0,"Do you wish to save before exit?","Save?",MB_ICONQUESTION | MB_YESNO) == IDYES)
			{
				MenuProc(ID_FILESAVE);
			}

			SendMessage(hwnd,WM_DESTROY,0,0);
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}