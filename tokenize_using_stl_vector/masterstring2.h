/* MasterString2 
   string library

  written by Jared Bruni
  www.LostSideDead.com

  "Open  Source, Open Mind" 


  freestyle-> spin_it();
*/


#ifndef MASTERSTRING2
#define MASTERSTRING2



// optomized algorithms
// namespace for masterstring
namespace masterstring
{
	int i,z,j,len;
	bool check;
	unsigned int mstrlen(char* str);
	void mstrcpy(char* dest, char* source);
	void mstrcat(char* dest, char* source);
	void mstrleft(char* source,char* output,unsigned int pos);
	void mstrright(char* source,char* output, unsigned int pos);
	void mstrmid(char* source,char* output, unsigned int pos, unsigned int pos2);
	void mstrvbmid(char* source, char* output, unsigned int pos, unsigned int pos2);
	bool mstrcmp(char* string1,char* string2);
	void killspace(char* in, char* out);
	unsigned int mcharoccourance(char* source, char c);
	unsigned int mstrfind(char* source, char* string);
	unsigned int mstrifind(unsigned int start, char* source, char* string);
	unsigned int mstrbfind(char* source, char* string);
	unsigned int mstribfind(unsigned int start, char* source, char* string);

	/* tokenize class */

class Tokenize
{
	struct Token
	{
		char* str;
		Token()
		{
			str = NULL;
		}

		~Token()
		{
			if(str != NULL)
			{
				delete [] str;
				str = NULL;
			}

		}

		void set(char* xstr)
		{
			if(str != NULL)
			{
				delete [] str;
				str = NULL;
			}

			str = new char [ masterstring::mstrlen(xstr) + 1 ];
			masterstring::mstrcpy(str,xstr);
		}
	};

	Token* tokens;
	int off_pos;

	int tokencount(char* s, char c)
	{
		int amt = 0;

		for(unsigned int i = 0; i < masterstring::mstrlen(s); i++)
		{
			if(s[i] == c)
			{
				amt++;
			}
		}
	
		return amt;
	}


public:

	Tokenize()
	{
		tokens = NULL;
	}

	~Tokenize()
	{
		if(tokens != NULL)
		{
			delete [] tokens;
			tokens = NULL;
		}

	}
	int length;

	void tokenize(char* str, char sep)
	{
		off_pos = 0;
		length = 0;

		if(tokens != NULL)
		{
			delete [] tokens;
			tokens = NULL;
		}

		if(tokencount(str,sep) == 0)
		{
			return;
		}

		tokens = new Token[tokencount(str,sep) + 1 ];
	 
		for(unsigned int i = 0; i < masterstring::mstrlen(str); i++)
		{
			if(str[i] == sep)
			{
				char* temp = new char [ masterstring::mstrlen(str) + 1 ];
				masterstring::mstrmid(str,temp,off_pos,i);
				tokens[length].set(temp);
				length++;
				off_pos = i + 1;
				delete [] temp;
				temp = NULL;
			}
		}

		char* temp = new char [ masterstring::mstrlen(str) + 1 ];
		masterstring::mstrright(str,temp,off_pos);
		tokens[length].set(temp);
		length++;
		delete [] temp;
	}

	char* operator[](int pos)
	{
		if(pos >= 0 && pos < length)
		{
			return tokens[pos].str;
		}

		return NULL;
	}

};

	/* tokenize quotes class */

class TokenizeQuotes
{
	struct Token
	{
		char* str;
		Token()
		{
			str = NULL;
		}

		~Token()
		{
			if(str != NULL)
			{
				delete [] str;
				str = NULL;
			}

		}

		void set(char* xstr)
		{
			if(str != NULL)
			{
				delete [] str;
				str = NULL;
			}

			str = new char [ masterstring::mstrlen(xstr) + 1 ];
			masterstring::mstrcpy(str,xstr);
		}
	};

	Token* tokens;
	int off_pos;

	int tokencount(char* s, char c)
	{
		int amt = 0;
		bool go = true;

		for(unsigned int i = 0; i < masterstring::mstrlen(s); i++)
		{
			if(s[i] == '\"') 
			{
				go = !go;
			}


			if(s[i] == c && go == true)
			{
				amt++;
			}
		}
	
		return amt;
	}


public:

	TokenizeQuotes()
	{
		tokens = NULL;
	}

	~TokenizeQuotes()
	{
		if(tokens != NULL)
		{
			delete [] tokens;
			tokens = NULL;
		}

	}
	int length;

