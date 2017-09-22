#pragma once
#define WIN32_LEAN_AND_MEAN
#include<windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#define DIRECTINPUT_VERSION 0x0800
#include<dinput.h>
#include <mmsystem.h>
#include <mmreg.h>
#include <dsound.h>
#include<stdarg.h>
#include<stdio.h>
#include<time.h>

// globals for mxJoystick
extern LPDIRECTINPUTDEVICE8 p_joy;
extern LPDIRECTINPUT8 pdi;


inline void memsetDWORD(void *dest, DWORD data, int count)
{
	_asm 
	{ 
		mov edi, dest   ; edi points to destination memory
		mov ecx, count  ; number of 16-bit words to move
		mov eax,  data   ; 16-bit data
		rep stosw       ; move data
	}
} 
inline void ErrorMsg(const char *str, ...) {
	char text[5000];
	va_list list;
	va_start(list, str);
	vsprintf((char*)text,str,list);
	va_end(list);
	MessageBox(GetForegroundWindow(),text,"Error !",MB_OK | MB_ICONERROR );
}

template<class type>
inline void SafeFree(type t) {
	if(t) {
		t->Release();
		t = 0;
	}
}

inline void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

inline void Swap(float& a, float& b)
{
	float temp = a;
	a = b;
	b = temp;
}

inline void Swap(float &a, float &b, float &temp) {
	temp = a;
	a = b;
	b = temp;
}

inline void Swap(int &a, int &b, int &temp) {
	temp = a;
	a = b;
	b = temp;
}

struct mxScreen {
	LPDIRECT3D9 pd3d;
	LPDIRECT3DDEVICE9 pd3d_dev;
	LPDIRECT3DSURFACE9 pback;
	int w,h;
	mxScreen() {
		pd3d = 0;
		pd3d_dev = 0;
		pback = 0;
	}
	RECT scr_rc;
	~mxScreen();
};

class mxText  {
	mxScreen *mxscr;
	LPD3DXFONT pfont;
	D3DCOLOR color;
public:
	void Init(mxScreen *mscr) {
		this->mxscr = mscr;
		if(FAILED(D3DXCreateFont( mxscr->pd3d_dev, -12, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pfont ) ) ) {
			ErrorMsg("Error Couldnt create font");
		}
		color = D3DCOLOR_XRGB(255,0,0);
	}

	void settextcolor(D3DCOLOR color) {
		this->color = color;
	}

	void setfont(HFONT hfont) {
		char fnt_name[255];
		HDC dc = GetDC(GetForegroundWindow());
		HFONT prev_font = (HFONT) SelectObject(dc,(HFONT)hfont);
		GetTextFace(dc,LF_FULLFACESIZE,fnt_name);
		TEXTMETRIC textmetric;
		GetTextMetrics (dc, &textmetric) ;
		if(pfont) {
			SafeFree<LPD3DXFONT>(pfont);
		}
		if(FAILED(D3DXCreateFont( mxscr->pd3d_dev, textmetric.tmHeight, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, fnt_name, &pfont ) ) ) {
			ErrorMsg("Error Couldnt create font");
		}

		SelectObject(dc,prev_font);

	}

	void printtextf(int x, int y, const char *str, ...) {
		mxscr->pd3d_dev->BeginScene();
		RECT rc = {x,y,0,0};
		char text[5000];
		va_list list;
		va_start(list, str);
		vsprintf((char*)text,str,list);
		va_end(list);
		pfont->DrawText(NULL,text,-1,&rc,DT_NOCLIP,color);
		mxscr->pd3d_dev->EndScene();
	}

	mxText()  { pfont = 0; }
	~mxText() { SafeFree<LPD3DXFONT>(pfont); }
};


class mxSprite {
	mxScreen *mxscr;
	D3DCOLOR color_key;
public:
	LPDIRECT3DTEXTURE9 tex;
	LPD3DXSPRITE sprite;
	int w,h;
	void init(mxScreen *mxscr) {
		this->mxscr = mxscr;
		w = h = 0;
	}

	void setcolorkey(D3DCOLOR color_key) {
		this->color_key = color_key;
	}

	bool load(const char *source) {
		/*if(FAILED(D3DXCreateTextureFromFileEx(mxscr->pd3d_dev, source, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, color_key, NULL, NULL, &tex))) {
			ErrorMsg("Error couldnt load texture!\n");
			return false;
		}*/
    if(FAILED(D3DXCreateTextureFromFileEx(mxscr->pd3d_dev, source,
                                          D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT_NONPOW2,
                                          1,
                                          0,
                                          D3DFMT_UNKNOWN,
                                          D3DPOOL_MANAGED,
                                          D3DX_FILTER_NONE,D3DX_FILTER_NONE,
                                          color_key,
                                          NULL,NULL,
                                          &tex)))
										  return false;

		/*if(FAILED(D3DXCreateTextureFromFile(mxscr->pd3d_dev,source,&tex)))
			return false;*/

			
		if(FAILED(D3DXCreateSprite(mxscr->pd3d_dev,&sprite))) {
			ErrorMsg("Error couldnt load sprite!\n");
			return false;
		}
		D3DSURFACE_DESC surface_desc;
		tex->GetLevelDesc(0, &surface_desc);
		w = surface_desc.Width;
		h = surface_desc.Height;
		return true;

	}

