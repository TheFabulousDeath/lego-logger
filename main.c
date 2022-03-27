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


#define MAXTEST 3

char* testArray[MAXTEST] = {
		"add 5 5",
		"remove 5 6",
		"cancel"
};
int testCounter;


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
	testCounter = 0;
	instruction newInstruction;
	while(1)
	{
		userInput = calloc(200, 1);
		//if(testCounter > MAXTEST) exit(1);
		//strcpy(userInput, testArray[testCounter]);
		userInput = getUserInput();
		testCounter++;
		newInstruction = buildInstruction(&userInput);
		workInstruction(newInstruction, mainComponent);

		free(userInput);
	}

	return 1;
}
