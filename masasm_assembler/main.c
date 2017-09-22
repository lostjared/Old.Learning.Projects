/*

  MasAsm - written by Jared Bruni
  www.lostsidedead.com
  
	assembler, for the MAS bytecode
	
	  written in the C programming language
	  decided to change up my style for this one
	  for practice
	  
*/

#include "thehead.h"


// variables
char* sourcecode = NULL;
int err_count = 0;
struct ProgramHeader prog;
char filepath[100];

// function prototypes

void loadsource(const char *source);
void assemble();
void printerrorf( const char *source, ...);
void getname();
void getblocks();
void initblocks();
void clearblocks();
void getblock(int pos, char *data, char *name);
void procblocks();
void procvariables(int i);
void procvconst();
void procvdec(int i);
void proccode(int i);
BOOL procinc(char* inc, char *data);
BOOL inctobyte(char *ins, char *op1, char *op2, int opnum, char *bytecode);
void addvar(char *dec);
void debugprintout();
void outputmve();
void getvarnamebydata(char* data,char* name);
void getvarindexbydata(char* data, char* datastr);
void constfix();

BOOL quotecheck();
BOOL blockcheck();
BOOL concheck();
BOOL varcheck();
BOOL outblockcheck();
BOOL outblockcheck2();
BOOL invalidcharcheck();
BOOL isvar(char *var);


int  varindexbyname(char* var);
void getvarbyname(char *name, char *data);
void getvarbyindex( int index, char *data);
void setvarbyname(char *name, char *data);
void setvarbyindex(int index, char *data);
int  varbyconst(char* con);
int  gettypebyname(char* name);



// print a error found in source code
void printerrorf( const char *source, ...)
{
	va_list list; 
	char* string;
	err_count++;
	string = malloc(strlen(source)+1);
	va_start(list, source); 
	vsprintf((char*)string,source,list);
	va_end(list); 
	printf("error: %s\n",string);
	free(string);
	string = 0;
}

// main function
void main(int count, char** argument)
{
	
	int last_s;
	
	printf("\nmasasm - assembler version %i\n\nwritten by Jared Bruni\n\nwww.lostsidedead.com\n\n",MASASM_VERSION);
	
	last_s = bfindstr(argument[0],"\\");
	leftcopy(argument[0],filepath,last_s+1); // contains the last backslash 
	
	
	
	if(count == 1)
	{
		printf("\nsyntax error: requires parameters\n\ncorrect syntax\n\nmasasm sourcename.mas\n\n\n");
		system("pause");
		return;
	}
	
	if(isfile(argument[1]) == FALSE)
	{
		printf ("\nfatal error: file (%s) not found!",argument[1]);
		printf ("\n\n\n\n");
		system("pause");
		return;
	}
	
	sourcecode = malloc (flen(argument[1]) + 1);
	
	initblocks();
	
	loadsource(argument[1]);
	assemble();
	
	// watch out for this one
	debugprintout();
	
	if( err_count == 0 )
	{
		printf("\n%s assemebled with (0) errors\n",argument[1]);
		// output file
		outputmve();
	}
	else
	{
		printf("\n%s assembled with (%i) errors\n",argument[1],err_count);
	}
	
	// clean up after words
	if(sourcecode != NULL)
	{
		free(sourcecode);
	}
	
	
	clearblocks();
	
	system("pause");
}


// debug printout
void debugprintout()
{
	FILE* file;
	int i;
	char fname[100];
	
	strcpy(fname,filepath);
	strcat(fname,"debugasm.html");
	
	printf("\noutputing debug file to: %s",fname);
	
	file = fopen(fname,"w");
	
	fprintf(file,"<HTML><FONT FACE=\"FIXEDSYS\" COLOR=\"#BD0000\">masasm assembler debug output, written by Jared Bruni<br><br>\n\n<a href=\"http://www.lostsidedead.com\">www.lostsidedead.com</a><br>\n");
	fprintf(file,"\n\n<br><br><font color=\"green\">variable list</font><br>\n\n");
	
	if(prog.var != NULL)
	{
		
		for(i = 0; i < prog.voff; i++)
		{
			fprintf(file,"<br>variable name: <font color=\"blue\">%s</font>  value (<font color=\"purple\"> %s </font> ) \n<br>",prog.var[i].name,prog.var[i].data);
		}
		
	}
	
	fprintf(file,"\n<br><br><font color=\"green\">code blocks</font><br><br>\n\n");
	
	for(i = 1; i < prog.num; i++)
	{
		fprintf(file,"\n<br>code block (proc/con/var) <font color=\"blue\">%s </font>\n<br>{<br>\n%s\n<br>}<br>\n",prog.blocks[i].name,prog.blocks[i].data);
	}
	
	
	fprintf(file,"</FONT></HTML>");
	
	fclose(file);
}

