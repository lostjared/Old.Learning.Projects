/*

  MasterKong LE (Level Editor)
  written by Jared Bruni
  www.lostsidedead.com

  open source, open mind

*/

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <fstream.h>
#include "resource.h"

const int IMAGE_MAX = 10;

extern HINSTANCE hInst;
extern HWND      mainwindow;
extern HWND      grid[1240];
extern HBITMAP   images[IMAGE_MAX];
extern int       img_tool;
extern int       img_index;
extern HWND      tcombo;
extern char      filename[100];


inline void Init();
inline void LoadGraphics();

int ArrayIndexByPoint(int x, int y);
void SetGrid(int pos, int image);
void reloadgrid();
void setimage(int pos, int image, bool solid);
void setbrick(int x, int y);
bool isolid(int tile);
void MenuProc(WPARAM wParam);
void updatetitle();
void savelevel(char* filename);
void loadlevel(char* filename);
bool savefile(char*);
bool openfile(char*);



// size of the tile map
const int LEVEL_SIZE = 700-4+24;

// level block structure
struct LevelBlock
{
	int block;
	bool solid;
};
// levelmap structure
struct LevelMap
{
	int gsp;
	int hsp;
	LevelBlock blocks[LEVEL_SIZE];
	int items[LEVEL_SIZE];

	// constructor for level map
	inline LevelMap()
	{
		for(int i = 0; i < LEVEL_SIZE; i++)
		{
			blocks[i].block = 0;
			blocks[i].solid = false;
			items[i] = 0;
		}
	}

	// calculate the position of an object in the grid, by its position
	inline void GetPointFromPos(int pos,int& x, int& y)
	{
		x = 0;
		y = 0;

		int startby = 75;
		
		int bx,by;
		bx = 75; by = startby;
		int gcount = 0;
		
		
		for(int i = 0; i < 700-4+24; i++)
		{
			if(i == pos)
			{
				x = bx;
				y = by;
				return;
			}
			
			by = by + 16;
			gcount++;
			if(gcount > 23)
			{
				gcount = 0;
				by = startby;
				bx = bx + 16;
			}
			
		}
	}
};

extern LevelMap level;


LRESULT APIENTRY MainProc(HWND,UINT,WPARAM,LPARAM);



/************************************************************************** www.lostsidedead.com */