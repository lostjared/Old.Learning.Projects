/*

  MasterX SDK 1.9.1  ( with a Example ) 
  written by Jared Bruni
  wwww.lostsidedead.com

	" all the doubts, have been cleared from my mind
 true intentions, displayed intertwined
  peices , coming back and in tune
connecting ,showing me the dark side of the moon "

  lost, who are you?

  in thought, comfortably numb
 
*/


#include "masterx.h"
// function prototypes

long XSTD eventmodel(HWND hwnd,UINT msg, WPARAM wParam,LPARAM lParam);
void render(MASTERSCREEN screen);

MasterXHWND mxhwnd;// masterX hwnd
 


inline void init();


// master main entry point
int XSTD MasterMain(HINSTANCE hInst,LPSTR line)
{

	if ( mxhwnd.CreateMasterX (" mx 1.9.1 ", 640,480,COLOR_DEFAULT,eventmodel,hInst,NULL,NULL))
	{
		init();
		return mxhwnd.InitLoop(render);
	}

	return (0);
}

// initilize 
inline void init()
{
	mxhwnd.HideCursor();

 	mxhwnd.media.openmp3("floyd.mp3");
	mxhwnd.media.play();

	

}


// window call back function ( microsoft event driven programming model )

long XSTD eventmodel(HWND hwnd,UINT msg, WPARAM wParam,LPARAM lParam)
{
	switch ( msg ) {

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ACTIVATEAPP:
		mxhwnd.activeapp = wParam;
		break;
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_ESCAPE:
				mxhwnd.media.close();
				mxhwnd.Kill();
				break;
			}
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	
	}

	return 0;
}

// render call back function
void render(MASTERSCREEN screen)
{
	mxhwnd.text.printtext ( " hello world with masterX 1.9.1 ",10,10);
	mxhwnd.text.printtextrectf( 20,20,20+200,20+200," this is a example of a stream\nheres the second line\n masterX is # %i \n :) www.lostsidedead.com",1);
}

