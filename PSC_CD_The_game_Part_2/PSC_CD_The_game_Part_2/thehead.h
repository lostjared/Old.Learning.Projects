/* PSC CD The Game 2 
written by Jared Bruni
www.LostSideDead.com
head 

*/


/* free -> style */

#define MASTERXSDK
#define Sync if(mxhwnd.SyncChange()) 
#include "masterx.h"

extern MasterXHWND mxhwnd;
 
enum { ID_INTRO , ID_GAME, ID_OVER };

const int MAX = 500;
unsigned long final_score = 0;
int final_hits = 0;

class MasterProgram : public MasterGameObject {
	
	
public:
	
	virtual void load()
	{
		intro.load();
		game.load();
		over.load();
	}
	
	
	virtual void update()
	{
		switch(mxhwnd.GetScreen())
		{
		case ID_INTRO:
			intro.update();
			break;
		case ID_GAME:
			game.update();
			break;
		case ID_OVER:
			over.update();
			break;
		}
	}
	
	
private:
	
	class MasterIntro : public MasterGameObject  {
		
	public:
		
		virtual void load()
		{
			mxhwnd.LoadGraphic(&logo,"logo.bmp");
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
			logo.DisplayGraphic(0,0);
		}
		
		inline void logic()
		{
			static t_count = 0;
			if( ++t_count > 25 )
			{
				mxhwnd.SetScreen(ID_GAME);
				t_count = 0;
			}
		}
		
		
	private:
		
		MasterGraphic logo;
		
		
		
		
	};
	
	MasterIntro intro;
	
	class MasterGame : public MasterGameObject {
		
	public:
		
		virtual void load()
		{
			mxhwnd.LoadGraphic(&gamelogo,"game.bmp");
			emiter.load();
		}
		
		virtual void update()
		{
			gamelogo.DisplayGraphic(0,0);
			emiter.update();
			draw();
			Sync
			{
				logic();
			}
		}
		
	private:
		
		MasterGraphic gamelogo;
		
		inline void draw()
		{
			mxhwnd.paint.mxdrawrect(0,0,640,30,RGB(150,150,150),RGB(150,150,150));
			mxhwnd.text.setbkcolor(RGB(150,150,150));
			mxhwnd.text.settextcolor(RGB(200,0,0));
			mxhwnd.text.sprinttext(10,10," PSC CD The Game 2 - Score (%i) - Hits (%i) - Lives (%i)",emiter.score,emiter.hits,emiter.lives);
		}
		
		inline void logic()
		{
			
		}
		
		class ParticleEmiter : public MasterGameObject {
			
		public:
			unsigned long score;
			int hits;
			int lives;

			
			
			virtual void load()
			{
				coin.SetColorKey(RGB(255,255,255));
				cd.SetColorKey(RGB(255,0,255));
				mxhwnd.LoadGraphic(&coin,"coin.bmp");
				mxhwnd.LoadGraphic(&cd,"cd.bmp");
			    score = 0;
				hits = 0;
				lives = 10;
				cannon.load();
			}
			
			virtual void update()
			{
				cannon.update();
				draw();
				Sync
				{
					logic();
				}
				
			}
			
		private:
			
			int loop;
			
			inline void logic()
			{
				if(mxhwnd.KeyCheck(DIK_SPACE))
				{
					int off;
					off = getoffparticle();
					if(off != -1)
					{
						particles[off].type = 1;
						particles[off].x = cannon.getx() + 40;
						particles[off].y = 400;
						particles[off].dir = 1;
						particles[off].speed = 10;
					}
				}
				
				proc();
				
				static int r_count = 0;
				if( ++r_count > 10 )
				{
					int off = getoffparticle();
					if(off != -1)
					{
						particles[off].type = 2;
						particles[off].x = rand()%640-32;
						particles[off].y = 50;
						particles[off].speed = randspeed();
						
					}
					
					r_count = 0;
				}
			}
			
			inline int randspeed()
			{
				int val = 0;
				do
				{
					val = rand()%10;
				}while(val <= 3);
				
				return val;
			}
			
			inline void proc()
			{
				for(loop = 0; loop <= MAX; loop++)
				{
					if(particles[loop].type == 1)
					{
						particles[loop].y -= particles[loop].speed;
						if(particles[loop].y <= 30)
						{
							particles[loop].kill();
						}
						else
						{
							detectproc(loop);
						}
					}
					else if(particles[loop].type == 2)
					{
						particles[loop].y += particles[loop].speed;
						if(particles[loop].y > 480-cd.h)
						{
							particles[loop].kill();
							lives--;
							if(lives < 0)
							{
								final_score = score;
								final_hits = hits;
								mxhwnd.SetScreen(ID_OVER);
							}
						}
					}
				}
			}
			
