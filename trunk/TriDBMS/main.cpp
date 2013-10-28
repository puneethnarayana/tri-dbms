/*
 * main.cpp
 *
 *  Created on: Oct 25, 2013
 *      Author: ravin
 */

#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include "diskManagement/basicDiskOperations.h"
#include "BufferManagement/BufferManager.h"

#include "Global/globalDefines.h"
#include "Global/globalStructures.h"
using namespace std;


int main(){
	//BufferManager *buffMan=BufferManager.getInstance();
	//buffMan->getHitRate();
	basicDiskOperations *diskOps=new basicDiskOperations();
	char *DBName=new char[12];
	//int PAGE_SIZE=4096;
	int DBSizeInMB;
	char *pageContent=new char[4096];
	cout << "Enter the database name:";
	cin >> DBName;
	cout << "Enter the database size (in MB):";
	cin >> DBSizeInMB;
	strcpy(pageContent,"ji");
	diskOps->createDiskFile(DBName,PAGE_SIZE,DBSizeInMB*256);
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
}
