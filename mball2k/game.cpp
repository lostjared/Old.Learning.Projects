// the game source file
// written by jared bruni
// www.lostsidedead.com

#include "thehead.h"
#define BALL_UP 1
#define BALL_DOWN 2
#define SLANT_LEFT 3
#define SLANT_RIGHT 4
#define NOBLOCK -2

HFONT gtitlefont = MakeFont("Arial",18);
HFONT gscorefont = MakeFont("Arial",12);


void game_logic();
void game_draw();
void game_drawmenu();
void game_drawgraph();
void game_input();
void game_barproc();
void game_ballcheck();
int  game_blockbypos(int x, int y);


// ball structure
struct Ball
{
	int x;
	int y;
	int dir;
	int slant;
	int slantx;
	int speed;

	// constructor for the ball
	inline Ball()
	{
		x = 100;
		y = 100;
		dir = BALL_DOWN;
		slant = SLANT_RIGHT;
		slantx = 5;
		speed = 5;
	}
	// draw the ball
	inline void DrawBall()
	{
		mxhwnd.paint.mxdrawellipse(x,y,x+15,y+15,0xFFFFFF,0xFFFFFF);
		mxhwnd.paint.mxdrawellipse(x+3,y+3,x+12,y+12,RGB(rand()%255,rand()%255,rand()%255),RGB(rand()%255,rand()%255,rand()%255));
	}
	// proccess the ball
	inline void ProcBall()
	{
		// move the ball
		if(dir == BALL_DOWN)
		{
			if(slant == SLANT_RIGHT)
			{
				x += slantx;
			}
			else
			{
				x -= slantx;
			}

			y += speed;// rate of decline
			y += player.difficulty;
		}
		else
		{
			if(slant == SLANT_RIGHT)
			{
				x +=  slantx;
			}
			else
			{
				x -= slantx;
			}
			
			y -= speed;
			y -= player.difficulty;
		}
	}

	// set the direction in which the ball is traveling
	inline void SetBallDirection(int bdir, int bslant, int bslantx, int bspeed)
	{
		dir = bdir;
		slant = bslant;
		slantx = bslantx;
		speed = bspeed;
		
	}
};

const int MAP_SIZE = 520;
const int NULL_BLOCK = -1;
// level map structure
struct LevelMap
{
	int blocks[MAP_SIZE];

	// constructor
	inline LevelMap()
	{
		for(int i = 0; i <= MAP_SIZE; i++)
		{
			blocks[i] = NULL_BLOCK;
		}

		RandMap(5,6);
	}
	// random map generator
	inline void RandMap(int mass,int max)
	{
		srand(time(NULL));

		for(int i = 0; i <= MAP_SIZE; i++)
		{ 
			int rmap = rand()%max;
			if(rmap >= mass )
			{
				blocks[i] = RGB(rand()%255,rand()%255,rand()%255);
			}
			else
			{
				blocks[i] = NULL_BLOCK;
			}
		}

		// clear the bottom 4 of each row
	}
	// draw the map
	inline void DrawMap()
	{
		int sx = 7;
		int sy = 51;

		int dx = sx;
		int dy = sy;

		int row = 0;

		for(int i = 0; i <= MAP_SIZE; i++)
		{
			DrawTile(dx,dy,blocks[i]);

			dy = dy + 15;

			row++;

			if(row > 20)
			{
				row = 0;
				dx = dx + 25;
				dy = sy;
			}
		}
	}
	// draw a specific tile
	inline void DrawTile(int x, int y,int type)
	{
		if(type != NULL_BLOCK)
		{

	//	mxhwnd.paint.mxdrawrect(x,y,x+25,y+15,type,type);
	    mxhwnd.paint.mxdrawellipse(x,y,x+25,y+15,type,type);

		}
	}
	// has this level been cleared? 
	inline bool LevelOver()
	{
		for(int i = 0; i <= MAP_SIZE; i++)
		{
			if(blocks[i] != NULL_BLOCK)
			{
				return false;
			}
		}

		return true;
	}
};

