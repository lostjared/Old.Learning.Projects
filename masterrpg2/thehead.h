/* MasterRPG Alpha 2
   written by Jared Bruni
   www.LostSideDead.com

  "Open Source, Open Mind"
*/

#define WIN2K /* uncomment for compiling on windows 2000/XP */
#define MASTERXSDK
#include"masterlibrary4.h"
#include<fstream.h>
#define Sync if(mxhwnd.SyncChange())

extern MasterXHWND mxhwnd;

enum { ID_INTRO, ID_GAME };

long __stdcall event(struct HWND__* hwnd,unsigned int msg, unsigned int wparam, long lparam);
void render(int screen);

class Intro : public MasterGameObject {

public:

	virtual void load()
	{
		mxhwnd.LoadGraphic(&intro_graphic,"intro.bmp");
	}

	virtual void update()
	{
		intro_graphic.DisplayGraphic(0,0);
		Sync 
		{
			static int wait = 0;
			if( ++wait > 75 )
			{
				wait = 0;
				mxhwnd.SetScreen(ID_GAME);
			}
		}
	}

private:

	MasterGraphic intro_graphic;


};

struct Level {

	int array[1000][1000];
	int start_row;
	int start_col;

	Level()
	{
		clear();
		start_row = 0;
		start_col = 0;
	}

	void clear()
	{
		for(int i = 0; i < 1000; i++)
		{
			for(int z = 0; z < 1000; z++)
			{
				array[i][z] = rand()%4;
			}
		}
	}
};


class Game : public MasterGameObject {

public:

	virtual void load()
	{
		mxhwnd.LoadGraphic(&bg[0],"water1.bmp");
		mxhwnd.LoadGraphic(&bg[1],"water2.bmp");
		mxhwnd.LoadGraphic(&bg[2],"blue_brick.bmp");
		mxhwnd.LoadGraphic(&bg[3],"bluesky.bmp");
		mxhwnd.LoadGraphic(&bg[4],"grass.bmp");
		mxhwnd.LoadGraphic(&bg[5],"gray_brick.bmp");
		mxhwnd.LoadGraphic(&bg[6],"red_brick.bmp");
		mxhwnd.LoadGraphic(&bg[7],"sand1.bmp");
		mxhwnd.LoadGraphic(&bg[8],"sand2.bmp");
		mxhwnd.LoadGraphic(&bg[9],"snow.bmp");
		mxhwnd.LoadGraphic(&bg[10],"blacksky.bmp");
		mxhwnd.LoadGraphic(&bg[11],"stone.bmp");
		mxhwnd.LoadGraphic(&bg[12],"stone2.bmp");
		mxhwnd.LoadGraphic(&bg[13],"stone3.bmp");
		mxhwnd.LoadGraphic(&bg[14],"stone4.bmp");
		mxhwnd.LoadGraphic(&pes,"pes.bmp");
		pes.SetColorKey(RGB(255,0,255));
		ifstream fin("level.dat",ios::binary);
		fin.read((char*)&level,sizeof(level));
		fin.close();
		level.start_row = 0;
		level.start_col = 0;
		cur_hero = 0;
		hero_x = 10;
		hero_y = 10;
		hero_row = 0;
		hero_col = 0;
	}

	virtual void update()
	{
		drawbg();
		drawhero();
		Sync
		{
			logic();
		}
	}

