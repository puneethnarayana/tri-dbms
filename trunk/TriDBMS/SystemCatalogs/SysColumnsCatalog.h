/*
 * SysColumnsCatalog.h
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#ifndef SYSCOLUMNSCATALOG_H_
#define SYSCOLUMNSCATALOG_H_
#include "../Global/globalStructures.h"

class SysColumnsCatalog {
public:
	SysColumnsCatalog();
	virtual ~SysColumnsCatalog();

private:

	typedef struct{
		GenPageHeaderStruct genPageHeader_;
		char* columnName_;
		char* tableName_;
		int columnPosition_;
		char* columnType_;

	}SysColumnStruct;
	SysColumnStruct sysColumnEntry_;
};

#endif /* SYSCOLUMNSCATALOG_H_ */
