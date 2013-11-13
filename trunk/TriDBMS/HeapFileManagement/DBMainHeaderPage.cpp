/*
 * DBMainHeaderPage.cpp
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#include "DBMainHeaderPage.h"
#include "../Global/globalStructures.h"
#include "../Global/globalDefines.h"
#include "../BufferManagement/BufferManager.h"
#include <stdio.h>
#include <string.h>
DBMainHeaderPage::DBMainHeaderPage(int fd,int pageNumber) {
	// TODO Auto-generated constructor stub
	fd_=fd;
	pageNumber_=pageNumber;
	buffManager_=BufferManager::getInstance();
	memset(pageData_,0,sizeof(DEFAULT_PAGE_SIZE));
	buffManager_->readPage(fd,pageNumber,pageData_);
	memcpy(&dbMainHeader_,pageData_,sizeof(DBMainHeaderStruct));
	isDBMainHeaderChanged_=false;

}

DBMainHeaderPage::~DBMainHeaderPage() {
	// TODO Auto-generated destructor stub

	if(isDBMainHeaderChanged_==true){
		buffManager_=BufferManager::getInstance();
		buffManager_->writePage(fd_,pageNumber_,pageData_);
	}
	delete []pageData_;
}

int DBMainHeaderPage::createDBMainHeaderStruct(char *databaseName,int noOfPages,int pageSize,char *pageData){
	dbMainHeader_.genPageHeader_.pageNumber=0;
	dbMainHeader_.genPageHeader_.pageType=DB_MAIN_HEADER_PAGE;
	dbMainHeader_.genPageHeader_.nextPageNumber=-1;
	memcpy(&dbMainHeader_.dbName_,databaseName,sizeof(databaseName));
	dbMainHeader_.pageSize_=pageSize;
	dbMainHeader_.noOfTables_=0;
	dbMainHeader_.noOfPages_=noOfPages;
	dbMainHeader_.noOfPagesUsed_= 1;
	dbMainHeader_.sysTablesHeaderPageNumber_= -1;
	dbMainHeader_.sysColumnsHeaderPageNumber_= -1;
	dbMainHeader_.indexCatalogHeaderPageNumber_= -1;
	dbMainHeader_.freeStructurePageNumber_= -1;
	memcpy(pageData,&dbMainHeader_,sizeof(dbMainHeader_));
	memcpy(pageData_,&dbMainHeader_,sizeof(dbMainHeader_));
	isDBMainHeaderChanged_=true;
	return SUCCESS;
}

int DBMainHeaderPage::getPageNumber(){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
	return dbMainHeader_.genPageHeader_.pageNumber;
}

int DBMainHeaderPage::getNoOfPagesUsed(){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
		return dbMainHeader_.noOfPagesUsed_;
}

int DBMainHeaderPage::getSysTablesHeaderPageNumber(){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
	return dbMainHeader_.sysTablesHeaderPageNumber_;
}

int DBMainHeaderPage::getSysColumnHeaderPageNumber(){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
		return dbMainHeader_.sysColumnsHeaderPageNumber_;
}

int DBMainHeaderPage::getIndexCatalogHeaderPageNumber(){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
		return dbMainHeader_.indexCatalogHeaderPageNumber_;
}

int DBMainHeaderPage::getFreeStructurePageNumber(){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
		return dbMainHeader_.freeStructurePageNumber_;
}


void DBMainHeaderPage::setPageNumber(int pageNumber){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
	dbMainHeader_.genPageHeader_.pageNumber=pageNumber;
	memcpy(pageData_,&dbMainHeader_,sizeof(DBMainHeaderStruct));
	isDBMainHeaderChanged_=true;
}
void DBMainHeaderPage::setNoOfPagesUsed(int noOfPagesUsed){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
	dbMainHeader_.genPageHeader_.pageNumber=noOfPagesUsed;
	memcpy(pageData_,&dbMainHeader_,sizeof(DBMainHeaderStruct));
	isDBMainHeaderChanged_=true;
}
void DBMainHeaderPage::setSysTablesHeaderPageNumber(int sysTableHeaderPageNumber){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
	dbMainHeader_.genPageHeader_.pageNumber=sysTableHeaderPageNumber;
	memcpy(pageData_,&dbMainHeader_,sizeof(DBMainHeaderStruct));
	isDBMainHeaderChanged_=true;
}
void DBMainHeaderPage::setSysColumnHeaderPageNumber(int sysColumnsHeaderPageNumber){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
	dbMainHeader_.genPageHeader_.pageNumber=sysColumnsHeaderPageNumber;
	memcpy(pageData_,&dbMainHeader_,sizeof(DBMainHeaderStruct));
	isDBMainHeaderChanged_=true;
}
void DBMainHeaderPage::setIndexCatalogHeaderPageNumber(int indexCatalogHeaderPageNumber){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
	dbMainHeader_.genPageHeader_.pageNumber=indexCatalogHeaderPageNumber;
	memcpy(pageData_,&dbMainHeader_,sizeof(DBMainHeaderStruct));
	isDBMainHeaderChanged_=true;
}
void DBMainHeaderPage::setFreeStructurePageNumber(int freeStructurePageNumber){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
	dbMainHeader_.genPageHeader_.pageNumber=freeStructurePageNumber;
	memcpy(pageData_,&dbMainHeader_,sizeof(DBMainHeaderStruct));
	isDBMainHeaderChanged_=true;
}



