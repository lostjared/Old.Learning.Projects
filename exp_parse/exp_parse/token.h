#ifndef __TOKEN__H_
#define __TOKEN__H_
#include "input.h"
#include<ctype.h>
#include<string.h>

#define IDENTIFIER 257
#define INTEGER 258
#define ERRONEOUS 259

enum token_type { PLUS, MINUS, DIV, MUL, OP, CP, SC, NOTHING,eof };

static char *tokens[] = { "+", "-", "/", "*", "(", ")", ";",0 };


typedef struct {
	char *file_name;
	int line_num;
	int char_number;
} Position_in_file;

typedef struct {
	int cls,val;
	char *repr;
	Position_in_file pos;
} Token_Type;

extern Token_Type Token;
extern char buffer[256];

extern void start_lex();
extern void skip_whitespace();
extern void nexttoken();
extern void next_tok();
extern int atoI(const char *source);
extern void putback();
extern void setIcode(int pos, int cls);



#endif
