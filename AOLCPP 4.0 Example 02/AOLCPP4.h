// AOLCPP4  * America Online Manipulation  at its Best *
// written by Jared Bruni ( Master on LSD ) programmed in 2 1/2 days
// MasterOnLSD@LostSideDead.com

// NOTICE TERMS OF USE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// this source file is for no means, to be used for anything illegal
// it is stricly for programmers who used to write Visual Basic applications
// for AOL,to see the relationships between how C++ code works, and how vb code works
// if your A vb' AOL'er then this source code, is your dream
// questions comments, or whatever send me a mail

// IF you choose to use this in your own C++ program, all I ask is that
// in your programs greets you say whats up to me use my handle
// Master On LSD or just say Jared Bruni

// C++ owns :)

// sites to check out
// www.lostsidedead.com       - my web site
// www.lostsidedead.com/gameprog/ - my game programming site
// www.lostsidedead.com/aolcpp3/ - the old shity aolcpp3
// www.aolcpp.cjb.net - the shity aolcpp1 & aolcpp2,
// www.planetsourcecode.com - look up Jared Bruni for over 30,000 lines of C++ source
// that I have written !
/// GREETS: 
//  Micheal (LqDSyph0n)
//  Inc 
//  Source
//  and all you other l33tr0r c++ cod0rsz lol

// and everyone please remember to tell yewnix about her bloated ego :)

// notice AOL C++ Programmers,from now on go to private room AOLCPP 
// the vb rooms sux
// AOLCPP is a great resource when moving from Visual Basic to C++ !


#include <windows.h>
#include <string.h>
#include <fstream.h>
#include <iostream.h>
#include <ctime>

// enumerated constants 

enum AOLVER { NOAOL = 0, AOL2, AOL3, AOL4, AOL5, AOL6 };
enum AOLTYPE {ICON, LISTBOX, TREE, VIEW, RICHCNTL, STATIC,GLYPH, IMAGE, CHECKBOX};

// Important Functions
void cppDoEvents();
HWND FindWindowLike_Class(HWND Parent, char* Class); // Just Class
HWND FindWindowLike_Title(HWND Parent, char* Title); // Just Title
#define NOTFOUND -1
#define INULL    -1
#define NOPREV   -1
#define NULLI    -1
#define STRBEGIN -1
#define MRANGE_HI 1
#define MRANGE_LO 0
#define NULLPOS  -1

// string algorithims
void stringcopy(char* dest,char* from); // string copy
void stringattach(char* dest,char* from); // string attach
void leftcopy(char* from,char* dest,int pos);// left copy (leftstr)
void rightcopy(char* from,char* dest,int pos);// right copy (rightstr)
void midcopy(char* from,char* dest,int start_pos,int stop_pos);// middle copy (midstr)
void trimspace(char* buff);// trim space characters
int findstr(char* buffer,char* search);// find string search
int ifindstr(int i,char* buffer,char* search);// find string search from position
int findstrb(char* buffer,char* search); // backwards search
int ifindstrb(int i,char* buffer,char* search); // inside backwards search
int fsearchstr(int start,int stop,char* buff,char* search);// fully controled range search (forward)
int bsearchstr(int start,int stop,char* buff,char* search);// fully controled range search (backward)
void removestr(char* buff,char* str);// remove instances of str in buff
int getlen(char* buff);// get length of the string
void lcase(char* buff);// lower case string
void ucase(char* buff);// upper case string
int  lcasel(int c);// lower case letter
int  ucasel(int c);// upper case letter
int  findoccurance(char* buff,char* search);// find occourances of a specific string
void convertinteger(int integer,char* buff,int base); // convert integer to string
int  convertstring(char* buff); // convert string to integer
bool ishexc(char c);// is this character a hexidecimal digit?
bool ishex(char* buff);// is this string a hexidecimal value?
int  hextointc(char c);// hexidecimal digit to integer value
int  hextoint(char* buff); // hexidecimal digits to integer value
int findoccourance(char* buff,char* search);// find the numeric of times a string occours
void tripcharup(char* buff,int upby);// bump the digits up X times
void tripchardown(char* buff,int downby);// dump the digits down  X times
void replacechar(char* string,char findchr,char replace);// replace single character, through out all instances
void replacestr(char* string,char* findstr,char* rep,char* output);// replace string inside string
void rmvinst(char* buff,char* findstr,char* replace,char* output); // remove single instance of string
char randomchar(int max);// produce a random character
char randomchar(int max,int up);// produce a random character, and then make it + up
void randomstr(char* buff,int char_max,int char_size);// random string
void removechar(char* input,char* output,char c); // remove characters from buffer
int  findchar(char* str,char c);// find single char (forward)
int  ifindchar(int start,char* str,char c); // inside find single char (forward)
int  findcharb(char* str,char c);// find single char (backward)
int  ifindcharb(int start,char* str,char c); // find single char backward ex
int  findcharcf(char* str,int start,int stop,char c);// find single char controled forward
int  findcharcb(char* str,int start,int stop,char c);// find single char controled backward
void removestr(char* input,char* output,char* string); // remove instance of string
void rmvstrx(char* buff,char* output,char* string); // remove single instance of string
void strsavefile(char* filename,char* string);// save the string as a text file
int  getfilestringlength(char* filename);// get the string length of a text file
bool strloadfile(char* filename,char* output);// load a string from a text file
void reversestring(char* input,char* output); // reverse sring
bool isstrvalid(char* string); // checks to see if the string is valid or not (is null terminated)
// string compares
bool mstrcmp(char* buff1,char* buff2); // case sensitive compare
bool mstrcmpx(char* buff1,char* buff2);// not case sensitive compare
bool insidestr(char* buff1,char* buff2); // am i inside this string?
bool insidestrx(char* buff1,char* buff2);// am i inside this string lowercased ?
void strsep(char* str, char* sleft, int go_left, char* sright, int go_right);// seperate into 2 seperate strings from 2 seperate points
void strsetnull(char* str,int pos); // reset the 0's position
void rmvnullset(char* str); // remove the 0 to end the string
int  getnullpos(char* str); // get the position of the null
void trimcom(char* buff, char* output, char startstr,char stopstr); 
void asmtrim(char* input,char* output);
int  countlines(char* buffer); // counts how many \n characters exisit
int  getfirstletter(char* buffer); // get first letter thats not a space

// static

static char g_sn[200];
static char g_msg[200];

// the structures


