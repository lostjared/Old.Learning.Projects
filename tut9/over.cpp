// the over object
// jared bruni
// http://www.lostsidedead.com/gameprog/

#include "mxhead.h"
// update the over object
void over::update()
{
	mxhwnd->text.printtext("application over",100,100);
	mxhwnd->text.printtext("escape to quit",100,130);
}
// check if keys are pressed
void over::keycheck()
{

}