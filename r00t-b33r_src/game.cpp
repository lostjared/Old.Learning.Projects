//by Deslock (Jean_René Bédard)
// 11/08/01
// game using the MasterX SDK 
// www.lostsidedead.com
// ************************************************** 
// *												*
// *     R00T B33R   Version 1.0.2.1.2.3.4.6.7.2.1b *
// *												*
// *	"Brings the old Tapper spirit alive"		*
// *												*
// **************************************************
//Deslock1@hotmail.com
//
// if you never played :
// rules : -------#1  theres no rules!, yeah some rules apply see #2
//                #2 You dont want to throw a root beer on the wall
//				  #3 YOu got to catch the empty mug when the customer are done
//				  #4 Dont let the customers reach the end of the counter where you are
//				  #5 The goal is to send all customer home waves after waves
//				  #6 ENJOY!!!!!!!!

//the score tells you the number of customers that you have knocked down
// 
// you got an X-tra Life every 15 levels
// its all optimized so theres an infinity of levels

//now stop reading this and go play
//Dont worry if its easy at start the difficulty increase all the time

//the code of all the game is on this page!


#include "theHead.h"
#include "resource.h"
#include "math.h"


MasterJoyStick stick;
bool joystick;

//these are importants game variables

int lvl=1;				  // level
int life=3;				  // life
int advanced=1;           // huh.....increment to gives extra lifes,increase difficulty

int bar_tender=1;		  // == 1,2,3 || 4 this is the bartender'S status
int bar_tender_pos=1;     // ==1,2 || 3 track (counter) where he is
int drunk_num =1;         // number of customers for that level
int beer_num;             // number if cirulating rootbeer
int beer_tot;             // pretty much the same
int beer_speed=2;         // rootbeer speed**************************************************ajust
int drunk_speed=1;        // customer speed**************************************************if too
int drinkin_time=300;     // time that the customers take to drink***************************fast
int luck_temper=400;      // this is the maximum of a random function that-
int weird=0;				//decide where to put customer at the start position-
int wait=0;                 //increase when more people
int update_counter;
int update_h;
unsigned __int64 cpuspeed(void);



//load everything
void game::load()
{
	mxhwnd.LoadGraphic(&floor,"bmps\\floor.bmp");
	mxhwnd.LoadGraphic(&bartender,"bmps\\bartender.bmp");
	mxhwnd.LoadGraphic(&mug,"bmps\\beer.bmp");
	mxhwnd.LoadGraphic(&guys,"bmps\\drunk.bmp");
	
	mxhwnd.LoadSound(&move_snd,MAKEINTRESOURCE(IDR_WAVE16));
	mxhwnd.LoadSound(&pour,MAKEINTRESOURCE(IDR_WAVE17));
	mxhwnd.LoadSound(&glass,MAKEINTRESOURCE(IDR_WAVE18));
	mxhwnd.LoadSound(&gotit,MAKEINTRESOURCE(IDR_WAVE19));
	mxhwnd.LoadSound(&rip,MAKEINTRESOURCE(IDR_WAVE20));
	mxhwnd.LoadSound(&yip,MAKEINTRESOURCE(IDR_WAVE21));
	mxhwnd.LoadSound(&bell,MAKEINTRESOURCE(IDR_WAVE22));
	mxhwnd.LoadSound(&gameover,MAKEINTRESOURCE(IDR_WAVE23));
	mxhwnd.LoadSound(&burp,MAKEINTRESOURCE(IDR_WAVE24));

	bartender.SetColorKey(RGB(0,255,0));
	guys.SetColorKey(RGB(0,255,0));
	mug.SetColorKey(RGB(0,255,0));

	joystick = stick.SetupJoystick();

	update_counter = cpuspeed();
	update_counter = update_counter/467456454;
}
//************************************************************************************************


