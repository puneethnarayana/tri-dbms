/*
 * DataPage.cpp
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */


#include <iostream>
#include <istream>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include "DataPage.h"
#include "../Global/globalStructures.h"
#include "../Global/globalDefines.h"
#include "../BufferManagement/BufferManager.h"
#include "../HeapFileManagement/FreePageManager.h"
#include <stdio.h>
#include <string.h>
using namespace std;
DataPage::DataPage(int fd,int pageNumber) {
	// TODO Auto-generated constructor stub
	fd_=fd;
	pageNumber_=pageNumber;
	buffManager_=BufferManager::getInstance();
	pageData_=new char[DEFAULT_PAGE_SIZE];
	memset(pageData_,0,DEFAULT_PAGE_SIZE);
	buffManager_->readPage(fd,pageNumber,pageData_);
	memcpy(&dataPageHeader_,pageData_,sizeof(DataPageHeaderStruct));
	isDataPageChanged_=false;
}

DataPage::~DataPage() {
	// TODO Auto-generated destructor stub

		buffManager_=BufferManager::getInstance();
		buffManager_->writePage(fd_,pageNumber_,pageData_);

	delete []pageData_;

}

int DataPage::createDataPageHeaderStruct(int pageNumber){
	dataPageHeader_.genPageHeader_.pageNumber=pageNumber;
	dataPageHeader_.genPageHeader_.pageType=DATA_PAGE;
	dataPageHeader_.genPageHeader_.nextPageNumber=-1;
	dataPageHeader_.noOfRecords_=0;
	dataPageHeader_.headerOffset_=sizeof(DataPageHeaderStruct);
	dataPageHeader_.continuousFreeSpaceOffset_=dataPageHeader_.headerOffset_;
	dataPageHeader_.continuousFreeSpaceAvailable_=DEFAULT_PAGE_SIZE-dataPageHeader_.headerOffset_;
	dataPageHeader_.directoryPageBackPtr=-1;
	dataPageHeader_.directoryEntryBackPtr=-1;
	//memcpy(pageData,&dataPageHeader_,sizeof(DataPageHeaderStruct));
	memcpy(pageData_,&dataPageHeader_,sizeof(DataPageHeaderStruct));
	isDataPageChanged_=true;
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	return SUCCESS;
}

int DataPage::deleteDataPage(){
	FreePageManager *freePageManager=new FreePageManager(fd_,1);
	freePageManager->freePage(pageNumber_);
	//cout << "deleted data pageNo :"<<pageNumber_<<endl;
	memset(pageData_,0,DEFAULT_PAGE_SIZE);
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	delete freePageManager;
	return SUCCESS;
}
int DataPage::insertRecord(char *record,int recordLength){
	int slotNumberForInsert_;
	int offsetForInsert_;
	SlotDirectoryEntry slotDirectoryEntry_;
	slotNumberForInsert_=getSlotNoForRecord(recordLength);
	if(slotNumberForInsert_==-1){
		slotNumberForInsert_=getNoOfRecords();
		addSlotDirectoyEntry(recordLength);
		//cout << "In add" << endl;
	}
	else{
		//cout << "In update : slotNumberForInsert :" << slotNumberForInsert_ << " record length :" << recordLength <<endl;
		updateSlotDirectoryEntry(slotNumberForInsert_,recordLength);
	}
	slotDirectoryEntry_=getSlotDirectoryEntry(slotNumberForInsert_);
	//cout << "page Number "<<pageNumber_;

	offsetForInsert_=slotDirectoryEntry_.recordOffset;
	//cout << "slot number for insert " << slotNumberForInsert_<<endl;
	//cout << "offset for insert " << offsetForInsert_ <<endl;
	memcpy(&pageData_[offsetForInsert_],record,recordLength);
	//cout << "offset for insert is " << offsetForInsert_<<endl;
	//cout << "record length is " << recordLength<<endl;
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDataPageChanged_=true;
	return SUCCESS;
}

int DataPage::getRecord(int slotEntryNumber,char *&record,int *recordLen){
	//stringstream recordstream;
	SlotDirectoryEntry slotEntry_;
	//record=new char[DEFAULT_PAGE_SIZE];
	int slotEntryOffset=DEFAULT_PAGE_SIZE-(slotEntryNumber+1)*sizeof(SlotDirectoryEntry);
	memcpy(&slotEntry_,&pageData_[slotEntryOffset],sizeof(SlotDirectoryEntry));
	if(slotEntry_.recordLength<0){
		*recordLen=-1;
		return -1;
	}
	if(slotEntry_.recordLength>=0){
		memcpy(record,&pageData_[slotEntry_.recordOffset],slotEntry_.recordLength);
	}
	*recordLen=slotEntry_.recordLength;
	return SUCCESS;
}


