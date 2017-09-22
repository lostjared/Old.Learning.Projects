// masterrpg Level Editor 
// written by jared bruni
// www.lostsidedead.com

#include "thehead.h"


inline void Init();

HINSTANCE hInst;
HWND mainwindow;
HWND sthwnd[LevelSize];
HBITMAP graphics[GRAPHIC_MAX];
int cur_image = 0;
int cur_draw = 0;
LevelStructure level;
HFONT myfont = MakeFont("Arial",14);
char filename[100];

// entry point
int APIENTRY WinMain(HINSTANCE hInstx,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	hInst = hInstx;
	strcpy(filename,"Untitled.mrpg");
	MSG msg;
	Init();
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

// init the application
inline void Init()
{
	LoadGraphics();
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH )GetStockObject(LTGRAY_BRUSH);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hInstance = hInst;
	wc.lpfnWndProc = (WNDPROC) MainProc;
	wc.lpszClassName = "MasterRPGLE";
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	mainwindow = CreateWindow("MasterRPGLE","MasterRPG Level Editor",WS_OVERLAPPED|WS_SYSMENU|WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,640,390,0,0,hInst,0);

	UpdateTitle();
	ShowWindow(mainwindow,SW_SHOW);
	UpdateWindow(mainwindow);
}

// loading graphics
void LoadGraphics()
{

	graphics[0] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP1));
	graphics[1] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP2));
	graphics[2] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP3));
	graphics[3] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP4));
	graphics[4] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP5));
	graphics[5] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP6));
	graphics[6] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP7));
	graphics[7] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP8));
	graphics[8] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP9));
	graphics[9] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP10));
	graphics[10] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP11));
	graphics[11] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP12));
	graphics[12] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP13));
	graphics[13] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP14));
	graphics[14] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP15));
}

// delete graphics
void DeleteGraphics()
{
	for(int i = 0; i <= GRAPHIC_MAX; i++)
	{
		if(graphics[i] != NULL)
		{
			DeleteObject(graphics[i]);
		}
	}
}

// set the default font
void SetFont(HWND hwnd)
{
	SetFont(hwnd,myfont);
}