// api helper structure
struct APIHELP
{
	// Click a Window
	inline void Click(HWND hwnd)
	{
		SendMessage(hwnd,WM_LBUTTONDOWN,0,0);
		SendMessage(hwnd,WM_LBUTTONUP,0,0);
	}
	// Double Click a Window
	inline void DoubleClick(HWND hwnd)
	{
		SendMessage(hwnd,WM_LBUTTONDBLCLK,0,0);
	}
	// Send a KeyDown to a Window
	inline void KeyDown(HWND hwnd,char c)
	{
		SendMessage(hwnd,WM_KEYDOWN,c,0);
	}
	// Send a Key Up to a Window
	inline void KeyUp(HWND hwnd,char c)
	{
		SendMessage(hwnd,WM_KEYUP,c,0);
	}
	// Send a Key Press to a Window
	inline void KeyPress(HWND hwnd,char c)
	{
		KeyDown(hwnd,c);
		KeyUp(hwnd,c);
	}
	// Send a Close Message to a window
	inline void Close(HWND hwnd)
	{
		SendMessage(hwnd,WM_CLOSE,0,0);
	}
	// Send a SetText Message to a window
	inline void SetText(HWND hwnd,char* buff)
	{
		SendMessage(hwnd,WM_SETTEXT,strlen(buff),(LPARAM)(LPCSTR)buff);
	}
	// Send a GetText Message to a Window
	inline void GetText(HWND hwnd,char* buff)
	{
		int len;
		len = SendMessage(hwnd,WM_GETTEXTLENGTH,0,0);
		SendMessage(hwnd,WM_GETTEXT,len+1,(LPARAM)(LPCSTR)buff);
	}
	// Send a Get List Item message to a list box
	inline void GetListText(HWND hwnd,int index,char* buff)
	{
		SendMessage(hwnd,LB_GETTEXT,index,(LPARAM)(LPCSTR)buff);
	}
	// Send a Get list Count message
	inline int  GetListCount(HWND hwnd)
	{
		return SendMessage(hwnd,LB_GETCOUNT,0,0);
	}
	// Send a Get List Current Sel message
	inline int  GetListCurSel(HWND hwnd)
	{
		return SendMessage(hwnd,LB_GETCURSEL,0,0);
	}
	// Send a Get List Cur Sel Message
	inline void SetListCurSel(HWND hwnd, int x)
	{
		SendMessage(hwnd,LB_SETCURSEL,x,0);
	}
	// Send a Add Item to List Box Message
	inline void  AddList(HWND hwnd,char* buff)
	{
		SendMessage(hwnd,LB_ADDSTRING,strlen(buff),(LPARAM)(LPCSTR)buff);
	}
	// Send a Rmv Item From listBox Message
	inline void RmvList(HWND hwnd,int x)
	{
		SendMessage(hwnd,LB_DELETESTRING,x,0);
	}
	// pause the application (doesnt freeze) :)
	inline void Pause(double breaktime)
	{
		double wTime = time(NULL) + breaktime;
        while (time(NULL) <= wTime){ cppDoEvents(); }
	}
	// click a button
	inline void ButtonClick(HWND hwnd)
	{
     SendMessage(hwnd, WM_KEYDOWN, VK_SPACE, NULL);
     SendMessage(hwnd, WM_KEYUP, VK_SPACE, NULL);
	}
	// for this window to appear
	inline void WaitForWindow(char* window_class,char* window_title)
	{
		while(FindWindow(window_class,window_title) == 0)
		{
			cppDoEvents();
		}
	}
	// wait for this window to appear ex
	inline void WaitForWindowEx(HWND hwnd,HWND hwnd2,LPCSTR l1,LPCSTR l2)
	{
		while(FindWindowEx(hwnd,hwnd2,l1,l2) == 0)
		{
			cppDoEvents();
		}
	}
	// wait for a window like this to appear
	inline void WaitForWindowLike_Title(HWND parent,char* title)
	{
		while(FindWindowLike_Title(parent,title) == 0)
		{
			cppDoEvents();
		}
	}
	// wait for a window like this to appear
	inline void WaitForWindowLike_Class(HWND parent,char* winclass)
	{
		while(FindWindowLike_Class(parent,winclass) == 0)
		{
			cppDoEvents();
		}
	}
	// compare to windows, are they the same ?
	inline bool WindowCompare(HWND hwnd,HWND hwnd2)
	{
		if(hwnd == hwnd2)
		{
			return true;
		}

		return false;
	}
	// is this window handle valid?
	inline bool isValidHandle(HWND hwnd)
	{
		if(hwnd == 0)
		{
			return false;
		}

		return true;
	}
	// Show this window
	inline void ShowWin(HWND hwnd)
	{
		ShowWindow(hwnd,SW_SHOW);
	}
	// Hide this Window
	inline void HideWin(HWND hwnd)
	{
		ShowWindow(hwnd,SW_HIDE);
	}
	// Minimize this Window
	inline void MiniWin(HWND hwnd)
	{
		ShowWindow(hwnd,SW_MINIMIZE);
	}
	// Maximize this Window
	inline void MaxWin(HWND hwnd)
	{
		ShowWindow(hwnd,SW_MAXIMIZE);
	}
	// restore this window
	inline void RestoreWin(HWND hwnd)
	{
		ShowWindow(hwnd,SW_RESTORE);
	}
	// send a menu command
	inline void SendMenuCommand(HWND hwnd,int cmd)
	{
		
		SendMessage(hwnd,WM_COMMAND,cmd,NULL);
	}
};


// the AOLCPP base object
struct AOLCPPOBJ : APIHELP
{
	// Find AOL Window Handle
	inline HWND FindAOL()
	{
		return FindWindow("AOL Frame25",NULL);
	}
	// Find the AOL MDI Handle
	inline HWND FindMDI()
	{
		return FindWindowEx(FindAOL(),0,"MDIClient",NULL);
	}
	// Get the users Screen Name
	inline void GetScreenName(char* buff)
	{
		if(FindAOL() == 0)
		{
			strcpy(buff,"AOL Not Found");
			return;
		}

		HWND welw;
		welw = FindWindowLike_Title(FindMDI(),"Welcome,");

		if(welw == 0)
		{
			strcpy(buff,"Not signed On");
			return;
		}

		char temp[50];
		SendMessage(welw,WM_GETTEXT,50,(LPARAM)(LPCSTR)temp);
		int fc = findstr(temp,",");
		int fi = findstr(temp,"!");
		midcopy(temp,buff,fc+2,fi);
		
	}
	// Get The Version of AOL They are running
	inline AOLVER GetAOLVersion()
	{
		if(isAOLOpen() == false)
		{
			return NOAOL;
		}

		HMENU mnu = GetAOLMenu();
		HMENU msub = GetSubMenu(mnu,NULL);
		int subi;
		subi = GetMenuItemID(msub,8);

		char stritem[100];
		GetMenuString(msub, subi, stritem, 100, 1);
		if(findstr(stritem,"&Logging...") != -1)
		{
			return AOL2;
		}
		if(findstr(stritem,"P&ersonal Filing Cabinet") != -1)
		{
			return AOL3;
		}

		msub = GetSubMenu(mnu,4);
		subi = GetMenuItemID(msub,9);
        GetMenuString(msub, subi, stritem, 100, 1);

		if(findstr(stritem,"4.0") != -1)
		{
			return AOL4;
		}
		if(findstr(stritem,"5.0") != -1)
		{
			return AOL5;
		}

		msub = GetSubMenu(mnu,5);
		subi = GetMenuItemID(msub,8);
		GetMenuString(msub, subi, stritem, 100, 1);

		if(findstr(stritem,"6.0") != -1)
		{
			return AOL6;
		}
	
		return NOAOL;
	}
	// Find a AOL Child Window
	inline HWND FindAOLChild(char* title)
	{
		return FindWindowEx(FindMDI(),0,"AOL Child",title);
	}
	// Find A AOL Child Window Like
	inline HWND FindAOLChildLike(char* title)
	{
		return FindWindowLike_Title(FindMDI(),title);
	}
	// Get The AOL Menu Handle
	inline HMENU GetAOLMenu()
	{
		return GetMenu(FindAOL());
	}
	// Close AOL
	inline void CloseAOL()
	{
		Close(FindAOL());
	}
	// is the user signed on ?
	inline bool SignedOn()
	{
		if(FindWindowLike_Title(FindMDI(),"Welcome,") == 0)
		{
			return false;
		}
		return true;
	}
	// is the user signed off ?
	inline bool SignedOff()
	{
		if(FindWindowLike_Title(FindMDI(),"Goodbye from") == 0)
		{
			return false;
		}
		return true;
	}
	// is AOL Open?
	inline bool isAOLOpen()
	{
		if(FindAOL())
		{
			return true;
		}

		return false;
	}
	// close all the children 
	inline void CloseAllChildren()
	{
		while(1)
		{
			HWND win;
			win = FindWindowEx(FindMDI(),0,"AOL Child",0);
			if(win == 0)
			{
				break;
			}
			else
			{
				Close(win);
			}
			cppDoEvents();
		}
	}
	// kill all the modal windows 
	inline void KillModal()
	{
		if(FindWindow("_AOL_Modal",NULL))
		{
			while(1)
			{
				HWND f;
				f = FindWindow("_AOL_Modal",NULL);
				if(f == 0)
				{
					break;
				}
				Close(f);

				cppDoEvents();
			}
		}
	}
	// kill all aol message boxs
	inline void KillAOLMessage()
	{

		HWND mod;
		mod = FindWindow("#32770", "America Online");
		if(mod == 0)
		{
			return;
		}
		while(1)
		{
			mod = FindWindow("#32770", "America Online");
			if(mod == 0)
			{
				break;
			}
			Close(mod);
			cppDoEvents();
		}

	}
	// special search for AOL Child Windows 
	inline HWND GetAolWindow(HWND parent, AOLTYPE aolchild, int num)
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
    // up chat
	inline void UpChat()
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
    // un up chat
	inline void UnUpChat()
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

