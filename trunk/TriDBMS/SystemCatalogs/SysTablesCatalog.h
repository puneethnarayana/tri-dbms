/*
 * SysTablesCatalog.h
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#ifndef SYSTABLESCATALOG_H_
#define SYSTABLESCATALOG_H_
#include "../Global/globalStructures.h"

class SysTablesCatalog {
public:
	SysTablesCatalog();
	virtual ~SysTablesCatalog();

private:

	typedef struct{
		GenPageHeaderStruct genPageHeader_;
		char* tableName_;
		int recordSize_;
		int noOfColumns_;
		int* dpChainHeaderAddress_;
	}SysTableStruct;

	SysTableStruct sysTableEntry_;
};

#endif /* SYSTABLESCATALOG_H_ */
