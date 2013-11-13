/*
 * DataPage.cpp
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#include "DataPage.h"
#include "../Global/globalStructures.h"
#include "../Global/globalDefines.h"
#include "../BufferManagement/BufferManager.h"
#include <stdio.h>
#include <string.h>

DataPage::DataPage(int fd,int pageNumber) {
	// TODO Auto-generated constructor stub
	fd_=fd;
	pageNumber_=pageNumber;
	buffManager_=BufferManager::getInstance();
	memset(pageData_,0,sizeof(DEFAULT_PAGE_SIZE));
	buffManager_->readPage(fd,pageNumber,pageData_);
	memcpy(&dataPageHeader_,pageData_,sizeof(DataPageHeaderStruct));
	isDataPageChanged_=false;
}

DataPage::~DataPage() {
	// TODO Auto-generated destructor stub
	if(isDataPageChanged_==true){
		buffManager_=BufferManager::getInstance();
		buffManager_->writePage(fd_,pageNumber_,pageData_);
	}
	delete []pageData_;
}

int DataPage::createDataPageHeaderStruct(int pageNumber,char *pageData){
	dataPageHeader_.genPageHeader_.pageNumber=pageNumber;
	dataPageHeader_.genPageHeader_.pageType=DATA_PAGE;
	dataPageHeader_.genPageHeader_.nextPageNumber=-1;
	dataPageHeader_.noOfRecords_=0;
	memcpy(pageData,&dataPageHeader_,sizeof(DataPageHeaderStruct));
	memcpy(pageData_,&dataPageHeader_,sizeof(DataPageHeaderStruct));
	isDataPageChanged_=true;
	return SUCCESS;
}



int DataPage::getPageNumber(){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	return dataPageHeader_.genPageHeader_.pageNumber;
}
int DataPage::getPageType(){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
		return dataPageHeader_.genPageHeader_.pageType;
}
int DataPage::getnextPageNumber(){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
		return dataPageHeader_.genPageHeader_.nextPageNumber;
}
int DataPage::getNoOfRecords(){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	return dataPageHeader_.noOfRecords_;
}
int DataPage::getDataPageSize(){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	return sizeof(DataPageHeaderStruct);
}

void DataPage::setPageNumber(int pageNumber){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	dataPageHeader_.genPageHeader_.pageNumber=pageNumber;
	memcpy(pageData_,&dataPageHeader_,sizeof(DataPageHeaderStruct));
	isDataPageChanged_=true;
}
void DataPage::setPageType(int pageType){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	dataPageHeader_.genPageHeader_.pageType=pageType;
	memcpy(pageData_,&dataPageHeader_,sizeof(DataPageHeaderStruct));
	isDataPageChanged_=true;
}
void DataPage::setNextPageNumber(int nextPageNumber){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	dataPageHeader_.genPageHeader_.nextPageNumber=nextPageNumber;
	memcpy(pageData_,&dataPageHeader_,sizeof(DataPageHeaderStruct));
	isDataPageChanged_=true;
}
void DataPage::setNoOfRecords(int noOfRecords){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	dataPageHeader_.noOfRecords_=noOfRecords;
	memcpy(pageData_,&dataPageHeader_,sizeof(DataPageHeaderStruct));
	isDataPageChanged_=true;
}

