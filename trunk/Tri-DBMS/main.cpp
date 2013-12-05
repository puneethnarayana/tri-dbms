

#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <istream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <time.h>
using namespace std;
#include "Utils/CommonUtil.h"
#include "Global/globalDefines.h"
#include "BufferManagement/BufferManager.h"
#include "Index/IndexUI.h"

// #include "Parser/heading.h"
// prototype of bison-generated parser function

extern int yylex();
extern int yyparse();
extern FILE *yyin;
extern int yy_scan_string(const char *);

extern int mode;

void cacheConsole(){

	BufferManager *buffManager=BufferManager::getInstance();
	char *command=new char[MAX_QUERY_LENGTH];
	char *readPage;
	char *pageContent;
	char *dbname;
	char *temp;
	int fd,frameNo,pageNo,cacheSize,noOfPages,noOfFrames;
	char *query_string=new char[256];
	while(1){
		cout << endl << endl <<"Cache-Console>> ";
		delete[] query_string;
		query_string=new char[256];
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
				cout << "Wrong Number of Arguments for " << command << endl;
				continue;
			}
			temp=strtok(NULL," ");

			if(temp==NULL){
				cout << "Wrong Number of Arguments for " << command << endl;
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
				cout << "Wrong Number of Arguments for " << command << endl;
				continue;
			}
			//                      cout << endl << command;
			//                      cout << endl << fd << endl;
			cout << "cd is :"<< buffManager->openDatabase(dbname);
		}
		else if(strcasecmp(command,"closedb")==0){
			temp=strtok(NULL," ");
			if(temp==NULL){
				cout << "Wrong Number of Arguments for " << command << endl;
				continue;
			}
			fd=atoi(temp);

			buffManager->closeDatabase(fd);
		}
		else if(strcasecmp(command,"readpage")==0){
			clock_t startTime = clock();
			temp=strtok(NULL," ");
			if(temp==NULL){
				cout << "Wrong Number of Arguments for " << command << endl;
				continue;
			}
			fd=atoi(temp);
			temp=strtok(NULL," ");
			if(temp==NULL){
				cout << "Wrong Number of Arguments for " << command << endl;
				continue;
			}
			pageNo=atoi(temp);
			readPage=new char[DEFAULT_PAGE_SIZE];
			memset(readPage,0,DEFAULT_PAGE_SIZE);
			if(buffManager->readPage(fd,pageNo,readPage)!=-1){
				buffManager->hexDump(readPage);
			}

			else{
				cout << "ERROR READING PAGE" <<endl;
			}
			delete[] readPage;
			//cout << endl <<double( clock() - startTime ) << " micro seconds." << endl;
			//cout << "page read is :" << readPage;
		}
		else if(strcasecmp(command,"writepage")==0){
			clock_t startTime = clock();
			temp=strtok(NULL," ");
			if(temp==NULL){
				cout << "Wrong Number of Arguments for " << command << endl;
				continue;
			}
			fd=atoi(temp);
			temp=strtok(NULL," ");
			if(temp==NULL){
				cout << "Wrong Number of Arguments for " << command << endl;
				continue;
			}
			pageNo=atoi(temp);
			if(temp==NULL){
				cout << "Wrong Number of Arguments for " << command << endl;
				continue;
			}

			pageContent=new char[DEFAULT_PAGE_SIZE];

			memset(readPage,0,DEFAULT_PAGE_SIZE);
			pageContent=strtok(NULL,"\n");
			if(pageContent==NULL){
				cout << "Wrong Number of Arguments for " << command << endl;
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
				cout << "Wrong Number of Arguments for " << command << endl;
				continue;
			}
			fd=atoi(temp);
			temp=strtok(NULL," ");
			if(temp==NULL){
				cout << "Wrong Number of Arguments for " << command << endl;
				continue;
			}
			pageNo=atoi(temp);
			buffManager->hexDump(fd,pageNo);
		}
		else if(strcasecmp(command,"fullhexdump")==0){
					temp=strtok(NULL," ");
					if(temp==NULL){
						cout << "Wrong Number of Arguments for " << command << endl;
						continue;
					}
					fd=atoi(temp);
					temp=strtok(NULL," ");
					if(temp==NULL){
						cout << "Wrong Number of Arguments for " << command << endl;
						continue;
					}
					pageNo=atoi(temp);
					buffManager->hexDumpFull(fd,pageNo);
				}
		else if(strcasecmp(command,"bufferlist")==0){
			//cout << endl << command;
			buffManager->displayBufferList();
		}
		else if(strcasecmp(command,"viewbuffer")==0){
			temp=strtok(NULL," ");
			if(temp==NULL){
				cout << "Wrong Number of Arguments for " << command << endl;
				continue;
			}
			frameNo=atoi(temp);

			cout << endl << command;
			buffManager->viewFrameBuffer(frameNo);
		}
		else if(strcasecmp(command,"startcache")==0){
			temp=strtok(NULL," ");
			if(temp==NULL){
				cout << "Wrong Number of Arguments for " << command << endl;
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
			buffManager->getHitRate();
		}
		else if(strcmp(command,"exit")==0){
			break;
		}
		else if(strcmp(command,"memory")==0){
			buffManager->memoryUsage();
		}
		else{
			cout << "WRONG COMMAND " << command << " Please try again :)";
		}


	}
}

