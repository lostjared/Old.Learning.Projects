/* Lost Side Dead*/
// simulation of lsd hallicunations using windows graphics device interface
// emailme: master322@aol.com
// well heres the thought thats on my mind:
// Lost Side Dead


/* explanation:

 ' the ->intellagnce<- and being ->intellagent<-, are two things
  i believe alot of people get mixed up. i believe
  that ->intellagnce<- is not something which some individual
  is granted with. i believe it is something, an individual
  can express. life is simply choices. Your thoughts in there
  pure state have no properties, your will forms it to create
  what you desire if you know it or not. Life is so perfect
  things can seem anyway you want because thats what they are.
  ->intellagnce<- is something which is in all of us, it is how you
  express it which creates the changes you want, know how you
  say it.' 


*/

// preprocesscor directives
#include <windows.h>
#include "masterx.h"
#include "resource.h"
#include <string.h>
#include <time.h>

// stuff
#define TRIP1 1
#define TRIP2 2
#define TRIP3 3
#define TRIP4 4
#define TRIP5 5
#define TRIPALL 420
#define TRIPQUESTION 69
#define TRIPINTRO 200
#define TRIPRESULTS 100
#define TRIPFOURTNE 101



#define LT 1
#define LQ 0


#define trip_debug false // toggle when nessicary
#define trip_esc   true // ditto :)



// message prototypes
LRESULT APIENTRY WndProc(HWND,UINT,WPARAM,LPARAM);
void game_update();
void draw_bg();
// bgstars 
void draw_bgstar();
void draw_bgsquare();
void draw_bgtrip();
void draw_trip1();
void draw_trip2();
void draw_trip3();
void draw_trip4();
void draw_trip5();
void draw_tripproc();
void drawtime();
void initpoem();
void drawpoem();
void drawlost();
void draworb();
void drawtwist();
void drawaround();
void drawaround2();
void drawquestion();
void drawintro();
void mtrip_off();
void mtrip_on();
bool bfilp(bool);
void loadgraphics();
void killgrpahics();
void initlsd();
void lsd_keypress(WPARAM wParam);
void draw_keys();
char fixkey(int key,int caps,bool cmd);
void answerq(char* answer);
void displayerror(char* errorstr);
void displaysuc(char* sucstr);
void drawresults();
void procfourtne();
void drawfourtne();

// death
void kill();
// variables
char errorstr[100];
int  errorcount = 0;
bool erroron = false;
HWND main;
MasterXHWND game;
UINT activeapp;
int colormove = 0;
int tripscreen = TRIPINTRO;
// this program takes a few variables :)
int sx;
int sy;
int sw;
int sh;

int sf;
int so;

int fillr = 200;
int fillg = 0;
int fillb = 0;

int outlineb = 100;
int outlineg = 0;
int outliner = 0;

bool strobebg;
int  strobecount = 0;

char curmsg[100];
int msgcount = 0;
int msgx = 100;
int msgy = 100;
int sx2 = 0;
int sy2 = 0;
int sw2 = 640;
int sh2 = 480;
int sx2x = 10;
int sy2y = 10;
int s2_fr = 0;
int s2_fg = 0;
int s2_fb = 0;
int s2_or = 0;
int s2_og = 0;
int s2_ob = 0;
int s2_switch = 0;
int s2_change = 0;
int sx3 = 0;
int sy3 = 0;
int sw3 = 640;
int sh3 = 480;
int s3_fr = 100;
int s3_fg = 0;
int s3_fb = 0;
int s3_or = 150;
int s3_og = 0;
int s3_ob = 0;
int s3_space = 0;
COLORREF s3_f;
COLORREF s3_o;
int tcount = 0;
int tx = 640;
int ty = 0;
bool txs = true;
bool tys = false;
int t_x = 0;
int t_y = 0;
int px;
int py;
int p_fr = 200;
int p_fg = 0;
int p_fb = 0;
int p_or = 0;
int p_og = 0;
int p_ob = 0;
int p_index = 0;
int px_index = 0;
bool die = false;
HFONT p_font;
HFONT lsd_font;
int lsd_x = 0;
int lsd_y = 0;
int lsd_rate = 0;
int bgindex = 0;
int bgcount = 0;
int hcount = 0;
bool hon = false;
int h_or = rand()%255,h_og = rand()%255,h_ob = rand()%255;
int h_fr = rand()%255,h_fg = rand()%255,h_fb = rand()%255;
int yp_index = 0;
int t4x = 0;
int t4y = 0;
int t4w = 0;
int t4h = 0;
COLORREF t4_fill;
COLORREF t4_out;
int orb_x = 0,orb_y = 0;
int orb_fr = rand()%255,orb_fg = rand()%255,orb_fb = rand()%255;
int orb_or = rand()%255,orb_og = rand()%255,orb_ob = rand()%255;
int orb_len = 0;
bool orb_state = true;
bool trip_on = false;
int t5x = 0,t5y = 0,t5h = 20,t5w = 20;
int t5_fr = rand()%255,t5_fg = rand()%255,t5_fb = rand()%255;
int t5_or = rand()%255,t5_og = rand()%255,t5_ob = rand()%255;
int twist_len = 0;
bool twist_on = false;
bool orb_on = false;
bool around_on = false;
int lcount = 0;
bool im_trippin = true;
int  trip_add = rand()%10;
LPDIRECTDRAWSURFACE thesurf[10];
int intro_x = 0;
int intro_y = 0;
bool lsd_cr = false;
// question colors/fonts/other variables ;)

COLORREF bk_black = RGB(0,0,0);
COLORREF bk_white = RGB(255,255,255);
COLORREF bk_red = RGB(200,0,0);
COLORREF bk_blue = RGB(0,0,200);
HFONT 	bk_font = CreateFont(15,0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,NONANTIALIASED_QUALITY,VARIABLE_PITCH,"FixedSys"); 
HFONT 	bk_sfont = CreateFont(10,0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,NONANTIALIASED_QUALITY,VARIABLE_PITCH,"FixedSys"); 
HFONT   bk_afont = CreateFont(12,0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,NONANTIALIASED_QUALITY,VARIABLE_PITCH,"Arial"); 
int bk_x = 250;
int bk_y = 100;
bool bk_uswitch = true;
int bk_count = rand()%10;
int bk_index = 0;
bool bk_color = false;
bool prank_on = false;
int  ft_index = 11;



struct poem {

	COLORREF fore;
	COLORREF back;
	bool used;
	int  index;
	char msg[100];
	int type;
	char answer[100];
	bool answer_t;
	char trip[100];


};

int poslevel = NULL;
char posrank[100];
char fourtne[100];


poem xpoem[22];
poem ypoem[22];
poem lsd_q[19];// 20 acid quesitons (questions are init 1 at a time) linked list
poem lsd_a[19];// 20 acid questions (questions are init 1 at a time) linked list
int  lsd_cur = 0;

char lsd_str[100];
int trip_index = 0;
int trip_max = rand()%5000;
int bgrs = 0;
char lsd_input[100];
int  lsd_inputindex = 0;
int r_pump = rand()%255;
bool r_up = false;
char mprank[100];
int lsd_ic = 0;


MasterScreen main_scr;



// now for the clock
// counts down seconds 


