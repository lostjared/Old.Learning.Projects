/*


  MasterLibrary
	a collection of my librarys
	you can use this header file to access my functions whenever you need
	use

  #define MASTERX
   
	 to create a MASTERX application, with the MasterMain entry

  required librarys for linking proccess
  wsock32.lib dxguid.lib dsound.lib dinput.lib ddraw.lib
	 
  #define MASTERLIB

	to input the basic string , and aol/windows manipultion functions

  required librarys for linking proccess
  none

  written by jared bruni
  for educational purposes only
	www.lostsidedead.com

*/



#ifdef MASTERX
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

 

/********** MasterScreen Object ******************/

MasterScreen::~MasterScreen()
{
	if(lpBack)
	{
		lpBack->Release();
		lpBack = NULL;
	}

	if(lpFront)
	{
		lpFront->Release();
		lpFront = NULL;
	}

	if(lpDD)
	{
		lpDD->Release();
		lpDD = NULL;
	}
}

// ****************** MasterXHWND Object 

// Create and initilze MasterX
bool MasterXHWND::CreateMasterX(char* mytitle,int width, int height,DisplayColor color,WNDPROC proc,HINSTANCE hInst,HICON icon,HCURSOR cursor)
{

	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hInstance = hInst;
	wc.hIcon = icon;
	wc.hCursor = cursor;
	wc.lpfnWndProc = (WNDPROC) proc;
	wc.lpszClassName = mytitle;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	hwnd = CreateWindow(mytitle,mytitle,WS_POPUPWINDOW,0,0,width,height,0,0,hInst,0);

	if(hwnd == 0)
	{
		return false;
	}

	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);

	int bpp;


	switch(color)
	{
	case COLOR_DEFAULT:
    HDC hdc;
	// retrieves device-specific information about 
    // the specified device. 
	
    // Get the windows device context
	hdc = GetDC(NULL);
    // Get the number of adjacent color bits for each pixel.
    bpp = GetDeviceCaps(hdc, BITSPIXEL);
    // Release the Device Context
	ReleaseDC(NULL, hdc);
		break;

	case COLOR_8:
		bpp = 8;
		break;
	case COLOR_16:
		bpp = 16;
		break;
	case COLOR_24:
		bpp = 24;
		break;
	case COLOR_32:
		bpp = 32;
		break;
	}

	
	HRESULT ddrval;
	
	// create main dd object
	
	ddrval = DirectDrawCreate(NULL, &scr.lpDD,NULL);
	
	if(ddrval != DD_OK)
	{
		MessageBox(NULL,"Couldnt Create DirectX Object! Error: Terminating!","Error!!!",MB_ICONERROR);
		SendMessage(hwnd,WM_CLOSE,0,0);// Get outta here
	}
	
	ddrval = scr.lpDD->SetCooperativeLevel(hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT );
	

	
	if(ddrval != DD_OK)
	{
		scr.lpDD->Release();
		MessageBox(0,"Couldnt Set Cooperative Level, Fatal Error Aborting","Error",MB_ICONERROR);		
	}
	
	ddrval = scr.lpDD->SetDisplayMode(width,height,bpp);
	
	if(ddrval != DD_OK)
	{
		MessageBox(0,"Error Setting Display Mode",0,MB_ICONERROR);
		scr.lpDD->Release();
		return false;
		
	}
	
	if(setprimarysurface())
	{
		sound_ok = initSound();
	}
	else
	{
		MessageBox(0,"Couldnt Set Surfaces! Fatal Error! DirectX is jacked Man","Broken Software :(",MB_ICONERROR);
		return false;
	}

	initInput();
	text.init((MasterScreen*)&scr);
	paint.init(&scr);
	
	alive = true;

	return true;
}

// initilize Message Processing Loop
WPARAM MasterXHWND::InitLoop(void(* update)(MASTERSCREEN xscr))
{
	
	MSG msg;

	while(1)
    {
		
        int t = PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);
        if (t)
        {
            if (!GetMessage (& msg, NULL, 0, 0))
            return msg.wParam;
            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }
        
        else if (activeapp)// this is important here
		{	
			clear();
			update(mscr);
			mx_update();
		}
        else if (!activeapp)
		{
         WaitMessage();
		}
    }

	Destroy();
	return msg.wParam;
	
}

// release and destroy Objects 
void MasterXHWND::Destroy()
{
	// Kill Sound Handler
	// Kill Graphic Handler

	pKeyboard->Unacquire();
	pKeyboard->Release();
	pDI->Release();
	pDI = NULL;

	if(pDS)
	{
		pDS->Release();
	}

	
}
// Break the Loop and kill this Program
void MasterXHWND::Kill()
{
	alive = false;
	SendMessage(hwnd,WM_CLOSE,0,0);
}


// Get Current Screen
MASTERSCREEN MasterXHWND::GetScreen()
{
	return mscr;
}
// Set the Screen
void MasterXHWND::SetScreen(MASTERSCREEN xmscr)
{
	mscr = xmscr;
}

// Send a Message to the HWND current iniilized
LRESULT MasterXHWND::SendMasterMessage(UINT msg,WPARAM wParam,LPARAM lParam)
{

	return SendMessage(hwnd,msg,wParam,lParam);
}
// Master Clear Screen
void MasterXHWND::clear()
{
	ZeroMemory(&ddbltfx,sizeof(ddbltfx));
	ddbltfx.dwSize = sizeof(ddbltfx);
	ddbltfx.dwFillColor = 0;
	scr.lpBack->Blt(NULL,NULL,NULL,DDBLT_COLORFILL | DDBLT_WAIT,&ddbltfx);
}

// Manual MasterX Update (Buffer Flip)
void MasterXHWND::mx_update()
{
	
	HRESULT ddrval;
	ddrval = scr.lpFront->Flip(NULL, DDFLIP_WAIT);
	
	if(ddrval == DD_OK)
	{
	}
	else
	{
  	 scr.lpFront->Restore();
	}
}
// initilize Input
void MasterXHWND::initInput()
{
	DirectInputCreate(GetModuleHandle(NULL),DIRECTINPUT_VERSION,(struct IDirectInputA**)&pDI,NULL);

	pDI->CreateDevice(GUID_SysKeyboard,&pKeyboard,NULL);
	pKeyboard->SetDataFormat(&c_dfDIKeyboard);

	// Set the cooperative level 
	pKeyboard->SetCooperativeLevel(hwnd, 
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 
	pKeyboard->Acquire();
}

// set primary surfaces
bool MasterXHWND::setprimarysurface()
{
	
	DDSURFACEDESC ddsd;
	DDSCAPS ddscaps;
	HRESULT ddrval;
	
	memset(&ddsd,0,sizeof(ddsd)); // ok were filling out a surface description
	ddsd.dwSize = sizeof(ddsd); // then using createsurface
	// to attach it to the global surface
	ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
	ddsd.dwBackBufferCount = 1;
	
	ddrval = scr.lpDD->CreateSurface(&ddsd,&scr.lpFront,NULL);
	if(ddrval != DD_OK)
	{
        scr.lpDD->Release();
		return false;
	}
	
	// Set the description for backbuffer
	
	ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
	ddrval = scr.lpFront->GetAttachedSurface(&ddscaps, &scr.lpBack);
	if(ddrval != DD_OK)
	{
		
		scr.lpFront->Release();
		scr.lpDD->Release();
		return false;
	}
	
	return true;
}

// init sound
bool MasterXHWND::initSound()
{
	HRESULT h;
	
	h = DirectSoundCreate(NULL, &pDS, NULL);
	if (h != DS_OK)
		return FALSE;
	
	HWND hWnd = GetForegroundWindow();
	if (hWnd == NULL)
		hWnd = GetDesktopWindow();
	
	h = pDS->SetCooperativeLevel(hWnd, DSSCL_PRIORITY);
	if (h != DS_OK)
	{	pDS->Release();
	pDS = NULL;
	return FALSE;
	}
	
	IDirectSoundBuffer *lpDsb;
	DSBUFFERDESC		dsbdesc;
	
	memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	dsbdesc.dwBufferBytes = 0;
	dsbdesc.lpwfxFormat = NULL;
	
	if (pDS->CreateSoundBuffer(&dsbdesc, &lpDsb, NULL) != DS_OK)
	{	pDS->Release();
	pDS = NULL;
	return FALSE;
	}
	lpDsb->Play(0, 0, DSBPLAY_LOOPING);
	
	return TRUE;
}
// Load a Graphic 
bool MasterXHWND::LoadGraphic(MasterGraphic* g,char* filename)
{
	return g->LoadGraphic(filename,&scr);
}
// Load a Sound
bool MasterXHWND::LoadSound(MasterSound* s,LPCSTR resourceID)
{
	return s->LoadSound(pDS,resourceID);
}
// Check a keystate via DirectInput
bool MasterXHWND::KeyCheck(int key)
{
	BYTE	state[256];
	pKeyboard->GetDeviceState(sizeof(state), &state);

	if(state[key] & 0x80)
	{
		return true;
	}
	else
	{
		return false;
	}
}
// get mouse pos through windows api
void MasterXHWND::GetMousePosWin(long& x, long& y)
{
	POINT point;
	GetCursorPos(&point);
	x = point.x;
	y = point.y;
}

// Check a keystate via Windows
bool MasterXHWND::AsyncKeyCheck(int key)
{
  if(GetAsyncKeyState(key))
  {
	  return true;
  }
  else
  {
	  return false;
  }
}
// create a font, to use with the text object
HFONT MasterXHWND::CreateMasterFont(char* font_name,int size)
{
	// make a font
	return CreateFont(size,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,font_name);
}
// create timer by, id and interval
void MasterXHWND::InitTimer(int id, int interval)
{
	SetTimer(hwnd,id,interval,NULL);
}
// destroy the timer by id
void MasterXHWND::DestroyTimer(int id)
{
	KillTimer(hwnd,id);
}
// hide the cursor
void MasterXHWND::HideCursor()
{
	ShowCursor(false);
}
// show the cursor
void MasterXHWND::RestoreCursor()
{
	ShowCursor(true);
}
// has time changed?
bool MasterXHWND::TimeChange()
{
	if(pre_time == timer_count)
	{
	return false;
	}
	else
	{
		pre_time = timer_count;
		return true;
	}
}
// change the time
void MasterXHWND::ChangeTime()
{
	timer_count++;

	if(timer_count > 100)
	{
		timer_count = 0;
	}
}
// auto set time change
void MasterXHWND::SetTimeFlag()
{
	time_flag = TimeChange();
}
// insync update
bool MasterXHWND::SyncChange()
{
	return time_flag;
}


/***** Master Text Object *****************************************/
// set the default font back agian & shit
// set the default font
void MasterText::setdefaultfont()
{
	font = CreateFont(13,
        0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        "Arial");
}


//init master text object
void MasterText::init(MasterScreen* x)
{
	
	scr = (MasterScreen*)x;
	font = CreateFont(13,
        0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        "Arial"); //  Create a Stupid Font
	
	underfont = CreateFont(13,
        0, 0, 0, FW_NORMAL, FALSE, TRUE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        "Arial"); //  Create a Stupid Font
	
	bk = TRANSPARENT;
	text = RGB(255,0,0);
	
}
// set the font
void MasterText::setfont(HFONT f)
{
    font = f;
	
}
// set ud
void MasterText::setunderfont(HFONT f)
{
	underfont = f;
}
// set the bg color (RGB)
void MasterText::setbkcolor(COLORREF f)
{
	
	bk = f;
	
}
// set the textcolor
void MasterText::settextcolor(COLORREF f)
{
	
	text = f;
	
}
// print text
void FAST MasterText::printtext(char* strtext, int x, int y)
{
	
	HDC dc;
    scr->lpBack->GetDC(&dc);
	
	SetTextColor(dc,text);
	SetBkColor(dc,bk);
	
	if(font != NULL)
	{
		SelectObject(dc, font);
	}
	
	TextOut(dc,x,y,strtext,strlen(strtext));
	
	scr->lpBack->ReleaseDC(dc);
	
	
	
}
// print formated text within a rectangle
void FAST MasterText::printtextrect(char* strtext, int y, int x, int w, int h)
{
	RECT rt;
	SetRect(&rt,x,y,w,h);
	
	HDC dc;
    scr->lpBack->GetDC(&dc);
	
	SetTextColor(dc,text);
	SetBkColor(dc,bk);
	
	if(font != NULL)
	{
		SelectObject(dc, font);
	}
	
	DrawText(dc,strtext,strlen(strtext),&rt,DT_EDITCONTROL);
	
	scr->lpBack->ReleaseDC(dc);
	
	
	
}
// print text with a underline
void FAST MasterText::printtextunderline(char* strtext, int x, int y)
{
	HDC dc;
    scr->lpBack->GetDC(&dc);
	
	SetTextColor(dc,text);
	SetBkColor(dc,bk);
	
	if(underfont != NULL)
	{
		SelectObject(dc, underfont);
	}
	
	TextOut(dc,x,y,strtext,strlen(strtext));
	
	scr->lpBack->ReleaseDC(dc);
	
}


//************************************* GRAPHIC OBJECT ***************************************/

MasterGraphic::~MasterGraphic()
{
	if(surf)
	{
		surf->Release();
		surf = NULL;
	}
}

MasterGraphic::MasterGraphic()
{
	ckey = false;
	surf = NULL;
	scr  = NULL;
}
// Release a exisiting MasterX Graphic
void MasterGraphic::Release()
{
	if(surf)
	{
		surf->Release();
	}
}
// Display Graphic ex (display a area of the bitmap)
void MasterGraphic::DisplayGraphicEx(int bx, int by, int bw, int bh,int image_x, int image_y)
{
	HRESULT ddrval;
	RECT     rcRect;

	SetRect(&rcRect,bx,by,bw,bh);

	if(surf)
	{

	if(ckey)
	{
		ddrval= scr->lpBack->BltFast(image_x, image_y, surf,&rcRect, DDBLTFAST_SRCCOLORKEY);

		if(ddrval != DD_OK)
		{
			ReLoadGraphic();
		}
	}
	else
	{
		ddrval = scr->lpBack->BltFast(image_x,image_y,surf,&rcRect,DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
		if(ddrval != DD_OK)
		{
			ReLoadGraphic();
		}
	}
	}
}


// Display a exisiting MasterX Graphic
void MasterGraphic::DisplayGraphic(int x, int y)
{
	HRESULT ddrval;
	RECT     rcRect;

	SetRect(&rcRect,0,0,w,h);

	if(surf)
	{

	if(ckey)
	{
		ddrval= scr->lpBack->BltFast(x, y, surf,&rcRect, DDBLTFAST_SRCCOLORKEY);

		if(ddrval != DD_OK)
		{
			ReLoadGraphic();
		}
	}
	else
	{
		ddrval = scr->lpBack->BltFast(x,y,surf,&rcRect,DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
		if(ddrval != DD_OK)
		{
			ReLoadGraphic();
		}
	}
	}
}
// initilize the Screen Data structure
void MasterGraphic::init(MasterScreen* xscr)
{
	scr = xscr;
}
// Load MasterX Graphic
bool MasterGraphic::LoadGraphic(char* filenamex, MasterScreen* scrx)
{
	scr = scrx;
	strcpy(filename,filenamex);
	return LoadGraphic(filename);
}
// Reload the Graphic when Destroyed
void MasterGraphic::ReLoadGraphic()
{
	DDReLoadBitmap(surf,filename);
}
// Load the Graphic, if you already initilized a screen
bool MasterGraphic::LoadGraphic(char* filenamex)
{
	strcpy(filename,filenamex);
	if(scr != NULL)
	{
		surf = DDLoadBitmap(scr->lpDD,filename);
		if(surf) 
		{
			w = MXWIDTH; // from static global
	    	h = MXHEIGHT; // from static global

		return true;

		}
		else
		{
			return false;
		}
	} else
	{
		return false;// no screen initilized
	}
}
// Set a Color key to this graphic
void MasterGraphic::SetColorKey(COLORREF r)
{
	if(surf)
	{

	DDSetColorKey(surf,r);
	ckey = true;
	
	}
}

/***************************** THE PAITNING OBJECT ******************************************/
// initlize the MasterPaint
void MasterPaint::init(MasterScreen* xscr)
{
	scr = xscr;
}
// set a pixel
void FAST MasterPaint::mxsetpixel(int x, int y, COLORREF rgbval)
{
	HDC dc;
	scr->lpBack->GetDC(&dc);
	SetPixel(dc, x, y, rgbval);  
	scr->lpBack->ReleaseDC(dc);
}

// get the color of a pixel
COLORREF FAST MasterPaint::mxgetpixel(int x, int y)
{
	COLORREF rgbval;
	HDC dc;
	scr->lpBack->GetDC(&dc);
	rgbval = GetPixel(dc, x, y);     // Save current pixel value
	scr->lpBack->ReleaseDC(dc);
	return rgbval;
}

// draw an arc
void FAST MasterPaint::mxarc(int x1, int x2, int x3, int x4,int x5, int x6,int x7, int x8,COLORREF fill,COLORREF outline)
{
	
	HDC dc;
	scr->lpBack->GetDC(&dc);
	
	   HBRUSH hNewBrush,hOldBrush;
	   HPEN hNewPen,hOldPen; 
	   
	   hNewBrush = (HBRUSH)CreateSolidBrush(fill);
	   hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush); // set this brush and get the old brush
	   
	   hNewPen = CreatePen(PS_SOLID,2,outline); // create this pen
	   hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); // set this pen and  get the old one
	   
	   Arc(dc,x1,x2,x3,x4,x5,x6,x7,x8);
	   
	   SelectObject(dc,hOldPen);
	   SelectObject(dc,hOldBrush);
	   
	   DeleteObject(hNewBrush); 
	   DeleteObject(hNewPen); 
	   scr->lpBack->ReleaseDC(dc);
}

// draw a line
void FAST MasterPaint::mxlineto(int x, int y,COLORREF fill,COLORREF outline)
{
	
	HDC dc;
	scr->lpBack->GetDC(&dc);
	
    HBRUSH hNewBrush,hOldBrush;
    HPEN hNewPen,hOldPen; 
	   
    hNewBrush = (HBRUSH)CreateSolidBrush(fill);
    hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush); // set this brush and get the old brush
	   
    hNewPen = CreatePen(PS_SOLID,2,outline); // create this pen
    hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); // set this pen and  get the old one
	   
	LineTo(dc,x,y);
	   
	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);
	  
	DeleteObject(hNewBrush); 
	DeleteObject(hNewPen); 
	scr->lpBack->ReleaseDC(dc);
}

