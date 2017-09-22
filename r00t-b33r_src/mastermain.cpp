// master principal


#include "thehead.h"


MasterXHWND   mxhwnd;// masterX hwnd object
//HFONT mfont = MakeFont("Arial",14); // font
klosed klosed;
intro intro;

game game;



// mastermain
int XSTD MasterMain(HINSTANCE hInst,LPSTR line)
{
	srand(time(NULL));

	// init masterX
	if(mxhwnd.CreateMasterX("Deslock",800,600,COLOR_DEFAULT,MasterProc,hInst,LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1)),NULL),LoadCursor(NULL,IDC_ARROW))//LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1)),NULL))
	{
		
		mxhwnd.InitTimer(1,1);
		
		klosed.load();
		intro.load();
		game.load();
	

		mxhwnd.SetScreen(ID_KLOSED);
		mxhwnd.HideCursor();
		
		//playgamesound(0);
		return mxhwnd.InitLoop(update);
	}
	
	return 0;
}






// masterproc callback proccess
long XSTD MasterProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_ACTIVATEAPP:
		mxhwnd.activeapp = wParam; 
		break; 
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		{
			
		
			
				switch(mxhwnd.GetScreen())
				{
				
				case ID_KLOSED:
					mxhwnd.SetScreen(ID_INTRO);
					break;
				case ID_INTRO:
					mxhwnd.SetScreen(ID_GAME);
					break;
				case ID_GAME:
					if(mxhwnd.KeyCheck(DIK_ESCAPE) )
					{
		
					  mxhwnd.Kill();

					}
					
					
					
					break;
				//case ID_GAMEOVER:
				//	gameover.keypress(wParam);
				//	break;
				}
		
			
		
		}

	
	
	
	case WM_TIMER:
		{
			mxhwnd.ChangeTime();
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	
	return 0;
}


// update
void update(MASTERSCREEN screen)
{
	mxhwnd.SetTimeFlag();
	
	switch(screen)
	{
	case ID_KLOSED:
		klosed.update();
		break;
	case ID_INTRO:
		intro.intro_update();
		break;
	
	case ID_OPTIONS:
		//options_update();
		break;
	case ID_GAME:
		
		game.update();
	
		break;
	case ID_GAMEOVER:
		//gameover_update();
		break;
	}
	
}