// output mve (output the executable)
void outputmve()
{
	// produce the executable file with MAS bytecode
	FILE* ofile;
	char iname[100];
	int i;
	
	
	sprintf(iname,"%s%s.mve",filepath,prog.name);
	
	printf("\n\nexecutable outputed to: %s\n\n",iname);
	
	killline(iname);
	
	ofile = fopen(iname,"w");
	
	fprintf(ofile,"var{");
	
	
	// print out variables, and constant variables
	
	for(i = 0; i < prog.voff; i++)
	{
		char mtype[10];
		
		if(prog.var[i].type == TYPE_STRING)
		{
			strcpy(mtype,"$");
		}
		else
		{
			if(prog.var[i].type == TYPE_REAL)
			{
				strcpy(mtype,"#");
			}
			else
			{
				
				strcpy(mtype,"&");
				
			}
			
		}
		
		
		
		if( i != prog.voff - 1 )
		{
			fprintf(ofile,"%s%s:\"%s\",",prog.var[i].name,mtype,prog.var[i].data);
		}
		else
		{
			fprintf(ofile,"%s%s:\"%s\"",prog.var[i].name,mtype,prog.var[i].data);
		}
	}
	
	fprintf(ofile,"}");
	
	
	// print out all the code blocks
	
	for(i = 1; i < prog.num; i++)
	{
		if(strcmp(prog.blocks[i].name,"variables") != 0)
		{
			
			fprintf(ofile,"%s{%s}",prog.blocks[i].name,prog.blocks[i].cdata);
			
		}
	}
	
	
	fclose(ofile);
	
}


// load up the source
void loadsource(const char *source)
{
	readfile(source,sourcecode);
}


// begin assembly proccess
void assemble()
{
	trimr(sourcecode);
	trimcomments(sourcecode);
	constfix();
	// ensure data is valid for block proccessing
	if(quotecheck() == FALSE || blockcheck() == FALSE || concheck() == FALSE || varcheck() == FALSE || outblockcheck() == FALSE || outblockcheck2() == FALSE ||  invalidcharcheck() == FALSE)
	{
		return;
	}
	killwspace(sourcecode);
	lcase(sourcecode);
	getname();
	getblocks();
	procblocks();
}

// fix the constants
void constfix()
{
	int i,len = strlen(sourcecode),pos = 0;
	BOOL go = FALSE;
	char* temp;
	temp = malloc(len + 1);
	
	for(i = 0; i < len; i++)
	{
		if(sourcecode[i] == '\"')
		{
			if(go == TRUE) { go = FALSE; } else { temp[pos] = sourcecode[i]; pos++; go = TRUE; continue; }
		}
		
		
		if(go == TRUE)
		{
			switch(sourcecode[i])
			{
			case ' ':
				temp[pos] = 'µ';
				break;
			case '\n':
				temp[pos] = '¶';
				break;
			case '\r':
				temp[pos] = 'Ý';
				break;
			default:
				temp[pos] = sourcecode[i];
				break;
			}
			
		}
		else
		{
			temp[pos] = sourcecode[i];
		}
		
		pos++;
		
	}
	
	temp[pos] = 0;
	
	
	strcpy(sourcecode,temp);
	
	free(temp);
}

// get the objects name
void getname()
{
	char name[100];
	int mas;
	int obrace;
	
	
	mas = findstr(sourcecode,"mas object");
	
	if(mas == -1)
	{
		printerrorf(" program missing mas object implementation");
		return;
	}
	
	obrace = ifindstr(mas,sourcecode,"{");
	
	if(obrace == -1)
	{
		printerrorf(" missing the first opening brace ");
		return;
	}
	
	midcopy(sourcecode,name,mas + 10,obrace);
	killspace(name);
	
	if(strlen(name) == 1)
	{
		printerrorf(" this mas object requires a name");
		return;
	}
	
	strcpy(prog.name,name);
}

// get the opening code blocks
void getblocks()
{
	int ocount;
	int ccount;
	int i = 0, len = strlen(sourcecode);
	int blocks = 0;
	
	
	
	ocount = findoccourance(sourcecode,'{');
	ccount = findoccourance(sourcecode,'}');
	
	if(ocount != ccount)
	{
		printerrorf(" code blocks do not allign, your missing a { or a } somewere");
		return;
	}
	
	// make room for the blocks
	
	prog.blocks = (struct CodeBlock*)malloc( ocount * sizeof (struct CodeBlock));
	
	
	for(i = 0; i < len; i++)
	{
		if(sourcecode[i] == '{' )
		{
			char *cblock = NULL;
			char cname[100];
			
			cblock = malloc(strlen(sourcecode) + 1);
			
			getblock(i,cblock,cname);
			prog.blocks[blocks].data = malloc(strlen(sourcecode) + 1);
			strcpy(prog.blocks[blocks].data,cblock);
			strcpy(prog.blocks[blocks].name,cname);
			
			blocks++;
			
			if(cblock != NULL)
			{
				free(cblock);
			}
		}
		
	}
	
	prog.num = blocks;
	
	for(i = 0; i < blocks; i++)
	{
		prog.blocks[i].cdata = NULL;
	}
	
	
}
// get the block
void getblock(int pos, char *block, char *blockname)
{
	int oc = 0;
	int cc = 0;
	int i,len = strlen(sourcecode);
	int pr;
	int co;
	int de;
	int va;
	int cpos = 0;
	int open_b;
	int close_b;
	
	int noff = 0;
	
	
	for(i = pos-1; i < len; i++)
	{
		if(sourcecode[i] == '{')
		{
			oc++;
			if(oc == 1)
			{
				open_b = i;
			}
			
		}
		
		if(sourcecode[i] == '}')
		{
			cc++;
			if(oc == cc)
			{
				close_b = i;
				break;
			}
		}
	}
	
	
	midcopy(sourcecode,block,open_b+1,close_b);
	
	pr = ibfindstr(pos,sourcecode,"proc");
	co = ibfindstr(pos,sourcecode,"constructor");
	de = ibfindstr(pos,sourcecode,"deconstructor");
	va = ibfindstr(pos,sourcecode,"var");
	
	if(sourcecode[co-1] == 'e')
	{
		co = ibfindstr(co-1,sourcecode,"constructor");
	}
	
	if(pr > co && pr > de && pr > va)
	{
		cpos = pr;
	}
	
	if( co > pr && co > de && co > va)
	{
		cpos = co;
	}
	
	if( de > co && de > pr && de > va)
	{
		cpos = de;
	}
	
	if( va > de && va > co && va > pr)
	{
		cpos = va;
	}
	
	
	midcopy(sourcecode,blockname,cpos,pos);
	nametrim(blockname);
}

