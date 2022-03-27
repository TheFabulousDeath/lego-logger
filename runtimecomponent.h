/*
 * runtimecomponent.h
 *
 *  Created on: 27.03.2022
 *      Author: vince
 */

#ifndef RUNTIMECOMPONENT_H_
#define RUNTIMECOMPONENT_H_

typedef struct{
	Part partsArr;
	int partCounter;
}*storage;

typedef struct{
	storage storage;
	instructionStack instructionStack;
}*runtimeComponent;


#endif /* RUNTIMECOMPONENT_H_ */
