/*
 * DatabaseOperations.cpp
 *
 *  Created on: Nov 11, 2013
 *      Author: ravin
 */


#include <iostream>
#include <istream>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>

#include "DatabaseOperations.h"
#include "../HeapFileManagement/DBMainHeaderPage.h"
#include "../HeapFileManagement/DirectoryHeaderPage.h"
#include "../HeapFileManagement/DirectoryPage.h"
#include "../HeapFileManagement/DataPage.h"
#include "../HeapFileManagement/DirectoryEntry.h"
#include "../HeapFileManagement/FreePageManager.h"
#include "../SystemCatalogs/SysTablesCatalog.h"
#include "../SystemCatalogs/SysColumnsCatalog.h"
#include "../SystemCatalogs/IndexCatalog.h"
#include "../Global/globalDefines.h"
#include "../Global/globalStructures.h"
#include "../Utils/CommonUtil.h"
#include "../Utils/Record.h"
#include "../BufferManagement/BufferManager.h"
#include "../HeapFileManagement/Schema.h"
#include "../HeapFileManagement/DirectoryEntry.h"

using namespace std;
DatabaseOperations::DatabaseOperations() {
	// TODO Auto-generated constructor stub
	fd_=-1;
	pageData_=new char[DEFAULT_PAGE_SIZE];
	openDatabaseName_=new char[MAX_FILE_NAME_LENGTH];
	buffManager_=BufferManager::getInstance();
	isDatabaseOpen_=false;
}

DatabaseOperations::~DatabaseOperations() {
	// TODO Auto-generated destructor stub
}

int DatabaseOperations::createDatabase(char *databaseName){
	createDatabase(databaseName,DEFAULT_DB_SIZE);
	return SUCCESS;
}


int DatabaseOperations::createDatabase(char *databaseName,int databaseSize){
	int noOfPages=databaseSize*1024*1024/DEFAULT_PAGE_SIZE;
	int sysTablePageNumber_,sysColumnPageNumber_,indexCatalogPageNumber_;
	buffManager_=BufferManager::getInstance();
	buffManager_->createDatabase(databaseName,DEFAULT_PAGE_SIZE,noOfPages);
	fd_=buffManager_->openDatabase(databaseName);
	DBMainHeaderPage *dbMainHeader_=new DBMainHeaderPage(fd_,0);
	pageData_=new char[DEFAULT_PAGE_SIZE];

	dbMainHeader_->createDBMainHeaderStruct(databaseName,noOfPages,DEFAULT_PAGE_SIZE,pageData_);
	pageData_=new char[DEFAULT_PAGE_SIZE];
	FreePageManager *freePageManager_=new FreePageManager(fd_,1);
	freePageManager_->createFreePageManagerPage(1,pageData_);
	pageData_=new char[DEFAULT_PAGE_SIZE];

	sysTablePageNumber_=freePageManager_->getFreePage();
	SysTablesCatalog *sysTablePage_=new SysTablesCatalog(fd_,sysTablePageNumber_);
	sysTablePage_->createSysTablePage(sysTablePageNumber_,pageData_);


	pageData_=new char[DEFAULT_PAGE_SIZE];
	sysColumnPageNumber_=freePageManager_->getFreePage();
	SysColumnsCatalog *sysColumnPage_=new SysColumnsCatalog(fd_,sysColumnPageNumber_);
	sysColumnPage_->createSysColumnsPage(sysColumnPageNumber_,pageData_);

	pageData_=new char[DEFAULT_PAGE_SIZE];
	indexCatalogPageNumber_=freePageManager_->getFreePage();
	IndexCatalog *indexCatalogPage_=new IndexCatalog();
	indexCatalogPage_->createIndexCatalogPage(indexCatalogPageNumber_,pageData_);

	dbMainHeader_->setFreeStructurePageNumber(1);
	dbMainHeader_->setSysTablesHeaderPageNumber(sysTablePageNumber_);
	dbMainHeader_->setSysColumnHeaderPageNumber(sysColumnPageNumber_);
	dbMainHeader_->setIndexCatalogHeaderPageNumber(indexCatalogPageNumber_);
	dbMainHeader_->setNoOfPagesUsed(dbMainHeader_->getNoOfPagesUsed()+3);

	//buffManager_->commitCache();
	buffManager_->closeDatabase(fd_);
	return fd_;
}
int DatabaseOperations::openDatabase(char *databaseName){
	// What should happen if another database is opened???
	strcpy(openDatabaseName_,databaseName);
	isDatabaseOpen_=true;
	fd_=buffManager_->openDatabase(databaseName);
	dbMainHeader_=new DBMainHeaderPage(fd_,0);
	freePageManager_=new FreePageManager(fd_,1);
	sysTableCatalog_=new SysTablesCatalog(fd_,dbMainHeader_->getSysTablesHeaderPageNumber());
	sysColumnCatalog_=new SysColumnsCatalog(fd_,dbMainHeader_->getSysColumnHeaderPageNumber());
	return fd_;
}
int DatabaseOperations::closeDatabase(int fd){
	if(fd!=fd_ || isDatabaseOpen_==false){
		return ERR_DATABASE_NOT_OPEN;
	}
	isDatabaseOpen_=false;
	openDatabaseName_=new char[MAX_FILE_NAME_LENGTH];

	buffManager_->commitCache();
	buffManager_->closeDatabase(fd);
	return SUCCESS;
}

