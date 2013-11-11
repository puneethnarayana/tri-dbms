/*
 * DatabaseOperations.cpp
 *
 *  Created on: Nov 11, 2013
 *      Author: ravin
 */

#include "DatabaseOperations.h"
#include "../HeapFileManagement/DBMainHeaderPage.h"
#include "../HeapFileManagement/DirectoryHeaderPage.h"
#include "../HeapFileManagement/DirectoryPage.h"
#include "../HeapFileManagement/DataPage.h"
#include "../HeapFileManagement/DirectoryEntry.h"
#include "../HeapFileManagement/FreePageManager.h"
#include "../Global/globalDefines.h"
#include "../Global/globalStructures.h"
#include "../BufferManagement/BufferManager.h"

DatabaseOperations::DatabaseOperations() {
	// TODO Auto-generated constructor stub

}

DatabaseOperations::~DatabaseOperations() {
	// TODO Auto-generated destructor stub
}

int DatabaseOperations::createDatabase(char *databaseName){
	createDatabase(databaseName,DEFAULT_DB_SIZE);
}

int DatabaseOperations::createDatabase(char *databaseName,int databaseSize){
	int fd;
	int noOfPages=databaseSize*1024*1024/DEFAULT_PAGE_SIZE;
	buffManager_=BufferManager::getInstance();
	buffManager_->createDatabase(databaseName,DEFAULT_PAGE_SIZE,noOfPages);
	fd=buffManager_->openDatabase(databaseName);
	DBMainHeaderPage *dbMainHeader=new DBMainHeaderPage(fd,0);


	return SUCCESS;
}
