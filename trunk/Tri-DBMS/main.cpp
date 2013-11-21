/*
 * main.cpp
 *
 *  Created on: Oct 25, 2013
 *      Author: ravin
 */

#include <iostream>
#include <istream>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <time.h>
#include "Utils/CommonUtil.h"

#include "diskManagement/BasicDiskOperations.h"
#include "BufferManagement/BufferManager.h"

#include "HeapFileManagement/FreePageManager.h"
#include "HeapFileManagement/DirectoryPage.h"
#include "HeapFileManagement/DataPage.h"
#include "SystemCatalogs/SysTablesCatalog.h"
#include "Global/globalDefines.h"
#include "Global/globalStructures.h"
#include "DatabaseManagement/DatabaseOperations.h"
#include "Utils/Record.h"

//#include <boost/serialization/vector.hpp>
using namespace std;


int main(){
	BufferManager *buffManager=BufferManager::getInstance();
	//buffMan->getHitRate();
	//basicDiskOperations *diskOps=new basicDiskOperations();
	int fileDesc;
	char *DBName=new char[12];
	char *command=new char[MAX_QUERY_LENGTH];
	char *temp;
	char *query_string=new char[MAX_QUERY_LENGTH];
	char *dbname;
	int fd,frameNo,pageNo,cacheSize,noOfPages,noOfFrames;
	//int PAGE_SIZE=4096;
	int DBSizeInMB;
	char *pageContent=new char[DEFAULT_PAGE_SIZE];
	char *readPage=new char[DEFAULT_PAGE_SIZE];


//	stringstream mystream;
//	mystream<<"hey";
//	mystream<<"wassup";
//	cout << mystream.str() << endl;




/*//getAllRecords testing

	dbname=new char[MAX_FILE_NAME_LENGTH];
	strcpy(dbname,"test");

	buffManager->createDatabase(dbname,DEFAULT_PAGE_SIZE,10);
	fd=buffManager->openDatabase(dbname);
	//get all records from datapage Testing!!
	vector<string> colNames,colCopy;
	int recSize=0,ii;
	char *recordcolNames=new char[DEFAULT_PAGE_SIZE];
	colNames.push_back("c1");
	colNames.push_back("co2");
	colNames.push_back("col3");
	Record *rec=new Record();
	rec->getRecordString(colNames,recordcolNames,&recSize);
	DataPage *dp=new DataPage(fd,1);
	dp->createDataPageHeaderStruct(1,pageContent);
	dp->insertRecord(recordcolNames,recSize);
	colCopy=dp->getAllRecords();
	buffManager->commitCache();
	buffManager->hexDump(fd,1);
	for(ii=0; ii < colCopy.size(); ii++)
	{
		cout << colCopy[ii] ;


	}
	stringstream ss;
	copy( colCopy.begin(), colCopy.end(), ostream_iterator<string>(ss, "\0"));
	string s = ss.str();
	cout << "pring this please! " << s<< endl;
	vector<char> SS2;
	std::copy(s.begin(), s.end(),back_inserter(SS2));

	cout << "ss2 size is :" << SS2.size() << endl;
	for(ii=0; ii < SS2.size(); ii++)
	{
		cout << SS2[ii] ;
	}
*/
/*
	// Testing getvectorFromRecord!!
	vector<string> colNames,colCopy;
	int recSize=0,ii;
	char *recordcolNames=new char[DEFAULT_PAGE_SIZE];
	colNames.push_back("c1");
	colNames.push_back("co2");
	colNames.push_back("col3");
	Record *rec=new Record();
	rec->getRecordString(colNames,recordcolNames,&recSize);
	colCopy=rec->getvectorFromRecord(recordcolNames,3);
	for(ii=0; ii < colCopy.size(); ii++)
	{
		cout << colCopy[ii] ;
	}
*/


/*
	vector<string> values_;
	values_.push_back("hello");
	values_.push_back("hey wassup");
	values_.push_back("dude");

	Record *newRecord = new Record();
	char *record= newRecord->getRecordString(values_);

	buffManager->createDatabase("test",DEFAULT_PAGE_SIZE,10);
	fd=buffManager->openDatabase("test");
	buffManager->hexDump(fd,3);
	buffManager->writePage(fd,3,record);
	buffManager->commitCache();
	buffManager->hexDump(fd,3);

	*/
/*	//Vector testing!!

	vector<string> SS;

	SS.push_back("The number is 10");
	SS.push_back("The number is 20");
	SS.push_back("The number is 30");
	cout << "Loop by index:" << endl;
	unsigned int ii;
	for(ii=0; ii < SS.size(); ii++)
	{
		cout << SS[ii] << endl;
	}

	dbname=new char[MAX_FILE_NAME_LENGTH];
	strcpy(dbname,"test");

	buffManager->createDatabase(dbname,DEFAULT_PAGE_SIZE,10);
	fd=buffManager->openDatabase(dbname);
	//buffManager->hexDump(fd,3);

	DataPage *dp=new DataPage(fd,3);
	dp->createDataPageHeaderStruct(3,pageContent);
//	buffManager->commitCache();
//	buffManager->hexDump(fd,3);

//	memcpy(pageContent,&SS,SS.size());
//	//cout << pageContent << endl;
//	memcpy(&SS2,pageContent,SS.size());
	stringstream ss;
	copy( SS.begin(), SS.end(), ostream_iterator<string>(ss, "\0"));
	string s = ss.str();

	s = s.substr(0, s.length()-1);
	cout << s << endl;
	string str = "hello";
	dp->insertRecord((char *)s.c_str(),s.size());
	buffManager->commitCache();
	buffManager->hexDump(fd,3);

	vector<char> SS2;
	vector<string> SS3;
	//SS3(s.begin(), s.end());
	std::copy(s.begin(), s.end(),back_inserter(SS2));
	vector<string> s2(SS2.begin(),SS2.end());
	//cout << "s2 is :" << s2 << endl;
//	cout << "ss2 size is :" << SS2.size() << endl;
//	for(ii=0; ii < SS2.size(); ii++)
//		{
//			cout << SS2[ii] ;
//		}
//	cout << "ss2 size is :" << SS2.size() << endl;
//
//	dp->insertRecord(pageContent,SS.size());
//	dp->insertRecord("how are you !",13);
//	buffManager->commitCache();
//	buffManager->hexDump(fd,3);


*/




	/* //Directory page testing!!
	cout<<"*******Started*******"<<endl;
	        dbname=new char[MAX_FILE_NAME_LENGTH];
	        strcpy(dbname,"test");

	        buffManager->createDatabase(dbname,DEFAULT_PAGE_SIZE,10);
	        fd=buffManager->openDatabase(dbname);
	        //buffManager->hexDump(fd,3);
	        FreePageManager *fpm=new FreePageManager(fd,1);
	        fpm->createFreePageManagerPage(1,pageContent);
	        DirectoryPage *dp=new DirectoryPage(fd,3);

	        dp->createDirectoryPage(3,pageContent);

	        cout<<"*******Created*******"<<endl;
	        buffManager->commitCache();
	        buffManager->hexDump(fd,3);

	        dp->insertSlotEntry(4000);
	        dp->insertSlotEntry(1200);
	        //dp->freeSlotDirectoryEntry(1);
	        buffManager->commitCache();
	        buffManager->hexDump(fd,3);
	        dp->insertRecord("hello",5);
	        buffManager->commitCache();
	        buffManager->hexDump(fd,3);
	        cout << "*****  end  *****" << endl;

*/

/* // SysTablePage Testing!!
	dbname=new char[MAX_FILE_NAME_LENGTH];
	strcpy(dbname,"test");

	buffManager->createDatabase(dbname,DEFAULT_PAGE_SIZE,10);
	fd=buffManager->openDatabase(dbname);
	buffManager->hexDump(fd,5);

	SysTablesCatalog *syscat=new SysTablesCatalog(fd,5);
	syscat->createSysTablePage(5,pageContent);
	buffManager->commitCache();
	buffManager->hexDump(fd,5);
	syscat->insertSysTableEntry("table1",35,7,5,pageContent);
	buffManager->commitCache();
	buffManager->hexDump(fd,5);
*/

	/* //Data page testing!!

	dbname=new char[MAX_FILE_NAME_LENGTH];
	strcpy(dbname,"test");

	buffManager->createDatabase(dbname,DEFAULT_PAGE_SIZE,10);
	fd=buffManager->openDatabase(dbname);
	buffManager->hexDump(fd,3);

	DataPage *dp=new DataPage(fd,3);
	dp->createDataPageHeaderStruct(3,pageContent);
	buffManager->commitCache();
	buffManager->hexDump(fd,3);

	dp->insertRecord("hello",5);
	dp->insertRecord("how are you !",13);
	dp->freeSlotDirectoryEntry(1);
	buffManager->commitCache();
	buffManager->hexDump(fd,3);
	dp->insertRecord("hello",5);
	dp->insertRecord("hello",5);
	dp->insertRecord("hello",5);
	buffManager->commitCache();
	buffManager->hexDump(fd,3);
	cout << "end!!!----------------------" << endl;
*/

/* //freePageManager Testing!!

	dbname=new char[MAX_FILE_NAME_LENGTH];
	strcpy(dbname,"test");

	buffManager->createDatabase(dbname,DEFAULT_PAGE_SIZE,10);
	fd=buffManager->openDatabase(dbname);
	buffManager->hexDump(fd,1);
	{
		FreePageManager *fpm=new FreePageManager(fd,1);
		fpm->createFreePageManagerPage(1,pageContent);
		buffManager->commitCache();
		buffManager->hexDump(fd,1);
		cout << "getfreepage after create: " <<(int)fpm->getFreePage() << endl;
		fpm->setPage(2);

		cout << "getfreepage after 2: " <<fpm->getFreePage() << endl;
		buffManager->commitCache();
		buffManager->hexDump(fd,1);
		fpm->setPage(3);

		cout << "getfreepage after 3: " <<fpm->getFreePage() << endl;
		buffManager->commitCache();
		buffManager->hexDump(fd,1);
		fpm->freePage(2);

		fpm->setPage(4);
		cout << "getfreepage after 4: " <<fpm->getFreePage() << endl;

		fpm->setPage(14);
		cout << "getfreepage after 7: " <<fpm->getFreePage() << endl;
		buffManager->commitCache();
		buffManager->hexDump(fd,1);
		int i;
//	for(i=0;i<100;i++){
//		cout << "is free (" << i << ") is:" << fpm->isPageFree(i) << endl;
//	}

	}

	FreePageManager *fpm=new FreePageManager(fd,1);
	int i;
	cout << "getfreepage after second: " <<fpm->getFreePage() << endl;
	for(i=0;i<20;i++){
			cout << "is free (" << i << ") is:" << fpm->isPageFree(i) << endl;
		}
*/
/*
	typedef struct abc{
		int a;
		char *c;
		char *d;
		char *e;

	}Dummy;
	cout << "sizeof struct before initialize :" << sizeof(Dummy) << endl;
	Dummy dummy,dummy1;
	//dummy.a=64;
	//dummy.b=20;
	dummy.c=new char[100];
	strcpy(dummy.c,"h");
	cout << "sizeof struct after initialize :" << sizeof(Dummy) << endl;
	cout << "sizeof variable after initialize :" << sizeof(dummy) << endl;

	dbname=new char[MAX_FILE_NAME_LENGTH];
	strcpy(dbname,"test");
	buffManager->createDatabase(dbname,DEFAULT_PAGE_SIZE,5);
	fd=buffManager->openDatabase(dbname);
	cout << sizeof(dummy) << endl;
	//cout << dummy.a << " " << dummy.b << endl;
	memcpy(pageContent,&dummy,sizeof(dummy));
	memcpy(&dummy1,pageContent,sizeof(Dummy));
	cout << pageContent << endl;
	cout << dummy1.a << " " << dummy1.c << endl;
	//strcpy(pageContent,"hi");
	buffManager->writePage(fd,0,pageContent);
	buffManager->commitCache();
	//buffManager->hexDump(fd,0);
	pageContent=new char[DEFAULT_PAGE_SIZE];
	buffManager->readPage(fd,0,pageContent);
	cout << pageContent << endl;

*/



	//Create Database, Insert into table, Select from Table Testing!!!

	buffManager->setInitCache(true);
	buffManager->setInitCache(false);
	dbname=new char[MAX_FILE_NAME_LENGTH];
	strcpy(dbname,"db1");
	char *tablename=new char[MAX_FILE_NAME_LENGTH];
	strcpy(tablename,"table1");

	time_t startTime,endTime,startTime1;

	DatabaseOperations *dbOps=new DatabaseOperations();

	dbOps->createDatabase(dbname,1);

	fd=dbOps->openDatabase(dbname);
//	buffManager->hexDump(fd,0);
//	buffManager->hexDump(fd,1);
//	buffManager->hexDump(fd,2);
//	buffManager->hexDump(fd,3);
	vector<string> colNames,insertValues_,insertValues1_,insertValues2_;
	colNames.push_back("c1");
	colNames.push_back("co2");
	colNames.push_back("col3");
	vector<string> colTypes;
	colTypes.push_back(CommonUtil::int_to_string(TYPE_INT));
	colTypes.push_back(CommonUtil::int_to_string(TYPE_CHAR));
	colTypes.push_back(CommonUtil::int_to_string(TYPE_BOOL));

	dbOps->createTable(tablename,colNames,colTypes);
	insertValues_.push_back(CommonUtil::int_to_string(34));
	insertValues_.push_back("Ravindra");
	insertValues_.push_back(CommonUtil::int_to_string(true));
	dbOps->insertIntoTable(tablename,insertValues_);

	insertValues_.clear();
	insertValues_.push_back(CommonUtil::int_to_string(12));
	insertValues_.push_back("Alka");
	insertValues_.push_back(CommonUtil::int_to_string(false));
	dbOps->insertIntoTable(tablename,insertValues_);

	insertValues_.clear();
	insertValues_.push_back(CommonUtil::int_to_string(83));
	insertValues_.push_back("puneeth");
	insertValues_.push_back(CommonUtil::int_to_string(false));
	dbOps->insertIntoTable(tablename,insertValues_);

	insertValues_.clear();
	insertValues_.push_back(CommonUtil::int_to_string(48));
	insertValues_.push_back("sreeraag");
	insertValues_.push_back(CommonUtil::int_to_string(false));
	dbOps->insertIntoTable(tablename,insertValues_);

	insertValues_.clear();
	insertValues_.push_back(CommonUtil::int_to_string(36));
	insertValues_.push_back("vikranth");
	insertValues_.push_back(CommonUtil::int_to_string(false));
	dbOps->insertIntoTable(tablename,insertValues_);

	insertValues_.clear();
	insertValues_.push_back(CommonUtil::int_to_string(66));
	insertValues_.push_back("pridhvi");
	insertValues_.push_back(CommonUtil::int_to_string(true));
	dbOps->insertIntoTable(tablename,insertValues_);

	insertValues_.clear();
	insertValues_.push_back(CommonUtil::int_to_string(60));
	insertValues_.push_back("sriram");
	insertValues_.push_back(CommonUtil::int_to_string(false));
	dbOps->insertIntoTable(tablename,insertValues_);

	insertValues_.clear();
	insertValues_.push_back(CommonUtil::int_to_string(45));
	insertValues_.push_back("don't know");
	insertValues_.push_back(CommonUtil::int_to_string(false));
	dbOps->insertIntoTable(tablename,insertValues_);

	insertValues_.clear();
	insertValues_.push_back(CommonUtil::int_to_string(1));
	insertValues_.push_back("A");
	insertValues_.push_back(CommonUtil::int_to_string(false));
	dbOps->insertIntoTable(tablename,insertValues_);


//	buffManager->hexDump(fd,0);
//	buffManager->hexDump(fd,1);
//	buffManager->hexDump(fd,2);
//	buffManager->hexDump(fd,3);
//	buffManager->hexDump(fd,4);
//	buffManager->hexDump(fd,5);
	//buffManager->hexDump(fd,6);
	//buffManager->hexDump(fd,7);
	//Testing getSchema in sysColumnCatalog
	//strcpy(tablename,"table2");

	startTime= clock();
		for(int i=0;i<30000;i++){
			dbOps->insertIntoTable(tablename,insertValues_);
		}
		buffManager->commitCache();
//		buffManager->hexDump(fd,0);
//		buffManager->hexDump(fd,1);
//		buffManager->hexDump(fd,2);
		//buffManager->hexDump(fd,6);
//		buffManager->hexDump(fd,7);
//		buffManager->hexDump(fd,8);
//		buffManager->hexDump(fd,200);
//		buffManager->hexDump(fd,18);
//		buffManager->hexDump(fd,25);
		//buffManager->hexDump(fd,24);
		//buffManager->hexDump(fd,25);

		dbOps->selectAllFromTable(tablename);
		endTime=clock();
	cout << endl <<double( endTime - startTime )/1000  << " milliseconds." << endl;
	buffManager->getHitRate();
	//strcpy(tablename,"table1");

//	buffManager->commitCache();
//	buffManager->hexDump(fd,0);
//	buffManager->hexDump(fd,1);
//	buffManager->hexDump(fd,2);
//	buffManager->hexDump(fd,3);
//	buffManager->hexDump(fd,4);
//	buffManager->hexDump(fd,5);
//	buffManager->hexDump(fd,6);
//	buffManager->hexDump(fd,7);

//
//
//	buffManager->setInitCache(false);
//	startTime1 = clock();
//	for(int i=0;i<100;i++){
//		dbOps->insertIntoTable(tablename,insertValues_);
//	}
	//dbOps->selectAllFromTable(tablename);


//	endTime=clock();
//		cout << endl <<double( endTime - startTime )/1000  << " milliseconds." << endl;
//	cout << endl <<double( clock() - startTime1 ) << " micro seconds." << endl;




/*

	while(1){
		cout << endl << endl <<"Cache-Console>>";
		query_string=new char[100];
		//cin >> command;
		cin.getline(query_string,MAX_QUERY_LENGTH);
		//cout << query_string << endl;
		command=strtok(query_string," ");
		//cout << command << endl;


		if(strcasecmp(command,"cacheon")==0){
			buffManager->setInitCache(true);
		}
		else if(strcasecmp(command,"cacheoff")==0){
			buffManager->setInitCache(false);
		}

		else if(strcasecmp(command,"createdb")==0){
			dbname=new char[MAX_FILE_NAME_LENGTH];
			dbname=strtok(NULL," ");
			if(dbname==NULL){
				cout << "Wrong Number of Aurguments for " << command << endl;
				continue;
			}
			temp=strtok(NULL," ");

			if(temp==NULL){
				cout << "Wrong Number of Aurguments for " << command << endl;
				continue;
			}
			noOfPages=atoi(temp);
			//cout << endl << command;
			cout << endl << dbname;
			cout << endl << noOfPages;
			cout << endl;
			if(noOfPages==0){
				cout << "Invalid Number of Pages" << endl;
				continue;
			}
			buffManager->createDatabase(dbname,DEFAULT_PAGE_SIZE,noOfPages);
		}
		else if(strcasecmp(command,"opendb")==0){
			dbname=new char[MAX_FILE_NAME_LENGTH];
			dbname=strtok(NULL," ");
			if(!dbname){
				cout << "Wrong Number of Aurguments for " << command << endl;
				continue;
			}
//			cout << endl << command;
//			cout << endl << fd << endl;
			cout << "cd is :"<< buffManager->openDatabase(dbname);
		}
		else if(strcasecmp(command,"closedb")==0){
			temp=strtok(NULL," ");
			if(temp==NULL){
				cout << "Wrong Number of Aurguments for " << command << endl;
				continue;
			}
			fd=atoi(temp);

			buffManager->closeDatabase(fd);
		}
		else if(strcasecmp(command,"readpage")==0){
			clock_t startTime = clock();
			temp=strtok(NULL," ");
			if(temp==NULL){
				cout << "Wrong Number of Aurguments for " << command << endl;
				continue;
			}
			fd=atoi(temp);
			temp=strtok(NULL," ");
			if(temp==NULL){
				cout << "Wrong Number of Aurguments for " << command << endl;
				continue;
			}
			pageNo=atoi(temp);
			readPage=new char[DEFAULT_PAGE_SIZE];
			if(buffManager->readPage(fd,pageNo,readPage)!=-1){
				buffManager->hexDump(readPage);
			}
			else{
				cout << "ERROR READING PAGE" <<endl;
			}
			//cout << endl <<double( clock() - startTime ) << " micro seconds." << endl;
			//cout << "page read is :" << readPage;
		}
		else if(strcasecmp(command,"writepage")==0){
			clock_t startTime = clock();
			temp=strtok(NULL," ");
			if(temp==NULL){
				cout << "Wrong Number of Aurguments for " << command << endl;
				continue;
			}
			fd=atoi(temp);
			temp=strtok(NULL," ");
			if(temp==NULL){
				cout << "Wrong Number of Aurguments for " << command << endl;
				continue;
			}
			pageNo=atoi(temp);
			if(temp==NULL){
				cout << "Wrong Number of Aurguments for " << command << endl;
				continue;
			}

			pageContent=new char[DEFAULT_PAGE_SIZE];
			pageContent=strtok(NULL,"\n");
			if(pageContent==NULL){
				cout << "Wrong Number of Aurguments for " << command << endl;
				continue;
			}
			if(buffManager->writePage(fd,pageNo,pageContent)==-1){
				cout << "ERROR WRITING TO PAGE" << endl;
			}


			//cout << endl <<double( clock() - startTime ) << " micro seconds." << endl;

		}
		else if(strcasecmp(command,"hexdump")==0){
			temp=strtok(NULL," ");
			if(temp==NULL){
				cout << "Wrong Number of Aurguments for " << command << endl;
				continue;
			}
			fd=atoi(temp);
			temp=strtok(NULL," ");
			if(temp==NULL){
				cout << "Wrong Number of Aurguments for " << command << endl;
				continue;
			}
			pageNo=atoi(temp);
			buffManager->hexDump(fd,pageNo);
		}
		else if(strcasecmp(command,"bufferlist")==0){
			//cout << endl << command;
			buffManager->displayBufferList();
		}
		else if(strcasecmp(command,"viewbuffer")==0){
			temp=strtok(NULL," ");
			if(temp==NULL){
				cout << "Wrong Number of Aurguments for " << command << endl;
				continue;
			}
			frameNo=atoi(temp);

			cout << endl << command;
			buffManager->viewFrameBuffer(frameNo);
		}
		else if(strcasecmp(command,"startcache")==0){
			temp=strtok(NULL," ");
			if(temp==NULL){
				cout << "Wrong Number of Aurguments for " << command << endl;
				continue;
			}
			noOfFrames=atoi(temp);
			//cout << endl << command;
			buffManager->initializeCache(noOfFrames);
		}
		else if(strcasecmp(command,"commitcache")==0){
			//cout << endl << command;
			buffManager->commitCache();
		}
		else if(strcasecmp(command,"resetcache")==0){
			//cout << endl << command;
			buffManager->resetCache();
		}
		else if(strcasecmp(command,"hitrate")==0){
			//cout << endl << command;
			cout << buffManager->getHitRate();
		}
		else if(strcmp(command,"exit")==0){
			cout << endl << "Bye!";
			break;
		}
		else{
			cout << "WRONG COMMAND " << command << " Please try again :)";
		}


	}

*/

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
