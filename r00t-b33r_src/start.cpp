#include "thehead.h"
#include "resource.h"

int bof;
int menu=1;
int linex;
char* binary;
bool option_mnu;
bool multiplayer_mnu;

void start::load()
{

	mxhwnd.LoadSound(&menu_snd,MAKEINTRESOURCE(IDR_WAVE4));
	mxhwnd.LoadGraphic(&icons,"bmps\\icons.bmp");
	mxhwnd.LoadGraphic(&intro_s,"bmps\\intro.bmp");
	mxhwnd.LoadGraphic(&selector,"bmps\\selector.bmp");
	mxhwnd.LoadGraphic(&gui,"bmps\\gui.bmp");

	
	intro_s.SetColorKey(RGB(0,0,0));
	icons.SetColorKey(RGB(0,255,0));
}




void start::update()
{

	KeyCheck();
	draw();
	
	if(option_mnu==true)
	option_m();
	
	if(multiplayer_mnu==true)
	multiplayer_m();
	
	
	animation();
	
	if(anim != 0)
	icons_sel();
}


void start::animation()
{

	switch(anim)
	{
	case 0:
		break;

	case 1:
		{
		if(mxhwnd.SyncChange())
		{
		bof++;
			
		if(bof>5)
			{
			new_icon();
			bof=0;
			}
		}
		
		break;
		}

	}





}



void start::screen()
{

		switch(sel_screen)
		{
		case 0: 
			break;


		case 1:
			break;

		}





}











void start::draw()
{
	
	selector.DisplayGraphic(15,70);
	selector.DisplayGraphic(470,70);
	
	intro_s.DisplayGraphicEx(0,42,36,75,35,128);
	intro_s.DisplayGraphicEx(0,42,36,75,35,198);
	intro_s.DisplayGraphicEx(0,42,36,75,35,278);
	intro_s.DisplayGraphicEx(0,42,36,75,35,356);
	
	
	
	
	
	mxhwnd.text.setfont(credit_font);
	mxhwnd.text.settextcolor(RGB(237,251,5));
	mxhwnd.text.printtext("Made by Jean-René Bédard",100,530);
	
	mxhwnd.text.printtext("Summer 2001-------all right reserved------",400,530);
	mxhwnd.text.setfont(menu_font);
	
	switch(menu)
	{
	case 1:
		newg();
		break;
	case 2:
		option();
		break;
	case 3:
		multiplayer();
		break;
	case 4:
		quit();
		break;
	}


	
}



void start::KeyCheck()
{
	
	
	if(mxhwnd.KeyCheck(DIK_DOWN))
	{
		
		if(menu_snd.PlayStatus()==false)
		{
			
		ShowCursor(false);
		option_mnu=false;
		multiplayer_mnu=false;
		
		menu_snd.Play();
		if(menu<4)
		menu++;
			
		icon=0;
		anim=0;
		linex=0;
		return;
		}
		
		if(menu_snd.PlayStatus()==true)
		{
		return;
		}
	}
	
	
	if(mxhwnd.KeyCheck(DIK_UP))
	{
		
		if(menu_snd.PlayStatus()==false)
		{
			
			ShowCursor(false);
			option_mnu=false;
			multiplayer_mnu=false;
			
			menu_snd.Play();
			if(menu>1)
			menu--;
			
			icon=0;
			linex=0;
			return;
		}
		
		if(menu_snd.PlayStatus()==true)
		{
		return;
		}
	}

	
	if(mxhwnd.KeyCheck(DIK_RETURN))
	{
	if(menu==1)
	{
		mxhwnd.SetScreen(ID_GAME);
	}
	
	if(menu==4)
	{
		//mxhwnd.media.close();
		mxhwnd.Kill();
	}	
	
	if(menu==2)
	{
		option_mnu=true;
	}
	
	if(menu==3)
	{
		multiplayer_mnu=true;
	}
	}

}