//Update the whole thing
void game::update()
{
 render_room();

 keycheck();

 lk++;
 if(lk<=1)
 {
	level();
	create_drunk();
 }
 
 if(pouring==true)
	served();
 
 
 level();
 
 update_h++;
 
 if(update_h >= update_counter) // update circulation at a speed that differ based on your CPU speed
 {
 drunk();	
 beer_travel();
 update_h=0;
 }
 
 drunk_draw();
 
 beer_draw();

 collision();
 
 draw();

 panel();

}






//calculate your cpu speed
unsigned __int64 cpuspeed(void)
{
    unsigned __int64 start, stop;
    unsigned __int64 nCtr, nFreq, nCtrStop; 
    QueryPerformanceFrequency((LARGE_INTEGER *)&nFreq);
    _asm _emit 0x0F
    _asm _emit 0x31
    _asm mov DWORD PTR start, eax
    _asm mov DWORD PTR [start+4], edx
    QueryPerformanceCounter((LARGE_INTEGER *)&nCtrStop);
    nCtrStop += nFreq;
    
	do
	{
      QueryPerformanceCounter((LARGE_INTEGER *)&nCtr);
    } while (nCtr < nCtrStop);
    _asm _emit 0x0F
    _asm _emit 0x31
    _asm mov DWORD PTR stop, eax
    _asm mov DWORD PTR [stop+4], edx
    return (stop-start);
}







//draw the floor
void game::render_room()
{
	floor.DisplayGraphic(0,0);	
}


//check input keyboard/Joystick
void game::keycheck()
{
	int b;
	b = stick.JoyButtonDown();


	if(mxhwnd.KeyCheck(DIK_DOWN) || stick.JoyBackward() )          //  D O W N
	{
		
    if(move_snd.PlayStatus()==false)
	{
	
	serving=false;
	bar_tender=1;
	
	
	if(bar_tender_pos < 3)
	bar_tender_pos++;
	else
	bar_tender_pos=1;
	
	move_snd.Play();
	}

	if(move_snd.PlayStatus()==true)
	{
	return;
	}
	}
	
	
	if(mxhwnd.KeyCheck(DIK_UP) || stick.JoyForward())			// U P
	{
	if(move_snd.PlayStatus()==false)
	{
    
	serving=false;	
	bar_tender=1;
	
	if(bar_tender_pos > 1)
	bar_tender_pos--;
	else
	bar_tender_pos=3;
	
	move_snd.Play();
	}
	
	if(move_snd.PlayStatus()==true)
	{
	return;
	}
	}
	
	
	if(mxhwnd.KeyCheck(DIK_SPACE) || b==1)			// S P A C E
	{
		pouring=true;
	}
	
}





//the bartender on a dettermined track (counter) -> bar_tender_pos
void game::draw()
{
	switch(bar_tender_pos)
	{
	case 1:
		drawsprite(75,110,bar_tender);
		break;
	case 2:
		drawsprite(40,265,bar_tender);
		break;
	case 3:
		drawsprite(10,430,bar_tender);
		break;
	}
}




//draw the differents bartenders
void game::drawsprite(int x, int y, int sprite)
{
    switch(sprite)
	{
	case 1:
		bartender.DisplayGraphicEx(0,0,65,126,x+35,y+12);
		break;
	case 2:
		bartender.DisplayGraphicEx(70,0,132,123,x+38,y+15);
		break;
	case 3:
		bartender.DisplayGraphicEx(134,0,185,125,x+38,y+15);
		break;
	case 4:
		bartender.DisplayGraphicEx(186,0,251,125,x+28,y+15);
		break;
	}
}



//pour and throw the root beer
void game::served()
{
	
	if(pour.PlayStatus()==false && already==0)
	{
		pour.Play();
		already++;
	}
	
	
	if(pour.PlayStatus()==true)
	{
		bar_tender=2;
		return;
	}

	
	if(pour.PlayStatus()==false && already==1)
	{
		bar_tender=1;
		pouring=false;
		already=0;
		create_beer(false,bar_tender_pos,0);
		return;
	}
	
}


