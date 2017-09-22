/*

  MasterPiece written utilizing MasterX SDK
  written by Jared Bruni
  
	
	  www.lostsidedead.com
	  
		
		  
			Open Source, Open Mind
			
			  "I am only as I think and believe"
			  
*/


#define WIN2K

#ifndef __MPX__H_
#define __MPX__H_

// FREESTYLE
#include "masterx.h"
#include "resource.h"


extern MasterXHWND mxhwnd; // a global instance of MasterXHWND class


extern unsigned long user_score;


struct SoundHandler : MasterGameObject {

	virtual void load()
	{
		mxhwnd.LoadSound(&sounds[0],"open.wav");
		mxhwnd.LoadSound(&sounds[1],"line.wav");
	}

	virtual void update() {}

	MasterSound sounds[3];


};

extern SoundHandler shandle;


// the scores user
// this contains the high scores
// sorting the highscores

struct MPScore {

	char user_name[100];
	unsigned long score;

	inline MPScore()
	{
		strcpy(user_name,"Unknown Player");
		score = 0;
	}

};
// scores data structure
struct Scores {

	MPScore scorez[11];
 
 
	void AddNew(char* user_name, unsigned long user_score)
	{
		strcpy(scorez[10].user_name,user_name);
		scorez[10].score = user_score;
		
		// now we have elminated the loser
		// now we bubble sort

	int max = 11;
	int pas,compare;

	for(pas = 0; pas < max - 1; pas++)
	{ 

		for(compare = 0; compare < max - 1; compare++)
		{
			if(scorez[compare].score < scorez[compare+1].score)
			{
				MPScore  temp;
				temp = scorez[compare];
				scorez[compare] = scorez[compare+1];
				scorez[compare+1] = temp;
				
			}
		}
	}

	}


	void Reset()
	{
		for(int i = 0; i <= 11; i++)
		{
			strcpy(scorez[i].user_name,"Unknown User");
			scorez[i].score = 0;
		}
	}
};



extern Scores fscores;


struct gOp {

	int linec;

	inline gOp()
	{
		linec = 5;
	}

};

extern gOp Options;


enum { ID_INTRO, ID_START, ID_GAME, ID_SCORES };
enum { STARTX = 185 , STARTY = 95 };
enum { BLOCK_BLACK = 0, BLOCK_YELLOW, BLOCK_ORANGE, BLOCK_LTBLUE, BLOCK_DBLUE, BLOCK_PURPLE, BLOCK_PINK,BLOCK_GRAY,BLOCK_RED,BLOCK_GREEN,BLOCK_CLEAR };



void newgame();
void gameover();
void getcords(int r, int c, int& x, int& y);
void savescore();
void loadscore();
char fixkeys(int key,int caps,bool cmd);



long XSTD MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void update(MASTERSCREEN scr);

const int mfsize = 5;
extern HFONT mfonts[mfsize];


// intro object
// this is the object, that contains the games introduction
// as well as its sounds
class Intro : public MasterGameObject {
	
public:
	
	MASTERSCREEN screen_pos;
	int icur;
	
	
	virtual void load()
	{
		mxhwnd.LoadGraphic(&introg,"intro.bmp");
		
		mxhwnd.LoadGraphic(&ibg[0],"bg1.bmp");
		mxhwnd.LoadGraphic(&ibg[1],"bg2.bmp");
		mxhwnd.LoadGraphic(&ibg[2],"bg3.bmp");
		mxhwnd.LoadGraphic(&ibg[3],"bg4.bmp");
		mxhwnd.LoadGraphic(&ibg[4],"bg5.bmp");
		mxhwnd.LoadGraphic(&ibg[5],"bg6.bmp");
		screen_pos = 0;
		icur = 0;
		
	}
	
	virtual void update()
	{
		ondraw();
		if(mxhwnd.SyncChange())
		{
			onlogic();
		}
	}
	
	
private:
	MasterGraphic introg;
	MasterGraphic ibg[6];
	
	
	
	void ondraw();
	void onlogic();
	
	
};

