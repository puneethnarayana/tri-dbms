/*
 * Record.cpp
 *
 *  Created on: Nov 18, 2013
 *      Author: ravin
 */

#include "Record.h"
#include <vector>
#include <iostream>
#include <istream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sstream>
#include <cstring>
#include <iomanip>
#include "../Global/globalDefines.h"
#include "CommonUtil.h"
#include "../BufferManagement/BufferManager.h"
using namespace std;
Record::Record() {
	// TODO Auto-generated constructor stub
}

Record::~Record() {
	// TODO Auto-generated destructor stub
}


Record::Record(Schema& schema, char *record, unsigned recordLen) {
	fromConstructor_1 = false;
	schema_ = schema;
	record_ = record;
	length_ = recordLen;
}

void Record::getRecordString(vector<string> values,char *record,int *recLen){
	vector<string> values_=values;
	int offset=sizeof(int)*values_.size();

	char *record_;
	//char *record_=new char[DEFAULT_PAGE_SIZE];
	for(unsigned i=0;i<values_.size();i++){
		record_=(char *)values_[i].c_str();
		memcpy(&record[offset],record_,strlen(record_)+1);
		memcpy(&record[i*sizeof(int)],&offset,sizeof(int));
		offset=offset+strlen(record_)+1;

	}

	values_.clear();
	*recLen=offset;
}



vector<string> Record::getvectorFromRecord(char *record,int noOfColumns){
	vector<string> values_;
	int i,offset;
	for(i=0;i<noOfColumns;i++){
		memcpy(&offset,&record[i*sizeof(int)],sizeof(int));
		values_.push_back(&record[offset]);
	}

	return values_;
}






unsigned Record::getLength() {
	return length_;
}

void Record::getField(int fieldNum, void *fieldData) {
	int cur_field_offset;
	int cur_next_field_offset;
	int cur_field_length;
	//cout << "schema no of cols:"<<schema_.numOfColumns << "field num :" <<fieldNum<< endl;

//	BufferManager *bufMan=BufferManager::getInstance();
//	bufMan->hexDump(record_);
	memcpy(&cur_field_offset, &record_[fieldNum * sizeof(int)], sizeof(int));
	if(fieldNum<schema_.numOfColumns-1){
		//cout << "field offset :"<<cur_field_offset<<" schema no of cols:"<<schema_.numOfColumns << endl;
		memcpy(&cur_next_field_offset, &record_[(fieldNum +1)* sizeof(int)], sizeof(int));
		cur_field_length=cur_next_field_offset-cur_field_offset;
	}
	else{

		cur_field_length=length_-cur_field_offset;
		//cout << "don't come here " << cur_field_length << endl;
	}
	if (cur_field_offset >= 0 && cur_field_offset <= 8192) {//temp hack to fix a bug
		memcpy(fieldData, &record_[cur_field_offset], cur_field_length);
	}
}

std::string Record::getFieldInStringFormat(std::string columnName) {
	std::ostringstream mystream;
	int columnNum = schema_.getColumnNum(columnName);
	int colType = schema_.fieldTypes.at(columnNum);
	switch (colType) {
	case TYPE_INT: {
		int recordData;
		getField(columnNum, &recordData);
		mystream << recordData;
		break;
	}
	case TYPE_VARCHAR: {
		char recordData[schema_.fieldLengths.at(columnNum)];
		getField(columnNum, recordData);
		mystream << recordData;
		break;
	}
	default:
		mystream << "COULDNT GET";
		break;
	}
	return mystream.str();
}

bool Record::fieldMatch(int fieldNum, const void *fieldData) {
	if (schema_.fieldTypes.at(fieldNum) == TYPE_INT) {
		int recordData;
		getField(fieldNum, &recordData);
		int inputData = *((int*) fieldData);
		if (inputData == recordData) {
			return true;
		} else {
			return false;
		}
	} else if (schema_.fieldTypes.at(fieldNum) == TYPE_VARCHAR) {
		char recordData[schema_.fieldLengths.at(fieldNum)];
		getField(fieldNum, recordData);
		if (strcmp((char*) fieldData, recordData) == 0) {
			return true;
		} else {
			return false;
		}
	}
	return false;
}

