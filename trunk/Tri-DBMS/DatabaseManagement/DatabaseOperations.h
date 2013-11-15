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
	DatabaseOperations(int fd);
	virtual ~DatabaseOperations();
	int createDatabase(char *databaseName);
	int createDatabase(char *databaseName,int databaseSize);

private:
	BufferManager *buffManager_;
	int fd_;
	char *pageData_;
};

#endif /* DATABASEOPERATIONS_H_ */
