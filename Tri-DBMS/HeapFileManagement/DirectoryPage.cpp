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
#include "../HeapFileManagement/FreePageManager.h"
#include "DirectoryEntry.h"
#include <stdio.h>
#include <string.h>
using namespace std;
#include <iostream>
#include <istream>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>

DirectoryPage::DirectoryPage(int fd, int pageNumber) {
	// TODO Auto-generated constructor stub
	fd_=fd;
	pageNumber_=pageNumber;
	pageData_=new char[DEFAULT_PAGE_SIZE];
	buffManager_=BufferManager::getInstance();
	memset(pageData_,0,DEFAULT_PAGE_SIZE);
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

int DirectoryPage::createDirectoryPage(int pageNumber){
	directoryPageHeader_.genPageHeader_.pageNumber=pageNumber;
	directoryPageHeader_.genPageHeader_.nextPageNumber=-1;
	directoryPageHeader_.genPageHeader_.pageType=DIRECTORY_PAGE;
	directoryPageHeader_.maxFreeSpace_=DEFAULT_PAGE_SIZE-DataPage::getDataPageSize();
	directoryPageHeader_.headerOffset_=sizeof(DirectoryPageHeaderStruct);
	directoryPageHeader_.noOfDirectoryEntries_=0;
	directoryPageHeader_.maxNoOfDirectoryEntries_=(DEFAULT_PAGE_SIZE-
			sizeof(DirectoryPageHeaderStruct))/DirectoryEntry::getDirectoryEntrySize();
	//Directory Entry = page number + free space
	//memcpy(pageData,&directoryPageHeader_,directoryPageHeader_.headerOffset_);
	memcpy(pageData_,&directoryPageHeader_,directoryPageHeader_.headerOffset_);

	isDirectoryPageChanged_=true;
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	return SUCCESS;
}

DirectoryEntry::DirectoryEntryStruct DirectoryPage::getDirectorySlot(int slotEntryNumber){
	DirectoryEntry *singleEntry=new DirectoryEntry();
	int offset =directoryPageHeader_.headerOffset_+ slotEntryNumber*DirectoryEntry::getDirectoryEntrySize();
	memcpy(&singleEntry->directoryEntry_,&pageData_[offset],DirectoryEntry::getDirectoryEntrySize());
	return singleEntry->directoryEntry_;
}

DirectoryEntry::DirectoryEntryStruct DirectoryPage::insertSlotEntry(int sizeRequired,int *slotNumber){
	int slotEntryNumber= searchForSlotEntry(sizeRequired);
	//cout << "slot entry number" << slotEntryNumber << endl;
	updateMaxFreeSpace();
	int offset =directoryPageHeader_.headerOffset_+
			slotEntryNumber*DirectoryEntry::getDirectoryEntrySize();
	*slotNumber=slotEntryNumber;
	DirectoryEntry *singleEntry=new DirectoryEntry();
	memcpy(&singleEntry->directoryEntry_,&pageData_[offset],DirectoryEntry::getDirectoryEntrySize());
	return singleEntry->directoryEntry_;
}
int DirectoryPage::searchForSlotEntry(int sizeRequired){
	int i, offset;
	DirectoryEntry *dirEntry=new DirectoryEntry();
	for(i=0;i<directoryPageHeader_.noOfDirectoryEntries_;i++){
		offset= directoryPageHeader_.headerOffset_+
				(i*DirectoryEntry::getDirectoryEntrySize());
		memcpy(&dirEntry->directoryEntry_,&pageData_[offset],DirectoryEntry::getDirectoryEntrySize());
		if(dirEntry->directoryEntry_.freeSpace_>=sizeRequired){

			updateSlotEntry(i,dirEntry->directoryEntry_.freeSpace_-sizeRequired);
			return i;
		}
	}
	// new DirectoryEntry slot required
	//cout << "it came here "<< endl;
	delete dirEntry;
	return addSlotEntry(sizeRequired);
}

int DirectoryPage::addSlotEntry(int sizeRequired){
	if(directoryPageHeader_.noOfDirectoryEntries_==directoryPageHeader_.maxNoOfDirectoryEntries_){
		return -1;
	}

	FreePageManager *page= new FreePageManager(fd_,1);
			//char *trialData= new char[DEFAULT_PAGE_SIZE];
			//page->createFreePageManagerPage(1,trialData);


	int offset =directoryPageHeader_.headerOffset_+
			directoryPageHeader_.noOfDirectoryEntries_*DirectoryEntry::getDirectoryEntrySize();
	DirectoryEntry *dirEntry= new DirectoryEntry();
	dirEntry->directoryEntry_={
			page->getFreePage(),
			DEFAULT_PAGE_SIZE-DataPage::getDataPageSize()-sizeRequired
	};
//	cout << dirEntry->directoryEntry_.pageNumber_ << endl;
//	cout << dirEntry->directoryEntry_.freeSpace_ << endl;

	memcpy(&pageData_[offset],&dirEntry->directoryEntry_,DirectoryEntry::getDirectoryEntrySize());

	setNoOfDirectoryEntries(getNoOfDirectoryEntries()+1);
	isDirectoryPageChanged_=true;
	buffManager_->writePage(fd_,pageNumber_,pageData_);

	delete dirEntry;
	delete page;
	return getNoOfDirectoryEntries()-1;
}



int DirectoryPage::updateSlotEntry(int slotNumber,int freeSpace){
	int offset =directoryPageHeader_.headerOffset_+
					slotNumber*DirectoryEntry::getDirectoryEntrySize();
	DirectoryEntry *dirEntry=new DirectoryEntry();
	memcpy(&dirEntry->directoryEntry_,&pageData_[offset],DirectoryEntry::getDirectoryEntrySize());
	dirEntry->directoryEntry_.freeSpace_=freeSpace;
	memcpy(&pageData_[offset],&dirEntry->directoryEntry_,DirectoryEntry::getDirectoryEntrySize());
	isDirectoryPageChanged_=true;
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	delete dirEntry;
	return SUCCESS;
}
//int DirectoryPage::deleteSlotEntry(int slotNumber){
//
//	updateSlotEntry(int slotNumber,
//	return SUCCESS;
//}
//

int DirectoryPage::deleteDirectoryPage(){
	int offset;
	DataPage *dataPage;

	DirectoryEntry *dirEntry=new DirectoryEntry();
	for(unsigned i=0;i<directoryPageHeader_.noOfDirectoryEntries_;i++){
		offset= directoryPageHeader_.headerOffset_+
				(i*DirectoryEntry::getDirectoryEntrySize());
		memcpy(&dirEntry->directoryEntry_,&pageData_[offset],DirectoryEntry::getDirectoryEntrySize());
		dataPage= new DataPage(fd_,dirEntry->directoryEntry_.pageNumber_);
		dataPage->deleteDataPage();
		delete dataPage;

	}
	memset(pageData_,0,DEFAULT_PAGE_SIZE);
	cout << "deleted dir pageNo :"<<pageNumber_<<endl;
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	FreePageManager *freePageManager=new FreePageManager(fd_,1);
	freePageManager->freePage(pageNumber_);
	delete freePageManager;
	return SUCCESS;
}

int DirectoryPage::getFreeSpace(int slotNumber){
	int offset =directoryPageHeader_.headerOffset_+
			slotNumber*DirectoryEntry::getDirectoryEntrySize();
	DirectoryEntry singleEntry;
	memcpy(&singleEntry,&pageData_[offset],DirectoryEntry::getDirectoryEntrySize());
	return singleEntry.getFreeSpace();
}

void DirectoryPage::updateMaxFreeSpace(){
	int i, offset;
	DirectoryEntry *dirEntry=new DirectoryEntry();
	if(getMaxNoOfDirectoryEntries()>getNoOfDirectoryEntries()){
		directoryPageHeader_.maxFreeSpace_=DEFAULT_PAGE_SIZE-DataPage::getDataPageSize();
	}
	else{
		directoryPageHeader_.maxFreeSpace_=0;
		for(i=0;i<directoryPageHeader_.noOfDirectoryEntries_;i++){
			offset= directoryPageHeader_.headerOffset_+
					(i*DirectoryEntry::getDirectoryEntrySize());
			memcpy(&dirEntry->directoryEntry_,&pageData_[offset],DirectoryEntry::getDirectoryEntrySize());
			if(directoryPageHeader_.maxFreeSpace_<dirEntry->directoryEntry_.freeSpace_){
				directoryPageHeader_.maxFreeSpace_=dirEntry->directoryEntry_.freeSpace_;
			}
		}
	}
	memcpy(pageData_,&directoryPageHeader_,sizeof(DirectoryPageHeaderStruct));
	isDirectoryPageChanged_=true;
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	delete dirEntry;
}


int DirectoryPage::getNoOfDirectoryEntries(){
	//memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
	return directoryPageHeader_.noOfDirectoryEntries_;
}

int DirectoryPage::getMaxNoOfDirectoryEntries(){
	//memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
	return directoryPageHeader_.maxNoOfDirectoryEntries_;
}

int DirectoryPage::getMaxFreeSpace(){
	//memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
	return directoryPageHeader_.maxFreeSpace_;
}

int DirectoryPage::getHeaderOffset(){
	//memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
		return directoryPageHeader_.headerOffset_;
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
	directoryPageHeader_.noOfDirectoryEntries_=noOfDirectoryEntries;
	memcpy(pageData_,&directoryPageHeader_,sizeof(DirectoryPageHeaderStruct));
	isDirectoryPageChanged_=true;
	buffManager_->writePage(fd_,pageNumber_,pageData_);
}

void DirectoryPage::setMaxNoOfDirectoryEntries(int maxNoOfDirectoryEntries){
	//memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
	directoryPageHeader_.maxNoOfDirectoryEntries_=maxNoOfDirectoryEntries;
	memcpy(pageData_,&directoryPageHeader_,sizeof(DirectoryPageHeaderStruct));
	isDirectoryPageChanged_=true;
	buffManager_->writePage(fd_,pageNumber_,pageData_);
}

void DirectoryPage::setMaxFreeSpace(int maxFreeSpace){
	//memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
	directoryPageHeader_.maxFreeSpace_=maxFreeSpace;
	memcpy(pageData_,&directoryPageHeader_,sizeof(DirectoryPageHeaderStruct));
	isDirectoryPageChanged_=true;
	buffManager_->writePage(fd_,pageNumber_,pageData_);
}

void DirectoryPage::setHeaderOffset(int headerOffset){
	//memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
		directoryPageHeader_.headerOffset_=headerOffset;
		memcpy(pageData_,&directoryPageHeader_,sizeof(DirectoryPageHeaderStruct));
		isDirectoryPageChanged_=true;
		buffManager_->writePage(fd_,pageNumber_,pageData_);
}

void DirectoryPage::setPageNumber(int pageNumber){
	//memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
	directoryPageHeader_.genPageHeader_.pageNumber=pageNumber;
	memcpy(pageData_,&directoryPageHeader_,sizeof(DirectoryPageHeaderStruct));
	isDirectoryPageChanged_=true;
	buffManager_->writePage(fd_,pageNumber_,pageData_);
}

void DirectoryPage::setPageType(int pageType){
	//memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
	directoryPageHeader_.genPageHeader_.pageType=pageType;
	memcpy(pageData_,&directoryPageHeader_,sizeof(DirectoryPageHeaderStruct));
	isDirectoryPageChanged_=true;
	buffManager_->writePage(fd_,pageNumber_,pageData_);
}

void DirectoryPage::setNextPageNumber(int nextPageNumber){
	//memcpy(&directoryPageHeader_,pageData_,sizeof(DirectoryPageHeaderStruct));
	directoryPageHeader_.genPageHeader_.nextPageNumber=nextPageNumber;
	memcpy(pageData_,&directoryPageHeader_,sizeof(DirectoryPageHeaderStruct));
	isDirectoryPageChanged_=true;
	buffManager_->writePage(fd_,pageNumber_,pageData_);
}
