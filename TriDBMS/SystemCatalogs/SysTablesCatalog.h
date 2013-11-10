/*
 * SysTablesCatalog.h
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#ifndef SYSTABLESCATALOG_H_
#define SYSTABLESCATALOG_H_

class SysTablesCatalog {
public:
	SysTablesCatalog();
	virtual ~SysTablesCatalog();

private:
	GenPageHeaderStruct genPageHeader_;
	typedef struct{
		char* tableName_;
		int recordSize_;
		int noOfColumns_;
		int* dpChainHeaderAddress_;
	}SysTableStruct;

	SysTableStruct sysTableEntry_;
};

#endif /* SYSTABLESCATALOG_H_ */
