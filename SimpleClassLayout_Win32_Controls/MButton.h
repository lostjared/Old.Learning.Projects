// MBUTTON.h
// written by jared bruni
// www.lostsidedead.com

// example on how you could make a class, for controls


#include <windows.h>


class MButton
{
public:
	HWND    parhwnd;
	HWND    myhwnd;
	UINT    myid;
	WNDPROC myproc;

	HWND    CreateButton(DWORD ex_style,char* title,DWORD but_style,int x, int y, int w, int h,HWND parent, HINSTANCE hInst, UINT ID);
	WNDPROC SubClassWindow(WNDPROC newProc);

	// add in all members you wish to use to manipulate the button heres some examples

	inline void SetText(char* buffer)
	{
		SendMessage(myhwnd,WM_SETTEXT,strlen(buffer),(LPARAM)(LPCSTR)buffer);
	}

	inline void GetText(char* buffer)
	{
		SendMessage(myhwnd,WM_GETTEXT,strlen(buffer),(LPARAM)(LPCSTR)buffer);
	}

	inline void ShowWin(int nCmdShow)
	{
		ShowWindow(myhwnd,nCmdShow);
	}
};