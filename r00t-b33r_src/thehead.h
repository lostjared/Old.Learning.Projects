// the head.h

#include "resource.h"
#include "masterx.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

// for the debug mode
#define iDEBUG
// sprites
#define INTRO 0
#define START 1
#define GAME  2

#define LevelSize 100813



//extern the important masterX objects
extern MasterXHWND mxhwnd;


//enumerated constants for screens
enum { ID_KLOSED,ID_INTRO,ID_OPTIONS,ID_GAME,ID_GAMEOVER };

// callback proccess
long XSTD MasterProc(HWND,UINT,WPARAM,LPARAM);
void update(MASTERSCREEN);




struct klosed
{
 MasterGraphic compagnie;
 MasterGraphic explose;
 MasterGraphic flame;
 
 MasterSound boom;
 MasterSound bip;	
	//MasterSound music_intro;
 void load();
 void update();
 void draw();
 void letters();
 void messages();
 void explosion();
 void fire();
 void blind();

struct camp_fire     //fire structure
{
int pos_x;
int pos_y;
int state;
};

camp_fire fires[200];

};




struct intro
{
MasterGraphic root;
void load();
void intro_update();
};







struct game
{

MasterGraphic floor;
MasterGraphic counter;
MasterGraphic bartender;
MasterGraphic wall;
MasterGraphic mug;
MasterGraphic guys;

MasterSound move_snd;
MasterSound pour;
MasterSound glass;
MasterSound gotit;
MasterSound rip;
MasterSound yip;
MasterSound bell;
MasterSound gameover;
MasterSound burp;


bool serving;
void served();

void keycheck();

void drawsprite(int x, int y, int sprite);

void load();
void update();
void draw();

void create_drunk();
void drunk();
void drunk_draw();
void drunk_walk();
void drunk_clipping();
void not_drunk();
int drunk_track(int gps);
void switch_drunk();
int sx,sy,ex,ey;

void create_beer(bool empty,int position_y,int position_x);
void beer_travel();
void beer_draw();
void beer_explosion(int track,bool entrence);

void collision();
void render_room();

void level();
void panel();
void delete_all();

int extra_luck;
int dead;
int creation[3];
long int score;
int gone;
int msg;
int yep;
int vep;
int numb;
bool pouring;
int already;
int find;
int glas;
int lk;
int luck;
int need_a_life;

struct drank		// customers structure
{
long int pos_x;
int pos_y;
bool drinkin;
int speed;
int recul;
int walking;
float walk;
int character;
};

drank drunks[50];


struct beer			// beer structure
{
int pos_x;
int pos_y;
bool full;
bool direction;
int speed;

};

beer beers[300];

};




MasterJoyStick* getstick();





// FONTS 
static HFONT maxi_font = CreateFont(174,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,"Arial");
static HFONT menu_font = CreateFont(20,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,"Arial");
static HFONT panel_font = CreateFont(18,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,"Arial");
