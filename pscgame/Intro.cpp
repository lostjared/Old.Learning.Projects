// intro.cpp
// written by jared bruni

#include "thehead.h"



void Intro::ondraw()
{
	switch(screen)
	{
	case ID_LOGO:
		intrologo.DisplayGraphic(0,0);
		break;
	case ID_START:
		startlogo.DisplayGraphic(0,0);
		break;
	}
}

void Intro::onlogic()
{
	if(screen == ID_LOGO)
	{
		logo_count++;
		if(logo_count > 30)
		{
			logo_count = 0;
			screen = ID_START;
			return;
		}
	}
}


void Intro::keypress(WPARAM wParam)
{
	switch(screen)
	{
	case ID_START:
		if(wParam == VK_RETURN)
		{
			player.newgame();
			screen = ID_LOGO;
			mxhwnd.SetScreen(ID_GAME);
		}
		break;
	}
}