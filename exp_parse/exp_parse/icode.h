#ifndef __ICODE__H_
#define __ICODE__H_

#include "token.h"


#define max_size 256

struct Icode {
	int token;
	int val;
	char str[256];
};

extern Icode icode[max_size];
extern int isize;

extern void Put(int token, int val, char *str);

struct Stack {
	int stack_ptr;
	int stack[256];
	int of_;
	char *stack_name;

	Stack(char *stack_name) {
		this->stack_name = stack_name;
		of_ = 0;
		stack_ptr = 0;
	}

	int Pop() {
		if(this->stack_ptr-1 < 0) {
			return 0;
		}
		return this->stack[--this->stack_ptr];
	}

	void Push(int x) {
		printf("Pushed %d on to %s Stack\n", x, this->stack_name);
		this->stack[this->stack_ptr++] = x;
	}

	int Pound() {
	return this->stack[of_++] ;
	}

};


class BackEnd {
	int pos;
	int rtvar;
	Stack st;

	void setpos() {
		dot = this->pos;
	}
public:
	BackEnd() : st("Runtime") {

	}

	void _goto(int pos) {
		this->pos = pos;
		setpos();
	}


	void exec() {
		_goto(0);
		nexttoken();
		do {
			execute_statement();
			while(Token.cls == SC) nexttoken();
		} while(Token.cls != EOF);

		rtvar = st.Pop();
	}

	void execute_statement() {
		execute_assignment();
	}

	void execute_assignment() {
		execute_expression();
	}

	void execute_expression() {
		execute_simple_expression();
	}

	void execute_simple_expression() {
		int code = 0, op;
		op = PLUS;

		if(Token.cls == PLUS || Token.cls == MINUS) {
			op = Token.cls;
			nexttoken();
		}
		execute_term();
		if(op == MINUS) st.Push ( -st.Pop() );
		while ((Token.cls == PLUS) || (Token.cls == MINUS)) {
			op  = Token.cls;
			nexttoken();
			execute_term();

			int op2 = st.Pop();
			int op1 = st.Pop();

			switch(op) {
				case PLUS:
					printf("%d + %d = %d\n", op1,op2,(op1+op2));
					st.Push( (op1 + op2) );
					break;
				case MINUS:
					printf("%d - %d = %d\n",op1,op2,(op1-op2));
					st.Push ( (op1 - op2 ) );
					break;
			}
		}
	}

	void execute_term() {
		int op;
		execute_factor();
		while (Token.cls == MUL || Token.cls == DIV) {
			op = Token.cls;
			nexttoken();
			execute_factor();

			int op1, op2;
			op2 = st.Pop();
			op1 = st.Pop();
			switch(op) {
				case MUL:
					printf("%d * %d = %d\n",op1,op2,(op1*op2));
					st.Push ( (op1 * op2) );
					break;
				case DIV:
					if(op2 != 0)
					st.Push ( (op1 / op2));
					else {
						printf("Division by Zero Runtime Error.\n");
						st.Push (0);
					}
					break;
			}

		}
	}

	void execute_factor() {
		switch(Token.cls) {
			case IDENTIFIER:
				// add later
				nexttoken();
				break;
			case INTEGER:
				st.Push(Token.val);
				nexttoken();
				break;
			case OP:
				nexttoken();
				execute_expression();
				nexttoken();
				break;

		}


	}

	int getrtval() { return rtvar; }



};

#endif
