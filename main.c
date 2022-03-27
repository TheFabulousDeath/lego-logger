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
#include "bool.h"
#include "runtimecomponent.h"


runtimeComponent initializeProgram(){
	runtimeComponent mainComponent = malloc(sizeof(runtimeComponent));
	mainComponent->instructionStack = initStack();
	mainComponent->storage = malloc(sizeof(storage));
	mainComponent->storage->partsArr = calloc(_MAXPARTS, sizeof(struct PartElement));
	loadParts(mainComponent->storage->partsArr);
	mainComponent->storage->partCounter = partsLen(mainComponent->storage->partsArr);
	return mainComponent;
}

int main()
{	
	runtimeComponent mainComponent = initializeProgram();
	printWelcomeMessage();
	char* userInput;
	instruction newinstruction;
	while(1)
	{
		userInput = getUserInput();
		newinstruction = buildInstruction(&userInput);
		workInstruction(newinstruction, mainComponent);
		free(userInput);
	}

	return 1;
}
