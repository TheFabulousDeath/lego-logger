#ifndef STACK_H_
#define STACK_H_

#include <stdlib.h>
#include "instruction.h"
#include "bool.h"

#define _MAXSTACKSIZE 2000
#define _ERRORSTACK NULL
#define _ERRORPOSITION -1

typedef struct stack
{
	instruction * instructionArray;
	int stackPosition;
}*instructionStack;

instructionStack initStack()
{
	instructionStack stack = malloc(sizeof(struct stack));
	stack->instructionArray = malloc(sizeof(instruction) * _MAXSTACKSIZE);
	stack->stackPosition = _ERRORPOSITION;
	return stack;
}

Bool stackIsEmpty(instructionStack stack)
{
	if(stack->stackPosition == _ERRORPOSITION) return True;
	else return False;
}

instruction peekStack(instructionStack stack)
{
	if(stackIsEmpty(stack)) return NULL;
	else return (stack->instructionArray)[stack->stackPosition];
}

instruction pop(instructionStack stack)
{
	if(stackIsEmpty(stack)) return NULL;
	else 
	{
		instruction returnValue = peekStack(stack);
		stack->stackPosition -= 1;
		return returnValue;
	}
}

Bool push(instructionStack stack, instruction validInstruction)
{
	if(stack->stackPosition +1 == _MAXSTACKSIZE || stack->stackPosition < _ERRORPOSITION)
	{ //if stack overflow
		fprintf(stderr, "instructionStack overflow");
		return False;
	}else
	{ //stack stackPosition is in range
		stack->stackPosition++;
		(stack->instructionArray)[stack->stackPosition] = validInstruction;
		return True;
	}
}


#endif