//*********************************** R O O T B E E R   Z O N E**********************************

// creates a new beer
void game::create_beer(bool empty,int position_y,int position_x)
{
		beer_num++;
		beer_tot=beer_num;
		
		if(beer_num>100)
		{
			beer_num=0;
			beer_tot=0;
		}
	
				if(empty==false)             // The beer is created by the bartender ,goes right
				{
				switch(position_y)
				{
				case 0:
				break;
				case 1:
				beers[beer_num].pos_y=120;
				beers[beer_num].pos_x=150;
				break;
				case 2:
				beers[beer_num].pos_y=275;
				beers[beer_num].pos_x=125;
				break;
				case 3:
				beers[beer_num].pos_y=440;
				beers[beer_num].pos_x=110;
				break;
				}	
				beers[beer_num].full=true;
				}

				
				if(empty==true)             // The beer is empty created by the drunk , goes left
				{
				switch(position_y)
				{
				case 0:
				break;
				case 1:
				beers[beer_num].pos_y=120;
				beers[beer_num].pos_x= position_x;
				break;
				case 2:
				beers[beer_num].pos_y=275;
				beers[beer_num].pos_x=position_x;
				break;
				case 3:
				beers[beer_num].pos_y=440;
				beers[beer_num].pos_x=position_x;
				break;
				}	
				beers[beer_num].full=false;
				}
		
}



// control beer's circulation
void game::beer_travel()
{
	
			for(vep=0;vep<=beer_tot;vep++) // for each beer
			{
			if(beers[vep].pos_x>1 && beers[vep].pos_x < 750 && beers[vep].full==true)
			{
				beers[vep].pos_x+=beer_speed;			// beer goes toward customres w/ always same strenght
			}
			
			if(beers[vep].pos_x>1 && beers[vep].pos_x > 10 && beers[vep].full==false)
			{
				beers[vep].pos_x-=beer_speed;			// beer goes toward bartender
			}
			}
}



//display the beer on screen
void game::beer_draw()
{
	
			for(vep=0;vep<=beer_tot;vep++)
			{
			if(beers[vep].pos_x>1 && beers[vep].pos_x < 700 && beers[vep].full==true)
			mug.DisplayGraphicEx(0,0,40,52,beers[vep].pos_x,beers[vep].pos_y);
			
			if(beers[vep].pos_x>1 && beers[vep].pos_x < 700 && beers[vep].full==false)
			mug.DisplayGraphicEx(36,0,81,48,beers[vep].pos_x,beers[vep].pos_y);
			}
			
}



//****************************************** C U S T O M E R S      Z O N E*********************

// create a or more than one new drunk customers  (they are not really drunk....the name of the functions is to get your attention, that's rootbeer !
void game::create_drunk()   
{
	for(yep=0; yep<drunk_num; yep++)
	{	
		luck=rand()%3;        // random track
		

		extra_luck=rand()%luck_temper; // make sure the customer dont appears in a "block" / same time
		
	
		drunks[yep].character=rand()%6;
		
		switch(luck)
		{
		case 0:
			drunks[yep].pos_y = 85;
			drunks[yep].pos_x= 700+extra_luck;
			break;
		case 1:
			drunks[yep].pos_y = 234;
			drunks[yep].pos_x= 700+extra_luck;
			break;
		case 2:
			drunks[yep].pos_y = 400;
			drunks[yep].pos_x= 700+extra_luck;
			break;
		}
		
		drunks[yep].drinkin=false;
	}
}



