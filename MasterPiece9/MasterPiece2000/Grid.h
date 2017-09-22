// this is old school
// i wrote this when I was like 16 

#include "masterx.h"
#include <time.h>
#include <ctime>

#define STARTX 185
#define STARTY 95
 

#define BLOCK_BLACK  0
#define BLOCK_YELLOW 1
#define BLOCK_ORANGE 2
#define BLOCK_LTBLUE 3
#define BLOCK_DBLUE 4
#define BLOCK_PURPLE 5
#define BLOCK_PINK 6

// ------ FULL GAME

#define BLOCK_GRAY 7
#define BLOCK_RED 8
#define BLOCK_GREEN 9
#define BLOCK_CLEAR 10

//  --
#define GRIDBLOCKMAX 11
// ---
#define D_UP 0
#define D_DOWN 1
// MOVEMENTS

#define MOV_LEFT 100
#define MOV_RIGHT 101
#define MOV_DOWN 102
#define MOV_A 103
#define MOV_B 104

void blocksound();


struct Color { int c1; int c2; int c3; };

class Block {


	

public:

	Color color;
	int x;
	int y1;
	int y2;
	int y3;

	void colorswitch(int dir);
	void setcolors();
};

class AGame
{

	int plines;
public:
	int score;
	int lines;
	int speed;
    
	void newgame();
	void addline();
};


class GameGrid
{
public:
// ---- VARIABLES
   
   bool block_going;
   Block block;
   int update_frame; 
   bool game_over;
   //--- FUNCTIONS
   void init_graph();
   void uninit_graph();

   void paint();
   void paint_block();
   void clearGrid();
   void clearBlockGrid();

   void blockproc();
   void move_left();
   void move_right();
   void move_down();

   void setblock();
   void gameover();

   void blockcheck();
   void blockmovedown();
   void movedowncheck();


// --- VARIABLES
 	int Grid[17][8];
	int BlockGrid[17][8];
	Block block2;
	AGame Game;
//------  FUNCTIONS
	GameGrid();
	~GameGrid();

    void init_Grid();
	void update();
   
	bool ifgameover();
   
	void HandleInput(int MOV);

   
};
 // This Cannot Be Implemented W/O the Classes it uses; so its done outside