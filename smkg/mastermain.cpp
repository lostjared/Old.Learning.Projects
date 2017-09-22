// masterkong
// written by jared bruni
// www.lostsidedead.com

// Open Source Open Mind

#include "thehead.h"

Player player;

MasterXHWND mxhwnd;

Intro intro;
Start start;
Game  game;
Options opt;
GameOver gameover;
About about;
GIntro gintro;
LevelMap level;
SoundHandle soundhandle;
ParticleHandler hparticle;

int XSTD MasterMain(HINSTANCE hInst,LPSTR line)
{

	srand(time(NULL));

	if(mxhwnd.CreateMasterX("MasterKong",640,480,COLOR_DEFAULT,MasterProc,hInst,LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1)),NULL))
	{
		mxhwnd.InitTimer(1,1);
		mxhwnd.HideCursor();
		mxhwnd.SetScreen(ID_INTRO);
		intro.load();
		start.load();
		game.load();
		opt.load();
		about.load();
		gameover.load();
		gintro.load();
		soundhandle.load();
		hparticle.load();
		loadlevel("demo.mxk");
		soundhandle.Play(OPEN);
		return mxhwnd.InitLoop(update);
	}

	return 0;
}


long XSTD MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
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
			if(wParam == VK_ESCAPE)
			{
				mxhwnd.Kill();
			} else
			{
				switch(mxhwnd.GetScreen())
				{
				case ID_START:
					start.keypress(wParam);
					break;
				case ID_ABOUT:
					about.keypress(wParam);
					break;
				case ID_OPTIONS:
					opt.keypress(wParam);
					break;
				case ID_GINTRO:
					gintro.keypress(wParam);
					break;
				case ID_GAME:
					game.hero.keypress(wParam);
					break;
				case ID_GAMEOVER:
					gameover.keypress(wParam);
					break;
				}
			}
			
		}
		break;
	case WM_KEYUP:
		{
			switch(mxhwnd.GetScreen())
			{
			case ID_GAME:
				game.hero.keyrelease(wParam);
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
	case ID_GAMEOVER:
		gameover.update();
		break;
	case ID_OPTIONS:
		opt.update();
		break;
	case ID_ABOUT:
		about.update();
		break;
	case ID_GINTRO:
		gintro.update();
		break;
	}

}

// load the level
void loadlevel(char* levelstr)
{
	ifstream fin(levelstr,ios::binary);
	fin.read((char*)&level,sizeof(level));
	fin.close();

	game.hero.hero_pos = level.hsp;
	game.grandma.pos = level.gsp;
	game.grandma.spos = level.gsp;
	game.hero.start_pos = level.hsp;

	game.grandma.birth();

}

// how many rows over
int rows(int row)
{
	return (row*24);
}

Hero* GetHero()
{
	return (Hero*)&game.hero;
}

Grandma* GetGrandma()
{
	return (Grandma*)&game.grandma;
}

MasterJoyStick* getstick()
{
	return (MasterJoyStick*)&game.stick;
}

void thegameover(bool win)
{
	mxhwnd.SetScreen(ID_GAMEOVER);
	gameover.passgameover(win);
}

/*************************************************************************** lostsidedead.com */