	void display(float x, float y) {
		D3DXVECTOR3 pos;
		pos.x=x;
		pos.y=y;
		pos.z=0.0f;
		if(sprite) {
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(tex,NULL,NULL,&pos,0xFFFFFFFF);
		sprite->End();
		}
	}

	void display_scale(float x, float y, float scale_x, float scale_y, float rotation) {
		D3DXVECTOR3 pos;
		pos.x=x;
		pos.y=y;
		pos.z=0.0f;
		if(sprite) {
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXVECTOR2 sprite_center =D3DXVECTOR2(0.0f,0.0f);
		D3DXVECTOR2 trans=D3DXVECTOR2(x,y);
		D3DXMATRIX mat;
		D3DXVECTOR2 scaling(scale_x,scale_y);
		D3DXMatrixTransformation2D(&mat,NULL,0.0,&scaling,NULL,rotation,&trans);
		sprite->SetTransform(&mat);
		sprite->Draw(tex,NULL,NULL,NULL,0xFFFFFFFF);
		sprite->End();
		}

	}

	void display_ex(float x, float y, int x1, int y1, int x2, int y2, float scale_x, float scale_y, float rotation) {
		D3DXVECTOR3 pos;
		pos.x=x;
		pos.y=y;
		pos.z=0.0f;
		RECT rc = { x1,y1,x2,y2 };
		if(sprite) {
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXVECTOR2 trans=D3DXVECTOR2(x,y);
		D3DXMATRIX mat;
		D3DXVECTOR2 scaling(scale_x,scale_y);
		//D3DXMatrixTransformation2D(&mat,0,0.0,&scaling,NULL,rotation,&trans);
		//sprite->SetTransform(&mat);
		sprite->Draw(tex,&rc,NULL,&pos,0xFFFFFFFF);
		sprite->End();
		}
	}

	mxSprite() {
		tex = 0;
		sprite = 0;
		color_key = 0;
	}
	~mxSprite() {
		SafeFree<LPDIRECT3DTEXTURE9>(tex);
		SafeFree<LPD3DXSPRITE>(sprite);
	}
};

class mxPaint  {
public:
	mxScreen *mxscr;
	D3DLOCKED_RECT rect;
	DWORD *data;
	void init(mxScreen *mxscr) {
		this->mxscr = mxscr;
		data = 0;
		max_clip_x = mxscr->w;
		max_clip_y = mxscr->h;
		min_clip_x = min_clip_y = 0;
	}
	int max_clip_x, min_clip_x, max_clip_y, min_clip_y;
	void __fastcall Lock();
	void __fastcall UnLock();
	void __fastcall fast_sp(int x, int y, int pitch, D3DCOLOR color);
	void __fastcall setpixel(int x, int y, D3DCOLOR color);
	DWORD __fastcall fast_gp(int x, int y);
	void __fastcall drawrect(int x, int y, int w , int h, D3DCOLOR color);
	// slow gdi functions
	void __fastcall drawroundrect(int x, int y, int w, int h,int ch, int cw, COLORREF color, COLORREF out_color);
	void __fastcall drawpie(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2, COLORREF fill,COLORREF outline);
	void __fastcall drawchord(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2,COLORREF fill,COLORREF outline);
	void __fastcall drawellipse(int x, int y, int x2, int y2,COLORREF fill,COLORREF outline);
	void __fastcall drawpolygon(CONST POINT* point,int n_points,COLORREF fill,COLORREF outline);
	void __fastcall drawanglearc(int x, int y, long radius, float startangle,float sweepangle,COLORREF fill,COLORREF outline);
	void __fastcall drawarc(int x1, int x2, int x3, int x4,int x5, int x6,int x7, int x8,COLORREF fill,COLORREF outline);
	void __fastcall drawlineto(int x, int y,COLORREF fill,COLORREF outline);
	void __fastcall drawpixel(int x, int y, COLORREF color);
	COLORREF __fastcall drawgetpixel(int x, int y);
	void __fastcall drawline(int start_x, int start_y, int stop_x, int stop_y,D3DCOLOR color);
	void __fastcall drawtoptri(int x1, int y1, int x2, int y2, int x3, int y3, D3DCOLOR color);
	void __fastcall drawgentri(int x1, int y1, int x2, int y2, int x3, int y3, D3DCOLOR color);
	void __fastcall drawtoptri2(float x1, float y1, float x2, float y2, float x3, float y3, D3DCOLOR color);
	void __fastcall drawbottomtri2(float x1, float y1, float x2, float y2, float x3, float y3, D3DCOLOR color);
	void __fastcall drawtri2(float x1, float y1, float x2, float y2, float x3, float y3, D3DCOLOR color);
	void __fastcall drawbottomtri(int x1, int y1, int x2, int y2, int x3, int y3, D3DCOLOR color);
	void __fastcall drawtri(int x1, int y1, int x2, int y2, int x3, int y3, D3DCOLOR color);
	void __fastcall filltri(POINT &p1, POINT &p2, POINT &p3, D3DCOLOR color);
	void __fastcall drawhline(int x, int x2, int y, D3DCOLOR color);
};