//
//vector<string> DataPage::getAllRecords(){
//	vector<string> records_;
//	stringstream recordstream;
//	char *record=new char[DEFAULT_PAGE_SIZE];
//	SlotDirectoryEntry slotEntry_;
//	int slotEntryOffset=DEFAULT_PAGE_SIZE-sizeof(SlotDirectoryEntry);
//	memcpy(&dataPageHeader_,pageData_,sizeof(DataPageHeaderStruct));
//	for(unsigned i=0;i<dataPageHeader_.noOfRecords_;i++){
//		memcpy(&slotEntry_,&pageData_[slotEntryOffset],sizeof(SlotDirectoryEntry));
//		memcpy(record,&pageData_[slotEntry_.recordOffset],slotEntry_.recordLength);
//		records_.push_back(record);
//		slotEntryOffset=slotEntryOffset-sizeof(SlotDirectoryEntry);
//	}
//
//
//	return records_;
//}

int DataPage::getOffsetForRecord(int recordLength){
	SlotDirectoryEntry slotDirectoryEntry_;
	slotDirectoryEntry_=getSlotDirectoryEntry(getSlotNoForRecord(recordLength));

	return slotDirectoryEntry_.recordOffset;
}
int DataPage::getSlotNoForOffset(int offset){
	int i;
	int slotEntryOffset_;
	SlotDirectoryEntry slotDirectoryEntry_;
	for(i=0;i<dataPageHeader_.noOfRecords_;i++){
		slotEntryOffset_=DEFAULT_PAGE_SIZE-((i+1)*sizeof(SlotDirectoryEntry));
		memcpy(&slotDirectoryEntry_,&pageData_[slotEntryOffset_],sizeof(SlotDirectoryEntry));
		if(slotDirectoryEntry_.recordOffset == offset){
			return i;
		}
	}
	return -1;
}
int DataPage::getSlotNoForRecord(int recordLength){
	int i;
	int slotEntryOffset_;
	SlotDirectoryEntry slotDirectoryEntry_;
	for(i=0;i<dataPageHeader_.noOfRecords_;i++){
		slotEntryOffset_=DEFAULT_PAGE_SIZE-((i+1)*sizeof(SlotDirectoryEntry));
		memcpy(&slotDirectoryEntry_,&pageData_[slotEntryOffset_],sizeof(SlotDirectoryEntry));
		if(slotDirectoryEntry_.recordLength < 0 && (-slotDirectoryEntry_.recordLength) >= recordLength){
			return i;
		}
	}
	return -1;
}
int DataPage::addSlotDirectoyEntry(int recordLength){
	int slotEntryOffset_=DEFAULT_PAGE_SIZE-((dataPageHeader_.noOfRecords_+1)*sizeof(SlotDirectoryEntry));
	int prevContinuousFreeSpaceOffset=getContinuousFreeSpaceOffset();
	SlotDirectoryEntry slotDirectoryEntry_= {
			getContinuousFreeSpaceOffset() ,
			recordLength
		};
	setContinuousFreeSpaceOffset(getContinuousFreeSpaceOffset()+recordLength);
	setContinuousFreeSpaceAvailable(getContinuousFreeSpaceAvailable()-recordLength-sizeof(SlotDirectoryEntry));
	setNoOfRecords(getNoOfRecords()+1);
	memcpy(&pageData_[slotEntryOffset_],&slotDirectoryEntry_,sizeof(SlotDirectoryEntry));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDataPageChanged_=true;
	//return prevContinuousFreeSpaceOffset;
	return slotEntryOffset_;
}
int DataPage::addSlotDirectoyEntry(int offset,int recordLength){
	int slotEntryOffset_=DEFAULT_PAGE_SIZE-((dataPageHeader_.noOfRecords_+1)*sizeof(SlotDirectoryEntry));
		int prevContinuousFreeSpaceOffset=offset;
		SlotDirectoryEntry slotDirectoryEntry_= {
				offset ,
				recordLength
			};
		setNoOfRecords(getNoOfRecords()+1);
		memcpy(&pageData_[slotEntryOffset_],&slotDirectoryEntry_,sizeof(SlotDirectoryEntry));
		buffManager_->writePage(fd_,pageNumber_,pageData_);
		isDataPageChanged_=true;
		//return prevContinuousFreeSpaceOffset;
		return slotEntryOffset_;
}
int DataPage::updateSlotDirectoryEntry(int slotNumber,int recordLength){
	int newOffset,newFreeSpace;
	int slotEntryOffset_=DEFAULT_PAGE_SIZE-((slotNumber+1)*sizeof(SlotDirectoryEntry));
	SlotDirectoryEntry slotDirectoryEntry_;
	memcpy(&slotDirectoryEntry_,&pageData_[slotEntryOffset_],sizeof(SlotDirectoryEntry));

	newOffset=slotDirectoryEntry_.recordOffset+recordLength;
	newFreeSpace=slotDirectoryEntry_.recordLength+recordLength;
	//cout << "slotDirEntry len :" << slotDirectoryEntry_.recordLength << endl;
	slotDirectoryEntry_.recordLength=recordLength;
	//cout << "slotDirEntry len:" << slotDirectoryEntry_.recordLength << endl;
	//addSlotDirectoyEntry(newOffset,newFreeSpace);
	memcpy(&pageData_[slotEntryOffset_],&slotDirectoryEntry_,sizeof(SlotDirectoryEntry));
	//cout << "slotEntry offset:" << slotEntryOffset_ << endl;
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDataPageChanged_=true;
	return SUCCESS;
}

