#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#define INSTRUCTIONSIZE 8
#define _ERRORINSTRUCTION -1

#include <time.h> //including timestamp
#include <ctype.h> //uppercasing
#include <stdlib.h>
#include "element.h"

typedef enum {
	ADD,
	LF,
	LIST,
	CSV,
	REMOVE,
	CANCEL,
	EXIT,
	HELP
} _constInstruction;


typedef struct instruction{
	int instrNum;
	int partNum;
	int amount;
	int timestamp;
	struct instruction* nextp;
}instructionElem,*_instRef;


char* _instructions[INSTRUCTIONSIZE] = {
		"ADD",
		"LF",
		"LIST",
		"CSV",
		"REMOVE",
		"CANCEL",
		"EXIT",
		"HELP"
};


#define DEFAULT 0

int readMainInstruction(char** input)
{
	char* uppercase = calloc(100, sizeof(char));
	//make uppercase
	for (int i = 0; i < strlen(*input); i++)
	{
		uppercase[i] = toupper((*input)[i]);
	}
	strcpy(*input, uppercase);
	free(uppercase);
	//scan for main instruction
	for(int i =0; i < INSTRUCTIONSIZE; i++)
	{
		if(strstr(*input, _instructions[i])){
			*input += strlen(_instructions[i]);
			return i;
		}
	}
	return _ERRORINSTRUCTION;
}

_instRef initInstruction(){
	_instRef new = malloc(sizeof(instructionElem));
	new -> instrNum = _ERRORINSTRUCTION;
	new -> partNum = _ERRORID;
	new -> amount = _ERRORAM;
	new -> timestamp = time(NULL);
	new -> nextp = _ERROREL;
	return new;
}

int readIntSequence(char** input)
{
	int num = 0;
	while(!isdigit(**input) && **input != '\0'){
		(*input)++;
	}
	while(isdigit(**input) && **input != '\0'){
		num = num*10 + (**input-'0');
		(*input)++;
	}
	return num;
}

_instRef makeInstruction(char** input)
{
	_instRef newInstruction = initInstruction();
	switch(readMainInstruction(input))
	{
	case ADD:
		newInstruction->instrNum = ADD;
		newInstruction->partNum = readIntSequence(input);
		if(newInstruction->partNum == _ERRORAM) {return _ERROREL;}
		newInstruction->amount = readIntSequence(input);
		if(newInstruction->amount == _ERRORAM) newInstruction->amount = 1;
		break;
	case LF:
		newInstruction->instrNum = LF;
		newInstruction->partNum = readIntSequence(input);
		if(newInstruction->partNum == _ERRORAM) return _ERROREL;
		break;
	case LIST:
		newInstruction->instrNum = LIST;
		break;
	case CSV:
		newInstruction->instrNum = CSV;
		break;
	case REMOVE:
		newInstruction->instrNum = REMOVE;
		newInstruction->partNum = readIntSequence(input);
		if(newInstruction->partNum == _ERRORAM) return _ERROREL;
		newInstruction->amount = readIntSequence(input);
		if(newInstruction->amount == _ERRORAM) return _ERROREL;
		break;
	case CANCEL:
		newInstruction->instrNum = CANCEL;

		break;
	case EXIT:
		exit(1);
	case HELP:
		newInstruction->instrNum = HELP;
		break;
	case _ERRORINSTRUCTION:
		printf("Kein g\x81ltiger Befehl.\n");
		break;
	default:
		return _ERROREL;
	}
	return newInstruction;
}

List interpret(char** input, List l)
{
	_instRef inst = makeInstruction(input);
	if(inst == _ERROREL)
	{
		return _ERROREL;
	}
	if(inst->instrNum == _ERRORINSTRUCTION){
		return _ERROREL;
	}
	/*
	if(inst->instrNum == LF || inst->instrNum == LIST || inst->instrNum == CANCEL || inst->instrNum == CSV)
	{
		return l;
	*/
	return insert(inst, l);
}

void printInstructionList(Value e)
{
	fprintf(stderr, "Instruction name: %s; Part Number: %d; Amount: %d\n", _instructions[e->instrNum], e->partNum, e->amount);
}
#endif /* INTERPRETER_H_ */
