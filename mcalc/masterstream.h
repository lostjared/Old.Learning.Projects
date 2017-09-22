/* masterstream.h 
   header file, for creating simple console applications
   that run under MasterConsole
   written by Jared Bruni
   www.lostsidedead.com
*/

#ifndef MASTERSTREAM
#define MASTERSTREAM

#include <windows.h>
#include <fstream.h>
#include <stdio.h>

#define endl "\n"
#define MASTER_IN WM_USER + 5
#define MASTER_OUT WM_USER + 6
#define MASTER_DONE WM_USER + 7
#define MASTER_INIT WM_USER + 8
#define MASTER_CLEAR WM_USER + 9
#define MASTER_PAUSE WM_USER + 10


// yes I know a pipe would have been much more efficent.


int mastermain(char*);
LRESULT APIENTRY WndProc( HWND hwnd , UINT msg, WPARAM wParam, LPARAM lParam );
inline void init();
void readfile(const char *filename, char* data);
int flen(const char *filename);

HWND hwnd;
HWND hconsole;
bool in_go = false;
bool pause_go = false;
char* the_line = NULL;

class masterconsole
{
	void concat(char* buffer);
	void input( char* buffer );

public:

	masterconsole& operator<<(char*);
	masterconsole& operator<<(char);
	masterconsole& operator<<(int);
	masterconsole& operator<<(short);
	masterconsole& operator<<(long);
	masterconsole& operator<<(double);
	masterconsole& operator>>(char*);
	masterconsole& operator>>(int&);
	masterconsole& operator>>(short&);
	masterconsole& operator>>(long&);
	masterconsole& operator>>(double&);

	void pause();
	void clear();
 
};

void masterconsole::concat(char* buffer)
{
	ofstream fout("c:\\stream.o");
	fout << buffer;
	fout.close();
	SendMessage(hconsole,MASTER_OUT,0,0);
	
}

// stream the data
masterconsole& masterconsole::operator <<(char* buffer)
{
	concat(buffer);
	return (*this);
}

masterconsole& masterconsole::operator <<(char c)
{
	char pc[1];
	pc[0] = c;
	pc[1] = 0;
	concat(pc);
	return (*this);
}

masterconsole& masterconsole::operator<<(int num)
{
	char cnum[25];
	itoa(num,cnum,10);
	concat(cnum);
	return(*this);
}

masterconsole& masterconsole::operator <<(short num)
{
	char cnum[25];
	itoa((int)num,cnum,10);
	concat(cnum);
	return(*this);
}

masterconsole& masterconsole::operator <<(long num)
{
	char cnum[50];
	ltoa(num,cnum,10);
	concat(cnum);
	return(*this);
}

masterconsole& masterconsole::operator << (double num )
{
	char cnum[50];
	gcvt(num,10,cnum);
	concat(cnum);
	return(*this);
}

void masterconsole::input(char* buffer)
{
	// send the signal to do input
	// wait in a do events loop
	in_go = true;
	SendMessage(hconsole, MASTER_IN, 0,0);

	// lets wait until, its time to read in the dat
	while( in_go == true )
	{
		MSG msg;
		int t = PeekMessage(0,0,0,0,PM_NOREMOVE);
		if(t == WM_QUIT) { break; }
		TranslateMessage(&msg); 
		DispatchMessage(&msg);
	}

	int len;
	len = flen("c:\\stream.i");
	if(len == -1) { strcpy(buffer,"<null>"); return; }
	readfile("c:\\stream.i",buffer);
	return;
}

// input stream
masterconsole& masterconsole::operator>>(char* buffer)
{
	// send the signal to do input
	// wait in a do events loop
	in_go = true;
	SendMessage(hconsole, MASTER_IN, 0,0);

	// lets wait until, its time to read in the dat
	while( in_go == true )
	{
		MSG msg;
		int t = PeekMessage(0,0,0,0,PM_NOREMOVE);
		if(t == WM_QUIT) { break; }
		TranslateMessage(&msg); 
		DispatchMessage(&msg);
	}

	int len;
	len = flen("c:\\stream.i");
	if(len == -1) { strcpy(buffer,"<null>"); return (*this); }
	readfile("c:\\stream.i",buffer);
	return (*this);
}

masterconsole& masterconsole::operator>>(int& num)
{
	char* buffer;
	buffer = new char [ 5000 ];
	input(buffer);
	num = atoi(buffer);
	delete [] buffer;
	buffer = NULL;

	return (*this);
}

masterconsole& masterconsole::operator>>(short& num)
{
	char* buffer;
	buffer = new char [ 5000 ];
	input(buffer);
	num  = atoi(buffer);
	delete [] buffer;
	buffer = NULL;


	return (*this);
}

masterconsole& masterconsole::operator>>(long& num)
{
	char* buffer;
	buffer = new char [ 5000 ];
	input(buffer);
	num = atol(buffer);
	delete [] buffer;
	buffer = NULL;

	return (*this);
}

masterconsole& masterconsole::operator>>(double& num)
{
	char* buffer;
	buffer = new char [ 5000 ];
	input(buffer);
	num = atof(buffer);
	delete [] buffer;
	buffer = NULL;

	return (*this);
}

// flush out the buffer
void masterconsole::clear()
{
	SendMessage(hconsole,MASTER_CLEAR,0,0);
}
// press any key to continue
void masterconsole::pause()
{
	SendMessage(hconsole,MASTER_PAUSE,0,0);

	pause_go = true;

	while(pause_go == true)
	{
		MSG msg;
		int t = PeekMessage(0,0,0,0,PM_NOREMOVE);
		if(t == WM_QUIT) { break; }
		TranslateMessage(&msg); 
		DispatchMessage(&msg);
	}
}

extern masterconsole console;
masterconsole console;


int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	the_line = line;
	hconsole = FindWindow("MasterConsole",NULL);
	if( hconsole == NULL )
	{
		MessageBox(0,"Error!\nThis application must be ran from the MasterConsole command line"," Runtime Error", MB_ICONERROR );
		return (0);
	}

 	init();
	return (0);
}

inline void init()
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = NULL;
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = "master_console_app";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	hwnd = CreateWindow("master_console_app","",WS_OVERLAPPED,0,0,0,0,0,0,GetModuleHandle(NULL),0);

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}


LRESULT APIENTRY WndProc( HWND hwnd , UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch (msg)
	{
	case WM_DESTROY:
		SendMessage(hconsole,MASTER_DONE,0,0);
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		{
		 
			SendMessage(hconsole,MASTER_INIT,0,0);
			mastermain(the_line);
			SendMessage(hwnd,WM_CLOSE,0,0);
		}
		break;
	case MASTER_IN:
		{
			in_go = false;
		}
		break;
	case MASTER_PAUSE:
		{
			pause_go = false;
		}
		break;

	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return (0);
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


#endif