// draw a angle arc
void FAST MasterPaint::mxanglearc(int x, int y, long radius, float startangle,float sweepangle,COLORREF outline)
{
	HDC dc;
	scr->lpBack->GetDC(&dc);
	
    HBRUSH hNewBrush,hOldBrush;
    HPEN hNewPen,hOldPen; 
	COLORREF fill = RGB(0,0,0); // null colored brush
    hNewBrush = (HBRUSH)CreateSolidBrush(fill);
    hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush); // set this brush and get the old brush
	   
    hNewPen = CreatePen(PS_SOLID,2,outline); // create this pen
    hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); // set this pen and  get the old one
	   
	AngleArc(dc,x,y,radius,startangle,sweepangle);
	   
	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);
	  
	DeleteObject(hNewBrush); 
	DeleteObject(hNewPen); 
	scr->lpBack->ReleaseDC(dc);
}

// draw a polygon
void FAST MasterPaint::mxpolygon(CONST POINT* point,int n_points,COLORREF fill,COLORREF outline)
{
	HDC dc;
	scr->lpBack->GetDC(&dc);
	
	   HBRUSH hNewBrush,hOldBrush;
	   HPEN hNewPen,hOldPen; 
	   
	   hNewBrush = (HBRUSH)CreateSolidBrush(fill);
	   hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush); // set this brush and get the old brush
	   
	   hNewPen = CreatePen(PS_SOLID,2,outline); // create this pen
	   hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); // set this pen and  get the old one
	   
	   Polygon(dc,point,n_points);
	   
	   SelectObject(dc,hOldPen);
	   SelectObject(dc,hOldBrush);
	   
	   DeleteObject(hNewBrush); 
	   DeleteObject(hNewPen); 
	   scr->lpBack->ReleaseDC(dc);
}


// Draw a Rectangle
void FAST MasterPaint::mxdrawrect(int x, int y, int xx, int yy, COLORREF fill, COLORREF outline)
{
	HDC dc;
	scr->lpBack->GetDC(&dc);
	
	   HBRUSH hNewBrush,hOldBrush;
	   HPEN hNewPen,hOldPen; 
	   
	   hNewBrush = (HBRUSH)CreateSolidBrush(fill);
	   hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush); // set this brush and get the old brush
	   
	   hNewPen = CreatePen(PS_SOLID,2,outline); // create this pen
	   hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); // set this pen and  get the old one
	   
	   Rectangle(dc,x,y,xx,yy); // Draw a rectangle
	   
	   SelectObject(dc,hOldPen);
	   SelectObject(dc,hOldBrush);
	   
	   DeleteObject(hNewBrush); 
	   DeleteObject(hNewPen); 
	   scr->lpBack->ReleaseDC(dc);
}
// Draw a rectangle
void FAST MasterPaint::mxdrawroundrect(int x, int y, int x2, int y2, int cw, int ch, COLORREF fill,COLORREF outline)
{
	HDC dc;
	scr->lpBack->GetDC(&dc);
	
	HBRUSH hNewBrush,hOldBrush;// new Brush to paint with and one thats current (so we can restore)
	   HPEN hNewPen,hOldPen; // New pen to paint with and the current (so we can restore)
	   
	   hNewBrush = (HBRUSH)CreateSolidBrush(fill); // create this brush
	   hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush); // set this brush and get the old brush
	   
	   hNewPen = CreatePen(PS_SOLID,2,outline); // create this pen
	   hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); // set this pen and  get the old one
	   
	   
	   RoundRect(dc,x,y,x2,y2,cw,ch);
	   
	   
	   SelectObject(dc,hOldPen);
	   SelectObject(dc,hOldBrush);
	   
	   DeleteObject(hNewBrush);
	   DeleteObject(hNewPen); // i dont need this sso lets KILL It
	   scr->lpBack->ReleaseDC(dc);
}
// draw a circle (pie)
void FAST MasterPaint::mxdrawpie(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2, COLORREF fill,COLORREF outline)
{
	HDC dc;
	scr->lpBack->GetDC(&dc);
	
	HBRUSH hNewBrush,hOldBrush;// new Brush to paint with and one thats current (so we can restore)
	   HPEN hNewPen,hOldPen; // New pen to paint with and the current (so we can restore)
	   
	   hNewBrush = (HBRUSH)CreateSolidBrush(fill); // create this brush
	   hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush); // set this brush and get the old brush
	   
	   hNewPen = CreatePen(PS_SOLID,2,outline); // create this pen
	   hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); // set this pen and  get the old one
	   
	   
	   Pie(dc,x,y,x2,y2,nx,ny,nx2,ny2);
	   
	   SelectObject(dc,hOldPen);
	   SelectObject(dc,hOldBrush);
	   
	   DeleteObject(hNewBrush); 
	   DeleteObject(hNewPen); 
	   scr->lpBack->ReleaseDC(dc);
}
// draw chord
void FAST MasterPaint::mxdrawchord(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2,COLORREF fill,COLORREF outline)
{
	   HDC dc;
	   scr->lpBack->GetDC(&dc);
	   
       HBRUSH hNewBrush,hOldBrush;// new Brush to paint with and one thats current (so we can restore)
	   HPEN hNewPen,hOldPen; // New pen to paint with and the current (so we can restore)
	   
	   hNewBrush = (HBRUSH)CreateSolidBrush(fill); // create this brush
	   hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush); // set this brush and get the old brush
	   
	   hNewPen = CreatePen(PS_SOLID,2,outline); // create this pen
	   hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); // set this pen and  get the old one
	   
	   Chord(dc,x,y,x2,y2,nx,ny,nx2,ny2);
	   
	   SelectObject(dc,hOldPen);
	   SelectObject(dc,hOldBrush);
	   
	   DeleteObject(hNewBrush); 
	   DeleteObject(hNewPen);
	   scr->lpBack->ReleaseDC(dc);
}
// draw ellipse
void FAST MasterPaint::mxdrawellipse(int x, int y, int x2, int y2,COLORREF fill,COLORREF outline)
{
	   HDC dc;
	   scr->lpBack->GetDC(&dc);
	   
       HBRUSH hNewBrush,hOldBrush;// new Brush to paint with and one thats current (so we can restore)
	   HPEN hNewPen,hOldPen; // New pen to paint with and the current (so we can restore)
	   
	   hNewBrush = (HBRUSH)CreateSolidBrush(fill); // create this brush
	   hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush); // set this brush and get the old brush
	   
	   hNewPen = CreatePen(PS_SOLID,2,outline); // create this pen
	   hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); // set this pen and  get the old one
	   
	   Ellipse(dc,x,y,x2,y2);
	   
	   
	   
	   SelectObject(dc,hOldPen);
	   SelectObject(dc,hOldBrush);
	   
	   DeleteObject(hNewBrush); 
	   DeleteObject(hNewPen); 
	   scr->lpBack->ReleaseDC(dc);
}

//*********************** MASTER SOUND OBJECT ***********************************************/

MasterSound::MasterSound()
{
	pSound = NULL;
}

MasterSound::~MasterSound()
{
	if(sound_ok)
	{

	if(pSound)
	{
		pSound->Release();
	}

	}
}

// Load a Sound
bool MasterSound::LoadSound(IDirectSound *pds,LPCSTR name)
{
	if(sound_ok)
	{


	pSound = DSLoadSoundBuffer(pds,name);

	if(pSound)
	{
		return true;
	}
	else
	{
		return false;
	}

	}

	return false;
}
// Play the Sound
void MasterSound::Play()
{
	if(sound_ok)
	{


	if(pSound)
	{
		pSound->Play(0,0,0);
	}

	}
}
// Play status of Sound (is it Playing?)
bool MasterSound::PlayStatus()
{
	if(sound_ok) {
   DWORD status;
   pSound->GetStatus(&status);

	  if(status & DSBSTATUS_PLAYING)
	  { 
		  return true;
	  } 
	  else 
	  {
		  return false;
	  }
		
	  return false;

	}

	else {


		return false;
	}
}

void MasterSound::Release()
{
	if(pSound)
	{
		pSound->Release();
	}
}


