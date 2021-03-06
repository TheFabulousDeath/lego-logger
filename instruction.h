/*	interpret() takes an input and returns a full instruction
 * makeInstruction -> makes instruction from string
 * initInstruction -> initializes instruction from ERRORELEMENTS
 *
*/

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


typedef enum {False ,True} Bool;
typedef _instRef Value;


typedef struct _list {
	Value val;
	struct _list *next;
} Elem, *List;

typedef void (* VProc )( Value );

List init () { return NULL; }

Bool empty(List l) { return l == NULL; }

List insert(Value v, List l)
{
	List e = malloc(sizeof(Elem));
	e->val = v;
	e->next = l;
	return e;
}

Value head(List l)
{
	if(l) return l->val;
	return DEFAULT;
}

List tail(List l) { return l ? l->next : l; }

Value nth(List l, unsigned int n)
{
	return n>0 ? nth(tail(l),n-1) : head(l);
}
Bool isin(Value n, List l)
{
	return empty(l) ? False
	: (head(l) == n ? True
	: isin(n,tail(l)));
}

void iterate(List l, VProc p)
{
	for (;! empty(l);l=tail(l)) p(head(l));
}

List append(List la , List lb)
{
	return la ? insert(head(la),append(tail(la),lb))
	: lb;
}

Value last(List l)
{
	if(l) return l->next ? last(l->next) : l->val;
	else printf("{last} empty list\n");
	return DEFAULT;
}

unsigned int length(List l)
{
	return empty(l) ? 0 : 1+ length(tail(l));
}

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
