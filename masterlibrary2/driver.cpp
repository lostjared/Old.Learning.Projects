/* heres a example driver using masterlibrary2 */
/* this is going to use some of the C++ features of the library */
/* if you try to use C features with the C++ compiler you will get errors like
c:\masterlibrary2\masterlibrary2.h(305) : error C2440: '=' : cannot convert from 'void *' to 'char *'
thats becuase theres differences between C and C++ they are fairly small so make sure
to read all the directions to know how to use which defines for which languages ! 
if you get linking errors, remember to link to the right librarys, inside the 
header file it explains what librarys to  link to !*/


#define MASTERXSDK
#include "masterlibrary2.h"

// the MasterXHWND 
MasterXHWND mxhwnd;


LRESULT APIENTRY event(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void render(MASTERSCREEN screen);

int _stdcall MasterMain(struct HINSTANCE__* hInst, char* line)
{
	if(mxhwnd.CreateMasterX("MasterX Skeleton",640,480,COLOR_DEFAULT,event,hInst,NULL,NULL))
	{
		return mxhwnd.InitLoop(render);
	}

	return (0);
}


LRESULT APIENTRY event(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ACTIVATEAPP:
		mxhwnd.activeapp = wParam;
		break;
	case WM_KEYDOWN:
		{
			if(wParam == VK_ESCAPE)
			{
				mxhwnd.Kill();
			}
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return (0);
}

void render(MASTERSCREEN screen)
{
	mxhwnd.text.printtext(" press escape to exit..",0,0);
}