/*

  MasterX API - Encapsulation of DirectX 
                640x480 Video Game Encapsulation
				                   Required Librarys
				          DirectDraw (library) ddraw.lib
						        DirectSound (library) dsound.lib
								     DirectInput (library) dinput.lib
									       extra: dxguid.lib


  MasterXHWND - Master DirectX Window Object
  MasterAnimiation - Animated Object
  MasterXRCGraphic - Graphic Scence
  MasterText  - Manual Text
  playsound   - Direct Sound
  initjoy     - direct input (joystick)

	MasterOnLSD

    im me on aim:  master on LSD

*/


#ifndef _MASTERX_H_
#define _MASTERX_H_

#define MAX_SURF 250
#define JOY_DEADZONE 20
#define J_LEFT 45
#define J_RIGHT 55
#define J_FORWARD 56
#define J_BACKWARD 57
#define J_B1  1
#define J_B2  2
#define J_B3  3
#define J_B4  4
#define LEMPTY "NULL"
#define FEMPTY "NULL"
#define STRNULL "NULL"
#define NULLSTR "NULL"
#ifndef _DDRAW_H_
#include <ddraw.h>
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>


#endif


struct MasterScreen
{
	LPDIRECTDRAW lpDD;
	LPDIRECTDRAWSURFACE lpBack;
	LPDIRECTDRAWSURFACE lpFront;

	MasterScreen();
	~MasterScreen();
};

struct MasterMessage
{

	IDirectDraw* lpDD;
	IDirectDrawSurface* lpBack;
	IDirectDrawSurface* lpFront;
	
	int screen;
	bool restore;
	
};

class MasterGraphic
{
public:

	LPDIRECTDRAWSURFACE surf;
	void loadgraphic(char*,MasterScreen);
};

struct XRCList
{
	char filename[50];
	LPDIRECTDRAWSURFACE surf;
	bool colorkey;
	int x;
	int y;
	int w;
	int h;
	bool on;
};
// Auto-Reload/Auto Sized Graphic Package (scenes, individual image)
typedef class MasterXRCGraphic
{
    XRCList list[MAX_SURF];
	int getoffgraphic();
public:

	void addgraphic(char* filename,MasterScreen scr, int x, int y);
	void setcolorkey(char* filename, COLORREF rgb);
	void restoregraphic(MasterScreen);
	void removegraphic(char* filename);
	void displaygraphics(MasterScreen scr);
    void displaygraphic(MasterScreen,char*,int x, int y);
	void setgraphicpos(char* filename, int x, int y, bool on);
	MasterXRCGraphic();
	~MasterXRCGraphic();
}GraphicLayer,GraphicList, Graphic_List_Object_ZX69;
// for every update, clip all images, (has  a restore 2)
// instead of a single graphic; can pass it a grahpiclist

typedef class AnimatedGraphic
{
	XRCList list[MAX_SURF];

	int index;
	bool iplay;
	int time;
	int getoffgraphic();
public:

	void restoregraphic(MasterScreen);
	void clear();
	void add(char* filename,MasterScreen);
	void addi(char* filename,MasterScreen, int i);
	void rmv(char* filename);
    void setcolorkey(char* filename, COLORREF rgb);
	bool play(MasterScreen,int x, int y, int start, int stop);
	bool playatspeed(MasterScreen,int x,int y, int start, int stop, int speed);
    void reset();
	~AnimatedGraphic();
}MasterAnimation;

typedef class MGraphic
{
	
	char filename[50];
	MasterScreen scr;
    bool colorkey;
	void restoremgraphic();
	int mx;
	int my;
	bool on;
public:

	LPDIRECTDRAWSURFACE surf;

	void setcolorkey(COLORREF);
	void killcolorkey();
	void loadgraphic(char* filename,MasterScreen);
	void setsurface(LPDIRECTDRAWSURFACE surf,MasterScreen scr,int mx,int my);
	void displaygraphic(int x,int y,int w,int h);
	void displaygraphic(int x, int y);
	MGraphic();
	~MGraphic();

}SingleGraphic, MasGraphic,mgraphic,MasterXGraphic,MXG;


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
	void printtext(char*,int x,int y);
	void printtextunderline(char*, int x, int y);
	void printtextrect(char*, int x, int y, int w, int h);
	void setdefaultfont();

};


class MasterXHWND
{

	bool setprimarysurface();
	bool initSound();
	void initInput();
	int  curscreen;
public:

	
	HWND hwndx;

	// DirectX INPUT
	IDirectInput		*pDI;
    IDirectInputDevice	*pKeyboard;


	void destroy();
	int getcurscreen();
	DDBLTFX ddbltfx;
	IDirectSoundBuffer *pSoundx;

	// Joy Stick Information

	JOYINFOEX joystickInfoEx;
    JOYCAPS joystickCaps;
    bool GetJoyPressed();
	void SetJoyPressed(bool);
	bool getbdown();
	bool joystickPresent;
    bool joystickHasThrottle;
    bool joystickActive;
    bool iJoy;
    bool j_pressed;
    bool b_down;
    UINT joystickDeadXMin, joystickDeadXMax, joystickDeadYMin, joystickDeadYMax;

	bool TheCords(JOYINFOEX* info);
    void JoyStickCheck();
    bool JoyForward();
    bool JoyBackward();
    bool JoyLeft();
    bool JoyRight();
    bool JoyStop();
    int BPressed(JOYINFOEX* info);



	bool joyinit();
	void init2(HWND);

	// masterx graphic stuff // 
	void mxdrawrect(int x, int y, int x2, int y2,COLORREF fill,COLORREF outline);
	void mxdrawroundrect(int x, int y, int x2, int y2,int cw, int ch, COLORREF fill,COLORREF outline);
	void mxdrawpie(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2,COLORREF fill, COLORREF outline);
	void mxdrawchord(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2, COLORREF fill, COLORREF outline);
	void mxdrawellipse(int x, int y, int x2, int y2,COLORREF fill,COLORREF outline);
	HRESULT mxbltsurf(LPDIRECTDRAWSURFACE, int x, int y, int w, int h,bool key);


	// Sound Informatoin

	// --
    IDirectSound	*pDS;//sound

	void playsound(int id);
	// Graphic Informatoin
	void setscreen(int);
	bool addgraphic(char*,int,int,int,int);
	bool addgraphic(HBITMAP,int x, int y);
	 // clip graphics
    MasterText    text;   //  clip text
	// -- 
	MasterScreen* scr;
	
	// Init
	bool init(HWND);
	
	// ** Paint **//
	void clear();
	void update(); //set shit; then update (update /flip)
	
	MasterXHWND();
	~MasterXHWND();
	

};

//Graphics
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



#endif
