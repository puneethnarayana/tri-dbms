/*
 * IndexHeader.cpp
 *
 *  Created on: Oct 23, 2013
 *      Author: puneeth
 */

#include "IndexHeader.h"
#include "LeafNode.h"
#include "IndexNode.h"
#include "../BufferManagement/BufferManager.h"
#include "../Global/globalStructures.h"
#include "../Global/globalDefines.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>



IndexHeader::IndexHeader(int fd,int indexHeaderPageNumber) {
	// TODO Auto-generated constructor stub
	fd_=fd;
	pageNumber_= indexHeaderPageNumber;
	buffManager_ = BufferManager::getInstance();
	pageData_=new char[DEFAULT_PAGE_SIZE];
	memset(pageData_,0,DEFAULT_PAGE_SIZE);
	buffManager_->readPage(fd,indexHeaderPageNumber,pageData_);
	memcpy(&indexHeaderPage_,pageData_,sizeof(IndexHeaderStruct));
	isIndexHeaderChanged_ = false;
	initializeColumns();

}

IndexHeader::~IndexHeader() {
	// TODO Auto-generated destructor stub

	buffManager_=BufferManager::getInstance();
	buffManager_->writePage(fd_,pageNumber_,pageData_);

	delete []pageData_;
}

void IndexHeader::createIndexHeaderPage(int numOfColumns, int colTypes[],int colSizes[], int keySize){

	indexHeaderPage_.generalPageHeaderStruct.pageNumber=pageNumber_;
	indexHeaderPage_.generalPageHeaderStruct.nextPageNumber=-1;
	indexHeaderPage_.generalPageHeaderStruct.pageType = INDEX_HEADER_PAGE;
	indexHeaderPage_.keySize = keySize;
	indexHeaderPage_.maxNoOfRecordsInLeaf = (int) floor((DEFAULT_PAGE_SIZE
			- (LeafNode::getLeafNodeHeaderSize())) / (keySize + sizeof(RIDStruct)));
	indexHeaderPage_.fanout = (int) floor((DEFAULT_PAGE_SIZE
			- IndexNode::getIndexNodeHeaderSize()) / (keySize + 4));
	indexHeaderPage_.rootPageNumber = -1;
	indexHeaderPage_.heightOfTree = 0;
	indexHeaderPage_.numberOfKeys = 0;
	indexHeaderPage_.noOfcolumns = numOfColumns;

	memcpy(pageData_, &indexHeaderPage_, sizeof(IndexHeaderStruct));
	int offset = sizeof(IndexHeaderStruct);
	for (int i = 0; i < numOfColumns; i++) {
		memcpy(&pageData_[offset], &colTypes[i], sizeof(int));
		offset += sizeof(int);
	}
	for (int i = 0; i < numOfColumns; i++) {
		memcpy(&pageData_[offset], &colSizes[i], sizeof(int));
		offset += sizeof(int);
	}
	buffManager_=BufferManager::getInstance();
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	initializeColumns();

}


void IndexHeader::initializeColumns(){
	int offset = sizeof(IndexHeaderStruct);

	colTypes_ = new int[indexHeaderPage_.noOfcolumns];
	for (int i=0; i < indexHeaderPage_.noOfcolumns; i++){
		memcpy(&colTypes_[i],&pageData_[offset],sizeof(int));
		offset += sizeof(int);
	}

	colSizes_ = new int[indexHeaderPage_.noOfcolumns];
	for(int j=0;j<indexHeaderPage_.noOfcolumns;j++){
		memcpy(&colSizes_[j],&pageData_[offset],sizeof(int));
		offset += sizeof(int);
	}

}

int IndexHeader::getRootPageNumber(){
	//memcpy(&indexHeaderPage_, pageData_, sizeof(IndexHeaderStruct));
	return indexHeaderPage_.rootPageNumber;
}

