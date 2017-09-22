// hero source file

#include "thehead.h"


void Hero::update()
{
	keycheck();
	draw();
}

void Hero::load()
{

}

void Hero::draw()
{
	mxhwnd->paint.mxdrawellipse(x,y,x+25,y+25,RGB(255,255,255),RGB(200,200,200));
	mxhwnd->paint.mxdrawellipse(x+5,y+5,x+20,y+20,RGB(100,100,100),RGB(200,200,200));
}

void Hero::keycheck()
{
	if(mxhwnd->KeyCheck(DIK_LEFT))
	{
		if(x > 5)
		{
			x = x - speed;
		}
	}

	if(mxhwnd->KeyCheck(DIK_RIGHT))
	{
		if(x < 640-25)
		{
			x = x + speed;
		}
	}

	if((mxhwnd->KeyCheck(DIK_RETURN))||(mxhwnd->KeyCheck(DIK_SPACE)))
	{
		fire();
	}
	
}

void Hero::fire()
{
	// if dely is gone

	fdely++;

	if(fdely > 5)
	{

	int off;
	off = fmap.getoffball();

	// no fire balls allowed
	if(off != -1)
	{
		fmap.fire[off].on = true;
		fmap.fire[off].x = x+15;
		fmap.fire[off].y = y-25;
	}
	fdely = 0;
	}
}