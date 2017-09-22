// game source file

#include "thehead.h"



void Game::load()
{
	hero.Init(mxhwnd);
	hero.load();
}

void Game::update()
{
	keycheck();
	draw();
}

void Game::keycheck()
{

}

void Game::draw()
{
	if(startx == true)
	{
		drawstart();
	}
	else
	{

	drawmap();
	drawhero();
	drawscore();
	
	}
}

void Game::drawscore()
{
	char thelife[10];
	itoa(hero.life,thelife,10);
	char thescore[10];
	itoa(score,thescore,10);

	char buff[100];
	strcpy(buff,"Score: ");
	strcat(buff,thescore);
	strcat(buff," Life: ");
	strcat(buff,thelife);
	mxhwnd->text.setfont(sfont);
	mxhwnd->text.setbkcolor(RGB(0,0,0));
	mxhwnd->text.settextcolor(RGB(rand()%255,rand()%255,rand()%255));
	mxhwnd->text.printtext(buff,20,10);

}

void Game::drawhero()
{
	hero.update();
}

void Game::drawmap()
{
	// draw fmap

	for(int i = 0; i < 200; i++)
	{
		if(fmap.fire[i].on == true)
		{
			
			// draw fireball
			mxhwnd->text.printtext("test",fmap.fire[i].x,fmap.fire[i].y);
		}
	}
}

// draw the start
void Game::drawstart()
{
	COLORREF back;
	back = RGB(rand()%255,rand()%255,rand()%255);
	mxhwnd->paint.mxdrawrect(0,0,640,480,back,back);
	
	mxhwnd->text.setbkcolor(back);
	mxhwnd->text.setfont(bigfont);
	mxhwnd->text.settextcolor(RGB(0,0,0));

	switch(start_pos)
	{
	case 0:
		mxhwnd->text.printtext("Get Ready...",100,480/2-100);
		break;
	case 1:
		mxhwnd->text.printtext("Entering Level",100,480/2-100);
		break;
	case 2:
		mxhwnd->text.printtext(" Go !!",100,480/2-100);
		break;
	case 3:
		startx = false;
		break;
	}

	start_count++;

	if(start_count > 40)
	{
		start_pos++;
		start_count = 0;
	}
}
