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
	delete[] pageData_;
	delete[] openDatabaseName_;
}

int DatabaseOperations::createDatabase(char *databaseName){
	createDatabase(databaseName,DEFAULT_DB_SIZE);
	//delete[] databaseName;
	return SUCCESS;
}


int DatabaseOperations::createDatabase(char *databaseName,int databaseSize){
	int noOfPages=(databaseSize*1024*1024)/DEFAULT_PAGE_SIZE;
	int sysTablePageNumber_,sysColumnPageNumber_,indexCatalogPageNumber_;
	buffManager_=BufferManager::getInstance();
	buffManager_->createDatabase(databaseName,DEFAULT_PAGE_SIZE,noOfPages);
	fd_=buffManager_->openDatabase(databaseName);
	DBMainHeaderPage *dbMainHeader_=new DBMainHeaderPage(fd_,0);


	dbMainHeader_->createDBMainHeaderStruct(databaseName,noOfPages,DEFAULT_PAGE_SIZE);

	FreePageManager *freePageManager_=new FreePageManager(fd_,1);
	freePageManager_->createFreePageManagerPage(1);


	sysTablePageNumber_=freePageManager_->getFreePage();
	SysTablesCatalog *sysTablePage_=new SysTablesCatalog(fd_,sysTablePageNumber_);
	sysTablePage_->createSysTablePage(sysTablePageNumber_);


	sysColumnPageNumber_=freePageManager_->getFreePage();
	SysColumnsCatalog *sysColumnPage_=new SysColumnsCatalog(fd_,sysColumnPageNumber_);
	sysColumnPage_->createSysColumnsPage(sysColumnPageNumber_);

	indexCatalogPageNumber_=freePageManager_->getFreePage();
	IndexCatalog *indexCatalogPage_=new IndexCatalog();
	indexCatalogPage_->createIndexCatalogPage(indexCatalogPageNumber_);

	dbMainHeader_->setFreeStructurePageNumber(1);
	dbMainHeader_->setSysTablesHeaderPageNumber(sysTablePageNumber_);
	dbMainHeader_->setSysColumnHeaderPageNumber(sysColumnPageNumber_);
	dbMainHeader_->setIndexCatalogHeaderPageNumber(indexCatalogPageNumber_);
	dbMainHeader_->setNoOfPagesUsed(dbMainHeader_->getNoOfPagesUsed()+3);

	//buffManager_->commitCache();
	buffManager_->closeDatabase(fd_);

	delete dbMainHeader_;
	delete freePageManager_;
	delete sysTablePage_;
	delete sysColumnPage_;
	delete indexCatalogPage_;

	return fd_;
}
int DatabaseOperations::openDatabase(char *databaseName){
	// What should happen if another database is opened???
	strcpy(openDatabaseName_,databaseName);
	isDatabaseOpen_=true;
	fd_=buffManager_->openDatabase(databaseName);
	dbMainHeader_=new DBMainHeaderPage(fd_,0);
	//freePageManager_=new FreePageManager(fd_,1);
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
	dirHeaderPage_->createDirectoryHeaderPageHeaderStruct(dirHeaderPageNumber_);
	int directoryPageNumber_=freePageManager_->getFreePage();
	DirectoryPage *dirPage_=new DirectoryPage(fd_,directoryPageNumber_);
	dirPage_->createDirectoryPage(directoryPageNumber_);
	dirHeaderPage_->setNoOfDirectoryPages(1);
	dirHeaderPage_->setNextPageNumber(directoryPageNumber_);
	dbMainHeader_->setNoOfPagesUsed(dbMainHeader_->getNoOfPagesUsed()+2);
	dbMainHeader_->setNoOfTables(dbMainHeader_->getNoOfTables()+1);

	SysTablesCatalog *sysTableCatalog=new SysTablesCatalog(fd_,dbMainHeader_->getSysTablesHeaderPageNumber());
	//cout << " middle of create table"<< endl;
	//TODO:max record size needs to be computed from the column types
	sysTableCatalog->insertSysTableEntry(tableName,DEFAULT_PAGE_SIZE,
			columnList.size(),dirHeaderPage_->getPageNumber());
	//cout << " middle of create table"<< endl;
	SysColumnsCatalog *sysColumnCatalog=new SysColumnsCatalog(fd_,dbMainHeader_->getSysColumnHeaderPageNumber());
	for(unsigned i=0;i<columnList.size();i++){
		colPos=CommonUtil::string_to_int(columnTypeList[i].c_str());
		sysColumnCatalog->insertSysColumnEntry((char *)columnList[i].c_str(),tableName,i,colPos);
	}

	//cout << " end of create table"<< endl;

	//buffManager_->commitCache();
	delete dbMainHeader_;
	delete freePageManager_;
	delete dirHeaderPage_;
	delete sysTableCatalog;
	delete sysColumnCatalog;
	delete dirPage_;
	return SUCCESS;
}