// main entry to program
int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR l, int CmdShow)
{
	game.scr = (MasterScreen*)&main_scr;
	strcpy(lsd_str,"Lost Side Dead");
	MSG msg;
	WNDCLASS wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject( BLACK_BRUSH);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.hInstance = hInst;
	wc.lpszClassName = "Master";
	wc.lpszMenuName= NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	main = CreateWindowEx(WS_EX_STATICEDGE,"Master","Trippy",WS_POPUPWINDOW,0,0,640,480,0,0,hInst,0);

	strcpy(curmsg, "what is it, that your looking to see");
	game.init(main);
	loadgraphics();

	ShowWindow(main,SW_SHOW);
	UpdateWindow(main);

	initpoem();
					
	lsd_font = CreateFont(20,
        0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        "FixedSys"); //  Create a Stupid Font


  while(1)
    {
		
        int t = PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);
        if (t)
        {
            if (!GetMessage (& msg, NULL, 0, 0))
            return msg.wParam;
            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }
        
        else if (activeapp)// this is important here
		{	
		
		if(die == false)
		{

			game.clear();
			game_update();
			game.update();
		}

		}
        else if (!activeapp)
         WaitMessage();
    }



	return 0;
}
//  windows message process
LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		kill();
		PostQuitMessage(0);
		break;
	case WM_ACTIVATEAPP:
		activeapp = wParam;
		break;
	case WM_KEYDOWN:

		if(tripscreen == TRIPQUESTION)
		{
			lsd_keypress(wParam);
		}

		switch(wParam)
		{
		case VK_ESCAPE:

			if((trip_debug)||(trip_esc))
			{
				kill();
			}

			break;
		case VK_CONTROL:

		
			if(trip_esc)
			{
				tripscreen = TRIPQUESTION;
				im_trippin = false;

			}

			break;
		case VK_SPACE:

			if(tripscreen == TRIPRESULTS)
			{
					tripscreen = TRIPFOURTNE;
				im_trippin = false;
			}


			break;

		case 13:

			switch(tripscreen)
			{
			case TRIPINTRO:

				tripscreen = TRIP3;
				trip_on = true;
				im_trippin = true;
				trip_index = 0;


				break;
			case TRIPRESULTS:
			
				break;
			}

			break;
		}


		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

// update masterx game object (draw current frame)
void game_update()
{
	if(im_trippin)
	{

	draw_bg();

	}

	switch(tripscreen)
	{
	case TRIP1:
		draw_trip1();
		break;
	case TRIP2:
		draw_trip2();
		break;
	case TRIP3:
		draw_trip3();
		break;
	case TRIP4:
		draw_trip4();
		break;
	case TRIP5:
		draw_trip5();
		break;
	case TRIPALL:

		draw_trip1();
		draw_trip2();
		draw_trip3();
		draw_trip4();
		draw_trip5();

		break;
	case TRIPQUESTION:
		im_trippin = false;
		drawquestion();

		break;
	case TRIPINTRO:
		im_trippin = false;
		drawintro();
		break;
	case TRIPRESULTS:
		im_trippin = false;
		drawresults();
		break;
	case TRIPFOURTNE:

		im_trippin = false;
		drawfourtne();

		break;
	}

	if(trip_debug)
	{
		game.text.settextcolor(RGB(200,0,0));
		game.text.setbkcolor(RGB(0,0,0));
		game.text.printtext("Debug Mode On Press Esc To Exit",10,10);
	}

	if(im_trippin)
	{

		trip_index++;
		if(trip_index > 1000 + rand()%200)
		{

				tripscreen = TRIPQUESTION;
				im_trippin = false;
		}


	draw_tripproc();

	if(rand()%5 > 3)
	{

	
	draworb();

	}
	else
	{
		drawtwist();
	}

	drawtime();
	drawpoem();
	drawlost();

	if(rand()%10 > 2)
	{
		drawaround();
	}
	if(rand()%25 > 10)
	{
		drawaround2();
	}

	}

}
// turn the trippin on
void mtrip_on()
{
	im_trippin = true;
}
// turn the trippin of
void mtrip_off()
{
	im_trippin = false;
}

// draw the background for the strobe effect

void draw_bg()
{
	lcount++;

	if(strobebg)
	{
	game.mxdrawrect(0,0,640,480,RGB(0,0,0),RGB(0,0,0));
	game.text.settextcolor(RGB(255,255,255));
	game.text.setbkcolor(RGB(0,0,0));
	game.text.printtext(curmsg,msgx,msgy);	
	game.text.settextcolor(RGB(rand()%255,rand()%255,rand()%255));
	game.text.printtext(ypoem[yp_index].msg,msgx + 20,msgy + 20);
	yp_index++;
	if(yp_index > 22)
	{
		yp_index = rand()%22;
	}

	s3_f = RGB(255,255,255);
	s3_o = RGB(0,0,0);
	
	}
	else
	{
	game.mxdrawrect(0,0,640,480,RGB(255,255,255),RGB(255,255,255));
	game.text.settextcolor(RGB(0,0,0));
    game.text.setbkcolor(RGB(255,255,255));
   	game.text.printtext(curmsg,msgx,msgy);	

	s3_f = RGB(0,0,0);
	s3_o = RGB(255,255,255);
	
	}

	if(strobecount > 4)
	{
		// flip
		if(strobebg) { strobebg = false; } else { strobebg = true; }
    	strobecount = 0;
		bgcount++;
	}

	if(bgcount >15)
	{
		bgcount = 0;
		bgindex = rand()%2;
	}
	strobecount++;

	switch(bgindex)
	{
	case 0:
		draw_bgstar();
		break;
	case 1:
		draw_bgsquare();
		break;
	case 2:
		draw_bgtrip();
		break;
	}
}


// different trip screens/types of halliucnations

void draw_trip1()
{
	int x = sx;
	int y = sy;
	int w = sw;
	int h = sh;

	COLORREF fill = RGB(fillr,fillg,fillb);
	COLORREF outline = RGB(outliner,outlineg,outlineb);
	

	game.mxdrawrect(x,y,x+w,x+h,fill,outline);
	game.text.setbkcolor(outline);
	game.text.settextcolor(fill);
	game.text.printtext(curmsg,x+(w/2),y+(h/2));

	game.mxdrawroundrect(x,y,x+w-h,y+h-w,10,10,outline,fill);
	game.text.setbkcolor(fill);
	game.text.settextcolor(outline);
	game.text.printtext(curmsg,x+(w/2),y+(h/2));

	game.mxdrawellipse(x,y,x+w,x+h,outline,fill);
	game.mxdrawchord(x,y,x+w,x+h,x-y,x+outliner,x+outlineg,y+fillr,fill,outline);
	game.mxdrawpie(x,y,x+w,x+h,x-y,y-h,x+w-outliner,y+h-outlineg,fill,outline);
	
	game.text.setbkcolor(fill);
	game.text.settextcolor(outline);
	game.text.printtext(curmsg,x+(w/2),y+(h/2));


	if(x > 100)
	{
		game.mxdrawrect(x,y,x+w/2,y+h/2,RGB(fillr/2,fillg/2*2,fillb),outline);
	}

	if(x < 100)
	{
		game.mxdrawellipse(x,y,x+w/2,y+h/2,RGB(outliner,fillg,outlineb),RGB(fillr,outlineg,fillb));
	}

	if(y > 100)
	{
		game.mxdrawpie(x,y,x+w,y+h,x-(w/2),y-(h/2),x+(w/2)*2,y+(y/2)+rand()%4,fill,outline);
	}
	if(y < 100)
	{
		game.mxdrawpie(x,y,x+(w/2),y+(h/2),x+h,y-w,100,100,outline,fill);
	}

	if(y > 300)
	{
		game.mxdrawroundrect(x,y,x+(w/2),y+(h/2),x+w,y+h,outline,fill);
	}

	if(x > 300)
	{
		game.mxdrawroundrect(y,x,y+(y/2),x+(x/2),x+w,y+h,fill,outline);
	}
	
	x++;
	w--;
	y++;
	h--;

	fill = RGB(fillr,fillg,fillb);
	outline = RGB(outliner,outlineg,outlineb);

	fillr++;
	outlineb--;

	game.text.settextcolor(outline);
	game.text.setbkcolor(fill);


}