/* the scrolling credits class  (to be fit inside of a master game object) */
// starting position for a credits variable
const int starty_pos = 320;
const int start_xover = 120;

static int credit_offset = 0;

// credits structure 
struct Cred  {
	
	char name[100];
	COLORREF color;
	int y_pos;
	bool on;
	
	inline void setcredit(char* pname, COLORREF xcolor)
	{
		strcpy(name,pname);
		color = xcolor;
		y_pos = starty_pos;
		on = false;
		credit_offset ++;
		
	}
};


/* nested object , fitted inside of Start object */
class MasterCredits : public MasterGameObject {
	
public:
	Cred credits[100];
	int off_credit;
	int max_credit;
	
	virtual void load()
	{
		credit_offset = 0;
		credits[0].setcredit(" MasterPeice v1 by Jared Bruni",RGB(200,0,0));
		credits[1].setcredit(" dreams can become a reality",RGB(0,0,200));
		credits[2].setcredit(" its simply a decesion",RGB(0,0,200));
		credits[3].setcredit(" Evolve",RGB(0,255,0));
		credits[4].setcredit("",0x0);
		credits[5].setcredit(" Your",0xFF);
		credits[6].setcredit(" ",0xFF);
		credits[7].setcredit(" Mind",0xFFFFFF);
		credits[8].setcredit("",0x0);
		credits[9].setcredit(" www.lostsidedead.com ", RGB(0,0,200));
		credits[10].setcredit("",0x0);
		credits[11].setcredit("",0x0);
		credits[12].setcredit("",0x0);
		credits[13].setcredit("",0x0);
		credits[14].setcredit(" shout outs go to: ", RGB(100,250,rand()%100));
		credits[15].setcredit(" planetsourcecode.com - (best coding site on the net)",RGB(0,255,0));
		credits[16].setcredit(" lostsidedead.com - and all its members",RGB(0,0,255));
		credits[17].setcredit(" cplusplus.com - for publishing my source for all the c++ community to see!",RGB(255,0,0));
		credits[18].setcredit(" ",0x0);
		credits[19].setcredit(" * greets * (in random order) ", RGB( 0,100,100));
		credits[20].setcredit(" inc - c++ hackin l33tr0r", RGB( 0,0,200));
		credits[21].setcredit(" vulcan lord - awesome programmer", RGB(0,0,200));
		credits[22].setcredit(" lee trager - (aka the little master)",RGB( 0,0,200));
		credits[23].setcredit(" smut - leet ao-packet reverse enginer",RGB(0,0,200));
		credits[24].setcredit(" deslock, - makes cool stuff with masterX! ",RGB(0,0,200));
		credits[25].setcredit(" xeek, - newest lostsidedead member",RGB(0,0,200));
		credits[26].setcredit(" derick dong - awesome programmer, and writer of Glob2D!",RGB(0,0,200));
		credits[27].setcredit(" evilz ad - software enginer who I tutor ;] supz bro",RGB(0,0,200));
		credits[28].setcredit(" sue palms - my proffesor who taught me about machine language",RGB(0,255,0));
		credits[29].setcredit(" Todd - for my making the awesome lostsidedead.com page",RGB(255,0,0));
		credits[30].setcredit(" Allen - my good friend", RGB(0,255,0));
		credits[31].setcredit(" bo - ellite warez crackstar", RGB(0,255,0));
		credits[32].setcredit(" Micheal Essary, - hommie from the AOLCPP days",RGB(255,255,255));
		credits[33].setcredit("***  B0nk *** - this guys awesome, he made all the lost logo's",RGB(255,255,255));
		credits[34].setcredit(" voodo - ellite 3d game programmer (gets all the ladys)", RGB(0,0,255));
		credits[35].setcredit(" my grandma for buying me my first computer", RGB(255,255,0));
		credits[36].setcredit(" Ian Ippolito for making the best Site online",RGB(255,255,0));
		credits[37].setcredit(" uncle mark, for showing me whats up with the computer", RGB(255,255,0));
		credits[38].setcredit(" my mom, for buying me this huge collection of programming books", RGB(255,255,0));
		credits[39].setcredit(" my friend chris",RGB(255,150,0));
		credits[40].setcredit(" america online, for writing such crappy software", RGB(100,0,0));
		credits[41].setcredit(" nail princess - because shes pretty ;]",RGB(200,0,0));
		credits[42].setcredit(" john - good friend who dwell's in japan",RGB(200,0,0));
		credits[43].setcredit(" suneet - and his cool godzilla games!",RGB(200,0,0));
		credits[44].setcredit(" and EVERYONE ELSE, I tried to remember you all!! ;]",RGB(200,0,0));
		credits[45].setcredit(" ",0x0);
		credits[46].setcredit(" ",0x0);
		credits[47].setcredit(" ",0x0);
		credits[48].setcredit(" master@lostsidedead.com - aim: xmasterxx3 ",0xFFFFFF);
		credits[49].setcredit("[ the end ] www.lostsidedead.com ",0xFFFFFF);
		credits[50].setcredit(" ",0x0);
		credits[51].setcredit(" ",0x0);
		credits[52].setcredit(" ",0x0);
		credits[53].setcredit(" ",0x0);
		credits[54].setcredit(" ",0x0);
		
		off_credit = 0;
		max_credit = credit_offset;
		
		this->releasecredit();
		
	}
	
