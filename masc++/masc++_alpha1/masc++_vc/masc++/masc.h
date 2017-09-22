#ifndef MASC__H_
#define MASC__H_

#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<string>
#include<list>
#include<cstdio>
#include "garbage.h"

namespace masc {

	const double version = 2.01;

	char *mysprintf(char *src, const char *sptr, ...);
	int myprintf(const char *src, ...);

	struct symb {
		std::string val,name;
		int type;
		symb() { val = name = ""; type = 0; }
	};

	class BackEnd;
	class Parser;

	class Symbol_Table {

	public:
		void Set(int type, std::string val, std::string name);
		symb &Get(std::string name);
		void DebugPrint() const;
		symb &operator[]( std::string str ) { return vars[str]; }
		symb &operator() ( size_t pos );
		symb operator--();
		std::list<symb>::iterator operator*() { return st.begin(); }
		void operator+=(const symb &s);
		std::list<symb> st;
		symb Pop();
		void PopAll();
		void Push(symb &s);
	protected:
		std::map<std::string, symb> vars;
		friend class BackEnd;
		friend class Parser;
	};

	class MFile {
	public:
		std::string cur_line;

		MFile(std::string s) {
			file = 0;
			Open(s);
		}

		~MFile() {
			if(opened == true)
				file->close();
			delete file;
		}

		void Open(std::string s) {
			if(file && file->is_open())
			file->close();
			if(file) delete file;
			file = new std::fstream;
			file->open(s.c_str(),std::ios::in);
			if(!file->is_open()) { opened = false; return; }
			opened = true;
			file_name = s;
			curline = 0;
		}

		bool GetLine() {
			if(file->eof()) {
				file->close();
				return true;
			}
			std::getline(*file,cur_line);
			++curline;
			return false;
		}

	protected:
		std::fstream *file;
		bool opened;
		std::string file_name;
		int curline;
	};

	struct Token {
		unsigned char type;
		std::string token;
		int line_num;
		std::string source_file;
	};

	enum { IDENTIFIER = 1, DIGIT, STRING, CODELABEL };

	class Parser : public MFile {
	public:
		friend class BackEnd;
		Parser(std::string s);
		void Begin();
		void Parse(std::string str);
		void DebugTokens();
		Token &operator[](size_t pos) {  if(pos >= 0 && pos < tok_vec.size()) return tok_vec[pos]; else return cur; }
		bool LexAnayalize();
		void StartParse(std::string str);
		inline bool pBounds(size_t pos) { 
			if(pos >= 0 && pos < tok_vec.size()) { 
				current_line = tok_vec[pos].line_num;
				current_file = tok_vec[pos].source_file;
				return true;
			}
			return false;
		}
		void ErrorMsg(const char *str, ...);
	private:
		Token cur;
		int err,current_line;
		std::string current_file;
		std::vector<Token> tok_vec;
		std::vector<std::string> insert_vec;
	};

	struct Instruct {
		unsigned char op_code;
		std::string op1;
		std::string op2;
		Instruct(unsigned char op_code, std::string op1, std::string op2) {
			this->op_code = op_code;
			this->op1 = op1;
			this->op2 = op2;
		}
		Instruct() { op_code = 0; op1 = op2 = ""; }
	};

	struct External_Callback {
		int (*f) (Symbol_Table &t);
		std::string name,other_name;
		bool isdef,imp;
		External_Callback() {
			name = "";
			isdef = false;
			imp = false;
		}
	};

	enum TOK_TYPE { TOK_INSERT, TOK_MAIN, TOK_USES, TOK_MAS, TOK_VAR, TOK_BEGIN, TOK_END, TOK_MOV, TOK_ADD,TOK_SUB,TOK_MUL,TOK_DIV,TOK_OR, TOK_XOR,TOK_AND,TOK_NOT,TOK_PUSH,TOK_POP,TOK_INC,TOK_DEC,TOK_CMP,TOK_JMP,TOK_JNE,TOK_JE,TOK_JL,TOK_JG,TOK_JLE,TOK_JGE,TOK_RET, TOK_EXIT,TOK_CALL,TOK_SCAT,TOK_PRINT, TOK_PROC,TOK_IMPLEMENT,TOK_EXTERN,VAR_INTEGER, VAR_STRING, VAR_FLOAT };
	static char *tok_array[] = {"insert", "master","uses","mas","var","begin","end","mov","add","sub","mul","div","or","xor","and","not", "push", "pop","inc","dec","cmp","jmp","jne","je","jl","jg","jle","jge","ret","exit","call","scat","print","proc","implement","extern","var&","var$","var#", 0, 0 };
	enum PROC_RETURN { PROC_CONT, PROC_JMP, PROC_RET };
	struct Code_Label {
		std::string label_name;
		std::string proc;
		size_t pos;
		Code_Label(std::string label_name, std::string proc, size_t pos) {
			this->label_name = label_name;
			this->pos = pos;
			this->proc = proc;
		}
		Code_Label() {
			label_name = "";
			pos = 0;
			proc = "";
		}
	};

	class BackEnd {
		Parser *p;
		std::vector<std::vector<Instruct> > ins;
		std::string prog_name,current_obj;
		std::vector<std::string> uses;
		std::list<std::pair<size_t,size_t> > code;
	public:

		Symbol_Table symbols;

		BackEnd(Parser *p) {
			this->p = p;
			memset(reg,0,sizeof(reg));
			back = this;
		}
		~BackEnd() {
			if(p)
				delete p;
		}
		void Convert();
		void Execute(bool anaylize);
		
		inline void Debug() { std::cout << "Program Name: " << prog_name << '\n'; p->DebugTokens(); symbols.DebugPrint();  DebugInc(); }
		inline bool Bounds(size_t pos) { if(pos >= 0 && pos < p->tok_vec.size()) return true; return false; }
		size_t Find(std::string what);
		void AddExternal(std::string name, int (*f)(Symbol_Table &t));
		void DebugHTML(std::string src,bool sout);
		std::string GetName() { return prog_name; }
		void CallProcedure(std::string proc_name);
		static class BackEnd *back;
	protected:
		void AddIncBlock(std::string block_name, size_t start);
		void DebugInc();
		PROC_RETURN ProcInc(size_t block, size_t &inc);
		bool IsVar(std::string &name);
		std::string byteToString(unsigned char type);
		std::string tokenTypeToString(TOK_TYPE t);
		size_t i , cur_pos;
		bool reg[4];// flag registers
		std::string prev_op1,prev_op2;
		std::map<std::string, External_Callback> callb;
		std::map<std::string,Code_Label> labels;
		std::map<std::string,std::string> obj;
		friend class Parser;
	};
	
	inline int IdentToValue(std::string s);
	inline BackEnd *GetBend() { return BackEnd::back; }

}



#endif