	void tokenize(char* str, char sep)
	{
		off_pos = 0;
		length = 0;

		if(tokens != NULL)
		{
			delete [] tokens;
			tokens = NULL;
		}

		if(tokencount(str,sep) == 0)
		{
			return;
		}

		tokens = new Token[tokencount(str,sep) + 1 ];
		bool go = true;

		for(unsigned int i = 0; i < masterstring::mstrlen(str); i++)
		{
			if(str[i] == '\"')
			{
				go = !go;
			}


			if(str[i] == sep && go == true)
			{
				char* temp = new char [ masterstring::mstrlen(str) + 1 ];
				masterstring::mstrmid(str,temp,off_pos,i);
				tokens[length].set(temp);
				length++;
				off_pos = i + 1;
				delete [] temp;
				temp = NULL;
			}
		}

		char* temp = new char [ masterstring::mstrlen(str) + 1 ];
		masterstring::mstrright(str,temp,off_pos);
		tokens[length].set(temp);
		length++;
		delete [] temp;
	}

	char* operator[](int pos)
	{
		if(pos >= 0 && pos < length)
		{
			return tokens[pos].str;
		}

		return NULL;
	}

};

}

/*************************  string algorithms **********************************************/

// mstrlen  - get string length
unsigned int masterstring::mstrlen(char* str)
{
    char* temp = str;
	i = 0;
	while( *temp++)
	{
		i++;
	}

	return i;
}
// mstrcpy - string copy
void masterstring::mstrcpy(char* dest,char* source)
{
	z =  mstrlen(source);
	for(i = 0; i < z; i++)
	{
		dest[i] = source[i];
	}
	dest[z] = 0;
}

// mstrcat - string concatination
void masterstring::mstrcat(char* dest,char* source)
{
	z = mstrlen(source);
	j = mstrlen(dest);
	for(i = 0; i < z; i++)
	{
 		dest[i+j] = source[i];
	}
	dest[j+z] = 0;

}

// mstrleft - left string copy 
void masterstring::mstrleft(char* source,char* output,unsigned int pos)
{
	for(i = 0; i < (int) pos; i++)
	{
		output[i] = source[i];
	}
	output[pos] = 0;
}

// mstrright - right string copy
void masterstring::mstrright(char* string,char* output, unsigned int pos)
{
	len = mstrlen(string);
    z = 0;
	for(i = pos; i < len; i++)
	{
    	output[z] = string[i];
		z++;
	}
	
	output[z] = 0;
}
// mstrmid - middle string copy
void masterstring::mstrmid(char* string,char* out, unsigned int start, unsigned int stop)
{
	z = 0;
	for(i = start; i < (int) stop; i++)
	{
		out[z] = string[i];
		z++;
	}
	out[z] =0;
}
// mstrvbmind - middle string copy vb style
void masterstring::mstrvbmid(char* source, char* output, unsigned int start, unsigned int length)
{
	z = 0;
	for(i = start; i < (int)start+(int)length; i++)
	{
		output[z] = source[i];
		z++;
	}
	output[z] = 0;	
}
// mstrcmp - string compare
bool masterstring::mstrcmp(char* string1,char* string2)
{
	len = mstrlen(string1);
	z = mstrlen(string2);
	if(len != z)
	{
		return false;
	}

	for(i = 0; i < len; i++)
	{
		if( string1[i] != string2[i] )
		{
			return false;
		}
	}
	return true;
}

// killspace - kill space from a string
void masterstring::killspace(char* in, char* out)
{
	j = mstrlen(in);
	z = 0;
	for(i = 0; i < j; i++)
	{
		if(in[i] != ' ')
		{

		out[z] = in[i];
		z++;

		}
	}
	out[z] = 0;
}

// mcharoccourance - find number of occourances of a char
unsigned int masterstring::mcharoccourance(char* source, char c)
{
	z = 0;
	j = mstrlen(source);
	for(i = 0; i < j; i++)
	{
		if(source[i] == c)
		{
			z++;
		}
	}

	return z;
}

// mstrfind - find a string within a string
unsigned int masterstring::mstrfind(char* source, char* string)
{
	j = mstrlen(source);
	len = mstrlen(string);
	for(i = 0; i < j; i++)
	{
		if(source[i] == string[0])
		{
			check = true;

			for(z = 0; z < len; z++)
			{
				if(source[i+z] != string[z])
				{
					check = false;
				}
			}

			if(check == true)
			{
				return i;
			}
		}
	}

	return -1; // fail
}

