// TileMap.cpp
// written by Jared Bruni
// specificly for planetsourcecode

#include "thehead.h"



// on the tile maps load
void TileMap::onload()
{
	mxhwnd->LoadGraphic(&tiles[0],"sky.bmp");
	mxhwnd->LoadGraphic(&tiles[1],"grass.bmp");
	mxhwnd->LoadGraphic(&tiles[2],"block.bmp");
	mxhwnd->LoadGraphic(&tiles[3],"block2.bmp");
}

// on the tile maps update
void TileMap::update()
{
	keycheck();
	drawmap();
}

// keycheck
void TileMap::keycheck()
{
	// scroll map left
	if(mxhwnd->KeyCheck(DIK_LEFT))
	{
		scrollleft();
		return;
	}

	// scroll map right
	if(mxhwnd->KeyCheck(DIK_RIGHT))
	{
		scrollright();
		return;
	}
}

// draw map
void TileMap::drawmap()
{
	int start_x = 50;
	int start_y = 50;

	int cur_x = start_x;
	int cur_y = start_y;

	int index = 0;

	for(int i = 0; i < 700-7; i++)
	{

		if(level_index < 9000-700-7-100)
		{

		
		tiles[level.img[i+level_index]].DisplayGraphic(cur_x,cur_y);

		}

		index++;
		cur_y = cur_y + 16;

		if(index > 20)
		{
			index = 0;
			cur_y = start_y;
			cur_x = cur_x + 16;
		}
	}

	mxhwnd->text.printtext("use left and right keys to scroll map",10,30);
}

// scroll left
void TileMap::scrollleft()
{
	if(level_index > 0)
	{
		dely++;

		if(dely > 2)//scroll speed
		{
			level_index = level_index - 21;
			dely = 0;
		}
	}
}

// scroll right
void TileMap::scrollright()
{
	dely++;

	if(dely > 2)// speed
	{
		level_index = level_index + 21;
		dely = 0;
	}

}
