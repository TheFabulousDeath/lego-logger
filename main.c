#include <string.h>
#include <stdlib.h>
#include <unistd.h>
//custom headers
#include "element.h"
#include "instruction.h"

typedef enum {false, true} bool;

void printInst(List l){iterate(l, printInstructionList);}

int partsLen(_part partsArr){
	for(int i = 0; i < _MAXPARTS;i++)
	{
		if(partsArr[i].ID == _ERRORID || partsArr[i].amount == _ERRORAM) return i;
	}
	return _MAXPARTS;
}

int compareParts(const void* a, const void* b){
	return (((_part)b)->ID - ((_part)a)->ID);
}


void printParts(_part partsArr)
{
	qsort(partsArr,partsLen(partsArr),sizeof(_ELEMENT), compareParts);
	for(int i = 0; i < _MAXPARTS;i++)
	{
		if(partsArr[i].ID == _ERRORID || partsArr[i].amount == _ERRORAM) break;
		printf("		%d   %d\n", partsArr[i].ID, partsArr[i].amount);
	}
}


void exportParts(_part partsArr){
	FILE* csv = fopen("partList.csv", "w");
	if(csv == NULL) return;
	fprintf(csv, "Teilnummer;Anzahl;\n");
	for(int i = 0; i < _MAXPARTS;i++){
		if(partsArr[i].ID == _ERRORID || partsArr[i].amount == _ERRORAM) break;
		fprintf(csv, "%d;%d;\n", partsArr[i].ID, partsArr[i].amount);

		fflush(csv);
	}
	fclose(csv);
}

int lookForPart(_part partsArr, int lfID){
	for(int i = 0; i < _MAXPARTS; i++, partsArr++)
	{
		if(partsArr->amount == _ERRORAM) break;
		if(partsArr->ID == lfID)
		{
			return i;
		}
	}
	return -1;
}
void removePart(int index, _part partsArr)
{
	for(int i = index; i<_MAXPARTS-1; i++)
	{
		partsArr[i] = partsArr[i+1];
	}
}

void saveParts(_part partsArr)
{
	FILE* savefile = fopen("partlist.llf", "w");
	if(!savefile){ perror("Bauteile konnten nicht gespeichert werden"); return;}
	fwrite(partsArr, sizeof(_ELEMENT), _MAXPARTS, savefile);
	fclose(savefile);
}

int addPart(_instRef inst, int* partshift, _part* partHead, _part partsArr)
{
	if(*partshift >= _MAXPARTS) return -1;
	partsArr[*partshift] = *add(inst->partNum, inst->amount);
	(*partHead)++;
	(*partshift)++;
	printf("Bauteil(e) hinzugef\x81gt. ID: %d, Anzahl %d.\n", inst->partNum, inst->amount);
	saveParts(partsArr);
	return *partshift;
}

int editPart(_instRef inst, int* partshift, _part* partHead, _part partsArr)
{
	int index = lookForPart(partsArr, inst->partNum);
	if(index == -1 && inst->instrNum != REMOVE) return addPart(inst, partshift, partHead, partsArr);
	if(inst->instrNum == ADD) {
		partsArr[index].amount += inst->amount;
		printf("Bauteil(e) hinzugef\x81gt. ID: %d, Anzahl %d.\n", inst->partNum, inst->amount);
	}
	else if(inst->instrNum == REMOVE){
		partsArr[index].amount -= inst->amount;
		printf("Bauteil(e) entfernt. ID: %d, Anzahl %d.\n", inst->partNum, inst->amount);
	}
	if(partsArr[index].amount <= 0) removePart(index, partsArr);
	saveParts(partsArr);
	return index;
}



List cancelInstruction(List instructionList, int* partshift, _part* partHead, _part partsArr){
	while(instructionList)
	{
		switch(head(instructionList)->instrNum){
		case(ADD):
			head(instructionList)->instrNum = REMOVE;
			head(instructionList)->timestamp = time(NULL);
			editPart(head(instructionList),partshift, partHead, partsArr);
			return tail(instructionList);
		case(REMOVE):
			head(instructionList)->instrNum = ADD;
			head(instructionList)->timestamp = time(NULL);
			editPart(head(instructionList),partshift, partHead, partsArr);
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

void loadParts(_part partsArr)
{
	FILE* savefile = fopen("partlist.llf", "r");
	if(!savefile){
		printf("Keine Teil%cbersicht gefunden. Leere Liste erstellt.\n", '\x81');
		saveParts(partsArr);
		return;
	}
	fread(partsArr, sizeof(_ELEMENT), _MAXPARTS, savefile);
	fclose(savefile);
}

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
			printf("Alle g\x81ltigen Befehlte lauten:\n    ADD - F\x81gt ein Bauteil hinzu. Beispiel: ADD 412314 41\n    LF - Sucht nach einem Bauteil und gibt den Eintrag zur%cck. Beispiel LF 412314\n    LIST - Listet alle Eintr\x84ge auf.\n    CSV - Erzeugt eine CSV Datei aus den Eintr\x84gen.\n    REMOVE - Reduziert den Betrag eines Bauteils. Beispiel: remove 412321 5\n    CANCEL - Macht die letzte Bauteil\x84nderung ungeschehen.\n    EXIT - F\x81hrt zur sofortigen Beendigung der Anwendung.\n    HELP - Ruft diese Ansicht auf.\n", '\x81');
			break;
	}
	return instruction;
}


int main()
{

	printf("Legologger Alpha v3.1 - Gib \"HELP\" ein um eine Ansicht aller Befehle zu erhalten.\n");

	List instructionList = init();
    char* buffer;
    size_t bufferSize = 100;

    _part partsArr = calloc(_MAXPARTS, sizeof(_ELEMENT)); //struct that includes a pointer to an_ELEMENT
    loadParts(partsArr);
    _part partsHead = partsArr;
    int partshift = partsLen(partsArr);
    int lastTimestamp = time(NULL);

    //int i = 0;
    //char* arr[6] = {"add 45 45", "add 4225 45", "add 445 12" ,"add 451235 2", "add 455123 90", "list"};
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
		//if(i == 6) exit(1);
		//strcpy(buffer, arr[i]);
		//i++;

		instructionList = interpret(&buffer, instructionList);
		//printInst(instructionList);
		if(head(instructionList) && head(instructionList)->timestamp >= lastTimestamp)
		{
			instructionList = workInstruction(instructionList, &partshift, &partsHead, partsArr);
		}
		lastTimestamp = time(NULL);
		free(orgbuff);
	}
	return 1;
}
