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
	IndexHeader(int indexHeaderPageNumber);
	void createIndexHeaderPage(int numOfColumns, int colTypes[],int colSizes[], int keySize);
	virtual ~IndexHeader();

	int getRootPageNumber();
	int getFanout();
	int getHeightOfTree();
	int getMaxNoOfRecordsInLeaf();
	int getKeySize();
	int getNoOfKeys();
	int getNoOfColumns();
	void setRootPageNumber(int rootPageNumber);
	void setFanout(int fanout);
	void setHeightOfTree(int heightOfTree);
	void setMaxNoOfRecordsInLeaf(int maxNoOfRecordsInLeaf);
	void setKeySize(int keySize);
	void setNoOfKeys(int numberOfKeys);
	void setNoOfColumns(int noOfColumns);



private:
	void initialize();
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
	int* colTypes_;
	int* colSizes_;
};

#endif /* INDEXHEADER_H_ */
