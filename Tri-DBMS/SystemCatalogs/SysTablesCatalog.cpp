/*
 * SysTablesCatalog.cpp
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#include "SysTablesCatalog.h"
#include "../BufferManagement/BufferManager.h"
#include "../Global/globalStructures.h"
#include "../Global/globalDefines.h"
#include "../HeapFileManagement/DataPage.h"
#include "../Utils/CommonUtil.h"
#include "../Utils/Record.h"
#include <vector>
#include <string>
using namespace std;
SysTablesCatalog::SysTablesCatalog(int fd,int pageNumber) {
	// TODO Auto-generated constructor stub
	fd_=fd;
	pageNumber_=pageNumber;
	pageData_=new char[DEFAULT_PAGE_SIZE];
	buffManager_ = BufferManager::getInstance();
	memset(pageData_,0,DEFAULT_PAGE_SIZE);
	buffManager_->readPage(fd,pageNumber,pageData_);
//	maxSysTableEntriesPerPage_=(DEFAULT_PAGE_SIZE-sizeof(GenPageHeaderStruct)-sizeof(int))/sizeof(SysTableEntryStruct);
//	memset(sysTablePage_.sysTableEntries_,0,maxSysTableEntriesPerPage_);
//	memcpy(&sysTablePage_,pageData_,sizeof(sysTablePageStruct));
	isSysTableChanged_=false;

}
int SysTablesCatalog::createSysTablePage(int pageNumber){
	DataPage *sysTablePage=new DataPage(fd_,pageNumber_);
	sysTablePage->createDataPageHeaderStruct(pageNumber_);
	sysTablePage->setPageType(SYS_TABLES_PAGE);
	delete sysTablePage;
	return SUCCESS;
}
int SysTablesCatalog::insertSysTableEntry(char *tableName,int maxRecordSize,int noOfColumns,int dpChainHeader){

//	int sysTableEntrySize_= strlen(tableName)+sizeof(int)*3+1;
//	SysTableEntryStruct sysTableEntry_;
//	sysTableEntry_.recordSize_=maxRecordSize;
//	sysTableEntry_.noOfColumns_=noOfColumns;
//	sysTableEntry_.dpChainHeaderAddress_=dpChainHeader;
//	memcpy(sysTableEntry_.tableName_,tableName,strlen(tableName)+1);
//	memcpy(pageData_,&sysTableEntry_,sysTableEntrySize_);
//	DataPage *sysTablePage=new DataPage(fd_,pageNumber_);
//	sysTablePage->insertRecord(pageData_,sysTableEntrySize_);

	vector<string> values;
		int sysTableRecLength_=0;
		char *recordString=new char[DEFAULT_PAGE_SIZE];
		Record *record=new Record();
		values.push_back(tableName);
		values.push_back(CommonUtil::int_to_string(maxRecordSize));
		values.push_back(CommonUtil::int_to_string(noOfColumns));
		values.push_back(CommonUtil::int_to_string(dpChainHeader));
		record->getRecordString(values,recordString,&sysTableRecLength_);

		DataPage *sysTablePage=new DataPage(fd_,pageNumber_);
		sysTablePage->insertRecord(recordString,sysTableRecLength_);

		delete[] recordString;
		delete record;
		delete sysTablePage;

	return SUCCESS;
}

int SysTablesCatalog::deleteSysTableEntry(char *tableName){
	char *recordString=new char[DEFAULT_PAGE_SIZE];
	int recordLen=0;
	Record *record=new Record();
	vector<string> recordVector,nullVector;
	DataPage *sysTablePage=new DataPage(fd_,pageNumber_);
	//cout <<sysTablePage->getNoOfRecords();
	for(int i=0;i< sysTablePage->getNoOfRecords();i++){
		//recordString=new char[DEFAULT_PAGE_SIZE];
		sysTablePage->getRecord(i,recordString,&recordLen);
		if(recordLen==-1){
			continue;
		}
		recordVector=record->getvectorFromRecord(recordString,4);
		if(recordVector.size()>0){
			//cout << recordVector[1].c_str() << " " << tableName << endl;
			if(strcmp(recordVector[0].c_str(),tableName)==0){
				sysTablePage->freeSlotDirectoryEntry(i);
			}
			recordVector.clear();
		}

	}
	delete[] recordString;
	delete record;
	delete sysTablePage;
	return SUCCESS;
}

SysTablesCatalog::~SysTablesCatalog() {
	// TODO Auto-generated destructor stub

//	if(isSysTableChanged_==true){
//		buffManager_=BufferManager::getInstance();
//		buffManager_->writePage(fd_,pageNumber_,pageData_);
//	}
	delete[] pageData_;

}

vector<string> SysTablesCatalog::getSysTableRecordAsVector(char *tableName){
	char *recordString=new char[DEFAULT_PAGE_SIZE];
	int recordLen=0,flag=1;
	Record *record=new Record();
	vector<string> recordVector,nullVector;
	DataPage *sysTablePage=new DataPage(fd_,pageNumber_);
	//cout <<sysTablePage->getNoOfRecords();
	for(int i=0;i< sysTablePage->getNoOfRecords();i++){
		//recordString=new char[DEFAULT_PAGE_SIZE];
		flag=sysTablePage->getRecord(i,recordString,&recordLen);
		if(flag!=-1){
			if(recordLen==-1){
				continue;
			}
			recordVector=record->getvectorFromRecord(recordString,4);

			//cout << recordVector[1].c_str() << " " << tableName << endl;
			if(strcmp(recordVector[0].c_str(),tableName)==0){
				delete record;
				delete[] recordString;
				delete sysTablePage;
				return recordVector;
			}
			recordVector.clear();
		}
		flag=1;
	}
	delete[] recordString;
	delete record;
	delete sysTablePage;
	return nullVector;

}

int SysTablesCatalog::getNoOfColumns(char *tableName){
	//vector<string> recordVector=getSysTableRecordAsVector(tableName);
	//return 3;
	return CommonUtil::string_to_int(getSysTableRecordAsVector(tableName)[2].c_str());

}

int SysTablesCatalog::getDPChainHeaderPageNumber(char *tableName){
	//vector<string> recordVector=getSysTableRecordAsVector(tableName);
	//return 5;
	return CommonUtil::string_to_int(getSysTableRecordAsVector(tableName)[3].c_str());

}


int SysTablesCatalog::getMaxRecordSize(char *tableName){
	//vector<string> recordVector=getSysTableRecordAsVector(tableName);
	return CommonUtil::string_to_int(getSysTableRecordAsVector(tableName)[1].c_str());

}