bool Record::fieldMatch(std::string columnName, const void *fieldData) {
	int columnNum = schema_.getColumnNum(columnName);
	return fieldMatch(columnNum, fieldData);
}

bool Record::fieldMatchByConversion(std::string columnName, std::string value) {
	int fieldNum = schema_.getColumnNum(columnName);
	if (schema_.fieldTypes.at(fieldNum) == TYPE_INT) {
		//cout << "in record - 1" << endl;
		//int recordData;
		char *recordData=new char[DEFAULT_PAGE_SIZE];
		getField(fieldNum, recordData);
		//int inputData = CommonUtil::string_to_int(value);
		string inputData=value;
		//cout << inputData << " " << recordData;
		//if (inputData == recordData) {
		if (strcmp(value.c_str(), recordData) == 0){
			delete[] recordData;
			return true;
		} else {
			delete[] recordData;
			return false;
		}
	} else if (schema_.fieldTypes.at(fieldNum) == TYPE_VARCHAR) {
		//cout << "in record - 2" << endl;
		//cout << schema_.fieldLengths.at(fieldNum) << endl;
		//char recordData[schema_.fieldLengths.at(fieldNum)];
		char *recordData=new char[DEFAULT_PAGE_SIZE];
		getField(fieldNum, recordData);
		//cout <<"fieldNum " <<fieldNum << " " << recordData << endl;
		if (strcmp(value.c_str(), recordData) == 0) {
			delete []recordData;
			return true;
		} else {
			delete []recordData;
			return false;
		}

	} else {
		char *recordData=new char[DEFAULT_PAGE_SIZE];
				getField(fieldNum, recordData);
				//cout <<"fieldNum " <<fieldNum << " " << recordData << endl;
				if (strcmp(value.c_str(), recordData) == 0) {
					delete []recordData;
					return true;
				} else {
					delete []recordData;
					return false;
				}
	}

	return false;
}

bool Record::lessThanByConversion(std::string columnName, std::string value) {
	int fieldNum = schema_.getColumnNum(columnName);
	if (schema_.fieldTypes.at(fieldNum) == TYPE_INT) {
		char *recordData=new char[DEFAULT_PAGE_SIZE];
		getField(fieldNum, recordData);
		if (strcmp(recordData, value.c_str()) < 0) {
			delete []recordData;
			return true;
		} else {
			delete []recordData;
			return false;
		}
	} else if (schema_.fieldTypes.at(fieldNum) == TYPE_VARCHAR) {
		char *recordData=new char[DEFAULT_PAGE_SIZE];
		getField(fieldNum, recordData);
		if (strcmp(recordData, value.c_str()) < 0) {
			delete []recordData;
			return true;
		} else {
			delete []recordData;
			return false;
		}
	}
	return false;
}

bool Record::lessThanOrEqualByConversion(std::string columnName,
		std::string value) {
	int fieldNum = schema_.getColumnNum(columnName);
	if (schema_.fieldTypes.at(fieldNum) == TYPE_INT) {
		char *recordData=new char[DEFAULT_PAGE_SIZE];
				getField(fieldNum, recordData);
				if (strcmp(recordData, value.c_str()) <= 0) {
					delete []recordData;
					return true;
				} else {
					delete []recordData;
					return false;
				}
	} else if (schema_.fieldTypes.at(fieldNum) == TYPE_VARCHAR) {
		char *recordData=new char[DEFAULT_PAGE_SIZE];
		getField(fieldNum, recordData);
		if (strcmp(recordData, value.c_str()) <= 0) {
			delete []recordData;
			return true;
		} else {
			delete []recordData;
			return false;
		}

	}
	return false;
}

