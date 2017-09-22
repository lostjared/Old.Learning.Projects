#include "masterx.h"

mxHwnd __mxhwnd;

int PASCAL WinMain(HINSTANCE hInst,HINSTANCE hPrev, LPSTR lpszLine, int nCmdShow) {
	mxSound dxsound(__mxhwnd.hwnd );
	return MasterMain(hInst,lpszLine);
}

HFONT MakeFont(char* ftype, int size)
{
	return CreateFont(size,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,ftype);
}








