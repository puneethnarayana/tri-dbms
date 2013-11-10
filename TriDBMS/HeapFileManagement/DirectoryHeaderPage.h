/*
 * DirectoryHeaderPage.h
 *
 *  Created on: Nov 10, 2013
 *      Author: ravin
 */

#ifndef DIRECTORYHEADERPAGE_H_
#define DIRECTORYHEADERPAGE_H_

class DirectoryHeaderPage {
public:
	DirectoryHeaderPage();
	virtual ~DirectoryHeaderPage();
private:
	typedef struct{
		GenPageHeaderStruct genPageHeader_;
		int noOfRecordsInTable;
		int noOfDirectoryPages;
		int maxDirectoryEntriesPerDP;
	}DirectoryHeaderPageHeaderStruct;
	DirectoryHeaderPageHeaderStruct directoryHeaderPageHeader_;
};

#endif /* DIRECTORYHEADERPAGE_H_ */
