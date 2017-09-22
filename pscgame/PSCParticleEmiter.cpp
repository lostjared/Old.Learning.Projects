// PSCParticleEmiter written by Jared Bruni
// www.lostsidedead.com

#include "thehead.h"



int PSCParticleEmiter::getoffparticle()
{
	for(int i = 0; i <= MAX_PARTICLE;i++)
	{
		if(particles[i].on == false)
		{
			return i;
		}
	}

	return -1;
}

void PSCParticleEmiter::releaseparticle(int x, int y, int speed, psctype ptype)
{
	int off;
	off = getoffparticle();
	if(off == -1)
	{
		return;
	}
	particles[off].on = true;
	particles[off].x = x;
	particles[off].y = y;
	particles[off].speed = speed;
	particles[off].ptype = ptype;
}

void PSCParticleEmiter::killparticle(int index)
{
	particles[index].on = false;
	particles[index].speed = 0;
	particles[index].x = 0;
	particles[index].y = 0;
}

void PSCParticleEmiter::ondraw()
{
	for(int i = 0; i <= MAX_PARTICLE;i++)
	{
		if(particles[i].on == true)
		{
			switch(particles[i].ptype)
			{
			case BALL:
				{
			
					mxhwnd.paint.mxdrawellipse( particles[i].x,particles[i].y,particles[i].x + 25,particles[i].y + 25,RGB(rand()%255,rand()%255,rand()%255),RGB(rand()%255,rand()%255,rand()%255));
				}
				break;
			case CD:
				{
					psc_cd.DisplayGraphic(particles[i].x,particles[i].y);

				}
				break;
			}
		}
	}
}

void PSCParticleEmiter::onlogic()
{
	for(int i = 0; i <= MAX_PARTICLE;i++)
	{
		if(particles[i].on == true)
		{
			switch(particles[i].ptype)
			{
			case BALL:
				{
					particles[i].y -= particles[i].speed;
				
					if(particles[i].y <= 0)
					{
						killparticle(i);
					}

					DetectProc(i);

					}
				break;
			case CD:
				{
					particles[i].y += particles[i].speed;

					if(particles[i].y >= 480-psc_cd.h - 5)
					{
						// they loose a life here
						player.lives -= 1;
						killparticle(i);
					}
				}
				break;
			}
		}
	}
}


void PSCParticleEmiter::DetectProc(int i)
{
		int x1;
		int x2;
		int y1;
		int y2;
		x1 = particles[i].x;
		y1 = particles[i].y;
		
						
	for(int p = 0; p <= MAX_PARTICLE; p++)
	{
		if(p != i && particles[p].on == true && particles[p].ptype == CD)
		{
			// ok its a CD
			// lets see if im clipping it
			x2 = particles[p].x;
			y2 = particles[p].y;
			
			if(x1 >= x2 && x1 <= x2 + 106 && y1 >= y2 && y1 <= y2 + 82)
			{
				player.hit();
				killparticle( i );
				killparticle( p );
				return;
			}

		}
	}
}



