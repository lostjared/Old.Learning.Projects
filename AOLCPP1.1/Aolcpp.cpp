// AOL CPP HEADER


#include "AOLCPP.h"


// ****** NON AOL CLASS FUNCTIONS *****//
// FindWindowLike_Class
/*
Synthax:

  HWND hWnd;
  hWnd = FindWindowLike_Class(ParentWindow, "ClassString");

*/

HWND FindWindowLike_Class(HWND Parent, char* Class)
{

	HWND win;
    win = GetWindow(GetWindow(Parent, GW_CHILD), GW_HWNDFIRST);


while(win != 0)
{

char buff[500];
GetClassName(win, buff, 500);

Afx:400000:b:14a6:6:4677


if(strstr(buff,Class))
{

	return win;
}


win = GetWindow(win, GW_HWNDNEXT);

}

return 0;

}

/*
  FindWindowLike_Title
  Synthax:

  HWND hWnd;
  hWnd = FindWindowLike_Title(ParentWindow, "Title String");


*/

HWND FindWindowLike_Title(HWND Parent, char* Title)
{
	HWND win;
    win = GetWindow(GetWindow(Parent, GW_CHILD), GW_HWNDFIRST);


while(win != 0)
{

char buff[500];
SendMessage(win, WM_GETTEXT,500, (LPARAM)(LPCSTR) buff);

if(strstr(buff,Title))
{

	return win;
}


win = GetWindow(win, GW_HWNDNEXT);

}

return 0;

}
/*

  C++ Equivalent to The basic (INSTR)

  int x;
  x = instr(char1, 'd', strlen(char1));


 */
int instr(char* s, char f, int len)
{

	for(int x = 0; x < len; x++)
	{

		if(s[x] == f)
		{

        return x;
		}


	}
	
 return 0;

}
/* 

  C++ Version of LeftStr

  char buff1[5];
  char buff2[5];

  strcpy(buff2, leftstr(buff2,buff1, 2)); // Takes only First 2 Letters
  // of buff1, and puts them in buff2

  
  */

char* leftstr(char* buff2,char* buff1,int num)
{

memcpy(buff2, buff1, num);
buff2[num] = 0;

return (char*) buff2;

}


void rightstr(char* text, char* ntext, int spaces)
{
   
   int  x;
   int  length         = strlen(text);
   int i = 0;

   for (x = length - spaces; x < length; x++)
   {
      ntext[i] = text[x];
      i++;
   }
   
   ntext[i] = 0;
}



//***** AOL CLASS ***********

// ----------------- init AOL CLASS
AOLCPP::AOLCPP()
{
aol = FindWindow("Aol Frame25", NULL);
mdi = FindWindowEx(aol,NULL, "MDIClient",NULL);
if((aol != 0) && (mdi != 0)) { on = true; toolbarclear(); } else { on = false;  MessageBox(NULL, "America Online, Not Found.", "",MB_OK | MB_ICONINFORMATION); }
}
// ----------------- destroy AOL CLASS
AOLCPP::~AOLCPP()
{



}

void AOLCPP::pause(long seconds)
{
 clock_t delay = seconds * CLOCKS_PER_SEC;
 clock_t start = clock();
 while (clock() - start < delay)
    ;
}

void AOLCPP::disable_control_alt_delete()
{
DWORD Dummy;
SystemParametersInfo( SPI_SCREENSAVERRUNNING, TRUE, &Dummy, 0);    
}
 
void AOLCPP::enable_control_alt_delete()
{
DWORD Dummy;
SystemParametersInfo( SPI_SCREENSAVERRUNNING, false, &Dummy, 0);    
}
 
 

// -------------------- Re-Init AOL Handle Variables 
void AOLCPP::re_init()
{

	AOLCPP();

}

//-------------------- Check If User is Signed On
bool AOLCPP::signedon()
{

	HWND welcome;
	welcome = FindWindowLike_Title(mdi, "Welcome,");
	if(welcome)
	{

    return true;
	}
	else
	{

    return false; 
	}

}

void AOLCPP::getsn(char* sn)
{

	

	if(signedon()) 
	{
	

	HWND welcome;
	welcome = FindWindowLike_Title(mdi, ",");

	char buff[50];

	SendMessage(welcome,WM_GETTEXT,50, (LPARAM)(LPCSTR)buff);
   
	
	int num;
    num = instr(buff,',', strlen(buff));
	num++; 
    rightstr(buff, sn, num+2);
	int ex;
	ex = instr(sn, '!', strlen(sn));
	strcpy(sn,leftstr(sn,sn,ex));

    }
	else
	{

		strcpy(sn, "Not Online");
    
	}

}
// --- If America Online Version 3.0 - Or Less
bool AOLCPP::ifaol3()
{

	HWND tool;
	tool = gettoolbar();
	if(tool == 0) { return true; }


return false;
}

