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
	int readPage(int cd, int pageNumber, char*& pageContent);
	int writePage(int cd, int pageNumber, char *pageContent);
	int closeDatabase(int fd);
	int dropDatabase();
	int commitCache();
	int resetCache();
	int displayBufferList();
	int viewFrameBuffer(int frameNumber);
	int pinAndGetPageForRead(int fd,int pageNumber,char*& pageContent);
	int pinAndGetPageForWrite(int fd,int pageNumber);
	void replaceFrameWithAnother(int fd,int frameNumber, int pageNumber);
	void replaceFrameWithAnother(int fd,int frameNumber, int pageNumber, char *newPageContent);
	void flushAllPagesToDisk();
	void flushPageToDisk(int fd,int pageNumber);
	int getFrameNumber(int fd,int pageNumber);
	int getFd(int frameNumber);
	int getCd(int fd);
	int getFreeFrame();
	int getHitRate();
	int hexDump(int fd,int pageNumber);
	int hexDump(char *pageContent);
	bool isInitCache() const;

	void setInitCache(bool initCache);

	LRUPageReplacement *LRUReplacement;
	int pageSize_;
	int bufferSizeInMB_;
	int numberOfFrames_;
	int numberOfFramesUsed_;

	typedef struct{
		int fd_;
		char fileName_[MAX_FILE_NAME_LENGTH+1];
	}Cache_Index;

	Cache_Index cacheIndex[MAX_DATABASES];



private:
	BufferManager();
	std::time_t t;
	//int fd_;
	int noOfDBsOpened_;
	char *openedFileName_;
	int totalNumberOfRequests_;
	int numberOfHits_;
	int numberOfDiskAccesses_;
	bool initCache_;
	static BufferManager* BufferManagerInstance_;
	BasicDiskOperations *diskManager_;



};

#endif /* BUFFERMANAGER_H_ */
