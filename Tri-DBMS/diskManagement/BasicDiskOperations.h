/*
 * BasicDiskOperations.h
 *
 *  Created on: Oct 23, 2013
 *      Author: ravin
 */

#ifndef BasicDiskOperations_H_
#define BasicDiskOperations_H_

#include "../Global/globalDefines.h"
#include "../Global/globalStructures.h"
#include "../Global/globalVariables.h"
class BasicDiskOperations {
public:
	BasicDiskOperations();
	virtual ~BasicDiskOperations();
	int createDiskFile(char *fileName, int pageSize, int noOfPages);
	int openDiskFile(char *fileName);
	int readDiskFile(int fd, int pageNumber,int pageSize, char *pageContent);
	int writeDiskFile(int fd, int pageNumber,int pageSize, char *pageContent);
	int seekDiskFile(int fd,int pageNumber,int pageSize);
	int closeDiskFile(int fd);
	int deleteDiskFile(char *fileName);
	long int diskFileSize(char *fileName);
private:
	int fd_;
	int pageSize_;
	int noOfPages_;
};

#endif /* BasicDiskOperations_H_ */
