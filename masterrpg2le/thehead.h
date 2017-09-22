/* MasterRPG Alpha 2  Level Editor
   written by Jared Bruni
   www.LostSideDead.com

  "Open Source, Open Mind"
*/

//#define WIN2K /* uncomment for compiling on windows 2000/XP */
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
		mxhwnd.LoadGraphic(&left_scroll,"left_scroll.bmp");
		mxhwnd.LoadGraphic(&right_scroll,"right_scroll.bmp");
		cur_img = 0;
		ifstream fin("level.dat",ios::binary);
		fin.read((char*)&level,sizeof(level));
		fin.close();
	}

	virtual void update()
	{
		drawbg();
		left_scroll.DisplayGraphic(475,200);
		right_scroll.DisplayGraphic(590,200);
		mxhwnd.text.settextcolor(RGB(255,0,0));
		mxhwnd.text.setbkcolor(RGB(0,0,0));
		mxhwnd.text.printtext("Use arrow keys to scroll map",475,10);
		bg[cur_img].DisplayGraphic(545,220);
		mxhwnd.paint.mxdrawrect(480,250,630,275,RGB(150,150,150),RGB(175,175,175));
		mxhwnd.text.setbkcolor(RGB(150,150,150));
		mxhwnd.text.printtext("Save",535,255);
	}

	inline void drawbg()
	{
		int start_x = 10;
		int start_y = 10;

		int x = start_x ,y = start_y;

		for(i = level.start_row; i < level.start_row+29; i++)
		{
			for(z = level.start_col; z < level.start_col+29; z++)
			{
				bg[level.array[i][z]].DisplayGraphic(x,y);
				x += 16;

			}

			x = start_x;
			y += 16;
		}
	}

	inline void keypress(int key)
	{
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
	}

	inline void leftclick(int x, int y)
	{
		if(x > 475 && x < 475 + 45 && y > 200 && y < 200 + 45)
		{
			if(cur_img > 0)
			{
				cur_img--;
			}
		}

		if(x > 590 && x < 590 + 45 && y > 200 && y < 200 + 45)
		{
			if(cur_img < 14)
			{
				cur_img++;
			}
		}

		if(x > 480 && x < 630 && y > 250 && y < 275)
		{
			ofstream fout("level.dat",ios::binary);
			fout.write((char*)&level,sizeof(level));
			fout.close();
		}
	}

	inline void mousemove(int x, int y, int wparam)
	{
		if(wparam & MK_LBUTTON)
		{
			int row,col;
			getblockbypos(x,y,row,col);
		 	if(row == -1 || col == -1)
			{
				return;
			}
			level.array[row][col] = cur_img;
		
		}
	}

	inline void fill()
	{
		for(i = 0; i < 1000; i++)
		{
			for(z = 0; z < 1000; z++)
			{
				level.array[i][z] = 4;
			}
		}
	}

private:

	MasterGraphic bg[15];
	MasterGraphic left_scroll;
	MasterGraphic right_scroll;
	Level level;
	int i,z;
	int cur_img;
 
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
	
	inline void getblockbypos(int ix, int iy, int& row, int& col)
	{
		int start_x = 10;
		int start_y = 10;
		
		int x = start_x ,y = start_y;
		
		for(i = level.start_row; i < level.start_row+29; i++)
		{
			for(z = level.start_col; z < level.start_col+29; z++)
			{
				if(ix > x && ix < x + 16 && iy > y && iy < y + 16)
				{
					row = i;
					col = z;
					return;
				}
				x += 16;
				
			}
			
			x = start_x;
			y += 16;
		}

		row = -1;
		col = -1;
	}

};
