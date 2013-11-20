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
	noOfDBsOpened_=0;
	numberOfFrames_=bufferSizeInMB_*1024*1024/pageSize_;
	LRUReplacement = new LRUPageReplacement();
	diskManager_ = new BasicDiskOperations();
	//fd_=-1;
	openedFileName_=new char[MAX_FILE_NAME_LENGTH];
	initializeCache(numberOfFrames_);


}

bool BufferManager::isInitCache() const {
	return initCache_;
}

void BufferManager::setInitCache(bool initCache) {
	initCache_ = initCache;
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
	int fd= diskManager_->createDiskFile(fileName,pageSize,noOfPages);
	return fd;
}
int BufferManager::openDatabase(char *fileName){
	openedFileName_=fileName;
	long int fd;
	fd=diskManager_->openDiskFile(fileName);
	if(fd!=-1){
		cacheIndex[noOfDBsOpened_].fd_=fd;
		strcpy(cacheIndex[noOfDBsOpened_].fileName_,fileName);
		noOfDBsOpened_++;
		return noOfDBsOpened_-1;
	}
	return -1;
}
int BufferManager::readPage(int cd, int pageNumber, char*& pageContent){
	totalNumberOfRequests_++;
	pageContent=new char[DEFAULT_PAGE_SIZE];
	int retVal=-1,frameNo=-1;
	long int fd = -1;
	if (cd < 0||cd >=noOfDBsOpened_)
		goto ret;
	//fd=BufferPool_[frameNumber]->fd_;
	fd=cacheIndex[cd].fd_;

	//cout << "fd is :" << fd <<endl;
	if(fd<0){
		goto ret;
	}
	//code to get file descriptor for given cd, from cache index.
	if(initCache_==false){
		retVal=diskManager_->readDiskFile(fd,pageNumber,pageSize_,pageContent);
		numberOfDiskAccesses_++;
		goto ret;
	}
	else{
		/*Check if the page is in the buffer.
		 * if not, get it into buffer, replace the frame if needed.
		 */
		frameNo=getFrameNumber(fd,pageNumber);
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
		memcpy(pageContent,BufferPool_[frameNo]->pageData_,DEFAULT_PAGE_SIZE);
		BufferPool_[frameNo]->pageNumber_=pageNumber;
		t = std::time(0);
		BufferPool_[frameNo]->fd_=fd;
		BufferPool_[frameNo]->priority_ = t;//LRUReplacement->getMaximumPriority()+ 1;//use time-stamp
		BufferPool_[frameNo]->pinCount_ = 0;
		//cout << "page content at end of read page(read page): "<< pageContent << endl;
	}
	retVal=SUCCESS;
	ret: return retVal;
}
int BufferManager::writePage(int cd, int pageNumber, char *newPageContent){
	totalNumberOfRequests_++;
	//cout << "content to be written is " << newPageContent << endl;
	int retVal=-1,frameNo=-1;
	char *pageContent=new char[DEFAULT_PAGE_SIZE];
	long int fd = -1;
	if (cd < 0||cd >=noOfDBsOpened_)
		goto ret;
	//fd=BufferPool_[frameNumber]->fd_;
	fd=cacheIndex[cd].fd_;
	//cout << "fd is :" << fd <<endl;
	if(fd<0){
		goto ret;
	}
	//cout << "opened db's cd, fd :"<< cd << fd <<endl;
	//code to get file descriptor for given cd, from cache index.
	if(initCache_==false){
		retVal=diskManager_->writeDiskFile(fd,pageNumber,pageSize_,newPageContent);
		numberOfDiskAccesses_++;
		goto ret;
	}
	else{
		/*Check if the page is in the buffer.
		 * if not, get it into buffer, replace the frame if needed.
		 */
		frameNo=getFrameNumber(fd,pageNumber);
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
		memcpy(BufferPool_[frameNo]->pageData_,newPageContent,DEFAULT_PAGE_SIZE);
		BufferPool_[frameNo]->pageNumber_=pageNumber;
		t = std::time(0);
		BufferPool_[frameNo]->fd_=fd;
		BufferPool_[frameNo]->priority_ = t;//LRUReplacement->getMaximumPriority()+ 1;//use time-stamp
		BufferPool_[frameNo]->pinCount_ = 0;
		BufferPool_[frameNo]->dirtyFlag_=true;

		retVal = SUCCESS;// change to status code which says success or buffer used.
	}
	ret: return retVal;
}

