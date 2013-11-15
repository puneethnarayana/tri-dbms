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

DatabaseOperations::DatabaseOperations(int fd) {
	// TODO Auto-generated constructor stub
	fd_=fd;
	pageData_=new char[DEFAULT_PAGE_SIZE];
	buffManager_=BufferManager::getInstance();
}

DatabaseOperations::~DatabaseOperations() {
	// TODO Auto-generated destructor stub
}

int DatabaseOperations::createDatabase(char *databaseName){
	createDatabase(databaseName,DEFAULT_DB_SIZE);


	return SUCCESS;
}

int DatabaseOperations::createDatabase(char *databaseName,int databaseSize){

	int noOfPages=databaseSize*1024*1024/DEFAULT_PAGE_SIZE;
	buffManager_=BufferManager::getInstance();
	buffManager_->createDatabase(databaseName,DEFAULT_PAGE_SIZE,noOfPages);
	fd_=buffManager_->openDatabase(databaseName);
	DBMainHeaderPage *dbMainHeader_=new DBMainHeaderPage(fd_,0);
	dbMainHeader_->createDBMainHeaderStruct(databaseName,noOfPages,DEFAULT_PAGE_SIZE,pageData_);
	dbMainHeader_->setFreeStructurePageNumber(1);
	FreePageManager *freePageManager_=new FreePageManager(fd_,1);
	freePageManager_->createFreePageManagerPage(1,pageData_);

	return SUCCESS;
}
