// masterparticle
// written by jared bruni
// www.lostsidedead.com

#include "thehead.h"


// initilize the particles
void MasterParticle::initparticles(int speedx,int windx)
{
	speed = speedx;
	wind = windx;
}

// load 
void MasterParticle::load()
{
	initparticles(10,0);

	for(int i = 0; i <= pmax; i++)
	{
		releaseparticle(rand()%640,rand()%480,rand()%10,0xFFFFFF);
	}
}

// release a new particle
void MasterParticle::releaseparticle(int x, int y,int size, MASTERCOLOR color)
{
	int offp = getoffparticle();

	if(offp == -1) 
	{
		return;// no open particles
	}

	particles[offp].x = x;
	particles[offp].y = y;
	particles[offp].color = color;
	particles[offp].state = ACTIVE;
	particles[offp].size = size;

}


// update
void MasterParticle::update()
{
	draw();
	if(mxhwnd.SyncChange())
	{
		procparticles();
		keycheck();
	}
	drawstats();
}

// draw particles
void MasterParticle::draw()
{
	for(int i = 0; i < pmax; i++)
	{
		// active particle
		if(particles[i].state != DEAD)
		{
			if(particles[i].state == ACTIVE)
			{
				// draw the particle
				mxhwnd.paint.mxdrawellipse(particles[i].x,particles[i].y,particles[i].x + particles[i].size,particles[i].y + particles[i].size,particles[i].color,particles[i].color);
			}
		}
	}
}
// proccess the active particles
void MasterParticle::procparticles()
{
	for(int i = 0; i < pmax; i++)
	{
		// active particle
		if(particles[i].state != DEAD)
		{
			if(particles[i].state == ACTIVE)
			{
				if(particles[i].x > 640 || particles[i].y > 480)
				{
					particles[i].state = DEAD;
					setoffparticle();
					continue;
				}
				else
				{

					particles[i].x += wind;
					particles[i].y += speed;
				}
		
			}
	
		}
	}
}

// set off praticle
void MasterParticle::setoffparticle()
{
	releaseparticle(rand()%640,0,rand()%10,0xFFFFFF);
}

// get a turned off particle
int MasterParticle::getoffparticle()
{
	int offp = -1;

	for(int i = 0; i <= pmax; i++)
	{
		if(particles[i].state == DEAD)
		{
			offp = i;
			break;
		}
	}

	return offp;
}
// keycheck
void MasterParticle::keycheck()
{
	if(mxhwnd.KeyCheck(DIK_LEFT))
	{
		wind -= 1;
	}
	if(mxhwnd.KeyCheck(DIK_RIGHT))
	{
		wind += 1;
	}
	if(mxhwnd.KeyCheck(DIK_UP))
	{
		if(speed > 1)
		{
			speed -= 1;
		}
	}
	if(mxhwnd.KeyCheck(DIK_DOWN))
	{
		speed += 1;
	}
}

// draw the stats, information about wind and speed
void MasterParticle::drawstats()
{
	char wstr[50];
	char sstr[50];

	sprintf(wstr,"Wind: %i",wind);
	sprintf(sstr,"Speed: %i",speed);

	mxhwnd.text.setbkcolor(0);
	mxhwnd.text.settextcolor(0xFF0000);
	mxhwnd.text.printtext(wstr,10,25);
	mxhwnd.text.printtext(sstr,10,40);
	mxhwnd.text.printtext("use the left and right arrows to toggle wind, and up and down to toggle speed",10,55);
}
