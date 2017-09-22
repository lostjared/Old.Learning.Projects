// mxhead.h
// jared bruni
#include"masterx.h"
#include "resource.h"


// using what I call screen threads

#define iDEBUG

// enumerated constants
enum { INTRO = 1, GAME , OVER };
enum { INTRO_START = 4, INTRO_OP };
enum { GAME_START = 7, GAME_MAIN,GAME_DIE };
enum { OVER_SCREEN = 9, OVER_SCORE };

// 'master game chunk' - object prototype
class mgcobject
{
public:
	MasterXHWND* mxhwnd;
    MASTERSCREEN sub_screen;
    void init(MasterXHWND* mxhwndx);
    void setsub(MASTERSCREEN scr);
    MASTERSCREEN getsub();
};

// 'master game chunk' - intro prototype
class mgcintro : public mgcobject
{
public:
	void loadgraphics();
	void update();
	void draw();
	void drawstart();
	void drawop();
	void keycheck();

};
// 'master game chunk' game prototype
class mgcgame : public mgcobject
{
	MasterGraphic mgc_graphic;
public:
	void loadgraphics(); 
	void update();
	void draw();
	void drawgamestart();
	void drawgamegame();
	void drawgamedie();
	void keycheck();
};

// 'master game chunk ' game over prototype
class mgcover : public mgcobject
{
	MasterGraphic mgc_graphic2;
public:
	void loadgraphics();
	void update();
	void draw();
	void drawscreen();
	void drawscore();
	void keycheck();
};