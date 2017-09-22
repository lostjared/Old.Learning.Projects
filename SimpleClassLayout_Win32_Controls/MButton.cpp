// MBUTTON .CPP
// written by jared bruni
// www.lostsidedead.com
#include "Mbutton.h"



HWND MButton::CreateButton(DWORD ex_style,char* title,DWORD but_style,int x, int y, int w, int h, HWND parent,HINSTANCE hInst,UINT ID)
{
	myid = ID;
	parhwnd = parent;
	myhwnd = CreateWindowEx(ex_style,"Button",title,but_style,x,y,w,h,parent,(HMENU)ID,hInst,0);
	return myhwnd;
}


WNDPROC MButton::SubClassWindow(WNDPROC newProc)
{
	WNDPROC oldProc;

	oldProc = (WNDPROC)SetWindowLong(myhwnd,GWL_WNDPROC,(LONG)(WNDPROC)newProc);

	return oldProc;
}