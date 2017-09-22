#include"mx3d.h"
#include "mxmath.h"

struct customVertex {
	float x,y,z;
	DWORD color;
};


inline void not(UINT *x) {
	if(*x == MF_CHECKED)
		*x = MF_UNCHECKED;
	else if(*x == MF_UNCHECKED)
		*x = MF_CHECKED;
}

UINT tea_item = MF_UNCHECKED,box_item = MF_CHECKED;

class WireFrame : public mxApp {

	
public:

	WireFrame() {
		pmesh = ppmesh = 0;
	}
	virtual void init() {
		if(Init("WireFrame",false,0,0,640,480,WndProc,LoadIcon(NULL,IDI_APPLICATION)) == true && InitDX(false,24) == true) {
			this->screen.pd3d_dev->SetRenderState( D3DRS_LIGHTING, FALSE );
			screen.pd3d_dev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			initVB();
			InitLoop();
		}
		else
			ErrorMsg("Error Initalizing Direct3D!\n");

	}

	virtual ~WireFrame() {
		if(pmesh) pmesh->Release();
		if(ppmesh) ppmesh->Release();
	}
	
	HRESULT initVB() {

		D3DXCreateBox(screen.pd3d_dev,.5f,.5f,.5f,&pmesh,0);
		D3DXCreateTeapot(screen.pd3d_dev,&ppmesh,0);

		return S_OK;
	}


	ID3DXMesh *pmesh,*ppmesh;
	void setupMatrices() {
	D3DXMATRIXA16 mat,mat2,mat3,mat4,matrt,matval;
     UINT  iTime  = timeGetTime() % 1000;
    FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 1000.0f;
	
  	D3DXMatrixRotationX( &mat, fAngle );
	D3DXMatrixRotationY( &mat3, fAngle);
	D3DXMatrixTranslation(&mat2,1.0f,1.0f,-1.0f);
	matval = mat * mat2 * mat3;
	this->screen.pd3d_dev->SetTransform( D3DTS_WORLD,&matval);
    D3DXVECTOR3 vEyePt( 3.0f, 3.0f, 3.0f);
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    this->screen.pd3d_dev->SetTransform( D3DTS_VIEW, &matView );
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
    this->screen.pd3d_dev->SetTransform( D3DTS_PROJECTION, &matProj );
	
	}

	virtual void render(int screen) {
		this->screen.pd3d_dev->BeginScene();
		setupMatrices();
		if(tea_item == MF_CHECKED)
			ppmesh->DrawSubset(0);
		else
			pmesh->DrawSubset(0);
		//ppmesh->DrawSubset(0);
        this->screen.pd3d_dev->EndScene();
	}

	static LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {
		switch(msg) {
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			case WM_ACTIVATEAPP:
				wire.active = wParam;
				break;
			case WM_KEYDOWN:
				break;
			case WM_COMMAND: {
				static HMENU menu = GetMenu(hwnd);
				switch(wParam)
				{
				case ID_FILE_EXIT:
					SendMessage(hwnd,WM_CLOSE,0,0);
					break;
				case ID_DRAW_TEAPOT:
					not(&tea_item);
					CheckMenuItem(menu,ID_DRAW_TEAPOT,tea_item);
					break;
				case ID_HELP_ABOUT:
					MessageBox(hwnd,"Written by Jared Bruni.\n",":)",MB_OK | MB_ICONINFORMATION);
					break;
				}
				}
			    break;
			default:
				return DefWindowProc(hwnd,msg,wParam,lParam);
		}

		return 0;
	}

	static WireFrame wire;
private:
	LPDIRECT3DVERTEXBUFFER9 _vb;

};

WireFrame WireFrame::wire;

int PASCAL WinMain(HINSTANCE hInst,HINSTANCE hPrev, LPSTR lpszLine, int nCmdShow) {
	WireFrame wire;
	wire.init();
	return 0;
}