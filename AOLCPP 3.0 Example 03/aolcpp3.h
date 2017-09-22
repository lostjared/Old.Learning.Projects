// aolcpp3 by Master on LSD some people call me Jared
// aolcpp3 site :  http://www.lostsidedead.com/aolcpp3/
// www.aolcpp.cjb.net
// email: masteronlsd@lostsidedead.com  aim: master on lsd
// www.lostsidedead.com

// this source file is freeware
// the only term to using this is that you visit my web page
// and say hey master on lsd, in your program or something
// or put some jive like 'powered by aolcpp'
// I dunno, have fun trippin off these codes
// I know ill always remember how fun it was to write them
// this was just for pratice, request from friend
// to expand the shotty AOLCPP and give it a new interface
// and allow it to still have backwards compatibility with
// AOL6 / a 'doevent' simulation style of functions
/*---------------------------------------------------

  written by 
   -Master on LSD/ jared

----------------------------------------------------*/
/* EXPLANATION

  The AOLCPP 3.0 

  aolcpp3 contains the orignal aolcpp for aol4/5
  and adds a new interface so you can easily add
  and manage new functions into your aolcpp3
  class.

  the aolcpp3 class is to be thought of kinda like
  a remote control within the class are a number
  of objects that will handle manipulating a certin
  area of aol. like the chat object can be filled
  with all the new functions nessicary to manipulate
  the aol6 interface. while still providing an acitve
  pointer back to the AOLCPP1.0 class interface so that
  you can use any of the older functions.

  what this means is by looking at were I put notes at
  you can make all new functions that fit into any part
  of the new AOLCPP3 objects interface so that your
  object can use all the things call cpp can do and sitll
  evolve into what is nessicary for your specific task.

  example you can take all the things that aolcpp does
  and build a new object that sits inside the interface
  that has all the things nessicary for mail fowarder
  or spammer its that type of concept. Peice together
  your AOL functions from the methods that exisit
  inside. Then use this class in your program to totaly
  encapsulate aol interface manipulation proccess


  // note if you want to use the functions, that pass there
  // loops and waiting into the update, so that they can
  // not freeze up the app,(like doevents) make sure you have 
  // the update
  // method being called inside the programs loop. 
  // thats inside the while(GetMessage(&msg,0,0,0)) {} block

  note2:

  c++ is very fast and is touchy. alot of vb proggers usin this
  havent figured out that doevents isnt here
  well, how you would make it work is have a function
  that always calls, but only does certin steps in
  a order that gets them complete while still allowing
  the other instructions to execute, also note
  that when aol freezes up, its because the loop
  is going to fast, and it freezes up and dies
  use a pausing method within your function
  or use a timer that can check up on things
  ethier way it can work. and fast to

*/

#include <windows.h>
#include <string.h>
#include <ctime>


#define NOSTRING 708 // mailsearch not found string
#define MSIZE 1000 // Set Your Maximum Basic String Size
// AOL HWND TYPES 

enum AOLTYPE {ICON, LISTBOX, TREE, VIEW, RICHCNTL, STATIC,GLYPH, IMAGE, CHECKBOX};


// API Functions-----------------
HWND FindWindowLike_Class(HWND Parent, char* Class); // Just Class
HWND FindWindowLike_Title(HWND Parent, char* Title); // Just Title
// the AOLCPP (aol4/5) base instruction class interface
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
	 void chatignore(int index);
	 void chatunignore(int index);
     HWND getchatlistbox();
	 //***************************************
     //*************Modals********************

     void killmodal();
     void killaolmessagebox();
     void upchat();
	 void unupchat();
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
	 void mail_opennew(bool);
     void mail_keepasnew(int index);
     void mail_delete(int index);
     void mail_getboxstring(int index, char* string);
     int  mail_searchmailboxbystring(char* string);
     void mail_addmailboxtolistbox(HWND);
	 void mail_geterrorstring(char*);
	 void mail_resetnames(HWND,char*);
	 void mail_resetsub(HWND,char*);
	 void mail_resettext(HWND,char*);
	 void mail_send(HWND);
	 void mail_forward(HWND);
	 void mail_reply(HWND);
	 void mail_getnewmessage(HWND,char*);
	 void mail_rmverrstring(char* string, char* error);
	 void mail_fixerror(HWND mail, char*);
     void mail_senderrorcorrect(char* name, char* sub, char* text);
	 void mail_forwarderrorcorrect(char* name, char* sub, char* text);


	 HWND geterrorbox();
     HWND getmailbox();
     HWND getwritemail();
     HWND getmailtree();
     //***************************************

};

