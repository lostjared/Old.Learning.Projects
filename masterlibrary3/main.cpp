/*

MasterLibrary3 Example Driver
written by Jared Bruni
www.LostSideDead.com

*/

#include<iostream>
#define MASTER_STRING2
#include"masterlibrary3.h"

using namespace std;


int main(void)
{

	cout << "masterlibrary3 example driver" << endl;
	cout << "length of string:-> " << masterstring::mstrlen("this string") << endl;
	return (system("pause"));
}