//mstrifind - master string start pos find
unsigned int masterstring::mstrifind(unsigned int start, char* source, char* string)
{
	j = mstrlen(source);
	len = mstrlen(string);
	for(i = start; i < j; i++)
	{
		if(source[i] == string[0])
		{
			check = true;

			for(z = 0; z < len; z++)
			{
				if(source[i+z] != string[z])
				{
					check = false;
				}
			}

			if(check == true)
			{
				return i;
			}
		}
	}

	return -1; // fail
}

// mstrbfind - string backwards find
unsigned int masterstring::mstrbfind(char* source, char* string)
{
	j = mstrlen(source);
	len = mstrlen(string);
	for(i = j; i >= 0; i--)
	{
		if(source[i] == string[0])
		{
			check = true;

			for(z = 0; z < len; z++)
			{
				if(source[i+z] != string[z])
				{
					check = false;
				}
			}

			if(check == true)
			{
				return i;
			}
		}
	}

	return -1; // fail
}

// mstribfind - string backwards position find
unsigned int masterstring::mstribfind(unsigned int start, char* source, char* string)
{
	j = mstrlen(source);
	len = mstrlen(string);
	for(i = start; i >= 0; i--)
	{
		if(source[i] == string[0])
		{
			check = true;

			for(z = 0; z < len; z++)
			{
				if(source[i+z] != string[z])
				{
					check = false;
				}
			}

			if(check == true)
			{
				return i;
			}
		}
	}

	return -1; // fail
}



#endif

// use a #define MASTERSTRING1
// before including the masterstring header
// to use masterstring 1 algorithms
#ifdef MASTERSTRING1
// masterstring - null terminated string manipulation 
// class hierarchy , as well as a large series of string related algorithims
// by jared bruni 
// my new string algorithims
// jared@lostsidedead.com

// some very important algorithims
// I totaly re-wrote all these from scratch
// so it would work better with the new masasm (my newest project)
// www.lostsidedead.com

// this source file is dedicated to my buds (hehe)


/************ Using MasterString ********************

  Within this source file consits of a series of
  algorithims and classes. You can inturn use these
  different aspects of the source to produce your
  own string classes, or to simply manipulate 
  char arrays. There are multiple levels of functionality
  as well as a few base classes for your classes to
  inhert from. This source is to be thought of as the
  layer ontop of string.h , allowing for simplicity
  as well as expanding the types of things it can do.

  The Functions**************************************

  All the simple functions with lowercased names, are
  the c-style functions. These allow you to pass a pointer
  to the character array, and manipulate it , in the way
  it describes (ex: findstr,stringcopy) etc these functions
  are very useful when directly manipulating character arrays
  and provide a much deeper form of control over the array.
  There are seires of different forms of string searches,
  which allow you to have full control. One of my favorite
  new ones which Im going to talk about here is findstrloc.
  findstrloc stands for find string location, its prototype is
  the following.

  void findstrloc(char* buff,char* search,MasStrDataLoc* dloc);

  This function cycles through the buffer, and every time it
  finds an instance of search, it leaves a refrence to it
  inside the MasStrDataLoc structure. Pretty nifty, but
  there are other ways to be able to cycle through all the
  characters, with very explicit searchs.

  findstr
  ifindstr
  findstrb
  ifindstrb

  etc

  These forms of searching for strings within your strings are
  extermly useful. They allow you to start off at the begining
  and then continue searching were you left off at. Allows you
  to search forward, backward, and even within a range of those
  two points. findstrcf (find string cycle forward) and findstrcb 
  (find string cycle backward). There are also a seires of functions
  that directly manipulate with ranges. These searchs, return a structure
  (MasStrRange) which contains two points. One for the starting location
  of the sub string, and one for were it stops. Pretty nifty when needing
  to have a full detailed structure of were things are at, to make
  the whole manipulation proccess easy. 


  The Classes / Structures *************************

  The next layer ontop of these functions, is the
  MasStrObj. This is a object, to use as a base
  object to inhert into your string classes, or
  whatever other class would need the structure
  of these functions.

  MasterString object

  The master string object, is a String class, which rather
  then attempting to just encapsulate all the string functionality
  it instead, trys to simplfy the proccess of using the object
  but still consist of the same amount of power. The MasterString
  inherts from MasStrObj, and then expands upon this to provide
  a autosizing string. It does this by creating a pointer to memory
  on the freestore, and then freeing that memory at appropriate times.
  It also has another layer, were the methods which use a form
  of hungarin notation (FindWindow LikeThis) automaticly point to the
  string within the Object. Let me give a example of this.

  theres the function findstr, and then the method within the
  MasterString object, FindString

  the following would be how you would call it

  char string1[100];
  stringcopy(string1, "stuff is x here");
  int placeval;
  placeval = findstr(string1,"x");

  using the MasterString , its actualy quite simpler

  MasterString str("stuff is x here");
  int placeval;
  placeval = str.FindString("x");

  When using the MasterString object, it basicly lets you
  encapsulate what character array the low level functions
  are pointing to, while still allowing you the ability
  to directly call any of the other functions.

  MasterStringList ********************************

  The MasterStringList class , is pretty simple to grasp
  and use. Its simply a class which holds a list of
  MasterStrings :)
  This class incorperates multiple inheritance one of my
  favorite features of the C++ language

  MasterINI ***************************************

  The MasterINI class is also fairly simple. It is a
  object that is kinda like a INI file. You basicly
  put in strings, by there name, and what the value is
  for that name, and it can then be saved & loaded.
  Its really easy to use / work, just remember to always
  create your size, or its gonna trip! example:

  MasterINI mstr(100); // allows 100 entrys

  MasterINI mstrx; // has no size
  mstrx.Create(100);// now has the size of 100 entrys


  - Jared Bruni

  Master@LostSideDead.com -

****************************************************/


