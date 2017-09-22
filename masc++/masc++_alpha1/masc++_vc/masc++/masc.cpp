/* NO its NOT RANDOM the way I format my CODE */

#include "masc.h"
#include<sstream>
#include<stdarg.h>



namespace masc {

	using std::cout;
	using std::endl;

	char *mysprintf(char *src, const char *sptr, ...) {
		va_list l;
		char *p, *sval = src, *ptr;
		va_start(l,sptr);
		for(p = const_cast<char*>(sptr); *p; p++) {
			if(*p != '%') {
				*sval = *p;
				sval++;
				continue;
			}
			else {
				switch(*++p) {
					case 'd': {
						int ival = va_arg(l,int);
						std::ostringstream s;
						s << ival;
						std::string d = s.str();
						for(size_t i = 0; i < d.length(); i++)
							*sval = d[i], sval++;
							  }
							  break;
					case 's':
						for(ptr = va_arg(l, char*); *ptr; ptr++)
							*sval = *ptr, sval++; 
						break;
					case 'f':
						{
							double dval = va_arg(l,double);
							std::ostringstream s;
							s << dval;
							std::string d = s.str();
							for(size_t i = 0; i < d.length(); i++)
								*sval = d[i], sval++;
						}
						break;
					default:
						*sval = *p;
						sval++;
						break;
				}
			}

		}
		*sval = 0;
		return src;
	}

	int myprintf(const char *src, ...) {
		va_list l;
		char *p,*ptr;
		va_start(l,src);
		for(p = const_cast<char*>(src); *p; p++) {
			if(*p != '%') {
				putchar(*p);
				continue;
			}
			else {
				switch(*++p) {
					case 'd': {
						int ival = va_arg(l,int);
						std::cout << ival;
						break;
							  }
					case 's':
						for(ptr = va_arg(l, char*); *ptr; ptr++)
							putchar(*ptr);
						break;
					case 'f':
						{
							double dval = va_arg(l,double);
							std::cout << dval;
						}
						break;
					default:
						putchar(*p);
						break;
				}
			}

		}
		return 0;
	}

	void Symbol_Table::Set(int type, std::string val, std::string name) {
		vars[name].name = name;
		vars[name].val = val;
		vars[name].type = type;
	}

	symb &Symbol_Table::Get(std::string name) {
		return vars[name];
	}

	void Symbol_Table::DebugPrint() const {
		std::map<std::string,symb>::const_iterator i;
		for(i = vars.begin(); i != vars.end(); i++)
			std::cout << "Variable name: " << i->first << " Variable value: " << i->second.val << '\n';
	}

	symb &Symbol_Table::operator() ( size_t pos ) {
		std::list<symb>::iterator i = st.begin();
		for(size_t z = 0; z < pos; z++)
			i++;
		return *i;
	}

	symb Symbol_Table::Pop() {
		if(!st.empty()) {
			symb p = st.back();
			st.pop_back();
			return p;
		}
		return symb();
	}

	void Symbol_Table::operator+=(const symb &s) {
		st.push_back(s);
	}

	symb Symbol_Table::operator--() {
		return Pop();
	}

	void Symbol_Table::PopAll() {
		while(!st.empty())
			st.pop_back();
	}

	void Symbol_Table::Push(symb &s) {
		st.push_back(s);
	}


	Parser::Parser(std::string s) : MFile(s) , err(0) , current_line(0) {
		if(opened == true) {
			GetLine();
			Begin();
		}
		else {
			current_line = 0;
			ErrorMsg("Couldnt open file (%s)\n", s.c_str());
			return;
		}

	}

	void Parser::StartParse(std::string str) {
		opened = false;
		Open(str);
		if(opened == true) {
			GetLine();
			Begin();
		}
		else {
			current_line = 0;
			ErrorMsg("Couldnt open file (%s)\n", str.c_str());
			return;
		}
	}

	void Parser::Begin() {
		Parse(cur_line);
		if(!GetLine())
			Begin();
	}

	void Parser::Parse(std::string str) {
		std::string::iterator p;
		std::string cur_tok = "";
		cur.line_num = curline;
		cur.source_file = file_name;
		cur.token = "";
				
		str += "\n";
		if(str.find("insert") != -1 && str.find('\"') != -1 && str.find(";") != -1) {
			std::string insert_file;
			insert_file = str.substr(str.find('\"')+1, str.length());
			if(insert_file.find('\"') != -1)
				insert_file =  insert_file.substr(0, insert_file.find('\"'));
			insert_vec.push_back(insert_file);
		}
		for(p = str.begin(); p != str.end(); p++) {

			if(*p == '/')
				return;

			if(isalpha(*p)) {
				cur_tok = "";
				while(*p != '\n' && (isalpha(*p) || isdigit(*p) || *p == '_'  || *p == '$' || *p == '&' || *p == '#' || *p == '.' || *p == '[' || *p == ']') && p != str.end()) {
					cur_tok += *p;
					p++;
				}
				if(*p != ':')
					cur.type = IDENTIFIER;
				else
					cur.type = CODELABEL;
				cur.token = cur_tok;
				tok_vec.push_back(cur);
				cur_tok = "";
			} 
			else if(isdigit(*p)) {
				cur_tok = "";
				while((isdigit(*p) || *p == '.') && p != str.end()) {
					cur_tok += *p;
					p++;
				}
				cur.token = cur_tok;
				cur.type = DIGIT;
				tok_vec.push_back(cur);
			}
			else if(*p == '\"') {
				p++;
				while(*p != '\"' && p != str.end()) {
					if(*p != '\\') {

						cur_tok += *p;
						p++;

					}
					else 
						if(*p == '\\')
						{
							p++;
							if(*p == '\"')
								cur_tok += *p, p++;
							else if(*p == 'n')
								cur_tok += '\n', p++;
						}

				}

				cur.token = cur_tok;
				cur.type = STRING;
				tok_vec.push_back(cur);
				cur_tok = "";
			}

			switch(*p) {
				case '{':
				case '}':
				case ';':
				case ',':
				case '=':
				case '<':
				case '~':
				case '\'':
				case '@':
				case '!':
				case '#':
				case '$':
				case '%':
				case '^':
				case '&':
				case '*':
				case '(':
				case ')':
				case '-':
				case '+':
				case '/':
				case '\\':
				case '.':
				case '>':
				case ':':
					if(*(p+1) == '<') {
						p++;
					}
					cur.token = *p;
					cur.type = *p; 
					tok_vec.push_back(cur);
					cur_tok = "";
					break;
			}
		}
	}

	void Parser::DebugTokens() {
		for(unsigned int i = 0; i < tok_vec.size(); i++)
			cout << "token (type:" << int(tok_vec[i].type) << ") " << tok_vec[i].token << endl;
	}

	void Parser::ErrorMsg(const char *str, ...) {
		va_list l;
		char error_msg[5000];
		va_start(l,str);
		vsprintf(const_cast<char*>(error_msg),str,l);
		va_end(l);
		cout << "**** error#: " << (++err) << " " << error_msg << " \n\t->line(" << current_line << ").file(" << current_file << ") " << endl;
	}

