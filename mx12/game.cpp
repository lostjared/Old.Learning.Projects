// written by jared bruni
// www.lostsidedead.com

#include "thehead.h"

HFONT mfont = MakeFont("Verdana",14);
HFONT afont = MakeFont("Arial",12);


void Game::ondraw()
{
	drawmap();
	mxhwnd.text.setbkcolor(0x0);
	mxhwnd.text.setfont(mfont);
	mxhwnd.text.settextcolor(RGB(rand()%255,0,rand()%255));
	char l[100];
	sprintf(l,"Lives: %i", player.lives);
	mxhwnd.text.printtext(l,20,20);
	mxhwnd.text.setfont(afont);
	mxhwnd.text.settextcolor(RGB(0,0,180));
	mxhwnd.text.printtext("www.lostsidedead.com",20,50);

}

void Game::onlogic()
{

}


void Game::drawmap()
{
	int startby = 75;

	int bx,by;
	bx = 75; by = startby;
	int gcount = 0;


	for(int i = 0; i < 700-4+24; i++)
	{

	tiles[level.blocks[i].block].DisplayGraphic(bx,by);

	by = by + 16;
	gcount++;
	if(gcount > 23)
	{
		gcount = 0;
		by = startby;
		bx = bx + 16;
	}

	}
}

/*************************************************************************** lostsidedead.com */