// over.cpp written by jared bruni
// www.lostsidedead.com

#include "thehead.h"


HFONT gover = MakeFont("Arial",100);
HFONT gover2 = MakeFont("Arial",15);

void Over::ondraw()
{
	mxhwnd.paint.mxdrawrect(0,0,640,480,RGB(180,180,180),RGB(200,200,200));
	mxhwnd.text.setbkcolor( RGB( 180,180,180));
	mxhwnd.text.settextcolor(RGB(0,rand()%255,rand()%255));
	mxhwnd.text.setfont(gover);
	mxhwnd.text.printtext("Game over",50,50);
	mxhwnd.text.setfont(gover2);
	mxhwnd.text.settextcolor(0xff);
	mxhwnd.text.sprinttext(70,150+50,"Player Stats");
	mxhwnd.text.sprinttext(70,180+50,"Score: %i",player.score);
	mxhwnd.text.sprinttext(70,210+50,"Kills: %i",player.kills);

	if(player.kills > 20)
	{
		mxhwnd.text.sprinttext(70,240+50,"You have destroyed over 20 cds, the price has been lowered 70 precent!");
	}
	else
	{
		mxhwnd.text.sprinttext(70,240+50,"You have not meet the specified amount of cds destroyed, price is still $100");
	}

	mxhwnd.text.printtext("press enter to continue, escape to exit",70,240+50+30+10);

}

void Over::onlogic()
{

}

void Over::keypress(WPARAM wParam)
{
	if(wParam == 13)
	{
		mxhwnd.SetScreen(ID_INTRO);
	}
}