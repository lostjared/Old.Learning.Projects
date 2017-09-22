/*

  MasAsm - written by Jared Bruni
  www.lostsidedead.com

  assembler, for the MAS bytecode

  written in the C programming language
  decided to change up my style for this one
  for practice

*/

#include "thehead.h"

// does this file exisit? if yes, then return true
BOOL isfile(char *filename)
{
	HANDLE hSearch;
	WIN32_FIND_DATA p;
	hSearch = FindFirstFile(filename,&p);
	if(hSearch!=INVALID_HANDLE_VALUE)
		return TRUE;
	else
		return FALSE;
}

// return the length of this file
int flen(const char *filename)
{
	FILE* sfile;
	int count = 0;

	sfile = fopen(filename,"rb+");

	while (1)
	{
		char c;
		c = fgetc( sfile );
		if(c == EOF)
		{
			break;
		}
		else
		{
			count++;
		}
	}

	return count;
}

// read in the file
void readfile(const char *filename, char* data)
{
	int pos;
	FILE* ofile;

	pos = 0;

	ofile = fopen(filename,"rb+");

	while (1)
	{
		char c;
		c = fgetc( ofile );
		if(c == EOF)
		{
			break;
		}

		data[pos] = c;
		pos++;

	}

	data[pos] = 0;
	fclose(ofile);
}

// trim all \r characters
void trimr(char *source)
{
	char *temp;
	int  i = 9,len = 0,pos = 0;

	len = strlen(source);
	temp = malloc (len + 1);
	
	for(i = 0; i < len; i++)
	{
		if(source[i] != '\r')
		{
			temp[pos] = source[i];
			pos++;
		}
	}

	temp[pos] = 0;
	strcpy(source,temp);
	free(temp);
}

// lower case all the characters
void lcase(char *source)
{
	unsigned int i;

	for(i = 0; i < strlen(source); i++)
	{
		source[i] = tolower(source[i]);
	}
}

// kill white space
void killwspace(char *source)
{
	char *temp;
	int i,len = strlen(source),pos = 0;
	BOOL inq = FALSE;
	
	temp = malloc(strlen(source) + 1);


	// 'accomodate for for data in " "
	// other other data is white space trim (only 1 space inbetween each word)
	for(i = 0; i < len; i++)
	{ 
		if(source[i] == '"')
		{
			if(inq == FALSE) 
			{
				inq = TRUE;
				temp[pos] = source[i];
				pos++;
				continue;
			}
			else
			{
				inq = FALSE;
			}
		}


		if(inq == FALSE)
		{

		if(source[i] != ' ')
		{
			temp[pos] = source[i];
			pos++;
		}
		else
		{
			if(source[i+1] != ' ')
			{
				temp[pos] = ' ';
				pos++;
			}
		}

		}
		else
		{
			temp[pos] = source[i];
			pos++;
		}
	
	}

	temp[pos] = 0;
	strcpy(source,temp);
	free(temp);
}

// trim comments
void trimcomments(char *in)
{
	int len = strlen(in);
	int i,pos = 0;
	char *temp;
	BOOL add = TRUE;
	BOOL iadd = TRUE;

	temp = malloc(len + 2);

	for(i = 0; i < len; i++)
	{
		if(in [i] == '\"')
		{
			if(iadd == TRUE) { iadd = FALSE; } else { iadd = TRUE; }
		}
		
		if(iadd == TRUE)
		{

		if( in[i] == ';' )
		{
			add = FALSE;
		}
		
		if(in[i] == '\n')
		{
			add = TRUE;
		}

		}

		if( add == TRUE )
		{
			temp[pos] = in[i];
			pos++;
		}


	}

	temp[pos] = 0;

	strcpy(in,temp);

	free(temp);
}

// kill all line characters
void killline(char *data)
{
	char *temp;
	int len = strlen(data),i = 0,pos = 0;


	temp = malloc (strlen(data)+1);

	for(i = 0; i < len; i++)
	{
		if(data[i] != '\n' && data[i] != '\r' && data[i] != ' ')
		{
			temp[pos] = data[i];
			pos++;
		}
	}

	temp[pos] = 0;

	strcpy(data,temp);

	free(temp);
}

// trim the quotes from a string
void trimquotes(char *string)
{
	char *temp;
	int i,pos = 0,len = strlen(string);


	temp = malloc(strlen(string) + 1);

	for(i = 0; i < len; i++)
	{
		if(string[i] != '\"')
		{
			temp[pos] = string[i];
			pos++;
		}
	}

	temp[pos] = 0;
	strcpy(string,temp);
	free(temp);
}

// code trim, change it around like, remove empty lines remove the { }
void codetrim(char *code)
{
	char *temp;
	int i,len = strlen(code),fo,fc;

	temp = malloc (len + 1);


	fo = findstr(code,"{");
	fc = findstr(code,"}");

	midcopy(code,temp,fo+1,fc);
	strcpy(code,temp);
	len = strlen(code);

	for(i = 0; i < len; i++)
	{
	}

	free(temp);
}

