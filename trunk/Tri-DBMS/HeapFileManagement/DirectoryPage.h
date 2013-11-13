/*
 * DirectoryPage.h
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#ifndef DIRECTORYPAGE_H_
#define DIRECTORYPAGE_H_

#include "../Global/globalStructures.h"
#include "../BufferManagement/BufferManager.h"

class DirectoryPage {
public:
	DirectoryPage(int fd, int pageNumber);
	virtual ~DirectoryPage();

	int getNoOfDirectoryEntries();
	int getMaxFreeSpace();
	int getPageNumber();
	int getPageType();
	int getNextPageNumber();
	static int getDirectoryPageSize();
	void setNoOfDirectoryEntries(int noOfDirectoryEntries);
	void setMaxFreeSpace(int maxFreeSpace);
	void setPageNumber(int pageNumber);
	void setPageType(int pageType);
	void setNextPageNumber(int nextPageNumber);

	int createDirectoryPage(int pageNumber, char *pageData);

private:
	typedef struct{
		GenPageHeaderStruct genPageHeader_;
		int noOfDirectoryEntries;
		int maxFreeSpace;
	}DirectoryPageHeaderStruct;
	DirectoryPageHeaderStruct directoryPageHeader_;
	BufferManager *buffManager_;
	int fd_;
	int pageNumber_;
	char *pageData_;
	bool isDirectoryPageChanged_;
};

#endif /* DIRECTORYPAGE_H_ */
