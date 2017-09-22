/* MasterX Window Example
   written by Jared Bruni
   www.LostSideDead.com


  "Open Source, Open Mind"
*/

#define Sync if(mxhwnd.SyncChange()) 
#define MASTERXSDK
#include"masterlibrary2.h"


extern MasterXHWND mxhwnd;


class MasterWindow : public MasterGameObject {


public:

	virtual void load()
	{
		x = 0;
		y = 0;
		w = 640;
		h = 480;
	}

	virtual void update()
	{
		draw();
		Sync
		{
			logic();
		}
	}

private:

	int x,y,w,h;


	inline void draw()
	{
		mxhwnd.paint.mxdrawrect(x,y,w,h,RGB(150,150,150),RGB(170,170,170));
		mxhwnd.paint.mxdrawrect(x,y,w+20,y+20,RGB(0,0,150),RGB(0,0,180));
		mxhwnd.text.settextcolor(RGB(200,0,0));
		mxhwnd.text.setbkcolor(RGB(0,0,150));
		mxhwnd.text.printtext("Hello World",5,5);
	}

	inline void logic()
	{

	}

};

