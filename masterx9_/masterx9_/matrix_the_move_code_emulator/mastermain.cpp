
// MAtrix code emulator made by Deslock   6-08-01
// Using Jared Bruni's MasterX SDK
// www.lostsidedead.com
// UPDATED by Jared to work with MasterX 9



#include "masterx.h"
// function prototypes


static HFONT matrix_font = CreateFont(24,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,"Quartz");
static HFONT bye_font = CreateFont(32,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,"Arial");




long XSTD eventmodel(HWND hwnd,UINT msg, WPARAM wParam,LPARAM lParam);
void render(MASTERSCREEN screen);

MasterXHWND mxhwnd;// masterX hwnd
 


#define MAX_VS 100   //Number of Vertical strings (V-String) at once on screen (5-150)
					//150 would be for faster computers

MasterGraphic deslock;
MasterGraphic mx;


void goodbye();
void create_string(int string_line);
void matrix_calc();
void matrix_display();
void matrix_caption();
char randomchar(int max);


int initialize;
int count;
int luck;

int inc;
int string_line;
int adder;
int factor;

bool bye;

struct string
{
	int pos_x;
	int pos_y;
	int pos_start;
	
	int color;
	int color_start;
	
	int char_numb;
	char chara[30];
	
	int speed;
};

string strs[100];





inline void init();


// master main entry point
int XSTD MasterMain(HINSTANCE hInst,LPSTR line)
{

	mxhwnd.setfullflag(false);
	if ( mxhwnd.CreateMasterX (" masterX ", 800,600,COLOR_DEFAULT,eventmodel,hInst,NULL,NULL))
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
	mxhwnd.text.setfont(matrix_font);
	mxhwnd.media.openmp3("demon.mp3");
	
	mxhwnd.LoadGraphic(&mx,"mx.bmp");
	mxhwnd.LoadGraphic(&deslock,"deslock1.bmp");
		
}


// window call back function 

long XSTD eventmodel(HWND hwnd,UINT msg, WPARAM wParam,LPARAM lParam)
{
	switch ( msg ) {

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ACTIVATEAPP:
		__mxhwnd.active = wParam;
		break;
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_ESCAPE:
				mxhwnd.media.play();
				bye=true;
				
				break;
			case VK_RETURN:
				
				mxhwnd.Kill();
				break;
			}
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	
	}

	return 0;
}


// render call back function    ( Update-like function )
void render(MASTERSCREEN screen)
{
	
	if(count>=luck)      //Allow to generate the 60 first vertical lines
	if(initialize<60)
	{
		luck = rand()%100;     // at a random delay between them (no rush!)
		initialize++;
		create_string(initialize);    
	}
	count++;
	
	
	
	
	if(bye==false)
	matrix_display();
	
	
	matrix_caption();

	
	if(bye==true)    // little ending animation
	goodbye();

	

}





// Create a new vertical string with random parameter
void create_string(int string_line)
{
	adder=string_line;							// each "adder" values represents a v-string 
	
	strs[adder].pos_x = rand()%800;				// x position on the screen
	
	strs[adder].char_numb = rand()%30;			// number of characters in the v-string
	strs[adder].speed = rand()%60+2;			// speed of a  v-string
	
	strs[adder].color_start = rand()%100+(155-62)+strs[adder].speed;       //color according to speed
	
	strs[adder].pos_start = -strs[adder].char_numb*15;
	
	
	for(int att=0;att <= strs[adder].char_numb; att++)
	{	
		
		strs[adder].chara[att] = randomchar(175);					  // I want a random char
		
	}
	
}




void matrix_display()
{

	for(adder=0; adder<MAX_VS; adder++)
	{

		
		for(inc=0; inc <= strs[adder].char_numb; inc++)
		{
		
		matrix_caption();				// draw it
		
		strs[adder].pos_y += 15;        // increment y position
		strs[adder].color -= 5;
	
		
		if(inc==strs[adder].char_numb)   // reset parameters for the next update for that v-string
		{
			strs[adder].pos_start += strs[adder].speed;
			strs[adder].pos_y = 0;
			strs[adder].color = 0;
		}
		
	
	
	
		if(strs[adder].pos_start>790 || strs[adder].pos_y >790)  // the vertical string die
		{
		strs[adder].pos_start=0;
		strs[adder].pos_y=0;
		
		create_string(adder);	// make sure the dead string will be replaced
		 
		
		}
		
		}
	
	
	}

}



//Draw (or write) it
void matrix_caption()
{

	if(bye==false)
	mxhwnd.text.settextcolor(RGB(0,strs[adder].color_start+strs[adder].color,0));
	
	mxhwnd.text.sprinttext(strs[adder].pos_x,strs[adder].pos_start+strs[adder].pos_y,"%c",strs[adder].chara[inc]);
	
}



//get a random char
char randomchar(int max)
{
	int x;
	
	do
	x = rand()%max;
	while(x <33 || x >165);   // I dont want trash chars
	
	char c;
	c = x;
	return c;
}




void goodbye()
{
	if(factor<900)
	factor+= 30;
	
	mxhwnd.text.setfont(bye_font);
	mxhwnd.paint.mxdrawellipse(400-factor,300-factor,400+factor,300+factor,RGB(255,255,255),RGB(0,255,0));
	

	
	mxhwnd.text.setbkcolor(RGB(255,255,255));

	
	mxhwnd.text.printtext("MATRIX style by DESLOCK",240,70);
	mxhwnd.paint.mxdrawrect(200,100,620,400,RGB(255,255,255),RGB(0,0,0));

	mx.DisplayGraphic(200,450);	
	deslock.DisplayGraphic(290,150);

	mxhwnd.text.settextcolor(RGB(0,0,factor/4));
	mxhwnd.text.printtext("Press RETURN",320,550);

	

}