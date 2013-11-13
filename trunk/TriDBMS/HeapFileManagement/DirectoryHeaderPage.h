/*
 * DirectoryHeaderPage.h
 *
 *  Created on: Nov 10, 2013
 *      Author: ravin
 */

#ifndef DIRECTORYHEADERPAGE_H_
#define DIRECTORYHEADERPAGE_H_
#include "../Global/globalStructures.h"
class DirectoryHeaderPage {
public:
	DirectoryHeaderPage(int fd,int pageNumber);
	virtual ~DirectoryHeaderPage();

	int getPageNumber();
	int getPageType();
	int getNextPageNumber();
	int getNoOfRecordsInTable();
	int getNoOfDirectoryPages();
	int getMaxDirectoryEntriesPerDP();

	void setPageNumber(int pageNumber);
	void setPageType(int pageType);
	void setNextPageNumber(int nextPageNumber);
	void setNoOfRecordsInTable(int noOfRecordsInTable);
	void setNoOfDirectoryPages(int noOfDirectoryPages);
	void setMaxDirectoryEntriesPerDP(int maxDirectoryEntriesPerDP);



private:
	typedef struct{
		GenPageHeaderStruct genPageHeader_;
		int noOfRecordsInTable;
		int noOfDirectoryPages;
		int maxDirectoryEntriesPerDP;
	}DirectoryHeaderPageHeaderStruct;
	DirectoryHeaderPageHeaderStruct directoryHeaderPageHeader_;
	BufferManager *buffManager_;
	char* pageData_;
	bool isDirectoryHeaderChanged_;
	int fd_;
	int pageNumber_;
};

#endif /* DIRECTORYHEADERPAGE_H_ */
