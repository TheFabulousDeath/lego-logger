#include <stdlib.h>
#include <stdio.h>


#ifndef ELEMENT_H_
#define ELEMENT_H_

#define _MAXPARTS 2000
#define _ERROREL NULL
#define _ERRORAM 0
#define _ERRORID -1

typedef struct
{
	int ID;
	int amount;
}_ELEMENT, *_part;

_part mkerrorel(){return _ERROREL;}

_part mknul(){
	_part new;
	new = calloc(1, sizeof(_ELEMENT));
	//check if calloc worked
	if(new != NULL) return new;
	else {
		fprintf(stderr, "Calloc failed, NULL returned");
		return NULL;
	}
}

int mkerroram(){return _ERRORAM;}

int mkerrorid(){return _ERRORID;}

_part _remove(_part e){
	free(e);
	return _ERROREL;
}

_part edit(_part e, int _amount){
	if(e->amount == _ERRORAM || e->ID == _ERRORID || e == _ERROREL){
		fprintf(stderr, "Faulty element detected, entry removed");
		return _remove(e);
	}
	else e->amount = _amount;
	return e;
}

_part add(int id, int amount)
{
	_part new = mknul();
	if(id == _ERRORID || amount == _ERRORAM){
		return _remove(new);
	}
	new->ID = id;
	new->amount = amount;
	return new;
}

#endif /* ELEMENT_H_ */