/// instruction trim (remove stuff that shouldnt be there)
void inctrim(char *code)
{
	char *temp;
	int i,len = strlen(code),off = 0;
	BOOL add = FALSE;
	BOOL addi = TRUE;

	temp = malloc(len + 1);

	 //old loop 
	for(i = 0; i < len; i++)
	{
		if(code[i] != ' ' && code[i] != '\n')
		{
			add = TRUE;
		}
		
		if(add == TRUE)
		{

		if(code[i] != '\n')
		{

		temp[off] = code[i];
		off++;

		}

		}

	}

	/*
	for(i = 0; i < len; i++)
	{
		if(code[i] == '\"')
		{
			if(addi == TRUE) { addi = FALSE; } else { addi = TRUE; }
		}

		if(addi == TRUE)
		{
			if(code[i] != ' ' && code[i] != '\n')
			{
				add = TRUE;
			}

		
			if(code[i] != '\n')
			{
				temp[off] = code[i];
				off++;
			}

		}
	}*/


	temp[off] = 0;
	strcpy(code,temp);
	free(temp);
}

// encrypt the code (for output, so that you cant just look at the mve)
void encryptcode(char *code)
{
	int i,len = strlen(code);

	for(i = 0; i < len; i++)
	{
		code[i] += 25;
	}
}

// decrypt the code 
void decryptcode(char *code)
{
	int i,len = strlen(code);

	for(i = 0; i < len; i++)
	{
		code[i] -= 25;
	}
}

BOOL cmdcheck(char* code)
{

	int i,len = strlen(code);

	BOOL check_it = TRUE;


	for(i = 0; i < len; i++)
	{
		if(code[i] == '\"')
		{

			if(check_it == TRUE)
			{
				check_it = FALSE;
			}
			else
			{
				check_it = TRUE;
			}
		}



		if(check_it == TRUE)
		{

		if(cmdcheckc(code[i]) == TRUE)
		{
			return TRUE;
		}

		}
	}

	return FALSE;
}
// cmd check c
BOOL cmdcheckc(char c)
{
	switch(c)
	{
	case '~':
	case '`':
	case '!':
	case '@':
	case '#':
	case '^':
	case '*':
	case '(':
	case ')':
	case '-':
	case '+':
	case '/':
	case '\\':
	case '<':
	case '>':
//	case '.': now accepts dot notation
	case '?':
	case ']':
	case '[':
	case '=':
	case '|':
		return TRUE;
		break;
	}

	return FALSE;
}

// trim the name, so that it is propper for MVE output
void nametrim(char *name)
{
	char *temp;
	int pos;

	killspace(name);
	killline(name);

	pos = findstr(name,"proc");


	if(pos != FAIL)
	{

	temp = malloc(strlen(name) + 1);

	rightcopy(name,temp,4);
	strcpy(name,temp);

	free(temp);

	}
}

// is ins, is this string a valid instruction? if so return its OPCODE
int isins(char *ins)
{

	// operand type 1

	// integer instructions

	if(strcmp(ins,"add") == 0)
	{
		return 0x1;
	}
	if(strcmp(ins,"sub") == 0)
	{
		return 0x2;
	}
	if(strcmp(ins,"div") == 0)
	{
		return 0x3;
	}
	if(strcmp(ins,"mul") == 0)
	{
		return 0x4;
	}
	if(strcmp(ins,"or") == 0)
	{
		return 0x5;
	}
	if(strcmp(ins,"xor") == 0)
	{
		return 0x6;
	}
	if(strcmp(ins,"and") == 0)
	{
		return 0x7;
	}
	if(strcmp(ins,"mov") == 0)
	{
		return 0x8;
	}



	// operand type 2

	if(strcmp(ins,"inc") == 0)
	{
		return 0x20;
	}

	if(strcmp(ins,"dec") == 0)
	{
		return 0x21;
	}

	if(strcmp(ins,"not") == 0)
	{
		return 0x22;
	}


	// string instructions

	if(strcmp(ins,"smov") == 0)
	{
		return 0x40;
	}

	if(strcmp(ins,"scat") == 0)
	{
		return 0x41;
	}


	// string instructions operand type 1

	if(strcmp(ins,"println") == 0)
	{
		return 0x60;
	}
	if(strcmp(ins,"input") == 0)
	{
		return 0x61;
	}
	if(strcmp(ins,"iline") == 0)
	{
		return 0x62;
	}
	if(strcmp(ins,"print") == 0)
	{
		return 0x63;
	}

	// failure, this is *NOT* a valid instruction
	return FAIL;
}


// is this character, a acceptable mas character?
BOOL ismaschar(char c)
{
	switch(c)
	{
	case 'a':// alphabet
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case ' ':
	case '\n':// chr 13 (0xD)
	case '\r':// chr 10 (0xA)
	case '_':// for word seperation
	case '=':// operator
	case '{':// block open
	case '}':// block close
	case '&':// integer operator
	case '$':// string operator
	case '#':// for float operator
	case ':':// colon for code labels
	case ',':// comma to seperate operands
	case '+':// for streams
	case ';':// for comments
	case '\"':// for strings
	case '.':// for decimal points/dot notation
		return TRUE;
	}

	return FALSE;
} 