//************** NON CLASS RELATED FUNCTION **************************************************/
// DirectDraw Load Bitmap (to surface)
IDirectDrawSurface* DDLoadBitmap(IDirectDraw* pdd, LPCSTR szBitmap)
{
	 
	HBITMAP hbm;
	BITMAP bm;
	IDirectDrawSurface *pdds;
	
	// Load Image for loading from Disk
	
	hbm = (HBITMAP)LoadImage(NULL, szBitmap, IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	
	
	
	if(hbm == NULL) { return NULL; }
	
	GetObject(hbm, sizeof(bm), &bm); // size
	
	
	// Create Surface for this Bitmap
	
	int cw = bm.bmWidth;
	int ch = bm.bmHeight;

	MXWIDTH = cw;
	MXHEIGHT = ch;

	
	pdds = CreateOffScreenSurface(pdd, bm.bmWidth,bm.bmHeight);
	
	if(pdds)
	{
		
		DDCopyBitmap(pdds, hbm, bm.bmWidth,bm.bmHeight);
	}
	
	
	DeleteObject(hbm);
	
	return pdds;
	
}

mxbitmap DDLoadBitmapX(IDirectDraw* pdd, LPCSTR szBitmap)
{
	
	HBITMAP hbm;
	BITMAP bm;
	IDirectDrawSurface *pdds;
	
	// Load Image for loading from Disk
	
	hbm = (HBITMAP)LoadImage(NULL, szBitmap, IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	
	mxbitmap xbm;
	

	
	if(hbm == NULL) { xbm.surf = NULL; return xbm; }
	
	GetObject(hbm, sizeof(bm), &bm); // size
	
	
	// Create Surface for this Bitmap
	
	int cw = bm.bmWidth;
	int ch = bm.bmHeight;
	
	pdds = CreateOffScreenSurface(pdd, bm.bmWidth,bm.bmHeight);
	
	if(pdds)
	{
		
		DDCopyBitmap(pdds, hbm, bm.bmWidth,bm.bmHeight);
	}
	
	
	DeleteObject(hbm);
	
	xbm.surf = pdds;
	xbm.w = cw;
	xbm.h = ch;

	return xbm;
	
}
// this is a surface when can be cliped 
IDirectDrawSurface* CreateOffScreenSurface(IDirectDraw* pdd, int dx, int dy)
{
	
	DDSURFACEDESC ddsd;
	IDirectDrawSurface* pdds;
	
	// Create Surface for this bitmap
	
	ZeroMemory(&ddsd,sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwWidth = dx;
	ddsd.dwHeight = dy;
	
	if(pdd->CreateSurface(&ddsd, &pdds,NULL) != DD_OK)
	{
		return NULL;
		
	} else {
		
		return pdds;
		
	}
	
}
// Copy Bitmap
HRESULT DDCopyBitmap(IDirectDrawSurface* pdds, HBITMAP hbm, int dx, int dy)
{
	
	HDC hdcImage;
	HDC hdc;
	HRESULT hr;
	HBITMAP hbmOld;
	
	// Select Bitmap into a MemoryDC 
	
	hdcImage = CreateCompatibleDC(NULL);
	hbmOld = (HBITMAP)SelectObject(hdcImage, hbm);
	
	if((hr = pdds->GetDC(&hdc)) == DD_OK)
	{
		
		BitBlt(hdc,0,0,dx,dy,hdcImage,0,0,SRCCOPY);
		pdds->ReleaseDC(hdc);
	}
	
	SelectObject(hdcImage, hbmOld);
	DeleteDC(hdcImage);
	
	return hr;
	
}

// Wav Data
static const TCHAR c_szWAV[] = {"WAVE"};

///////////////////////////////////////////////////////////////////////////////
//
// DSLoadSoundBuffer
//
///////////////////////////////////////////////////////////////////////////////

IDirectSoundBuffer *DSLoadSoundBuffer(IDirectSound *pDS, LPCTSTR lpName)
{
	IDirectSoundBuffer *pDSB = NULL;
	DSBUFFERDESC dsBD = {0};
	BYTE *pbWaveData;
	
	if (DSGetWaveResource(NULL, lpName, &dsBD.lpwfxFormat, &pbWaveData, &dsBD.dwBufferBytes))
	{
		dsBD.dwSize = sizeof(dsBD);
		dsBD.dwFlags = DSBCAPS_STATIC | DSBCAPS_GETCURRENTPOSITION2;
		
		if (SUCCEEDED(pDS->CreateSoundBuffer(&dsBD, &pDSB, NULL)))
		{
			if (!DSFillSoundBuffer(pDSB, pbWaveData, dsBD.dwBufferBytes))
			{
				pDSB->Release();
				pDSB = NULL;
			}
		}
		else
		{
			pDSB = NULL;
		}
	}
	
	return pDSB;
}

///////////////////////////////////////////////////////////////////////////////
//
// DSReloadSoundBuffer
//
///////////////////////////////////////////////////////////////////////////////

BOOL DSReloadSoundBuffer(IDirectSoundBuffer *pDSB, LPCTSTR lpName)
{
	BOOL result=FALSE;
	BYTE *pbWaveData;
	DWORD cbWaveSize;
	
	if (DSGetWaveResource(NULL, lpName, NULL, &pbWaveData, &cbWaveSize))
	{
		if (SUCCEEDED(pDSB->Restore()) &&
			DSFillSoundBuffer(pDSB, pbWaveData, cbWaveSize))
		{
			result = TRUE;
		}
	}
	
	return result;
}

///////////////////////////////////////////////////////////////////////////////
//
// DSGetWaveResource
//
///////////////////////////////////////////////////////////////////////////////

BOOL DSGetWaveResource(HMODULE hModule, LPCTSTR lpName,
					   WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData, DWORD *pcbWaveSize)
{
	HRSRC hResInfo;
	HGLOBAL hResData;
	void *pvRes;
	
	if (((hResInfo = FindResource(hModule, lpName, c_szWAV)) != NULL) &&
		((hResData = LoadResource(hModule, hResInfo)) != NULL) &&
		((pvRes = LockResource(hResData)) != NULL) &&
		DSParseWaveResource(pvRes, ppWaveHeader, ppbWaveData, pcbWaveSize))
	{
		return TRUE;
	}
	
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

BOOL DSFillSoundBuffer(IDirectSoundBuffer *pDSB, BYTE *pbWaveData, DWORD cbWaveSize)
{
	if (pDSB && pbWaveData && cbWaveSize)
	{
		LPVOID pMem1, pMem2;
		DWORD dwSize1, dwSize2;
		
		if (SUCCEEDED(pDSB->Lock(0, cbWaveSize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0)))
		{
			CopyMemory(pMem1, pbWaveData, dwSize1);
			
			if ( 0 != dwSize2 )
				CopyMemory(pMem2, pbWaveData+dwSize1, dwSize2);
			
			pDSB->Unlock(pMem1, dwSize1, pMem2, dwSize2);
			return TRUE;
		}
	}
	
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

BOOL DSParseWaveResource(void *pvRes, WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData,DWORD *pcbWaveSize)
{
	DWORD *pdw;
	DWORD *pdwEnd;
	DWORD dwRiff;
	DWORD dwType;
	DWORD dwLength;
	
	if (ppWaveHeader)
		*ppWaveHeader = NULL;
	
	if (ppbWaveData)
		*ppbWaveData = NULL;
	
	if (pcbWaveSize)
		*pcbWaveSize = 0;
	
	pdw = (DWORD *)pvRes;
	dwRiff = *pdw++;
	dwLength = *pdw++;
	dwType = *pdw++;
	
	if (dwRiff != mmioFOURCC('R', 'I', 'F', 'F'))
		goto exit;		// not even RIFF
	
	if (dwType != mmioFOURCC('W', 'A', 'V', 'E'))
		goto exit;		// not a WAV
	
	pdwEnd = (DWORD *)((BYTE *)pdw + dwLength-4);
	
	while (pdw < pdwEnd)
	{
		dwType = *pdw++;
		dwLength = *pdw++;
		
		switch (dwType)
		{
		case mmioFOURCC('f', 'm', 't', ' '):
			if (ppWaveHeader && !*ppWaveHeader)
			{
				if (dwLength < sizeof(WAVEFORMAT))
					goto exit;		// not a WAV
				
				*ppWaveHeader = (WAVEFORMATEX *)pdw;
				
				if ((!ppbWaveData || *ppbWaveData) &&
					(!pcbWaveSize || *pcbWaveSize))
				{
					return TRUE;
				}
			}
			break;
			
		case mmioFOURCC('d', 'a', 't', 'a'):
			if ((ppbWaveData && !*ppbWaveData) ||
				(pcbWaveSize && !*pcbWaveSize))
			{
				if (ppbWaveData)
					*ppbWaveData = (LPBYTE)pdw;
				
				if (pcbWaveSize)
					*pcbWaveSize = dwLength;
				
				if (!ppWaveHeader || *ppWaveHeader)
					return TRUE;
			}
			break;
		}
		
		pdw = (DWORD *)((BYTE *)pdw + ((dwLength+1)&~1));
	}
	
exit:
	return FALSE;
}

HRESULT
DDSetColorKey(IDirectDrawSurface * pdds, COLORREF rgb)
{
    DDCOLORKEY              ddck;
	
    ddck.dwColorSpaceLowValue = DDColorMatch(pdds, rgb);
    ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;
    return pdds->SetColorKey(DDCKEY_SRCBLT, &ddck);
}


DWORD
DDColorMatch(IDirectDrawSurface * pdds, COLORREF rgb)
{
    COLORREF                rgbT;
    HDC                     hdc;
    DWORD                   dw = CLR_INVALID;
    DDSURFACEDESC          ddsd;
    HRESULT                 hres;
	
    //
    //  Use GDI SetPixel to color match for us
    //
    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
        rgbT = GetPixel(hdc, 0, 0);     // Save current pixel value
        SetPixel(hdc, 0, 0, rgb);       // Set our value
        pdds->ReleaseDC(hdc);
    }
    //
    // Now lock the surface so we can read back the converted color
    //
    ddsd.dwSize = sizeof(ddsd);
    while ((hres = pdds->Lock(NULL, &ddsd, 0, NULL)) == DDERR_WASSTILLDRAWING)
        ;
    if (hres == DD_OK)
    {
        dw = *(DWORD *) ddsd.lpSurface;                 // Get DWORD
        if (ddsd.ddpfPixelFormat.dwRGBBitCount < 32)
            dw &= (1 << ddsd.ddpfPixelFormat.dwRGBBitCount) - 1;  // Mask it to bpp
        pdds->Unlock(NULL);
    }
    //
    //  Now put the color that was there back.
    //
    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
        SetPixel(hdc, 0, 0, rgbT);
        pdds->ReleaseDC(hdc);
    }
    return dw;
}

HRESULT
DDReLoadBitmap(IDirectDrawSurface * pdds, LPCSTR szBitmap)
{
    HBITMAP                 hbm;
    HRESULT                 hr;

    //
    //  Try to load the bitmap as a resource, if that fails, try it as a file
    //
    hbm = (HBITMAP) LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, 0,
                              0, LR_CREATEDIBSECTION);
    if (hbm == NULL)
        hbm = (HBITMAP) LoadImage(NULL, szBitmap, IMAGE_BITMAP, 0, 0,
                                  LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if (hbm == NULL)
    {
        OutputDebugString("handle is null\n");
        return E_FAIL;
    }

	hr = DDCopyBitmap2(pdds, hbm, 0, 0, 0, 0);

   
	if (hr != DD_OK)
    {
        OutputDebugString("ddcopybitmap failed\n");
    }
    DeleteObject(hbm);
    return hr;
}

HRESULT
DDCopyBitmap2(IDirectDrawSurface * pdds, HBITMAP hbm, int x, int y,
             int dx, int dy)
{
    HDC                     hdcImage;
    HDC                     hdc;
    BITMAP                  bm;
    DDSURFACEDESC          ddsd;
    HRESULT                 hr;

    if (hbm == NULL || pdds == NULL)
        return E_FAIL;
    //
    // Make sure this surface is restored.
    //
    pdds->Restore();
    //
    // Select bitmap into a memoryDC so we can use it.
    //
    hdcImage = CreateCompatibleDC(NULL);
    if (!hdcImage)
        OutputDebugString("createcompatible dc failed\n");
    SelectObject(hdcImage, hbm);
    //
    // Get size of the bitmap
    //
    GetObject(hbm, sizeof(bm), &bm);
    dx = dx == 0 ? bm.bmWidth : dx;     // Use the passed size, unless zero
    dy = dy == 0 ? bm.bmHeight : dy;
    //
    // Get size of surface.
    //
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
    pdds->GetSurfaceDesc(&ddsd);

    if ((hr = pdds->GetDC(&hdc)) == DD_OK)
    {
        StretchBlt(hdc, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcImage, x, y,
                   dx, dy, SRCCOPY);
        pdds->ReleaseDC(hdc);
    }
    DeleteDC(hdcImage);
    return hr;
}

// ****** misc

HFONT MakeFont(char* ftype, int size)
{
	return CreateFont(size,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,ftype);
}

//*********

// ************************************* MASTERSOCKET

// initilze windows sockets
void initwinsock()
{
	
WORD wVersionRequested;
WSADATA wsaData;
int err;

wVersionRequested = MAKEWORD( 1, 1 );

err = WSAStartup( wVersionRequested, &wsaData );
if ( err != 0 ) {
 	MessageBox(0,"Error Couldnt Init Winsock!","Aborting",MB_ICONINFORMATION);
	PostQuitMessage(0);
    return;
}


if ( LOBYTE( wsaData.wVersion ) != 1 ||
         HIBYTE( wsaData.wVersion ) != 1 ) {
    WSACleanup( );
    return;   

}
}

// killwinsock, on lcose
void killwinsock()
{
	WSACleanup();
}

// the master socket data structure
void MasterSocket::CreateSocket(HWND hwndx, UINT SOCKET_IDx)
{
	hwnd = hwndx;
	SOCKET_ID = SOCKET_IDx;
	socketx = socket(AF_INET,SOCK_STREAM,0);
	WSAAsyncSelect(socketx,hwnd,SOCKET_ID,FD_CONNECT|FD_READ|FD_CLOSE|FD_ACCEPT);
}

// begin listening
void MasterSocket::Listen(UINT port)
{
	if(port == DEFAULT_PORT) { port = 7; }
     struct sockaddr_in addy;
	// begin watching on port 7
  	addy.sin_family = AF_INET;
	addy.sin_port = htons(port);
	addy.sin_addr.s_addr = INADDR_ANY; //inet_addr("172.129.243.252");
   	bind(socketx,(struct sockaddr*)&addy,sizeof(addy));
	listen(socketx,5);
}
// connect to a remote socket
void MasterSocket::Connect(char* ipaddress,UINT port)
{
	struct sockaddr_in addy2;
	if(port == DEFAULT_PORT) { port = 7; }

	addy2.sin_family = AF_INET;
	addy2.sin_port = htons(port);
	addy2.sin_addr.s_addr = inet_addr(ipaddress);
	connect(socketx,(struct sockaddr*)&addy2,sizeof(addy2));
}
// accept a request from remote socket
void MasterSocket::Accept()
{
	struct sockaddr cli_addr;
    int clilen;
	clilen = sizeof(cli_addr);
	socketx = accept(socketx,(struct sockaddr*)&cli_addr,&clilen);
}

// send data once socket is connected
void MasterSocket::Send(char* buff, int len)
{
	send(socketx,buff,len,0);
}
// recive data from a connected socket
int MasterSocket::Recive(char* buff,int len)
{
	return recv(socketx,buff,len,0);
}
// get the ID of a given socket, for the wndproc callback
const UINT MasterSocket::GetID()
{
	return (const UINT)SOCKET_ID;
}
// close an open socket
void MasterSocket::Close()
{
	closesocket(socketx);
}

//**********************************************************************************


// ENTRY
int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR l,int CmdShow)
{
	return MasterMain(hInst,l);
}

#endif

#ifdef MASTERLIB

#include <windows.h>
#include <string.h>
#include <fstream.h>
#include <iostream.h>
#include <ctime>

// enumerated constants 

enum AOLVER { NOAOL = 0, AOL2, AOL3, AOL4, AOL5, AOL6 };
enum AOLTYPE {ICON, LISTBOX, TREE, VIEW, RICHCNTL, STATIC,GLYPH, IMAGE, CHECKBOX};

// Important Functions
void cppDoEvents();
HWND FindWindowLike_Class(HWND Parent, char* Class); // Just Class
HWND FindWindowLike_Title(HWND Parent, char* Title); // Just Title
#define NOTFOUND -1
#define INULL    -1
#define NOPREV   -1
#define NULLI    -1
#define STRBEGIN -1
#define MRANGE_HI 1
#define MRANGE_LO 0
#define NULLPOS  -1

// string algorithims
void stringcopy(char* dest,char* from); // string copy
void stringattach(char* dest,char* from); // string attach
void leftcopy(char* from,char* dest,int pos);// left copy (leftstr)
void rightcopy(char* from,char* dest,int pos);// right copy (rightstr)
void midcopy(char* from,char* dest,int start_pos,int stop_pos);// middle copy (midstr)
void trimspace(char* buff);// trim space characters
int findstr(char* buffer,char* search);// find string search
int ifindstr(int i,char* buffer,char* search);// find string search from position
int findstrb(char* buffer,char* search); // backwards search
int ifindstrb(int i,char* buffer,char* search); // inside backwards search
int fsearchstr(int start,int stop,char* buff,char* search);// fully controled range search (forward)
int bsearchstr(int start,int stop,char* buff,char* search);// fully controled range search (backward)
void removestr(char* buff,char* str);// remove instances of str in buff
int getlen(char* buff);// get length of the string
void lcase(char* buff);// lower case string
void ucase(char* buff);// upper case string
int  lcasel(int c);// lower case letter
int  ucasel(int c);// upper case letter
int  findoccurance(char* buff,char* search);// find occourances of a specific string
void convertinteger(int integer,char* buff,int base); // convert integer to string
int  convertstring(char* buff); // convert string to integer
bool ishexc(char c);// is this character a hexidecimal digit?
bool ishex(char* buff);// is this string a hexidecimal value?
int  hextointc(char c);// hexidecimal digit to integer value
int  hextoint(char* buff); // hexidecimal digits to integer value
int findoccourance(char* buff,char* search);// find the numeric of times a string occours
void tripcharup(char* buff,int upby);// bump the digits up X times
void tripchardown(char* buff,int downby);// dump the digits down  X times
void replacechar(char* string,char findchr,char replace);// replace single character, through out all instances
void replacestr(char* string,char* findstr,char* rep,char* output);// replace string inside string
void rmvinst(char* buff,char* findstr,char* replace,char* output); // remove single instance of string
char randomchar(int max);// produce a random character
char randomchar(int max,int up);// produce a random character, and then make it + up
void randomstr(char* buff,int char_max,int char_size);// random string
void removechar(char* input,char* output,char c); // remove characters from buffer
int  findchar(char* str,char c);// find single char (forward)
int  ifindchar(int start,char* str,char c); // inside find single char (forward)
int  findcharb(char* str,char c);// find single char (backward)
int  ifindcharb(int start,char* str,char c); // find single char backward ex
int  findcharcf(char* str,int start,int stop,char c);// find single char controled forward
int  findcharcb(char* str,int start,int stop,char c);// find single char controled backward
void removestr(char* input,char* output,char* string); // remove instance of string
void rmvstrx(char* buff,char* output,char* string); // remove single instance of string
void strsavefile(char* filename,char* string);// save the string as a text file
int  getfilestringlength(char* filename);// get the string length of a text file
bool strloadfile(char* filename,char* output);// load a string from a text file
void reversestring(char* input,char* output); // reverse sring
bool isstrvalid(char* string); // checks to see if the string is valid or not (is null terminated)
// string compares
bool mstrcmp(char* buff1,char* buff2); // case sensitive compare
bool mstrcmpx(char* buff1,char* buff2);// not case sensitive compare
bool insidestr(char* buff1,char* buff2); // am i inside this string?
bool insidestrx(char* buff1,char* buff2);// am i inside this string lowercased ?
void strsep(char* str, char* sleft, int go_left, char* sright, int go_right);// seperate into 2 seperate strings from 2 seperate points
void strsetnull(char* str,int pos); // reset the 0's position
void rmvnullset(char* str); // remove the 0 to end the string
int  getnullpos(char* str); // get the position of the null
void trimcom(char* buff, char* output, char startstr,char stopstr); 
void asmtrim(char* input,char* output);
int  countlines(char* buffer); // counts how many \n characters exisit
int  getfirstletter(char* buffer); // get first letter thats not a space

// static

static char g_sn[200];
static char g_msg[200];

// the structures


// api helper structure
struct APIHELP
{
	// Click a Window
	inline void Click(HWND hwnd)
	{
		SendMessage(hwnd,WM_LBUTTONDOWN,0,0);
		SendMessage(hwnd,WM_LBUTTONUP,0,0);
	}
	// Double Click a Window
	inline void DoubleClick(HWND hwnd)
	{
		SendMessage(hwnd,WM_LBUTTONDBLCLK,0,0);
	}
	// Send a KeyDown to a Window
	inline void KeyDown(HWND hwnd,char c)
	{
		SendMessage(hwnd,WM_KEYDOWN,c,0);
	}
	// Send a Key Up to a Window
	inline void KeyUp(HWND hwnd,char c)
	{
		SendMessage(hwnd,WM_KEYUP,c,0);
	}
	// Send a Key Press to a Window
	inline void KeyPress(HWND hwnd,char c)
	{
		KeyDown(hwnd,c);
		KeyUp(hwnd,c);
	}
	// Send a Close Message to a window
	inline void Close(HWND hwnd)
	{
		SendMessage(hwnd,WM_CLOSE,0,0);
	}
	// Send a SetText Message to a window
	inline void SetText(HWND hwnd,char* buff)
	{
		SendMessage(hwnd,WM_SETTEXT,strlen(buff),(LPARAM)(LPCSTR)buff);
	}
	// Send a GetText Message to a Window
	inline void GetText(HWND hwnd,char* buff)
	{
		int len;
		len = SendMessage(hwnd,WM_GETTEXTLENGTH,0,0);
		SendMessage(hwnd,WM_GETTEXT,len+1,(LPARAM)(LPCSTR)buff);
	}
	// Send a Get List Item message to a list box
	inline void GetListText(HWND hwnd,int index,char* buff)
	{
		SendMessage(hwnd,LB_GETTEXT,index,(LPARAM)(LPCSTR)buff);
	}
	// Send a Get list Count message
	inline int  GetListCount(HWND hwnd)
	{
		return SendMessage(hwnd,LB_GETCOUNT,0,0);
	}
	// Send a Get List Current Sel message
	inline int  GetListCurSel(HWND hwnd)
	{
		return SendMessage(hwnd,LB_GETCURSEL,0,0);
	}
	// Send a Get List Cur Sel Message
	inline void SetListCurSel(HWND hwnd, int x)
	{
		SendMessage(hwnd,LB_SETCURSEL,x,0);
	}
	// Send a Add Item to List Box Message
	inline void  AddList(HWND hwnd,char* buff)
	{
		SendMessage(hwnd,LB_ADDSTRING,strlen(buff),(LPARAM)(LPCSTR)buff);
	}
	// Send a Rmv Item From listBox Message
	inline void RmvList(HWND hwnd,int x)
	{
		SendMessage(hwnd,LB_DELETESTRING,x,0);
	}
	// pause the application (doesnt freeze) :)
	inline void Pause(double breaktime)
	{
		double wTime = time(NULL) + breaktime;
        while (time(NULL) <= wTime){ cppDoEvents(); }
	}
	// click a button
	inline void ButtonClick(HWND hwnd)
	{
     SendMessage(hwnd, WM_KEYDOWN, VK_SPACE, NULL);
     SendMessage(hwnd, WM_KEYUP, VK_SPACE, NULL);
	}
	// for this window to appear
	inline void WaitForWindow(char* window_class,char* window_title)
	{
		while(FindWindow(window_class,window_title) == 0)
		{
			cppDoEvents();
		}
	}
	// wait for this window to appear ex
	inline void WaitForWindowEx(HWND hwnd,HWND hwnd2,LPCSTR l1,LPCSTR l2)
	{
		while(FindWindowEx(hwnd,hwnd2,l1,l2) == 0)
		{
			cppDoEvents();
		}
	}
	// wait for a window like this to appear
	inline void WaitForWindowLike_Title(HWND parent,char* title)
	{
		while(FindWindowLike_Title(parent,title) == 0)
		{
			cppDoEvents();
		}
	}
	// wait for a window like this to appear
	inline void WaitForWindowLike_Class(HWND parent,char* winclass)
	{
		while(FindWindowLike_Class(parent,winclass) == 0)
		{
			cppDoEvents();
		}
	}
	// compare to windows, are they the same ?
	inline bool WindowCompare(HWND hwnd,HWND hwnd2)
	{
		if(hwnd == hwnd2)
		{
			return true;
		}

		return false;
	}
	// is this window handle valid?
	inline bool isValidHandle(HWND hwnd)
	{
		if(hwnd == 0)
		{
			return false;
		}

		return true;
	}
	// Show this window
	inline void ShowWin(HWND hwnd)
	{
		ShowWindow(hwnd,SW_SHOW);
	}
	// Hide this Window
	inline void HideWin(HWND hwnd)
	{
		ShowWindow(hwnd,SW_HIDE);
	}
	// Minimize this Window
	inline void MiniWin(HWND hwnd)
	{
		ShowWindow(hwnd,SW_MINIMIZE);
	}
	// Maximize this Window
	inline void MaxWin(HWND hwnd)
	{
		ShowWindow(hwnd,SW_MAXIMIZE);
	}
	// restore this window
	inline void RestoreWin(HWND hwnd)
	{
		ShowWindow(hwnd,SW_RESTORE);
	}
	// send a menu command
	inline void SendMenuCommand(HWND hwnd,int cmd)
	{
		
		SendMessage(hwnd,WM_COMMAND,cmd,NULL);
	}
};


// the AOLCPP base object
struct AOLCPPOBJ : APIHELP
{
	// Find AOL Window Handle
	inline HWND FindAOL()
	{
		return FindWindow("AOL Frame25",NULL);
	}
	// Find the AOL MDI Handle
	inline HWND FindMDI()
	{
		return FindWindowEx(FindAOL(),0,"MDIClient",NULL);
	}
	// Get the users Screen Name
	inline void GetScreenName(char* buff)
	{
		if(FindAOL() == 0)
		{
			strcpy(buff,"AOL Not Found");
			return;
		}

		HWND welw;
		welw = FindWindowLike_Title(FindMDI(),"Welcome,");

		if(welw == 0)
		{
			strcpy(buff,"Not signed On");
			return;
		}

		char temp[50];
		SendMessage(welw,WM_GETTEXT,50,(LPARAM)(LPCSTR)temp);
		int fc = findstr(temp,",");
		int fi = findstr(temp,"!");
		midcopy(temp,buff,fc+2,fi);
		
	}
	// Get The Version of AOL They are running
	inline AOLVER GetAOLVersion()
	{
		if(isAOLOpen() == false)
		{
			return NOAOL;
		}

		HMENU mnu = GetAOLMenu();
		HMENU msub = GetSubMenu(mnu,NULL);
		int subi;
		subi = GetMenuItemID(msub,8);

		char stritem[100];
		GetMenuString(msub, subi, stritem, 100, 1);
		if(findstr(stritem,"&Logging...") != -1)
		{
			return AOL2;
		}
		if(findstr(stritem,"P&ersonal Filing Cabinet") != -1)
		{
			return AOL3;
		}

		msub = GetSubMenu(mnu,4);
		subi = GetMenuItemID(msub,9);
        GetMenuString(msub, subi, stritem, 100, 1);

		if(findstr(stritem,"4.0") != -1)
		{
			return AOL4;
		}
		if(findstr(stritem,"5.0") != -1)
		{
			return AOL5;
		}

		msub = GetSubMenu(mnu,5);
		subi = GetMenuItemID(msub,8);
		GetMenuString(msub, subi, stritem, 100, 1);

		if(findstr(stritem,"6.0") != -1)
		{
			return AOL6;
		}
	
		return NOAOL;
	}
	// Find a AOL Child Window
	inline HWND FindAOLChild(char* title)
	{
		return FindWindowEx(FindMDI(),0,"AOL Child",title);
	}
	// Find A AOL Child Window Like
	inline HWND FindAOLChildLike(char* title)
	{
		return FindWindowLike_Title(FindMDI(),title);
	}
	// Get The AOL Menu Handle
	inline HMENU GetAOLMenu()
	{
		return GetMenu(FindAOL());
	}
	// Close AOL
	inline void CloseAOL()
	{
		Close(FindAOL());
	}
	// is the user signed on ?
	inline bool SignedOn()
	{
		if(FindWindowLike_Title(FindMDI(),"Welcome,") == 0)
		{
			return false;
		}
		return true;
	}
	// is the user signed off ?
	inline bool SignedOff()
	{
		if(FindWindowLike_Title(FindMDI(),"Goodbye from") == 0)
		{
			return false;
		}
		return true;
	}
	// is AOL Open?
	inline bool isAOLOpen()
	{
		if(FindAOL())
		{
			return true;
		}

		return false;
	}
	// close all the children 
	inline void CloseAllChildren()
	{
		while(1)
		{
			HWND win;
			win = FindWindowEx(FindMDI(),0,"AOL Child",0);
			if(win == 0)
			{
				break;
			}
			else
			{
				Close(win);
			}
			cppDoEvents();
		}
	}
	// kill all the modal windows 
	inline void KillModal()
	{
		if(FindWindow("_AOL_Modal",NULL))
		{
			while(1)
			{
				HWND f;
				f = FindWindow("_AOL_Modal",NULL);
				if(f == 0)
				{
					break;
				}
				Close(f);

				cppDoEvents();
			}
		}
	}
	// kill all aol message boxs
	inline void KillAOLMessage()
	{

		HWND mod;
		mod = FindWindow("#32770", "America Online");
		if(mod == 0)
		{
			return;
		}
		while(1)
		{
			mod = FindWindow("#32770", "America Online");
			if(mod == 0)
			{
				break;
			}
			Close(mod);
			cppDoEvents();
		}

	}
	// special search for AOL Child Windows 
	inline HWND GetAolWindow(HWND parent, AOLTYPE aolchild, int num)
	{
		if(parent == 0) { return 0; } // No Parent 
		int count = 1;
		if(num == 0) { return 0; }
		
		HWND win;
		win = GetWindow(GetWindow(parent, GW_CHILD), GW_HWNDFIRST);
		//.ICON, LISTBOX, TREE, VIEW, RICHCNTL, STATIC,GLYPH, IMAGE, CHECKBOXICON, LISTBOX, TREE, VIEW, RICHCNTL, STATIC,GLYPH, IMAGE, CHECKBOX
		char aolclass[50];
		
		switch(aolchild)
		{
		case ICON:
			strcpy(aolclass, "_AOL_Icon");
			break;
		case LISTBOX:
			strcpy(aolclass, "_AOL_Listbox");
			break;
		case TREE:
			strcpy(aolclass, "_AOL_Tree");
			break;
		case VIEW:
			strcpy(aolclass, "_AOL_View");
			break;
		case RICHCNTL:
			strcpy(aolclass, "RICHCNTL");
			break;
		case STATIC:
			strcpy(aolclass, "_AOL_Static");
			break;
		case GLYPH:
			strcpy(aolclass, "_AOL_Glyph");
			break;
		case IMAGE:
			strcpy(aolclass, "_AOL_Image");
			break;
		case CHECKBOX:
			strcpy(aolclass, "_AOL_Checkbox");
			break;
		}
		
		
		while(win != 0)
		{
			
			char buff[100];
			GetClassName(win,buff,100);
			if(strstr(buff,aolclass))
			{
				
				if(count == num) {
					return win; } else { count++; }
			}
			
			win = GetWindow(win, GW_HWNDNEXT);
			
		}
		
		
		return  0;
	}
    // up chat
	inline void UpChat()
	{
    HWND modal;
    modal = FindWindow("_AOL_Modal",NULL);
    char buff[255];
    SendMessage(modal,WM_GETTEXT,255,(LPARAM)(LPCSTR)buff);

    if((strstr(buff, "File")) || (strstr(buff, "Send")))
    {

        EnableWindow(FindWindow("AOL Frame25",NULL),1);
        ShowWindow(modal, SW_MINIMIZE);

    }

	}
    // un up chat
	inline void UnUpChat()
	{
		
    HWND modal;
    modal = FindWindow("_AOL_Modal",NULL);
    char buff[255];
    SendMessage(modal,WM_GETTEXT,255,(LPARAM)(LPCSTR)buff);

    if((strstr(buff, "File")) || (strstr(buff, "Send")))
    {

        EnableWindow(FindWindow("AOL Frame25",NULL),1);
        ShowWindow(modal, SW_RESTORE);

    }

	}

	// send a wm_command, to aitem in the aol menu by id
	inline void AOLMenuInvokeByID(int id)
	{
		SendMenuCommand(FindAOL(),id);
	}
    // run a item, off the AOL menu 
	inline void RunMenu(int menu_over,int menu_down)
	{
		HMENU aolmenu;
        aolmenu = GetAOLMenu();
		HMENU sub;
        sub = GetSubMenu(aolmenu, menu_over);
        int sub2;
        sub2 = GetMenuItemID(sub, menu_down);
        SendMessage(FindAOL(), WM_COMMAND, sub2,NULL);
	}
	// set aol's caption
	inline void SetAOLCaption(char* buffer)
	{
		SetText(FindAOL(),buffer);
	}
	// get aol's caption
	inline void GetAOLCaption(char* buffer)
	{
		GetText(FindAOL(),buffer);
	}
	// get the chat window (ethier 3.0 or 4.0)
	inline HWND GetChatWindow()
	{
		
		HWND win;
		win = GetWindow(GetWindow(FindMDI(), GW_CHILD), GW_HWNDFIRST);
		
		
		while(win != 0)
		{
			
			char buff[500];
			GetClassName(win, buff, 500);
			
			
			if(strstr(buff,"AOL Child"))
			{
				
				HWND list;
				HWND combo;
				HWND stat;
				HWND rich;
				HWND view;
				list = FindWindowEx(win,NULL, "_AOL_Listbox",NULL);
				combo = FindWindowEx(win,NULL, "_AOL_Combobox",NULL);
				stat = FindWindowEx(win,NULL, "_AOL_Static",NULL);
				rich = FindWindowEx(win,NULL, "RICHCNTL",NULL);
				view = FindWindowEx(win,NULL, "_AOL_View",NULL);
				if((list) && (combo) && (stat) && (rich))
				{
					
					return win;
				}
				if((list) && (stat) && (view)) { return win; }
			}
			
			win = GetWindow(win, GW_HWNDNEXT);
			
		}
		
		return 0;
		
	}
	// get the chat view (3.0 or 5.0)
	inline HWND GetChatView()
	{
		HWND Wnd;
		HWND chat;
		chat = GetChatWindow();
		Wnd  = FindWindowEx(chat,NULL, "_AOL_View",NULL);
		if(Wnd == 0) 
		{
			Wnd = FindWindowEx(chat,NULL, "RICHCNTL",NULL);
		}
		
		return Wnd;
	}
	// is user in a chat room?
	inline bool IsUserChatting()
	{
		if(GetChatWindow()) { return true; }

		return false;
	}

	// send text to ethier 3.0 or 4.0/5.0
	inline void SendText(char* str)
	{
		HWND chat;
		chat  =  GetChatWindow();
		HWND edit;
		HWND button;
		HWND rich;
		char text[300];
		char temp[300];
		char a[1] = "";
		edit = FindWindowEx(chat,NULL, "_AOL_Edit",NULL);
		button = GetNextWindow(edit, 2);
		
		if(edit == 0) 
		{
			//bad way of doing it
			/*edit = GetWindow(GetWindow(chat, GW_CHILD), GW_HWNDFIRST);
			
			  edit = GetNextWindow(edit, 2);
			  edit = GetNextWindow(edit, 2);
			  edit = GetNextWindow(edit, 2);
			  edit = GetNextWindow(edit, 2);
			  edit = GetNextWindow(edit, 2);
			  edit = GetNextWindow(edit, 2);
			  edit = GetNextWindow(edit, 2);
			edit = GetNextWindow(edit, 2);*/
			
			//good way	   
			rich = GetAolWindow(GetChatWindow(), RICHCNTL,2); 
			button = GetNextWindow(rich,2);
		}
		SendMessage(rich, WM_GETTEXT,300,(LPARAM)(LPCSTR) temp);
		SendMessage(rich, WM_SETTEXT,1, (LPARAM)(LPCSTR) a);
		SendMessage(rich, WM_SETTEXT,300, (LPARAM)(LPCSTR) str);
		SendMessage(rich, WM_CHAR ,  13, 0);
		
		SendMessage(rich, WM_GETTEXT,300,(LPARAM)(LPCSTR) text);
		while(strstr(text,str))
		{
			Click(button);
			SendMessage(rich, WM_GETTEXT,300,(LPARAM)(LPCSTR) text);
		}
		
		SendMessage(rich, WM_SETTEXT,300, (LPARAM)(LPCSTR) temp);

	}

	// get welcome window
	inline HWND GetWelcome()
	{
		return FindWindowLike_Title(FindMDI(),"Welcome,");
	}
	// get the buddy list window
	inline HWND GetBuddyList()
	{
		return FindWindowLike_Title(FindMDI(),"Buddy List");
	}

};


// the AOLCPP object for AOL 3.0
struct AOLCPP_3 : AOLCPPOBJ 
{
private:

	void (*ChatScan)(char* sn,char* msg);
	bool scan_set;
	int  pre_len;

public:

	// constructor
	inline AOLCPP_3()
	{
		scan_set = false;
		pre_len = -1;
	}

	inline ~AOLCPP_3()
	{

	}

	// is this aol3.0 ?
	inline bool isAOL30()
	{
		if(GetAOLVersion() == AOL3)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// get the tool bar
	inline HWND GetToolBar()
	{

		HWND aol,toolbar;
		aol=FindWindow("AOL Frame25",NULL);
		toolbar=FindWindowEx(aol,NULL,"AOL Toolbar",NULL);
		return toolbar;
 
		return 0;
	}
	// run the toolbar 0 being first icon, 1 being second etc
	inline void RunToolBar(int b_over)
	{ 
		HWND ico;
		ico = GetAolWindow(GetToolBar(),ICON,b_over);
		Click(ico);
	}
	// open the 3.0 email box
	inline void OpenEmailBox()
	{
		RunToolBar(1); // example of toolbar run
	}
	// open a new email
	inline void OpenNewEmail()
	{
		RunToolBar(2); // example of toolbar run
	}
	// send email 3.0
	inline void SendEmail(char* sn,char* subj,char* msg)
	{
		if(SignedOn() == false)
		{
			return;
		}

		OpenNewEmail();
		WaitForWindowLike_Title(FindMDI(),"Compose Mail");
		HWND mail;
		mail = FindWindowLike_Title(FindMDI(),"Compose Mail");
		HWND ed;
		ed = FindWindowEx(mail,0,"_AOL_Edit",0);
		SetText(ed,sn);
		HWND sub;
		sub = FindWindowEx(mail,0,0,"Subject:");
		sub = GetNextWindow(sub,2);
		SetText(sub,subj);
		HWND rich;
		rich = FindWindowEx(mail,0,"RICHCNTL",0);
		SetText(rich,msg);
		HWND ico;
		ico = FindWindowEx(mail,0,"_AOL_Icon",0);
		Click(ico);
	}
	// send instant message
	inline void SendInstantMessage(char* sn,char* msg)
	{
		if(SignedOn() == false)
		{
			return;
		}

		RunMenu(4,6);
		WaitForWindowLike_Title(FindMDI(),"Send Instant Message");
		HWND imwin;
		imwin = FindWindowLike_Title(FindMDI(),"Send Instant Message");
		HWND ed;
		ed = FindWindowEx(imwin,0,"_AOL_Edit",0);
		SetText(ed,sn);
		HWND rich;
		rich = FindWindowEx(imwin,0,"RICHCNTL",0);
		SetText(rich,msg);
		HWND ico;
		ico = GetNextWindow(rich,2);
		Click(ico);

		while(true)
		{
			HWND eim;
			HWND emsg;
			eim = FindWindowLike_Title(FindMDI(),"Send Instant Message");
			if(eim == 0)
			{
				break;
			}
			emsg = FindWindow(NULL,"America Online");
			if(emsg)
			{
				Close(emsg);
				Close(eim);
				break;
			}

			cppDoEvents(); // so are program wont lock up
		}
	}

	// run the keyword
	inline void AolKeyword(char* word)
	{
		if(SignedOn() == false)
		{
			return; // they anit signed on
		}

		RunMenu(2,5);
		WaitForWindowLike_Title(FindMDI(),"Keyword");
		HWND kw;
		kw = FindWindowLike_Title(FindMDI(),"Keyword");
		HWND ed;
		ed = FindWindowEx(kw,0,"_AOL_Edit",0);
		SetText(ed,word);
		SendMessage(ed,WM_CHAR,13,0);
		KeyPress(ed,13);
	}
	// Set The Chat Com Scan CallBack Function
    inline void SetChatComScan(void (*ChatScanX)(char* sn,char* msg))
	{
		ChatScan = ChatScanX;
		scan_set = true;
	}
//  Scan the chat
	inline void ChatComScan()
	{
			if(scan_set == true)
			{
			if(GetChatWindow())
			{


			int tlen;
			tlen = SendMessage(GetChatView(),WM_GETTEXTLENGTH,0,0);

			if(pre_len == -1)
			{
				pre_len = tlen;
				return; // first chat get
			}

			if(tlen == pre_len) // value is the same
			{
				return;
			}

			char chatbuff[5000];
			SendMessage(GetChatView(),WM_GETTEXT,tlen+1,(LPARAM)(LPCSTR)chatbuff);
			char newline[500];

			int copy_pos = pre_len;


			for(int i = tlen; i > 0; i--)
			{
				
				if(chatbuff[i] == 13)
				{
					copy_pos = i+1;
					break;
				}

			}
		
			rightcopy(chatbuff,newline,copy_pos);
			pre_len = tlen;

			char msn[100];
			char mmsg[200];
			int fcol;
			fcol = findstr(newline,":");
			leftcopy(newline,msn,fcol);
			rightcopy(newline,mmsg,fcol+3);
			ChatScan(msn,mmsg); // call users call back function

			}
		}
	}

};

// the AOLCPP object for 4.0/5.0
typedef struct AOLCPP_4 : AOLCPPOBJ
{
private:
	void (* ChatScan)(char* sn,char* msg);
	bool scan_set;
	int  pre_len;

public:

	// constructor
	inline AOLCPP_4()
	{
		scan_set = false;
		pre_len = -1;
	}

	// deconstructor
	inline ~AOLCPP_4()
	{

	}

    // get 4.0 toolbar
	inline HWND GetToolBar()
	{
		HWND tool;
		tool = FindWindowEx(FindAOL(),0,"AOL Toolbar",0);
		HWND Tool;
		Tool = FindWindowEx(tool,0,"_AOL_Toolbar",0);
		return Tool;
	}
	// run a icon in the toolbar
	inline void RunToolBar(int tool_over)
	{
		HWND tool;
		tool = GetToolBar();
		HWND ico;
		ico = GetAolWindow(tool,ICON,tool_over);
		Click(ico);
	}
	// Open there Email Box
	inline void OpenEmailBox()
	{
		RunToolBar(1);
	}

	// Open up a new Send Email
	inline void OpenNewEmail()
	{
		RunToolBar(2);
	}

	// is there email Box open ?
	inline bool isMailOpen()
	{
		HWND mb;
		mb = FindWindowLike_Title(FindMDI(),"Online MailBox");
		if(mb == 0)
		{
			return false;
		}

		return true;
	}
	// send email 4.0/5.0
	inline void SendEmail(char* sn,char* subj,char* msg)
	{
		if(SignedOn() == false)
		{
			return; // no signed on
		}

		OpenNewEmail();
		WaitForWindowLike_Title(FindMDI(),"Write Mail");
		HWND mail;
		mail = FindWindowLike_Title(FindMDI(),"Write Mail");
		HWND ed;
		ed = FindWindowEx(mail,0,"_AOL_Edit",0);
		SetText(ed,sn);
		HWND ed2;
		ed2 = GetNextWindow(ed,2);
		ed2 = GetNextWindow(ed2,2);
		ed2 = GetNextWindow(ed2,2);
		ed2 = GetNextWindow(ed2,2);
		SetText(ed2,subj);
		HWND ri;
		ri = FindWindowEx(mail,0,"RICHCNTL",0);
		SetText(ri,msg);
		HWND ico;
		ico = GetAolWindow(mail,ICON,16);
		Click(ico);

	}

	// keyword
	inline void AolKeyword(char* buff)
	{
		if(SignedOn() == false)
		{
			return; // there signed off
		}
		HWND kw;
		kw = FindWindowEx(GetToolBar(),0,"_AOL_ComboBox",0);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		Click(kw);
		WaitForWindowLike_Title(FindMDI(),"Keyword");
		HWND kww;
		kww = FindWindowLike_Title(FindMDI(),"Keyword");
		HWND ed;
		ed = FindWindowEx(kww,0,"_AOL_Edit",0);
		SetText(ed,buff);
		HWND ico;
		ico = FindWindowEx(kww,0,"_AOL_Icon",0);
		Click(ico);
	}
// get chat room text 4.0/5.0
	inline void GetChatText(char* buff)
	{
		HWND view = GetChatView();
		int len;
		len = SendMessage(view,WM_GETTEXTLENGTH,0,0);
		SendMessage(view,WM_GETTEXT,len,(LPARAM)(LPCSTR)buff);
	}

	// scan if the callback function is set
	inline void ChatComScan()
	{
		if(scan_set == true)
		{
			if(GetChatWindow())
			{


			int tlen;
			tlen = SendMessage(GetChatView(),WM_GETTEXTLENGTH,0,0);

			if(pre_len == -1)
			{
				pre_len = tlen;
				return; // first chat get
			}

			if(tlen == pre_len) // value is the same
			{
				return;
			}

			char chatbuff[5000];
			SendMessage(GetChatView(),WM_GETTEXT,tlen+1,(LPARAM)(LPCSTR)chatbuff);
			char newline[500];

			int copy_pos = pre_len;


			for(int i = tlen; i > 0; i--)
			{
				
				if(chatbuff[i] == 13)
				{
					copy_pos = i+1;
					break;
				}

			}
		
			rightcopy(chatbuff,newline,copy_pos);
			pre_len = tlen;

			char msn[100];
			char mmsg[200];
			int fcol;
			fcol = findstr(newline,":");
			leftcopy(newline,msn,fcol);
			rightcopy(newline,mmsg,fcol+3);
			ChatScan(msn,mmsg); // call users call back function

			}
		}
	}
	// initlize the callback function for a chat scan
	inline void SetChatComScan( void (*ChatScanX)(char* sn, char* msg))
	{
		ChatScan = ChatScanX;
		scan_set = true;
	}
	// get mail box
	inline HWND GetMailBox()
	{
		return FindWindowLike_Title(FindMDI(),"Online MailBox");
	}

	// dump aol mail box to a hwnd
	inline void GetAOLMailBox(HWND hwnd)
	{
		HWND mail;
		mail = GetMailBox();
		HWND mail_tree;
		mail_tree = FindWindowEx(mail,0,"_AOL_Tree",0);

		int l_len;
		l_len = SendMessage(mail_tree,LB_GETCOUNT,0,0);
		for(int i = 0; i < l_len; i++)
		{
			char curitem[200];
			SendMessage(mail_tree,LB_GETTEXT,200,(LPARAM)(LPCSTR)curitem);
			SendMessage(hwnd,LB_ADDSTRING,200,(LPARAM)(LPCSTR)curitem);
		}
		
	}

	// send a aol 4.0 instant message
	inline void SendInstantMessage(char* sn,char* msg)
	{
		HWND buddylist;
		buddylist = GetBuddyList();
		if(buddylist == 0)
		{
			return; // no buddy list found :(
		}

		HWND iim;
		iim = FindWindowEx(buddylist,0,0,"IM");
		iim = GetNextWindow(iim,2);
		Click(iim);

		WaitForWindowLike_Title(FindMDI(),"Send Instant Message");

		HWND im;
		im = FindWindowLike_Title(FindMDI(),"Send Instant Message");
		HWND ed;
		ed = FindWindowEx(im,0,"_AOL_Edit",0);
		SetText(ed,sn);
		HWND rich;
		rich = FindWindowEx(im,0,"RICHCNTL",0);
		SetText(rich,msg);
		HWND ico;
		ico = GetNextWindow(rich,2);
		Click(ico);

		while(true) // loop to see if stuff went succesfully
		{
			HWND eim;
			HWND emsg;
			eim = FindWindowLike_Title(FindMDI(),"Send Instant Message");

			if(eim == 0)
			{
				break;
			}

			emsg = FindWindow(NULL,"America Online");
			if(emsg)
			{
				Close(emsg); // error message
				Close(eim);
				break;
			}

			cppDoEvents(); // make sure are program dont lock up
		}


	}

	// turn ghosting on
	inline void GhostOn()
	{
		if(SignedOn() == false)
		{
			return; // there not signed on !
		}

		HWND bud;
		bud = GetBuddyList();
		if(bud == 0)
		{
			return; // they anit got no buddy list open 
		}
		HWND set;
		set = FindWindowEx(bud,0,0,"Setup");
		set = GetNextWindow(set,2);
		Click(set);
		WaitForWindowLike_Title(FindMDI(),"'s Buddy List");
		HWND budwin;
		budwin = FindWindowLike_Title(FindMDI(),"'s Buddy List");
		HWND ico;
		ico = GetAolWindow(budwin,ICON,5);
		Click(ico);
		WaitForWindowLike_Title(FindMDI(),"Privacy Pref");
		HWND pref;
		pref = FindWindowLike_Title(FindMDI(),"Privacy Pref");
		HWND chk;
		chk = FindWindowEx(pref,0,"_AOL_Checkbox",0);
		chk = GetNextWindow(chk,2);
		chk = GetNextWindow(chk,2);
		chk = GetNextWindow(chk,2);
		chk = GetNextWindow(chk,2);
		Click(chk);
		HWND icogo;
		icogo = FindWindowEx(pref,0,"_AOL_Edit",0);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		Click(icogo);
		Click(icogo);
		WaitForWindow(NULL,"America Online");
		HWND a;
		a = FindWindow(NULL,"America Online");
		Close(a);
		Close(budwin); // all done
	}
	// turn ghosting off
	inline void GhostOff()
	{
		if(SignedOn() == false)
		{
			return; // there not signed on !
		}

		if(SignedOn() == false)
		{
			return; // there not signed on !
		}

		HWND bud;
		bud = GetBuddyList();
		if(bud == 0)
		{
			return; // they anit got no buddy list open 
		}
		HWND set;
		set = FindWindowEx(bud,0,0,"Setup");
		set = GetNextWindow(set,2);
		Click(set);
		WaitForWindowLike_Title(FindMDI(),"'s Buddy List");
		HWND budwin;
		budwin = FindWindowLike_Title(FindMDI(),"'s Buddy List");
		HWND ico;
		ico = GetAolWindow(budwin,ICON,5);
		Click(ico);
		WaitForWindowLike_Title(FindMDI(),"Privacy Pref");
		HWND pref;
		pref = FindWindowLike_Title(FindMDI(),"Privacy Pref");
		HWND chk;
		chk = FindWindowEx(pref,0,"_AOL_Checkbox",0);
		Click(chk);
		HWND icogo;
		icogo = FindWindowEx(pref,0,"_AOL_Edit",0);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		Click(icogo);
		Click(icogo);
		WaitForWindow(NULL,"America Online");
		HWND a;
		a = FindWindow(NULL,"America Online");
		Close(a);
		Close(budwin); // all done

	}



}AOLCPP_5;



// ***********************************************************************************************
// *********************************** MasterString - Simple, and Explicit String Manipluation



// string data location structure use w/ (findstrl)
struct MasStrDataLoc
{
	int* dindex;
	int  array_size;
	char* thestring;
	char* searchstr;
	bool search_status;

	inline MasStrDataLoc()
	{
		search_status = false;
		dindex = 0;
		array_size = 0;
		searchstr = 0;
	}
	
	inline ~MasStrDataLoc()
	{
		if(dindex != 0)
		{

		delete [] dindex;
		dindex = 0;

		}
		if(thestring != 0)
		{

		delete [] thestring;
		thestring = 0;

		}
		if(searchstr != 0)
		{

		delete [] searchstr;
		searchstr = 0;

		}
	}

	inline void create_array(int size)
	{
		dindex = new int[size];
		array_size = size;
	}

	inline void setstr(char* buff)
	{
		int len;
		len = strlen(buff);
		thestring = new char[len+1];
		stringcopy(thestring,buff);
	}

	inline void setstatus(bool x)
	{
		search_status = x;
	}

	inline void setsearchstr(char* buff)
	{
		int len;
		len = strlen(buff);
		searchstr = new char[len+1];
		stringcopy(searchstr,buff);
	}

	// return pointer to the string which the array holds data for
	inline char* getstr()
	{
		return thestring;
	}

	inline char* getsearchstr()
	{
		return searchstr;
	}

	inline int getarraysize()
	{
		return array_size;
	}

	inline int getstringpoint(int index)
	{
		if(index <= array_size)
		{

		return dindex[index];

		}
	}
	// maximum string points for search
	inline int getmaxpoint()
	{
		return array_size;
	}
	// get status
	inline bool getstatus()
	{
		return search_status;
	}

	inline bool wassearchsuccesful()
	{
		return getstatus();// was it succesfull?
	}
};
// find string location (dumps all locations into the location data structure (MasStrDataLoc))
bool findstrloc(char* buff,char* search,MasStrDataLoc* dloc);// standard
bool findstrlocf(char* buff,char* search,MasStrDataLoc* dloc);// forward
bool findstrlocb(char* buff,char* search,MasStrDataLoc* dloc);// backward

// master string range structure
struct MasStrRange
{
	int start_x;
	int stop_y;

	inline MasStrRange()
	{
		start_x = 0;
		stop_y = 0;
	}

	inline void SetRange(int x, int y)
	{
		start_x = x;
		stop_y = y;
	}

	inline int GetRangeX()
	{
		return start_x;
	}

	inline int GetRangeY()
	{
		return stop_y;
	}

	inline int GetRangeHI()
	{
		return start_x;
	}

	inline int GetRangeLO()
	{
		return stop_y;
	}

	inline int Clear()
	{
		start_x = 0;
		stop_y = 0;
	}
};

// range search structures for range style string manipulation
bool searchrange(char* buff,char* search,MasStrRange* mrang);
void copyleftrange(char* input,char* output,MasStrRange* mrang, int hi_lo);
void copyrightrange(char* input,char* output,MasStrRange* mrang,int hi_lo);
void copymidrange(char* input,char* output,MasStrRange* mrang, int hi_lo,MasStrRange* mrangx, int hi_lox);
bool isearchrange(int startx, char* buff,char* search,MasStrRange* mrang);

// master string list structure string data
struct MasStrList_String
{
	char* thestring;

	inline ~MasStrList_String()
	{
		delete [] thestring;
	}

	inline void set(char* buff)
	{
		int len;
		len = strlen(buff) + 1;
		thestring = new char[len];
		stringcopy(thestring,buff);
	}

	inline char* get()
	{
		return thestring;
	}
};
// master string list , list handler structure
struct MasStrList
{
	MasStrList_String* strings;
	int list_size;

	inline ~MasStrList()
	{
		delete [] strings;
	}

	inline MasStrList(int list_size)
	{
		create(list_size);
	}

	inline MasStrList()
	{
		list_size = 0;
		strings = NULL;
	}

	inline void create(int list_sizez)
	{
		list_size = list_sizez;
		strings = new MasStrList_String[list_size];
	}

	inline char* getstr(int index)
	{
		return strings[index].get();
	}

	inline int getcount()
	{
		return list_size;
	}
};

// create string list
void createstrlist(char* buffer, char* list_marker,MasStrList* list);


// charwrap  easy to use char array, that automaticly removes itself from freestore
struct charwrap
{
	char* str;

	inline charwrap(int size)
	{
		str = new char[size];
	}

	inline charwrap(char* buff)
	{
		set(buff);
	}

	inline charwrap(char* buff,bool x)
	{
		set(buff);
		strclearn();
	}

	inline ~charwrap()
	{
		delete [] str; // delete that shit
	}

	inline void set(char* buff)
	{
		int len;
		len = strlen(buff) + 1;
		str = new char[len];
		stringcopy(str,buff);
	}

	inline void snew(int size)
	{
		str = new char[size];
	}

	// clear off freestore
	inline void clear()
	{
		delete [] str;
		str = NULL;
	}

	inline void strclear()
	{
		int len;
		len = getlen(str);

		for(int i = 0; i < len; i++)
		{
			str[i] = 0;
		}
	}

	inline void strclearn()
	{
		stringcopy(str,"");
	}

	inline char* get()
	{
		return str;
	}

	inline int len()
	{
		return getlen(str);
	}

	inline void qmsg()
	{
		MessageBox(0,str,"QMSG",MB_OK|MB_ICONINFORMATION);
	}

};

// structure of string manipulation algorithims to use for objects to inhert
struct MasStrObj
{
    inline void mstr_stringcopy(char* input,char* output)
	{
		stringcopy(input,output);
	}

	inline void mstr_stringattach(char* input,char* output)
	{
		stringattach(input,output);
	}

	inline void mstr_leftcopy(char* input,char* output,int pos)
	{
		leftcopy(input,output,pos);
	}

	inline void mstr_rightcopy(char* input,char* output,int pos)
	{
		rightcopy(input,output,pos);
	}

	inline void mstr_midcopy(char* input,char* output,int start_pos,int stop_pos)
	{
		midcopy(input,output,start_pos,stop_pos);
	}

	inline void mstr_trimspace(char* buff)
	{
		trimspace(buff);
	}

	inline int mstr_findstr(char* buffer,char* search)
	{
		return findstr(buffer,search);
	}

	inline int mstr_ifindstr(int i,char* buffer,char* search)
	{
		return ifindstr(i,buffer,search);
	}

	inline int mstr_findstrb(char* body,char* search)
	{
		return findstrb(body,search);
	}

	inline int mstr_ifindstrb(int startx,char* body,char* search)
	{
		return ifindstrb(startx,body,search);
	}

	inline int mstr_fsearchstr(int start,int stop,char* buff,char* search)
	{
		return fsearchstr(start,stop,buff,search);
	}

	inline int mstr_bsearchstr(int start,int stop,char* buff,char* search)
	{
		return bsearchstr(start,stop,buff,search);
	}

	inline int mstr_getlen(char* buff)
	{
		int len;
		len = strlen(buff);
		return len;
	}

	inline int mstr_lcase(char* buffer)
	{
		lcase(buffer);
	}

	inline int mstr_ucase(char* buffer)
	{
		ucase(buffer);
	}

	inline int mstr_ucasel(char c)
	{
		return ucasel(c);
	}

	inline int mstr_lcasel(char c)
	{
		return lcasel(c);
	}

	inline bool mstr_findstrloc(char* buff,char* search,MasStrDataLoc* dloc)
	{
		return findstrloc(buff,search,dloc);
	}

	inline bool mstr_findstrlocf(char* buff,char* search,MasStrDataLoc* dloc)
	{
		return findstrlocf(buff,search,dloc);
	}

	inline bool mstr_findstrlocb(char* buff,char* search,MasStrDataLoc* dloc)
	{
		return findstrlocb(buff,search,dloc);
	}

	inline bool mstr_searchrange(char* buff,char* search,MasStrRange* mrang)
	{
		return searchrange(buff,search,mrang);
	}

	inline bool mstr_isearchrange(int startx, char* buff,char* search,MasStrRange* mrang)
	{
		return isearchrange(startx,buff,search,mrang);
	}

	inline void mstr_copyleftrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
	{
		copyleftrange(input,output,mrang,hi_lo);
	}

	inline void mstr_copyrightrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
	{
		copyrightrange(input,output,mrang,hi_lo);
	}

	inline void mstr_copymidrange(char* input,char* output,MasStrRange* mrang,int hi_lo,MasStrRange* mrangx,int hi_lox)
	{
		copymidrange(input,output,mrang,hi_lo,mrangx,hi_lox);
	}

	inline int mstr_findoccourance(char* buffer,char* searchx)
	{
		return findoccourance(buffer,searchx);
	}

	inline void mstr_convertinteger(int integer,char* buff,int base)
	{
		convertinteger(integer,buff,base);
	}

	inline int mstr_convertstring(char* buff)
	{
		return convertstring(buff);
	}

	inline bool mstr_ishexc(char c)
	{
		return ishexc(c);
	}

	inline bool mstr_ishex(char* buff)
	{
		return ishex(buff);
	}

	inline int mstr_hextointc(char c)
	{
		return hextointc(c);
	}
	inline int mstr_hextoint(char* buff)
	{
		return hextoint(buff);
	}

	inline void mstr_tripchardown(char* buff,int by)
	{
		tripchardown(buff,by);
	}

	inline void mstr_tripcharup(char* buff, int by)
	{
		tripcharup(buff,by);
	}
	inline void mstr_replacechar(char* buff,char findchr,char replace)
	{
		replacechar(buff,findchr,replace);
	}
	inline void mstr_replacestr(char* buff,char* findstr,char* replacex,char* output)
	{
		replacestr(buff,findstr,replacex,output);
	}
	inline void mstr_rmvinst(char* buff,char* findchr,char* re,char* out)
	{
		rmvinst(buff,findchr,re,out);
	}

	inline char mstr_randomchar(int max)
	{
		return randomchar(max);
	}
	inline char mstr_randomchar(int max, int up)
	{
		return randomchar(max,up);
	}
	inline void mstr_randomstr(char* buff,int max, int size)
	{
		randomstr(buff,max,size);
	}
	inline void mstr_removechar(char* input,char* output,char c)
	{
		removechar(input,output,c);
	}
	inline char mstr_findchar(char* str,char c)
	{
		return findchar(str,c);
	}
	inline char mstr_ifindchar(int start,char* str,char c)
	{
		return ifindchar(start,str,c);
	}
	inline char mstr_findcharb(char* str,char c)
	{
		return findcharb(str,c);
	}
	inline char mstr_ifindcharb(int start,char* str,char c)
	{
		return ifindcharb(start,str,c);
	}
	inline char mstr_findcharcf(char* str,int start,int stop,char c)
	{
		return findcharcf(str,start,stop,c);
	}
	inline char mstr_findcharcb(char* str,int start,int stop,char c)
	{
		return findcharcb(str,start,stop,c);
	}
	inline void mstr_removestr(char* str,char* output,char* strsearch)
	{
		removestr(str,output,strsearch);
	}
	inline void mstr_removestrinstance(char* str,char* output,char* strx)
	{
		rmvstrx(str,output,strx);
	}
	inline void mstr_savestr(char* filename,char* string)
	{
		strsavefile(filename,string);
	}
	inline bool mstr_loadstr(char* filename,char* output)
	{
		return strloadfile(filename,output);
	}
	inline int  mstr_getfilestrlen(char* filename)
	{
		return getfilestringlength(filename);
	}
	inline int mstr_reversestr(char* str_input,char* str_output)
	{
		reversestring(str_input,str_output);
	}
	inline bool mstr_isstrvalid(char* str)
	{
		return isstrvalid(str);
	}
	inline bool mstr_mstrcmp(char* buff1,char* buff2)
	{
		return mstrcmp(buff1,buff2);
	}

	inline bool mstr_mstrcmpl(char* buff1,char* buff2)
	{
		return mstrcmpx(buff1,buff2);
	}

	inline bool mstr_insidestr(char* buff1,char* buff2)
	{
		return insidestr(buff1,buff2);
	}
	inline bool mstr_insidestrl(char* buff1,char* buff2)
	{
		return insidestrx(buff1,buff2);
	}
	inline void mstr_strsep(char* str,char* lstr,int lpos,char* rstr,int rpos)
	{
		strsep(str,lstr,lpos,rstr,rpos);
	}
	inline int mstr_getnullpos(char* str)
	{
		return getnullpos(str);
	}
	inline void mstr_rmvnullset(char* str)
	{
		rmvnullset(str);
	}
	inline void mstr_strsetnull(char* str,int pos)
	{
		strsetnull(str,pos);
	}
	inline void mstr_trimcom(char* input,char* output, char start_c,char stop_c)
	{
		trimcom(input,output,start_c,stop_c);
	}
	inline void mstr_asmtrim(char* input,char* output)
	{
		asmtrim(input,output);
	}
};

// the MasterString Object

struct MasterString : MasStrObj
{
	char* str;
	int array_size;
	bool str_on;

	/********** constructors & deconstructors ****************/
	inline MasterString()
	{
		str_on = false;
		array_size = 0;
		str = NULL;
	}

	inline MasterString(int size)
	{
		set(size,"");
	}

	inline MasterString(char* buff)
	{
		int size = strlen(buff) + 2;
		set(size,buff);
	}

	inline MasterString(int size,char* buff)
	{
		set(size,buff);
	}

	inline ~MasterString()
	{
		if(str_on)
		{
			delete [] str;
			str_on = false;

		}
	}

	/* internal functions **************************/
	inline void set(int size,char* buff)
	{
		if(str_on == false)
		{
			str = new char[size];
			str_on = true;
		}
		else
		{
			delete [] str;
			str = new char[size];
		}

		mstr_stringcopy(str,buff);
		array_size = size;
	}

	inline void add(char* buff)
	{
		int total_length = GetStringLength() + strlen(buff) + 2;

		if(total_length > GetStringLength())
		{
			char* ptemp;
			ptemp = new char[GetStringLength()+1];
			strcpy(ptemp,str);

			delete [] str;
			str = 0;// set pointer to 0 
			str = new char[total_length+2];
			strcpy(str,ptemp);
			delete [] ptemp;
			strcat(str,buff);
		}
		else
		{
			strcat(str,buff);
		}
	}

	inline void unset()
	{
		if(str_on == true)
		{
			delete [] str;
			str_on = false;
		}
	}

	inline char* get()
	{
		return str;
	}

	// operators *************************

	inline void operator=(char* buffer)
	{
		// set
		int len;
		len = strlen(buffer)+2;
		set(len,buffer);
	}

	inline void operator+=(char* buffer)
	{
		add(buffer);
	}
	inline void operator+=(int x)
	{
		char buffer[30];
		itoa(x,buffer,10);
		add(buffer);
	}

	inline void operator+=(long x)
	{
		char buffer[30];
		itoa(x,buffer,10);
		add(buffer);
	}

	// misc *********************************

	inline int GetStringLength()
	{
		return mstr_getlen(str);
	}

	inline char* GetCharPointer()
	{
		return str;
	}

	inline int FindChar(char c)
	{
		return mstr_findchar(str,c);
	}

	inline int FindCharEx(int pre_pos,char c)
	{
		return mstr_ifindchar(pre_pos,str,c);
	}
	inline int FindCharBackward(char c)
	{
		return mstr_findcharb(str,c);
	}
	inline int FindCharBackwardEx(int pre_pos,char c)
	{
		return mstr_ifindcharb(pre_pos,str,c);
	}
	inline int FindCharControledForward(int start,int stop,char c)
	{
		return mstr_findcharcf(str,start,stop,c);
	}
	inline int FindCharControledBackward(int start,int stop,char c)
	{
		return mstr_findcharcb(str,start,stop,c);
	}
	inline int FindString(char* search)
	{
		return mstr_findstr(str,search);
	}

	inline int FindStringEx(int index,char* search)
	{
		return mstr_ifindstr(index,str,search);
	}

	inline int FindStringBackward(char* search)
	{
		return mstr_findstrb(str,search);
	}
	inline int FindStringBackwardEx(int index,char* search)
	{
		return mstr_ifindstrb(index,str,search);
	}
	inline int FindOccourance(char* search)
	{
		return mstr_findoccourance(str,search);
	}
	inline void StringCopy(char* buff)
	{
		mstr_stringcopy(str,buff);
	}
	inline void StringAttach(char* buff)
	{
		mstr_stringattach(str,buff);
	}
	inline void StringResize(int newSize)
	{
		char* ptemp;
		ptemp = new char[strlen(str)+1];
		strcpy(ptemp,str);

		delete [] str;
		str = new char[newSize];
		strcpy(str,ptemp);
		delete [] ptemp;
	}
	inline void StringLeft(char* output,int pos)
	{
		mstr_leftcopy(str,output,pos);
	}
	inline void StringRight(char* output,int pos)
	{
		mstr_rightcopy(str,output,pos);
	}
	inline void StringMid(char* output,int x,int y)
	{
		mstr_midcopy(str,output,x,y);
	}
	inline void TrimSpace()
	{
		trimspace(str);
	}

	inline void UpperCase()
	{
		ucase(str);
	}
	inline void LowerCase()
	{
		lcase(str);
	}
	inline char ExtractChar(int index)
	{
		if(index <= GetStringLength())
		{
			return str[index];
		}
		return 0;
	}
	inline int ForwardStringSearch(int start,int stop,char* search)
	{
		return mstr_fsearchstr(start,stop,str,search);
	}

	inline int BackwardStringSearch(int start,int stop,char* search)
	{
		return mstr_bsearchstr(start,stop,str,search);
	}
	inline bool FindStringLocation(char* search,MasStrDataLoc* dloc)
	{
		return mstr_findstrloc(str,search,dloc);
	}
	inline bool FindStringLocationF(char* search,MasStrDataLoc* dloc)
	{
		return mstr_findstrlocf(str,search,dloc);
	}
	inline bool FindStringLocationB(char* search,MasStrDataLoc* dloc)
	{
		return mstr_findstrlocb(str,search,dloc);
	}
	inline void SearchRange(char* search,MasStrRange* mrang)
	{
		mstr_searchrange(str,search,mrang);
	}
	inline void SearchRangeEx(int startx,char* search,MasStrRange* mrang)
	{
		mstr_isearchrange(startx,str,search,mrang);
	}
	inline void CopyLeftRange(char* output, MasStrRange* mrang,int hi)
	{
		mstr_copyleftrange(str,output,mrang,hi);
	}
	inline void CopyRightRange(char* output, MasStrRange* mrang,int hi)
	{
		mstr_copyrightrange(str,output,mrang,hi);
	}
	inline void CopyMidRange(char* output,MasStrRange* mrang,int hi, MasStrRange* mrangx,int hix)
	{
		mstr_copymidrange(str,output,mrang,hi,mrangx,hix);
	}
	
	inline int GetHexValue()
	{
		return mstr_hextoint(str);
	}
	inline int GetDecValue()
	{
		return atoi(str);
	}
	inline int ConvertToInteger()
	{
		return atoi(str);
	}
	inline bool IsHex()
	{
		return mstr_ishex(str);
	}

	inline void qprint()
	{
		cout << str;
	}
	inline void qmsg()
	{
		MessageBox(0,str,"QMSG",MB_ICONINFORMATION);
	}
	inline void ClearString()
	{
		for(int z = 0; z < GetStringLength(); z++)
		{
			str[z] = 0;
		}
	}
	inline void SetWindowText(HWND hwnd)
	{
		SendMessage(hwnd,WM_SETTEXT,strlen(str),(LPARAM)(LPCSTR)str);
	}
	inline void AddToList(HWND hwnd)
	{
		SendMessage(hwnd,LB_ADDSTRING,strlen(str),(LPARAM)(LPCSTR)str);
	}
	inline void AddToCombo(HWND hwnd)
	{
		SendMessage(hwnd,CB_ADDSTRING,strlen(str),(LPARAM)(LPCSTR)str);
	}

	inline void CopyTextFromHWND(HWND hwnd)
	{
		char* buffer;
		int len;
		len = SendMessage(hwnd,WM_GETTEXTLENGTH,0,0);
		buffer = new char[len+1];
		SendMessage(hwnd,WM_GETTEXT,len,(LPARAM)(LPCSTR)buffer);
		
		set(len+1,buffer);

		delete [] buffer;
	}
	
	inline void AttachTextFromHWND(HWND hwnd)
	{
		char* buffer;
		int len;
		len = SendMessage(hwnd,WM_GETTEXTLENGTH,0,0);
		buffer = new char[len+1];
		SendMessage(hwnd,WM_GETTEXT,len,(LPARAM)(LPCSTR)buffer);
		
		add(buffer);

		delete [] buffer;
	}
	inline void ReplaceCharacter(char findchr,char replace)
	{
		mstr_replacechar(str,findchr,replace);
	}
	inline void RandomizeString()
	{
		randomstr(str,255,strlen(str));
	}
	inline void ReplaceString(char* search, char* replacestr)
	{
		if(mstr_findstr(str,search) != -1)
		{

		char* output;
		output = new char[strlen(str)+10];
		mstr_replacestr(str,search,replacestr,output);
		set(strlen(output)+10,output);
		delete [] output;
		output = 0;
		
		}
	}
	inline void RemoveCharacters(char c)
	{
		char* output;
		output = new char[strlen(str)+10];
		mstr_removechar(str,output,c);
		set(strlen(output)+10,output);
		delete [] output;
		output = 0;
	}
	inline void RemoveString(char* search)
	{
		if(mstr_findstr(str,search) != -1)
		{
			char* output;
			output = new char[strlen(str)+10];
			mstr_removestr(str,output,search);
			set(strlen(output)+10,output);
			delete [] output;
			output = 0;
		}
	}
	inline void RemoveSingleInstanceOfString(char* search)
	{
		if(mstr_findstr(str,search) != -1)
		{
			char* output;
			output = new char[strlen(str)+10];
			rmvstrx(str,output,search);
			set(strlen(output)+10,search);
			delete [] output;
			output = 0;
		}
	}
	inline void SaveToFile(char* filename)
	{
		mstr_savestr(filename,str);
	}
	inline void LoadStringFromFile(char* filename)
	{
		if(getfilestringlength(filename) == -1)
		{
			return; // failure file not found
		}

		char* temp;
		temp = new char[getfilestringlength(filename)+20];
		mstr_loadstr(filename,temp);
		set(strlen(temp)+20,temp);
		delete [] temp;
		temp = 0;
	}
	inline bool IsStringValid()
	{
		return mstr_isstrvalid(str);
	}

	inline int ReverseString() // reverse the string
	{
		char* temp;
		temp = new char[GetStringLength()+10];

		reversestring(str,temp);
		set(strlen(temp)+10,temp);

		delete [] temp;
		temp = 0;
	}

	inline bool StringCompare(char* buff)
	{
		return mstr_mstrcmp(str,buff);
	}
	inline bool StringCompare_NOCASE(char* buff)
	{
		return mstr_mstrcmpl(str,buff);
	}
	inline bool IsInsideString(char* buff)
	{
		return mstr_insidestr(str,buff);
	}
	inline bool IsInsideString_NOCASE(char* buff)
	{
		return mstr_insidestrl(str,buff);
	}
	inline void SeperateString(char* lbuff,int lpos,char* rbuff,int rpos)
	{
		mstr_strsep(str,lbuff,lpos,rbuff,rpos);
	}
	inline void AsmTrim()
	{
		// trim string as tho it were assembly language source
		char* output;
		output = new char[GetStringLength()+10];
		asmtrim(str,output);
		set(strlen(output)+10,output);
		delete [] output;
		output = 0;
	}

	inline void TrimComments(char start_c,char stop_c)
	{
		char* output;
		output = new char[GetStringLength()+10];
		trimcom(str,output,start_c,stop_c);
		set(strlen(output)+10,output);
		delete [] output;
		output = 0;
	}
};

// MasterString Item Structure 
struct ListItem
{
	int list_index;

	inline void setindex(int i)
	{
		list_index = i;
	}

	inline int getindex()
	{
		return list_index;
	}
};

struct MasterStringItem : MasterString,ListItem
{
	bool on;

	inline MasterStringListItem()
	{
		on = false;
	}

	inline void seton(bool x)
	{
		on = x;
	}

	inline bool geton()
	{
		return on;
	}
};

// example of a list using MasterStrings
struct MasterStringList 
{
	MasterStringItem* item;
	bool ion;
	int array_size;
	int off;

	inline MasterStringList()
	{
		ion = false;
		off = 0;
	}

	inline ~MasterStringList()
	{
		if(ion == true)
		{
			delete [] item;
			item = NULL;
		}
	}

	inline MasterStringList(int size)
	{
		createList(size);
	}
	
	inline void createList(int size)
	{
		item = new MasterStringItem[size];
		ion = true;
		array_size = size;
	}

	inline int  GetArraySize()
	{
		return array_size;
	}

	inline char* GetListStringPointerByIndex(int index)
	{
		return item[index].get();
	}

	inline int AddString(char* buffer)
	{
  		item[off].set(strlen(buffer)+10,buffer);
		int xoff = off;
		off++;
		return xoff;
	}

	inline int GetListLength()
	{
		return off;
	}

	inline void GetString(int index,char* output)
	{
		strcpy(output,item[index].get());
		
	}


	inline void Clear()
	{
		for(int i = 0; i < off; i++)
		{
			item[i].ClearString();
		}

		off = 0;
	}
};

struct MasterEntry : ListItem
{
	MasterString name;
	MasterString value;
	bool on_switch;

	inline MasterEntry()
	{
		name = "";
		value = "";
		on_switch = false;
	}

	inline bool amion()
	{
		return on_switch;
	}

};

// easy to use INI object, using MasterStrings
struct MasterINI
{
	MasterEntry* masEntry;
	bool mas_on;
	int array_size;
	int off_count;

	// constructors/deconstructors

	inline MasterINI()
	{
		masEntry = 0;
		mas_on = false;
		off_count = 0;
	}
	
	inline MasterINI(int size)
	{
		set(size);
	}

	inline ~MasterINI()
	{
		if(mas_on)
		{
			delete [] masEntry;
			masEntry = 0;
		}
	}

	inline set(int size)
	{
		if(mas_on == true)
		{
			delete [] masEntry;
			masEntry = 0;
		}

		masEntry = new MasterEntry[size];
		mas_on = true;
		array_size = size;
		off_count = 0;
	}

	inline int getsize()
	{
		return array_size;
	}

	inline void Create(int size)
	{
		set(size);
	}

	inline bool AddEntry(char* name,char* value)
	{
		if(off_count < getsize())
		{


		masEntry[off_count].name = name;
		masEntry[off_count].value = value;
		masEntry[off_count].list_index = off_count;

		off_count++;
		return true;
		}

		return false;
	}

	inline bool GetEntry(char* name,char* output_value)
	{
		for(int i = 0; i < getsize(); i++)
		{
			if(findstr(masEntry[i].name.get(),name) != -1)
			{
				stringcopy(output_value,masEntry[i].value.get());
				return true;
			}
		}

		strcpy(output_value,"*NULL*");
		return false;
	}
};

bool SaveMasterINI(char* filename,MasterINI* mini); // Save INI
bool LoadMasterINI(char* filename,MasterINI* mini); // Load INI

struct MasCharList // char list based on the \n (breaks strings into lines) (for use with MasAsm)
{
	MasterString* list;
	bool list_on;
	int array_size;
	int list_len;


	inline MasCharList()
	{
		list = 0;
		list_on = false;
	}

	inline MasCharList(char* buff)
	{
		BuildList(buff);
	}

	inline ~MasCharList()
	{
		if(list_on == true)
		{

		delete [] list;
		list = 0;

		}
	}

	inline void BuildList(char* buff)
	{
		int size;
		size = countlines(buff) + 1;
		list = new MasterString[size];
		list_on = true;
		array_size = size;
		// format the characters into this array
		int pre_pos = 0;
		int acount = 0;

		while(1)
		{
			int find_x;
			find_x = ifindstr(pre_pos,buff,"\n");
			
			if(find_x == -1)
			{
				break;// all done !
			}

			
			char* temp;
			temp = new char[strlen(buff)+1];

			midcopy(buff,temp,pre_pos,find_x);
			pre_pos = find_x;
		
			// add
			list[acount] = temp;
			acount++;
		

			delete [] temp;
			temp = 0;

		}

		list_len = acount;

	}

	inline int GetLength()
	{
		return list_len;
	}

	inline MasterString* GetMasterString(int index)
	{
		return (MasterString*)&list[index];
	}

};


static AOLCPP_4 aol4;// aolcpp4 object
static AOLCPP_3 aol3; // aol3 object
static APIHELP  apihlp; // static apihelp
static AOLCPPOBJ aolobj; // aol object

 
// C++ Version of DoEvents
void cppDoEvents() 
{ 
	MSG Msg; 
	while(PeekMessage(&Msg,NULL,0,0,PM_REMOVE))
	{
		if (Msg.message == WM_QUIT)break;
		TranslateMessage(&Msg); 
		DispatchMessage(&Msg);
	} 
}   

// FindWindowLike
HWND FindWindowLike_Class(HWND Parent, char* Class)
{

    HWND win;
    win = GetWindow(GetWindow(Parent, GW_CHILD), GW_HWNDFIRST);


while(win != 0)
{

char buff[500];
GetClassName(win, buff, 500);



if(strstr(buff,Class))
{

    return win;
}


win = GetWindow(win, GW_HWNDNEXT);

}

return 0;

}

/*
  FindWindowLike_Title
  Synthax:

  HWND hWnd;
  hWnd = FindWindowLike_Title(ParentWindow, "Title String");


*/

HWND FindWindowLike_Title(HWND Parent, char* Title)
{
    HWND win;
    win = GetWindow(GetWindow(Parent, GW_CHILD), GW_HWNDFIRST);


while(win != 0)
{

char buff[500];
SendMessage(win, WM_GETTEXT,500, (LPARAM)(LPCSTR) buff);

if(strstr(buff,Title))
{

    return win;
}


win = GetWindow(win, GW_HWNDNEXT);

}

return 0;

}


/********************** STRING MANIPULATION **************************************************/

// master string
// jared bruni
// my string algorithims :)

// string copy
void stringcopy(char* input,char* output)
{
	strcpy(input,output);
}

// string attach
void stringattach(char* input,char* output)
{
	strcat(input,output);
}

// left copy
void leftcopy(char* input,char* output,int pos)
{
	int index = 0;
	for(int i = 0; i < pos; i++)
	{
		output[index] = input[i];
		index++;
	}
	output[index] = 0;
}
// right copy
void rightcopy(char* input,char* output,int pos)
{
	int index = 0;
	int len = strlen(input);
	for(int i = pos; i < len; i++)
	{
		output[index] = input[i];
		index++;
	}
	output[index] = 0;

}
// mid copy
void midcopy(char* input,char* output,int start_pos, int stop_pos)
{
	int index = 0;
	for(int i = start_pos; i < stop_pos; i++)
	{
		output[index] = input[i];
		index++;
	}

	output[index] = 0;
}

// trim the space
void trimspace(char* buffer)
{
	int len;
	len = strlen(buffer);
	char* ptemp;
	ptemp = new char[len+1];
	strcpy(ptemp,buffer);

	int index = 0;
	for(int z = 0; z < len; z++)
	{
		if(ptemp[z] != ' ')
		{
			buffer[index] = ptemp[z];
			index++;
		}
	}
	buffer[index] = 0;

	delete [] ptemp;
}

int findstr(char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search); // search len

	for(int i = 0; i < len; i++)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;

			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i;
			}
		}
	}

	return -1; // failure
}

