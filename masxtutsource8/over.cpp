// over.cpp
// the game over section
// jared bruni
// http://www.lostsidedead.com/gameprog/


#include"mxhead.h"

// update the over object
void mgcover::update()
{
	keycheck();
	draw();
}
// loading up graphics/resources
void mgcover::loadgraphics()
{
	mxhwnd->LoadGraphic(&mgc_graphic2,"ex2.bmp");
}
// keychecks
void mgcover::keycheck()
{
	// keychecks
	switch(sub_screen)
	{
	case OVER_SCREEN:
		{

		}
		break;
	case OVER_SCORE:
		{

		}
		break;
	}
}
// drawing to the screen
void mgcover::draw()
{
	switch(sub_screen)
	{
	case OVER_SCREEN:
		drawscreen();
		break;
	case OVER_SCORE:
		drawscore();
		break;
	}
	mgc_graphic2.DisplayGraphic(0,0);
	mxhwnd->text.printtext("press esc to exit",200,200);

}

// drawing the game over screen
void mgcover::drawscreen()
{

}

// drawing the highscores menu
void mgcover::drawscore()
{

}
