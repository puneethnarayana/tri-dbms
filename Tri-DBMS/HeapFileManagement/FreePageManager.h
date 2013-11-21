/*
 * FreePageManager.h
 *
 *  Created on: Nov 10, 2013
 *      Author: ravin
 */

#ifndef FREEPAGEMANAGER_H_
#define FREEPAGEMANAGER_H_
#include "../BufferManagement/BufferManager.h"
class FreePageManager {
public:
	FreePageManager(int fd,int pageNumber);
	virtual ~FreePageManager();
	int createFreePageManagerPage(int pageNumber);
	int setPage(int pageNumber); // 0 means free, 1 means allocated.
	int freePage(int pageNumber);
	bool isPageFree(int pageNumber);
	int getFreePage();
private:
	//	typedef struct{
	//		bool isFree_;
	//	}freePageStruct;

	typedef struct{
		GenPageHeaderStruct genPageHeader_;
		int maxNoOfPages_;
		int noOfFreePages_;
		int headerOffset_;
	}freePageStruct;

	freePageStruct freePageManager_;
	BufferManager *buffManager_;
	int fd_;
	int pageNumber_;
	char *pageData_;
	bool isFreePageManagerChanged_;
};

#endif /* FREEPAGEMANAGER_H_ */
