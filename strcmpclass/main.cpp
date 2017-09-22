// written by jared bruni
// for planetsourcecode
// for the ask a pro help

#include <iostream.h>
#include <string.h>


// setting up a rectangel class (for ask a pro)
class Rect
{
	inline Rect()
	{
		x = 1;
		y = 1;
		w = 1;
		h = 1;
	}

public:
	int x;
	int y;
	int w;
	int h;

	inline int GetParm()
	{
		return x + y + w + h;
	}
};



// using strcmp
void main()
{
	char buffer[100];
	cout << "please enter string1: ";
	char buffer2[100];
	cin >> buffer;
	cout << "\nplease enter string2: ";
	cin >> buffer2;
	cout << "\n";

	if(strcmp(buffer,buffer2) == 0)
	{
		cout << "they are equal!";
	}
	else
	{
		cout << "they are not equal!";
	}
}
