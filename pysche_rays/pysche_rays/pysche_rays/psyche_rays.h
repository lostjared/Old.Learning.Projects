#include "errormsg.h"
#include "mx3d.h"

namespace Pysche {

	double THE_PI = 3.14159265;

	// the direction of movement
	enum DIR { D_UP, D_DOWN, D_LEFT, D_RIGHT };

	// array to stand for world objects
	int bm[1024]={
		65535,128,448,128,65535,14336,4096,14336,65535,14,4,14,65535,448,128,448, //wall
		65535,53259,53259,53259,53259,53259,53259,53259,53259,53259,53259,53259,53259,53259,53259,53259, // door
			2040,1224,720,7928,4740,32740,65508,1088,1008,1032,2244,2340,2052,2340,1032,1008, //enemy
			8184,4104,12680,12680,6120,6120,4488,4488,4104,8184,0,0,0,0,0,0, //health
			8184,8184,8184,8184,8184,8184,8184,8184,8184,8184,0,0,0,0,0,0, //health mask
			2040,2040,0x3f0,8184,8188,32764,65532,18424,1008,2040,4092,4092,4092,4092,2040,1008, //enemy mask
			5136,5136,2592,2592,1088,1984,0,0,0,0,0,0,0,0,0,0,//gun
			8176,8176,4064,4064,1984,1984,0,0,0,0,0,0,0,0,0,0,//gun mask
			1008,1032,2340,2052,2340,2244,1032,1008,0,0,0,0,0,0,0,0, //dead enemy
			1008,2040,4092,4092,4092,4092,2040,1008,0,0,0,0,0,0,0,0,	//dead enemy mask
			0,0,0,0,0,2080,6096,9544,2336,256,0,0,0,0,0,0 //gunfire
	};

	class Pysche_Ray {
	public:

		// constructor
		Pysche_Ray() {
			c = THE_PI;
			//m=playerHealth=64;
			player_rot = 0.0;
			h = 64;// height of the grid
			w = 128;// width of the grid
			player_x = player_y = 128;// position of point of view
			RAD = c/180.0; 	// used to convert the angles to radians
			player_eyes = 32;
			INF = 10e30;			        //infinity
			F = 30.0f * RAD;			    //angle of view (larger distorts the "lens")
			R = 2.0 * F / 128.0;		    	//this is the angle of each ray to cover 128 pixels
			distance = floor(64.0/tan(F));	//110 pixels
			b2 = c/2.0;				        //90 degrees
			c3 = c;			            	//180 degrees
			c4 = c * 3.0 / 2.0; 			//270 degrees

			// initalize the blank screen structure
			// put a bar across the bottom
			for(int i = 0; i< 9216; i++)
			{
				if(i >= 8192)
					b_screen[i] = 2;
				else
					b_screen[i] = 0;
			}

			rand_color = true;
			InitMap();
		}

