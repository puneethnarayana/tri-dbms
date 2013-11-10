/*
 * DirectoryPage.h
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#ifndef DIRECTORYPAGE_H_
#define DIRECTORYPAGE_H_

class DirectoryPage {
public:
	DirectoryPage();
	virtual ~DirectoryPage();
private:
	typedef struct{
		GenPageHeaderStruct genPageHeader_;
		int noOfDirectoryEntries;
		int maxFreeSpace;
	}DirectoryPageHeaderStruct;
	DirectoryPageHeaderStruct directoryPageHeader_;
};

#endif /* DIRECTORYPAGE_H_ */
