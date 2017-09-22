// header file
// contains functions, we wanna keep out of the way
// jared bruni
// mail me: master@lostsidedead.com

#include <iostream.h>
#include <stdlib.h>
#include "masterstring.h"

bool isline(char* buff); // is this a valid line? 
bool isinc(char* buff); // is this a instruction ?
int  ginc(char* buff);// yeah its a instruction, translate the mnemoic
void disperror(int line,char* buff);// display error
bool checkopr(char* buff);// check operands
bool checknopr(char* buff);// check for a null operand instruction (theres only 1)
void getoprands(char* data,char* op1,char* op2);
bool ireg(char* data);// is this a register? 
int  greg(char* data); // get this register value from handle
void addiline(char* buff);// add the next line
void initfdata(); 
void getexename(char* source,char* output);
bool isfile(char* file);


MasterString fdata;// autosizing master string :)
bool fline = false;

int err_count = 0;

// display error, and increment error count
void disperror(int line,char* buff)
{
	line = line + 1;

	err_count++;
	cout << "error on line(" << line << "): " << buff << endl;
/*
	if(err_count > 4)
	{
		cout << " stoping to many errors " << endl;
		exit(0);
	}
*/
}


// body (is this a valid line? or was it comments)
bool isline(char* buff)
{
	char* nbuff;

	nbuff = new char[strlen(buff)+1];

	strcpy(nbuff,buff);

	trimspace(nbuff);

	int len;
	len = strlen(nbuff) - 1;
	delete [] nbuff;
	nbuff = 0;

	if(len != 0)
	{
		return true;
	}

	return false;
}
// make the instruction check, and the mnemoic check
// be very explicit, use full head on searchZ

bool isinc(char* buff)
{

	// talk about overhead
	// cant use a jump table here sorry
	if(findstr(buff,"loadm") != -1) // 0
	{
		return true;
	}

	if(findstr(buff,"load") != -1) // 1
	{
		return true;
	}

	if(findstr(buff,"store") != -1) // 2
	{
		return true;
	}

	if(findstr(buff,"mov") != -1) // 3
	{
		return true;
	}

	if(findstr(buff,"add") != -1) // 4
	{
		return true;
	}

	if(findstr(buff,"sub") != -1) // 5
	{
		return true;
	}
	
	if(findstr(buff,"mul") != -1) // 6
	{
		return true;
	}

	if(findstr(buff,"div") != -1) // 7
	{
		return true;
	}

	if(findstr(buff,"inc") != -1) // 8
	{
		return true;
	}

	if(findstr(buff,"dec") != -1) // 9
	{
		return true;
	}

	if(findstr(buff,"or") != -1) // A
	{
		return true;
	}

	if(findstr(buff,"xor") != -1) // B
	{
		return true;
	}
	
	if(findstr(buff,"and") != -1) // C
	{
		return true;
	}

	if(findstr(buff,"rotate") != -1) // D
	{
		return true;
	}

	if(findstr(buff,"halt") != -1) // E
	{
		return true;
	}

	return false;
}
// int get current opcode from mnemoic
int ginc(char* buff)
{
	if(findstr(buff,"loadm") != -1) // 1
	{
		return 1;
	}

	if(findstr(buff,"load") != -1) // 2
	{
		return 2;
	}

	if(findstr(buff,"store") != -1) // 3
	{
		return 3;
	}

	if(findstr(buff,"mov") != -1) // 4
	{
		return 4;
	}

	if(findstr(buff,"add") != -1) // 5
	{
		return 5;
	}

	if(findstr(buff,"sub") != -1) // 6
	{
		return 6;
	}
	
	if(findstr(buff,"mul") != -1) // 7
	{
		return 7;
	}

	if(findstr(buff,"div") != -1) // 8
	{
		return 8;
	}

	if(findstr(buff,"inc") != -1) // 9
	{
		return 9;
	}

	if(findstr(buff,"dec") != -1) // A
	{
		return 10;
	}

	if(findstr(buff,"or") != -1) // B
	{
		return 11;
	}

	if(findstr(buff,"xor") != -1) // C
	{
		return 12;
	}
	
	if(findstr(buff,"and") != -1) // D
	{
		return 13;
	}

	if(findstr(buff,"rotate") != -1) // E
	{
		return 14;
	}

	if(findstr(buff,"halt") != -1) // F
	{
		return 15;
	}

	return 0;// never should happen
}


