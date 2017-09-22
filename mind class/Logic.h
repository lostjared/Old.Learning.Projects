// the logic objects
// jared bruni

#include <windows.h>

// theory
// there can be one logic unit object
// that all sub objects have the abilty to get information from


class JB_LogicObject
{
public:
	// static global variables values
    long long_var;
    unsigned long ulong_var;
    short short_var;
    unsigned short ushort_var;
    char* str_var;
    int  int_var;
    unsigned int uint_var;
    bool bool_var;
    float float_var;
    double double_far;

	// memory stack

	// memory pointer array
 
	// some quick often used operations
	// a set of always accessible
	// areas of memory which can be
	// set, that everyone else can see

	void int_set(int);
	void uint_set(unsigned int);
	int  int_get();
	unsigned int uint_get();
	void long_set(long);
	long long_get();
	void ulong_set(unsigned long);
	unsigned long ulong_get();
	void short_set(short);
	short short_get();
	void ushort_set(unsigned short);
	unsigned short ushort_get();
	void float_set(float);
	float float_get();

	//  operations on parts of memory
	void iadd(int*, int);
	void iclear(int*);// set NULL
	void isubtract(int*, int);
	void idiv(int*, int);

	void ladd(long*,long);
	void lclear(long*);
	void ldiv(long*,long);
	void lsubtract(long*,long);

};