int ifindstr(int startx,char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search); // search len

	for(int i = startx+1; i < len; i++)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;

			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i;
			}
		}
	}

	return -1; // failure
}

int findstrb(char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search);

	for(int i = len; i > 0; i--)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;
			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i; // found it
			}
		}

	}
	return -1; // failure
}
// find inside backwards string loop
int ifindstrb(int startx, char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search);

	for(int i = startx-1; i > 0; i--)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;
			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i; // found it
			}
		}

	}
	return -1; // failure
}
// forward search string (controled range) 
int fsearchstr(int start,int stop,char* buff,char* search)
{
	int len = strlen(buff);
	int len2 = strlen(search);

	for(int i = start; i < stop; i++)
	{
		if(buff[i] == search[0])
		{
			bool ichk = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
			  return i; // found it
			}
		}
	}

	return -1; // failure
}

// backward search string (controled range)
int bsearchstr(int start,int stop,char* buff,char* search)
{
	int len = strlen(buff);
	int len2 = strlen(search);

	for(int i = start; i > stop; i--)
	{
		if(buff[i] == search[0])
		{
			bool ichk = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i; // found it;
			}
		}
	}

	return -1;// failure
}
// getting length
int getlen(char* buff)
{
	return strlen(buff);// use strlen :)
}
// lower case
void lcase(char* buffer)
{
	int len = getlen(buffer);

	for(int i = 0; i < len; i++)
	{
		buffer[i] = tolower(buffer[i]);
	}
}
// upercase
void ucase(char* buffer)
{
	int len = getlen(buffer);

	for(int i = 0; i < len; i++)
	{
		buffer[i] = toupper(buffer[i]);
	}
}
// uppercase letter
int ucasel(char c)
{
	return tolower(c);
}