void draw_trip2()
{
	COLORREF s2_fill;
	COLORREF s2_outline;

	s2_fill = RGB(s2_fr,s2_fg,s2_fb);
	s2_outline = RGB(s2_or,s2_og,s2_ob);

	game.mxdrawroundrect(sx2,sy2,sx2+sw2,sy2+sh2,sx2x,sy2y,s2_fill,s2_outline);
	game.mxdrawroundrect(sw2,sh2,sx2+sw2,sy2+sh2,sx2x,sy2y,s2_outline,s2_fill);
	game.mxdrawellipse(sx2,sy2,sx2+sw2,sy2+sh2,s2_fill,s2_outline);
	game.mxdrawpie(sw2,sh2,sx2+sw2,sy2+sh2,sx2x,sy2y,sx2x+s2_change,sy2y+s2_change,s2_outline,s2_fill);

	sx2++;
	sy2++;
	sw2--;
	sh2--;

	s2_fr++;
	s2_fg++;
	s2_fb++;

	s2_or--;
	s2_og--;
	s2_ob--;

	if(s2_fr > 255)
	{
		s2_fr = 0 + s2_switch + 80;
		s2_fg = 0 + s2_switch + 50;
		s2_fb = 0 + s2_switch + 10;

		s2_switch++;
	}
	if(s2_or < 0)
	{
		s2_or = 255 - s2_switch - 10;
		s2_ob = 255 - s2_switch - 80;
		s2_og = 255 - s2_switch - 50;

		s2_switch++;
	}

	if(s2_switch > 50)
	{
		s2_switch = 0;
	}

	if(sx2 > 640+500)
	{
		sx2 = 0;
	}
	if(sy2 > 480+500)
	{
		sy2 = 0;
	}

	if(sw2 < 0)
	{
		sw2 = 640;
	}

	if(sh2 < 0)
	{
		sh2 = 480;
	}
	
	s2_change++;

	if(s2_change > 640)
	{
		s2_change = 0;
	}


}

void draw_trip3()
{
	s3_space = 0;
	COLORREF s3_fill = RGB(s3_fr,s3_fg,s3_fb);
	COLORREF s3_outline = RGB(s3_or,s3_og,s3_ob);

	game.mxdrawrect(sx3,sy3,sw3,sh3,s3_fill,s3_outline);
	game.mxdrawellipse(sx3,sy3,sw3,sh3,s3_fill,s3_outline);

	for(int z = 0; z < 3; z++)
	{

	game.mxdrawellipse(sx3-s3_space,sy3-s3_space,sw3-s3_space,sh3-s3_space,RGB(rand()%255,rand()%255,rand()%255),RGB(rand()%255,rand()%255,rand()%255));

	s3_space = s3_space + 2;
	}

	if((sw3 > 100) && (sh3 > 100))
	{
		game.text.setbkcolor(s3_o);
		game.text.settextcolor(s3_f);
		game.text.printtext(curmsg,sx3+(sw3/2),sy3+(sh3/2));

	}

	sx3 = sx3 + 10;
	sw3 = sw3 - 10;

	if(sx3 > 640)
	{
		sx3 = 0;
		sw3 = 640;
	}

	s3_fr = s3_fr++;
	s3_or = s3_or++;

	if(s3_fr > 255)
	{
		s3_fr = 100;
		s3_or = 150;
	}

	s3_fg = s3_fg++;
	s3_og = s3_og + 5;

	if(s3_og > 255)
	{
		s3_fg = 0;
		s3_og = 50;
	}

	s3_fb = s3_fb++;
	s3_ob = s3_ob + 5;

	if(s3_ob > 255)
	{
		s3_fb = 0;
		s3_ob = 100;
	}
}

void draw_trip4()
{
	t4x = 10;
	t4y = 10;
	t4w = 30;
	t4h = 30;
	t4_fill = RGB(0,0,100);
	t4_out =  RGB(0,0,150);

	game.mxdrawellipse(t4x,t4y,t4x+t4w,t4y+t4h,t4_fill,t4_out);

}

void draw_trip5()
{
	t4x++;
	t4y--;
	t4w = t4x + 5;
	t4h = t4y + 7;
	t4w++;
	t4h++;

	game.mxdrawellipse(t4x,t4y,t4w,t4h,RGB(rand()%255,0,rand()%255),RGB(0,rand()%255,0));
	game.mxdrawpie(t4x,t4y,t4w,t4h,t4x+rand()%10,t4y+rand()%10,rand()%10,rand()%10,RGB(0,0,rand()%255),RGB(rand()%255,0,0));

}

// changes that occour so different screens can appear