	// send a wm_command, to aitem in the aol menu by id
	inline void AOLMenuInvokeByID(int id)
	{
		SendMenuCommand(FindAOL(),id);
	}
    // run a item, off the AOL menu 
	inline void RunMenu(int menu_over,int menu_down)
	{
		HMENU aolmenu;
        aolmenu = GetAOLMenu();
		HMENU sub;
        sub = GetSubMenu(aolmenu, menu_over);
        int sub2;
        sub2 = GetMenuItemID(sub, menu_down);
        SendMessage(FindAOL(), WM_COMMAND, sub2,NULL);
	}
	// set aol's caption
	inline void SetAOLCaption(char* buffer)
	{
		SetText(FindAOL(),buffer);
	}
	// get aol's caption
	inline void GetAOLCaption(char* buffer)
	{
		GetText(FindAOL(),buffer);
	}
	// get the chat window (ethier 3.0 or 4.0)
	inline HWND GetChatWindow()
	{
		
		HWND win;
		win = GetWindow(GetWindow(FindMDI(), GW_CHILD), GW_HWNDFIRST);
		
		
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
	// get the chat view (3.0 or 5.0)
	inline HWND GetChatView()
	{
		HWND Wnd;
		HWND chat;
		chat = GetChatWindow();
		Wnd  = FindWindowEx(chat,NULL, "_AOL_View",NULL);
		if(Wnd == 0) 
		{
			Wnd = FindWindowEx(chat,NULL, "RICHCNTL",NULL);
		}
		
		return Wnd;
	}
	// is user in a chat room?
	inline bool IsUserChatting()
	{
		if(GetChatWindow()) { return true; }

		return false;
	}

	// send text to ethier 3.0 or 4.0/5.0
	inline void SendText(char* str)
	{
		HWND chat;
		chat  =  GetChatWindow();
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
			rich = GetAolWindow(GetChatWindow(), RICHCNTL,2); 
			button = GetNextWindow(rich,2);
		}
		SendMessage(rich, WM_GETTEXT,300,(LPARAM)(LPCSTR) temp);
		SendMessage(rich, WM_SETTEXT,1, (LPARAM)(LPCSTR) a);
		SendMessage(rich, WM_SETTEXT,300, (LPARAM)(LPCSTR) str);
		SendMessage(rich, WM_CHAR ,  13, 0);
		
		SendMessage(rich, WM_GETTEXT,300,(LPARAM)(LPCSTR) text);
		while(strstr(text,str))
		{
			Click(button);
			SendMessage(rich, WM_GETTEXT,300,(LPARAM)(LPCSTR) text);
		}
		
		SendMessage(rich, WM_SETTEXT,300, (LPARAM)(LPCSTR) temp);

	}

	// get welcome window
	inline HWND GetWelcome()
	{
		return FindWindowLike_Title(FindMDI(),"Welcome,");
	}
	// get the buddy list window
	inline HWND GetBuddyList()
	{
		return FindWindowLike_Title(FindMDI(),"Buddy List");
	}

};


// the AOLCPP object for AOL 3.0
struct AOLCPP_3 : AOLCPPOBJ 
{
private:

	void (*ChatScan)(char* sn,char* msg);
	bool scan_set;
	int  pre_len;

public:

	// constructor
	inline AOLCPP_3()
	{
		scan_set = false;
		pre_len = -1;
	}

	inline ~AOLCPP_3()
	{

	}

