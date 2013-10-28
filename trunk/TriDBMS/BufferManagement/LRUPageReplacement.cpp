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
#include "../Global/globalDefines.h"
#include "../Global/globalStructures.h"
#include "../Global/globalVariables.h"
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
	unsigned long minPriority=getMaximumPriority();//initialize this to some number which is greater than all priorities.
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