void draw_tripproc()
{

	if(fillr > 255)
	{
		fillr = 0;

		fillg = fillg + 20;
		colormove++;
		lcount++;
	}

	if(lcount > 25)
	{
		orb_on = true;
	}

	if(lcount > 250)
	{
		twist_on = true;
	}

	if(lcount > 500)
	{
		around_on = true;
	}

	if(lcount > 800)
	{
		around_on = false;
	}

	if(lcount > 1000)
	{
		twist_on = false;
	}
	if(lcount > 1400)
	{
		orb_on = false;
	}

	if(lcount > 1600)
	{
		lcount = 0;
	}

	if(fillg > 255)
	{
		fillg = 0;
		fillb = fillb + 40;

	}

	if(fillb > 255)
	{
		fillb = 0;
		colormove++;
	}

	sx++;
	sw--;
	sy++;
	sh--;

	if(rand()%2 == 1)
	{

	// second color scheme
		fillr = fillr + 1;
		fillg = fillg + 1;
		fillb = fillb + 1;

		if(fillr > 255)
		{
			fillr = 0;
			fillg = 0;
			fillb = 0;
			colormove++;
		}

		if(colormove > 10)
		{
			colormove = 0;
		}

	sx--;
	sw++;
	sy--;
	sh++;
	
	}
	



	if(outlineb < 0)
	{
		outlineb = 255;
		outliner = outliner + 1;
	}
	if(outliner > 255)
	{
		outliner = 0;
		outlineg = outlineg - 1;
	}

	if(outlineg < 0) 
	{
		outlineg = 255;
	}

	if(msgx > 640)
	{
		msgx = 0;
	}
	if(msgx < 0)
	{
		msgx = 640;
	}

	if(msgy > 480)
	{
		msgy = 0;
	}
	if(msgy < 0)
	{
		msgy = 480;
	}

	msgx = msgx + fillr;
	msgy = msgy - outlineb;



	if(sx > 640)
	{
		sx = 0;
	}
	if(sx < 0)
	{
		sx = 640;
	}

	if(sw < 0)
	{
		sw = 640;
	}
	if(sw > 640)
	{
		sw = 0;
	}

	if(sy > 480)
	{
		sy = 0;
	}
	if(sh < 0)
	{
		sh = 480;
	}

	if(msgcount > 30)
	{
		int xr2;
		xr2 = rand()%35;

		switch(xr2)
		{
		case 0:
			strcpy(curmsg, "she stands there");
			break;
		case 1:
			strcpy(curmsg, "perfected delesion, of tommorow");
			break;
		case 2:
			strcpy(curmsg,"twisting thoughts, causes discomfort");
			break;
		case 3:
			strcpy(curmsg,"The execution of your mind");
			break;
		case 4:
			strcpy(curmsg,"destruction, destroy hurting , release love");
			break;
		case 5:
			strcpy(curmsg,"turning, changing becoming");
			break;
		case 6:
			strcpy(curmsg,"twisted vision eternal life");
		case 7:
			strcpy(curmsg,"changing, who am i, finding me");
			break;
		case 8:
			strcpy(curmsg,"frying , ahh its turning");
			break;
		case 9:
			strcpy(curmsg,"life long, dreams encapsulated");
			break;
		case 10:
			strcpy(curmsg,"hidden meanings, showing");
			break;
		case 11:
			strcpy(curmsg,"just for the hell of it");
			break;
		case 12:
			strcpy(curmsg,"pratice makes the master");
			break;
		case 13:
			strcpy(curmsg, "look deeper");
			break;
		case 14:
			strcpy(curmsg, "past the moon, into the s un");
			break;
		case 15:
			strcpy(curmsg,"round and round");
			break;
		case 16:
			strcpy(curmsg,"its going");
			break;
		case 17:
			strcpy(curmsg,"look out , hes coming");
			break;
		case 18:
			strcpy(curmsg,"pink purple");
			break;
		case 19:
			strcpy(curmsg,"run forest run");
			break;
		case 20:
			strcpy(curmsg,"i like mah shrimp");
			break;
		case 21:
			strcpy(curmsg,"your reprogrammed like a turkey");
			break;
		case 22:
			strcpy(curmsg,"do you use a baster");
			break;
		case 23:
			strcpy(curmsg,"haha");
			break;
		case 24:
			strcpy(curmsg,"hAhA");
			break;
		case 25:
			strcpy(curmsg,"HAHA-haha");
			break;
		case 26:
			strcpy(curmsg,"Hu-Hah some more");
			break;
		case 27:
			strcpy(curmsg,"insane in the");
			break;
		case 29:
			strcpy(curmsg,"turkey in my oven");
			break;
		case 30:
			strcpy(curmsg,"tweaker");
			break;
		case 31:
			strcpy(curmsg, "this is stupid");
			break;
		case 32:
			strcpy(curmsg, "like i saw on tv grandma");
			break;
		case 33:
			strcpy(curmsg,"i am a sin");
			break;
		case 34:
			strcpy(curmsg," Secerts )<>( f u ck <-->-dog band ?");
			break;
		case 35:
			strcpy(curmsg,"your monster appears");
			break;

		}

		msgcount = 0;
	}

	msgcount++;
	tcount++;

	if(tcount > 100)
	{
		tcount = 0;
		switch(rand()%4)
		{
		case 0:
			tripscreen = TRIP1;
			break;
		case 1:
			tripscreen = TRIP2;
			break;
		case 2:
			tripscreen = TRIP3;
			break;
		case 3:
			tripscreen = TRIP4;
			break;
		case 4:
			tripscreen = TRIP5;
			break;
		}

		// update poem index

		p_index++;
		if(p_index > 20)
		{
			p_index = 0;
			// font switch
			switch(rand()%5)
			{
			case 0:
					p_font = CreateFont(13,
        0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        "Arial"); 

				break;
			case 1:
					p_font = CreateFont(13,
        0, 0, 0, FW_NORMAL, FALSE, TRUE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        "Arial");

				break;
			case 2:
					p_font = CreateFont(17,
        0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        "Arial Bold"); 
				break;
			case 3:
					p_font = CreateFont(10,
        0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        "Verdana"); 

				break;
			case 4:
					p_font = CreateFont(20,
        0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        "Verdana"); 

				break;
			case 5:
					p_font = CreateFont(15,
        0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        "FixedSys"); 

				break;
			}



			px_index++;
			if(px_index > 3)
			{
				// kill
				// fini-objects
				SendMessage(main,WM_CLOSE,0,0);
			}
		}
	}

}

// draw the apporpiate time with font
void drawtime()
{
	 int mw;
	 mw = 70;

	 char tbuff[50];
	 _strtime(tbuff);

	 COLORREF c,c2;
	 c = RGB(rand()%255,rand()%255,rand()%255);
	 c2 = RGB(rand()%255,rand()%255,rand()%255);


	 game.mxdrawroundrect(tx,ty,tx+mw,40,t_x,t_y,c2,c);
HFONT   font = CreateFont(20,
        0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        "Arial"); //  Create a Stupid Font
HFONT oldfont;
oldfont = game.text.font;
game.text.font = font;

	game.text.setbkcolor(c2);
	game.text.settextcolor(c);
	 game.text.printtext(tbuff,tx/mw,ty);
	 game.text.font = oldfont;

	 if(txs == true)
	 {

	 tx--;
	 t_x--;

	 }

	 else
	 {
		 tx++;
		 t_y++;
	 }

	 if(tys == true)
	 {
		 ty--;
		 t_y--;
	 }
	 else
	 {
		 ty++;
		 t_y++;
	 }

	 if(tx > 640)
	 {
		 tx = 0;
		 txs = false;
		 t_x = 0;
	 }
	 if(tx < 0)
	 {
		 tx = 640;
		 txs = true;
		 t_x = 640;

	 }
	 if(ty > 480)
	 {
		 ty = 0;
		 tys = false;
		 t_y = 0;
	 }
	 if(ty < 0)
	 {
		 ty = 480;
		 tys = true;
		 t_y = 480;
	 }

	 
}

