// game.cpp written by jared bruni
// www.lostsidedead.com

#include "thehead.h"

HFONT afont = MakeFont("Arial",14);

void Game::ondraw()
{
	// draw out user scores 
	mxhwnd.text.setfont(afont);
	mxhwnd.text.settextcolor(RGB(0,0,255));
	mxhwnd.text.setbkcolor(0);
	mxhwnd.text.sprinttext(10,10,"Player Lives: %i",player.lives);
	mxhwnd.text.sprinttext(10,30,"Player Score: %i",player.score);
	mxhwnd.text.sprinttext(10,50,"Player Kills: %i",player.kills);

}

void Game::onlogic()
{
	// is the game over?
	if(player.lives < 0)
	{
		mxhwnd.SetScreen(ID_OVER);
	}


	wrc++;

	if(wrc > 20)
	{
		wrc = 0;
		int pos;
		pos = rand()%640-106;
		if(pos < 0)
		{
			pos = 0;
		}
	
		pscemiter.releaseparticle( pos,0,7,CD);

	}
}
