// Lost String
// by Jared Bruni
// www.lostsidedead.com

#include "LostString.h"


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



