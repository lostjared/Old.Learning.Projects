// aolcpp3 by Master on LSD
// www.aolcpp.cjb.net
// masteronlsd@lostsidedead.com
// www.lostsidedead.com

#include "aolcpp3.h"


// the AOLCPP3 Object
void AOLCPP3_OBJ::init(AOLCPP3I* aolcppx)
{
	aolcpp = aolcppx;
}

// the AOLCPP3 Interface (aol functions)

HWND AOLCPP3I::getaol()
{
	return FindWindow("AOL Frame25",NULL);
}
HWND AOLCPP3I::getmdi()
{
	return FindWindowEx(getaol(),0,"MDIClient",0);
}
// here
void AOLCPP3I::update()
{

}
// inc25 wrote this
HWND AOLCPP3I::FindFwdWin()
{
HWND child,ahwnd,ahwnd2,ahwnd3;
child=FindWindowEx(getmdi(),NULL,"AOL Child",NULL);
while(child!=0){
child=FindWindowEx(getmdi(),NULL,"AOL Child",NULL);
ahwnd=FindWindowEx(child,NULL,"_AOL_Static","Reply");
ahwnd2=FindWindowEx(child,NULL,"_AOL_Static","Forward");
ahwnd3=FindWindowEx(child,NULL,"_AOL_Static","Reply to All");
if((ahwnd!=0)&&(ahwnd2!=0)&&(ahwnd3!=0)){return child;}
child=GetWindow(child,GW_HWNDNEXT);}
return 0;
}


// inc25 wrote this: works on all version of aol
HWND AOLCPP3I::FindDownloadWindow()
{
HWND child,thegague;
child=FindWindowEx(getmdi(),NULL,"AOL Child",NULL);
while(child!=0){
child=FindWindowEx(getmdi(),NULL,"AOL Child",NULL);
thegague=FindWindowEx(child,NULL,"_AOL_Gauge",NULL);
if(thegague!=0){ {return child;} }
child=GetWindow(child,GW_HWNDNEXT);}
return 0;
}

// get progress bar integer value
int  AOLCPP3I::getdlprogressbar()
{
	HWND prog;
start:
	prog = FindWindowLike_Title(getmdi(),"File Transfer -");
	if(prog)
	{
		char buff[50];
		SendMessage(prog,WM_GETTEXT,50,(LPARAM)(LPCSTR)buff);
		if(instr(buff,"-")) {} else { goto start; }

		int pos1;
		int pos2;

		pos1 = instr(buff,"-");
		pos2 = instr(buff,"%");

		char midbuff[100];
		midstr(buff,midbuff,pos1+1,pos2-1);

		return atoi(midbuff);
		
	}

	return 0;
}
// get progress bar char of the integer value
void AOLCPP3I::getdlprogressbar(char* buffX)
{
		HWND prog;
start:
	prog = FindWindowLike_Title(getmdi(),"File Transfer -");
	if(prog)
	{
		char buff[50];
		SendMessage(prog,WM_GETTEXT,50,(LPARAM)(LPCSTR)buff);
		if(instr(buff,"-")) {} else { goto start; }

		int pos1;
		int pos2;

		pos1 = instr(buff,"-");
		pos2 = instr(buff,"%");

		char midbuff[100];
		midstr(buff,midbuff,pos1+1,pos2-1);
		strcpy(buffX,midbuff);
	}

}

// the AOLCPP3 main class

AOLCPP3::AOLCPP3()
{
	chat.init(&aolcpp_interface);
	im.init(&aolcpp_interface);
	mail.init(&aolcpp_interface);
	aolmain.init(&aolcpp_interface);
}

void AOLCPP3::update()
{
	aolcpp_interface.update();
	chat.update();
	im.update();
	mail.update();
	aolmain.update();
}


// the AOL objects, to manipulate the programs interface

// mail instruction module

void AOLCPP3_MAIL::update()
{

}
// add mailbox to a listbox with sn & date or not
void AOLCPP3_MAIL::mailbox_addtolist(HWND listbox,bool add_sn_date)
{
	if(aolcpp->aolcpp1.getmailbox())
	{

	for(int i = 0; i < aolcpp->aolcpp1.mail_count();i++)
	{
		char string[200];
		aolcpp->aolcpp1.mail_getboxstring(i,string);

		int tb;
		tb = instrfind(string,0,strlen(string),"/");
		int tb2;
		tb2 = instrfind(string,tb+1,strlen(string),"/");

	
		if(add_sn_date)
		{
			SendMessage(listbox,LB_ADDSTRING,strlen(string),(LPARAM)(LPCSTR)string);
		}
		else
		{
			char stringx[200];
			midstr(string,stringx,tb2+4,strlen(string));
			int t;
			t = instr(stringx,"\t");
			char stringxy[200];
			midstr(stringx,stringxy,t+1,strlen(string));
			SendMessage(listbox,LB_ADDSTRING,strlen(string),(LPARAM)(LPCSTR)stringxy);
		}

	}

	}
}
// get the mail count
int AOLCPP3_MAIL::getmailcount()
{
	return aolcpp->aolcpp1.mail_count();
}

// open this index
void AOLCPP3_MAIL::openmail(int index)
{
	aolcpp->aolcpp1.mail_open(index);
}

 
// im instruction module