// clear the blocks
void clearblocks()
{
	int i;
	for(i = 0; i < prog.num; i++)
	{
		free(prog.blocks[i].data);
		
		if(prog.blocks[i].cdata != NULL)
		{
			free(prog.blocks[i].cdata);
		}
	}
	
	if(prog.blocks != NULL)
	{
		
		
		free(prog.blocks);
		
	}
	
	for(i = 0; i < prog.vnum; i++)
	{
		if(prog.var[i].data != NULL)
		{
			
			free(prog.var[i].data);
			
		}
	}
	
	if(prog.var != NULL)
	{
		
		free(prog.var);
		
	}
}

// initilize the blocks
void initblocks()
{
	prog.blocks = NULL;
	prog.num = 0;
	prog.var = NULL;
	prog.vnum = 0;
	prog.voff = 0;
}

// check and see if quotes line up correctly
BOOL quotecheck()
{
	int oq;
	
	// find the occourance of quotes
	// then use the moduls operator, to see if it is a even value
	// if it is not, then print a error message
	oq = findoccourance(sourcecode,'"')%2;
	
	if(oq != 0)
	{
		printerrorf(" quotes do not allign, somewere your forgot a ending \" ");
		return FALSE;
	}
	
	return TRUE;
}

// check and see if the blocks are event, if not, we dont want to continue
BOOL blockcheck()
{
	int ob = findoccourance(sourcecode,'{');
	int cb = findoccourance(sourcecode,'}');
	
	if(ob == cb)
	{
		return TRUE;
	}
	
	printerrorf(" blocks to not allign, somewere you forgot a opening { or closing }");
	return FALSE;
}

// check and see if nessicary code blocks, exisit (like var, and constructor)
BOOL concheck()
{
	
	int vchk;
	int cchk;
	int dchk;
	
	vchk = findstr(sourcecode,"variables");
	cchk = findstr(sourcecode,"constructor");
	dchk = findstr(sourcecode,"deconstructor");
	
	if(vchk == NULLPOS)
	{
		printerrorf(" missing the variables code block ");
		return FALSE;
	}
	
	if(cchk == NULLPOS || sourcecode[cchk-1] == 'e')
	{
		printerrorf(" object missing constructor ");
		return FALSE;
	}
	
	if(dchk == NULLPOS)
	{
		printerrorf(" object missing deconstructor ");
		return FALSE;
	}
	
	
	vchk = ifindstr(vchk+1,sourcecode,"variables");
	
	if(vchk != NULLPOS)
	{
		printerrorf(" more then one variables block in mas object");
		return FALSE;
	}
	
	cchk = ifindstr(cchk+1,sourcecode,"constructor");
	
	if(sourcecode[cchk-1] == 'e')
	{
		cchk = ifindstr(cchk+1,sourcecode,"constructor");
	}
	
	if(cchk != NULLPOS)
	{
		printerrorf(" more then one constructor block in mas object");
		return FALSE;
	}
	
	dchk = ifindstr(dchk+1,sourcecode,"deconstructor");
	
	if(dchk != NULLPOS)
	{
		printerrorf(" more then one deconstructor block in mas object");
		return FALSE;
	}
	
	return TRUE;
}

// ensure that variables , and variable declerations are alright
BOOL varcheck()
{
	
	int i = 0, len = strlen(sourcecode);
	
	for(i; i < len; i++)
	{
		if(sourcecode[i] == '\"' && sourcecode[i+1] == '\"')
		{
			char err[200];
			int line;
			
			line = linebypos(sourcecode,i);
			sprintf(err," on line (%i) there is a null constant (2 quotes ""), .. null constants are illegal",line);
			printerrorf(err);
			return FALSE;
			
		}
		
	}
	
	
	return TRUE;
}

// ensure that there is no 'junk' data in invalid positions, unless they are comments
BOOL  outblockcheck()
{
	int i, len = strlen(sourcecode),lo;
	BOOL igo = TRUE;
	
	lo = bfindstr(sourcecode,"}") + 1; // find the very last }
	
	
	// ensure that there is no invalid data after the last }
	for(i = lo; i < len; i++)
	{
		
		if(sourcecode[i] == ';')
		{
			igo = FALSE;
			continue;
		}
		
		if(sourcecode[i] == '\n')
		{
			igo = TRUE;
		}
		
		
		if(igo == TRUE)
		{
			
			if( sourcecode[i] != ' ' && sourcecode[i] != 10 && sourcecode[i] != 13 )
			{
				int line = linebypos(sourcecode,i);
				printerrorf("  invalid character (%c) on line (%i) (why code after last })",sourcecode[i],line);
				return FALSE;
			}
			
		}
		
	}
	
	// search before the first {
	lo = findstr(sourcecode,"mas");
	
	if(lo != -1)
	{
		lo -= 3;
		
		for(i = lo; i > 0; i--)
		{
			
			if(sourcecode[i] == ';')
			{
				igo = FALSE;
				continue;
			}
			
			if(sourcecode[i] == '\n')
			{
				igo = TRUE;
			}
			
			
			if(igo == TRUE)
			{
				
				if( sourcecode[i] != ' ' && sourcecode[i] != 10 && sourcecode[i] != 13 )
				{
					int line = linebypos(sourcecode,i);
					printerrorf("  invalid character (%c) on line (%i) (why data before first block?)",sourcecode[i],line);
					return FALSE;
				}
				
			}
			
		}
		
	}
	
	return TRUE;
}

