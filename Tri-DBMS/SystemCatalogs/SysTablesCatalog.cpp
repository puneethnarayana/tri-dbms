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

SysTablesCatalog::SysTablesCatalog(int fd,int pageNumber) {
	// TODO Auto-generated constructor stub
	fd_=fd;
	pageNumber_=pageNumber;
	buffManager_ = BufferManager::getInstance();
	memset(pageData_,0,sizeof(DEFAULT_PAGE_SIZE));
	buffManager_->readPage(fd,pageNumber,pageData_);
	maxSysTableEntriesPerPage_=(DEFAULT_PAGE_SIZE-sizeof(GenPageHeaderStruct)-sizeof(int))/sizeof(SysTableEntryStruct);
	memset(sysTablePage_.sysTableEntries_,0,maxSysTableEntriesPerPage_);
	memcpy(&sysTablePage_,pageData_,sizeof(sysTablePageStruct));
	isSysTableChanged_=false;

}

int SysTablesCatalog::insertSysTableEntry(char *tableName,int recordSize,int noOfColumns,int dpChainHeader,char *pageData){

		sysTablePage_.genPageHeader_.pageNumber=pageNumber_;
		sysTablePage_.genPageHeader_.pageType=SYS_TABLES_PAGE;
		sysTablePage_.genPageHeader_.nextPageNumber=-1;
		sysTablePage_.sysTableEntries_[sysTablePage_.noOfEntries].recordSize_=recordSize;
		sysTablePage_.sysTableEntries_[sysTablePage_.noOfEntries].noOfColumns_=noOfColumns;
		sysTablePage_.sysTableEntries_[sysTablePage_.noOfEntries].dpChainHeaderAddress_=dpChainHeader;
		memset(sysTablePage_.sysTableEntries_[sysTablePage_.noOfEntries].tableName_,0,MAX_FILE_NAME_LENGTH);
		memcpy(sysTablePage_.sysTableEntries_[sysTablePage_.noOfEntries].tableName_,tableName,MAX_FILE_NAME_LENGTH);
		sysTablePage_.noOfEntries++;
		memcpy(pageData_,&sysTablePage_,sizeof(sysTablePageStruct));
		memcpy(pageData,&sysTablePage_,sizeof(sysTablePageStruct));
		isSysTableChanged_=true;

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

