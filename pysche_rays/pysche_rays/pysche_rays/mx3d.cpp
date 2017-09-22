#include "mx3d.h"

float z_pos = 0.0f;
LPDIRECTSOUND8 m_pDS = 0;
LPDIRECTSOUND3DLISTENER g_pDSListener = 0;  
int mxApp::InitLoop() {
	MSG msg;
	go = true;
	while(go == true)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;
			
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		else if(active) {
			screen.pd3d_dev->Clear(NULL,NULL,D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0),1.0f,NULL);

			this->render(cur_screen);

			screen.pd3d_dev->Present(NULL,NULL,NULL,NULL);

		}
		else if(!active) {
			WaitMessage();
		}
	}

	return (int) msg.wParam;
}


mxHwnd::mxHwnd(const char *title, int x, int y, int w ,int h, bool fullscreen, WNDPROC wndProc, HICON hIcon ) {
	if(Init(title,fullscreen,x,y,w,h,wndProc, hIcon) == true) {
		if(InitDX(fullscreen,32) == true) {

		}
	}
}

mxHwnd::mxHwnd() {
	hwnd = 0, w = h = 0;
}

bool mxHwnd::Init(const char *title, bool full, int x, int y, int w, int h, WNDPROC WndProc, HICON hIcon) {

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	wc.hInstance = GetModuleHandle(0);
	wc.hIcon = hIcon;
	wc.hIconSm = hIcon;
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = title;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wc);


	this->hwnd = CreateWindow(title,title,(full == true) ? WS_POPUPWINDOW : WS_SYSMENU | WS_MINIMIZEBOX, x,y,w,h,NULL,NULL,GetModuleHandle(0),NULL);
	if(!hwnd) {
		ErrorMsg("Couldnt create window!.\n");
		return false;
	}
	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);
	this->w = w;
	this->h = h;
	return true;
}

bool mxHwnd::InitDX(bool fullscreen, int bpp) {
	screen.pd3d = Direct3DCreate9(D3D_SDK_VERSION);
	if(!screen.pd3d) {
		ErrorMsg("Error couldnt create Direct3D Device.");
		return false;
	}


	D3DPRESENT_PARAMETERS dpp;
	ZeroMemory(&dpp, sizeof(dpp));
	dpp.BackBufferCount = 1;
	dpp.BackBufferWidth = this->w;
	dpp.BackBufferHeight = this->h;
	if( bpp == 16 )
		dpp.BackBufferFormat        = D3DFMT_R5G6B5;
	else if( bpp == 24 )
		dpp.BackBufferFormat        = D3DFMT_X8R8G8B8;
	else if( bpp == 32 )
		dpp.BackBufferFormat        = D3DFMT_A8R8G8B8;
	else
		ErrorMsg("Invalid Format for BackBuffer you choose %d", bpp);
	dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	dpp.MultiSampleQuality = 0;
	dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	dpp.hDeviceWindow = this->hwnd;
	dpp.Windowed = (fullscreen == true) ? FALSE : TRUE;
	dpp.EnableAutoDepthStencil = TRUE;
	dpp.AutoDepthStencilFormat = D3DFMT_D16;
	dpp.FullScreen_RefreshRateInHz = (fullscreen == false) ? 0 : D3DPRESENT_RATE_DEFAULT;
	dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	HRESULT rt = screen.pd3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,&dpp,&screen.pd3d_dev );
	if(FAILED(rt)) {
		ErrorMsg("Error couldnt create Device.\n");
		return false;
	}
	screen.scr_rc.top = screen.scr_rc.left = 0;
	screen.scr_rc.right = this->w;
	screen.scr_rc.bottom = this->h;
	screen.pd3d_dev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &screen.pback );
	if(!screen.pback) {
		ErrorMsg("Error couldnt retrive the back buffer!\n");
		return false;
	}
	text.Init(&screen);
	paint.init(&screen);
	input.Init(this->hwnd);
	return true;
}



int mxHwnd::InitLoop(void(*render)(int screen)) {

	MSG msg;
	go = true;
	SetFocus(hwnd);
	while(go == true)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		else if(active) {
			input.Update();
			screen.pd3d_dev->Clear(NULL,NULL,D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0),1.0f,NULL);
			render(cur_screen);

			screen.pd3d_dev->Present(NULL,NULL,NULL,NULL);

		}
		else if(!active)
			WaitMessage();
	}

	input.Free();

	return (int) msg.wParam;
}