// check and sife if there is invalid out of place data inside of the mas objects blocks
BOOL outblockcheck2()
{ 
	
	// this is commented out because I  have it automaticly truncate data outside of the blocks
	// in the wrong spots
	
	
	/*
	char* temp = NULL;
	int i, pos = 0, len = strlen(sourcecode);
	
	  
		temp = malloc( strlen(sourcecode) + 1 ); // allocate data
		
		  for(i = 0; i < len; i++)
		  {
		  if(sourcecode[i] != '\n' && sourcecode[i] != '\r')
		  {
		  temp[pos] = sourcecode[i];
		  pos++;
		  }
		  }
		  
			temp[pos] = 0;
			
			  
				
				  
					free(temp); // free up allocated data
					
	*/
	/*
	int i = 0,z,q, len = bfindstr(sourcecode,"}");
	
	  
		for(i = findstr(sourcecode,"{") + 1; i < len; i++)
		{
		if(sourcecode[i] == '{')
		{
		for(z = i-1; z > 0; z--)
		{
		if(sourcecode[z] != ' ' && sourcecode[z] != 10 && sourcecode[z] != 13)
		{
		for(q = z; q > 0; q--)
		{
		char cx[1];
		if(sourcecode[q] == '}')
		{
		break;
		}
		cx[0] = sourcecode[q];
		cx[1] = 0;
		MessageBox(0,cx,"",0);
		}
		
		  }
		  
			}
			
			  }
			  
}*/
	
	return TRUE;
}


// search through the string, for any characters which are not accepted by the assembler
// exclude those inside of ""
BOOL invalidcharcheck()
{
	int i , len = strlen(sourcecode);
	BOOL igo = TRUE;
	
	for(i = 0; i < len; i++)
	{
		if(sourcecode[i] == '\"')
		{
			if(igo == TRUE) { igo = FALSE; } else { igo = TRUE; }
		}
		
		if(igo == TRUE)
		{
			if(ismaschar(sourcecode[i]) == FALSE)
			{
				// here
				char err[100];
				int line;
				line = linebypos(sourcecode,i);
				sprintf(err," invalid character (%c)  on line (%i) was this an accident? ", sourcecode[i],line);
				printerrorf(err);
				return FALSE;
			}
		}
		
	}
	
	return TRUE;
	
}



// proccess the code blocks
void procblocks()
{
	int i;
	
	
	for(i = 1; i < prog.num; i++)
	{
		// ensure no there are nested code blocks
		if(findstr(prog.blocks[i].data,"}") != -1 || findstr(prog.blocks[i].data,"}") != -1)
		{
			char err[100];
			sprintf(err," the code block (%s) contains invalid data ( a { or a }), you cannot nest blocks",prog.blocks[i].name); 
			// error block contains invalid data
			printerrorf(err);
			return;
		}
		if(findstr(prog.blocks[i].name,"variables") != -1)
		{
			procvariables(i);
		}
		else
		{
			proccode(i);
		}
	}
}

// proccess the variables code block
void procvariables(int i)
{
	
	int qcount;
	int fpos;
	int j;
	
	// first lets find out exactly how many slots for variables, we will have
	
	fpos = findstr(prog.blocks[i].data,"var");
	// find all " ", (locate all constant variables first)
	qcount = findoccourance( sourcecode, '"') / 2;
	
	if(fpos != -1)
	{ 
		qcount ++;
	}
	
	
	while(fpos != -1)
	{
		fpos = ifindstr(fpos+1,prog.blocks[i].data,"var");
		
		if(fpos != -1)
		{
			qcount++;
		}
	}
	
	prog.var = (struct Variables*) malloc(qcount * sizeof(struct Variables)); 
	
	for(j = 0; j < qcount; j++)
	{
		prog.var[j].data = NULL;
	}
	
	prog.vnum = qcount;
	
	// first add in all constant variables
	procvconst();
	// then  add in all variable declerations
	procvdec(i);
	// after all variable declerations have been added in
	// modify the source code, so that it contains the corret address
	
	
}


// load all the constant variables, into the variable table
void procvconst()
{
	int i,len = strlen(sourcecode);
	BOOL qopen = FALSE;
	char *temp;
	int  tindex = 0;
	int cnum = 0;
	
	char tempname[20];
	
	temp = malloc ( strlen( sourcecode ) );
	
	
	
	for(i = 0; i < len; i++)
	{
		if(sourcecode[i] == '"')
		{
			
			if(qopen == TRUE)
			{
				qopen = FALSE;
				temp[tindex] = 0;
				tindex = 0;
				sprintf(tempname,"con%i",cnum);
				cnum++;
				strcpy(prog.var[prog.voff].name,tempname);
				prog.var[prog.voff].data = malloc ( strlen(temp) + 1);
				strcpy(prog.var[prog.voff].data,temp);
				prog.var[prog.voff].type = TYPE_STRING;
				prog.voff++;
				
			}
			else
			{
				qopen = TRUE;
				i++;
			}
		}
		
		if(qopen == TRUE)
		{
			temp[tindex] = sourcecode[i];
			tindex++;
		}
	}
	
	temp[tindex] = 0;
	
	
	
	free(temp);
	
}

