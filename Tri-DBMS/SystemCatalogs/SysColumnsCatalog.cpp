/*
 * SysColumnsCatalog.cpp
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#include "SysColumnsCatalog.h"
#include "../BufferManagement/BufferManager.h"
#include "../Global/globalStructures.h"
#include "../Global/globalDefines.h"

SysColumnsCatalog::SysColumnsCatalog(int fd, int pageNumber) {
	// TODO Auto-generated constructor stub
	fd_=fd;
	pageNumber_=pageNumber;
	buffManager_=BufferManager::getInstance();
	memset(pageData_,0,sizeof(DEFAULT_PAGE_SIZE));
	buffManager_->readPage(fd,pageNumber,pageData_);
	maxSysColumnEntriesPerPage_=
			(DEFAULT_PAGE_SIZE-sizeof(GenPageHeaderStruct)-sizeof(int))/sizeof(sysColumnPageStruct);
	memset(sysColumnPage_.sysColumnEntry_,0,maxSysColumnEntriesPerPage_);
	memcpy(&sysColumnPage_,pageData_,sizeof(sysColumnPageStruct));
	isSysColumnChanged_=false;
}

SysColumnsCatalog::~SysColumnsCatalog() {
	// TODO Auto-generated destructor stub
	if(isSysColumnChanged_ ==true){
			buffManager_=BufferManager::getInstance();
			buffManager_->writePage(fd_,pageNumber_,pageData_);
		}
		delete []pageData_;
}

int SysColumnsCatalog::insertSysColumnEntry(char *columnName, char *tableName, int columnPosition, int columnType, char *pageData){

	sysColumnPage_.genPageHeader_.pageNumber=pageNumber_;
	sysColumnPage_.genPageHeader_.pageType=SYS_COLUMNS_PAGE;
	sysColumnPage_.genPageHeader_.nextPageNumber=-1;

	memcpy(sysColumnPage_.sysColumnEntry_[sysColumnPage_.noOfEntries].columnName_,columnName,MAX_FILE_NAME_LENGTH);
	memcpy(sysColumnPage_.sysColumnEntry_[sysColumnPage_.noOfEntries].tableName_,tableName,MAX_FILE_NAME_LENGTH);
	sysColumnPage_.sysColumnEntry_[sysColumnPage_.noOfEntries].columnPosition_=columnPosition;
	sysColumnPage_.sysColumnEntry_[sysColumnPage_.noOfEntries].columnType_=columnType;
	sysColumnPage_.noOfEntries++;
	memcpy(pageData_,&sysColumnPage_,sizeof(sysColumnPageStruct));
	memcpy(&pageData,&sysColumnPage_,sizeof(sysColumnPageStruct));

	isSysColumnChanged_=true;
	return SUCCESS;
}

