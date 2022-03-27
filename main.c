#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//custom headers
#include "element.h"
#include "instruction.h"
#include "instructionhandler.h"
#include "usermessages.h"
#include "parser.h"
#include "parthandler.h"
#include "stack.h"
#include "userinput.h"

typedef enum {false, true} bool;

typedef struct storage{
	Part * partsArr;
	int storagePosition;
}*storage;

typedef struct runtimeComponent{
	 storage storage;
	instructionStack instructionStack;
}*runtimeComponent;

runtimeComponent initializeProgram(){
	runtimeComponent mainComponent = malloc(sizeof(runtimeComponent));
	mainComponent->instructionStack = initStack();
	mainComponent->storage->partsArr = calloc(_MAXPARTS, sizeof(struct PartElement));
	loadParts(mainComponent->storage->partsArr);
	mainComponent->storage->storagePosition = partsLen(mainComponent->storage->partsArr);
	return mainComponent;
}

int main()
{	
	runtimeComponent mainComponent = initializeProgram();
	printWelcomeMessage();
	char* orgbuff;
	while(1)
	{
		orgbuff = getUserInput();
		parseInput(orgbuff);
		instructionList = interpret(&buffer, instructionList);
		workInstruction(instructionList, partsArr);
		free(orgbuff);
	}

	return 1;
}