// drawing master on lsd poem / init & draw
void initpoem()
{
	// init xpoem
	strcpy(xpoem[0].msg,"Lost Side Dead - the pattern circles in my head");
	strcpy(xpoem[1].msg,"just ask me for another question today");
	strcpy(xpoem[2].msg,"press down tommorow between yesterday");
	strcpy(xpoem[3].msg,"force me to play the game with you");
	strcpy(xpoem[4].msg,"make me do and repeat it too");
	strcpy(xpoem[5].msg,"dont belong, walk in line");
	strcpy(xpoem[6].msg,"dont remember my last line");
	strcpy(xpoem[7].msg,"dont care to be,");
	strcpy(xpoem[8].msg,"never remembered forgotten and lonely.");
	strcpy(xpoem[9].msg,"twisting nothing out you agian");
	strcpy(xpoem[10].msg,"something remembering its not the end");
	strcpy(xpoem[11].msg,"to much time on your hands");
	strcpy(xpoem[12].msg,"forgot it was nothing then found 10,000 lines");
	strcpy(xpoem[13].msg,"so my answers dont fit up, dont remember");
	strcpy(xpoem[14].msg,"and dont care agian, and you prespire");
	strcpy(xpoem[15].msg,"the ground youll fall, codes hidden in line");
	strcpy(xpoem[16].msg,"and lied to me and still pretend");
	strcpy(xpoem[17].msg,"i understand and its nothing really big");
	strcpy(xpoem[18].msg,"simply suggestions you try to place within.");
	strcpy(xpoem[19].msg,"escape from something i pretend i win");
	strcpy(xpoem[20].msg,"so much about nothing ,i just do it agian.");

	// init ypoem
	strcpy(ypoem[0].msg,"came back here agian");
	strcpy(ypoem[1].msg,"forgot to ask questions");
	strcpy(ypoem[2].msg,"wound up found agian");
	strcpy(ypoem[3].msg,"everything written perfect in line");
	strcpy(ypoem[4].msg,"made up for you");
	strcpy(ypoem[5].msg,"written within my mind");
	strcpy(ypoem[6].msg,"watch the colors as they dance around");
	strcpy(ypoem[7].msg,"twisted vision, lost it right now");
	strcpy(ypoem[8].msg,"press you around, try to fuck you up");
	strcpy(ypoem[9].msg,"they never remembered and you didnt give a fuck");
	strcpy(ypoem[10].msg,"push your mouth, press your shoes");
	strcpy(ypoem[11].msg,"look at the ground, gas your blues");
	strcpy(ypoem[12].msg,"piles of money all around");
	strcpy(ypoem[13].msg,"filthy nasty stuff down town");
	strcpy(ypoem[14].msg,"get off of my stack pop that");
	strcpy(ypoem[15].msg,"trippy dip, whip stick, bullshit");
	strcpy(ypoem[16].msg,"happy little evles, dancing dwarfs");
	strcpy(ypoem[17].msg,"jungle jim banna's barba's skirt");
	strcpy(ypoem[18].msg,"hamburger meant, chinese food");
	strcpy(ypoem[19].msg,"diarea you got it to?");
	strcpy(ypoem[20].msg,"switft kick in the ass you say");
	strcpy(ypoem[21].msg,"i really give alot of love today");
	strcpy(ypoem[22].msg,"no pretending not to care , just lies anyway");


}

void drawpoem()
{
	HFONT oldfont;
	oldfont = game.text.font;
	game.text.font = p_font;
	game.text.setbkcolor(RGB(p_or,p_og,p_ob));
	game.text.settextcolor(RGB(p_fr,p_fg,p_fb));
	game.text.printtext(xpoem[p_index].msg,px,py);
	game.text.font = oldfont;

	// poem color stuff

	p_fr++;
	p_fg--;
	p_fb++;

	if(p_fr > 255)
	{
		p_fr = 0;
	}
	if(p_fg < 0)
	{
		p_fg = 255;
	}
	if(p_fb > 255)
	{
		p_fb = 0;
	}

	p_or--;
	p_og++;
	p_ob--;

	if(p_or < 0)
	{
		p_or = 255;
	}
	if(p_or > 255)
	{
		p_or = 0;
	}
	if(p_or < 0)
	{
		p_ob = 255;
	}

}

// last but not least drawing lost side dead logo floating in the back
void drawlost()
{
	HFONT oldfont;
	lsd_rate++;

	if(lsd_rate > 100)
	{
		lsd_rate = 0;
	}

	game.text.setbkcolor(s3_o);

	if(lsd_rate < 50)
	{

		game.text.settextcolor(s3_f);
	}
	else
	{
		game.text.settextcolor(RGB(0,0,rand()%255));
	}

	oldfont = game.text.font;
	game.text.font = lsd_font;
	game.text.printtext(lsd_str,lsd_x,lsd_y);
	game.text.font = oldfont;

	// lsd change

	lsd_x = lsd_x + rand()%3;
	if(lsd_x > 640) 
	{
		lsd_x = 0;
	}
	lsd_y = lsd_y + rand()%3;
	if(lsd_y > 480)
	{
		lsd_y = 0;
	}

}
// bool flip
bool bflip(bool x)
{
	if(x)
	{
		return false;
	}
	else
	{
		return true;
	}
}


// drawing of the vision bg change
// of the stars
void draw_bgstar()
{

	// the stars came down upon my eyes
	COLORREF e_fill = RGB(255,255,255);
	COLORREF f_out  = RGB(0,0,0);

	hcount++;

	// time to start trippin 
	// each bump is increase in color
	if(hcount > 300)
	{

		hcount = 0;
		hon = true;// let us know were on it now
		h_fr = h_fr+rand()%10;
		h_fg = h_fg+rand()%10;
		h_fb = h_fb+rand()%10;
		h_or = h_or+rand()%10;
		h_og = h_og+rand()%12;
		h_ob = h_ob+rand()%15;
	}

	// lets do some checks, if were over the limit, lets start over

	if(h_fr > 255)
	{
		h_fr = rand()%255;
	}
	if(h_fg > 255)
	{
		h_fg = rand()%255/rand()%100;
	}
	if(h_fb > 255)
	{
		h_fg = rand()%255/rand()%10+rand()%100;
	}
	if(h_or > 255)
	{
		h_or = rand()%10*rand()%10;
	}
	if(h_og > 255)
	{
		h_og = rand()%10;
	}
	if(h_ob > 255)
	{
		h_ob = rand()%2;
	}



	// yes we are hallicunating lets change colors
	if(hon == true)
	{
		e_fill = RGB(h_fr,h_fg,h_fb);
		f_out  = RGB(h_or,h_og,h_ob);
	}

	int ex = 0,ey = 0,ew = 10,eh = 10;

	ex = rand()%640/2,ey=rand()%480/2;

	for(int z = 0; z < 10; z++)
	{

	game.mxdrawellipse(ex,ey,ew,eh,e_fill,f_out);

	ex = ex + 10;
	ey = ey + 14;

	}

}
// of the box
void draw_bgsquare()
{
	int bx = 0,by = 0,bw = 10,bh = 10;
	COLORREF b_out,b_fill;

	int o_r = rand()%255,o_g = rand()%255,o_b = rand()%255;
	int f_r = rand()%255,f_g = rand()%255,f_b = rand()%255;

	int steep = rand()%255/rand()%10;
	int drop = rand()%255/rand()%5;

	// starting randomized color
	b_out = RGB(o_r,o_g,o_b);
	b_fill= RGB(f_r,f_g,f_b);

	for(int z = 0; z < 11; z++)
	{
		game.mxdrawrect(bx,by,bw,bh,b_out,b_fill);

		b_out = RGB(o_r + steep,o_g - drop,o_b + steep);
		b_fill = RGB(f_r - steep,f_g + drop,f_b +steep);

		bx = bx + 10;
		by = by + 5;
		bw = bx + bw;
		bh = by + bh;

		switch(rand()%5)
		{
			case 0:
				game.mxdrawellipse(bx,by,bw,bh,b_out,b_fill);
				break;
			case 1:
				game.mxdrawroundrect(bx,by,bw,bh,rand()%10,rand()%10,b_out,b_fill);
				break;
			case 2:

				for(int p = 0; p < 3; p++)
				{
					game.mxdrawellipse(bx,by,bx+3,by+3,s3_f,s3_o);
				}
				break;
		}


		switch(rand()%2)
		{
		case 0:
			strcpy(lsd_str,"Lost Side Dead");
			break;
		case 1:
			strcpy(lsd_str,"Sounds perfected");
			break;
		case 2:
			strcpy(lsd_str,"Dreams alive and in tune");
			break;
		}
	}

}
// of the reason
void draw_bgtrip()
{
	switch(rand()%3)
	{
	case 0:
	case 1:

	draw_bgstar();
	draw_bgsquare();

	break;
	case 2:
	case 3:
		draw_bgsquare();
		draw_bgstar();
		break;
	}

}