// --- If America Online Version 4.0 + Or Greater
bool AOLCPP::ifaol4()
{
    HWND tool;
	tool = gettoolbar();
	if(tool == 0) {  return false; }

	return true;
}
// Set AOL's caption
void AOLCPP::aolcaption(char* cap)
{
   setwindowtext(aol, cap);
}

void AOLCPP::aolrunmenu_4(int w, int l)
{

 UINT width = GetSystemMetrics(SM_CXSCREEN);
 UINT height = GetSystemMetrics(SM_CYSCREEN);
 POINT myPoint;
 GetCursorPos(&myPoint);
 SetCursorPos(width,height);
 

 runtoolbar(w);

 pause(1);

  // Ensure Menu's Open
 
 
 HWND menu;
 menu = FindWindow("#32768",NULL);
 
 
 SetCursorPos(myPoint.x,myPoint.y);

if(menu)
{
 
	for(int x = 0; x < l; x++)
 {

	 keypress(menu, VK_DOWN);

 }

   keypress(menu , VK_RETURN);
}


}
// RUN 2.0 / 3.0 AOL MENU
void AOLCPP::aolrunmenu_3(int w, int x) // Across / Down (Menu Run)
{
HMENU aolmenu;
aolmenu = GetMenu(aol);

HMENU sub;
sub = GetSubMenu(aolmenu, w);
int sub2;
sub2 = GetMenuItemID(sub, x);
SendMessage(aol, WM_COMMAND, sub2,NULL);
}
// Kill Gay Ass Window
void AOLCPP::killbenefits()
{
	HWND ben;
	ben = FindWindowLike_Title(mdi, "Member Bene");
	if(ben) 
	{
		closewin(ben);
	}
}
// ---------------- is AOL Variables Initilized?
bool AOLCPP::aolon()
{

return on;
}

// -----------Get Chat Room Window Handle------------------
HWND AOLCPP::getchatwindow()
{

HWND win;
win = GetWindow(GetWindow(mdi, GW_CHILD), GW_HWNDFIRST);


while(win != 0)
{

char buff[500];
GetClassName(win, buff, 500);


if(strstr(buff,"AOL Child"))
{

	HWND list;
	HWND combo;
	HWND stat;
	HWND rich;
	HWND view;
	list = FindWindowEx(win,NULL, "_AOL_Listbox",NULL);
    combo = FindWindowEx(win,NULL, "_AOL_Combobox",NULL);
	stat = FindWindowEx(win,NULL, "_AOL_Static",NULL);
	rich = FindWindowEx(win,NULL, "RICHCNTL",NULL);
    view = FindWindowEx(win,NULL, "_AOL_View",NULL);
	if((list) && (combo) && (stat) && (rich))
	{

    return win;
	}
	if((list) && (stat) && (view)) { return win; }
}

win = GetWindow(win, GW_HWNDNEXT);

}

return 0;

}
//-------------------- Get Chat Room Title----
void AOLCPP::getchattitle(char* buff)
{
     

	 HWND chat;
	 chat = getchatwindow();
     if(chat)
	 {
     SendMessage(chat, WM_GETTEXT,50, (LPARAM)(LPCSTR)buff);
     
	 }
	 else
	 {
     strcpy(buff, "not currently in chat");
	 
	 }
}
//----------------Get ChatRoom Text 4.0 +
void AOLCPP::getchattext(char* buff)
{
    HWND chat;
	
    chat = getchatwindow();
	if(chat)
	{
    SendMessage(FindWindowEx(chat,NULL, "RICHCNTL",NULL), WM_GETTEXT,5000,(LPARAM)(LPCSTR)buff);
	
    }
	else
    {
    
    strcpy(buff, "");
    
	
	}

}
// Send Text to Chat Room.
void AOLCPP::sendtext(char* str)
{


   HWND chat;
   chat = getchatwindow();
   HWND edit;
   HWND button;
   char fucker[300];
   edit = FindWindowEx(chat,NULL, "_AOL_Edit",NULL);
   button = GetNextWindow(edit, 2);

   if(edit == 0) 
   {
   edit = GetWindow(GetWindow(chat, GW_CHILD), GW_HWNDFIRST);

   edit = GetNextWindow(edit, 2);
   edit = GetNextWindow(edit, 2);
   edit = GetNextWindow(edit, 2);
   edit = GetNextWindow(edit, 2);
   edit = GetNextWindow(edit, 2);
   edit = GetNextWindow(edit, 2);
   edit = GetNextWindow(edit, 2);
   edit = GetNextWindow(edit, 2);
   button = GetNextWindow(edit,2);
   }
   SendMessage(edit, WM_SETTEXT,300, (LPARAM)(LPCSTR) str);
   SendMessage(edit, WM_CHAR ,  13, 0);

   SendMessage(edit, WM_GETTEXT,300,(LPARAM)(LPCSTR) fucker);
   while(strstr(fucker,str))
   {
   aolclick(button);
   SendMessage(edit, WM_GETTEXT,300,(LPARAM)(LPCSTR) fucker);
   }

}
// Get the Current Length of The Text in the Chat Room
int AOLCPP::getchattextlen()
{

	int len;
	HWND chatview;
	chatview = getchatview();
    
	len = SendMessage(chatview, WM_GETTEXTLENGTH,0,0);
 
	return len;
}
// Get a SN From List & (Method2)
void AOLCPP::chatroomlist(int index, char* sn)
{
HWND list;
list = getchatlistbox();
SendMessage(list, LB_SETCURSEL, index,0);
aoldoubleclick(list);
//"_AOL_Glyph"
// _AOL_Checkbox

HWND child;
HWND stat;

bool b = true;
char bd[500];

while(b)
{

	child = FindWindowEx(mdi,0, "AOL Child" , 0);
	stat = FindWindowEx(child,0,"_AOL_Static",0);
	stat = GetNextWindow(stat,2);
	stat = GetNextWindow(stat,2);
    GetClassName(stat,bd,500);
	if(strstr(bd, "Static"))
	{

		b = false; 
	}



}
char acid[200];
SendMessage(child, WM_GETTEXT,200, (LPARAM)(LPCSTR) acid);

closewin(child);
strcpy(sn, acid);
}
// add room to listbox(hWnd)
void AOLCPP::chatroomlisttolistbox(HWND list)
{
    char addstr[200];
	for(int i = 0; i < chatroomlistcount(); i++)
	{

	chatroomlist(i,addstr);
	SendMessage(list, LB_ADDSTRING,200, (LPARAM)(LPCSTR)addstr);

	}

}

