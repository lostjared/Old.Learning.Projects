/* simple window example */

#define Sync if(mxhwnd.SyncChange()) 
#define MASTERXSDK
#include"masterlibrary2.h"

extern MasterXHWND mxhwnd;


class Window : public MasterGameObject {


public:

	virtual void load()
	{
		setpos(10,10,100,100);
		back_color = RGB(175,175,175);
		strcpy(title,"Untitled");
	}


	virtual void update()
	{
		draw();
		Sync
		{
			logic();
		}
	}

	inline void setpos(int ix, int iy, int iw,int ih)
	{
		x = ix;
		y = iy;
		w = iw;
		h = ih;
	}

	inline void setbackcolor(COLORREF color)
	{
		back_color = color;
	}

	inline void setwindowtitle(char* titlex)
	{
		strcpy(title,titlex);
	}

private:

	inline void draw()
	{
		mxhwnd.paint.mxdrawrect(x,y,x+w,y+h,back_color,back_color);
		mxhwnd.paint.mxdrawrect(x,y,x+w,y+15,RGB(0,0,100),RGB(0,0,100));
		mxhwnd.text.setbkcolor(RGB(0,0,100));
		mxhwnd.text.settextcolor(RGB(200,0,0));
		mxhwnd.text.printtext(title,x+2,y+2);
	}

	inline void logic()
	{


	}

	int x,y,w,h;
	COLORREF back_color;
	char title[255];

};