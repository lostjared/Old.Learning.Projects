/* Example Skeleton for masterio 
   written by Jared Bruni
   www.LostSideDead.com
*/

#include "masterio.h"



int mastermain(char* argument)
{
	char user_name[255];
	mprintf("%s\n%s\n%s\n"," Welcome to the masterio example program ", " Written by Jared Bruni ", " www.LostSideDead.com ");
	mprintf("%s:","please enter your name");
	mscanf("%s", user_name );
	mprintf("\n%s%s!\nplease enter a number: "," Hello ", user_name);
	
	switch(miint())
	{
     default:
		mprintf("\nyou didnt pick 1 :(\n");
		break;
	case 1:
		mprintf("\nyou picked 1");
		break;
	}
	
	mpause();

	return (0);
}

 /* structured vrs OO ? I like them both :) */