// customers circulation
void game::drunk()
{

	for(yep=0; yep<drunk_num;yep++)
	{
	
		if(drunks[yep].drinkin==false && drunks[yep].pos_x>1)
		{
			drunks[yep].pos_x-=drunk_speed;
			drunks[yep].recul=0;
		}	
		

		if(drunks[yep].drinkin==true && drunks[yep].pos_x >1)
		{
			
			drunks[yep].pos_x+=drunk_speed;
			drunks[yep].recul+=drunk_speed;
			
			if(drunks[yep].recul>drinkin_time)     // the customer want some more!
			{
			 drunks[yep].drinkin=false;
			 drunks[yep].recul=0;
			 create_beer(true,drunk_track(drunks[yep].pos_y),drunks[yep].pos_x);
			}
		
		}	

			if(drunks[yep].pos_x>730 && drunks[yep].drinkin==true) // the customer is dead, hurray!
			{
			drunks[yep].pos_x=0;
			drunks[yep].drinkin=false;
			dead++;
			}
			
			if(drunks[yep].pos_x>1 && drunks[yep].drinkin==false)
			switch(drunk_track(drunks[yep].pos_y))  // look if the customer reach the end of the counter 4 each tracks
			{
			case 1:
				if(drunks[yep].pos_x < 160)
				not_drunk();
				break;
			case 2:
				if(drunks[yep].pos_x < 123)
				not_drunk();
				break;
			case 3:
				if(drunks[yep].pos_x < 90)
				not_drunk();
				break;
			}
	}

}




//make them walking using sinus
void game::drunk_walk()
{
	drunks[yep].walk += 0.22;
	
	if(drunks[yep].walk>3.14)
	drunks[yep].walk=0;
		
	drunks[yep].walking =  sin(drunks[yep].walk)*5;
}




// display the customer on screen
void game::drunk_draw()
{
	
	for(yep=0; yep<drunk_num;yep++)
	{	
		if(mxhwnd.SyncChange())
		drunk_walk();
		
		if(drunks[yep].pos_x>1 && drunks[yep].pos_x < 799)
		{
		
		if(drunks[yep].drinkin==false)
		{
		switch_drunk();
		drunk_clipping();
		guys.DisplayGraphicEx(sx,sy,ex,ey,drunks[yep].pos_x,drunks[yep].pos_y+drunks[yep].walking-5+weird); //+drunks[yep].walking-5/
		}
		
		if(drunks[yep].drinkin==true)
		{
		switch_drunk();
		drunk_clipping();
		guys.DisplayGraphicEx(sx,sy,ex,ey,drunks[yep].pos_x,drunks[yep].pos_y+5+weird);
		}
		}
	weird=0;
	}

}


// make the customers look like they enter or leave the bar
void game::drunk_clipping()  
{
	find=drunk_track(drunks[yep].pos_y);
		
	switch(find)
	{
	case 1: // TRACK 1
		if(drunks[yep].pos_x < 641 && drunks[yep].drinkin==false)
		ex = (641-drunks[yep].pos_x);
		if(ex>41 && drunks[yep].drinkin==false )
		ex=41;
		
		if(drunks[yep].drinkin==true && drunks[yep].pos_x > (641-(ex-sx)))
		ex = 641-drunks[yep].pos_x+sx;
		if(ex<43 && drunks[yep].drinkin==true)  // the customer is deedeely dead on track 1
		{
		ex=43;
		drunks[yep].pos_x=0;
		drunks[yep].drinkin=false;
		dead++;
		rip.Play();
		score++;
		}
		break;

	case 2: //TRACK 2
		if(drunks[yep].pos_x < 673 && drunks[yep].drinkin==false )
		ex = (673-drunks[yep].pos_x);
		if(ex>41 && drunks[yep].drinkin==false )
		ex=41;
		
		if(drunks[yep].drinkin==true && drunks[yep].pos_x > (673-(ex-sx)))
		ex = 673 -drunks[yep].pos_x+sx;
		if(ex<43 && drunks[yep].drinkin==true) // the customer ride the midnight train to slumberland on track 2
		{
		ex=43;
		drunks[yep].pos_x=0;
		drunks[yep].drinkin=false;
		dead++;
		rip.Play();
		score++;
		}
		break;

	
	case 3://TRACK 3
		if(drunks[yep].pos_x < 710 && drunks[yep].drinkin==false)
		ex = (710-drunks[yep].pos_x);
		if(ex>41&& drunks[yep].drinkin==false )
		ex=41;
		
		if(drunks[yep].drinkin==true && drunks[yep].pos_x > (710-(ex-sx)))
		ex = 710-drunks[yep].pos_x+sx; 
		if(ex<43 && drunks[yep].drinkin==true) // the customer passed the way on track 3, may he RIP
		{
		ex=43;	
		drunks[yep].pos_x=0;
		drunks[yep].drinkin=false;
		dead++;
		rip.Play();
		score++;
		}
			
		break;
	

	}
}



