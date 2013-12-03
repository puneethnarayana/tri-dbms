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
#include <stdlib.h>
#include <iostream>

using namespace std;
DBMainHeaderPage::DBMainHeaderPage(int fd,int pageNumber) {
	// TODO Auto-generated constructor stub
	fd_=fd;
	pageNumber_=pageNumber;
	buffManager_=BufferManager::getInstance();
	pageData_=new char[DEFAULT_PAGE_SIZE];
	memset(pageData_,0,DEFAULT_PAGE_SIZE);
	buffManager_->readPage(fd,pageNumber,pageData_);
	memcpy(&dbMainHeader_,pageData_,sizeof(DBMainHeaderStruct));
	//cout << "in dbmain header page --------------------------:"<< getIndexCatalogHeaderPageNumber()<<endl;
	//cout << "dbmain header page index page no:"<< dbMainHeader_.indexCatalogHeaderPageNumber_<<endl;
	//buffManager_->hexDump(fd_,0);
	isDBMainHeaderChanged_=false;

}

DBMainHeaderPage::~DBMainHeaderPage() {
	// TODO Auto-generated destructor stub

	buffManager_=BufferManager::getInstance();
	buffManager_->writePage(fd_,pageNumber_,pageData_);

	delete[] pageData_;
}

int DBMainHeaderPage::createDBMainHeaderStruct(char *databaseName,int noOfPages,int pageSize){
	dbMainHeader_.genPageHeader_.pageNumber=0;
	dbMainHeader_.genPageHeader_.pageType=DB_MAIN_HEADER_PAGE;
	dbMainHeader_.genPageHeader_.nextPageNumber=-1;
	memcpy(&dbMainHeader_.dbName_,databaseName,strlen(databaseName)+1);
	dbMainHeader_.pageSize_=pageSize;
	dbMainHeader_.noOfTables_=0;
	dbMainHeader_.noOfPages_=noOfPages;
	dbMainHeader_.noOfPagesUsed_= 2;
	dbMainHeader_.sysTablesHeaderPageNumber_= -1;
	dbMainHeader_.sysColumnsHeaderPageNumber_= -1;
	dbMainHeader_.indexCatalogHeaderPageNumber_= -1;
	dbMainHeader_.freeStructurePageNumber_= 1;
	//memcpy(pageData,&dbMainHeader_,sizeof(DBMainHeaderStruct));
	memcpy(pageData_,&dbMainHeader_,sizeof(DBMainHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDBMainHeaderChanged_=true;
	return SUCCESS;
}

int DBMainHeaderPage::getPageNumber(){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
	return dbMainHeader_.genPageHeader_.pageNumber;
}
int DBMainHeaderPage::getPageType(){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
	return dbMainHeader_.genPageHeader_.pageType;
}
int DBMainHeaderPage::getNextPageNumber(){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
	return dbMainHeader_.genPageHeader_.nextPageNumber;
}
int DBMainHeaderPage::getNoOfPagesUsed(){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
		return dbMainHeader_.noOfPagesUsed_;
}

int DBMainHeaderPage::getNoOfTables(){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
		return dbMainHeader_.noOfTables_;
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
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDBMainHeaderChanged_=true;
}
void DBMainHeaderPage::setPageType(int pageType){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
	dbMainHeader_.genPageHeader_.pageType=pageType;
	memcpy(pageData_,&dbMainHeader_,sizeof(DBMainHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDBMainHeaderChanged_=true;
}
void DBMainHeaderPage::setNextPageNumber(int nextPageNumber){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
	dbMainHeader_.genPageHeader_.nextPageNumber=nextPageNumber;
	memcpy(pageData_,&dbMainHeader_,sizeof(DBMainHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDBMainHeaderChanged_=true;
}

void DBMainHeaderPage::setNoOfPagesUsed(int noOfPagesUsed){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
	dbMainHeader_.noOfPagesUsed_=noOfPagesUsed;
	memcpy(pageData_,&dbMainHeader_,sizeof(DBMainHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDBMainHeaderChanged_=true;
}
void DBMainHeaderPage::setNoOfTables(int noOfTables){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
	dbMainHeader_.noOfTables_=noOfTables;
	memcpy(pageData_,&dbMainHeader_,sizeof(DBMainHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDBMainHeaderChanged_=true;
}
void DBMainHeaderPage::setSysTablesHeaderPageNumber(int sysTableHeaderPageNumber){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
	dbMainHeader_.sysTablesHeaderPageNumber_=sysTableHeaderPageNumber;
	memcpy(pageData_,&dbMainHeader_,sizeof(DBMainHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDBMainHeaderChanged_=true;
}
void DBMainHeaderPage::setSysColumnHeaderPageNumber(int sysColumnsHeaderPageNumber){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
	dbMainHeader_.sysColumnsHeaderPageNumber_=sysColumnsHeaderPageNumber;
	memcpy(pageData_,&dbMainHeader_,sizeof(DBMainHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDBMainHeaderChanged_=true;
}
void DBMainHeaderPage::setIndexCatalogHeaderPageNumber(int indexCatalogHeaderPageNumber){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
	dbMainHeader_.indexCatalogHeaderPageNumber_=indexCatalogHeaderPageNumber;
	memcpy(pageData_,&dbMainHeader_,sizeof(DBMainHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDBMainHeaderChanged_=true;
}
void DBMainHeaderPage::setFreeStructurePageNumber(int freeStructurePageNumber){
	//memcpy(&dbMainHeader_, pageData_, sizeof(DBMainHeaderStruct));
	dbMainHeader_.freeStructurePageNumber_=freeStructurePageNumber;
	memcpy(pageData_,&dbMainHeader_,sizeof(DBMainHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDBMainHeaderChanged_=true;
}



