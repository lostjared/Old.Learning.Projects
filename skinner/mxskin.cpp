#include <windows.h>
#include "resource.h"



#define LIST1 105
#define BUTTON1 106

#define FEDIT 107
#define FCHANGE 108
#define FCANCEL 109

LRESULT APIENTRY MainProc(HWND,UINT,WPARAM,LPARAM);
LRESULT APIENTRY AboutProc(HWND,UINT,WPARAM,LPARAM);
LRESULT APIENTRY SelectProc(HWND,UINT,WPARAM,LPARAM);
void imageselect();
void loadlist();
void filenamebyindex(int index, char* filename);
void idnamebyindex(int index, char* id);
bool openfile(char* cFile);


struct mlist
{
	char filename[100];
	char fileid[100];

	void set(char*,char*);
};

int flen = 0;
int xlen = 0;
int cur_w = 0;
int cur_h = 0;

char curfile[100];

int curindex = 0;

mlist list[100];


HINSTANCE hInst;

HWND hwnd_main;
HWND hwnd_mlist;
HWND hwnd_edit;


HWND hwnd_about;


HWND hwnd_select;

HWND hwnd_fname;
HWND hwnd_fedit;
HWND hwnd_fchange;
HWND hwnd_fcancel;


int APIENTRY WinMain(HINSTANCE xhInst,HINSTANCE hPrev,LPSTR l,int CmdShow)
{
	strcpy(curfile,"");
	MSG msg;
	WNDCLASS wc;
	hInst = xhInst;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	wc.lpfnWndProc = (WNDPROC)MainProc;
	wc.lpszClassName = "MasterXSkin_Main";
	wc.lpszMenuName = NULL;

	RegisterClass(&wc);

	wc.lpfnWndProc = (WNDPROC)AboutProc;
	wc.lpszClassName = "MasterXSkin_About";
	wc.lpszMenuName = NULL;

	RegisterClass(&wc);

	wc.lpfnWndProc = (WNDPROC)SelectProc;
	wc.lpszClassName = "MasterXSkin_Select";
	wc.lpszMenuName = NULL;

	RegisterClass(&wc);

	hwnd_main = CreateWindowEx(WS_EX_STATICEDGE,"MasterXSkin_Main","MasterX- Interface Design",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,300,295,0,0,hInst,0);
	hwnd_about = CreateWindowEx(WS_EX_STATICEDGE,"MasterXSkin_About","MasterX-Interface Skinner",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,315,335,0,0,hInst,0);
	hwnd_select = CreateWindowEx(WS_EX_STATICEDGE | WS_EX_TOPMOST,"MasterXSkin_Select","[Select]",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,180+40,85,0,0,hInst,0);

	SetTimer(hwnd_about,0,2500,0);


	ShowWindow(hwnd_about,SW_SHOW);
	UpdateWindow(hwnd_about);

	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return msg.wParam;
}

LRESULT APIENTRY MainProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
	
	
		hwnd_mlist = CreateWindowEx(WS_EX_STATICEDGE | WS_EX_CLIENTEDGE,"ListBox",NULL,WS_VSCROLL | WS_CHILD | WS_VISIBLE ,5,5,285,240,hwnd,(HMENU)LIST1,hInst,0);

		loadlist();

		hwnd_edit = CreateWindowEx(WS_EX_STATICEDGE,"Button","Edit",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,240,240,50,25,hwnd,(HMENU)BUTTON1,hInst,0);
		HWND hwnd_st;
		hwnd_st = CreateWindow("Static","Select Aspect of Interface",WS_CHILD | WS_VISIBLE ,6,245,200,25,hwnd,0,hInst,0);
		break;

	case WM_COMMAND:

		switch(HIWORD(wParam))
		{
		case BN_CLICKED:

			switch(LOWORD(wParam))
			{
			case BUTTON1:

				imageselect();
			
				break;
			}

			break;

			case LBN_DBLCLK:

				imageselect();

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
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		SendMessage(hwnd,WM_TIMER,0,0);
		break;
	case WM_CREATE:

		HBITMAP hbitmap; hbitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));

		HWND splash;
		splash = CreateWindow("STATIC", "INTRO_MASTERONLSD", SS_BITMAP|WS_CHILD|WS_VISIBLE,5,5,0,0,hwnd,0,hInst,0);
        SendMessage(splash, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbitmap);

		break;
	case WM_TIMER:

			ShowWindow(hwnd,SW_HIDE);
			ShowWindow(hwnd_main,SW_SHOW);

			KillTimer(hwnd,1);
			
			break;

	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}
