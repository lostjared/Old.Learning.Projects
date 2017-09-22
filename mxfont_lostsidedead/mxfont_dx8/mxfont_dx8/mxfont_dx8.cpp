#include<windows.h>
#include<d3d8.h>
#include "mxFont.h"

HWND hwnd;
LPDIRECT3D8 d3dobj;
LPDIRECT3DDEVICE8 device;
D3DLOCKED_RECT lr;
DWORD *udata;
int dh,dw,w_w = 640,w_h = 480;
WPARAM active;
mxFont mxf,mxf2;

inline int getRval(int x) {
    return (unsigned char) x;   
}

inline int getGval(int x) {
       return ((unsigned char)((x)>>8));
}
inline int getBval(int x) {
       return ((unsigned char)((x)>>16));
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {

	switch(msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_ACTIVATEAPP:
			active = wParam;
			break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

void _SetPixel(int x, int y, DWORD color, int pitch, DWORD *data)
{
	if( ( x > dw ) || ( x < 0 ) ) 
		return;
	if( y > dh || y < 0 )
		return;
	data[(((pitch/4) * y) + x )] = color;
}

bool DX_printtextf(struct mxFont *m,int x, int y, const char *str, ...) {
	int prev_x = x;
	int offset_x = prev_x, offset_y = y;
	int width = 0, height = 0;

	char text[5000];
	va_list list;
	va_start(list, str);
	vsprintf((char*)text,str,list);
	va_end(list);

	for(unsigned int p = 0; p < strlen(text); p++) {
		if(text[p] == '\n') {
			offset_x  = prev_x;
			offset_y += height;
			if(offset_y+height >= w_h) 
				return false;
			continue;
		}
		if(offset_x >= w_h) {
			offset_x = prev_x;
			offset_y += height;
		}

		for(int i = 0; i < m->mx; i++) {
			for(int z = 0; z < m->my; z++) {

				if(m->letters[text[p]].fnt_ptr[i][z] != m->tcolor) {
					_SetPixel(offset_x+i,offset_y+z,D3DCOLOR_XRGB(getRval(m->letters[text[p]].fnt_ptr[i][z]),getGval(m->letters[text[p]].fnt_ptr[i][z]),getBval(m->letters[text[p]].fnt_ptr[i][z])),lr.Pitch, udata);
					width=i;
					if(height < z)
						height=z;
				}
			}       

		}
		offset_x += width;
	}

	return true;
}

int InitDevice(HWND hwnd, int w, int h, bool windowed, LPDIRECT3DDEVICE8 *p_device)
{
	D3DPRESENT_PARAMETERS d3d_pp;
	D3DDISPLAYMODE dp_mode;
	HRESULT rt = 0;
	if(*p_device)
		(*p_device)->Release();

	dh = h, dw = w;

	ZeroMemory(&d3d_pp,sizeof(D3DPRESENT_PARAMETERS));
	rt = d3dobj->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&dp_mode);
	if(FAILED(rt))
		return 2;

	d3d_pp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3d_pp.BackBufferWidth = w;
	d3d_pp.BackBufferFormat = windowed ? dp_mode.Format : D3DFMT_X8R8G8B8;
	d3d_pp.BackBufferHeight = h;
	d3d_pp.BackBufferCount = 1;
	d3d_pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3d_pp.hDeviceWindow = hwnd;
	d3d_pp.Windowed = (BOOL) windowed;
	d3d_pp.EnableAutoDepthStencil = TRUE;
	d3d_pp.AutoDepthStencilFormat = D3DFMT_D16;
	d3d_pp.FullScreen_RefreshRateInHz = 0;
	d3d_pp.FullScreen_PresentationInterval = windowed ? 0 : D3DPRESENT_INTERVAL_IMMEDIATE;
	d3d_pp.Flags =  D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	rt = d3dobj->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3d_pp,p_device);
	if(FAILED(rt))
		return 3;

	return 1;
}

int InitDX()
{
	HRESULT rt = 0;
	d3dobj = Direct3DCreate8( D3D_SDK_VERSION );
	if(d3dobj == 0)
		return 2;
	if( (rt = InitDevice(hwnd,w_w,w_h,true,&device) ) != 1 )
	{
		return rt;
	}
	return 1;
}

void Render()
{
	HRESULT rt = 0;
	LPDIRECT3DSURFACE8 b_s;

	device->Clear(0,0,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0),1.0f,0);
	rt = device->GetBackBuffer(0,D3DBACKBUFFER_TYPE_MONO,&b_s);
	if(FAILED(rt))
		return;
	rt = b_s->LockRect(&lr,0,0);
	if(FAILED(rt))
		return;
	udata = (DWORD*)(lr.pBits);
	for(int i = 0; i < 640; i++)
		for(int z = 0; z < 480; z++)
	_SetPixel(i,z,RGB(rand()%255,rand()%255,rand()%255),lr.Pitch,udata);
	DX_printtextf(&mxf,0,0,"Hello World in MX Font D3D8\n =)");
	DX_printtextf(&mxf2,100,100,"Hello World in MX Font D3D8 \nwith a different font");


	b_s->UnlockRect();
	udata = 0;
	b_s->Release();
	b_s = 0;
	device->Present(NULL,NULL,NULL,NULL);
}

void Init() {
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	wc.hInstance = GetModuleHandle(0);
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	wc.lpszClassName = "mxFont_example";
	wc.lpszMenuName = 0;//MAKEINTRESOURCE(IDR_MENU1);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wc);

	hwnd = CreateWindow("mxFont_example", "mxFont example DirectX8",WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT,CW_USEDEFAULT,640,480,0,0,GetModuleHandle(0),0);
	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);
	if(InitDX() != 1) {
		MessageBox(hwnd,"Error Initilizing DirectX\n","Error",MB_OK);
	}

	read_font(&mxf,"terminal.mxf");
	read_font(&mxf2,"arial.mxf");

}

void Clean() {
	if(device)
	{
		device->Release();
	}

	if(d3dobj)
	{
		d3dobj->Release();
	}

	free_font(&mxf);
	free_font(&mxf2);
}

int Loop() {
	MSG msg;
	while(1)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		else if(active)
			Render();
		else if(!active)
			WaitMessage();
	}
	Clean();
	return (int)msg.wParam;
}

int PASCAL WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR lpszLine, int nCmdShow) {
	Init();
	return Loop();
}