/*
 * parser.h
 *
 *  Created on: 21.03.2022
 *      Author: vince
 */

#ifndef LEGO_LOGGER_PARSER_H_
#define LEGO_LOGGER_PARSER_H_

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

#endif /* LEGO_LOGGER_PARSER_H_ */
