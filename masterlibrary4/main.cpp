/* Example Driver
   written by Jared Bruni
   www.LostSideDead.com
*/

#include<iostream>

#define MASTER_LIST
#define MASASM
#include"masterlibrary4.h"

using namespace std;

void interupt(int call);


int main()
{
	masasm::program.setinterupt(interupt);
	masasm::compile("script.masasm");
	return (0);
}

void interupt(int call)
{

	switch(call)
	{
	case 1:
		{

		}
		break;

	}

}
