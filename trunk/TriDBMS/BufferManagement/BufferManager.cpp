/*
 * BufferManager.cpp
 *
 *  Created on: Oct 19, 2013
 *      Author: ravin
 */

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <ctime>
#include <iomanip>

#include "BufferManager.h"
#include "string.h"
#include "Frame.h"
#include "LRUPageReplacement.h"
#include "../Global/globalDefines.h"
#include "../Global/globalStructures.h"
#include "../Global/globalVariables.h"
#include "../diskManagement/BasicDiskOperations.h"
using namespace std;
BufferManager::BufferManager() {
	// TODO Auto-generated constructor stub
	pageSize_=DEFAULT_PAGE_SIZE;
	bufferSizeInMB_=100;
	initCache_=false;
	numberOfFrames_=bufferSizeInMB_*1024*1024/pageSize_;
	LRUReplacement = new LRUPageReplacement();
	diskManager_ = new BasicDiskOperations();
	fd_=-1;
	openedFileName_=new char[MAX_FILE_NAME_LENGTH];
	initializeCache(numberOfFrames_);


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
int BufferManager::initializeCache(int noOfPages){

	numberOfFrames_=noOfPages;
	bufferSizeInMB_=numberOfFrames_*pageSize_/1024*1024;
	totalNumberOfRequests_=0;
	numberOfHits_=0;
	numberOfDiskAccesses_=0;
	BufferPool_= new Frame *[numberOfFrames_];
	for (int i = 0; i < numberOfFrames_; i++) {
			BufferPool_[i] = new Frame(pageSize_);
	}
	initCache_=true;
	return SUCCESS;
}
int BufferManager::createDatabase(char *fileName, int pageSize, int noOfPages){
	int fd=diskManager_->createDiskFile(fileName,pageSize,noOfPages);
	return fd;
}
int BufferManager::openDatabase(char *fileName){
	openedFileName_=fileName;
	fd_=diskManager_->openDiskFile(fileName);
	return fd_;
}
int BufferManager::readPage(int fd, int pageNumber, char*& pageContent){
	totalNumberOfRequests_++;
	int retVal=-1,frameNo=-1;
	//long int fd = -1;
	if (fd==-1||fd!=fd_)
		goto ret;
	//fd=BufferPool_[frameNumber]->fd_;
	//code to get file descriptor for given cd, from cache index.
	if(initCache_==false){
		retVal=diskManager_->readDiskFile(fd,pageNumber,pageSize_,pageContent);
		goto ret;
	}
	else{
		/*Check if the page is in the buffer.
		 * if not, get it into buffer, replace the frame if needed.
		 */
		frameNo=getFrameNumber(pageNumber);
		if(frameNo==-1){
			//cout << "in frame number == -1" << endl;
			//page is not present in the buffer; diskAccess.
			frameNo=pinAndGetPage(fd,pageNumber,pageContent);
			numberOfDiskAccesses_++;
			//cout << "page content after pin and get page(read page): "<< pageContent << endl;
			//cout << "frameNo after pin and get page(read page): "<< frameNo << endl;

		}
		else{
			//cout << "in frame number != -1" << endl;
			numberOfHits_++;

		}
		//cout << "+++++pageNumber is+++++++:"<<pageNumber<<endl;
		strcpy(pageContent,BufferPool_[frameNo]->pageData_);
		BufferPool_[frameNo]->pageNumber_=pageNumber;
		t = std::time(0);
		BufferPool_[frameNo]->priority_ = t;//LRUReplacement->getMaximumPriority()+ 1;//use time-stamp
		BufferPool_[frameNo]->pinCount_ = 0;
		//cout << "page content at end of read page(read page): "<< pageContent << endl;
	}
	ret: return retVal;
}
int BufferManager::writePage(int fd, int pageNumber, char *newPageContent){
	totalNumberOfRequests_++;
	int retVal=-1,frameNo=-1;
	char *pageContent=new char[DEFAULT_PAGE_SIZE];
	//long int fd = -1;
	if (fd==-1||fd!=fd_)
		goto ret;
	//fd=BufferPool_[frameNumber]->fd_;
	//code to get file descriptor for given cd, from cache index.
	if(initCache_==false){
		retVal=diskManager_->writeDiskFile(fd,pageNumber,pageSize_,newPageContent);
		goto ret;
	}
	else{
		/*Check if the page is in the buffer.
		 * if not, get it into buffer, replace the frame if needed.
		 */
		frameNo=getFrameNumber(pageNumber);
		if(frameNo==-1){
			//cout << "in frame number == -1" << endl;
			//page is not present in the buffer; diskAccess.
			frameNo=pinAndGetPage(fd,pageNumber,pageContent);
			numberOfDiskAccesses_++;
			//cout << "page content after pin and get page: "<< pageContent << endl;
			//cout << "frameNo after pin and get page: "<< frameNo << endl;

		}
		else{
			//cout << "in frame number != -1" << endl;
			numberOfHits_++;
		}
		//cout << "+++++pageNumber is+++++++:"<<pageNumber<<endl;
		strcpy(BufferPool_[frameNo]->pageData_,newPageContent);
		BufferPool_[frameNo]->pageNumber_=pageNumber;
		t = std::time(0);
		BufferPool_[frameNo]->priority_ = t;//LRUReplacement->getMaximumPriority()+ 1;//use time-stamp
		BufferPool_[frameNo]->pinCount_ = 0;
		BufferPool_[frameNo]->dirtyFlag_=true;

		retVal = SUCCESS;// change to status code which says success or buffer used.
	}
	ret: return retVal;
}

int BufferManager::pinAndGetPage(int fd,int pageNumber,char*& pageContent){
	int freeFrame=getFreeFrame();
	diskManager_->readDiskFile(fd,pageNumber,pageSize_,pageContent);
	//cout <<" ******************* *********" << pageContent << "********** *******************" << endl;
	if(freeFrame!=-1){
		//cout << "in free frame != -1" << endl;
		//cout << "free frame number is :" << freeFrame << endl;


		return freeFrame;
	}
	else{
		//cout << "in free frame == -1" << endl;
		int frameToBeReplaced=LRUReplacement->getFrameToBeReplaced();
		replaceFrameWithAnother(fd,frameToBeReplaced,pageNumber);
		return frameToBeReplaced;
	}

}


void BufferManager::replaceFrameWithAnother(int fd,int frameNumber,int newPageNumber){
	char *newPageContent=new char[DEFAULT_PAGE_SIZE];
	diskManager_->readDiskFile(fd,newPageNumber,pageSize_,newPageContent); //read the page content into newPageContent using newPageNumber.
	replaceFrameWithAnother(fd,frameNumber,newPageNumber,newPageContent);
}

void BufferManager::replaceFrameWithAnother(int fd,int frameNumber,int newPageNumber,char *newPageContent){

	//Use time-stamp as priority, and different types of pages as priority types.

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
		diskManager_->writeDiskFile(fd,BufferPool_[frameNumber]->pageNumber_,pageSize_,BufferPool_[frameNumber]->pageData_);

	}
	else{
		/* No write operations are done on page to be replaced.
		 * So, we can directly replace without writing it into disk.
		 */
	}
	t = std::time(0);
	BufferPool_[frameNumber]->priority_ = t; //LRUReplacement->getMaximumPriority()+ 1;// use time-stamp
	BufferPool_[frameNumber]->pageNumber_ = newPageNumber;
	strcpy(BufferPool_[frameNumber]->pageData_,newPageContent);
	BufferPool_[frameNumber]->pinCount_ = 0;
	BufferPool_[frameNumber]->dirtyFlag_=false;

}
int BufferManager::closeDatabase(int fd){
	if(fd!=fd_){
		cout << "DATABASE_NOT_OPEN" << endl;
		return -1;
	}
	commitCache();
	if(diskManager_->closeDiskFile(fd)==-1){
		return -1;
	}
	return SUCCESS;
}
int BufferManager::dropDatabase(){
	if(diskManager_->deleteDiskFile(openedFileName_)==-1){
		return -1;
	}
	return SUCCESS;
}
int BufferManager::commitCache(){
	flushAllPagesToDisk();
	return SUCCESS;
}
int BufferManager::resetCache(){
	flushAllPagesToDisk();
	delete BufferPool_;
	initializeCache(numberOfFrames_);

	return SUCCESS;
}