class mxKeyboard {
public:
	LPDIRECTINPUTDEVICE8 key_dev;
	char keys[256];

	void Init(LPDIRECTINPUT8 pdi,HWND hwnd) {
		HRESULT rt = pdi->CreateDevice(GUID_SysKeyboard,&key_dev,NULL);
		if(FAILED(rt)) {
			ErrorMsg("Error couldnt create the keyboard device.");
			return;
		}

		if(FAILED(key_dev->SetDataFormat(&c_dfDIKeyboard))) {
			ErrorMsg("Couldnt set the data format!\n");
			return;
		}

		if(FAILED(key_dev->SetCooperativeLevel(hwnd,DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))) {
			ErrorMsg("Failed to set cooperative level!\n");
			return;
		}
	}

	void Clear() {
		memset((void*)keys,0,sizeof(char)*256);
	}

	void Free() {
		if(key_dev)
			key_dev->Unacquire();
		SafeFree<LPDIRECTINPUTDEVICE8>(key_dev);
	}

	bool KeyCheck(int key) {
		if(keys[key] & 0x80) {
			return true;
		}
		return false;
	}

	void Update() {
		char new_state[256];
		HRESULT rt = key_dev->Poll();
		memset(new_state,0,sizeof(new_state));
		rt = key_dev->GetDeviceState(sizeof(new_state),(void*)&new_state);
		if(FAILED(rt)) {
			rt = key_dev->Acquire();
			if(FAILED(rt)) {
				OutputDebugString("Failed to aquire keyboard.\n");
				return;
			}
			rt = key_dev->Poll();
			rt = key_dev->GetDeviceState(sizeof(new_state),(void*)&new_state);
			if(FAILED(rt)) { 
				OutputDebugString("Failed to get Device State.\n");
				return;
			}
		}
		memcpy(keys,new_state,256);

	}
};



extern bool joy_exisits;
extern char joy_name[256];

class mxJoystick {

public:
	DIJOYSTATE2 joy_st;
	

	void Init(HWND hwnd, LPDIRECTINPUT8 pdix) {
		pdi = pdix;

		pdi->EnumDevices( DI8DEVCLASS_GAMECTRL,Enum,NULL, DIEDFL_ATTACHEDONLY );
		if(p_joy == 0) {
			OutputDebugString("Joystick Not Found!.\n");
			return;
		}
		HRESULT rt = p_joy->SetDataFormat( &c_dfDIJoystick2 );
		rt = p_joy->SetCooperativeLevel( hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND );
		if(FAILED(rt)) {
			OutputDebugString("Error setting of cooperative level for joystick failed!.\n");
			return;
		}

		rt = p_joy->EnumObjects( EnumObjects,(VOID*)hwnd, DIDFT_ALL );
		if(FAILED(rt)) {
			OutputDebugString("FAILED to enumObjects\n");
			return;
		}
	}

	void Update() {
		if(p_joy == 0)
			return;
		HRESULT rt = p_joy->Poll();
		if(FAILED(rt)) {
			p_joy->Acquire();
			while( rt == DIERR_INPUTLOST ) 
				rt = p_joy->Acquire();

			return;
		}
		rt = p_joy->GetDeviceState( sizeof(DIJOYSTATE2), &joy_st );
		if(FAILED(rt)) {
			return;
		}

	}

	void Free() {
		if(p_joy) {
			SafeFree<LPDIRECTINPUTDEVICE8>(p_joy);
		}
	}

	static BOOL CALLBACK Enum(const DIDEVICEINSTANCE *joy_inst, VOID *context) {
		HRESULT hr = pdi->CreateDevice( joy_inst->guidInstance, &p_joy, NULL );
		if(FAILED(hr)) {
			return DIENUM_CONTINUE;
		}
		else {
			strcpy(joy_name,joy_inst->tszProductName);
			joy_exisits = true;
		}

		return DIENUM_STOP;
	}