// load all the declared variables into the variable table
void procvdec(int i)
{
	int len = strlen(prog.blocks[i].data);
	int z;
	int lcopy = 0;
	
	char *temp;
	
	temp = malloc (strlen(sourcecode)+1);
	
	
	for(z = 0; z < len; z++)
	{
		if(prog.blocks[i].data[z] == '\n')
		{
			midcopy(prog.blocks[i].data,temp,lcopy,z);
			lcopy = z;
			killspace(temp);
			if(strlen(temp) > 1)
			{
				
				addvar(temp);
				
			}
		}
	}
	
	
	free(temp);
}

// add a variable, declared in variables section
void addvar(char *dec)
{
	int fvar;
	char name[25];
	int atype = TYPE_NULL;
	int es,chk;
	
	
	if(strlen(dec) < 3)
	{
		printerrorf("invalid statement in variable code block\n");
		return;
	}
	
	fvar = findstr(dec,"var");
	
	if(fvar == -1)
	{
		printerrorf("invalid statement only variable declerations in variable code block!");
		return;
	}
	
	if( dec[fvar+3] != '$' && dec[fvar+3] != '&' && dec[fvar+3] != '#')
	{
		printerrorf(" invalid variable decleration, missing variable type (&(unsigned long), #(double),$(string))");
		return;
	}
	
	
	if( iop(dec) )
	{
		printerrorf(" variable block contains invalid characters!");
		return;
	}
	
	
	rightcopy( dec, name, fvar+4);
	
	// decide which variable type
	switch(dec[fvar+3])
	{
	case '$':
		atype = TYPE_STRING;
		break;
	case '&':
		atype = TYPE_NUMERIC;
		break;
	case '#':
		atype = TYPE_REAL;
		break;
	}
	
	// my ode to pascal
	es = findstr(dec,":=");
	chk = findstr(dec,":");
	
	if(dec[chk+1] != '=' && chk != -1)
	{
		printerrorf(" invalid variable decleration unknown character ':'");
		return;
	}
	
	chk = findstr(dec,"=");
	
	if(dec[chk-1] != ':' && chk != -1)
	{
		printerrorf(" invalid variable decleration unknown character '='");
		return;
		
	}
	
	if(es == FAIL)
	{
		
		if(checkvname(name) == FALSE)
		{
			printerrorf(" variable declerations, contain duplicate variable names", name);
			return;
		}
		
		strcpy(prog.var[prog.voff].name,name);
		prog.var[prog.voff].type = atype;
		prog.var[prog.voff].data = NULL;
		
	}
	else
	{
		char *temp;
		int  epos;
		temp = malloc ( strlen(dec) + 1);
		rightcopy( dec, temp,es+2);
		
		if(atype == TYPE_NUMERIC)
		{
			killline(temp);
			if(findstr(temp,"\"") != FAIL)
			{
				printerrorf(" invalid delceration, trying to assign string to numeric variable");
				goto ifree;
			}
			
			epos = findstr(name,":=");
			leftcopy(name,prog.var[prog.voff].name,epos);
			
			// variable name already exisits
			if(checkvname(prog.var[prog.voff].name) == FALSE)
			{
				printerrorf(" variable name (%s) already exisits!", prog.var[prog.voff].name);
				strcpy(prog.var[prog.voff].name,"");
				free(temp);
				return;
			}
			
			prog.var[prog.voff].data = malloc (strlen(temp)+1);
			
			strcpy(prog.var[prog.voff].data,temp);
			prog.var[prog.voff].type = TYPE_NUMERIC;
		}
		
		if(atype == TYPE_STRING)
		{
			printerrorf(" string data types, do not allow assignment operator :=");
		}
		
		if(atype == TYPE_REAL)
		{
			printerrorf(" real numbers cannot use the assignment operator :=  use mov on the constructor to assign a value");
		}
		
ifree:
		free(temp);
	}
	
	
	prog.voff++;
	
}


// check and see if a variable name already exisits
BOOL checkvname(char *name)
{
	int i;
	for(i = 0; i < prog.voff; i++)
	{
		// name already exisits
		if(strcmp(prog.var[i].name,name) == 0)
		{
			return FALSE;
		}
	}
	
	return TRUE;
}

// get the variable index by its name
int getvarindexbyname(char* name)
{
	int i;
	
	for(i = 0; i < prog.voff; i++)
	{
		if(strcmp(prog.var[i].name,name) == 0)
		{
			return i;
		}
	}
	
	return FAIL; // is not a variable
}
// get the variable index by its data
void getvarindexbydata(char* data, char* datastr)
{
	char* temp;
	char* tempdata;
	
	int i;
	
	tempdata = malloc (strlen(data) + 1);
	strcpy(tempdata,data);
	
	trimquotes(tempdata);
	killspace(tempdata);
	killline(tempdata);
	
	
	for(i = 0; i <  prog.voff; i++)
	{
		temp = malloc( strlen(prog.var[i].data) + 1);
		strcpy(temp,prog.var[i].data);
		trimquotes(temp);
		killspace(temp);
		killline(temp);
		
		if(findstr(temp,tempdata) != -1)
		{
			
			strcpy(datastr,prog.var[i].name);
			free(temp);
			free(tempdata);
			return;
			
		}
		
		
		free(temp);
		
	}
	
	
	free(tempdata);
	strcpy(datastr,"<null>");
	
}

// get a variable by its name
void getvarbyname(char *name, char *data)
{
	int i;
	
	for(i = 0; i < prog.voff; i++)
	{
		if( strcmp ( prog.var[i].name, name ) == 0 )
		{
			strcpy (data, prog.var[i].data);
			return;
		}
	}
	
	strcpy( data, "<null>");
	return;
}

