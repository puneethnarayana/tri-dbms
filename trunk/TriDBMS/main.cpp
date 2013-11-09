/*
 * main.cpp
 *
 *  Created on: Oct 25, 2013
 *      Author: ravin
 */

#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include "diskManagement/BasicDiskOperations.h"
#include "BufferManagement/BufferManager.h"

#include "Global/globalDefines.h"
#include "Global/globalStructures.h"
using namespace std;


int main(){
	BufferManager *buffManager=BufferManager::getInstance();
	//buffMan->getHitRate();
	//basicDiskOperations *diskOps=new basicDiskOperations();
	int fileDesc;
	char *DBName=new char[12];
	char *command;
	char *dbname;
	int fd,frameNo,pageNo,cacheSize,noOfPages,noOfFrames;
	//int PAGE_SIZE=4096;
	int DBSizeInMB;
	char *pageContent=new char[DEFAULT_PAGE_SIZE];
	char *readPage=new char[DEFAULT_PAGE_SIZE];


	while(1){
		cout << endl << endl <<"Cache-Console$$";
		command=new char[10];
		cin >> command;
		if(strcasecmp(command,"createdb")==0){
			dbname=new char[MAX_FILE_NAME_LENGTH];
			cin >> dbname;
			cin >> noOfPages;
			cout << endl << command;
			cout << endl << dbname;
			cout << endl << noOfPages;
			cout << endl;
			buffManager->createDatabase(dbname,DEFAULT_PAGE_SIZE,noOfPages);
		}
		else if(strcasecmp(command,"opendb")==0){
			dbname=new char[MAX_FILE_NAME_LENGTH];
			cin >> dbname;
			cout << endl << command;
			cout << endl << fd;
			cout << "fd is :"<< buffManager->openDatabase(dbname);
		}
		else if(strcasecmp(command,"closedb")==0){
			cin >> fd;
			buffManager->closeDatabase(fd);
		}
		else if(strcasecmp(command,"readpage")==0){
			cin >> fd;
			cin >> pageNo;
			readPage=new char[DEFAULT_PAGE_SIZE];
			buffManager->readPage(fd,pageNo,readPage);
			cout << "page read is :" << readPage;
		}
		else if(strcasecmp(command,"writepage")==0){
			cin >> fd;
			cin >> pageNo;
			pageContent=new char[DEFAULT_PAGE_SIZE];
			cin.get(pageContent,DEFAULT_PAGE_SIZE);
			buffManager->writePage(fd,pageNo,pageContent);
		}
		else if(strcasecmp(command,"hexdump")==0){
			cin >> fd;
			cin >> pageNo;
			buffManager->hexDump(fd,pageNo);
		}
		else if(strcasecmp(command,"bufferlist")==0){
			cout << endl << command;
			buffManager->displayBufferList();
		}
		else if(strcasecmp(command,"viewbuffer")==0){
			cin >> frameNo;
			cout << endl << command;
			buffManager->viewFrameBuffer(frameNo);
		}
		else if(strcasecmp(command,"startcache")==0){
			cin >> noOfFrames;
			cout << endl << command;
			buffManager->initializeCache(noOfFrames);
		}
		else if(strcasecmp(command,"commitcache")==0){
			cout << endl << command;
			buffManager->commitCache();
		}
		else if(strcasecmp(command,"resetcache")==0){
			cout << endl << command;
			buffManager->resetCache();
		}
		else if(strcasecmp(command,"hitrate")==0){
			cout << endl << command;
			cout << buffManager->getHitRate();
		}
		else if(strcmp(command,"exit")==0){
			cout << endl << command;
			break;
		}
		else{
			cout << "WRONG COMMAND! Please try again :)";
		}
	}
	/*
	cout << "Enter the database name:";
	cin >> DBName;
	cout << "Enter the database size (in MB):";
	cin >> DBSizeInMB;
	strcpy(pageContent,"1");

	buffManager->createDatabase(DBName,DEFAULT_PAGE_SIZE,10);
	fileDesc=buffManager->openDatabase(DBName);
	buffManager->writePage(fileDesc,0,pageContent);
	buffManager->viewFrameBuffer(0);
	pageContent=new char[DEFAULT_PAGE_SIZE];
	strcpy(pageContent,"hello");
	buffManager->writePage(fileDesc,1,pageContent);
	buffManager->viewFrameBuffer(1);
	pageContent=new char[DEFAULT_PAGE_SIZE];
	strcpy(pageContent,"Welcome");
	buffManager->writePage(fileDesc,3,pageContent);
	buffManager->viewFrameBuffer(2);
	cout << "hit rate is: " << buffManager->getHitRate();
	buffManager->commitCache();

	buffManager->viewFrameBuffer(0);
	buffManager->viewFrameBuffer(1);
	buffManager->viewFrameBuffer(2);
	buffManager->readPage(fileDesc,0,readPage);
	cout << "page read is--------------------------: " << readPage << endl;
	buffManager->readPage(fileDesc,1,readPage);
	cout << "page read is--------------------------: " << readPage << endl;
	buffManager->readPage(fileDesc,3,readPage);
	cout << "page read is--------------------------: " << readPage << endl;
	cout << "hit rate is: " << buffManager->getHitRate();

	buffManager->hexDump(fileDesc,1);
	cout << "----------------------------------------------------------------" << endl;
	buffManager->displayBufferList();
	buffManager->viewFrameBuffer(0);
	buffManager->viewFrameBuffer(1);
	buffManager->viewFrameBuffer(2);
	*/

	/*
	diskOps->createDiskFile(DBName,DEFAULT_PAGE_SIZE,DBSizeInMB*256);
	diskOps->openDiskFile(DBName);
	cout << "\nsize of DB is : ";
	cout << diskOps->diskFileSize(DBName);
	diskOps->writeDiskFile(0,pageContent);
	diskOps->writeDiskFile(1,pageContent);
	diskOps->readDiskFile(0,pageContent);
	cout << "\nreading page 0:";
	cout << pageContent;
	pageContent=new char[4096];
	diskOps->readDiskFile(1,pageContent);
	cout << "\nreading page 1:";
	cout << pageContent;
	diskOps->closeDiskFile();
	*/
}