	static BOOL CALLBACK EnumObjects(const DIDEVICEOBJECTINSTANCE* dioi, VOID* context) {

		if( dioi->dwType & DIDFT_AXIS )
		{
			DIPROPRANGE diprg; 
			diprg.diph.dwSize       = sizeof(DIPROPRANGE); 
			diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
			diprg.diph.dwHow        = DIPH_BYID; 
			diprg.diph.dwObj        = dioi->dwType; 
			diprg.lMin              = -1000; 
			diprg.lMax              = +1000; 

			if( FAILED(p_joy->SetProperty( DIPROP_RANGE, &diprg.diph ) ) ) 
				return DIENUM_STOP;
		}

		return DIENUM_CONTINUE;
	}
};


class mxMouse {

	LPDIRECTINPUTDEVICE8 mo_dev;

public:
	DIMOUSESTATE mo_st;
	POINT cur_pos;

	void Init(HWND hwnd, LPDIRECTINPUT8 pdi) {
		HRESULT rt = pdi->CreateDevice( GUID_SysMouse,&mo_dev, NULL );
		if(FAILED(rt)) {
			ErrorMsg("Error couldnt create mouse device!\n");
			return;
		}
		rt = mo_dev->SetDataFormat(&c_dfDIMouse);
		if(FAILED(rt)) {
			ErrorMsg("Couldnt set the mouse data format!\n");
			SafeFree<LPDIRECTINPUTDEVICE8>(mo_dev);
			return;
		}

		rt = mo_dev->SetCooperativeLevel( hwnd, DISCL_NONEXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND );
		if(FAILED(rt)) {
			ErrorMsg("Couldnt set the coorperative level!\n");
			SafeFree<LPDIRECTINPUTDEVICE8>(mo_dev);
		}

		mo_st.lX = mo_st.lY = mo_st.lZ = 0;
		mo_st.rgbButtons[0] = 0;
		mo_st.rgbButtons[1] = 0;
		mo_st.rgbButtons[2] = 0;
		//GetCursorPos(&cur_pos);
	}

	void Free() {
		if(mo_dev) {
			mo_dev->Unacquire();
			SafeFree<LPDIRECTINPUTDEVICE8>(mo_dev);
		}
	}

	void Update() {
		DIMOUSESTATE cur_st;
		HRESULT hr = mo_dev->Poll();
		hr = mo_dev->GetDeviceState( sizeof(DIMOUSESTATE),(void*)&cur_st );
		if(FAILED(hr)) {
			hr = mo_dev->Acquire();
			if(FAILED(hr)) {
				OutputDebugString("Error Aquire of Mouse Failed.\n");
				return;
			}

			hr = mo_dev->Poll();
			hr = mo_dev->GetDeviceState( sizeof(DIMOUSESTATE),(void*)&cur_st );
		}

		if(cur_st.lX || cur_st.lY) {
			mo_st = cur_st;
			GetCursorPos(&cur_pos);
		}


	}

};
class mxInput  {
public:
	LPDIRECTINPUT8 pdi;
	mxKeyboard key;
	mxMouse mouse;
	void Init(HWND hwnd) {
		HRESULT rt;
		rt = DirectInput8Create(GetModuleHandle(0),DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&pdi,NULL);
		if(FAILED(rt)) {
			ErrorMsg("Error DirectInput could not be initialized\n");
			return;
		}

		key.Init(pdi,hwnd);
		mouse.Init(hwnd,pdi);
	}

	void Free() {
		key.Free();
		mouse.Free();
		SafeFree<LPDIRECTINPUT8>(pdi);
	}

	void Update() {
		key.Update();
		mouse.Update();
	}

};

class mxHwnd {
protected:
	int cur_screen;
	bool go;
public:
	HWND hwnd;
	WPARAM active;
	int w,h;
	mxScreen screen;
	mxText text;
	mxPaint paint;
	mxInput input;
	unsigned long ticks;

	mxHwnd( const char *title, int x, int y, int w , int h, bool fullscreen , WNDPROC WndProc, HICON hIcon);
	mxHwnd();
	bool Init(const char *title,bool full, int x, int y, int w , int h , WNDPROC WndProc, HICON hIcon);
	bool InitDX(bool,int);
	int  InitLoop(void (*render)(int screen));
	LPDIRECT3DSURFACE9 GetBackSurf() { return screen.pback; }
	void Kill() { go = false; }
	void SetScreen(int scr) { this->cur_screen = scr; }
	int  GetScreen() { return this->cur_screen; }
	void SetTicks() { ticks = GetTickCount(); }
	void WaitTicks(unsigned long ticks) { while(GetTickCount() - this->ticks < ticks); }

};


