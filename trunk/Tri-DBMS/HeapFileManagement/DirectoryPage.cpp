/*
 * DirectoryPage.cpp
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#include "DirectoryPage.h"
#include "../Global/globalStructures.h"
#include "../BufferManagement/BufferManager.h"
#include "../HeapFileManagement/DataPage.h"
#include <stdio.h>
#include <string.h>

DirectoryPage::DirectoryPage(int fd, int pageNumber) {
	// TODO Auto-generated constructor stub
	fd_=fd;
	pageNumber_=pageNumber;
	buffManager_=BufferManager::getInstance();
	memset(pageData_,0,sizeof(DEFAULT_PAGE_SIZE));
	buffManager_->readPage(fd,pageNumber,pageData_);
	memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
	isDirectoryPageChanged_=false;
}

DirectoryPage::~DirectoryPage() {
	// TODO Auto-generated destructor stub
	if(isDirectoryPageChanged_==true){
		buffManager_=BufferManager::getInstance();
		buffManager_->writePage(fd_,pageNumber_,pageData_);
	}
	delete []pageData_;
}


int DirectoryPage::getNoOfDirectoryEntries(){
	//memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
	return directoryPageHeader_.noOfDirectoryEntries;
}

int DirectoryPage::getMaxFreeSpace(){
	//memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
	return directoryPageHeader_.maxFreeSpace;
}

int DirectoryPage::getPageNumber(){
	//memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
	return directoryPageHeader_.genPageHeader_.pageNumber;
}

int DirectoryPage::getPageType(){
	//memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
	return directoryPageHeader_.genPageHeader_.pageType;
}

int DirectoryPage::getNextPageNumber(){
	//memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
	return directoryPageHeader_.genPageHeader_.nextPageNumber;
}

int DirectoryPage::getDirectoryPageSize(){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	return sizeof(DirectoryPageHeaderStruct);
}


void DirectoryPage::setNoOfDirectoryEntries(int noOfDirectoryEntries){
	//memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
	directoryPageHeader_.noOfDirectoryEntries=noOfDirectoryEntries;
	memcpy(pageData_,&directoryPageHeader_,sizeof(DirectoryPageHeaderStruct));
	isDirectoryPageChanged_=true;
}

void DirectoryPage::setMaxFreeSpace(int maxFreeSpace){
	//memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
	directoryPageHeader_.maxFreeSpace=maxFreeSpace;
	memcpy(pageData_,&directoryPageHeader_,sizeof(DirectoryPageHeaderStruct));
	isDirectoryPageChanged_=true;
}

void DirectoryPage::setPageNumber(int pageNumber){
	//memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
	directoryPageHeader_.genPageHeader_.pageNumber=pageNumber;
	memcpy(pageData_,&directoryPageHeader_,sizeof(DirectoryPageHeaderStruct));
	isDirectoryPageChanged_=true;
}

void DirectoryPage::setPageType(int pageType){
	//memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
	directoryPageHeader_.genPageHeader_.pageType=pageType;
	memcpy(pageData_,&directoryPageHeader_,sizeof(DirectoryPageHeaderStruct));
	isDirectoryPageChanged_=true;
}

void DirectoryPage::setNextPageNumber(int nextPageNumber){
	//memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
	directoryPageHeader_.genPageHeader_.nextPageNumber=nextPageNumber;
	memcpy(pageData_,&directoryPageHeader_,sizeof(DirectoryPageHeaderStruct));
	isDirectoryPageChanged_=true;
}

int DirectoryPage::createDirectoryPage(int pageNumber, char *pageData){
	directoryPageHeader_.genPageHeader_.pageNumber=pageNumber;
	directoryPageHeader_.genPageHeader_.nextPageNumber=-1;
	directoryPageHeader_.genPageHeader_.pageType=DIRECTORY_PAGE;
	directoryPageHeader_.maxFreeSpace=DEFAULT_PAGE_SIZE-DataPage::getDataPageSize();
	directoryPageHeader_.noOfDirectoryEntries=
			(DEFAULT_PAGE_SIZE-sizeof(DirectoryPageHeaderStruct))/8;
	//Directory Entry = page number + free space
	memcpy(&pageData,&directoryPageHeader_,sizeof(directoryPageHeader_));
	memcpy(pageData_,&directoryPageHeader_,sizeof(directoryPageHeader_));
	isDirectoryPageChanged_=true;
	return SUCCESS;
}