#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream.h>
#include <fstream.h>

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


// string copy
void stringcopy(char* input,char* output)
{
	strcpy(input,output);
}

// string attach
void stringattach(char* input,char* output)
{
	strcat(input,output);
}

// left copy
void leftcopy(char* input,char* output,int pos)
{
	int index = 0;
	for(int i = 0; i < pos; i++)
	{
		output[index] = input[i];
		index++;
	}
	output[index] = 0;
}
// right copy
void rightcopy(char* input,char* output,int pos)
{
	int index = 0;
	int len = strlen(input);
	for(int i = pos; i < len; i++)
	{
		output[index] = input[i];
		index++;
	}
	output[index] = 0;

}
// mid copy
void midcopy(char* input,char* output,int start_pos, int stop_pos)
{
	int index = 0;
	for(int i = start_pos; i < stop_pos; i++)
	{
		output[index] = input[i];
		index++;
	}

	output[index] = 0;
}

// trim the space
void trimspace(char* buffer)
{
	int len;
	len = strlen(buffer);
	char* ptemp;
	ptemp = new char[len+1];
	strcpy(ptemp,buffer);

	int index = 0;
	for(int z = 0; z < len; z++)
	{
		if(ptemp[z] != ' ')
		{
			buffer[index] = ptemp[z];
			index++;
		}
	}
	buffer[index] = 0;

	delete [] ptemp;
}

int findstr(char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search); // search len

	for(int i = 0; i < len; i++)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;

			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i;
			}
		}
	}

	return -1; // failure
}

int ifindstr(int startx,char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search); // search len

	for(int i = startx+1; i < len; i++)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;

			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i;
			}
		}
	}

	return -1; // failure
}

int findstrb(char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search);

	for(int i = len; i > 0; i--)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;
			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i; // found it
			}
		}

	}
	return -1; // failure
}
// find inside backwards string loop
int ifindstrb(int startx, char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search);

	for(int i = startx-1; i > 0; i--)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;
			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i; // found it
			}
		}

	}
	return -1; // failure
}
// forward search string (controled range) 
int fsearchstr(int start,int stop,char* buff,char* search)
{
	int len = strlen(buff);
	int len2 = strlen(search);

	for(int i = start; i < stop; i++)
	{
		if(buff[i] == search[0])
		{
			bool ichk = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
			  return i; // found it
			}
		}
	}

	return -1; // failure
}

// backward search string (controled range)
int bsearchstr(int start,int stop,char* buff,char* search)
{
	int len = strlen(buff);
	int len2 = strlen(search);

	for(int i = start; i > stop; i--)
	{
		if(buff[i] == search[0])
		{
			bool ichk = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i; // found it;
			}
		}
	}

	return -1;// failure
}
// getting length
int getlen(char* buff)
{
	return strlen(buff);// use strlen :)
}
// lower case
void lcase(char* buffer)
{
	int len = getlen(buffer);

	for(int i = 0; i < len; i++)
	{
		buffer[i] = tolower(buffer[i]);
	}
}
// upercase
void ucase(char* buffer)
{
	int len = getlen(buffer);

	for(int i = 0; i < len; i++)
	{
		buffer[i] = toupper(buffer[i]);
	}
}
// uppercase letter
int ucasel(char c)
{
	return tolower(c);
}