	virtual void update()
	{
		drawcredits();
		if(mxhwnd.SyncChange())
		{
			syncchange();
		}
	}
	
	// draw the credits to the screen
	inline void drawcredits()
	{
		mxhwnd.text.setfont( mfonts[0] );
		for(int i = 0; i <= max_credit; i++)
		{
			if(credits[i].on == true)
			{
				mxhwnd.text.settextcolor(credits[i].color);
				mxhwnd.text.printtext(credits[i].name,start_xover,credits[i].y_pos);
			}
		}
	}
	
	// proccess the credits
	inline void syncchange()
	{
		
		static int rc_count = 0;
		
		rc_count ++;
		
		if(rc_count > 30)
		{
			rc_count = 0;
			releasecredit();
		}
		
		for(int i = 0; i <= max_credit; i++)
		{
			if(credits[i].on == true)
			{
				credits[i].y_pos -= 1; // see deslock its the -= !;]
				if( credits[i].y_pos < 105 + 20 )
				{
					credits[i].y_pos = starty_pos;
					credits[i].on = false;
				}
				
			}
			
		}
	}
	
	inline void releasecredit()
	{
		credits[off_credit].y_pos = starty_pos;
		credits[off_credit].on = true;
		off_credit ++;
		
		if(off_credit > max_credit)
		{
			// reset
			off_credit = 0;
		}
	}
	
	
};



// enumerated constants 
enum { IDS_START, IDS_OP, IDS_CRED , IDS_SCORE };

// the start screen object
class Start: public MasterGameObject {
	
public:
	MASTERSCREEN sub_screen;
	int cursor_pos;
	MasterCredits credits;
	
	char scr_username[100];
	int off_pos;
	char input_data[100];
	int  input_index;
	bool im_off;


	virtual void load()
	{
		credits.load();
		startcur.SetColorKey(RGB(255,0,255));
		mxhwnd.LoadGraphic(&startg,"start.bmp");
		mxhwnd.LoadGraphic(&startcur,"shot1.bmp");
		mxhwnd.LoadGraphic(&mxg,"mx.bmp");
		mxhwnd.LoadGraphic(&jaredg,"jared.bmp");
		
		
		sub_screen = IDS_START;
		cx = 250;
		cy = 170;
		cursor_pos = 0;
		off_pos = 0;
 		strcpy(scr_username,"");

		
	}
	
	virtual void update()
	{
		ondraw();
		if(mxhwnd.SyncChange())
		{
			onlogic();
		}
	}
	
