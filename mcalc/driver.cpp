/* example calculator program
   to run under master console
   written by Jared Bruni
   www.lostsidedead.com
*/

#include "masterstream.h"

void printmenu();


int mastermain(char* argument)
{
	console << " Welcome to the example calculator program " << endl;
	console << " written specificly for planetsourcecode.com " << endl;
	char yourname[100];
	console << " please enter your name: ";
	console >> yourname;
	console << "\n Hello " << yourname << "!" << endl;
 
	bool go = true;
	while( go == true )
	{
		printmenu();
		int menu_item;
		console >> menu_item;

		switch(menu_item)
		{
		case 0:
			console << "\nerror: please enter a valid menu item" << endl;
			break;
		case 1:
			{

			int num1;
			int num2;
			int val;
			console << "\nplease enter the first digit: ";
			console >> num1;
			console << "\nplease enter the second digit: ";
			console >> num2;
			val = num1 + num2;
			console << "\n the results... " << endl;
			console << num1 << " + " << num2 << " = " << val << endl;
			}
			break;
		case 2:
			{
			int num1;
			int num2;
			int val;
			console << "\nplease enter the first digit: ";
			console >> num1;
			console << "\nplease enter the second digit: ";
			console >> num2;
			val = num1 - num2;
			console << "\n the results... " << endl;
			console << num1 << " - " << num2 << " = " << val << endl;
			}
			break;
		case 3:
			console.clear();
			break;
		case 4:
			go = false;
			break;
		}

		console << "\n";

	}


	console.pause();

	return (0);
}


void printmenu()
{
	console << "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ" << endl;
	console << "              MENU                 " << endl;
	console << " (1) - Add " << endl;
	console << " (2) - Sub " << endl;
	console << " (3) - Flush " << endl;
	console << " (4) - Exit  " << endl;
	console << "please enter item index: ";
}