/*

  MasterPiece written utilizing MasterX SDK
  written by Jared Bruni


  www.lostsidedead.com



  Open Source, Open Mind

   "I am only as I think and believe"


*/

#include "thehead.h"




void Intro::ondraw()
{
	if(screen_pos == 0)
	{

	introg.DisplayGraphic(0,0);

	}
	else
	{
		ibg[icur].DisplayGraphic(0,0);
	}
}

void Intro::onlogic()
{
	static int wait = 0;
	static int wait2 = 0;


	if(screen_pos == 0)
	{

	wait++;

	if(wait > 50)
	{
		wait = 0;
		wait2 = 0;
		screen_pos = 1;
		return;
	}

	}
	else
	{
		wait2++;
		if(wait2 > 3)
		{
			wait2 = 0;
			icur ++ ;// increment
			if(icur > 5)
			{
				icur = 0;
				mxhwnd.SetScreen(ID_START);
				screen_pos = 0;
				return;
			}
		


		}
	}
}