/*
 * Record.h
 *
 *  Created on: Nov 18, 2013
 *      Author: ravin
 */

#ifndef RECORD_H_
#define RECORD_H_
#include <vector>
#include <string>
#include "../HeapFileManagement/Schema.h"
using namespace std;
class Record {
public:
	Record();
	virtual ~Record();
	void getRecordString(vector<string> values,char *record,int *recLen);
	vector<string> getvectorFromRecord(char *record,int noOfColumns);

	unsigned getLength();
	void getField(int fieldNum,void *fieldData);
	void setField(int fieldNum,const void *fieldData);
	bool fieldMatch(int fieldNum,const void *fieldData);
	bool fieldMatch(std::string columnName,const void *fieldData);
	std::string getFieldInStringFormat(std::string columnName);
	bool fieldMatchByConversion(std::string columnName,std::string value);
	bool lessThanByConversion(std::string columnName,std::string value);
	bool lessThanOrEqualByConversion(std::string columnName,std::string value);
	bool greaterThanByConversion(std::string columnName,std::string value);
	bool greaterThanOrEqualByConversion(std::string columnName,std::string value);
	void setFieldByConversion(std::string columnName,std::string value);
	void getKeyData(std::vector<std::string>& columnList,char*& keyData);
	std::string toString();
private:
	Schema schema_;
	std::vector<std::string> values_;
	char *record_;
	unsigned length_;
			bool fromConstructor_1;

};

#endif /* RECORD_H_ */
