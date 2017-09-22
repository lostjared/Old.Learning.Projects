/* Tokenize Algorithm
   written by Jared Bruni
   www.LostSideDead.com

  "Open Source, Open Mind"
*/

#include<iostream>
#include<vector>
#include<string>
#include"masterstring2.h"


using namespace std;
using namespace masterstring;

void tokenize(char *source, char *delim, vector<string>& vect);

int main()
{
	vector<string> vect;
	char str[] = "this is the string";
	char sep[] = " ";

	tokenize(str, sep, vect);

	cout << "tokenizing [" << str << "] " << endl;

	/* print out vector */
	for(int i = 0; i < vect.size(); i++)
	{
		cout << vect[i] << endl;
	}

	return (0);
}


void tokenize(char *source, char *delim, vector<string>& vect)
{
	int off = 0;
	int pos = 0;

	if(mstrfind(source,delim) == -1)
	{
		return;
	}

	while(1)
	{
		pos = mstrifind(off,source,delim);
		if(pos == -1)
		{
			break;
		}
		char *temp = new char [ strlen(source) + 1 ];
		mstrmid(source,temp,off,pos);
		vect.push_back(temp);
		off = pos + 1;
		delete [] temp;
	}
	char *temp = new char [ strlen(source) + 1 ];
	mstrright(source,temp,off);
	vect.push_back(temp);
	delete [] temp;
}