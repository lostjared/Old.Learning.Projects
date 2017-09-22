/* MasterX Software Devlopment Kit (SDK) 1.9.1
DirectX/Win32 Encapsulation For easy game programming.
Written by Jared Bruni
Email Me: JaredBruni@lostsidedead.com 
www.lostsidedead.com


  now contains MasterX Media ( Mp3 Class ) 
  written by Lee Trager ( newest member of lostsidedead.com )
  

  for MasterX SDK documentation check out
  www.lostsidedead.com/gameprog/

  I really am a video game programming fan
 
  note required librarys within your project link settings

  dxguid.lib ddraw.lib dsound.lib dinput.lib  wsock32.lib winmm.lib

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
 
// the masterscreen structure, holds the directX objects
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
			fopen(finname);
		}
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
	void poistion(){
		sprintf(todo, "set %s time format milliseconds", alias);
		mciSendString (todo, 0 ,0, 0);
		sprintf(todo, "status %s position", alias);
		mciSendString (todo, p, strlen(p), 0);
	}

	//gets the lenght of a file
	void lenght(){
		sprintf(todo, "set %s time format milliseconds", alias);
		mciSendString (todo, 0, 0, 0);
		sprintf(todo, "status %s length", alias);
		mciSendString (todo, l, strlen(l), 0);
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
		a = mciSendString(todo, statuss, strlen(statuss), 0);
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

//*********************************

// Note: MasterAnimation Postponed, until 2.0
// will come with a animation editor

