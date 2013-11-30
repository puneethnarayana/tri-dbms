/*
 * LeafNode.h
 *
 *  Created on: Oct 23, 2013
 *      Author: puneeth
 */

#ifndef LEAFNODE_H_
#define LEAFNODE_H_
#include "../Global/globalStructures.h"
#include "IndexHeader.h"
#include<vector>
#include<string.h>
#include<string>
using namespace std;
class LeafNode {
public:
	LeafNode();
	LeafNode(int fd,int leafPageNumber);
	int getIndexHeaderPageNumber();
	LeafNode(int fd, IndexHeader *indexHeaderPage, int leafPageNumber);
	virtual ~LeafNode();
	int createLeafPage(IndexHeader *indexHeaderPage_);
	int insertIntoLeafPage(const char* key, RIDStruct rid);
	int searchInLeafNode(const char* key);
	int searchInLeafNode(const char* key, RIDStruct rid);
	int deleteFromLeafPage(const char* key, RIDStruct &rid,
			std::vector<int> &deletedPages);
	int redistributeLeafPage(int pagenumber);
	int getLevelOfNode();
	void setLevelOfNode(int level);
	int getParentPageNumber();
	void setParentPageNumber(int parentPageNumber);
	int getNoOfRecordsInNode();
	void setNoOfRecordsInNode(int noOfRecords);
	int getRightPageNumber();
	void setRightPageNumber(int newRightPageNumber);
	int getLeftPageNumber();
	int ridsCompare(RIDStruct rid1, RIDStruct rid2);
	void setLeftPageNumber(int newLeftPageNumber);
	static int getLeafNodeHeaderSize();
	int getPageNumber();
	int getFirstKey(char* firstKey, RIDStruct &rid);
	int getLastKey(char* lastKey, RIDStruct &rid);
	int getFirstKey(char* firstKey);
	int searchKeyInLeafNode(const char* key,
			std::vector<RIDStruct> &RIDVector);
	//To find key at keynumber location
	void getKey(int keyNumber, char* tempKey);
	void getKeyAndRID(int keyNumber, char*tempKey, RIDStruct &rid);
	int dummyKeyCompare(char* key1, char* key2);
	void getParentKey(char* key);
	void UILeafNode();
	void display();
	void UIDisplayOfLeafNode(int numOfTabs);
	void DisplayKeyAt(int keyPosition);
	int searchKeyInLeafNodeWithOp(const char* key, int op, std::vector<
			RIDStruct> &RIDVector, std::vector<string> &keyVector);
	std::string toString();
	int searchFirstKeyToSecondKey(const char* firstKey,const char* secondKey,std::vector<RIDStruct> &RIDVector,
			std::vector<string> &keyVector);
	void getKeysAndRIDs(std::vector<RIDStruct> &RIDVector,std::vector<string> &keyVector);
	static int testPinCount;
	bool indexHeaderObjCreatedHere;
private:
	typedef struct LeafNodePageHeaderStructure {
		GenPageHeaderStruct generalPageHeader;
		int leftPageNumber;
		int rightPageNumber;
		int level;
		int noOfRecords;
		int parentPageNumber;
		int indexHeaderPageNumber;
	} LeafNodePageHeaderStruct;
	LeafNodePageHeaderStruct leafNodePageHeader_;
	IndexHeader *indexHeader_;
	int fd_;
	char* pageData_;
};


#endif /* LEAFNODE_H_ */
