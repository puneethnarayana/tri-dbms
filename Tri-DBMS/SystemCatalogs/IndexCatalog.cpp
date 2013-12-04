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





int IndexCatalog::insertIndexEntry(char *indexName, char *tableName, char *indexAttribute, int indexType, int keySize,int indexHeaderPageNo,int useIndex){

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
	values.push_back(CommonUtil::int_to_string(useIndex));


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






int IndexCatalog::deleteIndexEntryForTable(char *indexName){
	char *recordString=new char[DEFAULT_PAGE_SIZE];
	int recordLen=0;
	cout << "in dlete entry index:"<<fd_<<pageNumber_<<endl;
	Record *record=new Record();
	//cout << "1"<<endl;
	vector<string> recordVector,nullVector;
	//cout << "2"<<endl;
	//cout << "in dlete entry index:"<<fd_<<" "<<pageNumber_<<endl;
	DataPage *indexCatalogPage=new DataPage(fd_,pageNumber_);
	//cout <<indexCatalogPage->getNoOfRecords();
	cout << " hey"<<endl;
	for(int i=0;i< indexCatalogPage->getNoOfRecords();i++){
		//recordString=new char[DEFAULT_PAGE_SIZE];
		indexCatalogPage->getRecord(i,recordString,&recordLen);
		if(recordLen==-1){
			continue;
		}
		recordVector=record->getvectorFromRecord(recordString,7);
		if(recordVector.size()>0){
			//cout << recordVector[0].c_str() << " " << indexName << endl;
			if(strcmp(recordVector[0].c_str(),indexName)==0){
				indexCatalogPage->freeSlotDirectoryEntry(i);
			}
			recordVector.clear();
		}

	}
	cout << "after delete in index catalog:"<<indexCatalogPage->getNoOfRecords()<<endl;
	delete[] recordString;
	delete record;
	delete indexCatalogPage;
	return SUCCESS;

}




vector<string> IndexCatalog::getIndexCatalogVectorFromIndexName(char *indexName){
	char *recordString=new char[DEFAULT_PAGE_SIZE];
	int recordLen=0,flag=1;
	Record *record=new Record();
	vector<string> recordVector,nullVector;
	DataPage *indexCatalogPage=new DataPage(fd_,pageNumber_);
	//cout <<sysTablePage->getNoOfRecords();
	for(int i=0;i< indexCatalogPage->getNoOfRecords();i++){
		//recordString=new char[DEFAULT_PAGE_SIZE];
		flag=indexCatalogPage->getRecord(i,recordString,&recordLen);
		if(flag!=-1){
			if(recordLen==-1){
				continue;
			}
			recordVector=record->getvectorFromRecord(recordString,7);

			//cout << recordVector[1].c_str() << " " << tableName << endl;
			if(strcmp(recordVector[0].c_str(),indexName)==0){
				delete record;
				delete[] recordString;
				delete indexCatalogPage;
				return recordVector;
			}
			recordVector.clear();
		}
		flag=1;
	}
	delete[] recordString;
	delete record;
	delete indexCatalogPage;
	return nullVector;

}




vector<string> IndexCatalog::getIndexCatalogVectorFromIndexAttr(char *indexAttr){
	char *recordString=new char[DEFAULT_PAGE_SIZE];
	int recordLen=0,flag=1;
	Record *record=new Record();
	vector<string> recordVector,nullVector;
	DataPage *indexCatalogPage=new DataPage(fd_,pageNumber_);
	//cout <<sysTablePage->getNoOfRecords();
	for(int i=0;i< indexCatalogPage->getNoOfRecords();i++){
		//recordString=new char[DEFAULT_PAGE_SIZE];
		flag=indexCatalogPage->getRecord(i,recordString,&recordLen);
		if(flag!=-1){
			recordVector=record->getvectorFromRecord(recordString,7);

			//cout << recordVector[1].c_str() << " " << tableName << endl;
			if(strcmp(recordVector[5].c_str(),indexAttr)==0){
				delete record;
				delete[] recordString;
				delete indexCatalogPage;
				return recordVector;
			}
			recordVector.clear();
		}
		flag=1;
	}
	delete[] recordString;
	delete record;
	delete indexCatalogPage;
	return nullVector;

}


int IndexCatalog::getIndexHeaderPageNumberUsingIndexName(char *indexName){
	//vector<string> recordVector=getSysTableRecordAsVector(tableName);
	//return 3;
	if(getIndexCatalogVectorFromIndexName(indexName).size()>0){
		return CommonUtil::string_to_int(getIndexCatalogVectorFromIndexName(indexName)[3].c_str());
	}
	return -1;

}



int IndexCatalog::getIndexHeaderPageNumberUsingAttr(char *indexAttribute){
	//vector<string> recordVector=getSysTableRecordAsVector(tableName);
	//return 3;
	if(getIndexCatalogVectorFromIndexAttr(indexAttribute).size()>0){
		return CommonUtil::string_to_int(getIndexCatalogVectorFromIndexAttr(indexAttribute)[3].c_str());
	}
	return -1;
}

int IndexCatalog::setUseIndexForGivenIndex(char *indexName,bool useIndex){
	char *recordString=new char[DEFAULT_PAGE_SIZE];
		int recordLen=0,flag=1;
		Record *record=new Record();
		vector<string> recordVector,nullVector;
		DataPage *indexCatalogPage=new DataPage(fd_,pageNumber_);
		//cout <<sysTablePage->getNoOfRecords();
		for(int i=0;i< indexCatalogPage->getNoOfRecords();i++){
			//recordString=new char[DEFAULT_PAGE_SIZE];
			flag=indexCatalogPage->getRecord(i,recordString,&recordLen);

			if(flag!=-1){
				if(recordLen==-1){
					continue;
				}
				recordVector=record->getvectorFromRecord(recordString,7);

				//cout << recordVector[1].c_str() << " " << tableName << endl;
				if(strcmp(recordVector[0].c_str(),indexName)==0){
					indexCatalogPage->freeSlotDirectoryEntry(i);
					recordVector[6]=CommonUtil::int_to_string(useIndex);
					record->getRecordString(recordVector,recordString,&recordLen);
					indexCatalogPage->insertRecord(recordString,recordLen);
				}
				recordVector.clear();
			}
			flag=1;
		}
		delete[] recordString;
		delete record;
		delete indexCatalogPage;
		return SUCCESS;
}


vector<string> IndexCatalog::getIndexNamesFromTableName(char *tableName){
	char *recordString=new char[DEFAULT_PAGE_SIZE];
	int recordLen=0,flag=1;
	Record *record=new Record();
	vector<string> recordVector,nullVector,indexNames;
	DataPage *indexCatalogPage=new DataPage(fd_,pageNumber_);
	//cout <<sysTablePage->getNoOfRecords();
	for(int i=0;i< indexCatalogPage->getNoOfRecords();i++){
		//recordString=new char[DEFAULT_PAGE_SIZE];
		flag=indexCatalogPage->getRecord(i,recordString,&recordLen);
		if(flag!=-1){
			if(recordLen==-1){
				continue;
			}
			recordVector=record->getvectorFromRecord(recordString,7);

			//cout << recordVector[1].c_str() << " " << tableName << endl;
			if(strcmp(recordVector[4].c_str(),tableName)==0){
				indexNames.push_back(recordVector[0].c_str());

			}
			recordVector.clear();
		}
		flag=1;
	}
	delete[] recordString;
	delete record;
	delete indexCatalogPage;
	return indexNames;
}
