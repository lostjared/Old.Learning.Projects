/* MasterX Software Devlopment Kit (SDK) 2.1
DirectX/Win32 Encapsulation For easy game programming.
Written by Jared Bruni
Email Me: JaredBruni@lostsidedead.com 
www.lostsidedead.com


  now contains NuclearMedia
  written by Lee Trager 

  now also includes MasterGraphicEx
  by Danny Anderson
   garageguy@garagegaming.com
   www.garagegaming.com


  as well as MasterLump resource file support 
  
  for MasterX SDK documentation check out
  www.lostsidedead.com
 
  note required librarys within your project link settings

  dxguid.lib ddraw.lib dsound.lib dinput.lib  wsock32.lib winmm.lib

  also before you include this header file
  use
  #define MASTERFILE
  to use the File Lump releated algorithms
  use 
  #define WIN2K
  to use Windows 2000 stuff
  (very little as of now)

*/
 

#ifndef MASTERX
#define MASTERX


#define DIRECTINPUT_VERSION 0x700


#include <ddraw.h>
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>
#include <winsock.h>
#include <stdio.h>
#include<stdarg.h> 
#include<stdlib.h>
 


// the default port ID for mastersocket(when it sees -1 it changes it to 7)
#define DEFAULT_PORT -1
// for register based calling convention rather then stack based (speed)
#define FAST __fastcall
// for std based calling convention
#define XSTD __stdcall 
#define MXENTRY __stdcall
// for pascal based calling convention
#define XPAS __pascal
// joydead zone
#define JOY_DEADZONE 20 

// Helper typedef's
typedef int MASTERSCREEN;
typedef int MASTERMSG;
typedef long MXRESULT;
typedef unsigned long WindowHandle;



enum DisplayColor { COLOR_8, COLOR_16,COLOR_24,COLOR_32,COLOR_DEFAULT };

// ADT game object
class MasterGameObject 
{
public:
	virtual void load() = 0;
	virtual void update() = 0;
};
 
// the masterscreen structure, holds the pointers to the directX com objects interfaces
struct MasterScreen
{
	LPDIRECTDRAW lpDD;
	LPDIRECTDRAWSURFACE lpBack;
	LPDIRECTDRAWSURFACE lpFront;
	~MasterScreen();
};

// text output object, which exisits inside the MasterXHWND object
class MasterText
{
public:
	MasterScreen*  scr;
	HFONT font;
	HFONT underfont;
	
	COLORREF bk;
	COLORREF text;
	void init(MasterScreen*);
	void setfont(HFONT);
	void setunderfont(HFONT);
	void setbkcolor(COLORREF);
	void settextcolor(COLORREF);
	void FAST printtext(char*,int x,int y);
	void FAST sprinttext(int x, int y,char* str, ...);
	void FAST printtextunderline(char*, int x, int y);
	void FAST printtextrect(char*, int x, int y, int w, int h);
	void FAST printtextrectf(int x, int y, int x2, int y2, char* str, ...);


	void setdefaultfont();
};

// graphic object, - displays bitmaps, and peices of bitmaps, supports color keys
typedef class MasterGraphic
{
protected:
	MasterScreen* scr;
	LPDIRECTDRAWSURFACE surf;
	char  filename[50];
	bool ckey;
public:
	int w;
	int h;
	void init(MasterScreen* scr);
	bool LoadGraphic(char* filename);
	bool LoadGraphic(char* filename,MasterScreen* scr);
	void ReLoadGraphic();
	void SetColorKey(COLORREF r);
	void DisplayGraphic(int x, int y);
	void DisplayGraphicEx(int bx, int by, int bw, int bh,int image_x, int image_y);
	~MasterGraphic();
	MasterGraphic();
	void Release();
}MasterSprite;