LRESULT APIENTRY SelectProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
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

		hwnd_fname = CreateWindow("Static","FileName - 640x480 ",WS_CHILD | WS_VISIBLE,5,5,200,25,hwnd,0,hInst,0);
		hwnd_fedit = CreateWindowEx(WS_EX_STATICEDGE,"Button","Paint",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,50+20+40,30,50,25,hwnd,(HMENU)FEDIT,hInst,0);
		hwnd_fchange = CreateWindowEx(WS_EX_STATICEDGE,"Button","Switch",WS_CHILD |WS_VISIBLE | BS_PUSHBUTTON,100+20+40,30,50,25,hwnd,(HMENU)FCHANGE,hInst,0);
		hwnd_fcancel = CreateWindowEx(WS_EX_STATICEDGE,"Button","[x]",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,5,30,50,25,hwnd,(HMENU)FCANCEL,hInst,0);
		
		break;
	case WM_COMMAND:

		switch(HIWORD(wParam))
		{
		case BN_CLICKED:
			switch(LOWORD(wParam))
			{
			case FEDIT:

				char fname[100];
				filenamebyindex(curindex,fname);
				char ex[150];
				strcpy(ex,"mspaint.exe ");
				strcat(ex,fname);

				ShellExecute(0,"open",ex,0,0,SW_SHOW);
				break;
			case FCHANGE:

				char fnamex[100];
				if(openfile(fnamex))
				{

						
	    HBITMAP hbm;
		BITMAP  bm;
        
		hbm = (HBITMAP)LoadImage(NULL, fnamex, IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        GetObject(hbm, sizeof(bm), &bm); // size

		int mw;
		mw = bm.bmWidth;
		int mh;
		mh = bm.bmHeight;

			if(hbm == NULL) { 
			
				mw = 0;
				mh = 0;
			
			}
	

			DeleteObject(hbm);

				if((mw == cur_w) && (mh == cur_h))
				{


					CopyFile(fnamex,curfile,false);
					MessageBox(hwnd_select,"Succesful Change","Succes!",MB_OK | MB_ICONINFORMATION);

				}
				else
				{
					char moutput[100];
					strcpy(moutput,"Error: Incorrect Image Size!\nRequire size is: ");
					char mx[25];
					char my[25];
					itoa(cur_w,mx,10);
					itoa(cur_h,my,10);
					strcat(moutput,mx);
					strcat(moutput,"x");
					strcat(moutput,my);

					MessageBox(hwnd_select,moutput,"Error",MB_OK | MB_ICONERROR);
					break;
				}
			}

				break;
			case FCANCEL:

				SendMessage(hwnd_fname,WM_SETTEXT,1,(LPARAM)(LPCSTR)"");
				ShowWindow(hwnd_select,SW_HIDE);

				break;
			}
			break;
		}

		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}


/// non-api realated functions

void mlist::set(char* file,char* id)
{
	strcpy(filename,file);
	strcpy(fileid,id);
	SendMessage(hwnd_mlist,LB_ADDSTRING,255,(LPARAM)(LPCSTR)id);
	xlen++;
}

