// mxhead, application header file

#include <windows.h>
#include "aolcpp.h"
#include "resource.h"

// enumerated constants
enum { ID_EDIT = 1, ID_BUTTON };

// prototypes
LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
LRESULT APIENTRY EditProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);

void sendeditdata();
// global variables

static HWND main;
static HWND edit;
static HWND button;
static HINSTANCE g_hInst;
static WNDPROC MainP;
