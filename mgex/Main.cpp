/* 
	Demonstration of MasterGraphicEx
	
	###	written by Danny Anderon

	###	www.garagegaming.com

	###	garageguy@garagegaming.com
*/

#include "settings.h"

MasterXHWND mxhwnd;// masterX hwnd

//image we are playing with
MasterGraphicEx image;
//zoom scale factor
float scale_factor = 1.0f;
//clipping area
RECT clip_rect;
bool menu_visible = false;

// callback functions
long _stdcall event(struct HWND__* hwnd,unsigned int msg, unsigned int wparam, long lparam);
void render(int screen);

// main entry point
int _stdcall MasterMain(HINSTANCE hInst,char* line)
{
	if(mxhwnd.CreateMasterX("MasterX",SC_WIDTH,SC_HEIGHT,BITS_PER_PIXEL,event,hInst,NULL,NULL))
	{

		mxhwnd.LoadGraphic (&image, "intro.bmp");
		ShowCursor (FALSE);
		//set clipping rect
		clip_rect.left = SC_WIDTH/30; 
		clip_rect.top = SC_HEIGHT/30;
		clip_rect.right = clip_rect.left + SC_WIDTH - (SC_WIDTH/15);
		clip_rect.bottom = clip_rect.top + SC_HEIGHT - (SC_HEIGHT/15);

		return (mxhwnd.InitLoop(render));
	}

	return (0);
}


// draw function
void render(int screen)
{

	int scale_width = int(SC_WIDTH*scale_factor);
	int scale_height = int(SC_HEIGHT*scale_factor);

	//draw the graphic
	image.DisplayGraphic_scale_clip (
		//center of screen
		(SC_WIDTH>>1) - (scale_width>>1), 
		(SC_HEIGHT>>1) - (scale_height>>1), 
		//size to scale to
		scale_width, scale_height,
		//clipping area
		&clip_rect );

	//top of rect
	mxhwnd.paint.mxhorizontalline (clip_rect.left, clip_rect.right, 
		clip_rect.top, BOX_COLOR);

	//right side of rect
	mxhwnd.paint.mxverticalline (clip_rect.top, clip_rect.bottom, 
		clip_rect.right, BOX_COLOR);

	//bottom of rect
	mxhwnd.paint.mxhorizontalline (clip_rect.left, clip_rect.right, 
		clip_rect.bottom, BOX_COLOR);
	//left side of rect
	mxhwnd.paint.mxverticalline (clip_rect.top, clip_rect.bottom, 
		clip_rect.left, BOX_COLOR);

	//zoom percentage
	mxhwnd.text.sprinttext(0,0, " ZOOM: %i %%", int(scale_factor*100));
	
	//menu
	if (menu_visible)
	{
	mxhwnd.text.sprinttext (0, SC_HEIGHT - 45, "| Esc to EXIT | + to ZOOM_IN | - to ZOOM_OUT | w to restore graphic | q to grayscale | b to brighten |");
	mxhwnd.text.sprinttext (0, SC_HEIGHT - 25, "| d to darken | e to add red | r to add green | t to add blue | y to minus red | u to minus green | i to minus blue |");

	}
	else
	{
	mxhwnd.text.sprinttext (0, SC_HEIGHT - 20, "| Press spacebar for menu |");
	}
}

void clean_up ()
{
	ShowCursor (TRUE);
	mxhwnd.Kill();

}

// event callback
long _stdcall event(struct HWND__* hwnd,unsigned int msg, unsigned int wparam, long lparam)
{
	switch(msg)
	{
	case WM_ACTIVATEAPP:
		mxhwnd.activeapp = wparam;
		break;
	case WM_KEYDOWN:
		{
			switch(wparam)
			{
			case VK_ESCAPE:
				clean_up ();
				break;
			//complement
			case 'C':
				image.apply_complement ();
				break;
			//grayscale
			case 'Q':
				image.apply_grayscale ();
				break;
			//restore graphic
			case 'W':
				image.ReLoadGraphic ();
				break;
			//brighten
			case 'B':
				image.apply_brighten (ZOOM_INCREMENT);
				break;
			//darken
			case 'D':
				image.apply_darken (ZOOM_INCREMENT);
				break;

			//add red
			case 'E':
				image.apply_balance (ZOOM_INCREMENT, 0, 0);
				break;
			//add blue
			case 'R':
				image.apply_balance (0, ZOOM_INCREMENT, 0);
				break;
			//add green
			case 'T':
				image.apply_balance (0, 0, ZOOM_INCREMENT);
				break;

			//add red
			case 'Y':
				image.apply_balance (-ZOOM_INCREMENT, 0, 0);
				break;
			//add blue
			case 'U':
				image.apply_balance (0, -ZOOM_INCREMENT, 0);
				break;
			//add green
			case 'I':
				image.apply_balance (0, 0, -ZOOM_INCREMENT);
				break;
			//zoom in
			case VK_ADD:
				if ((scale_factor += ZOOM_INCREMENT) > ZOOM_HIGH)
				{
					scale_factor = ZOOM_HIGH;
				}
				break;
			//zoom out
			case VK_SUBTRACT:
				if ((scale_factor -= ZOOM_INCREMENT) < ZOOM_LOW)
				{
					scale_factor = ZOOM_LOW;
				}
				break;
			case VK_SPACE:
				menu_visible = !menu_visible;
				break;
			}
		}
		break;

	default: return DefWindowProc(hwnd,msg,wparam,lparam);
	}

	return (0);
}
