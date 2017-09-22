#ifndef __MP_H__
#define __MP_H__

#include<stdio.h>
#include<stdlib.h>

enum { D_DOWN = 1, D_UP = 2 };
enum { STARTX = 185 , STARTY = 95 };
enum { BLOCK_BLACK = 0, BLOCK_YELLOW, BLOCK_ORANGE, BLOCK_LTBLUE, BLOCK_DBLUE, BLOCK_PURPLE, BLOCK_PINK,BLOCK_GRAY,BLOCK_RED,BLOCK_GREEN,BLOCK_CLEAR, BLOCK_FADE };

extern void fill_rect(int x, int y, int w, int h, unsigned long color);
// the game object
const int BR  = 5;
void proccess_move_down();

struct Color {
	int c1,c2,c3;
};

struct GameBlock {
	struct Color col;
	int x,y;
};

#define GRID_X 19
#define GRID_Y 26

static int Tiles[GRID_X+25][GRID_Y+25] = { 0 };
static struct GameBlock gblock,nblock;
static int score = 0, lines = 0;
const int data_w = 32, data_h = 16;




void block_randcolor(struct GameBlock *c) {
	do {

		c->col.c1 = 1+(rand()%8);
		c->col.c2 = 1+(rand()%8);
		c->col.c3 = 1+(rand()%8);

	} while ( c->col.c1 == c->col.c2 && c->col.c1 == c->col.c3 );

}

void block_copy(struct GameBlock *in, struct GameBlock *out) {
	out->col.c1 = in->col.c1;
	out->col.c2 = in->col.c2;
	out->col.c3 = in->col.c3;
}

void shiftcolor(struct GameBlock *c, int dir)
{
	int ic1;
	int ic2;
	int ic3;
	ic1 = c->col.c1;
	ic2 = c->col.c2;
	ic3 = c->col.c3;

	if(dir)
	{
		c->col.c1 = ic3;
		c->col.c2 = ic1;
		c->col.c3 = ic2;
	}
	else
	{
		c->col.c1 = ic2;
		c->col.c2 = ic3;
		c->col.c3 = ic1;
	}
}

void init_matrix() {
	int i,z;
	int total = 0;

	memset(Tiles, 0, sizeof(Tiles));
	block_randcolor(&gblock);
	block_randcolor(&nblock);
	gblock.x = GRID_X/2;
	gblock.y = 0;
	Tiles[16][0] = 0;
	Tiles[16][3] = 0;

	// check to see if its all good
}



// color constants dont stand for the acutal colors of blocks
void draw_block(int x, int y, int type) {

	fill_rect(x,y,data_w,data_h, type);
}



void draw_grid() {

	int offset_x = 7, offset_y = 7, offset_y2 = 7;
	int i,z;
	//fill_rect(100,0,260,272,0x0);
	for(i = 0; i < GRID_X; i++) {
		for(z = 0; z < GRID_Y; z++) {
			
			draw_block(offset_x+i,offset_y+z, Tiles[i][z]);

			offset_y += 16;
		}

		offset_y2 = offset_y;
		offset_y = 7;
		offset_x += 32;
	}

	offset_x = 7, offset_y = 7, offset_y2 = 7;

	for(i = 0; i < GRID_X; i++) {
		for(z = 0; z < GRID_Y; z++) {

			if(gblock.x == i && gblock.y == z) {
				
				draw_block(offset_x+i,offset_y+z, gblock.col.c1);
				draw_block(offset_x+i,offset_y+z+data_h, gblock.col.c2);
				draw_block(offset_x+i,offset_y+z+data_h*2,gblock.col.c3);
			}
			offset_y += 16;
			
		}
		offset_y2 = offset_y;
		offset_y = 7;
		offset_x += 32;
	
	}

}

void release_block() {

	block_copy(&nblock,&gblock);
	block_randcolor(&nblock);
	gblock.x = GRID_X/2;
	gblock.y = 0;

}

extern void gameover();