class mxApp : public mxHwnd  {
public:
	virtual void init() = 0;
	virtual void render(int screen) = 0;
	int InitLoop();
};

extern LPDIRECTSOUND8 m_pDS;
extern LPDIRECTSOUND3DLISTENER g_pDSListener; 
// from Microsoft SDK examples
class mxSound {
private:
	DS3DLISTENER g_dsListenerParams;
public:
	mxSound(HWND hwnd) {
		Init(hwnd);
	}
	mxSound() {

	}
	~mxSound()
	{
		if(g_pDSListener!=NULL)
		{ 
			g_pDSListener->Release(); 
			g_pDSListener=NULL;
		}	

		if(m_pDS!=NULL)
		{ 
			m_pDS->Release(); 
			m_pDS=NULL;
		}
	}

	void Init(HWND hWnd)
	{
		DirectSoundCreate8( NULL, &m_pDS, NULL );
		m_pDS->SetCooperativeLevel( hWnd, DSSCL_PRIORITY );

		DSBUFFERDESC dsbd;
		ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
		dsbd.dwSize        = sizeof(DSBUFFERDESC);
		dsbd.dwFlags       =   DSBCAPS_PRIMARYBUFFER|DSBCAPS_CTRL3D;
		dsbd.dwBufferBytes = 0;
		dsbd.lpwfxFormat   = NULL;

		LPDIRECTSOUNDBUFFER pDSBPrimary = NULL;
		m_pDS->CreateSoundBuffer( &dsbd, &pDSBPrimary, NULL ) ;

		WAVEFORMATEX wfx;
		ZeroMemory( &wfx, sizeof(WAVEFORMATEX) ); 
		wfx.wFormatTag      = (WORD) WAVE_FORMAT_PCM; 
		wfx.nChannels       =  2; 
		wfx.nSamplesPerSec  = 22050; 
		wfx.wBitsPerSample  = (WORD) 16; 
		wfx.nBlockAlign     = (WORD) (wfx.wBitsPerSample / 8 * wfx.nChannels);
		wfx.nAvgBytesPerSec = (DWORD) (wfx.nSamplesPerSec * wfx.nBlockAlign);

		pDSBPrimary->SetFormat(&wfx);

		if(pDSBPrimary)
		{ 
			(pDSBPrimary)->Release(); 
			(pDSBPrimary)=NULL;
		}	

		DSBUFFERDESC dsbdesc;
		ZeroMemory( &dsbdesc, sizeof(DSBUFFERDESC) );
		dsbdesc.dwSize = sizeof(DSBUFFERDESC);
		dsbdesc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;

		LPDIRECTSOUNDBUFFER pDSBPrimary2 = NULL;
		m_pDS->CreateSoundBuffer( &dsbdesc, &pDSBPrimary2, NULL );
		pDSBPrimary2->QueryInterface( IID_IDirectSound3DListener, (VOID**) &g_pDSListener );


		if(pDSBPrimary2)
		{ 
			(pDSBPrimary2)->Release(); 
			(pDSBPrimary2)=NULL;
		}	

		g_dsListenerParams.dwSize = sizeof(DS3DLISTENER);
		g_pDSListener->GetAllParameters( &g_dsListenerParams );
	}

};

class mxWave
{
private:
	WAVEFORMATEX* m_pwfx;        
	HMMIO         m_hmmio;       
	MMCKINFO      m_ck;          
	MMCKINFO      m_ckRiff;      
	MMIOINFO      m_mmioinfoOut;
	DWORD         m_dwFlags;

	BYTE*         m_pbData;
	BYTE*         m_pbDataCur;
	ULONG         m_ulDataSize;
	CHAR*         m_pResourceBuffer;

	void ResetFile()
	{
		if( m_dwFlags == 1 )
		{
			mmioSeek( m_hmmio, m_ckRiff.dwDataOffset + sizeof(FOURCC),SEEK_SET );
			m_ck.ckid = mmioFOURCC('d', 'a', 't', 'a');
			mmioDescend( m_hmmio, &m_ck, &m_ckRiff, MMIO_FINDCHUNK ) ;
		}
		else
		{
			m_ck.ckid = mmioFOURCC('d', 'a', 't', 'a');
			m_ck.cksize = 0;
			mmioCreateChunk( m_hmmio, &m_ck, 0 ) ;
			mmioGetInfo( m_hmmio, &m_mmioinfoOut, 0 );
		}
	}

