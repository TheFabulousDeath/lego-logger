#ifndef _PARTHANDLER_H_
#define _PARTHANDLER_H_

#include "runtimecomponent.h"

int partsLen(Part partsArr){
	for(int i = 0; i < _MAXPARTS;i++)
	{
		if(partsArr[i].ID == _ERRORID || partsArr[i].amount == _ERRORAM) return i;
	}
	return _MAXPARTS;
}

int compareParts(const void* a, const void* b){
	return (((Part)b)->ID - ((Part)a)->ID);
}


void printParts(Part partsArr)
{
	qsort(partsArr,partsLen(partsArr),sizeof(struct PartElement), compareParts);
	for(int i = 0; i < _MAXPARTS;i++)
	{
		if(partsArr[i].ID == _ERRORID || partsArr[i].amount == _ERRORAM) break;
		printf("		%d   %d\n", partsArr[i].ID, partsArr[i].amount);
	}
}


void exportParts(Part partsArr){
	FILE* csv = fopen("partList.csv", "w");
	if(csv == NULL) return;
	qsort(partsArr,partsLen(partsArr),sizeof(struct PartElement), compareParts);
	fprintf(csv, "Teilnummer;Anzahl;\n");
	for(int i = 0; i < _MAXPARTS;i++){
		if(partsArr[i].ID == _ERRORID || partsArr[i].amount == _ERRORAM) break;
		fprintf(csv, "%d;%d;\n", partsArr[i].ID, partsArr[i].amount);

		fflush(csv);
	}
	fclose(csv);
}

int lookForPart(Part partsArr, int lfID){
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
void removePart(int index, Part partsArr)
{
	for(int i = index; i<_MAXPARTS-1 || partsArr[i].ID == 0; i++)
	{
		partsArr[i] = partsArr[i+1];
	}
}

void saveParts(Part partsArr)
{
	FILE* savefile = fopen("partlist.llf", "w");
	if(!savefile){ perror("Bauteile konnten nicht gespeichert werden"); return;}
	fwrite(partsArr, sizeof(struct PartElement), _MAXPARTS, savefile);
	fclose(savefile);
}

int addPartToArray(instruction instruction, runtimeComponent mainComponent)
{
	if(mainComponent->storage->partCounter >= _MAXPARTS) return -1;
	Part new = newPart(instruction->partID, instruction->amount);
	if(new)
	{
		mainComponent->storage->partsArr[mainComponent->storage->partCounter] = *new;
		(mainComponent->storage->partCounter)++;
		printf("Bauteil(e) hinzugef\x81gt. ID: %d, Anzahl %d.\n", instruction->partID, instruction->amount);
		saveParts(mainComponent->storage->partsArr);
	}
	return mainComponent->storage->partCounter;
}

int editPartInArray(instruction instruction, runtimeComponent mainComponent)
{
	int index = lookForPart(mainComponent->storage->partsArr, instruction->partID);
	if(index == -1 && instruction->instrNum == ADD)
		return addPartToArray(instruction, mainComponent);
	else if(index == -1 && instruction->instrNum == REMOVE)
		return index;

	if(instruction->instrNum == ADD)
	{
		mainComponent->storage->partsArr[index].amount += instruction->amount;
		printf("Bauteil(e) hinzugef\x81gt. ID: %d, Anzahl %d.\n", instruction->partID, instruction->amount);
	} else if(instruction->instrNum == REMOVE)
	{
		mainComponent->storage->partsArr[index].amount -= instruction->amount;
		printf("Bauteil(e) entfernt. ID: %d, Anzahl %d.\n", instruction->partID, instruction->amount);
		if(mainComponent->storage->partsArr[index].amount < 0)
			instruction->amount += mainComponent->storage->partsArr[index].amount;
	}
	if(instruction->instrNum == ADD)
		instruction->instrNum = REMOVE;
	else
		instruction->instrNum = ADD;

	if(mainComponent->storage->partsArr[index].amount <= 0)
		removePart(index, mainComponent->storage->partsArr);

	saveParts(mainComponent->storage->partsArr);
	return index;
}

void loadParts(Part partsArr)
{
	FILE* savefile = fopen("partlist.llf", "r");
	if(!savefile){
		printf("Keine Teil%cbersicht gefunden. Leere Liste erstellt.\n", '\x81');
		saveParts(partsArr);
		return;
	}
	fread(partsArr, sizeof(struct PartElement), _MAXPARTS, savefile);
	fclose(savefile);
}

#endif
