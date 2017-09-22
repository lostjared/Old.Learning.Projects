#include "mx3d.h"
#include <math.h>

mxHwnd mxhwnd;
int type = 9;

struct mxPixel {
	int x,y;
	D3DCOLOR color;
	float d;
	mxPixel() {
		memset(this, 0, sizeof(this));		
	}
};

mxPixel pixel[800][600];


LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {

	switch(msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_ACTIVATEAPP:
			mxhwnd.active = wParam;
			break;
		case WM_KEYDOWN: {
			
			switch(tolower(int(wParam))) {
			case '1':
				type = 0;
				break;
			case '2':
				type = 1;
				break;
			case '3':
				type = 2;
				break;
			case '4':
				type = 3;
				break;
			case '5':
				type = 4;
				break;
			case '9':
				type = 9;
				break;
			case VK_RETURN:
				for(int i = 0; i < 800; i++)
					for(int z = 0; z < 600; z++) {
						pixel[i][z].x = i;
						pixel[i][z].y = z;
					}
					type = 9;
				break;
			}
			}
		    break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}


void proc() {

	int counter_i = 0, counter_z = 0;
	static double rad = 150.0;
	for(int i = 0; i < 800; i++) 
		for(int z = 0; z < 600; z++) {
			switch(type) {
			case 0:
			counter_z++;
			switch(counter_i) {
				case 1:
					pixel[i][z].x++;
					pixel[i][z].y++;
					break;
				case 2:
					pixel[i][z].x++;
					pixel[i][z].y--;
					break;
				case 3:
					pixel[i][z].y--;
					pixel[i][z].x++;
					break;
				case 4:
					pixel[i][z].x--;
					pixel[i][z].y--;
					break;
				case 5:
					pixel[i][z].d += 0.0005f;
					pixel[i][z].x -= int(rad * cos(pixel[i][z].d));
					pixel[i][z].y += int(rad * sin(pixel[i][z].d));
				case 6:
					counter_i = 0;
					break;
			}
			
			counter_i++;
			switch(counter_z) {
				case 4:
					pixel[i][z].x++;
					pixel[i][z].y++;
					break;
				case 3:
					pixel[i][z].x++;
					pixel[i][z].y--;
					pixel[i][z].color = D3DCOLOR_XRGB(rand()%255,rand()%255,rand()%255);
					break;
				case 2:
					pixel[i][z].y--;
					pixel[i][z].x++;
					break;
				case 1:
					pixel[i][z].x--;
					pixel[i][z].y--;
					break;
				case 5:
					pixel[i][z].d += 0.0005f;
					pixel[i][z].x += int(rad * cos(pixel[i][z].d));
					pixel[i][z].y -= int(rad * sin(pixel[i][z].d));
					break;
				case 6:
					counter_z = 0;
					break;
			}
					break;
			case 1:
				
				switch(counter_i) {
				case 0:
					pixel[i][z].x--;
					break;
				case 1:
					pixel[i][z].y--;
					break;
				case 2:
					pixel[i][z].x++;
					break;
				case 3:
					pixel[i][z].y++;
					break;
				case 4:
					counter_i = 0;
					break;
				}
				counter_i++;
				break;
			case 2:
				switch(counter_i) {
				case 1:
					pixel[i][z].x--;
					break;
				case 2:
					pixel[i][z].y--;
					break;
				case 3:
					pixel[i][z].x++;
					break;
				case 0:
					pixel[i][z].y++;
					break;
				case 4:
					counter_i = 0;
					break;
				}
				counter_i++;

				break;
			case 3:
				switch(counter_i) {
				case 2:
					pixel[i][z].x--;
					break;
				case 3:
					pixel[i][z].y--;
					break;
				case 1:
					pixel[i][z].x++;
					break;
				case 0:
					pixel[i][z].y++;
					break;
				case 4:
					counter_i = 0;
					break;
				}
				
				break;
			case 4:
				if(timeGetTime()%2 == 0) {
				pixel[i][z].x += (timeGetTime()%2 == 0) ? int((int)rand()%120*sin(double(rand()%180))) : -rand()%5;
				pixel[i][z].y += int((int)rand()%180*cos(double(rand()%180)));
				}
				break;
			}
		}

}

void render(int screen) {
	proc();
	mxhwnd.paint.Lock();

	int i,z;
	

	for(i = 0; i < 800; i++) 
		for(z = 0; z < 600; z++)
			if(pixel[i][z].x > 0 && pixel[i][z].y > 0 && pixel[i][z].x < 800 && pixel[i][z].y < 600)
		mxhwnd.paint.fast_sp(pixel[i][z].x,pixel[i][z].y,mxhwnd.paint.rect.Pitch,pixel[i][z].color);
	for(i=0;i<800;i++)
		for(z=0;z<600;z++)
			if(pixel[i][z].color == 0)
				mxhwnd.paint.fast_sp(i,z,mxhwnd.paint.rect.Pitch,D3DCOLOR_XRGB(rand()%255,rand()%255,rand()%255));

	mxhwnd.paint.UnLock();
}

inline void init_app() {
	for(int i = 0; i < 800; i++) {
		for(int z = 0; z < 600; z++) {
			pixel[i][z].color = D3DCOLOR_XRGB(rand()%255,rand()%255,rand()%255);
			pixel[i][z].x = i;
			pixel[i][z].y = z;
		}
	}

	SendMessage(mxhwnd.hwnd,WM_SETTEXT,255,(LPARAM)(LPCSTR)"HppdLogic press 1-5 keys to change level");

}

int PASCAL WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR lpszLine, int iCmdShow) {
	if(mxhwnd.Init("HPPD_LOGIC",false,0,0,800,600,WndProc,LoadIcon(NULL,IDI_APPLICATION)) && mxhwnd.InitDX(false,32)) {
		init_app();
		return mxhwnd.InitLoop(render);
	}

	return 0;
}