// lowercase letter
int lcasel(char c)
{
	return tolower(c);
}

// find string location algorithims
bool findstrloc(char* buff,char* search,MasStrDataLoc* dloc)
{
	int len = strlen(buff);
	int len2 = strlen(search);
	int* f;
	int  f_i = 0;
	f = new int[len+1];// big just in case

	for(int i = 0; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ic = true;
				
			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{

				}
				else
				{
					ic = false;
				}
			}

			if(ic == true)
			{
				f[f_i] = i;
				f_i++;
			}
		}
	}

	dloc->create_array(f_i);
	dloc->setstr(buff);
	dloc->setsearchstr(search);
	for(int p = 0; p < f_i; p++)
	{
		dloc->dindex[p] = f[p];
	}
	delete [] f;

	if(f_i != 0)
	{
		dloc->setstatus(true);
		return true; // we got some locations
	}
	else
	{
		dloc->setstatus(false); 
		return false; // not found
	}
}
// find string location forward search
bool findstrlocf(char* buff,char* search,MasStrDataLoc* dloc)
{
	return findstrloc(buff,search,dloc);
}
// find string location backwards search
bool findstrlocb(char* buff,char* search,MasStrDataLoc* dloc)
{
	int len = strlen(buff);
	int len2 = strlen(search);
	int* f;
	int  f_i = 0;
	f = new int[len+1];// big just in case

	for(int i = len; i > 0; i--)
	{
		if(buff[i] == search[0])
		{
			bool ic = true;
				
			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{

				}
				else
				{
					ic = false;
				}
			}

			if(ic == true)
			{
				f[f_i] = i;
				f_i++;
			}
		}
	}

	dloc->create_array(f_i);
	dloc->setstr(buff);
	dloc->setsearchstr(search);
	for(int p = 0; p < f_i; p++)
	{
		dloc->dindex[p] = f[p];
	}
	delete [] f;

	if(f_i != 0)
	{
		dloc->setstatus(true);
		return true; // we got some locations
	}
	else
	{
		dloc->setstatus(false);
		return false; // not found
	}
}