			inline void draw()
			{
				for(loop = 0; loop <= MAX; loop++)
				{
					if( particles[loop].type == 1 )
					{
						coin.DisplayGraphic(particles[loop].x,particles[loop].y);
					}
					else if(particles[loop].type == 2)
					{
						cd.DisplayGraphic(particles[loop].x,particles[loop].y);
					}
				}
				
			}
			
			inline int getoffparticle()
			{
				for(loop = 0; loop <= MAX; loop++)
				{
					
					if(particles[loop].type == 0)
					{
						return loop;
					}
				}
				
				
				return -1;
			}
			
			inline void detectproc(int i)
			{
				
				int x1;
				int x2;
				int y1;
				int y2;
				x1 = particles[i].x;
				y1 = particles[i].y;
				
				
				for(int p = 0; p <= MAX; p++)
				{
					if(p != i && particles[p].type == 2)
					{
						// ok its a CD
						// lets see if im clipping it
						x2 = particles[p].x;
						y2 = particles[p].y;
						
						if(x1 >= x2 && x1 <= x2 + 106 && y1 >= y2 && y1 <= y2 + 82)
						{
						
						    particles[i].kill();
							particles[p].kill();
							score += 3;
							hits++;
							
							return;
						}
						
					}
				}
			}
			
			struct Particle 
			{
				int dir; // direction
				int  type; // ethier coin, or cd
				int  speed; // speed of the particle
				int  x;
				int  y;
				
				inline Particle()
				{
					kill();
				}
				
				inline void kill()
				{
					dir = 0;
					type = 0;
					speed = 0;
				}
			};
			
			Particle particles[MAX];
			
			class Cannon : public MasterGameObject {
				
			public:
				
				virtual void load()
				{
					x = 640/2-100;
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
				
				
			private:
				
				int x;
				
				
				
				inline void draw()
				{
					mxhwnd.paint.mxdrawrect(x,470,x+100,480,RGB(0,0,255),RGB(0,0,255));
					mxhwnd.paint.mxdrawrect(x+10,460,x+90,470,RGB(0,0,240),RGB(0,0,240));
					mxhwnd.paint.mxdrawrect(x+20,450,x+80,460,RGB(0,0,230),RGB(0,0,230));
					mxhwnd.paint.mxdrawrect(x+30,440,x+70,450,RGB(150,150,150),RGB(150,150,150));
				}
				
				inline void logic()
				{
					if(mxhwnd.KeyCheck(DIK_LEFT))
					{
						if(x > 0)
						{
							x -= 10;
						}
					}
					
					if(mxhwnd.KeyCheck(DIK_RIGHT))
					{
						if(x < 640-100)
						{
							x += 10;
						}
					}
				}
				
				
			};
			
			Cannon cannon;
			MasterGraphic coin;
			MasterGraphic cd;
			
			
		};
		
		ParticleEmiter emiter;
		
		
	};
	
	MasterGame game;
	
	
	class MasterGameOver : public MasterGameObject {
		
	public:

		HFONT nFont;
		HFONT rFont;
		
		virtual void load()
		{
			nFont = MakeFont("Arial",35);
			rFont = MakeFont("Verdana",12);
		}
		
		virtual void update()
		{
			mxhwnd.paint.mxdrawrect(0,0,640,480,RGB(150,150,150),RGB(150,150,150));
			mxhwnd.paint.mxdrawrect(0,0,640,25,RGB(0,0,200),RGB(0,0,200));
			mxhwnd.text.setfont(rFont);
			mxhwnd.text.setbkcolor(RGB(0,0,200));
			mxhwnd.text.settextcolor(RGB(0,0,0));
			mxhwnd.text.sprinttext(5,5," Final Score (%i) - CD Kills (%i)",final_score,final_hits);
			mxhwnd.text.setbkcolor(RGB(150,150,150));
			mxhwnd.text.settextcolor(RGB(255,0,0));
			mxhwnd.text.setfont(nFont);
			mxhwnd.text.printtext("Game Over press enter to exit",100,480/2-20);

			if(mxhwnd.KeyCheck(DIK_RETURN))
			{
				mxhwnd.Kill();
			}
		}
		
	};
	
	MasterGameOver over;
	
	
};