int DatabaseOperations::createTable(char *tableName,vector<string> columnList,vector<string> columnTypeList){
	int i,colPos;
	DBMainHeaderPage *dbMainHeader_=new DBMainHeaderPage(fd_,0);
	FreePageManager *freePageManager_=new FreePageManager(fd_,1);
	int dirHeaderPageNumber_=freePageManager_->getFreePage();
	DirectoryHeaderPage *dirHeaderPage_= new DirectoryHeaderPage(fd_,dirHeaderPageNumber_);
	dirHeaderPage_->createDirectoryHeaderPageHeaderStruct(dirHeaderPageNumber_,pageData_);
	int directoryPageNumber_=freePageManager_->getFreePage();
	DirectoryPage *dirPage_=new DirectoryPage(fd_,directoryPageNumber_);
	dirPage_->createDirectoryPage(directoryPageNumber_,pageData_);
	dirHeaderPage_->setNoOfDirectoryPages(1);
	dirHeaderPage_->setNextPageNumber(directoryPageNumber_);
	dbMainHeader_->setNoOfPagesUsed(dbMainHeader_->getNoOfPagesUsed()+2);
	dbMainHeader_->setNoOfTables(dbMainHeader_->getNoOfTables()+1);

	SysTablesCatalog *sysTableCatalog=new SysTablesCatalog(fd_,dbMainHeader_->getSysTablesHeaderPageNumber());
	//TODO:max record size needs to be computed from the column types
	sysTableCatalog->insertSysTableEntry(tableName,DEFAULT_PAGE_SIZE,
			columnList.size(),dirHeaderPage_->getPageNumber(),pageData_);

	SysColumnsCatalog *sysColumnCatalog=new SysColumnsCatalog(fd_,dbMainHeader_->getSysColumnHeaderPageNumber());
	for(unsigned i=0;i<columnList.size();i++){
		colPos=CommonUtil::string_to_int(columnTypeList[i].c_str());
		sysColumnCatalog->insertSysColumnEntry((char *)columnList[i].c_str(),tableName,i,colPos,pageData_);
	}


	//buffManager_->commitCache();

	return SUCCESS;
}

