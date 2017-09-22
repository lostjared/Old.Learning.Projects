// gameobject souce file
// jared bruni
// http://www.lostsidedead.com/gameprog/

#include "mxhead.h"

// pass in pointer to MasterXHWND object
void gameobj::init(MasterXHWND* mxhwndx)
{
	mxhwnd = mxhwndx;
}

// get & manipulate the subscreen

void gameobj::setsub(MASTERSCREEN screen)
{
	sub_screen = screen;
}

MASTERSCREEN gameobj::getsub()
{
	return sub_screen;
}
