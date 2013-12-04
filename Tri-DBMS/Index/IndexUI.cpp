/*
 * IndexUI.cpp
 *
 *  Created on: Dec 4, 2013
 *      Author: bill
 */

#include "IndexUI.h"
#include "../BufferManagement/BufferManager.h"
#include "IndexHeader.h"
#include "BPlusTree.h"
#include <string.h>
#include <iostream>
#include <istream>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <sstream>
#include <string>

IndexUI::IndexUI() {
	// TODO Auto-generated constructor stub

}

void IndexUI::CreateIndexDB(int fanout){
		BufferManager *buffManager=BufferManager::getInstance();
		buffManager->setInitCache(true);
		char *dbname;
		dbname=new char[MAX_FILE_NAME_LENGTH];
		strcpy(dbname,"TestIndex");
		buffManager->createDatabase(dbname,DEFAULT_PAGE_SIZE,10);
		int fd=buffManager->openDatabase(dbname);
		FreePageManager *fpm=new FreePageManager(fd,1);
		fpm->createFreePageManagerPage(1);
		int indexHeaderPageNumber=2;
		int colTypes[1]={TYPE_INT};
		int colSizes[1]={4};
		IndexHeader *indexHeader=new IndexHeader(fd,indexHeaderPageNumber);
		indexHeader->createIndexHeaderPage(1,colTypes,colSizes,4);
		indexHeader->setFanout(fanout);
		indexHeader->setMaxNoOfRecordsInLeaf(fanout+1);
		BPlusTree *BPT = new BPlusTree(fd,indexHeaderPageNumber);
		BPT->userInterface(indexHeaderPageNumber);
		delete dbname;
		delete BPT;
		delete indexHeader;
}

void IndexUI::OpenIndexDB(){
	BufferManager *buffManager=BufferManager::getInstance();
	buffManager->setInitCache(false);
	char *dbname;
	dbname=new char[MAX_FILE_NAME_LENGTH];
	strcpy(dbname,"TestIndex");
	int fd=buffManager->openDatabase(dbname);
	int indexHeaderPageNumber=2;
	buffManager->setInitCache(false);
	BPlusTree *BPT = new BPlusTree(fd,indexHeaderPageNumber);
	BPT->userInterface(indexHeaderPageNumber);
	delete BPT;


}

IndexUI::~IndexUI() {
	// TODO Auto-generated destructor stub
}

