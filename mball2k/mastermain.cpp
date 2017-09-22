// master ballgame
// written by jared bruni
// www.lostsidedead.com

#include "thehead.h"


MasterXHWND   mxhwnd;// masterX hwnd object
HFONT mfont = MakeFont("Arial",14); // font
MasterGraphic introg; // intro graphic
MasterGraphic gameg; // game graphic
MasterGraphic startg; // start graphic
BallPlayer    player;
MasterJoyStick stick;
MasterSound   opens;
MasterSound   boings;


// load graphics
void loadgraphics();
// load sound
void loadsound();

// mastermain
int XSTD MasterMain(HINSTANCE hInst,LPSTR line)
{
	srand(time(NULL));

	// init masterX
	if(mxhwnd.CreateMasterX("MasterBallGame",640,480,COLOR_DEFAULT,MasterProc,hInst,LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1)),NULL))
	{
		loadgraphics();
		loadsound();
		bool init_joy = stick.SetupJoystick();
		if(init_joy == false)
		{
			player.nojoystick = true;
			player.joystick_on = false;
		}
		else
		{
			player.nojoystick = false;
			player.joystick_on = false;
		}
		player.lives = 5;
		player.difficulty = 3;

		mxhwnd.SetScreen(ID_INTRO);
		mxhwnd.HideCursor();


#ifdef WIN2K
		mxhwnd.InitTimer(1,3);
#else
		mxhwnd.InitTimer(1,60);
#endif

		playgamesound(0);
		return mxhwnd.InitLoop(update);
	}
	
	return 0;
}

// load up the graphics
void loadgraphics()
{
	mxhwnd.LoadGraphic(&introg,"intro.bmp");
	mxhwnd.LoadGraphic(&startg,"start.bmp");
	mxhwnd.LoadGraphic(&gameg,"game.bmp");
}
// load up the sounds
void loadsound()
{
	mxhwnd.LoadSound(&opens,MAKEINTRESOURCE(IDR_WAVE1));
	mxhwnd.LoadSound(&boings,MAKEINTRESOURCE(IDR_WAVE2));
}

// masterproc callback proccess
long XSTD MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_ACTIVATEAPP:
		mxhwnd.activeapp = wParam; 
		break; 
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		{
			switch(mxhwnd.GetScreen())
			{
			case ID_START:
				{
					start_keypress(wParam);
				}
				break;
			case ID_OPTIONS:
				{
					options_keypress(wParam);
				}
				break;
			case ID_GAMEOVER:
				{
					gameover_keypress(wParam);
				}
				break;
			}
			
			switch(wParam)
			{
			case VK_ESCAPE:
				{
					
#ifdef iDEBUG
					mxhwnd.Kill();
					
#endif
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


// update
void update(MASTERSCREEN screen)
{
	mxhwnd.SetTimeFlag();
	switch(screen)
	{
	case ID_INTRO:
		intro_update();
		break;
	case ID_START:
		start_update();
		break;
	case ID_OPTIONS:
		options_update();
		break;
	case ID_GAME:
		game_update();
		break;
	case ID_GAMEOVER:
		gameover_update();
		break;
	}
	
#ifdef iDEBUG
	mxhwnd.text.settextcolor(0xFF0000);
	mxhwnd.text.setbkcolor(0x000000);
	mxhwnd.text.setfont(mfont);
//	mxhwnd.text.printtext("Currently running in debug mode press escape to exit",10,10);
	
#endif
	
}

// draw a sprite
void drawsprite(int x, int y, int sprite)
{
	switch(sprite)
	{
	case 0:
		introg.DisplayGraphic(x,y);
		break;
	case 1:
		startg.DisplayGraphic(x,y);
		break;
	case 2:
		gameg.DisplayGraphic(x,y);
		break;
	}
}
// playgamesound
void playgamesound(int sound)
{
	switch(sound)
	{
	case 0:
		opens.Play();
		break;
	case 1:
		boings.Play();
		break;
	}
}

