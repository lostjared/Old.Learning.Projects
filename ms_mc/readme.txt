MasterConsole
MasterStream

written by Jared Bruni
www.lostsidedead.com


aim: xmasterxx3
aol: master322
yahoo: jared_bruni@yahoo.com



How to make a MasterConsole Program


Simply make a blank win32 application
Then add the masterstream file to the project files.
Then create your driver source file and include the masterstream source flie.
Example



#include "masterstream.h"


int mastermain(char* argument)
{

console << "hello world" << endl;
char name[100];
console << "enter your name: ";
console >> name;
console << "\n" << "Hello " << name << endl;
console.pause();
return (0);

}