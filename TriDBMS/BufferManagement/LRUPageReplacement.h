/*
 * LRUPageReplacement.h
 *
 *  Created on: Oct 19, 2013
 *      Author: ravin
 */

#ifndef LRUPAGEREPLACEMENT_H_
#define LRUPAGEREPLACEMENT_H_

#include "BufferManager.h"
#include "string.h"
#include "Frame.h"
class BufferManager;
class LRUPageReplacement {
public:
	LRUPageReplacement();
	virtual ~LRUPageReplacement();

	void initializePriorities();
	void increasePriority(int frameNumber);
	void decreasePriority(int frameNumber);
	void resetPriority(int frameNumber);
	int getFrameToBeReplaced();
	unsigned long getMaximumPriority();
	void replaceFrameWithAnother(unsigned long oldFrameNumber,int pageNumber, char *newPageContent);
private:
	BufferManager *bufManager_;
};

#endif /* LRUPAGEREPLACEMENT_H_ */
