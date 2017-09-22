/* List Template example driver
   writen by Jared Bruni
   www.LostSideDead.com

  "Open Source, Open Mind"
*/


#include<iostream>
#include"list.h"

using namespace std;

int main()
{

	List<char> list1;
	list1.add('m');
	list1.add('a');
	list1.add('s');
	list1.add('t');
	list1.add('e');
	list1.add('r');
	for(int i = 0; i < list1.length(); i++)
	{
		char c;
		c = list1.get(i);
		cout << c << endl;
	}

	return (system("pause"));
}