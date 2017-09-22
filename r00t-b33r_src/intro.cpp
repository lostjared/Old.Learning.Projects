//By Deslock
// its the main menu....well there's no menu but the title of the game

#include "thehead.h"
#include "resource.h"



void intro::load()
{
   mxhwnd.text.setfont(menu_font);    
	mxhwnd.text.settextcolor(RGB(23,245,43));
   mxhwnd.LoadGraphic(&root,"bmps\\root.bmp");

   root.SetColorKey(RGB(17,196,255));


}




void intro::intro_update()
{
   mxhwnd.paint.mxdrawrect(100,50,700,400,RGB(112,40,16),RGB(191,192,192));

   
   root.DisplayGraphic(200,55);

	mxhwnd.text.setbkcolor(RGB(0,0,0));
   mxhwnd.text.printtext("Up arrow or joystick up              : Move Up",20,460);
	mxhwnd.text.printtext("Down arrow or joystick down      : Move Down",20,480);
	mxhwnd.text.printtext("Space or button 1                      : pour & serve!",20,500);
	mxhwnd.text.printtext("Escape                                     : Exit",20,520);
	
	mxhwnd.paint.mxdrawrect(490,450,690,530,RGB(16,2,202),RGB(134,203,165));

	mxhwnd.text.setbkcolor(RGB(16,2,202));
	mxhwnd.text.printtext("Made by Deslock",500,460);
	mxhwnd.text.printtext("Jean-René Bédard",500,480);
	mxhwnd.text.printtext("deslock1@hotmail.com",500,500);

}




