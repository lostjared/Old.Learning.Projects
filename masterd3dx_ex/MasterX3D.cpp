// MasterX3D.cpp written by Jared Bruni
// www.lostsidedead.com

#include "MasterX3D.h"

// CreateMaster3D
bool MasterX3DHWND::CreateMaster3D(char* title, int x, int y, int width, int height,HICON icon,HCURSOR cur,WNDPROC proc,COLORREF back_color)
{
	 WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, proc, 0L, 0L, 
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      title, NULL };
    RegisterClassEx( &wc );

    hwnd = CreateWindow(title, title, 
                              WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
                              GetDesktopWindow(), NULL, wc.hInstance, NULL );

	if(InitD3D())
	{
      ShowWindow( hwnd, SW_SHOWDEFAULT );
      UpdateWindow( hwnd);

		return true;
	}
	else
	{
		MessageBox(0,"Unable To Initilize DirectX8","Error",MB_OK | MB_ICONERROR);
		DestroyWindow(hwnd);
		return false;
	}

}

// initilize program looop
WPARAM MasterX3DHWND::InitLoop(void (*updatex)(MASTERSCREEN))
{
	update = updatex;
	MSG msg;
    ZeroMemory( &msg, sizeof(msg) );
    while( msg.message!=WM_QUIT )
    {
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
			update(screenx);
	}

		return msg.wParam;
}

// initilize Direct3D
bool MasterX3DHWND::InitD3D()
{

	if( NULL == ( m3d.mD3D = Direct3DCreate8( D3D_SDK_VERSION ) ) )
        return false;
    D3DDISPLAYMODE d3ddm;
    if( FAILED( m3d.mD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
        return false;
    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = d3ddm.Format;
    if( FAILED( m3d.mD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &m3d.mDevice ) ) )
    {
        return false;
    }
 
	return true;
}

// clear the back to the default color
void MasterX3DHWND::Clear()
{
	 m3d.mDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );

}

// set the screen
void MasterX3DHWND::SetScreen(MASTERSCREEN scr)
{
	screenx = scr;
}

// get the current screen
MASTERSCREEN MasterX3DHWND::GetScreen()
{
	return screenx;
}

// initlize 
bool MasterTriangle::InitVerBuffer(MasterX3DHWND* mx)
{
	init(mx);

	MasterVertex g_Vertices[] =
    {
        { 150.0f,  50.0f, 0.5f, 1.0f, RGB(200,0,255), }, // x, y, z, rhw, color
        { 250.0f, 250.0f, 0.5f, 1.0f, RGB(150,0,0), },
        {  50.0f, 250.0f, 0.5f, 1.0f, RGB(255,255,255), },
    };

    if( FAILED( mx3d->m3d.mDevice->CreateVertexBuffer( 3*sizeof(MasterVertex),
                                                  0, D3DFVF_MASTERVERTEX,
                                                  D3DPOOL_DEFAULT, &mVer ) ) )
    {
        return false;
    }

    VOID* pVertices;
    if( FAILED( mVer->Lock( 0, sizeof(g_Vertices), (BYTE**)&pVertices, 0 ) ) )
        return false;
    memcpy( pVertices, g_Vertices, sizeof(g_Vertices) );
    mVer->Unlock();
	on = true;
    return true;
}

// set the vertices
void MasterTriangle::SetVertices(MasterVertex* g_Vertices)
{
	VOID* pVertices;
    if( FAILED( mVer->Lock( 0, sizeof(g_Vertices), (BYTE**)&pVertices, 0 ) ) )
        return;
    memcpy( pVertices, g_Vertices, sizeof(g_Vertices) );
    mVer->Unlock();
}

// render triangle
void MasterTriangle::Render()
{
	if(on == true)
	{

	mx3d->m3d.mDevice->SetStreamSource( 0, mVer, sizeof(MasterVertex) );
    mx3d->m3d.mDevice->SetVertexShader( D3DFVF_MASTERVERTEX );
    mx3d->m3d.mDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 1 );

	}
}

//**********************************************************************************************

// WinMain Program Entry Point

int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	return MasterMain(hInst,line);
}

