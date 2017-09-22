#include "parser.h"


int main(int argc, char *argv[]) {
	if(argc == 2) {
		strcpy(source,argv[1]);
		Parser parser(source);
		start_lex();
		int rtval = parser.Parse();
		printf("Answer to Expression is %d\n compared to %d", rtval,2+2+4*(2+2)-(2*5+(5*5))-5*1+(2*2));
		free(inputstr);
		system("PAUSE");
		return 0;
	}
	printf("Enter  expression example 5+5*(2-2*5)");
	inputstr = (char*) malloc ( sizeof(char) * 256 );

	fgets(inputstr,255,stdin);
	dot = 0;
	input_char = inputstr[dot];
	Parser parser("txt.txt");
	int rtval = parser.Parse();
	printf("Value to the expression is: %d\n", rtval);
	free(inputstr);
	system("PAUSE");
	return 0;
}

void setIcode(int pos, int cls) {
	icode[pos].token = cls;
}
