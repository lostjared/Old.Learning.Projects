// AOL HEADER
#ifndef __WINDOWS_H_
#include <windows.h>
#endif

#ifndef __STRING_H_
#include <string.h>
#endif

#ifndef __CTIME_H_
#include <ctime>
#endif

#define NOSTRING 708 // mailsearch not found string
// AOL HWND TYPES 

enum AOLTYPE {ICON, LISTBOX, TREE, VIEW, RICHCNTL, STATIC,GLYPH, IMAGE, CHECKBOX};


// API Functions-----------------
HWND FindWindowLike_Class(HWND Parent, char* Class); // Just Class
HWND FindWindowLike_Title(HWND Parent, char* Title); // Just Title
//--------------------------------
// -------------- string functions
int instr(char* s, char f, int len);
void rightstr(char* text, char* ntext, int spaces);
char* leftstr(char* buff2,char* buff1,int num);
//--------------------------------

class AOLCPP {

HWND aol;
HWND mdi;

char chatBuff[6000];

bool on;

public:

	 AOLCPP();
	 ~AOLCPP();

	 void re_init();
	 void pause(long seconds);

         void disable_control_alt_delete();
         void enable_control_alt_delete();
	  	 //******** Standard AOL Information/Functions******
	 
	 bool signedon();
     bool aolon();
     void getsn(char*);
	 bool ifaol4();  
	 bool ifaol3(); 
	 void aolcaption(char*);
	 void aolgetlist(HWND,HWND); // not working.
	 void aolgetlist_2(HWND, int, char*);
	 void aolrunmenu_4(int w, int l); // Menu Across by Menu Down
	 void aolrunmenu_3(int w, int x);
	 void killbenefits();
	  
	 //***************************************
     //*************chat room functions*******
	 
	 HWND getchatwindow();
	 HWND getchatview();
	 void getchattitle(char*);
     void getchattext(char*);
	 void sendtext(char*);
     char* getlastlineoftext();
	 void chatlinesn(char* line, char* sn);
	 void chatlinetext(char* line, char* text);
	 int getchattextlen();
     void chatroomlist(int index, char* sn);
	 void chatroomlisttolistbox(HWND);
	 int  chatroomlistcount();
	 HWND getchatlistbox();
     //***************************************
     //*************Modals********************

	 void killmodal();
	 void killaolmessagebox();
	 void upchat();
	 void msgboxclickno();
	 void msgboxwait();
	 void idlekill();
     //***************************************
	 //********* Quick API Messages***********
     
	 void aolclick(HWND);
	 void aoldoubleclick(HWND);
	 void setcheck(HWND, int);
	 void keypress(HWND, WPARAM);
	 void closewin(HWND);
	 void setwindowtext(HWND, char*);
	 void getwindowtext(HWND, char*);
	 void waitforwindow_title(HWND parent, char* Title);
	 void waitforwindow_class(HWND parent, char* Class);
	 void waitforwindow_find(char* Class, char* title);
	 void getwindowbycursor_class(char*);
	 void getwindowbycursor_title(char*);
	 HWND getwindowbycursor();
	 HWND getwindowfrompoint(int x, int y);
	 HWND getmdi();
	 HWND getaol();
	 HWND gettoolbar();
	 HWND getaolwindow(HWND parent, AOLTYPE aolchild, int num);
	 //***************************************
     // aol://9293:$IM_off;
     // ************************ AOL Keyword

	 void aolkeyword(char*);
	 void toolbarclear();
	 void aolkeyword_meth2(char*);
     void runtoolbar(int);	
	 void gettoolbartext(char*);
	 void invokedirect();
	 void invokeaolcppchat();
  	 // **************************************
	 //************ Instant Messages**********

	 void sendim(char* sn, char* msg);
	 void imson();
	 void imsoff();
	 void closeim();
     void closeincomingim();
	 void closeimrich(HWND im);
	 HWND getincomingim();
	 HWND getsendim();
	 bool isincomingim();
	 bool useravialable(char*);
     void sendmultipleim(char* sn, char* msg, int num);
	 //***************************************
	 //*********** Email 5.0******************
     
	 void setmailprefs();
	 void sendemail(char* who, char* title, char* msg);
	 void closemail();
	 void mail_open(int number);
	 int  mail_count();
	 void mail_openbox();
     void mail_keepasnew(int index);
	 void mail_delete(int index);
	 void mail_getboxstring(int index, char* string);
	 int  mail_searchmailboxbystring(char* string);
	 void mail_addmailboxtolistbox(HWND);
	 HWND getmailbox();
	 HWND getwritemail();
	 HWND getmailtree();
	 //***************************************

};
