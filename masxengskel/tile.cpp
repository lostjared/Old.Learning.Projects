// the tile engine object
// jared bruni
#include "mxhead.h"


// passing in a pointer to the MasterXHWND object
void tileEngine::init(MasterXHWND* mxhwndx)
{
	mxhwnd = mxhwndx;
	loadgraphics();
}
// loading the graphics
void tileEngine::loadgraphics()
{
	mxhwnd->LoadGraphic(&tile_graphic[0],"red_tile.bmp");
	mxhwnd->LoadGraphic(&tile_graphic[1],"blue_tile.bmp");
	mxhwnd->LoadGraphic(&tile_graphic[2],"green_tile.bmp");
	loadlevel();
	tile_index = 0;
}

// get sub screen
MASTERSCREEN tileEngine::getsub()
{
	return sub_screen;
}
// set sub screen
void tileEngine::setsub(MASTERSCREEN scr)
{
	sub_screen = scr;
}

// engine keychecks
void tileEngine::keycheck()
{
	if(mxhwnd->KeyCheck(DIK_LEFT))
	{
		// left
	}

	if(mxhwnd->KeyCheck(DIK_RIGHT))
	{
		// right
	}
}
// update
void tileEngine::update()
{
	keycheck();
	drawtile();
}

// draw tilemap
void tileEngine::drawtile()
{
	int start_x = 0;
	int start_y = 0;
	int draw_count = 0;
	int t_x = start_x;
	int t_y = start_y;

	for(int i = 0; i < TILE_SIZE; i++)
	{
		tile_graphic[tile[i+tile_index].tile_type].DisplayGraphic(t_x,t_y);
		t_y = t_y + 16;
		draw_count++;
		if(draw_count > 20)
		{
			draw_count = 0;
			t_x = t_x + 16;
			t_y = 0;
		}
	}
}

// loading the tile map level
void tileEngine::loadlevel()
{
	for(int i = 0; i < TILE_SIZE*TILE_ROW;i++)
	{
		tile[i].solid = false;
		tile[i].tile_type = rand()%1;
	}

}
