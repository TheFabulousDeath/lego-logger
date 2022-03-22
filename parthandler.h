

#ifndef _PARTHANDLER_H_
#ifdef _PARTHANDLER_H_

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

#endif
