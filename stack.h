#ifndef STACK_H_
#define STACK_H_

#include <stdlib>
#include "instruction.h"

#define MAXSTACKSIZE 500
#define _ERRORSTACK NULL
#define _ERRORPOSITION -1

typedef struct stack
{
	void* value[MAXSTACKSIZE];
	int position;	
}stackElement, *stackRef;

int stackIsEmpty(stackRef stack)
{
	if(stack->position == _ERRORPOSITION) return 1;
}

instructionElement peek(stackRef stack)
{
	if(stackIsEmpty(stack)) return NULL;	
	//WIP: give instruction at top
}








#endif

