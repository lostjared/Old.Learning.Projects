// application main header file
// jared bruni
// http://www.lostsidedead.com/gameprog/
#include "masterx.h"

#define iDEBUG

// enumerated constants
enum { INTRO = 1, GAME , OVER };
enum { INTRO_ANI = 1, INTRO_START };

// function prototypes
long _stdcall MasterProc(HWND,UINT,WPARAM,LPARAM);
void update(MASTERSCREEN);

// global variables

static MasterXHWND mxhwnd;
static HWND main;
// game object prototype
class gameobj
{
public:
	MasterXHWND* mxhwnd;
	MASTERSCREEN sub_screen;
	void init(MasterXHWND* mxhwnd);
	void setsub(MASTERSCREEN screen);
	MASTERSCREEN getsub();
};
// intro object prototype
class intro : public gameobj
{
	bool menu_state;
	int  start_ani;
	int  add_w;
	int  add_h;
public:
	void update();
	void keycheck();
	void drawani();
	void drawstart();
};

// the game object prototype
class game : public gameobj
{
	int x;
	int y;
public:
	void update();
	void keycheck();
	void drawobject();
	void setpos(int ix,int iy);

};

// the over object prototype
class over : public gameobj
{
public:
	void update();
	void keycheck();
};