int BufferManager::pinAndGetPage(int fd,int pageNumber,char*& pageContent){
	int freeFrame=getFreeFrame();

//	long int fd;
//	fd=cacheIndex[cd].fd_;
	//cout << "please print this line "<<fd<< endl;

	//cout <<" ******************* *********" << pageContent << "********** *******************" << endl;
	if(freeFrame!=-1){
		//cout << "in free frame != -1" << endl;
		//cout << "free frame number is :" << freeFrame << endl;


		return freeFrame;
	}
	diskManager_->readDiskFile(fd,pageNumber,pageSize_,pageContent);
	numberOfDiskAccesses_++;
	//cout << "in free frame == -1" << endl;
	int frameToBeReplaced=LRUReplacement->getFrameToBeReplaced();
	replaceFrameWithAnother(fd,frameToBeReplaced,pageNumber);
	return frameToBeReplaced;


}


void BufferManager::replaceFrameWithAnother(int fd,int frameNumber,int newPageNumber){
//	long int fd;
//
//	fd=cacheIndex[cd].fd_;
	char *newPageContent=new char[DEFAULT_PAGE_SIZE];
	numberOfDiskAccesses_++;
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
//	long int fd;
//
//	fd=cacheIndex[cd].fd_;
		if (BufferPool_[frameNumber]->dirtyFlag_ == true) {

		/*write content in (frameNumber)th frame into (pageNumber)th page in DB and
		 * change current frame fields
		 * diskmanager.writeToDB(int pageNumber,char *pageContent);
		 */

		numberOfDiskAccesses_++; // page needs to be replaced.

		diskManager_->writeDiskFile(fd,BufferPool_[frameNumber]->pageNumber_,pageSize_,BufferPool_[frameNumber]->pageData_);

	}
	else{
		/* No write operations are done on page to be replaced.
		 * So, we can directly replace without writing it into disk.
		 */
	}
	t = std::time(0);
	BufferPool_[frameNumber]->fd_=fd;
	BufferPool_[frameNumber]->priority_ = t; //LRUReplacement->getMaximumPriority()+ 1;// use time-stamp
	BufferPool_[frameNumber]->pageNumber_ = newPageNumber;
	memcpy(BufferPool_[frameNumber]->pageData_,newPageContent,DEFAULT_PAGE_SIZE);
	BufferPool_[frameNumber]->pinCount_ = 0;
	BufferPool_[frameNumber]->dirtyFlag_=false;

}
int BufferManager::closeDatabase(int cd){
	if(cd<0 || cd>=noOfDBsOpened_){
		cout << "DATABASE_NOT_OPEN" << endl;
		return -1;
	}
	long int fd;
	fd=cacheIndex[cd].fd_;
	commitCache();
	if(diskManager_->closeDiskFile(fd)==-1){
		return -1;
	}
	cacheIndex[cd].fd_=-1;
	return SUCCESS;
}
int BufferManager::dropDatabase(){
	if(diskManager_->deleteDiskFile(openedFileName_)==-1){
		return -1;
	}
	return SUCCESS;
}
int BufferManager::commitCache(){
	//cout << "commit is called" << endl;
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
			flushPageToDisk(BufferPool_[i]->fd_,BufferPool_[i]->pageNumber_);
	}
}
void BufferManager::flushPageToDisk(int fd,int pageNumber){
	int frameNumber=getFrameNumber(fd,pageNumber);
	if(BufferPool_[frameNumber]->dirtyFlag_==true){
		//cout << "in flush page to disk, page number: " << pageNumber << endl;
		numberOfDiskAccesses_++;
		diskManager_->writeDiskFile(fd,pageNumber,pageSize_,BufferPool_[frameNumber]->pageData_);
		BufferPool_[frameNumber]->dirtyFlag_=false;
	}
}
int BufferManager::getFrameNumber(int fd,int pageNumber){
	for(int i=0;i<numberOfFrames_;i++){
		if(BufferPool_[i]->pageNumber_==pageNumber && BufferPool_[i]->fd_==fd){
			return i;
		}
	}
	return -1;
}

