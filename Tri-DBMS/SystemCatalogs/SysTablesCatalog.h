/*
 * SysTablesCatalog.h
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#ifndef SYSTABLESCATALOG_H_
#define SYSTABLESCATALOG_H_
#include "../Global/globalStructures.h"
#include "../Global/globalDefines.h"
#include "../BufferManagement/BufferManager.h"
#include <vector>
#include <string>
using namespace std;
class SysTablesCatalog {
public:
        SysTablesCatalog(int fd,int pageNumber);
        virtual ~SysTablesCatalog();
        int createSysTablePage(int pageNumber,char *pageData);
        int insertSysTableEntry(char *tableName,int maxRecordSize,int noOfColumns,int dpChainHeader,char *pageData);
        vector<string> getSysTableRecordAsVector(char *tableName);
        int getDPChainHeaderPageNumber(char *tableName);
        int getNoOfColumns(char *tableName);
        int getMaxRecordSize(char *tableName);
private:
        typedef struct{

        	int recordSize_;
        	int noOfColumns_;
        	int dpChainHeaderAddress_;
        	char tableName_[MAX_FILE_NAME_LENGTH];
        }SysTableEntryStruct;

        int fd_;
        int pageNumber_;
        char *pageData_;
        BufferManager *buffManager_;
        bool isSysTableChanged_;
        //int maxSysTableEntriesPerPage_;
};

#endif /* SYSTABLESCATALOG_H_ */
