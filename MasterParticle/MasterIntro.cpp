// masterintro game object
// written by jared bruni
// www.lostsidedead.com

#include "thehead.h"



// introduction load
void MasterIntro::load()
{
	int font_size = 2;
	for(int i = 0; i <= 10; i++)
	{
		mfonts[i] = MakeFont("Arial",font_size);
		font_size += 2;
	}

	font_index = 0;
	font_dir = true;
	fade_color = 0;
}

// update
void MasterIntro::update()
{
	mxhwnd.paint.mxdrawrect(0,0,640,480,fade_color,fade_color);
	mxhwnd.text.setbkcolor(fade_color);
	mxhwnd.text.settextcolor(RGB(rand()%255,rand()%255,rand()%255));
	mxhwnd.text.setfont(mfonts[font_index]);
	mxhwnd.text.printtext("MasterParticle Example - written by Jared Bruni",30,30);

	if(mxhwnd.SyncChange())
	{


	if(font_dir)
	{
		font_index++;

		if(font_index > 10)
		{
			font_index = 10;
			font_dir = false;
		}
	}
	else
	{
		font_index--;
		if(font_index < 0)
		{
			font_index = 0;
			font_dir = true;
		}
	}

	fade_color += 10;

	}

	if(fade_color >= 0xFF)
	{
		mxhwnd.SetScreen(ID_PARTICLE);
	}

}
