/*
 * DBMainHeaderPage.cpp
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#include "DBMainHeaderPage.h"
#include "../Global/globalStructures.h"
#include "../Global/globalDefines.h"

#include <stdio.h>
#include <string.h>
DBMainHeaderPage::DBMainHeaderPage(int fd,int pageNumber) {
	// TODO Auto-generated constructor stub
	char *pageData;
	buffManager_=BufferManager::getInstance();
	buffManager_->readPage(fd,pageNumber,pageData);
	memset(&dbMainHeader_,NULL,sizeof(DBMainHeaderStruct));
	memset(&dbMainHeader_.genPageHeader_,NULL,sizeof(dbMainHeader_.genPageHeader_));
	memcpy(&dbMainHeader_,pageData,sizeof(DBMainHeaderStruct));

}

DBMainHeaderPage::~DBMainHeaderPage() {
	// TODO Auto-generated destructor stub
}

int DBMainHeaderPage::createDBMainHeaderStruct(char *databaseName,int noOfPages,int pageSize,char *pageData){
	memset(&dbMainHeader_,NULL,sizeof(DBMainHeaderStruct));
	memset(&dbMainHeader_.genPageHeader_,NULL,sizeof(dbMainHeader_.genPageHeader_));
	dbMainHeader_.genPageHeader_.pageNumber=0;
	dbMainHeader_.genPageHeader_.pageType=DB_MAIN_HEADER_PAGE;
	dbMainHeader_.genPageHeader_.nextPageNumber=-1;
	memcpy(&dbMainHeader_.dbName_,databaseName,sizeof(databaseName));
	dbMainHeader_.noOfPages_=noOfPages;
	dbMainHeader_.noOfTables_=0;
	dbMainHeader_.pageSize_=pageSize;
	dbMainHeader_.noOfPagesUsed_= 1;
	dbMainHeader_.freeStructurePageNumber_= -1;
	dbMainHeader_.indexCatalogHeaderPageNumber_= -1;
	dbMainHeader_.sysColumnsHeaderPageNumber_= -1;
	dbMainHeader_.sysTablesHeaderPageNumber_= -1;
	memcpy(pageData,&dbMainHeader_,sizeof(dbMainHeader_));
	return SUCCESS;
}

int DBMainHeaderPage::getPageNumber(){
	memcpy(&dbMainHeader_, pageData_, sizeof(DBMainheaderStruct));
	return dbMainHeader_.sysTableHeaderPageNumber;
}

int DBMainHeaderPage::getNoOfPagesUsed(){
	int noOfPagesUsed;
	memcpy(&noOfPagesUsed,&dbMainHeader_.noOfPagesUsed_,sizeof(int));
	return noOfPagesUsed;
}

int DBMainHeaderPage::getSysTablesHeaderPageNumber(){
	int sysTablesHeaderPageNumber;
	memcpy(&sysTablesHeaderPageNumber,&dbMainHeader_.sysTablesHeaderPageNumber_,sizeof(int));
	return sysTablesHeaderPageNumber;
}

int DBMainHeaderPage::getSysColumnHeaderPageNumber(){
	int sysColumnsHeaderPageNumber;
	memcpy(&sysColumnsHeaderPageNumber,&dbMainHeader_.sysColumnsHeaderPageNumber_,sizeof(int));
	return sysColumnsHeaderPageNumber;
}

int DBMainHeaderPage::getIndexCatalogHeaderPageNumber(){
	int indexCatalogHeaderPageNumber;
	memcpy(&indexCatalogHeaderPageNumber,&dbMainHeader_.indexCatalogHeaderPageNumber_,sizeof(int));
	return indexCatalogHeaderPageNumber;
}

int DBMainHeaderPage::getFreeStructurePageNumber(){
	int freeStructurePageNumber;
	memcpy(&freeStructurePageNumber,&dbMainHeader_.freeStructurePageNumber_,sizeof(int));
	return freeStructurePageNumber;
}


void DBMainHeaderPage::setPageNumber(int pageNumber){
	memcpy(&dbMainHeader_.genPageHeader_.pageNumber,pageNumber,sizeof(int));
}
void DBMainHeaderPage::setNoOfPagesUsed(int noOfPagesUsed);
void DBMainHeaderPage::setSysTablesHeaderPageNumber(int sysTableHeaderPageNumber);
void DBMainHeaderPage::setSysColumnHeaderPageNumber(int sysColumnsHeaderPageNumber);
void DBMainHeaderPage::setIndexCatalogHeaderPageNumber(int indexCatalogHeaderPageNumber);
void DBMainHeaderPage::setFreeStructurePageNumber(int freeStructurePageNumber);