void start::newg()
{

	intro_s.DisplayGraphicEx(0,0,105,41,35,129);
	
	mxhwnd.text.settextcolor(RGB(214,214,214));
	mxhwnd.text.setbkcolor(RGB(34,23,174));
	
	mxhwnd.text.printtext("New Game",120,130);
	
	mxhwnd.text.settextcolor(RGB(134,134,134));
	mxhwnd.text.setbkcolor(RGB(0,0,0));
	
	mxhwnd.text.printtext("Option",120,200);
	mxhwnd.text.printtext("Multiplayer",120,280);
	mxhwnd.text.printtext("Quit",120,360);

	mxhwnd.paint.mxhorizontalline(290,linex+290,150,RGB(linex+45,linex+45,linex+45));
	mxhwnd.text.setfont(numeric_font);
	if(linex<200)
	{
		if(mxhwnd.SyncChange())
		{
			//strcat(binary,"a");
			//mxhwnd.text.printtext(binary,linex+200,150);
			linex += 10;
		}	    
	}
	else
	{
		mxhwnd.paint.mxdrawellipse(490,170,530,130,RGB(0,0,0),RGB(255,255,255));
		anim=1;
	}
	mxhwnd.text.setfont(credit_font);

}




void start::option()
{
	intro_s.DisplayGraphicEx(0,0,105,41,35,199);
	
	
	mxhwnd.text.settextcolor(RGB(214,214,214));
	mxhwnd.text.setbkcolor(RGB(34,23,174));
	
	mxhwnd.text.printtext("Option       ",120,200);
	
	mxhwnd.text.settextcolor(RGB(134,134,134));
	mxhwnd.text.setbkcolor(RGB(0,0,0));
	
	mxhwnd.text.printtext("New Game",120,130);
	
	mxhwnd.text.printtext("Multiplayer",120,280);
	mxhwnd.text.printtext("Quit",120,360);
	
	mxhwnd.paint.mxhorizontalline(290,linex+290,220,RGB(linex+45,linex+45,linex+45));
	if(linex<200)
	{
		if(mxhwnd.SyncChange())
		linex += 10;
    }
    else
	{
		mxhwnd.paint.mxdrawellipse(490,240,530,200,RGB(0,0,0),RGB(255,255,255));
		
		anim=2;
	}


}


void start::multiplayer()
{

	intro_s.DisplayGraphicEx(0,0,105,41,35,279);
	

	mxhwnd.text.settextcolor(RGB(214,214,214));
	mxhwnd.text.setbkcolor(RGB(34,23,174));
	mxhwnd.text.printtext("Multiplayer ",120,280);
	
	
	mxhwnd.text.settextcolor(RGB(134,134,134));
	mxhwnd.text.setbkcolor(RGB(0,0,0));
	
	mxhwnd.text.printtext("New Game",120,130);
	
	mxhwnd.text.printtext("Option",120,200);
	mxhwnd.text.printtext("Quit",120,360);

	mxhwnd.paint.mxhorizontalline(290,linex+290,300,RGB(linex+55,linex+55,linex+55));
	if(linex<200)
	{
		if(mxhwnd.SyncChange())
		linex += 10;
    }
    else
	{
		mxhwnd.paint.mxdrawellipse(490,320,530,280,RGB(0,0,0),RGB(255,255,255));
		
		anim=3;
	}



}





void start::quit()
{
	intro_s.DisplayGraphicEx(0,0,105,41,35,357);
	
	
	mxhwnd.text.settextcolor(RGB(214,214,214));
	mxhwnd.text.setbkcolor(RGB(34,23,174));
	mxhwnd.text.printtext("Quit           ",120,360);
	
	
	mxhwnd.text.settextcolor(RGB(134,134,134));
	mxhwnd.text.setbkcolor(RGB(0,0,0));
	
	mxhwnd.text.printtext("New Game",120,130);
	mxhwnd.text.printtext("Option",120,200);
	mxhwnd.text.printtext("Multiplayer",120,280);
	
	mxhwnd.paint.mxhorizontalline(290,linex+290,380,RGB(linex+45,linex+45,linex+45));
	if(linex<200)
	{
		if(mxhwnd.SyncChange())
		linex += 10;
    }
    else
	{
		mxhwnd.paint.mxdrawellipse(490,400,530,360,RGB(0,0,0),RGB(255,255,255));
		
		anim=4;
	}
}


