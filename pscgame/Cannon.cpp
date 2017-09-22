// cannon.cpp written by Jared Bruni
// www.lostsidedead.com

#include "thehead.h"



void Cannon::ondraw()
{
	mxhwnd.paint.mxdrawrect( x , 480-20, x + 100,480,RGB(180,180,180),RGB(200,200,200));
	mxhwnd.paint.mxdrawrect( x + 20,480-40,x + 100-20,480-20,RGB(255,255,255),RGB(200,200,200));
	mxhwnd.paint.mxdrawrect( x + 35,480-60,x + 100-35,480-40,RGB(0,0,255),RGB(0,0,255));
}

void Cannon::onlogic()
{
	if(mxhwnd.KeyCheck(DIK_RIGHT))
	{
		if( x + 100 < 640)
		{

		x += 10;

		}
	}

	if(mxhwnd.KeyCheck(DIK_LEFT))
	{
		if(x > 0)
		{
			x -= 10;
		}
	}
}

void Cannon::keypress(WPARAM wParam)
{
	switch(wParam)
	{
	case VK_SPACE:
		{
			pscemiter.releaseparticle (x + 40,480-60,20,BALL);
		}
		break;
	}
}