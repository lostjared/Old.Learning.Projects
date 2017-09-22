// Credits.cpp

#include "cr.h"


// draw me goin up 
void cr::update()
{
	if(on)
	{
		cswitch++;
		if(cswitch > 1)
		{
		y--;
		cswitch = 0;
		}

		if(y < 150)
		{
			on = false;
		}
	}
}


void crPoem::init(MasterXHWND* mxhwndx)
{
	mxhwnd = mxhwndx;
	off = 0;
}

void crPoem::add(char* buff,COLORREF rgb)
{
	strcpy(data[off].buff,buff);
	data[off].color = rgb;
	data[off].x = SX;
	data[off].y = SY;
	data[off].on = false;
	off++;
}

void crPoem::release()
{
	if(rcount < PSIZE)
	{

  	data[rcount].on = true;
	rcount++;

	}
}

// we always are updating all of them.
// each one will go until it dies
// every so often we release a new one
// and its done thru a variable that incremenmnts and knows which one to release
void crPoem::update()
{
	for(int i = 0; i < PSIZE; i++)
	{
		data[i].update();
		if(data[i].on)
		{
			mxhwnd->text.setbkcolor(curbg);
			mxhwnd->text.settextcolor(data[i].color);
			mxhwnd->text.printtext(data[i].buff,data[i].x,data[i].y);
		}
	}
}