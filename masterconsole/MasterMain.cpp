/* 

  MasterConsole
  written specificly for PlanetSourceCode.com
  by Jared Bruni
  www.lostsidedead.com

  "Open Source, Open Mind"

*/


#include "thehead.h"


// instance of the MasterXHWND 
MasterXHWND mxhwnd;
// instance of the MasterConsole
MasterConsole console;


// function prototypes
inline void load();

// main entry point
int XSTD MasterMain(HINSTANCE hInst,LPSTR line)
{

	if( mxhwnd.CreateMasterX( "MasterConsole",640,480,COLOR_DEFAULT,event,hInst,NULL,NULL) )
	{
		load();
		return (mxhwnd.InitLoop(render));
	}

	return (0);
}

// program initilization 
inline void load()
{
	mxhwnd.HideCursor();
	console.load();
	console << " Welcome to MasterConsole Streams Example \n Written by Jared Bruni \n Jared@LostSideDead.com \n www.lostsidedead.com \n";
	console << "cmd=)> ";
	console.input();
}


// event callback function (m$ event model)
long XSTD event(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ACTIVATEAPP:
		mxhwnd.activeapp = wParam;
		break;
	case WM_KEYDOWN:
		{

#ifdef iDEBUG
			if( wParam == VK_ESCAPE ) { mxhwnd.Kill(); }
#endif
			console.keypress(wParam);
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return (0);
}

// render to the screen
void render( MASTERSCREEN screen )
{
	console.update();
}


// fix a key, format it correctly
char fixkeys(int key,int caps,bool cmd)
{
	
	char cur;	
	int shift;
	shift = 0;
	// shift switch
	if(GetAsyncKeyState(16))
	{
		shift = 1;
		if(caps)
		{
			cur = tolower(key);
		}
		else
		{
			cur = toupper(key);
		}
		// special shift character switch
		
		switch(cur)
		{
		case '0':
			cur = ')';
			break;
		case '1':
			cur = '!';
			break;
		case '2':
			cur = '@';
			break;
		case '3':
			cur = '#';
			break;
		case '4':
			cur = '$';
			break;
		case '5':
			cur = '%';
			break;
		case '6':
			cur = '^';
			break;
		case '7':
			cur = '&';
			break;
		case '8':
			cur = '*';
			break;
		case '9':
			cur = '(';
			break;
		}
	}
	else
	{
		
		if(caps)
		{
			cur =  toupper(key);
		}
		else
		{
			cur = tolower(key);
		}
	}
	
	// quick key to special char switch
	switch(key)
	{
	case 220:
		
		cur = '\\';
		
		break;
		
	case 191:
		if(shift)
		{
			cur = '?';
		}
		else
		{
			
			cur = '/';
		}
		
		break;
		
	case 192:
		
		cur = 'µ';
		break;
		
	case 186:
		if(shift)
		{
			cur = ':';
		}
		else
		{
			cur = ';';
		}
		break;
		
	case 219:
		
		if(shift)
		{
			if(cmd == false)
			{
				cur = '{';
			}
			else
			{
                cur = '/';
			}
		}
		else
		{
			cur = '[';
		}
		
		break;
	case 221:
		if(shift)
		{
			if(cmd == false)
			{
				cur = '}';
			}
			else
			{
                cur = '\\';
			}
		}
		else
		{
			cur = ']';
		}
		
		break;
	case 187:
		if(shift)
		{
			cur = '+';
		}
		else
		{
			cur = '=';
		}
		break;
	case 189:
		
		if(shift)
		{
			cur = '_';
		}
		else
		{
			cur = '-';
		}
		
		break;
	case 188:
		
		if(shift)
		{
			cur = '<';
		}
		else
		{
			cur = ',';
		}
		
		break;
		
	case 190:
		
		if(shift)
		{
			cur = '>';
		}
		else
		{
			cur = '.';
		}
		
		
		break;
	case 222:
		if(shift)
		{
			cur = '\"';
			break;
		}
		else
		{
			cur = '\'';
			break;
		}
		
		
		
		break;
		
		}
		
		return cur;
}

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
// find the amount of characters of a specific type inside the array
int  findcharnum(char* string)
{
	char seps[] = " ";
	char *token;
	int count = 0;

	 /* Establish string and get the first token: */
   token = strtok( string, seps );
   while( token != NULL )
   {
      /* While there are tokens in "string" */
  //    printf( " %s\n", token );
      /* Get next token: */
      token = strtok( NULL, seps );
	  count ++;

   }

   return count;
}

bool isnum(char* data)
{
	for( unsigned int i = 0; i < strlen(data); i++)
	{
		if( data[i] != '0' && data[i] != '1' && data[i] != '2' && data[i] == '3' && data[i] != '4' && data[i] != '5' && data[i] != '6' && data[i] != '7' && data[i] != '8' && data[i] != '9' )
		{
			return false;
		}
	}

	return true;
}

// does this file exisit ?
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

	if( sfile == NULL )
	{
		return -1;
	}

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

	if( ofile == NULL )
	{
		strcpy(data,"î");
		return;
	}

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


	return -1;
}
