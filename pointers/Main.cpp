// function pointer / pointer example
// jared bruni
// www.lostsidedead.com
// for planetsourcecode

#include <iostream.h>
#include <string.h>
#include <stdlib.h>
// class
class Class
{
	void (*xCallBack)(int message);// function pointer

public:
	inline void Init(void (*CallBack)(int message))// initlize function pointer
	{
		xCallBack = CallBack;// set function pointer
	}

	inline void update()// update
	{
		xCallBack(rand()%100);// call , callback
	}
};

void CallBack(int message);// callback function, to point to


void main()
{

	// pointer example

	char* buffer;// declare pointer

	buffer = new char[100];// allocate using new keyword

	strcpy(buffer, " this is on the free store ");// copy into array

	cout << "pointer variable to freestore: " << buffer << endl;// display

	delete [] buffer; // delete the buffer
	buffer = 0;// set the pointer to null, incase we try to access it later on accident
	// always do this it is good programming habbit




	// function pointer example
	Class theclass;
	theclass.Init(CallBack);

// program loop
	while(1)
	{
		theclass.update();
		char c;
		cout << " do you wish to continue  y/n ?" << endl;
		cin >> c;
		if(c != 'y')
		{
			break;
		}

	}

}

// callback message process function
void CallBack(int message)
{
	cout << " the message is: " << message << endl;
}