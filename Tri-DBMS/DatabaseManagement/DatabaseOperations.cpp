/*
 * DatabaseOperations.cpp
 *
 *  Created on: Nov 11, 2013
 *      Author: ravin
 */

#include <stdio.h>
#include <iostream>
#include <istream>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <string.h>
#include <dirent.h>

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
#include "../Utils/WhereExpressionElement.h"
#include "../Utils/PostFixEvaluator.h"
#include "../Index/IndexHeader.h"
#include "../Index/BPlusTree.h"
#include "../Utils/WhereExpressionElement.h"

extern int indexHeaderPageNo;

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
	return SUCCESS;
}


int DatabaseOperations::createDatabase(char *databaseName,int databaseSize){
	char *dbName=new char[MAX_FILE_NAME_LENGTH+MAX_FILE_NAME_LENGTH];
	strcpy(dbName,databaseName);
	strcpy(databaseName,"./DatabaseFiles/");
	strcat(databaseName,dbName);
	strcat(databaseName,".db");
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
	IndexCatalog *indexCatalogPage_=new IndexCatalog(fd_,indexCatalogPageNumber_);
	indexCatalogPage_->createIndexCatalogPage(indexCatalogPageNumber_);

	dbMainHeader_->setFreeStructurePageNumber(1);
	dbMainHeader_->setSysTablesHeaderPageNumber(sysTablePageNumber_);
	dbMainHeader_->setSysColumnHeaderPageNumber(sysColumnPageNumber_);
	dbMainHeader_->setIndexCatalogHeaderPageNumber(indexCatalogPageNumber_);
	dbMainHeader_->setNoOfPagesUsed(dbMainHeader_->getNoOfPagesUsed()+3);

//	buffManager_->commitCache();
//	buffManager_->hexDump(fd_,1);

	buffManager_->closeDatabase(fd_);

	delete dbMainHeader_;
	delete freePageManager_;
	delete sysTablePage_;
	delete sysColumnPage_;
	delete indexCatalogPage_;
	delete[] dbName;
	//buffManager_->commitCache();

	return fd_;
}
int DatabaseOperations::openDatabase(char *databaseName){
	// What should happen if another database is opened???
	char *dbName=new char[MAX_FILE_NAME_LENGTH+MAX_FILE_NAME_LENGTH];
	strcpy(dbName,databaseName);
	strcpy(databaseName,"./DatabaseFiles/");
	strcat(databaseName,dbName);
	strcat(databaseName,".db");
	//cout <<"in open db:"<< databaseName <<endl;
	strcpy(openDatabaseName_,databaseName);
	isDatabaseOpen_=true;
	fd_=buffManager_->openDatabase(databaseName);
	//cout << "after open db :"<<fd_<<endl;
	//dbMainHeader_=new DBMainHeaderPage(fd_,0);
	//freePageManager_=new FreePageManager(fd_,1);
	//sysTableCatalog_=new SysTablesCatalog(fd_,dbMainHeader_->getSysTablesHeaderPageNumber());
	//sysColumnCatalog_=new SysColumnsCatalog(fd_,dbMainHeader_->getSysColumnHeaderPageNumber());
	delete[] dbName;
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

int DatabaseOperations::createTable(char *tableName,vector<string> columnList,vector<string> columnTypeList,vector<string> columnSizeList){
	int i,colPos,colSize;
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
		colSize=CommonUtil::string_to_int(columnSizeList[i].c_str());
		sysColumnCatalog->insertSysColumnEntry((char *)columnList[i].c_str(),tableName,i,colPos,colSize);
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
	dbMainHeader_=new DBMainHeaderPage(fd_,0);
	sysTableCatalog_=new SysTablesCatalog(fd_,dbMainHeader_->getSysTablesHeaderPageNumber());
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
			//cout << "dirPageNumber : "<< dirPageNumber_ << endl;
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
	//buffManager_->hexDump(recordString);
	//buffManager_->hexDump(fd_,7);
	dataPage->insertRecord(recordString,recordLength);
	//cout << "dirPage No:" << dirPageNumber_ << " dataPage No:"<<dirSlotEntry.pageNumber_<< endl;

	delete dbMainHeader_;
	delete sysTableCatalog_;
	delete[] recordString;
	delete freePageManager_;
	delete dirHeaderPage_;
	delete dirPage_;
	delete record;
	delete dataPage;
	//insertValues.clear();

	return SUCCESS;
}

int DatabaseOperations::selectAllFromTable(char *tableName, vector<string> columnList,vector<WhereExpressionElement> whereExpressions){

	//vector<WhereExpressionElement> whereExpressions;

	/*WhereExpressionElement whereExpr(WhereExpressionElement::IDENTIFIER_TYPE,"col3");
	whereExpressions.push_back(whereExpr);
	WhereExpressionElement whereExpr1(WhereExpressionElement::LITERAL_TYPE,"0");
	whereExpressions.push_back(whereExpr1);
	WhereExpressionElement whereExpr2(WhereExpressionElement::OPERATOR_TYPE,"=");
	whereExpressions.push_back(whereExpr2);
	WhereExpressionElement whereExpr4(WhereExpressionElement::IDENTIFIER_TYPE,"c1");
	whereExpressions.push_back(whereExpr4);
	WhereExpressionElement whereExpr5(WhereExpressionElement::LITERAL_TYPE,"34");
	whereExpressions.push_back(whereExpr5);
	WhereExpressionElement whereExpr6(WhereExpressionElement::OPERATOR_TYPE,"=");
	whereExpressions.push_back(whereExpr6);
	WhereExpressionElement whereExpr3(WhereExpressionElement::OPERATOR_TYPE,"OR");
	whereExpressions.push_back(whereExpr3);*/



	//	strcpy((char *)whereExpr.identifierValue.c_str(),"c1");
	//	strcpy((char *)whereExpr.literalValue.c_str(),"35");
	//	strcpy((char *)whereExpr.operatorValue.c_str(),">");
	//	whereExpressions.push_back(whereExpr);
	dbMainHeader_=new DBMainHeaderPage(fd_,0);
	sysTableCatalog_=new SysTablesCatalog(fd_,dbMainHeader_->getSysTablesHeaderPageNumber());
	sysColumnCatalog_=new SysColumnsCatalog(fd_,dbMainHeader_->getSysColumnHeaderPageNumber());
	delete dbMainHeader_;
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
	delete sysTableCatalog_;
	sysColumnCatalog_->getTableSchema(tableName,schema);
	delete sysColumnCatalog_;
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

					//cout << "in j= " << j<<endl;
					recordString=new char[DEFAULT_PAGE_SIZE];
					dataPage->getRecord(j,recordString,&recordLength);
					//buffManager_->hexDump(recordString);
					if(recordLength>0){
						//cout << "don't come here" << endl;
						recordVector=record->getvectorFromRecord(recordString,noOfColumns_);

						stringstream recordStream;
						int pos;
						Record recordWhere(schema,recordString,recordLength);

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
						if(whereExpressions.size()>0){
							PostFixEvaluator postFixEval(recordWhere);
							//cout << "inside where expr size > 0" << endl;
							if(postFixEval.evaluate(whereExpressions)==true){

								//cout << "after postfix eval"<<  j << endl;
								cout << recordStream.str() << endl;
								//recordStream.clear();
								//recordsVector.push_back(recordStream.str());
							}

						}
						else{
							cout << recordStream.str() << endl;
						}

						delete[] recordString;
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
	DBMainHeaderPage *dbMainHeader_=new DBMainHeaderPage(fd_,0);
	sysTableCatalog_=new SysTablesCatalog(fd_,dbMainHeader_->getSysTablesHeaderPageNumber());
	sysColumnCatalog_=new SysColumnsCatalog(fd_,dbMainHeader_->getSysColumnHeaderPageNumber());

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
	delete dbMainHeader_;
	delete sysTableCatalog_;
	delete sysColumnCatalog_;
	delete dirHeaderPage_;
	return SUCCESS;
}



int DatabaseOperations::deleteFromTable(char *tableName,vector<WhereExpressionElement> whereExpressions){

	//vector<WhereExpressionElement> whereExpressions;

			/*WhereExpressionElement whereExpr(WhereExpressionElement::IDENTIFIER_TYPE,"c1");
		whereExpressions.push_back(whereExpr);
		WhereExpressionElement whereExpr1(WhereExpressionElement::LITERAL_TYPE,"34");
		whereExpressions.push_back(whereExpr1);
		WhereExpressionElement whereExpr2(WhereExpressionElement::OPERATOR_TYPE,"=");
		whereExpressions.push_back(whereExpr2);
		WhereExpressionElement whereExpr4(WhereExpressionElement::IDENTIFIER_TYPE,"c1");
		whereExpressions.push_back(whereExpr4);
		WhereExpressionElement whereExpr5(WhereExpressionElement::LITERAL_TYPE,"83");
		whereExpressions.push_back(whereExpr5);
		WhereExpressionElement whereExpr6(WhereExpressionElement::OPERATOR_TYPE,"=");
		whereExpressions.push_back(whereExpr6);
		WhereExpressionElement whereExpr3(WhereExpressionElement::OPERATOR_TYPE,"OR");
		whereExpressions.push_back(whereExpr3);
			 */
	dbMainHeader_=new DBMainHeaderPage(fd_,0);
	sysTableCatalog_=new SysTablesCatalog(fd_,dbMainHeader_->getSysTablesHeaderPageNumber());
	sysColumnCatalog_=new SysColumnsCatalog(fd_,dbMainHeader_->getSysColumnHeaderPageNumber());
	delete dbMainHeader_;
	Schema schema;
	vector<string> tableEntry=sysTableCatalog_->getSysTableRecordAsVector(tableName);
	if(tableEntry.size()==0){
		cout << tableName << " does not exist in the current Database!" << endl;
		return -1;
	}
	if(whereExpressions.size()==0){ // for delete * from table;
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

						stringstream recordStream;


						// check the where condition while deleting
						Record recordWhere(schema,recordString,recordLength);

						PostFixEvaluator postFixEval(recordWhere);
						//cout << "inside where expr size > 0" << endl;
						if(postFixEval.evaluate(whereExpressions)==true){
							//cout << "inside where expr size == true" << endl;
							dataPage->freeSlotDirectoryEntry(j);
						}

						delete[] recordString;

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
	delete sysTableCatalog_;
	delete sysColumnCatalog_;
	return SUCCESS;
}


int DatabaseOperations::updateTable(char *tableName,vector<string> columnList,vector<string> updateValues,vector<WhereExpressionElement> whereExpressions){


	//vector<WhereExpressionElement> whereExpressions;

		/*	WhereExpressionElement whereExpr(WhereExpressionElement::IDENTIFIER_TYPE,"c1");
		whereExpressions.push_back(whereExpr);
		WhereExpressionElement whereExpr1(WhereExpressionElement::LITERAL_TYPE,"34");
		whereExpressions.push_back(whereExpr1);
		WhereExpressionElement whereExpr2(WhereExpressionElement::OPERATOR_TYPE,"=");
		whereExpressions.push_back(whereExpr2);
		WhereExpressionElement whereExpr4(WhereExpressionElement::IDENTIFIER_TYPE,"co2");
		whereExpressions.push_back(whereExpr4);
		WhereExpressionElement whereExpr5(WhereExpressionElement::LITERAL_TYPE,"Alka");
		whereExpressions.push_back(whereExpr5);
		WhereExpressionElement whereExpr6(WhereExpressionElement::OPERATOR_TYPE,"=");
		whereExpressions.push_back(whereExpr6);
		WhereExpressionElement whereExpr3(WhereExpressionElement::OPERATOR_TYPE,"OR");
		whereExpressions.push_back(whereExpr3);*/
	dbMainHeader_=new DBMainHeaderPage(fd_,0);
	sysTableCatalog_=new SysTablesCatalog(fd_,dbMainHeader_->getSysTablesHeaderPageNumber());
	sysColumnCatalog_=new SysColumnsCatalog(fd_,dbMainHeader_->getSysColumnHeaderPageNumber());
	delete dbMainHeader_;
	Schema schema;
	vector<string> tableEntry=sysTableCatalog_->getSysTableRecordAsVector(tableName);
	if(tableEntry.size()==0){
		cout << tableName << " does not exist in the current Database!" << endl;
		return -1;
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
					delete dataPage;
					//cout << noOfRecordsInDataPage << endl;
					for(int j=0;j<noOfRecordsInDataPage;j++){
						recordString=new char[DEFAULT_PAGE_SIZE];
						dataPage=new DataPage(fd_,dataPageNumber);
						dataPage->getRecord(j,recordString,&recordLength);
						//buffManager_->hexDump(recordString);
						recordVector=record->getvectorFromRecord(recordString,noOfColumns_);

						stringstream recordStream;


						// check the where condition while deleting
						Record recordWhere(schema,recordString,recordLength);
						if(whereExpressions.size()>0){
							PostFixEvaluator postFixEval(recordWhere);
							//cout << "inside where expr size > 0" << endl;
							if(postFixEval.evaluate(whereExpressions)==true){
								//cout << "inside where expr size == true" << endl;
								dataPage->freeSlotDirectoryEntry(j);
								delete dataPage;
								int pos;
								for(unsigned c=0;c<columnList.size();c++){
									pos= schema.getColumnNum(columnList[c].c_str());
									//cout << "c :" << c << " pos :" << pos << endl;
									recordVector[pos]=updateValues[c];
//									for (unsigned i=0;i<recordVector.size();i++){
//										cout << recordVector[i] <<", " ;
//									}
//									cout << endl;
								}
								insertIntoTable(tableName,recordVector);
							}
						}
						else{
							dataPage->freeSlotDirectoryEntry(j);
							delete dataPage;
							int pos;
							for(unsigned c=0;c<columnList.size();c++){
								pos= schema.getColumnNum(columnList[c].c_str());
								recordVector[pos]=updateValues[c];
							}
							insertIntoTable(tableName,recordVector);
						}
						delete[] recordString;


					}

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
	delete sysTableCatalog_;
	delete sysColumnCatalog_;
	return SUCCESS;
}











int DatabaseOperations::createIndex(char *indexName,char *tableName,vector<string> columnList){
	DBMainHeaderPage *dbMainHeader_=new DBMainHeaderPage(fd_,0);
	sysTableCatalog_=new SysTablesCatalog(fd_,dbMainHeader_->getSysTablesHeaderPageNumber());
	sysColumnCatalog_=new SysColumnsCatalog(fd_,dbMainHeader_->getSysColumnHeaderPageNumber());
	Schema schema;
	vector<string> tableEntry=sysTableCatalog_->getSysTableRecordAsVector(tableName);
	if(tableEntry.size()==0){
		cout << tableName << " does not exist in the current Database!" << endl;
		return -1;
	}
	//buffManager_->hexDump(fd_,1);
	FreePageManager *fpMgr_=new FreePageManager(fd_,1);

	int indexCatalogPageNumber=dbMainHeader_->getIndexCatalogHeaderPageNumber();
	delete dbMainHeader_;
	IndexCatalog *indexCatalog=new IndexCatalog(fd_,indexCatalogPageNumber);
	cout << "index cat page no:" <<indexCatalogPageNumber<<endl;
	vector<string> recordVector;
	//vector<string> recordsVector;
	int dirPageNumber_=-1;
	int recordLength;
	int dataPageNumber,noOfDirEntries,noOfRecordsInDataPage;
	Record *record;
	DirectoryPage *dirPage_;
	char *recordString;
	stringstream indexAttribute;
	DataPage *dataPage;
	//		int dpChainHeader_=5;
	//		int noOfColumns_=3;
	int dpChainHeader_=sysTableCatalog_->getDPChainHeaderPageNumber(tableName);
	int noOfColumns_=sysTableCatalog_->getNoOfColumns(tableName);
	delete sysTableCatalog_;
	int pos;
	int keySizeForIndex=0;
	sysColumnCatalog_->getTableSchema(tableName,schema);
	delete sysColumnCatalog_;
	int colTypes[columnList.size()];
	int colSizes[columnList.size()];
	RIDStruct ridForIndex;
	for(unsigned c=0;c<columnList.size();c++){
		pos= schema.getColumnNum(columnList[c].c_str());
		colSizes[c]=schema.fieldLengths[pos];
		colTypes[c]=schema.fieldTypes[pos];
		keySizeForIndex+=schema.fieldLengths[pos];
	}

	for(unsigned c=0;c<columnList.size();c++){
		indexAttribute<<columnList[c].c_str();

	}
	cout << "index Attr :"<<indexAttribute.str()<<endl;
	int indexHeaderPageNumber_=fpMgr_->getFreePage();
	delete fpMgr_;
	indexHeaderPageNo=indexHeaderPageNumber_;
	cout<< "indexHeader page :"<< indexHeaderPageNumber_<<endl;

	IndexHeader *indexHeader=new IndexHeader(fd_,indexHeaderPageNumber_);
	indexHeader->createIndexHeaderPage(columnList.size(),colTypes,colSizes,keySizeForIndex);
	if(columnList.size()==1){
		indexCatalog->insertIndexEntry(indexName,tableName,(char *)indexAttribute.str().c_str(),INDEX_SIMPLE_KEY,keySizeForIndex,indexHeaderPageNumber_,1);
	}
	else{
		indexCatalog->insertIndexEntry(indexName,tableName,(char *)indexAttribute.str().c_str(),INDEX_COMPOSITE_KEY,keySizeForIndex,indexHeaderPageNumber_,1);
	}

	cout << "1" <<endl;

	BPlusTree *bplusTree=new BPlusTree(fd_,indexHeaderPageNumber_);
	/*		cout << "No of columns is: "<< schema.columnNames.size() << endl;
			for(int i=0;i<schema.columnNames.size();i++){
				cout << schema.columnNames[i].c_str() << endl;
				cout << schema.fieldPosition[i] << endl;
				cout << schema.fieldTypes[i] << endl;
				cout << endl << endl;
			}*/
	DirectoryHeaderPage *dirHeaderPage_= new DirectoryHeaderPage(fd_,dpChainHeader_);
	dirPageNumber_=dirHeaderPage_->getNextPageNumber();
	cout << "2" <<endl;
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

					//cout << "in j= " << j<<endl;
					recordString=new char[DEFAULT_PAGE_SIZE];
					dataPage->getRecord(j,recordString,&recordLength);
					//buffManager_->hexDump(recordString);
					if(recordLength>0){
						//cout << "don't come here" << endl;
						recordVector=record->getvectorFromRecord(recordString,noOfColumns_);

						stringstream recordStream;
						int pos;
						Record recordWhere(schema,recordString,recordLength);

						for(unsigned c=0;c<columnList.size();c++){
							pos= schema.getColumnNum(columnList[c].c_str());
							recordStream<<recordVector[pos].c_str();

						}
						//cout << recordStream.str() <<endl;
						ridForIndex={dataPageNumber,j};
						bplusTree->insertIntoBPlusTree(recordStream.str().c_str(),ridForIndex);
						//cout << "index root page :"<<indexHeader->getRootPageNumber();
						delete[] recordString;
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
	//buffManager_->commitCache();

	delete indexHeader;
	delete bplusTree;
	delete dirHeaderPage_;

	delete indexCatalog;


	//return recordsVector;
	return SUCCESS;

}

int DatabaseOperations::deleteIndex(char *indexName){
	DBMainHeaderPage *dbMainHeader_=new DBMainHeaderPage(fd_,0);
	int indexCatalogPageNumber=dbMainHeader_->getIndexCatalogHeaderPageNumber();

	IndexCatalog *indexCatalog=new IndexCatalog(fd_,indexCatalogPageNumber);
	int indexHeaderPagenumber=indexCatalog->getIndexHeaderPageNumberUsingIndexName(indexName);
	IndexHeader *indexHeaderPage=new IndexHeader(fd_,indexHeaderPagenumber);
	BPlusTree *bplusTree=new BPlusTree(fd_,indexHeaderPagenumber);
	bplusTree->deleteIndex(indexHeaderPagenumber);
	cout << "3"<<endl;
	indexCatalog->deleteIndexEntryForTable(indexName);
	cout << "4"<<endl;
	delete indexCatalog;
	delete bplusTree;
	delete dbMainHeader_;

	return SUCCESS;
}




int DatabaseOperations::listDatabases(){

	DIR *dir;
	char *dbName=new char[MAX_FILE_NAME_LENGTH];

	struct dirent *ent;
	cout << "List of Databases in the System:"<<endl;
	if ((dir = opendir ("/home/ravin/workspace/Tri-DBMS/DatabaseFiles")) != NULL) {
	  /* print all the files and directories within directory */
	int countdb=0;
	  while ((ent = readdir (dir)) != NULL) {
		  if(strlen(ent->d_name) >= strlen(".db"))
		      {
		          if(!strcmp(ent->d_name + strlen(ent->d_name) - strlen(".db"), ".db"))
		          {
		        	  memset(dbName,0,MAX_FILE_NAME_LENGTH);
		        	  strncpy(dbName,ent->d_name,strlen(ent->d_name)-2);
		        	  dbName[strlen(dbName)-1]='\0';
		        	  countdb++;
		        	  cout<< "Database"<<countdb<<" ||\t"<<dbName<<"\t||"<<endl;
		          }
		      }

	  }
	  closedir (dir);
	} else {
	  /* could not open directory */
	  perror ("");
	  return EXIT_FAILURE;
	}
	delete[] dbName;
	return SUCCESS;

}
int DatabaseOperations::listTables(){

	Schema schema;
	char *recordString;
	int recordLength;
	vector<string> recordVector;
	Record *record=new Record();
	DBMainHeaderPage *dbMainHeader_=new DBMainHeaderPage(fd_,0);
	int sysTablePageNumber=dbMainHeader_->getSysTablesHeaderPageNumber();
	delete dbMainHeader_;
	DataPage *sysTableCatalog=new DataPage(fd_,sysTablePageNumber);
	cout << endl<<endl;
	cout << "||\tTable Name\t||  Max Record Size  ||  No of Columns  ||  DBChain Header Page No\t" <<endl;
	for(int i=0;i<sysTableCatalog->getNoOfRecords();i++){
		recordString=new char[DEFAULT_PAGE_SIZE];
		sysTableCatalog->getRecord(i,recordString,&recordLength);
		//buffManager_->hexDump(recordString);
		if(recordLength>0){
			//cout << "don't come here" << endl;
			stringstream recordStream;
			recordVector=record->getvectorFromRecord(recordString,4);
			for(unsigned j=0;j<recordVector.size();j++){
					recordStream<<"||\t" <<recordVector[j].c_str()<<"\t\t";
			}

			cout << recordStream.str()<<endl;
			recordVector.clear();
		}
		delete[] recordString;

	}
	cout << endl<<endl;
	delete sysTableCatalog;

	delete record;
	return SUCCESS;
}







int DatabaseOperations::listIndex(){

	Schema schema;
	char *recordString;
	int recordLength;
	vector<string> recordVector;
	Record *record=new Record();
	//cout << "fd is:(1)" <<fd_ <<endl;
	//buffManager_->hexDump(fd_,0);
	DBMainHeaderPage *dbMainHeader_=new DBMainHeaderPage(fd_,0);
	int indexCatalogPageNumber=dbMainHeader_->getIndexCatalogHeaderPageNumber();
	delete dbMainHeader_;
	//cout << "fd is:(2)" <<fd_<<" indexCatalog :"<<indexCatalogPageNumber<<endl;
	DataPage *indexCatalog=new DataPage(fd_,indexCatalogPageNumber);
	cout << endl<<endl;
	cout << "||\tIndex Name\t||\tKey Type\t\t||\tSize\t||IndexHeaderPage||  RootPage  ||\tTable\t||\tIndex Attribute\t" <<endl;
	for(int i=0;i<indexCatalog->getNoOfRecords();i++){
		recordString=new char[DEFAULT_PAGE_SIZE];
		indexCatalog->getRecord(i,recordString,&recordLength);
		//buffManager_->hexDump(recordString);
		if(recordLength>0){
			//cout << "don't come here" << endl;
			stringstream recordStream;
			recordVector=record->getvectorFromRecord(recordString,7);
			IndexHeader *indexHeaderPage=new IndexHeader(fd_,CommonUtil::string_to_int(recordVector[3].c_str()));
			for(unsigned j=0;j<recordVector.size();j++){
				if(j==1){
					if(CommonUtil::string_to_int(recordVector[j].c_str())==1)
						recordStream << "||\tSIMPLE_ATTRIBUTE   \t";
					else
						recordStream << "||\tCOMPOSITE_ATTRIBUTE\t";
				}
				else if(j==3){

					recordStream<<"||\t" <<recordVector[j].c_str()<<"\t";
					recordStream<<"||\t"<<indexHeaderPage->getRootPageNumber()<<"\t";
				}
				else
					recordStream<<"||\t" <<recordVector[j].c_str()<<"\t";



			}

			cout << recordStream.str()<<endl;
			recordVector.clear();
		}
		delete[] recordString;

	}
	cout << endl<<endl;
	delete indexCatalog;

	delete record;
	return SUCCESS;
}


