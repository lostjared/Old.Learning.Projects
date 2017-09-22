// writen by jared bruni
// for planetsourcecode
// this was a request
// www.lostsidedead.com
// typecasting void pointers

#include <iostream.h>
#include <string.h>
#include <stdlib.h>


void main()
{
	cout << "hello world, lets typecast a void pointer" << endl;


	void* buffer;// void pointer

	buffer = new char[100];// allocate on free store

	strcpy((char*)buffer,"this is in the buffer");// typecast

	cout << "output this buffer: " << (char*)buffer << endl;// print out

	delete [] buffer;// delete array from freestore

	buffer = 0;// set pointer to null

	system("pause"); // pause
}

