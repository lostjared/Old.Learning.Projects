// program main header file
// jared bruni
// http://www.lostsidedead.com/gameprog/
#include "masterx.h"

#define iDEBUG
#define TILE_SIZE 500+4
#define TILE_ROW  25
// enumerated constants
enum { TILE_RED = 0, TILE_BLUE = 1, TILE_GREEN = 2 };


// function prototypes
long _stdcall MasterProc(HWND,UINT,WPARAM,LPARAM);
void update(MASTERSCREEN screen);

// global variables

static MasterXHWND mxhwnd;

struct gtiles
{
	int tile_type;
	bool solid;
};


// tile engine prototype
class tileEngine
{
	MasterXHWND* mxhwnd;
	MASTERSCREEN sub_screen;
	MasterGraphic tile_graphic[4];
public:
	gtiles tile[TILE_SIZE*TILE_ROW];
	int   tile_index;
	int   scroll_lag;

	void init(MasterXHWND* mxhwnd);
	void loadgraphics();
	void setsub(MASTERSCREEN);
	MASTERSCREEN getsub();
	void update();
	void drawtile();
	void keycheck();
	void loadlevel();

};