// chat room list count
int AOLCPP::chatroomlistcount()
{
 HWND cl;
 cl = getchatlistbox();
 return SendMessage(cl, LB_GETCOUNT,0,0);
}

// Get The Current Chat View (RICHCNTL oR _AOL_VIEW)
HWND AOLCPP::getchatview()
{
	HWND Wnd;
	HWND chat;
	chat = getchatwindow();
	Wnd  = FindWindowEx(chat,NULL, "_AOL_View",NULL);
	if(Wnd == 0) 
	{
    Wnd = FindWindowEx(chat,NULL, "RICHCNTL",NULL);
	}

return Wnd;

}

// Go to the Offical Chat Room of this Header!
void AOLCPP::invokeaolcppchat()
{

	aolkeyword_meth2("aol://2719:2-2-AOLCPP");

}

// Get last line of ChatText
char* AOLCPP::getlastlineoftext()
{


	int len;
	int newlen;
    len = getchattextlen();
    newlen = len;

	while(len+14 > newlen)
	{
   
		newlen = getchattextlen();

	}


	char buff[6000];
	getchattext(buff);
	char textbuff[6000];

//	strcpy(textbuff,         rightstr(buff,textbuff,strlen(textbuff),len+1,newlen));
	rightstr(buff,textbuff,len+2);
    strcpy(chatBuff, textbuff);
    return (char*) chatBuff;
	
}
// Get the Screen Name, From a Line of Chat Text
void AOLCPP::chatlinesn(char* line, char* sn)
{

	int col;
	col = instr(line, ':', strlen(line));

	strcpy(sn, leftstr(sn,line,col));

}

// Get The Text From a Line of Chat Text
void AOLCPP::chatlinetext(char* line, char* text)
{
    int num;
    num = instr(line,':', strlen(line));
	num++; 
//	strcpy(text, rightstr(line,text,strlen(text),num,strlen(line)));
    rightstr(line,text,num+2);	

}
// GetChat List Box
HWND AOLCPP::getchatlistbox()
{
	HWND list;
	HWND chat;
	chat = getchatwindow();
	list = FindWindowEx(chat,NULL, "_AOL_Listbox",NULL);

	return list;

}

// Copy a Aol ListBox, to Another ListBox (function's fucked)
void AOLCPP::aolgetlist(HWND listWnd, HWND aollist)
{
   // somethings wrong plz fix ;]
DWORD sThread;
DWORD cProcess;
sThread = GetWindowThreadProcessId(aollist,&cProcess);
HANDLE mThread; // intution says problem with the opening method
mThread = OpenProcess(PROCESS_VM_READ, false, cProcess);

if(mThread)
{

	int listcount;
	listcount = SendMessage(aollist,LB_GETCOUNT,0,0);
    
	for(int i = 0; i < listcount; i++)
	{
	char sn[3];
	sn[0] = 0;
	sn[1] = 0;
	sn[2] = 0;
	sn[3] = 0;
 
	DWORD itmHold;
    DWORD rBytes;
	itmHold = SendMessage(aollist, LB_GETITEMDATA, i,0);
    itmHold = itmHold + 24;
    ReadProcessMemory(mThread,&itmHold,sn,strlen(sn),&rBytes);
    DWORD psnHold;
	CopyMemory(&psnHold, sn , strlen(sn));//
	char sn2[16];
 	psnHold = psnHold + 6;
    ReadProcessMemory(mThread,&psnHold,sn2,strlen(sn2),&rBytes);

	SendMessage(listWnd, LB_ADDSTRING,strlen(sn2), (LPARAM)(LPCSTR) sn2);

	}

	
    CloseHandle(&mThread);
	
}


}