DataPage::SlotDirectoryEntry DataPage::getSlotDirectoryEntry(int slotNumber){
	SlotDirectoryEntry slotEntry_;
	int slotEntryOffset=DEFAULT_PAGE_SIZE-((slotNumber+1)*sizeof(SlotDirectoryEntry));
	memcpy(&slotEntry_,&pageData_[slotEntryOffset],sizeof(SlotDirectoryEntry));
	return slotEntry_;
}
int DataPage::freeSlotDirectoryEntry(int slotNumber){

	int slotEntryOffset_=DEFAULT_PAGE_SIZE-((slotNumber+1)*sizeof(SlotDirectoryEntry));
	SlotDirectoryEntry slotDirectoryEntry_;
	memcpy(&slotDirectoryEntry_,&pageData_[slotEntryOffset_],sizeof(SlotDirectoryEntry));
	slotDirectoryEntry_.recordLength=-slotDirectoryEntry_.recordLength;
	memcpy(&pageData_[slotEntryOffset_],&slotDirectoryEntry_,sizeof(SlotDirectoryEntry));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
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
int DataPage::getDataSlotEntrySize(){
	return sizeof(SlotDirectoryEntry);
}

int DataPage::getHeaderOffset(){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	return dataPageHeader_.headerOffset_;
}
int DataPage::getContinuousFreeSpaceOffset(){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	return dataPageHeader_.continuousFreeSpaceOffset_;
}
int DataPage::getContinuousFreeSpaceAvailable(){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	return dataPageHeader_.continuousFreeSpaceAvailable_;
}

int DataPage::getDirectoryPageBackPtr(){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	return dataPageHeader_.directoryPageBackPtr;
}

int DataPage::getDirectoryEntryBackPtr(){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	return dataPageHeader_.directoryEntryBackPtr;
}

void DataPage::setPageNumber(int pageNumber){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	dataPageHeader_.genPageHeader_.pageNumber=pageNumber;
	memcpy(pageData_,&dataPageHeader_,sizeof(DataPageHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDataPageChanged_=true;
}
void DataPage::setPageType(int pageType){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	dataPageHeader_.genPageHeader_.pageType=pageType;
	memcpy(pageData_,&dataPageHeader_,sizeof(DataPageHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDataPageChanged_=true;
}
void DataPage::setNextPageNumber(int nextPageNumber){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	dataPageHeader_.genPageHeader_.nextPageNumber=nextPageNumber;
	memcpy(pageData_,&dataPageHeader_,sizeof(DataPageHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDataPageChanged_=true;
}
void DataPage::setNoOfRecords(int noOfRecords){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	dataPageHeader_.noOfRecords_=noOfRecords;
	memcpy(pageData_,&dataPageHeader_,sizeof(DataPageHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDataPageChanged_=true;
}


void DataPage::setContinuousFreeSpaceOffset(int offset){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	dataPageHeader_.continuousFreeSpaceOffset_=offset;
	memcpy(pageData_,&dataPageHeader_,sizeof(DataPageHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDataPageChanged_=true;
}

void DataPage::setContinuousFreeSpaceAvailable(int freeSpace){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	dataPageHeader_.continuousFreeSpaceAvailable_=freeSpace;
	memcpy(pageData_,&dataPageHeader_,sizeof(DataPageHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDataPageChanged_=true;
}

void DataPage::setDirectoryPageBackPtr(int dirPageBackPtr){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	dataPageHeader_.directoryPageBackPtr=dirPageBackPtr;
	memcpy(pageData_,&dataPageHeader_,sizeof(DataPageHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDataPageChanged_=true;
}

void DataPage::setDirectoryEntryBackPtr(int dirEntryBackPtr){
	//memcpy(&dataPageHeader_, pageData_, sizeof(DataPageHeaderStruct));
	dataPageHeader_.directoryEntryBackPtr=dirEntryBackPtr;
	memcpy(pageData_,&dataPageHeader_,sizeof(DataPageHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isDataPageChanged_=true;
}


