/*

  Mcstr.h written by Jared Bruni

  (Master C style String Manipulation)

  www.lostsidedead.com

*/

#include "mcstr.h"


// left copy
void leftcopy(const char *string, char *out, int pos)
{
	int len = strlen(string);
	int i,p = 0;

	for(i = 0; i < pos; i++)
	{
		out[p] = string[i];
		p++;
	}

	out[p] = 0;
}

// right copy
void rightcopy(const char *string, char *out, int pos)
{
	int len = strlen(string);
	int i;
	int p = 0;

	for(i = pos; i < len; i++)
	{
		out[p] = string[i];
		p++;
	}

	out[p] = 0;
}

// mid copy
void midcopy(const char *string, char *out, int start, int stop)
{
	int i;
	int p = 0;

	for(i = start; i < stop; i++)
	{
		out[p] = string[i];
		p++;
	}

	out[p] =0;

}


// find the position of a string, within a string
int findstr(const char *string, const char *search)
{
	int i = 0,p = 0,len = strlen(string),len2 = strlen(search);

	for(i = 0; i < len; i++)
	{
		if( string[i] == search[0] )
		{
			BOOL add = TRUE;
			for(p = 0; p < len2; p++)
			{
				if( string[i+p] != search[p] )
				{
					add = FALSE;
				}
			}

			if(add == TRUE)
			{
				return i;
			}

		}
	}


	return NULLPOS;
}

// backwards string search

// find the position of a string, within a string
int bfindstr(const char *string, const char *search)
{
	int i = 0,p = 0,len = strlen(string),len2 = strlen(search);

	for(i = len; i > 0; i--)
	{
		if( string[i] == search[0] )
		{
			BOOL add = TRUE;
			for(p = 0; p < len2; p++)
			{
				if( string[i+p] != search[p] )
				{
					add = FALSE;
				}
			}

			if(add == TRUE)
			{
				return i;
			}

		}
	}


	return NULLPOS;
}


// find string, starting from 
int ifindstr( int start, const char *string, const char *search)
{
	int i = 0,p = 0,len = strlen(string),len2 = strlen(search);

	for(i = start; i < len; i++)
	{
		if( string[i] == search[0] )
		{
			BOOL add = TRUE;
			for(p = 0; p < len2; p++)
			{
				if( string[i+p] != search[p] )
				{
					add = FALSE;
				}
			}

			if(add == TRUE)
			{
				return i;
			}

		}
	}


	return NULLPOS;
}

// find string, starting from 
int ibfindstr( int start, const char *string, const char *search)
{
	int i = 0,p = 0,len = strlen(string),len2 = strlen(search);

	for(i = start; i > 0; i--)
	{
		if( string[i] == search[0] )
		{
			BOOL add = TRUE;
			for(p = 0; p < len2; p++)
			{
				if( string[i+p] != search[p] )
				{
					add = FALSE;
				}
			}

			if(add == TRUE)
			{
				return i;
			}

		}
	}

	return NULLPOS;
}

// kill all space in this string
void killspace(char *string)
{
	int len = strlen(string);
	char *temp;
	int pos = 0,i;

	temp = malloc(len + 1);
	
	for(i = 0; i < len; i++)
	{
		if(string[i] != ' ')
		{
			temp[pos] = string[i];
			pos++;
		}
	}

	temp[pos] = 0;

	strcpy(string,temp);

	free(temp);
}

// find the occourace of a specific character within a string
int findoccourance(const char *str, char c)
{
	int cpos = 0,len = strlen(str),found = 0;

	for(cpos = 0; cpos < len; cpos++)
	{
		if(str[cpos] == c)
		{
			found++;
		}			
	}

	return found;
}
 
// is this a hex character?
BOOL ishexc(char c)
{
	c = tolower(c);
	switch (c)
	{
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
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
		return TRUE;
		break;
	default:
		return FALSE;
		break;
	}

	return TRUE;
}

// is this string only contain hex digits?
BOOL ishex(char *data)
{
	int i,len = strlen(data);
	for(i = 0; i < len; i++)
	{
		if(ishexc(data[i]) == FALSE)
		{
			return FALSE;
		}
	}

	return TRUE;
}

// hex to int character 
unsigned long hextointc(char c)
{
	c = tolower(c);
	switch(c)
	{
	case '0':
		return 0;
		break;
	case '1':
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
		break;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;
	case '7':
		return 7;
		break;
	case '8':
		return 8;
		break;
	case '9':
		return 9;
		break;
	case 'a':
		return 10;
		break;
	case 'b':
		return 12;
		break;
	case 'c':
		return 13;
		break;
	case 'e':
		return 14;
		break;
	case 'f':
		return 15;
		break;
	}

	return FAIL;
}

// translate this string into hex digits
unsigned long hextoint( char *buff)
{
	int len = strlen(buff);
	unsigned long* hexval;
	int hexvali = 0,i,z,index; 
	unsigned long rt = 0;

	if(ishex(buff) == FALSE)
	{
		return FAIL;
	}

	hexval = malloc ((len+1) * sizeof(unsigned long));

	for(i = 0; i < len; i++)
	{
		hexval[hexvali] = hextointc(buff[i]);
		hexvali++;
	}

    index = 0;
	for(z = hexvali-1; z >= 0; z--)
	{
		int cur;
		if(index == 0)
		{
			cur = hexval[z];
			index = 16;
		}
		else
		{
			cur = hexval[z] * index;
			index = index * 16;
		}

		rt = rt + cur;
	}

	free(hexval);

	return rt;
}

// is this character a illegal character?
BOOL iopc(char c)
{
	switch(c)
	{
	case '~':
	case '`':
	case '!':
	case '@':
//	case '#': for float
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
	case '.':
	case ',':
	case '?':
		return TRUE;
		break;
	}

	return FALSE;
}


// do illegal characters exisit within this string?
BOOL iop(char *string)
{

	int i, len = strlen(string);

	for(i = 0; i < len; i++)
	{
		if(iopc(string[i]) == TRUE)
		{
			return TRUE;
		}
	}


	return FALSE;
}

// is this a numeric string?
BOOL isnumeric(char *str)
{
	/*
	int val;
	
	val = hextoint(str);

	if(val == -1)
	{
		return FALSE;
	}*/

	int i, len = strlen(str);

	for(i = 0; i < len; i++)
	{
		switch(str[i])
		{
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
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case '.':
			break;
		default:
			return FALSE;
			break;
		}

	}

	return TRUE;
}
// search for symbols, disregarding data inside of  " "
int quotesearch(int start, const char* source, const char search)
{
	int i, len = strlen(source);
	BOOL igo = TRUE;

	for(i = start; i < len; i++)
	{

		if(source[i] == '\"')
		{
			if(igo == TRUE) { igo = FALSE; } else { igo = TRUE; }
		}

		if(igo == TRUE)
		{
			if(source[i] == search)
			{
				return i;
			}
		}
	}

	return FAIL;
}

// get how many \n characters (lines) there are before the pos
int linebypos(const char* source, int pos)
{
	int i, linecount = 0, len = strlen(source);

	for(i = 0; i < pos; i++)
	{
		if(source[i] == '\n')
		{
			linecount++;
		}
	}

	return linecount;
}
