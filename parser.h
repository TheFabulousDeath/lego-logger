#ifndef LEGO_LOGGER_PARSER_H_
#define LEGO_LOGGER_PARSER_H_

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "element.h"

char* instructionLiterals[] = {
		"ADD",
		"LF",
		"LIST",
		"CSV",
		"REMOVE",
		"CANCEL",
		"EXIT",
		"HELP",
		"END"
};

typedef enum {
	ADD,
	LF,
	LIST,
	CSV,
	REMOVE,
	CANCEL,
	EXIT,
	HELP,
	END
} instructionNumbers;

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

int readMainInstruction(char** input)
{
	char* uppercase = calloc(100, sizeof(char));
	//make uppercase
	for (int i = 0; i < strlen(*input); i++)
	{
		uppercase[i] = toupper((*input)[i]);
	}
	memcpy(*input, uppercase, strlen(uppercase));
	free(uppercase);
	//scan for main instruction
	for(int i =0; strcmp(instructionLiterals[i], "END"); i++)
	{
		if(strstr(*input, instructionLiterals[i])){
			*input += strlen(instructionLiterals[i]);
			return i;
		}
	}
	return _ERRORINSTRUCTIONNUMBER;
}

instruction buildInstruction(char** input)
{
	instruction newInstruction = initInstruction();
	switch(readMainInstruction(input))
	{
	case ADD:
		newInstruction->instrNum = ADD;
		newInstruction->partID = readIntSequence(input);
		if(newInstruction->partID == _ERRORAM) break;
		newInstruction->amount = readIntSequence(input);
		if(newInstruction->amount == _ERRORAM) newInstruction->amount = 1;
		break;
	case LF:
		newInstruction->instrNum = LF;
		newInstruction->partID = readIntSequence(input);
		if(newInstruction->partID == _ERRORAM) break;
		break;
	case LIST:
		newInstruction->instrNum = LIST;
		break;
	case CSV:
		newInstruction->instrNum = CSV;
		break;
	case REMOVE:
		newInstruction->instrNum = REMOVE;
		newInstruction->partID = readIntSequence(input);
		if(newInstruction->partID == _ERRORAM) break;
		newInstruction->amount = readIntSequence(input);
		if(newInstruction->amount == _ERRORAM) break;
		break;
	case CANCEL:
		newInstruction->instrNum = CANCEL;

		break;
	case EXIT:
		exit(1);
	case HELP:
		newInstruction->instrNum = HELP;
		break;
	case _ERRORINSTRUCTIONNUMBER:
		printf("Kein g\x81ltiger Befehl.\n");
		break;
	default:
		break;
	}
	return newInstruction;
}

#endif /* LEGO_LOGGER_PARSER_H_ */
