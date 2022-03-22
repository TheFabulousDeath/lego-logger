#ifndef _INSTRUCTIONHANDLER_H_
#ifdef _INSTRUCTIONHANDLER_H_


List workInstruction(List instruction, int* partshift, _part* partHead, _part partsArr)
{
	int index;
	switch(head(instruction)->instrNum)
	{
		case(ADD):
		case(REMOVE):
			editPart(head(instruction), partshift, partHead, partsArr);
			break;
		case(CSV):
			exportParts(partsArr);
			break;
		case(LF):
			index = lookForPart(partsArr, head(instruction)->partNum);
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



#endif


