/* I wrote this when I was 16, it orignaly was to be ran under mickey kawick's
engine (the one from age of the empires), I gutted it, edit it, and ported it
into my engine */



#include "Grid.h"
#include <fstream.h>

void GameGrid::init_graph()
{

		block2.setcolors();
        block2.x = 3;
		block2.y1 = 0;
		block2.y2 = 1;
		block2.y3 = 2;
	/*
	
	STRINGC str = "block_black.tga";
	grid_blocks[0]->Load (str, compress);
    str = "block_yellow.tga";
	grid_blocks[1]->Load(str,compress);
    str = "block_orange.tga";
	grid_blocks[2]->Load(str,compress);
	str = "block_ltblue.tga";
    grid_blocks[3]->Load(str,compress);
	str = "block_dblue.tga";
	grid_blocks[4]->Load(str,compress);
	str = "block_purple.tga";
	grid_blocks[5]->Load(str,compress);
	str = "block_pink.tga";
	grid_blocks[6]->Load(str,compress);
	str = "block_gray.tga";
	grid_blocks[7]->Load(str,compress);
	str = "block_red.tga";
	grid_blocks[8]->Load(str,compress);
	str = "block_green.tga";
	grid_blocks[9]->Load(str,compress);
	str = "block_clear.tga";
	grid_blocks[10]->Load(str,compress);

  

	grid_blocks[0] = DDLoadBitmap(gamescreen, "block_black.bmp");
	grid_blocks[1] = DDLoadBitmap(gamescreen, "block_yellow.bmp");
	grid_blocks[2] = DDLoadBitmap(gamescreen, "block_orange.bmp");
	grid_blocks[3] = DDLoadBitmap(gamescreen, "block_ltblue.bmp");
	grid_blocks[4] = DDLoadBitmap(gamescreen, "block_dblue.bmp");
	grid_blocks[5] = DDLoadBitmap(gamescreen, "block_purple.bmp");
	grid_blocks[6] = DDLoadBitmap(gamescreen, "block_pink.bmp");
	grid_blocks[7] = DDLoadBitmap(gamescreen, "block_gray.bmp");
	grid_blocks[8] = DDLoadBitmap(gamescreen, "block_red.bmp");
	grid_blocks[9] = DDLoadBitmap(gamescreen, "block_green.bmp");
	grid_blocks[10] = DDLoadBitmap(gamescreen, "block_clear.bmp");

 */


}

void GameGrid::uninit_graph()
{
/*
for(int x = 0; x < GRIDBLOCKMAX; x++) 
{

		if(grid_blocks[x]) { delete grid_blocks[x];}

}
*/
}


GameGrid::GameGrid()
{

init_graph();

}


GameGrid::~GameGrid()
{

uninit_graph();

}


void GameGrid::init_Grid()
{

	//gamescreen = screen;
    clearGrid();
	clearBlockGrid();
	block_going = false;
	//game_speed = 35; //.. Starting Speed
	update_frame = 0;
	Game.newgame();
    game_over = false;
}

void GameGrid::update()
{


	blockproc();
	paint();
	blockcheck();


	// paint

}


void GameGrid::clearBlockGrid()
{
	for(int i = 0; i < 17; i++)
	{

		for(int j = 0; j < 8; j++)
		{

			BlockGrid[i][j] = BLOCK_BLACK;

		}
	}


}

void GameGrid::clearGrid()
{

	for(int i = 0; i < 17; i++)
	{

		for(int j = 0; j < 8; j++)
		{

			Grid[i][j] = BLOCK_BLACK;

		}

	}



}

void GameGrid::paint()
{
// x = across
// y = down

//	ofstream fout("debug.txt");
int STARTPOSX = 200;
int STARTPOSY = 100;
int x = STARTPOSX,y = STARTPOSY;

	for(int i = 0; i < 17; i++)
	{


		for(int j = 0; j < 8; j++)
		{
     
// draw to screen
			//printscr.PrintText(x,y,gamescreen, "X");

			//			grid_blocks[Grid[i][j]]->DrawAt(gamescreen,x,y);

            x = x + 32;

		}
          x = STARTPOSX;
		  y = y + 16;
		// down lower
	}




	paint_block();


	// drawn to screen;

}