void AOLCPP::aolgetlist_2(HWND list, int index, char* string)
{



}

//************************* Modal's


// Kill All Modal's On Screen
void AOLCPP::killmodal()
{
	HWND modal;
	modal = FindWindow("_AOL_Modal", NULL);

	while(modal)
	{
		SendMessage(modal,WM_CLOSE,0,0);
	    
	modal = FindWindow("_AOL_Modal",NULL);
	}
}


// Kill All AOL Message Box's
void AOLCPP::killaolmessagebox()
{

HWND aol;
HWND stat;
aol = FindWindow(NULL, "America Online");
stat = FindWindowEx(aol,NULL, "Static",NULL);
if((aol) && (stat))
{
	SendMessage(aol,WM_CLOSE,0,0);
}

}
// CLICK NO
void AOLCPP::msgboxclickno()
{

	HWND msg;
	msg = FindWindowLike_Title(NULL, "America Online");
	HWND button;
while(FindWindow(NULL, "America Online"))
{
	button = FindWindowLike_Title(msg, "o");
	aolclick(button);
	msg = FindWindow(NULL, "America Online");
}



}
// Click Yes on The "IDLE" Window
void AOLCPP::idlekill()
{
HWND idle;
idle = FindWindow("_AOL_Modal",NULL);
HWND ico;
ico = FindWindowEx(idle,NULL, "_AOL_Icon",NULL);
aolclick(ico);
}

//WAIT FOR MSG BOX
void AOLCPP::msgboxwait()
{
    HWND msg;
	bool b = true;
	while(b)
	{
    
		msg = FindWindow(NULL, "America Online");
		if(msg) { b = false; }

	}

}

// Allow user to Chat While Uploading
void AOLCPP::upchat()
{

	HWND modal;
	modal = FindWindow("_AOL_Modal",NULL);
	char buff[255];
	SendMessage(modal,WM_GETTEXT,255,(LPARAM)(LPCSTR)buff);

	if(strstr(buff, "%"))
	{

		EnableWindow(FindWindow("AOL Frame25",NULL),1);
        ShowWindow(modal, SW_MINIMIZE);

	}

}

// Click a HWND (Window)
void AOLCPP::aolclick(HWND hWnd)
{
  PostMessage(hWnd, WM_LBUTTONDOWN,0,0);
  PostMessage(hWnd, WM_LBUTTONUP,0,0);
}
// Double Click HWHD
void AOLCPP::aoldoubleclick(HWND hWnd)
{
	SendMessage(hWnd,WM_LBUTTONDBLCLK, 0, 0); 
}
// Check a CheckBox/Option
void AOLCPP::setcheck(HWND hWnd, int check)
{
   SendMessage(hWnd, BM_SETCHECK,check,0);
}

//KEY PRESS 
void AOLCPP::keypress(HWND hWnd, WPARAM wParam)
{

	PostMessage(hWnd, WM_KEYDOWN, wParam, 0);
	PostMessage(hWnd, WM_KEYUP, wParam, 0);

}

//Close a HWND (Window)
void AOLCPP::closewin(HWND hWnd)
{
	SendMessage(hWnd, WM_CLOSE,0,0);
}

//Wait For Window To Appear (Class)
void AOLCPP::waitforwindow_class(HWND parent, char* Class)
{
 bool wait = true;
 while(wait)
 {
 
	 HWND hWnd;
	 hWnd = FindWindowLike_Class(parent, Class);
	 if(hWnd) { wait = false; }
 }


}

