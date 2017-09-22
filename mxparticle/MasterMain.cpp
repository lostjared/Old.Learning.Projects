#define MASTERXSDK
#include"masterlibrary4.h"
#define Sync if(mxhwnd.SyncChange())

long _stdcall event(struct HWND__* hwnd, unsigned int msg, unsigned int wparam, long lparam);
void render(int screen);
inline void load();

const int MAX_PARTICLE = 1000;

MasterXHWND mxhwnd;

struct Particle {
	int x;
	int y;
	int width;
	bool on;
};

class ParticleEmiter : public MasterGameObject {

public:

	virtual void load()
	{
		for(i = 0; i < MAX_PARTICLE; i++)
		{
			particles[i].x = 0;
			particles[i].y = 0;
			particles[i].width = 0;
			particles[i].on = false;
		}
	}

	virtual void update()
	{
		draw();
		Sync
		{
			logic();
		}
	}

	inline void draw()
	{
		for(i = 0; i < MAX_PARTICLE; i++)
		{
			if(particles[i].on == true)
			{
				mxhwnd.paint.mxdrawellipse(particles[i].x,particles[i].y,particles[i].x+particles[i].width+2,particles[i].y+particles[i].width+2,RGB(255,255,255),RGB(255,255,255));
			}
		}
	}

	inline void logic()
	{
		static int st = 0;
		if( ++st > 4 )
		{
			releaseparticle();
			st = 0;
		}

		for(i = 0; i < MAX_PARTICLE; i++)
		{
			if(particles[i].on == true)
			{
				particles[i].y += 5;

				if(particles[i].y > 480)
				{
					particles[i].on = false;
				}
			}
		}
	}

private:

	Particle particles[MAX_PARTICLE];
	int i;

	inline void releaseparticle()
	{
		int off = getoffparticle();
		if(off != -1)
		{
			particles[off].x = rand()%640;
			particles[off].y = 0;
			particles[off].width = rand()%5;
			particles[off].on = true;
		}
	}

	int getoffparticle()
	{
		for(i = 0; i < MAX_PARTICLE; i++)
		{
			if(particles[i].on == false)
			{
				return i;
			}
		}

		return -1;
	}

};

ParticleEmiter emiter;

int _stdcall MasterMain(struct HINSTANCE__* hInst, char* line)
{
	if(mxhwnd.CreateMasterX("MasterX",640,480,COLOR_DEFAULT,event,hInst,NULL,NULL))
	{
		load();
		return mxhwnd.InitLoop(render);
	}

	return (0);
}

inline void load()
{
	mxhwnd.HideCursor();
	mxhwnd.InitTimer(1,1);
	emiter.load();
}

long _stdcall event(struct HWND__* hwnd, unsigned int msg, unsigned int wparam, long lparam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ACTIVATEAPP:
		mxhwnd.activeapp = wparam;
		break;
	case WM_KEYDOWN:
		if(wparam == VK_ESCAPE)
		{
			mxhwnd.Kill();
		}
		break;
	case WM_TIMER:
		{
			mxhwnd.ChangeTime();
		}
		break;
	default: return DefWindowProc(hwnd,msg,wparam,lparam);
	}

	return (0);
}

void render(int screen)
{
	mxhwnd.SetTimeFlag();
	emiter.update();

}

