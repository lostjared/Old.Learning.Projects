#ifndef __TOKE_H__
#define __TOKE_H__

#include<iostream>
#include<string>
#include<vector>
#include<fstream>

enum char_code { c_null, c_letter, c_digit, c_quote, c_whitespace,c_eof,c_special,c_err };
enum token_code { t_null, t_int, t_ch, t_string , t_special, t_comment };
enum special_type { st_null, st_op, st_cp, st_g, st_ge, st_l, st_le, st_p, st_pp, st_m, st_mm, st_a, st_aa, st_o, st_oo,
st_po, st_n, st_ne, st_e, st_ee, st_pe, st_me, st_mu, st_mue, st_d, st_de, st_ae, st_oe, st_sc, st_c, st_dot, st_x, st_xe,
st_mod, st_ao, st_ac, st_bo, st_bc, st_pd, st_si, st_so, st_cc

};
extern unsigned char token_map[256];

class text_buffer {
public:
	std::string source;
	inline std::string get_source() { return source; }
	text_buffer() { source = ""; offset = 0; }
	text_buffer(std::string s) { offset = 0; source = s; }
	unsigned char get_ch() { 
		if(offset < source.length())
		return source[offset++]; 
		else
			return 0;
	}
	unsigned char get_i(size_t index) { if(index < source.length() && index >= 0) return source[index]; else return 0; }
	unsigned char get_cur() {
		if(offset < source.length())
			return source[offset];
		return 0;
	}
	size_t get_offset() { return offset; }
	void set_offset(size_t offset) { this->offset = offset; }
protected:
	size_t offset;
};

class file_buffer {
public:
	file_buffer(std::string file_name) {
		read_all(file_name);
	}

	void read_all(std::string file_name) {
		file.open(file_name.c_str(),std::ios::in);
		if(file.is_open() && file.good()) {
			file.seekg(0,std::ios::end);
			size_t len = file.tellg();
			file.seekg(0,std::ios::beg);
			char *buf = new char [ len + 1 ];
			file.read(buf, std::streamsize(len));
			str = buf;
			delete [] buf;
			file.close();
		}
	}

	std::string get_str() {
		return this->str;
	}

protected:
	std::fstream file;
	std::string  str;
};

class mas_token {
public:
	token_code tok;
	special_type stype;
	std::string token_string;
	std::string type_c_str() {
		switch(tok) {
			case t_int:
				return "<font color=\"#BD0000\">Number</font>";
			case t_ch:
				return "<b>Word</b>";
			case t_string:
				return "<font color=\"blue\">String</font>";
			case t_special:
				return "<font color=\"orange\">Symbol</font>";
			case t_comment:
				return "<font color=\"green\">Comment</font>";
		}
		return "";
	}
	std::string type_str() {
		switch(tok) {
			case t_int:
				return "Number";
			case t_ch:
				return "Word";
			case t_special:
				return "Symbol";
			case t_comment:
				return "Comment";
		}
		return "";
	}
	virtual void toke(text_buffer *buff) = 0;
};

extern std::vector<mas_token*> tokens;


class mas_int_token : public mas_token {
public:
	mas_int_token() { tok = t_int;  token_string = ""; }
	virtual void toke(text_buffer *buff) {
		char ch;
		token_string += buff->get_i(buff->get_offset()-1);
		while ( (ch = buff->get_ch())) {
			switch(token_map[ch]) {
				case c_digit:
					token_string += ch;
					break;
				default:
					buff->set_offset(buff->get_offset()-1);
					return;
			}
		}
	}
};

class mas_word_token : public mas_token {
public:
	mas_word_token() { tok = t_ch; token_string = ""; }
	virtual void toke(text_buffer *buff) {
		char ch;
		token_string += buff->get_i(buff->get_offset()-1);
		while ( (ch = buff->get_ch()) ) {
			switch(token_map[ch]) {
				case c_letter:
				case c_digit:
					token_string += ch;
					break;
				default:
					buff->set_offset(buff->get_offset()-1);
					return;
			}
		}
	}
};

