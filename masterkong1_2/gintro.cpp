// gintro (game intro) written by jared bruni
// www.lostsidedead.com

#include "thehead.h"



void GIntro::keypress(WPARAM wParam)
{
	// initilize level information structures

	switch(wParam)
	{
	case VK_RETURN:

		char fn[100];
		strcpy(fn,"level");
		char sf[10];
		itoa(curmenu+1,sf,10);
		strcat(fn,sf);
		strcat(fn,".mxk");
		loadlevel(fn);
		mxhwnd.SetScreen(ID_GAME);
		break;
	case VK_UP:
		if(curmenu > 0)
		{
			curmenu--;
		}
		break;
	case VK_DOWN:
		if(curmenu < 4)
		{
			curmenu++;
		}
		break;
	}
}

void GIntro::ondraw()
{
	COLORREF gc = RGB(180,180,180);
	mxhwnd.paint.mxdrawrect(0,0,640,480,gc,gc);

	int addx = 2;
	for(int i = 0; i < 4; i++)
	{
		mxhwnd.paint.mxdrawrect(0+addx,0+addx,640-addx,480-addx,RGB(addx+180,addx+180,addx+180),RGB(180-addx,180-addx,180-addx));

		addx += 10;

	}

	mxhwnd.paint.mxdrawrect(42,42,640-42,480-42,0,0);

	granl.DisplayGraphic(50,480-42-64-5);
	herol.DisplayGraphic(640-42-32,480-42-64-5);

	// draw introduction story

	mxhwnd.text.settextcolor(RGB(200,0,0));
	mxhwnd.text.setfont(gfont[0]);
	mxhwnd.text.setbkcolor(0x0);
	mxhwnd.text.printtext("select your battle ground....",50,75);
	mxhwnd.text.printtext( "level 1",100,75+25);
	mxhwnd.text.printtext( "level 2",100,75+50);
	mxhwnd.text.printtext( "level 3",100,75+50+25);
	mxhwnd.text.printtext( "level 4",100,75+50+25+25);
	mxhwnd.text.printtext( "level 5",100,75+50+25+25+25);
	mxhwnd.text.settextcolor(RGB(rand()%255,rand()%255,rand()%255));

	int mx;
	int my;
	mx = 70;
	switch(curmenu)
	{
	case 0:
		my = 75+25;
		break;
	case 1:
		my = 75+50;
		break;
	case 2:
		my = 75+50+25;
		break;
	case 3:
		my = 75+50+25+25;
		break;
	case 4:
		my = 75+50+25+25+25;
		break;
	}

	mxhwnd.text.printtext("=)>",mx,my);
	
	
	mxhwnd.text.printtext("select level, and press return",50,300);

}

void GIntro::onlogic()
{



}

/*************************************************************************** lostsidedead.com */