// get the name of this variable, by what is inside it
void getvarnamebydata(char* data,char* name)
{
	int i;
	
	for(i = 0; i < prog.voff; i++)
	{
		if( strcmp(prog.var[i].data,data) == 0)
		{
			strcpy(name,prog.var[i].name);
			return;
		}
	}
	
	strcpy(name,"<null>");
}

// get a variable by its index
void getvarbyindex(int index, char *data)
{
	strcpy(data,prog.var[index].data);
}


// set variable by name 
void setvarbyname(char *name, char *data)
{
	int i;
	
	for(i = 0; i < prog.voff; i++)
	{
		// copy into buffer
		if(strcmp(prog.var[i].name ,name) == 0)
		{
			if(prog.var[i].data != NULL)
			{
				free(prog.var[i].data);
			}
			
			prog.var[i].data = malloc ( strlen(data) + 1);
			
			strcpy(prog.var[i].data, data);
			return;
		}
	}
	
	return; // not found
}

// set variable by index
void setvarbyindex(int index, char *data)
{
	if(prog.var[index].data != NULL)
	{
		free(prog.var[index].data);
	}
	
	prog.var[index].data = malloc ( strlen(data) + 1);
	strcpy(prog.var[index].data,data);
}

// does this variable name exisit?
BOOL isvar(char *var)
{
	int i;
	
	for(i = 0; i < prog.voff; i++)
	{
		// yep it exisits
		if(strcmp(prog.var[i].name,var) == 0)
		{
			return TRUE;
		}
	}
	
	return FALSE;
}
// return the type of variable by its name
int gettypebyname(char* name)
{
	int i;
	for(i = 0; i < prog.voff; i++)
	{
		
		if(strcmp(prog.var[i].name,name) == 0)
		{
			return prog.var[i].type;
		}
	}
	
	return TYPE_NULL;
}

// proccess code block
void proccode(int i)
{ 
	// build up each code block for instructions
	
	int offpos = 0;
	int z = 0;
	int len = strlen(prog.blocks[i].data);
	char *temp;
	char *source;
	int first = 0;
	BOOL zgo = TRUE;
	
	
	source = malloc( strlen(sourcecode) * 2); // make it big just in case
	
	
	strcpy(source,"");
	temp = malloc( len + 1 );
	
	
	for(z = 0; z < len; z++)
	{
		if(prog.blocks[i].data[z] == '\"')
		{
			if( zgo == TRUE ) { zgo = FALSE; } else { zgo = TRUE; }
		}
		
		if(zgo == FALSE)
		{
			continue;
		}
		
		if(prog.blocks[i].data[z] == '\n')
		{
			char *addinc = NULL;
			BOOL ok;
			midcopy(prog.blocks[i].data,temp,offpos,z);
			offpos = z;
			
			addinc = malloc(strlen(temp)+100);
			
			
			ok = procinc(temp,addinc);
			
			
			if(ok == TRUE)
			{
				
				// concatinate to exisiting string
				if(first == 1 && z != len)
				{
					strcat(source,",");
				}
				else
				{
					first++;
				}
				
				strcat(source,addinc);
			}
			
			
			free(addinc);
			
		}
		
		
		
	}
	
	// copy over into the correct buffer
	prog.blocks[i].cdata = malloc(strlen(source)+1);
	strcpy(prog.blocks[i].cdata,source);
	
	free(source);
	free(temp);
	
}

// translate a line of script into bytecode
// this is a very important function
BOOL procinc(char *script, char *bytecode)
{
	inctrim(script);
	
	if(strlen(script) > 2)
	{
		int lchk;
		int i = 0;
		int il = strlen(script);
		BOOL igo = TRUE;
		
		// first things first
		// lets break this up into instruction, and operands
		
		// first illegal characters check
		if(cmdcheck(script))
		{
			char errs[100];
			sprintf(errs," line of code (%s) contains invalid characters",script);
			printerrorf(errs);
			return FALSE;
		}
		
		// ok we only have the characters we need
		// there instructions can be 2 things
		// a code label, or a instruction
		lchk = FAIL;
		// find the colon, without finding colons inside of the " "
		for(i = 0; i < il; i++)
		{
			if( script[i] == '\"' )
			{
				if(igo == TRUE) { igo = FALSE; } else { igo = TRUE; }
				
			}
			
			if(igo == TRUE)
			{
				if(script[i] == ':')
				{
					lchk = i;
					break;
				}
			}
		}
		
		
		if(lchk != FAIL)
		{
			char *temp;
			
			temp = malloc ( strlen(script) + 1);
			
			leftcopy(script,temp,lchk);
			
			killspace(temp);
			killline(temp);
			
			// totaly ignore data on opposite site of :
			
			// pass this code label name, back to the assembler
			strcpy(bytecode,temp);
			
			
			free(temp);
			
			return TRUE;
		}
		else
		{
			int fcomma,fspace;
			
			char *ins = NULL; // the instruction
			char *op1 = NULL; // the first operand
			char *op2 = NULL; // the second operand
			int   opnum = 0; // the number of operands
			BOOL iok; // was the instruction translation ok?
			int ic = 0; // counter variable
			int len = strlen(script);
			BOOL igo = TRUE;
			
			ins = malloc ( strlen(script) + 1);
			op1 = malloc ( strlen(script) + 1);
			op2 = malloc ( strlen(script) + 1);
			
			// its a instruction
			// that means it can have 2 forms
			// ethier
			// mov ax
			// or 
			// mov ax,bx
			
			
			//	fcomma = findoccourance(script,',');
			fcomma = 0;
			
			// special search, make sure not to count commas, inside of " "
			
			for(ic = 0; ic < len; ic++)
			{
				
				if( script[ic] == '\"' )
				{
					if(igo == TRUE) { igo = FALSE; } else { igo = TRUE; }
				}
				
				
				if(igo == TRUE)
				{
					
					if( script[ic] == ',' )
					{
						fcomma++;
					}
					
				}
				
			}
			
			
			if(findstr(script,"\"") != -1)
			{
				fcomma = 0;
			}
			
			if(fcomma > 1)
			{
				char str[100];
				sprintf(str," error line of code (%s) contains more then one comma",script);
				printerrorf(str);
				goto endfail;
			}
			
			
			//	fcomma = findstr(script,",");
			fcomma = quotesearch(0,script,',');
			fspace = findstr(script," ");
			leftcopy(script,ins,fspace);
			
			// only has one operand
			if(fcomma == FAIL)
			{
				opnum = 1;
				rightcopy(script,op1,fspace);	   		
			}
			// has two operands
			else
			{
				opnum = 2;
				midcopy(script,op1,fspace,fcomma);
				rightcopy(script,op2,fcomma+1);
				
			}
			
			// pass to function, that proccesses a instruction, and
			// translates to bytecode
			if(strlen(ins) == 0) 
			{
				char err[100];
				sprintf(err," invalid instruction or unknown mnemoic (%s)  ", script);
				printerrorf(err);
				return FALSE;
			}
			
			iok = inctobyte(ins,op1,op2,opnum,bytecode);
			
			free(ins);
			free(op1);
			free(op2);
			
			return iok;
endfail:
			free(ins);
			free(op1);
			free(op2);
			return FALSE;
			
			
		}
		
	}
	
	return FALSE;
}

