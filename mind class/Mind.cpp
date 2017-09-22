// perspective of mind
// jared bruni
#include "mind.h"

// the main focus of attention

// starting it
void Mind::InitilzeLifeCycle()
{
	subM.init(&instruction_memory);
	conM.init(&instruction_memory);
	superM.init(&instruction_memory);

	SetMindFocus(CON_MIND);
}

void Mind::ContinueFrom(char* filename)
{

}

// as you can see each one is initlized
void Mind::Destruction()
{

	// save file
	// with name of day it exisited
	// then a whole can read up each day,
	// (load them all backwards in order
	// of when they occoured. so the last thing
	// that happend is first in your mind

}
// set the current mind focus state
void Mind::SetMindFocus(layer layerX)
{
layer_focus = layerX;
}

// signal instruction
// ability to signal that instruction using the mind memory object
void Mind::SignalInstruction(mind_instruction mindI)
{
	switch(mindI)
	{
	case 0:
		{

		}
		break;
	}
}

void Mind::thought()
{
	switch(layer_focus)
	{
	case SUB_MIND:
		{
			subM.thought();
			conM.thought();
			superM.thought();
		}
		break;
	case CON_MIND:
		{
			conM.thought();
			superM.thought();
			subM.thought();
		}
		break;
	case SUPER_MIND:
		{
			superM.thought();
			subM.thought();
			conM.thought();
		}
		break;

	}

}

void SubMind::thought()
{

}

void SubMind::init(JB_LogicObject* wmem)
{
	whole_memory = wmem;
}

void ConMind::init(JB_LogicObject* wmem)
{
	whole_memory = wmem;
}

void SuperMind::init(JB_LogicObject* wmem)
{
	whole_memory = wmem;
}


void ConMind::thought()
{
	cout << "concious thought:";
}

void SuperMind::thought()
{

}


