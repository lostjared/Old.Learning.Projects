// Cr.h
// Poem Header File

#include <windows.h>
#include "c:\sslib\masterx.h"

#define PSIZE 100
#define SX 226
#define SY 400-10

// node
struct cr
{
	char buff[100];
	COLORREF color;
	int x;
	int y;
	int cswitch;
	bool on;
	void update();
};

// the class
class crPoem
{
	int rcount;
	MasterXHWND* mxhwnd;
public:
	int off;

	cr data[PSIZE];
	COLORREF curbg;

	void init(MasterXHWND*);
	void add(char* buff,COLORREF rgb);
	void release();
	void update();
};