// instruction to bytecode
BOOL inctobyte(char *ins, char *op1, char *op2, int opnum, char *bytecode)
{
	int opcode;
	char opc[10];
	
	if(strlen(ins) == 0)
	{
		printerrorf("invalid instruction");
		return FALSE;
	}
	
	killline(ins);
	
	if(opnum >= 1)
	{
		killline(op1);
	}
	
	if(opnum >= 2)
	{
		killline(op2);
	}
	
	opcode = isins(ins);
	
	
	if(opcode == FAIL)
	{
		char err[75];
		sprintf(err," invalid instruction (%s) ",ins);
		printerrorf(err);
		return FALSE;
		
	}
	
	
	itoa(opcode,opc,16);
	
	
	switch(opcode)
	{ 
		//  instruction type  [inc][var][var/const]
	case 0x1:
	case 0x2:
	case 0x3:
	case 0x4:
	case 0x5:
	case 0x6:
	case 0x7:
	case 0x8:
		{
			int op1num;
			int op2num;
			
			char nop1[25];
			char nop2[25];
			
			
			BOOL vchk;
			BOOL nchk;
			BOOL vchk2;
			
			int vtype = TYPE_NULL;
			
			strcpy(bytecode,opc);
			strcat(bytecode,"!");
			vchk = isvar(op1);
			
			if(opnum != 2)
			{
				printerrorf(" instruction requires only 2 operands");
				return FALSE;
			}
			
			if(vchk == FALSE)
			{
				char err[100];
				sprintf(err," on instruction (%s %s, %s) first operand requires a variable, you have a (%s)",ins,op1,op2,op1);
				printerrorf(err);
				return FALSE;
			}
			
			// make sure first operand's variable is of TYPE NUMERIC or TYPE REAL
			vtype = gettypebyname(op1);
			
			if(vtype == TYPE_REAL)
			{
				switch(opcode)
				{
				case 0x5:
				case 0x6:		
				case 0x7:
					{
						char errorx[100];
						sprintf(errorx," invalid type for instruction (%s), please use a unsigned long (&)",ins);
						printerrorf(errorx);
						return FALSE;
					}
					break;
				}
				
				// trying to use invalid instructions
				
				
				
			}
			
			if(vtype == TYPE_NUMERIC || vtype == TYPE_REAL)
			{
			}
			else
			{
				char err[100];
				sprintf(err," on instruction (%s %s, %s) first operand requires type of NUMERIC (&) or REAL (#)",ins,op1,op2);
				printerrorf(err);
				return FALSE;
			}
			
			
			
			strcat(bytecode,"*");
			op1num = getvarindexbyname(op1);
			itoa(op1num,nop1,16);
			strcat(bytecode,nop1);
			strcat(bytecode,":");
			
			
			nchk = isnumeric(op2);
			vchk2 = isvar(op2);
			
			if(nchk == FALSE && vchk2 == FALSE)
			{
				char err[100];
				sprintf(err," instruction (%s %s,%s) second operand contains invalid data", ins,op1,op2);
				printerrorf(err);
				return FALSE;
			}
			
			// it is a variable on the second operand lets get its type
			vtype = gettypebyname(op2);
			
			if(vtype == TYPE_STRING)
			{
				char err[100];
				sprintf(err," instruction (%s %s,%s) second operand (%s) contains string varaible.. requres numeric or real ",ins,op1,op2,op2);
				printerrorf(err);
				return FALSE;
			}
			
			if(vtype != gettypebyname(op1) && nchk == FALSE)
			{
				char err[100];
				sprintf(err," instruction (%s %s,%s) second operand (%s) contains type other then first operand ( both must be same type )", ins,op1,op2,op2);
				printerrorf(err);
				return FALSE;
			}
			
			// ok now
			// we need to check and see if the variable type is NUMERIC
			// that there is no DECIMAL point
			// and we also need to see if the variable type is REAL
			// that no hex digits exisit
			
			vtype = gettypebyname(op1); // operand 1 type
			
			switch(vtype)
			{
			case TYPE_NUMERIC:
				{
					int pchk;
					pchk = findstr(op2,".");
					if(pchk != -1)
					{
						char err[150];
						sprintf(err," instruction (%s %s,%s) second operand contains constant value containing a decimal point, however your variable type is Numeric & (unsigned long)",ins,op1,op2);
						printerrorf(err);
						return FALSE;
					}
				}
				break;
			case TYPE_REAL:
				{
					int j,jlen = strlen(op2);
					
					if(gettypebyname(op2) == TYPE_NULL)
					{
						
						for(j = 0; j < jlen; j++)
						{
							switch(op2[j])
							{
							case 'a':
							case 'b':
							case 'c':
							case 'd':
							case 'e':
							case 'f':
								{
									char err[150];
									sprintf(err," instruction(%s %s,%s) second operand contains hexadecimal constant, however the first operand contains type of real (#) a double",ins,op1,op2);
									printerrorf(err);
									return FALSE;
								}
								break;
							}
						}
						
					}
				}
				break;
			}
			
			
			
			if(nchk == TRUE)
			{
				strcat(bytecode,op2);
			}
			else
			{
				strcat(bytecode,"*");
				op2num = getvarindexbyname(op2);
				itoa(op2num,nop2,16);
				strcat(bytecode,nop2);
			}
			
			return TRUE;
		}
		break;
		
		
		// instruction type name [ax]
	case 0x20:
	case 0x21:
	case 0x22:
		{
			BOOL vchk;
			char vstr[50];
			int vnum;
			
			
			if(opnum != 1)
			{
				char err[50];
				sprintf(err," this instruction (%s) requires only 1 operand",ins);
				printerrorf(err);
				return FALSE;
			}
			
			vchk = isvar(op1);
			
			if(vchk == FALSE)
			{
				char err[50];
				sprintf(err," operand contains a unknown variable/value (%s)", op1);
				printerrorf(err);
				return FALSE;
			}
			
			vnum = getvarindexbyname(op1);
			
			itoa(vnum,vstr,16);
			
			
			strcpy(bytecode,opc);
			strcat(bytecode,"!");
			strcat(bytecode,"*");
			strcat(bytecode,vstr);
			strcat(bytecode,":");
			strcat(bytecode,"(null)");
			
			return TRUE;
			
		}
		break;
		
		// string algorithms operand type 1
		
	case 0x40:// smov ax,bx
	case 0x41:// scat var,""
		{
			// ensure that the variables are strings
			
			char varname[100];
			int  varadd1;// variable 1
			int  varadd2;// variable 2
			char vadd1[25]; // string for varaible address 1
			char vadd2[25]; // string for variable address 2
			
			if(opnum != 2)
			{
				char err[50];
				sprintf(err," instruction (%s) contains a invalid number of operands",ins);
				printerrorf(err);
				return FALSE;
				
			}
			
			
			if(findstr(op1,"\"") != -1)
			{
				char err[50];
				sprintf(err," instruction (%s) cannot take constant as first operand",ins);
				printerrorf(err);
				return FALSE;
			}
			
			if(isvar(op1) == FALSE)
			{
				char err[50];
				sprintf(err," instruction (%s) operand 1 contains unknown variable (%s)",ins,op1);
				return FALSE;
			}
			
			varadd1 = getvarindexbyname(op1);
			
			// second operand is a variable
			if(findstr(op2,"\"") != -1)
			{
				
				
				trimquotes(op2);
				// get variable index by data
				getvarindexbydata(op2,varname);	
				varadd2 = getvarindexbyname(varname);
				
			}
			else
			{
				if(isvar(op2) == FALSE)
				{
					char err[50];
					sprintf(err,"instruction (%s) operand 2 contains a unknown variable (%s)",ins,op2);
					printerrorf(err);
					return FALSE;
				}
				
				varadd2 = getvarindexbyname(op2);
			}
			
			itoa(varadd1,vadd1,16);
			itoa(varadd2,vadd2,16);
			
			strcpy(bytecode,opc);
			strcat(bytecode,"!");
			strcat(bytecode,"*");
			strcat(bytecode,vadd1);
			strcat(bytecode,":");
			strcat(bytecode,"*");
			strcat(bytecode,vadd2);
			
			
			return TRUE;
			
			
			
		}
		break;
		
		
		// string algorithms, with only 1 operand (mprint/minput/miline)
	case 0x60:
	case 0x61:
	case 0x62:
	case 0x63:
		{
			int varadd;
			char svaradd[50];
			char svarname[50];
			
			//               not sure why opnum comes up as 2
			if(opnum != 1)
			{
				char err[50];
				sprintf(err," instruction (%s) has a invalid number of operands", ins);
				printerrorf(err);
				return FALSE;
			}
			
			
			if(findstr(op1,"\"") != -1)
			{
				getvarindexbydata(op1,svarname);
				varadd = getvarindexbyname(svarname);
			}
			else
			{
				if(isvar(op1) == FALSE)
				{
					char err[50];
					sprintf(err," instruction (%s) contains a invalid variable name (%s)",ins,op1);
					printerrorf(err);
					return FALSE;
				}
				
				varadd = getvarindexbyname(op1);
			}
			
			itoa(varadd,svaradd,16);
			
			strcpy(bytecode,opc);
			strcat(bytecode,"!");
			strcat(bytecode,"*");
			strcat(bytecode,svaradd);
			strcat(bytecode,":(null)");
			
			return TRUE;
		}
		break;
		
	}
	
	
	return TRUE;
}

