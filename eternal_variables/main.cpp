/* eternal variable driverl
   written by Jared Bruni
   www.LostSideDead.com

  Open Source Open Mind"
*/

#include<iostream>
#include<string>
#include<conio.h>
#include"eternal.h"

eternal<bool> boolean (true, "bool.dat");
 
int main()
{
	eternal<char*> st("this is the default string","filename.dat");

	cout<< st.get() << endl;

	st = "this is the second string, assigned laster";


	cout << "boolean =  ";
	if(boolean.get() == true)
	{
		cout << "true";
	}
	else
	{
		cout << "false";
	}

	cout << "\nSwitching boolean value...\n";
	if(boolean.get() == true)
	{
		boolean = false;
		
	}
	else
	{
		boolean = true;
	}

	cout << "run program agian, to see that the values stay the same " << endl;
	getch();
	return (0);
}