	bool Parser::LexAnayalize() {

		int masteronLucy = 0;
		std::string obj_name = "";
			
		for(unsigned int z = 0; z < tok_vec.size(); z++) {
			current_line = tok_vec[z].line_num;
			current_file = tok_vec[z].source_file;
			int vid = IdentToValue(tok_vec[z].token);

			if(vid == TOK_USES) {
				std::map<std::string,masc::External_Callback>::iterator itz;
				for(itz = GetBend()->callb.begin(); itz != GetBend()->callb.end(); itz++) {
					if(itz->second.imp == true && itz->second.isdef == false) {
						std::map<std::string,std::string>::iterator it;
						bool found_it = false;
						for(it = GetBend()->obj.begin(); it != GetBend()->obj.end(); it++) {
							if(GetBend()->Find(it->second + "." + itz->second.other_name) != 0 || GetBend()->Find("master." + itz->second.other_name) != 0) {
								found_it = true;
								break;
							}

						}
						if(found_it == false) {
							ErrorMsg(" (fatal) procedure (%s) not implemented yet is defined to be so ", itz->second.name.c_str());
							return false;
						}
					}
				}

			}
			else if(tok_vec[z].type == '{' && pBounds(z-4)) {
				int zid = IdentToValue(tok_vec[z-1].token), zzid = IdentToValue(tok_vec[z-2].token);
				if(zid == -1 && zzid != TOK_PROC && zzid != TOK_EXTERN && tok_vec[z-4].type != '}' && GetBend()->obj[tok_vec[z-1].token] == "") {
					ErrorMsg("Invalid object/uses/procedure name on opening block you put (%s)", tok_vec[z-1].token.c_str());
					z++;
					continue;
				}
			}
			else if(pBounds(z-1) && (vid == TOK_USES || vid == TOK_BEGIN || vid == TOK_END || vid == TOK_PROC || vid == TOK_MAS || vid == TOK_MAIN) && pBounds(z-1)) {
			   int rid = IdentToValue(tok_vec[z-1].token);
				if(rid == -1 && tok_vec[z-1].type != ';' && tok_vec[z-1].type != '}') {
					ErrorMsg("Error bad value before keyword (%s) i found (%s)", tok_array[vid], tok_vec[z-1].token.c_str());
					z++;
					continue;
				} 
				else {
					if((vid == TOK_MAS || vid == TOK_MAIN) && pBounds(z+1) && tok_vec[z+1].type == IDENTIFIER) {
						obj_name = tok_vec[z+1].token;
						continue;
					}
				}

			}
			else if(vid == TOK_IMPLEMENT) {
				if(pBounds(++z) && (vid = IdentToValue(tok_vec[z].token)) == TOK_PROC && pBounds(++z) && tok_vec[z].type == IDENTIFIER && pBounds(++z) && tok_vec[z].type == ';') {
					if(pBounds(z-1) && GetBend()->callb[obj_name + "." + tok_vec[z-1].token].imp == false) {
						ErrorMsg("implemented procedure is missing from object (%s)" ,"");
						continue;
					}

				}
				else	{

					ErrorMsg(" there is a problem with the implement keyword probaly you forgot a semi-colon,proc keyword, or name ");

				}

				z++;

			}

		}
		current_line = 0;
		int ID = 0;

		for(unsigned int i = 0;  i < tok_vec.size(); i++) {
			current_line = tok_vec[i].line_num;
			current_file = tok_vec[i].source_file;
			switch(tok_vec[i].type) {
				case IDENTIFIER:
					{
						int id = IdentToValue(tok_vec[i].token);

						switch(id) 
						{
						case TOK_USES:
							{
								if(pBounds(i+3) && (tok_vec[i+1].type == '{')) {
									i+=2;
									while(pBounds(i) && tok_vec[i].type != '}') {
										if(pBounds(i) && tok_vec[i].type != ';' && GetBend()->obj[tok_vec[i].token] != tok_vec[i].token) {
											ErrorMsg("Error uses block is trying to inhert from a unknown object (%s)\n", tok_vec[i].token.c_str());
											i++;
											continue;
										}
										i++;
									}
								}

							}
							break;
						case TOK_INSERT:
							{
								i++;
								if(pBounds(i)) {
									std::fstream f;
									f.open(tok_vec[i].token.c_str(), std::ios::in);
									if(f.is_open())
									{  f.close(); continue; }
									else
										f.close(), ErrorMsg("insert not including a file instead I found %s", tok_vec[i].token.c_str());
									continue;
								}
							}
							break;
						case TOK_MAS: 
						case TOK_MAIN:
							{
								if(id == TOK_MAIN) {
									masteronLucy++;
									if(masteronLucy >= 2) {
										ErrorMsg("(fatal) more than one main object cannot continue try only putting one master object in your script.");
										return false;
									}
								}
								if(pBounds(++i)) {
									int tid = IdentToValue(tok_vec[i].token);
									if(tid >= TOK_INSERT && tid <= VAR_FLOAT) {
										ErrorMsg("mas(ter) keyword found another keyword (%s) instead of name of the object.", tok_vec[i].token.c_str());
										continue;
									}
									else if(tok_vec[i].type == DIGIT || tok_vec[i].type == STRING || (tok_vec[i].type >= '!' && tok_vec[i].type <= '@') || (tok_vec[i].type >= '{' && tok_vec[i].type <= '~')) {
										ErrorMsg("mas(ter) keyword found a digit,string,or special character instead of identifier (%s)", tok_vec[i].token.c_str());
										continue;
									}
								}
								ID++;
							}
							break;
						case TOK_VAR:
							{
								ID++;
								i++;
								if(pBounds(i) && pBounds(i+1)) {
									if(tok_vec[i].type != '{') {
										ErrorMsg("(fatal) variable code block missing opening brace instead I found (%s) ", tok_vec[i].token.c_str());
										return false;
									}
								}

								while(pBounds(++i) && tok_vec[i].type != '}') {
									current_line = tok_vec[i].line_num;
									current_file = tok_vec[i].source_file;
									int zid = IdentToValue(tok_vec[i].token);
									if(zid >= TOK_USES && zid <= TOK_EXTERN) {
										ErrorMsg("(fatal) found keyword (%s) instead of variable decleration (maybe you forgot } or \")", tok_vec[i].token.c_str());
										return false;
									}

									if(zid >= VAR_INTEGER && zid <= VAR_FLOAT) {
										if(pBounds(++i)) {
											if(tok_vec[i].type != IDENTIFIER) {
												ErrorMsg(" found a string,digit,or special character (%s) instead of a identifier for variable name!", tok_vec[i].token.c_str());
												continue;
											}
											else if(pBounds(++i) && tok_vec[i].type != '=' && tok_vec[i].type != ';') {
												ErrorMsg(" found %s instead of equal sign or semi-colon.", tok_vec[i].token.c_str());
												continue;

											}
											else if(pBounds(i) && tok_vec[i].type == '=' && pBounds(++i) && tok_vec[i].type != STRING && tok_vec[i].type != DIGIT) {
												ErrorMsg(" looking for string or digit for varaible decleration initilzation instead i found (%s) ", tok_vec[i].token.c_str());
												continue;
											}
											else if(pBounds(i) && (zid == VAR_INTEGER || zid == VAR_FLOAT) && tok_vec[i].type == STRING) {
												ErrorMsg(" numeric variable decleration contains a string (%s)", tok_vec[i].token.c_str());
												continue;
											}
											else if(pBounds(i) && (zid == VAR_STRING) && tok_vec[i].type == DIGIT) {
												ErrorMsg(" string variable decleration contains numeric values (%s)", tok_vec[i].token.c_str());
												continue;
											}
										}
									}
									else if(GetBend()->symbols.vars[tok_vec[i].token].name == "" && tok_vec[i].type != ',' && tok_vec[i].type != ';') {
										ErrorMsg("Error invalid variable decleration! (%s)", tok_vec[i].token.c_str());
										continue;
									}
									
								}
								if(tok_vec[i].type == '}') 
									continue;
								else {
									ErrorMsg("(fatal) variable code block missing closing brace !" );
									return false;
								}
							}
							break;
						case TOK_EXTERN:
						case TOK_BEGIN:
						case TOK_END:
						case TOK_PROC:
							{
								ID++;


								if(id == TOK_EXTERN && pBounds(i+2) && tok_vec[i+1].type != IDENTIFIER && tok_vec[i+2].type != ';') {
									ErrorMsg("external function (c++) call dosent have a name, or is missing terminating semi-colon");
									i+=2;
									continue;
								}
								if(id == TOK_BEGIN && pBounds(i+1) && tok_vec[i+1].type != '{') {
									ErrorMsg("looking for { on begin statement instead i found %s", tok_vec[i+1].token.c_str());
									continue;

								}
								
								if(id == TOK_END && pBounds(i+1) && tok_vec[i+1].type != '{') {
									ErrorMsg("looking for { on end statement instead i found %s", tok_vec[i+1].token.c_str());
									continue;

								}

								if(id == TOK_PROC && pBounds(i+2) && (tok_vec[i+2].type != '{' && tok_vec[i+2].type != ';') ) {
									ErrorMsg("looking for (normal) { or (extern) ; on procedure statement instead i found (%s)", tok_vec[i+2].token.c_str());
									continue;
								}

								if(id == TOK_PROC && pBounds(++i) && tok_vec[i].type != IDENTIFIER) {
									ErrorMsg(" procedure has string or digit or symbol (%s) as a name", tok_vec[i].token.c_str());
									continue;
								}

								i ++;
								while(pBounds(++i) && (tok_vec[i].type != '}')) {
									int prev_i = i;
									current_line = tok_vec[i].line_num;
									current_file = tok_vec[i].source_file;
									int qid = IdentToValue(tok_vec[i].token);
									if(qid == -1 && id != TOK_EXTERN && tok_vec[i].type == IDENTIFIER && GetBend()->symbols.vars[tok_vec[i].token].name == "" && GetBend()->callb[tok_vec[i].token].name == "" && GetBend()->labels[tok_vec[i].token].label_name == "" && GetBend()->Find(tok_vec[i].token) == 0) {
										ErrorMsg("Invalid instruction (%s)", tok_vec[i].token.c_str());
										continue;
									}
									if(qid >= TOK_MOV && qid <= TOK_PRINT) {

										if(pBounds(i-1) && tok_vec[i-1].type != ';' && tok_vec[i-1].type != '{' && tok_vec[i-1].type != ':') {
											ErrorMsg(" Error should have found semi-colon instead found (%s) ", tok_vec[i-1].token.c_str());
											continue;
										}
										

										switch(qid) {
										case TOK_MOV: 
										case TOK_CMP:
										case TOK_ADD:
										case TOK_SUB:
										case TOK_MUL:
										case TOK_DIV:
										case TOK_OR:
										case TOK_XOR:
										case TOK_AND:
											{

												if(pBounds(++i) && tok_vec[i].type != IDENTIFIER) {
													ErrorMsg(" looking for variable name on (%s) instruction instead i found (%s)", tok_array[qid], tok_vec[i].token.c_str());
													continue;
												}
												else if(pBounds(i) && tok_vec[i].type == IDENTIFIER && GetBend()->symbols.vars[tok_vec[i].token].name == "") {
													ErrorMsg(" looking for variable name on (%s) instruction instead i found (%s)", tok_array[qid], tok_vec[i].token.c_str());
													continue;
												}
												else if(pBounds(i+2) && tok_vec[i+2].type == IDENTIFIER && GetBend()->symbols.vars[tok_vec[i].token].name == "") {
													
													ErrorMsg(" expected variable or constant on (%s) instruction operand 2 instead i found (%s)", tok_array[qid], tok_vec[i].token.c_str());
													continue;

												}
												else if(pBounds(++i) && tok_vec[i].type != ',') {
													ErrorMsg(" looking for comma to seperate (%s) instruction instead i found (%s)", tok_array[qid],tok_vec[i].token.c_str());
													continue;

												}
												else if(pBounds(++i) && tok_vec[i].type != IDENTIFIER && tok_vec[i].type != STRING && tok_vec[i].type != DIGIT) {
													ErrorMsg(" looking for variable or constant on (%s) instruction instead i found (%s)", tok_array[qid], tok_vec[i].token.c_str());
													continue;
												}
												
											}
											break;
										case TOK_INC:
										case TOK_DEC:
										case TOK_NOT:
										case TOK_JMP:
										case TOK_JNE:
										case TOK_JE:
										case TOK_JL:
										case TOK_JG:
										case TOK_JGE:
										case TOK_JLE:
										case TOK_POP:
											{
												if((!(qid >= TOK_JMP && qid <= TOK_JGE) || qid == TOK_POP) && pBounds(++i) && tok_vec[i].type != IDENTIFIER) {
													ErrorMsg(" looking for variable name on (%s)  instead I found (%s)" , tok_array[qid], tok_vec[i].token.c_str());
													continue;
												}
												else if((!(qid >= TOK_JMP && qid <= TOK_JGE) || qid == TOK_POP) && pBounds(i) && tok_vec[i].type == IDENTIFIER && GetBend()->symbols.vars[tok_vec[i].token].name == "") {
													ErrorMsg(" looking for variable name on (%s) instead I found (%s)", tok_array[qid], tok_vec[i].token.c_str());
													continue;
												}
												else if(qid >= TOK_JMP && qid <= TOK_JGE && pBounds(++i) && tok_vec[i].type != IDENTIFIER ) {
													ErrorMsg(" looking for code label to (%s) to instead I found which might not be a valid label (%s)", tok_array[qid],tok_vec[i].token.c_str());
													continue;
												}
												else if(qid >= TOK_JMP && qid <= TOK_JGE && pBounds(i) && tok_vec[i].type == IDENTIFIER && GetBend()->labels[tok_vec[i].token].label_name == "") {
													ErrorMsg(" couldnt find label (%s) on instruction (%s) ", tok_vec[i].token.c_str(),tok_array[qid]);
													continue;
												}
												
											}
											break;
										case TOK_CALL:
											{
												if(pBounds(++i) && tok_vec[i].type != IDENTIFIER || (tok_vec[i].type == IDENTIFIER && GetBend()->Find(tok_vec[i].token) == 0 && GetBend()->callb[tok_vec[i].token].name == "")) {
													ErrorMsg("call instruction excpets a valid procedure or external C++ function instead i found (%s)", tok_vec[i].token.c_str());
													continue;
												}

											}
											break;
										case TOK_PRINT:
										case TOK_SCAT:
											{

												if(qid == TOK_PRINT && pBounds(++i) && tok_vec[i].type == '<') {

													if(pBounds(i+1) && tok_vec[i+1].type == ';') {
														ErrorMsg("stream terminated with semi-colon before any data was passed you put (%s)", tok_vec[i+1].token.c_str());
														continue;
													}
													while(pBounds(++i) && tok_vec[i].type != ';') {
														if(tok_vec[i].type != STRING && tok_vec[i].type != DIGIT && tok_vec[i].type != '<' && GetBend()->symbols.vars[tok_vec[i].token].name == "") {
															ErrorMsg("on print instruction requires string/digit/or stream operator you put (%s)", tok_vec[i].token.c_str());
															continue;
														}
														else if(pBounds(i+1) && tok_vec[i+1].type == '<' && pBounds(i+2) && tok_vec[i+2].type != STRING && tok_vec[i+2].type != DIGIT && GetBend()->symbols.vars[tok_vec[i+2].token].name == "") {
															ErrorMsg(" on print instruction stream operator requires r-value ( a variable on the right hand side ) of the stream operator you put (%s)" , tok_vec[i+2].token.c_str());
															i+=2;
															continue;
														}
														
													}
												}
												else if(qid == TOK_PRINT && pBounds(i) && (tok_vec[i].type != STRING && tok_vec[i].type != DIGIT) && GetBend()->symbols.vars[tok_vec[i].token].name == "") {
													ErrorMsg("print instruction requires variable/string/digit or stream operator you put (%s)", tok_vec[i].token.c_str());
													continue;
												}
												else if(qid == TOK_SCAT && pBounds(++i) && (GetBend()->symbols.vars[tok_vec[i].token].name == "")) {
													ErrorMsg(" on scat stream , requires variable for first operand you put (%s)", tok_vec[i].token.c_str());
													continue;
												}
												else if(qid == TOK_SCAT && pBounds(++i) && tok_vec[i].type != '<') {
													ErrorMsg(" on scat stream, requires stream operator for second operand. you put (%s)", tok_vec[i].token.c_str());
													continue;
												}
												else if(qid == TOK_SCAT && pBounds(i)) {
													while(pBounds(++i) && tok_vec[i].type != ';') {
														if(tok_vec[i].type != STRING && tok_vec[i].type != DIGIT && tok_vec[i].type != '<' && GetBend()->symbols.vars[tok_vec[i].token].name == "") {
															ErrorMsg("on scat stream requires string/digit/or stream operator you put (%s)", tok_vec[i].token.c_str());
															continue;
														}
													}
												}

											}
											break;
										}

										if(pBounds(i+1) && tok_vec[i+1].type == ';') i++;
									}
									else if(id != TOK_EXTERN && qid == TOK_PROC || qid == TOK_BEGIN || qid == TOK_END) {
										ErrorMsg("nested procedures / blocks not allowed I found (%s) ", tok_vec[i].token.c_str());
										continue;
									}

								}

								if(tok_vec[i].type != '}') {
									ErrorMsg(" code block is missing closing brace } ");
									continue;
								}

							}
							break;
							
						default:
							{


							}
						}


					}
					break;
					
			}
		}
		if(err == 0 && ID >= 4) // make sure its a valid program before execution.. 
			                    //this can be disabled for speed but its not advised
		return true;
		return false;
	}

