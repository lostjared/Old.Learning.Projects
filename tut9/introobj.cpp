// intro object
// jared bruni
// http://www.lostsidedead.com/gameprog/

#include "mxhead.h"

// update the intro object
void intro::update()
{
	keycheck();
	switch(sub_screen)
	{
	case INTRO_ANI:
		drawani();
		break;
	case INTRO_START:
		drawstart();
		break;
	}

}
// keychecks on the intro object
void intro::keycheck()
{
	switch(sub_screen)
	{
	case INTRO_ANI:
		{
			if(mxhwnd->KeyCheck(DIK_UP))
			{
				menu_state = false;
			}
			if(mxhwnd->KeyCheck(DIK_DOWN))
			{
				menu_state = true;
			}
			if(mxhwnd->KeyCheck(DIK_SPACE))
			{
			    if(menu_state)
				{
					mxhwnd->Kill();
				}
				else
				{
					setsub(INTRO_START);
				}
			}
		}
		break;
	case INTRO_START:
		{
		
		}
		break;
	}
}

// drawing the intro animation
void intro::drawani()
{
	mxhwnd->paint.mxdrawrect(0,0,640,480,RGB(0,0,100),RGB(0,0,150));
	mxhwnd->paint.mxdrawrect(10,10,630,200,RGB(0,0,200),RGB(0,0,255));
	mxhwnd->text.printtext("intro logo; jared bruni http://www.lostsidedead.com",20,20);

	mxhwnd->text.setbkcolor(RGB(0,0,100));
	mxhwnd->text.printtext("start new game",100,250);
	mxhwnd->text.printtext("exit",100,270);
	if(menu_state)
	{
		mxhwnd->text.printtext("->",80,270);
	}
	else
	{
		mxhwnd->text.printtext("->",80,250);
	}

	mxhwnd->text.printtext("Press Space ",80,300);

}

// drawing the start screen
void intro::drawstart()
{
	start_ani++;

	if(start_ani > 100)
	{
		start_ani = 0;
		mxhwnd->SetScreen(GAME);
	}

	COLORREF rand_color = RGB(rand()%255,rand()%255,rand()%255);

	mxhwnd->paint.mxdrawrect(0,0,640-add_w,480-add_h,rand_color,rand_color);
	add_w = add_w - 5;
	add_h = add_h - 5;
	COLORREF old_bg;
	old_bg = mxhwnd->text.bk;
	mxhwnd->text.setbkcolor(rand_color);
	mxhwnd->text.printtext(" Starting game animation",640/2-100,100);
	mxhwnd->text.bk = old_bg;
}
