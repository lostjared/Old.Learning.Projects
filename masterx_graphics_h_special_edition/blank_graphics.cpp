#include<iostream>
#include"graphics.h"

using namespace std;


int main()
{
	int gd = DETECT, gm = 0;
	initgraph(&gd,&gm,"");
	setcolor(RED);
	outtextxy(10,10,"Hello World");
	getch();
	return (0);
}