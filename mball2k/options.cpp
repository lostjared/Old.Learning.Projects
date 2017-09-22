// the options source file
// written  by jared bruni
// www.lostsidedead.com

#include "thehead.h"

HFONT TitleFont = MakeFont("Arial",18);
HFONT RegFont = MakeFont("Arial",14);

int op_index = 0;

void options_draw();
void options_logic();
void options_drawmenu();

// options update
void options_update()
{
	options_draw();
	if(mxhwnd.SyncChange())
	{
		options_logic();
	}
}

// options draw
void options_draw()
{
	COLORREF rcolor = RGB(rand()%255,rand()%255,rand()%255);
	drawsprite(0,0,START);
	mxhwnd.paint.mxdrawrect(100,100,535,400,NULL,NULL);
	mxhwnd.text.setbkcolor(0x000000);
	mxhwnd.text.settextcolor(0xFF0000);
	mxhwnd.text.setfont(TitleFont);
	mxhwnd.text.printtext("Options Menu",115,115);
	mxhwnd.paint.mxhorizontalline(115,515,135,rcolor);
	mxhwnd.paint.mxverticalline(135,380,115,rcolor);
	mxhwnd.paint.mxhorizontalline(115,515,380,rcolor);
	mxhwnd.paint.mxverticalline(135,380,515,rcolor);

	options_drawmenu();

}

// options drawmenu
void options_drawmenu()
{
	mxhwnd.text.settextcolor(RGB(255,0,0));
	mxhwnd.text.setbkcolor(0);
	mxhwnd.text.setfont(RegFont);
	char gdiff[50];
	sprintf(gdiff,"Game Difficulty: %i",player.difficulty);
	mxhwnd.text.printtext(gdiff,145,150);
	char ldiff[50];
	sprintf(ldiff,"Player Lives: %i",player.lives);
	mxhwnd.text.printtext(ldiff,145,170);
	char joystr[100];
	if(player.nojoystick)
	{
		strcpy(joystr,"Joystick: No Joystick");
	}
	else
	{
		strcpy(joystr,"Joystick: ");
		if(player.joystick_on)
		{
			strcat(joystr,"On");
		}
		else
		{
			strcat(joystr,"Off");
		}
	}

	mxhwnd.text.printtext(joystr,145,190);


	mxhwnd.text.printtext("All Done",145,350);

	int arrow_x,arrow_y;
	switch(op_index)
	{
	case 0:
		arrow_x = 120;
		arrow_y = 150;
		break;
	case 1:
		arrow_x = 120;
		arrow_y = 170;
		break; 
	case 2:
		arrow_x = 120;
		arrow_y = 190;
		break;
	case 3:
		arrow_x = 120;
		arrow_y = 350;
		break;
	}
	mxhwnd.text.settextcolor(RGB(rand()%255,rand()%255,rand()%255));
	mxhwnd.text.printtext("=)>",arrow_x,arrow_y);

}

// options logic
void options_logic()
{

}

// options keypress
void options_keypress(WPARAM wParam)
{
	switch(wParam)
	{
	case VK_DOWN:
		if(op_index < 3)
		{
			op_index++;
		}
		break;
	case VK_UP:
		if(op_index > 0)
		{
			op_index--;
		}
		break;
	case VK_RIGHT:
		switch(op_index)
		{
		case 0:
			if(player.difficulty < 5)
			{
				player.difficulty ++;
			}
			break;
		case 1:
			if(player.lives < 10)
			{
				player.lives ++;
			}
			break;
		case 2:
			if(player.nojoystick == false)
			{
				player.joystick_on = true;
			}
			break;
		}
		break;
	case VK_LEFT:
		switch(op_index)
		{
		case 0:
			if(player.difficulty > 1)
			{
				player.difficulty--;
			}
			break;
		case 1:
			if(player.lives > 1)
			{
				player.lives--;
			}
			break;
		case 2:
			if(player.nojoystick == false)
			{
				player.joystick_on = false;
			}
			break;
		}
		break;
	case VK_RETURN:
		switch(op_index)
		{
		case 3:
			{
				op_index = 0;
				mxhwnd.SetScreen(ID_START);
			}
			break;
		}
		break;
	}
}

