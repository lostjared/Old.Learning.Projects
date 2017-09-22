/* Open Source, Open Mind 
   MXC (MasterX Console)
   Fourtne Bot
   written as a Example on how to use
   MasterLibrary to write a MasterConsole Program
 */


#define MASTER_IOSTREAM
#include "masterlibrary2.h"
#include<time.h>

void displayfourtne();
int  getrand();

int mastermain(char* argument)
{
	char name[255];
	srand(time(NULL));
	console << " welcome to the fourtne bot \n";
	console << " please enter your name: " >> name << endl;
	console << " welcome " << name << " now for your fourtne ! " << endl;
	displayfourtne();
	console.pause();
	return (0);
}

// random 1-10
void displayfourtne()
{
	switch(getrand())
	{
	case 1:
		console << " you hold knowledge of 1 " << endl;
		break;
	case 2:
		console << " good things will come to you if you are patient " << endl;
		break;
	case 3:
		console << " you dont believe in this fate stuff " << endl;
		break;
	case 4:
		console << " cause 1 and 1 and 1 = 3 " << endl;
		break;
	case 5:
		console << " you will succed in your life " << endl;
		break;
	case 6:
		console << " everyone wants a piece of you " << endl;
		break;
	case 7:
		console << " you will be succcesful " << endl;
		break;
	case 8:
		console << " watch out -> there lookin at you " << endl;
		break;
	case 9:
	case 10:
		console << " peace love and harmony flow to you " << endl;
		break;
	}
}

int getrand()
{
	int value = 0;
	do
	{
		value = rand()%10;

	} while ( value <= 0 );

	return value;
}