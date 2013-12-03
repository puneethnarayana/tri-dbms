/*
 * IndexCatalog.h
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#ifndef INDEXCATALOG_H_
#define INDEXCATALOG_H_
#include "../Global/globalStructures.h"
#include "../Global/globalDefines.h"
#include "../BufferManagement/BufferManager.h"
#include <vector>
#include <string>
using namespace std;
class IndexCatalog {
public:
	IndexCatalog(int fd,int pageNumber);
	virtual ~IndexCatalog();
	int createIndexCatalogPage(int pageNumber);
	int insertIndexEntry(char *indexName, char *tableName, char *indexKey, int indexType,int keySize,int indexHeaderPageNo);

private:

	        int fd_;
	        int pageNumber_;
	        char *pageData_;
	        BufferManager *buffManager_;
	        bool isIndexCatalogChanged_;
};

#endif /* INDEXCATALOG_H_ */
