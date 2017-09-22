// game over screen
// written by jared bruni
// www.lostsidedead.com

#include "thehead.h"

HFONT xTitleFont = MakeFont("Arial",18);
HFONT xRegFont = MakeFont("Arial",14);


void gameover_draw();

// gameover update
void gameover_update()
{
	gameover_draw();
}

// game over draw
void gameover_draw()
{
	COLORREF rcolor = RGB(rand()%255,rand()%255,rand()%255);
	drawsprite(0,0,START);
	mxhwnd.paint.mxdrawrect(100,100,535,400,NULL,NULL);
	mxhwnd.text.setbkcolor(0x000000);
	mxhwnd.text.settextcolor(0xFF0000);
	mxhwnd.text.setfont(xTitleFont);
	mxhwnd.text.printtext("Game Over",115,115);
	mxhwnd.paint.mxhorizontalline(115,515,135,rcolor);
	mxhwnd.paint.mxverticalline(135,380,115,rcolor);
	mxhwnd.paint.mxhorizontalline(115,515,380,rcolor);
	mxhwnd.paint.mxverticalline(135,380,515,rcolor);
	mxhwnd.text.settextcolor(RGB(255,0,0));
	mxhwnd.text.setbkcolor(0);
	mxhwnd.text.setfont(xRegFont);
	char scordiff[50];
	sprintf(scordiff,"Player Score: %i",player.score);
	mxhwnd.text.printtext(scordiff,145,150);
	char hitdiff[50];
	sprintf(hitdiff,"Player hits: %i",player.hits);
	mxhwnd.text.printtext(hitdiff,145,165);
	char glev[50];
	sprintf(glev,"Level: %i",player.level);
	mxhwnd.text.printtext(glev,145,180);
	mxhwnd.text.settextcolor(RGB(rand()%255,rand()%255,rand()%255));
	mxhwnd.text.printtext("Press enter to continue",145,220);
}
// keypress for gameover
void gameover_keypress(WPARAM wParam)
{
	if(wParam == 13 || wParam == VK_SPACE)
	{

	mxhwnd.SetScreen(ID_INTRO);
	player.lives = 3;

	}
}