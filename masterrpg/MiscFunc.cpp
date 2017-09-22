// misc functions
// written by jared bruni
// www.lostsidedead.com

#include "thehead.h"
// make a font
HFONT MakeFont(char* ftype, int size)
{
	return CreateFont(size,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,ftype);
}
// set a font
void SetFont(HWND hwnd,HFONT f)
{
	SendMessage(hwnd,WM_SETFONT,(WPARAM)(HFONT)f,0);
}

// set one of the images, to an hwnd
void SetImage(HWND hwnd,int image)
{
	if(image <= GRAPHIC_MAX)
	{

	SendMessage(hwnd,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)(HBITMAP)graphics[image]);

	}
}
// set which image to draw with
void SetDrawImage(int type)
{
	cur_image = type;
}

// get block by pos
int  getblockbypos(int x, int y)
{
	
	int start_x = 5;
	int start_y = 5;
	
	int sx = start_x;
	int sy = start_y;
	
	int row_count = 0;
	
	for(int i = 0; i < LevelSize; i++)
	{
		
		if(x > sx && x < sx+16 && y >  sy && y < sy+16)
		{
			return i;
		}
		
		row_count ++;
		
		sy = sy + 16;
		
		if(row_count > 20)
		{
			row_count = 0;
			sx = sx + 16;
			sy = start_y;
		}
	}

	return -1; // not a block
}
// update the map
void updatemap()
{
	for(int i = 0; i < LevelSize; i++)
	{
		SetImage(sthwnd[i],level.level_block[i]);
	}
}
// fill the map with a specific color
void fillmap(int cur)
{
	for(int i = 0; i < LevelSize; i++)
	{
		level.level_block[i] = cur;
	}

	updatemap();
}
// update the title of the window
void UpdateTitle()
{
	char titlebuff[100];
	strcpy(titlebuff,"MasterRPG Level Editor - ");
	strcat(titlebuff,filename);
	SendMessage(mainwindow,WM_SETTEXT,255,(LPARAM)(LPCSTR)titlebuff);
}
// pause this program
void pause(long seconds)
{
 clock_t delay = seconds * CLOCKS_PER_SEC;
 clock_t start = clock();
 while (clock() - start < delay)
    ;
}

// common dialogs, for save & load

// the dialogs
bool openfile(char* cFile)
{
	char szFile[200];
	
	
	OPENFILENAME ofn;       // common dialog box structure
	
	strcpy(szFile, "*.mrpg");
	
	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = mainwindow;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "MasterRPG Map Format\0*.mrpg\0ALL\0*.*\0";
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
	
	strcpy(szFile, "*.mrpg");
	
	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = mainwindow;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "MasterRPG map format\0*.mrpg\0ALL\0*.*\0";
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