	// proccess keyboard input, into the start screen
	inline void keypress(WPARAM wParam)
	{
		switch(sub_screen)
		{
		case IDS_START:
			{
				switch(wParam)
				{
				case VK_DOWN:
					{
						if(cursor_pos < 3)
						{
							
							cursor_pos++;
							
						}
					}
					break;
				case VK_UP:
					{
						if(cursor_pos > 0)
						{
							
							cursor_pos--;
							
						}
					}
					break;
				case VK_RETURN:
					{
						// start screen triggers 
						switch(cursor_pos)
						{
						case 0: { /* start a new game */  newgame(); mxhwnd.SetScreen(ID_GAME); } break;
						case 1: { /* options */ sub_screen = IDS_OP; return; } break;
						case 2: { /* credits */ sub_screen = IDS_CRED; return; } break;
						case 3: { mxhwnd.Kill(); } break; 
						}
					}
					break;
				}
			}
			break;
		case IDS_OP:
			{
				switch(wParam)
				{
				case VK_RETURN:
					{
						sub_screen = IDS_START;
						return;
					}
					break;
				case VK_LEFT:
					{
						if(Options.linec > 5)
						{

						Options.linec--;

						}

					}
					break;
				case VK_RIGHT:
					{
						if(Options.linec < 10)
						{
							Options.linec++;
						}
					}
					break;
				}
			}
			break;
		case IDS_CRED:
			{
				switch(wParam)
				{
				case VK_RETURN:
					{
						sub_screen = IDS_START;
						return;
					}
					break;
				}
			}
			break;
		case IDS_SCORE:
			{
				static bool icaps = false;

				if( user_score > fscores.scorez[10].score  && im_off == false)
				{
						
					switch(wParam)
					{
					case VK_UP:
					case VK_DOWN:
					case VK_LEFT:
					case VK_RIGHT:
					case VK_ESCAPE:
					case VK_SHIFT:
					case VK_CONTROL:
						return;
						break;
					case VK_RETURN:
						{
							// pass command
							fscores.AddNew(input_data,user_score);
							im_off = true;

							strcpy(input_data,"");
							input_data[0] = 0;
							input_index = 0;
						
							return;
						}
						break;
					case VK_BACK:
						{
							input_index--;
							if(input_index < 0) { input_index = 0; input_data[0] = 0;  return; }
							input_data[input_index] = 0;
							return;
						}
						break;
					case VK_CAPITAL:
						{

							if(icaps == true) { icaps = false; } else { icaps = true; }
						}
						break;
						
					}
					
					if(input_index < 30) 
					{
						
						input_data[input_index] = fixkeys((int)wParam,(int)icaps,false);
						input_index++;
						input_data[input_index] = 0;
						
					}



					return;
				}

				switch(wParam)
				{
				case VK_RETURN:
					{

						// if its not there name
						sub_screen = IDS_START;
					    savescore();
						mxhwnd.SetScreen(ID_INTRO);
						im_off = false;
						return;
					}
					break;
				}
			}
			break;
			
		}
	}
	
private:
	
	MasterGraphic startg;
	MasterGraphic startcur;
	MasterGraphic mxg;
	MasterGraphic jaredg;
	
	
	int cx;
	int cy;
	
	
	void ondraw();
	void drawsub();
	void onlogic();
	
	
};

enum { D_DOWN = 1, D_UP = 2 };

// the game object
const int BR  = 5;
// contains the game grid
// which is were the game play occours
class Game : public MasterGameObject {
	
public:

	// games tile matrix
	class TileMatrix {

	public:

		struct GameData {

			unsigned long score;
			int lines;
			int speed;
			int lineamt;


			inline GameData()
			{
				newgame();
			}

			inline void newgame()
			{
				score = 0;
				lines = 0;
				speed = 20;
				lineamt;
			}

			inline void addline()
			{
				lines++;
				score += 6;
				lineamt++;

				if(lineamt >= Options.linec)
				{
					lineamt = 0;
					speed = speed - 4;
					if(speed < 4)
					{
						speed = 5;
					}
				}

				shandle.sounds[1].Play();

			}
		};

		struct GameBlock {


			struct Color {
				int c1,c2,c3;