////////////////////////////////////////////////////////////////////
//Author: Danny Anderson
//contact: garageguy@garagegaming.com
//
//This is a MasterGraphicEx. It adds more functionality to MasterGraphic.
//You can scale your image, flip it vertically & horizontally (very slow),
//You can clip your blit to the screen. There are also filters that can
//be applied to the graphic on the fly, such as grayscale, darken, brighten, etc.
//These filters should be applied during initialization. They require heavy
//calculations and can be slow if put into the drawing loop. Calling ReLoadGraphic
//will restore your graphic to the original state. Works for 15, 16, 24, 32 bit
//color spaces.
//
//Note: In the original MasterGraphic, the private members need to be
//		declared as protected in order for MasterGraphicEx to work.
//
//Bugs: This is still in testing phase. There are a few problems, such
//		as the 15/16 bit transparency color getting filtered. Also, if
//		you apply a filter it could theoretically change that pixel to
//		the transparency color. apply_balance has not been thoroughly
//		tested. Otherwise this class is rocking and rolling!
////////////////////////////////////////////////////////////////////

class MasterGraphicEx : public MasterGraphic
{
protected:
	//bit conversion masks
	enum {BIT_5_MASK = 0x1F, BIT_6_MASK = 0x3F, BIT_8_MASK = 0xFF};
	//internal filter constants
	enum {GRAYSCALE, BRIGHTEN, DARKEN, COMPLEMENT, BALANCE};
	//used by flip specifically and the Blt method
	DDBLTFX	m_ddbltfx;

	COLORREF color_key;
protected:
	//generic drawing routines
	void generic_draw (const int x, const int y, const int dest_w, const int dest_h, DWORD blt_flags);
	void generic_draw_clip (const int x, const int y, const int dest_w, const int dest_h, const RECT* clip_rect, DWORD blt_flags);

	//get this graphic's surface description
	DDSURFACEDESC get_surface_desc ();
	//changes r, g, b acording to the filter type
	void filter (const int type, int& r, int& g, int& b, const float r_amount = 0.0f, const float g_amount = 0.0f, const float b_amount = 0.0f);
	//cycles through the pixels and applies a filter to each
	void apply_filter_to_pixels (const int type, const float r_amount = 0.0f, const float g_amount = 0.0f, const float b_amount = 0.0f);
	//get the bits per pixel of environment
	int get_bit_count ();
	//constains a float amount
	void constrain_amount (float& amount, const float low, const float high);
public:
	MasterGraphicEx ();

	//### draw methods ###

	//same as DisplayGraphic, but should not give errors
	void DisplayGraphic_draw (const int x, const int y);
	//scale the graphic to new width & height, no clipping
	void DisplayGraphic_scale (const int x, const int y, const int dest_w, const int dest_h);
	//flip a graphic horizontally or vertically (slow)
	void DisplayGraphic_flip (const int x, const int y, const bool horizontal);

	//### clipping version of draw methods ###

	//draw the graphic clipped
	void DisplayGraphic_clip (const int x, const int y, const RECT* clip_rect);
	//scale the graphic with clipping
	void DisplayGraphic_scale_clip (const int x, const int y, const int dest_w, const int dest_h, const RECT* clip_rect);
	//scale the graphic to new width & height, no clipping (slow)
	void DisplayGraphic_flip_clip (const int x, const int y, const bool horizontal, const RECT* clip_rect);

	//### filters ###

	void apply_grayscale ();
	void apply_complement ();
	//range 0 to 1
	void apply_brighten (float amount);
	//range 0 to 1 
	void apply_darken (float amount);
	//range -1 to 1
	void apply_balance (float r_amount, float g_amount, float b_amount);

	//this is overloaded because i cant get the ColorKey by
	//using DDSURFACE::GetColorKey (...)
	void SetColorKey (COLORREF r);
};

// mastersound object ,  - sound object, plays imbeded wave files
class MasterSound
{
public:
	IDirectSoundBuffer *pSound;
	bool LoadSound(IDirectSound* pds,LPCTSTR name);
	void Play();
	bool PlayStatus();
	void Release();

	MasterSound();
	~MasterSound();
};

// Painting Functions
class MasterPaint
{
	MasterScreen* scr;
public:

