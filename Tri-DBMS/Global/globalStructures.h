/*
 * globalStructures.h
 *
 *  Created on: Oct 23, 2013
 *      Author: ravin
 */

#ifndef GLOBALSTRUCTURES_H_
#define GLOBALSTRUCTURES_H_

typedef struct{
	int pageNumber;
	int pageType;
	int nextPageNumber;
}GenPageHeaderStruct;



typedef struct{
	int pageNumber;
	short slotNumber;
}RIDStruct;

#endif /* GLOBALSTRUCTURES_H_ */
