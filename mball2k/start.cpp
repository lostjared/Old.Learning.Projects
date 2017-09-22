// start.cpp
// written by jared bruni
// www.lostsidedead.com

#include "thehead.h"

void start_draw();
void start_logic();

int ball_pos = 0;

void start_update()
{
	start_draw();
	if(mxhwnd.SyncChange())
	{
		start_logic();
	}
}

// start draw update
void start_draw()
{
	drawsprite(0,0,START);
	int dx;
	int dy;

	switch(ball_pos)
	{
	case 0:
		dx = 160;
		dy = 195;
		break;
	case 1:
		dx = 160;
		dy = 235;
		break;
	case 2:
		dx = 160;
		dy = 235 + (235-195) + 5;
		break;
	}

	mxhwnd.paint.mxdrawellipse(dx,dy,dx+20,dy+20,RGB(rand()%255,rand()%255,rand()%255),0xFFFFFF);
}

// start logic update
void start_logic()
{

}

// start keypress
void start_keypress(WPARAM wParam)
{
	switch(wParam)
	{
	case VK_UP:
		if(ball_pos > 0)
		{
			ball_pos--;
		}
		break;
	case VK_DOWN:
		if(ball_pos < 2)
		{
			ball_pos++;
		}
		break;
	case VK_RETURN:
		switch(ball_pos)
		{
		case 0:
			{
				// start new game
				player.score = 0;
				player.level = 1;
				player.hits = 0;
				loadlevel(player.level);
				mxhwnd.SetScreen(ID_GAME);
			}
			break;
		case 1:
			{
				mxhwnd.SetScreen(ID_OPTIONS);
			}
			break;
		case 2:
			{
				// exit
				mxhwnd.Kill();
			}
			break;
		}

		break;
	}
}
