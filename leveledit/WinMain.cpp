// by jared Bruni (master on lsd)
// here


// note to self: make it werk with new tilemap

#include <windows.h>
#include <fstream.h>
#include "ss420le.h"
#include "c:\sslib\ssxrcex.h"

#include "resource.h"

#define RES_ADD  9
#define RES_RMV 10
#define RES_SAVE 11
#define MAIN_LEFT 12
#define MAIN_RIGHT 13
#define MAIN_SELECT 100
#define OBJ_NEW 14
#define OBJ_EDIT 15
#define OBJ_LIST 16
#define OBJ_COMBO 17
#define OBJ_KILL 18
#define OBJ_SOLID 19
#define OBJ_CREATE 20
#define ID_HELP  4
#define ID_ABT   5
#define BG_KILL  3
#define BG_SOLID 4
#define BG_SAVE  5



LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
LRESULT APIENTRY ResProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
LRESULT APIENTRY ObjProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
LRESULT APIENTRY ObjNewProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
LRESULT APIENTRY SelectProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
LRESULT APIENTRY EditBgProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
LRESULT APIENTRY AboutProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);



void MenuProc(WPARAM wParam);
int ArrayIndexByPoint(int x, int y);
void ReloadGrid();
void LoadGraphics();
void LoadLevelGraphics();
void SetGridImage(int index,HBITMAP hbm,int IMGI);
void EraseGridImage(int index);
bool savefile(char*);
bool savefile2(char*);
bool openfile(char*);
bool openfile2(char*);
void GridLeft();
void GridRight();
void SelectTool(int tool);
void ComboChange();
void UpdateTitle();
void NewFile();
void SaveFile();
void LoadFile();
void HideTools();
void CompileLevel();


//MAIN WINDOW
HWND main;
HWND grid[1240];
HWND sel;
HWND changeimg;
HWND changecombo;
HWND button_left;
HWND button_right;
HWND tool1;
HWND tool2;
HWND tool3;
HWND tool4;
HWND tool5;
HWND tool6;

// RES WINDOW
HWND reswin;
HWND reslist;
HWND resadd;
HWND resrmv;
HWND ressave;

// OBJECT VIEW WINDOW
HWND objwin;
HWND objcombo;
HWND objlist;
HWND objedit;
HWND objnew;

HWND objnewbgwin;
HWND objnewbg;
HWND objnewbgname;
HWND objnewbgkill;
HWND objnewbgsolid;
HWND objnewbgcreate;

int xarray[GSIZE];
int yarray[500];
int zarray[500];
int zbg = 0;
char curfile[100];
int bgedit_cur = SSNULL;

HWND selectlist;
HWND selectwin;
HWND selectok;

HWND bgeditwin;
HWND bgeditname;
HWND bgeditkill;
HWND bgeditsolid;
HWND bgeditsave;

HWND aboutwin;



HFONT xfont = CreateFont(14,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,"Arial");




// GRAPHICS & LEVEL FILE
ss420_Level level;
int  level_index = 0;

HBITMAP level_graphic[300];
int graphic_index = 0;
bool ss_solid = false;
bool ss_kill = false;
bool objOn = false;


HBITMAP brick;
HBITMAP tool1up;
HBITMAP tool1down;
HBITMAP tool2up;
HBITMAP tool2down;
HBITMAP tool3up;
HBITMAP tool3down;
HBITMAP tool4up;
HBITMAP tool4down;
HBITMAP tool5up;
HBITMAP tool5down;
HBITMAP tool6up;
HBITMAP tool6down;


int tool_index = 0;

HINSTANCE hInst;

void LoadGraphics()
{
	tool1up = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP3));
	tool1down = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP4));
	tool2up = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP5));
	tool2down = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP6));
	tool3up = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP8));
	tool3down = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP9));
	tool4up = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP10));
	tool4down = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP11));
	tool5up = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP12));
	tool5down = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP13));
	tool6up = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP14));
	tool6down= LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP15));
	brick = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP7));
}


