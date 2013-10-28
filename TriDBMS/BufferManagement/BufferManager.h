/*
 * BufferManager.h
 *
 *  Created on: Oct 19, 2013
 *      Author: ravin
 */

#ifndef BUFFERMANAGER_H_
#define BUFFERMANAGER_H_

#include "string.h"
#include "Frame.h"
#include "LRUPageReplacement.h"
#include "../Global/globalDefines.h"
#include "../Global/globalStructures.h"
#include "../Global/globalVariables.h"
class LRUPageReplacement;
class BufferManager {
public:
	Frame **BufferPool_;
	virtual ~BufferManager();

	static BufferManager* getInstance();
	void replaceFrameWithAnother(int frameNumber,int pageNumber);
	void replaceFrameWithAnother(int frameNumber,int pageNumber, char *newPageContent);
	void flushAllPagesToDisk();
	void flushPageToDisk(int pageNumber);
	int getFrameNumber(int pageNumber);
	float getHitRate();

	LRUPageReplacement *LRUReplacement;
	int pageSize_;
	int bufferSizeInMB_;
	int numberOfFrames_;
private:
	BufferManager();


	int totalNumberOfRequests_;
	int numberOfHits_;
	int numberOfDiskAccesses_;
	static BufferManager* BufferManagerInstance_;
	basicDiskOperations *diskManager_;
};

#endif /* BUFFERMANAGER_H_ */