// lowercase letter
int lcasel(char c)
{
	return tolower(c);
}

// find string location algorithims
bool findstrloc(char* buff,char* search,MasStrDataLoc* dloc)
{
	int len = strlen(buff);
	int len2 = strlen(search);
	int* f;
	int  f_i = 0;
	f = new int[len+1];// big just in case

	for(int i = 0; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ic = true;
				
			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{

				}
				else
				{
					ic = false;
				}
			}

			if(ic == true)
			{
				f[f_i] = i;
				f_i++;
			}
		}
	}

	dloc->create_array(f_i);
	dloc->setstr(buff);
	dloc->setsearchstr(search);
	for(int p = 0; p < f_i; p++)
	{
		dloc->dindex[p] = f[p];
	}
	delete [] f;

	if(f_i != 0)
	{
		dloc->setstatus(true);
		return true; // we got some locations
	}
	else
	{
		dloc->setstatus(false); 
		return false; // not found
	}
}
// find string location forward search
bool findstrlocf(char* buff,char* search,MasStrDataLoc* dloc)
{
	return findstrloc(buff,search,dloc);
}
// find string location backwards search
bool findstrlocb(char* buff,char* search,MasStrDataLoc* dloc)
{
	int len = strlen(buff);
	int len2 = strlen(search);
	int* f;
	int  f_i = 0;
	f = new int[len+1];// big just in case

	for(int i = len; i > 0; i--)
	{
		if(buff[i] == search[0])
		{
			bool ic = true;
				
			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{

				}
				else
				{
					ic = false;
				}
			}

			if(ic == true)
			{
				f[f_i] = i;
				f_i++;
			}
		}
	}

	dloc->create_array(f_i);
	dloc->setstr(buff);
	dloc->setsearchstr(search);
	for(int p = 0; p < f_i; p++)
	{
		dloc->dindex[p] = f[p];
	}
	delete [] f;

	if(f_i != 0)
	{
		dloc->setstatus(true);
		return true; // we got some locations
	}
	else
	{
		dloc->setstatus(false);
		return false; // not found
	}
}

// string ( range based ) manipulation algorithims
bool searchrange(char* buff,char* search,MasStrRange* mrang)
{
	int len;
	int len2;
	len = strlen(buff);
	len2 = strlen(search);

	for(int i = 0; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ik = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ik = false;
				}
			}

			if(ik == true)
			{
				mrang->SetRange(i,i+len2);
				return true;
			}
		}
	}
	mrang->SetRange(0,0);
	return false;
}
// string range manipluation ex (i)
bool isearchrange(int startx, char* buff,char* search,MasStrRange* mrang)
{
	int len;
	int len2;
	len = strlen(buff);
	len2 = strlen(search);

	for(int i = startx+1; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ik = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ik = false;
				}
			}

			if(ik == true)
			{
				mrang->SetRange(i,i+len2);
				return true;
			}
		}
	}
	mrang->SetRange(0,0);
	return false;
}

// find the occourance amount of a specific string
int findoccourance(char* buff,char* search)
{
	int len;
	int len2;
	len = strlen(buff);
	len2 = strlen(search);

	int occ = 0;

	for(int i = 0; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ic = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ic = false;
				}
			}

			if(ic == true)
			{
				occ++;
			}

		}
	}

	if(occ == 0)
	{

	return -1; // failure

	}
	else
	{
		return occ;
	}
}

// string range manipulation copy left range
void copyleftrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
{
	if(hi_lo == MRANGE_HI)
	{
		leftcopy(input,output,mrang->GetRangeHI());
	}
	else
	{
		leftcopy(input,output,mrang->GetRangeLO());
	}
}
// string range manipulation copy right range
void copyrightrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
{
	if(hi_lo == MRANGE_HI)
	{
		rightcopy(input,output,mrang->GetRangeHI());
	}
	else
	{
		rightcopy(input,output,mrang->GetRangeLO());
	}
}
// string range manipulation mid copy
void copymidrange(char* input,char* output,MasStrRange* mrang, int hi_lo,MasStrRange* mrangx, int hi_lox)
{
	int cx;
	int cy;

	if(hi_lo == MRANGE_HI)
	{
		cx = mrang->GetRangeHI();
	}
	else
	{
		cx = mrang->GetRangeLO();
	}

	if(hi_lox == MRANGE_HI)
	{
		cy = mrangx->GetRangeHI();
	}
	else
	{
		cy =mrangx->GetRangeLO();
	}

	midcopy(input,output,cx,cy);
}