int APIENTRY WinMain(HINSTANCE hInstx,HINSTANCE hPrev,LPSTR l,int CmdShow)
{

	hInst = hInstx;
	LoadGraphics();
	HWND splash2;
	HBITMAP hbitmap2 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP16));
    splash2 = CreateWindowEx(WS_EX_TOPMOST,"STATIC", "INTRO_MASTERONLSD", WS_BORDER | SS_BITMAP|WS_POPUP,1024/2,400,0,0,0,0,hInst,0);
    SendMessage(splash2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbitmap2);
    ShowWindow(splash2, SW_SHOW);
    UpdateWindow(splash2);


    SetFocus(splash2);


	HWND hwnd;
	MSG msg;
	WNDCLASS wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszMenuName= MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = "SS420LE";
	wc.style = CS_HREDRAW | CS_VREDRAW;
	
	RegisterClass(&wc);

	wc.lpszMenuName= NULL;
	wc.lpszClassName = "SS420RES";
	wc.lpfnWndProc = (WNDPROC) ResProc;

	RegisterClass(&wc);

	wc.lpszMenuName = NULL;
	wc.lpszClassName = "SS420OBJ";
	wc.lpfnWndProc = (WNDPROC) ObjProc;

	RegisterClass(&wc);

	wc.lpszClassName = "SS420OBJNEW";
	wc.lpfnWndProc = (WNDPROC) ObjNewProc;

	RegisterClass(&wc);

	wc.lpszClassName = "SS420SELECT";
	wc.lpfnWndProc = (WNDPROC) SelectProc;

	RegisterClass(&wc);

	wc.lpszClassName = "SS420BGEDIT";
	wc.lpfnWndProc = (WNDPROC) EditBgProc;

	RegisterClass(&wc);

	wc.lpszClassName = "SS420ABOUT";
	wc.lpfnWndProc = (WNDPROC)AboutProc;

	RegisterClass(&wc);


	hwnd = CreateWindowEx(WS_EX_STATICEDGE,"SS420LE","Super Stoner 420 Level Editor Loading..",WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX,0,0,1024-255-150,800-250-100,0,0,hInst,0);
	reswin = CreateWindow("SS420RES","Level Resources",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,100,100,300,305,0,0,hInst,0);
	main = hwnd;
	objwin = CreateWindow("SS420OBJ","Level Objects",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,100,100,215,305,0,0,hInst,0);
	objnewbg = CreateWindow("SS420OBJNEW","New Background Object",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,100,100,200,200,0,0,hInst,0);
	objnewbgwin = CreateWindowEx(WS_EX_STATICEDGE,"SS420OBJNEW","Create New Background Object",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,10,10,215,175,0,0,hInst,0);
	bgeditwin = CreateWindowEx(WS_EX_STATICEDGE,"SS420BGEDIT","Edit Background Object",WS_OVERLAPPED | WS_SYSMENU |WS_MINIMIZEBOX,10,10,215-25,145-35,0,0,hInst,0);
	selectwin = CreateWindowEx(WS_EX_STATICEDGE | WS_EX_TOPMOST,"SS420SELECT","Select Object",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,300,100,300,250,0,0,hInst,0);
	aboutwin = CreateWindowEx(WS_EX_STATICEDGE | WS_EX_TOPMOST,"SS420ABOUT","About SS420VLE",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,400,450,0,0,hInst,0);

	
	strcpy(level.levelname,"Untitled Level");
	strcpy(curfile,"Untitled1.ssl");

	
	int bx,by;
	bx = 5; by = 5;
	int gcount = 0;


	for(int i = 0; i < 700-4+24; i++)
	{

	grid[i] = CreateWindow("Static",NULL, WS_CHILD | WS_VISIBLE |SS_BITMAP,bx,by,16,16,hwnd,0,hInst,0);

	SendMessage(grid[i],STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)brick);

	by = by + 16;
	gcount++;
	if(gcount > 23)
	{
		gcount = 0;
		by = 5;
		bx = bx + 16;
	}

	}

	HWND st;
	int over = 200;
	int up = 120;

	st = CreateWindow("Static","Select Object",WS_CHILD | WS_VISIBLE,700-over,460-up,100,25,hwnd,0,hInst,0);
	sel = CreateWindowEx(WS_EX_STATICEDGE,"Static",NULL, SS_BITMAP | WS_BORDER | WS_CHILD | WS_VISIBLE,700-over,480+4-up,16,15,hwnd,0,hInst,0);
    changeimg = CreateWindowEx(WS_EX_STATICEDGE,"Button","Select",  WS_BORDER  | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,700+16-over+5,480-up,75,25,hwnd,(HMENU)MAIN_SELECT,hInst,0);

	SendMessage(changeimg,WM_SETFONT,(WPARAM)xfont,0);

	
	changecombo = CreateWindowEx(WS_EX_STATICEDGE,"ComboBox",NULL, WS_BORDER | CBS_DISABLENOSCROLL | WS_CHILD | CBS_DROPDOWNLIST| WS_VISIBLE,700-over,430-up,100,200,hwnd,0,hInst,0);

	SendMessage(changecombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Background");
	SendMessage(changecombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Items");
	SendMessage(changecombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Enemys");
	SendMessage(changecombo,CB_SETCURSEL,0,0);

	SendMessage(changecombo,WM_SETFONT,(WPARAM)xfont,0);


	HWND st2;
	st2 = CreateWindow("Static","Select Layer",WS_CHILD | WS_VISIBLE,700-over,410-up,100,20,hwnd,0,hInst,0);

	HWND st3;
	st3 = CreateWindow("Static","Scroll Level",WS_CHILD | WS_VISIBLE,700-over+10,5,100,20,hwnd,0,hInst,0);
	button_left = CreateWindowEx(WS_EX_STATICEDGE,"Button","Left",WS_BORDER | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,700-over,25,50,25,hwnd,(HMENU)MAIN_LEFT,hInst,0);
	button_right = CreateWindowEx(WS_EX_STATICEDGE,"Button","Right",WS_BORDER | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,700-over+57,25,50,25,hwnd,(HMENU)MAIN_RIGHT,hInst,0);

	
	SendMessage(button_left,WM_SETFONT,(WPARAM)xfont,0);
	SendMessage(button_right,WM_SETFONT,(WPARAM)xfont,0);



	HWND st4;
	st4 = CreateWindow("static","Select Tool",WS_CHILD | WS_VISIBLE,700-over+10,55,100,20,hwnd,0,hInst,0);
	tool1 = CreateWindowEx(WS_EX_STATICEDGE,"Static",NULL,WS_BORDER|WS_VISIBLE|WS_CHILD|SS_BITMAP,700-over+10+3,75,32,32,hwnd,0,hInst,0);
	tool2 = CreateWindowEx(WS_EX_STATICEDGE,"Static",NULL,WS_BORDER|WS_VISIBLE|WS_CHILD|SS_BITMAP,700-over+10+3+32+10,75,32,32,hwnd,0,hInst,0);
	tool3 = CreateWindowEx(WS_EX_STATICEDGE,"Static",NULL,WS_BORDER|WS_VISIBLE|WS_CHILD|SS_BITMAP,700-over+10+3,75+32+5,32,32,hwnd,0,hInst,0);
	tool4 = CreateWindowEx(WS_EX_STATICEDGE,"Static",NULL,WS_BORDER|WS_VISIBLE|WS_CHILD|SS_BITMAP,700-over+10+3+32+10,75+32+5,32,32,hwnd,0,hInst,0);
	tool5 = CreateWindowEx(WS_EX_STATICEDGE,"Static",NULL,WS_BORDER|WS_VISIBLE|WS_CHILD|SS_BITMAP,700-over+10+3,75+32+5+32+5,32,32,hwnd,0,hInst,0);
	tool6 = CreateWindowEx(WS_EX_STATICEDGE,"Static",NULL,WS_BORDER|WS_VISIBLE|WS_CHILD|SS_BITMAP,700-over+10+3+32+10,75+32+5+32+5,32,32,hwnd,0,hInst,0);

HBITMAP hbitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
HWND splash;
splash = CreateWindow("STATIC", NULL, SS_BITMAP|WS_CHILD|WS_VISIBLE,700-over+10+3,75+32+5+32+5+32+5,0,0,hwnd,0,hInst,0);
//SendMessage(splash, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbitmap);
SelectTool(0);	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);

	DestroyWindow(splash2);

	HMENU m;
	m = GetSystemMenu(main,false);
	AppendMenu(m,MF_SEPARATOR,0,0);
	AppendMenu(m,MF_STRING,4,"Online Help");
	AppendMenu(m,MF_STRING,ID_HELPABOUT,"About..");


	
	UpdateTitle();

	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

// WndProc (Main Window Process)
LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	int mx;
	int my;

	switch(msg)
	{
	case WM_DESTROY:
		int i;
		for(i = 0; i < 1240; i++)
		{
			if(grid[i])
			{
				DestroyWindow(grid[i]);
			}
		}
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:

		switch(wParam)
		{
		case VK_LEFT:
			GridLeft();
			break;
		case VK_RIGHT:
			GridRight();
			break;
		}

		break;
	case WM_COMMAND:

		MenuProc(wParam);

		switch(HIWORD(wParam))
		{
		case BN_CLICKED:
			switch(LOWORD(wParam))
			{
			case MAIN_LEFT:
				if(level_index > 0)
				{
					level_index = level_index - 24;
					ReloadGrid();
				}
		
				break;
		
			case MAIN_RIGHT:
				if(level_index < LEVEL_SIZE)
				{
					level_index = level_index + 24;
					ReloadGrid();
				}
		
				break;

			case MAIN_SELECT:
				{

				SendMessage(selectlist,LB_RESETCONTENT,0,0);
				// setup list
				ZeroMemory(&zarray,sizeof(zarray));
				int zcount = 0;

				zbg = SendMessage(changecombo,CB_GETCURSEL,0,0);


				for(int z = 0; z < 500; z++)
				{
					switch(zbg)
					{
					case 0:
						{
					//switch selected object
					if(level.bgobject[z].on)
					{
						SendMessage(selectlist,LB_ADDSTRING,255,(LPARAM)(LPCSTR)level.bgobject[z].name);

						zarray[zcount] = z;
						zcount++;
					}
						} 
						break;
					}

				}
			
				SetFocus(selectwin);
				ShowWindow(selectwin,SW_SHOW);
		

				}
				break;
			}

			break;
		}


		break;
	case WM_LBUTTONDOWN:

			mx = LOWORD(lParam);
			my = HIWORD(lParam);
	
		int index;
		index = ArrayIndexByPoint(mx,my);

/*		char ms[100];
		itoa(index,ms,10);
		MessageBox(0,ms,ms,0);
		*/
		// this is NON*GRID Mouse Clicks
		if(index == -1)
		{
			int over = 200;


/*			// check for a new Tool Selection
	700-over+10+3,75,32,32,hwnd,0,hInst,0);
,700-over+10+3+32+10,75,32,32,hwnd,0,hInst,0);
700-over+10+3,75+32+5,32,32,hwnd,0,hInst,0);
,700-over+10+3+32+10,75+32+5,32,32,hwnd,0,hInst,0);
	,700-over+10+3,75+32+5+32+5,32,32,hwnd,0,hInst,0);
,700-over+10+3+32+10,75+32+5+32+5,32,32,hwnd,0,hInst,0);
*/

// tool 1
if((mx > 700-over+10+3) && (mx < 700-over+10+3+32) && (my > 75) && (my < 75+32))
{
	SelectTool(0);
}

if((mx > 700-over+10+3+32+10) && (mx < 700-over+10+3+32+32+10+32) && (my > 75) && (my < 75+32))
{
	SelectTool(1);
}
if((mx > 700-over+10+3) && (mx < 700-over+10+3+32) && (my > 75+32) && (my < 75+32+32))
{
	SelectTool(2);
}

if((mx > 700-over+10+3+32+10) && (mx < 700-over+10+3+32+32+10+32) && (my > 75+32) && (my < 75+32+32))
{
	SelectTool(3);
}

if((mx > 700-over+10+3) && (mx < 700-over+10+3+32) && (my > 75+32+32) && (my < 75+32+32+32))
{
	SelectTool(4);
}

if((mx > 700-over+10+3+32+10) && (mx < 700-over+10+3+32+32+10+32) && (my > 75+32+32) && (my < 75+32+32+32))
{
	SelectTool(5);
}



		}
		else
		{
			// THIS IS GRID (INDEX BEING THE INDEX IN THE ARRAY + LEVEL_INDEX)

			if(objOn)
			{

			switch(tool_index)
			{
			case 0:

			SetGridImage(index,level_graphic[graphic_index],graphic_index);
			break;
			case 1:
				
			

			
			SetGridImage(index,level_graphic[graphic_index],graphic_index);
			SetGridImage(index+1,level_graphic[graphic_index],graphic_index);
			SetGridImage(index+23,level_graphic[graphic_index],graphic_index);
			SetGridImage(index+24,level_graphic[graphic_index],graphic_index);

				
		
			break;

			case 2:


				EraseGridImage(index);



				break;
					case 3:// EYEDROP
					
						if(level.grid.bg[index+level_index].bg_index == SSNULL) { break; }
						graphic_index = level.grid.bg[index+level_index].bg_index;
						ss_solid = level.grid.bg[index+level_index].solid;
						ss_kill  = level.grid.bg[index+level_index].kill;

						if(graphic_index != SSNULL)
						{

						SendMessage(sel,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)(HBITMAP)level_graphic[graphic_index]);

						} else
						{
						SendMessage(sel,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)(HBITMAP)brick);
						}



				break;
			case 4://FILL
				
				if(MessageBox(hwnd,"Are you sure you wish to fill this screen?","CLEAR SCREEN?",MB_ICONQUESTION | MB_YESNO) == IDYES)
				{

					for(int i = 0; i < 700-4+24; i++)
					{
						SetGridImage(i,level_graphic[graphic_index],graphic_index);
					}
				}

				break;

			case 5://SCLR

				if(MessageBox(hwnd,"Are you sure you wish to clear this screen?","CLEAR SCREEN?",MB_ICONQUESTION | MB_YESNO) == IDYES)
				{

					for(int i = 0; i < 700-4+24; i++)
					{
						EraseGridImage(i);
					}
				}

				break;

			}

			}
		}

		break;

	case WM_MOUSEMOVE:

			mx = LOWORD(lParam);
			my = HIWORD(lParam);
			
		
			int cindex; cindex = 0;

			cindex = ArrayIndexByPoint(mx,my);

			if(objOn == false) {

				if(wParam & MK_LBUTTON)
				{


					// no object
				//MessageBox(hwnd,"Error: Please  Select a Object","Object Needed",MB_OK |MB_ICONERROR);
				break;

				}


			}
			if(objOn)
			{

			if(cindex != -1)
			{
				
			if(wParam & MK_LBUTTON)
			{
				switch(tool_index)
				{
				case 0:

		
			   SetGridImage(cindex,level_graphic[graphic_index],graphic_index);
			   break;
			case 1:
		
			


			SetGridImage(cindex,level_graphic[graphic_index],graphic_index);
			SetGridImage(cindex+1,level_graphic[graphic_index],graphic_index);
			SetGridImage(cindex+23,level_graphic[graphic_index],graphic_index);
			SetGridImage(cindex+24,level_graphic[graphic_index],graphic_index);

							
		
			break;

			case 2:

				EraseGridImage(cindex);
				break;
				}

			}

			}

			}


		break;

	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

// Menu Process
void MenuProc(WPARAM wParam)
{
	switch(wParam)
	{
	case ID_IMAGEEDITOR:

		ShowWindow(reswin,SW_SHOW);
		level.graphics.dumplist(reslist);

		break;

	case ID_ONLINEHELP:

	
	
		break;
	case ID_FILECOMPILE:

		CompileLevel();


		break;

	case ID_SCRREFRESH:

		ReloadGrid();

		break;

	case ID_SCRLEFT:
		if(level_index > 0)
		{
					level_index = level_index - 24;
					ReloadGrid();
		}
		
		break;

	case ID_SCRRIGHT:
		if(level_index < LEVEL_SIZE)
		{
					level_index = level_index + 24;
					ReloadGrid();
		}

		break;

	case ID_OBJECTVIEW:

		ShowWindow(objwin,SW_SHOW);
		SetFocus(objwin);

		break;
	case ID_FILENEW:

		// creating a new (reload&clear levelgid)
		NewFile();

		break;
	case ID_FILELOAD:
		// load up a differnt Level
		LoadFile();

		break;

	case ID_FILESAVE:

		if(strstr(curfile,"Untitled1.ssl"))
		{
			char xtest[100];
			if(savefile(xtest))
			{
				strcpy(curfile,xtest);
				SaveFile();
			}
		}
		else
		{

		SaveFile();

		}

		break;


	case ID_FILESAVEAS:
		// Diloag for filename

		char ctest[100];

		if(savefile(ctest))
		{
			strcpy(curfile,ctest);
			SaveFile();
		}
		break;

	case ID_FILEEXIT:

		if(MessageBox(main,"Do you wish to save?","Save?",MB_ICONQUESTION | MB_YESNO) == IDYES)
		{
			MenuProc(ID_FILESAVE); // recursion
		}

		SendMessage(main,WM_CLOSE,0,0);

		break;

	case ID_HELPABOUT:
	case ID_ABT:
		ShowWindow(aboutwin,SW_SHOW);
		break;



	case ID_OBJECTCRBG:
					// index the index's of the array
				int lcount = 0;

				SendMessage(objnewbg,CB_RESETCONTENT,0,0);

				for(int i =0; i < GSIZE;i++)
				{
					if(level.graphics.graphic[i].on)
					{
						SendMessage(objnewbg,CB_ADDSTRING,200,(LPARAM)(LPCSTR)level.graphics.graphic[i].gname);
 						xarray[lcount] = i;
						lcount++;
					}
				}

				if(lcount == 0)
				{
					MessageBox(main,"Image Resources are Required!","Error",MB_ICONERROR);
					break;
				}

				SendMessage(objnewbgkill,BM_SETCHECK,0,0);
				SendMessage(objnewbgsolid,BM_SETCHECK,0,0);
				SendMessage(objnewbgname,WM_SETTEXT,255,(LPARAM)(LPCSTR)"");


				ShowWindow(objnewbgwin,SW_SHOW);
break;

	}
}


// RESOURCE EDITOR PROCESS
LRESULT APIENTRY ResProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{

	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:

		LoadLevelGraphics();
		ShowWindow(hwnd,SW_HIDE);

		break;
	case WM_CREATE:
		reslist = CreateWindowEx(WS_EX_STATICEDGE,"ListBox",NULL, WS_BORDER | WS_VSCROLL | WS_CHILD | WS_VISIBLE,5,5,285,250,hwnd,0,hInst,0);
		resadd = CreateWindowEx(WS_EX_STATICEDGE,"Button","Add", WS_BORDER | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,5,250,75,25,hwnd,(HMENU)RES_ADD,hInst,0);
		resrmv = CreateWindowEx(WS_EX_STATICEDGE,"Button","?",WS_BORDER | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,5+75,250,75,25,hwnd,(HMENU)RES_RMV,hInst,0);
	    ressave = CreateWindowEx(WS_EX_STATICEDGE,"Button","Save",WS_BORDER | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,5+75+75+60,250,75,25,hwnd,(HMENU)RES_SAVE,hInst,0);

		SendMessage(reslist,WM_SETFONT,(WPARAM)xfont,0);
		SendMessage(resadd,WM_SETFONT,(WPARAM)xfont,0);
		SendMessage(resrmv,WM_SETFONT,(WPARAM)xfont,0);
		SendMessage(ressave,WM_SETFONT,(WPARAM)xfont,0);



		break;
	case WM_COMMAND:

		switch(HIWORD(wParam))
		{
		case BN_CLICKED:
			switch(LOWORD(wParam))
			{
			case RES_ADD:

				char bmpfile[100];

				if(openfile(bmpfile))
				{
					level.graphics.add(bmpfile);
					level.graphics.dumplist(reslist);
				}

				ShowWindow(hwnd,SW_RESTORE);
				SetFocus(hwnd);
				break;
			case RES_RMV:

				MessageBox(hwnd,"Here is were you choose all the graphics files you want\nthe game to read and load into memory\nyou then create objects using these images\nimages cannot be removed once embeded because they possibly could be linked\nto objects and that would cause problems\n","SS420LE",MB_OK | MB_ICONINFORMATION);


				break;
			case RES_SAVE:

				LoadLevelGraphics();
				ShowWindow(hwnd,SW_HIDE);

				break;
			}
			break;
		}


		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

// Object Window Process
LRESULT APIENTRY ObjProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		ShowWindow(hwnd,SW_HIDE); 
		break;
	case WM_CREATE:

		HWND st;
		st = CreateWindow("Static","Select Object Group",WS_CHILD | WS_VISIBLE ,5,5,200,20,hwnd,0,hInst,0);
		objcombo = CreateWindowEx(WS_EX_STATICEDGE,"ComboBox",NULL, WS_BORDER | CBS_DISABLENOSCROLL | WS_CHILD | CBS_DROPDOWNLIST| WS_VISIBLE,5,25,200,200,hwnd,(HMENU)OBJ_COMBO,hInst,0);
		objlist = CreateWindowEx(WS_EX_STATICEDGE,"ListBox",NULL, WS_BORDER | LBS_NOTIFY | WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL,5,25+25,200,200,hwnd,(HMENU)OBJ_LIST,hInst,0);
		objedit = CreateWindowEx(WS_EX_STATICEDGE,"Button","Edit",WS_BORDER | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,200-70,25+25+200,75,25,hwnd,(HMENU)OBJ_EDIT,hInst,0);
		objnew = CreateWindowEx(WS_EX_STATICEDGE,"Button","New",WS_BORDER | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,5,25+25+200,75,25,hwnd,(HMENU)OBJ_NEW,hInst,0);
		SendMessage(objcombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Background");
		SendMessage(objcombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Items");
		SendMessage(objcombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Baddies");

		SendMessage(objcombo,WM_SETFONT,(WPARAM)xfont,0);
		SendMessage(objlist,WM_SETFONT,(WPARAM)xfont,0);
		SendMessage(objedit,WM_SETFONT,(WPARAM)xfont,0);
		SendMessage(objnew,WM_SETFONT,(WPARAM)xfont,0);



		break;

	case WM_COMMAND:

		switch(HIWORD(wParam))
		{
		case BN_CLICKED:
			switch(LOWORD(wParam))
			{
			case OBJ_NEW:
				int gcur;
				gcur = SendMessage(objcombo,CB_GETCURSEL,0,0);
				switch(gcur)
				{
				case 0:
					
					// index the index's of the array
				int lcount = 0;

				SendMessage(objnewbg,CB_RESETCONTENT,0,0);

				for(int i =0; i < GSIZE;i++)
				{
					if(level.graphics.graphic[i].on)
					{
						SendMessage(objnewbg,CB_ADDSTRING,200,(LPARAM)(LPCSTR)level.graphics.graphic[i].gname);
 						xarray[lcount] = i;
						lcount++;
					}
				}

				if(lcount == 0)
				{
					MessageBox(main,"Image Resources are Required!","Error",MB_ICONERROR);
					SetFocus(hwnd);
					break;
				}

				SendMessage(objnewbgkill,BM_SETCHECK,0,0);
				SendMessage(objnewbgsolid,BM_SETCHECK,0,0);
				SendMessage(objnewbgname,WM_SETTEXT,255,(LPARAM)(LPCSTR)"");


				ShowWindow(objnewbgwin,SW_SHOW);
				break;
				}

				break;
			case OBJ_EDIT:
			{

				int cur = 0;
				cur = SendMessage(objlist,LB_GETCURSEL,0,0);
			
				int acur = 0;
				acur = SendMessage(objcombo,CB_GETCURSEL,0,0);
				if(acur == -1)
				{
					MessageBox(hwnd,"Please Select Object Type","Select Object Type",MB_ICONERROR);
					break;
				}

				if(cur == -1)
				{
					MessageBox(hwnd,"Please Select Object For Edit","Select Object!",MB_ICONERROR);
					break;
				}
				switch(acur)
				{
				case 0:
					
				ShowWindow(bgeditwin,SW_SHOW);
				SendMessage(bgeditname,WM_SETTEXT,255,(LPARAM)(LPCSTR)level.bgobject[yarray[cur]].name);
				
				if(level.bgobject[yarray[cur]].kill)
				{
					SendMessage(bgeditkill,BM_SETCHECK,1,0);
				}
				else
				{
					SendMessage(bgeditkill,BM_SETCHECK,0,0);
				}

				if(level.bgobject[yarray[cur]].solid)
				{
					SendMessage(bgeditsolid,BM_SETCHECK,1,0);
				}
				else
				{
					SendMessage(bgeditsolid,BM_SETCHECK,0,0);
				}
				bgedit_cur = cur;



					break;
				case 1:
					break;
				case 2:
					break;
				}

				/*
				char test[100];
				itoa(level.bgobject[yarray[cur]].bg_index,test,10);
				*/
				//	graphic_index = level.bgobject[yarray[cur]].bg_index;



			}
				break;
			}
			break;
			case CBN_SELCHANGE:

				switch(LOWORD(wParam))
				{
				case OBJ_COMBO:

					ComboChange();
			
				break;
				}

				break;
		}



		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

LRESULT APIENTRY ObjNewProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		ShowWindow(hwnd,SW_HIDE);
		break;
	case WM_CREATE:

		HWND se;
		se = CreateWindow("Static","Select Image Resource",WS_CHILD | WS_VISIBLE,5,5,200,20,hwnd,0,hInst,0);
		objnewbg = CreateWindowEx(WS_EX_STATICEDGE,"ComboBox",NULL, WS_BORDER | CBS_DISABLENOSCROLL | WS_CHILD | CBS_DROPDOWNLIST| WS_VISIBLE,5,25,200,200,hwnd,0,hInst,0);
		objnewbgname = CreateWindowEx(WS_EX_STATICEDGE,"Edit",NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,5,70,200,20,hwnd,0,hInst,0);
		HWND se2;
		se2 = CreateWindow("Static","Object Name",WS_CHILD | WS_VISIBLE,5,50,200,20,hwnd,0,hInst,0);
		objnewbgkill = CreateWindow("Button","Kill on Clip",BS_CHECKBOX | WS_VISIBLE | WS_CHILD,5,95,100,20,hwnd,(HMENU)OBJ_KILL,hInst,0);
		objnewbgsolid = CreateWindow("Button","Solid",BS_CHECKBOX | WS_VISIBLE | WS_CHILD,105,95,100,20,hwnd,(HMENU)OBJ_SOLID,hInst,0);
		objnewbgcreate = CreateWindowEx(WS_EX_STATICEDGE,"Button","Create",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|WS_BORDER,130,120,75,25,hwnd,(HMENU)OBJ_CREATE,hInst,0);
		
		SendMessage(objnewbg,WM_SETFONT,(WPARAM)xfont,0);
		SendMessage(objnewbgname,WM_SETFONT,(WPARAM)xfont,0);
		SendMessage(objnewbgkill,WM_SETFONT,(WPARAM)xfont,0);
		SendMessage(objnewbgsolid,WM_SETFONT,(WPARAM)xfont,0);
		SendMessage(objnewbgcreate,WM_SETFONT,(WPARAM)xfont,0);

		break;

	case WM_COMMAND:

		switch(HIWORD(wParam))
		{
		case BN_CLICKED:

			switch(LOWORD(wParam))
			{
			case OBJ_KILL:
				{
				int kstate;
				kstate = SendMessage(objnewbgkill,BM_GETCHECK,0,0);
				if(kstate)
				{
					SendMessage(objnewbgkill,BM_SETCHECK,0,0);
				}
				else
				{
					SendMessage(objnewbgkill,BM_SETCHECK,1,0);
				}
				}
				break;
			case OBJ_SOLID:
					{
				int kstate;
				kstate = SendMessage(objnewbgsolid,BM_GETCHECK,0,0);
				if(kstate)
				{
					SendMessage(objnewbgsolid,BM_SETCHECK,0,0);
				}
				else
				{
					SendMessage(objnewbgsolid,BM_SETCHECK,1,0);
				}
				}
				break;
			case OBJ_CREATE:
				{

				char namebuff[100];
				SendMessage(objnewbgname,WM_GETTEXT,255,(LPARAM)(LPCSTR)namebuff);

				if(strlen(namebuff) < 3)
				{
					MessageBox(objnewbg,"Name is Required (3 Characters Minimum)!","Enter Name",MB_ICONERROR);
					break;
				}

				int cur;
				cur = SendMessage(objnewbg,CB_GETCURSEL,0,0);
				if(cur == -1)
				{
					MessageBox(objnewbg,"Please Select Graphic Resource","Resource Required",MB_OK | MB_ICONERROR);
					break;
				}

				// ok lets find a blank node in the object linked list and add
				// our lil item here

				bool ikill = false;
				bool isolid = false;

				int ik;
				int is;

				ik = SendMessage(objnewbgkill,BM_GETCHECK,0,0);
				is = SendMessage(objnewbgsolid,BM_GETCHECK,0,0);
				if(ik)
				{
					ikill = true;
				}
				if(is)
				{
					isolid = true;
				}




				int off = -1;

				for(int v = 0; v < 500; v++)
				{
					if(level.bgobject[v].on == false)
					{
						off = v;
						break;
					}
				}

				if(off == -1)
				{
					MessageBox(objnewbg,"You have Over 500 Resources, more then that will lag macines bro\n\n","To Much Shit",MB_OK | MB_ICONERROR);
					break;
				}

				level.bgobject[v].on = true;
				level.bgobject[v].kill = ikill;
				level.bgobject[v].solid = isolid;
				strcpy(level.bgobject[v].script,"");
				level.bgobject[v].bg_index = xarray[cur];
				strcpy(level.bgobject[v].name,namebuff);
				ShowWindow(hwnd,SW_HIDE);
				objOn = true;
				ComboChange();
				}



				break;
			}

			break;
		}

		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

// SELECT WINDOW PROCESS
LRESULT APIENTRY SelectProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_CLOSE:
		SendMessage(selectlist,LB_RESETCONTENT,0,0);
		ShowWindow(hwnd,SW_HIDE);
		break;
	case WM_CREATE:

		selectlist = CreateWindowEx(WS_EX_STATICEDGE,"ListBox",NULL,WS_CHILD | WS_VISIBLE | WS_BORDER,5,5,285,200,hwnd,0,hInst,0);
		selectok  = CreateWindowEx(WS_EX_STATICEDGE,"Button","Select",WS_CHILD | WS_BORDER | WS_VISIBLE | BS_PUSHBUTTON,215,195,75,25,hwnd,(HMENU)420,hInst,0);

		SendMessage(selectlist,WM_SETFONT,(WPARAM)xfont,0);
		SendMessage(selectok,WM_SETFONT,(WPARAM)xfont,0);

		break;

	case WM_COMMAND:

		switch(HIWORD(wParam))
		{
		case BN_CLICKED:
			switch(LOWORD(wParam))
			{
			case 420:

				// Select the Object
				switch(zbg)
				{
				case 0:
					int c;
					c = SendMessage(selectlist,LB_GETCURSEL,0,0);
					if(c != -1)
					{


					graphic_index = level.bgobject[zarray[c]].bg_index;
					ss_kill = level.bgobject[zarray[c]].kill;
					ss_solid = level.bgobject[zarray[c]].solid;

					SendMessage(sel,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)(HBITMAP)level_graphic[graphic_index]);

					// set the graphic

				     SendMessage(hwnd,WM_CLOSE,0,0);
		

					}
					else
					{
						MessageBox(hwnd,"Please Select Object!","Error!",MB_OK | MB_ICONERROR);
						break;
					}


					break;
				case 1:

					break;
				case 2:

					break;
				}

				break;
			}
			break;
		}


		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

LRESULT APIENTRY EditBgProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_CLOSE:
		ShowWindow(hwnd,SW_HIDE);
		break;
	case WM_CREATE:

		bgeditname = CreateWindow("Static","Background ObjName",WS_CHILD | WS_VISIBLE,10,10,200,20,hwnd,0,hInst,0);
		bgeditkill = CreateWindow("Button","Kill",WS_CHILD | WS_VISIBLE | BS_CHECKBOX,10,30,100,20,hwnd,(HMENU)BG_KILL,hInst,0);
		bgeditsolid = CreateWindow("Button","Solid", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,105,30,100,20,hwnd,(HMENU)BG_SOLID,hInst,0);
		bgeditsave = CreateWindowEx(WS_EX_STATICEDGE,"Button","Save", WS_BORDER | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,105,55,75,25,hwnd,(HMENU)BG_SAVE,hInst,0); 

		SendMessage(bgeditname,WM_SETFONT,(WPARAM)xfont,0);
		SendMessage(bgeditkill,WM_SETFONT,(WPARAM)xfont,0);
	    SendMessage(bgeditsolid,WM_SETFONT,(WPARAM)xfont,0);
		SendMessage(bgeditsave,WM_SETFONT,(WPARAM)xfont,0);


		break;

	case WM_COMMAND:

		switch(HIWORD(wParam))
		{
		case BN_CLICKED:
			switch(LOWORD(wParam))
			{
			case BG_KILL:

				int kstate;
				kstate = SendMessage(bgeditkill,BM_GETCHECK,0,0);
				if(kstate)
				{
					SendMessage(bgeditkill,BM_SETCHECK,0,0);
				}
				else
				{
					SendMessage(bgeditkill,BM_SETCHECK,1,0);
				}


				break;
			case BG_SOLID:

				int sstate;
				sstate = SendMessage(bgeditsolid,BM_GETCHECK,0,0);
				if(sstate)
				{
					SendMessage(bgeditsolid,BM_SETCHECK,0,0);
				}
				else
				{
					SendMessage(bgeditsolid,BM_SETCHECK,1,0);
				}
				
				break;
			case BG_SAVE:
				{
					bool ikill = false;
					bool isolid = false;

					int  ik;
					int  is;
					ik = SendMessage(bgeditkill,BM_GETCHECK,0,0);
					is = SendMessage(bgeditsolid,BM_GETCHECK,0,0);
					if(ik) { ikill = true; }
					if(is) { isolid = true; }

				level.bgobject[yarray[bgedit_cur]].kill = ikill;
				level.bgobject[yarray[bgedit_cur]].solid = isolid;

				ShowWindow(hwnd,SW_HIDE);


				}
				break;
			}
			break;
		}

		break;

	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

LRESULT APIENTRY AboutProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_CLOSE:
		ShowWindow(hwnd,SW_HIDE);
		break;
	case WM_CREATE:
		{

		HWND st;
		st = CreateWindow("Static",NULL,WS_CHILD | WS_VISIBLE |SS_BITMAP,10,10,0,0,hwnd,0,hInst,0);
		SendMessage(st,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)(HBITMAP)LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP17)));
		HWND ed;
		ed = CreateWindowEx(WS_EX_STATICEDGE,"Edit",NULL,ES_READONLY | WS_CHILD|WS_VISIBLE|ES_MULTILINE|WS_VSCROLL,10,230,375,150,hwnd,0,hInst,0);
		HWND bt;
		bt = CreateWindowEx(WS_EX_STATICEDGE,"Button","Ok",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|WS_BORDER,400-75-5-10,390,75,25,hwnd,(HMENU)1,hInst,0);


		
		SendMessage(ed,WM_SETFONT,(WPARAM)xfont,0);
		SendMessage(bt,WM_SETFONT,(WPARAM)xfont,0);

		/* Load in ReadMe Text File & Format Correctly*/
	char code[5000];

	ifstream fin("readme.txt");

	char ch;
	int index = 0;
	while(fin.get(ch))
	{
		if(ch != '\n')
		{

		code[index] = ch;
		index++;
		
		}
		else
		{
			code[index] = '\r';
			code[index+1] = '\n';
			index = index + 2;
		}
	}

	code[index] = 0;
	fin.close();

	SendMessage(ed,WM_SETTEXT,5000,(LPARAM)(LPCSTR)code);


		}
		break;

	case WM_COMMAND:
	{
		switch(HIWORD(wParam))
		{
		case BN_CLICKED:// no need for loword wparam switch since theres only 1 button

			ShowWindow(hwnd,SW_HIDE);

			break;
		}
	}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}