int BufferManager::getFd(int pageNumber){
	for(int i=0;i<numberOfFrames_;i++){
		if(BufferPool_[i]->pageNumber_==pageNumber){
			return BufferPool_[i]->fd_;
		}
	}
	return -1;
}
int BufferManager::getCd(int fd){
	for(int i=0;i<noOfDBsOpened_;i++){
		if(cacheIndex[i].fd_==fd){
			return i;
		}
	}
	return -1;
}

int BufferManager::getFreeFrame(){
	for(int i=0;i<numberOfFrames_;i++){
		//cout << "===============" <<BufferPool_[i]->pinCount_<<endl;
		if(BufferPool_[i]->pinCount_==-1){

			return i;
		}
	}
	return -1;
}

int BufferManager::displayBufferList(){
	cout << "\n=======================================================================================================================" << endl;
	cout << "||Frame No.||      cd    ||   File Name   ||   Page No.   ||   Dirty Flag  ||    Priority Type  || Priority Value  ||" << endl;
	for(int i=0;i<numberOfFrames_;i++){
		if(BufferPool_[i]->pinCount_!=-1){
			cout << "||    " <<i <<"    ||";
			cout << "      " << getCd(BufferPool_[i]->fd_) << "    ||";
			cout << "      "<<cacheIndex[getCd(BufferPool_[i]->fd_)].fileName_<< "   ||" ;
			cout <<"        " <<BufferPool_[i]->pageNumber_ <<"     ||";
			cout <<"         "<<BufferPool_[i]->dirtyFlag_ <<"     ||";
			cout <<"       "<<BufferPool_[i]->priorityType_ <<"   ||";
			cout <<"     "<<BufferPool_[i]->priority_ <<"    ||";
			cout << endl;
		}
	}
	cout << "\n=======================================================================================================================" << endl;
	return SUCCESS;
}
int BufferManager::viewFrameBuffer(int frameNumber){
	if(frameNumber<0||frameNumber>=numberOfFrames_){
		cout << "\nInvalid Frame Number\n";
		return -1;
	}
	cout << "\n=========================== FRAME - " << frameNumber << " ===================================" << endl;
	cout << "File Name is: " << cacheIndex[getCd(BufferPool_[frameNumber]->fd_)].fileName_<< endl;
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
	cout <<"Number of disk accesses	        : "<<numberOfDiskAccesses_<<endl;
	cout << "hit rate:			: ";
	if(totalNumberOfRequests_!=0)
		return (float)numberOfHits_/totalNumberOfRequests_;
	else
		return 0;
}
int BufferManager::hexDump(char *pageContent){
	cout <<"\n";
	cout <<
			"Address               Hexadecimal values                    Printable\n";
	cout <<
			"--------  -----------------------------------------------  -------------\n";
	cout << "\n";
	unsigned long address = 0;
	//char c;
	int ptr=0;

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

int BufferManager::hexDump(int cd,int pageNumber){

	if(cd<0 || cd>=noOfDBsOpened_){
		cout << "DATABASE_NOT_OPEN" << endl;
		return -1;
	}
	long int fd;
	fd=cacheIndex[cd].fd_;
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
