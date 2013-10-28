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
}PageHeaderStruct;

typedef struct{
	int dbName;
	int pageSize;
	int noOfPages;
	int pageType;
	int sysTablesHeaderPageNumber;
	int sysColumnsHeaderPageNumber;
	int indexCatalogHeaderPageNumber;
}DBMainPageHeaderStruct;

typedef struct{
	int pageNumber;
	int slotNumber;
}RIDStruct;

#endif /* GLOBALSTRUCTURES_H_ */
