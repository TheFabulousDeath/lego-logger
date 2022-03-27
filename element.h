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

Part mkerrorel(){return _ERROREL;}

Part mknul(){
	Part new = calloc(1, sizeof(struct PartElement));
	if(new != NULL) return new;
	else {
		return NULL;
	}
}

int mkerroram(){return _ERRORAM;}

int mkerrorid(){return _ERRORID;}

Part _remove(Part e){
	free(e);
	return _ERROREL;
}

Part edit(Part e, int _amount){
	if(e->amount == _ERRORAM || e->ID == _ERRORID || e == _ERROREL){
		fprintf(stderr, "Faulty element detected, entry removed");
		return _remove(e);
	}
	else e->amount = _amount;
	return e;
}

Part add(int id, int amount)
{
	Part new = mknul();
	if(id == _ERRORID || amount == _ERRORAM){
		return _remove(new);
	}
	new->ID = id;
	new->amount = amount;
	return new;
}

#endif /* ELEMENT_H_ */