void GameGrid::paint_block()
{


	int STARTPOSX = 200;
int STARTPOSY = 100;
int x = STARTPOSX,y = STARTPOSY;

	for(int s = 0; s < 17; s++)
	{
       
		for(int i = 0; i < 8; i++)
		{
           // graphics
			// draw to screen.
			switch(BlockGrid[s][i])
			{

			case BLOCK_BLACK:
				// draw black
			//	mout.PrintText(x,y,gamescreen, "B!");
				//grid_blocks[BLOCK_BLACK]->DrawAt(gamescreen,x,y);
				break;

			case BLOCK_YELLOW:
              // draw yellow
				//mout.PrintText(x,y,gamescreen, "Y!");
//				grid_blocks[BLOCK_YELLOW]->DrawAt(gamescreen,x,y);
				break;

			case BLOCK_ORANGE:
//				grid_blocks[BLOCK_ORANGE]->DrawAt(gamescreen,x,y);

				break;
			case BLOCK_LTBLUE:
//				grid_blocks[BLOCK_LTBLUE]->DrawAt(gamescreen,x,y);

				break;
			case BLOCK_DBLUE:
//				grid_blocks[BLOCK_DBLUE]->DrawAt(gamescreen,x,y);

				break;
			case BLOCK_PURPLE:
//				grid_blocks[BLOCK_PURPLE]->DrawAt(gamescreen,x,y);
				break;
            case BLOCK_PINK:
//                grid_blocks[BLOCK_PINK]->DrawAt(gamescreen,x,y);
				break;
			case BLOCK_GRAY:
//				grid_blocks[BLOCK_GRAY]->DrawAt(gamescreen,x,y);
				break;
			case BLOCK_RED:
//				grid_blocks[BLOCK_RED]->DrawAt(gamescreen,x,y);
				break;
			case BLOCK_GREEN:
//				grid_blocks[BLOCK_GREEN]->DrawAt(gamescreen,x,y);
				break;
			case BLOCK_CLEAR:
//				grid_blocks[BLOCK_CLEAR]->DrawAt(gamescreen,x,y);
				break;

			}

		x = x + 32;

		}

		y = y + 16;
        x = STARTPOSX;
	}



}

void GameGrid::blockproc()
{

	if(block_going == false) 
	{

		// No Block, Add a  New One.
  //----------NEW BLOCK
	
		

		block = block2;

		block2.setcolors();
        block2.x = 3;
		block2.y1 = 0;
		block2.y2 = 1;
		block2.y3 = 2;
 //--------------
		block_going = true;

	}

// update count. if cout > speed, move_down, reset count

	blockmovedown(); // see if we need to move shit down
	clearBlockGrid();
	
	update_frame++;

	if(update_frame  > Game.speed) {

		move_down();
		update_frame = 0;

	}

	char u_f[5];
	char s[5];
	itoa(update_frame,u_f,5);
	itoa(Game.speed,s,5);



	BlockGrid[block.y1][block.x] = block.color.c1;
	BlockGrid[block.y2][block.x] = block.color.c2;
	BlockGrid[block.y3][block.x] = block.color.c3;
     
	

}

void GameGrid::HandleInput(int MOV)
{

	switch(MOV)
	{

	case MOV_LEFT:
	move_left();
		break;
	case MOV_RIGHT:
		move_right();
		break;
	case MOV_DOWN:
		move_down();
		break;
	case MOV_A:
	//	clearBlockGrid();
		block.colorswitch(D_UP);
		
		break;
	case MOV_B:
	//	clearBlockGrid();
		block.colorswitch(D_DOWN);
		
		break;

	}


}


void GameGrid::move_left()
{

	int px = block.x;
    int py1 = block.y1;
	int py2 = block.y2;
	int py3 = block.y3;

	if(px <= 0) { return; }

	if((Grid[py1][px-1] == 0) && (Grid[py2][px-1] == 0) && (Grid[py3][px-1] == 0))
	{

		block.x = px - 1;
		
	}

 
	

}

void GameGrid::move_right()
{
	int px = block.x;
    int py1 = block.y1;
	int py2 = block.y2;
	int py3 = block.y3;

	if(px >= 7) { return; }

	if((Grid[py1][px+1] == 0) && (Grid[py2][px+1] == 0) && (Grid[py3][px+1] == 0))
	{

		block.x = px + 1;
		
	}


 


}

void GameGrid::move_down()
{
	int px = block.x;
    int py1 = block.y1;
	int py2 = block.y2;
	int py3 = block.y3;


	if(Grid[2][px] != 0)
	{

	// Game over.
		gameover();

	}

	if(py3 >= 16) { setblock(); return; }// no way buddy
    if(py2 >= 15) { setblock(); return; }
	if(py1 >= 14) { setblock(); return; }

	if(Grid[py1+1][px] == 0) // First Block Space is OK
	{

		if(Grid[py2+1][px] == 0) { // Second Space is Ok


			if(Grid[py3+1][px] == 0) { // 3rd Spot is Ok

				// is ok to go down
				block.y1++;
				block.y2++;
				block.y3++;

			} else { setblock();}


		}

	}

}