class mas_string_token : public mas_token {
public:
	mas_string_token() { tok = t_string; token_string = ""; }
	virtual void toke(text_buffer *buff) {
		char ch, pch = 0;
		token_string += buff->get_i(buff->get_offset()-1);
		
		while ( (ch = buff->get_ch()) ) {
			pch = buff->get_cur();
			token_string += ch;
			if(pch == '\\' && (ch == '\"' || ch == '\''))
				continue;
			else if((ch == '\"' || ch == '\'')) break;
		}

		buff->get_ch();
	}

};

class mas_special_token : public mas_token {
public:
	mas_special_token() { tok = t_special; token_string = ""; }
	
	virtual void toke(text_buffer *buff) {
		char ch;
		ch = buff->get_i(buff->get_offset()-1);
		char pch;
		switch(ch) {
			case '.':
				stype = st_dot;
				token_string += ch;
				return;
			case ':':
				pch = buff->get_cur();
				if(pch == ':') {
					buff->get_ch();
					stype = st_cc;
					token_string += ch;
					token_string += pch;
					return;
				}
				stype = st_c;
				token_string += ch;
				return;
			case ';':
				stype = st_sc;
				token_string += ch;
				return;
			case '=':
				pch = buff->get_cur();
				if(pch == '=') {
					buff->get_ch();
					stype = st_ee;
					token_string += ch;
					token_string += pch;
					return;
				}
				stype = st_e;
				token_string += ch;
				return;
				break;
			case '%':
				stype = st_mod;
				token_string += ch;
				return;
			case '(':
				stype = st_op;
				token_string += ch;
				return;
			case ')':
				stype = st_cp;
				token_string += ch;
				return;
			case '[':
				stype = st_ao;
				token_string += ch;
				return;
			case ']':
				stype = st_ac;
				token_string += ch;
				return;
			case '{':
				stype = st_bo;
				token_string += ch;
				return;
			case '}':
				stype = st_bc;
				token_string += ch;
				return;
			case '#':
				stype = st_pd;
				token_string += ch;
				return;
			case '^':
				pch = buff->get_cur();
				if(pch == '=') {
					buff->get_ch();
					stype = st_xe;
					token_string += ch;
					token_string += pch;
					return;
				}
				stype = st_x;
				token_string += ch;
				return;
				break;
			case '!':
				pch = buff->get_cur();
				if(pch == '=') {
					buff->get_ch();
					stype = st_ne;
					token_string += ch;
					token_string += pch;
					return;
				}
				stype = st_n;
				token_string += ch;
				break;
			case '*':
				pch = buff->get_cur();
				if(pch == '=') {
					buff->get_ch();
					stype = st_mue;
					token_string += ch;
					token_string += pch;
					return;
				}
				stype = st_mu;
				token_string += ch;
				return;
				break;
			case '/':
				pch = buff->get_cur();
				if(pch == '=') {
					buff->get_ch();
					stype = st_de;
					token_string += ch;
					token_string += pch;
					return;
				}
				stype = st_d;
				token_string += ch;
				return;
				break;
			case '-':
				pch = buff->get_cur();
				if(pch == '-') {
					buff->get_ch();
					stype = st_mm;
					token_string += ch;
					token_string += pch;
					return;
				}
				else if(pch == '>') {
					buff->get_ch();
					stype = st_po;
					token_string += ch;
					token_string += pch;
					return;
				} else if(pch == '=') {
					buff->get_ch();
					stype = st_me;
					token_string += ch;
					token_string += pch;
					return;
				}
				stype = st_m;
				token_string += ch;
				return;
				break;
			case '+':
				pch = buff->get_cur();
				if(pch == '+')
				{
					buff->get_ch();
					stype = st_pp;
					token_string += ch;
					token_string += pch;
					return;
				} else if(pch == '=') {
					buff->get_ch();
					stype = st_pe;
					token_string += ch;
					token_string += pch;
					return;
				}
				stype = st_p;
				token_string += ch;
				return;
				break;
			case '&':
				pch = buff->get_cur();
				if(pch == '&') {
					buff->get_ch();
					stype = st_aa;
					token_string += ch;
					token_string += pch;
					return;
				} else if(pch == '=') {
					buff->get_ch();
					stype = st_ae;
					token_string += ch;
					token_string += pch;
					return;
				}
				stype = st_a;
				token_string += ch;
				return;
				break;
			case '|':
				pch = buff->get_cur();
				if(pch == '|') {
					buff->get_ch();
					stype = st_oo;
					token_string += ch;
					token_string += pch;
					return;
				} else if(pch == '=') {
					buff->get_ch();
					stype = st_oe;
					token_string += ch;
					token_string += pch;
					return;
				}


				stype = st_o;
				token_string += ch;
				return;
				break;
			case '>':
			case '<':
				pch = buff->get_cur();
				
				if(ch == '>' && pch == '>') {
					buff->get_ch();
					stype = st_si;
					token_string += ch;
					token_string += pch;
					return;
				}
				
				if(ch == '<' && pch == '<')  {
					buff->get_ch();
					stype = st_so;
					token_string += ch;
					token_string += pch;
					return;
				}
				if(pch == '=') {
					buff->get_ch();
					stype = (ch == '>') ? st_ge : st_le ;
					token_string += ch;
					token_string += pch;
					return;
				}
				stype = (ch == '>') ? st_g : st_l;
				token_string += ch;
				return;
				
				break;
			default:
				token_string += ch;
				return;
		}
	}
};

