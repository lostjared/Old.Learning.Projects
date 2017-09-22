// main header file
// written by jared bruni
// for masterparticle
// www.lostsidedead.com

#include "masterx.h"
#include <time.h>
#include <stdio.h>

#define pmax 120

enum { ID_INTRO = 1, ID_PARTICLE };

extern MasterXHWND mxhwnd;

long XSTD MasterProc(HWND,UINT,WPARAM,LPARAM);
void update(MASTERSCREEN screen);

// introduction game object
class MasterIntro
{
public:
	void load();
	void update();
private:
	HFONT mfonts[10];
	int font_index;
	bool font_dir;
	int fade_color;

};

// enumerated constants for particle state
enum PARTICLESTATE { ACTIVE ,DEAD };

// Particle structure
struct Particle
{
	int x;
	int y;
	int size;
	PARTICLESTATE state;
	MASTERCOLOR color;

	// inline constructor
	inline Particle()
	{
		x = 0;
		y = 0;
		state = DEAD;
		color = 0;
		size = 0;
	}
};
 

// MasterParticle class
class MasterParticle
{
public:
	void load();
	void update();
	void initparticles(int speed, int wind);
	void releaseparticle(int x, int y,int size,MASTERCOLOR color);
	void setoffparticle();
	void draw();
	void drawstats();
	void procparticles();
	int  getoffparticle();
	void keycheck();
private:
	Particle particles[pmax];
	int wind;
	int speed;
	int wind_count;
};