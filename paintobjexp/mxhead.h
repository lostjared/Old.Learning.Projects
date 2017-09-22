// app's header file
// jared bruni

#include "masterx.h"

class dprog
{
	MasterXHWND* mxhwnd;
	int cir_add;
public:
	void init(MasterXHWND* mxhwndx);
	void update();
	void drawsquare();
	void drawcircle();
	void drawstuff();
};