void IndexHeader::setRootPageNumber(int rootPageNumber){
	//memcpy(&indexHeaderPage_,pageData_,sizeof(IndexHeaderStruct));
	indexHeaderPage_.rootPageNumber = rootPageNumber;
	memcpy(pageData_,&indexHeaderPage_,sizeof(IndexHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isIndexHeaderChanged_=true;
}

int IndexHeader::getFanout(){
	//memcpy(&indexHeaderPage_, pageData_, sizeof(IndexHeaderStruct));
	return indexHeaderPage_.fanout;
}

void IndexHeader::setFanout(int fanout){
	//memcpy(&indexHeaderPage_,pageData_,sizeof(IndexHeaderStruct));
	indexHeaderPage_.fanout = fanout;
	memcpy(pageData_,&indexHeaderPage_,sizeof(IndexHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isIndexHeaderChanged_=true;
}

int IndexHeader::getHeightOfTree(){
	//memcpy(&indexHeaderPage_, pageData_, sizeof(IndexHeaderStruct));
	return indexHeaderPage_.heightOfTree;
}

void IndexHeader::setHeightOfTree(int heightOfTree){
	//memcpy(&indexHeaderPage_,pageData_,sizeof(IndexHeaderStruct));
	indexHeaderPage_.heightOfTree = heightOfTree;
	memcpy(pageData_,&indexHeaderPage_,sizeof(IndexHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isIndexHeaderChanged_=true;
}

int IndexHeader::getMaxNoOfRecordsInLeaf(){
	//memcpy(&indexHeaderPage_, pageData_, sizeof(IndexHeaderStruct));
	return indexHeaderPage_.maxNoOfRecordsInLeaf;
}

void IndexHeader::setMaxNoOfRecordsInLeaf(int maxNoOfRecords){
	//mmemcpy(&indexHeaderPage_,pageData_,sizeof(IndexHeaderStruct));
	indexHeaderPage_.maxNoOfRecordsInLeaf = maxNoOfRecords;
	memcpy(pageData_,&indexHeaderPage_,sizeof(IndexHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isIndexHeaderChanged_=true;
}

int IndexHeader::getKeySize(){
	//memcpy(&indexHeaderPage_,pageData_,sizeof(IndexHeaderStruct));
	return indexHeaderPage_.keySize;
}

void IndexHeader::setKeySize(int keySize){
	//memcpy(&indexHeaderPage_,pageData_,sizeof(IndexHeaderStruct));
	indexHeaderPage_.keySize = keySize;
	memcpy(pageData_,&indexHeaderPage_,sizeof(IndexHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isIndexHeaderChanged_=true;
}

int IndexHeader::getNoOfKeys(){
	//memcpy(&indexHeaderPage_,pageData_,sizeof(IndexHeaderStruct));
	return indexHeaderPage_.numberOfKeys;
}

void IndexHeader::setNoOfKeys(int numberOfKeys){
	//memcpy(&indexHeaderPage_,pageData_,sizeof(IndexHeaderStruct));
	indexHeaderPage_.numberOfKeys = numberOfKeys;
	memcpy(pageData_,&indexHeaderPage_,sizeof(IndexHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isIndexHeaderChanged_=true;
}

int IndexHeader::getNoOfColumns(){
	//memcpy(&indexHeaderPage_,pageData_,sizeof(IndexHeaderStruct));
	return indexHeaderPage_.noOfcolumns;
}

void IndexHeader::setNoOfColumns(int noOfColumns){
	//memcpy(&indexHeaderPage_,pageData_,sizeof(IndexHeaderStruct));
	indexHeaderPage_.noOfcolumns = noOfColumns;
	memcpy(pageData_,&indexHeaderPage_,sizeof(IndexHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isIndexHeaderChanged_=true;
}

int IndexHeader::getPageNumber(){
	//memcpy(&indexHeaderPage_,pageData_,sizeof(IndexHeaderStruct))
	return indexHeaderPage_.generalPageHeaderStruct.pageNumber;
}

void IndexHeader::setPageNumber(int pageNumber){
	//memcpy(&indexHeaderPage_,pageData_,sizeof(IndexHeaderStruct));
	indexHeaderPage_.generalPageHeaderStruct.pageNumber = pageNumber;
	memcpy(pageData_,&indexHeaderPage_,sizeof(IndexHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isIndexHeaderChanged_=true;
}

int IndexHeader::getPageType(){
	//memcpy(&indexHeaderPage_,pageData_,sizeof(IndexHeaderStruct))
	return indexHeaderPage_.generalPageHeaderStruct.pageType;
}

void IndexHeader::setPageType(int pageType){
	//memcpy(&indexHeaderPage_,pageData_,sizeof(IndexHeaderStruct));
	indexHeaderPage_.generalPageHeaderStruct.pageType = pageType;
	memcpy(pageData_,&indexHeaderPage_,sizeof(IndexHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isIndexHeaderChanged_=true;
}

int IndexHeader::getNextPageNumber(){
	//memcpy(&indexHeaderPage_,pageData_,sizeof(IndexHeaderStruct))
	return indexHeaderPage_.generalPageHeaderStruct.nextPageNumber;
}

void IndexHeader::setNextPageNumber(int nextPageNumber){
	//memcpy(&indexHeaderPage_,pageData_,sizeof(IndexHeaderStruct));
	indexHeaderPage_.generalPageHeaderStruct.nextPageNumber = nextPageNumber;
	memcpy(pageData_,&indexHeaderPage_,sizeof(IndexHeaderStruct));
	buffManager_->writePage(fd_,pageNumber_,pageData_);
	isIndexHeaderChanged_=true;
}

void IndexHeader::UIIndexHeaderPage() {
	cout
			<< "\n\t********************-INDEX HEADER PAGE-***********************"
			<< endl;
	cout << "\tINDEX HEADER PAGE NUMBER------------:" << getPageNumber()
			<< endl;
	cout << "\tRoot page number--------------------:" << getRootPageNumber() << endl;
	cout << "\tIndexNode fanout--------------------:" << getFanout() << endl;
	cout << "\tMaximum records in leaf page--------:"
			<< getMaxNoOfRecordsInLeaf() << endl;
	cout << "\tHeight of tree----------------------:" << getHeightOfTree()
			<< endl;
	cout << "\tNumber of columns in Index----------:" << getNoOfColumns()
			<< endl;
	cout << "\tKey size----------------------------:" << getKeySize() << endl;
	cout << "\tNumber of Keys----------------------:" << getNoOfKeys()
			<< endl;
	for (int i = 0; i < getNoOfColumns(); i++) {
		char columnT[10];
		memset(columnT, '\0', 10);
		switch (colTypes_[i]) {
		case 1:
			memcpy(columnT, "INTEGER", sizeof("INTEGER"));
			break;
		case 2:
			memcpy(columnT, "FLOAT", sizeof("FLOAT"));
			break;
		case 3:
			memcpy(columnT, "DOUBLE", sizeof("DOUBLE"));
			break;
		case 4:
			memcpy(columnT, "STRING", sizeof("STRING"));
			break;
		case 5:
			memcpy(columnT, "LONG", sizeof("LONG"));
			break;
		}
		cout << "\tColumn Types [field " << i + 1 << "]--------------:"
				<< columnT << endl;
	}
	cout << "\t**************************************************************"
			<< endl;
}
