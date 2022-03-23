#ifndef STACK_H_
#define STACK_H_

#include <stdlib.h>

#define _MAXSTACKSIZE 200
#define _ERRORSTACK NULL
#define _ERRORPOSITION -1

enum Bool;
struct instructionStack;
struct stack;

struct instructionStack newStack();
enum Bool stackIsEmpty(instructionStack);
struct instruction peekStack(instructionStack);
struct instruction pop(instructionStack);
enum Bool push(instructionStack, instruction);
struct instructionStack newStack();

typedef struct stack
{
	instruction arr[_MAXSTACKSIZE];
	int position;	
}*instructionStack;

instructionStack newStack()
{
	return NULL;
}

instructionStack initStack()
{
	instructionStack stack = newStack();
	stack->arr = malloc(sizeof(struct instructionStack) * _MAXSTACKSIZE);
	stack->position = _ERRORPOSITION;
}

Bool stackIsEmpty(instructionStack stack)
{
	if(stack->position == _ERRORPOSITION) return TRUE;
	else return FALSE;
}

instruction peekStack(instructionStack stack)
{
	if(stackIsEmpty(stack)) return NULL;
	else return (stack->arr)[stack->position];
}

instruction pop(instructionStack stack)
{
	if(stackIsEmpty(stack)) return NULL;
	else 
	{
		instruction returnValue = peekStack(stack);
		stack->position -= 1;
		return returnValue;
	}
}

Bool push(instructionStack stack, instruction validInstruction)
{
	if(stack->position +1 == _MAXSTACKSIZE || stack->position < _ERRORPOSITION)
	{ //if stack overflow
		fprintf(stderr, "instructionStack overflow");
		return False;
	}else
	{ //stack position is in range
		stack->position++;
		(stack->arr)[stack->position] = validInstruction;
		return True;
	}
}

#endif

