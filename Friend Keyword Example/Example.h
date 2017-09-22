// friend example
// written by jared bruni
// www.lostsidedead.com

#include <iostream.h>

void PrintHello();

void PrintHello()
{
	cout << "HELLO";
}

class Jared
{
public:
	inline void test()
	{
		PrintHello();
	}
	friend void PrintHello();
};