// aolcpp3 class interfaces
class AOLCPP3I
{
public:
	AOLCPP aolcpp1;
	HWND getaol();
	HWND getmdi();
	HWND FindFwdWin();
	HWND FindDownloadWindow(); 
	void update();
	int  getdlprogressbar();
	void getdlprogressbar(char* buff);
}; // note: this is were you add in your main aolcpp3.0 (aol6.0) functions


// a AOLCPP3 Object
class AOLCPP3_OBJ
{
public:
	AOLCPP3I* aolcpp;
	void init(AOLCPP3I* aolcppx);
};

// the aol mail object
class AOLCPP3_MAIL : public AOLCPP3_OBJ
{
public:
	void mailbox_addtolist(HWND listbox,bool add_sn_date);
	int getmailcount();
	void openmail(int index);
	void update();
};//note: here is were you add all your new mail functions


// the aol im object
class AOLCPP3_IM   : public AOLCPP3_OBJ
{
public:
	void getimdata(char* buff);
	void update();
};// note: here is were you add all your new IM functions

// the aol chat object
class AOLCPP3_CHAT : public AOLCPP3_OBJ
{
public:
	void sendtext(char* buff);
	void update();
};// note: here is were you add all your  new CHAT functions

// the aol main object
class AOLCPP3_AOLMAIN : public AOLCPP3_OBJ
{
public:
	void update();
	
};//note: here is were you add all your new MAIN functinos


// the AOLCPP interface
class AOLCPP3
{
public:
	AOLCPP3I aolcpp_interface;
	AOLCPP3_MAIL mail;
	AOLCPP3_IM   im;
	AOLCPP3_CHAT chat;
	AOLCPP3_AOLMAIN aolmain;

	void update();

	AOLCPP3();
};

// API Functions-----------------
HWND FindWindowLike_Class(HWND Parent, char* Class); // Just Class
HWND FindWindowLike_Title(HWND Parent, char* Title); // Just Title
//--------------------------------
// -------------- string functions
int instr(char* s, char f, int len);
void Lrightstr(char* text, char* ntext, int spaces);
char* Lleftstr(char* buff2,char* buff1,int num);
//--------------------------------
/*
MSTRING FUNCTIONS / EASY BASIC STYLE STRINGS _ (Stands for Specific Left,Right function Type)
*/

void _leftstr(char* , char* , int); // Left String
void _rightstr(char*, char* , int); // Right String
void _midstr(char*, char*, int, int); // Mid String
int  __instr(char*, char*); // InStr the _ String
void trim_null(char* buff,char*);
void lcase(char*);
void ucase(char*);
void replacestr(char* , char*, char* , char*);
void addreturn(char*);
void removestr(char* str, char* nstr, char* removestring); // Remove String

// the Lost String Algorithims to help ya

class LostString
{
public:
	char* myStr;

	void setstr(char* buff);
	void getstr(char* buff,char* ibuff);
	void addstr(char* buff);
	void clear();
	void operator=(char* buff);
	void operator+=(char* buff);
	void operator+=(int);// for the integers
	int  getlen();
	char* getstr();

	LostString();
	LostString(char*);
	~LostString();

	void qMsgBox(char* title);
	void qMsgBox();

	// copyto

	void CopyTo(LostString* lost);
	void CopyTo(char* buff);
	void AttachTo(LostString* lost);
	void AttachTo(char* buff);
	int  InString(char* buff);
	int  InStringBackward(char* buff);
	int  InStringFind(int start,int stop,char* search);
	int  InStringFindBackwards(int start,int stop,char* search);
	int  IntegerValue();
};

// LostString Manipluation

int ConvertStringToInt(char* string);


// assorted string algorithims

void leftstr(char* , char* , int);
void rightstr(char*, char* , int);
void midstr(char*, char*, int, int);
int  instr(char*, char*);
int  instrback(char*,char*);
int instrfind(char*,int start, int stop, char* search);
int instrbfind(char*, int start,int stop, char* search);
void removecomment(char* source, char* newsource);
void trimspace(char* s,char* ns);
void extractfunc(char* code, char* func);
void f_lbrace(char*,char*);
void fullbrace(char*,char*);
int firststatement(char*,char*);
void gethead(char*,char*);
void procfunc(char*);
void getelsehead(char* input, char* output);
void getopen(char* input, char* output);
void getcmd(char* code, char* curcmd);
void getstate(char* code, char* state);
void getstatehead(char* input, int open, char* output);
bool checkforclose(char* input, int open);
bool iffunc(char*);
bool isstrequal(char* i1, char* i2);
void trimcomment(char* input, char* output);
bool standardfunc(char* input);
bool chkifop(char* input);

void qbox(char*);
void qboxi(int);

//  compiler string algorithims
int  getfirstsyntax(char*,int pos);

char fixkeys(int key,int caps,bool cmd);