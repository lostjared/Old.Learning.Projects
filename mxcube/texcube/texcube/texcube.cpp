#include "mx3d.h"
#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZ | D3DFVF_TEX1 )

struct Vertex
{
    float x, y, z;
    float tu, tv;
};

Vertex Vertices[] =
{
	{-1.0f, 1.0f,-1.0f,  0.0f,0.0f },
	{ 1.0f, 1.0f,-1.0f,  1.0f,0.0f },
	{-1.0f,-1.0f,-1.0f,  0.0f,1.0f },
	{ 1.0f,-1.0f,-1.0f,  1.0f,1.0f },
	
	{-1.0f, 1.0f, 1.0f,  1.0f,0.0f },
	{-1.0f,-1.0f, 1.0f,  1.0f,1.0f },
	{ 1.0f, 1.0f, 1.0f,  0.0f,0.0f },
	{ 1.0f,-1.0f, 1.0f,  0.0f,1.0f },
	
	{-1.0f, 1.0f, 1.0f,  0.0f,0.0f },
	{ 1.0f, 1.0f, 1.0f,  1.0f,0.0f },
	{-1.0f, 1.0f,-1.0f,  0.0f,1.0f },
	{ 1.0f, 1.0f,-1.0f,  1.0f,1.0f },
	
	{-1.0f,-1.0f, 1.0f,  0.0f,0.0f },
	{-1.0f,-1.0f,-1.0f,  1.0f,0.0f },
	{ 1.0f,-1.0f, 1.0f,  0.0f,1.0f },
	{ 1.0f,-1.0f,-1.0f,  1.0f,1.0f },

	{ 1.0f, 1.0f,-1.0f,  0.0f,0.0f },
	{ 1.0f, 1.0f, 1.0f,  1.0f,0.0f },
	{ 1.0f,-1.0f,-1.0f,  0.0f,1.0f },
	{ 1.0f,-1.0f, 1.0f,  1.0f,1.0f },
	
	{-1.0f, 1.0f,-1.0f,  1.0f,0.0f },
	{-1.0f,-1.0f,-1.0f,  1.0f,1.0f },
	{-1.0f, 1.0f, 1.0f,  0.0f,0.0f },
	{-1.0f,-1.0f, 1.0f,  0.0f,1.0f }
};


class CubeApp : public mxApp {
	LPDIRECT3DTEXTURE9 tex;
	IDirect3DVertexBuffer9 *g_pVertexBuffer;
public:
	CubeApp() {
		init();
	}

	~CubeApp() {
		if(tex) 
			tex->Release();
		if(g_pVertexBuffer)
			g_pVertexBuffer->Release();
	}
	virtual void init() {
		if(Init("CubeApp",false,0,0,640,480,WndProc,LoadIcon(NULL,IDI_APPLICATION) )&& InitDX(false,24)) {
			load();
			InitLoop();
		}


	}

	void load() {
		
    D3DXCreateTextureFromFile( screen.pd3d_dev, "logo.bmp", &tex );

	screen.pd3d_dev->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    screen.pd3d_dev->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

	screen.pd3d_dev->CreateVertexBuffer( 24*sizeof(Vertex),0, D3DFVF_CUSTOMVERTEX,D3DPOOL_DEFAULT, &g_pVertexBuffer, NULL );
	void *pVertices = NULL;

    g_pVertexBuffer->Lock( 0, sizeof(Vertices), (void**)&pVertices, 0 );
    memcpy( pVertices, Vertices, sizeof(Vertices) );
    g_pVertexBuffer->Unlock();

    screen.pd3d_dev->SetRenderState( D3DRS_LIGHTING, FALSE );
    screen.pd3d_dev->SetRenderState( D3DRS_ZENABLE, TRUE );

    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DXToRadian( 45.0f ), 640.0f / 480.0f, 0.1f, 100.0f );
    screen.pd3d_dev->SetTransform( D3DTS_PROJECTION, &matProj );
	}

	void drawCube() {
		_GD()->SetTexture( 0, tex );
		_GD()->SetStreamSource( 0, g_pVertexBuffer, 0, sizeof(Vertex) );
		_GD()->SetFVF( D3DFVF_CUSTOMVERTEX );

		_GD()->DrawPrimitive( D3DPT_TRIANGLESTRIP,  0, 2 );
		_GD()->DrawPrimitive( D3DPT_TRIANGLESTRIP,  4, 2 );
		_GD()->DrawPrimitive( D3DPT_TRIANGLESTRIP,  8, 2 );
		_GD()->DrawPrimitive( D3DPT_TRIANGLESTRIP, 12, 2 );
		_GD()->DrawPrimitive( D3DPT_TRIANGLESTRIP, 16, 2 );
		_GD()->DrawPrimitive( D3DPT_TRIANGLESTRIP, 20, 2 );
	}

	virtual void render(int screen) {

	static float roll = 0.0f;
	roll += 0.2f;
	D3DXMATRIX trans,rot,world,rotf;
    D3DXMatrixTranslation( &trans, 0.0f, 0.0f, 5.0f );
	D3DXMatrixRotationZ(&rot,timeGetTime()/300.0f);
	D3DXMatrixRotationYawPitchRoll( &rotf,D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(roll) );

	world = trans * rot * rotf;
	this->_GD()->BeginScene();
	
	this->_GD()->SetTransform( D3DTS_WORLD, &world );

	drawCube();

	D3DXMatrixTranslation(&trans,-1.0f,0.0f,3.0f);
	D3DXMatrixRotationZ(&rot,timeGetTime()/400.0f);
	D3DXMatrixRotationYawPitchRoll( &rotf,D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(roll) );

	world = trans * rot * rotf;
	this->_GD()->SetTransform( D3DTS_WORLD, &world);
	drawCube();

	
	D3DXMatrixTranslation(&trans,2.0f,0.0f,3.0f);
	D3DXMatrixRotationZ(&rot,timeGetTime()/300.0f);
	D3DXMatrixRotationYawPitchRoll( &rotf,D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(roll) );

	world = trans * rot * rotf;
	this->_GD()->SetTransform( D3DTS_WORLD, &world);
	drawCube();

	this->_GD()->EndScene();
	
	}

	LPDIRECT3DDEVICE9 _GD() {
		return (this->screen.pd3d_dev);
	}

	static LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {
		switch(msg) {
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			case WM_ACTIVATEAPP:
				cube.active = wParam;
				break;
			default:
				return DefWindowProc(hwnd,msg,wParam,lParam);
		}
		return 0;
	}

	static CubeApp cube;
};

CubeApp CubeApp::cube;

int PASCAL WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR lpszLine, int nCmdShow) { return 0; }