mxScreen::~mxScreen() {
	SafeFree<LPDIRECT3DSURFACE9>(this->pback);
	SafeFree<LPDIRECT3DDEVICE9>(this->pd3d_dev);
	SafeFree<LPDIRECT3D9>(this->pd3d);
}

void __fastcall mxPaint::Lock() {
	mxscr->pback->LockRect(&rect,NULL,NULL);
	data = (DWORD*) rect.pBits;
}

void __fastcall mxPaint::UnLock() {
	mxscr->pback->UnlockRect();
}

void __fastcall mxPaint::fast_sp(int x, int y, int pitch, D3DCOLOR color) {

	data[(((pitch/4) * y) + x)] = color;

}

DWORD __fastcall mxPaint::fast_gp(int x, int y) {
	int pitch = this->rect.Pitch;
	return data[((pitch/4) * y) +x];
}

void __fastcall mxPaint::setpixel(int i, int z,D3DCOLOR color) {
	mxscr->pback->LockRect(&rect,NULL,NULL);
	DWORD *pdata = (DWORD*) rect.pBits;
	int pitch = rect.Pitch;
	pdata[(((pitch/4) * z) + i)] = color;
	mxscr->pback->UnlockRect();
}

void __fastcall mxPaint::drawrect(int x, int y, int w , int h, D3DCOLOR color) {
	D3DRECT rc = { x,y,w,h };
	mxscr->pd3d_dev->Clear(1,&rc,D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, color,1.0f,NULL);
}

void __fastcall mxPaint::drawroundrect(int x, int y, int x2, int y2, int ch, int cw, COLORREF fill, COLORREF outline) {

	HDC dc;
	mxscr->pback->GetDC(&dc);
	HBRUSH hNewBrush,hOldBrush;
	HPEN hNewPen,hOldPen; 

	hNewBrush = (HBRUSH)CreateSolidBrush(fill); 
	hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush);

	hNewPen = CreatePen(PS_SOLID,2,outline); 
	hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); 

	RoundRect(dc,x,y,x2,y2,cw,ch);

	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);

	DeleteObject(hNewBrush);
	DeleteObject(hNewPen);
	mxscr->pback->ReleaseDC(dc);
}

void __fastcall mxPaint::drawpie(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2, COLORREF fill, COLORREF outline) {
	HDC dc;
	mxscr->pback->GetDC(&dc);
	HBRUSH hNewBrush,hOldBrush;
	HPEN hNewPen,hOldPen; 

	hNewBrush = (HBRUSH)CreateSolidBrush(fill); 
	hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush);

	hNewPen = CreatePen(PS_SOLID,2,outline); 
	hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); 

	Pie(dc,x,y,x2,y2,nx,ny,nx2,ny2);

	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);

	DeleteObject(hNewBrush);
	DeleteObject(hNewPen);
	mxscr->pback->ReleaseDC(dc);
}

void __fastcall mxPaint::drawchord(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2,COLORREF fill,COLORREF outline) {
	HDC dc;
	mxscr->pback->GetDC(&dc);
	HBRUSH hNewBrush,hOldBrush;
	HPEN hNewPen,hOldPen; 

	hNewBrush = (HBRUSH)CreateSolidBrush(fill); 
	hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush);

	hNewPen = CreatePen(PS_SOLID,2,outline); 
	hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); 

	Chord(dc,x,y,x2,y2,nx,ny,nx2,ny2);

	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);

	DeleteObject(hNewBrush);
	DeleteObject(hNewPen);
	mxscr->pback->ReleaseDC(dc);
}

void __fastcall mxPaint::drawellipse(int x, int y, int x2, int y2,COLORREF fill,COLORREF outline) {
	HDC dc;
	mxscr->pback->GetDC(&dc);
	HBRUSH hNewBrush,hOldBrush;
	HPEN hNewPen,hOldPen; 

	hNewBrush = (HBRUSH)CreateSolidBrush(fill); 
	hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush);

	hNewPen = CreatePen(PS_SOLID,2,outline); 
	hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); 

	Ellipse(dc,x,y,x2,y2);

	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);

	DeleteObject(hNewBrush);
	DeleteObject(hNewPen);
	mxscr->pback->ReleaseDC(dc);
}

void __fastcall mxPaint::drawpolygon(CONST POINT* point,int n_points,COLORREF fill,COLORREF outline) {
	HDC dc;
	mxscr->pback->GetDC(&dc);
	HBRUSH hNewBrush,hOldBrush;
	HPEN hNewPen,hOldPen; 

	hNewBrush = (HBRUSH)CreateSolidBrush(fill); 
	hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush);

	hNewPen = CreatePen(PS_SOLID,2,outline); 
	hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); 

	Polygon(dc,point,n_points);

	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);

	DeleteObject(hNewBrush);
	DeleteObject(hNewPen);
	mxscr->pback->ReleaseDC(dc);
}

