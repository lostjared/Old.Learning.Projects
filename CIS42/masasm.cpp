// masasm - simple 8 bit assembler / 8 bit assembly langauge
// for the 8 bit CPU emulator
// written by jared bruni
// mailme: master@lostsidedead.com

// for cosumnes river college
// thanks to my proffessor (sue palms)
// for all her help!


#include "thehead.h"


void assemble(char* sourcefile);// begin the proccess
void startasm(char* data);// straightd ata
void breakdown(char* tdata);// trimed data
void procline(int line, char* data);// proccess line
void transline(int line,char* data); // translate line
void stopcmp();
 


// main (entry) point
void main(int argc,char** argv)
{
	if(argc == 1)
	{
		cout << "error: invalid command line parameters"<< endl;
		cout <<"correct format is the following" << endl;
		cout << "masasmx source.asm" << endl;
		system("pause");
		return;
	}

	if(findstr(argv[1],".") == -1)
	{
		cout << "fatal error: source file missing file extension" << endl;
		system("pause");
		return;
	}

	if(isfile(argv[1]) == false)
	{
		cout << "fatal error: could not find the file" << argv[1] << endl;
		system("pause");
		return;
	}
		

	assemble(argv[1]);

	cout << "process stoped with  (" << err_count << ") fatal errors" << endl;

	// no errors
	if(err_count == 0)
	{
		char ifname[250];

		getexename(argv[1],ifname);
		cout << "was succesful emu binary code (in hex)  named: "<< ifname << endl;
		//cout << fdata.get();
		strsavefile(ifname,fdata.get());
	}


	system("pause");
}


// begin the assemble process
void assemble(char* sourcefile)
{
	// first check if files found
	// if yes
	cout << "now assembling: " << sourcefile << endl;

	char* cmpbuff;
	cmpbuff = new char[getfilestringlength(sourcefile)+10];
	strloadfile(sourcefile,cmpbuff);
	MasterString buf;
	buf = cmpbuff;
	delete [] cmpbuff;
	cmpbuff = 0;
	startasm(buf.get());

}

// start the actual translation
void startasm(char* data)
{
	char* tdata = new char[strlen(data)+50];

	if(findstr(tdata,";") == -1)
	{
		MasterString m;
		m = "; using masasmx";
		m += data;
		asmtrim(data,tdata);
		breakdown(tdata);
	}
	else
	{

	asmtrim(data,tdata);
	breakdown(tdata);

	}


 
	delete [] tdata;
	tdata = 0;
}

// break down
void breakdown(char* tdata)
{

 	if(findstr(tdata,"halt") == -1)
	{
		err_count ++ ;

		cout << "fatal error: application requries a halt instruction" << endl;
		return;
	}


	strcat(tdata,"\n");
	MasCharList mlist;
	mlist.BuildList(tdata);

	for(int i = 0; i < mlist.GetLength(); i++)
	{
 
		procline(i,mlist.list[i].get());
	}
}

// proccess line
void procline(int line,char* data)
{
	// check if it is a valid instruction
	if(isline(data))
	{
		// yes it is a line
		if(isinc(data))
		{
			// yes valid instruction
			transline(line,data);
		}
		else
		{
			// NO invalid instruction
			disperror(line," invalid instruction");
			return;
		}

	}
}

// translate line
void transline(int line,char* data)
{

 
	// find out what instruction it is, and translate it
	int curop;

	curop = ginc(data); // get the opcode

	char hexop[2];
	itoa(curop,hexop,16);
	char hexstring[10];// contains 4 digits

	strcpy(hexstring,hexop); // add the opcode

	char op1[100]; // large incase of typ0's
	char op2[100]; // large incase of typ0's

// translate the operands
	switch(curop)// current
	{
	case 1:// loadm register,xy // register,hex form of instruction
	case 2: // load register,const
	case 3: // store register,xy
		{
			if(checkopr(data))
			{
				getoprands(data,op1,op2);

				if(ireg(op1))
				{
					int regval;

					regval = greg(op1);

					char oreg[10];
					itoa(regval,oreg,16);
					strcat(hexstring,oreg);// add the register

				}
				else
				{
					disperror(line," the first operand must be a register");
					stopcmp();
					return;
				}

				// get the second operands, hex value

				if(ishex(op2))
				{
					int value;
					value = hextoint(op2);

					if(value > 255)
					{
						disperror(line," operand size conflict, value to large for register");
						stopcmp();
						return;
					}

					if(value <= 15)
					{
						strcat(hexstring,"0");
					}

					char hval[10];
					itoa(value,hval,16);
					strcat(hexstring,hval);

				}
				else
				{
					disperror(line," the second operand must contain a hex value");
					stopcmp();
					return;
				}

			}
			else
			{
				disperror(line," invalid number of operands on instruction");
				stopcmp();
				return;
			}
		}

		break;


	case 4:// register,register form of instruction
	case 5:
	case 6:
	case 7:
	case 8:
	case 11:
	case 12:
	case 13:
	case 14:
		{

		strcat(hexstring,"0"); // nullify first operand

		if(checkopr(data))
		{
			getoprands(data,op1,op2);
			// now we got the operands, do the shit on it
			if(ireg(op1))
			{
				int regval;
				regval = greg(op1);
				char oreg[10];
				itoa(regval,oreg,16);
				strcat(hexstring,oreg); // successful lets add to string
			}
			else
			{
				disperror(line,"the first operand must be a register");
				stopcmp();
				return;
			}

			if(ireg(op2))
			{
				int regval;
				regval = greg(op2);
				char oreg[10];
				itoa(regval,oreg,16);
				strcat(hexstring,oreg); // successful lets add to string
			}
			else
			{
				disperror(line,"the second operand must be a register");
				stopcmp();
				return;
			}
		}
		else
		{
			disperror(line,"  (fatal) invalid number of operands on instruction");
			stopcmp(); // fatal
			return;
		}
		}
		break;
	case 9://inc regster (1 register)
	case 10:// dec register
		{
			if(findstr(data,",") != -1)
			{
				disperror(line," instruction only takes a single operand, no comma to seperate");
				stopcmp();
				return;
			}

			lcase(data);

		 
			if(greg(data) != -1)
			{
				lcase(data);
				int rval;
				rval = greg(data);

				char opr[25];
				itoa(rval,opr,16);

				strcat(hexstring,"00");
				strcat(hexstring,opr);

			}
			else
			{
				disperror(line," single operand instruction, must contain register");
				stopcmp();
				return;
			}
		}
		break;

	case 15:// halt 0

		if(checknopr(data))
		{
			// correct
			strcat(hexstring,"000"); // the arguments
		}
		else
		{
			disperror(line,"  (fatal) invalid number of operands on instruction");
			stopcmp();
			return;
		}

		break;
	}

	addiline(hexstring);
}

void stopcmp()
{
//	proc_go = false;
//	exit(0);
}

