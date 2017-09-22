/* 

  MasterConsole


  written specificly for PlanetSourceCode.com
  by Jared Bruni
  www.lostsidedead.com

  "Open Source, Open Mind"

*/

#include "thehead.h"

// setting the consoles properties

// set the background color
void MasterConsole::setbkcolor(COLORREF x)
{
	back_color = x;
}
// set the text color
void MasterConsole::settextcolor(COLORREF x)
{
	fore_color = x;
}
// set the font
void MasterConsole::setfont(HFONT f)
{
	font = f;
}

// concatinate the data into the buffer
void MasterConsole::concat(char* b)
{
	strcat(buffer, b);
	linescan();
}

// next command 
void MasterConsole::nextcmd()
{
	linescan();
	if( do_batch == true ) { return; }
	printf("\ncmd=)> ");
	input();
}

// concatinate the key into the buffer
void MasterConsole::concatkey(int key)
{
	if( do_input != true ) { return; }

	int lenbuf = strlen( buffer );
	int size = lenbuf - start_pos;
	if( size >= letter_max - 15 && key != VK_RETURN && key != VK_BACK ) { return; }

 	switch(key)
	{
	case VK_UP:
	case VK_DOWN:
	case VK_LEFT:
	case VK_RIGHT:
	case VK_ESCAPE:
	case VK_SHIFT:
	case VK_CONTROL:
	case VK_HOME:
		return;
		break;
	case VK_RETURN:
		{
			do_input = false;
			int stop_pos = strlen(buffer);
			char *inputbuffer;
			int   buf_size;
			buf_size = strlen(buffer) - start_pos + 5;
			inputbuffer = new char [ buf_size + 1];
			midcopy( buffer, inputbuffer, start_pos, stop_pos);
			if( console_input == false )
			{
			
			// let the command prompt, proccess the data
			proccmd( inputbuffer );

			}
			else
			{
				// let the user retrive the data
				console_input = false;
				ofstream fout("c:\\stream.i");
				fout << inputbuffer;
				fout.close();
				SendMessage( FindWindow("master_console_app",NULL),MASTER_IN,0,0); 
			}

			delete [] inputbuffer;
			inputbuffer = 0;
			return;
		}
		break;
	case VK_BACK:
		{
			int pos;
			pos = strlen(buffer);
			pos--;
			if( pos < 0 ) { pos = 0; buffer[0] = 0; return; }
			if( pos < start_pos ) { return; }
			buffer[pos] = 0;
			return;
		}
		break;
	case VK_CAPITAL:
		{
			
			if(icaps == true)
			{ 
				icaps = false; 
			} 
			else 
			{
				icaps = true;
			}
			return;
		}
		break;
		
	}

 	int len;
	len = strlen(buffer);
	buffer[len] = fixkeys(key,(int)icaps,false);
	len++;
	buffer[len] =0;
}

// flush the buffer out
void MasterConsole::flush()
{
	strcpy( buffer, "");
	buffer[0] = 0;
}

// print formated data into the buffer ( stream )
void MasterConsole::printf( const char *str, ... )
{
	if( do_input == true ) { return; } // cannot print while they are inputing
	va_list list; 
	char* string;
	string = new char [ strlen(str) + 2];
	va_start(list, str); 
	vsprintf((char*)string,str,list);
	va_end(list); 
	concat(string);
	delete [] string;
	string = 0;
}

// stream the data into the buffer using the output stream data
MasterConsole& MasterConsole::operator<<(char* data)
{
 	concat(data);
	return(*this);
}

// stream the data into the buffer this time a integer
MasterConsole& MasterConsole::operator <<(int data)
{
 	char numeric[10];
	itoa( data,numeric,10);
	concat( numeric );
	return (*this);
}

MasterConsole& MasterConsole::operator <<(char c)
{
	char pC[1];
	pC[0] = c;
	pC[1] = 0;
	concat(pC);
	return (*this);
}

MasterConsole& MasterConsole::operator<<(long data)
{
  	char numeric[25];
	ltoa(data,numeric,10);
	concat(numeric);
	return (*this);
}

MasterConsole& MasterConsole::operator<<(double data)
{
	char numeric[25];
	gcvt(data,10,numeric);
	concat(numeric);
	return (*this);
}

