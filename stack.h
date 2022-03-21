#ifndef STACK_H_
#define STACK_H_


#define MAXSTACKSIZE 500
#define _ERRORSTACK NULL
#define _ERRORPOSITION -1

#include <stdlib.h>

typedef struct{
	int instrNum;
	int partNum;
	int amount;
	int timestamp;
	struct instruction* nextp;
}*instructionRef;


typedef struct stack
{
	instructionRef arr[MAXSTACKSIZE];
	int position;	
}*instructionStack;

int stackIsEmpty(instructionStack stack)
{
	if(stack->position == _ERRORPOSITION) return 1;
	else return 0;
}

instructionRef peek(instructionStack stack)
{
	if(stackIsEmpty(stack)) return NULL;
	//WIP: give instruction at top
}


#endif

