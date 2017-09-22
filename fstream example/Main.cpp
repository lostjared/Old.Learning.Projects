// fstream example
// writing to text file
// and saving a structure as a binary file
// this code was a request
// keep your requests comin
// jared bruni
// for planetsourcecode


#include <iostream.h>
#include <fstream.h>
#include <string.h>


// a structure
struct BFile
{
	int x;// storing a integer
	char buffer[100]; // a string
	long y; // stroing a long 
	// etc

	inline BFile()
	{
		x = 100;
		y = 400;
		strcpy(buffer,"this");
	}
};

void main()
{
	cout << " planet source code example by jared bruni " << endl;
	cout << " how to write to text file, and how to write to binary file" << endl;
	cout << " using fstream " << endl;

	char filename[100];
	cout << " enter the file name for text file: ";
	cin >> filename;

	cout << "\nnow writing to text file.." << endl;

	ofstream fout(filename);

	fout << " this is some data written to the file ";

	fout.close();

	char filename2[100];

	cout << "\nenter another file name for binary data file: ";
	cin >> filename2;
	cout << "\n writing binary data to file.." << endl;

	ofstream fout2(filename2,ios::binary);
	BFile dat;
	fout2.write((char*)&dat,sizeof(dat));
	fout2.close();

}