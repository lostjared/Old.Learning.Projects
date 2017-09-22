
// introduction object

#include "thehead.h"


void Intro::load()
{
	mxhwnd->LoadGraphic(&logo,"intro.bmp");
}

void Intro::update()
{

	keycheck();
	logo.DisplayGraphic(0,0);
	drawmenu();
}

void Intro::drawmenu()
{
	int x,y;
	
	switch(menu_pos)
	{
	case 0:
		x = 50;
		y = 250;
	
		break;
	case 1:
		x = 50;
		y = 340;
		break;
	}

	mxhwnd->paint.mxdrawellipse(x,y,x+40,y+40,RGB(rand()%255,rand()%255,rand()%255),RGB(rand()%255,rand()%255,rand()%255));


}

void Intro::keycheck()
{
	if(mxhwnd->KeyCheck(DIK_UP))
	{
		menu_pos = 0;
	}

	if(mxhwnd->KeyCheck(DIK_DOWN))
	{
		menu_pos = 1;
	}

	if(mxhwnd->KeyCheck(DIK_RETURN))
	{
		switch(menu_pos)
		{
		case 0:
		mxhwnd->SetScreen(GAME);
		break;
		case 1:
		mxhwnd->Kill();
		break;
		}

	}
}