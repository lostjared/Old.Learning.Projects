/* sample driver
   using masterstring2
*/

#include<iostream.h>
#include"masterstring2.h"
#include<stdlib.h>
 
int main()
{
	char str[] = "Jared Bruni";
	cout << masterstring::mstrlen(str) << endl;
	char str2[255];
	masterstring::mstrcpy(str2,"LostSideDead");
	cout << "string copy: " << str2 << endl;
	masterstring::mstrcat(str2,".com");
	cout << " string concatination " << str2 << endl;
	char left[255];
	masterstring::mstrleft(str2,left,7);
	cout << " string left " << left << endl;
	char right[255];
	masterstring::mstrright(str2,right,4);
	cout << " string right " << right << endl;
	char mid[255];
	masterstring::mstrmid(str2,mid,4,8);
	cout << "string mid " << mid << endl;
	char mid2[255];
	masterstring::mstrvbmid(str2,mid2,4,4);
	cout << "string mid 2 " << mid2 << endl;

	if( masterstring::mstrcmp( "1234","123" ) )
	{
		cout << " string compare - the same " << endl;
	}
	else
	{
		cout << " string compare - not the same " << endl;
	}
	char space[255];
	masterstring::killspace(" t e s t i n g ",space);
	cout << " Kill space -> " << space << endl;

	cout << "position of Side-> " << masterstring::mstrfind(str2,"Side") << endl;
	cout << "position of Dead-> " << masterstring::mstrifind(0,str2,"Dead") << endl;
	cout << "position of Lost-> " << masterstring::mstrbfind(str2,"Lost") << endl;
	cout << "position of ad  -> " << masterstring::mstribfind(masterstring::mstrlen(str2),str2,"ad") << endl;

	cout << " \n\n********test driver by Jared Bruni********" << endl;
	system("pause");

	return (0);
}