	void Read( BYTE* pBuffer, DWORD dwSizeToRead, DWORD* pdwSizeRead )
	{
		MMIOINFO mmioinfoIn; 

		if( pdwSizeRead != NULL )
			*pdwSizeRead = 0;

		mmioGetInfo( m_hmmio, &mmioinfoIn, 0 );                  
		UINT cbDataIn = dwSizeToRead;

		if( cbDataIn > m_ck.cksize ) 
			cbDataIn = m_ck.cksize;       

		m_ck.cksize -= cbDataIn;

		for( DWORD cT = 0; cT < cbDataIn; cT++ )
		{
			if( mmioinfoIn.pchNext == mmioinfoIn.pchEndRead )
				mmioAdvance( m_hmmio, &mmioinfoIn, MMIO_READ );

			*((BYTE*)pBuffer+cT) = *((BYTE*)mmioinfoIn.pchNext);
			mmioinfoIn.pchNext++;
		}

		mmioSetInfo( m_hmmio, &mmioinfoIn, 0 );

		if( pdwSizeRead != NULL )
			*pdwSizeRead = cbDataIn;
	}

	void Close()
	{
		if( m_dwFlags == 1 )
		{
			mmioClose( m_hmmio, 0 );
			m_hmmio = NULL;

			if(m_pResourceBuffer) 
			{ 
				delete[] m_pResourceBuffer; 
				m_pResourceBuffer=NULL; 
			}  
		}
		else
		{
			m_mmioinfoOut.dwFlags |= MMIO_DIRTY;
			mmioSetInfo( m_hmmio, &m_mmioinfoOut, 0 );
			mmioAscend( m_hmmio, &m_ck, 0 );
			mmioAscend( m_hmmio, &m_ckRiff, 0 ) ;
			mmioSeek( m_hmmio, 0, SEEK_SET );
			(INT)mmioDescend( m_hmmio, &m_ckRiff, NULL, 0 );
			m_ck.ckid = mmioFOURCC('f', 'a', 'c', 't');

			if( 0 == mmioDescend( m_hmmio, &m_ck, &m_ckRiff, MMIO_FINDCHUNK ) ) 
			{
				DWORD dwSamples = 0;
				mmioWrite( m_hmmio, (HPSTR)&dwSamples, sizeof(DWORD) );
				mmioAscend( m_hmmio, &m_ck, 0 ); 
			}

			mmioAscend( m_hmmio, &m_ckRiff, 0 );
			mmioClose( m_hmmio, 0 );
			m_hmmio = NULL;
		} 
	}

	void Open( LPTSTR strFileName, WAVEFORMATEX* pwfx, DWORD dwFlags )
	{
		m_dwFlags = dwFlags;

		if( m_dwFlags == 1 )
		{
			if(m_pwfx)
			{ 
				delete[] m_pwfx;
				m_pwfx=NULL;
			}

			m_hmmio = mmioOpen( strFileName, NULL, MMIO_ALLOCBUF | MMIO_READ );

			if( NULL == m_hmmio )
			{
				DWORD   dwSize=0;
				VOID*   pvRes=NULL; 

				m_pResourceBuffer = new CHAR[ dwSize ];
				memcpy( m_pResourceBuffer, pvRes, dwSize );

				MMIOINFO mmioInfo;
				ZeroMemory( &mmioInfo, sizeof(mmioInfo) );
				mmioInfo.fccIOProc = FOURCC_MEM;
				mmioInfo.cchBuffer = dwSize;
				mmioInfo.pchBuffer = (CHAR*) m_pResourceBuffer;

				m_hmmio = mmioOpen( NULL, &mmioInfo, MMIO_ALLOCBUF | MMIO_READ );
			}

			ReadMMIO();
			ResetFile();

			m_ck.cksize = m_ck.cksize;
		}
		else
		{
			m_hmmio = mmioOpen( strFileName, NULL, MMIO_ALLOCBUF  | MMIO_READWRITE | MMIO_CREATE );
			WriteMMIO( pwfx );
			ResetFile();     
		}
	}


	void ReadMMIO()
	{
		MMCKINFO        ckIn;          
		PCMWAVEFORMAT   pcmWaveFormat;    
		m_pwfx = NULL;

		mmioDescend( m_hmmio, &m_ckRiff, NULL, 0 );
		ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend( m_hmmio, &ckIn, &m_ckRiff, MMIO_FINDCHUNK ) ;
		mmioRead( m_hmmio, (HPSTR) &pcmWaveFormat, sizeof(pcmWaveFormat));

		if( pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM )
		{
			m_pwfx = (WAVEFORMATEX*)new CHAR[ sizeof(WAVEFORMATEX) ];
			memcpy( m_pwfx, &pcmWaveFormat, sizeof(pcmWaveFormat) );
			m_pwfx->cbSize = 0;
		}
		else
		{
			WORD cbExtraBytes = 0L;
			mmioRead( m_hmmio, (CHAR*)&cbExtraBytes, sizeof(WORD)) ;
			m_pwfx = (WAVEFORMATEX*)new CHAR[ sizeof(WAVEFORMATEX) + cbExtraBytes ];

			memcpy( m_pwfx, &pcmWaveFormat, sizeof(pcmWaveFormat) );
			m_pwfx->cbSize = cbExtraBytes;

			if( mmioRead( m_hmmio, (CHAR*)(((BYTE*)&(m_pwfx->cbSize))+sizeof(WORD)), cbExtraBytes ) != cbExtraBytes )
			{
				if(m_pwfx) 
				{ 
					delete m_pwfx;
					m_pwfx=NULL; 
				} 
			} 
		}

		if( 0 != mmioAscend( m_hmmio, &ckIn, 0 ) )
		{
			if(m_pwfx)
			{ 
				delete m_pwfx; 
				m_pwfx=NULL; 
			}
		}
	}

