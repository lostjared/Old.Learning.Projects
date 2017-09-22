/* Knights Tour
   written by Jared Bruni
   www.LostSideDead.com

  "Open Source, Open Mind"

*/


#define Sync if(mxhwnd.SyncChange()) 
#define MASTERXSDK
#include "masterlibrary2.h"
#include<time.h>

// masterX HWND
MasterXHWND mxhwnd;


// callback functions
long _stdcall event(struct HWND__* hwnd,unsigned int msg,unsigned int wParam,long lParam);
void render(MASTERSCREEN screen);

namespace knight
{

	struct Position
	{
		int row,col;
	};

  	MasterGraphic gknight;
	Position pos;
	int moves = 0,	
	startx = 50,
	starty = 50,
	i,z,counter,
	board[8][8],
    htable[8][8] = {
		{2,3,4,4,4,4,3,2},
		{3,4,6,6,6,6,4,3},
		{4,6,8,8,8,8,6,4},
		{4,6,8,8,8,8,6,4},
		{4,6,8,8,8,8,6,4},
		{4,6,8,8,8,8,6,4},
		{3,4,6,6,6,6,4,3},
		{2,3,4,4,4,4,3,2}
	};

	int horizontal[8] = { 2,1,-1,-2,-2,-1,1,2 };
	int vertical[8] = { -1,-2,-2,-1,1,2,2,1 };

	
	inline void init();
	inline void draw();
	inline void logic();
	inline void drawboard();
	inline void drawknight();
	inline void clearboard();
	inline void nextmove();
	
}

int _stdcall MasterMain(struct HINSTANCE__* hInst, char* line) 
{
	if(mxhwnd.CreateMasterX("MasterX",640,480,COLOR_DEFAULT,event,hInst,NULL,NULL))
	{
		knight::init();
		return mxhwnd.InitLoop(render);
	}

	return (0);
}

inline void knight::init()
{
	mxhwnd.HideCursor();
	mxhwnd.InitTimer(1,1);
	mxhwnd.LoadGraphic(&gknight,"knight.bmp");
	gknight.SetColorKey(RGB(255,255,255));
	srand(time(NULL));
	pos.row = 1;
	pos.col = 6;
	clearboard();
}



long _stdcall event(struct HWND__* hwnd,unsigned int msg,unsigned int wParam,long lParam)
{

	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ACTIVATEAPP:
		mxhwnd.activeapp = wParam;
		break;
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_ESCAPE:
				mxhwnd.Kill();
				break;
			case VK_SPACE:
				knight::nextmove();
				break;
			case VK_RETURN:
				knight::clearboard();
				knight::pos.row = 1;
				knight::pos.col = 6;
				knight::moves = 0;
				break;
			}
		}
		break;
	case WM_TIMER:
		{
			mxhwnd.ChangeTime();// you can use whatever type of clock
			// or timer you want to change the time for the sync changes
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return (0);
}

void render(MASTERSCREEN screen)
{
	mxhwnd.SetTimeFlag();// set the time flag
	knight::draw();
	Sync
	{
		knight::logic();
	}
}

inline void knight::draw()
{
	mxhwnd.text.settextcolor(RGB(0,0,255));
 	mxhwnd.text.sprinttext(10,10,"CRC - Knights Tour - written by Jared Bruni - Press Space to Make Move, Press Enter to Clear : Moves: %i",moves);
	drawboard();
	drawknight();

}

inline void knight::logic()
{


}

inline void knight::drawboard()
{
	startx = 100;
	starty = 30;
	counter = 0;
	
	static int dx,dy;
	dx = startx;
	dy = starty;
	static COLORREF curcolor;
	static bool ion = true;

	for(i = 0; i < 8; i++)
	{
		for(z = 0; z < 8; z++)
		{
			if(ion == true)
			{
				curcolor = RGB(255,255,255);
			}
			else
			{
				curcolor = RGB(255,0,0);
			}
			ion = !ion;

			if(board[i][z] == 0)
			{

			mxhwnd.paint.mxdrawrect(dx,dy,dx+50,dy+50,curcolor,curcolor);

			}

			dx += 55;
			counter++;
			if(counter >= 8)
			{
				counter = 0;
				dy += 55;
				dx = startx;
				ion = !ion;
			}

		}
	}
}

inline void knight::drawknight()
{
	static int dx,dy;
	dx = startx;
	dy = starty;
	static COLORREF curcolor;
	static bool ion = true;

	for(i = 0; i < 8; i++)
	{
		for(z = 0; z < 8; z++)
		{
		
			if(pos.row == i && pos.col == z)
			{
				gknight.DisplayGraphic(dx,dy);
				return;
			}

			dx += 55;
			counter++;
			if(counter >= 8)
			{
				counter = 0;
				dy += 55;
				dx = startx;
				ion = !ion;
			}

		}
	}
}

inline void knight::clearboard()
{
	for(i = 0; i < 8; i++)
	{
		for(z = 0; z < 8; z++)
		{
			board[i][z] = 0;
		}
	}
}

inline void knight::nextmove()
{ 
	int smallest = 100;
	int choice = -1;

	for(i = 0; i < 8; i++)
	{
		int row,col;
		row = pos.row;
		col = pos.col;
		row += horizontal[i];
		col += vertical[i];
		if(row >= 0 && row < 8 && col >= 0 && col < 8 && board[row][col] == 0)
		{
			if(htable[row][col] < smallest && htable[row][col] != 0)
			{
				smallest = htable[row][col];
				choice = i;
			}
		}
	}

	if(choice != -1)
	{
		board[pos.row][pos.col] = 1;
	 	pos.row += horizontal[choice];
		pos.col += vertical[choice];
		moves++;
		if(moves == 63) 
		{
			moves++;
			board[pos.row][pos.col] = 1;
		}
	}
	
}
