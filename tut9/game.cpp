// the game object
// jared bruni
// http://www.lostsidedead.com/gameprog/

#include "mxhead.h"

//update
void game::update()
{
	keycheck();
	drawobject();
}
// keycheck
void game::keycheck()
{
	// keycheck for down movement
	if(mxhwnd->KeyCheck(DIK_DOWN))
	{
		if(y < 480-100)
		{
			y++;
		}

	}
	// keycheck for up movement
	if(mxhwnd->KeyCheck(DIK_UP))
	{
		if(y > 0)
		{
			y--;
		}
	}
	// keycheck left
	if(mxhwnd->KeyCheck(DIK_LEFT))
	{
		if(x > 0)
		{
			x--;
		}
	}
	// right
	if(mxhwnd->KeyCheck(DIK_RIGHT))
	{
		if(x < 640-100)
		{
			x++;
		}
	}

	// space
	if(mxhwnd->KeyCheck(DIK_SPACE))
	{
		mxhwnd->SetScreen(OVER);
	}

}

// drawing object
void game::drawobject()
{
	mxhwnd->paint.mxdrawrect(x,y,x+100,y+100,RGB(0,0,100),RGB(0,0,100));
	mxhwnd->paint.mxdrawellipse(x,y,x+100,y+100,RGB(0,0,150),RGB(0,0,150));

	COLORREF cur_bg;
	cur_bg = mxhwnd->text.bk;
	mxhwnd->text.setbkcolor(cur_bg);
	mxhwnd->text.printtext("Use Arrows",x+10,y+20);
	mxhwnd->text.printtext("Space to leave",x+10,y+40);
	mxhwnd->text.bk = cur_bg;
}

void game::setpos(int ix, int iy)
{
	x = ix;
	y = iy;
}