// string ( range based ) manipulation algorithims
bool searchrange(char* buff,char* search,MasStrRange* mrang)
{
	int len;
	int len2;
	len = strlen(buff);
	len2 = strlen(search);

	for(int i = 0; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ik = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ik = false;
				}
			}

			if(ik == true)
			{
				mrang->SetRange(i,i+len2);
				return true;
			}
		}
	}
	mrang->SetRange(0,0);
	return false;
}
// string range manipluation ex (i)
bool isearchrange(int startx, char* buff,char* search,MasStrRange* mrang)
{
	int len;
	int len2;
	len = strlen(buff);
	len2 = strlen(search);

	for(int i = startx+1; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ik = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ik = false;
				}
			}

			if(ik == true)
			{
				mrang->SetRange(i,i+len2);
				return true;
			}
		}
	}
	mrang->SetRange(0,0);
	return false;
}

// find the occourance amount of a specific string
int findoccourance(char* buff,char* search)
{
	int len;
	int len2;
	len = strlen(buff);
	len2 = strlen(search);

	int occ = 0;

	for(int i = 0; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ic = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ic = false;
				}
			}

			if(ic == true)
			{
				occ++;
			}

		}
	}

	if(occ == 0)
	{

	return -1; // failure

	}
	else
	{
		return occ;
	}
}

