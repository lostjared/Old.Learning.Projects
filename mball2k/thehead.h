// the head.h
// written by jared bruni
// www.lostsidedead.com


#define WIN2K


#include "masterx.h"
#include "resource.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// for the debug mode
#define iDEBUG
// sprites
#define INTRO 0
#define START 1
#define GAME  2

//extern the important masterX objects
extern MasterXHWND mxhwnd;
extern MasterJoyStick stick;

struct BallPlayer
{
	bool joystick_on;
	bool nojoystick;
	int difficulty;
	int lives;
	int score;
	int hits;
	int level;
};

extern BallPlayer player;

//enumerated constants for screens
enum { ID_INTRO = 1,ID_START,ID_OPTIONS,ID_GAME,ID_GAMEOVER };

// callback proccess
long XSTD MasterProc(HWND,UINT,WPARAM,LPARAM);
void update(MASTERSCREEN);
void intro_update();
void start_update();
void options_update();
void game_update();
void gameover_update();

// draw sprites
void drawsprite(int x, int y, int sprite);
// load level
void loadlevel(int level);
// play game sound
void playgamesound(int sound);


// keypresses
void start_keypress(WPARAM wParam);
void options_keypress(WPARAM wParam);
void gameover_keypress(WPARAM wParam);

// the ballplayer information structure

