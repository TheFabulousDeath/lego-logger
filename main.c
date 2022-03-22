#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//custom headers
#include "element.h"
#include "instruction.h"
#include "usermessages.h"

typedef enum {false, true} bool;

void printInst(List l){iterate(l, printInstructionList);}

void initializeProgram(_part){
	stack instructionStack = initStack();
}
void restartProgram();//In case of an error this should reinitialize the program to reach a usable state.

int main()
{	
	printWelcomeMessage();
	
	char* buffer;
	size_t bufferSize = 100;
	_part partsArr = calloc(_MAXPARTS, sizeof(_ELEMENT)); //struct that includes a pointer to an_ELEMENT
	loadParts(partsArr);
	_part partsHead = partsArr;
	int partshift = partsLen(partsArr);
	int lastTimestamp = time(NULL);
	while(1)
	{
	printf("  > ");
	buffer = (char *) calloc(bufferSize, sizeof(char));
	char** orgbuff = &buffer;
	if(buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}
	getline(&buffer, &bufferSize, stdin);
	instructionList = interpret(&buffer, instructionList);
	if(head(instructionList) && head(instructionList)->timestamp >= lastTimestamp)
	{
		instructionList = workInstruction(instructionList, &partshift, &partsHead, partsArr);
	}
	lastTimestamp = time(NULL);
	free(orgbuff);
	}
	return 1;
}
