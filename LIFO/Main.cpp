// setting up a LIFO (Last In First Out) Data Structure (STACK)
// written by jared bruni
// www.lostsidedead.com




#include <iostream.h>
#include <stdlib.h>
#include "StackStruct.h"


inline void printmenu();

Stack mystack;// the stack (lifo)

void main()
{
	cout << "******* stack example: its in dos, so you can just see how a stack works*****\n";

	while(true)
	{
		printmenu();

		char choice[100];
		cin >> choice;
		int cx;
		cx = atoi(choice);
		if(cx == 0)
		{
			cout << "**\n invalid choice **\n";
			continue;
		}
		
		switch(cx)
		{
		case 1:
			// enter data to push
			char ch[100];
			cout << "\nenter integer value to push into the stack: ";
			cin >> ch;
			int cy;
			cy = atoi(ch);
			if(cy == 0)
			{
				cout << "\n**error you inputed invalid data**\n";
				continue;
			}
			mystack.stackpush(cy);
			cout << "\n** pushed value: " << cy << " into the stack **\n";
			break;
		case 2:
			{
			// pop value
		int popval = mystack.stackpop();
		if(popval != STACK_FAIL)
		{
			cout << "\n*** poped item : " << popval << " from the stack\n";
		}
			}
			break;
		case 3:
			mystack.stackdump();
			break;
		case 4:
			return;
			break;
		default:
			cout << "\n******* error, invalid selection *********\n";
			continue;
			break;
		}

	}


}

inline void printmenu()
{
	cout << "\n*** press 1 to push data\npress 2 to pop data\n3 to display stack dump\n4 to quit****\n";
}