	void WriteMMIO( WAVEFORMATEX *pwfxDest )
	{
		DWORD    dwFactChunk; 
		MMCKINFO ckOut1;
		dwFactChunk = (DWORD)-1;

		m_ckRiff.fccType = mmioFOURCC('W', 'A', 'V', 'E');       
		m_ckRiff.cksize = 0;
		mmioCreateChunk( m_hmmio, &m_ckRiff, MMIO_CREATERIFF ) ;

		m_ck.ckid = mmioFOURCC('f', 'm', 't', ' ');
		m_ck.cksize = sizeof(PCMWAVEFORMAT);   
		mmioCreateChunk( m_hmmio, &m_ck, 0 );

		if( pwfxDest->wFormatTag == WAVE_FORMAT_PCM )
			mmioWrite( m_hmmio, (HPSTR) pwfxDest, sizeof(PCMWAVEFORMAT)); 
		else         
			(UINT)mmioWrite( m_hmmio, (HPSTR) pwfxDest, sizeof(*pwfxDest) + pwfxDest->cbSize );

		mmioAscend( m_hmmio, &m_ck, 0 ) ;
		ckOut1.ckid = mmioFOURCC('f', 'a', 'c', 't');
		ckOut1.cksize = 0;
		mmioCreateChunk( m_hmmio, &ckOut1, 0 );

		mmioWrite( m_hmmio, (HPSTR)&dwFactChunk, sizeof(dwFactChunk));
		mmioAscend( m_hmmio, &ckOut1, 0 );           
	}

	LPDIRECTSOUNDBUFFER  m_apDSBuffer;
	DWORD                m_dwDSBufferSize;
	DWORD                m_dwCreationFlags;

	void CSoundA(char filename[] , GUID guid3DAlgorithm ,DWORD dwFlags = 0)
	{
		m_pwfx    = NULL;
		m_hmmio   = NULL;
		m_pResourceBuffer = NULL;
	    Open( filename, NULL, 1 );
		DSBUFFERDESC dsbd;
		ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
		dsbd.dwSize          = sizeof(DSBUFFERDESC);
		dsbd.dwFlags         = dwFlags;
		dsbd.dwBufferBytes   = m_ck.cksize;
		dsbd.guid3DAlgorithm = guid3DAlgorithm;
		dsbd.lpwfxFormat     = m_pwfx;
		m_pDS->CreateSoundBuffer( &dsbd, &m_apDSBuffer, NULL );
		m_dwDSBufferSize = m_ck.cksize;
		m_dwCreationFlags = dwFlags;
		FillBufferWithSound( m_apDSBuffer, FALSE );

		Close();
	}

	void FillBufferWithSound( LPDIRECTSOUNDBUFFER pDSB, BOOL bRepeatWavIfBufferLarger )
	{

		VOID*   pDSLockedBuffer      = NULL; 
		DWORD   dwDSLockedBufferSize = 0;   
		DWORD   dwWavDataRead        = 0;   

		RestoreBuffer( pDSB, NULL );
		pDSB->Lock( 0, m_dwDSBufferSize, &pDSLockedBuffer, &dwDSLockedBufferSize,   NULL, NULL, 0L );

		ResetFile();
		Read( (BYTE*) pDSLockedBuffer,  dwDSLockedBufferSize,   &dwWavDataRead ) ;

		if( dwWavDataRead == 0 )
			FillMemory( (BYTE*) pDSLockedBuffer, dwDSLockedBufferSize, (BYTE)(m_pwfx->wBitsPerSample == 8 ? 128 : 0 ) );
		else if( dwWavDataRead < dwDSLockedBufferSize )
		{
			if( bRepeatWavIfBufferLarger )
			{       
				DWORD dwReadSoFar = dwWavDataRead;   
				while( dwReadSoFar < dwDSLockedBufferSize )
				{  
					ResetFile();
					Read( (BYTE*)pDSLockedBuffer + dwReadSoFar, dwDSLockedBufferSize - dwReadSoFar, &dwWavDataRead );
					dwReadSoFar += dwWavDataRead;
				} 
			}
			else
				FillMemory( (BYTE*) pDSLockedBuffer + dwWavDataRead, dwDSLockedBufferSize - dwWavDataRead, (BYTE)(m_pwfx->wBitsPerSample == 8 ? 128 : 0 ) );
		}

		pDSB->Unlock( pDSLockedBuffer, dwDSLockedBufferSize, NULL, 0 );
	}

