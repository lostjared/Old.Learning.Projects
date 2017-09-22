/*

  MasterPiece written utilizing MasterX SDK
  written by Jared Bruni


  www.lostsidedead.com



  Open Source, Open Mind

   "I am only as I think and believe"


*/

#include "thehead.h"

#include <fstream>

using namespace std;

// save the high scores
void savescore()
{
	ofstream fout("scores.mps",ios::binary);
	fout.write((char*)&fscores,sizeof(fscores));
	fout.close();
}
// load the high scores
void loadscore()
{
	ifstream fin("scores.mps",ios::binary);
	fin.read((char*)&fscores,sizeof(fscores));
	fin.close();
}