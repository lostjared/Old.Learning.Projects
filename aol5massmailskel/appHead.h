// application header
// jared bruni
// http://www.lostsidedead.com/aolcpp3/
#include <windows.h>
#include "aolcpp3.h"
#include "resource.h"

//static 
static HWND mainwindow;
static HWND main_list;
static HWND main_send;
static HWND main_badd;
static HWND main_bclear;
static HWND main_bsend;
static HWND aboutwindow;
static HWND sendwindow;
static HWND sendingwindow;
static HINSTANCE g_hInst;
static AOLCPP3   aolcpp3;
static HFONT appfont = CreateFont(14,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,"Arial");
static HWND sendingstr;
static bool fwd_send = false;

enum { ID_ADDLIST = 0, ID_CLEARLIST, ID_SENDLIST, ID_MAILLIST };

LRESULT APIENTRY MainProc(HWND,UINT,WPARAM,LPARAM);
LRESULT APIENTRY SendProc(HWND,UINT,WPARAM,LPARAM);
LRESULT APIENTRY AboutProc(HWND,UINT,WPARAM,LPARAM);
LRESULT APIENTRY SendingProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam); 

void InitApp(HINSTANCE hInst);
void MenuProc(WPARAM);
void SetTheFont(HWND);

struct mailSend
{
	int index;
};
// the AOL Fwder class prototype 
class AOLFwder
{
	int off_index;
	int pop_index;
	bool fwdx;
	int  isend;
	char sendsn[500];
	char sendtag[500];
public:
	AOLCPP3 aolcpp3;
	mailSend sendlist[650]; // no more then 650 aol mails

	void pushList(int index);
	int  popList();
	void clear();
	void send(char* sn, char* tag);
	void stop();
	void update();
	void on();
	void sendmail();
	void openandfwd();
	void sendthemail();
	void checkifrepeat();

	AOLFwder();
};

static AOLFwder fwd;
