// the drawprog class object
// jared bruni
// http://www.lostsidedead.com/gameprog/

#include "mxhead.h"

// init

// program init
void dprog::init(MasterXHWND* mxhwndx)
{
	mxhwnd = mxhwndx;
}

// program update
void dprog::update()
{
	drawsquare();
	drawcircle();
	drawstuff();
}

// drawing a square
void dprog::drawsquare()
{
	mxhwnd->paint.mxdrawrect(10,10,10+100,10+100,RGB(100,0,0),RGB(100,0,0));

	// drawing a shaded square

	int start_r = 100;
	int start_g = 100;
	int start_b = 100;

	int sx = 105;
	int sy = 10;
	int sw = 100;
	int sh = 100;

	int dcount = 10;
	int dadd = 5;
	int dspan = 5;
	
	for(int i = 0; i < dcount; i++)
	{
		mxhwnd->paint.mxdrawrect(sx,sy,sx+sw+dadd,sy+sh+dadd,RGB(start_r,start_g,start_b),RGB(start_r,start_g,start_b));

		dadd = dadd + 1;
		dspan = dspan + 5; 
		start_r = start_r + dspan;
		start_g = start_g + dspan;
		start_b = start_b + dspan;
	}



}

// drawing a circle
void dprog::drawcircle()
{
	cir_add++;
	if(cir_add > 100)
	{
		cir_add = 0;
	}
	mxhwnd->paint.mxdrawellipse(10,300,10+cir_add,300+cir_add,RGB(255,255,255),RGB(255,255,255));
}

// drawing stuff
void dprog::drawstuff()
{
	mxhwnd->text.setbkcolor(RGB(255,0,0));
	mxhwnd->text.settextcolor(RGB(0,0,255));
	mxhwnd->text.printtext("hello world w/ style",300,300);
}
