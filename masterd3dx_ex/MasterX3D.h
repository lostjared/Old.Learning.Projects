// MasterX3D.h written by Jared Bruni
// www.lostsidedead.com
// MasterX3D Engine v.01
// I love video games =]

#ifndef MASTERX3D
#define MASTERX3D
#define D3DFVF_MASTERVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
#define XSTD __stdcall
#define XFC  __fastcall

#include <d3d8.h>

typedef int MASTERSCREEN;


// Master3D structure
struct Master3D
{
	LPDIRECT3D8             mD3D;
	LPDIRECT3DDEVICE8       mDevice;
 

	inline Master3D()
	{
		mDevice = NULL;
		mD3D = NULL;
	}

	inline ~Master3D()
	{
		if(mDevice)
		{
			mDevice->Release();
			mDevice = NULL;
		}

		if(mD3D)
		{
			mD3D->Release();
			mD3D = NULL;
		}
	}
};

// MasterX3D class
class MasterX3DHWND
{
public:
	HWND hwnd;
	Master3D m3d;

	bool CreateMaster3D(char* title,int x, int y, int width, int height,HICON icon,HCURSOR cur,WNDPROC proc,COLORREF back_color);
	WPARAM InitLoop(void (*updatex)(MASTERSCREEN));
	void Clear();
	void SetScreen(MASTERSCREEN);
	MASTERSCREEN GetScreen();
private:
	void (*update)(MASTERSCREEN);
	COLORREF bgcolor;
	bool InitD3D();
	MASTERSCREEN screenx;

};
// masterobject
struct MasterObject
{
	MasterX3DHWND* mx3d;
	MASTERSCREEN   screen;

	inline void init(MasterX3DHWND* m)
	{
		mx3d = m;
	}
};

// MasterVertex
struct MasterVertex
{
    float x, y, z, rhw; 
    DWORD color;        
};

// MasterTriangle class
class MasterTriangle : public MasterObject
{
public:
	LPDIRECT3DVERTEXBUFFER8 mVer; 
	bool InitVerBuffer(MasterX3DHWND* m);
	void Render();
	void SetVertices(MasterVertex* g_Vertices);
	bool on;
	
	inline MasterTriangle()
	{
		mVer = NULL;
		on = false;
	}

	inline ~MasterTriangle()
	{
		if(mVer)
		{
			mVer->Release();
			mVer = NULL;
		}
	}

};

int XSTD WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR line,int CmdShow);
int XSTD MasterMain(HINSTANCE hInst,LPSTR line);

#endif