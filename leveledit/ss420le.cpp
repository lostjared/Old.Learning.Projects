// LEVEL FILE .CPP
// JARED BRUNI (MASTER ON LSD)

#include "ss420le.h"



// list dump
void ss420_graphics::dumplist(HWND hwnd)
{

	SendMessage(hwnd,LB_RESETCONTENT,0,0);

	for(int i = 0; i < 300; i++)
	{
		if(graphic[i].on)
		{

		SendMessage(hwnd,LB_ADDSTRING,255,(LPARAM)(LPCSTR)graphic[i].gname);

		}

	}
}

int ss420_graphics::getoff()
{
	for(int i = 0; i < 300; i++)
	{
		if(graphic[i].on == false)
		{
			return i;// you got a empty node
		}
	}

	return -1; // list is full!
}

void ss420_graphics::add(char* buff)
{
	// when graphics are added; save there 'front name'
	// but the fileidentifer is really just some numbers
	int off;
	off = getoff();
	graphic[off].on = true;
	strcpy(graphic[off].gname,buff);

}

void ss420_graphics::rmv(int index)
{
	graphic[index].on = false;
	ZeroMemory(graphic[index].gname,sizeof(graphic[index].gname));
}


ss420_Pixel::ss420_Pixel()
{
	bg_index = SSNULL;
}

void ss420_Level::NULLBG()
{
	for(int z = 0; z < LEVEL_SIZE; z++)
	{
		grid.bg[z].bg_index = SSNULL;
	}
}


void DecompileLevel(char* filename,HINSTANCE hInst)
{


}