//******** GRID FUNCTIONS


void ComboChange()
{
		int cur;
					cur = SendMessage(objcombo,CB_GETCURSEL,0,0);
					SendMessage(objlist,LB_RESETCONTENT,0,0);

					switch(cur)
					{
					case 0:
					{
						ZeroMemory(&yarray,sizeof(yarray));

						int xc = 0;

						// bg
						for(int z = 0; z < 500;z++)
						{
							if(level.bgobject[z].on)
							{
								SendMessage(objlist,LB_ADDSTRING,255,(LPARAM)(LPCSTR)level.bgobject[z].name);
								// setup special array sort
								yarray[xc] = z;
									xc++;
							}
						}
					}
						break;
					case 1:
						// it
						break;
					case 2:
						// en
						break;
					}
				
	
}

// get the grid index by point
int ArrayIndexByPoint(int x, int y)
{
		int bx,by;
	bx = 0; by = 0;
	int gcount = 0;


	for(int i = 0; i < 700-4+24; i++)
	{

		if((x > bx) && (x < bx+16) && (y>by) && (y<by+16))
		{

			return i;
		}

	by = by + 16;
	gcount++;
	if(gcount > 23)
	{
		gcount = 0;
		by = 0;
		bx = bx + 16;
	}

	}


	// failure

	return -1;
}

