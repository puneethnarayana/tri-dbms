/*
 * SysTablesCatalog.cpp
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#include "SysTablesCatalog.h"
#include "../BufferManagement/BufferManager.h"
#include "../Global/globalStructures.h"
#include "../Global/globalDefines.h"
#include "../HeapFileManagement/DataPage.h"

SysTablesCatalog::SysTablesCatalog(int fd,int pageNumber) {
	// TODO Auto-generated constructor stub
	fd_=fd;
	pageNumber_=pageNumber;
	pageData_=new char[DEFAULT_PAGE_SIZE];
	buffManager_ = BufferManager::getInstance();
	memset(pageData_,0,sizeof(DEFAULT_PAGE_SIZE));
	buffManager_->readPage(fd,pageNumber,pageData_);
//	maxSysTableEntriesPerPage_=(DEFAULT_PAGE_SIZE-sizeof(GenPageHeaderStruct)-sizeof(int))/sizeof(SysTableEntryStruct);
//	memset(sysTablePage_.sysTableEntries_,0,maxSysTableEntriesPerPage_);
//	memcpy(&sysTablePage_,pageData_,sizeof(sysTablePageStruct));
	isSysTableChanged_=false;

}
int SysTablesCatalog::createSysTablePage(int pageNumber,char *pageData){
	DataPage *sysTablePage=new DataPage(fd_,pageNumber_);
	sysTablePage->createDataPageHeaderStruct(pageNumber_,pageData);
	sysTablePage->setPageType(SYS_TABLES_PAGE);
	return SUCCESS;
}
int SysTablesCatalog::insertSysTableEntry(char *tableName,int maxRecordSize,int noOfColumns,int dpChainHeader,char *pageData){

	int sysTableEntrySize_= strlen(tableName)+sizeof(int)*3+1;
	SysTableEntryStruct sysTableEntry_;
	sysTableEntry_.recordSize_=maxRecordSize;
	sysTableEntry_.noOfColumns_=noOfColumns;
	sysTableEntry_.dpChainHeaderAddress_=dpChainHeader;
	strcpy(sysTableEntry_.tableName_,tableName);
	memcpy(pageData_,&sysTableEntry_,sysTableEntrySize_);
	DataPage *sysTablePage=new DataPage(fd_,pageNumber_);
	sysTablePage->insertRecord(pageData_,sizeof(sysTableEntry_)+strlen(tableName)+1);
	return SUCCESS;
}

SysTablesCatalog::~SysTablesCatalog() {
	// TODO Auto-generated destructor stub

	if(isSysTableChanged_==true){
		buffManager_=BufferManager::getInstance();
		buffManager_->writePage(fd_,pageNumber_,pageData_);
	}
	delete []pageData_;

}

