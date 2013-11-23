/*
 * SysColumnsCatalog.cpp
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#include "SysColumnsCatalog.h"
#include "../BufferManagement/BufferManager.h"
#include "../Global/globalStructures.h"
#include "../Global/globalDefines.h"
#include "../HeapFileManagement/DataPage.h"
#include "../Utils/Record.h"
#include "../Utils/CommonUtil.h"
#include "../HeapFileManagement/Schema.h"
#include <vector>
#include <cstdlib>
SysColumnsCatalog::SysColumnsCatalog(int fd, int pageNumber) {
	// TODO Auto-generated constructor stub
	fd_=fd;
	pageNumber_=pageNumber;
	buffManager_=BufferManager::getInstance();
	pageData_=new char[DEFAULT_PAGE_SIZE];
	memset(pageData_,0,sizeof(DEFAULT_PAGE_SIZE));
	buffManager_->readPage(fd,pageNumber,pageData_);
//	maxSysColumnEntriesPerPage_=
//			(DEFAULT_PAGE_SIZE-sizeof(GenPageHeaderStruct)-sizeof(int))/sizeof(sysColumnPageStruct);
//	memset(sysColumnPage_.sysColumnEntry_,0,maxSysColumnEntriesPerPage_);
//	memcpy(&sysColumnPage_,pageData_,sizeof(sysColumnPageStruct));
	isSysColumnChanged_=false;
}

SysColumnsCatalog::~SysColumnsCatalog() {
	// TODO Auto-generated destructor stub
//	if(isSysColumnChanged_ ==true){
//			buffManager_=BufferManager::getInstance();
//			buffManager_->writePage(fd_,pageNumber_,pageData_);
//		}
		delete[] pageData_;
}

int SysColumnsCatalog::createSysColumnsPage(int pageNumber){
	DataPage *sysColumnsPage=new DataPage(fd_,pageNumber_);
	sysColumnsPage->createDataPageHeaderStruct(pageNumber_);
	sysColumnsPage->setPageType(SYS_COLUMNS_PAGE);
	delete sysColumnsPage;
	return SUCCESS;
}

int SysColumnsCatalog::insertSysColumnEntry(char *columnName, char *tableName, int columnPosition, int columnType){

// Code needs to be written here!!!
	vector<string> values;
	int sysColumnRecLength_=0;
	char *recordString=new char[DEFAULT_PAGE_SIZE];
	Record *record=new Record();
	values.push_back(columnName);
	values.push_back(tableName);
	values.push_back(CommonUtil::int_to_string(columnPosition));
	values.push_back(CommonUtil::int_to_string(columnType));

	record->getRecordString(values,recordString,&sysColumnRecLength_);
	DataPage *sysColumnPage=new DataPage(fd_,pageNumber_);

	sysColumnPage->insertRecord(recordString,sysColumnRecLength_);
	isSysColumnChanged_=true;

	delete[] recordString;
	delete sysColumnPage;
	delete record;
	values.clear();
	return SUCCESS;
}

int SysColumnsCatalog::getTableSchema(char *tableName,Schema& schema){

	char *recordString=new char[DEFAULT_PAGE_SIZE];
	int recordLen=0;
	Record *record=new Record();
	vector<string> recordVector;
	DataPage *sysColumnPage=new DataPage(fd_,pageNumber_);
	//cout <<sysColumnPage->getNoOfRecords();
	for(int i=0;i< sysColumnPage->getNoOfRecords();i++){
		recordString=new char[DEFAULT_PAGE_SIZE];
		sysColumnPage->getRecord(i,recordString,&recordLen);
//		buffManager_->hexDump(recordString);
//		cout << "record length :" << recordLen << endl;
		recordVector=record->getvectorFromRecord(recordString,4);
		//cout << "print me" <<endl;
		//cout << recordVector[1].c_str() << " " << tableName << endl;
		if(strcmp(recordVector[1].c_str(),tableName)==0){
			schema.columnNames.push_back(recordVector[0].c_str());
			schema.fieldPosition.push_back(CommonUtil::string_to_int(recordVector[2].c_str()));
			schema.fieldTypes.push_back(CommonUtil::string_to_int(recordVector[3].c_str()));
			//schema.fieldLengths.push_back();
			delete[] recordString;
			delete record;
			delete sysColumnPage;
			recordVector.clear();
			return SUCCESS;
		}
	}
	delete[] recordString;
	delete record;
	delete sysColumnPage;
	recordVector.clear();
	return -1;
}