	void BackEnd::Convert() {
		for(size_t z = 0;  z < p->insert_vec.size(); z++)
		{
			p->StartParse(p->insert_vec[z]);
		}

		if(!p->insert_vec.empty()) p->insert_vec.clear();

		std::string current_proc = ""; 
		for(size_t i = 0; i < p->tok_vec.size();i++) {
			switch(p->tok_vec[i].type) {

				case IDENTIFIER: 
					{
						int id = IdentToValue(p->tok_vec[i].token);
						if(id != -1) {
							switch(id) 
							{
							case VAR_INTEGER:
								i++;
								if(Bounds(i)) {
									if(Bounds(i+1)) {
										if(p->tok_vec[i].token.find('[') != -1 && p->tok_vec[i].token.find(']') != -1) {
											std::string num = p->tok_vec[i].token.substr(p->tok_vec[i].token.find('[')+1, p->tok_vec[i].token.find(']')-2);
											std::string name = p->tok_vec[i].token.substr(0,p->tok_vec[i].token.find('['));

											for(size_t p = 0; p < size_t(atoi(num.c_str())); p++) {
												std::ostringstream s;
												s << current_obj + "." + name << "[" << int(p) << "]";
												symbols.Set(VAR_INTEGER,"0",s.str());
											}
										}
										else
											if(p->tok_vec[i+1].type == '=') {
												if(Bounds(i+2)) 
													symbols.Set(VAR_INTEGER,p->tok_vec[i+2].token,current_obj + "." + p->tok_vec[i].token);
											}
											else {
												symbols.Set(VAR_INTEGER,"0", current_obj + "." + p->tok_vec[i].token);
											}
									}
								}

								break;
							case VAR_STRING:
								i++;
								if(Bounds(i)) {
									if(Bounds(i+1)) {
										if(p->tok_vec[i].token.find('[') != -1 && p->tok_vec[i].token.find(']') != -1) {
											std::string num = p->tok_vec[i].token.substr(p->tok_vec[i].token.find('[')+1, p->tok_vec[i].token.find(']')-2);
											std::string name = p->tok_vec[i].token.substr(0,p->tok_vec[i].token.find('['));

											for(size_t p = 0; p < size_t(atoi(num.c_str())); p++) {
												std::ostringstream s;
												s << current_obj + "." +name << "[" << int(p) << "]";
												symbols.Set(VAR_STRING,"",s.str());
											}
										}
										else
											if(p->tok_vec[i+1].type == '=') {
												if(Bounds(i+2))
													symbols.Set(VAR_STRING,p->tok_vec[i+2].token,current_obj + "." + p->tok_vec[i].token);
											}
											else {
												symbols.Set(VAR_STRING,"", current_obj + "." + p->tok_vec[i].token);
											}
									}
								}
								break;
							case VAR_FLOAT:
								i++;
								if(Bounds(i)) {
									if(Bounds(i+1)) {
										if(p->tok_vec[i].token.find('[') != -1 && p->tok_vec[i].token.find(']') != -1) {
											std::string num = p->tok_vec[i].token.substr(p->tok_vec[i].token.find('[')+1, p->tok_vec[i].token.find(']')-2);
											std::string name = p->tok_vec[i].token.substr(0,p->tok_vec[i].token.find('['));

											for(size_t p = 0; p < size_t(atoi(num.c_str())); p++) {
												std::ostringstream s;
												s << current_obj + "." + name << "[" << int(p) << "]";
												symbols.Set(VAR_FLOAT,"0.0",s.str());
											}
										}
										else if(p->tok_vec[i+1].type == '=') {
											if(Bounds(i+2))
												symbols.Set(VAR_FLOAT,p->tok_vec[i+2].token,current_obj + "." + p->tok_vec[i].token);
										}
										else {
											symbols.Set(VAR_FLOAT,"0.0", current_obj + "." + p->tok_vec[i].token);
										}
									}
								}

								break;
							case TOK_MAIN:
								{
									i++;
									if(Bounds(i)) {
										prog_name = p->tok_vec[i].token;
										current_obj = "master";
										obj[p->tok_vec[i].token] =  p->tok_vec[i].token;
									}
								}
								break;
							case TOK_USES:
								{
									i += 2;
									if(Bounds(i))
										while(p->tok_vec[i].type != ';' && i < p->tok_vec.size()) {
											uses.push_back(current_obj + "." + p->tok_vec[i].token);
											i++;
											if(Bounds(i) && p->tok_vec[i].type == ',')
												i++;
										}
								}
								break;
							case TOK_MAS:
								i++;
								if(Bounds(i)) {
									current_obj = p->tok_vec[i].token;
									obj[current_obj] = current_obj;
								}
								break;
							case TOK_BEGIN:
								i ++;
								current_proc = current_obj + "." + "begin";
								if(Bounds(i))
									AddIncBlock(current_obj + "." + "begin", i);

								break;
							case TOK_END:
								i ++;
								current_proc = current_obj + "." + "end";
								if(Bounds(i))
									AddIncBlock(current_obj + "." + "end", i);
								break;
							case TOK_EXTERN:
								i += 2;
								if(Bounds(i)) {
									callb[current_obj + "." + p->tok_vec[i].token].isdef = true;
								}
								break;
							case TOK_PROC:
								i++;
								current_proc = current_obj + "." + p->tok_vec[i].token;
								if(Bounds(i+2)) {
									AddIncBlock(current_obj + "." + p->tok_vec[i].token, i+1);
								}
								break;
							case TOK_IMPLEMENT:
								{
									i+=2;
									if(Bounds(i)) {
										callb[current_obj + "." + p->tok_vec[i].token].imp = true;
										callb[current_obj + "." + p->tok_vec[i].token].name = current_obj + "." + p->tok_vec[i].token;
										callb[current_obj + "." + p->tok_vec[i].token].other_name = p->tok_vec[i].token;
									}


								}
								break;
							}
						}
					}
					break;
				case STRING:
					break;
				case DIGIT:
					break;
				case CODELABEL:
					labels[p->tok_vec[i].token].label_name = p->tok_vec[i].token;
					labels[p->tok_vec[i].token].proc = current_proc;
					break;
			}
		}
	}

