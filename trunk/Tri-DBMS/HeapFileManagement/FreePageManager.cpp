/*
 * FreePageManager.cpp
 *
 *  Created on: Nov 10, 2013
 *      Author: ravin
 */

#include <iostream>
#include <istream>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>

#include "FreePageManager.h"
#include "../BufferManagement/BufferManager.h"
using namespace std;
FreePageManager::FreePageManager(int fd,int pageNumber) {
	// TODO Auto-generated constructor stub
	fd_=fd;
	pageNumber_=pageNumber;
	buffManager_=BufferManager::getInstance();
	pageData_=new char[DEFAULT_PAGE_SIZE];
	memset(pageData_,0,sizeof(DEFAULT_PAGE_SIZE));
	buffManager_->readPage(fd,pageNumber,pageData_);
	memcpy(&freePageManager_,pageData_,sizeof(freePageStruct));
	isFreePageManagerChanged_=false;
}

FreePageManager::~FreePageManager() {
	// TODO Auto-generated destructor stub
	if(isFreePageManagerChanged_==true){
		buffManager_=BufferManager::getInstance();
		buffManager_->writePage(fd_,pageNumber_,pageData_);
	}
	delete []pageData_;
}

int FreePageManager::createFreePageManagerPage(int pageNumber,char *pageData){
	freePageManager_.genPageHeader_.pageNumber=pageNumber;
	freePageManager_.genPageHeader_.pageType=FREE_PAGE_MANAGER_PAGE;
	freePageManager_.genPageHeader_.nextPageNumber=-1;
	freePageManager_.headerOffset_=sizeof(freePageStruct);
	freePageManager_.maxNoOfPages_=(DEFAULT_PAGE_SIZE-freePageManager_.headerOffset_)*8;
	freePageManager_.noOfFreePages_=(DEFAULT_PAGE_SIZE-freePageManager_.headerOffset_)*8-2;
	memcpy(pageData,&freePageManager_,sizeof(freePageStruct));
	memcpy(pageData_,&freePageManager_,sizeof(freePageStruct));
	pageData[freePageManager_.headerOffset_]=0x03;
	pageData_[freePageManager_.headerOffset_]=0x03;
	isFreePageManagerChanged_= true;
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	return SUCCESS;
}



int FreePageManager::setPage(int pageNumber){
	char mask=0x01;
	mask = mask << (pageNumber % 8);
	int offset=freePageManager_.headerOffset_+pageNumber/8;
	pageData_[offset]=pageData_[offset] | mask;
	isFreePageManagerChanged_= true;
	freePageManager_.noOfFreePages_--;
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	return SUCCESS;
}

int FreePageManager::freePage(int pageNumber){
	char mask=0x01;
	mask = mask << (pageNumber % 8);
	int offset=freePageManager_.headerOffset_+pageNumber/8;
	pageData_[offset]=pageData_[offset] & (~mask);
	isFreePageManagerChanged_= true;
	freePageManager_.noOfFreePages_++;
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	return SUCCESS;
}

bool FreePageManager::isPageFree(int pageNumber){
	char mask=0x01;
		mask = mask << (pageNumber % 8);
		int offset=freePageManager_.headerOffset_+pageNumber/8;
		if((pageData_[offset] & mask)==0){
			return true;
		}
		else{
			return false;
		}
}
int FreePageManager::getFreePage(){
	int i;
	if(freePageManager_.noOfFreePages_!=0){
		cout << "max no of pages is: " << (int)freePageManager_.maxNoOfPages_<< endl;
		for(i=0;i<freePageManager_.maxNoOfPages_;i++){
			if(isPageFree(i) == true){
				setPage(i);
				return i;
			}
		}
	}

	return -1;
}


