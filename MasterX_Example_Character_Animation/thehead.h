// the header file
// writtey by jared bruni
// for planetsourcecode

#include "MasterX.h"

enum { INTRO = 1, GAME };

#define DLEFT true
#define DRIGHT false


long _stdcall MasterProc(HWND,UINT,WPARAM,LPARAM);
void update(MASTERSCREEN);


// screen object structure
struct screenObject
{
	MASTERSCREEN sub_screen;
	MasterXHWND* mxhwnd;

	inline void init(MasterXHWND* mxhwndx)
	{
		mxhwnd = mxhwndx;
	}

	inline void setscreen(MASTERSCREEN scr)
	{
		sub_screen = scr;
	}

	inline MASTERSCREEN getscr()
	{
		return sub_screen;
	}
};

// intro Object
struct Intro : screenObject
{
	void load();
	void update();
	void keycheck();
	void draw();
};


// the Hero Object
struct  Hero : screenObject
{
	MasterGraphic hero_graphic;
	int hero_x;
	int hero_y;
	int hero_cur;
	int dely;


	int cur_right;
	int cur_left;
	int cur_up;
	int cur_down;
	int cur_punch;

	bool ipunch;
	bool idir;

	void update();
	void load();
	void draw();
	void keycheck();
	void moveleft();
	void moveright();
	void movedown();
	void moveup();
	void punch();
	void drawsprite(int x, int y, int sprite);
	int  getnextleft();
	int  getnextright();
	int  getnextup();
	int  getnextdown();
	int  getpunch();

};



// Game Object
struct Game : screenObject
{
	Hero hero;
	void load();
	void update();
	
};

static HFONT m_font = CreateFont(20,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,"Arial");
static HFONT x_font = CreateFont(18,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,"Arial");