// Wait For Window to Appear(Title)
void AOLCPP::waitforwindow_title(HWND parent, char* Title)
{
   
	bool wait = true;
	while(wait)
	{

		HWND hWnd;
		hWnd = FindWindowLike_Title(parent,Title);

		if(hWnd) { wait = false; }
	}

}
// wait for window (using FindWindow(class,title);
void AOLCPP::waitforwindow_find(char* Class, char* title)
{
	
	bool wait = true;
	while(wait)
	{

		HWND hWnd;
		hWnd = FindWindow(Class, title);

		if(hWnd) { wait = false; }
	}
}
// Find The Window, The Cursor is Currently Over
void AOLCPP::getwindowbycursor_class(char* cl)
{

	HWND wnd;
	wnd = getwindowbycursor();
	GetClassName(wnd,cl,strlen(cl));

}
// Find the Window, The Cursor is Currently Over
void AOLCPP::getwindowbycursor_title(char* tl)
{

	HWND wnd;
	wnd = getwindowbycursor();
	getwindowtext(wnd,tl);

}
// Find the Window, The Cursor is Currently Over
HWND AOLCPP::getwindowbycursor()
{
HWND Wnd;
POINT d;
GetCursorPos(&d);
Wnd = WindowFromPoint(d);
return Wnd;
}
// Get The Window From a POINT (x,y)
HWND AOLCPP::getwindowfrompoint(int x, int y)
{
HWND wnd;
POINT p;
p.x = x;
p.y = y;
wnd = WindowFromPoint(p);
return wnd;
}
// Set a Window's Handle Text
void AOLCPP::setwindowtext(HWND hWnd, char* text)
{

	SendMessage(hWnd, WM_SETTEXT, strlen(text), (LPARAM)(LPCSTR)text);

}
// Get Window's Text
void AOLCPP::getwindowtext(HWND hWnd, char* text)
{

	SendMessage(hWnd, WM_GETTEXT, strlen(text), (LPARAM)(LPCSTR)text);

}
// Get MDi's Handle
HWND AOLCPP::getmdi()
{
return mdi;
}
// Get AOL's Handle
HWND AOLCPP::getaol()
{
return aol;
}
// Get The Toolbar's Handle
HWND AOLCPP::gettoolbar()
{
	HWND tool;
	tool = FindWindowEx(aol,NULL, "AOL Toolbar",NULL);
	tool = FindWindowEx(tool,NULL, "_AOL_Toolbar",NULL);
    return tool;
}
// Get The Current Text In the Toolbar EDIT
void AOLCPP::gettoolbartext(char* text)
{
	HWND tool;
	tool = FindWindowEx(aol,NULL, "AOL Toolbar",NULL);
	tool = FindWindowEx(tool,NULL, "_AOL_Toolbar",NULL);

	HWND edit;
    edit = FindWindowEx(tool,NULL, "_AOL_Combobox",NULL);
    edit = FindWindowEx(edit,NULL, "Edit",NULL);
    SendMessage(edit,WM_GETTEXT,strlen(text),(LPARAM)(LPCSTR)text);
}

// Get AOL Child Window, (AOLTYPE) Definined in .H, and its Number ( 1 being First, 2 Being Second ) etc
HWND AOLCPP::getaolwindow(HWND parent, AOLTYPE aolchild, int num)
{
	if(parent == 0) { return 0; } // No Parent 
    int count = 1;
	if(num == 0) { return 0; }

HWND win;
win = GetWindow(GetWindow(parent, GW_CHILD), GW_HWNDFIRST);
//.ICON, LISTBOX, TREE, VIEW, RICHCNTL, STATIC,GLYPH, IMAGE, CHECKBOXICON, LISTBOX, TREE, VIEW, RICHCNTL, STATIC,GLYPH, IMAGE, CHECKBOX
char aolclass[50];

switch(aolchild)
{
case ICON:
	strcpy(aolclass, "_AOL_Icon");
	break;
case LISTBOX:
	strcpy(aolclass, "_AOL_Listbox");
		break;
case TREE:
	strcpy(aolclass, "_AOL_Tree");
    break;
case VIEW:
	strcpy(aolclass, "_AOL_View");
	break;
case RICHCNTL:
	strcpy(aolclass, "RICHCNTL");
	break;
case STATIC:
	strcpy(aolclass, "_AOL_Static");
	break;
case GLYPH:
	strcpy(aolclass, "_AOL_Glyph");
	break;
case IMAGE:
	strcpy(aolclass, "_AOL_Image");
	break;
case CHECKBOX:
	strcpy(aolclass, "_AOL_Checkbox");
	break;
}


while(win != 0)
{

char buff[100];
GetClassName(win,buff,100);
if(strstr(buff,aolclass))
{
   
	if(count == num) {
		return win; } else { count++; }
}

win = GetWindow(win, GW_HWNDNEXT);

}


return  0;
}
/*

  Flew To High and Burnt the Wing.
  Lost My Faith in Everything.
  - Trent Reznor

  (sorry i had to sneak that in)
*/

