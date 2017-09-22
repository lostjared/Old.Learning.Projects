// hero source file
// written by jared bruni
// for planetsourcecode


#include "thehead.h"

// load
void Hero::load()
{
	hero_x = 100;
	hero_y = 100;
	hero_cur = 0;
	mxhwnd->LoadGraphic(&hero_graphic,"war.bmp");
}

// draw
void Hero::draw()
{
	drawsprite(hero_x,hero_y,hero_cur);
	mxhwnd->text.printtext("escape to exit, arrow keys to move the hero! FF style",10,10);
}

// check keys
void Hero::keycheck()
{
	if(mxhwnd->KeyCheck(DIK_DOWN))
	{
		movedown();
		return;
	}
	if(mxhwnd->KeyCheck(DIK_UP))
	{
		moveup();
		return;
	}
	if(mxhwnd->KeyCheck(DIK_LEFT))
	{
		moveleft();
		return;
	}
	if(mxhwnd->KeyCheck(DIK_RIGHT))
	{
		moveright();
		return;
	}
	if(mxhwnd->KeyCheck(DIK_SPACE))
	{
		punch();
		return;
	}
}

// punch
void Hero::punch()
{
	dely++;

	if(dely > 5)
	{
		ipunch = true;
		hero_cur = getpunch();
		dely = 0;
	}

}

// move left
void Hero::moveleft()
{
	if(hero_x > 0)
	{

	 
		dely++;

		if(dely > 5)
		{
			hero_cur = getnextleft();
			hero_x = hero_x - 5;
			dely = 0;
		}

	}
 
}
// move right
void Hero::moveright()
{
	if(hero_x < 640-32)
	{

	dely++;

	if(dely > 5)
	{

	hero_cur = getnextright();
	hero_x = hero_x + 5;

	dely = 0;
	
	}
	}

}
// move down
void Hero::movedown()
{
	if(hero_y < 480-32)
	{


	dely++;

	if(dely > 5)
	{
		hero_cur = getnextdown();

		hero_y = hero_y + 5;


		dely = 0;
	}
	}

}
// move up
void Hero::moveup()
{
	if(hero_y > 0)
	{


	dely++;

	if(dely > 5)
	{
		hero_cur = getnextup();
		hero_y = hero_y - 5;
		dely = 0;
	}

	}
}

// get punch variable
int Hero::getpunch()
{
	if(cur_punch == 0)
	{
		if(idir == DLEFT)
		{
			cur_punch = 11;
			return cur_punch;
		}
		else
		{
			cur_punch = 9;
			return cur_punch;
		}
		
	}

	if(cur_punch == 9)
	{
		cur_punch = 2;
		return cur_punch;
	}

	if(cur_punch == 11)
	{
		cur_punch = 3;
		return cur_punch;
	}

	if(cur_punch == 3)
	{
		cur_punch = 11;
		return cur_punch;
	}

	if(cur_punch == 2)
	{
		cur_punch = 9;
		return cur_punch;
	}


	return 0;
}


// get the next frame, for moving down
int Hero::getnextdown()
{
	if(cur_down == 0)
	{
		cur_down = 8;
		return cur_down;
	}

	if(cur_down == 8)
	{
		cur_down = 0;
		return cur_down;
	}

	return 0;
}
// figure out whats the next sprite
int Hero::getnextleft()
{
	idir = DLEFT;
	if(cur_left == 0)
	{
		cur_left = 3;
	return cur_left;
	}

	if(cur_left == 3)
	{
		cur_left = 7;
		return cur_left;
	}

	if(cur_left == 7)
	{
		cur_left = 3;
		return cur_left;
	}

	return 0;
}
// figure out whats the next sprite
int Hero::getnextright()
{
	idir = DRIGHT;

	if(cur_right == 0)
	{
		cur_right = 1;
		return cur_right;
	}

	if(cur_right == 1)
	{
		cur_right = 5;
		return cur_right;
	}

	if(cur_right == 5)
	{
		cur_right = 1;
		return cur_right;
	}
	return 0;
}
// figure out whats the next sprite
int Hero::getnextup()
{
	if(cur_up == 0)
	{
		cur_up = 2;
		return cur_up;
	}

	if(cur_up == 2)
	{
		cur_up = 6;
		return cur_up;
	}

	if(cur_up == 6)
	{
		cur_up = 2;
		return cur_up;
	}

	return 0;
}

// draw a hero sprite
void Hero::drawsprite(int x, int y, int sprite)
{
	int bmx = 0;
	int bmw = 0;
// pick out which one	
	switch(sprite)
	{
	case 0:
		bmx = 0;
		bmw = 32;
		break;
	case 1:
		bmx = 32;
		bmw = 64;
		break;
	case 2:
		bmx = 64;
		bmw = 64+32;
		break;
	case 3:
		bmx = 64+32;
		bmw = 64+32+32;
		break;
	case 4:
		bmx = 64+32+32;
		bmw = 64+32+32+32;
		break;
	case 5:
		bmx = 64+32+32+32;
		bmw = 64+32+32+32+32;
		break;
	case 6:
		bmx = 64+32+32+32+32;
		bmw = 64+32+32+32+32+32;
		break;
	case 7:
		bmx = 64+32+32+32+32+32;
		bmw = 64+32+32+32+32+32+32;
		break;
	case 8:
		bmx = 64+32+32+32+32+32+32;
		bmw = 64+32+32+32+32+32+32+32;
		break;
	case 9:
		bmx = 64+32+32+32+32+32+32+32;
		bmw = 64+32+32+32+32+32+32+32+32;
		break;
	case 10:
		bmx = 64+32+32+32+32+32+32+32+32;
		bmw = 64+32+32+32+32+32+32+32+32+32;
		break;
	case 11:
		bmx = 64+32+32+32+32+32+32+32+32+32;
		bmw = 64+32+32+32+32+32+32+32+32+32+32;
		break;
	}

	hero_graphic.DisplayGraphicEx(bmx,0,bmw,32,x,y);
}

// update hero object
void Hero::update()
{
	keycheck();
	draw();
}

