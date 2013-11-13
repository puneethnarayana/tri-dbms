/*
 * DBMainHeaderPage.h
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#ifndef DBMAINHEADERPAGE_H_
#define DBMAINHEADERPAGE_H_

#include "../Global/globalStructures.h"
#include "../BufferManagement/BufferManager.h"
class DBMainHeaderPage {
public:
	DBMainHeaderPage(int fd,int pageNumber);
	virtual ~DBMainHeaderPage();
	int createDBMainHeaderStruct(char *databaseName,int noOfPages,int pageSize,char *pageData);

	int getPageNumber();
	int getPageType();
	int getNextPageNumber();
	int getNoOfPagesUsed();
	int getSysTablesHeaderPageNumber();
	int getSysColumnHeaderPageNumber();
	int getIndexCatalogHeaderPageNumber();
	int getFreeStructurePageNumber();

	void setPageNumber(int pageNumber);
	void setPageType(int pageType);
	void setNextPageNumber(int nextPageNumber);
	void setNoOfPagesUsed(int noOfPagesUsed);
	void setSysTablesHeaderPageNumber(int sysTableHeaderPageNumber);
	void setSysColumnHeaderPageNumber(int sysColumnsHeaderPageNumber);
	void setIndexCatalogHeaderPageNumber(int indexCatalogHeaderPageNumber);
	void setFreeStructurePageNumber(int freeStructurePageNumber);

private:
	typedef struct{
		GenPageHeaderStruct genPageHeader_;
		int dbName_;
		int pageSize_;
		int noOfTables_;
		int noOfPages_;
		int noOfPagesUsed_;
		int sysTablesHeaderPageNumber_;
		int sysColumnsHeaderPageNumber_;
		int indexCatalogHeaderPageNumber_;
		int freeStructurePageNumber_;
	}DBMainHeaderStruct;
	DBMainHeaderStruct dbMainHeader_;
	BufferManager *buffManager_;
	int fd_;
	int pageNumber_;
	char *pageData_;
	bool isDBMainHeaderChanged_;
};

#endif /* DBMAINHEADERPAGE_H_ */
