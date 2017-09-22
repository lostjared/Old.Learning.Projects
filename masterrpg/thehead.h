// the header file
// for masterrpg LE
// written by jared bruni

#include <windows.h>
#include <fstream.h>
#include <commdlg.h>
#include <ctime>
#include "resource.h"
#define LevelSize 609
#define GRAPHIC_MAX 15

extern HINSTANCE hInst;
extern HWND mainwindow;
extern int  cur_image;
extern int  cur_draw;
// filename
extern char filename[100]; // currently loaded file


extern HWND sthwnd[LevelSize];
extern HBITMAP graphics[GRAPHIC_MAX];
// main callback function
LRESULT APIENTRY MainProc(HWND,UINT,WPARAM,LPARAM);

// menu proccess
void MenuProc(WPARAM wParam);


// main functions
void LoadGraphics();
void DeleteGraphics();


// misc functions
HFONT MakeFont(char* ftype, int size);
void SetFont(HWND hwnd,HFONT font);
void SetFont(HWND hwnd);
void SetImage(HWND hwnd,int image);
void SetDrawImage(int type);
int  getblockbypos(int x, int y);
void fillmap(int cur_image);
void updatemap();
void UpdateTitle();
bool savefile(char* cFile);
bool openfile(char* cFile);
void pause(long seconds);
// data structures

struct LevelStructure
{
	int level_block[LevelSize];

	inline LevelStructure()
	{
		for(int i = 0; i < LevelSize; i++)
		{
			level_block[i]  = 0;
		}
	}
};

extern LevelStructure level;
