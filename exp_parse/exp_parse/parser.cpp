// theres nothing you can make that cant be made 
// thanks to 1 for the help


#include "parser.h"

int total = 0;
char buff[256];
int of_ = 0;

Parser::Parser(const char *source) {
	strcpy(this->filename, source);
}

int Parser::Parse() {
	bend.exec();
	return bend.getrtval();
}