	void init(MasterScreen* xscr);
	void FAST mxdrawrect(int x, int y, int x2, int y2,COLORREF fill,COLORREF outline);
	void FAST mxdrawroundrect(int x, int y, int x2, int y2,int cw, int ch, COLORREF fill,COLORREF outline);
	void FAST mxdrawpie(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2,COLORREF fill, COLORREF outline);
	void FAST mxdrawchord(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2, COLORREF fill, COLORREF outline);
	void FAST mxdrawellipse(int x, int y, int x2, int y2,COLORREF fill,COLORREF outline);
	void FAST mxsetpixel(int x, int y, COLORREF rgbval);
	COLORREF FAST mxgetpixel(int x, int y);
	void FAST mxarc(int x1,int x2, int x3, int x4, int x5, int x6, int x7, int x8,COLORREF fill,COLORREF outline);
	void FAST mxpolygon(CONST POINT* point,int n_points,COLORREF fill,COLORREF outline);
	void FAST mxlineto(int x, int y,COLORREF fill,COLORREF outline);
	void FAST mxanglearc(int x, int y, long radius,float startangle, float sweepangle,COLORREF outline);
	void FAST mxhorizontalline(int x, int x2, int y,COLORREF color);
	void FAST mxverticalline(int y1,int y2,int x,COLORREF color);
	void FAST mxline(int start_x, int start_y, int stop_x, int stop_y,COLORREF color);// draw diagnoal lines
};

// MasterMedia class, written by Lee Trager ( age : 13 years old )
// you can contact Lee, his screen name on AIM is nukem996
// if you find any problems with his code, or want to
// help him work on it, go ahead and message him
class MasterMedia {

private:

	//gets error number
	long a;
	//for getshortpath
	char finname[1000];
	//to put string together
	char todo[2000];
		
	//error code
	void error(long what){
		mciGetErrorString(what, err, 128);
	}

public:

	char cfile[255];
	//this is where the error is stored
	char err[10000];
	 //this is the alias name of the file ex. mpeg
	char alias[100];
	 //tells u the status of a file
	TCHAR statuss[40];
	//tells u the position number(millisec)
	TCHAR p[40];
	//tells u the lenght number(millisec)
	TCHAR l[40];

	//opens files and dose not put them in a window
	void open(char file[1000]){
		if(GetShortPathName(file, finname, 1000) != 0){
			strcpy(cfile,file);
			fopen(finname);
		}
	}

	// get a pointer to the name of the currently opened file
	char* openedfile()
	{
		return (char*) cfile;
	}


	// open mp3
	void openmp3(char file[1000])
	{ 
		strcpy(alias,"mpeg");
		open(file);
	}

	/*if you have the short path name call to this
	by doing this the file will load faster
	opens files and dose not put them in a window*/
	void fopen(char file[1000]){
		close();
		sprintf(todo, "open %s type mpegvideo Alias %s", file, alias);
		a = mciSendString(todo, 0, 0, 0);
		error(a);
    }

	//open files and puts them in a parent space
	void vidopen(char file[1000], HWND parent){
		if(GetShortPathName(file, finname, 1000) != 0){
			fvidopen(finname, parent);
		}
	}

	/*if you have the short path name call to this
	by doing this the file will load faster
	open files and puts them in a parent space*/
	void fvidopen(char file[1000], HWND parent){
		close();
		sprintf(todo, "open %s type mpegvideo Alias %s parent %s Style 1073741824", file, alias, parent);
		a = mciSendString(todo, 0, 0, 0);
		error(a);
	}

	//play file
	void play(){
		sprintf(todo, "Play %s from 0", alias);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
    }

	//stop file
    void stop(){
		sprintf(todo, "Stop %s", alias);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
    }

	//pause file
	void pause(){
		sprintf(todo, "Pause %s", alias);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
    }

	//resume file
    void resume(){
		sprintf(todo, "Resume %s", alias);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
    }

	//close file
    void close(){
		sprintf(todo, "Close %s", alias);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
	}

	/*for poistion and lenght error code will now work winmm.dll returns too big of a char
	to ask for the error code it has to be an int but since we cannt use a int we cannt use
	error code here*/
	//get the poistion of a file
	
	unsigned long poistion(){
		sprintf(todo, "set %s time format milliseconds", alias);
		mciSendString (todo, 0 ,0, 0);
		sprintf(todo, "status %s position", alias);
		mciSendString (todo, p, 40, 0);

		return ( unsigned long ) atol(p);
	}

