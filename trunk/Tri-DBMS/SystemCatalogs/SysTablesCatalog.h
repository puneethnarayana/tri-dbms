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
class SysTablesCatalog {
public:
        SysTablesCatalog(int fd,int pageNumber);
        virtual ~SysTablesCatalog();
        int createSysTablePage(int pageNumber,char *pageData);
        int insertSysTableEntry(char *tableName,int recordSize,int noOfColumns,int dpChainHeader,char *pageData);
private:

        typedef struct{
                //char* tableName_;
                int recordSize_;
                int noOfColumns_;
                int dpChainHeaderAddress_;
        }SysTableEntryStruct;
//
//        typedef struct{
//                GenPageHeaderStruct genPageHeader_;
//                int noOfEntries;
//                SysTableEntryStruct *sysTableEntries_;
//        }sysTablePageStruct;
//
//        sysTablePageStruct sysTablePage_;
        int fd_;
        int pageNumber_;
        char *pageData_;
        BufferManager *buffManager_;
        bool isSysTableChanged_;
        //int maxSysTableEntriesPerPage_;
};

#endif /* SYSTABLESCATALOG_H_ */
