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
#include "../BufferManagement/BufferManager.h"
#include "../HeapFileManagement/Schema.h"

class SysColumnsCatalog {
public:
	SysColumnsCatalog(int fd, int pageNumber);
	virtual ~SysColumnsCatalog();
	int createSysColumnsPage(int pageNumber);
	int insertSysColumnEntry(char *columnName, char *tableName, int columnPosition, int columnType, int columnSize);
	int getTableSchema(char *tableName,Schema& schema);
	int deleteSysColumnEntryForTable(char *tableName);
private:

//	typedef struct{
//			char* columnName_;
//			char* tableName_;
//			int columnPosition_;
//			int columnType_;
//
//		}SysColumnEntryStruct;


	char *pageData_;
	BufferManager *buffManager_;
	int fd_;
	int pageNumber_;
	bool isSysColumnChanged_;
	//int maxSysColumnEntriesPerPage_;
};

#endif /* SYSCOLUMNSCATALOG_H_ */
