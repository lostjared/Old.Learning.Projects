// intro.cpp
// written by jared bruni
// www.lostsidedead.com

#include "thehead.h"


void Intro::load()
{
	mxhwnd.LoadGraphic(&introg,"intro.bmp");
}

void Intro::update()
{
	introg.DisplayGraphic(0,0);

	if(TimeChange())
	{
		fcount++;

		if(fcount > 50)
		{
			fcount = 0;
			mxhwnd.SetScreen(ID_GAME);
		}
	}
}
