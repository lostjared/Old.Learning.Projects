//by DEslock
// this is the "Deslock" logo / animation
// at the beginning


#include "thehead.h"
#include "resource.h"

int counter_l=-1;
bool disp_l =true;
bool slogan =false;

int letter_x;
int cous;
int counter_t;
bool explosio;
int fire_num=1;
int luck_x;
int luck_y;
int io;
int counter_c;
int letter_d=-1;
char disturbing[50];

bool cursor;
int p;


void klosed::load()
{

	mxhwnd.LoadGraphic(&compagnie,"bmps\\klosed.bmp");
	mxhwnd.LoadGraphic(&explose,"bmps\\explosion.bmp");
	mxhwnd.LoadGraphic(&flame,"bmps\\fire.bmp");
	mxhwnd.LoadSound(&boom,MAKEINTRESOURCE(IDR_WAVE25));
	mxhwnd.LoadSound(&bip,MAKEINTRESOURCE(IDR_WAVE20));
	
	flame.SetColorKey(RGB(0,0,0));
	compagnie.SetColorKey(RGB(0,0,0));
	explose.SetColorKey(RGB(0,0,0));
}



void klosed::update()
{

//if(music_intro.PlayStatus()==false)
//music_intro.Play();
	
	if(cous==0)
	{
	//mxhwnd.media.play();
	cous=1;
	}
	
	
	if(disp_l ==true)
	{
	
	if(mxhwnd.SyncChange())
	counter_t++;
		
	if(counter_t >5)
	{	
	letters();
	counter_t=0;
	}
	}
	
	
	if(slogan==true)
	{
	if(mxhwnd.SyncChange())
	counter_t++;
		
	
	if(counter_t >4)
	{	
	letter_d++;
	bip.Play();
	counter_t=0;
	}
		
	if(letter_d > 17)
	slogan=false;
	}
	
	
	if(explosio==true)
	if(mxhwnd.SyncChange())
	explosion();
	
	fire();
	
	
	draw();

	
	messages();
}



//Draw the letters
void klosed::draw()
{

	 compagnie.DisplayGraphicEx(0,0,letter_x,106,20,200);
	compagnie.DisplayGraphicEx(0,118,letter_d*13,142,30,370);

}



//controls the display of each letters of deslock
void klosed::letters()
{
	if(counter_l ==-1)
	{
		p=0;
		letter_x = 0;
		explosio=true;
		counter_l++;
		return;
	}
	
	if(counter_l ==0 )
	{
		p=0;
		letter_x = 95;
		counter_l++;
		return;
	}

	if(counter_l ==1 )
	{
		p=0;
		letter_x =173;
		counter_l++;
		return;
	}

	if(counter_l ==2 )
	{
		p=0;
		letter_x =247;
		counter_l++;
		return;
	}

	if(counter_l ==3 )
	{
		p=0;
		letter_x =291;
		counter_l++;
		return;
	}

	if(counter_l ==4 )
	{
		p=0;
		letter_x = 370;
		counter_l++;
		return;
	}

	if(counter_l ==5 )
	{
		p=0;
		letter_x=448;
		counter_l++;
		return;
	}

	
	if(counter_l ==6 )
	{
		p=0;
		letter_x=538;
		explosion();
		counter_l++;
		return;
	}

	if(counter_l ==7 )
	{
		letter_x=760;
	
		disp_l =false;
		slogan=true;
		explosio=false;
		return;
	}
}



//Boom!
void klosed::explosion()
{
	p++;
	io=182*p;
	
	
	explose.DisplayGraphicEx(io,0,io+180,135,letter_x,200);
 
	
	//create some fire, I know its not optimized but I want some fire on my name
	switch(letter_x)	
	{
	case 0:
		break;
	case 95:
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 60;
		fires[fire_num].pos_y = 167;
		fire_num++;
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 40;
		fires[fire_num].pos_y = 167;
		fire_num++;
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 30;
		fires[fire_num].pos_y = 167;
		fire_num++;
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 65;
		fires[fire_num].pos_y = 167;
		fire_num++;
		break;
	case 173:
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 145;
		fires[fire_num].pos_y = 244-53;
		fire_num++;
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 120;
		fires[fire_num].pos_y = 251-53;
		fire_num++;
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 160;
		fires[fire_num].pos_y = 251-53;
		fire_num++;
		break;
	case 247:
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 209;
		fires[fire_num].pos_y = 248-53;
		fire_num++;
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 231;
		fires[fire_num].pos_y = 243-53;
		fire_num++;
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 240;
		fires[fire_num].pos_y = 246-53;
		fire_num++;
		break;
	case 291:
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 280;
		fires[fire_num].pos_y = 220-53;
		fire_num++;
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 290;
		fires[fire_num].pos_y = 220-53;
		fire_num++;
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 294;
		fires[fire_num].pos_y = 220-53;
		fire_num++;
		break;
	case 370:
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 340;
		fires[fire_num].pos_y = 243-53;
		fire_num++;
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 319;
		fires[fire_num].pos_y = 254-53;
		fire_num++;
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 355;
		fires[fire_num].pos_y = 256-53;
		fire_num++;
		break;
	case 448:
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 340+80;
		fires[fire_num].pos_y = 243-53;
		fire_num++;
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 319+85;
		fires[fire_num].pos_y = 254-53;
		fire_num++;
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 355+87;
		fires[fire_num].pos_y = 256-53;
		fire_num++;
		break;
	
	case 538:
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 484;
		fires[fire_num].pos_y = 221-53;
		fire_num++;
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 490;
		fires[fire_num].pos_y = 221-53;
		fire_num++;
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 526;
		fires[fire_num].pos_y = 245-53;
		fire_num++;
		fires[fire_num].state=rand()%31;
		fires[fire_num].pos_x = 530;
		fires[fire_num].pos_y = 245-53;
		fire_num++;
		break;
	}
	

	if(boom.PlayStatus()==false)
	{
		boom.Play();
		blind();
	}
	
	
	if(p>9)
	p=0;
	
}



//Displays some fire on the letters
void klosed::fire()
{
	for(int fe=0;fe<fire_num;fe++)
	{
	
	if(fires[fe].pos_x!=0)
	flame.DisplayGraphicEx(fires[fe].state*31,0,fires[fe].state*31+30,53,fires[fe].pos_x,fires[fe].pos_y);
	
	
	if(mxhwnd.SyncChange())
	fires[fe].state++;

	if(fires[fe].state>32)
		fires[fe].state=0;
	
	}
}



//Makes the screen goes white bamm!!!
void klosed::blind()
{

	for(int bl=0;bl<214;bl += 30)
	{
	//mxhwnd.paint.mxdrawellipse(letter_x+50-bl,230-bl,letter_x+50+bl,letter_x+bl,RGB(bl,bl,bl),RGB(bl,bl,bl));
	mxhwnd.paint.mxdrawrect(0,0,800,600,RGB(bl,bl,bl),RGB(bl,bl,bl));
	}


}




//DISTURBING__G@ME$
void klosed::messages()
{
	
if(cursor==false)
{
compagnie.DisplayGraphicEx(0,142,13,162,letter_d*13+28,372);

if(mxhwnd.SyncChange())
counter_c++;

if(counter_c >2)
{
cursor=true;
counter_c=0;
}


return;
}
else
{

if(mxhwnd.SyncChange())
counter_c++;

if(counter_c >2)
{
cursor=false;
counter_c=0;	
}

return;

}


}