int DatabaseOperations::insertIntoTable(char *tableName, vector<string> insertValues){
	//we need schema to convert "insert into .." statement to insertvalues vector;
	int dirPageNumber_=-1;
	int recordLength;
	char *pageData=new char[DEFAULT_PAGE_SIZE];
	int dataPageNumber;
	char *recordString=new char[DEFAULT_PAGE_SIZE];
	int dpChainHeader_=sysTableCatalog_->getDPChainHeaderPageNumber(tableName);
	int noOfColumns_=sysTableCatalog_->getNoOfColumns(tableName);


	DirectoryHeaderPage *dirHeaderPage_= new DirectoryHeaderPage(fd_,dpChainHeader_);
	DirectoryPage *dirPage_=new DirectoryPage(fd_,dirHeaderPage_->getNextPageNumber());
	Record *record=new Record();
	record->getRecordString(insertValues,recordString,&recordLength);

	DirectoryEntry::DirectoryEntryStruct dirSlotEntry=dirPage_->insertSlotEntry(recordLength);
	//cout <<"-----------------"<<dirSlotEntry.pageNumber_<< endl;
	DataPage *dataPage=new DataPage(fd_,dirSlotEntry.pageNumber_);

	if(dirSlotEntry.freeSpace_==DEFAULT_PAGE_SIZE-DataPage::getDataPageSize()-recordLength){
		//cout << "=================you will see this================="<<endl;
		dataPage->createDataPageHeaderStruct(dirSlotEntry.pageNumber_,pageData);
	}
	//cout << "print this also " << recordLength<< endl;
	dataPage->insertRecord(recordString,recordLength);
	//cout << "print this also2" << endl;

	//buffManager_->commitCache();
	return SUCCESS;
}


vector<string> DatabaseOperations::selectAllFromTable(char *tableName){
		Schema schema;
		//string record;
		vector<string> recordVector;
		vector<string> recordsVector;
		int dirPageNumber_=-1;
		int recordLength;
		char *pageData=new char[DEFAULT_PAGE_SIZE];
		int dataPageNumber,noOfDirEntries,noOfRecordsInDataPage;
		char *recordString=new char[DEFAULT_PAGE_SIZE];
		int dpChainHeader_=sysTableCatalog_->getDPChainHeaderPageNumber(tableName);
		int noOfColumns_=sysTableCatalog_->getNoOfColumns(tableName);

		sysColumnCatalog_->getTableSchema(tableName,schema);

		//cout << "No of columns is: "<< schema.columnNames.size() << endl;
		for(int i=0;i<schema.columnNames.size();i++){
//			cout << schema.columnNames[i].c_str() << endl;
//			cout << schema.fieldPosition[i] << endl;
//			cout << schema.fieldTypes[i] << endl;
//			cout << endl << endl;
		}
		DirectoryHeaderPage *dirHeaderPage_= new DirectoryHeaderPage(fd_,dpChainHeader_);
		dirPageNumber_=dirHeaderPage_->getNextPageNumber();

		//loop the following for all the directory pages of table;

		DirectoryPage *dirPage_=new DirectoryPage(fd_,dirPageNumber_);
		DirectoryEntry::DirectoryEntryStruct dirEntry_;
		Record *record=new Record();
		noOfDirEntries=dirPage_->getNoOfDirectoryEntries();

		for(int i=0;i<noOfDirEntries;i++){
			dirEntry_=dirPage_->getDirectorySlot(i);
			if(dirEntry_.freeSpace_< DEFAULT_PAGE_SIZE-DataPage::getDataPageSize()){
				dataPageNumber=dirEntry_.pageNumber_;
				DataPage *dataPage=new DataPage(fd_,dataPageNumber);
				noOfRecordsInDataPage=dataPage->getNoOfRecords();
				for(int j=0;j<noOfRecordsInDataPage;j++){
					recordString=new char[DEFAULT_PAGE_SIZE];
					dataPage->getRecord(j,recordString,&recordLength);
					//buffManager_->hexDump(recordString);
					recordVector=record->getvectorFromRecord(recordString,noOfColumns_);
					stringstream recordStream;
					for(int k=0;k<noOfColumns_;k++){
						recordStream<<" '"<<recordVector[k].c_str()<<"' ";
					}
					recordsVector.push_back(recordStream.str());
				}



			}
		}
		for(int l=0;l<recordsVector.size();l++){
			cout << recordsVector[l].c_str() << endl;
		}

		return recordsVector;
}
