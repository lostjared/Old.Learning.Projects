// the main header file
// for master rpg
// written by jared bruni
// www.lostsidedead.com

/* copyright notice

  this software or any software I write, is stricly for educational
  uses only. you are not allowed to take my code, and use it in
  anything which is sold.
  open source, open mind
*/




// uncomment this, if your not on windows 2000
#define WIN2K



#include "masterx.h"
#include "resource.h"
#include <fstream.h>

// for debug mode
#define iDEBUG
#define VER "ALPHA 1.0"

extern MasterXHWND mxhwnd; 
extern HFONT mainfont;


enum { ID_INTRO = 0, ID_GAME };

long _stdcall MasterProc(HWND,UINT,WPARAM,LPARAM);
void update(MASTERSCREEN);
void keypress(WPARAM);



// games level screen - structure
const int LevelSize = 609;
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

struct BlockInfo
{
	bool solid;
	bool kill;
};
extern LevelStructure level;// extern the level structure, that exisits inside the game

void GetTileInfo(BlockInfo* info, int tile); // get information about a exisitng tile
void loadmap(char* filename);
bool TimeChange();
char fixkeys(int key,int caps,bool cmd);
void mprint(char* buff,COLORREF color);


// games objects / variables

enum HDIR { DIR_UP = 1, DIR_DOWN, DIR_LEFT, DIR_RIGHT };

// hero object
struct Hero
{
	HDIR dir;
	int hero_pos;
	int cur_sprite;
	int hero_dely;

	// player stats 
	char playername[0xF]; // no more then E characters
	int  player_score;
	int  player_life;
	int  player_lives;
	int  player_gold;
	int  player_magic;
	int  player_rank;


	MasterGraphic hero_graphic;

	// inline constructor
	inline Hero()
	{
		strcpy(playername,"Master");
		player_score = 0;
		player_life = 1000;
		player_lives = 5;
		player_gold = 0;
		player_magic = 0;
		player_rank = 0;
	}
	
	void load();
	void update();
	void drawhero();
	void drawsprite(int draw_x, int draw_y, int sprite);
	void keycheck();
	void setheropos(int pos);
	void keyup(WPARAM wParam); // keyup (release of key)
	void setstand();
};

// the display data structure
struct DispData
{
	char curline[300];
	COLORREF cur_color;
	bool on;

	inline void setnull()
	{
		on = false;
		for(int i = 0; i < 300; i++)
		{
			curline[i] = 0;
		}
		cur_color = NULL;
	}
};


// master console data structure
struct MasterConsole
{
	DispData dispdata[100]; // 100 lines of data before flush
	char input_data[300];
	int input_index;
	int print_pos;
	int gcount;
	bool icaps;

	inline MasterConsole()
	{
		strcpy(input_data,"");
		input_index = 0;
		print_pos = 0;
	}

	void update();
	void drawinput();
	void drawdata();
	void keypress(WPARAM wParam);
	void consolecmd(char* cmd);
	void printtext(char* buff,COLORREF color);
};

// the main game object
struct Game
{
	Hero hero;// are hero object
	MasterConsole console;
	MasterGraphic tiles[20]; // tiles
	MasterGraphic wallpaper; // wallpaper
	void load();// load are graphics/sounds
	void update();// update the frame
	void keypress(WPARAM);// send a keypress message
	void drawmap();// draw the map
	void drawtile(int x, int y, int tile);// draw a tile
	void drawstats();
};

struct Intro
{
	MasterGraphic introg;
	int fcount;
	void update();
	void load();
};