// the games hero source module
// written by jared bruni
// www.lostsidedead.com


/* copyright notice

  this software or any software I write, is stricly for educational
  uses only. you are not allowed to take my code, and use it in
  anything which is sold.
  open source, open mind
*/

#include "thehead.h"


// load up the hero
void Hero::load()
{
	mxhwnd.LoadGraphic(&hero_graphic,"pes.bmp");
	hero_graphic.SetColorKey(RGB(255,0,255));
	cur_sprite = 1;
	setheropos(20 + 20 -1);	
}

// update the hero
void Hero::update()
{
	drawhero();
	keycheck();
}

// set the hero position
void Hero::setheropos(int pos)
{
	hero_pos = pos;
}

// draw the hero
void Hero::drawhero()
{
	int start_x = 80;
	int start_y = 80;

	int sx = start_x;
	int sy = start_y;

	int row_count = 0;

	for(int i = 0; i < LevelSize; i++)
	{
		if(i == hero_pos)
		{
			drawsprite(sx,sy,cur_sprite);
			return;
		}

		row_count ++;

		sy = sy + 16;

		if(row_count > 20)
		{
			row_count = 0;
			sx = sx + 16;
			sy = start_y;
		}
	}
}


// draw a hero sprite  - 
void Hero::drawsprite(int draw_x, int draw_y, int sprite)
{
	if(sprite <= 11)
	{

	int bx = 32 * sprite;
	hero_graphic.DisplayGraphicEx(bx,0,bx+32,32,draw_x,draw_y);

	}
}
// keycheck on hero
void Hero::keycheck()
{
	
	if(TimeChange())
	{
		
		hero_dely++;
		
		if(hero_dely >= 2)
		{
			
			hero_dely = 0;
			
			
			// the down key is pressed
			if(mxhwnd.KeyCheck(DIK_DOWN))
			{
				bool checkup1;
				bool checkup2;
				BlockInfo info1;
				BlockInfo info2;
				GetTileInfo(&info1,level.level_block[hero_pos + 2]);
				GetTileInfo(&info2,level.level_block[hero_pos + 21 + 2]);
				checkup1 = info1.solid;
				checkup2 = info2.solid;
				
				if(checkup1 == false && checkup2 == false)
				{
					hero_pos++;
				}
				
				dir = DIR_DOWN;
				
				if(cur_sprite != 0 && cur_sprite != 1)
				{
					cur_sprite = 0;
					return;
				}
				
				if(cur_sprite == 0)
				{
					cur_sprite = 1;
					return;
				}
				
				if(cur_sprite == 1)
				{
					cur_sprite = 0;
					return;
				}
			}
			
			// up key is pressed
			if(mxhwnd.KeyCheck(DIK_UP))
			{
				
				bool checkup1;
				bool checkup2;
				BlockInfo info1;
				BlockInfo info2;
				GetTileInfo(&info1,level.level_block[hero_pos - 1]);
				GetTileInfo(&info2,level.level_block[hero_pos + 20]);
				checkup1 = info1.solid;
				checkup2 = info2.solid;
				
				if(checkup1 == false && checkup2 == false)
				{
					hero_pos--;
				}
				
				dir = DIR_UP;
				
				if(cur_sprite != 4 && cur_sprite != 5)
				{
					cur_sprite = 4;
					return;
				}
				
				if(cur_sprite == 4)
				{
					cur_sprite = 5;
					return;
				}
				
				if(cur_sprite == 5)
				{
					cur_sprite = 4;
					return;
				}
				
			}

				// right key is pressed
			if(mxhwnd.KeyCheck(DIK_RIGHT))
			{
				
				bool checkup1;
				bool checkup2;
				BlockInfo info1;
				BlockInfo info2;
				GetTileInfo(&info1,level.level_block[hero_pos + 21 + 21]);
				GetTileInfo(&info2,level.level_block[hero_pos + 21 + 22]);
				checkup1 = info1.solid;
				checkup2 = info2.solid;
				
				if(checkup1 == false && checkup2 == false)
				{
					hero_pos = hero_pos + 21;
				}
				
				dir = DIR_RIGHT;
				
				if(cur_sprite != 2 && cur_sprite != 3)
				{
					cur_sprite = 2;
					return;
				}
				
				if(cur_sprite == 2)
				{
					cur_sprite = 3;
					return;
				}
				
				if(cur_sprite == 3)
				{
					cur_sprite = 2;
					return;
				}
				
			}

			// left key is pressed
			if(mxhwnd.KeyCheck(DIK_LEFT))
			{
				
				bool checkup1;
				bool checkup2;
				BlockInfo info1;
				BlockInfo info2;
				GetTileInfo(&info1,level.level_block[hero_pos - 21]);
				GetTileInfo(&info2,level.level_block[hero_pos - 20]);
				checkup1 = info1.solid;
				checkup2 = info2.solid;
				
				if(checkup1 == false && checkup2 == false)
				{
					hero_pos = hero_pos - 21;
				}
				
				dir = DIR_LEFT;
				
				if(cur_sprite != 6 && cur_sprite != 7)
				{
					cur_sprite = 6;
					return;
				}
				
				if(cur_sprite == 6)
				{
					cur_sprite = 7;
					return;
				}
				
				if(cur_sprite == 7)
				{
					cur_sprite = 6;
					return;
				}
				
			}
			
		}
		
	}
	
}

// hero keyup
void Hero::keyup(WPARAM wParam)
{
	switch(wParam)
	{
	case VK_UP:
	case VK_DOWN:
	case VK_LEFT:
	case VK_RIGHT:
		setstand();
		break;
	}
}
// set the hero position, back to normal standing, based on the direction he is facing
void Hero::setstand()
{
	switch(dir)
	{
	case DIR_UP:
		cur_sprite = 5;
		break;
	case DIR_DOWN:
		cur_sprite = 0;
		break;
	case DIR_LEFT:
		cur_sprite = 6;
		break;
	case DIR_RIGHT:
		cur_sprite = 2;
		break;
	}
}

