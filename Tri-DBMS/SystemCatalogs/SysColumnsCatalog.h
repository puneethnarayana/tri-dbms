/*
 * SysColumnsCatalog.h
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#ifndef SYSCOLUMNSCATALOG_H_
#define SYSCOLUMNSCATALOG_H_
#include "../Global/globalStructures.h"
#include "../Global/globalDefines.h"
class SysColumnsCatalog {
public:
	SysColumnsCatalog();
	virtual ~SysColumnsCatalog();

private:

	GenPageHeaderStruct genPageHeader_;
	typedef struct{
		char* columnName_;
		char* tableName_;
		int columnPosition_;
		int columnType_;

	}SysColumnEntryStruct;
	SysColumnEntryStruct sysColumnEntry_;
};

#endif /* SYSCOLUMNSCATALOG_H_ */
