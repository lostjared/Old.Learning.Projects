#ifndef __PARSER_H__
#define __PARSER_H__

#include "input.h"
#include "token.h"
#include "icode.h"


class Parser {

	char filename[256];
	BackEnd bend;
public:
	Parser(const char *source);

	int Parse();

};

#endif