//This function take the Y position of the customer and return the track (counter 1&&2&&3)
int game::drunk_track(int gps)
{
	if(gps < 140)
		return 1;

	if(gps > 160 && gps < 280)
		return 2;

	if(gps > 300)
		return 3;

return 0;
}



//The customer reach the end of the counter and he is mad 
void game::not_drunk()
{
bar_tender=3;
life--;
delete_all();
bell.Play();
}


//This decide witch kind of customer will be displayed
void game::switch_drunk()
{
   switch(drunks[yep].character)
   {
   case 0: // red guy
	   if(drunks[yep].drinkin==false) 
	   sx=0,ex=1,sy=0,ey=68;
	   else
	   sx=42,ex=98,sy=0,ey=66;
	   break;
   case 1: // Mrs.Blonde
	   if(drunks[yep].drinkin==false)
	   sx=0,ex=1,sy=68,ey=131;
	   else
	   sx=42,ex=98,sy=68,ey=131;
	   break;
   case 2:// african-american
	   if(drunks[yep].drinkin==false)
	   sx=0,ex=1,sy=134,ey=205;
	   else
	   sx=42,ex=98,sy=134,ey=205;
	   break;
   case 3:// big fat
	    if(drunks[yep].drinkin==false)
	   sx=0,ex=1,sy=206,ey=270;
	   else
	   sx=42,ex=98,sy=206,ey=270;
	   break;
   case 4:// farmer brown
	    if(drunks[yep].drinkin==false)
	   sx=0,ex=1,sy=272,ey=340;
	   else
	   sx=42,ex=98,sy=272,ey=340;
	   break;
   case 5://  AFFRO GHETTO
	    if(drunks[yep].drinkin==false)
	   sx=0,ex=1,sy=344,ey=440;
	   else
	   sx=42,ex=98,sy=344,ey=440;
	   weird= -26;
	   break;	
   
   }
}

//************************ I N T E R A C T I O N   Z O N E************************************* 