MasterConsole& MasterConsole::operator <<(short data)
{
 	char numeric[10];
	itoa( (int)data, numeric, 10);
	concat(numeric);
	return (*this);
}


// buffer scan - this algorithm is designed to ensure
// that there are no more then 120 letters per line
void MasterConsole::bufferscan()
{
	int len = strlen(buffer);
	if( len < 119 ) { return; } // no need to scan
	// ok there is a need to scan, so first lets setup a temporary
	// buffer to copy data into
	char *temp;
	temp = new char [ strlen( buffer ) + 50 ]; // size it up just in case :)
	int counter = 0;
	int temp_pos = 0;
	bool change = false;

	for( unsigned int i = 0; i < strlen(buffer); i++)
	{
		if( buffer[i] == '\n' )
		{
			counter = 0;
		}
		else
		{
			counter++;
		}

		if( counter >= letter_max )
		{
			temp[temp_pos] = '\n';
			temp_pos++;
			temp[temp_pos] = buffer[i];
			temp_pos++;
			change = true;
		}
		else
		{
			temp[temp_pos] = buffer[i];
			temp_pos++;
		}
	}

	temp[temp_pos] = 0;

	if( change == true )
	{
		strcpy( buffer, temp );
	}

	delete [] temp;
	temp = NULL;
}

// scan the amount of lines, which exisit within the buffer
// if there are more then 39 lines, then remove the first line
void MasterConsole::linescan()
{
 	int n_count = 0;
	int f_pos = -1;

	for( unsigned int i = 0; i < strlen(buffer); i++)
	{
		if( buffer[i] == '\n' ) 
		{ 
			if(n_count == 0) 
			{ 
				f_pos = i;
			} 

			n_count++;
		}
	}

	if( n_count >= 39 && f_pos != -1 )
	{
		char *temp;
		temp = new char [ strlen( buffer ) + 10 ];
		rightcopy( buffer, temp, f_pos + 1 );
		strcpy( buffer,temp );
		delete [] temp;
		temp = NULL;
		linescan();// recursive algorithm
	
	} else  { return; }
}

// input data from the console, and place it in a character array
void MasterConsole::input()
{
	do_input = true;
	start_pos = strlen( buffer );
}

void MasterConsole::ioff()
{
	if(do_input == true )
	{

	do_input = false;
	int s_pos = start_pos - strlen("cmd=)>") - 1;
	if(s_pos < 0 ) { s_pos = 0; }
	buffer[s_pos] = 0;

	}
}
// pause, until another key is pressed
void MasterConsole::pause()
{
	printf("\n Press any key to continue ...");
	do_pause = true;

}

// proccess the command (tokenize the string)
void MasterConsole::proccmd(char *cmd)
{
	if ( strlen(cmd) == 0 ) { nextcmd(); return; }

	char *temp;
	char *temp2;

	temp = new char [ strlen(cmd) + 1 ];
	temp2 = new char [ strlen(cmd) + 1 ];
	strcpy( temp,cmd );
	strcpy( temp2, cmd );

	int num = findcharnum(temp);

 
	delete [] temp;
	temp = NULL;

	char *token;
	char seps[] = " ";

   token = strtok( cmd, seps );

   if( token == NULL ) { nextcmd(); return; } // no tokens found

   int cur_token = 0;
   char *tokens[500]; // no more then 500 tokens allowed


   while( token != NULL )
   {
   	   tokens[cur_token] = token;
	   cur_token++;
       token = strtok( NULL, seps);

   }

   curbuff = temp2;
   
   command( tokens, cur_token );

   delete [] temp2;
   temp2 = NULL;
   curbuff = NULL;

}

// batch proccess this data
void MasterConsole::batch(char *data)
{
	if( strlen(data) == 0 ) { return; } // no data found
	if( ifindstr(0,data,"\n") == -1 )
	{
		// there is only one line of data
		proccmd( data );
		return;
	}

	// there is alot more then just one line of data
	// lets go through, and get each line, and feed it to
	// the proccess command algorithm
	int s_pos = 0;

	for( unsigned int i = 0; i < strlen(data); i++)
	{
		if( data[i] == '\n' )
		{
			char icmd[255];
			midcopy(data,icmd,s_pos,i);
			s_pos = i + 1;
			proccmd(icmd);
		}
	}
	// last cmd
	char ecmd[255];
	rightcopy(data, ecmd, s_pos);
	proccmd(ecmd);

}

