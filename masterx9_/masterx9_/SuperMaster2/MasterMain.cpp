/* SuperMaster
   written by Jared Bruni
   www.LostSideDead.com

  "Open Source, Open Mind"
*/

#include"thehead.h"// grateful as can be

MasterXHWND mxhwnd;
Intro intro;
Start start;
Game  game;
GameOver over;
Launch launch;

long _stdcall event(struct HWND__* hwnd,unsigned int msg,unsigned int wParam,long lParam);
void render(MASTERSCREEN screen);
inline void init();
HWND sethwnd,chk1,chk2,game_speed,hok,hcan;
mxJoystick stick;
LRESULT joy_enabled = 0, full_enabled = 0;
int speed = 0;
bool run_game = false;

LRESULT CALLBACK SetProc(HWND hwnd,UINT msg,WPARAM wParam , LPARAM lParam) {
	static HFONT the_font = MakeFont("Arial",18);
	switch(msg) {
		case WM_DESTROY:
			DeleteObject(the_font);
			PostQuitMessage(0);
			break;
		case WM_CREATE: {
			HWND st = CreateWindow("Static","Joystick Device: ", WS_CHILD | WS_VISIBLE, 10,10,200,25,hwnd,0,GetModuleHandle(0),0);
			__mxhwnd.input.Init(hwnd);
			stick.Init(hwnd,__mxhwnd.input.pdi);
			if(!joy_exisits) {
				SendMessage(st,WM_SETTEXT,strlen("Joystick Not Detected!.\n"), (LPARAM)(LPCSTR)"Joystick Not Detected!.\n");
			}
			else {
				char dat[256];
				sprintf(dat, "Joystick: %s", joy_name);
				SendMessage(st,WM_SETTEXT,strlen(dat),(LPARAM)(LPCSTR)dat);
			}
			stick.Free();
			__mxhwnd.input.Free();
			chk1 = CreateWindow("Button","Enable Joystick",WS_CHILD | WS_VISIBLE |BS_CHECKBOX ,10,35,200,25,hwnd,(HMENU)2,GetModuleHandle(0),0);
			if(!joy_exisits) 
				EnableWindow(chk1,FALSE);
			chk2 = CreateWindow("Button", "Run fullscreen", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,10,35+25+5,200,25,hwnd,(HMENU)3,GetModuleHandle(0),0);
			HWND st2 = CreateWindow("Static","Game Speed", WS_CHILD | WS_VISIBLE, 10,35+50+5,200,25,hwnd,0,GetModuleHandle(0),0);
			
			game_speed = CreateWindow("ComboBox","",WS_CHILD | WS_VISIBLE |CBS_DROPDOWNLIST,10,35+75+5,200,25,hwnd,0,GetModuleHandle(0),0);
			hok = CreateWindow("Button","Play",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,10,35+100+10,75,25,hwnd,(HMENU)4,GetModuleHandle(0),0);
			hcan = CreateWindow("Button", "Cancel", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,90,35+100+10,75,25,hwnd,(HMENU)5,GetModuleHandle(0),0);

			SendMessage(chk1,WM_SETFONT,(WPARAM)the_font,0); 
			SendMessage(chk2,WM_SETFONT,(WPARAM)the_font,0);
			SendMessage(st, WM_SETFONT,(WPARAM)the_font,0);
			SendMessage(st2,WM_SETFONT,(WPARAM)the_font,0);
			SendMessage(game_speed,WM_SETFONT,(WPARAM)the_font,0);
			SendMessage(game_speed,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Default");
			SendMessage(game_speed,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Fast");
			SendMessage(game_speed,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Slow");
			SendMessage(game_speed,CB_SETCURSEL,0,0);


		}
		break;
		case WM_COMMAND: {
			switch(HIWORD(wParam)) {
			case BN_CLICKED:
				switch(LOWORD(wParam)) {
					case 2: {
						LRESULT rt = SendMessage(chk1,BM_GETCHECK,0,0);
						if(rt)
						SendMessage(chk1,BM_SETCHECK,0,0);
						else
						SendMessage(chk1,BM_SETCHECK,1,0);
						break;
						}
					case 3: {
						LRESULT rt = SendMessage(chk2,BM_GETCHECK,0,0);
						if(rt)
							SendMessage(chk2,BM_SETCHECK,0,0);
						else
							SendMessage(chk2,BM_SETCHECK,1,0);
						break;
						}
					case 4: {
						int the_speed = SendMessage(game_speed,CB_GETCURSEL,0,0);
						switch(the_speed) {
						case 0:
							speed = 55;
							break;
						case 1:
							speed = 5;
							break;
						case 2:
							speed = 100;
							break;
						}
						full_enabled = SendMessage(chk2,BM_GETCHECK,0,0);
						joy_enabled = SendMessage(chk1,BM_GETCHECK,0,0);
						SendMessage(hwnd,WM_CLOSE,0,0);
						run_game = true;
					}
					break;
					case 5: { SendMessage(hwnd,WM_CLOSE,0,0); }
				}
				break;
			}
		}
	    break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

void InitSet() {
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) (COLOR_3DFACE+1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(GetModuleHandle(0),MAKEINTRESOURCE(IDI_ICON1));
	wc.hIconSm = LoadIcon(GetModuleHandle(0),MAKEINTRESOURCE(IDI_ICON1));
	wc.hInstance = GetModuleHandle(0);
	wc.lpfnWndProc = (WNDPROC) SetProc;
	wc.lpszClassName = "smSetup";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wc);

	sethwnd = CreateWindow("smSetup", "SuperMaster Setup",WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,225,220,0,0,GetModuleHandle(0),NULL);
	ShowWindow(sethwnd,SW_SHOW);
	UpdateWindow(sethwnd);
}

void LoopSet() {
	MSG msg;
	while(GetMessage(&msg,0,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

int _stdcall MasterMain(struct HINSTANCE__* hInst, char* line) 
{
	InitSet();
	LoopSet();
	if(run_game == false)
		return 0;
	if(full_enabled) 
		mxhwnd.setfullflag(true);
	else
		mxhwnd.setfullflag(false);
	if(mxhwnd.CreateMasterX("MasterX",640,480,COLOR_DEFAULT,event,hInst,LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1)),NULL))
	{
		if(joy_enabled)
			stick.Init(__mxhwnd.hwnd,__mxhwnd.input.pdi);
		init();
		mxhwnd.InitLoop(render);
		if(joy_enabled)
			stick.Free();
	}

	return (0);
}

inline void init()
{
	intro.load();
	start.load();
	game.load();
	over.load();
	launch.load();

	mxhwnd.HideCursor();
	mxhwnd.InitTimer(1,speed);

	mxhwnd.SetScreen(ID_INTRO);

	mxhwnd.media.openmp3("theme.mp3");
	mxhwnd.media.play();
	
}



long _stdcall event(struct HWND__* hwnd,unsigned int msg,unsigned int wParam,long lParam)
{

	switch(msg)
	{
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
				mxhwnd.Kill();
				break;
			}

			switch(mxhwnd.GetScreen())
			{
			case ID_START:
				start.keypress(wParam);
				break;
			case ID_GAMEOVER:
				{
					over.keypress(wParam);
				}
				break;
			case ID_LAUNCH:
				{
					launch.keypress(wParam);
				}
				break;
			}
		
		}
		break;
	case WM_KEYUP:
		{
			game.keyup(wParam);
		}
		break;
	case WM_TIMER:
		{
			mxhwnd.ChangeTime();// you can use whatever type of clock
			// or timer you want to change the time for the sync changes
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return (0);
}

void render(MASTERSCREEN screen)
{
	SetFocus(mxhwnd.hwnd);

	if(joy_enabled && mxhwnd.SyncChange()) {
		static bool moved = true;
		static bool bt_dwn = true;
		stick.Update();
		if(stick.joy_st.lY > 700 && moved == true) {
			mxhwnd.SendMasterMessage(WM_KEYDOWN,VK_DOWN,0);
			moved = false;
		}
		else
			moved = true;
		if(stick.joy_st.lY < -700 && moved == true) {
			mxhwnd.SendMasterMessage(WM_KEYDOWN,VK_UP,0);
			moved = false;
		}
		else
			moved = true;

		if(stick.joy_st.lX < -700 && moved == true) {
			mxhwnd.SendMasterMessage(WM_KEYDOWN,VK_LEFT,0);
			moved = false;
		}
		else
			moved = true;
		if(stick.joy_st.lX > 700 && moved == true) {
			mxhwnd.SendMasterMessage(WM_KEYDOWN,VK_RIGHT,0);
			moved = false;
		}
		else
			moved = true;

		if(stick.joy_st.rgbButtons[0] & 0x80 && bt_dwn) {
			mxhwnd.SendMasterMessage(WM_KEYDOWN,VK_RETURN,0);
			bt_dwn = false;
		}
		else
			bt_dwn = true;
	}


	mxhwnd.SetTimeFlag();// set the time flag
	switch(screen)
	{
	case ID_INTRO:
		intro.update();
		break;
	case ID_START:
		start.update();
		break;
	case ID_GAME:
		game.update();
		break;
	case ID_GAMEOVER:
		over.update();
		break;
	case ID_LAUNCH:
		launch.update();
		break;
	}
	
	if(mxhwnd.media.poistion () >= 303439-100)
	{
		mxhwnd.media.seekto(0);
	}
}

inline void GetPointFromPos(int pos,int& x, int& y)
{
	x = 0;
	y = 0;
	
	static int startby = 75;
	static int bx,by;
	static int i;
	bx = 75; by = startby;
	int gcount = 0;
	
	
	for(i = 0; i < 700-4+24; i++)
	{
		if(i == pos)
		{
			x = bx;
			y = by;
			return;
		}
		
		by = by + 16;
		gcount++;
		if(gcount > 23)
		{
			gcount = 0;
			by = startby;
			bx = bx + 16;
		}
		
	}
}

int getoff_set()
{
	return game.getoffset();
}


void scrollleft()
{
	game.moveleft();
}

void scrollright()
{
	game.moveright();
}

void releaseparticle(int pos, int type,bool dir)
{
	game.emiter.releaseparticle (pos,type,dir);
}

void newgame()
{
	game.resetgame();
	cur_level = 1;

}

void load_level(char* levelstr)
{
	game.loadlevel(levelstr);
}


void setcredits()
{
	mxhwnd.SetScreen(ID_START);
	start.screen = 1;
}