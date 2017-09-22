#include"token.h"


Token_Type Token;
char buffer[256];
int prev = 0, pos = 0;


void start_lex() {
	inputstr = get_input();
	dot = 0;
	input_char = inputstr[dot];
}

void putback() {
	dot = prev;
}

void nexttoken() {

	if(dot >= strlen(inputstr)) {
		buffer[0] = EOF;
		Token.cls = EOF;
		Token.val = 0;
		return;
	}
	skip_whitespace();
	prev = dot;
	int pos = 0;
	buffer[0] = 0;
	
	while(isdigit(input_char)) {
		buffer[pos++] = input_char;
		input_char = inputstr[++dot];
	} 
	buffer[pos] = 0;
	if(strlen(buffer) > 0) { 
		Token.cls = INTEGER;
		Token.val = atoi(buffer);
		return;
	}
	while(input_char >= 'a' && input_char <= 'z') {
		buffer[pos++] = input_char;
		input_char = inputstr[++dot];
	} 
	buffer[pos] = 0;
	if(strlen(buffer) > 0) {
		Token.cls = IDENTIFIER;
		return;
	}
	buffer[0] = input_char;
	buffer[1] = 0;
	Token.cls = atoI(buffer);
	Token.val = 0;
	input_char = inputstr[++dot];
}

void next_tok() {
	nexttoken();
	setIcode(pos++,Token.cls);
}

void skip_whitespace() {
	while(input_char == ' ' || input_char == '\n') {
		input_char = inputstr[++dot];
	}

}

int atoI(const char *source)
{
	int i;
	for(i = 0; tokens[i] != 0; i++) {
		if(strcmp(source,tokens[i]) == 0)
			return i;
	}
	return -1;
}


