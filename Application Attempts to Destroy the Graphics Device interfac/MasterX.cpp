/*

  MasterX API - Encapsulation of DirectX
  640x480 Video Game Encapsulation
  Required Librarys
  DirectDraw (library) ddraw.lib
  DirectSound (library) dsound.lib
  DirectInput (library) dinput.lib
  extra: dxguid.lib
  
	(COLORKEY) 255,0,255
	
*/


#include "masterx.h"

// init master screen
MasterScreen::MasterScreen()
{
	
}
// uninit master screen

MasterScreen::~MasterScreen()
{

}

// Master Graphic

// init graphic
MGraphic::MGraphic()
{
	
	
}
// unint graphic
MGraphic::~MGraphic()
{
	
	if(surf != NULL) { surf->Release(); }
	
}

// Load a Graphic
void MGraphic::loadgraphic(char* filenamex, MasterScreen scrx)
{
	
	surf = DDLoadBitmap(scrx.lpDD, filenamex);
	HBITMAP hbm;
	BITMAP bm;
	
	hbm = (HBITMAP)LoadImage(NULL, filenamex, IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	
	if(hbm == NULL) { on = false; } else { on = true; }
	
	GetObject(hbm, sizeof(bm), &bm); // size
	
	
	// Create Surface for this Bitmap
	
	int cw = bm.bmWidth;
	int ch = bm.bmHeight;

	DeleteObject(hbm);
	
	mx = cw;
	my = ch;
	
	strcpy(filename,filenamex);
	scr = scrx;
	
	
}
// set the graphic surface
void MGraphic::setsurface(LPDIRECTDRAWSURFACE surfx,MasterScreen scrx,int cx,int cy)
{
	surf = surfx;
	scr  = scrx;
	mx = cx;
	my = cy;
	
}
// restore the graphic
void MGraphic::restoremgraphic()
{
	
//	surf = DDLoadBitmap(scr->lpDD, filename);
	
}
// display the graphic
void MGraphic::displaygraphic(int x,int y,int w,int h)
{
/*	if(on == false) { return; }
	
	HRESULT ddrval;
    RECT rcRect;
	
	SetRect(&rcRect,0,0,w,h);
	
	if(colorkey == true)
	{
		
		ddrval= scr->lpBack->BltFast(x, y, surf,
			&rcRect, DDBLTFAST_SRCCOLORKEY);
	}
	else
	{
		ddrval = scr->lpBack->BltFast(x,y,surf,&rcRect,DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
	}
	
	
	if(ddrval != DD_OK) {  restoremgraphic(); }
	
	  */
	
}
/// display the graphic
void MGraphic::displaygraphic(int x, int y)
{
	/*
	if(on == false) { return; }
	
	HRESULT ddrval;
    RECT rcRect;
	
	SetRect(&rcRect,0,0,mx,my);
	
	if(colorkey == true)
	{
		
		ddrval= scr->lpBack->BltFast(x, y, surf,
			&rcRect, DDBLTFAST_SRCCOLORKEY);
	}
	else
	{
		ddrval = scr->lpBack->BltFast(x,y,surf,&rcRect,DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
	}
	
	
	if(ddrval != DD_OK) {  restoremgraphic(); }
	*/
	
}
// set color key
void MGraphic::setcolorkey(COLORREF f)
{
	
	DDSetColorKey(surf,f);
	colorkey = true;
	
	
}
// kill color key
void MGraphic::killcolorkey()
{
	
	colorkey = false;
	
}

// set the default font back agian & shit

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
void MasterText::printtext(char* strtext, int x, int y)
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
void MasterText::printtextrect(char* strtext, int y, int x, int w, int h)
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
void MasterText::printtextunderline(char* strtext, int x, int y)
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
// load graphic
void MasterGraphic::loadgraphic(char* filename,MasterScreen scr)
{
	
//	surf = DDLoadBitmap(scr->lpDD,filename);
}
// get null graphic index
int MasterXRCGraphic::getoffgraphic()
{
	
	for(int i = 0; i < MAX_SURF; i++)
	{
		
		if(list[i].on == false) { return i; }
		
	}
	
	return 0;
}
// add graphic
void MasterXRCGraphic::addgraphic(char* filename, MasterScreen scr, int x, int y)
{
	
	/*
	int off = getoffgraphic();
	
//	list[off].surf = DDLoadBitmap(scr->lpDD, filename);
	strcpy(list[off].filename,filename);
	list[off].x = x;
	list[off].y = y;
	HBITMAP hbm;
	BITMAP   bm;
	hbm = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hbm, sizeof(bm), &bm); // size
	
	
	// Create Surface for this Bitmap
    int w; int h;
	w = bm.bmWidth;
	h = bm.bmHeight;
	
	//	SetRect(&rcRect,0,0,w,h);
	
	DeleteObject(hbm);

	
	
	
	
	
	
	list[off].w = w;
	list[off].h = h;
	list[off].on = true;
	*/
	
}
// destroy master xhwnd
void MasterXHWND::destroy()
{
	scr->lpDD->Release();
	
	
	
}

// restore graphics
void MasterXRCGraphic::restoregraphic(MasterScreen scr)
{/*
	
	for(int i = 0; i < MAX_SURF; i++)
	{
		
		int off;
		off = i;
		if(list[off].on == true)
		{
			
			list[off].surf = DDLoadBitmap(scr->lpDD,list[off].filename);
			list[off].on = true;
			
		}
		
	}
	*/
	
}
// remove graphics
void MasterXRCGraphic::removegraphic(char* filename)
{
	
	for(int i = 0; i < MAX_SURF; i++)
	{
        int off;
		off = i;
		if(strstr(list[i].filename,filename))
		{
			
			strcpy(list[off].filename, "");
			list[off].x = 0;
			list[off].y = 0;
			list[off].w = NULL;
			list[off].h = NULL;
			list[off].on = false;
			
			
		}
		
	}
	
}
// display graphics (all)
void MasterXRCGraphic::displaygraphics(MasterScreen scr)
{
	
//	HRESULT ddrval;
//	RECT rcRect;
	
	/*
	
	for(int i = 0; i < MAX_SURF; i++)
	{
		

		if(list[i].on == true)
		{
			int w;
			int h;
			int x;
			int y;
			w = list[i].w;
			h = list[i].h;
			x = list[i].x;
			y = list[i].y;
			
			SetRect(&rcRect,0,0,w,h);
			
			
			if(list[i].colorkey)
			{
				
				ddrval= scr->lpBack->BltFast(x, y, list[i].surf,
					&rcRect, DDBLTFAST_SRCCOLORKEY);
				if(ddrval != DD_OK) { restoregraphic(scr); }
				
			} else {
				
				
				ddrval = scr->lpBack->BltFast(x,y,list[i].surf,&rcRect,DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
				
				
				if(ddrval != DD_OK) { restoregraphic(scr); }
				
			}
		}
	}
	
	  */
}
// display graphic (single)
void MasterXRCGraphic::displaygraphic(MasterScreen scr, char* filename, int x, int y)
{
	/*
	HRESULT ddrval;
	RECT rcRect;
	
	for(int i = 0; i < MAX_SURF; i++)
	{
		
		if((list[i].on) && (strstr(list[i].filename,filename)))
		{
			int w;
			int h;
			w = list[i].w;
			h = list[i].h;
			x = list[i].x;
			y = list[i].y;
			
			SetRect(&rcRect,0,0,w,h);
			
			if(list[i].colorkey)
			{
				
				ddrval= scr->lpBack->BltFast(x, y, list[i].surf,
					&rcRect, DDBLTFAST_SRCCOLORKEY);
				if(ddrval != DD_OK) { restoregraphic(scr); }
				
			}
			else
			{
				ddrval = scr->lpBack->BltFast(x,y,list[i].surf,&rcRect,DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
			}
			
			if(ddrval != DD_OK) { restoregraphic(scr); }
			
		}
		
		
	}

  */
	
}
// set position of a certin graphic
void MasterXRCGraphic::setgraphicpos(char* filename, int x, int y, bool on)
{
	
	for(int i = 0; i < MAX_SURF; i++)
	{
		
		
		if((list[i].on) && (strstr(list[i].filename,filename)))
		{
			list[i].x = x;
			list[i].y = y;
			list[i].on = on;
			return;
			
		}
	}
	
}
// set color key
void MasterXRCGraphic::setcolorkey(char* filename, COLORREF rgb)
{
	
	for(int i = 0; i < MAX_SURF; i++)
	{
        int off;
		off = i;
		if(strstr(list[i].filename,filename))
		{
			list[off].colorkey = true;
			DDSetColorKey(list[i].surf, rgb);
			
		}
		
	}
	
}
// init MasterXRCGraphic (constructor)
MasterXRCGraphic::MasterXRCGraphic()
{
	
	int i = 0;
	for(i = 0; i < MAX_SURF; i++)
	{
		
		list[i].on = false;
		
	}
	
}
// uninit (deconstructor)
MasterXRCGraphic::~MasterXRCGraphic()
{
	
	for(int i = 0; i < MAX_SURF; i++)
	{
		if(list[i].surf != NULL)
		{
			list[i].surf->Release();
		}
		
	}
	
	
}
// MasterXHWND
// init
MasterXHWND::MasterXHWND()
{
	
	
}
// unint
MasterXHWND::~MasterXHWND()
{

}
// get emtpy graphic spot
int AnimatedGraphic::getoffgraphic()
{
	
	for(int i = 0; i < MAX_SURF; i++)
	{
		
		if(list[i].on == false) { return i; }
		
	}
	
	return 0;
}
// clear off animated graphic
void AnimatedGraphic::clear()
{
	for(int i = 0; i< MAX_SURF; i++)
	{
		
		int off;
		off = i;
		strcpy(list[off].filename, "");
		list[off].x = 0;
		list[off].y = 0;
		list[off].w = NULL;
		list[off].h = NULL;
		list[off].on = false;
		
		
	}
	
}
// add image to animated graphic
void AnimatedGraphic::add(char* filename, MasterScreen scr)
{
	/*
	int off;
	off = getoffgraphic();
	list[off].surf = DDLoadBitmap(scr->lpDD, filename);
	strcpy(list[off].filename,filename);
	list[off].x = 0;
	list[off].y = 0;
	HBITMAP hbm;
	BITMAP   bm;
	hbm = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hbm, sizeof(bm), &bm); // size
    int w; int h;
	w = bm.bmWidth;
	h = bm.bmHeight;
	DeleteObject(hbm);

	list[off].w = w;
	list[off].h = h;
	list[off].on = true;
	*/
	
}
// add image i
void AnimatedGraphic::addi(char* filename, MasterScreen scr, int i)
{
	/*
	
	int off;
	off = i;
	list[off].surf = DDLoadBitmap(scr->lpDD, filename);
	strcpy(list[off].filename,filename);
	list[off].x = 0;
	list[off].y = 0;
	HBITMAP hbm;
	BITMAP   bm;
	hbm = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hbm, sizeof(bm), &bm); // size
    int w; int h;
	w = bm.bmWidth;
	h = bm.bmHeight;
	DeleteObject(hbm);
	list[off].w = w;
	list[off].h = h;
	list[off].on = true;
	*/
}
// remove graphic
void AnimatedGraphic::rmv(char* filename)
{
	
	for(int i = 0; i < MAX_SURF; i++)
	{
		
		if(strstr(list[i].filename,filename))
		{
			
			list[i].surf->Release();
			list[i].on = false;
			strcpy(list[i].filename,"");
			
		}
	}
	
}
// play graphic
bool AnimatedGraphic::play(MasterScreen scr,int x, int y, int start,int stop)
{
	/*
	
	HRESULT ddrval;
	RECT rcRect;
	
	
	bool ret = true;
	if(iplay == false)
	{
		
		index = start;
		iplay = true;
		
	}
	
	if(index == stop)
	{
		
		ret = false;
	}
	/*
	if(index <= stop)
	{
		
		int i;
		i = index;
		int w;
		int h;
		w = list[i].w;
		h = list[i].h;
		
		SetRect(&rcRect,0,0,w,h);
		
		if(list[i].colorkey)
		{
			
            ddrval= scr->lpBack->BltFast(x, y, list[i].surf,
				&rcRect, DDBLTFAST_SRCCOLORKEY);
			if(ddrval != DD_OK) { restoregraphic(scr); }
			
		} else {
			
			ddrval = scr->lpBack->BltFast(x,y,list[i].surf,&rcRect,DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
			
			
			if(ddrval != DD_OK) { restoregraphic(scr); } }
		
		index++;
		
		return ret;
		
	}
	else
	{
		
		iplay = false;
		index = start;
		return false;
		
	}
	
	  */
	return NULL;
}

// reset animation
void AnimatedGraphic::reset()
{
	
	time = 0;
	iplay = false;
	index = 0;
	
}
// play animation at speed
bool AnimatedGraphic::playatspeed(MasterScreen scr,int x,int y, int start, int stop, int speed)
{
	/*
	HRESULT ddrval;
	RECT rcRect;
	
	bool result;
	if(time > speed)
	{
		
		result = play(scr,x,y,start,stop);
		
		time = 0;
	} else { 
		
		int i;
		i = index;
		if(list[i].colorkey)
		{
			
			
			
			SetRect(&rcRect,0,0,list[i].w,list[i].h);
			ddrval= scr->lpBack->BltFast(x, y, list[i].surf,
				&rcRect, DDBLTFAST_SRCCOLORKEY);
			if(ddrval != DD_OK) { restoregraphic(scr); }
			
		} else {
			
			ddrval = scr->lpBack->BltFast(x,y,list[i].surf,&rcRect,DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
			
			
			if(ddrval != DD_OK) { restoregraphic(scr); } }
		
		
		
		
	}
	
	
	time++;
	
	return result;

 */
	return NULL;
}

// restore graphics
void AnimatedGraphic::restoregraphic(MasterScreen scr)
{
	
	/*
	for(int i = 0; i < MAX_SURF; i++)
	{
		
		int off;
		off = i;
		if(list[off].on == true)
		{
			
			list[off].surf = DDLoadBitmap(scr->lpDD,list[off].filename);
			list[off].on = true;
			
		}
		
	}
	*/
}

// deconstruct
AnimatedGraphic::~AnimatedGraphic()
{
	
	
	for(int i = 0; i < MAX_SURF; i++)
	{
		if(list[i].surf)
		{
			list[i].surf->Release();
		}
		
	}
	
}
// set color key rgb
void AnimatedGraphic::setcolorkey(char* filename, COLORREF rgb)
{

	for(int i = 0; i < MAX_SURF; i++)
	{
        int off;
		off = i;
		if(strstr(list[i].filename,filename))
		{
			list[off].colorkey = true;
			DDSetColorKey(list[i].surf, rgb);
			
		}
		
	}
	
}

void MasterXHWND::init2(HWND hwnd)
{
	  HDC hdc;
	// retrieves device-specific information about 
    // the specified device. 
	int bpp;

    // Get the windows device context
	hdc = GetDC(NULL);
    // Get the number of adjacent color bits for each pixel.
    bpp = GetDeviceCaps(hdc, BITSPIXEL);
    // Release the Device Context
	ReleaseDC(NULL, hdc);
		hwndx = hwnd;
	
	HRESULT ddrval;
	
	// create main dd object
	
	ddrval = DirectDrawCreate(NULL, &scr->lpDD,NULL);
	
	if(ddrval != DD_OK)
	{
		MessageBox(NULL,"Couldnt Create DirectX Object! Error: Terminating!","Error!!!",MB_ICONERROR);
		exit(0);		
	}
	
	ddrval = scr->lpDD->SetCooperativeLevel(hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT );
	

	
	if(ddrval != DD_OK)
	{
		
		scr->lpDD->Release();
		MessageBox(0,"Couldnt Set Cooperative Level, Fatal Error Aborting","Error",MB_ICONERROR);

		
	}
	
	// Set Mode to 640x480 in EXCLUSIVE MODE
	
	ddrval = scr->lpDD->SetDisplayMode(640,480,bpp);
	
	if(ddrval != DD_OK)
	{
		MessageBox(0,"Error Setting Display Mode",0,MB_ICONERROR);
		scr->lpDD->Release();
		return;
		
	}
	
	if(setprimarysurface())
	{
		
		text.init(scr);
		
		initSound();
	}
	else
	{
		MessageBox(0,"Couldnt Set Surfaces! Fatal Error! DirectX is jacked Man","Broken Software :(",MB_ICONERROR);
		return;
	}

	initInput();

	
	return;

}



// init master xhwnd
bool MasterXHWND::init(HWND hwnd)
{
	
	hwndx = hwnd;
	
	HRESULT ddrval;
	
	// create main dd object
	
	ddrval = DirectDrawCreate(NULL, &scr->lpDD,NULL);
	
	if(ddrval != DD_OK)
	{
		MessageBox(NULL,"Couldnt Create DirectX Object! Error: Terminating!","Error!!!",MB_ICONERROR);
		exit(0);		
		return false;
	}
	
	ddrval = scr->lpDD->SetCooperativeLevel(hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT );
	

	
	if(ddrval != DD_OK)
	{
		
		scr->lpDD->Release();
		MessageBox(0,"Couldnt Set Cooperative Level, Fatal Error Aborting","Error",MB_ICONERROR);

		return false;
		
	}
	
	// Set Mode to 640x480 in EXCLUSIVE MODE
	
	ddrval = scr->lpDD->SetDisplayMode(640,480,16);
	
	if(ddrval != DD_OK)
	{
		MessageBox(0,"Error Setting Display Mode",0,MB_ICONERROR);
		scr->lpDD->Release();
		return false;
		
	}
	
	if(setprimarysurface())
	{
		
		text.init(scr);
		
		initSound();
	}
	else
	{
		MessageBox(0,"Couldnt Set Surfaces! Fatal Error! DirectX is jacked Man","Broken Software :(",MB_ICONERROR);
		return false;
	}

	initInput();

	
	return true;
}
// init INput
void MasterXHWND::initInput()
{


	DirectInputCreate(GetModuleHandle(NULL),DIRECTINPUT_VERSION,(struct IDirectInputA**)&pDI,NULL);
	
/*	pDI->CreateDevice(GUID_SysKeyboard, IID_IDirectInputDevice,
		(void **)&pKeyboard, NULL); */

	pDI->CreateDevice(GUID_SysKeyboard,&pKeyboard,NULL);
	pKeyboard->SetDataFormat(&c_dfDIKeyboard);

	// Set the cooperative level 
	pKeyboard->SetCooperativeLevel(hwndx, 
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
	
	ddrval = scr->lpDD->CreateSurface(&ddsd,&scr->lpFront,NULL);
	if(ddrval != DD_OK)
	{
        scr->lpDD->Release();
		return false;
	}
	
	// Set the description for backbuffer
	
	ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
	ddrval = scr->lpFront->GetAttachedSurface(&ddscaps, &scr->lpBack);
	if(ddrval != DD_OK)
	{
		
		scr->lpFront->Release();
		scr->lpDD->Release();
		return false;
	}
	
	return true;
	
}
// get current mscreen
int MasterXHWND::getcurscreen()
{	
	return curscreen;
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
// play sound from resource
void MasterXHWND::playsound(int id)
{
	
	pSoundx = DSLoadSoundBuffer(pDS, MAKEINTRESOURCE(id));
	
	pSoundx->Play(0,0,0);
	
}
// clear lpBack surface
void MasterXHWND::clear()
{
	ZeroMemory(&ddbltfx,sizeof(ddbltfx));
	ddbltfx.dwSize = sizeof(ddbltfx);
	ddbltfx.dwFillColor = 0;
	scr->lpBack->Blt(NULL,NULL,NULL,DDBLT_COLORFILL | DDBLT_WAIT,&ddbltfx);
	// clear bg
}

// draw a rect tangle

void MasterXHWND::mxdrawrect(int x, int y, int xx, int yy, COLORREF fill, COLORREF outline)
{
	HDC dc;
	scr->lpBack->GetDC(&dc);
	
	   HBRUSH hNewBrush,hOldBrush;// new Brush to paint with and one thats current (so we can restore)
	   HPEN hNewPen,hOldPen; // New pen to paint with and the current (so we can restore)
	   
	   hNewBrush = (HBRUSH)CreateSolidBrush(fill); // create this brush
	   hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush); // set this brush and get the old brush
	   
	   hNewPen = CreatePen(PS_SOLID,2,outline); // create this pen
	   hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); // set this pen and  get the old one
	   
	   Rectangle(dc,x,y,xx,yy); // Draw a rectangle
	   // when using shape functions, it outlines the shape with the Pen, and fills it in
	   // with the brush
	   
	   // how shapes work is x,y,xx,yy
	   // x is the top left x cord, y, is the bottom left y cord
	   // xx is the top right x cord, and yy is the bottom right x cord
	   
	   // so you basicly set 4 cords and it fills in that space :)
	   // restore shit
	   
	   SelectObject(dc,hOldPen);
	   SelectObject(dc,hOldBrush);
	   
	   DeleteObject(hNewBrush); // DIE DIE MY PEN ILL BE SEEING YOU AGIAN
	   DeleteObject(hNewPen); // i dont need this sso lets KILL It
	   scr->lpBack->ReleaseDC(dc);
}

void MasterXHWND::mxdrawroundrect(int x, int y, int x2, int y2, int cw, int ch, COLORREF fill,COLORREF outline)
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
	   
	   // when using shape functions, it outlines the shape with the Pen, and fills it in
	   // with the brush
	   
	   // how shapes work is x,y,xx,yy
	   // x is the top left x cord, y, is the bottom left y cord
	   // xx is the top right x cord, and yy is the bottom right x cord
	   
	   // so you basicly set 4 cords and it fills in that space :)
	   // restore shit
	   
	   SelectObject(dc,hOldPen);
	   SelectObject(dc,hOldBrush);
	   
	   DeleteObject(hNewBrush); // DIE DIE MY PEN ILL BE SEEING YOU AGIAN
	   DeleteObject(hNewPen); // i dont need this sso lets KILL It
	   scr->lpBack->ReleaseDC(dc);
}
// draw a circle (pie)
void MasterXHWND::mxdrawpie(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2, COLORREF fill,COLORREF outline)
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
	   // when using shape functions, it outlines the shape with the Pen, and fills it in
	   // with the brush
	   
	   // how shapes work is x,y,xx,yy
	   // x is the top left x cord, y, is the bottom left y cord
	   // xx is the top right x cord, and yy is the bottom right x cord
	   
	   // so you basicly set 4 cords and it fills in that space :)
	   // restore shit
	   
	   SelectObject(dc,hOldPen);
	   SelectObject(dc,hOldBrush);
	   
	   DeleteObject(hNewBrush); // DIE DIE MY PEN ILL BE SEEING YOU AGIAN
	   DeleteObject(hNewPen); // i dont need this sso lets KILL It
	   scr->lpBack->ReleaseDC(dc);
}
// draw chord
void MasterXHWND::mxdrawchord(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2,COLORREF fill,COLORREF outline)
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
	   
	   
	   // when using shape functions, it outlines the shape with the Pen, and fills it in
	   // with the brush
	   
	   // how shapes work is x,y,xx,yy
	   // x is the top left x cord, y, is the bottom left y cord
	   // xx is the top right x cord, and yy is the bottom right x cord
	   
	   // so you basicly set 4 cords and it fills in that space :)
	   // restore shit
	   
	   SelectObject(dc,hOldPen);
	   SelectObject(dc,hOldBrush);
	   
	   DeleteObject(hNewBrush); // DIE DIE MY PEN ILL BE SEEING YOU AGIAN
	   DeleteObject(hNewPen); // i dont need this sso lets KILL It
	   scr->lpBack->ReleaseDC(dc);
}
// draw ellipse
void MasterXHWND::mxdrawellipse(int x, int y, int x2, int y2,COLORREF fill,COLORREF outline)
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
	   
	   
	   // when using shape functions, it outlines the shape with the Pen, and fills it in
	   // with the brush
	   
	   // how shapes work is x,y,xx,yy
	   // x is the top left x cord, y, is the bottom left y cord
	   // xx is the top right x cord, and yy is the bottom right x cord
	   
	   // so you basicly set 4 cords and it fills in that space :)
	   // restore shit
	   
	   SelectObject(dc,hOldPen);
	   SelectObject(dc,hOldBrush);
	   
	   DeleteObject(hNewBrush); // DIE DIE MY PEN ILL BE SEEING YOU AGIAN
	   DeleteObject(hNewPen); // i dont need this sso lets KILL It
	   scr->lpBack->ReleaseDC(dc);
}