// Reload a by index
void ReloadGrid()
{
	for(int i = 0; i < 1240; i++)
	{
		//grid[i+index]
		int cur;
		cur = level.grid.bg[i+level_index].bg_index;
		if(cur != SSNULL)
		{
			SendMessage(grid[i],STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)level_graphic[cur]);
		}
		else
		{

		SendMessage(grid[i],STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)brick);

		}
	}

}

void LoadLevelGraphics()
{
	/*
		HBITMAP hbm;
		BITMAP  bm;
        
		hbm = (HBITMAP)LoadImage(NULL, szBitmap, IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        GetObject(hbm, sizeof(bm), &bm); // size

		if(hbm == NULL) { return; }
		int w;
		w = bm.bmWidth;
		int h;
		h = bm.bmHeight;
		*/
	for(int i = 0; i < 300; i++)
	{
		if(level.graphics.graphic[i].on)
		{
			level_graphic[i] = (HBITMAP)LoadImage(NULL,level.graphics.graphic[i].gname,IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		}
		else
		{
			level_graphic[i] = NULL;
		}
	}
}

void EraseGridImage(int index)
{
	if(index <= 1240)
	{
		SendMessage(grid[index],STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)brick);
		level.grid.bg[index+level_index].bg_index = SSNULL;
    	level.grid.bg[index+level_index].kill = false;
    	level.grid.bg[index+level_index].solid = false;
	}
}

