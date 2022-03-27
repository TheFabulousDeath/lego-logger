#ifndef _PARTHANDLER_H_
#define _PARTHANDLER_H_

int partsLen(Part * partsArr){
	for(int i = 0; i < _MAXPARTS;i++)
	{
		if(partsArr[i]->ID == _ERRORID || partsArr[i]->amount == _ERRORAM) return i;
	}
	return _MAXPARTS;
}

int compareParts(const void* a, const void* b){
	return (((_part)b)->ID - ((_part)a)->ID);
}


void printParts(Part * partsArr)
{
	qsort(partsArr,partsLen(partsArr),sizeof(struct PartElement), compareParts);
	for(int i = 0; i < _MAXPARTS;i++)
	{
		if(partsArr[i].ID == _ERRORID || partsArr[i].amount == _ERRORAM) break;
		printf("		%d   %d\n", partsArr[i].ID, partsArr[i].amount);
	}
}


void exportParts(Part * partsArr){
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

int lookForPart(Part * partsArr, int lfID){
	for(int i = 0; i < _MAXPARTS; i++, partsArr++)
	{
		if((*partsArr)->amount == _ERRORAM) break;
		if((*partsArr)->ID == lfID)
		{
			return i;
		}
	}
	return -1;
}
void removePart(int index, Part * partsArr)
{
	for(int i = index; i<_MAXPARTS-1; i++)
	{
		partsArr[i] = partsArr[i+1];
	}
}

void saveParts(Part * partsArr)
{
	FILE* savefile = fopen("partlist.llf", "w");
	if(!savefile){ perror("Bauteile konnten nicht gespeichert werden"); return;}
	fwrite(partsArr, sizeof(struct PartElement), _MAXPARTS, savefile);
	fclose(savefile);
}

int addPartToArray(instruction instruction, int partshift, Part * partsArr)
{
	if(partshift >= _MAXPARTS) return -1;
	partsArr[partshift] = newPart(instruction->partID, instruction->amount);
	(partshift)++;
	printf("Bauteil(e) hinzugef\x81gt. ID: %d, Anzahl %d.\n", instruction->partID, instruction->amount);
	saveParts(partsArr);
	return partshift;
}

int editPartInArray(instruction instruction, int partshift, Part * partsArr)
{
	int index = lookForPart(partsArr, instruction->partID);
	if(index == -1 && inst->instrNum != REMOVE) return addPartToArray(instruction, partshift, partsArr);
	if(instruction->instrNum == ADD) {
		partsArr[index].amount += instruction->amount;
		printf("Bauteil(e) hinzugef\x81gt. ID: %d, Anzahl %d.\n", instruction->partID, instruction->amount);
	}
	else if(instruction->instrNum == REMOVE){
		partsArr[index].amount -= instruction->amount;
		printf("Bauteil(e) entfernt. ID: %d, Anzahl %d.\n", instruction->partID, instruction->amount);
	}
	if(partsArr[index].amount <= 0) removePart(index, partsArr);
	saveParts(partsArr);
	return index;
}

void loadParts(Part * partsArr)
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