	void RestoreBuffer( LPDIRECTSOUNDBUFFER pDSB, BOOL* pbWasRestored )
	{
		HRESULT hr;

		if( pbWasRestored )
			*pbWasRestored = FALSE;

		DWORD dwStatus;
		pDSB->GetStatus( &dwStatus );    

		if( dwStatus & DSBSTATUS_BUFFERLOST )
		{
			do 
			{
				hr = pDSB->Restore();
				if( hr == DSERR_BUFFERLOST )
					Sleep( 10 );
			}
			while( ( pDSB->Restore() ) == DSERR_BUFFERLOST );

			if( pbWasRestored != NULL )
				*pbWasRestored = TRUE;
		}
	}

	HRESULT Get3DBufferInterface( DWORD dwIndex, LPDIRECTSOUND3DBUFFER* ppDS3DBuffer )
	{
		*ppDS3DBuffer = NULL;
		return m_apDSBuffer->QueryInterface( IID_IDirectSound3DBuffer, (VOID**)ppDS3DBuffer );
	}

	LPDIRECTSOUND3DBUFFER   g_pDS3DBuffer;   
	DS3DBUFFER              g_dsBufferParams;               
	bool threeDFlag;

public:
	mxWave() {
		m_apDSBuffer = 0;
		g_pDS3DBuffer = 0;
	}
	~mxWave()
	{
		if(m_pDS) {
		if(m_apDSBuffer)
		{ 
			m_apDSBuffer->Release();
			m_apDSBuffer=NULL; 
		}

		if(g_pDS3DBuffer) 
		{ 
			g_pDS3DBuffer->Release(); 
			g_pDS3DBuffer=NULL; 
		}
		}
	}	

	void load(char filename[], int threeDimensionLevel=0)
	{
		g_pDS3DBuffer = 0;

		switch (threeDimensionLevel) 
		{
		case 0:
			CSoundA(filename,GUID_NULL,DSBCAPS_CTRLVOLUME);
			threeDFlag=false;
			break;

		case 1:
			CSoundA(filename,GUID_NULL,DSBCAPS_CTRL3D|DSBCAPS_CTRLVOLUME);
			break;

		case 2:
			CSoundA(filename,DS3DALG_NO_VIRTUALIZATION,DSBCAPS_CTRL3D|DSBCAPS_CTRLVOLUME);
			break;

		case 3:
			CSoundA(filename,DS3DALG_HRTF_LIGHT,DSBCAPS_CTRL3D|DSBCAPS_CTRLVOLUME);
			break;

		case 4:
			CSoundA(filename,DS3DALG_HRTF_FULL,DSBCAPS_CTRL3D|DSBCAPS_CTRLVOLUME);
			break;
		}

		if (threeDimensionLevel!=0)
		{

			Get3DBufferInterface( 0, &g_pDS3DBuffer );
			g_dsBufferParams.dwSize = sizeof(DS3DBUFFER);
			g_pDS3DBuffer->GetAllParameters( &g_dsBufferParams );
			g_dsBufferParams.dwMode = DS3DMODE_HEADRELATIVE;
			g_pDS3DBuffer->SetAllParameters( &g_dsBufferParams, DS3D_IMMEDIATE );

			DSBCAPS dsbcaps;
			ZeroMemory( &dsbcaps, sizeof(DSBCAPS) );
			dsbcaps.dwSize = sizeof(DSBCAPS);

			m_apDSBuffer->GetCaps( &dsbcaps );
			threeDFlag=true;
		}
	}

	void Play(long volume = 0, float x = 0, float y = 0, float z = 0, float minDist = 1, float maxDist = 1, float rolloff = 1)
	{
		if (threeDFlag)
			g_pDS3DBuffer->SetPosition(x,y,z,DS3D_IMMEDIATE); 

		m_apDSBuffer ->SetVolume(volume);
		m_apDSBuffer ->Stop();
		m_apDSBuffer ->SetCurrentPosition(0);
		m_apDSBuffer->Play(0,0,0 );
	}

	void stop()
	{
		m_apDSBuffer ->Stop();
		m_apDSBuffer ->SetCurrentPosition(0);
	}

	bool is_playing()
	{
		bool answer=false;
		DWORD dwStatus = 0;
		m_apDSBuffer->GetStatus( &dwStatus );
		answer |= ( ( dwStatus & DSBSTATUS_PLAYING ) != 0 );
		return answer;
	}
};

