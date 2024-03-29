/*
 * DirectoryHeaderPage.cpp
 *
 *  Created on: Nov 10, 2013
 *      Author: ravin
 */

#include "DirectoryHeaderPage.h"
#include "../Global/globalStructures.h"
#include "../Global/globalDefines.h"
#include "../BufferManagement/BufferManager.h"
#include <stdio.h>
#include <string.h>

DirectoryHeaderPage::DirectoryHeaderPage(int fd,int pageNumber) {
	// TODO Auto-generated constructor stub
		fd_=fd;
		pageNumber_=pageNumber;
		buffManager_=BufferManager::getInstance();
		memset(pageData_,0,sizeof(DEFAULT_PAGE_SIZE));
		buffManager_->readPage(fd,pageNumber,pageData_);
		memcpy(&directoryHeaderPageHeader_,pageData_,sizeof(DirectoryHeaderPageHeaderStruct));
		isDirectoryHeaderChanged_=false;

}

DirectoryHeaderPage::~DirectoryHeaderPage() {
	// TODO Auto-generated destructor stub
	if(isDirectoryHeaderChanged_ ==true){
			buffManager_=BufferManager::getInstance();
			buffManager_->writePage(fd_,pageNumber_,pageData_);
		}
		delete []pageData_;
	}


int DirectoryHeaderPage::getPageNumber(){
	//memcpy(&directoryHeaderPageHeader_, pageData_, sizeof(DirectoryHeaderPageHeaderStruct));
	return directoryHeaderPageHeader_.genPageHeader_.pageNumber;
}

int DirectoryHeaderPage::getPageType(){
	//memcpy(&directoryHeaderPageHeader_, pageData_, sizeof(DirectoryHeaderPageHeaderStruct));
	return directoryHeaderPageHeader_.genPageHeader_.pageType;
}

int DirectoryHeaderPage::getNextPageNumber(){
	//memcpy(&directoryHeaderPageHeader_, pageData_, sizeof(DirectoryHeaderPageHeaderStruct));
	return directoryHeaderPageHeader_.genPageHeader_.nextPageNumber;
}

int DirectoryHeaderPage::getNoOfRecordsInTable(){
	//memcpy(&directoryHeaderPageHeader_, pageData_, sizeof(DirectoryHeaderPageHeaderStruct));
	return directoryHeaderPageHeader_.noOfRecordsInTable;
}

int DirectoryHeaderPage::getNoOfDirectoryPages(){
	//memcpy(&directoryHeaderPageHeader_, pageData_, sizeof(DirectoryHeaderPageHeaderStruct));
	return directoryHeaderPageHeader_.noOfDirectoryPages;
}

int DirectoryHeaderPage::getMaxDirectoryEntriesPerDP(){
	//memcpy(&directoryHeaderPageHeader_, pageData_, sizeof(DirectoryHeaderPageHeaderStruct));
	return directoryHeaderPageHeader_.maxDirectoryEntriesPerDP;
}

void DirectoryHeaderPage::setPageNumber(int pageNumber){
	//memcpy(&directoryHeaderPageHeader_, pageData_, sizeof(DirectoryHeaderPageHeaderStruct));
		directoryHeaderPageHeader_.genPageHeader_.pageNumber=pageNumber;
		memcpy(pageData_,&directoryHeaderPageHeader_,sizeof(DirectoryHeaderPageHeaderStruct));
		isDirectoryHeaderChanged_=true;

}

void DirectoryHeaderPage::setPageType(int pageType){
	//memcpy(&directoryHeaderPageHeader_, pageData_, sizeof(DirectoryHeaderPageHeaderStruct));
			directoryHeaderPageHeader_.genPageHeader_.pageType=pageType;
			memcpy(pageData_,&directoryHeaderPageHeader_,sizeof(DirectoryHeaderPageHeaderStruct));
			isDirectoryHeaderChanged_=true;
}

void DirectoryHeaderPage::setNextPageNumber(int nextPageNumber){
	//memcpy(&directoryHeaderPageHeader_, pageData_, sizeof(DirectoryHeaderPageHeaderStruct));
			directoryHeaderPageHeader_.genPageHeader_.nextPageNumber = nextPageNumber;
			memcpy(pageData_,&directoryHeaderPageHeader_,sizeof(DirectoryHeaderPageHeaderStruct));
			isDirectoryHeaderChanged_=true;
}

void DirectoryHeaderPage::setNoOfRecordsInTable(int noOfRecordsInTable){
	//memcpy(&directoryHeaderPageHeader_, pageData_, sizeof(DirectoryHeaderPageHeaderStruct));
	directoryHeaderPageHeader_.noOfRecordsInTable = noOfRecordsInTable;
	memcpy(pageData_,&directoryHeaderPageHeader_,sizeof(DirectoryHeaderPageHeaderStruct));
	isDirectoryHeaderChanged_=true;
}

void DirectoryHeaderPage::setNoOfDirectoryPages(int noOfDirectoryPages){
	//memcpy(&directoryHeaderPageHeader_, pageData_, sizeof(DirectoryHeaderPageHeaderStruct));
	directoryHeaderPageHeader_.noOfDirectoryPages = noOfDirectoryPages;
	memcpy(pageData_,&directoryHeaderPageHeader_,sizeof(DirectoryHeaderPageHeaderStruct));
	isDirectoryHeaderChanged_=true;
}

void DirectoryHeaderPage::setMaxDirectoryEntriesPerDP(int maxDirectoryEntriesPerDP){
	//memcpy(&directoryHeaderPageHeader_, pageData_, sizeof(DirectoryHeaderPageHeaderStruct));
	directoryHeaderPageHeader_.maxDirectoryEntriesPerDP = maxDirectoryEntriesPerDP;
	memcpy(pageData_,&directoryHeaderPageHeader_,sizeof(DirectoryHeaderPageHeaderStruct));
	isDirectoryHeaderChanged_=true;

}

