/* MasterX System Devlopment Kit (SDK)
   DirectX API Encapsulation For easy game programming.
   Written by Jared Bruni . Age 17
   Email Me: MasterOnLSD@lostsidedead.com 

	www.lostsidedead.com

  for MasterX Documentation check out

  www.lostsidedead.com/gameprog/

  I LOVE VIDEO GAMES!!!!!!!!!!!!!!

  - :)

*/

#include "MasterX.h"


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
		initSound();
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
// Draw a Rectangle
void FAST MasterPaint::mxdrawrect(int x, int y, int xx, int yy, COLORREF fill, COLORREF outline)
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

//*********************** MASTER SOUND OBJECT ***********************************************/

MasterSound::MasterSound()
{
	pSound = NULL;
}

MasterSound::~MasterSound()
{
	if(pSound)
	{
		pSound->Release();
	}
}
// Load a Sound
bool MasterSound::LoadSound(IDirectSound *pds,LPCSTR name)
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

	return false;
}
// Play the Sound
void MasterSound::Play()
{
	if(pSound)
	{
		pSound->Play(0,0,0);
	}
}
// Play status of Sound (is it Playing?)
bool MasterSound::PlayStatus()
{
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