void AOLCPP3_IM::update()
{

}
// getting the IM data
void AOLCPP3_IM::getimdata(char* buff)
{
	HWND rich;
	rich = FindWindowEx(aolcpp->aolcpp1.getincomingim(),0,"RICHCNTL",0);
	SendMessage(rich,WM_GETTEXT,strlen(buff),(LPARAM)(LPCSTR)buff);
}
// the chat instruction module

void AOLCPP3_CHAT::update()
{

}

void AOLCPP3_CHAT::sendtext(char* buff)
{
	aolcpp->aolcpp1.sendtext(buff);
}


// the chat instruction module

void AOLCPP3_AOLMAIN::update()
{

}




/************* OLD AOLCPP CODE */


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

char* Lleftstr(char* buff2,char* buff1,int num)
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
//    strcpy(sn,leftstr(sn,sn,ex));
	char exc[100];
	leftstr(sn,exc,ex-1);
	strcpy(sn,exc);

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
   HWND rich;
   char text[300];
   char temp[300];
   char a[1] = "";
   edit = FindWindowEx(chat,NULL, "_AOL_Edit",NULL);
   button = GetNextWindow(edit, 2);

   if(edit == 0) 
   {
   //bad way of doing it
   /*edit = GetWindow(GetWindow(chat, GW_CHILD), GW_HWNDFIRST);

   edit = GetNextWindow(edit, 2);
   edit = GetNextWindow(edit, 2);
   edit = GetNextWindow(edit, 2);
   edit = GetNextWindow(edit, 2);
   edit = GetNextWindow(edit, 2);
   edit = GetNextWindow(edit, 2);
   edit = GetNextWindow(edit, 2);
   edit = GetNextWindow(edit, 2);*/

   //good way	   
   rich = getaolwindow(getchatwindow(), RICHCNTL,2); 
   button = GetNextWindow(rich,2);
   }
   SendMessage(rich, WM_GETTEXT,300,(LPARAM)(LPCSTR) temp);
   SendMessage(rich, WM_SETTEXT,1, (LPARAM)(LPCSTR) a);
   SendMessage(rich, WM_SETTEXT,300, (LPARAM)(LPCSTR) str);
   SendMessage(rich, WM_CHAR ,  13, 0);

   SendMessage(rich, WM_GETTEXT,300,(LPARAM)(LPCSTR) text);
   while(strstr(text,str))
   {
   aolclick(button);
   SendMessage(rich, WM_GETTEXT,300,(LPARAM)(LPCSTR) text);
   }

   SendMessage(rich, WM_SETTEXT,300, (LPARAM)(LPCSTR) temp);

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

// Ignore by Index
void AOLCPP::chatignore(int index)
{

	HWND chat;
	chat = getchatlistbox();

   	
	SendMessage(chat, LB_SETCURSEL,index,0);

	// double click

	HWND check;
	HWND win;


	while(true)
	{

		win = FindWindowEx(mdi,0, "AOL Child" , 0);
		check = FindWindowEx(win,0, "_AOL_Checkbox",0);
		if(check) { break; }

	}
	
    SendMessage(check, BM_SETCHECK, (WPARAM)BST_CHECKED,0);
  
	SendMessage(win,WM_CLOSE,0,0);
	
}
void AOLCPP::chatunignore(int index)
{

	HWND chat;
	chat = getchatlistbox();

//    Awindow window;
	
	SendMessage(chat, LB_SETCURSEL,index,0);

//	window.dblclick(chat);

	HWND check;
	HWND win;

	

	while(true)
	{

		win = FindWindowEx(mdi,0, "AOL Child" , 0);
		check = FindWindowEx(win,0, "_AOL_Checkbox",0);
		if(check) { break; }

	}
	
    SendMessage(check, BM_SETCHECK, (WPARAM)BST_UNCHECKED,0);
  
//	window.close(win);
	
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

//    strcpy(textbuff,         rightstr(buff,textbuff,strlen(textbuff),len+1,newlen));
    rightstr(buff,textbuff,len+2);
    strcpy(chatBuff, textbuff);
    return (char*) chatBuff;
    
}
// Get the Screen Name, From a Line of Chat Text
void AOLCPP::chatlinesn(char* line, char* sn)
{

    int col;
    col = instr(line, ':', strlen(line));

//    strcpy(sn, leftstr(sn,line,col));
	leftstr(line,sn,col-1);

}