struct PlayerBar
{
	int x;
	int y;
	// constructor
	inline PlayerBar()
	{
		x = 100;
		y = 480-35;
	}
	// draw the bar
	inline void DrawBar()
	{
	//	mxhwnd.paint.mxdrawrect(x,y,x+100,y+10,0xFFFFFF,0xFFFFFF);
		int color = 0xFFFFFF;
		for(int i = y; i < y + 10; i++)
		{
			// draw shaded line
			mxhwnd.paint.mxhorizontalline(x,x+98,i,color);
			color -= 25;
		}

	}

	// user pressed left
	inline void PressLeft()
	{
		if(x > 7)
		{

		x -= 7;

		}
	}

	// user pressed right
	inline void PressRight()
	{
		if(x < 640-7-100)
		{

		x += 7;

		}
	}

};

Ball ball;
LevelMap map;
PlayerBar bar;

// load a level
void loadlevel(int level)
{
	switch(level)
	{
	case 1:
		map.RandMap(19,20);
		break;
	case 2:
		map.RandMap(15,20);
		break;
	case 3:
		map.RandMap(10,20);
		break;
	case 4:
	case 5:
	case 6:
		map.RandMap(7,20);
		break;
	}
	if(level >= 7)
	{
		map.RandMap(rand()%255,rand()%400);
	}
}

// the game update
void game_update()
{
	game_draw();
	if(mxhwnd.SyncChange())
	{
		game_logic();
	}

}

// game draw update
void game_draw()
{
	drawsprite(0,0,GAME);
	game_drawgraph();
	game_drawmenu();
}
// draw the game menu for score etc
void game_drawmenu()
{
	COLORREF rcolor = RGB(rand()%255,rand()%255,rand()%255);
	mxhwnd.paint.mxdrawrect(5,5,640-5,50,0x0,0x0);
	mxhwnd.paint.mxverticalline(5,480-5,4,rcolor);
	mxhwnd.paint.mxhorizontalline(4,640-6,4,rcolor);
	mxhwnd.paint.mxverticalline(5,480-5,640-6,rcolor);
	mxhwnd.paint.mxhorizontalline(4,640-6,480-5,rcolor);
	mxhwnd.paint.mxhorizontalline(4,640-6,50,rcolor);
	mxhwnd.text.setbkcolor(0x0);
	mxhwnd.text.settextcolor(0xFF0000);
	mxhwnd.text.setfont(gtitlefont);
	mxhwnd.text.printtext("Master Ball Game",15,15);
	mxhwnd.paint.mxhorizontalline(15,160,35,rcolor);
	int bx = 145;
	int by = 20;
	mxhwnd.paint.mxdrawellipse(bx,by,bx+10,by+10,rcolor,rcolor);
	mxhwnd.text.settextcolor(RGB(200,0,0));
	mxhwnd.text.setfont(gscorefont);
	char strscore[50];
	sprintf(strscore,"Score: %i",player.score);
	char strdif[50];
	sprintf(strdif,"Difficulty: %i",player.difficulty);
	mxhwnd.text.printtext(strscore,170,15);
	mxhwnd.text.printtext(strdif,170,30);
	char strliv[50];
	sprintf(strliv,"Lives: %i",player.lives);
	mxhwnd.text.printtext(strliv,300,15);
	char strhit[50];
	sprintf(strhit,"Total Hits: %i",player.hits);
	mxhwnd.text.printtext(strhit,300,30);
	mxhwnd.text.setfont(gtitlefont);
	mxhwnd.text.settextcolor(rcolor);
	char levelbuff[50];
	sprintf(levelbuff,"Level: %i",player.level);
	mxhwnd.text.printtext(levelbuff,480,20);

}
// draw graph
void game_drawgraph()
{
	map.DrawMap();
	ball.DrawBall();
	bar.DrawBar();
}

// game logic update
void game_logic()
{
	game_input();
	ball.ProcBall();
	game_barproc();

	// check and see if they beat the level
	if(map.LevelOver() == true)
	{
		player.level++;
		loadlevel(player.level);
	    ball.x = 100;
		ball.y = 100;
		ball.SetBallDirection(BALL_DOWN,SLANT_RIGHT,5,5);
	}
	// see if they missed the ball
	if(ball.y > 480)
	{
		player.lives--;
		if(player.lives < 0)
		{
			// game over
			mxhwnd.SetScreen(ID_GAMEOVER);
		}
		else
		{
			ball.x = 100;
			ball.y = 100;
			ball.SetBallDirection(BALL_DOWN,SLANT_RIGHT,5,5);
		}
	}
}

