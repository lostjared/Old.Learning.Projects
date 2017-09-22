/* 

  MasterConsole
  written specificly for PlanetSourceCode.com
  by Jared Bruni
  www.lostsidedead.com
  
	"Open Source, Open Mind"
	
*/


#include "masterx.h"
#include <time.h>
#include <fstream.h>
#define iDEBUG  // comment out this defenition, if you wish to not have a debug executable
#define BUFFER_SIZE 5000
#define MASTER_IN WM_USER + 5
#define MASTER_OUT WM_USER + 6
#define MASTER_DONE WM_USER + 7
#define MASTER_INIT WM_USER + 8
#define MASTER_CLEAR WM_USER + 9
#define MASTER_PAUSE WM_USER + 10


// enumerated constants, to stand for the commands
                                                                                                                     // I know I skiped A-F
enum { FLUSH = 0x1, ABOUT = 0x2 , TIME = 0x3, HAPPY = 0x4, ADD = 0x5, SUB = 0x6, MUL = 0x7, DIV = 0x8 , DUMP = 0x9, EXIT = 0x10 , FCOLOR = 0x11, BCOLOR = 0x12, PAUSE = 0x13 , LOST = 0x14, ECHO = 0x15, BATCH = 0x16, CALL = 0x17};

extern MasterXHWND mxhwnd;


// function prototypes
LRESULT APIENTRY event(HWND,UINT,WPARAM,LPARAM);
void render(MASTERSCREEN);
char fixkeys(int key,int caps,bool cmd);
void midcopy(const char *string, char *out, int start, int stop);
void rightcopy(const char *string, char *out, int pos);
int  findcharnum(char* data);
bool isnum(char* data);
BOOL isfile(char *filename);
int flen(const char *filename);
void readfile(const char *filename, char* data);
int ifindstr( int start, const char *string, const char *search);

// MasterConsole class prototype
class MasterConsole : public MasterGameObject {
	
private:
	
	char buffer[ BUFFER_SIZE ];
	COLORREF back_color;
	COLORREF fore_color;
	HFONT    font;
	bool  icaps;
	int   letter_max;
	bool  do_input;
	bool  do_pause;
	bool  do_batch;
	int   start_pos;
	char* curbuff;

	void concat(char*);
	void concatkey(int key);
	void bufferscan();
	void linescan();
	
public:

	bool console_input;
	bool  spause;
 
	// events
	
	// on load
	virtual void load()
	{
		flush();
		font = MakeFont("Arial",12);
		back_color = RGB( 0,0,0 );
		fore_color = RGB( 0,200,0 );
		letter_max = 120;
		do_input = false;
		do_pause = false;
		do_batch = false;
		console_input = false;
		spause = false;
		start_pos = 0;
		curbuff = 0;

	}
	
	// on update
	virtual void update()
	{
		bufferscan();
		mxhwnd.text.setbkcolor(  back_color );
		if( mxhwnd.text.font != font ) 
		{
			mxhwnd.text.setfont( font );
		}
		mxhwnd.text.settextcolor( fore_color );
		if( do_input == false )
		{

		mxhwnd.paint.mxdrawrect(0,0,640,480,back_color,back_color);
		mxhwnd.text.printtextrectf( 0,0,640,480, buffer );

		}
		else
		{
			char* b;
			b = new char [ strlen(buffer) + 10 ];
			strcpy( b, buffer );
			if( rand()%10 > 5 )
			{
				strcat(b,"_");
			}
			mxhwnd.text.printtextrectf(0,0,640,480,b);
			delete [] b;
			b = NULL;
		}
	}
	
	// on keypress
	inline void keypress(WPARAM key)
	{

		if( spause == true && do_pause == true )
		{
			spause = false;
			SendMessage( FindWindow("master_console_app",NULL ), MASTER_PAUSE,0,0);
			do_pause = !do_pause;
			return;
		}

		if( do_pause == true )
		{
			do_pause = !do_pause;// not the pause (set to false)
			printf("\ncmd=)>");
			input();
			return;
		}

		if( do_input == true )
		concatkey(key);
	}
	
	
	
	// method prototypes

	// flush the buffer
	void flush();
	// c style stream
	void printf( const char*, ...);
	// set the text color
	void settextcolor(COLORREF);
	// set the background color
	void setbkcolor(COLORREF);
	// set the font
	void setfont(HFONT font);
	// input data from the stream
	void input();
	// press any key to continue
	void pause();

	// proccess  commands
	void proccmd(char *cmd);
	void batch(char* data);
	void command(char* argv[], int argc);
	void nextcmd();
	int  cmdstrtoint( char* data );
	int  cmdstrtocolor(char *data );
	void ioff();

	// for streaming into the buffer
	MasterConsole& operator<<(char*);
	MasterConsole& operator<<(char);
	MasterConsole& operator<<(int);
	MasterConsole& operator<<(long);
	MasterConsole& operator<<(double);
	MasterConsole& operator<<(short);

};