	void BackEnd::AddIncBlock(std::string block_name, size_t start) {
		std::vector<Instruct> v;
		v.push_back ( Instruct(0xFF,block_name, "") );
		size_t pos;
		for(start, pos = 0; p->tok_vec[start].type != '}' && start < p->tok_vec.size(); start++) {
			int id = IdentToValue(p->tok_vec[start].token);
			if(id >= TOK_MOV && id <= TOK_PRINT) {
				Instruct i;
				i.op_code = id;
				i.op1 = p->tok_vec[start+1].token;
				if(Bounds(start+3) && p->tok_vec[start+2].type == ',')
					i.op2 = p->tok_vec[start+3].token;
				else if(Bounds(start+3) && p->tok_vec[start+1].type == '<') {
					std::ostringstream string_s;
					start++;
					while(Bounds(start) && p->tok_vec[start].type != ';') {
						if(p->tok_vec[start].type != '<')
							string_s << p->tok_vec[start].token << char(0xFF);
						start++;
					}

					i.op1 = string_s.str();
					i.op2 = "";
				}
				else if(Bounds(start+3) && p->tok_vec[start+2].type == '<') {
					std::ostringstream string_s;
					i.op1 = p->tok_vec[start+1].token;
					start+=2;
					while(Bounds(start) && p->tok_vec[start].type != ';') {
						if(p->tok_vec[start].type != '<')
							string_s << p->tok_vec[start].token << char(0xFF);
						start++;
					}
					i.op2 = string_s.str();
				}
				else
					i.op2 = "";
				v.push_back(i);
				pos++;
			}
			if(p->tok_vec[start].type == 4) {
				labels[p->tok_vec[start].token].pos = pos++;
			}
		}

		ins.push_back(v);
	}

