// the header files
// jared bruni
#include <windows.h>
#include "resource.h"

// function prototypes
LRESULT APIENTRY MainProc(HWND,UINT,WPARAM,LPARAM);
LRESULT APIENTRY IntroProc(HWND,UINT,WPARAM,LPARAM);
LRESULT APIENTRY AboutProc(HWND,UINT,WPARAM,LPARAM);

void onmainmenu(WPARAM wParam);


// global variable handles
static HWND main;
static HWND intro;
static HWND about;
static HINSTANCE g_hInst;


