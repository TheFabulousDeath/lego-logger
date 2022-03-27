#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#define _ERRORINSTRUCTIONNUMBER -1
#define DEFAULT 0

#include <stdlib.h>
#include "element.h"

typedef struct instructionElement{
	int instrNum;
	int partID;
	int amount;
	struct instructionElement * nextp;
}*instruction;

instruction initInstruction(){
	instruction new = malloc(sizeof(struct instructionElement));
	new -> instrNum = _ERRORINSTRUCTIONNUMBER;
	new -> partID = _ERRORID;
	new -> amount = _ERRORAM;
	new -> nextp = _ERRORPART;
	return new;
}

void destroyInstruction(instruction instruction){
	free(instruction);
	instruction = NULL;
}

void changeInstructionNumber(instruction instruction, int instructionNumber){
	if(instructionNumber == _ERRORINSTRUCTIONNUMBER) return;
	instruction->instrNum = instructionNumber;
}

void changePartID(instruction instruction, int partID){
	if(partID == _ERRORID) return;
	instruction->partID = partID;
}

void changePartAmount(instruction instruction, int partAmount){
	if(partAmount == _ERRORAM) return;
	instruction->amount = partAmount;
}

#endif /* INTERPRETER_H_ */
