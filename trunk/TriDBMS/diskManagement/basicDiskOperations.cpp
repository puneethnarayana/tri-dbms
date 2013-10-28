/*
 * basicDiskOperations.cpp
 *
 *  Created on: Oct 23, 2013
 *      Author: ravin
 */


#include <stdlib.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "basicDiskOperations.h"
#include "../Global/globalDefines.h"
#include "../Global/globalStructures.h"
#include "../Global/globalVariables.h"
using namespace std;
basicDiskOperations::basicDiskOperations() {
	// TODO Auto-generated constructor stub
	fd_=-1;
	noOfPages_=0;
	pageSize_=4096;

}

basicDiskOperations::~basicDiskOperations() {
	// TODO Auto-generated destructor stub
}

void basicDiskOperations::createDiskFile(char *fileName, int pageSize, int noOfPages){
	fd_=creat(fileName,S_IRUSR|S_IWUSR);/*S_IRWXU : read, write, execute/search by owner*/
	if(fd_==-1){
		cout << strerror(errno);
		return;
	}
	fd_=open(fileName,O_RDWR);
	long int diskFileSize=pageSize*noOfPages;
	char *writeNull=new char[1];
	long int totalWritten=write(fd_,writeNull,diskFileSize);
	if(totalWritten==-1){
		cout << strerror(errno);
		return;
	}
	pageSize_=pageSize;
	noOfPages_=noOfPages;
	close(fd_);

}

void basicDiskOperations::openDiskFile(char *fileName){
	fd_=open(fileName,O_RDWR);
	if(fd_==-1){
		cout << strerror(errno);
		return;
	}
}

void basicDiskOperations::readDiskFile(int pageNumber,char *pageContent){
	lseek(fd_,pageNumber*pageSize_,SEEK_SET);
	int readSize=read(fd_,pageContent,pageSize_);
	cout <<"\n";
	if(readSize==-1){
		cout << strerror(errno);
		return;
	}
}


void basicDiskOperations::writeDiskFile(int pageNumber,char *pageContent){
	lseek(fd_,pageNumber*pageSize_,SEEK_SET);
	int writtenSize=write(fd_,pageContent,pageSize_);
	if(writtenSize==-1){
		cout << strerror(errno);
		return;
	}
}


void basicDiskOperations::closeDiskFile(){
	int close_ret=close(fd_);
	if(close_ret==-1){
		cout << strerror(errno);
		return;
	}
}
void basicDiskOperations::deleteDiskFile(char *fileName){
	int unlink_ret=unlink(fileName);
	if(unlink_ret==-1){
		cout << strerror(errno);
		return;
	}
}
long int basicDiskOperations::diskFileSize(char *fileName){
	long int startSize=lseek(fd_,0,SEEK_SET);
	long int endSize=lseek(fd_,0,SEEK_END);
	if(startSize==-1||endSize==-1){
		cout << strerror(errno);
	}
	return endSize-startSize;
}
