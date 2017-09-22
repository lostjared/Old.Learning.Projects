/* MasterX Software Devlopment Kit (SDK) 1.7
DirectX/Win32 Encapsulation For easy game programming.
Written by Jared Bruni
Email Me: JaredBruni@lostsidedead.com 
www.lostsidedead.com

  for MasterX SDK documentation check out
  www.lostsidedead.com/gameprog/

  I really am a video game programming fan
 
  note required librarys within your project link settings

  dxguid.lib dddraw.lib dsound.lib dinput.lib  wsock32.lib winmm.lib
*/

/*

  Some of the features for 1.6, were pulled into 2.0
  so that they could be perfected,
  its coming soon..

*/
 
#include <ddraw.h>
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>
#include <winsock.h>


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

// mouse position structure
struct MXMousePos 
{
	long x;
	long y;
	bool button1_state;
	bool button2_state;
	bool button3_state;
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
	void FAST printtextunderline(char*, int x, int y);
	void FAST printtextrect(char*, int x, int y, int w, int h);
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
};
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
};


//*********************************

// Note: MasterAnimation Postponed, until 2.0
// will come with a animation editor

