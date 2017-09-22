/* Vector Template example driver
   written by Jared Bruni
   www.LostSideDead.com

  "Open Source, Open Mind"
*/

#include<iostream>
#include"vector.h"

using namespace std;

int main()
{
	Vector<char> vect;

	vect.Add('m');
	vect.Add('a');
	vect.Add('s');
	vect.Add('t');
	vect.Add('e');
	vect.Add('r');
	vect.Add('!');

	for(int i = 0; i < vect.Length(); i++)
	{
		cout << vect[i];
	}

	cout << "\n example driver by Jared Bruni" << endl;

	return (system("pause"));
}