// proccess the commands
void MasterConsole::command( char* argv[], int argc )
{
	// dump standard output()
	 
	switch(cmdstrtoint(argv[0]))
	{
	case FLUSH:
		flush();
		break;
	case ABOUT:
		printf("\n MasterConsole .. streams example\nWritten by Jared Bruni\nwww.lostsidedead.com\n:)");
		linescan();
		break;
	case TIME:

		time_t ct;
		time(&ct);
		char* t;
		t = ctime(&ct);
		char the_time[200];
		sprintf(the_time, "\n%s",t);
		printf(the_time);

		break;

	case HAPPY:

		printf(" \n hE hE hE.. your prEEty happy hE hE hE");

		break;
	case ADD:
		{
			
			char dstr[1000];

			if( argc != 3 )
			{
				printf("\n [syntax error] - the add command must take two numeric arguments ");
				nextcmd();
				return;
			}

			long num1, num2, val;
			num1 = atol( argv[1] );
			num2 = atol( argv[2] );
			val = num1 + num2;
			sprintf(dstr,"\n %i + %i = %i",num1,num2,val);
			printf(dstr);

		}
		break;
	case SUB:
		{
			char dstr[1000];

			if( argc != 3 )
			{
				printf("\n [syntax error] - the sub command must take two numeric arguments ");
				nextcmd();
				return;
			}

			long num1, num2, val;
			num1 = atol( argv[1] );
			num2 = atol( argv[2] );
			val = num1 - num2;
			sprintf(dstr,"\n %i - %i = %i",num1,num2,val);
			printf(dstr);
		}
		break;
	case MUL:
		{
			char dstr[1000];

			if( argc != 3 )
			{
				printf("\n [syntax error] - the mul command must take two numeric arguments ");
				nextcmd();
				return;
			}

			long num1, num2, val;
			num1 = atol( argv[1] );
			num2 = atol( argv[2] );
			val = num1 * num2;
			sprintf(dstr,"\n %i * %i = %i",num1,num2,val);
			printf(dstr);
		}
		break;
	case DIV:
		{
			char dstr[1000];

			if( argc != 3 )
			{
				printf("\n [syntax error] - the div command must take two numeric arguments ");
				nextcmd();
				return;
			}

			long num1, num2, val;
			num1 = atol( argv[1] );
			num2 = atol( argv[2] );

			if( num1 == 0 || num2 == 0 ) 
			{
				printf("\n [syntax error] - the div commad cannot divide by zero ");
				nextcmd();
				return;
			}

			val = num1 / num2;
			sprintf(dstr,"\n %i / %i = %i",num1,num2,val);
			printf(dstr);
		}
		break;
	case DUMP:
		{
			char dstr[1000];

			if ( argc != 2 )
			{
				printf("\n [syntax error] - the dump command takes one argument the filename to write the data to");
				nextcmd();
				return;
			}

			ofstream fout( argv[1] );
			fout << buffer << endl;
			fout.close();
			sprintf(dstr,"\n succesful dump of the buffer into the file %s",argv[1]);
			printf(dstr);
		}
		break;
	case EXIT:
		{
			printf("\ngoodbye!!!");
			mxhwnd.Kill();
		}
		break;
	case FCOLOR:
		{
			if( argc != 2 )
			{
				printf("\n[syntax error] - the set color command requires one argument");
				nextcmd();
				return;
			}

			int color = cmdstrtocolor(argv[1]);
			if( color == -1 )
			{
				printf("\n[syntax error] - the set color command requires a valid color");
				nextcmd();
				return;
			}

			fore_color = color;
		}
		break;
	case BCOLOR:
		{
			if( argc != 2 )
			{
				printf("\n[syntax error] - the set color command requires one argument");
				nextcmd();
				return;
			}

			int color = cmdstrtocolor(argv[1]);
			if( color == -1 )
			{
				printf("\n[syntax error] - the set color command requires a valid color");
				nextcmd();
				return;
			}

			back_color = color;

		}
		break;
	case PAUSE:
		{
			pause();
			return;
		}
		break;
	case LOST:
		{
			printf("\n Lost in a sea of Idea, my mind points to a tune\n Something repeating on the dark side of the moon\n I can see beyond the scope of my eyes.\n Imagnation is the key \n Truth in disguise \n ");
			linescan();
			pause();
			return;
		}
		break;
	case ECHO:
		{
			char *ibuff;
			ibuff = new char [ strlen(curbuff) + 1 ];
			int e_pos;
			e_pos = ifindstr(-1,curbuff,"echo")+4;
			rightcopy(curbuff,ibuff,e_pos);
			printf("\n");
			printf(ibuff);
			delete [] ibuff;
			ibuff = NULL;
		}
		break;
	case BATCH:
		{
			if( argc != 2 )
			{
				printf("\n[syntax error] - batch command takes one argument that being the file to proccess");
				nextcmd();
				return;
			}

			if( isfile( argv[1] ) == FALSE )
			{
fe:
				printf("\n[error] - file not found");
				nextcmd();
				return;
			}

			// ok we have the file, so lets load it up,

			char *buf;
			int zlen =  flen( argv[1]  );
			if( zlen == -1) { goto fe; }
			buf = new char [zlen + 1  ];
			readfile( argv[1],buf );
			if( strcmp(buf,"î") == 0 ) { goto fe; }
			do_batch = true;
			batch( buf );
			do_batch = false;
			delete [] buf;
			buf = NULL;  

		}
		break;
	case CALL:// call a C++ program and let it take over control
		{

			
			if( argc == 1 )
			{
				printf("\n[syntax error] call command requires atleast one argument");
				nextcmd();
				return;
			}

			
	
			// ok everything is cool call the program, when its complete, it will return control
			// to the user, at the command prompt
			printf("\n");
			char *ibuff;
			ibuff = new char [ strlen(curbuff) + 1 ];
			int e_pos;
			e_pos = ifindstr(-1,curbuff,argv[1])+strlen(argv[1])+1;
			if( e_pos < (int) strlen(curbuff) )
			rightcopy(curbuff,ibuff,e_pos);
		//	ofstream fout("c:\\stream.p");
		//	fout << ibuff;
		//	fout.close();
	 		ShellExecute(NULL,"open",argv[1],ibuff,NULL,SW_SHOW);
	 		delete [] ibuff;
			ibuff = NULL;
		
		}
		break;
	case -1:
		printf("\n - unknown command");
		break;
	}

	nextcmd();

}

