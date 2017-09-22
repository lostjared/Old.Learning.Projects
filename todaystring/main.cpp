#include <windows.h>
#include "c:\sslib\masterx.h"
#include "cr.h"
#include "resource.h"


LRESULT APIENTRY WndProc(HWND,UINT,WPARAM,LPARAM);
void destroy();
void update();
void draw();
void drawintro();
void drawmain();
void loadgraphics();
void pinit();

UINT activeapp;
MasterScreen scr;
MasterXHWND mxhwnd;
crPoem      poem;
LPDIRECTDRAWSURFACE intro[5];
LPDIRECTDRAWSURFACE gmain[3];
int screen = 0;
int cur_intro = 0;
bool cur_switch = true;
int cur_start = 0;
bool idraw = false;
int gcount = 0;
int cwait = 0;
int mlen = 0;
HWND hwnd;

int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR l,int CmdShow)
{
	MSG  msg;
	WNDCLASS wc;
	mxhwnd.scr = (MasterScreen*)&scr;


	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	wc.hInstance = hInst;
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = "LostSideDead";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);

	RegisterClass(&wc);

	hwnd = CreateWindow("LostSideDead","Master on LSD - Today",WS_POPUPWINDOW,0,0,640,490,0,0,hInst,0);

	mxhwnd.init2(hwnd);
	poem.init((MasterXHWND*)&mxhwnd);
	pinit();
	loadgraphics();

	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);

	ShowCursor(false);


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
			update();
		}
        else if (!activeapp)
		{
         WaitMessage();
		}
		 
    }

	  destroy();
	  ShowCursor(true);
	return 0;
}


LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ACTIVATEAPP:
		activeapp = wParam;
		break;
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_ESCAPE:
				{
					SendMessage(hwnd,WM_CLOSE,0,0);
				}			
				break;
			}
		}
		break;

	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

void pinit()
{
	
	poem.add("Today a 'pyschedelic string'",RGB(100,0,0));
	poem.add("-----------------------------------------------",RGB(100,0,0));
	poem.add("",RGB(100,0,0));
	poem.add("Now, happines no longer in decay.",RGB(0,0,100));
	poem.add("woke up today, with the sun in my eyes",RGB(100,100,0));
    poem.add("just the answers came, and i realized",RGB(0,100,0));
	poem.add("powerful love starts to fill me within",RGB(100,0,100));
	poem.add("i remembered that i can win.",RGB(0,0,100));
	poem.add("",RGB(0,0,0)); // NULL
	poem.add("just another dream, played back for you",RGB(0,200,200));
	poem.add("purpose is shown,",RGB(0,100,100));
	poem.add("resited and forever apart of you",RGB(100,100,100));
	poem.add("sitting in the sky,",RGB(100,100,0));
	poem.add(" i remember your words",RGB(0,100,25));
	poem.add("never will i forget,",RGB(0,100,0));
	poem.add("never will i regert.",RGB(100,0,0));
	poem.add("",RGB(0,0,0));
	poem.add("something in the way, you know",RGB(100,0,0));
	poem.add("happines, provoke me let it show",RGB(0,100,0));
	poem.add("just let it flow, the answers explode",RGB(100,0,0));
	poem.add("and i am here, the fear can disappear",RGB(200,0,0));
	poem.add("",RGB(0,0,0));
	poem.add("yes ive got to be a joker, cause you",RGB(0,0,100));
	poem.add("just dont know what i mean,",RGB(0,0,200));
	poem.add("just make it up",RGB(0,0,255));
	poem.add("make it right, make it my way,",RGB(0,100,0));
	poem.add("make it today",RGB(0,200,0));
	poem.add("its alright anyway",RGB(100,0,0));
	poem.add("TODAY",RGB(255,0,0));
	poem.add("",RGB(0,0,0));
	poem.add("play it backwards: the answers came to",RGB(100,0,100));
	poem.add("love is free, happines within me.",RGB(0,0,255));
	poem.add("yes the sun shines today",RGB(0,100,100));
	poem.add("and its here to stay",RGB(0,200,200));

}

