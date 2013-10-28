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
#include "../Global/globalDefines.h"
#include "../Global/globalStructures.h"
#include "../Global/globalVariables.h"
#include "../diskManagement/basicDiskOperations.h"
BufferManager::BufferManager() {
	// TODO Auto-generated constructor stub
	pageSize_=PAGE_SIZE;
	bufferSizeInMB_=100;
	numberOfFrames_=bufferSizeInMB_*1024*1024/pageSize_;
	totalNumberOfRequests_=0;
	numberOfHits_=0;
	numberOfDiskAccesses_=0;
	BufferPool_= new Frame *[numberOfFrames_];
	LRUReplacement = new LRUPageReplacement();
	diskManager_ = new basicDiskOperations();
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
void BufferManager::replaceFrameWithAnother(int frameNumber,int newPageNumber){
	char *newPageContent=new char[PAGE_SIZE];
	diskManager_->readDiskFile(newPageNumber,newPageContent); //read the page content into newPageContent using newPageNumber.
	replaceFrameWithAnother(frameNumber,newPageNumber,newPageContent);
}

void BufferManager::replaceFrameWithAnother(int frameNumber,int newPageNumber,char *newPageContent){

	/* Doubt: do we have to change priorities for other frames??
	 * unsigned long frameOldPriority = bufManager_->BufferPool_[frameNumber]->priority_;
	 *
	 * for(int i=0;i<bufManager_->numberOfFrames_;i++)
	 * 	{
	 * 		if(frameOldPriority>bufManager_->BufferPool_[i]->priority_){
	 * 		}
	 * 	}
	 */
	numberOfDiskAccesses_++; // page needs to be replaced.
	if (BufferPool_[frameNumber]->dirtyFlag_ == true) {

		/*write content in (frameNumber)th frame into (pageNumber)th page in DB and
		 * change current frame fields
		 * diskmanager.writeToDB(int pageNumber,char *pageContent);
		 */
		diskManager_->writeDiskFile(BufferPool_[frameNumber]->pageNumber_,BufferPool_[frameNumber]->pageData_);

	}
	else{
		/* No write operations are done on page to be replaced.
		 * So, we can directly replace without writing it into disk.
		 */
	}
	BufferPool_[frameNumber]->priority_ = LRUReplacement->getMaximumPriority()+ 1;
	BufferPool_[frameNumber]->pageNumber_ = newPageNumber;
	BufferPool_[frameNumber]->pageData_ = newPageContent;
	BufferPool_[frameNumber]->pinCount_ = 0;
	BufferPool_[frameNumber]->dirtyFlag_=false;

}
void BufferManager::flushAllPagesToDisk(){
	for(int i=0;i<numberOfFrames_;i++){
			flushPageToDisk(BufferPool_[i]->pageNumber_);
	}
}
void BufferManager::flushPageToDisk(int pageNumber){
	int frameNumber=getFrameNumber(pageNumber);
	if(BufferPool_[frameNumber]->dirtyFlag_==true){
		diskManager_->writeDiskFile(pageNumber,BufferPool_[frameNumber]->pageData_);
	}
}
int BufferManager::getFrameNumber(int pageNumber){
	for(int i=0;i<numberOfFrames_;i++){
		if(BufferPool_[i]->pageNumber_==pageNumber){
			return i;
		}
	}
	return -1;
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

