/*
 * LRUPageReplacement.cpp
 *
 *  Created on: Oct 19, 2013
 *      Author: ravin
 */

#include "LRUPageReplacement.h"
#include "BufferManager.h"
#include "string.h"
#include "Frame.h"

LRUPageReplacement::LRUPageReplacement() {
	// TODO Auto-generated constructor stub
	bufManager_=BufferManager::getInstance();

}

LRUPageReplacement::~LRUPageReplacement() {
	// TODO Auto-generated destructor stub
}

void LRUPageReplacement::initializePriorities(){
	for(int i=0;i<bufManager_->numberOfFrames_;i++)
	{
		bufManager_->BufferPool_[i]->priority_=0;
	}
}
void LRUPageReplacement::increasePriority(int frameNumber){
	bufManager_->BufferPool_[frameNumber]->priority_++;
}
void LRUPageReplacement::decreasePriority(int frameNumber){
	bufManager_->BufferPool_[frameNumber]->priority_--;
}
void LRUPageReplacement::resetPriority(int frameNumber){
	bufManager_->BufferPool_[frameNumber]->priority_=0;
}
unsigned long LRUPageReplacement::getMaximumPriority(){
	unsigned long maxPriority_=0;
	for (int i = 0; i < bufManager_->numberOfFrames_; i++) {
		if (maxPriority_ < bufManager_->BufferPool_[i]->priority_) {
			maxPriority_ = bufManager_->BufferPool_[i]->priority_;
		}
	}
	return maxPriority_;
}
int LRUPageReplacement::getFrameToBeReplaced(){
	int freeFrameIndex=-1;
	unsigned long minPriority;//initialize this to some number which is greater than all priorities.
	for(int i=0;i<bufManager_->numberOfFrames_;i++)
	{
		if(bufManager_->BufferPool_[i]->pinCount_==-1){
			freeFrameIndex=i;
			break;
		}
		else if(bufManager_->BufferPool_[i]->pinCount_==0){
			if(minPriority>bufManager_->BufferPool_[i]->priority_){
				minPriority=bufManager_->BufferPool_[i]->priority_;
				freeFrameIndex=i;
			}
		}
	}
	return freeFrameIndex;
}

void LRUPageReplacement::replaceFrameWithAnother(unsigned long frameNumber,int pageNumber,char *newPageContent){

	/* Doubt: do we have to change priorities for other frames??
	 * unsigned long frameOldPriority = bufManager_->BufferPool_[frameNumber]->priority_;
	 *
	 * for(int i=0;i<bufManager_->numberOfFrames_;i++)
	 * 	{
	 * 		if(frameOldPriority>bufManager_->BufferPool_[i]->priority_){
	 * 		}
	 * 	}
	 */

	if (bufManager_->BufferPool_[frameNumber]->dirtyFlag_ == false) {
		/* No write operations are done on page to be replaced.
		 * So, we can directly replace without writing it into disk.
		 */
		bufManager_->BufferPool_[frameNumber]->priority_ = getMaximumPriority()+ 1;
		bufManager_->BufferPool_[frameNumber]->pageNumber_ = pageNumber;
		bufManager_->BufferPool_[frameNumber]->pageData_ = newPageContent;
		bufManager_->BufferPool_[frameNumber]->pinCount_ = 0;
	}
	else{
		/*write content in (frameNumber)th frame into (pageNumber)th page in DB and
		 * change current frame fields
		 * diskmanager.writeToDB(int pageNumber,char *pageContent);
		 */
		bufManager_->BufferPool_[frameNumber]->priority_ = getMaximumPriority()+ 1;
		bufManager_->BufferPool_[frameNumber]->pageNumber_ = pageNumber;
		bufManager_->BufferPool_[frameNumber]->pageData_ = newPageContent;
		bufManager_->BufferPool_[frameNumber]->pinCount_ = 0;
		bufManager_->BufferPool_[frameNumber]->dirtyFlag_=false;
	}

}

