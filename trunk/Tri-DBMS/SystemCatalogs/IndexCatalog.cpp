/*
 * IndexCatalog.cpp
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#include "IndexCatalog.h"
#include "../BufferManagement/BufferManager.h"
#include "../Global/globalStructures.h"
#include "../Global/globalDefines.h"
#include "../HeapFileManagement/DataPage.h"
#include "../Utils/CommonUtil.h"
#include "../Utils/Record.h"
#include <vector>
#include <string>
using namespace std;
IndexCatalog::IndexCatalog(int fd,int pageNumber) {
	// TODO Auto-generated constructor stub
	fd_=fd;
	pageNumber_=pageNumber;
	pageData_=new char[DEFAULT_PAGE_SIZE];
	buffManager_ = BufferManager::getInstance();
	memset(pageData_,0,DEFAULT_PAGE_SIZE);
	buffManager_->readPage(fd,pageNumber,pageData_);
	isIndexCatalogChanged_=false;
}

IndexCatalog::~IndexCatalog() {
	// TODO Auto-generated destructor stub
//	if(isIndexCatalogChanged_==true){
//		buffManager_->writePage(fd_,pageNumber_,pageData_);
//	}
	delete[] pageData_;
}


int IndexCatalog::createIndexCatalogPage(int pageNumber){
	DataPage *indexCatalogPage=new DataPage(fd_,pageNumber_);
	indexCatalogPage->createDataPageHeaderStruct(pageNumber_);
	indexCatalogPage->setPageType(INDEX_CATALOG_PAGE);
	delete indexCatalogPage;
	return SUCCESS;
}





int IndexCatalog::insertIndexEntry(char *indexName, char *tableName, char *indexAttribute, int indexType, int keySize,int indexHeaderPageNo){

// Code needs to be written here!!!
	vector<string> values;
	int indexAttributeLength_=0;
	char *recordString=new char[DEFAULT_PAGE_SIZE];
	memset(recordString,0,DEFAULT_PAGE_SIZE);
	Record *record=new Record();
	values.push_back(indexName);
	values.push_back(CommonUtil::int_to_string(indexType));
	values.push_back(CommonUtil::int_to_string(keySize));
	values.push_back(CommonUtil::int_to_string(indexHeaderPageNo));
	values.push_back(tableName);
	values.push_back(indexAttribute);


	record->getRecordString(values,recordString,&indexAttributeLength_);
	DataPage *indexPage=new DataPage(fd_,pageNumber_);
	//buffManager_->hexDump(recordString);
	//cout << "len of index attr:"<<indexAttributeLength_<<endl;
	indexPage->insertRecord(recordString,indexAttributeLength_);
	isIndexCatalogChanged_=true;
	//cout << "after inserting into index catalog"<<endl;
//	buffManager_->commitCache();
//	buffManager_->hexDump(fd_,4);
	delete[] recordString;
	delete indexPage;
	delete record;
	values.clear();
	return SUCCESS;
}