// create a list from string data
void createstrlist(char* buff,char* search,MasStrList* list)
{
	int occ;
	occ = findoccourance(buff,search);

	if(occ == -1)
	{
		return; // failure
	}
	list->create(occ);

	int occ_i = 0;

	MasStrDataLoc dloc;

	if(findstrloc(buff,search,&dloc))
	{
		int pre_pos = 0;

		for(int z = 0; z < dloc.getmaxpoint(); z++)
		{
			int cur = 0;
			cur = dloc.dindex[z];
			charwrap cwrap(buff);
			cwrap.strclearn();
			midcopy(buff,cwrap.get(),pre_pos,cur);
			list->strings[occ_i].set(cwrap.get());
			occ_i++;
			pre_pos = cur;
		}

		charwrap cwrapx(buff,true);
		rightcopy(buff,cwrapx.get(),pre_pos);
		list->strings[occ_i].set(cwrapx.get());
		occ_i++;
		}

	return;
}
// conversion of integers
void convertinteger(int integer,char* buff,int base)
{
	itoa(integer,buff,base);
}
// conversion of strings
int convertstring(char* buff)
{
	return atoi(buff);
}
// could this be a hexidecimal digit?
bool ishexc(char c)
{
	c = lcasel(c);
	switch(c)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
		return true;
		break;
	}
	return false;
}
// does this string contain a non-hexidecimal digit?
bool ishex(char* buff)
{
	int len;
	len = strlen(buff);

	for(int i = 0; i < len; i++)
	{
		if(ishexc(buff[i]) == false)
		{
			return false;
		}
	}
	return true;
}

// hexidecimal digit to integer value
int hextointc(char c)
{
	if(ishexc(c) == false)
	{
		return -1; // failure, not a hex digit
	}

	c = lcasel(c);

	switch(c)
	{
	case '0':
		return 0;
		break;
	case '1':
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
		break;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;
	case '7':
		return 7;
		break;
	case '8':
		return 8;
		break;
	case '9':
		return 9;
		break;
	case 'a':
		return 10;
		break;
	case 'b':
		return 11;
	case 'c':
		return 12;
	case 'd':
		return 13;
	case 'e':
		return 14;
	case 'f':
		return 15;
	}

	return -1; // failure ? never would get here
}

// convert hex value into a integer
int hextoint(char* buff)
{
	int rt = 0;

	if(buff[1] == 0)
	{
		return hextointc(buff[0]);
	}

	int len = strlen(buff);
	int* hexval;
	hexval = new int[len+1];
	int  hexvali = 0;

	for(int i = 0; i < len; i++)
	{
		hexval[hexvali] = hextointc(buff[i]);
		hexvali++;
	}

    int index = 0;

	for(int z = hexvali-1; z >= 0; z--)
	{
		int cur;
		if(index == 0)
		{
			cur = hexval[z];
			index = 16;
		}
		else
		{

		cur = hexval[z] * index;
		index = index * 16;
		}
		
		rt = rt + cur;
	}

	delete [] hexval;

	return rt;
} 


void tripcharup(char* buff, int up)
{
	int len;
	len = strlen(buff);

	for(int i = 0; i < len; i++)
	{
		if(buff[i] != 0)
		{

		buff[i] = buff[i] + up;

		}
	}
}

void tripchardown(char* buff,int up)
{
	int len;
	len = strlen(buff);

	for(int i = 0; i < len; i++)
	{
		if(buff[i] != 0)
		{

		buff[i] = buff[i] - up;

		}
	}
}
// replace single instance of a character
void replacechar(char* buff,char findchr,char replace)
{
	int len;
	len = strlen(buff);

	for(int z = 0; z < len; z++)
	{
		if(buff[z] == findchr)
		{
			buff[z] = replace;
		}
	}
}

void rmvinst(char* buff,char* findstr,char* replacex,char* output)
{

	int xt = ifindstr(NOPREV,buff,findstr);


	char* temp;
	temp = new char[strlen(buff)+1];
	stringcopy(temp,buff);

	char* ltemp;
	char* rtemp;

	ltemp = new char[strlen(buff)+1];
	rtemp = new char[strlen(buff)+1];

	leftcopy(buff,ltemp,xt);
	rightcopy(buff,rtemp,xt+strlen(findstr));


	cout << "\n#: " << ltemp << replacex << rtemp << endl;

	
	strcpy(output,ltemp);
	strcat(output,replacex);
	strcat(output,rtemp);

	delete [] temp;
	delete [] ltemp;
	delete [] rtemp;
}


