#pragma once

#include "mx3d.h"
#include<vector>


LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);

struct mxPoint {
	int x,y,z;
	D3DCOLOR color;
	bool dir;
};

class mxStarField {
	
public:

	~mxStarField() {
		stars.empty();
	}
	mxStarField() {
		for(int i = 0; i < 400; i++) {
			Star star; stars.push_back(star);
		}
	}
	virtual void draw_stars() = 0;
protected:
	
	void proc_stars() {
		for(unsigned int i = 0; i < stars.size(); i++) {
			stars[i].y++;
			if(stars[i].y >= 600)
				stars[i].y = 0;
		}
	}

	struct Star : public mxPoint {
		int dir;
		int speed;
		Star() {
			memset(this,0,sizeof(Star));
			color = D3DCOLOR_XRGB(255,255,255);
			x = rand()%800;
			y = rand()%600;
			z = 0;
		}
	};
	std::vector<Star> stars;

};

class mxShip : public mxPoint {
public:
	virtual void draw_ship() = 0;
	
	mxShip() {
		this->x = 800/2-057;
		this->y = 500;
		this->speed = 10;
	}
protected:
	int speed;
	void proc_ship() {

	}
};

enum { part_size = 800*600 };

class mxEmiter {
public:

	
	mxEmiter() {
		memset(part,0,sizeof(part));
	}

	~mxEmiter() {
	}

	virtual void draw_particles() = 0;
	virtual void blast() = 0;
	void proc_particles(int i) {
		
		switch(part[i].z) {
			case 1: {
		if(part[i].y > 5 && part[i].x < 795)
			part[i].y--;
		else
			part[i].z = 0;
		if(part[i].y < 550) {
			part[i].dir = rand()%2 >= 1 ? true : false;
		}
		if(part[i].dir == true) {
			part[i].x += 1;
			part[i].y += 1;
			if(part[i].x > 800 || part[i].x <= 0 || part[i].y > 600 || part[i].y <= 0) {
				part[i].z = 0;
			}
		}
		}
		break;
			case 3: {
				if(part[i].x > 6 && part[i].x < 800-6 && part[i].y > 6 && part[i].y < 600-6) {
				part[i].x += (timeGetTime()%2 == 0) ? rand()%5 : -rand()%5;
				part[i].y += (timeGetTime()%2 == 0)? rand()%5 : -rand()%5;
				}
				else  {
					part[i].x = rand()%800;
					part[i].y = rand()%600;
				}
			}
			break;
		}

	}
protected:

	int getoff() {
		for(int i = 0; i < part_size; i++)
			if(part[i].z == 0)
				return i;

		return -1;
	}
	mxPoint part[part_size];

};
class mxBlast : public mxApp, public mxStarField, public mxShip, public mxEmiter {

	bool part_on;
	int  ptype;

public:
	virtual void init() {
		if(Init("mxBlast",false,0,0,800,600,WndProc,LoadIcon(NULL,IDI_APPLICATION)) && InitDX(false,24)) {
			load();
			InitLoop();
		}
	}

	virtual void render(int screen) {
		
		paint.Lock();
		keycheck();
		draw_stars();
		draw_ship();
		draw_particles();
		paint.UnLock();
	}
	
	virtual void draw_stars() {
		proc_stars();
		for(unsigned int i = 0; i < stars.size(); i++) {
			paint.fast_sp(stars[i].x,stars[i].y,paint.rect.Pitch,stars[i].color);
		}
	}

	virtual void draw_ship() {
		proc_ship();
		int i=1,i2=2,z33=3, z = 0; 
		while(-i < 057) {

			for(z=i;z<=z33&&z+mxShip::x>=0&&z+mxShip::x<800;z++)
			paint.fast_sp(mxShip::x+z,mxShip::y+z33,paint.rect.Pitch,D3DCOLOR_XRGB(rand()%255,rand()%255,rand()%255));
			z33++;
			i2++;
			i--;
		}
	}

	virtual void draw_particles() {
		for(int i = 0; i < part_size; i++)  {
			if(part[i].z == 1 || part[i].z == 2 || part[i].z == 3) {
				paint.fast_sp(part[i].x,part[i].y,paint.rect.Pitch,D3DCOLOR_XRGB(rand()%255,rand()%255,rand()%255));
				proc_particles(i);
				if(part_on == true) {
					part[i].z = ptype;
				}
			}
		}
		part_on = false;
		ptype = 0;
	}

	virtual void blast() {
		
		for(int i = 0; i < 10; i++) {
		int pos = getoff();
		if(pos != -1) {
		part[pos].z = 1;
		part[pos].x = mxShip::x+rand()%3;
		part[pos].y = mxShip::y+rand()%25;
		part[pos].color = D3DCOLOR_XRGB(rand()%255,rand()%255,rand()%255);
		}
		}
		
	}
	void keycheck() {
		input.key.Update();
		if(input.key.KeyCheck(DIK_LEFT) == true) {
			keyin(VK_LEFT);
		}

		if(input.key.KeyCheck(DIK_RIGHT)) {
			keyin(VK_RIGHT);
		}

		if(input.key.KeyCheck(DIK_SPACE)) {
			keyin(VK_SPACE);
		}

		if(input.key.KeyCheck(DIK_RETURN)) {
			keyin(VK_RETURN);
		}
		if(input.key.KeyCheck(DIK_E)) {
			keyin('e');
		}

	}

	void keyin(int key) {
		static int sx = mxShip::x;

		switch(key) {
			// 
			case VK_LEFT: {
				/* 
				my way:
				int dx = 0;
				int *lx=&sx;
				if(*lx > dx)
				mxShip::x--; */
				// right way
				if(mxShip::x > 057+mxShip::speed)
					mxShip::x-=mxShip::speed;
				break;
			}
			case VK_RIGHT: 
				if(mxShip::x<800-057)
					mxShip::x+=mxShip::speed;
				break;
			case VK_SPACE:
				blast();
				break;
			case VK_RETURN: {
				part_on = true;
				ptype = 2;
			}
			break;
			case 'e':
				part_on = true;
				ptype = 3;
				break;
		}
	}

private:

	void load() {


	}


};

extern mxBlast blast;