	// is this aol3.0 ?
	inline bool isAOL30()
	{
		if(GetAOLVersion() == AOL3)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// get the tool bar
	inline HWND GetToolBar()
	{

		HWND aol,toolbar;
		aol=FindWindow("AOL Frame25",NULL);
		toolbar=FindWindowEx(aol,NULL,"AOL Toolbar",NULL);
		return toolbar;
 
		return 0;
	}
	// run the toolbar 0 being first icon, 1 being second etc
	inline void RunToolBar(int b_over)
	{ 
		HWND ico;
		ico = GetAolWindow(GetToolBar(),ICON,b_over);
		Click(ico);
	}
	// open the 3.0 email box
	inline void OpenEmailBox()
	{
		RunToolBar(1); // example of toolbar run
	}
	// open a new email
	inline void OpenNewEmail()
	{
		RunToolBar(2); // example of toolbar run
	}
	// send email 3.0
	inline void SendEmail(char* sn,char* subj,char* msg)
	{
		if(SignedOn() == false)
		{
			return;
		}

		OpenNewEmail();
		WaitForWindowLike_Title(FindMDI(),"Compose Mail");
		HWND mail;
		mail = FindWindowLike_Title(FindMDI(),"Compose Mail");
		HWND ed;
		ed = FindWindowEx(mail,0,"_AOL_Edit",0);
		SetText(ed,sn);
		HWND sub;
		sub = FindWindowEx(mail,0,0,"Subject:");
		sub = GetNextWindow(sub,2);
		SetText(sub,subj);
		HWND rich;
		rich = FindWindowEx(mail,0,"RICHCNTL",0);
		SetText(rich,msg);
		HWND ico;
		ico = FindWindowEx(mail,0,"_AOL_Icon",0);
		Click(ico);
	}
	// send instant message
	inline void SendInstantMessage(char* sn,char* msg)
	{
		if(SignedOn() == false)
		{
			return;
		}

		RunMenu(4,6);
		WaitForWindowLike_Title(FindMDI(),"Send Instant Message");
		HWND imwin;
		imwin = FindWindowLike_Title(FindMDI(),"Send Instant Message");
		HWND ed;
		ed = FindWindowEx(imwin,0,"_AOL_Edit",0);
		SetText(ed,sn);
		HWND rich;
		rich = FindWindowEx(imwin,0,"RICHCNTL",0);
		SetText(rich,msg);
		HWND ico;
		ico = GetNextWindow(rich,2);
		Click(ico);

		while(true)
		{
			HWND eim;
			HWND emsg;
			eim = FindWindowLike_Title(FindMDI(),"Send Instant Message");
			if(eim == 0)
			{
				break;
			}
			emsg = FindWindow(NULL,"America Online");
			if(emsg)
			{
				Close(emsg);
				Close(eim);
				break;
			}

			cppDoEvents(); // so are program wont lock up
		}
	}

	// run the keyword
	inline void AolKeyword(char* word)
	{
		if(SignedOn() == false)
		{
			return; // they anit signed on
		}

		RunMenu(2,5);
		WaitForWindowLike_Title(FindMDI(),"Keyword");
		HWND kw;
		kw = FindWindowLike_Title(FindMDI(),"Keyword");
		HWND ed;
		ed = FindWindowEx(kw,0,"_AOL_Edit",0);
		SetText(ed,word);
		SendMessage(ed,WM_CHAR,13,0);
		KeyPress(ed,13);
	}
	// Set The Chat Com Scan CallBack Function
    inline void SetChatComScan(void (*ChatScanX)(char* sn,char* msg))
	{
		ChatScan = ChatScanX;
		scan_set = true;
	}
//  Scan the chat
	inline void ChatComScan()
	{
			if(scan_set == true)
			{
			if(GetChatWindow())
			{


			int tlen;
			tlen = SendMessage(GetChatView(),WM_GETTEXTLENGTH,0,0);

			if(pre_len == -1)
			{
				pre_len = tlen;
				return; // first chat get
			}

			if(tlen == pre_len) // value is the same
			{
				return;
			}

			char chatbuff[5000];
			SendMessage(GetChatView(),WM_GETTEXT,tlen+1,(LPARAM)(LPCSTR)chatbuff);
			char newline[500];

			int copy_pos = pre_len;


			for(int i = tlen; i > 0; i--)
			{
				
				if(chatbuff[i] == 13)
				{
					copy_pos = i+1;
					break;
				}

			}
		
			rightcopy(chatbuff,newline,copy_pos);
			pre_len = tlen;

			char msn[100];
			char mmsg[200];
			int fcol;
			fcol = findstr(newline,":");
			leftcopy(newline,msn,fcol);
			rightcopy(newline,mmsg,fcol+3);
			ChatScan(msn,mmsg); // call users call back function

			}
		}
	}

};

// the AOLCPP object for 4.0/5.0
typedef struct AOLCPP_4 : AOLCPPOBJ
{
private:
	void (* ChatScan)(char* sn,char* msg);
	bool scan_set;
	int  pre_len;

public:

	// constructor
	inline AOLCPP_4()
	{
		scan_set = false;
		pre_len = -1;
	}

	// deconstructor
	inline ~AOLCPP_4()
	{

	}

    // get 4.0 toolbar
	inline HWND GetToolBar()
	{
		HWND tool;
		tool = FindWindowEx(FindAOL(),0,"AOL Toolbar",0);
		HWND Tool;
		Tool = FindWindowEx(tool,0,"_AOL_Toolbar",0);
		return Tool;
	}
	// run a icon in the toolbar
	inline void RunToolBar(int tool_over)
	{
		HWND tool;
		tool = GetToolBar();
		HWND ico;
		ico = GetAolWindow(tool,ICON,tool_over);
		Click(ico);
	}
	// Open there Email Box
	inline void OpenEmailBox()
	{
		RunToolBar(1);
	}

	// Open up a new Send Email
	inline void OpenNewEmail()
	{
		RunToolBar(2);
	}

	// is there email Box open ?
	inline bool isMailOpen()
	{
		HWND mb;
		mb = FindWindowLike_Title(FindMDI(),"Online MailBox");
		if(mb == 0)
		{
			return false;
		}

		return true;
	}
	// send email 4.0/5.0
	inline void SendEmail(char* sn,char* subj,char* msg)
	{
		if(SignedOn() == false)
		{
			return; // no signed on
		}

		OpenNewEmail();
		WaitForWindowLike_Title(FindMDI(),"Write Mail");
		HWND mail;
		mail = FindWindowLike_Title(FindMDI(),"Write Mail");
		HWND ed;
		ed = FindWindowEx(mail,0,"_AOL_Edit",0);
		SetText(ed,sn);
		HWND ed2;
		ed2 = GetNextWindow(ed,2);
		ed2 = GetNextWindow(ed2,2);
		ed2 = GetNextWindow(ed2,2);
		ed2 = GetNextWindow(ed2,2);
		SetText(ed2,subj);
		HWND ri;
		ri = FindWindowEx(mail,0,"RICHCNTL",0);
		SetText(ri,msg);
		HWND ico;
		ico = GetAolWindow(mail,ICON,16);
		Click(ico);

	}

	// keyword
	inline void AolKeyword(char* buff)
	{
		if(SignedOn() == false)
		{
			return; // there signed off
		}
		HWND kw;
		kw = FindWindowEx(GetToolBar(),0,"_AOL_ComboBox",0);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		kw = GetNextWindow(kw,2);
		Click(kw);
		WaitForWindowLike_Title(FindMDI(),"Keyword");
		HWND kww;
		kww = FindWindowLike_Title(FindMDI(),"Keyword");
		HWND ed;
		ed = FindWindowEx(kww,0,"_AOL_Edit",0);
		SetText(ed,buff);
		HWND ico;
		ico = FindWindowEx(kww,0,"_AOL_Icon",0);
		Click(ico);
	}
// get chat room text 4.0/5.0
	inline void GetChatText(char* buff)
	{
		HWND view = GetChatView();
		int len;
		len = SendMessage(view,WM_GETTEXTLENGTH,0,0);
		SendMessage(view,WM_GETTEXT,len,(LPARAM)(LPCSTR)buff);
	}

	// scan if the callback function is set
	inline void ChatComScan()
	{
		if(scan_set == true)
		{
			if(GetChatWindow())
			{


			int tlen;
			tlen = SendMessage(GetChatView(),WM_GETTEXTLENGTH,0,0);

			if(pre_len == -1)
			{
				pre_len = tlen;
				return; // first chat get
			}

			if(tlen == pre_len) // value is the same
			{
				return;
			}

			char chatbuff[5000];
			SendMessage(GetChatView(),WM_GETTEXT,tlen+1,(LPARAM)(LPCSTR)chatbuff);
			char newline[500];

			int copy_pos = pre_len;


			for(int i = tlen; i > 0; i--)
			{
				
				if(chatbuff[i] == 13)
				{
					copy_pos = i+1;
					break;
				}

			}
		
			rightcopy(chatbuff,newline,copy_pos);
			pre_len = tlen;

			char msn[100];
			char mmsg[200];
			int fcol;
			fcol = findstr(newline,":");
			leftcopy(newline,msn,fcol);
			rightcopy(newline,mmsg,fcol+3);
			ChatScan(msn,mmsg); // call users call back function

			}
		}
	}
	// initlize the callback function for a chat scan
	inline void SetChatComScan( void (*ChatScanX)(char* sn, char* msg))
	{
		ChatScan = ChatScanX;
		scan_set = true;
	}
	// get mail box
	inline HWND GetMailBox()
	{
		return FindWindowLike_Title(FindMDI(),"Online MailBox");
	}

	// dump aol mail box to a hwnd
	inline void GetAOLMailBox(HWND hwnd)
	{
		HWND mail;
		mail = GetMailBox();
		HWND mail_tree;
		mail_tree = FindWindowEx(mail,0,"_AOL_Tree",0);

		int l_len;
		l_len = SendMessage(mail_tree,LB_GETCOUNT,0,0);
		for(int i = 0; i < l_len; i++)
		{
			char curitem[200];
			SendMessage(mail_tree,LB_GETTEXT,200,(LPARAM)(LPCSTR)curitem);
			SendMessage(hwnd,LB_ADDSTRING,200,(LPARAM)(LPCSTR)curitem);
		}
		
	}

	// send a aol 4.0 instant message
	inline void SendInstantMessage(char* sn,char* msg)
	{
		HWND buddylist;
		buddylist = GetBuddyList();
		if(buddylist == 0)
		{
			return; // no buddy list found :(
		}

		HWND iim;
		iim = FindWindowEx(buddylist,0,0,"IM");
		iim = GetNextWindow(iim,2);
		Click(iim);

		WaitForWindowLike_Title(FindMDI(),"Send Instant Message");

		HWND im;
		im = FindWindowLike_Title(FindMDI(),"Send Instant Message");
		HWND ed;
		ed = FindWindowEx(im,0,"_AOL_Edit",0);
		SetText(ed,sn);
		HWND rich;
		rich = FindWindowEx(im,0,"RICHCNTL",0);
		SetText(rich,msg);
		HWND ico;
		ico = GetNextWindow(rich,2);
		Click(ico);

		while(true) // loop to see if stuff went succesfully
		{
			HWND eim;
			HWND emsg;
			eim = FindWindowLike_Title(FindMDI(),"Send Instant Message");

			if(eim == 0)
			{
				break;
			}

			emsg = FindWindow(NULL,"America Online");
			if(emsg)
			{
				Close(emsg); // error message
				Close(eim);
				break;
			}

			cppDoEvents(); // make sure are program dont lock up
		}


	}

	// turn ghosting on
	inline void GhostOn()
	{
		if(SignedOn() == false)
		{
			return; // there not signed on !
		}

		HWND bud;
		bud = GetBuddyList();
		if(bud == 0)
		{
			return; // they anit got no buddy list open 
		}
		HWND set;
		set = FindWindowEx(bud,0,0,"Setup");
		set = GetNextWindow(set,2);
		Click(set);
		WaitForWindowLike_Title(FindMDI(),"'s Buddy List");
		HWND budwin;
		budwin = FindWindowLike_Title(FindMDI(),"'s Buddy List");
		HWND ico;
		ico = GetAolWindow(budwin,ICON,5);
		Click(ico);
		WaitForWindowLike_Title(FindMDI(),"Privacy Pref");
		HWND pref;
		pref = FindWindowLike_Title(FindMDI(),"Privacy Pref");
		HWND chk;
		chk = FindWindowEx(pref,0,"_AOL_Checkbox",0);
		chk = GetNextWindow(chk,2);
		chk = GetNextWindow(chk,2);
		chk = GetNextWindow(chk,2);
		chk = GetNextWindow(chk,2);
		Click(chk);
		HWND icogo;
		icogo = FindWindowEx(pref,0,"_AOL_Edit",0);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		Click(icogo);
		Click(icogo);
		WaitForWindow(NULL,"America Online");
		HWND a;
		a = FindWindow(NULL,"America Online");
		Close(a);
		Close(budwin); // all done
	}
	// turn ghosting off
	inline void GhostOff()
	{
		if(SignedOn() == false)
		{
			return; // there not signed on !
		}

		if(SignedOn() == false)
		{
			return; // there not signed on !
		}

		HWND bud;
		bud = GetBuddyList();
		if(bud == 0)
		{
			return; // they anit got no buddy list open 
		}
		HWND set;
		set = FindWindowEx(bud,0,0,"Setup");
		set = GetNextWindow(set,2);
		Click(set);
		WaitForWindowLike_Title(FindMDI(),"'s Buddy List");
		HWND budwin;
		budwin = FindWindowLike_Title(FindMDI(),"'s Buddy List");
		HWND ico;
		ico = GetAolWindow(budwin,ICON,5);
		Click(ico);
		WaitForWindowLike_Title(FindMDI(),"Privacy Pref");
		HWND pref;
		pref = FindWindowLike_Title(FindMDI(),"Privacy Pref");
		HWND chk;
		chk = FindWindowEx(pref,0,"_AOL_Checkbox",0);
		Click(chk);
		HWND icogo;
		icogo = FindWindowEx(pref,0,"_AOL_Edit",0);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		icogo = GetNextWindow(icogo,2);
		Click(icogo);
		Click(icogo);
		WaitForWindow(NULL,"America Online");
		HWND a;
		a = FindWindow(NULL,"America Online");
		Close(a);
		Close(budwin); // all done

	}



}AOLCPP_5;



// ***********************************************************************************************
// *********************************** MasterString - Simple, and Explicit String Manipluation



// string data location structure use w/ (findstrl)
struct MasStrDataLoc
{
	int* dindex;
	int  array_size;
	char* thestring;
	char* searchstr;
	bool search_status;

