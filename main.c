#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//custom headers
#include "element.h"
#include "instruction.h"
#include "usermessages.h"

typedef enum {false, true} bool;

void printInst(List l){iterate(l, printInstructionList);}

void initializeProgram(_part* partsArr){
	stack instructionStack = initStack();
l
	*partsArr = calloc(_MAXPARTS, sizeof(_ELEMENT)); //Creating the global
	loadParts(partsArr);
}

void restartProgram();//In case of an error this should reinitialize the program to reach a usable state.

char* getUserInput()
{
	printf("  >");
	size_t bufferSize = 100;
	char* buffer = calloc(bufferSize, sizeof(char));
	if(buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}
	getline(&buffer, &bufferSize, stdin);
	return buffer;
}

int main(int argc, *char argv[])
{	

	printWelcomeMessage();
	char* orgbuff = getUserInput();
	_part partsHead = partsArr;
	int partshift = partsLen(partsArr); //do I need to keep track of the length?

	while(1)
	{

		instructionList = interpret(&buffer, instructionList);
		workInstruction(instructionList, &partshift, &partsHead, partsArr);
		lastTimestamp = time(NULL);
		free(orgbuff);
	}
	return 1;
}