int start::new_icon()
{
	if(icon > 5 || icon ==0)
	{ 
	return icon=1;	
	}
	
	if(icon==1)
	{
		return icon=2; 
	}

	if(icon ==2)
	{
		return icon=3; 
	}

	if(icon==3)
	{
		return icon=4; 
	}
	
	if(icon==4)
	{
		return icon=5; 
	}

	if(icon ==5)
	{
		return icon=6; 
	}

	if(icon==6)
	{
		return icon=1; 
	}
return 0;
}



void start::icons_sel()
{
	switch(icon)
	{
	case 0:
		break;

	case 1:
		icons.DisplayGraphicEx(0,0,41,41,489,129);	
		break;
	
	case 2:
		icons.DisplayGraphicEx(41,0,82,41,489,129);
		break;

	case 3:
		icons.DisplayGraphicEx(82,0,123,41,489,129);
		break;
	
	case 4:
		icons.DisplayGraphicEx(123,0,123+41,41,489,129);	
		break;
	
	case 5:
		icons.DisplayGraphicEx(123+41,0,123+82,41,489,129);
		break;

	case 6:
		icons.DisplayGraphicEx(123+82,0,123+123,41,489,129);
		break;

	}

}


















void start::option_m()
{

	mxhwnd.paint.mxdrawrect(550,100,750,450,RGB(113,113,113),RGB(113,113,113));
	mxhwnd.paint.mxdrawrect(560,110,740,440,RGB(0,63,127),RGB(0,63,127));
	
	ShowCursor(true);

	mxhwnd.text.setfont(option_font);
	mxhwnd.text.setbkcolor(RGB(0,63,127));
	
	
	
	mxhwnd.paint.mxdrawrect(570,130,690,168,RGB(0,63,127),RGB(164,181,196)); // carré control
	mxhwnd.paint.mxdrawrect(570,190,620,220,RGB(0,63,127),RGB(164,181,196));
	
	
	mxhwnd.text.settextcolor(RGB(120,238,247)); 
	mxhwnd.text.printtext("Control",580,115);    // frame caption
	mxhwnd.text.printtext("Music",580,175);
	
	
	mxhwnd.text.settextcolor(RGB(220,238,247));  // options
	mxhwnd.text.printtext("Keybord",590,135);
	mxhwnd.text.printtext("JoyStick",590,150);
	
	
	uncheck_box(575,150);								// check_boxe un checked
	uncheck_box(575,135);

	
	mxhwnd.paint.mxdrawrect(635,140,680,158,RGB(0,63,127),RGB(164,181,196));
	
	//button_box(630,147);

}




void start::multiplayer_m()
{

	mxhwnd.paint.mxdrawrect(550,100,750,450,RGB(113,113,113),RGB(113,113,113));
	ShowCursor(true);

	mxhwnd.text.setfont(option_font);
	mxhwnd.text.settextcolor(RGB(120,188,187));
	mxhwnd.text.setbkcolor(RGB(113,113,113));
	
	mxhwnd.text.printtext("Player's name:",600,110);
	mxhwnd.paint.mxdrawrect(600,140,700,170,RGB(113,113,113),RGB(100,100,100));

}













void start::uncheck_box(int obj_x,int obj_y)
{
	gui.DisplayGraphicEx(1,21,12,32,obj_x,obj_y);
}


void start::button_box(int obj_x,int obj_y)
{
	gui.DisplayGraphicEx(1,53,56,66,obj_x,obj_y);
}