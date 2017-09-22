// menuproc
// written by Jared Bruni
// www.lostsidedead.com

#include "thehead.h"
#include "supportj.h"


void MenuProc(WPARAM wParam)
{
	switch(wParam)
	{
	case ID_ABOUT:
		{
			ShowAbout("MasterKongLE","MasterKong LE\r\n written by jared bruni\r\nwww.lostsidedead.com\r\n\r\nopen source, open mind");
		}
		break;
	case ID_FILEEXIT:
		{
			SendMessage(mainwindow,WM_CLOSE,0,0);
		}
		break;
	case ID_FILENEW:
		{
			if(MessageBox(0,"Are you sure you wish to create a new flie?","Create new file?",MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				strcpy(filename,"Untitled1.mxk");
				
				for(int i = 0; i < LEVEL_SIZE; i++)
				{
					setimage(i,0,false);
				}

				level.gsp = 0;
				level.hsp = 1;

				reloadgrid();
				updatetitle();
			}

		}
		break;
	case ID_FILESAVE:
		{
			if(strcmp(filename,"Untitled1.mxk") == 0)
			{
				MenuProc(ID_FILESAVEAS);
				return;
			}

			if(strstr(filename,".mxk"))
			{} else
			{
				strcat(filename,".mxk");
			}

			savelevel(filename);
			updatetitle();
		}
		break;
	case ID_FILESAVEAS:
		{
			char ofile[255];
			if(savefile(ofile))
			{
				strcpy(filename,ofile);
				MenuProc(ID_FILESAVE);
				return;
			}
			else
			{
				return;
			}
		}
		break;
	case ID_FILELOAD:
		{
			char ofile[255];
			if(openfile(ofile))
			{
				strcpy(filename,ofile);
				loadlevel(filename);
				updatetitle();
				reloadgrid();
			}

		}
		break;
	}
}