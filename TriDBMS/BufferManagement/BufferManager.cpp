/*
 * BufferManager.cpp
 *
 *  Created on: Oct 19, 2013
 *      Author: ravin
 */

#include "BufferManager.h"
#include "string.h"
#include "Frame.h"
#include "LRUPageReplacement.h"

BufferManager::BufferManager() {
	// TODO Auto-generated constructor stub
	pageSize_=4096;
	bufferSizeInMB_=100;
	numberOfFrames_=bufferSizeInMB_*1024*1024/pageSize_;
	totalNumberOfRequests_=0;
	numberOfHits_=0;
	numberOfDiskAccesses_=0;
	BufferPool_=new Frame *[numberOfFrames_];
	LRUReplacement =new LRUPageReplacement();
}

BufferManager* BufferManager::BufferManagerInstance_= NULL;

BufferManager* BufferManager::getInstance() {
	if(BufferManager::BufferManagerInstance_==NULL){
		BufferManager::BufferManagerInstance_=new BufferManager();
	}
	return BufferManagerInstance_;
}

BufferManager::~BufferManager() {
	// TODO Auto-generated destructor stub
	delete[] BufferPool_;
}




/*getHitRate() returns the ratio of number of frame requests found in buffer
 * to the total number of requests.
 */
float BufferManager::getHitRate(){
	if(totalNumberOfRequests_!=0)
		return numberOfHits_/totalNumberOfRequests_;
	else
		return 0;
}

