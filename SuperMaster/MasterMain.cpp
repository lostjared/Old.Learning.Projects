/* SuperMaster
   written by Jared Bruni
   www.LostSideDead.com

  "Open Source, Open Mind"
*/

#include"thehead.h"// grateful as can be

//#define WIN2K

MasterXHWND mxhwnd;
Intro intro;
Start start;
Game  game;
GameOver over;
Launch launch;

long _stdcall event(struct HWND__* hwnd,unsigned int msg,unsigned int wParam,long lParam);
void render(MASTERSCREEN screen);
inline void init();



int _stdcall MasterMain(struct HINSTANCE__* hInst, char* line) 
{
	if(mxhwnd.CreateMasterX("MasterX",640,480,COLOR_DEFAULT,event,hInst,LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1)),NULL))
	{
		init();
		
		return mxhwnd.InitLoop(render);
	}

	return (0);
}

inline void init()
{
	intro.load();
	start.load();
	game.load();
	over.load();
	launch.load();

	mxhwnd.HideCursor();
#ifndef WIN2K
	mxhwnd.InitTimer(1,1);
#else
	mxhwnd.InitTimer(1,50);
#endif

	mxhwnd.SetScreen(ID_INTRO);
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
			}

			switch(mxhwnd.GetScreen())
			{
			case ID_START:
				start.keypress(wParam);
				break;
			case ID_GAMEOVER:
				{
					over.keypress(wParam);
				}
				break;
			case ID_LAUNCH:
				{
					launch.keypress(wParam);
				}
				break;
			}
		
		}
		break;
	case WM_KEYUP:
		{
			game.keyup(wParam);
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
		over.update();
		break;
	case ID_LAUNCH:
		launch.update();
		break;
	}
	
}

inline void GetPointFromPos(int pos,int& x, int& y)
{
	x = 0;
	y = 0;
	
	static int startby = 75;
	static int bx,by;
	static int i;
	bx = 75; by = startby;
	int gcount = 0;
	
	
	for(i = 0; i < 700-4+24; i++)
	{
		if(i == pos)
		{
			x = bx;
			y = by;
			return;
		}
		
		by = by + 16;
		gcount++;
		if(gcount > 23)
		{
			gcount = 0;
			by = startby;
			bx = bx + 16;
		}
		
	}
}

int getoff_set()
{
	return game.getoffset();
}


void scrollleft()
{
	game.moveleft();
}

void scrollright()
{
	game.moveright();
}

void releaseparticle(int pos, int type,bool dir)
{
	game.emiter.releaseparticle (pos,type,dir);
}

void newgame()
{
	game.resetgame();
	cur_level = 1;

}

void load_level(char* levelstr)
{
	game.loadlevel(levelstr);
}


void setcredits()
{
	mxhwnd.SetScreen(ID_START);
	start.screen = 1;
}