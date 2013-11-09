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
#include <ctime>
#include "LRUPageReplacement.h"
#include "../Global/globalDefines.h"
#include "../Global/globalStructures.h"
#include "../Global/globalVariables.h"
#include "../diskManagement/BasicDiskOperations.h"

class LRUPageReplacement;
class BufferManager {
public:
	Frame **BufferPool_;
	virtual ~BufferManager();

	static BufferManager* getInstance();
	int initializeCache(int noOfPages);
	int createDatabase(char *fileName, int pageSize, int noOfPages);
	int openDatabase(char *fileName);
	int readPage(int cd, int pageNumber, char*& ageContent);
	int writePage(int cd, int pageNumber, char *pageContent);
	int closeDatabase(int fd);
	int dropDatabase();
	int commitCache();
	int resetCache();
	int displayBufferList();
	int viewFrameBuffer(int frameNumber);
	int pinAndGetPage(int fd,int pageNumber,char*& pageContent);
	void replaceFrameWithAnother(int fd,int frameNumber, int pageNumber);
	void replaceFrameWithAnother(int fd,int frameNumber, int pageNumber, char *newPageContent);
	void flushAllPagesToDisk();
	void flushPageToDisk(int pageNumber);
	int getFrameNumber(int pageNumber);
	int getFreeFrame();
	float getHitRate();
	int hexDump(int fd,int pageNumber);
	LRUPageReplacement *LRUReplacement;
	int pageSize_;
	int bufferSizeInMB_;
	int numberOfFrames_;
private:
	BufferManager();
	std::time_t t;
	int fd_;
	char *openedFileName_;
	int totalNumberOfRequests_;
	int numberOfHits_;
	int numberOfDiskAccesses_;
	bool initCache_;
	static BufferManager* BufferManagerInstance_;
	BasicDiskOperations *diskManager_;
};

#endif /* BUFFERMANAGER_H_ */
