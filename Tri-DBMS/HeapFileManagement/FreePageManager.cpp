/*
 * FreePageManager.cpp
 *
 *  Created on: Nov 10, 2013
 *      Author: ravin
 */

#include "FreePageManager.h"

FreePageManager::FreePageManager(int totalNoOfPages) {
	// TODO Auto-generated constructor stub
	freePageManager=new freePageStruct[totalNoOfPages];
	int i;
	for(i=0;i<totalNoOfPages;i++){
		freePageManager[i].isFree_=true;
	}
}

FreePageManager::~FreePageManager() {
	// TODO Auto-generated destructor stub
	delete []freePageManager;
}

