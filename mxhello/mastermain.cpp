/* masterX hello world example
   written by Jared Bruni
   www.LostSideDead.com

  "Open Source, Open Mind"
*/

// define the MasterX SDK
#define MASTERXSDK
#include"masterlibrary2.h"// include masterlibrary 

// function prototypes
long _stdcall event(struct HWND__* hwnd,unsigned int msg, unsigned int wparam, long lparam);
void update(MASTERSCREEN screen);
// the MasterX hwnd
MasterXHWND mxhwnd;

// initilization
int _stdcall MasterMain(struct HINSTANCE__* hInst,char* line)
{

	// create MasterX initilize the screen
	if(mxhwnd.CreateMasterX("MyProgram",640,480,COLOR_DEFAULT,event,hInst,NULL,NULL))
	{
		return (mxhwnd.InitLoop(update)); 
		/*initilize the game loop
		whatever function you have this point to
		 will be called every update the screen makes
		  use this to draw your frames */
	} 

	return (0);
}

/* call back function for events, like keypresses and mouse moves */
long _stdcall event(struct HWND__* hwnd,unsigned int msg, unsigned int wparam, long lparam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ACTIVATEAPP:
		mxhwnd.activeapp = wparam;
		break;
	case WM_KEYDOWN:
		{
			mxhwnd.Kill();
		}
		break;
	default: return DefWindowProc(hwnd,msg,wparam,lparam);
	}
	return (0);
}
/* heres the important update function which we pointed to during initilization */
void update(MASTERSCREEN screen)
{
	mxhwnd.text.printtext("Hello World Press Escape to Exit..",10,10);// every
	// frame update draw this to the screen
}