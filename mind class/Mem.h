// Memory class header file
// jared bruni

/*

  Heres the real guts of each of the objects
  every single peice of memory, has 2 values
  its name, (how its found in memory)
  and what value it holds.
*/

#include <windows.h>
#include <fstream.h>


typedef unsigned short JB_VARID;

// integer memory value
struct memsel_Integer
{
	int var;
	JB_VARID varid;
};
// short memory value
struct memsel_Short
{
	short var;
	JB_VARID varid;
};
// long memory value
struct memsel_Long
{
	long var;
	JB_VARID varid;
};
// short memory string
struct memsel_String
{
	char* var;
	JB_VARID varid;
};
// boolean memory structure
struct memsel_Bool
{
	bool var;
	JB_VARID varid;
};
// floating point variable
struct memsel_Float
{
	float var;
	JB_VARID varid;
};
// double  point variable
struct memsel_Double
{
	double var;
	JB_VARID varid;
};

// A VM data object prototype
class JB_MemoryObject
{
public:
	memsel_String* jb_string;
	memsel_Short*  jb_short;
	memsel_Long*   jb_long;
	memsel_Bool*   jb_bool;
	memsel_Double* jb_double;
	memsel_Float*  jb_float;
	memsel_Integer* jb_integer;

	// create the array sizes on startup
	void CreateNew(int integer_max,int string_max, int short_max, int long_max, int bool_max, int double_max, int float_max);
	void Load(char* filename);
	void Release();
};