class mas_comment_token : public mas_token {
public:
	mas_comment_token() { token_string = ""; tok = t_comment; }

	virtual void toke(text_buffer *buff) {
		char ch;
		ch = buff->get_ch();
		switch(ch) {
			case '*':
				while( (ch = buff->get_ch()) ) {
					if(ch == '*' && buff->get_cur() == '/')
						break;
					else
						token_string += ch;
				}
				break;
			case '/':
				while ( (ch = buff->get_ch() ) ) {
					if(ch == '\n')
						break;
					else
						token_string += ch;
				}
				break;
		}
	}

};

class Scanner {
public:
	Scanner();
	Scanner(text_buffer *buff) {
		Scanner();
		Get(buff);
	}
	~Scanner();

	inline void Get(text_buffer *buff) {
		char ch;
		SkipSpace(buff);
		while ( (ch = buff->get_ch()) ) {
			switch(token_map[ch]) {
				case c_digit: {
					mas_int_token *mint_token = new mas_int_token;
					mint_token->toke(buff);
					tokens.push_back(mint_token);
					break;
					}
				case c_letter: {
					mas_word_token *mwrd_token = new mas_word_token;
					mwrd_token->toke(buff);
					tokens.push_back(mwrd_token);
					break;
					}
				case c_quote: {
					mas_string_token *mstr_token = new mas_string_token;
					mstr_token->toke(buff);
					tokens.push_back(mstr_token);
				}
			    break;
				case c_special:
					{
						if((ch == '/' && buff->get_cur() == '*') || (ch == '/' && buff->get_cur() == '/')) {
							mas_comment_token *mc_token = new mas_comment_token;
							mc_token->toke(buff);
							tokens.push_back(mc_token);
							break;
						}

						mas_special_token *ms_token = new mas_special_token;
						ms_token->toke(buff);
						tokens.push_back(ms_token);
					}
					break;
				default:
					continue;
			}
		}
	}

	inline void SkipSpace(text_buffer *buff) {
		if( buff->get_cur() == ' ')
			do {} while ( buff->get_ch() == ' ' );	

	}
	inline void PrintTokens() {

		for(size_t i = 0; i < tokens.size(); i++) {
			std::cout << "(" << i << " : " << tokens[i]->type_str() << " ) ->" << tokens[i]->token_string << "\n";
		}
	}

	inline void OutputHTML(std::ostream &out) {
		size_t i;
		out << "<HTML><TITLE> tokecpp - by jared bruni </TITLE><BODY><PRE>";
		out << " <center>tokecpp results: <br>";
		out << "<TABLE border=1>";
		out << "<TH>Token #<TH> Token <TH> Type <TR>";
		for(i = 0; i < tokens.size(); i++) {
			out << "<TH>" << i << "<TH>" << convertHTML(tokens[i]->token_string) << "<TH>" << tokens[i]->type_c_str() << "<TR>";
		}
		out << "</TABLE></center>";
		out << "</PRE></BODY></HTML>";
	}

	inline std::string convertHTML(std::string str) {
		size_t i;
		std::string final = "";
		for(i = 0; i < str.length(); i++) {
			switch(str[i]) {
				case '<':
					final += "&lt;";
					break;
				case '>':
					final += "&gt;";
					break;
				default:
					final += str[i];
			}
		}
		return final;
	}

protected:


};


#endif