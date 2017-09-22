// intro.cpp
// designed specificly for *planetsourcecode* PSC rocks!
// by jared bruni
// www.lostsidedead.com

#include "thehead.h"


// on load
void Intro::onload()
{

}

// on update
void Intro::update()
{
	keycheck();
	mxhwnd->paint.mxdrawrect(0,0,640,480,RGB(0,0,255),RGB(0,0,255));
	mxhwnd->paint.mxdrawellipse(0,0,640,480,RGB(0,255,0),RGB(0,255,0));
	mxhwnd->text.setfont(m_font);
	mxhwnd->text.setbkcolor(RGB(0,255,0));
	mxhwnd->text.settextcolor(RGB(255,0,0));
	mxhwnd->text.printtext("Side Scrolling Tile Map Example for planetsourcecode",100,100);
	mxhwnd->text.setfont(x_font);
	mxhwnd->text.printtext("by Jared Bruni",150,150);
	mxhwnd->text.settextcolor(RGB(255,0,0));
	mxhwnd->text.printtext("Press Space to Continue",150,250);
}

// key check
void Intro::keycheck()
{
	if(mxhwnd->KeyCheck(DIK_SPACE))
	{
		mxhwnd->SetScreen(GAME);
		return;
	}
}