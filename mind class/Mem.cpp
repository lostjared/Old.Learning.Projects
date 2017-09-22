//Memory Class Source File
// Jared Bruni

#include "mem.h"

// memory object create new
void JB_MemoryObject::CreateNew(int integer_max,int string_max,int short_max, int long_max, int bool_max, int double_max, int float_max)
{
	jb_string = new memsel_String[string_max];
	jb_integer = new memsel_Integer[integer_max];
	jb_short = new memsel_Short[short_max];
	jb_double = new memsel_Double[double_max];
	jb_long = new  memsel_Long[long_max];
	jb_float = new memsel_Float[float_max];
	jb_bool = new memsel_Bool[bool_max];
}
// memory object load
void JB_MemoryObject::Load(char* filename)
{
	// load up the memory objects from a binary file

}

// memory object release
void JB_MemoryObject::Release()
{
	delete jb_string;
	jb_string = 0;
	delete jb_integer;
	jb_integer = 0;
	delete jb_short;
	jb_short = 0;
	delete jb_double;
	jb_double = 0;
	delete jb_long;
	jb_long = 0;
	delete jb_float;
	jb_float = 0;
	delete jb_bool;
	jb_bool = 0;
}