// this is a big one, for each tracks (3 counters) that decide if the beer is caught or it crashed on the wall/floor
void game::collision()
{
   
	
	for(vep=0;vep<=beer_tot;vep++)      // for each beers
    {

	
	if(beers[vep].pos_y==120)          // 1st track    111111111111111111111111111111111
	{
	if(beers[vep].full==true && beers[vep].pos_x>620) // the beer crash on the wall
	{	
	beer_explosion(beers[vep].pos_y,true);
	beers[vep].pos_x=700;
	}
	
	if(beers[vep].full==false && beers[vep].pos_x<171 && beers[vep].pos_x >1) 
	{	
		if(bar_tender_pos ==1  && beers[vep].pos_x >1)
		{
		gotit.Play();
		beers[vep].pos_x=0;   // YOU caught the beer!
		}
		if(bar_tender_pos !=1 && beers[vep].pos_x<141 && beers[vep].pos_x >1)
		{
		beer_explosion(beers[vep].pos_y,false); // the beer crash on the floor
		beers[vep].pos_x=0;
		}
	
	}		
		
	if(beers[vep].full==true)
	for(yep=0;yep<drunk_num;yep++) // for each customer
	{
		if(drunk_track(drunks[yep].pos_y)==1 && drunks[yep].drinkin==false)
		if(beers[vep].pos_x > drunks[yep].pos_x-10 && beers[vep].pos_x < drunks[yep].pos_x+50)
		if(beers[vep].pos_x !=0 && drunks[yep].pos_x != 0)
		{
		    drunks[yep].drinkin=true;	// he drinks the beer
			beers[vep].pos_x=0;
		}
	}
	}



	
	if(beers[vep].pos_y==275)        // 2cd track     2222222222222222222222222222222222222
	{
	
	if(beers[vep].full==true && beers[vep].pos_x>640) // the beer crash on the wall
	{	
	beer_explosion(beers[vep].pos_y,true);
	beers[vep].pos_x=700;
	}	
		
	if(beers[vep].full==false && beers[vep].pos_x<149 && beers[vep].pos_x >1) 
	{	
		if(bar_tender_pos == 2 && beers[vep].pos_x >1 )
		{
		beers[vep].pos_x=0;   //you got the empty beer
		gotit.Play();
		}
		if(bar_tender_pos != 2 && beers[vep].pos_x <119 && beers[vep].pos_x >1)
		{
		beer_explosion(beers[vep].pos_y,false); // the beer crash on the floor
		beers[vep].pos_x=0;
		}
		
	}		
				
	if(beers[vep].full==true)
	for(yep=0;yep<drunk_num;yep++)
	{
		if(drunk_track(drunks[yep].pos_y)==2 && drunks[yep].drinkin==false)
		if(beers[vep].pos_x > drunks[yep].pos_x-10 && beers[vep].pos_x < drunks[yep].pos_x+50)
		if(beers[vep].pos_x !=0 && drunks[yep].pos_x != 0)
		{
			beers[vep].pos_x=0;     // he drinks the beer
			drunks[yep].drinkin=true;
		}
	}	
	}
   
	  
	
	
	if(beers[vep].pos_y==440)       // 3rd track   33333333333333333333333333333333333333
	{
	
		
	if(beers[vep].full==true && beers[vep].pos_x>670) 
	{	
	beer_explosion(beers[vep].pos_y,true);// the beer crash on the wall
	beers[vep].pos_x=700;
	}	
		
	if(beers[vep].full==false && beers[vep].pos_x<115 && beers[vep].pos_x >1) 
	{	
		if(bar_tender_pos == 3 && beers[vep].pos_x >1)
		{
		beers[vep].pos_x=0;   //you caught the beer
		gotit.Play();
		}
		if(bar_tender_pos !=3 && beers[vep].pos_x<85 && beers[vep].pos_x >1)
		{
		beer_explosion(beers[vep].pos_y,false); // the beer crash on the floor
		beers[vep].pos_x=0;
		}
	}		
			
	if(beers[vep].full==true)
	for(yep=0;yep<drunk_num;yep++)
	{
		if(drunk_track(drunks[yep].pos_y)==3 && drunks[yep].drinkin==false)
		if(beers[vep].pos_x > drunks[yep].pos_x-10 && beers[vep].pos_x < drunks[yep].pos_x+50)
		if(beers[vep].pos_x !=0 && drunks[yep].pos_x != 0)
		{
			beers[vep].pos_x=0;     // he drinks the beer
			drunks[yep].drinkin=true;
		}
	}	
	}
    }
	
	
}



//***************************** M I S C **********************************************************


//Beer explosion either against the wall or on the floor
void game::beer_explosion(int track,bool entrence)
{
	
	if(entrence==true)      // the beer explose against the wall
	{
		mug.DisplayGraphicEx(0,54,59,104,590+(track/5),track);
		bar_tender=3;
		life--;
		delete_all();

	if(glass.PlayStatus()==false)
	{
		glass.Play();
		mug.DisplayGraphicEx(0,54,59,104,590+(track/5),track);
	}
	}


	if(entrence==false)       // the beer crash on the floor
	{
		mug.DisplayGraphicEx(0,54,59,104,590+(track/5),track);
		bar_tender=3;
	    life--;
		delete_all();

	if(glass.PlayStatus()==false)
	{
		glass.Play();
		mug.DisplayGraphicEx(55,55,133,111,20+(track/8),track);
	}
	}

}