	void BackEnd::DebugInc() {
		size_t i;
		for(i = 0; i < ins.size(); i++)
			for(size_t z = 0; z < ins[i].size(); z++) {
				if(ins[i][z].op_code == 0xFF)
					cout << "Code Block Name: " << ins[i][z].op1 << endl;
				else
					cout << "Opcode: " << tok_array[ins[i][z].op_code]  << " Operand 1: " << ins[i][z].op1 << ((ins[i][z].op2.length()==0) ? "" : " Operand 2: ") << ins[i][z].op2 << endl;
			}

			for(i = 0; i < uses.size(); i++)
				cout << "Uses clause: " << uses[i] << endl;

			std::map<std::string,Code_Label>::iterator l = labels.begin();
			for(l; l != labels.end(); l++)
				cout << "Code Label: " << l->second.label_name << " In Procedure: " << l->second.proc << " At Code Position: " << int(l->second.pos) << endl;

	}

	void BackEnd::CallProcedure(std::string proc_name) {
		size_t p = Find(proc_name);
		if(p != 0) {
			code.push_back(std::make_pair(cur_pos,i+1));
			cur_pos = p, i = 0;
			return;
		}
		else
			std::cout << "**** Procedure " << proc_name << " Not Found!\n";

	}

	void BackEnd::Execute(bool anaylize) {
		if(anaylize && !p->LexAnayalize()) {
			cout << "**** Errors in script cannot continue...\n";
#ifdef _WIN32
			system("PAUSE");
#endif
			return;

		}

		if(p->err != 0) {
			cout << "**** Errors in script cannot continue...\n";
#ifdef _WIN32
			system("PAUSE");
#endif
			return;

		}

		if(!p->tok_vec.empty())
		p->tok_vec.clear();
		if(p->file)
		{
			p->file->close();
		}
		size_t begin_pos = Find("master.begin"), end_pos = Find("master.end");
		size_t u, b , e;
		cur_pos = begin_pos;
		i = 0;

		if(end_pos != 0)
			code.push_back( std::pair<size_t,size_t>(end_pos,0) );
		if(uses.size()!=0) {
		for(u = 0; u < uses.size(); u++) {
			std::string str = uses[u].substr(uses[u].find(".")+1,uses[u].length());
			e = Find(str + ".end");
			if(e != 0) 
				code.push_back(std::make_pair(e,0));
		}
		code.push_back(std::make_pair(begin_pos,0));
		for(u = 0; u < uses.size(); u++) {
			std::string str = uses[u].substr(uses[u].find(".")+1,uses[u].length());
			b = Find(str + ".begin");
			if(u != uses.size()-1)
				code.push_back(std::make_pair(b,0));
		}
		cur_pos = b;
		}
		else
			cur_pos = begin_pos;
		
		while(1) {

			while(i < ins[cur_pos].size()) {
				PROC_RETURN rt;
				if((rt = ProcInc(cur_pos, i)) == PROC_CONT)
					ins[cur_pos][i].op1 = prev_op1, ins[cur_pos][i].op2 = prev_op2, i++;
				else if(rt == PROC_JMP){
					ins[cur_pos][i].op1 = prev_op1, ins[cur_pos][i].op2 = prev_op2;
					size_t pos = Find(ins[cur_pos][i].op1);
					if(pos != 0) {
						if(ins[pos][0].op_code == 0xFF) {
							code.push_back(std::pair<size_t,size_t>(cur_pos,i+1));
							code.push_back(std::pair<size_t,size_t>(pos,0));
							break;
						}
					}
					else
					{
						if(callb[ins[cur_pos][i].op1].name == "" || callb[ins[cur_pos][i].op1].isdef == false)
							cout << "**** invalid procedure call-> " << ins[cur_pos][i].op1 << endl;
						else
							if(callb[ins[cur_pos][i].op1].f(symbols) != 0)
								std::cerr << "Error external callback didnt return 0\n";
						i++;
					}
				}
				else if(rt == PROC_RET) {
					ins[cur_pos][i].op1 = prev_op1, ins[cur_pos][i].op2 = prev_op2;
					break;
				}
			}

			if(code.empty())
				break;
			cur_pos = code.back().first;
			i = code.back().second;
			code.pop_back();
		}
	}

