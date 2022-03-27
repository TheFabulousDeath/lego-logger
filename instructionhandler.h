#ifndef _INSTRUCTIONHANDLER_H_
#define _INSTRUCTIONHANDLER_H_

#include "parser.h"
#include "stack.h"
#include "parthandler.h"
#include "usermessages.h"
void workInstruction(instruction instruction, runtimeComponent mainComponent)
{
	int index;
	switch(instruction->instrNum)
	{
		case(ADD):
		case(REMOVE):
			editPartInArray(instruction, mainComponent->storage->storagePosition, mainComponent->storage->partsArr);
			push(mainComponent->instructionStack,instruction);
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
			//return cancelInstruction(instruction, partshift, partHead, partsArr);
			break;
		case(HELP):
			printMainHelp();
			break;
	}
}
/*
void cancelInstruction(List instructionList, int* partshift, _part* partHead, _part partsArr){
	while(instructionList)
	{
		switch(head(instructionList)->instrNum){
		case(ADD):
			head(instructionList)->instrNum = REMOVE;
			head(instructionList)->timestamp = time(NULL);
			editPartInArray(head(instructionList),partshift, partHead, partsArr);
			return tail(instructionList);
		case(REMOVE):
			head(instructionList)->instrNum = ADD;
			head(instructionList)->timestamp = time(NULL);
			editPartInArray(head(instructionList),partshift, partHead, partsArr);
			return tail(instructionList);
		default:
			if(tail(instructionList)) {
				//memory Leck
				instructionList = tail(instructionList);
			} else return NULL;
		}
	}
	return NULL;
}
*/
#endif


