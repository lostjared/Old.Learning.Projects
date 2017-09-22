#include<iostream>
#include"masterstring2.h"

using namespace std;


int main()
{
	masterstring::Tokenize token;
	token.tokenize("this,is,the,string",',');
 
	for(int i = 0; i < token.length; i++)
	{
		cout  << token[i]  << endl;
	}

	system("pause");

	return (0);
}