void loadgraphics()
{
	intro[0] = DDLoadBitmap(scr.lpDD,"st_1.bmp");
	intro[1] = DDLoadBitmap(scr.lpDD,"st_2.bmp");
	intro[2] = DDLoadBitmap(scr.lpDD,"st_3.bmp");
	intro[3] = DDLoadBitmap(scr.lpDD,"st_4.bmp");
	intro[4] = DDLoadBitmap(scr.lpDD,"st_5.bmp");
	intro[5] = DDLoadBitmap(scr.lpDD,"st_6.bmp");

	gmain[0] = DDLoadBitmap(scr.lpDD,"t_1.bmp");
	gmain[1] = DDLoadBitmap(scr.lpDD,"t_2.bmp");
	gmain[2] = DDLoadBitmap(scr.lpDD,"t_3.bmp");
	gmain[3] = DDLoadBitmap(scr.lpDD,"t_4.bmp");
}


void update()
{
	mxhwnd.clear();
	draw();
	mxhwnd.update();
}

void draw()
{
	switch(screen)
	{
	case 0:
		drawintro();
		break;
	case 1:
		drawmain();
		break;
	}
}

void drawintro()
{
	HRESULT ddrval;
	RECT rcRect;
	SetRect(&rcRect,0,0,640,480);
	ddrval = scr.lpBack->BltFast(0,0,intro[cur_intro],&rcRect,DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);

	if(ddrval != DD_OK)
	{
		loadgraphics();
	}

	if(cur_switch == true)
	{

	cur_intro++;
	
	}
	else
	{
		cur_intro--;
	}


	if(cur_intro > 5)
	{
		cur_intro = 5;
		cur_switch = false;
	}

	if(cur_intro < 0)
	{
		cur_intro = 0;
		cur_switch = true;
	}

	cur_start++;

	if(cur_start > 200)
	{
		cur_start = 0;
		screen = 1;
		idraw = true;
	}

}

void drawmain()
{
	HRESULT ddrval;
	RECT rcRect;
	SetRect(&rcRect,0,0,640,480);


	ddrval = scr.lpBack->BltFast(0,0,gmain[gcount],&rcRect,DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);

	if(ddrval != DD_OK)
	{
		loadgraphics();
	}

	gcount++;

	if(gcount > 3)
	{
		gcount = 0;
	}

	if(idraw)
	{
		COLORREF bg;
		bg = RGB(rand()%255,rand()%255,rand()%255);

		mxhwnd.mxdrawrect(225,130,420,150,RGB(0,0,0),RGB(0,0,0));
		mxhwnd.mxdrawrect(225,150,420,400,bg,bg);
		mxhwnd.text.setbkcolor(RGB(0,0,0));
		mxhwnd.text.settextcolor(RGB(255,0,0));
		mxhwnd.text.printtext("Today - by the Master on LSD",226,131);
		poem.curbg = bg;
		poem.update();

		cwait++;

		if(cwait > 200)
		{
			poem.release();
			mlen++;

			if(mlen > poem.off+1)
			{
				SendMessage(hwnd,WM_CLOSE,0,0);
			}

			cwait = 0;
		}


	}
	

}


void destroy()
{

	mxhwnd.pDS->Release();
	mxhwnd.pDS = NULL;

	mxhwnd.pKeyboard->Unacquire();
	mxhwnd.pKeyboard->Release();
	mxhwnd.pDI->Release();
	mxhwnd.pDI = NULL;

	for(int i = 0; i <= 5; i++)
	{
		if(intro[i])
		{
			intro[i]->Release();
			intro[i] = NULL;
		}
	}

	for(i = 0; i <= 3; i++)
	{
		if(gmain[i])
		{
			gmain[i]->Release();
		}
	}

	scr.lpBack->Release();
	scr.lpBack = NULL;

	scr.lpFront->Release();
	scr.lpFront = NULL;

	scr.lpDD->Release();
	scr.lpDD = NULL;
}
