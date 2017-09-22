// main code module
#include "mxhead.h"

/*

  Tile Map Engine:

  using MasterXHWND object
  
	http://www.lostsidedead.com/gameprog/
*/

tileEngine engine;
// application entry point
int _stdcall MasterMain(HINSTANCE hInst,LPSTR line)
{
	if(mxhwnd.CreateMasterX("mxhwnd",640,480,COLOR_DEFAULT,MasterProc,hInst,LoadIcon(NULL,IDI_APPLICATION),LoadCursor(NULL,IDC_ARROW)))
	{
		engine.init(&mxhwnd);
		return mxhwnd.InitLoop(update);
	}

	return 0;
}
// master window message proccess
long _stdcall MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ACTIVATEAPP:
		{
			mxhwnd.activeapp = wParam;
		}
		break;
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_ESCAPE:
				{
#ifdef iDEBUG
					mxhwnd.Kill();
#endif
				}
				break;
			}
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}
// update the screen
void update(MASTERSCREEN screen)
{

	engine.update();
#ifdef iDEBUG
	mxhwnd.text.printtext("debug- here for free press esc",10,10);
#endif
}