int DatabaseOperations::insertIntoTable(char *tableName, vector<string> insertValues){
	//we need schema to convert "insert into .." statement to insertvalues vector;
	int dirPageNumber_=-1,dirEntryNumber=-1;
	int recordLength;
	char *recordString=new char[DEFAULT_PAGE_SIZE];
	FreePageManager * freePageManager_=new FreePageManager(fd_,1);
	DataPage *dataPage;
	Record *record=new Record();
	//	int dpChainHeader_=5;
	//	int noOfColumns_=3;
	int dpChainHeader_=sysTableCatalog_->getDPChainHeaderPageNumber(tableName);
	//int noOfColumns_=sysTableCatalog_->getNoOfColumns(tableName);
	DirectoryHeaderPage *dirHeaderPage_= new DirectoryHeaderPage(fd_,dpChainHeader_);
	dirPageNumber_=dirHeaderPage_->getNextPageNumber();
	DirectoryPage *dirPage_;
	if(dirPageNumber_!=-1){
		dirPage_=new DirectoryPage(fd_,dirPageNumber_);

	}
	else{
		dirPageNumber_=freePageManager_->getFreePage();
		dirPage_=new DirectoryPage(fd_,dirPageNumber_);
		dirPage_->createDirectoryPage(dirPageNumber_);
		dirHeaderPage_->setNextPageNumber(dirPageNumber_);
	}


	record->getRecordString(insertValues,recordString,&recordLength);

	while(dirPage_->getMaxFreeSpace()<recordLength){
		dirPageNumber_=dirPage_->getNextPageNumber();
		if(dirPageNumber_!=-1){
			delete dirPage_;
			dirPage_=new DirectoryPage(fd_,dirPageNumber_);
		}
		else{
			dirPageNumber_=freePageManager_->getFreePage();
			dirPage_->setNextPageNumber(dirPageNumber_);
			delete dirPage_;
			dirPage_=new DirectoryPage(fd_,dirPageNumber_);
			dirPage_->createDirectoryPage(dirPageNumber_);
			cout << "dirPageNumber : "<< dirPageNumber_ << endl;
		}
	}
	//cout << "dirPageNumber : "<< dirPageNumber_ << endl;
	DirectoryEntry::DirectoryEntryStruct dirSlotEntry=dirPage_->insertSlotEntry(recordLength+DataPage::getDataSlotEntrySize(),&dirEntryNumber);
	//cout <<"-----------------"<<dirSlotEntry.pageNumber_<< endl;
	dataPage=new DataPage(fd_,dirSlotEntry.pageNumber_);
	freePageManager_->setPage(dirSlotEntry.pageNumber_);
	//cout << "data page is: " << dirSlotEntry.pageNumber_ << endl;
	if(dirSlotEntry.freeSpace_ == DEFAULT_PAGE_SIZE-DataPage::getDataPageSize()-recordLength-DataPage::getDataSlotEntrySize()){
		//cout << "=================you will see this================="<<endl;
		dataPage->createDataPageHeaderStruct(dirSlotEntry.pageNumber_);
		dataPage->setDirectoryPageBackPtr(dirPageNumber_);
		dataPage->setDirectoryEntryBackPtr(dirEntryNumber);
	}
	//cout << "print this also " << recordLength<< endl;
	dataPage->insertRecord(recordString,recordLength);
	//cout << "print this also2" << endl;

	//buffManager_->commitCache();
	delete[] recordString;
	delete freePageManager_;
	delete dirHeaderPage_;
	delete dirPage_;
	delete record;
	delete dataPage;
	//insertValues.clear();
	return SUCCESS;
}