void GameGrid::setblock()
{
  int bx = block.x;
  int by1 = block.y1;
  int by2 = block.y2;
  int by3 = block.y3;

  if((Grid[by1][bx] == 0) && (Grid[by2][bx] == 0) && (Grid[by3][bx] == 0))
  {

Grid[block.y1][block.x] = block.color.c1;
Grid[block.y2][block.x] = block.color.c2;
Grid[block.y3][block.x] = block.color.c3;
// block in place	

block_going = false; //  we need a new one

  }


}

void GameGrid::gameover()
{

	clearGrid();
	clearBlockGrid();
    game_over = true;

}

bool GameGrid::ifgameover()
{

return game_over;

}
void GameGrid::blockcheck()
{

	// see if games over, see if any lines,
	// if a line remove it, and call 'blockmovedown'


	// check across

	for(int i = 0; i < 17 ; i++)
	{

		for(int j = 0; j < 8 - 2; j++)
		{

			int currentColor;
			currentColor = Grid[i][j];
			if(currentColor != 0) {
			if((Grid[i][j] == currentColor) && (Grid[i][j+1] == currentColor) && (Grid[i][j+2] == currentColor))
			{


				Grid[i][j] = 0;
				Grid[i][j+1] = 0;
				Grid[i][j+2] = 0;
		      Game.addline();
		//BlockGone();
		blockmovedown();
		
                      
			}
			}
			

		}
	}

// check down


	for(int j = 0; j < 8; j++)
    {


		for(int i = 0; i < 17 - 3; i++)
		{

			int curColor = Grid[i][j];
			if(curColor != 0) {
			if((Grid[i+1][j] == curColor) && (Grid[i+2][j] == curColor))
			{

				//


            Grid[i][j] = 0;
			Grid[i+1][j] = 0;
			Grid[i+2][j] = 0;
            Game.addline();
			}
            }

		}

	}

}

void GameGrid::blockmovedown()
{



	for(int j = 0; j < 8; j++)
	{

		for(int i = 0; i < 17 - 3; i++)
		{

			// I = DOWN , J = ACROSS
			if(i < 16) // Not Last Block (We Dont Check it, its on the Bottom)
			{
                  
				if((Grid[i][j] != 0) && (Grid[i+1][j] == 0))
				{

					Grid[i+1][j] = Grid[i][j];
					Grid[i][j] = 0;


				}


			}

		}


	}
	
	

}

void GameGrid::movedowncheck()
{

	for(int j = 0; j < 8; j++)
	{

		for(int i = 0; i < 17 - 3; i++)
		{

			// I = DOWN , J = ACROSS
			if(i < 16) // Not Last Block (We Dont Check it, its on the Bottom)
			{
                  
				if((Grid[i][j] != 0) && (Grid[i+1][j] == 0))
				{

				blockmovedown();
                return; // somethings out of line
				}


			}

		}


	}




}
// ----- BLOCK



void Block::colorswitch(int dir)
{
// 

	if(dir == D_DOWN)
	{
     
		int px; int py1; int py2; int py3;
		px = x; py1 = y1; py2 = y2; py3 = y3;
	 
		int pc1; int pc2; int pc3;
		pc1 = color.c1; pc2 = color.c2; pc3 = color.c3;

		color.c1 = pc3; color.c2 = pc1; color.c3 = pc2;
		
		x = px; y1 = py1; y2 = py2; y3 = py3;
	}

	if(dir == D_UP)
	{

		int px; int py1; int py2; int py3;
		px = x; py1 = y1; py2 = y2; py3 = y3;
	 
		int pc1; int pc2; int pc3;
		pc1 = color.c1; pc2 = color.c2; pc3 = color.c3;

		color.c1 = pc2; color.c2 = pc3; color.c3 = pc1;
		
		x = px; y1 = py1; y2 = py2; y3 = py3;


	}
}

void Block::setcolors()
{

	color.c1 = rand()%10;
	color.c2 = rand()%10;
	color.c3 = rand()%10;

	if(color.c1 == 0) { color.c1++; }
	if(color.c2 == 0) { color.c2++; }
	if(color.c3 == 0) { color.c3++; }

}


void AGame::newgame()
{

	score = 0;
	lines = 0;
	speed = 35; // = level 1
    plines = 0;

}

void AGame::addline()
{

   score = score + 200;
   lines++;

   plines++;

   if(plines >= 10)
   {

	   plines = 0;
	   speed = speed - 5;

   }

//   BlockGone();
   blocksound();
   // play the sound of the block gone

}