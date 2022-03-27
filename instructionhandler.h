#ifndef _INSTRUCTIONHANDLER_H_
#define _INSTRUCTIONHANDLER_H_

#include "parser.h"

void workInstruction(instruction instruction)
{
	int index;
	switch(instruction->instrNum)
	{
		case(ADD):
		case(REMOVE):
			editPartInArray(instruction);
			break;
		case(CSV):
			exportParts(partsArr);
			break;
		case(LF):
			index = lookForPart(partsArr, instruction->partNum);
			if(index > -1)
			{
				printf("ID: %d, Anzahl: %d\n", partsArr[index].ID, partsArr[index].amount);
			}else printf("Bauteil nicht in der Liste gefunden.\n");

			//Nach Bildern suchen
			char buffer1[200] = "start https://duckduckgo.com/?q=lego+";
			char* buffer2 = calloc(50, sizeof(char));
			sprintf(buffer2, "%d",head(instruction)->partNum);
			strcat(buffer2, "^&iax=images^&ia=images");
			strcat(buffer1, buffer2);
			system(buffer1);

			//Lego Seite
			/*
			strcpy(buffer1, "start https://www.lego.com/de-de/page/static/pick-a-brick?query=");
			sprintf(buffer2, "%d",head(instruction)->partNum);
			strcat(buffer1, buffer2);
			system(buffer1);
			*/
			break;
		case(LIST):
			printParts(partsArr);
			break;
		case(CANCEL):
			return cancelInstruction(instruction, partshift, partHead, partsArr);
			break;
		case(HELP):
			printMainHelp();
			break;
	}
	return instruction;
}

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

#endif


