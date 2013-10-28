/*
 * basicDiskOperations.h
 *
 *  Created on: Oct 23, 2013
 *      Author: ravin
 */

#ifndef BASICDISKOPERATIONS_H_
#define BASICDISKOPERATIONS_H_

#include "../Global/globalDefines.h"
#include "../Global/globalStructures.h"
#include "../Global/globalVariables.h"
class basicDiskOperations {
public:
	basicDiskOperations();
	virtual ~basicDiskOperations();
	void createDiskFile(char *fileName, int pageSize, int noOfPages);
	void openDiskFile(char *fileName);
	void readDiskFile(int pageNumber, char *pageContent);
	void writeDiskFile(int pageNumber, char *pageContent);
	void closeDiskFile();
	void deleteDiskFile(char *fileName);
	long int diskFileSize(char *fileName);
private:
	int fd_;
	int pageSize_;
	int noOfPages_;
};

#endif /* BASICDISKOPERATIONS_H_ */
