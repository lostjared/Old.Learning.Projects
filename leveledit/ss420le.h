// SS420LE.H
// HERES THE HEADER FILE
// JARED BRUNI
#include <string.h>
#include <windows.h>
#include <fstream.h>
#include "c:\sslib\ssxrcex.h"


#define SSNULL -1
#define LEVEL_SIZE 1040*200
#define GSIZE 30



// SS420 Level Pixel
struct ss420_Pixel
{
	int bg_index;
	bool solid;
	bool kill;
	bool color;
	COLORREF hcolor;
	ss420_Pixel();

};
struct ss420_Item
{
	bool on;
	int  item_index;
};

struct ss420_Enemy
{
	bool on;
	int en_index;
};


struct ss420_Grid
{
	ss420_Pixel bg[LEVEL_SIZE];
	ss420_Item  item[LEVEL_SIZE];
	ss420_Enemy en[LEVEL_SIZE];
};

// level graphics package
struct ss420_g
{
	bool on;
	char gname[100];
	char loadname[20];
};

struct ss420_graphics
{
	ss420_g graphic[GSIZE];
	int getoff();
	void dumplist(HWND);
	void add(char* buff);
	void rmv(int index);
};

struct ss420_bgobject
{
	bool on;
	char name[25];
	bool solid;
	bool kill;
	char script[200];
	int  bg_index;
};

struct ss420_itobject
{
	bool on;
	bool solid;
	bool kill;
	char script[200];
	int  it_index;
};

class ss420_Level
{
public:
	ss420_Grid grid;
	ss420_graphics graphics;
	ss420_bgobject bgobject[500];

	char level_intro[1000];
	char level_end[1000];
	char levelname[100];
	int level_len;

	void NULLBG();
};

void DecompileLevel(char* filename,HINSTANCE hInst);
