/*
 * DatabaseOperations.h
 *
 *  Created on: Nov 11, 2013
 *      Author: ravin
 */

#ifndef DATABASEOPERATIONS_H_
#define DATABASEOPERATIONS_H_

#include "../BufferManagement/BufferManager.h"
#include <vector>
using namespace std;
class DatabaseOperations {
public:
	DatabaseOperations();
	virtual ~DatabaseOperations();
	int createDatabase(char *databaseName);
	int createDatabase(char *databaseName,int databaseSize);
	int openDatabase(char *databaseName);
	int closeDatabase(int fd);
	int createTable(char *tableName, vector<string> columnList, vector<string> columnTypeList);

private:
	BufferManager *buffManager_;
	int fd_;
	char *pageData_;
	bool isDatabaseOpen_;
	char *openDatabaseName_;
};

#endif /* DATABASEOPERATIONS_H_ */
