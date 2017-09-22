// the logical objects header
// jared bruni
#include "Logic.h"

// math operations

void JB_LogicObject::int_set(int ix)
{
	int_var = ix;
}

int JB_LogicObject::int_get()
{
	return int_var;
}

void JB_LogicObject::uint_set(unsigned int ix)
{
	uint_var = ix;
}

unsigned int JB_LogicObject::uint_get()
{
	return uint_var;
}

void JB_LogicObject::long_set(long x)
{
	long_var = x;
}

long JB_LogicObject::long_get()
{
	return long_var;
}

void JB_LogicObject::ulong_set(unsigned long x)
{
	ulong_var = x;
}

unsigned long JB_LogicObject::ulong_get()
{
	return ulong_var;
}

void JB_LogicObject::short_set(short x)
{
	short_var = x;
}

short JB_LogicObject::short_get()
{
	return short_var;
}

void JB_LogicObject::ushort_set(unsigned short x)
{
	ushort_var = x;
}

unsigned short JB_LogicObject::ushort_get()
{
	return ushort_var;
}

// nessicary operations

void JB_LogicObject::float_set(float ix)
{
	float_var = ix;
}

float JB_LogicObject::float_get()
{
	return float_var;
}

void JB_LogicObject::iadd(int* pint, int x)
{
	pint = pint + x;
}

void JB_LogicObject::iclear(int* pint)
{
	pint = NULL;
}

void JB_LogicObject::idiv(int* ix, int xz)
{
	
}

void JB_LogicObject::isubtract(int* pint, int x)
{
	pint = pint - x;
}

void JB_LogicObject::ladd(long* l,long x)
{
	l = l + x;
}

void JB_LogicObject::lclear(long* l)
{
	l = NULL;
}

void JB_LogicObject::lsubtract(long* l,long x)
{
	l = l - x;
}


