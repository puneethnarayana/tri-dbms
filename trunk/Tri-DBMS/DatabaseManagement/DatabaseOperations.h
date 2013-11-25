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
#include "../HeapFileManagement/DBMainHeaderPage.h"
#include "../HeapFileManagement/DirectoryHeaderPage.h"
#include "../HeapFileManagement/DirectoryPage.h"
#include "../HeapFileManagement/DataPage.h"
#include "../HeapFileManagement/DirectoryEntry.h"
#include "../HeapFileManagement/FreePageManager.h"
#include "../SystemCatalogs/SysTablesCatalog.h"
#include "../SystemCatalogs/SysColumnsCatalog.h"
#include "../SystemCatalogs/IndexCatalog.h"
#include "../Global/globalDefines.h"
#include "../Global/globalStructures.h"
#include "../HeapFileManagement/Schema.h"
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
	int insertIntoTable(char *tableName, vector<string> insertValues);
	int selectAllFromTable(char *tableName);
private:
	BufferManager *buffManager_;
	int fd_;
	char *pageData_;
	bool isDatabaseOpen_;
	char *openDatabaseName_;
	DBMainHeaderPage *dbMainHeader_;
	//FreePageManager *freePageManager_;
	SysTablesCatalog *sysTableCatalog_;
	SysColumnsCatalog *sysColumnCatalog_;
};

#endif /* DATABASEOPERATIONS_H_ */