	PROC_RETURN BackEnd::ProcInc(size_t block, size_t &inc) {

		prev_op1 = ins[block][inc].op1;
		prev_op2 = ins[block][inc].op2;

		if(ins[block][inc].op1.find('[') != -1 && ins[block][inc].op1.find(']') != -1) {
			std::ostringstream curs;
			std::string num = ins[block][inc].op1;
			std::vector<std::string> vec;
			while(num.find('[') != -1) {
				num = num.substr(num.find('[')+1,num.length());
				num = num.substr(0,num.rfind(']'));
				vec.push_back(num);
			}

			std::string prev_index = "";
			for(int array_pos = int(vec.size())-1; array_pos >= 0; array_pos--) {
				std::string  the_name = "";
				if(vec[array_pos].find('[') != -1) {
					if(IsVar(vec[array_pos])) {
						prev_index = symbols.vars[vec[array_pos]].val;
					}
					else {
						the_name = vec[array_pos].substr(0,vec[array_pos].find('['));
						prev_index = symbols.vars[the_name + "[" + prev_index + "]"].val;
					}
				}
				else
					prev_index = (IsVar(vec[array_pos]) == true ? symbols.vars[vec[array_pos]].val : vec[array_pos]);
			}

			std::string name = ins[block][inc].op1.substr(0,ins[block][inc].op1.find('['));
			curs << name << "[" << prev_index << "]";
			ins[block][inc].op1 = curs.str();
		}
		if(ins[block][inc].op2.find('[') != -1 && ins[block][inc].op2.find(']') != -1) {
			std::ostringstream curs;
			std::string num = ins[block][inc].op2;
			std::vector<std::string> vec;
			while(num.find('[') != -1) {
				num = num.substr(num.find('[')+1,num.length());
				num = num.substr(0,num.rfind(']'));
				vec.push_back(num);
			}
			std::string prev_index = "";
			for(int array_pos = int(vec.size())-1; array_pos >= 0; array_pos--) {
				std::string  the_name;
				if(vec[array_pos].find('[') != -1) {
					if(IsVar(vec[array_pos])) {
						prev_index = symbols.vars[vec[array_pos]].val;
					}
					else {
						the_name = vec[array_pos].substr(0,vec[array_pos].find('['));
						prev_index = symbols.vars[the_name + "[" + prev_index + "]"].val;
					}
				}
				else
					prev_index = (IsVar(vec[array_pos]) == true ? symbols.vars[vec[array_pos]].val : vec[array_pos]);
			}

			std::string name = ins[block][inc].op2.substr(0,ins[block][inc].op2.find('['));
			curs << name << "[" << prev_index << "]";
			ins[block][inc].op2 = curs.str();
		}

		switch(ins[block][inc].op_code) {
			case TOK_MOV:
				if(IsVar(ins[block][inc].op1)) {
					if(IsVar(ins[block][inc].op2))
						symbols.vars[ins[block][inc].op1].val = symbols.vars[ins[block][inc].op2].val;
					else
						symbols.vars[ins[block][inc].op1].val = ins[block][inc].op2;
				}
				else
					std::cout << "**** invalid variable name on mov...[" << ins[block][inc].op1 << "]\n";
				break;
			case TOK_ADD:
			case TOK_SUB:
			case TOK_MUL:
			case TOK_DIV:
			case TOK_OR:
			case TOK_XOR:
			case TOK_AND:
				{
					if(IsVar(ins[block][inc].op1)) {
						if(IsVar(ins[block][inc].op2))
						{
							std::ostringstream s;
							switch(ins[block][inc].op_code) 
							{
							case TOK_ADD:
								s << (symbols.vars[ins[block][inc].op1].type == VAR_INTEGER ? (std::atoi(symbols.vars[ins[block][inc].op1].val.c_str())+std::atoi(symbols.vars[ins[block][inc].op2].val.c_str())) : (atof(symbols.vars[ins[block][inc].op1].val.c_str())+atof(symbols.vars[ins[block][inc].op2].val.c_str())));
								break;
							case TOK_SUB:
								s << (symbols.vars[ins[block][inc].op1].type == VAR_INTEGER ? (std::atoi(symbols.vars[ins[block][inc].op1].val.c_str())-std::atoi(symbols.vars[ins[block][inc].op2].val.c_str())) : (atof(symbols.vars[ins[block][inc].op1].val.c_str())-atof(symbols.vars[ins[block][inc].op2].val.c_str())));
								break;
							case TOK_MUL:
								s << (symbols.vars[ins[block][inc].op1].type == VAR_INTEGER ? (std::atoi(symbols.vars[ins[block][inc].op1].val.c_str())*std::atoi(symbols.vars[ins[block][inc].op2].val.c_str())) : (atof(symbols.vars[ins[block][inc].op1].val.c_str())*atof(symbols.vars[ins[block][inc].op2].val.c_str())));
								break;
							case TOK_DIV:
								if(std::atoi(symbols.vars[ins[block][inc].op1].val.c_str()) == 0 || std::atoi(symbols.vars[ins[block][inc].op2].val.c_str()) == 0)
									std::cout << "***** Error cannot divide by zero...\n";
								else
									s << (symbols.vars[ins[block][inc].op1].type == VAR_INTEGER ? (std::atoi(symbols.vars[ins[block][inc].op1].val.c_str())/std::atoi(symbols.vars[ins[block][inc].op2].val.c_str())) : (atof(symbols.vars[ins[block][inc].op1].val.c_str())/atof(symbols.vars[ins[block][inc].op2].val.c_str())));
								break;
							case TOK_OR:
								s << (std::atoi(symbols.vars[ins[block][inc].op1].val.c_str())|std::atoi(symbols.vars[ins[block][inc].op2].val.c_str()));
								break;
							case TOK_XOR:
								s << (std::atoi(symbols.vars[ins[block][inc].op1].val.c_str())^std::atoi(symbols.vars[ins[block][inc].op2].val.c_str()));
								break;
							case TOK_AND:
								s << (std::atoi(symbols.vars[ins[block][inc].op1].val.c_str())&std::atoi(symbols.vars[ins[block][inc].op2].val.c_str()));
								break;
							}
							symbols.vars[ins[block][inc].op1].val = s.str();
						}
						else
						{
							std::ostringstream s;
							switch(ins[block][inc].op_code) 
							{
							case TOK_ADD:
								s << (symbols.vars[ins[block][inc].op1].type == VAR_INTEGER ? (std::atoi(symbols.vars[ins[block][inc].op1].val.c_str())+std::atoi(ins[block][inc].op2.c_str())) : (atof(symbols.vars[ins[block][inc].op1].val.c_str())+atof(ins[block][inc].op2.c_str())));
								break;
							case TOK_SUB:
								s << (symbols.vars[ins[block][inc].op1].type == VAR_INTEGER ? (std::atoi(symbols.vars[ins[block][inc].op1].val.c_str())-std::atoi(ins[block][inc].op2.c_str())) : (atof(symbols.vars[ins[block][inc].op1].val.c_str())-atof(ins[block][inc].op2.c_str())));
								break;
							case TOK_MUL:
								s << (symbols.vars[ins[block][inc].op1].type == VAR_INTEGER ? (std::atoi(symbols.vars[ins[block][inc].op1].val.c_str())*std::atoi(ins[block][inc].op2.c_str())) : (std::atof(symbols.vars[ins[block][inc].op1].val.c_str())*std::atof(ins[block][inc].op2.c_str())));
								break;
							case TOK_DIV:
								if(std::atoi(symbols.vars[ins[block][inc].op1].val.c_str()) == 0 || std::atoi(ins[block][inc].op2.c_str()) == 0)
									cout << "***** Error cannot divide by zero...\n";
								else
									s << (symbols.vars[ins[block][inc].op1].type == VAR_INTEGER ? (std::atoi(symbols.vars[ins[block][inc].op1].val.c_str())/std::atoi(ins[block][inc].op2.c_str())) : (std::atof(symbols.vars[ins[block][inc].op1].val.c_str())/std::atof(ins[block][inc].op2.c_str())));
								break;
							case TOK_OR:
								s << (std::atoi(symbols.vars[ins[block][inc].op1].val.c_str())|std::atoi(ins[block][inc].op2.c_str()));
								break;
							case TOK_XOR:
								s << (std::atoi(symbols.vars[ins[block][inc].op1].val.c_str())^std::atoi(ins[block][inc].op2.c_str()));
								break;
							case TOK_AND:
								s << (std::atoi(symbols.vars[ins[block][inc].op1].val.c_str())&std::atoi(ins[block][inc].op2.c_str()));
								break;
							}
							symbols.vars[ins[block][inc].op1].val = s.str();
						}
					}
					else
						std::cout << "**** invalid variable name ...[" << ins[block][inc].op1 << "]\n";
				}
				break;
			case TOK_NOT:
				{
					if(IsVar(ins[block][inc].op1)) {
						std::ostringstream s;
						s << (!std::atoi(symbols.vars[ins[block][inc].op1].val.c_str()));
						symbols.vars[ins[block][inc].op1].val = s.str();
					}
					else
						std::cout << "**** invalid variable name ...[" << ins[block][inc].op1 << "]\n";
				}
				break;
			case TOK_INC:
			case TOK_DEC:
				{
					if(IsVar(ins[block][inc].op1)) {
						std::ostringstream s;
						if(ins[block][inc].op_code == TOK_INC)
							s << (std::atoi(symbols.vars[ins[block][inc].op1].val.c_str())+1);
						else
							s << (std::atoi(symbols.vars[ins[block][inc].op1].val.c_str())-1);
						symbols.vars[ins[block][inc].op1].val = s.str();
					}
					else
						std::cout << "**** invalid variable name ...[" << ins[block][inc].op1 << "]\n";
				}
				break;
			case TOK_PUSH: 
				{
					static symb s;

					if(IsVar(ins[block][inc].op1)) {
						s.name = ins[block][inc].op1;
						s.val = symbols.vars[s.name].val;
						s.type = symbols.vars[s.name].type;
						symbols += s;
					}
					else
					{
						s.name = "constant";
						s.type = IDENTIFIER;
						s.val = ins[block][inc].op1;
						symbols += s;
					}
				}
				break;
			case TOK_POP:
				{
					if(IsVar(ins[block][inc].op1))
					{
						symb s = --symbols;
						symbols[ins[block][inc].op1].val = s.val;
					}
					else
						std::cout << "**** invalid variable name on pop...[" << ins[block][inc].op1 << "]\n";
				}
				break;
			case TOK_PRINT:
				if(ins[block][inc].op1.find(char(0xFF)) == -1 && symbols.vars[ins[block][inc].op1].name != "")
					std::cout << symbols.vars[ins[block][inc].op1].val;
				else if(ins[block][inc].op1.find(char(0xFF)) == -1) {
					std::cout<<  ins[block][inc].op1;
				}
				else { // stream data
					std::ostringstream string_s;
					std::string left, right,temp = ins[block][inc].op1;

					while(temp.length() > 0 && temp.find(char(0xFF)) != -1) {
						left = temp.substr(0,temp.find(char(0xFF)));
						temp = temp.substr(temp.find(char(0xFF))+1,temp.length());
						if(IsVar(left)) 
							string_s << symbols.vars[left].val;
						else
							string_s << left;
					}

					cout << string_s.str();
				}
				break;
			case TOK_SCAT:
				{
					std::ostringstream string_s;
					if(ins[block][inc].op2.find(char(0xFF)) == -1 && symbols.vars[ins[block][inc].op1].name != "") {
						std::cout << "**** error no data to stream to variable...\n";
					}
					else { // stream data
						std::string left, right,temp = ins[block][inc].op2;

						while(temp.length() > 0 && temp.find(char(0xFF)) != -1) {
							left = temp.substr(0,temp.find(char(0xFF)));
							temp = temp.substr(temp.find(char(0xFF))+1,temp.length());
							if(IsVar(left)) 
								string_s << symbols.vars[left].val;
							else
								string_s << left;
						}

						symbols.vars[ins[block][inc].op1].val = string_s.str();
					}
				}
				break;
			case TOK_CALL:
				return PROC_JMP;
				break;
			case TOK_JMP:
				if(ins[block][0].op1 == labels[ins[block][inc].op1].proc)
					inc = labels[ins[block][inc].op1].pos;
				else
					std::cout << "***** on jmp instruction wrong procedure or no label found.\n";
				break;
			case TOK_JNE:
				if(ins[block][0].op1 == labels[ins[block][inc].op1].proc) {
					if(reg[0] == false) inc = labels[ins[block][inc].op1].pos;
				}
				else
					std::cout << "***** on jmp instruction wrong procedure or no label found.\n";

				break;
			case TOK_JE:
				if(ins[block][0].op1 == labels[ins[block][inc].op1].proc) {
					if(reg[0] == true) inc = labels[ins[block][inc].op1].pos;
				}
				else
					std::cout << "***** on jmp instruction wrong procedure or no label found.\n";

				break;
			case TOK_JL:
				if(ins[block][0].op1 == labels[ins[block][inc].op1].proc) {
					if(reg[1] != true) inc = labels[ins[block][inc].op1].pos;
				}
				else
					std::cout << "***** on jmp instruction wrong procedure or no label found.\n";

				break;
			case TOK_JG:
				if(ins[block][0].op1 == labels[ins[block][inc].op1].proc) {
					if(reg[1] == true) inc = labels[ins[block][inc].op1].pos;
				}
				else
					std::cout << "***** on jmp instruction wrong procedure or no label found.\n";
			case TOK_JLE:
				if(ins[block][0].op1 == labels[ins[block][inc].op1].proc) {
					if(reg[3] == true) inc = labels[ins[block][inc].op1].pos;
				}
				else
					std::cout << "***** on jmp instruction wrong procedure or no label found.\n";
				break;
			case TOK_JGE:
				if(ins[block][0].op1 == labels[ins[block][inc].op1].proc) {
					if(reg[2] == true) inc = labels[ins[block][inc].op1].pos;
				}
				else
					std::cout << "***** on jmp instruction wrong procedure or no label found.\n";
				break;

			case TOK_CMP:
				{
					if(IsVar(ins[block][inc].op1)) {
						if(IsVar(ins[block][inc].op2)) {

							reg[0] = (symbols.vars[ins[block][inc].op1].val == symbols.vars[ins[block][inc].op2].val);
							reg[1] = (std::atof(symbols.vars[ins[block][inc].op1].val.c_str()) > std::atof(symbols.vars[ins[block][inc].op2].val.c_str()));
							reg[2] = (std::atof(symbols.vars[ins[block][inc].op1].val.c_str()) >= std::atof(symbols.vars[ins[block][inc].op2].val.c_str()));
							reg[3] = (std::atof(symbols.vars[ins[block][inc].op1].val.c_str()) <= std::atof(symbols.vars[ins[block][inc].op2].val.c_str()));

						}
						else {

							reg[0] = (symbols.vars[ins[block][inc].op1].val == ins[block][inc].op2);
							reg[1] = (std::atof(symbols.vars[ins[block][inc].op1].val.c_str()) > std::atof(ins[block][inc].op2.c_str()));
							reg[2] = (std::atof(symbols.vars[ins[block][inc].op1].val.c_str()) >= std::atof(ins[block][inc].op2.c_str()));
							reg[3] = (std::atof(symbols.vars[ins[block][inc].op1].val.c_str()) <= std::atof(ins[block][inc].op2.c_str()));
						}
					}
				}
				break;
			case TOK_RET:
				{
					return PROC_RET;
				}
				break;
			case TOK_EXIT:
				{
					std::exit(0);
				}
				break;

		}

		return PROC_CONT;
	}

