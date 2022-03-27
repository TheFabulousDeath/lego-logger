#ifndef _INSTRUCTIONHANDLER_H_
#define _INSTRUCTIONHANDLER_H_

#include "parser.h"
#include "stack.h"
#include "parthandler.h"
#include "usermessages.h"
#include "runtimecomponent.h"

void workInstruction(instruction instruction, runtimeComponent mainComponent)
{
	int index;
	if(instruction){
		switch(instruction->instrNum)
		{
			case(ADD):
			case(REMOVE):
				editPartInArray(instruction, mainComponent);
				if(instruction->isCancelled == False){
					instruction->isCancelled = True;
					push(mainComponent->instructionStack, instruction);
				}
				break;
			case(CSV):
				exportParts(mainComponent->storage->partsArr);
				break;
			case(LF):
				index = lookForPart(mainComponent->storage->partsArr, instruction->partID);
				if(index > -1)
				{
					printf("ID: %d, Anzahl: %d\n", mainComponent->storage->partsArr[index].ID, mainComponent->storage->partsArr[index].amount);
				}else printf("Bauteil nicht in der Liste gefunden.\n");

				break;
			case(LIST):
				printParts(mainComponent->storage->partsArr);
				break;
			case(CANCEL):
				workInstruction(pop(mainComponent->instructionStack), mainComponent);
				break;
			case(HELP):
				printMainHelp();
				break;
		}
	} else
	{
		printf("Error\n");
	}
}
#endif


