/*
 * IndexHeader.h
 *
 *  Created on: Nov 13, 2013
 *      Author: bill
 */

#ifndef INDEXHEADER_H_
#define INDEXHEADER_H_

#include "../Global/globalStructures.h"
#include "../Global/globalDefines.h"

class IndexHeader {
public:
	IndexHeader();
	IndexHeader(int fd,int indexHeaderPageNumber);
	void createIndexHeaderPage(int numOfColumns, int colTypes[],int colSizes[], int keySize);
	virtual ~IndexHeader();

	int getPageNumber();
	int getPageType();
	int getNextPageNumber();
	int getRootPageNumber();
	int getFanout();
	int getHeightOfTree();
	int getMaxNoOfRecordsInLeaf();
	int getKeySize();
	int getNoOfKeys();
	int getNoOfColumns();

	void setPageNumber(int pageNumber);
	void setPageType(int pageType);
	void setNextPageNumber(int nextPageNumber);
	void setRootPageNumber(int rootPageNumber);
	void setFanout(int fanout);
	void setHeightOfTree(int heightOfTree);
	void setMaxNoOfRecordsInLeaf(int maxNoOfRecordsInLeaf);
	void setKeySize(int keySize);
	void setNoOfKeys(int numberOfKeys);
	void setNoOfColumns(int noOfColumns);
	int* colTypes_;
	int* colSizes_;

private:
	void initializeColumns();
	typedef struct IndexHeaderStructure {
			GenPageHeaderStruct generalPageHeaderStruct;
			int rootPageNumber;
			int fanout;
			int heightOfTree;
			int maxNoOfRecordsInLeaf;
			int keySize;
			int numberOfKeys;
			int noOfcolumns;
	} IndexHeaderStruct;
	IndexHeaderStruct indexHeaderPage_;
	char *pageData_;

	int fd_;
	int pageNumber_;
	BufferManager *buffManager_;
	bool isIndexHeaderChanged_;
};

#endif /* INDEXHEADER_H_ */
