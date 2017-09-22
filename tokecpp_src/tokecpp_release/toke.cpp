#include "toke.h"

unsigned char token_map[256];
std::vector<mas_token*> tokens;

Scanner::Scanner() {
	unsigned char c;
	for(c = 0; c <= 127; c++) token_map[c] = c_err;
	for(c = 'a'; c <= 'z'; c++) token_map[c] = c_letter;
	for(c = 'A'; c <= 'Z'; c++) token_map[c] = c_letter;
	for(c = '0'; c <= '9'; c++) token_map[c] = c_digit;
	token_map['_'] = c_letter;
	token_map['+'] = token_map['-'] = token_map['*'] = token_map['/'] = c_special;
	token_map['&'] = token_map['|'] = token_map['^'] = token_map['!'] = c_special;
	token_map[';'] = token_map[':'] = token_map['{'] = token_map['}'] = c_special;
	token_map['['] = token_map[']'] = token_map[','] = token_map['.'] = c_special;
	token_map['('] = token_map[')'] = token_map['>'] = token_map['<'] = c_special;
	token_map['='] = token_map['!'] = token_map['%'] = token_map['#'] = c_special;
	token_map['\"'] = token_map['\''] = c_quote;	
}


Scanner::~Scanner() {



}