void SetGridImage(int index,HBITMAP hbm,int IMGI)
{

	if(index <= 1240)
	{

	if(hbm)
	{

		SendMessage(grid[index],STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hbm);
	}
	else
	{
		SendMessage(grid[index],STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)brick);
	}

	level.grid.bg[index+level_index].bg_index = IMGI;
	level.grid.bg[index+level_index].kill = ss_kill;
	level.grid.bg[index+level_index].solid = ss_solid;

	}
	
}

void GridLeft()
{
if(level_index > 0)
{

	level_index = level_index - 24;
	ReloadGrid();
}
}

void GridRight()
{
if(level_index < LEVEL_SIZE)
{
	level_index = level_index + 24;
	ReloadGrid();
}
		
}


void SelectTool(int tool)
{
	// clear
SendMessage(tool1,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)tool1up);
SendMessage(tool2,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)tool2up);
SendMessage(tool3,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)tool3up);
SendMessage(tool4,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)tool4up);
SendMessage(tool5,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)tool5up);
SendMessage(tool6,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)tool6up);

tool_index = tool;

switch(tool)
{
case 0:
	SendMessage(tool1,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)tool1down);
	break;
case 1:
	SendMessage(tool2,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)tool2down);
	break;
case 2:
	SendMessage(tool3,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)tool3down);
	break;