void BufferManager::flushAllPagesToDisk(){
	for(int i=0;i<numberOfFrames_;i++){
			flushPageToDisk(BufferPool_[i]->pageNumber_);
	}
}
void BufferManager::flushPageToDisk(int pageNumber){
	int frameNumber=getFrameNumber(pageNumber);

	if(BufferPool_[frameNumber]->dirtyFlag_==true){
		//cout << "in flush page to disk, page number: " << pageNumber << endl;
		diskManager_->writeDiskFile(fd_,pageNumber,pageSize_,BufferPool_[frameNumber]->pageData_);
		BufferPool_[frameNumber]->dirtyFlag_=false;
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
int BufferManager::getFreeFrame(){
	for(int i=0;i<numberOfFrames_;i++){
		if(BufferPool_[i]->pinCount_==-1){
			return i;
		}
	}
	return -1;
}

int BufferManager::displayBufferList(){
	cout << "\n=======================================================================================================" << endl;
	cout << "||Frame No.||   File Name   ||   Page No.   ||   Dirty Flag  ||    Priority Type  || Priority Value  ||" << endl;
	for(int i=0;i<numberOfFrames_;i++){
		if(BufferPool_[i]->pinCount_!=-1){
			cout << "||    " <<i <<"    ||";
			cout << "      "<<openedFileName_<< "   ||" ;
			cout <<"        " <<BufferPool_[i]->pageNumber_ <<"     ||";
			cout <<"         "<<BufferPool_[i]->dirtyFlag_ <<"     ||";
			cout <<"       "<<BufferPool_[i]->priorityType_ <<"   ||";
			cout <<"     "<<BufferPool_[i]->priority_ <<"    ||";
			cout << endl;
		}
	}
	cout << "\n=======================================================================================================" << endl;
	return SUCCESS;
}
int BufferManager::viewFrameBuffer(int frameNumber){
	if(frameNumber<0||frameNumber>=numberOfFrames_){
		cout << "\nInvalid Frame Number\n";
		return -1;
	}
	cout << "\n=========================== FRAME - " << frameNumber << " ===================================" << endl;
	cout << "File Name is: " << openedFileName_<< endl;
	cout << "page Number is: " << BufferPool_[frameNumber]->pageNumber_ << endl;
	cout << "dirty flag is: " << BufferPool_[frameNumber]->dirtyFlag_ << endl;
	cout << "priority type is: " << BufferPool_[frameNumber]->priorityType_ << endl;
	cout << "priority value is: " << BufferPool_[frameNumber]->priority_ << endl;
	cout << "page Content is:\n" << BufferPool_[frameNumber]->pageData_ << endl;
	cout << "\n=====================================================================================\n";
	return SUCCESS;
}

/*getHitRate() returns the ratio of number of frame requests found in buffer
 * to the total number of requests.
 */
float BufferManager::getHitRate(){
	cout <<"Total Requests			: "<<totalNumberOfRequests_ << endl;
	cout <<"Number of hits			: "<<numberOfHits_ <<endl;
	cout <<"Number of disk accesses	: "<<numberOfDiskAccesses_<<endl;
	if(totalNumberOfRequests_!=0)
		return (float)numberOfHits_/totalNumberOfRequests_;
	else
		return 0;
}

int BufferManager::hexDump(int fd,int pageNumber){
	cout <<"\n";
	cout <<
			"Address               Hexadecimal values                    Printable\n";
	cout <<
			"--------  -----------------------------------------------  -------------\n";
	cout << "\n";
	unsigned long address = 0;
	//char c;
	int ptr=0;
	char *pageContent=new char[DEFAULT_PAGE_SIZE];
	int err=diskManager_->readDiskFile(fd,pageNumber,DEFAULT_PAGE_SIZE,pageContent);
	if(err==-1){
		cout<< endl << "FILE_NOT_OPENED" << endl;
		return -1;
	}
	cout << hex << setfill('0');
	while(ptr<DEFAULT_PAGE_SIZE)
	{
		int nread=0;
		char *buf=new char[16];

		for( nread = 0; nread < 16 ; nread++,ptr++ ){
			buf[nread]=pageContent[ptr];
		}
		if( nread == 0){
			break;
		}

		// Show the address
		cout << setw(8) << address;

		// Show the hex codes
		for( int i = 0; i < nread; i++ )
		{
			if( i % 8 == 0 ) cout << ' ';
			if( i < 16 )
				cout << ' ' << setw(2) << (unsigned)buf[i];
			else
				cout << "   ";
		}

		// Show printable characters
		cout << "  ";
		for( int i = 0; i < nread; i++)
		{
			if( buf[i] < 32 ) cout << '.';
			else cout << buf[i];
		}

		cout << "\n";
		address += 16;

	}
	return SUCCESS;
}