	inline MasStrDataLoc()
	{
		search_status = false;
		dindex = 0;
		array_size = 0;
		searchstr = 0;
	}
	
	inline ~MasStrDataLoc()
	{
		if(dindex != 0)
		{

		delete [] dindex;
		dindex = 0;

		}
		if(thestring != 0)
		{

		delete [] thestring;
		thestring = 0;

		}
		if(searchstr != 0)
		{

		delete [] searchstr;
		searchstr = 0;

		}
	}

	inline void create_array(int size)
	{
		dindex = new int[size];
		array_size = size;
	}

	inline void setstr(char* buff)
	{
		int len;
		len = strlen(buff);
		thestring = new char[len+1];
		stringcopy(thestring,buff);
	}

	inline void setstatus(bool x)
	{
		search_status = x;
	}

	inline void setsearchstr(char* buff)
	{
		int len;
		len = strlen(buff);
		searchstr = new char[len+1];
		stringcopy(searchstr,buff);
	}

	// return pointer to the string which the array holds data for
	inline char* getstr()
	{
		return thestring;
	}

	inline char* getsearchstr()
	{
		return searchstr;
	}

	inline int getarraysize()
	{
		return array_size;
	}

	inline int getstringpoint(int index)
	{
		if(index <= array_size)
		{

		return dindex[index];

		}
	}
	// maximum string points for search
	inline int getmaxpoint()
	{
		return array_size;
	}
	// get status
	inline bool getstatus()
	{
		return search_status;
	}

	inline bool wassearchsuccesful()
	{
		return getstatus();// was it succesfull?
	}
};
// find string location (dumps all locations into the location data structure (MasStrDataLoc))
bool findstrloc(char* buff,char* search,MasStrDataLoc* dloc);// standard
bool findstrlocf(char* buff,char* search,MasStrDataLoc* dloc);// forward
bool findstrlocb(char* buff,char* search,MasStrDataLoc* dloc);// backward

// master string range structure
struct MasStrRange
{
	int start_x;
	int stop_y;

	inline MasStrRange()
	{
		start_x = 0;
		stop_y = 0;
	}

	inline void SetRange(int x, int y)
	{
		start_x = x;
		stop_y = y;
	}

	inline int GetRangeX()
	{
		return start_x;
	}

	inline int GetRangeY()
	{
		return stop_y;
	}

	inline int GetRangeHI()
	{
		return start_x;
	}

	inline int GetRangeLO()
	{
		return stop_y;
	}

	inline int Clear()
	{
		start_x = 0;
		stop_y = 0;
	}
};

// range search structures for range style string manipulation
bool searchrange(char* buff,char* search,MasStrRange* mrang);
void copyleftrange(char* input,char* output,MasStrRange* mrang, int hi_lo);
void copyrightrange(char* input,char* output,MasStrRange* mrang,int hi_lo);
void copymidrange(char* input,char* output,MasStrRange* mrang, int hi_lo,MasStrRange* mrangx, int hi_lox);
bool isearchrange(int startx, char* buff,char* search,MasStrRange* mrang);

// master string list structure string data
struct MasStrList_String
{
	char* thestring;

	inline ~MasStrList_String()
	{
		delete [] thestring;
	}

	inline void set(char* buff)
	{
		int len;
		len = strlen(buff) + 1;
		thestring = new char[len];
		stringcopy(thestring,buff);
	}

	inline char* get()
	{
		return thestring;
	}
};
// master string list , list handler structure
struct MasStrList
{
	MasStrList_String* strings;
	int list_size;

	inline ~MasStrList()
	{
		delete [] strings;
	}

	inline MasStrList(int list_size)
	{
		create(list_size);
	}

	inline MasStrList()
	{
		list_size = 0;
		strings = NULL;
	}

	inline void create(int list_sizez)
	{
		list_size = list_sizez;
		strings = new MasStrList_String[list_size];
	}

	inline char* getstr(int index)
	{
		return strings[index].get();
	}

	inline int getcount()
	{
		return list_size;
	}
};

// create string list
void createstrlist(char* buffer, char* list_marker,MasStrList* list);


// charwrap  easy to use char array, that automaticly removes itself from freestore
struct charwrap
{
	char* str;

	inline charwrap(int size)
	{
		str = new char[size];
	}

	inline charwrap(char* buff)
	{
		set(buff);
	}

	inline charwrap(char* buff,bool x)
	{
		set(buff);
		strclearn();
	}

	inline ~charwrap()
	{
		delete [] str; // delete that shit
	}

	inline void set(char* buff)
	{
		int len;
		len = strlen(buff) + 1;
		str = new char[len];
		stringcopy(str,buff);
	}

	inline void snew(int size)
	{
		str = new char[size];
	}

	// clear off freestore
	inline void clear()
	{
		delete [] str;
		str = NULL;
	}

	inline void strclear()
	{
		int len;
		len = getlen(str);

		for(int i = 0; i < len; i++)
		{
			str[i] = 0;
		}
	}

	inline void strclearn()
	{
		stringcopy(str,"");
	}

	inline char* get()
	{
		return str;
	}

	inline int len()
	{
		return getlen(str);
	}

