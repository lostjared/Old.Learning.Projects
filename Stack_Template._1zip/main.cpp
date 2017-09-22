/* stack template example driver
   written by Jared Bruni
   www.LostSideDead.com
   "Open Source, Open Mind"
*/


#include<iostream>
#include"stack.h"

using namespace std;

int main()
{
	cout << " example driver " << endl;

	Stack <char> stack;

	stack.push('h');
	stack.push('e');
	stack.push('y');

	char c = stack.pop();
	cout << " the letter is -> " << c << endl;

	return (0);
}
