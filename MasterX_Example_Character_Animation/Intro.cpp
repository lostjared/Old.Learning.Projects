// intro.cpp
// written by jared bruni
// for planetsourcecode

#include "thehead.h"


// load graphics
void Intro::load()
{
	// were we would load are graphics
}

// update 
void Intro::update()
{
	keycheck();// key check
	draw();// draw routine
}

// keycheck
void Intro::keycheck()
{
	if(mxhwnd->KeyCheck(DIK_SPACE))
	{
		mxhwnd->SetScreen(GAME);
	}
}
// draw to the screen
void Intro::draw()
{
	mxhwnd->paint.mxdrawrect(0,0,640,480,RGB(0,0,100),RGB(0,0,100));
	mxhwnd->paint.mxdrawellipse(0,0,640,480,RGB(0,0,80),RGB(0,0,80));
	mxhwnd->text.setfont(m_font);
	mxhwnd->text.setbkcolor(RGB(0,0,80));
	mxhwnd->text.settextcolor(RGB(255,0,0));
	mxhwnd->text.printtext("Character Animation Example for planetsourcecode",100,100);
	mxhwnd->text.setfont(x_font);
	mxhwnd->text.printtext("by Jared Bruni",150,150);
	mxhwnd->text.settextcolor(RGB(0,100,0));
	mxhwnd->text.printtext("Press Space to Continue",150,250);
}
