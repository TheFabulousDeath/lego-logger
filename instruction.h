#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#define INSTRUCTIONSIZE 8
#define _ERRORINSTRUCTION -1
#define DEFAULT 0

#include <time.h> //including timestamp
#include <ctype.h> //uppercasing
#include <stdlib.h>
#include "element.h"
#include "stack.h"

typedef struct instructionElement{
	int instrNum;
	int partNum;
	int amount;
	int timestamp;
	struct instructionElement * nextp;
}*instruction;

_instRef initInstruction(){
	_instRef new = malloc(sizeof(instructionElem));
	new -> instrNum = _ERRORINSTRUCTION;
	new -> partNum = _ERRORID;
	new -> amount = _ERRORAM;
	new -> timestamp = time(NULL);
	new -> nextp = _ERROREL;
	return new;
}


List cancelInstruction(List instructionList, int* partshift, _part* partHead, _part partsArr){
	while(instructionList)
	{
		switch(head(instructionList)->instrNum){
		case(ADD):
			head(instructionList)->instrNum = REMOVE;
			head(instructionList)->timestamp = time(NULL);
			editPart(head(instructionList),partshift, partHead, partsArr);
			return tail(instructionList);
		case(REMOVE):
			head(instructionList)->instrNum = ADD;
			head(instructionList)->timestamp = time(NULL);
			editPart(head(instructionList),partshift, partHead, partsArr);
			return tail(instructionList);
		default:
			if(tail(instructionList)) {
				//memory Leck
				instructionList = tail(instructionList);
			} else return NULL;
		}
	}
	return NULL;
}

void printInstructionList(Value e)
{
	fprintf(stderr, "Instruction name: %s; Part Number: %d; Amount: %d\n", _instructions[e->instrNum], e->partNum, e->amount);
}
#endif /* INTERPRETER_H_ */