void __fastcall mxPaint::drawanglearc(int x, int y, long radius, float startangle,float sweepangle,COLORREF fill,COLORREF outline) {
	HDC dc;
	mxscr->pback->GetDC(&dc);
	HBRUSH hNewBrush,hOldBrush;
	HPEN hNewPen,hOldPen; 

	hNewBrush = (HBRUSH)CreateSolidBrush(fill); 
	hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush);

	hNewPen = CreatePen(PS_SOLID,2,outline); 
	hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); 

	AngleArc(dc,x,y,radius,startangle,sweepangle);

	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);

	DeleteObject(hNewBrush);
	DeleteObject(hNewPen);
	mxscr->pback->ReleaseDC(dc);
}

void __fastcall mxPaint::drawarc(int x1, int x2, int x3, int x4,int x5, int x6,int x7, int x8,COLORREF fill,COLORREF outline) {
	HDC dc;
	mxscr->pback->GetDC(&dc);
	HBRUSH hNewBrush,hOldBrush;
	HPEN hNewPen,hOldPen; 

	hNewBrush = (HBRUSH)CreateSolidBrush(fill); 
	hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush);

	hNewPen = CreatePen(PS_SOLID,2,outline); 
	hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); 

	Arc(dc,x1,x2,x3,x4,x5,x6,x7,x8);

	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);

	DeleteObject(hNewBrush);
	DeleteObject(hNewPen);
	mxscr->pback->ReleaseDC(dc);
}

void __fastcall mxPaint::drawlineto(int x, int y,COLORREF fill,COLORREF outline) {
	HDC dc;
	mxscr->pback->GetDC(&dc);
	HBRUSH hNewBrush,hOldBrush;
	HPEN hNewPen,hOldPen; 

	hNewBrush = (HBRUSH)CreateSolidBrush(fill); 
	hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush);

	hNewPen = CreatePen(PS_SOLID,2,outline); 
	hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); 

	LineTo(dc,x,y);

	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);

	DeleteObject(hNewBrush);
	DeleteObject(hNewPen);
	mxscr->pback->ReleaseDC(dc);
}

void __fastcall mxPaint::drawpixel(int x, int y, COLORREF color) {
	HDC dc;
	this->mxscr->pback->GetDC(&dc);
	SetPixel(dc,x,y,color);
	this->mxscr->pback->ReleaseDC(dc);

}

COLORREF __fastcall mxPaint::drawgetpixel(int x, int y) {
	HDC dc;
	this->mxscr->pback->GetDC(&dc);
	COLORREF color = GetPixel(dc,x,y);
	this->mxscr->pback->ReleaseDC(dc);
	return color;
}

void __fastcall mxPaint::drawline(int start_x, int start_y, int stop_x, int stop_y, COLORREF color) {
	HDC dc;
	mxscr->pback->GetDC(&dc);
	
	int y_unit,x_unit;
	int ydiff = stop_y-start_y;
	if(ydiff<0)
	{
		ydiff = ydiff;
		y_unit=-1;
	}
	else
	{
		y_unit =1;
	}
	int xdiff=stop_x-start_x;
	if(xdiff<0)
	{
		xdiff=-xdiff;
		x_unit = -1;
	}
	else
	{
		x_unit = 1;
	}
	
	int error_term=0;
	if(xdiff>ydiff)
	{
		int length=xdiff+1;
		for(int i = 0; i <length; i++)
		{
			SetPixel(dc,start_x,start_y,color);
			start_x += x_unit;
			error_term+=ydiff;
			if(error_term>xdiff)
			{
				error_term-=xdiff;
				start_y+=y_unit;
			}
		}
	}
	else
	{
		int length = ydiff+1;
		for(int i = 0; i < length; i++)
		{
			SetPixel(dc,start_x,start_y,color);
			start_y += y_unit;
			error_term+=xdiff;
			if(error_term>0)
			{
				error_term-=ydiff;
				start_x += x_unit;
			}
			
		}
	}

	mxscr->pback->ReleaseDC(dc);
}

LPDIRECTINPUTDEVICE8 p_joy = 0;
LPDIRECTINPUT8 pdi = 0;
bool joy_exisits;
char joy_name[256];