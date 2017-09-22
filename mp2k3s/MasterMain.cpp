/*

  MasterPeice written utilizing MasterX SDK
  written by Jared Bruni


  www.LostSideDead.com

  Open Source, Open Mind
 
 "I am only as I think and believe"

 a beautiful MasterPeace

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
bool play_the_mp3;
//function prototypes
void onload();
unsigned long user_score = 100;
SoundHandler shandle;
char themp3[255];
// master main entry point
int __stdcall MasterMain(struct HINSTANCE__* hInst,char *line)
{
	srand((unsigned int)time(NULL));
	loadscore();
	if(mxhwnd.CreateMasterX("MasterPeice",640,480,COLOR_DEFAULT,MasterProc,GetModuleHandle(NULL),NULL,NULL))
	{
		onload();
		shandle.sounds[0].Play();
 		return(int)mxhwnd.InitLoop(update);
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
	Options.init_joystick();
	shandle.load();
	mxhwnd.InitTimer(1,50);
	mxhwnd.SetScreen(ID_INTRO);
}


// masterproc callback function
long __stdcall MasterProc(struct HWND__* hwnd,unsigned int msg, unsigned int wParam, long lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		mxhwnd.media.stop();
		mxhwnd.media.close();
		savescore();
		PostQuitMessage(0);
		break;
	case WM_ACTIVATEAPP:
		mxhwnd.activeapp = (unsigned int)wParam;
		break;
	case WM_KEYDOWN:
		{
			if(wParam == VK_ESCAPE) {  mxhwnd.Kill(); }

			switch(mxhwnd.GetScreen())
			{
			case ID_START:
				{
					start.keypress(static_cast<int>(wParam));
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
	default: return (long)DefWindowProc(hwnd,msg,wParam,lParam);
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

void Pause(long seconds)
{
	clock_t delay = seconds * CLOCKS_PER_SEC;
	clock_t start = clock();
	while (clock() - start < delay)
	{
	}
}

int findstr(const char *str , const char *search)
{
	bool add = true;

	for(size_t i = 0; i < strlen(str); i++)
	{
		if(str[i] == search[0])
		{
			add = true;

			for(size_t z = 0; z < strlen(search) && i + z < strlen(str); z++)
			{
				if(str[i+z] != search[z])
				{
					add = false;
				}
			}

			if(add == true)
			{
				return (int) i;
			}
		}
	}
	return (-1);
}

void midcopy(const char *str, char *output, size_t start, size_t stop)
{
	size_t pos = 0;

	for(size_t i = start; i < stop; i++)
	{
		output[pos] = str[i];
		pos++;
	}

	output[pos] = 0;
}
