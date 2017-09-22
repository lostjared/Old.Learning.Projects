// the source file for the intro 
// written by jared bruni
// www.lostsidedead.com

#include "thehead.h"

// function prototypes
void intro_draw();
void intro_logic();
// varaibles
int intro_count = 0;

// the intro update
void intro_update()
{
	intro_draw();
	if(mxhwnd.SyncChange())
	{
		intro_logic();
	}
}

// inro draw
void intro_draw()
{
	drawsprite(0,0,INTRO);
}

// intro logic
void intro_logic()
{
	intro_count++;
	if(intro_count > 50)
	{
		intro_count = 0;
		mxhwnd.SetScreen(ID_START);
	}
}