	inline void qmsg()
	{
		MessageBox(0,str,"QMSG",MB_OK|MB_ICONINFORMATION);
	}

};

// structure of string manipulation algorithims to use for objects to inhert
struct MasStrObj
{
    inline void mstr_stringcopy(char* input,char* output)
	{
		stringcopy(input,output);
	}

	inline void mstr_stringattach(char* input,char* output)
	{
		stringattach(input,output);
	}

	inline void mstr_leftcopy(char* input,char* output,int pos)
	{
		leftcopy(input,output,pos);
	}

	inline void mstr_rightcopy(char* input,char* output,int pos)
	{
		rightcopy(input,output,pos);
	}

	inline void mstr_midcopy(char* input,char* output,int start_pos,int stop_pos)
	{
		midcopy(input,output,start_pos,stop_pos);
	}

	inline void mstr_trimspace(char* buff)
	{
		trimspace(buff);
	}

	inline int mstr_findstr(char* buffer,char* search)
	{
		return findstr(buffer,search);
	}

	inline int mstr_ifindstr(int i,char* buffer,char* search)
	{
		return ifindstr(i,buffer,search);
	}

	inline int mstr_findstrb(char* body,char* search)
	{
		return findstrb(body,search);
	}

	inline int mstr_ifindstrb(int startx,char* body,char* search)
	{
		return ifindstrb(startx,body,search);
	}

	inline int mstr_fsearchstr(int start,int stop,char* buff,char* search)
	{
		return fsearchstr(start,stop,buff,search);
	}

	inline int mstr_bsearchstr(int start,int stop,char* buff,char* search)
	{
		return bsearchstr(start,stop,buff,search);
	}

	inline int mstr_getlen(char* buff)
	{
		int len;
		len = strlen(buff);
		return len;
	}

	inline int mstr_lcase(char* buffer)
	{
		lcase(buffer);
	}

	inline int mstr_ucase(char* buffer)
	{
		ucase(buffer);
	}

	inline int mstr_ucasel(char c)
	{
		return ucasel(c);
	}

	inline int mstr_lcasel(char c)
	{
		return lcasel(c);
	}

	inline bool mstr_findstrloc(char* buff,char* search,MasStrDataLoc* dloc)
	{
		return findstrloc(buff,search,dloc);
	}

	inline bool mstr_findstrlocf(char* buff,char* search,MasStrDataLoc* dloc)
	{
		return findstrlocf(buff,search,dloc);
	}

	inline bool mstr_findstrlocb(char* buff,char* search,MasStrDataLoc* dloc)
	{
		return findstrlocb(buff,search,dloc);
	}

	inline bool mstr_searchrange(char* buff,char* search,MasStrRange* mrang)
	{
		return searchrange(buff,search,mrang);
	}

	inline bool mstr_isearchrange(int startx, char* buff,char* search,MasStrRange* mrang)
	{
		return isearchrange(startx,buff,search,mrang);
	}

	inline void mstr_copyleftrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
	{
		copyleftrange(input,output,mrang,hi_lo);
	}

	inline void mstr_copyrightrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
	{
		copyrightrange(input,output,mrang,hi_lo);
	}

	inline void mstr_copymidrange(char* input,char* output,MasStrRange* mrang,int hi_lo,MasStrRange* mrangx,int hi_lox)
	{
		copymidrange(input,output,mrang,hi_lo,mrangx,hi_lox);
	}

	inline int mstr_findoccourance(char* buffer,char* searchx)
	{
		return findoccourance(buffer,searchx);
	}

	inline void mstr_convertinteger(int integer,char* buff,int base)
	{
		convertinteger(integer,buff,base);
	}

	inline int mstr_convertstring(char* buff)
	{
		return convertstring(buff);
	}

	inline bool mstr_ishexc(char c)
	{
		return ishexc(c);
	}

	inline bool mstr_ishex(char* buff)
	{
		return ishex(buff);
	}

	inline int mstr_hextointc(char c)
	{
		return hextointc(c);
	}
	inline int mstr_hextoint(char* buff)
	{
		return hextoint(buff);
	}

	inline void mstr_tripchardown(char* buff,int by)
	{
		tripchardown(buff,by);
	}

	inline void mstr_tripcharup(char* buff, int by)
	{
		tripcharup(buff,by);
	}
	inline void mstr_replacechar(char* buff,char findchr,char replace)
	{
		replacechar(buff,findchr,replace);
	}
	inline void mstr_replacestr(char* buff,char* findstr,char* replacex,char* output)
	{
		replacestr(buff,findstr,replacex,output);
	}
	inline void mstr_rmvinst(char* buff,char* findchr,char* re,char* out)
	{
		rmvinst(buff,findchr,re,out);
	}

	inline char mstr_randomchar(int max)
	{
		return randomchar(max);
	}
	inline char mstr_randomchar(int max, int up)
	{
		return randomchar(max,up);
	}
	inline void mstr_randomstr(char* buff,int max, int size)
	{
		randomstr(buff,max,size);
	}
	inline void mstr_removechar(char* input,char* output,char c)
	{
		removechar(input,output,c);
	}
	inline char mstr_findchar(char* str,char c)
	{
		return findchar(str,c);
	}
	inline char mstr_ifindchar(int start,char* str,char c)
	{
		return ifindchar(start,str,c);
	}
	inline char mstr_findcharb(char* str,char c)
	{
		return findcharb(str,c);
	}
	inline char mstr_ifindcharb(int start,char* str,char c)
	{
		return ifindcharb(start,str,c);
	}
	inline char mstr_findcharcf(char* str,int start,int stop,char c)
	{
		return findcharcf(str,start,stop,c);
	}
	inline char mstr_findcharcb(char* str,int start,int stop,char c)
	{
		return findcharcb(str,start,stop,c);
	}
	inline void mstr_removestr(char* str,char* output,char* strsearch)
	{
		removestr(str,output,strsearch);
	}
	inline void mstr_removestrinstance(char* str,char* output,char* strx)
	{
		rmvstrx(str,output,strx);
	}
	inline void mstr_savestr(char* filename,char* string)
	{
		strsavefile(filename,string);
	}
	inline bool mstr_loadstr(char* filename,char* output)
	{
		return strloadfile(filename,output);
	}
	inline int  mstr_getfilestrlen(char* filename)
	{
		return getfilestringlength(filename);
	}
	inline int mstr_reversestr(char* str_input,char* str_output)
	{
		reversestring(str_input,str_output);
	}
	inline bool mstr_isstrvalid(char* str)
	{
		return isstrvalid(str);
	}
	inline bool mstr_mstrcmp(char* buff1,char* buff2)
	{
		return mstrcmp(buff1,buff2);
	}

	inline bool mstr_mstrcmpl(char* buff1,char* buff2)
	{
		return mstrcmpx(buff1,buff2);
	}

	inline bool mstr_insidestr(char* buff1,char* buff2)
	{
		return insidestr(buff1,buff2);
	}
	inline bool mstr_insidestrl(char* buff1,char* buff2)
	{
		return insidestrx(buff1,buff2);
	}
	inline void mstr_strsep(char* str,char* lstr,int lpos,char* rstr,int rpos)
	{
		strsep(str,lstr,lpos,rstr,rpos);
	}
	inline int mstr_getnullpos(char* str)
	{
		return getnullpos(str);
	}
	inline void mstr_rmvnullset(char* str)
	{
		rmvnullset(str);
	}
	inline void mstr_strsetnull(char* str,int pos)
	{
		strsetnull(str,pos);
	}
	inline void mstr_trimcom(char* input,char* output, char start_c,char stop_c)
	{
		trimcom(input,output,start_c,stop_c);
	}
	inline void mstr_asmtrim(char* input,char* output)
	{
		asmtrim(input,output);
	}
};

// the MasterString Object

struct MasterString : MasStrObj
{
	char* str;
	int array_size;
	bool str_on;

	/********** constructors & deconstructors ****************/
	inline MasterString()
	{
		str_on = false;
		array_size = 0;
		str = NULL;
	}

	inline MasterString(int size)
	{
		set(size,"");
	}

