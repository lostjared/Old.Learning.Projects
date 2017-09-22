// the mind header file
// heres the mind header file

#include "logic.h"
#include <iostream.h>
typedef unsigned short layer;
typedef unsigned long  mind_instruction;

// enumerated constants

enum { SUB_MIND,CON_MIND,SUPER_MIND };


// basic layers working together to produce illusion

// structure prototype of subcioncous mind
struct SubMind
{
	JB_LogicObject mind_memory;
	JB_LogicObject* whole_memory;
	void thought();
	void init(JB_LogicObject* wmem);
};
// structure prototype of concious mind
struct ConMind
{
	JB_LogicObject mind_memory;
	JB_LogicObject* whole_memory;
	void thought();
	void init(JB_LogicObject* wmem);
};
// structur eprototype of superconcious mind
struct SuperMind
{
	JB_LogicObject mind_memory[1];// double reared mind power
	JB_LogicObject* whole_memory;
	void thought();
	void init(JB_LogicObject* wmem);
};

// mind of life object prototype
class Mind
{

	JB_LogicObject instruction_memory;
	layer layer_focus;
	SuperMind superM;
	SubMind   subM;
	ConMind   conM;

public:

	void InitilzeLifeCycle();
	void ContinueFrom(char* filename);
	void Destruction();
	void SetMindFocus(layer layer_focus);
	void SignalInstruction(mind_instruction mindI);
	void thought();
};
