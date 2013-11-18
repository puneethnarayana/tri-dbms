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
using namespace std;
class Record {
public:
	Record();
	virtual ~Record();
	char* getRecordString(vector<string> values,char *record,int *recLen);
private:
	//char *record_;
};

#endif /* RECORD_H_ */
