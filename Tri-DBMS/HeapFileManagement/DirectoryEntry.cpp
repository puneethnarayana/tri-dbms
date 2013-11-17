/*
 * DirectoryEntry.cpp
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#include "DirectoryEntry.h"
#include "../Global/globalStructures.h"
#include "../Global/globalDefines.h"
#include "../BufferManagement/BufferManager.h"

DirectoryEntry::DirectoryEntry(){
}

DirectoryEntry::DirectoryEntry(int fd, int pageNumber) {
	// TODO Auto-generated constructor stub
	fd_=fd;
	pageNumber_=pageNumber;
	pageData_=new char[DEFAULT_PAGE_SIZE];
	buffManager_=BufferManager::getInstance();
	memset(pageData_,0,sizeof(DEFAULT_PAGE_SIZE));
	buffManager_->readPage(fd,pageNumber,pageData_);
	//memcpy(&directoryEntry_,pageData_,sizeof(DirectoryEntryStruct));
	isDirectoryEntryChanged_=false;
}

DirectoryEntry::~DirectoryEntry() {
	// TODO Auto-generated destructor stub
}

int DirectoryEntry::getDirectoryEntrySize(){
	return sizeof(DirectoryEntryStruct);
}

int DirectoryEntry::getPageNumber(){
	return directoryEntry_.pageNumber_;
}

int DirectoryEntry::getFreeSpace(){
	return directoryEntry_.freeSpace_;
}

void DirectoryEntry::setPageNumber(int pageNumber){
	directoryEntry_.pageNumber_=pageNumber;
}

void DirectoryEntry::setFreeSpace(int freeSpace){
	directoryEntry_.freeSpace_=freeSpace;
}

int DirectoryEntry::createDirectoryEntry(int pageNumber, int freeSpace){
	directoryEntry_.pageNumber_=pageNumber;
	directoryEntry_.freeSpace_=freeSpace;

	return SUCCESS;
}
