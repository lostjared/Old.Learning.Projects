/* Simple Particle Engine
   Taking a more slanted structured hybrid Approach
   written by Jared Bruni
   www.LostSideDead.com

  "Open Source, Open Mind"
*/



#define Sync if(mxhwnd.SyncChange()) 
#define MASTERXSDK
#include "masterlibrary2.h"
#include<time.h>
#define MAX_PARTICLE 700

MasterXHWND mxhwnd;
long _stdcall event(struct HWND__* hwnd,unsigned int msg,unsigned int wParam,long lParam);
void render(MASTERSCREEN screen);
inline void init();
 
namespace master
{

const int NADA = -1;
int i;

struct Particle
{
	int x;
	int y;
	int type;

	inline Particle()
	{
		x = 0;
		y = 0;
		type = NADA;
	}
};

inline void draw();
inline void logic();
inline void init();
inline int getoffparticle();
inline void releaseparticle();
inline void procparticles();

MasterGraphic sprites[3];
Particle particles[MAX_PARTICLE];

}

 

int _stdcall MasterMain(struct HINSTANCE__* hInst, char* line) 
{
	if(mxhwnd.CreateMasterX("MasterX",640,480,COLOR_DEFAULT,event,hInst,NULL,NULL))
	{
		master::init();
		return mxhwnd.InitLoop(render);
	}

	return (0);
}

inline void master::init()
{
	srand(time(NULL));
	mxhwnd.HideCursor();
	mxhwnd.InitTimer(1,1);
	mxhwnd.LoadGraphic(&sprites[0],"particle1.bmp");
	mxhwnd.LoadGraphic(&sprites[1],"particle2.bmp");
	mxhwnd.LoadGraphic(&sprites[2],"particle3.bmp");
	sprites[0].SetColorKey(RGB(0,0,0));
	sprites[1].SetColorKey(RGB(0,0,0));
	sprites[2].SetColorKey(RGB(0,0,0));
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
	master::draw();
	Sync
	{
		master::logic();
	}
	 
}

inline void master::draw()
{
	
	for(i = 0; i < MAX_PARTICLE; i++)
	{
		
		if(particles[i].type != NADA)
		{
			sprites[particles[i].type].DisplayGraphic(particles[i].x,particles[i].y);
		}
	}
}

inline void master::logic()
{
 		releaseparticle();
 		procparticles();
}

inline int master::getoffparticle()
{
	for(i = 0; i < MAX_PARTICLE; i++)
	{
		if(particles[i].type == NADA)
		{
			return i;
		}
	}

	return -1;
}

inline void master::releaseparticle()
{
	int off;
	off = getoffparticle();
	if(off != -1)
	{
		particles[off].x = rand()%600;
		particles[off].y = 0;
		particles[off].type = rand()%3;
	}
}

inline void master::procparticles()
{
	for(i = 0; i < MAX_PARTICLE; i++)
	{
		if( particles[i].type != NADA )
		{
			particles[i].y += 3;
			if(particles[i].y > 480-sprites[particles[i].type].h-35)
			{
				particles[i].type = NADA;// kill particle
			}
		}
	}
}