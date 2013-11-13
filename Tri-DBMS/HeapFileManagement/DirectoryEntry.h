/*
 * DirectoryEntry.h
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#ifndef DIRECTORYENTRY_H_
#define DIRECTORYENTRY_H_

class DirectoryEntry {
public:
	DirectoryEntry();
	virtual ~DirectoryEntry();
private:
	typedef struct{
		int pageNumber_;
		int freeSpace_;
	}DirectoryEntryStruct;
	DirectoryEntryStruct directoryEntry_;
};

#endif /* DIRECTORYENTRY_H_ */