// string range manipulation copy left range
void copyleftrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
{
	if(hi_lo == MRANGE_HI)
	{
		leftcopy(input,output,mrang->GetRangeHI());
	}
	else
	{
		leftcopy(input,output,mrang->GetRangeLO());
	}
}
// string range manipulation copy right range
void copyrightrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
{
	if(hi_lo == MRANGE_HI)
	{
		rightcopy(input,output,mrang->GetRangeHI());
	}
	else
	{
		rightcopy(input,output,mrang->GetRangeLO());
	}
}
// string range manipulation mid copy
void copymidrange(char* input,char* output,MasStrRange* mrang, int hi_lo,MasStrRange* mrangx, int hi_lox)
{
	int cx;
	int cy;

	if(hi_lo == MRANGE_HI)
	{
		cx = mrang->GetRangeHI();
	}
	else
	{
		cx = mrang->GetRangeLO();
	}

	if(hi_lox == MRANGE_HI)
	{
		cy = mrangx->GetRangeHI();
	}
	else
	{
		cy =mrangx->GetRangeLO();
	}

	midcopy(input,output,cx,cy);
}

// create a list from string data
void createstrlist(char* buff,char* search,MasStrList* list)
{
	int occ;
	occ = findoccourance(buff,search);

	if(occ == -1)
	{
		return; // failure
	}
	list->create(occ);

	int occ_i = 0;

	MasStrDataLoc dloc;

	if(findstrloc(buff,search,&dloc))
	{
		int pre_pos = 0;

		for(int z = 0; z < dloc.getmaxpoint(); z++)
		{
			int cur = 0;
			cur = dloc.dindex[z];
			charwrap cwrap(buff);
			cwrap.strclearn();
			midcopy(buff,cwrap.get(),pre_pos,cur);
			list->strings[occ_i].set(cwrap.get());
			occ_i++;
			pre_pos = cur;
		}

		charwrap cwrapx(buff,true);
		rightcopy(buff,cwrapx.get(),pre_pos);
		list->strings[occ_i].set(cwrapx.get());
		occ_i++;
		}

	return;
}
// conversion of integers
void convertinteger(int integer,char* buff,int base)
{
	itoa(integer,buff,base);
}
// conversion of strings
int convertstring(char* buff)
{
	return atoi(buff);
}
// could this be a hexidecimal digit?
bool ishexc(char c)
{
	c = lcasel(c);
	switch(c)
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
		return true;
		break;
	}
	return false;
}
// does this string contain a non-hexidecimal digit?
bool ishex(char* buff)
{
	int len;
	len = strlen(buff);

	for(int i = 0; i < len; i++)
	{
		if(ishexc(buff[i]) == false)
		{
			return false;
		}
	}
	return true;
}