	//gets the length of a file
	unsigned long length(){
		sprintf(todo, "set %s time format milliseconds", alias);
		mciSendString (todo, 0, 0, 0);
		sprintf(todo, "status %s length", alias);
		mciSendString (todo, l, 40, 0);
		return ( unsigned long ) atol (p);
	}

	//changes volume sp = speaker vol = what the volume should be set at
	void volume(char sp[6], long vol){
		vol = vol * 10;
		sprintf(todo, "setaudio %s %s Volume to %d", alias, sp, vol);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
	}

	//resize the video
	void resizevid(int left, int top, int width, int height){
		sprintf(todo, "put %s window at %i %i %i %i", alias, left, top, width, height);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
	}

	//seek somewhere with in the file
	void seekto(int where){
		where = where * 1000;
		sprintf(todo, "set %s time format milliseconds", alias);
		a = mciSendString(todo, 0, 0, 0);
		error(a);
		sprintf(todo, "play %s from %i", alias, where);
		a = mciSendString(todo, 0, 0, 0);
		error(a);
	}

	//finds out the status of whats being played
	void status(){
		sprintf(todo, "status %s mode", alias);
		a = mciSendString(todo, statuss, 40, 0);
	}

	//set the speed of a file 1000 = normal below 1000 = slower above 1000 = faster
	//changes speed will make audio only come out the frount 2 speakers
	void speed(int spe){
		sprintf(todo, "set %s speed %i", alias, spe);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
	}

	//auto repeat the file repeat [t] = true then repeat file false it wont or will stop
	void repeat(bool repeatt){
		if (repeatt == true){
		sprintf(todo, "play %s notify repeat", alias);
		a = mciSendString(todo, 0, 0, 0);
		error(a);
		}
		else{
			sprintf(todo, "play %s", alias);
			a = mciSendString(todo, 0, 0, 0);
			error(a);
		}
	}
};
// end of lee's media class
// back to jareds codes :)


// the MasterXHWND object, thie is the host object
class MasterXHWND
{
	MASTERSCREEN mscr;
	DDBLTFX ddbltfx;

	int pre_time;
    int timer_count;

	bool time_flag;

	void Destroy();
    bool setprimarysurface();
	bool initSound();
	void initInput();
	
public:
	HWND hwnd;
	MasterScreen scr;
	MasterText   text;
	MasterPaint  paint;
	MasterMedia  media;
	bool alive;
	UINT activeapp;
	IDirectInput		*pDI;
    IDirectInputDevice	*pKeyboard;
    IDirectSound	*pDS;
	
	
	void (* update) (MASTERSCREEN xscr);
	bool CreateMasterX(char* mytitle,int width,int height,DisplayColor color,WNDPROC proc,HINSTANCE hInst,HICON icon,HCURSOR cursor);
	WPARAM InitLoop( void (* update) (MASTERSCREEN xscr));
	void Kill();
	MASTERSCREEN  GetScreen();
	void SetScreen(MASTERSCREEN xmscr);
	LRESULT SendMasterMessage(UINT msg,WPARAM wParam,LPARAM lParam);
	void clear();
	void mx_update();
	bool LoadGraphic(MasterGraphic* g, char* filename);
	bool LoadSound(MasterSound* s,LPCSTR resourceID);
    bool KeyCheck(int key);
	bool AsyncKeyCheck(int key);
	void InitTimer(int id, int interval);
	void DestroyTimer(int id);
	void GetMousePosWin(long& x, long& y);
	HFONT CreateMasterFont(char* font_name,int size);
	void HideCursor();
	void RestoreCursor();
	bool TimeChange();
	void ChangeTime();
	void SetTimeFlag();
	bool SyncChange();
};


//******************************** DirectDraw/DirectSound Helper Functions.. from ddutil
IDirectDrawSurface* DDLoadBitmap(IDirectDraw* pdd, LPCSTR szBitmap);
IDirectDrawSurface* CreateOffScreenSurface(IDirectDraw* pdd, int dx, int dy); // Creating the Surface
HRESULT DDCopyBitmap(IDirectDrawSurface* pdds, HBITMAP hbm, int dx, int dy); // Copy Bitmap
///////////////////////////////////////////////////////////////////////////////
IDirectSoundBuffer *DSLoadSoundBuffer(IDirectSound *pDS, LPCTSTR lpName);
BOOL DSReloadSoundBuffer(IDirectSoundBuffer *pDSB, LPCTSTR lpName);
BOOL DSGetWaveResource(HMODULE hModule, LPCTSTR lpName,
					   WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData, DWORD *pdwWaveSize);
