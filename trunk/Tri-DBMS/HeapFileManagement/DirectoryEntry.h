/*
 * DirectoryEntry.h
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#ifndef DIRECTORYENTRY_H_
#define DIRECTORYENTRY_H_
#include "../BufferManagement/BufferManager.h"

class DirectoryEntry {
public:
	DirectoryEntry(int fd, int pageNumber);
	DirectoryEntry();
	virtual ~DirectoryEntry();

	int getPageNumber();
	int getFreeSpace();

	void setPageNumber(int pageNumber);
	void setFreeSpace(int freeSpace);

	static int getDirectoryEntrySize();
	int createDirectoryEntry(int pageNumber, int freeSpace);

	typedef struct{
		int pageNumber_;
		int freeSpace_;
	}DirectoryEntryStruct;
	DirectoryEntryStruct directoryEntry_;

private:
	BufferManager *buffManager_;
	int fd_;
	int pageNumber_;
	char *pageData_;
	bool isDirectoryEntryChanged_;
};

#endif /* DIRECTORYENTRY_H_ */