// check operands
bool checkopr(char* buff)
{
	int find_oc;

	find_oc = findoccourance(buff,",");

	if(find_oc == 1)
	{
		return true; // operand seperating the mnemoics
	}
	else
	{
		return false;
	}
}
// check for no operands
bool checknopr(char* buff)
{
	int find_oc;

	find_oc = findoccourance(buff,",");

	if(find_oc == -1)
	{
		return true;// yay no operands
	}
	else
	{
		return false;// return false
	}
}

// get oprands
void getoprands(char* data,char* op1,char* op2)
{
	int fspace;
	fspace = findstr(data," ");
	int fcomma;
	int lend = strlen(data);
	fcomma = ifindstr(fspace,data,",");
	midcopy(data,op1,fspace+1,fcomma);
	midcopy(data,op2,fcomma+1,lend);
	trimspace(op1);
	trimspace(op2);
}

// is this a register?
bool ireg(char* data)
{

	if(mstrcmp(data,"ax") != false) // 0
	{
		return true;
	}
	if(mstrcmp(data,"bx") != false) // 1
	{
		return true;
	}
	if(mstrcmp(data,"cx") != false)// 2
	{
		return true;
	}
	if(mstrcmp(data,"dx") != false) // 3
	{
		return true;
	}
	if(mstrcmp(data,"ex") != false)// 4
	{
		return true;
	}
	if(mstrcmp(data,"fx") != false)// 5
	{
		return true;
	}
	if(mstrcmp(data,"gx") != false)// 6
	{
		return true;
	}
	if(mstrcmp(data,"hx") != false)// 7
	{
		return true;
	}
	if(mstrcmp(data,"ix") != false)// 8
	{
		return true;
	}
	if(mstrcmp(data,"jx") != false)// 9
	{
		return true;
	}
	if(mstrcmp(data,"kx") != false)// A
	{
		return true;
	}
	if(mstrcmp(data,"lx") != false)// B
	{
		return true;
	}
	if(mstrcmp(data,"mx") != false)// C
	{
		return true;
	}
	if(mstrcmp(data,"nx") != false)// D
	{
		return true;
	}
	if(mstrcmp(data,"ox") != false)// E
	{
		return true;
	}
	if(mstrcmp(data,"px") != false)// F
	{
		return true;
	}

	return false;
}

int greg(char* data)
{
	if(findstr(data,"ax") != -1) // 0
	{
		return 0;
	}
	if(findstr(data,"bx") != -1) // 1
	{
		return 1;
	}
	if(findstr(data,"cx") != -1)// 2
	{
		return 2;
	}
	if(findstr(data,"dx") != -1) // 3
	{
		return 3;
	}
	if(findstr(data,"ex") != -1)// 4
	{
		return 4;
	}
	if(findstr(data,"fx") != -1)// 5
	{
		return 5;
	}
	if(findstr(data,"gx") != -1)// 6
	{
		return 6;
	}
	if(findstr(data,"hx") != -1)// 7
	{
		return 7;
	}
	if(findstr(data,"ix") != -1)// 8
	{
		return 8;
	}
	if(findstr(data,"jx") != -1)// 9
	{
		return 9;
	}
	if(findstr(data,"kx") != -1)// A
	{
		return 10;
	}
	if(findstr(data,"lx") != -1)// B
	{
		return 11;
	}
	if(findstr(data,"mx") != -1)// C
	{
		return 12;
	}
	if(findstr(data,"nx") != -1)// D
	{
		return 13;
	}
	if(findstr(data,"ox") != -1)// E
	{
		return 14;
	}
	if(findstr(data,"px") != -1)// F
	{
		return 15;
	}

	return -1; // failure (should never get here, use ireg to check if its a register value
}



// add instruction line
void addiline(char* buff)
{
	if(fline == false)
	{
		fline = true;
		fdata = buff;
		return;
	}

	fdata += buff;
}

// get the output exe name
void getexename(char* input,char* output)
{
	int fp;
	fp = findstr(input,".");

	char thename[200];

	leftcopy(input,thename,fp);
	strcpy(output,thename);
	strcat(output,".8xe");
}


// is this a file ? 

// micheal w essary gave me this function
bool isfile(char* filename)
{
 HANDLE hSearch;
 WIN32_FIND_DATA p;
 hSearch = FindFirstFile(filename,&p);
  if(hSearch!=INVALID_HANDLE_VALUE)
  return true;
 else
  return false;
}
