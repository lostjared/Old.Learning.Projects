// stack structure example (LIFO)
// written by jared bruni
// www.lostsidedead.com


#include <iostream.h>
#define STACK_SIZE 100 // stack size
#define STACK_FAIL -1 // failure, 

// prototype for class 
class Stack
{
private:
	int int_stack[STACK_SIZE];
	int stack_index;
public:

	inline Stack()
	{
		clearstack();
	}

	void clearstack();
	void stackpush(int x);
	int  stackpop();
	void stackdump();
};

//implementation for stack class

// clear the stack
void Stack::clearstack()
{
	for(int i = 0; i <= STACK_SIZE; i++)
	{
		int_stack[i] = 0; // null
	}

	stack_index = 0;
}
// push item into the stack
void Stack::stackpush(int x)
{
	if(stack_index < STACK_SIZE)
	{
		int_stack[stack_index] = x;
		stack_index++;
	}
	else
	{
		cout << "\nError, stack full..\n";
	}
}

// pop a item out of the stack
int  Stack::stackpop()
{
	stack_index--;
	if(stack_index >= 0)
	{
		int var = int_stack[stack_index];
		int_stack[stack_index] = 0;
		return var;
	}
	else
	{
		cout << "\n cannot pop, no item stack is clear\n";
		stack_index = 0;
		return STACK_FAIL; // stack fail
	}
}
// dump the stack
void Stack::stackdump()
{

	if(stack_index != 0)
	{


	cout << "\n************** stack dump **************\n";
	// current dump of items in the stack
	for(int i = 0; i < stack_index; i++)
	{
		if(int_stack[i] != 0)
		{
			cout << "\n" << int_stack[i] << "\n";
		}
	}
	cout << "\n***************************************\n";
	}
}