	inline MasterString(char* buff)
	{
		int size = strlen(buff) + 2;
		set(size,buff);
	}

	inline MasterString(int size,char* buff)
	{
		set(size,buff);
	}

	inline ~MasterString()
	{
		if(str_on)
		{
			delete [] str;
			str_on = false;

		}
	}

	/* internal functions **************************/
	inline void set(int size,char* buff)
	{
		if(str_on == false)
		{
			str = new char[size];
			str_on = true;
		}
		else
		{
			delete [] str;
			str = new char[size];
		}

		mstr_stringcopy(str,buff);
		array_size = size;
	}

	inline void add(char* buff)
	{
		int total_length = GetStringLength() + strlen(buff) + 2;

		if(total_length > GetStringLength())
		{
			char* ptemp;
			ptemp = new char[GetStringLength()+1];
			strcpy(ptemp,str);

			delete [] str;
			str = 0;// set pointer to 0 
			str = new char[total_length+2];
			strcpy(str,ptemp);
			delete [] ptemp;
			strcat(str,buff);
		}
		else
		{
			strcat(str,buff);
		}
	}

	inline void unset()
	{
		if(str_on == true)
		{
			delete [] str;
			str_on = false;
		}
	}

	inline char* get()
	{
		return str;
	}

	// operators *************************

	inline void operator=(char* buffer)
	{
		// set
		int len;
		len = strlen(buffer)+2;
		set(len,buffer);
	}

	inline void operator+=(char* buffer)
	{
		add(buffer);
	}
	inline void operator+=(int x)
	{
		char buffer[30];
		itoa(x,buffer,10);
		add(buffer);
	}

	inline void operator+=(long x)
	{
		char buffer[30];
		itoa(x,buffer,10);
		add(buffer);
	}

	// misc *********************************

	inline int GetStringLength()
	{
		return mstr_getlen(str);
	}

	inline char* GetCharPointer()
	{
		return str;
	}

	inline int FindChar(char c)
	{
		return mstr_findchar(str,c);
	}

	inline int FindCharEx(int pre_pos,char c)
	{
		return mstr_ifindchar(pre_pos,str,c);
	}
	inline int FindCharBackward(char c)
	{
		return mstr_findcharb(str,c);
	}
	inline int FindCharBackwardEx(int pre_pos,char c)
	{
		return mstr_ifindcharb(pre_pos,str,c);
	}
	inline int FindCharControledForward(int start,int stop,char c)
	{
		return mstr_findcharcf(str,start,stop,c);
	}
	inline int FindCharControledBackward(int start,int stop,char c)
	{
		return mstr_findcharcb(str,start,stop,c);
	}
	inline int FindString(char* search)
	{
		return mstr_findstr(str,search);
	}

	inline int FindStringEx(int index,char* search)
	{
		return mstr_ifindstr(index,str,search);
	}

	inline int FindStringBackward(char* search)
	{
		return mstr_findstrb(str,search);
	}
	inline int FindStringBackwardEx(int index,char* search)
	{
		return mstr_ifindstrb(index,str,search);
	}
	inline int FindOccourance(char* search)
	{
		return mstr_findoccourance(str,search);
	}
	inline void StringCopy(char* buff)
	{
		mstr_stringcopy(str,buff);
	}
	inline void StringAttach(char* buff)
	{
		mstr_stringattach(str,buff);
	}
	inline void StringResize(int newSize)
	{
		char* ptemp;
		ptemp = new char[strlen(str)+1];
		strcpy(ptemp,str);

		delete [] str;
		str = new char[newSize];
		strcpy(str,ptemp);
		delete [] ptemp;
	}
	inline void StringLeft(char* output,int pos)
	{
		mstr_leftcopy(str,output,pos);
	}
	inline void StringRight(char* output,int pos)
	{
		mstr_rightcopy(str,output,pos);
	}
	inline void StringMid(char* output,int x,int y)
	{
		mstr_midcopy(str,output,x,y);
	}
	inline void TrimSpace()
	{
		trimspace(str);
	}

	inline void UpperCase()
	{
		ucase(str);
	}
	inline void LowerCase()
	{
		lcase(str);
	}
	inline char ExtractChar(int index)
	{
		if(index <= GetStringLength())
		{
			return str[index];
		}
		return 0;
	}
	inline int ForwardStringSearch(int start,int stop,char* search)
	{
		return mstr_fsearchstr(start,stop,str,search);
	}

	inline int BackwardStringSearch(int start,int stop,char* search)
	{
		return mstr_bsearchstr(start,stop,str,search);
	}
	inline bool FindStringLocation(char* search,MasStrDataLoc* dloc)
	{
		return mstr_findstrloc(str,search,dloc);
	}
	inline bool FindStringLocationF(char* search,MasStrDataLoc* dloc)
	{
		return mstr_findstrlocf(str,search,dloc);
	}
	inline bool FindStringLocationB(char* search,MasStrDataLoc* dloc)
	{
		return mstr_findstrlocb(str,search,dloc);
	}
	inline void SearchRange(char* search,MasStrRange* mrang)
	{
		mstr_searchrange(str,search,mrang);
	}
	inline void SearchRangeEx(int startx,char* search,MasStrRange* mrang)
	{
		mstr_isearchrange(startx,str,search,mrang);
	}
	inline void CopyLeftRange(char* output, MasStrRange* mrang,int hi)
	{
		mstr_copyleftrange(str,output,mrang,hi);
	}
	inline void CopyRightRange(char* output, MasStrRange* mrang,int hi)
	{
		mstr_copyrightrange(str,output,mrang,hi);
	}
	inline void CopyMidRange(char* output,MasStrRange* mrang,int hi, MasStrRange* mrangx,int hix)
	{
		mstr_copymidrange(str,output,mrang,hi,mrangx,hix);
	}
	
	inline int GetHexValue()
	{
		return mstr_hextoint(str);
	}
	inline int GetDecValue()
	{
		return atoi(str);
	}
	inline int ConvertToInteger()
	{
		return atoi(str);
	}
	inline bool IsHex()
	{
		return mstr_ishex(str);
	}

	inline void qprint()
	{
		cout << str;
	}
	inline void qmsg()
	{
		MessageBox(0,str,"QMSG",MB_ICONINFORMATION);
	}
	inline void ClearString()
	{
		for(int z = 0; z < GetStringLength(); z++)
		{
			str[z] = 0;
		}
	}
	inline void SetWindowText(HWND hwnd)
	{
		SendMessage(hwnd,WM_SETTEXT,strlen(str),(LPARAM)(LPCSTR)str);
	}
	inline void AddToList(HWND hwnd)
	{
		SendMessage(hwnd,LB_ADDSTRING,strlen(str),(LPARAM)(LPCSTR)str);
	}
	inline void AddToCombo(HWND hwnd)
	{
		SendMessage(hwnd,CB_ADDSTRING,strlen(str),(LPARAM)(LPCSTR)str);
	}

	inline void CopyTextFromHWND(HWND hwnd)
	{
		char* buffer;
		int len;
		len = SendMessage(hwnd,WM_GETTEXTLENGTH,0,0);
		buffer = new char[len+1];
		SendMessage(hwnd,WM_GETTEXT,len,(LPARAM)(LPCSTR)buffer);
		
		set(len+1,buffer);

		delete [] buffer;
	}
	
