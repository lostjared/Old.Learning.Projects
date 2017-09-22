// the main source module
// written by jared bruni
// www.lostsidedead.com

#include "thehead.h"

MasterXHWND mxhwnd;
HFONT mainfont = MakeFont("Arial",14);
Game gameobj;
Intro introobj;
LevelStructure level;// level structure
int pre_time = 0;
int timer_count = 0;



// main program entry point
int _stdcall MasterMain(HINSTANCE hInst,LPSTR line)
{
	loadmap("demo.mrpg");

	if(mxhwnd.CreateMasterX("MasterRPG",800,600,COLOR_DEFAULT,MasterProc,hInst,LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1)),NULL))
	{
		// load graphics/sound/initilize objects
		introobj.load();
		gameobj.load();


#ifndef WIN2K

		mxhwnd.InitTimer(1,1);
#else
		mxhwnd.InitTimer(1,50);
#endif

		mxhwnd.HideCursor();
		mxhwnd.SetScreen(ID_INTRO);
		char vi[100];
		strcpy(vi,"Master RPG Version ");
		strcat(vi,VER);
		mprint(vi,RGB(200,200,200));
		mprint("now successfully loaded",RGB(200,200,200));
		mprint("written by Jared Bruni",RGB(200,200,200));
		mprint("www.lostsidedead.com",RGB(200,200,200));
		return mxhwnd.InitLoop(update);
	}

	return 0;
}

// master message proccess 
long _stdcall MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		{
#ifdef iDEBUG
			if(wParam == VK_ESCAPE)
			{
				mxhwnd.Kill();
			}
#endif
			keypress(wParam);
		}
		break;
	case WM_KEYUP:
		{
			switch(mxhwnd.GetScreen())
			{
			case ID_GAME:
				{
					gameobj.hero.keyup(wParam);
				}
				break;
			}
		}
		break;
	case WM_ACTIVATEAPP:
		{
			mxhwnd.activeapp = wParam;
		}
		break;
	// to keep the player movement speeds insync
	case WM_TIMER:
		{
			timer_count++;

			if(timer_count > 100)
			{
				timer_count = 0;
			}
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}


// update callback function
void update(MASTERSCREEN screen)
{

	switch(screen)
	{
	case ID_GAME:
		gameobj.update();
		break;
	case ID_INTRO:
		introobj.update();
		break;
	}

#ifdef iDEBUG
	mxhwnd.text.settextcolor(RGB(200,0,0));
	mxhwnd.text.setfont(mainfont);
	mxhwnd.text.printtext("Currently Running in Debug Mode, Press Escape to Exit",10,10);
#endif
}
// key press
void keypress(WPARAM wParam)
{
	switch(mxhwnd.GetScreen())
	{
	case ID_GAME:
		gameobj.keypress(wParam);
		break;
	}
}

//************************* MISC MAIN FUNCTIONS **************************************************/
// load up a map
void loadmap(char* filename)
{
	ZeroMemory(&level,sizeof(level)); // clear level structure
	ifstream fin(filename,ios::binary);
	fin.read((char*)&level,sizeof(level));
	fin.close();
}
// has time changed?
bool TimeChange()
{
	if(pre_time == timer_count)
	{
	return false;
	}
	else
	{
		pre_time = timer_count;
		return true;
	}
}

// mprint
void mprint(char* buffer,COLORREF color)
{
	gameobj.console.printtext(buffer,color);
}