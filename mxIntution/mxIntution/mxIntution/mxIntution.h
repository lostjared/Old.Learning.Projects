/* The HPPD Shuffle-LmaSterD*/


#pragma once
#include "mx3d.h"

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);

static char *imgz[] = {"card_back.bmp", NULL};

class mxShuffle {
public:
	inline int getRval(int x) {
		return (unsigned char) x;   
	}

	inline int getGval(int x) {
		return ((unsigned char)((x)>>8));
	}
	inline int getBval(int x) {
		return ((unsigned char)((x)>>16));
	}
	void start() {
		shuffle();
		int offset_x = 800/2-110;
		for(int i = 0; i < 5; i++) {
			cards[i].x = offset_x+(20*i);
			cards[i].y = 200;
			for(int p = 0; p < 83; p++) 
				for(int q = 0; q < 118; q++) {
					cards[i].p[p][q].xv = (timeGetTime()%2 == 0) ? (-rand()%4)+1 : (rand()%4)+1;
					cards[i].p[p][q].x = offset_x+(20*i)+p;
					cards[i].p[p][q].y = 200+q;
					cards[i].p[p][q].x_off = 0;
					cards[i].p[p][q].y_off = 0;
				}
		}

		speed = 1;
		sys_timer = 0;
		sys_speed = 100;
		loadPixelData();
	}

	void loadPixelData() {
		HBITMAP hbm = (HBITMAP)LoadImage(NULL, "card_back.bmp", IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		HDC dc = GetDC(GetForegroundWindow());
		HDC cdc = CreateCompatibleDC(dc);
		SelectObject(cdc,hbm);
		for(int i = 0; i < 83; i++) 
			for(int z = 0; z < 118; z++) {
				cards[0].p[i][z].color = GetPixel(cdc,i,z);
			}

		DeleteDC(cdc);
		DeleteDC(dc);
		DeleteObject(hbm);

	}
protected:
	void shuffle() {
		memset(cards,0,sizeof(cards));
		for(int i = 0; i < 5; i++) {
			cards[i].card_id = rand()%5;
		}
	}

	bool circled;

	bool proc() {


		if(timeGetTime()%2 == 0)
			sys_timer++;

		if(sys_speed <= 0) {

			static int circle = 0;
			for(int i =0; i < 5; i++) {
				double rad = 100.0f;
				int X = int(rad * cos(cards[i].deg));
				int Y = int(rad * sin(cards[i].deg));
				switch(i) {
				case 0:
				case 2:
					cards[i].deg += 0.001f;
					break;
				case 1:
				case 3:
					cards[i].deg -= 0.001f;
					break;
				case 4:
					cards[i].deg -= 0.01f;
					break;
				}

				cards[i].dx = X;
				cards[i].dy = Y;
				if(cards[i].deg > 10)  	
					return true;
			}
		}
		else if(sys_timer > sys_speed) {

			for(int i = 0; i < 5; i++) {
				if(cards[i].x <= 800/2-110) 
					cards[i].x += 800/2-110;
				else 
					cards[i].x -= speed;
			}
			sys_timer = 0;
			sys_speed--;
		}


		return false;
	}
	void setspeed(int speed) {
		this->speed = speed;
	}

	virtual void display() = 0;

	struct TCard {
		BYTE card_id;
		int x,y,dx,dy;
		struct points {
			int xv;
			int x,x_off;
			int y,y_off;
			COLORREF color;
		};
		points p[84][118];
		float deg;

	};
	struct TCard cards[5];
	int speed,sys_timer,sys_speed;

};


class mxIntution : public mxApp , public mxShuffle {
public:

	enum { INTRO, GAME, ABOUT };
	virtual void init() {
		if(Init("mxIntution",false,0,0,800,600,WndProc,LoadIcon(NULL,IDI_APPLICATION)) && InitDX(false,32)) {
			load();
			InitLoop();
		}
	}

	inline void setCircle(bool circled) {
		this->circled = circled;
	}

	inline void load() {
		for(int i = 0; imgz[i] != NULL; i++) {
			img[i].init(&this->screen);
			img[i].setcolorkey(0x0);
			img[i].load(imgz[i]);
		}
		start();
		this->SetScreen(INTRO);
	}

	virtual void render(int screen) {
		this->screen.pd3d_dev->BeginScene();

		switch(this->GetScreen()) {
			case INTRO:
				display();
				break;
			case GAME:
				break;
		}

		this->screen.pd3d_dev->EndScene();
	}

	virtual void display() {

		text.printtextf(10,10,"HPPD Shuffle-LmaSterD");
		if(proc()) {
			paint.Lock();

			for(int p = 0; p < 5; p++)
				for(int i = 0; i < 83; i++) 
					for(int z = 0; z < 118; z++) {
					if(cards[p].p[i][z].x+cards[p].p[i][z].x_off+cards[p].dx > 0 && cards[p].dy+cards[p].p[i][z].y+cards[p].p[i][z].y_off > 0 && cards[p].p[i][z].x+cards[p].p[i][z].x_off+cards[p].dx < 800 && cards[p].dy+cards[p].p[i][z].y+cards[p].p[i][z].y_off < 600)
						paint.fast_sp(cards[p].p[i][z].x+cards[p].p[i][z].x_off+cards[p].dx,cards[p].dy+cards[p].p[i][z].y+cards[p].p[i][z].y_off,paint.rect.Pitch, D3DCOLOR_XRGB(getRval(cards[0].p[i][z].color),getGval(cards[0].p[i][z].color),getBval(cards[0].p[i][z].color)));
					if(circled == false) {
						cards[p].p[i][z].x_off += cards[p].p[i][z].xv+-rand()%5;
						cards[p].p[i][z].y_off += cards[p].p[i][z].xv+-rand()%5;
					}
					else {
						double rad = 100.0f;
					int X = int(rad * cos(cards[p].deg));
					int Y = int(rad * sin(cards[p].deg));
					cards[p].p[i][z].x_off = X;
					cards[p].p[i][z].y_off = Y;
					cards[p].deg += 0.001f;
					
					}
				}
					paint.UnLock();


		}
		else {
			for(int p = 0; p < 5; p++)
				img[0].display((float)cards[p].x+cards[p].dx,(float)cards[p].y+cards[p].dy);
		}
	}

	int get(int g) {
		return 0;
	}

	int give() {
		return 0;
	}

private:
	mxSprite img[10];
};

extern mxIntution in;