void imageselect()
{
	ShowWindow(hwnd_select,SW_SHOW);
	char fbuff[100];
	strcpy(fbuff,"");
	int list_index;
	list_index = SendMessage(hwnd_mlist,LB_GETCURSEL,0,0);
	char lbuff[100];
	filenamebyindex(list_index,lbuff);
	strcpy(fbuff,lbuff);
	strcat(fbuff," : ");

	
	    HBITMAP hbm;
		BITMAP  bm;
        
		hbm = (HBITMAP)LoadImage(NULL, lbuff, IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        GetObject(hbm, sizeof(bm), &bm); // size

		int w;
		w = bm.bmWidth;
		int h;
		h = bm.bmHeight;

			if(hbm == NULL) { 
			
				w = 0;
				h = 0;
			
			}
	

			DeleteObject(hbm);
			


	char wx[25];
	char hx[25];
	itoa(w,wx,10);
	itoa(h,hx,10);

	strcat(fbuff,wx);
	strcat(fbuff,"x");
	strcat(fbuff,hx);

	cur_w = w;
	cur_h = h;

	if((w == 0) && (h == 0))
	{
		MessageBox(hwnd_select,"There was an Error File Missing or Corrupt","Error",MB_OK |MB_ICONERROR);
		ShowWindow(hwnd_select,SW_HIDE);
		return;
	}

		
	

	SendMessage(hwnd_fname,WM_SETTEXT,255,(LPARAM)(LPCSTR)fbuff);

}

void loadlist()
{

	list[0].set("wallpaper.bmp","Wall Paper");
	list[1].set("welcome.bmp","Welcome Image");
	list[2].set("mxicon.bmp","MasterX Icon");
	list[3].set("mqicon.bmp","MasterX Question");
	list[4].set("msicon.bmp","MasterX Up arrow");
	list[5].set("moveleft.bmp","MasterX Move Left Up");
	list[6].set("moveleft_down.bmp","MasterX Move Left Down");
	list[7].set("moveright.bmp","MasterX Move Right Up");
	list[8].set("moveright_down.bmp","Master Move Right Down");
	list[9].set("masterbg_mode2.bmp","MasterX Standard Background");
	list[10].set("sticon.bmp","System Icon");
	list[11].set("wl_down.bmp","Sys Window Move Left Down");
	list[12].set("wl_up.bmp","Sys Window Move Left Up");
	list[13].set("wr_down.bmp","Sys Window Move Right Down");
	list[14].set("wr_up.bmp","Sys Window Move Right up");
	list[15].set("inicon.bmp","Internet  Icon");
	list[16].set("mxsys.bmp","MasterX System Image");
	list[17].set("servicon.bmp","MasterX Server Icon");
	list[18].set("shicon.bmp","MasterX Game Icon");
	list[19].set("masterbg.bmp","MasterX Mode Animation Frame #1");
	list[20].set("masterbg2.bmp","MasterX Mode Animation Frame #2");
	list[21].set("masterbg3.bmp","MasterX Mode Animation Frame #3");
	list[22].set("masterbg4.bmp","MasterX Mode Animation Frame #4");
	list[23].set("masterbg5.bmp","MasterX Mode Animation Frame #5");
	list[24].set("masterbg6.bmp","MasterX Mode Animation Frame #6");

	
	flen = xlen;
}

void filenamebyindex(int index, char* filename)
{
	if(index <= flen)
	{

	strcpy(filename,list[index].filename);
	curindex = index;
	strcpy(curfile,list[index].filename);

	} else { strcpy(filename,"error"); }
}

void idnamebyindex(int index, char* filename)
{
	if(index <= flen)
	{

	strcpy(list[index].fileid,filename);

	} else { strcpy(filename,"error"); }
}

bool openfile(char* cFile)
{
	char szFile[200];


OPENFILENAME ofn;      

strcpy(szFile, "*.bmp");

ZeroMemory(&ofn, sizeof(OPENFILENAME));
ofn.lStructSize = sizeof(OPENFILENAME);
ofn.hwndOwner = hwnd_select;
ofn.lpstrFile = szFile;
ofn.nMaxFile = sizeof(szFile);
ofn.lpstrFilter = "Bmp\0*.Bmp\0";
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