BOOL DSFillSoundBuffer(IDirectSoundBuffer *pDSB, BYTE *pbWaveData, DWORD dwWaveSize);
BOOL DSParseWaveResource(void *pvRes, WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData, 
						 DWORD *pdwWaveSize);
HRESULT
DDSetColorKey(IDirectDrawSurface * pdds, COLORREF rgb);
DWORD
DDColorMatch(IDirectDrawSurface * pdds, COLORREF rgb);

HRESULT
DDCopyBitmap2(IDirectDrawSurface * pdds, HBITMAP hbm, int x, int y,
			  int dx, int dy);
HRESULT
DDReLoadBitmap(IDirectDrawSurface * pdds, LPCSTR szBitmap);
//********************************************************************************************
// make a font
HFONT MakeFont(char* ftype, int size);
int APIENTRY MasterMain(HINSTANCE hInst,LPSTR line);// mastermain entry point
// mxbitmap structure, for a surfaces information
struct mxbitmap
{
	int w;
	int h;
	IDirectDrawSurface* surf;
};

static int MXWIDTH;
static int MXHEIGHT;
static bool sound_ok;

// base screen object, inhert this object if you wish for it to have access to MasterXHWND object from a remote location
// it is good for if you want to make sections of the game in differnt areas of the code.
struct ScreenObject
{
	MASTERSCREEN sub_screen;
	MasterXHWND* mxhwnd;

	inline Init(MasterXHWND* mxhwndx)
	{
		mxhwnd = mxhwndx;
	}

	inline MASTERSCREEN getscreen()
	{
		return sub_screen;
	}

	inline void setscreen(MASTERSCREEN xscreen)
	{
		sub_screen = xscreen;
	}
};

//******************* mastersocket

// initilize and kill winsock
void initwinsock();
void killwinsock();

// structure to automaticly initlize and kill winsock
struct AutoWinSockHandle
{
	inline AutoWinSockHandle()
	{
		initwinsock();
	}

	inline ~AutoWinSockHandle()
	{
		killwinsock();
	}
};

static AutoWinSockHandle sock_handle; // automaticly construct, and deconstruct
// winsock with this static structure

struct MasterSocket
{
	SOCKET socketx; // the socket structure
	HWND  hwnd; // handle of the window the socket is attached to
	UINT  SOCKET_ID; // socket ID
	void CreateSocket(HWND hwndx,UINT SOCKET_IDx);// create the socket
	void Listen(UINT port);// listen on the socket
	void Connect(char* ipaddress,UINT port);// connect with the socket
	void Send(char* buff, int len); // send data with a connected socket
	int Recive(char* buff,int len);// recive data
	void Accept(); // accept a incomin socket
	const UINT GetID();// get the ID of this socket
	void Close();// close the socket
};

// MasterJoyStick for joysticks


struct MasterJoyStick
{
	JOYINFOEX joystickInfoEx ;// information about are joystick
	JOYCAPS   joystickCaps; // caps structure
	bool joystickPresent;
	bool joystickHasThrottle;
	bool joystickActive;
	unsigned int joystickDeadXMin,joystickDeadXMax,joystickDeadYMin,joystickDeadYMax;
	unsigned int GetJoysticks(); // returns the number of joysticks the drivers support
	bool         JoyExisit(); // does a joystick exisit
	bool         SetupJoystick(); // setup the default joystick
	bool         GetJoystickCoords(JOYINFOEX* info); // get joystick coords structure
	bool         JoyStop();
	bool         JoyForward();
	bool         JoyBackward();
	bool         JoyRight();
	bool         JoyLeft();
	int          GetButtonPressed(JOYINFOEX*);
	int          JoyButtonDown();

	inline ~MasterJoyStick()
	{
		ZeroMemory(&joystickInfoEx,sizeof(joystickInfoEx));
	} 
};


#endif

#ifdef MASTERFILE