case 3:
	SendMessage(tool4,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)tool4down);
	break;
case 4:
	SendMessage(tool5,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)tool5down);
	break;
case 5:
	SendMessage(tool6,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)tool6down);
	break;
}

}

void UpdateTitle()
{
	char xbuff[200];
	strcpy(xbuff,"Super Stoner 420 Visual Level Editor - ");
	strcat(xbuff,curfile);
	SendMessage(main,WM_SETTEXT,200,(LPARAM)(LPCSTR)xbuff);
}


void NewFile()
{
	if(MessageBox(main,"Are you sure you wish to create a new file?\ncurrent data will be lost.","New File?",MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
		HideTools();

		ZeroMemory(&level,sizeof(level));
		level.NULLBG();
		LoadLevelGraphics();
		level_index = 0;
		ReloadGrid();
		strcpy(curfile,"Untitled1.ssl");
		UpdateTitle();
	}
}

void SaveFile()
{
	// check filename
	ofstream fout(curfile,ios::binary);

	fout.write((char*)&level,sizeof(level));

	fout.close();

	UpdateTitle();


}


void LoadFile()
{
	char xtest[100];
	if(openfile2(xtest))
	{
		HideTools();
		strcpy(curfile,xtest);
		ifstream fin(curfile,ios::binary);
		fin.read((char*)&level,sizeof(level));
		fin.close();
		UpdateTitle();
		LoadLevelGraphics();
		objOn = true;
		level_index = 0;
		ReloadGrid();

	}
}


void HideTools()
{
	ShowWindow(objwin,SW_HIDE);
	ShowWindow(objnewbgwin,SW_HIDE);
	ShowWindow(reswin,SW_HIDE);
	ShowWindow(selectwin,SW_HIDE);
	SendMessage(sel,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)(HBITMAP)brick);
	ShowWindow(bgeditwin,SW_HIDE);
}

