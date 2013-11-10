/*
 * DBMainHeaderPage.h
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#ifndef DBMAINHEADERPAGE_H_
#define DBMAINHEADERPAGE_H_

#include "../Global/globalStructures.h"

class DBMainHeaderPage {
public:
	DBMainHeaderPage();
	virtual ~DBMainHeaderPage();

private:
	typedef struct{
		GenPageHeaderStruct genPageHeader_;
		int dbName_;
		int pageSize_;
		int noOfTables_;
		int noOfPages_;
		int pageType_;
		int sysTablesHeaderPageNumber_;
		int sysColumnsHeaderPageNumber_;
		int indexCatalogHeaderPageNumber_;
		int freeStructurePageNumber_;
	}DBMainHeaderStruct;
	DBMainHeaderStruct dbMainHeader_;
};

#endif /* DBMAINHEADERPAGE_H_ */