// option of whether or not to use Master Lump algorithms


#define SEPKEY "{mx-sep!}"

#define FDISPLAY // for debugging


// datablock structure
struct Master_block 
{
	char* data;
	char filename[100];

	unsigned long size_t;
	int size_f;
};
// wr file table
struct Master_table
{
	struct Master_block* blocks;
	unsigned long block_num;
};

// function prototypes
// load a file into a datablock
void loadblock(char* filename, struct Master_block* block);
void freeblock(struct Master_block* block);
unsigned long flen(const char* filename);
BOOL isfile(char* filename);
void readfile(const char* filename,char* data);
void savetable(char* table_name, struct Master_table* table);
void loadtable(char* table_name, struct Master_table* table);
void writeblock(FILE* file, struct Master_block* block);
void table_init(struct Master_table* table, unsigned long count);
void table_free(struct Master_table* table);
void table_addfile(struct Master_table* table, char* filename);
void table_extract(struct Master_table* table);
void table_extractblock (struct Master_block* block);


#define NULLPOS -1
#define FAIL -1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

int findstr(const char *string, const char *search);// find string
int bfindstr(const char *string, const char *search);// backwards find string
int ifindstr(int start, const char *string, const char *search, unsigned long size_t);// in find string
int ibfindstr(int start, const char *string, const char *search);// in backwards find string
void leftcopy(const char *in, char *out, int pos);// left copy
void rightcopy(const char *in, char *out, int pos);// right copy
void midcopy(const char *in, char *out, int start, int stop);// mid copy
void killspace(char *str);// kill space
int  findoccourance( const char *str, char c);// find occourance
int  findstroc( const char *str, const char *x, unsigned long size_t);
BOOL ishexc(char c);// is this a hex character?
BOOL ishex(char *data);// does this string only contain hex digits?
unsigned long hextointc(char c); // translate this character, into its integer equilvanet
unsigned long  hextoint(char *data); // translate this string of hex characters, into a integer
BOOL iop(char *data); // do illegal characters exisit within this string
BOOL iopc(char c); // illegal character?
BOOL isnumeric(char *numeric); // is this a numeric string?
int  quotesearch(int start, const char* source, const char search);// do a propper quote search (not looking at values with " " around them)
int  linebypos(const char* code, int pos);
void killfilepath(char* str);



// return the length of this file
unsigned long flen(const char *filename)
{
	FILE* sfile;
	unsigned long count = 0;

	sfile = fopen(filename,"rb+");

	while (1)
	{
		char c;
		c = fgetc( sfile );
#ifdef FDISPLAY 
		printf("%c",c);
#endif
     	if(feof(sfile))
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
		if(feof(ofile))
		{
			break;
		}

		data[pos] = c;
		pos++;

	}

	data[pos] = 0;
	fclose(ofile);
}

// load information from disk into a block of data
void loadblock(char* filename, struct Master_block* block)
{
	block->data = NULL;
	
	if(isfile(filename))
	{
		block->size_t = flen(filename)+1;
		block->data =  (char*)malloc(flen(filename)+5);
		strcpy(block->filename,filename);
		block->size_f = strlen(filename) + 1;
		readfile(filename,(char*)block->data);
 
	}
}

// free the block
void freeblock(struct Master_block* block)
{
	if(block->data != NULL)
	{

	free(block->data);
	free(block);

	}
}

// Masterite the block to a already opened file
void Masteriteblock(FILE* file, struct Master_block* block)
{
	unsigned int i;

	fprintf(file,"%s%s;%i:",SEPKEY,block->filename,block->size_t);

	for(i = 0; i < block->size_t; i++)
	{
		fputc(block->data[i],file);
	}
}

