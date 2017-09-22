// header file
// written by Jared Bruni

#include "masterx.h"
#include <iostream.h>

enum { INTRO = 1, GAME , OVER };


long _stdcall MasterProc(HWND,UINT,WPARAM,LPARAM);
void update(MASTERSCREEN);


struct ScreenObject
{
	MasterXHWND* mxhwnd;
	MASTERSCREEN sub_screen;

	inline void SetScreen(MASTERSCREEN x)
	{
		sub_screen = x;
	}

	inline MASTERSCREEN GetScreen()
	{
		return sub_screen;
	}

	inline void Init(MasterXHWND* mxhwndx)
	{
		mxhwnd = mxhwndx;
	}
};

struct Intro : ScreenObject
{
	MasterGraphic logo;
	int menu_pos;
	
	inline Intro()
	{
		menu_pos = 0;
	}
	
	void load();
	void update();
	void drawmenu();
	void keycheck();
};

struct Hero : ScreenObject
{
	// constructor
	inline Hero()
	{
		x = 100;
		y = 400;
		speed = 5;
		life = 100;
		fdely = 0;
	}

	int x;
	int y;
	int speed;
	int life;
	int fdely;


	void load();
	void update();
	void draw();
	void keycheck();
	void fire();

};

struct Game : ScreenObject
{
	bool startx;
	int start_pos;
	int start_count;
	Hero hero;
	int score;

	// constructor
	inline Game()
	{
		startx = true;
		start_pos = 0;
		start_count = 0;
		score = 0;
	}

	void load();
	void update();
	void keycheck();
	void draw();
	void drawscore();
	void drawhero();
	void drawmap();
	void drawstart();

};

// filre map
struct Fire
{
	int x;
	int y;
	int type;
	bool on;

	inline Fire()
	{
		on = false;
	}

};
struct FMap
{
	Fire fire[200]; // no more then 200 fire balls

	inline int getoffball()
	{
		for(int i = 0; i < 200; i++)
		{
			if(fire[i].on == false)
			{
				return i;
			}
		}

		return -1; // failure
	}
};

static FMap fmap; // fire map

static HFONT bigfont = CreateFont(80,
        0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        "Arial");
static HFONT sfont = CreateFont(17,
        0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        "Arial");