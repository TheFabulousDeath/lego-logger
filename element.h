#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <stdlib.h>
#include <stdio.h>

#define _MAXPARTS 2000
#define _ERRORPART NULL
#define _ERRORAM 0
#define _ERRORID -1

typedef struct PartElement
{
	int ID;
	int amount;
}*Part;

Part mkerrorel(){return _ERRORPART;}

Part mkEmptyPart(){
	Part new = calloc(1, sizeof(struct PartElement));
	if(new != NULL) return new;
	else {
		return NULL;
	}
}

int mkerroram(){return _ERRORAM;}

int mkerrorid(){return _ERRORID;}

void destroyPart(Part e){
	free(e);
	e = NULL;
}

Part editPart(Part part, int _amount){
	if(part->amount == _ERRORAM || part->ID == _ERRORID || part == _ERRORPART){
		fprintf(stderr, "Faulty element detected, entry removed");
		destroyPart(part);
		return _ERRORPART;
	}
	else part->amount = _amount;
	return part;
}

Part newPart(int id, int amount)
{
	Part new = mkEmptyPart();
	if(id == _ERRORID || amount == _ERRORAM){
		destroyPart(new);
		return _ERRORPART;
	}
	new->ID = id;
	new->amount = amount;
	return new;
}

#endif /* ELEMENT_H_ */