		// initalize the map and places the objects within the map array
		void InitMap() {
			//this function generates the initial screen and initializes
			//the map and object locations


			player_x = player_y = 128;						// initial player location
			player_rot = 0.0;
			memcpy(&the_buffer, &b_screen, sizeof(b_screen));	// store the blank screen in the "video memory"
			memset(w_, 0, sizeof(w));					// w is the world map,
			int d1=30+4*1; 				
			int x,y;									
			while(d1)
			{
				x=rand()%16;
				y=rand()%16;
				if(x*y>4)
				{
					w_[y]=w_[y]|1<<x;				
					d1--;
				}
			}

		}
		void SetObjectColor(D3DCOLOR the_color) {
			this->the_color = the_color;
			rand_color = false;
		}
		// function to preform ray casting algorithm orignaly from Wolf5K
		void CastRay() {
			memcpy(&the_buffer,&b_screen,sizeof(b_screen));
			double c2=-F; //F is the view angle, the larger F is the more we cram into the view area
			double a=player_rot+c2;  //angle of the ray we are calculating
			double a6=-1;
			double d;
			double Lht;
			double c1;
			double u;
			int uh,uv;
			double a5=INF;
			double a4,f=0.0f,dx,dy,a2,b,q,r,o,p,ht=0.0f;

			for(int v=0;v<w;v++) //what scanline we are working on (0-128)
			{
				c1=f;
				Lht=ht;
				double c=cos(a);
				double s=sin(a);
				double t=s/c;


				if(!a||a==c3) //if a is 0 or 180 then we get a divide by zero error so we ignore the ray
				{
					a4=INF;
				}
				else
				{
					if(s>0) //if we are in the top two quadrants
					{
						b=floor((double)player_y/64.0f+1.0f)*64; //start at the tile in front of the player
						dy=64;							//increment in whole tiles forward
						a2=(double)player_x+(b-(double)player_y)/t;		//start with an adjustment to the side of the player
						dx=64/t;						//increment 64/t to the side (plot chart)
					}
					else	//otherwise we are facing backwards so we go in the opposite direction
					{
						b=floor((double)player_y/64.0f)*64-.0001;
						dy=-64;
						a2=(double)player_x+(b-(double)player_y)/t;
						dx=-64/t;
					}
					//while we have not hit a wall tile or edge of the map
					while(!loc(a2,b))
					{
						a2+=dx;	//keep shooting the ray
						b+=dy;
					}
					q=a2;	//store the final location where the ray hits a wall tile
					r=b;
					a4=abs(((double)player_x-a2)/c);
					uh=(int)a2%64;	//the pattern repeats every 64 pixels.

					if(s>0)
						uh=64-uh;	//flip the pattern
				}
				if(a==b2||a==c4)  //if we are at 90 or 270 degrees our ray has infinite problems
				{
					a5=INF;
				}
				else
				{
					if(c>0)
					{
						a2=floor((double)player_x/64.0f+1.0f)*64;	//start one tile in front of player
						dx=64;
						b=(double)player_y+(a2-(double)player_x)*t;
						dy=64*t;
					}
					else
					{
						a2=floor((double)player_x/64.0f)*64.0f-.0001; //start just behind player
						dx=-64;
						b=(double)player_y+(a2-(double)player_x)*t;		//at 90 and 270, t goes to infinity so multiplying
						//results in an invalid number
						dy=-64*t;
					}

					//again look for the first wall tile we hit
					while(!loc(a2,b))
					{
						a2+=dx;
						b+=dy;
					}

					s=a2;
					t=b;
					a5=abs(((double)player_x-a2)/c);
					uv=(int)b%64;
					if(c<0)
						uv=64-uv;
				}

				d=a6;
				//we are looking for the smallest distance to travel
				//both rays cannot be infinite at once so we pick the one
				//that is not infinite
				if(a4<a5)
				{
					u=uh; //texture scanline
					f=a4; //distance from camera
					a6=0;
					o=q;	//map x position
					p=r;	//map y position
				}
				else
				{
					u=uv;	//text scanline
					f=a5;	//distance from camera
					a6=1;
					o=s;	//map x position
					p=t;	//map y position
				}

				f*=cos(c2);
				z_buffer[v]=f;	//zBuffer is our z-buffer, $f is the depth of the scanline
				ht=floor(64/f*distance); //height of the scanline
				double dd=abs(c1-f);	//change in distance from previous $f
				int k=(int)floor(player_eyes-ht/2.0);	//the top of our scanline
				int l=(int)floor(player_eyes+ht/2.0); //the bottom of the scanline
				int b3=k;	//starting position for scanning

				//a0 is the x pixel position in the texture
				//u will go from 0 to 63 so dividing by 4 gets us 0 to 15
				int a0=(int)(u/4.0);

				if(dd > 64 && Lht > ht)  //Lht is the previous scanline height
					ht=Lht;

				if(k<0)	//make sure we are not trying to draw above the view area
					k=0;

				if(l>=h) //if $l is greater than the height of the view area then adjust
					l=h-1;

				int x=(int)floor(o/64); //our tile position
				int y=(int)floor(p/64);

				//if we're out of bounds of the map
				//and the level is less than 5 then
				//alternate wall tiles
				//otherwise use the enemy sprite as a wall
				//tile and alternate it.
				//if we're in bounds then use the default
				//wall tile 0
				int pat=(x<0||x>15)&&y%2?1:1>4?2:0;

				//start at the top of the scanline and work down
				for(y=k;y<l;y++)
				{
					//var bit=0; //not actually used for anything.

					//the row of pixels is based on the current y
					//y position. >>2 divides by 4.  64/4==16
					int b1=(int)((y-b3)/ht*64)>>2;


					//we're subtracting from 15 because the tiles
					//are stored upside down
					int b2=bm[pat*16+(15-b1)]&1<<(a0&15);

					if(
						!(
				        b2 ||	// is the color 1 or 0?
						(v && d != a6) ||	//is $v 0 and $d not equal to a6 ($d is the prior version of a6)
						(dd >= 64 && v) ||	//if our change in distance is greater than 64 and $v is non 0
						(f >= 64*3 && f<64*4 && v%4==y%4) ||	//skip pixels based on distance from player
						(f >= 64*4 && f<64*6 && v%3==y%3) || //this is how the "lighting" is done
						(f >= 64*6 && v%2==y%2)
						)
						)
						SetPixel(v,y,1); //if after all of the checks we having something to plot
				}

				a+=R;	//increment the ray angle
				c2+=R;	//
			}
		}