	size_t BackEnd::Find(std::string what) {
		for(size_t i = 0; i < ins.size(); i++)
			if(strcmp(ins[i][0].op1.c_str(),what.c_str()) == 0)
				return i;
		return 0;
	}

	void BackEnd::AddExternal(std::string name, int (*f)(Symbol_Table &t)) {
		callb[name].f = f;
		callb[name].name = name;
	}

	bool BackEnd::IsVar(std::string &name) {
		if(symbols.vars[name].name == "")
			return false;
		return true;
	}

	std::string BackEnd::byteToString(unsigned char type) {
		std::string s;
		switch(type) {
			case 1:
				return "Identifier";
			case 2:
				return "Digit";
			case 3:
				return "String";
			case 4:
				return "Code Label";
		}

		s += type;
		return s;
	}

	std::string BackEnd::tokenTypeToString(TOK_TYPE t) {
		std::string s;
		switch(t) {
			case 0:
				return "Constant";
			case VAR_INTEGER:
				return "Integer";
			case VAR_STRING:
				return "String";
			case VAR_FLOAT:
				return "Float";
		}
		s += int(t);
		return s;
	}

	void BackEnd::DebugHTML(std::string src, bool sout) {
		std::fstream file;
		file.open(src.c_str(), std::ios::out);
		if(file.is_open()) {
			size_t i = 0, z = 0;
			file << "<HTML><TITLE>Masc Debug Output File for " << prog_name << "</TITLE><BODY>";
			file << "<font face=\"FixedSys\" size=\"4\" color=\"black\"><TABLE border=\"4\" bgcolor=\"#FFFFFF\" BORDERCOLOR=\"#000000\" CELLPADDING=\"3\" CELLSPACING=\"0\"><br>";
			file << "<TR><font color=\"#BD0000\"> Tokenized Code </font> </TR><br><TH> File/Line </TH><TH> Byte Code </TH><TH> Symbols </TH>";
			for(i = 0; i < p->tok_vec.size(); i++)
				file << "<TR><TH><font color=\"blue\">" << p->tok_vec[i].source_file << ":" << p->tok_vec[i].line_num << "</TH><TH>" << byteToString(p->tok_vec[i].type) << "</font></TH><TH><font color=\"A0A0A0\">" << p->tok_vec[i].token << "</font></TH>";
			file << "</TABLE><TABLE border =\"4\" bgcolor=\"#FFFFFF\" BORDERCOLOR=\"#000000\" CELLPADDING=\"3\" CELLSPACING=\"0\"> <br> <TR><font color=\"#BD0000\"> Intermediate Code</font></TR><br><TH> OpCode </TH><TH> Operand 1 </TH> <TH> Operand 2 </TH>";
			for(i = 0; i < ins.size(); i++)
				for(z = 0; z < ins[i].size(); z++)
					file << "<TR><TH><font color=\"orange\"> " <<  (ins[i][z].op_code == 0xFF ? "Code Block" : (ins[i][z].op_code <= TOK_PRINT ? tok_array[int(ins[i][z].op_code)] : "Unknown")) << " (" << int(ins[i][z].op_code) << ")</font></TH> <TH><font color=\"purple\">" << ins[i][z].op1 << "</font></TH>" << "<TH><font color=\"purple\">" << ins[i][z].op2 << "</font></TH>";
			file << "</TABLE><TABLE border =\"4\" bgcolor=\"#FFFFFF\" BORDERCOLOR=\"#000000\" CELLPADDING=\"3\" CELLSPACING=\"0\"> <br> <TR><font color=\"#BD0000\"> Symbol Table </font></TR><br><TH> String Name </TH><TH> Value </TH> <TH> Type </TH>";

			std::map<std::string,symb>::const_iterator x;
			for(x = symbols.vars.begin(); x != symbols.vars.end(); x++)
				file << "<TR><TH><font color=\"teal\">" <<  x->first  << "</font></TH> <TH><font color=\"green\">" << x->second.val << "</font></TH>" << "<TH><font color=\"red\">" << tokenTypeToString(TOK_TYPE(x->second.type)) << "</font></TH>";

			std::map<std::string, masc::External_Callback>::iterator y;
			file << "</TABLE><TABLE border =\"4\" bgcolor=\"#FFFFFF\" BORDERCOLOR=\"#000000\" CELLPADDING=\"3\" CELLSPACING=\"0\"> <br> <TR><font color=\"#BD0000\"> External Callbacks </font></TR><br><TH> Procedure Name </TH> <TH> Address </TH>";
			for(y = callb.begin(); y != callb.end(); y++)
				file << "<TR><TH><font color=\"purple\">" <<  y->first << "</font></TH> <TH><font color=\"green\">" << y->second.f << "</font></TH>";
			file << "<font></TABLE></BODY></HTML>";		
			file.close();
		}

		// dump debug output to stdout
		if(sout == true) {
			std::fstream ifile;
			cout << "Content-type: text/html\n\n";
			ifile.open(src.c_str(),std::ios::in);
			while(ifile.is_open() && !ifile.eof()) {
				std::string s;
				std::getline(ifile,s);
				cout << s << "\n";
			}
			ifile.close();
		}
	}

	inline int IdentToValue(std::string s) {
		for(int i = 0; tok_array[i] != 0; i++) 
			if(s == tok_array[i])
				return i;
		return -1;
	}

	
	BackEnd *BackEnd::back;
}