// Get The Text From a Line of Chat Text
void AOLCPP::chatlinetext(char* line, char* text)
{
    int num;
    num = instr(line,':', strlen(line));
    num++; 
//    strcpy(text, rightstr(line,text,strlen(text),num,strlen(line)));
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

// Copy a Aol ListBox, to Another ListBox (function's messed up)
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
    CopyMemory(&psnHold, sn , strlen(sn));
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

    if((strstr(buff, "File")) || (strstr(buff, "Send")))
    {

        EnableWindow(FindWindow("AOL Frame25",NULL),1);
        ShowWindow(modal, SW_MINIMIZE);

    }

}
void AOLCPP::unupchat()
{

    HWND modal;
    modal = FindWindow("_AOL_Modal",NULL);
    char buff[255];
    SendMessage(modal,WM_GETTEXT,255,(LPARAM)(LPCSTR)buff);

    if((strstr(buff, "File")) || (strstr(buff, "Send")))
    {

        EnableWindow(FindWindow("AOL Frame25",NULL),1);
        ShowWindow(modal, SW_RESTORE);

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

// Open a New Write Mail (true = wait, false = no wait)
void AOLCPP::mail_opennew(bool wait)
{
HWND tool;
tool = gettoolbar();
HWND ico;
ico = FindWindowEx(tool,NULL, "_AOL_Icon",NULL);
ico = GetNextWindow(ico, 2);

aolclick(ico);
if(wait)
{
waitforwindow_title(mdi, "Write Mail");
}
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

// Get The Error Window String
void AOLCPP::mail_geterrorstring(char* buff)
{
HWND err;
err = geterrorbox();
HWND view;
view = FindWindowEx(err,0, "_AOL_View",0);
SendMessage(view, WM_GETTEXT,strlen(buff), (LPARAM)(LPCSTR)buff);
}

// Reset the To: Box Names For Current Mail Window
void AOLCPP::mail_resetnames(HWND mail,char* buff)
{
	HWND ed;
	ed = FindWindowEx(mail,0, "_AOL_Edit",0);
	SendMessage(ed, WM_SETTEXT,strlen(buff), (LPARAM)(LPCSTR)buff);
}

// RESET MAIL SUBJECT
void AOLCPP::mail_resetsub(HWND mail,char* buff)
{
HWND snedit;
HWND subedit;
snedit = FindWindowEx(mail,NULL, "_AOL_Edit",NULL);
subedit = GetNextWindow(snedit, 2);
subedit = GetNextWindow(subedit, 2);
subedit = GetNextWindow(subedit, 2);
subedit = GetNextWindow(subedit, 2);
SendMessage(subedit, WM_SETTEXT,strlen(buff),(LPARAM)(LPCSTR)buff);
}

// RESET MAIL TEXT (RICHCNTL)
void AOLCPP::mail_resettext(HWND mail,char* buff)
{
    HWND mailr;
	mailr = FindWindowEx(mail,0,"RICHCNTL",0);
	SendMessage(mailr, WM_SETTEXT,strlen(buff),(LPARAM)(LPCSTR)buff);
}
//Press Send Button on Current Mail Window
void AOLCPP::mail_send(HWND mail)
{
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
aolclick(sendb); // Click send
}

// Press Forward Button
void AOLCPP::mail_forward(HWND mail)
{
HWND AOLIcon;
	AOLIcon = FindWindowEx(mail, 0, "_AOL_Icon", 0);
for(int i = 1; i < 7; i++)
{
    AOLIcon = FindWindowEx(mail, AOLIcon, "_AOL_Icon", 0);
}
aolclick(AOLIcon);
}

// Hit reply Button on a New Mail
void AOLCPP::mail_reply(HWND mail)
{
HWND AOLIcon;
	AOLIcon = FindWindowEx(mail, 0, "_AOL_Icon", 0);
for(int i = 1; i < 6; i++)
{
    AOLIcon = FindWindowEx(mail, AOLIcon, "_AOL_Icon", 0);
}
aolclick(AOLIcon);
}

// Get the String From a New Mail Window
void AOLCPP::mail_getnewmessage(HWND mail, char* buff)
{
	SendMessage(FindWindowEx(mail,0,"RICHCNTL",0), WM_GETTEXT,strlen(buff),(LPARAM)(LPCSTR)buff);
}

// Remove Error String From Name List  // ERRORSTR MIN 1000, STRING MIN 2000
void AOLCPP::mail_rmverrstring(char* string, char* error)
{

	char nerror[1000];
    char nstring[2000];
	trim_null(error,nerror);

	strcpy(error,nerror);


	// - to .
	// Take The Names From Error Message, and Remove them From String
    if(__instr(error, "."))
	{


		while(__instr(error, "."))
		{

			if(strstr(error, "-"))
			{
			char name[25];
            char newerror[1000];

			int index;
			index = __instr(error, "-") - 1;
			if(index)
			{
            _leftstr(error,name,index);
			}

            int index2;
			index2 = __instr(error, ".");
		    
			if(index2 != 0)
			{
			_rightstr(error,newerror,index2 + 1);
			strcpy(error,newerror);
			
			}
          
            //MessageBox(0, name,0,0);
			strcat(name, ",");
			removestr(string,nstring,name);
			strcpy(string,nstring);

			}
			else
			{
            return;
			}
		}
	}

}

// Tell Me the Mail Window, And The Names TO Remove Broken Names From
void AOLCPP::mail_fixerror(HWND mail, char* namestr)
{
    
	if(geterrorbox())
	{
	char errorstring[1000];
    mail_geterrorstring(errorstring);
	SendMessage(geterrorbox(), WM_CLOSE,0,0);
    mail_rmverrstring(namestr,errorstring);
    mail_resetnames(mail,namestr);
    mail_send(mail);
	}

}

// Send Email to Multiple Users with Screen Name Error Correction
void AOLCPP::mail_senderrorcorrect(char* name, char* sub, char* text)
{

	mail_opennew(true);
	HWND mail;
	mail = getwritemail();
	mail_resetnames(mail,name);
	mail_resetsub(mail,sub);
	mail_resettext(mail,text);

	mail_send(mail);
    
	while(mail)
	{ 
	
		if(geterrorbox())
		{
			mail_fixerror(mail,name);
		}


     mail = getwritemail();
	}


}

// Send Email to Multiple Users with Screen Name Error Correction
void AOLCPP::mail_forwarderrorcorrect(char* name, char* sub, char* text)
{

}



// Get the Error Mail Window
HWND AOLCPP::geterrorbox()
{
HWND Wnd;
Wnd = FindWindowEx(getmdi(), 0, "AOL Child", "Error");
return Wnd;
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



//--------------------
/*


Basic Style String Functions (NON MSTRING CLASS)

*/

void _leftstr(char* buff, char* buff2, int index)
{
strcpy(buff2, buff);
buff2[index + 1] = 0;
}


void _rightstr(char* buff, char* buff2, int index)
{
 
	int i = 0;
	int len = strlen(buff);
	for(int x = index; x < len; x++)
	{
     buff2[i] = buff[x];
	 i++;

	}
     buff2[i] = 0;

}


void lcase(char* buff)
{
int len = strlen(buff);
for(int i = 0; i < len; i++)
{

	buff[i] = tolower(buff[i]);

}

}

void ucase(char* buff)
{
int len = strlen(buff);
for(int i = 0; i < len; i++)
{

buff[i] = toupper(buff[i]);
}


}

void _midstr(char* buff, char* buff2, int start, int stop)
{

	int i = 0;
	for(int x = start; x < stop; x++)
	{
    buff2[i] = buff[x];
	i++;

	}
    buff2[i] = 0;

}

int __instr(char* buff, char* search)
{

	int slen = strlen(search);
	int blen = strlen(buff);

	for(int x = 0; x < blen; x++)
	{

		if(buff[x] == search[0])
		{
            int ss = x;
			bool start = true;

			for(int i = 0; i < slen; i++)
			{

				if(buff[x+i] == search[i])
				{


				} else
				{

					start = false;

				}

			}
			 if(start == true)
			 {

         		 return ss;
			 }

		}



	}

  



return 0;

}

void trim_null(char* buff, char* nbuff)
{
    int len = strlen(buff);
    
	int j = 0;

	for(int i = 0; i < len; i++)
	{
    
		if((buff[i] != '\n')  && (buff[i] != ' ') && (buff[i] != '\r'))
		{

			nbuff[j] = buff[i];
			j++;

		}


	}
     nbuff[j] = 0;

}


void replacestr(char* buff, char* nbuff,  char* rp, char* wp)
{

 if(strstr(buff, rp))
 {

	 int len;
	 len = strlen(buff);

	 for(int r = 0; r < len; r++)
	 {



	 }


 }
	 

}

void addreturn(char* buff) // add \r\t to char array (carrige return)
{
char tmp[2];
tmp[0] = '\r';
tmp[1] = '\n';
strcat(buff, tmp);
}

void removestr(char* str, char* nstr, char* removestring)
{
int x = __instr(str, removestring);
if(x)
{
	int j = 0;
    int el;
	el = x + strlen(removestring);
    int len;
	len = strlen(str);

	for(int i = 0; i < len; i++)
	{

		if((i > x - 1) && (i < el))
		{
          // pause and do not edit
		}
		else
		{
           nstr[j] = str[i];
           j++;
		}
	}
   nstr[j] = 0;
}

}

//********** the Lost String algorithims



void LostString::setstr(char* buff)
{
	if(myStr != 0)
	{
	delete [] myStr;
	}
	int len;
	len = strlen(buff) + 1;
	myStr = new char[len];
	strcpy(myStr,buff);
}

void LostString::getstr(char* buff,char* ibuff)
{
	if(myStr) 
	{
	strcpy(ibuff,myStr);
	}
}

char* LostString::getstr()
{
	return myStr;
}

void LostString::addstr(char* buff)
{
	char* pOld;
	pOld = new char[getlen()+1];
	strcpy(pOld,myStr);

	delete[] myStr;
	myStr = new char[getlen() + strlen(buff) + 2];
	strcpy(myStr,pOld);
	delete [] pOld;
	strcat(myStr,buff);
}


int LostString::getlen()
{
	return strlen(myStr);
}

LostString::LostString()
{
	myStr = 0;
}

LostString::LostString(char* buff)
{
	setstr(buff);
}

LostString::~LostString()
{
	delete [] myStr;
}

void LostString::operator=(char* buff)
{
	delete [] myStr;
	int len;
	len = strlen(buff);
	myStr = new char[len+1];
	strcpy(myStr,buff);
}

int  LostString::IntegerValue()
{
	return ConvertStringToInt(myStr);
}

void LostString::operator +=(char* buffx)
{
	int len;
	int xlen;
	len = strlen(myStr);
	xlen = strlen(buffx);
	int tlen;
	tlen = len + xlen + 2;

	char* tempOld;
	tempOld = new char[len+1];
	strcpy(tempOld,myStr);

	delete [] myStr;

	myStr = new char[tlen];
	strcpy(myStr,tempOld);
	strcat(myStr,buffx);

	delete [] tempOld;
}

void LostString::operator +=(int x)
{
	char buffx[10];
	itoa(x,buffx,10);
	int nlen;
	nlen = getlen() + 10 + 2;

	char* oldT;
	oldT = new char[getlen()+1];
	strcpy(oldT,myStr);

	delete [] myStr;
	myStr = new char[nlen];
	strcpy(myStr,oldT);
	strcat(myStr,buffx);

	delete [] oldT;
}



void LostString::qMsgBox(char* title)
{
	MessageBox(0,myStr,title,MB_OK | MB_ICONINFORMATION);
}

void LostString::qMsgBox()
{
	MessageBox(0,myStr,"LostString Quick Message",MB_OK | MB_ICONINFORMATION);
}

void LostString::CopyTo(LostString* lost)
{
	lost->setstr(myStr);
}

void LostString::CopyTo(char* buff)
{
	strcpy(buff,myStr);
}

void LostString::AttachTo(char* buff)
{
	strcat(buff,myStr);
}

void LostString::AttachTo(LostString* lost)
{
	lost->addstr(myStr);
}

void LostString::clear()
{
	if(myStr != 0)
	{
		delete [] myStr;
		myStr = 0;
	}
}

int  LostString::InString(char* buff)
{
	return instr(myStr,buff);
}

int  LostString::InStringBackward(char* buff)
{
	return instrback(myStr,buff);
}

int  LostString::InStringFind(int start,int stop,char* search)
{
	return instrfind(myStr,start,stop,search);
}
 
int  LostString::InStringFindBackwards(int start,int stop,char* search)
{
	return instrbfind(myStr,start,stop,search);
}


//************* assorted algorithims

// String Manipulation Functions 
void leftstr(char* buff, char* buff2, int index)
{

	strcpy(buff2, buff);
    buff2[index + 1] = 0;

}


void Lrightstr(char* buff, char* buff2, int index)
{
 
	int i = 0;
	int len = strlen(buff);
	for(int x = index; x < len; x++)
	{
     buff2[i] = buff[x];
	 i++;

	}
     buff2[i] = 0;
}

void midstr(char* buff, char* buff2, int start, int stop)
{

	int i = 0;
	for(int x = start; x < stop; x++)
	{
    buff2[i] = buff[x];
	i++;

	}
    buff2[i] = 0;
	buff2[i+1] = '\0';

}

int instr(char* buff, char* search)
{

	int slen = strlen(search);
	int blen = strlen(buff);

	for(int x = 0; x < blen; x++)
	{

		if(buff[x] == search[0])
		{
            int ss = x;
			bool start = true;

			for(int i = 0; i < slen; i++)
			{

				if(buff[x+i] == search[i])
				{


				} else
				{

					start = false;

				}

			}
			 if(start == true)
			 {

         		 return ss;
			 }

		}
	}

	return -1;
}

//backwards earch
int instrback(char* buff, char* search)
{
	int len;
	len = strlen(buff);
	for(int i = len; i > 0; i--)
	{

		if(buff[i] == search[0])
		{
			int slen;
			slen = strlen(search);
			bool stest = false;

			
			for(int y = 0; y < slen; y++)
			{
				if(buff[i+y] == search[y]) 
				{
                 stest = true;
				} else { stest = false; }
			}

			if(stest == true) { return i; }
		}

	}

	return 0;
}

int instrfind(char* buff,int start, int stop, char* search)
{
	int slen = strlen(search);
	int blen = strlen(buff);

	for(int x = start; x < stop; x++)
	{

		if(buff[x] == search[0])
		{
            int ss = x;
			bool start = true;

			for(int i = 0; i < slen; i++)
			{

				if(buff[x+i] == search[i])
				{


				} else
				{

					start = false;

				}

			}
			 if(start == true)
			 {

         		 return ss;
			 }

		}
	}

	return 0;


}

int instrbfind(char* buff, int start, int stop, char* search)
{

	for(int i = start; i > stop; i--)
	{

		if(buff[i] == search[0])
		{
			int slen;
			slen = strlen(search);
			bool stest = false;

			
			for(int y = 0; y < slen; y++)
			{
				if(buff[i+y] == search[y]) 
				{
                 stest = true;
				} else { stest = false; }
			}

			if(stest == true) { return i; }
		}

	}

	return 0;
}

void removecomment(char* source, char* newsource)
{
	int len;
	len = strlen(source);
	int index = 0;

	LPVOID tsource;
	tsource = new PCHAR[strlen(source)];
	strcpy((char*)tsource,source);

	while(instr((char*)tsource, "/*"))
	{
		int lslash;
		lslash = instr((char*)tsource,"/*");
		LPVOID ldat;
		ldat = new PCHAR[lslash + 1];
	    leftstr((char*)tsource,(char*)ldat,lslash-1);
	//	MessageBox(0,(char*)ldat,0,0);
		LPVOID rdat;
		int rlash;
		rlash = instr((char*)tsource, "*/");
		if(rlash == 0) { // comment error
			return;    }

		rdat = new PCHAR[strlen((char*)tsource) - rlash];
		rightstr((char*)tsource,(char*)rdat,rlash+2);

		strcpy((char*)tsource, (char*)ldat);
		strcat((char*)tsource, (char*)rdat);

	
	}

	strcpy(newsource,(char*)tsource);
}

// trim space crap
void trimspace(char* s, char* ns)
{
	int len;
	len = strlen(s);
	int index = 0;

	for(int i = 0; i < len; i++)
	{
		if((s[i] != ' ') && (s[i] != '\r') && (s[i] != '\n'))
		{
		ns[index] = s[i];
		index++;
		}
	}
    ns[index] = 0;
}

void extractfunc(char* code, char* func)
{
    // we are only called if we know there is code  in code
	char errbuff[1000];



	int fbo;
	int fpo;
	int fpc;

	fbo = instr(code, "{");
	fpo = instr(code, "(");
	fpc = instr(code, ")");

	if(fbo)
	{
   
		if(fpo) {

			if(fpc)
			{

			char namet[300];
			leftstr(code,namet,fpc);
			// now namet holds the function head
		    char body[3000];
			rightstr(code,body,fbo);

		//	MessageBox(0,namet,0,0);
		//	MessageBox(0,body,0,0);
			
			} else {
                  strcpy(errbuff, "missing closing )");
				  return;
			}


		} else {

           strcpy(errbuff, "missing opening par (");
		   return;

		}

 
	} else {

		strcpy(errbuff, "No opening brace!");
		return;
	}
}
// first lst brace
void f_lbrace(char* input, char* output)
{
	int firstpar;
	int lastpar;
	firstpar = instr(input, "{");
	lastpar = instr(input, "};");

	if(firstpar == 0) { return; // no first par
	}
	if(lastpar  == 0) { return; // no last par
	}

	midstr(input,output-1,firstpar,lastpar-1);
}
// full brace
void fullbrace(char* input, char* output)
{


}
// get the first statement in a function body
int firststatement(char* input, char* output)
{

	int len;
	len = strlen(input);
	int m;

	int count = 0;
	int count2 = 0;

	int start = 0;
	int stop = 0;

	for(m = 0; m < len; m++)
	{

    if(input[m] == '{')
	{
		count++;
		if(count == 1)
		{
			start = m;
		}
	}

	if(input[m] == '}')
	{
		count2++;

		if(count == count2)
		{
           leftstr(input,output,m);
		   if(instr(input, "else"))
		   {
		   char** checkif;
		   checkif = new PCHAR[strlen(input)];
		   rightstr(input,(char*)checkif,m+1);

		   int e;
		   int b;
		   e = instr((char*)checkif, "else");
		   b = instr((char*)checkif, "{");

		   if(b)
		   {

			   if(e < b)
			   {

				 // run same algorithim to capture the last par via recursion
				char** righte;
				righte = new PCHAR[strlen((char*)checkif)+1];
				rightstr((char*)checkif,(char*)righte,e + 4);
				char** full;
				full = new PCHAR[strlen(input)+1];
				char** estat;
				estat = new PCHAR[strlen((char*)righte)+1];
				firststatement((char*)righte,(char*)estat);

				strcat((char*)output, "else");
				strcat((char*)output, (char*)estat);

				int elast  = 0;
				int estart = 0;
				int ecount = 0;
				int ecountl = 0;  
				int eindex = 0;
				int elen   = 0;
				int rtVal  = 0;
				elen = strlen(input);

				for(int im = 0; im < elen; im++)
				{
					if(input[im] == '{')
					{
						ecount++;

						if(ecount == 1)
						{
							estart = im; 
						}
					}
					if(input[im] == '}')
					{
						ecountl++;

						if(ecountl == ecount)
						{
							eindex++;
							if(eindex == 2)
							{
								rtVal = im;
							}


						}
						
					}
				}

				return rtVal;


			   }

		   } else { return 0; } // error on else


		   } else
		   {
			   return m;
		   }

		}
	}

	}
	return NULL;
}

void qbox(char* f)
{
	//cout << f;
	MessageBox(0,f,"qboxstr",0);
	
}
// get the else head data
void getelsehead(char* input, char* output)
{
	strcpy(input,output);
	return;
//	MessageBox(0,input,"get else head",0);
	// go b


}


// get the head data
void gethead(char* input, char* output)
{
	
	int len;
	len = strlen(input);

	int bcount;
	int fcount;

	// first ones { }


	for(int i = len; i > 0; i--)
	{
		if(input[i] == '}')
		{
			fcount++;
		}

		if(input[i] == '{')
		{
			bcount++;
			if(bcount > fcount)
			{

               leftstr(input,output,i-1);
			   
			   int c;
			   int o;
			   c = instrback(output, "}");
			   o = instrback(output, "{");
			   int e;
			   e = instrback(output, "else");

			   if((e != 0) && (e > c) && (e > o))
			   {
                
				   
				   char** temp;
				   temp = new PCHAR[strlen(output)];
				   strcpy((char*)temp,output);
				   getelsehead((char*)temp,output);
			   }
			   break;
			}

		}


	}


}

void procfunc(char* code)
{
	int len;
	len = strlen(code);
	char** curcode;
	char** curcmd;
	char** curhead;
	char** temphead;



	curcode = new PCHAR[strlen(code)];
	curcmd  = new PCHAR[strlen(code)];
	curhead = new PCHAR[strlen(code)];
	temphead = new PCHAR[strlen(code)];


	char*  ccode;
	char*  ccmd;
	char*  chead;
	char*  thead;


	ccode = (char*) curcode;
	ccmd  = (char*) curcmd;
	chead = (char*) curhead;
	thead = (char*) temphead;
	


	for(int i = 0; i < len; i++)
	{
		if(code[i] == ';')
		{
	// make sure its not the last ; on the body of code
           leftstr(code,(char*)curcode,i);

		   int fs;
		   int ss;
		   int fo;
		   int fc;
		   
		   fs = instrback(ccode, ";");
		   fo = instrbfind(ccode,fs-1,0,"{");
		   ss = instrbfind(ccode,fs-1,0,";");
		   fc = instrbfind(ccode,fs-1,0,"}");

		   if((ss != 0) && (ss > fo) && ( ss > fc ))
		   {

			   rightstr(ccode,ccmd,ss+1);


		   } else if ((fo != 0) && (fo > ss) && (fo > fc))
		   {
			   rightstr(ccode,ccmd,fo+1);

		   } else if ((fc != 0) && (fc > fo) && ( fc > ss))
		   {
               rightstr(ccode,ccmd,fc+1);

		   }

           gethead(ccode,thead);// full head
		   strcpy(chead,thead);
		   char buff[200];
		   strcpy(buff, "");
	

		   while(instr(thead, "{"))
		   {
			   
			   gethead(thead, buff);
			   strcpy(thead,buff);
			   strcat(chead,buff);


			   
		   }
	

		   MessageBox(0,chead,"the head",0);

	//

		
		
		
		}
	}



}


void getopen(char* input, char* output)
{


	int len;
    len = strlen(input);



	char** tempinput;
	char* tinput;
	tempinput = new PCHAR[strlen(input)+1];
	tinput = (char*)tempinput;
	strcpy(tinput,input);

	// going backwards, find the first OPEN with no close
	// FIND FIRST OPEN WITH NO CLOSE

	int open_count  = 0;
	int close_count = 0;

	for(int i = len; i > 0; i--)
	{
		if(input[i] == '{')
		{
			open_count++;

			if(open_count > close_count)
			{
				leftstr(input,output,i-1);
				break;
			}

		}

		if(input[i] == '}')
		{
           close_count++;

		}
	}

}




void getcmd(char* code, char* cmd)
{

	int fs;
	int ss;
	int fo;
	int fc;
	int rt;

	fs = instrback(code, ";");
	ss = instrbfind(code,fs-1,0,";");
	fo = instrbfind(code,fs-1,0,"{");
	fc = instrbfind(code,fs-1,0,"}");
	rt = instrbfind(code,fs-1,0,"\r\n");

	if((ss != 0) && (ss > fo) && (ss > fc) && (ss > rt))
	{
		midstr(code,cmd,ss+1,fs+1);

	}

	if((fo != 0) && (fo > ss) && (fo > fc) && (fo > rt))
	{
		midstr(code,cmd,fo+1,fs+1);
	}

	if((fc != 0) && (fc > fo) && (fc > ss) && (fc > rt))
	{
        midstr(code,cmd,fc+1,fs+1);
	}

	if((rt != 0) && (rt > fo) && (rt > fc) && (rt > ss))
	{
       midstr(code,cmd,rt+2,fs+1);
	}

}

void getstate(char* code, char* state)
{
	int len;
	len = strlen(code);

	int closec = 0;
	int openc = 0;

	int open_index[100];
//	int close_index[100];


	char head[200];
	strcpy(state,"");
	strcpy(head, "");

	// fill out a list of what points to copy
	// then copy them

	for(int z = 0; z < len; z++)
	{
    
		if(code[z] == '{')
		{
	       	open_index[openc] = z;
			openc++;
		
		}
	}

	for(int c = 0; c < openc; c++)
	{
		bool chk;
		chk = checkforclose(code,open_index[c]);
		if(chk == true)
		{
			getstatehead(code,open_index[c],head);
			strcat(state,head);
			strcat(state,";");
		}
	}

	// check if { has its matching }
	

	
}

bool checkforclose(char* input, int open)
{
	int len;
	len = strlen(input);
	int openc = 0;
	int closec = 0;

	for(int i = open; i < len; i++)
	{
		if(input[i] == '{')
		{
		 openc++;
		}

		if(input[i] == '}')
		{
         closec++;

		 if(openc == closec)
		 {
			 return false;
		 }

		}
	}

return true;
}

void getstatehead(char* input, int open, char* output)
{
	
  
	leftstr(input,output,open-1);

	int chko;
	int chkc;
	int chks;

	chko = instrback(output,"{");
	chkc = instrback(output,"}");
	chks = instrback(output, ";");

	char** temp;
	temp = new PCHAR[strlen(output)+1];
	char*  tout;
	tout = (char*) temp;


	if((chkc == 0) && (chko == 0) && (chks == 0))
	{

		strcpy(tout,output);
	}

	if((chko != 0) && (chko > chkc) && (chko > chks))
	{
    rightstr(output,tout,chko+1);
	}

	if((chkc != 0) && (chkc > chko) && (chkc > chks))
	{
    rightstr(output,tout,chkc+1);
	}

	if((chks != 0) && (chks > chkc) && (chks > chko))
	{
    rightstr(output,tout,chks+1);
	}
	strcpy(output,tout); 
	 

   //MessageBox(0,input,"input",0);


}
// is this string data a masterx function
bool iffunc(char* input)
{
int chkpar;
chkpar = instr(input, "()");
if(chkpar != 0) { return true; }

chkpar = instr(input, ",");
if(chkpar != 0)
{
return true;//yes a function
}
return false;
}

// are these two strings equal
bool isstrequal(char* i1, char* i2)
{

	char** temp;
	char** temp2;
	temp = new PCHAR[strlen(i1)];
	temp2 = new PCHAR[strlen(i1)];
	char*  n1;
	char*  n2;
	n1 = (char*)temp;
	n2 = (char*)temp2;
	trimspace(i1,n1);
	trimspace(i2,n2);

	int l1;
	int l2;
	l1 = strlen(n1);
	l2 = strlen(n2);

	if(l1 != l2) { return false; }

	if(strstr(i1,i2))
	{
		return true;
	}
	else { return false;}


	return false;
}

// trim comments
void trimcomment(char* input,char* output)
{
	char** temp;
	char** temp2;
	char** temp3;

	temp = new PCHAR[strlen(input)+1];
	temp2 = new PCHAR[strlen(input)+1];
	temp3 = new PCHAR[strlen(input)+1];

	char* theleft;
	char* theright;
	char* theinput;

	theleft = (char*)temp;
	theright = (char*)temp2;
	theinput = (char*)temp3;

	strcpy(theinput,input);


	while((instr(theinput, "//")) || (instr(theinput, "/*")))
	{
		int chk1;
		int chk2;
		int len;
		len = strlen(theinput);
		chk1 = instr(theinput, "//");
		chk2 = instr(theinput, "/*");

		if((chk1 != 0) && (chk1 > chk2))
		{
			int chk1e;
			chk1e = instrfind(theinput,chk1+2,len,"\n");

			leftstr(theinput,theleft,chk1-2);
			rightstr(theinput,theright,chk1e+1);

			strcpy(theinput,theleft);
			strcat(theinput, theright);
		}

		if((chk2 != 0) && (chk2 > chk1))
		{
			int chk2e;
			chk2e = instrfind(theinput,chk2+2,len,"*/");
			
			leftstr(theinput,theleft,chk2-2);
			rightstr(theinput,theright,chk2e+2);

			strcpy(theinput,theleft);
			strcat(theinput,theright);

		}
	}

	strcpy(output,theinput);

}

bool standardfunc(char* input)
{

	int chk;
	chk = instr(input, "()");
	if(chk)
	{

		if(chkifop != 0)
		{ 
			return false;
		}
		else
		{

			return true;

		}
	}

return false;

}

bool chkifop(char* op)
{

	if(strstr(op, "+")) { return true; } 
	if(strstr(op, "-")) { return true; }
	if(strstr(op, "\\")) { return true; }
	if(strstr(op, "*")) { return true; }
	if(strstr(op, "=")) { return true; }
	if(strstr(op, "&")) { return true; }
	if(strstr(op, "|")) { return true; }
	if(strstr(op, "==")) { return true; }
	if(strstr(op, "!=")) { return true; }
	if(strstr(op, "<>")) { return true; }
	if(strstr(op, "or")) { return true; }
	if(strstr(op, "and")) { return true; }

	
return false;
}


int getfirstsyntax(char* code, int pos)
{

	int len;
	len = strlen(code);
	int syn_if = instrfind(code,pos+1,len,"if");

	if(syn_if) { return syn_if; }

	int syn_else = instrfind(code,pos+1,len,"else");
	if(syn_else) { return syn_else; }

	int syn_console;
	syn_console = instrfind(code, pos+1,len,"console");

	int syn_object;
	syn_object  = instrfind(code,pos+1,len,"object");
	if(syn_object) { return syn_object; }

	return NULL;
}


// parameter converter stuff

// convert the buffer into parameter form



// to format data for keypresses

char fixkeys(int key,int caps,bool cmd)
{

		char cur;	
		int shift;
		shift = 0;
		// shift switch
		if(GetAsyncKeyState(16))
		{
			shift = 1;
			if(caps)
			{
			cur = tolower(key);
			}
			else
			{
			cur = toupper(key);
			}
			// special shift character switch

			switch(cur)
			{
			case '0':
				cur = ')';
				break;
			case '1':
				cur = '!';
				break;
			case '2':
				cur = '@';
				break;
			case '3':
				cur = '#';
				break;
			case '4':
				cur = '$';
				break;
			case '5':
				cur = '%';
				break;
			case '6':
				cur = '^';
				break;
			case '7':
				cur = '&';
				break;
			case '8':
				cur = '*';
				break;
			case '9':
				cur = '(';
				break;
			}
		}
		else
		{

		if(caps)
		{
		   cur =  toupper(key);
		}
		else
		{
		   cur = tolower(key);
		}
		}

		// quick key to special char switch
		switch(key)
		{
		case 220:

			cur = '\\';

			break;

		case 191:
			if(shift)
			{
			cur = '?';
			}
			else
			{

			cur = '/';
			}

			break;

 		case 192:

			cur = 'µ';
			break;

		case 186:
			if(shift)
			{
				cur = ':';
			}
			else
			{
			cur = ';';
			}
			break;

		case 219:

			if(shift)
			{
				if(cmd == false)
				{
				cur = '{';
				}
				else
				{
                cur = '/';
				}
			}
			else
			{
				cur = '[';
			}

			break;
		case 221:
			if(shift)
			{
				if(cmd == false)
				{
				cur = '}';
				}
				else
				{
                cur = '\\';
				}
			}
			else
			{
				cur = ']';
			}

			break;
		case 187:
			if(shift)
			{
				cur = '+';
			}
			else
			{
				cur = '=';
			}
			break;
		case 189:

			if(shift)
			{
				cur = '_';
			}
			else
			{
				cur = '-';
			}

			break;
		case 188:

			if(shift)
			{
				cur = '<';
			}
			else
			{
				cur = ',';
			}

			break;

		case 190:

			if(shift)
			{
				cur = '>';
			}
			else
			{
				cur = '.';
			}


			break;
		case 222:
			if(shift)
			{
				cur = '\"';
				break;
			}
			else
			{
				cur = '\'';
				break;
			}
			


			break;

		}

		return cur;
}

int ConvertStringToInt(char* string)
{
	return atoi(string);
}



void removeStar(char* buff)
{
	int len = strlen(buff);
	for(int i = 0; i < len; i++)
	{
		if(buff[i] == '*')
		{
			buff[i] = 0;
		}
	}
}