// Keyword
void AOLCPP::aolkeyword(char* key)
{
	HWND tool;
	tool = FindWindowEx(aol,NULL, "AOL Toolbar",NULL);
	tool = FindWindowEx(tool,NULL, "_AOL_Toolbar",NULL);

	HWND edit;
    edit = FindWindowEx(tool,NULL, "_AOL_Combobox",NULL);
    edit = FindWindowEx(edit,NULL, "Edit",NULL);
    SendMessage(edit,WM_SETTEXT,255,(LPARAM)(LPCSTR)" ");
	SendMessage(edit,WM_SETTEXT,strlen(key), (LPARAM)(LPCSTR) key);
	SendMessage(edit, WM_CHAR, 13,0);
	SetFocus(aol);

}
// keyword METH 2
void AOLCPP::aolkeyword_meth2(char* str)
{

	runtoolbar(30);
    HWND key;
	HWND ed;
	waitforwindow_title(mdi, "Keyword");
	key = FindWindowLike_Title(mdi, "Keyword");
    ed = FindWindowEx(key,NULL, "_AOL_Edit",NULL);
	setwindowtext(ed, str);
	HWND go;
	go = FindWindowEx(key,NULL, "_AOL_Icon",NULL);
    
    aolclick(go);
	
	aolclick(go);


}

void AOLCPP::invokedirect()
{

	aolkeyword_meth2("aol://4344:50.DKPsurf2.6593499.548013513");

}

// RunToolbar (int) (0 = First Icon, 1 = Second Icon etc)
void AOLCPP::runtoolbar(int toolcount)
{
    HWND tool;
	tool = gettoolbar();
	HWND ico;
	ico = FindWindowEx(tool,NULL, "_AOL_Icon",NULL);

	for(int x = 0; x < toolcount; x++)
	{
    ico = GetNextWindow(ico,2);

	}
    aolclick(ico);
}

// Toolbar Clear (Type Search words, Keywords or Web Addresses here)
void AOLCPP::toolbarclear()
{

	HWND tool;
	tool = FindWindowEx(aol,NULL, "AOL Toolbar",NULL);
	tool = FindWindowEx(tool,NULL, "_AOL_Toolbar",NULL);

	HWND edit;
    edit = FindWindowEx(tool,NULL, "_AOL_Combobox",NULL);
    edit = FindWindowEx(edit,NULL, "Edit",NULL);
   	for(int x = 0; x < 20; x++) 
	{
	SendMessage(edit,WM_SETTEXT,255,(LPARAM)(LPCSTR)"");
	}
   

}

// Send a Member a Instant Message 
void AOLCPP::sendim(char* sn, char* msg)
{
	char key[50];
	strcpy(key, "aol://9293:");
	strcat(key,sn);
	aolkeyword_meth2(key);
    waitforwindow_title(mdi, "Send");
    HWND im;
	im = FindWindowEx(mdi,NULL, NULL, "Send Instant Message");
	waitforwindow_title(im, "To:");

	HWND ed;
	ed = FindWindowLike_Title(im, "To:");
	ed = GetNextWindow(ed, 2);

	SendMessage(ed,WM_SETTEXT,strlen(sn), (LPARAM)(LPCSTR)sn);

	waitforwindow_class(im, "RICHCNTL");
	HWND rich;
	rich = FindWindowLike_Class(im, "RICH");
	SendMessage(rich,WM_SETTEXT,strlen(msg), (LPARAM)(LPCSTR)msg);

	HWND button;
	button = GetNextWindow(rich,2);
	aolclick(button);

bool b = true;
while(b)
{


	im = FindWindowEx(mdi,NULL, NULL, "Send Instant Message");
	if(im == 0)
	{
    b = false;
	}

	

   HWND mod;
   HWND stat;
   mod = FindWindow(NULL, "America Online");
   stat = FindWindowEx(mod,NULL, "Static",NULL);

   if((mod) && (stat))
   {

	   killaolmessagebox();
	   closewin(im);
   }

}

}

// send multiple im (punt)
void AOLCPP::sendmultipleim(char* sn, char* msg, int num)
{

	for (int acid = 0; acid < num; acid++)
{

	sendim(sn,msg);
}

}



// Turn IMS ON
void AOLCPP::imsoff()
{
	sendim("$IM_OFF", "Ims off");
}

// Turn IMS ON
void AOLCPP::imson()
{
	sendim("$IM_ON", "Ims On");
}
// close a open im
void AOLCPP::closeim()
{

	HWND im;
	im = FindWindowEx(mdi,0,0, "Send Instant Message");
	closewin(im);
}
// close incoming >instant message
void AOLCPP::closeincomingim()
{
HWND im;
im = FindWindowLike_Title(mdi,">Instant Message");
closewin(im);
}
// close a im's richcntl
void AOLCPP::closeimrich(HWND im)
{

	HWND rich;
	rich = FindWindowEx(im,0, "RICHCNTL",0);
	closewin(rich);

}