				inline void randcolor()
				{
					c1 = rand()%10;
					c2 = rand()%10;
					c3 = rand()%10;
					if(c1 == 0) { c1++; }
					if(c2 == 0) { c2++; }
					if(c3 == 0) { c3++; }


					// were all the same
					if(c1 == c2 && c1 == c3)
					{
						randcolor();// try again
						return;
					}
				}

				inline void copycolor(Color* c)
				{
					c1 = c->c1;
					c2 = c->c2;
					c3 = c->c3;
				}

				// shift the colors up and down (true & false)
				inline void shiftcolor(bool dir)
				{
						int ic1;
						int ic2;
						int ic3;
						ic1 = c1;
						ic2 = c2;
						ic3 = c3;
					
					if(dir)
					{
						c1 = ic3;
						c2 = ic1;
						c3 = ic2;
					}
					else
					{
						c1 = ic2;
						c2 = ic3;
						c3 = ic1;
					}
				}

			};

			Color color;
			Color nextcolor;

			int x,y;

			inline GameBlock()
			{
				color.randcolor();
				nextcolor.randcolor();
			}

			inline void NextBlock()
			{
				color.copycolor(&nextcolor);
				nextcolor.randcolor();
				x = 3;
				y = 0;

			}

			inline void MoveDown()
			{
				if( y < 16 )
				{

				y++;
				
				}
			}

			inline void MoveLeft()
			{
				if(x > 0)
				{
					x--;
				}
			}

			inline void MoveRight()
			{
				if(x < 7)
				{
					x++;
				}
			}


		};

		GameData Game;
		GameBlock block;
		// breathing room
		int Tiles[17 + BR][8 + BR];
	
		inline void cleartiles()
		{

		
		for(int i = 0; i < 17; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				if( i <= 16 && j <= 7)
				Tiles[i][j] = 0;
			}
		}

		}

		// initilize the matrix, for a new game
		inline void init_matrix()
		{
			cleartiles();
			Game.newgame();
			block.NextBlock();
			
		}

		inline void setblock()
		{
			if ( block.y <= 0 )
			{
				gameover();
			}

			Tiles[ block.y ] [ block.x ] = block.color.c1;
			Tiles[ block.y+1 ] [ block.x ] = block.color.c2;
			Tiles[ block.y+2 ] [ block.x ] = block.color.c3;
			block.NextBlock();

			}

		// constructor

		inline TileMatrix()
		{
			cleartiles();
		}