// update the MasterXHWND Object
void MasterXHWND::update()
{
	
	
	
	// draw images
	
	HRESULT ddrval;
	
	
	
	ddrval = scr->lpFront->Flip(NULL, DDFLIP_WAIT);
	
	if(ddrval == DD_OK)
	{
//		msg.restore = false;
	}
	else
	{
		
//		msg.restore = true;
		scr->lpFront->Restore();
	}
	
	
}
// add graphic to current frame at position
bool MasterXHWND::addgraphic(char* filename,int w, int h,int x, int y)
{
	
	HRESULT ddrval;
	RECT rcRect;
	
	
	SetRect(&rcRect,0,0,w,h);
	LPDIRECTDRAWSURFACE surf;
	
	surf = DDLoadBitmap(scr->lpDD,filename);
	ddrval = scr->lpBack->BltFast(x,y,surf,&rcRect,DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
	
	
	if(ddrval != DD_OK) { return false; }
	
	return true;
}
// add graphic to current frame at position 
bool MasterXHWND::addgraphic(HBITMAP hbm, int x, int y)
{
	
	HRESULT ddrval;
	RECT rcRect;
	
	
	BITMAP bm;
	IDirectDrawSurface *pdds;
	
	// Load Image for loading from Disk
	
	//hbm = (HBITMAP)LoadImage(NULL, szBitmap, IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	
	
	
	if(hbm == NULL) { return NULL; }
	
	GetObject(hbm, sizeof(bm), &bm); // size
	
	
	// Create Surface for this Bitmap
	
	int cw = bm.bmWidth;
	int ch = bm.bmHeight;
	
	pdds = CreateOffScreenSurface(scr->lpDD, bm.bmWidth,bm.bmHeight);
	
	if(pdds)
	{
		
		DDCopyBitmap(pdds, hbm, bm.bmWidth,bm.bmHeight);
	}
	
	
	
	SetRect(&rcRect,0,0,bm.bmWidth,bm.bmHeight);
    DeleteObject(hbm);
	// pdds
	ddrval = scr->lpBack->BltFast(x,y,pdds,&rcRect,DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
	
	return true;
	
}

HRESULT MasterXHWND::mxbltsurf(LPDIRECTDRAWSURFACE surf, int x, int y, int w, int h, bool key)
{
	HRESULT ddrval;
	RECT rcRect;
	SetRect(&rcRect,0,0,w,h);

	if(surf)
	{

	
	if(key)
	{
		ddrval = scr->lpBack->BltFast(x,y,surf,&rcRect,DDBLTFAST_SRCCOLORKEY);
		
		
	}else
	{
		ddrval = scr->lpBack->BltFast(x,y,surf,&rcRect,DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
		
	}
	}
	else
	{
		OutputDebugString("Error: Surface is not Found!");
	}
	return ddrval;
}
// set screen
void MasterXHWND::setscreen(int s)
{
	
	curscreen = s;
	
}
// init joystick
bool MasterXHWND::joyinit()
{
	
	joystickInfoEx.dwSize = sizeof(joystickInfoEx);
	joystickPresent = (joyGetPosEx(JOYSTICKID1,&joystickInfoEx) == JOYERR_NOERROR);
	if(!joystickPresent)
	{
		iJoy = false;
		
	}
	else
	{
		
		iJoy  = true;
		joyGetDevCaps(JOYSTICKID1, &joystickCaps, sizeof(joystickCaps));
		joystickHasThrottle = (joystickCaps.wCaps & JOYCAPS_HASZ);
		
		int joystickDeadSize = (joystickCaps.wXmax - joystickCaps.wXmin) * JOY_DEADZONE / 100;
		joystickDeadXMax = (joystickCaps.wXmax - joystickCaps.wXmin) / 2 + (joystickDeadSize / 2);
		joystickDeadXMin = joystickDeadXMax - joystickDeadSize;
		
		joystickDeadSize = (joystickCaps.wYmax - joystickCaps.wYmin) * JOY_DEADZONE / 100;
		joystickDeadYMax = (joystickCaps.wYmax - joystickCaps.wYmin) / 2 + (joystickDeadSize / 2);
		joystickDeadYMin = joystickDeadYMax - joystickDeadSize;
		
		
	}
	
	return true;
}
// the Cordinates
bool MasterXHWND::TheCords(JOYINFOEX* info)
{
	
	if(iJoy == false) { return false; }
	
	info->dwSize = sizeof(joystickInfoEx);
	info->dwFlags = JOY_RETURNX | JOY_RETURNY;
	
	return (!joyGetPosEx(JOYSTICKID1, info));
	
}
// JoyStick Checke
void MasterXHWND::JoyStickCheck()
{
	int bDown = BPressed(&joystickInfoEx);
	
	if(bDown != 0) {
		// Button Pressed()
		//JoyStickHandle(bDown);
		b_down = true;
		
} else { b_down = false; }



if(JoyForward())
{
	
	//JoyStickHandle(J_FORWARD);
	j_pressed = true;
}

if(JoyBackward())
{
	
	//JoyStickHandle(J_BACKWARD);
	j_pressed = true;
	
}

if(JoyLeft())
{
	
	//	MessageBox(NULL, "JoyLeft",NULL,NULL);
	//JoyStickHandle(J_LEFT);
	j_pressed = true;
}

if(JoyRight())
{
	
	
	//JoyStickHandle(J_RIGHT);
	j_pressed = true;
	
}

if(JoyStop())
{
	//MessageBox(NULL, "STOPED",NULL,NULL);
	j_pressed = false;
	
}

}
// is JoyForward ?
bool MasterXHWND::JoyForward()
{
	if(!TheCords(&joystickInfoEx)) return false;
	return (joystickInfoEx.dwYpos < joystickDeadYMin);
	
}
// is JoyBackward ?
bool MasterXHWND::JoyBackward()
{
	if(!TheCords(&joystickInfoEx)) return false;
	return(joystickInfoEx.dwYpos > joystickDeadYMax);
	
}
// is JoyLeft ?
bool MasterXHWND::JoyLeft()
{
	
	if(!TheCords(&joystickInfoEx)) return false;
	return(joystickInfoEx.dwXpos < joystickDeadXMin);
	
}
// is JoyRight ?
bool MasterXHWND::JoyRight()
{
    
	if(!TheCords(&joystickInfoEx)) return false;
	return (joystickInfoEx.dwXpos > joystickDeadXMax);
	
}
// is JoyStop ?
bool MasterXHWND::JoyStop()
{
	
	if(!TheCords(&joystickInfoEx)) return false;
	return ((joystickInfoEx.dwYpos > joystickDeadYMin) && (joystickInfoEx.dwYpos < joystickDeadYMax) && (joystickInfoEx.dwXpos > joystickDeadXMin) && (joystickInfoEx.dwXpos < joystickDeadXMax));
	
}
//*******************************
//*******************************
//*******************************

// is Joy Pressed?
bool MasterXHWND::GetJoyPressed()
{
	
	return j_pressed;
}
// Set Joy Pressed..
void MasterXHWND::SetJoyPressed(bool b)
{
	
	j_pressed = b;
	
}
// is Button Pressed if So Return That Button. (0 BEING NONE)
int MasterXHWND::BPressed(JOYINFOEX* info)
{
	if(iJoy == false) { return 0; }
	
	info->dwSize = sizeof(joystickInfoEx);
	info->dwFlags =  JOY_RETURNBUTTONS;
    joyGetPosEx(JOYSTICKID1,info);
	
	int x = info->dwButtonNumber;
	
	//char bd[50];
	//itoa(x,bd,50);
	
	
	return x;
	
}
// get if button is down
bool MasterXHWND::getbdown()
{
	
	return b_down;
}

/* 

  Non Class DirectX Functions
  
*/
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
	
	pdds = CreateOffScreenSurface(pdd, bm.bmWidth,bm.bmHeight);
	
	if(pdds)
	{
		
		DDCopyBitmap(pdds, hbm, bm.bmWidth,bm.bmHeight);
	}
	
	
	DeleteObject(hbm);
	
	return pdds;
	
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

