/* space war
   written by Jared Bruni
   www.LostSideDead.com
*/

#define MASTERXSDK
#include"masterlibrary2.h"
#define Sync if(mxhwnd.SyncChange())
#define MAX_PARTICLE 500

extern MasterXHWND mxhwnd;


void getshipcord(int& x, int& y);


class Game : public MasterGameObject {


public:

	virtual void load()
	{
		ship.load();
		emiter.load();
	}

	virtual void update()
	{
		ship.update();
		emiter.update();
	}

	int getx()
	{
		return ship.getx();
	}

	int gety()
	{
		return ship.gety();
	}

private:

	class Ship : public MasterGameObject
	{
	public:
		
		virtual void load()
		{
			mxhwnd.LoadGraphic(&imgship,"ship.bmp");
			imgship.SetColorKey(RGB(255,255,255));
			x = 100;
			y = 100;
		}

		virtual void update()
		{
			draw();
			Sync
			{
				logic();
			}
		}

		int getx()
		{
			return x;
		}

		int gety()
		{
			return y;
		}

	private:

		inline void draw()
		{
			imgship.DisplayGraphic(x,y);
		}

		inline void logic()
		{
			if(mxhwnd.KeyCheck(DIK_LEFT))
			{
				if(x > 0)
				{
					x -= 1;
				}
			}

			if(mxhwnd.KeyCheck(DIK_RIGHT))
			{
				if(x < 640-imgship.w-2)
				{
					x += 1;
				}				
			}

			if(mxhwnd.KeyCheck(DIK_UP))
			{
				if(y > 0)
				{
					y -= 1;
				}

			
			}

			if(mxhwnd.KeyCheck(DIK_DOWN))
			{
				if(y < 480-imgship.h-2)
				{
					y += 1;
				}
			
			}
		}

		int x,y;

		MasterGraphic imgship;
	};

 
	Ship ship;

	class ParticleEmiter : public MasterGameObject
	{
	public:

		enum DIR { NADA, LEFT, RIGHT, DOWN, UP };

		virtual void load()
		{
			mxhwnd.LoadGraphic(&shot,"shot.bmp");
			shot.SetColorKey(RGB(255,255,255));
		}

		virtual void update()
		{
			draw();
			Sync 
			{
				logic();
				procparticles();
			}
		}
	private:

		int rx,ry;


		inline void draw()
		{
			for(i = 0; i < MAX_PARTICLE; i++)
			{
				if(particles[i].dir != NADA)
				{
					shot.DisplayGraphic(particles[i].x,particles[i].y);
				}
			}
		}

		inline void procparticles()
		{
			for(i = 0; i < MAX_PARTICLE; i++)
			{
				switch(particles[i].dir)
				{
				case RIGHT:
					{

					particles[i].x += 3;
					if(particles[i].x >= 640-16)
					{
						particles[i].dir = NADA;
					}

					}
					break;
				case LEFT:
					{
						particles[i].x -= 3;
						if( particles[i].x < 0 )
						{
							particles[i].dir = NADA;
						}
					}
					break;
				case DOWN:
					{
						particles[i].y += 3;
						if(particles[i].y > 470)
						{
							particles[i].dir = NADA;
						}
					}
					break;
				case UP:
					{
						particles[i].y -= 3;
						if(particles[i].y < 0)
						{
							particles[i].dir = NADA;
						}
					}
					break;
				}
			}
		}

		inline void logic()
		{
			static int r_off = 0;
			static int t_count = 0;


			if(++t_count > 3)
			{

			if(mxhwnd.KeyCheck(DIK_SPACE))
			{
				r_off = getoffparticle();
				if(r_off == -1) { return; }
				getshipcord(rx,ry);
				particles[r_off].x = rx;
				particles[r_off].y = ry;
				
				if(mxhwnd.KeyCheck(DIK_RIGHT))
				{
					particles[r_off].dir = RIGHT;
					goto over;
				}
				
				if(mxhwnd.KeyCheck(DIK_LEFT))
				{			
					particles[r_off].dir = LEFT;
					goto over;
				}
				
				if(mxhwnd.KeyCheck(DIK_UP))
				{
					particles[r_off].dir = UP;
					goto over;
				}

				if(mxhwnd.KeyCheck(DIK_DOWN))
				{
					particles[r_off].dir = DOWN;
					goto over;
				}

				particles[r_off].dir = RIGHT;
			}

over:

			t_count = 0;
			return;

			}
		}


		int i;

		struct Particle
		{
			int x;
			int y;
			DIR dir;

			inline Particle()
			{
				x = 0;
				y = 0;
				dir = NADA;
			}
		};

		Particle particles[MAX_PARTICLE];
		MasterGraphic shot;

		inline int getoffparticle()
		{
			for(i = 0; i < MAX_PARTICLE; i++)
			{
				if(particles[i].dir == NADA)
				{
					return i;
				}
			}

			return -1;
		}
	};

	ParticleEmiter emiter;

};