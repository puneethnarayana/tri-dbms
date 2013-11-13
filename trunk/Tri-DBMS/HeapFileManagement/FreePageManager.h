/*
 * FreePageManager.h
 *
 *  Created on: Nov 10, 2013
 *      Author: ravin
 */

#ifndef FREEPAGEMANAGER_H_
#define FREEPAGEMANAGER_H_

class FreePageManager {
public:
	FreePageManager(int totalNoOfPages);
	virtual ~FreePageManager();
	int getFreePage();
private:

	typedef struct{
		bool isFree_;
	}freePageStruct;

	freePageStruct *freePageManager;
};

#endif /* FREEPAGEMANAGER_H_ */