//Update score,level,lives Display
void game::panel()
{
mxhwnd.text.setfont(panel_font);
mxhwnd.text.setbkcolor(RGB(0,0,0));

mxhwnd.paint.mxdrawrect(715,10,790,140,RGB(0,0,0),RGB(232,234,33));


mxhwnd.text.settextcolor(RGB(221,134,89));
mxhwnd.text.printtext("score",730,15);
mxhwnd.text.printtext("Level",732,55);
mxhwnd.text.printtext("Lives",730,95);



mxhwnd.text.settextcolor(RGB(123,210,34));
mxhwnd.text.sprinttext(725 ,35,"%d",score);
mxhwnd.text.sprinttext(745,75,"%d",lvl);
mxhwnd.text.sprinttext(745,115,"%d",life);
}







//Differents importants events
void game::level()
{
	
	if(dead==drunk_num) // change level
	{
	lvl++;
	advanced++;
	need_a_life++;
	drunk_num++;
	yip.Play();
	bar_tender=4;
	luck_temper+=20;
	delete_all();
	}

  
	if(need_a_life==15)
	{
	life++;
	need_a_life=0;
	}
	
	
	if(advanced==15) // every 10 level restart 1 customer but the drinking time always decrease
	{
	advanced=1;
	drunk_num=1;
	drinkin_time-=30; // they drink it all in less time!!! 
	luck_temper=400;
	delete_all();
	}
	
	
	
	if(life==0)   // GAME OVER
	{
	mxhwnd.paint.mxdrawrect(200,200,600,400,RGB(0,0,0),RGB(255,255,255));
	mxhwnd.text.printtext("GAME OVER (We had fun but it's over!)",250,230);
	mxhwnd.text.printtext("Press Enter to Play again",250,260);
	mxhwnd.text.printtext("Press Escape to Exit",250,290);
	
		


	if(gone==0)
	{
	gameover.Play();
	msg=rand()%5;  // random exit message
	gone=1;
	}
	
	switch(msg)
	{
	case 0:
		mxhwnd.text.printtext("Hey, you cant leave now!",250,360);
		break;
	case 1:
		mxhwnd.text.printtext("hmmmm, you can do better",250,380);
		break;
	case 2:
		mxhwnd.text.printtext("Press enter for fame and glory, escape for work and worry",205,360);
		break;
	case 3:
		mxhwnd.text.printtext("Those customers are not gonna make their own beer!",230,360);
		break;
	case 4:
		mxhwnd.text.printtext("You know you want to play again",250,360);
		break;
	}
	
	delete_all();
	
	if(mxhwnd.KeyCheck(DIK_RETURN)) //if you want to retry
	{
	delete_all();
	score=0;
	drunk_num=1;
	gone=0;
	lvl=1;
	life=3;
	advanced=1;
	bar_tender=1;
	need_a_life=0;
	panel();
	beer_speed=2;
	drinkin_time=300;
	luck_temper=400;
	}
	
	}
}




// clear the screen of customers,beers for a new level or to retry
void game::delete_all()
{
 for(yep=0;yep<drunk_num;yep++)
 {
	drunks[yep].pos_x=0;
	drunks[yep].drinkin=false;
 }

for(vep=0;vep<=beer_tot;vep++)
 {
	beers[vep].pos_x=0;
	beers[vep].full=false;
 }

 dead=0;
 beer_num=0;
 beer_tot=0;
 create_drunk();
}




// THAT'S ALL FOLKS, *****deslock1@hotmail.com****** Made in 1 week 5/08/01 -> 12/08/01
// The engine used is MasterX more infos/games/examples on www.lostsidedead.com
// or www.planet-source-code.com