int DatabaseOperations::selectAllFromTable(char *tableName, vector<string> columnList){
	Schema schema;
	vector<string> tableEntry=sysTableCatalog_->getSysTableRecordAsVector(tableName);
	if(tableEntry.size()==0){
		cout << tableName << " does not exist in the current Database!" << endl;
		return -1;
	}
	vector<string> recordVector;
	//vector<string> recordsVector;
	int dirPageNumber_=-1;
	int recordLength;
	int dataPageNumber,noOfDirEntries,noOfRecordsInDataPage;
	Record *record;
	DirectoryPage *dirPage_;
	char *recordString;
	DataPage *dataPage;
	//		int dpChainHeader_=5;
	//		int noOfColumns_=3;
	int dpChainHeader_=sysTableCatalog_->getDPChainHeaderPageNumber(tableName);
	int noOfColumns_=sysTableCatalog_->getNoOfColumns(tableName);

	sysColumnCatalog_->getTableSchema(tableName,schema);

	/*		cout << "No of columns is: "<< schema.columnNames.size() << endl;
		for(int i=0;i<schema.columnNames.size();i++){
			cout << schema.columnNames[i].c_str() << endl;
			cout << schema.fieldPosition[i] << endl;
			cout << schema.fieldTypes[i] << endl;
			cout << endl << endl;
		}*/
	DirectoryHeaderPage *dirHeaderPage_= new DirectoryHeaderPage(fd_,dpChainHeader_);
	dirPageNumber_=dirHeaderPage_->getNextPageNumber();

	//loop the following for all the directory pages of table;
	while(dirPageNumber_!=-1){
		dirPage_=new DirectoryPage(fd_,dirPageNumber_);
		DirectoryEntry::DirectoryEntryStruct dirEntry_;
		record=new Record();
		noOfDirEntries=dirPage_->getNoOfDirectoryEntries();
		//cout <<" no of dir entries :" <<noOfDirEntries << endl;
		for(int i=0;i<noOfDirEntries;i++){
			dirEntry_=dirPage_->getDirectorySlot(i);
			//cout << dirEntry_.pageNumber_  << " " << dirEntry_.freeSpace_<< endl;
			if(dirEntry_.freeSpace_< DEFAULT_PAGE_SIZE-DataPage::getDataPageSize()){
				dataPageNumber=dirEntry_.pageNumber_;
				//cout << dataPageNumber << endl;
				dataPage=new DataPage(fd_,dataPageNumber);
				noOfRecordsInDataPage=dataPage->getNoOfRecords();
				//cout << noOfRecordsInDataPage << endl;
				for(int j=0;j<noOfRecordsInDataPage;j++){

					cout << "in j= " << j<<endl;
					recordString=new char[DEFAULT_PAGE_SIZE];
					dataPage->getRecord(j,recordString,&recordLength);
					//buffManager_->hexDump(recordString);
					if(recordLength>0){
						cout << "don't come here" << endl;
						recordVector=record->getvectorFromRecord(recordString,noOfColumns_);
						delete[] recordString;
						stringstream recordStream;
						int pos;

						for(unsigned c=0;c<columnList.size();c++){
							pos= schema.getColumnNum(columnList[c].c_str());
							if(schema.fieldTypes[pos]==TYPE_BOOL) {
								if(strcmp(recordVector[pos].c_str(),"1")==0)
									recordStream<< " 'TRUE' ";
								else
									recordStream<< " 'FALSE' ";
							}
							else

								recordStream<< " '"<<recordVector[pos].c_str()<<"' ";
						}

						//cout << j << endl;
						cout << recordStream.str() << endl;
						//recordStream.clear();
						//recordsVector.push_back(recordStream.str());
					}
					else{
						delete[] recordString;
					}
				}
				delete dataPage;
			}
		}
		dirPageNumber_=dirPage_->getNextPageNumber();
		delete dirPage_;
		delete record;
		//cout << dirPageNumber_ << endl;
	}
	//		for(int l=0;l<recordsVector.size();l++){
	//			//cout << recordsVector[l].c_str() << endl;
	//		}
	delete dirHeaderPage_;
	//return recordsVector;
	return SUCCESS;
}


int DatabaseOperations::dropTable(char *tableName){
	vector<string> tableEntry=sysTableCatalog_->getSysTableRecordAsVector(tableName);
	if(tableEntry.size()==0){
		cout << tableName << " does not exist in the current Database!" << endl;
		return -1;
	}
	int dpChainHeader_=sysTableCatalog_->getDPChainHeaderPageNumber(tableName);
	sysTableCatalog_->deleteSysTableEntry(tableName);
	sysColumnCatalog_->deleteSysColumnEntryForTable(tableName);
	DirectoryHeaderPage *dirHeaderPage_= new DirectoryHeaderPage(fd_,dpChainHeader_);
	dirHeaderPage_->deleteDirectoryHeaderPage();
	dbMainHeader_->setNoOfTables(dbMainHeader_->getNoOfTables()-1);
	delete dirHeaderPage_;
	return SUCCESS;
}


