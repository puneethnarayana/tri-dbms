/*
 * DatabaseOperations.h
 *
 *  Created on: Nov 11, 2013
 *      Author: ravin
 */

#ifndef DATABASEOPERATIONS_H_
#define DATABASEOPERATIONS_H_

#include "../BufferManagement/BufferManager.h"

class DatabaseOperations {
public:
	DatabaseOperations();
	virtual ~DatabaseOperations();
	int createDatabase(char *databaseName);
	int createDatabase(char *databaseName,int databaseSize);

private:
	BufferManager *buffManager_;
};

#endif /* DATABASEOPERATIONS_H_ */