// hexidecimal digit to integer value
int hextointc(char c)
{
	if(ishexc(c) == false)
	{
		return -1; // failure, not a hex digit
	}

	c = lcasel(c);

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
		return 11;
	case 'c':
		return 12;
	case 'd':
		return 13;
	case 'e':
		return 14;
	case 'f':
		return 15;
	}

	return -1; // failure ? never would get here
}

// convert hex value into a integer
int hextoint(char* buff)
{
	int rt = 0;

	if(buff[1] == 0)
	{
		return hextointc(buff[0]);
	}

	int len = strlen(buff);
	int* hexval;
	hexval = new int[len+1];
	int  hexvali = 0;

	for(int i = 0; i < len; i++)
	{
		hexval[hexvali] = hextointc(buff[i]);
		hexvali++;
	}

    int index = 0;

	for(int z = hexvali-1; z >= 0; z--)
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

	delete [] hexval;

	return rt;
} 


void tripcharup(char* buff, int up)
{
	int len;
	len = strlen(buff);

	for(int i = 0; i < len; i++)
	{
		if(buff[i] != 0)
		{

		buff[i] = buff[i] + up;

		}
	}
}

void tripchardown(char* buff,int up)
{
	int len;
	len = strlen(buff);

	for(int i = 0; i < len; i++)
	{
		if(buff[i] != 0)
		{

		buff[i] = buff[i] - up;

		}
	}
}
// replace single instance of a character
void replacechar(char* buff,char findchr,char replace)
{
	int len;
	len = strlen(buff);

	for(int z = 0; z < len; z++)
	{
		if(buff[z] == findchr)
		{
			buff[z] = replace;
		}
	}
}

void rmvinst(char* buff,char* findstr,char* replacex,char* output)
{

	int xt = ifindstr(NOPREV,buff,findstr);


	char* temp;
	temp = new char[strlen(buff)+1];
	stringcopy(temp,buff);

	char* ltemp;
	char* rtemp;

	ltemp = new char[strlen(buff)+1];
	rtemp = new char[strlen(buff)+1];

	leftcopy(buff,ltemp,xt);
	rightcopy(buff,rtemp,xt+strlen(findstr));


	cout << "\n#: " << ltemp << replacex << rtemp << endl;

	
	strcpy(output,ltemp);
	strcat(output,replacex);
	strcat(output,rtemp);

	delete [] temp;
	delete [] ltemp;
	delete [] rtemp;
}


// replace string
void replacestr(char* buff,char* findstr,char* replacex,char* output)
{
	int xt;
	xt = ifindstr(0,buff,findstr);

	if(xt == -1)
	{
		return; // failure no string to replace
	}

	char* ptemp;
	char* outtemp;
	ptemp = new char[strlen(buff) + 500];
	outtemp = new char[strlen(buff) + 500];
	stringcopy(ptemp,buff);

	while(1)
	{
		int xr;
		xr = ifindstr(0,ptemp,findstr);
		if(xr == -1)
		{
			break;
		}
		else
		{
			rmvinst(ptemp,findstr,replacex,outtemp);
			stringcopy(ptemp,outtemp);
		}
	}

	stringcopy(output,ptemp);

	delete [] ptemp;
	delete [] outtemp;

}

// random char
char randomchar(int max)
{
	int x;
	x = rand()%max;
	char c;
	c = x;
	return c;
}
// random char + up
char randomchar(int max,int up)
{
	int x;
	x = rand()%max+up;
	char c;
	c = x;
	return c;
}
// random string
void randomstr(char* buff,int max, int size)
{
	for(int i = 0; i < size; i++)
	{
		if(rand()%2)
		{
			buff[i] = randomchar(max);
		}
		else
		{
			buff[i] = randomchar(max,rand()%10);
		}
	}
}
// remove char
void removechar(char* in,char* out,char c)
{
	int len;
	len = strlen(in);
	int ic = 0;
	for(int i = 0; i < len; i++)
	{
		if(in[i] != c)
		{
			out[ic] = in[i];
			ic++;
		}
	}
	out[ic] = 0;
}

// find single character in string
int findchar(char* str,char c)
{
	int len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1; // failure
}
// find char ex (inside)
int ifindchar(int start,char* str,char c)
{
	int len = strlen(str);
	for(int i = start+1; i < len; i++)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1;
}
// find single char backward
int findcharb(char* str,char c)
{
	int len;
	len = strlen(str);
	for(int i = len; i > 0; i--)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1;
}
// find single char backward
int ifindcharb(int start,char* str,char c)
{
	int len;
	len = strlen(str);
	for(int i = start-1; i > 0; i--)
	{
		if(str[i] == c)
		{
			return i;
		}
	}
	return -1;
}

int  findcharcf(char* str,int start,int stop,char c)
{
	for(int i = start; i < stop; i++)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1; // failure
}
int  findcharcb(char* str,int start,int stop,char c)
{
	for(int i = stop; i > start; i--)
	{
		if(str[i] == c)
		{
			return i;
		}
	}
	return -1;// failure
}
// remove instances of string
void removestr(char* input,char* output,char* string)
{

	char* buff = input;
	char* findstr = string;

	int xt;
	xt = ifindstr(NULLPOS,buff,findstr);

	if(xt == -1)
	{
		return; // failure no string to replace
	}

	char* ptemp;
	char* outtemp;
	ptemp = new char[strlen(buff) + 500];
	outtemp = new char[strlen(buff) + 500];
	stringcopy(ptemp,buff);

	while(1)
	{
		int xr;
		xr = ifindstr(0,ptemp,findstr);
		if(xr == -1)
		{
			break;
		}
		else
		{
			rmvstrx(ptemp,findstr,outtemp);
			stringcopy(ptemp,outtemp);
		}
	}

	stringcopy(output,ptemp);

	delete [] ptemp;
	delete [] outtemp;

}

void rmvstrx(char* buff,char* output,char* string)
{
	int xt = ifindstr(NOPREV,buff,string);

	char* temp;
	temp = new char[strlen(buff)+1];
	stringcopy(temp,buff);

	char* ltemp;
	char* rtemp;

	ltemp = new char[strlen(buff)+1];
	rtemp = new char[strlen(buff)+1];

	leftcopy(buff,ltemp,xt);
	rightcopy(buff,rtemp,xt+strlen(string));
	
	strcpy(output,ltemp);
	strcat(output,rtemp);

	delete [] temp;
	delete [] ltemp;
	delete [] rtemp;
}

void strsavefile(char* filename,char* buff)
{
	ofstream fout(filename);

	fout << buff;

	fout.close();
}

int getfilestringlength(char* filename)
{
	int count = 0;
	ifstream fin(filename);
	if(fin)
	{
		char ch;
		while(fin.get(ch))
		{
			count++;
		}

		fin.close();
		return count;

	} else { return -1; } // failure

	return -1;
}

bool strloadfile(char* file,char* output)
{
	int count = 0;
	ifstream fin(file);
	if(fin)
	{
		char ch;
		int str_i = 0;
		while(fin.get(ch))
		{
			output[str_i] = ch;
			str_i++;
		}

		output[str_i] = 0;
		return true;
	}
	else
	{
		return false;
	}

	return false;
}

void reversestring(char* input,char* output)
{
	int len;
	len = strlen(input);
	int fcount = 0;

	for(int i = len; i > 0; i--)
	{
		output[fcount] = input[i];
		fcount++;
	}
	
	output[fcount] = 0;
}

bool isstrvalid(char* string)
{
	int len = strlen(string);
	for(int i = 0; i < len; i++)
	{
		if(string[i] == 0)
		{
			return true; // true it is a null terminated string!
		}
	}

	return false;
}

// Save Master INI
bool SaveMasterINI(char* filename,MasterINI* mini)
{
	ofstream fout(filename,ios::binary);

	if(fout)
	{


	fout.write((char*)&mini,sizeof(mini));

	fout.close();

	return true;

	}
	fout.close();
	return false;
}
// Load master INI
bool LoadMasterINI(char* filename,MasterINI* mini)
{
	ifstream fin(filename,ios::binary);

	if(fin)
	{
		fin.read((char*)&mini,sizeof(mini));
	}
	
	fin.close();
	return false;
}

// string compare (case sensitive)
bool mstrcmp(char* buff1,char* buff2)
{
	int len;
	int len2;
	len = strlen(buff1);
	len2 = strlen(buff2);

	if(len != len2)
	{
		return false; // not equal length
	}

	for(int i = 0; i < len; i++)
	{
		if(buff1[i] != buff2[i])
		{
			return false;
		}
	}

	return true;
}

// string compare (not case sensitive)
bool mstrcmpx(char* buff1,char* buff2)
{
	int len;
	int len2;
	len = strlen(buff1);
	len2 = strlen(buff2);

	if(len != len2)
	{
		return false; // not equal length
	}

	for(int i = 0; i < len; i++)
	{
		if(tolower(buff1[i]) != tolower(buff2[i]))
		{
			return false;
		}
	}

	return true;
}

bool insidestr(char* buff1,char* buff2)
{
	int chk;
	chk = findstr(buff1,buff2);

	if(chk == -1)
	{
		return false;
	}
	
	return true;
}

bool insidestrx(char* buff1,char* buff2)
{
	char* pbuff1;
	char* pbuff2;

	pbuff1 = new char[strlen(buff1)+1];
	pbuff2 = new char[strlen(buff2)+1];

	stringcopy(pbuff1,buff1);
	stringcopy(pbuff2,buff2);

	lcase(pbuff1);
	lcase(pbuff2);

	int chk;
	chk = findstr(pbuff1,buff2);

	delete [] pbuff1;
	delete [] pbuff2;
	pbuff1 = 0;
	pbuff2 = 0;

	if(chk == -1)
	{
		return false;
	}
	
	return true;
}
// string seperation from 2 points
void strsep(char* str, char* sleft, int go_left, char* sright, int go_right)
{
	leftcopy(str,sleft,go_left);
	rightcopy(str,sright,go_right);
}
void strsetnull(char* str,int pos)
{
	str[pos] = 0;
}

void rmvnullset(char* str)
{
	int len;
	len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		if(str[i] == 0)
		{
			str[i] = ' ';
		}
	}
}

int getnullpos(char* str)
{
	int len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		if(str[i] == 0)
		{
			return i;
		}
	}

	return -1; // failure to find 0
}
// trim commented characters () 
void trimcom(char* str, char* output,char start_c,char stop_c)
{
	int len = strlen(str);
	int index = 0;

	bool iadd = true;

	for(int z = 0; z < len; z++)
	{
		if(str[z] == start_c)
		{
			iadd = false; 
		}

		if(str[z] == stop_c)
		{
			iadd = true;
		}

		if(iadd == true)
		{
			output[index] = str[z];
			index++;
		}
	}
	
	output[index] = 0;
}

// trim comments to an assembly language source file
void asmtrim(char* input,char* output)
{
	trimcom(input,output,';','\n');
}

// count the number of lines exisitng within the source
int countlines(char* buffer)
{
	return findoccourance(buffer,"\n");
}
// get the first letter thats not a space
int getfirstletter(char* buff)
{
	int len = strlen(buff);
	
	for(int i = 0; i < len; i++)
	{
		if(buff[i] != ' ')
		{
			return i;
		}
	}
	return -1; // failure! no letters
}

#endif


// =]