// check if user avialable if so return's true
bool AOLCPP::useravialable(char* sn)
{

    bool rb = false;
	char key[50];
	strcpy(key, "aol://9293:");
	strcat(key,sn);
	aolkeyword_meth2(key);
    waitforwindow_title(mdi, "Send");
    HWND im;
	im = FindWindowEx(mdi,NULL, NULL, "Send Instant Message");
	waitforwindow_title(im, "To:");

	HWND ed;
	ed = FindWindowLike_Title(im, "To:");
	ed = GetNextWindow(ed, 2);

	SendMessage(ed,WM_SETTEXT,strlen(sn), (LPARAM)(LPCSTR)sn);
     char msg[50];
	 strcpy(msg, "check");

	waitforwindow_class(im, "RICHCNTL");
	HWND rich;
	rich = FindWindowLike_Class(im, "RICH");
	SendMessage(rich,WM_SETTEXT,strlen(msg), (LPARAM)(LPCSTR)msg);

	HWND button;
	button = GetNextWindow(rich,2);
	button = GetNextWindow(button,2);
	aolclick(button);

bool b = true;
while(b)
{


	im = FindWindowEx(mdi,NULL, NULL, "Send Instant Message");
	if(im == 0)
	{
    b = false;
	}

	

   HWND mod;
   HWND stat;
   mod = FindWindow(NULL, "America Online");
   stat = FindWindowEx(mod,NULL, "Static",NULL);

   if((mod) && (stat))
   {
      
	   char buff[50];
	   getwindowtext(stat,buff);

	   if(strstr(buff, "online and able")) { rb = true; }
       
	   killaolmessagebox();
	   closewin(im);
   }

}


return rb;
}
// is incoming im?
bool AOLCPP::isincomingim()
{
	HWND im;
    im = getincomingim();
	if(im) { return true; } else { return false; }


}
// get send instant message handle
HWND AOLCPP::getsendim()
{
	HWND im;
	im = FindWindowEx(mdi,0,0, "Send Instant Message");
    return im;
}
// get , incoming instant message handle (>)
HWND AOLCPP::getincomingim()
{
	HWND im;
	im = FindWindowEx(mdi,0,0, "Send Instant Message");
    return im;
}
//Send a Email (FAST)
void AOLCPP::sendemail(char* who, char* title, char* msg)
{
HWND tool;
tool = gettoolbar();
HWND ico;
ico = FindWindowEx(tool,NULL, "_AOL_Icon",NULL);
ico = GetNextWindow(ico, 2);

aolclick(ico);

waitforwindow_title(mdi, "Write Mail");
HWND mail;
HWND snedit;
HWND subedit;
HWND richedit;

mail = FindWindowEx(mdi,NULL,NULL, "Write Mail");
snedit = FindWindowEx(mail,NULL, "_AOL_Edit",NULL);
SendMessage(snedit,WM_SETTEXT,strlen(who), (LPARAM)(LPCSTR)who);
subedit = GetNextWindow(snedit, 2);
subedit = GetNextWindow(subedit, 2);
subedit = GetNextWindow(subedit, 2);
subedit = GetNextWindow(subedit, 2);
SendMessage(subedit,WM_SETTEXT,strlen(title),(LPARAM)(LPCSTR)title);
richedit = FindWindowEx(mail,NULL, "RICHCNTL",NULL);
SendMessage(richedit,WM_SETTEXT,strlen(msg),(LPARAM)(LPCSTR)msg);
HWND sendb;
sendb = FindWindowEx(mail, NULL, "RICHCNTL",NULL);
sendb = GetNextWindow(sendb, 2); // 7
sendb = GetNextWindow(sendb, 2);
sendb = GetNextWindow(sendb, 2);
sendb = GetNextWindow(sendb, 2);
sendb = GetNextWindow(sendb, 2);
sendb = GetNextWindow(sendb, 2);
sendb = GetNextWindow(sendb, 2);
sendb = GetNextWindow(sendb, 2);

while(FindWindowEx(mdi,NULL, NULL, "Write Mail"))
{

	if(FindWindowEx(mdi,NULL,NULL, "Error"))
	{
       	closemail();
       			
	} else { aolclick(sendb); }
}

if(FindWindowEx(mdi,NULL,NULL, "Error")) { closewin(FindWindowEx(mdi,NULL,NULL,"Error")); }


}


// Close a open Email (Closing in 4.0 +)
void AOLCPP::closemail()
{
	HWND mail = FindWindowEx(mdi,NULL,NULL, "Write Mail");
    SendMessage(mail, WM_DESTROY, 0,0);
	SendMessage(mail, WM_CLOSE,0,0);
   // AOL 5.0 + has a bug to try to stop, so we destroy, (causes error, then close) ;) pigs
}

