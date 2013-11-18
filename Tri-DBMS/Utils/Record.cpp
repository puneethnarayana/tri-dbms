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
#include <cstring>
#include "../Global/globalDefines.h"
using namespace std;
Record::Record() {
	// TODO Auto-generated constructor stub
	//record_=new char[DEFAULT_PAGE_SIZE];
}

Record::~Record() {
	// TODO Auto-generated destructor stub
}

void Record::getRecordString(vector<string> values,char *record_,int *recLen){
	vector<string> values_=values;
	int offset=sizeof(int)*values_.size();
	const char *val=new char[MAX_FILE_NAME_LENGTH];
	//record_=new char[DEFAULT_PAGE_SIZE];
	for(unsigned i=0;i<values_.size();i++){
		val=values_[i].c_str();
		memcpy(&record_[offset],val,strlen(val)+1);
		memcpy(&record_[i*sizeof(int)],&offset,sizeof(int));
		offset=offset+strlen(val)+1;
	}
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
