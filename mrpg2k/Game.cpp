// game source module
// written by jared bruni
// www.lostsidedead.com


/* copyright notice

  this software or any software I write, is stricly for educational
  uses only. you are not allowed to take my code, and use it in
  anything which is sold.
  open source, open mind
*/

#include "thehead.h"

 
 
// get information about a given tile, 
void GetTileInfo(BlockInfo* info,int tile)
{
	switch(tile)
	{
	case 0: // grass
		info->kill = false;
		info->solid = false;
		break;
	case 1:// stone
		info->kill = false;
		info->solid = false;
		break;
	case 2:// gray brick
		info->solid = true;
		info->kill = false;
		break;
	case 3:// stone 3
		info->solid = false;
		info->kill = false;
		break;
	case 4:// stone 4
		info->solid = false;
		info->kill = false;
		break;
	case 5:// sand1
		info->solid = false;
		info->kill = false;
		break;
	case 6:// sand2
		info->solid = false;
		info->kill = false;
		break;
	case 7:// snow
		info->solid = false;
		info->kill = false;
		break;
	case 8:// water 1
		info->solid = false;
		info->kill = false;
		break;
	case 9:// water 2
		info->solid = false;
		info->kill = false;
		break;
	case 10:// black sky
		info->solid = false;
		info->kill = false;
		break;
	case 11:// blue sky
		info->solid = false;
		info->kill = false;
		break;
	case 12:// stone 2
		info->solid = false;
		info->kill = false;
		break;
	case 13:// red brick
		info->solid = true;
		info->kill = false;
		break;
	case 14:// blue brick
		info->solid = true;
		info->kill = false;
		break;
	}
}

// game load graphics/sound
void Game::load()
{
	// load the tiles
	mxhwnd.LoadGraphic(&tiles[0],"grass.bmp");
	mxhwnd.LoadGraphic(&tiles[1],"stone.bmp");
	mxhwnd.LoadGraphic(&tiles[2],"gray_brick.bmp");
	mxhwnd.LoadGraphic(&tiles[3],"stone3.bmp");
	mxhwnd.LoadGraphic(&tiles[4],"stone4.bmp");
	mxhwnd.LoadGraphic(&tiles[5],"sand1.bmp");
	mxhwnd.LoadGraphic(&tiles[6],"sand2.bmp");
	mxhwnd.LoadGraphic(&tiles[7],"snow.bmp");
	mxhwnd.LoadGraphic(&tiles[8],"water1.bmp");
	mxhwnd.LoadGraphic(&tiles[9],"water2.bmp");
	mxhwnd.LoadGraphic(&tiles[10],"blacksky.bmp");
	mxhwnd.LoadGraphic(&tiles[11],"bluesky.bmp");
	mxhwnd.LoadGraphic(&tiles[12],"stone2.bmp");
	mxhwnd.LoadGraphic(&tiles[13],"red_brick.bmp");
	mxhwnd.LoadGraphic(&tiles[14],"blue_brick.bmp");
	mxhwnd.LoadGraphic(&wallpaper,"wallpaper.bmp");


	hero.load();
}
// game update
void Game::update()
{
	wallpaper.DisplayGraphic(0,0);
	drawmap();
	drawstats();
	hero.update();
}

// draw the current game map
void Game::drawmap()
{
	
	int start_x = 80;
	int start_y = 80;

	int sx = start_x;
	int sy = start_y;

	int row_count = 0;

	for(int i = 0; i < LevelSize; i++)
	{
		drawtile(sx,sy,level.level_block[i]);

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

// draw a tile
void Game::drawtile(int x, int y, int tile)
{
	tiles[tile].DisplayGraphic(x,y);
}


// incoming keypress
void Game::keypress(WPARAM wParam)
{
	console.keypress(wParam);
}

// drawing the game stats
void Game::drawstats()
{
	// drawing the background shapes
	COLORREF gamebg = RGB(200,200,200);
	mxhwnd.paint.mxdrawrect(640,0,800,600,gamebg,gamebg);
	mxhwnd.paint.mxdrawrect(0,480,800,600,gamebg,gamebg);
	mxhwnd.paint.mxdrawrect(640+5,5,800-10,600-5,RGB(0,0,0),RGB(0,0,0));
	mxhwnd.paint.mxdrawrect(5,485,640,600-5,RGB(0,0,0),RGB(0,0,0));
	// start drawing the stats
	hero.drawsprite(640+15,25,1);
	mxhwnd.text.settextcolor(RGB(200,0,0));
	mxhwnd.text.setfont(mainfont);
	char playerbuff[100];
	strcpy(playerbuff,"Player: ");
	strcat(playerbuff, hero.playername);
	mxhwnd.text.printtext(playerbuff, 640+15+32+5,25+16);
	char scorebuff[100];
	strcpy(scorebuff,"Score: ");
	char sbuf[10];
	itoa(hero.player_score,sbuf,10);
	strcat(scorebuff,sbuf);
	mxhwnd.text.printtext(scorebuff,640+15+32+5,25+16+20);
	char livesbuff[100];
	char lbuf[10];
	itoa(hero.player_lives,lbuf,10);
	strcpy(livesbuff,"Lives: ");
	strcat(livesbuff,lbuf);
	mxhwnd.text.printtext(livesbuff,640+15+32+5,25+16+20+20);
	char lifebuff[100];
	itoa(hero.player_life,lbuf,10);
	strcpy(lifebuff,"Health: ");
	strcat(lifebuff,lbuf);
	mxhwnd.text.printtext(lifebuff,640+15+32+5,25+16+20+20+20);
	char magicbuff[100];
	char mbuf[10];
	itoa(hero.player_magic,mbuf,10);
	strcpy(magicbuff,"Magic :");
	strcat(magicbuff,mbuf);
	mxhwnd.text.printtext(magicbuff,640+15+32+5,25+16+20+20+20+20);
	char goldbuff[100];
	strcpy(goldbuff,"Gold: ");
	char gbuf[10];
	itoa(hero.player_gold,gbuf,10);
	strcat(goldbuff,gbuf);
	mxhwnd.text.printtext(goldbuff,640+15+32+5,25+16+20+20+20+20+20);
	char rankbuff[100];
	char rbuf[10];
	itoa(hero.player_rank,rbuf,10);
	strcpy(rankbuff,"Rank: ");
	strcat(rankbuff,rbuf);
	mxhwnd.text.printtext(rankbuff,640+15+32+5,25+16+20+20+20+20+20+20);
	// start drawing the remote control colors
	mxhwnd.paint.mxdrawrect(640+10,25+16+20+20+20+20+20+20+20,800-15,600-10,RGB(150,150,150),RGB(150,150,150));
	// draw all the buttons for the menu

	// update the console
	console.update();

}