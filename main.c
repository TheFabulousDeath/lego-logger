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

int main(int argc, *char argv[])
{	

	printWelcomeMessage();

	_part partsHead = partsArr;
	int partshift = partsLen(partsArr); //do I need to keep track of the length?

	while(1)
	{
		printf("  >");
		char* buffer = calloc(bufferSize, sizeof(char));
		char** orgbuff = &buffer;
		if(buffer == NULL)
		{
			perror("Unable to allocate buffer");
			exit(1);
		}
		size_t bufferSize = 100;
		getline(&buffer, &bufferSize, stdin);
		instructionList = interpret(&buffer, instructionList);
		workInstruction(instructionList, &partshift, &partsHead, partsArr);
		lastTimestamp = time(NULL);
		free(orgbuff);
	}
	return 1;
}
