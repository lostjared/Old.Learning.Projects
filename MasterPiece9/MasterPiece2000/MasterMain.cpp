/*

  MasterPiece written utilizing MasterX SDK
  written by Jared Bruni


  www.lostsidedead.com



  Open Source, Open Mind


  "I am only as I think and believe"


*/


#include "thehead.h"
#include <time.h>
 
MasterXHWND mxhwnd; // masterxhwnd
Intro intro;
Start start;
Game  game;
Scores scores;
HFONT mfonts[mfsize];
gOp Options;
Scores fscores;
//function prototypes
void onload();
unsigned long user_score = 100;
SoundHandler shandle;
// master main entry point
int XSTD MasterMain(HINSTANCE hInst,LPSTR line)
{
	mxhwnd.setfullflag(false);
	srand(time(NULL));
	loadscore();
	if(mxhwnd.CreateMasterX("MasterPeiece",640,480,COLOR_DEFAULT,MasterProc,GetModuleHandle(NULL),NULL,NULL))
	{
		onload();
		shandle.sounds[0].Play();
 		return mxhwnd.InitLoop(update);
	}

	return 0;
}

// on load, initilization function
void onload()
{

	// load up the font table
	mfonts[0] = MakeFont("Verdana",14);
	mfonts[1] = MakeFont("Verdana",20);
	mxhwnd.HideCursor();
	intro.load();
	start.load();
	game.load();
	shandle.load();

	// possibly read in timer speed, to set the timer on
	
#ifndef WIN2K
	mxhwnd.InitTimer(1,2);
#else
	mxhwnd.InitTimer(1,50);
#endif

	mxhwnd.SetScreen(ID_INTRO);

}


// masterproc callback function
long XSTD MasterProc(HWND hwnd,UINT msg,WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		savescore();
		PostQuitMessage(0);
		break;
	case WM_ACTIVATEAPP:
		__mxhwnd.active = wParam;
		break;
	case WM_KEYDOWN:
		{
			if(wParam == VK_ESCAPE) { mxhwnd.Kill(); }

			switch(mxhwnd.GetScreen())
			{
			case ID_START:
				{
					start.keypress(wParam);
				}
				break;
			case ID_GAME:
				{
					game.keypress(wParam);
				}
				break;
			}

		}
		break;
	case WM_TIMER:
		{
			mxhwnd.ChangeTime();
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

/*

  update callback function, this sends the flow of instruction down the right path
*/

void update(MASTERSCREEN screen)
{
	mxhwnd.SetTimeFlag();
	switch(screen)
	{
	case ID_INTRO:
		intro.update();
		break;
	case ID_START:
		start.update();
		break;
	case ID_GAME:
		game.update();
		break;
	case ID_SCORES:
 		break;
	}
}

void newgame()
{
	game.matrix.init_matrix();
}


void gameover()
{
	start.off_pos = 0;
	start.scr_username[0] = '_';
	start.scr_username[1] = 0;

	user_score = game.matrix.Game.score;
	start.sub_screen = IDS_SCORE;
	mxhwnd.SetScreen(ID_START);
}

void blocksound()
{

}


void getcords(int r, int c, int& rx, int& ry)
{

	int STARTPOSX = STARTX;
    int STARTPOSY = STARTY;
    int x = STARTPOSX,y = STARTPOSY;

	for(int i = 0; i < 17; i++)
	{


		for(int j = 0; j < 8; j++)
		{
     
			if(r == i && c == j)
			{
				rx = x;
				ry = y;
				return;
			}

       		x = x + 32;

		}
          x = STARTPOSX;
		  y = y + 16;
		// down lower
	}

	rx = -1;
	ry = -1;

}