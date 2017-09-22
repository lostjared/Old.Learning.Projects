// the game source file
// jared bruni
// http://www.lostsidedead.com/gameprog/

#include "mxhead.h"

// object game object
void mgcgame::update()
{
	keycheck();
	draw();
}
// loading the graphics
void mgcgame::loadgraphics()
{
	mxhwnd->LoadGraphic(&mgc_graphic,"ex1.bmp");

}
// keychecks
void mgcgame::keycheck()
{
	// how you would handle the different keypresses
	switch(sub_screen)
	{
	case GAME_START:
		{
			if(mxhwnd->KeyCheck(DIK_RIGHT))
			{
				mxhwnd->SetScreen(OVER);
			}
		}
		break;
	case GAME_DIE:
		{
			if(mxhwnd->KeyCheck(DIK_LEFT))
			{
				mxhwnd->SetScreen(OVER);
			}
		}
		break;
	case GAME_MAIN:
		{
			if(mxhwnd->KeyCheck(DIK_SPACE))
			{
				sub_screen = GAME_DIE;
				break;
			}
		}
		break;
	}
}
// drawing to the screen
void mgcgame::draw()
{
	switch(sub_screen)
	{
	case GAME_START:
		drawgamestart();
		break;
	case GAME_MAIN:
		drawgamegame();
		break;
	case GAME_DIE:
		drawgamedie();
		break;
	}
}
// drawing the game start
void mgcgame::drawgamestart()
{
	mgc_graphic.DisplayGraphic(0,0);
	mxhwnd->text.printtext("the games start press right to skip to high scores ",200,200);
}
// drawing the game 
void mgcgame::drawgamegame()
{
	// u change
	//mxhwnd->text.printtext("the games area press space to jump into when they die",200,200);

}
// drawing section of game when hero dies
void mgcgame::drawgamedie()
{
	// u change
	//mxhwnd->text.printtext("the game die, area of code when you die, press left to jump to game over",200,200);
}