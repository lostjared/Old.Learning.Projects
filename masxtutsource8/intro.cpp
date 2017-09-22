// introduction source

#include "mxhead.h"

// introduction class defenition

// update this object
void mgcintro::update()
{
	keycheck();
	draw();
}
// load up graphics / sound resources
void mgcintro::loadgraphics()
{

}
// drawing to the screen
void mgcintro::draw()
{
	switch(sub_screen)
	{
	case INTRO_START:
		drawstart();
		break;
	case INTRO_OP:
		drawop();
		break;
	}
}
// key checks
void mgcintro::keycheck()
{
	switch(sub_screen)
	{
	case INTRO_START:
		{
			// keypresses here
			if(mxhwnd->KeyCheck(DIK_SPACE))
			{
				sub_screen = INTRO_OP;
			}
		}
		break;
	case INTRO_OP:
		{
			if(mxhwnd->KeyCheck(DIK_LEFT))
			{
				mxhwnd->SetScreen(GAME);
			}
		}
		break;
	}
	
}

// drawing the start screen
void mgcintro::drawstart()
{
	mxhwnd->text.printtext("This is the start game chunk!",50,50);
	mxhwnd->text.printtext("press space to jump to the options game chunk",50,80);

}
// drawing the options window
void mgcintro::drawop()
{
	mxhwnd->text.printtext("press left to jump to the game chunk",50,50);
}