// replace string
void replacestr(char* buff,char* findstr,char* replacex,char* output)
{
	int xt;
	xt = ifindstr(0,buff,findstr);

	if(xt == -1)
	{
		return; // failure no string to replace
	}

	char* ptemp;
	char* outtemp;
	ptemp = new char[strlen(buff) + 500];
	outtemp = new char[strlen(buff) + 500];
	stringcopy(ptemp,buff);

	while(1)
	{
		int xr;
		xr = ifindstr(0,ptemp,findstr);
		if(xr == -1)
		{
			break;
		}
		else
		{
			rmvinst(ptemp,findstr,replacex,outtemp);
			stringcopy(ptemp,outtemp);
		}
	}

	stringcopy(output,ptemp);

	delete [] ptemp;
	delete [] outtemp;

}

// random char
char randomchar(int max)
{
	int x;
	x = rand()%max;
	char c;
	c = x;
	return c;
}
// random char + up
char randomchar(int max,int up)
{
	int x;
	x = rand()%max+up;
	char c;
	c = x;
	return c;
}
// random string
void randomstr(char* buff,int max, int size)
{
	for(int i = 0; i < size; i++)
	{
		if(rand()%2)
		{
			buff[i] = randomchar(max);
		}
		else
		{
			buff[i] = randomchar(max,rand()%10);
		}
	}
}
// remove char
void removechar(char* in,char* out,char c)
{
	int len;
	len = strlen(in);
	int ic = 0;
	for(int i = 0; i < len; i++)
	{
		if(in[i] != c)
		{
			out[ic] = in[i];
			ic++;
		}
	}
	out[ic] = 0;
}

// find single character in string
int findchar(char* str,char c)
{
	int len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1; // failure
}
// find char ex (inside)
int ifindchar(int start,char* str,char c)
{
	int len = strlen(str);
	for(int i = start+1; i < len; i++)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1;
}
// find single char backward
int findcharb(char* str,char c)
{
	int len;
	len = strlen(str);
	for(int i = len; i > 0; i--)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1;
}
// find single char backward
int ifindcharb(int start,char* str,char c)
{
	int len;
	len = strlen(str);
	for(int i = start-1; i > 0; i--)
	{
		if(str[i] == c)
		{
			return i;
		}
	}
	return -1;
}

int  findcharcf(char* str,int start,int stop,char c)
{
	for(int i = start; i < stop; i++)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1; // failure
}
int  findcharcb(char* str,int start,int stop,char c)
{
	for(int i = stop; i > start; i--)
	{
		if(str[i] == c)
		{
			return i;
		}
	}
	return -1;// failure
}
// remove instances of string
void removestr(char* input,char* output,char* string)
{

	char* buff = input;
	char* findstr = string;

	int xt;
	xt = ifindstr(NULLPOS,buff,findstr);

	if(xt == -1)
	{
		return; // failure no string to replace
	}

	char* ptemp;
	char* outtemp;
	ptemp = new char[strlen(buff) + 500];
	outtemp = new char[strlen(buff) + 500];
	stringcopy(ptemp,buff);

	while(1)
	{
		int xr;
		xr = ifindstr(0,ptemp,findstr);
		if(xr == -1)
		{
			break;
		}
		else
		{
			rmvstrx(ptemp,findstr,outtemp);
			stringcopy(ptemp,outtemp);
		}
	}

	stringcopy(output,ptemp);

	delete [] ptemp;
	delete [] outtemp;

}

void rmvstrx(char* buff,char* output,char* string)
{
	int xt = ifindstr(NOPREV,buff,string);

	char* temp;
	temp = new char[strlen(buff)+1];
	stringcopy(temp,buff);

	char* ltemp;
	char* rtemp;

	ltemp = new char[strlen(buff)+1];
	rtemp = new char[strlen(buff)+1];

	leftcopy(buff,ltemp,xt);
	rightcopy(buff,rtemp,xt+strlen(string));
	
	strcpy(output,ltemp);
	strcat(output,rtemp);

	delete [] temp;
	delete [] ltemp;
	delete [] rtemp;
}

void strsavefile(char* filename,char* buff)
{
	ofstream fout(filename);

	fout << buff;

	fout.close();
}

int getfilestringlength(char* filename)
{
	int count = 0;
	ifstream fin(filename);
	if(fin)
	{
		char ch;
		while(fin.get(ch))
		{
			count++;
		}

		fin.close();
		return count;

	} else { return -1; } // failure

	return -1;
}

