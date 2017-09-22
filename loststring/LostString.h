// Lost String Header
// Jared Bruni
// www.lostsidedead.com

#include <string.h>
#include <windows.h>

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