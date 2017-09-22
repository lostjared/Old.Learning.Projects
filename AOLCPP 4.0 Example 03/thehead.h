// AOLCPP4 example #3
// written by Jared Bruni
#include <windows.h>
#include "aolcpp4.h"
#include "resource.h"


static HINSTANCE hInst;
static HWND      main;
static HFONT     thefont = CreateFont(14,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,"Arial");
static bool      afk_on = false;
static char      thereason[100];
static HWND      view_win;

LRESULT APIENTRY MainProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);// callback function for mainwindow
LRESULT APIENTRY ViewProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void SetMyFont(HWND);// set the font
void chatscan(char* sn,char* msg);// chat scan
bool isOn();
void ShowMessage(char* sn,char* msg);

