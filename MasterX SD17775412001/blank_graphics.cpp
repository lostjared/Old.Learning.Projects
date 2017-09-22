// I have no idea who wrote winbgi, so dont give me credit for it
// however I did edit it, and expand it so that it utilizes masterX
// www.lostsidedead.com

//
// Project Name: 
//
// Author: 
// Date  : 

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "graphics.h"

#define ESC 0x1b

void main() 
{
	srand(time(NULL));  // Seed the random number generator
	int GraphDriver=0,GraphMode=0; initgraph( &GraphDriver, &GraphMode, "" ); // Start Window


	getch(); //Wait for a key. (When main function ends, the window will close)
}

