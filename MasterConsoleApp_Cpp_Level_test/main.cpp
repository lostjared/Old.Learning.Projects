/* a MasterConsole application
   written by Jared Bruni
   www.LostSideDead.com

  "Open Source, Open Mind"
*/

#include "masterstream.h"

char user_name[255];
int  user_score = 0;

void game();
void score();
bool again();
int  getanswer();
void checkanswer( int answer, int question );


int mastermain(char* argument)
{
	console.printf("\nwelcome to the C++ level test\n you will be asked a seires of multiple choice questions\nand then will be ranked on C++ efficeny\n");
	console << "first things first, please enter your name: " >> user_name << endl;
	game();
	score();
	if(again() == true)
	{
		mastermain(argument);// recursive function
		return (0);
	}

	return (0);
}

void game()
{
	console << " question (1) - A  preproccescor does .. ?\n (1) Activates the Compiler \n (2) Procceses the Code before the Compiler \n (3) Its nothing your trying to trick me \n";
	checkanswer(2,getanswer());
	console << " question (2) - The sizeof a unsigned char is ?\n (1) 3 Bytes \n (2) 4 Bytes \n (3) 1 Byte\n";
	checkanswer(3,getanswer());
	console << " question (3) - Variables can start with numeric digits\n (1) true \n (2) false\n";
	checkanswer(2,getanswer());
	console << " question (4) - A structure cannot contain pointers\n (1) true \n (2) false\n";
	checkanswer(2,getanswer());
	console << " question (5) - Multiple Inheritance is\n (1) something Java dosent have\n (2) Used in the Perl programming Language \n (3) When you delete a pointer\n";
	checkanswer(1,getanswer());
	console << " question (6) - Whenever you use the new keyword you must use the\n (1) << operator \n (2) polymorphism \n (3) the delete keyword \n";
	checkanswer(3,getanswer());
	console << " question (7) - std is a acrynom for \n (1) Sexualy Transmited Disease \n (2) Standard \n (3) Street Fighter 2 Kicks ass!\n";
	checkanswer(2,getanswer());
	console << " question (8) - there is no such thing as a function pointer\n (1) true \n (2) false \n";
	checkanswer(2,getanswer());
	console << " question (9) - The standard calling convention is \n (1) The Windows Calling convention\n (2) The Pascal calling convention \n (3) What the hell is a calling convention ?\n";
	checkanswer(2,getanswer());
	console << " question (10) - Why does Java Suck\n (1) - It doesnt allow multiple inheritance \n (2) Doesnt retain backwards compatibility with C \n (3) Java is NOT platform independent , since Java IS a platform\n (4) All of the Above\n";
	checkanswer(4,getanswer());
}

void checkanswer( int answer, int question )
{
	if( answer == question )
	{
		console << "\n Yes you are correct !! \n";
		user_score++;
	}
	else
	{
		console << "\n Im sorry that is incorrect. \n";
	}
}


int getanswer()
{
	int choice = 0;
	console << "please enter choice: " >> choice << endl;
	if( choice == 0 )
	{
		return (getanswer()); // try again recursion style
	}
	else
	{
		return choice;
	}
}

void score()
{
	char rank[100];

	switch( user_score )
	{
	case 0:
		strcpy(rank," You dont even know how to code ");
		break;
	case 1:
	case 2:
		strcpy(rank," You are a beginer ");
		break;
	case 3:
	case 4:
	case 5:
	case 6:
		strcpy(rank," You are intermediate");
		break;
	case 7:
	case 8:
	case 9:
		strcpy(rank," You are peaking into advanced ");
		break;
	case 10:
		strcpy(rank," You are a Master Guru");
		break;

	}

	console.clear();
	console << "Ranking for " << user_name << "\n your rank is: " << rank << "\n you got a " << user_score << "/10\n";
	console.pause();
	user_score = 0;
}


bool again()
{
	char answer[255];
	console.clear();
	console << "\n would you like to take the test again if so type yes: " >> answer << endl;
	if( strstr(answer,"yes")  )
	{
		console.clear();
		return (true);
	}

	return (false);
}