// drawing the orb
void draworb()
{

	int dx = orb_x;
	int dy = orb_y;
	int tripx = 0;
	int tripy = 0;
	
    trip_on = false;


	if(orb_state == true)
	{

	orb_len++;

	}
	else
	{
		orb_len--;
	}


	orb_fr = rand()%255;
	orb_fg = rand()%255;
	orb_fb = rand()%255;

	orb_or = rand()%255;
	orb_og = rand()%255;
	orb_ob = rand()%255;

	for(int i = 0; i < orb_len; i++)
	{

		game.mxdrawellipse(dx,dy,dx+50,dy+50,RGB(orb_fr,orb_fg,orb_fb),RGB(orb_or,orb_og,orb_ob));

		if(trip_on == true)
		{
			game.mxdrawellipse(dx+10,dy+10,dx+40,dy+40,RGB(orb_fr,orb_or,orb_fb),RGB(orb_or,orb_og,orb_fb));
		}

		if(trip_on == true)
		{
			tripx = rand()%25;
			tripy = rand()%25;
		}
		else
		{
			tripx = 0;
			tripy = 0;
		}

		dx = dx + 3 + tripx + rand()%10;
		dy = dy + 1 + tripy + rand()%10;

		orb_fr = rand()%25 + orb_fr;
		orb_fg = rand()%50 + orb_fg;
		orb_fb = rand()%50 + orb_fb;

		orb_or = orb_fr + 50;
		orb_og = orb_fg + 25;
		orb_ob = orb_fb + 50;

	}

	if(orb_len > 100)
	{
		orb_len = 100;
		orb_state = false;
		if(trip_on == true)
		{
			trip_on = false;
		}
		else
		{
			trip_on = true;
		}
	}

	if(orb_len < 0)
	{
		orb_len = 0;
		orb_state = true;
	}
}

void drawtwist()
{

	if(twist_on)
	{

	twist_len++;

	if(twist_len > 20 + rand()%200)
	{
		twist_len = 0;
	}
	
	int dx = t5x;
	int dy = t5y;
	int t5sx = rand()%255;
	int t5sy = rand()%255;

	for(int i = 0; i < twist_len; i++)
	{
		game.mxdrawellipse(dx + rand()%10,dy,dx+t5w,dx+t5h,RGB(t5_fr,t5_fg,t5_fb),RGB(t5_or,t5_og,t5_ob));

		game.mxdrawpie(dx + rand()%10 - 100,dy,dx+t5w - 100,dx+t5h,rand()%10,rand()%10,rand()%10,rand()%100,RGB(t5_fr,t5_fg,t5_fb),RGB(t5_fr,t5_fg,t5_fb));

		game.mxdrawroundrect(dx,dy,dx+t5w,dy+t5h,t5sx,t5sy,RGB(t5_fr,t5_fg,t5_fb),RGB(t5_fr,t5_fb,t5_fb));


		t5sx = t5sx + 10;
		t5sy = t5sy + 10;

		dy = dy+5;
		dx = dx+2;
	}

	t5y = t5y + 3;
	
	t5_fr++;
	t5_fg--;
	t5_fb++;

	if(t5_fr > 255)
	{
		t5_fr = 0;
	}

	if(t5_fg < 0)
	{
		t5_fg = 255;
	}
	if(t5_fb > 255)
	{
		t5_fb = 0;
	}

	t5_or--;
	t5_og++;
	t5_ob--;

	if(t5_or < 0)
	{
		t5_or = 255;
	}
	if(t5_og > 255)
	{
		t5_og = 0;
	}
	if(t5_ob > 255)
	{
		t5_ob = 0;
	}


	if(t5x > 700)
	{
		t5x = rand()%640;
		t5y = rand()%480;
	}
	if(t5y > 600)
	{
		t5x = rand()%640;
		t5y = rand()%480;
	}

	// special instances

	if(t5x == 420)
	{
		t5w++;
	}

	if(t5x == 10)
	{
		t5w++;
	}

	}

}

void drawaround()
{
	if(around_on)
	{

	game.mxdrawellipse(rand()%640,rand()%480,rand()%640,rand()%480,RGB(rand()%255,rand()%255,rand()%255),RGB(rand()%255,rand()%255,rand()%255));
    game.mxdrawpie(rand()%640,rand()%480,rand()%640,rand()%480,rand()%640,rand()%480,rand()%640,rand()%480,RGB(rand()%255,rand()%255,rand()%255),RGB(rand()%255,rand()%255,rand()%255));
	game.mxdrawroundrect(rand()%640,rand()%480,rand()%640,rand()%480,rand()%640,rand()%480,RGB(rand()%255,rand()%255,rand()%255),RGB(rand()%255,rand()%255,rand()%255));

	}
}

void drawaround2()
{

	if(around_on)
	{

     game.mxdrawchord(rand()%640,rand()%480,rand()%640,rand()%480,rand()%640,rand()%480,rand()%640,rand()%480,RGB(rand()%255,rand()%255,rand()%255),RGB(rand()%255,rand()%255,rand()%255));

	}
}


// here is the other screens (questions,intro,etc)
void drawquestion()
{


	if(lsd_cr == false)
	{
		initlsd();
		lsd_cr = true;
	}
	// here is question screen.

	game.text.setfont(bk_font);
	game.text.setbkcolor(bk_black);

	if(bk_color)
	{
		game.text.settextcolor(RGB(rand()%255,rand()%255,rand()%255));
	}
	else
	{
	game.text.settextcolor(bk_white);//colors change when typing starts till then white
	}

	game.text.printtext("Acid Test",bk_x,bk_y);// title:();
	
	
	game.text.setfont(bk_sfont);
	char qbuff[200];//current question
	char qnum[20]; // its number
	itoa(lsd_cur,qnum,10);

	strcpy(qbuff,"Question [");
	strcat(qbuff,qnum);
	strcat(qbuff,"])>");
	strcat(qbuff,lsd_q[lsd_cur].msg);


	game.text.printtext(qbuff,bk_x,bk_y+30);
	game.text.printtext("use keyboard then press enter",bk_x,bk_y+60);


	// basicly a series of questions you have to answer
	// these questions will be based on some randomization
	// and other questions you said.after questions are answered
	// a result/ acid  fortune comes up



	if(bk_uswitch)
	{

	bk_x++;
	bk_y--;

	}
	else
	{
		bk_x--;
		bk_y++;
	}

	if(bk_y < 0)
	{
		bk_index++;

		bk_y = 480;
	}

	if(bk_x > 640)
	{
		bk_index++;

		bk_x = 0;
	}

	if(bk_y > 480)
	{
		bk_index++;

		bk_y = 0;
	}
	if(bk_x < 0)
	{
		bk_index++;
		bk_x = 640;
	}

	if(bk_index + bk_index > bk_count)
	{
		bk_color = bflip(bk_color);
	}

	if(bk_index > bk_count)
	{
		bk_index = 0;
		bk_count = rand()%10;
		bk_uswitch = bflip(bk_uswitch);
	}

	draw_keys();

}

