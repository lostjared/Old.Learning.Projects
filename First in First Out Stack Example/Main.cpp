// message que example
// written by jared bruni
// www.lostsidedead.com
// using the message que structure

#include "msgque.h"
#include <iostream.h>

MsgQue myque;

inline void printmenu();

void main()
{
	while(true)
	{
		printmenu();
		char input_data[100];
		cin >> input_data;
		int var;
		var = atoi(input_data);
		switch(var)
		{
		case 1:
			char givechar[100];
			cout << "\n enter message to add to que: ";
			cin >> givechar;
			myque.AddMessage(givechar);
			break;
		case 2:
			char buff[100];
			if(myque.GetNextMessage(buff))
			{

			cout << endl << "current message: " << buff << endl;

			}
			break;
		case 3:
			return;
			break;
		default:
			cout << "\n *** invalid input *** \n";
			continue;
			break;
		}

	}
}

inline void printmenu()
{
	cout << "\n*** press 1 to add, message to que, press 2 to proccess message from que, press 3 to exit ***";
}