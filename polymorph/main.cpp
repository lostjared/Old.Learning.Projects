// code request - how to use function polymorphsim
// written by jared bruni
// explicity for planetsourcecode

#include <iostream.h>
#include <stdlib.h>
#include <string.h>

// display val, and its many forms
void displayval(int x);
void displayval(long x);
void displayval(char*);


// main entry point
void main()
{
	int x = 100;
	long y = 200;
	char buff[100];
	strcpy(buff,"stuff");

	displayval(x);
	displayval(y);
	displayval(buff);

	system("pause");
}


// form 1
void displayval(int x)
{
	cout << " integer passed: " << x << endl;
}
// form 2
void displayval(long x)
{
	cout << " long integer passed: " << x << endl;
}

// form 3
void displayval(char* buff)
{
	cout << " string passed: " << buff << endl;
}