void indexConsole(){
	IndexUI *indui= new IndexUI();
	int fan, choice;
	while(1){
		cout<<"1. Create\n2. Open\n";
		cin>>choice;
		if(choice==1){
			cout<<"Enter fan out for the index  ";
			cin>>fan;
			indui->CreateIndexDB(fan);
		}
		else if(choice ==2){
			indui->OpenIndexDB();
		}
		else
			return;
	};
}

int main(int argc, char* argv[] ){

	if(argc<2){
		string buff;
		string prompt="SQL> ";
		do{
			cout<<endl<<prompt;
			getline(cin,buff);
			char *buffer= new char[buff.length()+1];
			strcpy(buffer,buff.c_str() );

			if((strcmp(buffer,"cache mode;")==0) || (strcmp(buffer,"CACHE MODE;")==0)){
				mode=CACHE_MODE;
				strcpy(buffer,"");
				cacheConsole();
				mode=SQL_MODE;
			}
			else if((strcmp(buffer,"cache on;")==0) || (strcmp(buffer,"CACHE ON;")==0)){
				prompt="CACHE> ";
			}
			else if((strcmp(buffer,"cache off;")==0) || (strcmp(buffer,"CACHE OFF;")==0)){
				prompt="SQL> ";
			}
			else if((strcmp(buffer,"index mode;")==0) || (strcmp(buffer,"INDEX MODE;")==0)){
				mode=INDEX_MODE;
				strcpy(buffer,"");
				indexConsole();
				mode=SQL_MODE;
			}
			else if((strcmp(buffer,"index on;")==0) || (strcmp(buffer,"INDEX ON;")==0)){
				prompt="INDEX> ";
			}
			else if((strcmp(buffer,"index off;")==0) || (strcmp(buffer,"INDEX OFF;")==0)){
				prompt="SQL> ";
			}
			else if((strcmp(buffer,"bulk insert")==0) || (strcmp(buffer,"BULK INSERT")==0)){
				int prevMode= mode;
				mode=BULK_MODE;
				char *fname;
				cout<<"Enter file name: ";
				cin>>fname;
				FILE *inputFile= fopen(fname,"r");
				if (!inputFile) {
							cout << "Cannot open input file!" << endl;
							return -1;
						}
				yyin = inputFile;
				do {
					yyparse();
				} while (!feof(yyin));
				cout<<"Phineesh"<<endl;
				strcpy(buffer,"");
				mode=prevMode;
			}

			yy_scan_string(buffer);
			yyparse();
		}while(1);

	}
	else{
		FILE *myfile = fopen(argv[1], "r");
		if (!myfile) {
			cout << "Cannot open input file!" << endl;
			return -1;
		}
		yyin = myfile;
		do {
			yyparse();
		} while (!feof(yyin));
	}


	return 0;
}