void CompileLevel()
{

	char xbuff[100];
    GetCurrentDirectory(100,xbuff);
	strcat(xbuff,"\\SS_release");
	CreateDirectory(xbuff,false);

	char gfile[200];
	strcpy(gfile,xbuff);
	strcat(gfile,"\\game.ssl");


	
	for(int i=0;i<GSIZE;i++)
		{
			if(level.graphics.graphic[i].on)
			{
				char xi[10];
				itoa(i,xi,10);
				char addn[100];
				char addnx[100];
				strcpy(addn,"\\ss_");
				strcpy(addnx,"ss_");
				strcat(addn,xi);
				strcat(addnx,xi);
				strcat(addn,".bmp");
				strcat(addnx,".bmp");
				strcpy(level.graphics.graphic[i].loadname,addnx);
     			char cpyx[200];
				strcpy(cpyx,xbuff);
				strcat(cpyx,addn);
				CopyFile(level.graphics.graphic[i].gname,cpyx,false);
			}
		}
		// save temp level file to add to exe

	ofstream fout(gfile,ios::binary);
	fout.write((char*)&level,sizeof(level));
	fout.close();

/*
		ofstream fout("xtemp.ssl",ios::binary);
		fout.write((char*)&level,sizeof(level));
		fout.close(); */

	
	
	/*
		for(i = 0; i < 500; i++)
		{
			if(level.graphics.graphic[i].on)
			{
			// add
			
			}
		}
		*/

}


