// code request about enumerated constants
// written by jared bruni
// explicity for planetsourcecode

#include<iostream.h>
#include<stdlib.h>

enum { NUM1 = 0, NUM2 , NUM3, NUM4, NUM5 };
enum ETYPE { THIS, THAT, NADA };



// program entry point
void main()
{
	cout << "hello world enumerated constants example for psc" << endl;

	cout << "num1: " << NUM1 << " num2: " << NUM2 << " num3: " << NUM3 << " num4: " << NUM4 << " num5: " << NUM5 << endl;

	ETYPE etype;

	etype = THIS;

	cout << "etype: " << etype << endl;

	etype = THAT;

	cout << "etype: " << etype << endl;

	etype = NADA;

	cout << "etype: " << etype << endl;


	system("pause");
}