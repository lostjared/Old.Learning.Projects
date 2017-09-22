// the head .h
// written for planetsourcecode
// by jared bruni
// www.lostsidedead.com


/*
This code is dedicated to the girl of my dreams, she is my
  inspiration, my hope, and my desire.
  Jenny I love you
*/


#include "masterx.h"

// using preprocesscor directives, to create debug executables

#define iDEBUG
// comment out, iDEBUG for a release executable


// masterX SDK 1.1 callback functions
long _stdcall MasterProc(HWND,UINT,WPARAM,LPARAM);
void update(MASTERSCREEN screen);


// enumerated constants, for screens

enum { INTRO = 1, GAME };


// structure prototypes


// screen object (base class)
struct ScreenObject
{
	MasterXHWND* mxhwnd;
	MASTERSCREEN sub_screen;
	
	inline void init(MasterXHWND* mxhwndx)
	{
		mxhwnd = mxhwndx;
	}

	inline void setscreen(MASTERSCREEN screen)
	{
		sub_screen = screen;
	}

	inline MASTERSCREEN getscreen()
	{
		return sub_screen;
	}
};

// intro game object
struct Intro : ScreenObject
{
	void onload();
	void update();
	void keycheck();

};

// level data structure
struct Level
{
	int img[9000]; // 5 screens of data 

	// constructor lets fill the array with garbage
	// so we can see what it looks like when we scroll
	// normaly, we would have a level editor
	// and load this level file up
	inline Level()
	{
		for(int i = 0; i < 9000; i++)
		{
			img[i] = rand()%3;
		}
	}
};


// tilemap object
struct TileMap : ScreenObject
{
	MasterGraphic tiles[5];
	Level         level;
	int           level_index;

	int dely; // for keycheck dely

	// constructor
	inline TileMap()
	{
		level_index = 0;
	}

	void onload();
	void update();
	void keycheck();
	void scrollleft();
	void scrollright();
	void drawmap();
};


// main game object
struct Game : ScreenObject
{
	TileMap map;
	void onload();
	void update();
};


static HFONT m_font = CreateFont(20,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,"Arial");
static HFONT x_font = CreateFont(18,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,"Arial");
static HFONT d_font = CreateFont(13,
        0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        "Arial");