	inline void AttachTextFromHWND(HWND hwnd)
	{
		char* buffer;
		int len;
		len = SendMessage(hwnd,WM_GETTEXTLENGTH,0,0);
		buffer = new char[len+1];
		SendMessage(hwnd,WM_GETTEXT,len,(LPARAM)(LPCSTR)buffer);
		
		add(buffer);

		delete [] buffer;
	}
	inline void ReplaceCharacter(char findchr,char replace)
	{
		mstr_replacechar(str,findchr,replace);
	}
	inline void RandomizeString()
	{
		randomstr(str,255,strlen(str));
	}
	inline void ReplaceString(char* search, char* replacestr)
	{
		if(mstr_findstr(str,search) != -1)
		{

		char* output;
		output = new char[strlen(str)+10];
		mstr_replacestr(str,search,replacestr,output);
		set(strlen(output)+10,output);
		delete [] output;
		output = 0;
		
		}
	}
	inline void RemoveCharacters(char c)
	{
		char* output;
		output = new char[strlen(str)+10];
		mstr_removechar(str,output,c);
		set(strlen(output)+10,output);
		delete [] output;
		output = 0;
	}
	inline void RemoveString(char* search)
	{
		if(mstr_findstr(str,search) != -1)
		{
			char* output;
			output = new char[strlen(str)+10];
			mstr_removestr(str,output,search);
			set(strlen(output)+10,output);
			delete [] output;
			output = 0;
		}
	}
	inline void RemoveSingleInstanceOfString(char* search)
	{
		if(mstr_findstr(str,search) != -1)
		{
			char* output;
			output = new char[strlen(str)+10];
			rmvstrx(str,output,search);
			set(strlen(output)+10,search);
			delete [] output;
			output = 0;
		}
	}
	inline void SaveToFile(char* filename)
	{
		mstr_savestr(filename,str);
	}
	inline void LoadStringFromFile(char* filename)
	{
		if(getfilestringlength(filename) == -1)
		{
			return; // failure file not found
		}

		char* temp;
		temp = new char[getfilestringlength(filename)+20];
		mstr_loadstr(filename,temp);
		set(strlen(temp)+20,temp);
		delete [] temp;
		temp = 0;
	}
	inline bool IsStringValid()
	{
		return mstr_isstrvalid(str);
	}

	inline int ReverseString() // reverse the string
	{
		char* temp;
		temp = new char[GetStringLength()+10];

		reversestring(str,temp);
		set(strlen(temp)+10,temp);

		delete [] temp;
		temp = 0;
	}

	inline bool StringCompare(char* buff)
	{
		return mstr_mstrcmp(str,buff);
	}
	inline bool StringCompare_NOCASE(char* buff)
	{
		return mstr_mstrcmpl(str,buff);
	}
	inline bool IsInsideString(char* buff)
	{
		return mstr_insidestr(str,buff);
	}
	inline bool IsInsideString_NOCASE(char* buff)
	{
		return mstr_insidestrl(str,buff);
	}
	inline void SeperateString(char* lbuff,int lpos,char* rbuff,int rpos)
	{
		mstr_strsep(str,lbuff,lpos,rbuff,rpos);
	}
	inline void AsmTrim()
	{
		// trim string as tho it were assembly language source
		char* output;
		output = new char[GetStringLength()+10];
		asmtrim(str,output);
		set(strlen(output)+10,output);
		delete [] output;
		output = 0;
	}

	inline void TrimComments(char start_c,char stop_c)
	{
		char* output;
		output = new char[GetStringLength()+10];
		trimcom(str,output,start_c,stop_c);
		set(strlen(output)+10,output);
		delete [] output;
		output = 0;
	}
};

// MasterString Item Structure 
struct ListItem
{
	int list_index;

	inline void setindex(int i)
	{
		list_index = i;
	}

	inline int getindex()
	{
		return list_index;
	}
};

struct MasterStringItem : MasterString,ListItem
{
	bool on;

	inline MasterStringListItem()
	{
		on = false;
	}

	inline void seton(bool x)
	{
		on = x;
	}

	inline bool geton()
	{
		return on;
	}
};

// example of a list using MasterStrings
struct MasterStringList 
{
	MasterStringItem* item;
	bool ion;
	int array_size;
	int off;

	inline MasterStringList()
	{
		ion = false;
		off = 0;
	}

	inline ~MasterStringList()
	{
		if(ion == true)
		{
			delete [] item;
			item = NULL;
		}
	}

	inline MasterStringList(int size)
	{
		createList(size);
	}
	
	inline void createList(int size)
	{
		item = new MasterStringItem[size];
		ion = true;
		array_size = size;
	}

	inline int  GetArraySize()
	{
		return array_size;
	}

	inline char* GetListStringPointerByIndex(int index)
	{
		return item[index].get();
	}

	inline int AddString(char* buffer)
	{
  		item[off].set(strlen(buffer)+10,buffer);
		int xoff = off;
		off++;
		return xoff;
	}

	inline int GetListLength()
	{
		return off;
	}

	inline void GetString(int index,char* output)
	{
		strcpy(output,item[index].get());
		
	}


	inline void Clear()
	{
		for(int i = 0; i < off; i++)
		{
			item[i].ClearString();
		}

		off = 0;
	}
};

struct MasterEntry : ListItem
{
	MasterString name;
	MasterString value;
	bool on_switch;

	inline MasterEntry()
	{
		name = "";
		value = "";
		on_switch = false;
	}

	inline bool amion()
	{
		return on_switch;
	}

};

// easy to use INI object, using MasterStrings
struct MasterINI
{
	MasterEntry* masEntry;
	bool mas_on;
	int array_size;
	int off_count;

	// constructors/deconstructors

	inline MasterINI()
	{
		masEntry = 0;
		mas_on = false;
		off_count = 0;
	}
	
	inline MasterINI(int size)
	{
		set(size);
	}

	inline ~MasterINI()
	{
		if(mas_on)
		{
			delete [] masEntry;
			masEntry = 0;
		}
	}

	inline set(int size)
	{
		if(mas_on == true)
		{
			delete [] masEntry;
			masEntry = 0;
		}

		masEntry = new MasterEntry[size];
		mas_on = true;
		array_size = size;
		off_count = 0;
	}

	inline int getsize()
	{
		return array_size;
	}

	inline void Create(int size)
	{
		set(size);
	}

	inline bool AddEntry(char* name,char* value)
	{
		if(off_count < getsize())
		{


		masEntry[off_count].name = name;
		masEntry[off_count].value = value;
		masEntry[off_count].list_index = off_count;

		off_count++;
		return true;
		}

		return false;
	}

	inline bool GetEntry(char* name,char* output_value)
	{
		for(int i = 0; i < getsize(); i++)
		{
			if(findstr(masEntry[i].name.get(),name) != -1)
			{
				stringcopy(output_value,masEntry[i].value.get());
				return true;
			}
		}

		strcpy(output_value,"*NULL*");
		return false;
	}
};

bool SaveMasterINI(char* filename,MasterINI* mini); // Save INI
bool LoadMasterINI(char* filename,MasterINI* mini); // Load INI

struct MasCharList // char list based on the \n (breaks strings into lines) (for use with MasAsm)
{
	MasterString* list;
	bool list_on;
	int array_size;
	int list_len;


	inline MasCharList()
	{
		list = 0;
		list_on = false;
	}

	inline MasCharList(char* buff)
	{
		BuildList(buff);
	}

	inline ~MasCharList()
	{
		if(list_on == true)
		{

		delete [] list;
		list = 0;

		}
	}

	inline void BuildList(char* buff)
	{
		int size;
		size = countlines(buff) + 1;
		list = new MasterString[size];
		list_on = true;
		array_size = size;
		// format the characters into this array
		int pre_pos = 0;
		int acount = 0;

		while(1)
		{
			int find_x;
			find_x = ifindstr(pre_pos,buff,"\n");
			
			if(find_x == -1)
			{
				break;// all done !
			}

			
			char* temp;
			temp = new char[strlen(buff)+1];

			midcopy(buff,temp,pre_pos,find_x);
			pre_pos = find_x;
		
			// add
			list[acount] = temp;
			acount++;
		

			delete [] temp;
			temp = 0;

		}

		list_len = acount;

	}

	inline int GetLength()
	{
		return list_len;
	}

	inline MasterString* GetMasterString(int index)
	{
		return (MasterString*)&list[index];
	}

};


static AOLCPP_4 aol4;// aolcpp4 object
static AOLCPP_3 aol3; // aol3 object
static APIHELP  apihlp; // static apihelp
static AOLCPPOBJ aolobj; // aol object
