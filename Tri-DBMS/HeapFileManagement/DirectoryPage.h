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
#include "DirectoryEntry.h"

class DirectoryPage {
public:
	DirectoryPage(int fd, int pageNumber);
	virtual ~DirectoryPage();

	int getNoOfDirectoryEntries();
	int getMaxNoOfDirectoryEntries();
	int getMaxFreeSpace();
	int getHeaderOffset();
	int getPageNumber();
	int getPageType();
	int getNextPageNumber();
	static int getDirectoryPageSize();
	void setNoOfDirectoryEntries(int noOfDirectoryEntries);
	void setMaxNoOfDirectoryEntries(int maxNoOfDirectoryEntries);
	void setMaxFreeSpace(int maxFreeSpace);
	void setHeaderOffset(int headerOffset);
	void setPageNumber(int pageNumber);
	void setPageType(int pageType);
	void setNextPageNumber(int nextPageNumber);

	int createDirectoryPage(int pageNumber);
	int deleteDirectoryPage();
	int searchForSlotEntry(int sizeRequired);
	int addSlotEntry(int sizeRequired);
	DirectoryEntry::DirectoryEntryStruct insertSlotEntry(int sizeRequired);
	int updateSlotEntry(int slotNumber,int freeSpace);
	int deleteSlotEntry(int slotNumber);
	int getFreeSpace(int slotNumber);
	void updateMaxFreeSpace();
	DirectoryEntry::DirectoryEntryStruct getDirectorySlot(int slotEntryNumber);

private:
	typedef struct{
		GenPageHeaderStruct genPageHeader_;
		int noOfDirectoryEntries_;
		int maxNoOfDirectoryEntries_;
		int maxFreeSpace_;
		int headerOffset_;
	}DirectoryPageHeaderStruct;
	DirectoryPageHeaderStruct directoryPageHeader_;
	BufferManager *buffManager_;
	int fd_;
	int pageNumber_;
	char *pageData_;
	bool isDirectoryPageChanged_;
};

#endif /* DIRECTORYPAGE_H_ */
