// Simple quick Code Editor
// written by Jared Bruni
// email me : Jared@LostSideDead.com


#include <windows.h>
#include <commdlg.h>
#include "resource.h"
#include "masterstring.h"

LRESULT APIENTRY WndProc(HWND,UINT,WPARAM,LPARAM);
void MenuProc(WPARAM wParam);
void UpdateTitle();
void Save();
void SaveAs();
bool openfile(char*);
bool savefile(char*);
void FixSave(char*,char*);
void FixLoad(char*,char*);

HFONT thef = CreateFont(15,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,"FixedSys");


HWND main;
HWND edit;
HINSTANCE g_hInst;

char filename[100];
bool ask_q = false;



int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	strcpy(filename,"Untitled.asm");
	g_hInst = hInst;
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.hInstance = hInst;
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = "CODEVIEW";
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	main = CreateWindow("CODEVIEW","MASASMX - [Code View]",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,640,480,0,0,hInst,0);

	ShowWindow(main,SW_SHOW);
	UpdateWindow(main);
	UpdateTitle();

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}


LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		{
			edit = CreateWindowEx(WS_EX_STATICEDGE | WS_EX_CLIENTEDGE,"Edit","",WS_CHILD |WS_BORDER | WS_VISIBLE | ES_MULTILINE | WS_HSCROLL | WS_VSCROLL,0,0,640,480,hwnd,(HMENU)1,g_hInst,0);
			SendMessage(edit,WM_SETFONT,(WPARAM)(HFONT)thef,0);
		}
		break;
	case WM_SIZE:
		{
			int x;
			int y;
			x = LOWORD(lParam);
			y = HIWORD(lParam);

			SetWindowPos(edit,0,0,0,x,y,0);
		}
		break;
	case WM_COMMAND:
		{
			MenuProc(wParam);

			switch(HIWORD(wParam))
			{
			case EN_CHANGE:
				ask_q = true;
				break;
			}

		}
			break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}


void MenuProc(WPARAM wParam)
{
	switch(wParam)
	{
	case ID_FILEEXIT:
		if(ask_q)
		{

		if(MessageBox(0,"Do you wish to Save before Exit?","Save?",MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			Save();
		}
		}
		SendMessage(main,WM_CLOSE,0,0);
		break;
	case ID_FILENEW:
		if(ask_q)
		{

		if(MessageBox(0,"Do you wish to Save current?","Save?",MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			Save();
		}
		}

		strcpy(filename,"Untitled.asm");
		UpdateTitle();
		SendMessage(edit,WM_SETTEXT,255,(LPARAM)(LPCSTR)"");
		ask_q = false;
		
		break;
	case ID_FILESAVE:
		Save();
		break;
	case ID_FILESAVEAS:
		SaveAs();
		break;
	case ID_FILEOPEN:
		{
			if(ask_q)
			{

			if(MessageBox(0,"Do you wish to save current?","Save?",MB_YESNO| MB_ICONQUESTION) == IDYES)
			{
				Save();
			}
			}

			char ofile[100];

			if(openfile(ofile))
			{
				strcpy(filename,ofile);
				UpdateTitle();
				char* buff;
				char* buff2;
				buff = new char[getfilestringlength(ofile) + 20];
				strloadfile(ofile,buff);
				buff2 = new char[strlen(buff)*2+1];
				FixLoad(buff,buff2);
				SendMessage(edit,WM_SETTEXT,strlen(buff),(LPARAM)(LPCSTR)buff2);
				delete [] buff;
				delete [] buff2;
			}


		}
		break;

	case ID_HELPABOUT:
		MessageBox(0,"Simple Code Editor\nWritten by Jared Bruni\nThis was done really quick so you can use something to type the code\nNothing fancy =)\n","About",MB_OK|MB_ICONINFORMATION);
		break;
	case ID_ASMBUILD:
		{
			// save
			Save();

			char cmdpar[100];
			strcpy(cmdpar,"masasmx ");
			strcat(cmdpar,filename);

			ShellExecute(NULL,"open","masasmx",filename,0,SW_SHOW);
	 


		}
		break;
	}
}

void UpdateTitle()
{
	char titlex[100];
	strcpy(titlex,"MASASMX - [Code View] - ");
	strcat(titlex,filename);
	SendMessage(main,WM_SETTEXT,255,(LPARAM)(LPCSTR)titlex);
}

void Save()
{
	if(mstrcmp(filename,"Untitled.asm") == true)
	{
		SaveAs();
		return;
	}

	char* buff;
	buff = new char[SendMessage(edit,WM_GETTEXTLENGTH,0,0) + 1];
	SendMessage(edit,WM_GETTEXT,SendMessage(edit,WM_GETTEXTLENGTH,0,0)  +1,(LPARAM)(LPCSTR)buff);
	// save to file

	if(findstr(filename,".asm") == -1)
	{
		strcat(filename,".asm");
	}

	char* buff2;
	buff2 = new char[strlen(buff) + 10];
	FixSave(buff,buff2);
	strsavefile(filename,buff2);
	ask_q = false;
	delete [] buff;
	delete [] buff2;

	UpdateTitle();
}

void SaveAs()
{
	char sfile[100];
	if(savefile(sfile))
	{
		strcpy(filename,sfile);
		Save();
		return;
	}

	UpdateTitle();
}

bool openfile(char* cFile)
{
	char szFile[200];


OPENFILENAME ofn;       // common dialog box structure

strcpy(szFile, "*.asm");

// Initialize OPENFILENAME
ZeroMemory(&ofn, sizeof(OPENFILENAME));
ofn.lStructSize = sizeof(OPENFILENAME);
ofn.hwndOwner = main;
ofn.lpstrFile = szFile;
ofn.nMaxFile = sizeof(szFile);
ofn.lpstrFilter = "asm\0*.asm\0ALL\0*.*\0";
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

strcpy(szFile, "*.asm");

// Initialize OPENFILENAME
ZeroMemory(&ofn, sizeof(OPENFILENAME));
ofn.lStructSize = sizeof(OPENFILENAME);
ofn.hwndOwner = main;
ofn.lpstrFile = szFile;
ofn.nMaxFile = sizeof(szFile);
ofn.lpstrFilter = "asm\0*.asm\0ALL\0*.*\0";
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


void FixSave(char* input,char* output)
{
	int len;
	len = strlen(input);
	int pos = 0;

	for(int i = 0; i < len;i++)
	{
		if(input[i] != '\r')
		{
			output[pos] = input[i];
			pos++;
		}
	}

	output[pos] = 0;
}

void FixLoad(char* input,char* output)
{
	int len;
	len = strlen(input);

	int add_pos = 0;

	for(int i = 0; i < len; i++)
	{
		if(input[i] == '\n')
		{
			output[add_pos] = '\r';
			output[add_pos+1] = '\n';
			add_pos = add_pos + 2;
		}
		else
		{
			if(input[i] != '\r')
			{

			output[add_pos] = input[i];
			add_pos++;

			}
		}
	}

	output[add_pos] = 0;
}