// FILE DIALOG BOX'z

bool openfile(char* cFile)
{
	char szFile[200];


OPENFILENAME ofn;       // common dialog box structure

strcpy(szFile, "*.bmp");

// Initialize OPENFILENAME
ZeroMemory(&ofn, sizeof(OPENFILENAME));
ofn.lStructSize = sizeof(OPENFILENAME);
ofn.hwndOwner = main;
ofn.lpstrFile = szFile;
ofn.nMaxFile = sizeof(szFile);
ofn.lpstrFilter = "Mas\0*.bmp\0";
ofn.nFilterIndex = 1;
ofn.lpstrFileTitle = NULL;
ofn.nMaxFileTitle = 0;
ofn.lpstrInitialDir = NULL;
ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


if (GetOpenFileName(&ofn)==TRUE) 
{
strcpy(cFile, ofn.lpstrFile);
return true;
}
else
{
return false;
}

}

bool openfile2(char* cFile)
{
	char szFile[200];


OPENFILENAME ofn;       // common dialog box structure

strcpy(szFile, "*.SSL");

// Initialize OPENFILENAME
ZeroMemory(&ofn, sizeof(OPENFILENAME));
ofn.lStructSize = sizeof(OPENFILENAME);
ofn.hwndOwner = main;
ofn.lpstrFile = szFile;
ofn.nMaxFile = sizeof(szFile);
ofn.lpstrFilter = "SSL\0*.SSL\0";
ofn.nFilterIndex = 1;
ofn.lpstrFileTitle = NULL;
ofn.nMaxFileTitle = 0;
ofn.lpstrInitialDir = NULL;
ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


if (GetOpenFileName(&ofn)==TRUE) 
{
strcpy(cFile, ofn.lpstrFile);
return true;
}
else
{
return false;
}

}
bool savefile(char* cFile)
{

	char szFile[200];


OPENFILENAME ofn;       // common dialog box structure

strcpy(szFile, "*.SSL");

// Initialize OPENFILENAME
ZeroMemory(&ofn, sizeof(OPENFILENAME));
ofn.lStructSize = sizeof(OPENFILENAME);
ofn.hwndOwner = reswin;
ofn.lpstrFile = szFile;
ofn.nMaxFile = sizeof(szFile);
ofn.lpstrFilter = "SSL\0*.SSL\0ALL\0*.*\0";
ofn.nFilterIndex = 1;
ofn.lpstrFileTitle = NULL;
ofn.nMaxFileTitle = 0;
ofn.lpstrInitialDir = NULL;
ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


if (GetSaveFileName(&ofn)==TRUE) 
{
strcpy(cFile, ofn.lpstrFile);
return true;
}
else
{
return false;
}


}
bool savefile2(char* cFile)
{

	char szFile[200];


OPENFILENAME ofn;       // common dialog box structure

strcpy(szFile, "*.SSE");

// Initialize OPENFILENAME
ZeroMemory(&ofn, sizeof(OPENFILENAME));
ofn.lStructSize = sizeof(OPENFILENAME);
ofn.hwndOwner = reswin;
ofn.lpstrFile = szFile;
ofn.nMaxFile = sizeof(szFile);
ofn.lpstrFilter = "Super Stoner 420 Executable Level\0*.SSE\0ALL\0*.*\0";
ofn.nFilterIndex = 1;
ofn.lpstrFileTitle = NULL;
ofn.nMaxFileTitle = 0;
ofn.lpstrInitialDir = NULL;
ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


if (GetSaveFileName(&ofn)==TRUE) 
{
strcpy(cFile, ofn.lpstrFile);
return true;
}
else
{
return false;
}


}