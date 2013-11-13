/*
 * BasicDiskOperations.cpp
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
#include "BasicDiskOperations.h"
#include "../Global/globalDefines.h"
#include "../Global/globalStructures.h"
#include "../Global/globalVariables.h"
using namespace std;
BasicDiskOperations::BasicDiskOperations() {
	// TODO Auto-generated constructor stub
	fd_=-1;
	noOfPages_=0;
	pageSize_=4096;

}

BasicDiskOperations::~BasicDiskOperations() {
	// TODO Auto-generated destructor stub
}

int BasicDiskOperations::createDiskFile(char *fileName, int pageSize, int noOfPages){
	long int diskFileSize=pageSize*noOfPages;
	char *writeNull=new char[1];
	long int totalWritten;
	fd_=creat(fileName,S_IRUSR|S_IWUSR);/*S_IRWXU : read, write, execute/search by owner*/
	if(fd_==-1){
		cout << strerror(errno);
		goto ret;
	}
	fd_=open(fileName,O_RDWR);
	totalWritten=write(fd_,writeNull,diskFileSize);
	if(totalWritten==-1){
		cout << strerror(errno);
		fd_=-1;
		goto ret;
	}
	pageSize_=pageSize;
	noOfPages_=noOfPages;
	close(fd_);
	ret: return fd_;
}

int BasicDiskOperations::openDiskFile(char *fileName){
	fd_=open(fileName,O_RDWR);
	if(fd_==-1){
		cout << strerror(errno);
	}
	return fd_;
}

int BasicDiskOperations::readDiskFile(int fd,int pageNumber,int pageSize,char *pageContent){
	lseek(fd,pageNumber*pageSize,SEEK_SET);
	int readSize=read(fd,pageContent,pageSize);
	cout <<"\n";
	if(readSize==-1){
		cout << strerror(errno);
	}
	return readSize;
}


int BasicDiskOperations::writeDiskFile(int fd,int pageNumber,int pageSize,char *pageContent){
	lseek(fd,pageNumber*pageSize,SEEK_SET);
	int writtenSize=write(fd,pageContent,pageSize);
	if(writtenSize==-1){
		cout << strerror(errno);
	}
	return writtenSize;
}

int BasicDiskOperations::seekDiskFile(int fd,int pageNumber,int pageSize){
	int seekSize=lseek(fd,pageNumber*pageSize,SEEK_SET);
	if(seekSize==-1){
		cout << strerror(errno);
	}
	return seekSize;
}
int BasicDiskOperations::closeDiskFile(int fd){
	int close_ret=close(fd);
	if(close_ret==-1){
		cout << strerror(errno);
	}
	return close_ret;
}
int BasicDiskOperations::deleteDiskFile(char *fileName){
	int unlink_ret=unlink(fileName);
	if(unlink_ret==-1){
		cout << strerror(errno);
	}
	return unlink_ret;
}
long int BasicDiskOperations::diskFileSize(char *fileName){
	long int startSize=lseek(fd_,0,SEEK_SET);
	long int endSize=lseek(fd_,0,SEEK_END);
	if(startSize==-1||endSize==-1){
		cout << strerror(errno);
	}
	return endSize-startSize;
}