		// proccess the blocks, move them down (this occours, when a line is cleared )
		inline ProccessBlocks()
		{
			// elite algorithm
			for(int z = 0; z < 8; z++)
			{
				for(int i = 0; i < 16; i++)
				{
					if(Tiles[i][z] != 0 && Tiles[i+1][z] == 0)
					{
						Tiles[i+1][z] = Tiles[i][z];
						Tiles[i][z] = 0;
					}
				}
			}
		}
	

	};

	TileMatrix matrix;

	
	
	virtual void load()
	{
	
	 	// lets load up are graphics
		mxhwnd.LoadGraphic(&grid_blocks[0],"block_black.bmp");
		mxhwnd.LoadGraphic(&grid_blocks[1],"block_yellow.bmp");
		mxhwnd.LoadGraphic(&grid_blocks[2],"block_orange.bmp");
		mxhwnd.LoadGraphic(&grid_blocks[3],"block_ltblue.bmp");
		mxhwnd.LoadGraphic(&grid_blocks[4],"block_dblue.bmp");
		mxhwnd.LoadGraphic(&grid_blocks[5],"block_purple.bmp");
		mxhwnd.LoadGraphic(&grid_blocks[6],"block_pink.bmp");
		mxhwnd.LoadGraphic(&grid_blocks[7],"block_gray.bmp");
		mxhwnd.LoadGraphic(&grid_blocks[8],"block_red.bmp");
		mxhwnd.LoadGraphic(&grid_blocks[9],"block_green.bmp");
		mxhwnd.LoadGraphic(&grid_blocks[10],"block_clear.bmp");
		
		mxhwnd.LoadGraphic(&gbg,"gamebg.bmp");

		matrix.init_matrix();
		

		
	}
	
	
	virtual void update()
	{ 
		draw();
		if(mxhwnd.SyncChange())
		{
			logic();
		}
	}
	
	inline void draw()
	{
		gbg.DisplayGraphic(0,0);
		drawmatrix();
		drawblock();
		mxhwnd.text.setfont(mfonts[0]);
		mxhwnd.text.settextcolor( RGB(rand()%255,rand()%255,rand()%255) );
		mxhwnd.text.setbkcolor( 0x0 );
		mxhwnd.text.sprinttext(200,60,"Score: %i", matrix.Game.score);
		mxhwnd.text.sprinttext(310,60,"Lines: %i", matrix.Game.lines);
		
		}

	inline void logic()
	{
		static int wait = 0;
		wait++;

		if(wait > matrix.Game.speed )
		{
			wait = 0;
			matrix.block.MoveDown();			
		}


		blockProc();

	}

	inline void blockProc()
	{
		// are we at the bottom ?
		if( matrix.block.y + 2 >= 16 )
		{
			matrix.setblock();
			return;
		}
		// did I run into another block?
		if( matrix.Tiles[ matrix.block.y + 3][matrix.block.x] != 0 )
		{
			matrix.setblock();
			return;
		}

		// now check and see if they are any 3 in a row going across

		for(int i = 0; i < 17; i++)
		{
			for(int j = 0; j < 8-2; j++)
			{
				int cur_color;
				cur_color = matrix.Tiles[ i ][ j ];
				if(cur_color != BLOCK_BLACK) 
				{

				if( matrix.Tiles [i][j+1] == cur_color && matrix.Tiles[i][j+2] == cur_color )
				{
					matrix.Tiles[i][j] = 0;
					matrix.Tiles[i][j+1] = 0;
					matrix.Tiles[i][j+2] = 0;

					// got a line
					matrix.Game.addline();
					return;
				}

				}

			}
		}

		// now check and see if there are any 3 i a row going down
		for(int z = 0; z < 8; z++)
		{
			for(int q = 0; q < 17-2; q++)
			{
				int cur_color = matrix.Tiles[q][z];
				if( cur_color != BLOCK_BLACK )
				{

					if( matrix.Tiles[q+1][z] == cur_color && matrix.Tiles[q+2][z] == cur_color )
					{
						matrix.Tiles[q][z]  = 0;
						matrix.Tiles[q+1][z] = 0;
						matrix.Tiles[q+2][z] = 0;
						matrix.Game.addline();
				 		return;
					}
				}
			}
		}

		//now lets see if we can find any diagnoal
		for(int p = 0; p < 8; p++)
		{
			for(int w = 0; w < 17; w++)
			{
				int cur_color;
				cur_color = matrix.Tiles[w][p];
				if(cur_color != 0)// we got a block ;]
				{
					// left
					if( matrix.Tiles [w+1][p+1] == cur_color && matrix.Tiles[w+2][p+2] == cur_color)
					{
						matrix.Tiles[w][p] = 0;
						matrix.Tiles[w+1][p+1] = 0;
						matrix.Tiles[w+2][p+2] = 0;
						matrix.Game.addline();
					}
					if( w-2 >= 0 && p-2 >= 0)
					{

					if(matrix.Tiles [w-1][p-1] == cur_color && matrix.Tiles[w-2][p-2] == cur_color)
					{
						matrix.Tiles[w][p] = 0;
						matrix.Tiles[w-1][p-1] = 0;
						matrix.Tiles[w-2][p-2] = 0;
						matrix.Game.addline();
					}

					}

					if(w-2 >= 0)
					{


					if(matrix.Tiles[w-1][p+1] == cur_color && matrix.Tiles[w-2][p+2] == cur_color)
					{
						matrix.Tiles[w][p] = 0;
						matrix.Tiles[w-1][p+1] = 0;
						matrix.Tiles[w-2][p+2] = 0;
						matrix.Game.addline();
					}

					}

					if(p-2 >= 0)
					{


					if(matrix.Tiles[w+1][p-1] == cur_color && matrix.Tiles[w+2][p-2] == cur_color)
					{
						matrix.Tiles[w][p] = 0;
						matrix.Tiles[w+1][p-1] = 0;
						matrix.Tiles[w+2][p-2] = 0;
						matrix.Game.addline();
					}

					}
				}
			}
		}


		matrix.ProccessBlocks();

	}

	// draw the matrix
	inline void drawmatrix()
	{
		
		int STARTPOSX = STARTX;
		int STARTPOSY = STARTY;
		int x = STARTPOSX,y = STARTPOSY;
		
		for(int i = 0; i < 17; i++)
		{
			
			
			for(int j = 0; j < 8; j++)
			{
				
				grid_blocks[matrix.Tiles[i][j]].DisplayGraphic(x,y);
				x = x + 32;
				
			}
			x = STARTPOSX;
			y = y + 16;
			// down lower
		}

		// draw the next block
	int bx = 510; int by = 200;

		
	grid_blocks[matrix.block.nextcolor.c1].DisplayGraphic(bx,by);
	grid_blocks[matrix.block.nextcolor.c2].DisplayGraphic(bx,by+16);
	grid_blocks[matrix.block.nextcolor.c3].DisplayGraphic(bx,by+32);

		

		
	}
	// draw the blocks
	inline void drawblock()
	{
		int bx;
		int by;
		getcords(matrix.block.y,matrix.block.x,bx,by);
		grid_blocks[matrix.block.color.c1].DisplayGraphic(bx,by);
		getcords(matrix.block.y+1,matrix.block.x,bx,by);
		grid_blocks[matrix.block.color.c2].DisplayGraphic(bx,by);
		getcords(matrix.block.y+2,matrix.block.x,bx,by);
		grid_blocks[matrix.block.color.c3].DisplayGraphic(bx,by);


	}
	// keypress
	inline void keypress(WPARAM wParam)
	{
		switch(wParam)
		{
		case VK_LEFT:
			if( matrix.block.x >= 1)
			{

			if( matrix.Tiles [ matrix.block.y ] [ matrix.block.x-1 ] == 0 && matrix.Tiles [ matrix.block.y + 1 ] [ matrix.block.x-1 ] == 0 && matrix.Tiles [ matrix.block.y  + 1 ] [ matrix.block.x-1 ] == 0 && matrix.Tiles [ matrix.block.y + 3] [ matrix.block.x-1 ] == 0)
			{

			//grid.HandleInput(wParam);
			matrix.block.MoveLeft();

			}

			}
			break;
		case VK_RIGHT:
			if( matrix.block.x < 7)
			{

					if( matrix.Tiles [ matrix.block.y ] [ matrix.block.x+1 ] == 0 && matrix.Tiles [ matrix.block.y + 1 ] [ matrix.block.x+1 ] == 0 && matrix.Tiles [ matrix.block.y  + 1 ] [ matrix.block.x+1 ] == 0 && matrix.Tiles [ matrix.block.y + 3] [ matrix.block.x+1 ] == 0)
					{

			//grid.HandleInput(wParam);
			matrix.block.MoveRight();

					}

			}
			break;
		case VK_DOWN:
		//	grid.HandleInput(wParam);
			if( matrix.Tiles [ matrix.block.y + 3 ][ matrix.block.x ] == 0 && matrix.block.y + 3 < 15 )
			{

				if(matrix.Tiles[ matrix.block.y + 4 ][ matrix.block.x ] == 0)
				{

			matrix.block.MoveDown();

				}

			}
			break;
		case 'A':
		case 'a':
	 		matrix.block.color.shiftcolor(true);
			break;
		case 'S':
		case 's':
	 		matrix.block.color.shiftcolor(false);
			break;
		}
		
	}
	
	void drawgame();
	
	
	
private:
	
	MasterGraphic grid_blocks[11];
	MasterGraphic gbg;
	
	
	
};


#endif