bool Record::greaterThanByConversion(std::string columnName, std::string value) {
	int fieldNum = schema_.getColumnNum(columnName);
	if (schema_.fieldTypes.at(fieldNum) == TYPE_INT) {
		char *recordData=new char[DEFAULT_PAGE_SIZE];
		getField(fieldNum, recordData);
				if (strcmp(recordData, value.c_str()) > 0) {
					delete []recordData;
					return true;
				} else {
					delete []recordData;
					return false;
				}
	} else if (schema_.fieldTypes.at(fieldNum) == TYPE_VARCHAR) {
		char *recordData=new char[DEFAULT_PAGE_SIZE];
		getField(fieldNum, recordData);
		if (strcmp(recordData, value.c_str()) > 0) {
			delete []recordData;
			return true;
		} else {
			delete []recordData;
			return false;
		}
	}
	return false;
}

bool Record::greaterThanOrEqualByConversion(std::string columnName,
		std::string value) {
	int fieldNum = schema_.getColumnNum(columnName);
	if (schema_.fieldTypes.at(fieldNum) == TYPE_INT) {
		char *recordData=new char[DEFAULT_PAGE_SIZE];
		getField(fieldNum, recordData);
				if (strcmp(recordData, value.c_str()) >= 0) {
					delete []recordData;
					return true;
				} else {
					delete []recordData;
					return false;
				}
	} else if (schema_.fieldTypes.at(fieldNum) == TYPE_VARCHAR) {
		char *recordData=new char[DEFAULT_PAGE_SIZE];
		getField(fieldNum, recordData);
		if (strcmp(recordData, value.c_str()) >= 0) {
			delete []recordData;
			return true;
		} else {
			delete []recordData;
			return false;
		}
	}
	return false;
}

void Record::setField(int fieldNum, const void *fieldData) {
	int cur_field_offset;
	memcpy(&cur_field_offset, &record_[fieldNum * sizeof(int)], sizeof(int));
	memcpy(&record_[cur_field_offset], fieldData, schema_.fieldLengths.at(
			fieldNum));
}

void Record::setFieldByConversion(std::string columnName, std::string value) {
	int fieldNum = schema_.getColumnNum(columnName);
	if (schema_.fieldTypes.at(fieldNum) == TYPE_INT) {
		int recordData = CommonUtil::string_to_int(value);
		setField(fieldNum, &recordData);//can act as setting also
	} else if (schema_.fieldTypes.at(fieldNum) == TYPE_VARCHAR) {
		//char recordData[schema_.fieldLengths.at(fieldNum)];
		const char *recordData = value.c_str();
		setField(fieldNum, recordData);
	}
}

std::string Record::toString() {

	std::ostringstream mystream;
	mystream << std::uppercase;
	mystream << std::setfill(' ') << std::setw(20);
	for (int i = 0; i < schema_.numOfColumns; i++) {
		int colType = schema_.fieldTypes.at(i);
		switch (colType) {
		case TYPE_INT: {
			int recordData;
			getField(i, &recordData);
			mystream << std::uppercase;
			mystream << std::setfill(' ') << std::setw(20);
			mystream << recordData;
			break;
		}
		case TYPE_VARCHAR: {
			char recordData[schema_.fieldLengths.at(i)];
			getField(i, recordData);
			mystream << std::uppercase;
			mystream << std::setfill(' ') << std::setw(20);
			mystream << recordData;
			break;
		}
		default:
			mystream << "TYPE NOT MATCHED";
			break;
		}
	}
	return mystream.str();
}

void Record::getKeyData(std::vector<std::string>& columnList, char*& keyData) {
	int offset = 0;
	for (int i = 0; i < columnList.size(); i++) {
		int fieldNum = schema_.getColumnNum(columnList[i]);
		if (schema_.fieldTypes.at(fieldNum) == TYPE_INT) {
			int recordData;
			getField(fieldNum, &recordData);
			memcpy(&keyData[offset], &recordData,
					schema_.fieldLengths[fieldNum]);
			offset = offset + schema_.fieldLengths[fieldNum];
		} else if (schema_.fieldTypes.at(fieldNum) == TYPE_VARCHAR) {
			char *recordData=new char[DEFAULT_PAGE_SIZE];
			getField(fieldNum, recordData);
			memcpy(&keyData[offset], &recordData,
					schema_.fieldLengths[fieldNum]);
			offset = offset + schema_.fieldLengths[fieldNum];
		}
	}
}
