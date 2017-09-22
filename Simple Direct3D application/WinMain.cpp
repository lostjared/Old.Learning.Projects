// written by jared bruni

#include <windows.h>
#include "masterx3d.h"

// callback functions
long XSTD MasterProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
void Update(MASTERSCREEN screen);

MasterX3DHWND mx3d;
MasterTriangle tri;
MasterTriangle tri2;


float mleft = 150.0f;
float mright = 50.0f;
int   mshade = 0x0;


// master main entry point
int XSTD MasterMain(HINSTANCE hInst,LPSTR line)
{
	if(mx3d.CreateMaster3D("MasterX3D",0,0,640,480,NULL,NULL,MasterProc,NULL))
	{
		
		tri.InitVerBuffer(&mx3d);
		tri2.InitVerBuffer(&mx3d);

		mx3d.SetScreen(0);
		return mx3d.InitLoop(Update);
	}

	return 0;
}

// masterproc callback function
long XSTD MasterProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;

        case WM_PAINT:
		//	Update();
            ValidateRect( hWnd, NULL );
            return 0;
		case WM_KEYDOWN:
			{
				switch(wParam)
				{
				case VK_ESCAPE:
					{
	
					}
					break;
				case VK_LEFT:
					{
						mleft -= 10;
					}
					break;
				case VK_RIGHT:
					{
						mleft += 10;
					}
					break;
				case VK_UP:
					{
						mright += 100;
					}
					break;
				case VK_DOWN:
					{
						mright -= 100;
					}
					break;
				}
			}
			break;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}

void Update(MASTERSCREEN screen)
{
	mx3d.Clear();
    mx3d.m3d.mDevice->BeginScene();
   	MasterVertex Vertices[] =
    {
        { mleft,  50.0f, 0.5f, 1.0f, RGB(mshade,0,0), }, // x, y, z, rhw, color
        { 250.0f, 250.0f, 0.5f, 1.0f, RGB(150,mshade,0), },
        {  50.0f, 250.0f, 0.5f, 1.0f, RGB(255,255,mshade), },
    };
	 MasterVertex Vertices2[] =
    {
        { 10,  50.0f, mright, 1.0f, RGB(mshade,0,0), }, // x, y, z, rhw, color
        { 250.0f, 250.0f, 0.5f, 1.0f, RGB(150,mshade,0), },
        {  mright, mright, 0.5f, 1.0f, RGB(255,255,mshade), },
    };

	tri.SetVertices(Vertices);
	tri2.SetVertices(Vertices2);

	tri2.Render();
	tri.Render();
 
    // End the scene
    mx3d.m3d.mDevice->EndScene();
    
    // Present the backbuffer contents to the display
    mx3d.m3d.mDevice->Present( NULL, NULL, NULL, NULL );
}