int DatabaseOperations::deleteFromTable(char *tableName){
	Schema schema;
	vector<string> tableEntry=sysTableCatalog_->getSysTableRecordAsVector(tableName);
	if(tableEntry.size()==0){
		cout << tableName << " does not exist in the current Database!" << endl;
		return -1;
	}
	if(0){ // for delete * from table;
		int dpChainHeader_=sysTableCatalog_->getDPChainHeaderPageNumber(tableName);
		DirectoryHeaderPage *dirHeaderPage_= new DirectoryHeaderPage(fd_,dpChainHeader_);
		int dirPageNumber_=dirHeaderPage_->getNextPageNumber();
		while(dirPageNumber_!=-1){
			DirectoryPage *dirPage_=new DirectoryPage(fd_,dirPageNumber_);
			dirPageNumber_=dirPage_->getNextPageNumber();
			dirPage_->deleteDirectoryPage();
			delete dirPage_;
		}
		dirHeaderPage_->setNoOfDirectoryPages(0);
		dirHeaderPage_->setNextPageNumber(-1);
		delete dirHeaderPage_;
	}


	else{
		vector<string> recordVector;
		int dirPageNumber_=-1;
		int recordLength;
		int dataPageNumber,noOfDirEntries,noOfRecordsInDataPage;
		Record *record;
		DirectoryPage *dirPage_;
		char *recordString;
		DataPage *dataPage;
		int dpChainHeader_=sysTableCatalog_->getDPChainHeaderPageNumber(tableName);
		int noOfColumns_=sysTableCatalog_->getNoOfColumns(tableName);

		sysColumnCatalog_->getTableSchema(tableName,schema);

		DirectoryHeaderPage *dirHeaderPage_= new DirectoryHeaderPage(fd_,dpChainHeader_);
		dirPageNumber_=dirHeaderPage_->getNextPageNumber();

		//loop the following for all the directory pages of table;
		while(dirPageNumber_!=-1){
			dirPage_=new DirectoryPage(fd_,dirPageNumber_);
			DirectoryEntry::DirectoryEntryStruct dirEntry_;
			record=new Record();
			noOfDirEntries=dirPage_->getNoOfDirectoryEntries();
			//cout <<" no of dir entries :" <<noOfDirEntries << endl;
			for(int i=0;i<noOfDirEntries;i++){
				dirEntry_=dirPage_->getDirectorySlot(i);
				//cout << dirEntry_.pageNumber_  << " " << dirEntry_.freeSpace_<< endl;
				if(dirEntry_.freeSpace_< DEFAULT_PAGE_SIZE-DataPage::getDataPageSize()){
					dataPageNumber=dirEntry_.pageNumber_;
					//cout << dataPageNumber << endl;
					dataPage=new DataPage(fd_,dataPageNumber);
					noOfRecordsInDataPage=dataPage->getNoOfRecords();
					//cout << noOfRecordsInDataPage << endl;
					for(int j=0;j<noOfRecordsInDataPage;j++){
						recordString=new char[DEFAULT_PAGE_SIZE];
						dataPage->getRecord(j,recordString,&recordLength);
						//buffManager_->hexDump(recordString);
						recordVector=record->getvectorFromRecord(recordString,noOfColumns_);
						delete[] recordString;
						stringstream recordStream;


						// check the where condition while deleting
						dataPage->freeSlotDirectoryEntry(j);

						//						int pos;
						//						for(unsigned c=0;c<columnList.size();c++){
						//							pos= schema.getColumnNum(columnList[c].c_str());
						//							if(schema.fieldTypes[pos]==TYPE_BOOL) {
						//								if(strcmp(recordVector[pos].c_str(),"1")==0)
						//									recordStream<< " 'TRUE' ";
						//								else
						//									recordStream<< " 'FALSE' ";
						//							}
						//							else
						//
						//								recordStream<< " '"<<recordVector[pos].c_str()<<"' ";
						//						}
						//cout << recordStream.str() << endl;
					}
					delete dataPage;
				}
			}
			dirPageNumber_=dirPage_->getNextPageNumber();
			delete dirPage_;
			delete record;
			//cout << dirPageNumber_ << endl;
		}
		delete dirHeaderPage_;
		//return recordsVector;

	}
	return SUCCESS;
}
