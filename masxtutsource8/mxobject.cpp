// the masterX base object
// jared bruni
// http://www.lostsidedead.com/gameprog/

#include "mxhead.h"

// pass in the pointer to the masterX hwnd object
void mgcobject::init(MasterXHWND* mxhwndx)
{
	mxhwnd = mxhwndx;
}
// set the subscreen value
void mgcobject::setsub(MASTERSCREEN scr)
{
	sub_screen = scr;
}
// get the subscreen value
MASTERSCREEN mgcobject::getsub()
{
	return sub_screen;
}