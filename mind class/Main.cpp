// memory scheme console

#include <iostream.h>
#include "now.h"

JB_Now the_now;

void main()
{
	the_now.start();

	while(the_now.im_alive())
	{
		the_now.thought();
	}
}