void setblock() {

	if(gblock.y <= 3) {
		// game over
		gameover();
		//init_matrix();
		return;
	}
	Tiles[gblock.x][gblock.y] = gblock.col.c1;
	Tiles[gblock.x][gblock.y+1] = gblock.col.c2;
	Tiles[gblock.x][gblock.y+2] = gblock.col.c3;
	release_block();
}

void proc_move() {
	static int wait = 0; int platform_wait = 30;
	
	proccess_move_down();

	if( gblock.y +  3 >= GRID_Y )
	{
			setblock();
			return;
	}
	
	if( Tiles[ gblock.x ][ gblock.y + 3] != 0 )
	{
		setblock();
		return;
	}


#ifndef FOR_PSP
	platform_wait = 0;
#endif
	
	if(++wait > 5)
	{

	if( gblock.y < GRID_Y-3 )
	{
		gblock.y++;
	}
	wait = 0;
	}


}



void move_left() {
	if( Tiles [ gblock.x-1 ] [ gblock.y ] == 0 && Tiles [ gblock.x-1 ] [ gblock.y + 1 ] == 0 && Tiles [gblock.x-1 ] [ gblock.y  + 1  ] == 0 && Tiles [ gblock.x-1 ] [ gblock.y + 3 ] == 0)

	if(gblock.x > 0)
	{
		gblock.x--;
	}
}

void move_right() {

	if( Tiles [ gblock.x+1  ] [ gblock.y ] == 0 && Tiles [ gblock.x+1 ] [  gblock.y + 1 ] == 0 && Tiles [ gblock.x+1 ] [ gblock.y  + 1 ] == 0 && Tiles [ gblock.x+1 ] [ gblock.y + 3 ] == 0)

	if(gblock.x < GRID_X-1)
		gblock.x++;
}



void proc_blocks() {
	int i,z;
	for(i = 0; i < GRID_X; i++) {
		for(z = 0; z < GRID_Y-2; z++) {

			if(Tiles[i][z] != 0 && Tiles[i][z+1] == 0) {
				Tiles[i][z+1] = Tiles[i][z];
				Tiles[i][z] = 0;
			}
		}
	}
}



void addline() {
	score += 5;
	lines++;
}

int bounds(int x, int y) {
	if(x >= 0 && y >= 0)
		return 1;
	return 0;
}

void proccess_move_down() {
	int i,z;

	for(i = 0; i < GRID_X; i++) {
		for(z = 0; z < GRID_Y; z++) {
			int c = Tiles[i][z];
			if(c != 0) {
				if(c == Tiles[i][z+1] && c == Tiles[i][z+2]) {
					Tiles[i][z] = 0;
					Tiles[i][z+1] = 0;
					Tiles[i][z+2] = 0;
					addline();
					return;
				}

				if(c == Tiles[i+1][z] && c == Tiles[i+2][z]) {
					Tiles[i][z] = 0;
					Tiles[i+1][z] = 0;
					Tiles[i+2][z] = 0;
					addline();
					return;
				}
				if(c == Tiles[i+1][z+1] && c == Tiles[i+2][z+2]) {
					Tiles[i][z] = 0;
					Tiles[i+1][z+1] = 0;
					Tiles[i+2][z+2] = 0;
					addline();
					return;
				}

				if(bounds(i-2,z-2) && c == Tiles[i-1][z-1] && c == Tiles[i-2][z-2]) {
					Tiles[i][z] = 0;
					Tiles[i-1][z-1] = 0;
					Tiles[i-2][z-2] = 0;
					addline();
					return ;
				}

				if(bounds(i-2,z) && c == Tiles[i-1][z+1] && Tiles[i-2][z+2] == c) {

					Tiles[i][z] = 0;
					Tiles[i-1][z+1] = 0;
					Tiles[i-2][z+2] = 0;
					addline();
					return;
				}

				if(bounds(i,z-2) && c == Tiles[i+1][z-1] == c && Tiles[i+2][z-2] == c) {
					Tiles[i][z] = 0;
					Tiles[i+1][z-1] = 0;
					Tiles[i+2][z-2] = 0;
					addline();
					return;
				}
			}
		}
	}
	proc_blocks();
}

#endif