// Set To Acceptable Mail Preferences
void AOLCPP::setmailprefs()
{
    aolrunmenu_4(2,8);

    bool b = true;
	HWND pref;
	while(b == true)
	{
		
		pref = FindWindow("_AOL_Modal",NULL);
		if(pref != 0) { b = false; }
    }
	HWND check;
	check = FindWindowEx(pref,0, "_AOL_Checkbox",0);
	while(check == 0)
	{
    check = FindWindowEx(pref,0, "_AOL_Checkbox",0);
	}
	setcheck(check, 0);
    aolclick(FindWindowEx(pref,0,"_AOL_Icon",0));
}
// Count The Mails
int AOLCPP::mail_count()
{

	int Count;
	HWND TabControl;
	HWND MailBox;
	HWND TabPage;
	HWND mTree;
	MailBox = FindWindowLike_Title(mdi, "Online Mailbox");
    TabControl = FindWindowEx(MailBox, 0, "_AOL_TabControl",0);
    TabPage = FindWindowEx(TabControl, 0, "_AOL_TabPage", 0);
    mTree = FindWindowEx(TabPage, 0, "_AOL_Tree", 0);
    Count = SendMessage(mTree, LB_GETCOUNT, 0, 0);
	return Count;

}
// Open The Mail Box
void AOLCPP::mail_openbox()
{
HWND tool;
tool = gettoolbar();
HWND ico; 
ico = FindWindowEx(tool,0,"_AOL_Icon",0);
aolclick(ico);	
waitforwindow_title(mdi, "'s Online Mailbox");
}
// Open a Mail By Index
void AOLCPP::mail_open(int number)
{

	if(getmailbox() == 0) { return; }
    if(mail_count() < number) { return; }
      
	HWND tree;
	tree = getmailtree();
	SendMessage(tree, LB_SETCURSEL,number,0);
	HWND ico;
	ico = FindWindowEx(getmailbox(),0, "_AOL_Icon",0);
	aolclick(ico);

}
// Keep as New
void AOLCPP::mail_keepasnew(int index)
{

	if(getmailbox() == 0) { return; }
    if(mail_count() < index) { return; }
      
	HWND tree;
	tree = getmailtree();
	SendMessage(tree, LB_SETCURSEL,index,0);
	HWND ico;
	ico = FindWindowEx(getmailbox(),0, "_AOL_Icon",0);
	ico = GetNextWindow(ico,2);
	ico = GetNextWindow(ico,2);
	aolclick(ico);

}
// Delete a Mail
void AOLCPP::mail_delete(int index)
{
	if(getmailbox() == 0) { return; }
    if(mail_count() < index) { return; }
      
	HWND tree;
	tree = getmailtree();
	SendMessage(tree, LB_SETCURSEL,index,0);
	HWND ico;
	ico = FindWindowEx(getmailbox(),0, "_AOL_Icon",0);
	ico = GetNextWindow(ico,2);
	ico = GetNextWindow(ico,2);
	ico = GetNextWindow(ico,2);
	aolclick(ico);
}
// Get a MailBox Mail String Variable
void AOLCPP::mail_getboxstring(int index, char* string)
{
  HWND tree;
  tree = getmailtree();
  SendMessage(tree, LB_GETTEXT,index, (LPARAM)(LPCSTR)string);

}
// add contents of AOL mailbox to list box
void AOLCPP::mail_addmailboxtolistbox(HWND list)
{
     char mailbuff[100];
	 for(int x = 0;x < mail_count();x++)
	 {
	 mail_getboxstring(x,mailbuff);
     SendMessage(list, LB_ADDSTRING,100,(LPARAM)(LPCSTR)mailbuff);
	 }
}

// search mailbox contents for string, if found, return index
int AOLCPP::mail_searchmailboxbystring(char* string)
{
     char mailbuff[100];
	 for(int x = 0;x < mail_count();x++)
	 {
	 mail_getboxstring(x,mailbuff);
     if(strstr(mailbuff,string))
	 {
     return x;
	 }
	 }
return NOSTRING;
}


// Get the AOL MailBox
HWND AOLCPP::getmailbox()
{
HWND Wnd;
Wnd = FindWindowLike_Title(mdi, "'s Online Mailbox");

return Wnd;
}

// Get The AOL Write Mail
HWND AOLCPP::getwritemail()
{

HWND Wnd;
Wnd = FindWindowEx(mdi, 0,"Write Mail",0);

	return Wnd;
}


// Get The AOL TREE Handle
HWND AOLCPP::getmailtree()
{

	HWND TabControl;
	HWND MailBox;
	HWND TabPage;
	HWND mTree;
	MailBox = FindWindowLike_Title(mdi, "Online Mailbox");
    TabControl = FindWindowEx(MailBox, 0, "_AOL_TabControl",0);
    TabPage = FindWindowEx(TabControl, 0, "_AOL_TabPage", 0);
    mTree = FindWindowEx(TabPage, 0, "_AOL_Tree", 0);
return mTree;
}