// load a table from file
void loadtable(char* table_name, struct Master_table* table)
{

	int amt = 0; // amount of seperation keys
	char* tdat;
	int file_len = flen( table_name );
	int start_offset = -1;




	tdat = (char*)malloc ( file_len + 1);

	readfile(table_name, tdat);

	amt = findstroc( tdat, SEPKEY, file_len );

	table_init( table, amt );


	while (1)
	{
		char tinfo[200];
		char tsize[0xFF];
		int open_pos = 0, close_pos = 0,end_pos = 0;
		long read_size = 0;
		long start_pos = 0;
		int addoff = 0;



		open_pos = ifindstr( start_offset + 1, tdat, SEPKEY, file_len );

		if(open_pos == -1) { break; }// no more seperation keys
		close_pos = ifindstr( open_pos, tdat, ";", file_len );
		end_pos = ifindstr( close_pos, tdat, ":", file_len );

		midcopy (tdat, tinfo, open_pos + strlen(SEPKEY),close_pos);
		midcopy (tdat, tsize, close_pos + 1, end_pos );


	/*	printf(" filename: %s size: %s", tinfo, tsize);

		system("pause"); */
		strcpy ( table->blocks[table->block_num].filename, tinfo);

		read_size = atol ( tsize );

		// now allocate the correct amount in the data buffer
		table->blocks[table->block_num].data = (char*)malloc ( read_size + 1 );
		table->blocks[table->block_num].size_t = read_size;

		for( start_pos = end_pos + 1; start_pos < end_pos + 1 + read_size; start_pos ++ )
		{
			table->blocks[table->block_num].data [ addoff ] = tdat [ start_pos ];
			addoff++;
		}

		table->blocks[table->block_num].size_t = read_size;


		// read in the data, proccess it into the table for a extract 

		table->block_num++;
		// set th enew offset

		start_offset = open_pos + 1;


	}

	free(tdat);


}

// save a table to file
void savetable(char* table_name, struct Master_table* table)
{
	// save the table to a binary file, to be read back
	unsigned long i;
	FILE* tfile;

	tfile = fopen(table_name,"w");

	for (i = 0; i < table->block_num; i++)
	{
		Masteriteblock(tfile,&table->blocks[i]);
	}

	fclose(tfile);
}

//
void table_init(struct Master_table* table, unsigned long count)
{
	table->block_num = 0;
	table->blocks = (struct Master_block*)malloc ( sizeof( struct Master_block ) *  count );
}

void table_free(struct Master_table* table)
{
	unsigned long i ;
	for( i = 0; i < table->block_num; i++)
	{
		free( table->blocks[i].data );

	}
	free(table->blocks);
}

void table_addfile(struct Master_table* table,char* filename)
{
	loadblock(filename,&table->blocks[table->block_num]);
	killfilepath(table->blocks[table->block_num].filename);
	table->block_num++;
}


void table_extract(struct Master_table* table) 
{
	unsigned long i;

	for( i = 0; i < table->block_num; i++)
	{
		table_extractblock ( &table->blocks[i] );
	}
}

void table_diskclr(struct Master_table* table)
{
	unsigned long i;

	for( i = 0; i < table->block_num; i++)
	{
		DeleteFile(table->blocks[i].filename);
	}
}

// extract this block
void table_extractblock (struct Master_block* block)
{
	FILE* sfile;
	unsigned long pos = 0;

    sfile = fopen(block->filename,"w");
 
	for(pos = 0; pos < block->size_t; pos++)
	{
		fputc( block->data [ pos ] , sfile );
	}
 

	fclose (sfile);

}


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
int ifindstr( int start, const char *string, const char *search, unsigned long size_t)
{
	int i = 0,p = 0,len = strlen(string),len2 = strlen(search);

	for(i = start; i < (int) size_t; i++)
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

	temp = (char*)malloc(len + 1);
	
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

	hexval = (unsigned long*)malloc ((len+1) * sizeof(unsigned long));

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


// 

int findstroc(const char *search, const char* str, unsigned long size_t)
{
	int pos;
	int amt = 0;
	pos = findstr( search, str );
	if( pos == -1 ) { return -1; } // failure
	amt ++;

	while(1)
	{
		pos = ifindstr(pos+1,search,str,size_t);

		if(pos == -1)
		{
			break;
		}
		else
		{
			amt++;
		}
	}


	return amt;
}

// kill the path from a file name
void killfilepath(char* str)
{
	int lpos;

	lpos = bfindstr( str, "\\");
	if( lpos != -1) {

		char* temp = (char*)malloc ( strlen (str) + 1 );

		rightcopy ( str, temp, lpos + 1);
		strcpy( str, temp );

		free( temp );

	}
}

#endif