// drawing intro with bitmaps
void drawintro()
{

	game.mxdrawrect(0,0,640,480,RGB(0,0,rand()%255),RGB(rand()%255,0,0));

	int sx = 0;
	int sy = 0;
	int sw = 640;
	int sh = 480;

	COLORREF bgcoloro = RGB(rand()%255,0,0);
	COLORREF bgcolorf = RGB(rand()%255,rand()%255,rand()%255);
	

	for(int i = 0; i < 8; i++)
	{
		game.mxdrawrect(sx,sy,sw,sh,bgcolorf,bgcoloro);

		sx = sx + 3;
		sy = sy + 3;
		sw = sw - 3;
		sh = sh - 3;
	}

	game.text.setfont(bk_font);
game.text.setbkcolor(bgcolorf);
game.text.settextcolor(RGB(bgrs,0,0));

if(bgrs > 255)
{
	bgrs = 100;
}
bgrs++;

game.text.printtext("by Master on LSD",410,240);


	game.mxdrawrect(intro_x+10,intro_y+10,intro_x+300+10,intro_y+300+10,RGB(rand()%255,rand()%255,rand()%255),RGB(rand()%255,rand()%255,rand()%255));

// last draw is graphic
HRESULT ddrval;
RECT rcRect;
SetRect(&rcRect,0,0,300,300);
ddrval = game.scr->lpBack->BltFast(intro_x,intro_y,thesurf[0],&rcRect,DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
if(ddrval != DD_OK) { loadgraphics(); game.scr->lpBack->Restore(); }
// then process x,y

if(intro_x > 640+300)
{
	intro_x = 0;
}
if(intro_x < 0)
{
	intro_x = 640+300;
}

if(intro_y > 480+300)
{
	intro_y = 0;
}
if(intro_y < 0)
{
	intro_y = 480+300;
}

// information on how to make it continue

int xx;
int yy;

xx=200;
yy=130;

game.mxdrawrect(400,100,400+xx,100+yy,RGB(0,0,0),RGB(rand()%255,0,0));
game.text.setfont(bk_afont);
game.text.settextcolor(RGB(200,0,0));
game.text.setbkcolor(RGB(0,0,0));
game.text.printtext("Warning: this is your random halliucunation",410,110);
game.text.printtext("random subliminals will come to you",410,125);
game.text.printtext("afterword answer a series of questions",410,135);
game.text.settextcolor(RGB(rand()%255,0,0));
game.text.printtext("and you will recive your acid test results",410,145);
game.text.settextcolor(RGB(200,0,0));
game.text.printtext("warning: this program contains",410,155);
game.text.printtext("messages, of both good and bad",410,165);
game.text.printtext("but setup in a way so that it should relate",410,175);
game.text.printtext("to you, the time to watch counts down",410,185);
game.text.printtext("sit down and be patient, and just watch",410,200);
game.text.printtext("press enter to continue",410,210);



}


void loadgraphics()
{
	thesurf[0] = DDLoadBitmap(game.scr->lpDD,"logo.bmp");
}

void killgraphics()
{
	for(int i = 0; i < 10; i++)
	{
		if(thesurf[i])
		{
			thesurf[i]->Release();
		}
	}
}


// init the questions
void initlsd()
{

    // Freestyle input with keyword scan

	strcpy(lsd_q[11].msg,"Enter you favorite color");//color
	strcpy(lsd_q[12].msg,"Have you ever been to the merry land of oz?");//trip
	strcpy(lsd_q[13].msg,"You think that L is in the word Ladder?");//belief
	strcpy(lsd_q[14].msg,"do you have any lunch money for uncle sam?");//money
	strcpy(lsd_q[15].msg,"what thoughts come to mind as response to this program?");//imagnation
	strcpy(lsd_q[16].msg,"Do you not like these types of applications?");//negativity check
	strcpy(lsd_q[17].msg,"Did someone make you watch this?");//negativity check
	strcpy(lsd_q[18].msg,"Do you have a hard time chewing with your mouth closed?");//oddity
	strcpy(lsd_q[19].msg,"my overall thoughts on this are");//ending

	strcpy(lsd_q[11].trip,"As you walked around the sun today, ray of color: ");
	strcpy(lsd_q[12].trip,"sounds i didnt pretend to hear, stupid crap someone fears: ");
	strcpy(lsd_q[13].trip,"As someone comes around in a different way you say: ");
	strcpy(lsd_q[14].trip,"remember you like it, but then get mad anyway the answer is today: ");
	strcpy(lsd_q[15].trip,"my personal opinion exisits upon such oh my blah blah and a bunch: ");
	strcpy(lsd_q[16].trip,"if towrads a meanie, this is what i say,:");
	strcpy(lsd_q[17].trip,"those little monsters they made you say: ");
	strcpy(lsd_q[18].trip,"haha what the hell ");
	strcpy(lsd_q[19].trip,"ok you got some info , here it is: ");
	



	// True or False Questions

	strcpy(lsd_q[0].msg,"True or False abnormal is not ok");// checking there normality
	strcpy(lsd_q[1].msg,"True or False television is gods creation");// releigon
	strcpy(lsd_q[2].msg,"True or False i dont believe in sublminal messages");//faith
	strcpy(lsd_q[3].msg,"True or False i like chinese food");//automatic response check
	strcpy(lsd_q[4].msg,"True or False the law is good for me");//law
	strcpy(lsd_q[5].msg,"True or False i hate things");//anger
	strcpy(lsd_q[6].msg,"True or False i am a member of the kkk");
	strcpy(lsd_q[7].msg,"True or False the panthers ride at night");
	strcpy(lsd_q[8].msg,"True or False anger management is for children");
	strcpy(lsd_q[9].msg,"True or False i am better then others");
	strcpy(lsd_q[10].msg,"True or False i am not a space alien i live on earth");

	for(int z = 0; z < 10; z ++)
	{
		lsd_q[z].type = LT;
	}
	lsd_q[10].type = LT;

	for(z=11;z<19;z++)
	{
		lsd_q[z].type = LQ;
	}


	lsd_input[0] = 0;
	lsd_cur = 0;
	lsd_inputindex = 0;



}
//keyinput when questions asked
void lsd_keypress(WPARAM wParam)
{
		switch(wParam)
		{
		case 8:
			if(lsd_inputindex > 0)
			{
			lsd_inputindex--;
			lsd_input[lsd_inputindex] = 0;
			return;
			}
			break;
		case 16:

			return;
			break;

		case 13:

			// they pressed enter

			answerq(lsd_input);

			lsd_inputindex = 0;
			strcpy(lsd_input,"");
			lsd_input[0] = 0;
			return;

			break;
		}

		if(lsd_inputindex < 60)
		{

	lsd_input[lsd_inputindex] = fixkey((int)wParam,false,false);
	lsd_inputindex++;
	lsd_input[lsd_inputindex] = 0;

		}
}

void answerq(char* msg)
{
	// check and if answer is apporpiate then attach it, and move on
	// if its not (ex: nothing or not a T  & F when a T & F error msg

	if(lsd_q[lsd_cur].type == LT)
	{

		if((strstr(msg,"t"))||(strstr(msg,"f")))
		{
		}
		else
		{
    	displayerror("this question requires a t or a f as the answer");
		return;
		}

	}

	if(strlen(msg) == 0)
	{
		displayerror("please enter a valid string");
		return;
	}


	// answering true and false question
	if(lsd_q[lsd_cur].type == LT)
	{
		if(strstr(msg,"t"))
		{

		lsd_q[lsd_cur].answer_t = true;
		displaysuc("answer accepted as being true");

		}
		if(strstr(msg,"f"))
		{
		lsd_q[lsd_cur].answer_t = false;
		displaysuc("answer accepted as being false");
		}

		lsd_q[lsd_cur].used = true;
		
		// search for next item

		lsd_cur++;
	}

	if(lsd_q[lsd_cur].type == LQ)
	{
		if(strlen(msg) < 3)
		{
			displayerror("please enter a valid string. be creative at least");
			return;
		}

		strcpy(lsd_q[lsd_cur].answer,msg);
		lsd_q[lsd_cur].used = true;
		lsd_q[lsd_cur].index = 0;
		lsd_cur++;

		if(lsd_cur > 19)
		{
			// all done go to results page
			procfourtne();
			tripscreen = TRIPRESULTS;
		}

	}
	
}


// input keydisplay

void draw_keys()
{
	char displaystring[110];
	strcpy(displaystring,lsd_input);
	strcat(displaystring,"_");
	game.text.setfont(bk_font);
	game.text.settextcolor(RGB(rand()%255,rand()%255,rand()%255));
	game.text.printtext(displaystring,40,300);

	/* if error response */

	if(erroron)
	{
		errorcount++;
		game.text.settextcolor(RGB(200,0,0));
		game.text.printtext(errorstr,40,330);
	}

	if(errorcount > 100)
	{
		errorcount = 0;
		erroron = false;
	}
}

// the death of are program
void kill()
{
   killgraphics();
   die =true;	
   activeapp = 0;
   game.scr->lpBack->Release();
   game.scr->lpFront->Release();
   game.scr->lpBack = NULL;
   game.scr->lpFront = NULL;
   game.scr->lpDD->Release();
   game.scr->lpDD = NULL;
    PostQuitMessage(0);
}

//************ LAST IS FIXKEY
char fixkey(int key,int caps,bool cmd)
{

		char cur;	
		int shift;
		shift = 0;
		// shift switch
		if(GetAsyncKeyState(16))
		{
			shift = 1;
			if(caps)
			{
			cur = tolower(key);
			}
			else
			{
			cur = toupper(key);
			}
			// special shift character switch

			switch(cur)
			{
			case '0':
				cur = ')';
				break;
			case '1':
				cur = '!';
				break;
			case '2':
				cur = '@';
				break;
			case '3':
				cur = '#';
				break;
			case '4':
				cur = '$';
				break;
			case '5':
				cur = '%';
				break;
			case '6':
				cur = '^';
				break;
			case '7':
				cur = '&';
				break;
			case '8':
				cur = '*';
				break;
			case '9':
				cur = '(';
				break;
			}
		}
		else
		{

		if(caps)
		{
		   cur =  toupper(key);
		}
		else
		{
		   cur = tolower(key);
		}
		}

		// quick key to special char switch
		switch(key)
		{
		case 220:

			cur = '\\';

			break;

		case 191:
			if(shift)
			{
			cur = '?';
			}
			else
			{

			cur = '/';
			}

			break;

 		case 192:

			cur = 'µ';
			break;

		case 186:
			if(shift)
			{
				cur = ':';
			}
			else
			{
			cur = ';';
			}
			break;

		case 219:

			if(shift)
			{
				if(cmd == false)
				{
				cur = '{';
				}
				else
				{
                cur = '/';
				}
			}
			else
			{
				cur = '[';
			}

			break;
		case 221:
			if(shift)
			{
				if(cmd == false)
				{
				cur = '}';
				}
				else
				{
                cur = '\\';
				}
			}
			else
			{
				cur = ']';
			}

			break;
		case 187:
			if(shift)
			{
				cur = '+';
			}
			else
			{
				cur = '=';
			}
			break;
		case 189:

			if(shift)
			{
				cur = '_';
			}
			else
			{
				cur = '-';
			}

			break;
		case 188:

			if(shift)
			{
				cur = '<';
			}
			else
			{
				cur = ',';
			}

			break;

		case 190:

			if(shift)
			{
				cur = '>';
			}
			else
			{
				cur = '.';
			}


			break;
		case 222:
			if(shift)
			{
				cur = '\"';
				break;
			}
			else
			{
				cur = '\'';
				break;
			}
			


			break;

		}

		return cur;
}

// error 

void displayerror(char* buff)
{
	erroron = true;
	errorcount = 0;
	strcpy(errorstr,"error: ");
	strcat(errorstr,buff);
}

void displaysuc(char* buff)
{
	erroron = true;
	errorcount = 0;
	strcpy(errorstr,"success: ");
	strcat(errorstr,buff);
}


// the ************** RESULTS SCREEN ***************

void drawresults()
{

	game.text.printtext("Press Escape to Exit",10,10);
	game.text.setfont(bk_font);
	if(rand()%5 > 2)
	{
	game.text.settextcolor(RGB(r_pump,0,0));
	game.text.printtext("**Welcome to the Results Screen**",40,100);
	}
	else
	{
	game.text.settextcolor(RGB(rand()%255,rand()%255,rand()%255));
	game.text.printtext("**Welcome to the Results Screen**",40,100);
	}

	if(r_pump > 255)
	{
		r_up = bflip(r_up);
	}
	if(r_pump < 0)
	{
		r_up = bflip(r_up);
	}
	if(r_up)
	{
		r_pump++;
	}
	else
	{
		r_pump--;
	}

	// printing out the results

	char mposlevel[10];
	itoa(poslevel,mposlevel,10);
	char posstr[100];
	strcpy(posstr,"Positivity Level: ");
	strcat(posstr,mposlevel);

	game.text.printtext(posstr,40,140);
	char prank[100];
	strcpy(prank,"Personal Rank: Haha Look Agian");
	strcat(prank,mprank);

	game.text.printtext(prank,40,160);
	game.text.printtext("Fourtne/Acid Trip: Press Space To Continue",40,180);
	
}

// processing of your fourtne
void procfourtne()
{
	poslevel = 0;
	strcpy(posrank,"");
	strcpy(fourtne,"");

	for(int i=0;i<10;i++)
	{
		if(lsd_q[i].answer_t)
		{
			poslevel++;
		}
		else
		{
		}

	}
	// first calculate the positivity rate, out of the true false statements
	// second look for dergoatory comments in there words, and flag them

	char mprank[100];
	switch(rand()%5)
	{
	case 0:
		strcpy(mprank,"Ok");
		break;
	case 1:
		strcpy(mprank,"Good Luck");
		break;
	case 2:
	case 3:
	case 4:
	case 5:
		strcpy(mprank,"Stuck on the bottom");
		
	}


}
// drawing the fourtne
void drawfourtne()
{

	lsd_ic++;
	if(lsd_ic > 200)
	{
		ft_index++;
		lsd_ic = 0;
		game.text.settextcolor(RGB(rand()%255,rand()%255,rand()%255));
	}

	game.text.printtext(lsd_q[ft_index].trip,20,20);
	game.text.printtext(lsd_q[ft_index].answer,20,40);


	if(ft_index > 19)
	{
		tripscreen = TRIPINTRO;
		ft_index = 11;
		lsd_cur = 0;
	}

}