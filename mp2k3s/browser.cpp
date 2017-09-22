/*

  MasterPeice written utilizing MasterX SDK
  written by Jared Bruni


  www.LostSideDead.com

  Open Source, Open Mind
 
 "I am only as I think and believe"

 a beautiful MasterPeace

*/

#include"thehead.h"



void FileBrowser::draw()
{
	int sx = 10, sy = 100, sw = 620, sh = 350;
	mxhwnd.paint.mxdrawrect (sx,sy,sx + sw, sy + sh,0x0,0x0);
	mxhwnd.text.settextcolor(RGB(255,0,0));

	switch(cursor_position)
	{
	case 0:
		{
			mxhwnd.text.printtext("choose a drive using the arrow keys then press enter", 100, 100);
			int dy = 120;
			long dlen = static_cast<long>(SendMessage(hdrive,LB_GETCOUNT,0,0));
			for(long z = 0; z < dlen; z++)
			{
				char dbuffer[255];
				SendMessage(hdrive,LB_GETTEXT,z,(LPARAM)(LPCSTR)dbuffer);
				mxhwnd.text.printtext(dbuffer,100,dy);
				dy += 15;
			}

			mxhwnd.text.printtext("=)>",px, py);
		}
		break;
	case 1:
		{
			mxhwnd.text.printtext("choose a folder/file using the arrow keys then press enter", 100,100);
			long len = static_cast<long>(SendMessage(hdir,LB_GETCOUNT,0,0));

			mxhwnd.text.printtext("....",100,120);
			int dy = 135;
			for(long i = start_pos; i < start_pos+21; i++)
			{
				if(i < len)
				{

				char dbuffer[255];
				SendMessage(hdir,LB_GETTEXT,i,(LPARAM)(LPCSTR)dbuffer);
				mxhwnd.text.printtext(dbuffer,100,dy);
				dy += 15;

				}
			}

			mxhwnd.text.printtext("=)>",px,py);
			mxhwnd.text.printtext(file_path,300,430);
		}
		break;
	}
}
	

void FileBrowser::logic()
{

}