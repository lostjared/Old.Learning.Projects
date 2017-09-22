// psc cd - the game
// written by jared bruni
// www.lostsidedead.com

#include "masterx.h"


extern MasterXHWND mxhwnd;

void update(MASTERSCREEN);
long XSTD MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);

 

enum { ID_INTRO, ID_GAME, ID_OVER };
enum { ID_LOGO = 3, ID_START };


struct Player
{
	int lives;
	int score;
	int kills;

	inline Player()
	{
		lives = 0;
		score = 0;
		kills = 0;
	}

	inline void newgame()
	{
		lives = 5;
		score = 0;
		kills = 0;
	}

	inline void hit()
	{
		kills = kills + 1;
		score = score + 3;
	}
};

extern Player player;

class Intro : public MasterGameObject
{
public:

	MASTERSCREEN screen;

	virtual void load()
	{
		mxhwnd.LoadGraphic(&intrologo,"intro.bmp");
		mxhwnd.LoadGraphic(&startlogo,"start.bmp");
		screen = ID_LOGO;
	}

	virtual void update()
	{
		ondraw();
		if(mxhwnd.SyncChange())
		{
			onlogic();
		}
	}

	void ondraw();
	void onlogic();
	void keypress(WPARAM);


private:

	MasterGraphic intrologo;
	MasterGraphic startlogo;
	int logo_count;

};

const int MAX_PARTICLE = 150;


enum psctype { CD, BALL };


struct PSCParticle
{
	int x;
	int y;
	int speed;
	psctype ptype;
	bool on;

	inline PSCParticle()
	{
		x = 0;
		y = 0;
		speed = 0;
		on = false;
		ptype = CD;
	}
};

//Particles emiter
class PSCParticleEmiter : public MasterGameObject
{
public:

	PSCParticle particles[MAX_PARTICLE];


	virtual void load()
	{
		mxhwnd.LoadGraphic(&psc_cd,"cd.bmp");
		psc_cd.SetColorKey(RGB(255,0,255));
	}

	virtual void update()
	{
		ondraw();
		if(mxhwnd.SyncChange())
		{
			onlogic();
		}
	}

	void releaseparticle(  int x, int y, int speed, psctype ptype);
	void killparticle(int index);
	void DetectProc(int i);


private:

	int getoffparticle();
	void ondraw();
	void onlogic();

	MasterGraphic psc_cd;




};

extern PSCParticleEmiter pscemiter;

class Cannon : public MasterGameObject
{
public:

	int x;
	int release_count;

	virtual void load()
	{
		x = 100;
		release_count = 0;
	}

	virtual void update()
	{
		ondraw();
		if(mxhwnd.SyncChange())
		{
			onlogic();
		}
	}

	void ondraw();
	void onlogic();
	void keypress(WPARAM wParam);



private:

};

extern Cannon cannon;


class Game: public MasterGameObject
{
public:
	virtual void load()
	{
		wrc = 25;
	}

	virtual void update()
	{
		ondraw();
		if(mxhwnd.SyncChange())
		{
			onlogic();
		}
		pscemiter.update();
		cannon.update();
	}

	void ondraw();
	void onlogic();


private:

	int wrc;


};



class Over: public MasterGameObject
{
public:
	virtual void load()
	{

	}

	virtual void update()
	{
		ondraw();
		if(mxhwnd.SyncChange())
		{
			onlogic();
		}
	}

	void ondraw();
	void onlogic();
	void keypress(WPARAM wParam);

private:


};