int  MasterConsole::cmdstrtoint( char* data )
{
	if( strcmp( data, "flush") == 0 )
	{
		return 0x1;
	}

	if( strcmp( data, "about") == 0 )
	{
		return 0x2;
	}

	if( strcmp( data, "time") == 0 )
	{
		return 0x3;
	}

	if( strcmp( data, ":)") == 0 )
	{
		return 0x4;
	}

	if( strcmp( data, "add") == 0 )
	{
		return ADD;
	}

	if( strcmp( data, "sub") == 0 )
	{
		return SUB;
	}

	if( strcmp( data, "mul") == 0 )
	{
		return MUL;

	}

	if( strcmp( data, "div") == 0 )
	{
		return DIV;
	}

	if( strcmp( data, "dump") == 0)
	{
		return DUMP;
	}

	if( strcmp( data,"exit") == 0)
	{
		return EXIT;
	}

	if( strcmp( data,"settextcolor") == 0)
	{
		return 0x11;
	}

	if( strcmp(data, "setbkcolor") == 0 )
	{
		return 0x12;
	}

	if( strcmp(data,"pause") == 0 )
	{
		return PAUSE;
	}

	if( strcmp(data,"lost") == 0 )
	{
		return LOST;
	}

	if ( strcmp(data,"echo") == 0 )
	{
		return ECHO;
	}

	if( strcmp(data,"batch") == 0 )
	{
		return BATCH;
	}

	if ( strcmp(data,"call") == 0 )
	{
		return CALL;
	}

	return -1;
}

int MasterConsole::cmdstrtocolor(char *data )
{
	if( strcmp(data,"white")  == 0)
	{
		return RGB(255,255,255);
	}

	if( strcmp(data,"red")  == 0)
	{
		return RGB(255,0,0);
	}

	if( strcmp(data,"blue") == 0 )
	{
		return RGB(0,0,255);
	}

	if( strcmp(data,"green") == 0)
	{
		return RGB(0,200,0);
	}

	if(strcmp(data,"black") == 0)
	{
		return RGB(0,0,0);
	}
	
	return -1;
}