bool strloadfile(char* file,char* output)
{
	int count = 0;
	ifstream fin(file);
	if(fin)
	{
		char ch;
		int str_i = 0;
		while(fin.get(ch))
		{
			output[str_i] = ch;
			str_i++;
		}

		output[str_i] = 0;
		return true;
	}
	else
	{
		return false;
	}

	return false;
}

void reversestring(char* input,char* output)
{
	int len;
	len = strlen(input);
	int fcount = 0;

	for(int i = len; i > 0; i--)
	{
		output[fcount] = input[i];
		fcount++;
	}
	
	output[fcount] = 0;
}

bool isstrvalid(char* string)
{
	int len = strlen(string);
	for(int i = 0; i < len; i++)
	{
		if(string[i] == 0)
		{
			return true; // true it is a null terminated string!
		}
	}

	return false;
}

// Save Master INI
bool SaveMasterINI(char* filename,MasterINI* mini)
{
	ofstream fout(filename,ios::binary);

	if(fout)
	{


	fout.write((char*)&mini,sizeof(mini));

	fout.close();

	return true;

	}
	fout.close();
	return false;
}
// Load master INI
bool LoadMasterINI(char* filename,MasterINI* mini)
{
	ifstream fin(filename,ios::binary);

	if(fin)
	{
		fin.read((char*)&mini,sizeof(mini));
	}
	
	fin.close();
	return false;
}

// string compare (case sensitive)
bool mstrcmp(char* buff1,char* buff2)
{
	int len;
	int len2;
	len = strlen(buff1);
	len2 = strlen(buff2);

	if(len != len2)
	{
		return false; // not equal length
	}

	for(int i = 0; i < len; i++)
	{
		if(buff1[i] != buff2[i])
		{
			return false;
		}
	}

	return true;
}

// string compare (not case sensitive)
bool mstrcmpx(char* buff1,char* buff2)
{
	int len;
	int len2;
	len = strlen(buff1);
	len2 = strlen(buff2);

	if(len != len2)
	{
		return false; // not equal length
	}

	for(int i = 0; i < len; i++)
	{
		if(tolower(buff1[i]) != tolower(buff2[i]))
		{
			return false;
		}
	}

	return true;
}

bool insidestr(char* buff1,char* buff2)
{
	int chk;
	chk = findstr(buff1,buff2);

	if(chk == -1)
	{
		return false;
	}
	
	return true;
}

bool insidestrx(char* buff1,char* buff2)
{
	char* pbuff1;
	char* pbuff2;

	pbuff1 = new char[strlen(buff1)+1];
	pbuff2 = new char[strlen(buff2)+1];

	stringcopy(pbuff1,buff1);
	stringcopy(pbuff2,buff2);

	lcase(pbuff1);
	lcase(pbuff2);

	int chk;
	chk = findstr(pbuff1,buff2);

	delete [] pbuff1;
	delete [] pbuff2;
	pbuff1 = 0;
	pbuff2 = 0;

	if(chk == -1)
	{
		return false;
	}
	
	return true;
}
// string seperation from 2 points
void strsep(char* str, char* sleft, int go_left, char* sright, int go_right)
{
	leftcopy(str,sleft,go_left);
	rightcopy(str,sright,go_right);
}
void strsetnull(char* str,int pos)
{
	str[pos] = 0;
}

void rmvnullset(char* str)
{
	int len;
	len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		if(str[i] == 0)
		{
			str[i] = ' ';
		}
	}
}

int getnullpos(char* str)
{
	int len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		if(str[i] == 0)
		{
			return i;
		}
	}

	return -1; // failure to find 0
}
// trim commented characters () 
void trimcom(char* str, char* output,char start_c,char stop_c)
{
	int len = strlen(str);
	int index = 0;

	bool iadd = true;

	for(int z = 0; z < len; z++)
	{
		if(str[z] == start_c)
		{
			iadd = false; 
		}

		if(str[z] == stop_c)
		{
			iadd = true;
		}

		if(iadd == true)
		{
			output[index] = str[z];
			index++;
		}
	}
	
	output[index] = 0;
}

// trim comments to an assembly language source file
void asmtrim(char* input,char* output)
{
	trimcom(input,output,';','\n');
}

// count the number of lines exisitng within the source
int countlines(char* buffer)
{
	return findoccourance(buffer,"\n");
}
// get the first letter thats not a space
int getfirstletter(char* buff)
{
	int len = strlen(buff);
	
	for(int i = 0; i < len; i++)
	{
		if(buff[i] != ' ')
		{
			return i;
		}
	}
	return -1; // failure! no letters
}

#endif
