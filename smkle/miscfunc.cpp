

#include "thehead.h"


// get the grid index by point
int ArrayIndexByPoint(int x, int y)
{
	int bx,by;
	bx = 0; by = 0;
	int gcount = 0;


	for(int i = 0; i < 700-4+24; i++)
	{

		if((x > bx) && (x < bx+16) && (y>by) && (y<by+16))
		{

			return i;
		}

	by = by + 16;
	gcount++;
	if(gcount > 23)
	{
		gcount = 0;
		by = 0;
		bx = bx + 16;
	}

	}


	// failure

	return -1;
}


void reloadgrid()
{
	for(int i = 0; i < LEVEL_SIZE; i++)
	{
		if( i == level.gsp )
		{
			SendMessage(grid[i],STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)images[6]);
			continue;
		}
		
		if( i == level.hsp )
		{
			SendMessage(grid[i],STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)images[7]);
			continue;
		}
					
			setimage(i,level.blocks[i].block,level.blocks[i].solid);
		
	}
}

void setimage(int pos, int image, bool solid)
{
	level.blocks[pos].block = image;
	level.blocks[pos].solid = solid;
	SendMessage(grid[pos],STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)images[image]);
}

void setbrick(int x, int y)
{
	int index = ArrayIndexByPoint(x,y);

	if(index == level.gsp || index == level.hsp)
	{
		return;
	}
	if(index != -1)
	{
		img_tool = SendMessage(tcombo,CB_GETCURSEL,0,0);
		
		switch(img_tool)
		{
		case 0:// standard square
			{

		setimage(index,img_index,isolid(img_index));

			}
		break;
		case 1:// square
			{
				if(index + 25 < LEVEL_SIZE)
				{

				setimage(index,img_index,isolid(img_index));
				setimage(index+1,img_index,isolid(img_index));
				setimage(index+24,img_index,isolid(img_index));
				setimage(index+25,img_index,isolid(img_index));

				}
			}
			break;
		case 2:// FILL
			{
				for(int i = 0; i < LEVEL_SIZE; i++)
					{
						setimage(i,img_index,isolid(img_index));
					}

					reloadgrid();
					return;

			}
			break;
		case 3:// CLEAR
			{
					for(int i = 0; i < LEVEL_SIZE; i++)
					{
						setimage(i,0,false);
					}

					reloadgrid();

			}
			break;
		}
	}
}




// isolid
bool isolid(int tile)
{
	switch(tile)
	{
	case 0:
		return true;
		break;
	case 1:
		return true;
		break;
	case 2:
		return true;
		break;
	case 3:
		return false;
		break;
	case 4:
		return true;
		break;
	case 5:
		return false;
		break;
	}

	return true;
}

// update title

void updatetitle()
{
	char mstr[100];
	sprintf(mstr,"MasterKong LE - %s",filename);
	SendMessage(mainwindow,WM_SETTEXT,strlen(mstr)+1,(LPARAM)(LPCSTR)mstr);
}

// save level structure to file
void savelevel(char* filename)
{
	ofstream fout(filename,ios::binary);
	fout.write((char*)&level,sizeof(level));
	fout.close();
}

// load the level from file into the structure
void loadlevel(char* filename)
{
	ifstream fin(filename,ios::binary);
	fin.read((char*)&level,sizeof(level));
	fin.close();
}

// the dialogs

bool openfile(char* cFile)
{
	char szFile[200];


OPENFILENAME ofn;       // common dialog box structure

strcpy(szFile, "*.mxk");

// Initialize OPENFILENAME
ZeroMemory(&ofn, sizeof(OPENFILENAME));
ofn.lStructSize = sizeof(OPENFILENAME);
ofn.hwndOwner = mainwindow;
ofn.lpstrFile = szFile;
ofn.nMaxFile = sizeof(szFile);
ofn.lpstrFilter = "masterx kong\0*.mxk\0ALL\0*.*\0";
ofn.nFilterIndex = 1;
ofn.lpstrFileTitle = NULL;
ofn.nMaxFileTitle = 0;
ofn.lpstrInitialDir = NULL;
ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


if (GetOpenFileName(&ofn)==TRUE) 
{
strcpy(cFile, ofn.lpstrFile);
return true;
}
else
{
return false;
}

}

bool savefile(char* cFile)
{

	char szFile[200];


OPENFILENAME ofn;       // common dialog box structure

strcpy(szFile, "*.mxk");

// Initialize OPENFILENAME
ZeroMemory(&ofn, sizeof(OPENFILENAME));
ofn.lStructSize = sizeof(OPENFILENAME);
ofn.hwndOwner = mainwindow;
ofn.lpstrFile = szFile;
ofn.nMaxFile = sizeof(szFile);
ofn.lpstrFilter = "masterx kong\0*.mxk\0ALL\0*.*\0";
ofn.nFilterIndex = 1;
ofn.lpstrFileTitle = NULL;
ofn.nMaxFileTitle = 0;
ofn.lpstrInitialDir = NULL;
ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


if (GetSaveFileName(&ofn)==TRUE) 
{
strcpy(cFile, ofn.lpstrFile);
return true;
}
else
{
return false;
}


}