		// function to move us around are 'virtual' world
		void MovePlayer(DIR dir) {

			double forward = 15.0;

			switch(dir) {
			case D_UP:
				{
					double c8 = player_x + forward * cos(player_rot);
					double c9 = player_y + forward * sin(player_rot);

					if(!loc(c8,c9)) //if we have not collided with anything
					{
						player_x = c8; //set the players location to the new location
						player_y = c9;
					}
				}
				break;
			case D_DOWN:
				{
					double c8 = player_x - forward * cos(player_rot);
					double c9 = player_y - forward * sin(player_rot);

					if(!loc(c8,c9)) //if we have not collided with anything
					{
						player_x = c8; //set the players location to the new location
						player_y = c9;
					}
				}
				break;
			case D_LEFT:
				{
					player_rot -= 5.0 * RAD;
				}
				break;
			case D_RIGHT:
				{
					player_rot += 5.0 * RAD;
				}
				break;
			}

		}

		int loc(double x,double y)
		{
			x=floor(x/64);//divide by 64 to figure out location
			y=floor(y/64);
			return(x<0||y<0||x>15||y>15)?1:(w_[(int)y]&1<<(int)x); // if out of bounds than return 1 otherwise return the location
		}


		// function to get the current pixel for streching the grid to fit the window
		D3DCOLOR GetScreenPixel(mxHwnd *mx, int x, int y) {
			int xp = (float)x * 128.0f / (float)mx->w;
			int yp = (float)y * 72.0f / (float)mx->h;
			int buffer_pos = the_buffer[yp*128+xp];
			switch(buffer_pos) {
				case 0:
					return D3DCOLOR_XRGB(0,0,0);
				case 1:
					
					return rand_color == true ? D3DCOLOR_XRGB(rand()%255,rand()%255,rand()%255) : the_color;
			}
			return D3DCOLOR_XRGB(255,255,255);
		}

		void CopyBuffer(mxHwnd *mx) {

			mx->paint.Lock();

			for(unsigned int i = 0; i < mx->w; i++) {
				for(unsigned int z = 0; z < mx->h; z++) {
					mx->paint.fast_sp(i,z,mx->paint.rect.Pitch, GetScreenPixel(mx,i,z));
				}
			}

			mx->paint.UnLock();
		}

		void SetPixel(int x, int y, int col) {
			the_buffer[y*w+x] = col;
		}
	protected:
		double c,F,R,b2,c3,c4,INF,RAD,player_rot;//double C,F,R,b2,c3,c4,INF,RAD,playerRotation;
		double distance;//DistToProjPlane;
		int m,h,w,health,player_eyes;//int M,H,W,playerHealth,playerEyeLevel;
		double player_x,player_y;// double player_x,player_y;
		double z_buffer[128];//double zBuffer[128];
		int b_screen[128*72];// int BlankScreen[128*72];
		int w_[64]; //int w[64];
		int the_buffer[128*72];//int p[128*72];
		bool rand_color;
		D3DCOLOR the_color;

	};

}