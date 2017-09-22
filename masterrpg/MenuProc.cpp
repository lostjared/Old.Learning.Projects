// menu message proccess
// written by jared bruni
// www.lostsidedead.com

#include "thehead.h"


// menu proc

void MenuProc(WPARAM wParam)
{

	switch(wParam)
	{
	case ID_FILENEW:
		{

		}
		break;
	case ID_FILELOAD:
		{
			// load a map
			char lfile[100];
			if(openfile(lfile))
			{
				strcpy(filename,lfile);

				ifstream fin(filename,ios::binary);
				fin.read((char*)&level,sizeof(level));
				fin.close();
				UpdateTitle();
				updatemap();
			}
		}
		break;
	case ID_FILESAVE:
		{
			// if its a new document
			if(strcmp(filename,"Untitled.mrpg") == 0)
			{
				MenuProc(ID_FILESAVEAS);
				return;
			}

			ofstream fout(filename,ios::binary);
			fout.write((char*)&level,sizeof(level));
			fout.close();

		}
		break;
	case ID_FILESAVEAS:
		{
			char fname[100];
			if(savefile(fname))
			{
				strcpy(filename,fname);
				MenuProc(ID_FILESAVE);
				return;
			}

			UpdateTitle();
		}
		break;
	case ID_FILEEXIT:
		{
			SendMessage(mainwindow,WM_CLOSE,0,0);
		}
		break;
	}
}