	inline void logic()
	{
		if(mxhwnd.KeyCheck(DIK_RIGHT))
		{
			if(hero_x < 275)
			{
				hero_x += 16;
				hero_col ++;

				if(cur_hero != 2 && cur_hero != 3)
				{
					cur_hero = 2;
				}
				if(cur_hero == 2)
				{
					cur_hero = 3;
					return;
				}
				if(cur_hero == 3)
				{
					cur_hero = 2;
					return;
				}

			}
			else
			{
				if(level.start_col >= 1000-39)
				{
					if(hero_x < 640-32-10)
					{

					hero_x += 16;
					hero_col++;

					}
				}
				else
				{

				scrollright();
				hero_col++;

				}

				if(cur_hero != 2 && cur_hero != 3)
				{
					cur_hero = 2;
				}
				if(cur_hero == 3)
				{
					cur_hero = 2;
					return;
				}
				if(cur_hero == 2)
				{
					cur_hero = 3;
					return;
				}
			
			}
		}

		if(mxhwnd.KeyCheck(DIK_LEFT))
		{
			if(hero_x > 275)
			{
				hero_x -= 16;
				hero_col --;

				if(cur_hero != 6 && cur_hero != 7)
				{
					cur_hero = 6;
				}
				if(cur_hero == 6)
				{
					cur_hero = 7;
					return;
				}
				if(cur_hero == 7)
				{
					cur_hero = 6;
					return;
				}

			}
			else
			{
				if(level.start_col == 0)
				{
					if(hero_x > 10)
					{

					hero_x -= 16;
					hero_col--;

					}
				}
				else
				{

				scrollleft();
				hero_col--;

				}

				if(cur_hero != 6 && cur_hero != 7)
				{
					cur_hero = 6;
				}
				if(cur_hero == 6)
				{
					cur_hero = 7;
					return;
				}
				if(cur_hero == 7)
				{
					cur_hero = 6;
					return;
				}
			
			}
		}

		if(mxhwnd.KeyCheck(DIK_DOWN))
		{
			if(hero_y < 220)
			{
				hero_y += 16;
				hero_row++;

				if(cur_hero != 0 && cur_hero != 1)
				{
					cur_hero = 0;
				}

				if(cur_hero == 0)
				{
					cur_hero = 1;
					return;
				}

				if(cur_hero == 1)
				{
					cur_hero = 0;
					return;
				}
			}
			else
			{
				if(level.start_row >= 1000-29)
				{
					if(hero_y < 480-32-10)
					{
						hero_y += 16;
						hero_row++;
					if(cur_hero != 0 && cur_hero != 1)
					{
						cur_hero = 0;
					}

					if(cur_hero == 0)
					{
						cur_hero = 1;
						return;
					}

					if(cur_hero == 1)
					{
						cur_hero = 0;
						return;
					}
				}
			
			}
			else
			{
					scrolldown();
					hero_row++;

					if(cur_hero != 0 && cur_hero != 1)
					{
						cur_hero = 0;
					}

					if(cur_hero == 0)
					{
						cur_hero = 1;
						return;
					}

					if(cur_hero == 1)
					{
						cur_hero = 0;
						return;
					}
				}
			}

		}

		if(mxhwnd.KeyCheck(DIK_UP))
		{
			if(hero_y > 220)
			{
				hero_y  -= 16;
				hero_row--;

				if(cur_hero != 4 && cur_hero != 5)
				{
					cur_hero = 4;
				}

				if(cur_hero == 4)
				{
					cur_hero = 5;
					return;
				}

				if(cur_hero == 5)
				{
					cur_hero = 4;
					return;
				}
			}
			else
			{
				if(level.start_row == 0)
				{
					if(hero_y > 10)
					{
						hero_y -=16;
						hero_row--;
						
			    	if(cur_hero != 4 && cur_hero != 5)
					{
			    		cur_hero = 4;
					}

			    	if(cur_hero == 4)
					{
				    	cur_hero = 5;
				    	return;
					}

				    if(cur_hero == 5)
					{
				    	cur_hero = 4;
				    	return;
					}

					}
				}
				else
				{
					scrollup();
					hero_row--;
					
					if(cur_hero != 4 && cur_hero != 5)
					{
						cur_hero = 4;
					}

					if(cur_hero == 4)
					{
						cur_hero = 5;
						return;
					}

					if(cur_hero == 5)
					{
						cur_hero = 4;
						return;
					}
				}

			}
		}


	}

	inline void drawbg()
	{
		int start_x = 10;
		int start_y = 10;

		int x = start_x ,y = start_y;

		for(i = level.start_row; i < level.start_row+29; i++)
		{
			for(z = level.start_col; z < level.start_col+39; z++)
			{
				bg[level.array[i][z]].DisplayGraphic(x,y);
				x += 16;

			}

			x = start_x;
			y += 16;
		}
	}

	inline void drawhero()
	{
		drawhero(hero_x,hero_y,cur_hero);
	}

	inline void keypress(int key)
	{
		/*
		switch(key)
		{
		case VK_UP:
			scrollup();
			break;
		case VK_DOWN:
			scrolldown();
			break;
		case VK_LEFT:
			scrollleft();
			break;
		case VK_RIGHT:
			scrollright();
			break;
		}
		*/
	}

private:

	MasterGraphic bg[15];
	MasterGraphic pes;
	Level level;
	int i,z;
	int cur_hero;
	int hero_x;
	int hero_y;
	int hero_row;
	int hero_col;

	inline void scrollleft()
	{
		if(level.start_col > 0)
		{
			level.start_col--;
		}
	}

	inline void scrollright()
	{
		if(level.start_col < 1000-39)
		{

		level.start_col++;

		}
	}

	inline void scrolldown()
	{
		if(level.start_row < 1000-29)
		{

		level.start_row++;
		
		}	
	}

	inline void scrollup()
	{
		if(level.start_row > 0)
		{

			level.start_row--;

		}
	}

	inline void drawhero(int x, int y, int sprite)
	{
		int bx,by,bw,bh;
		by = 0;
		bh = 32;

		switch(sprite)
		{
		case 0:
		bx = 0;
		bw = 32;
			break;
		case 1:
		bx = 32;
		bw = 32*2;
			break;
		case 2:
		bx = 32*2;
		bw = 32*3;
			break;
		case 3:
		bx = 32*3;
		bw = 32*4;
			break;
		case 4:
		bx = 32*4;
		bw = 32*5;
			break;
		case 5:
		bx = 32*5;
		bw = 32*6;
			break;
		case 6:
		bx = 32*6;
		bw = 32*7;
			break;
		case 7:
		bx = 32*7;
		bw = 32*8;
			break;
		case 8:
		bx = 32*8;
		bw = 32*9;
			break;
		case 9:
		bx = 32*9;
		bw = 32*10;
			break;
		case 10:
		bx = 32*10;
		bw = 32*11;
			break;
		case 11:
		bx = 32*11;
		bw = 32*12;
			break;
		}

		pes.DisplayGraphicEx(bx,by,bw,bh,x,y);
	}

};