// bar proccess, see if they colide
void game_barproc()
{
	// the ball and the bar are cliping
	if(ball.x < bar.x + 100 && ball.x > bar.x)
	{
		if(ball.y+15 >= bar.y && ball.y < bar.y + 25)
		{
			int dist;
			dist = bar.x - ball.x;
			if(dist < -50)
			{
			ball.SetBallDirection(BALL_UP,SLANT_LEFT,5,5);

			}
			else
			{
				ball.SetBallDirection(BALL_UP,SLANT_RIGHT,5,5);
			}

			player.hits++;
		}
	}

	game_ballcheck();
}
// check out the position of the ball
void game_ballcheck()
{
	if(ball.y < 55)
	{
		int slantdir;
		if(5 > rand()%10)
		{
			slantdir = SLANT_LEFT;
		}
		else
		{
			slantdir = SLANT_RIGHT;
		}
		ball.SetBallDirection(BALL_DOWN,slantdir,rand()%10,5);
	}

	if(ball.x < 6)
	{
	
		int godir;
		if(5 > rand()%10)
		{
			godir = BALL_UP;
		}
		else
		{
			godir = BALL_DOWN;
		}
			ball.SetBallDirection(godir,SLANT_RIGHT,ball.slantx,ball.speed);
	}
	if(ball.x > 640-5-25)
	{
		int godir;
		if(5 > rand()%10)
		{
			godir = BALL_UP;
		}
		else
		{
			godir = BALL_DOWN;
		}

		ball.SetBallDirection(godir,SLANT_LEFT,ball.slantx,ball.speed);

	}

	int block_pos;
	block_pos = game_blockbypos(ball.x,ball.y);
	if(block_pos == NOBLOCK) { return; }
	if(map.blocks[block_pos] == NULL_BLOCK) { return; }

	if(map.blocks [block_pos] != NULL_BLOCK)
	{
		playgamesound(1);
		map.blocks[block_pos] = NULL_BLOCK;
		player.score += 20;

		int gdir;
		int sdir;

		if(5 > rand()%10)
		{
			gdir = BALL_UP;
		}
		else
		{
			gdir = BALL_DOWN;
		}

		if(5 > rand()%10)
		{
			sdir = SLANT_LEFT;
		}
		else
		{
			sdir = SLANT_RIGHT;
		}

		ball.SetBallDirection(gdir,sdir,rand()%15,rand()%10);

	}

}

// get the input
void game_input()
{
	if(player.joystick_on)
	{
		if(stick.JoyLeft())
		{
			bar.PressLeft();
		}

		if(stick.JoyRight())
		{
			bar.PressRight();
		}
	}
	else // there using the keyboard
	{
		if(mxhwnd.KeyCheck(DIK_LEFT))
		{
			bar.PressLeft();
		}
		if(mxhwnd.KeyCheck(DIK_RIGHT))
		{
			bar.PressRight();
		}
	}
}
// ball by pos
int game_blockbypos(int x, int y)
{
	int sx = 7;
	int sy = 51;

	int dx = sx;
	int dy = sy;

	int row = 0;

	for(int i = 0; i <= MAP_SIZE; i++)
	{
		if(x > dx-25 && x < dx+25 && y > dy-15 && y < dy+15)
		{
			return i;
		}
		if(x > dx && y > dy && x < dx+25 && y > dy && y < dy + 15)
		{
			return i;
		}
		if(x+15 > dx && y+15>dy && x+15 < dx+25 && y +15 < dy+15)
		{
			return i;
		}
		if((x-15 >= dx) && x-15 <= dx+25 && y-15 >= y && y < dy+15)
		{
			return i;
		}

		dy = dy + 15;

		row++;

		if(row > 20)
		{
			row = 0;
			dx = dx + 25;
			dy = sy;
		}
	}

	return NOBLOCK;
}

