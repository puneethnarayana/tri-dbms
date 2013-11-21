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
	int createDBMainHeaderStruct(char *databaseName,int noOfPages,int pageSize);

	int getPageNumber();
	int getPageType();
	int getNextPageNumber();
	int getNoOfPagesUsed();
	int getNoOfTables();
	int getSysTablesHeaderPageNumber();
	int getSysColumnHeaderPageNumber();
	int getIndexCatalogHeaderPageNumber();
	int getFreeStructurePageNumber();

	void setPageNumber(int pageNumber);
	void setPageType(int pageType);
	void setNextPageNumber(int nextPageNumber);
	void setNoOfPagesUsed(int noOfPagesUsed);
	void setNoOfTables(int noOfTables);
	void setSysTablesHeaderPageNumber(int sysTableHeaderPageNumber);
	void setSysColumnHeaderPageNumber(int sysColumnsHeaderPageNumber);
	void setIndexCatalogHeaderPageNumber(int indexCatalogHeaderPageNumber);
	void setFreeStructurePageNumber(int freeStructurePageNumber);

private:
	typedef struct{
		GenPageHeaderStruct genPageHeader_;
		char dbName_[MAX_FILE_NAME_LENGTH];
		int pageSize_;
		int noOfTables_;
		int noOfPages_;
		int noOfPagesUsed_;
		int freeStructurePageNumber_;
		int sysTablesHeaderPageNumber_;
		int sysColumnsHeaderPageNumber_;
		int indexCatalogHeaderPageNumber_;
	}DBMainHeaderStruct;
	DBMainHeaderStruct dbMainHeader_;
	BufferManager *buffManager_;
	int fd_;
	int pageNumber_;
	char *pageData_;
	bool isDBMainHeaderChanged_;
};

#endif /* DBMAINHEADERPAGE_H_ */
