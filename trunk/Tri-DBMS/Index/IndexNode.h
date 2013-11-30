/*
 * IndexNode.h
 *
 *  Created on: Oct 23, 2013
 *      Author: puneeth
 */

#ifndef INDEXNODE_H_
#define INDEXNODE_H_

#include "../Global/globalStructures.h"
#include "IndexHeader.h"
#include<string>
#include <vector>
using namespace std;
class IndexNode {
private:
	int pagenumber;
	typedef struct IndexNodePage {
		GenPageHeaderStruct generalPageHeaderStruct;
		int leftPageNumber;
		int rightPageNumber;
		int noOfKeys;
		int level;
		int parentPageNumber;
		int indexHeaderPageNumber;
	} IndexNodePageHeaderStruct;
	IndexNodePageHeaderStruct indexNodePageHeader_;
	IndexHeader *indexHeader_;
	char* pageData_;
	static int debugCount_;
	int fd_;
public:
	IndexNode();
	IndexNode(int fd,int indexPageNumber);
	int getIndexHeaderPageNumber();
	IndexNode(int fd,IndexHeader *indexHeaderPage, int indexPageNumber);

	int createIndexNode(IndexHeader *indexHeaderPage_);
	int insertIntoIndexNode(const char* key, int leftPageNumber,
			int rightPageNumber);
	int insertAtTheEndOfIndexNode(const char* key, int rightPagenumber);
	int insertAtTheFrontOfIndexNode(const char* key, int leftPageNumber);
	//int inserIntoIndexNode(int pagenumber,char* key,char*data);
	//int deletefromIndexNode(int pagenumber,char* key);
	//	int reorganizeIndexNode(int pagenumber);
	int searchInIndexNode(const char* key);
	int foundInIndexNode(char* key);
	void replaceIfKeyFound(char* oldKey, char* newKey);
	int getLevelOfIndexNode();
	void setLevelOfIndexNode(int level);
	int dummyKeyCompare(char* key1, char* key2);
	//int searchInIndexPage(int key,IndexNodePageStruct indexNodeStruct);
	//int findChildPage(int rootPageNumber,int key,char* pageData);
	int getParentOfIndexNode();
	void setParentOfIndexNode(int parentPageNumber);
	int getNoOfKeysInIndexNode();
	void setNoOfKeysInIndexNode(int noOfKeys);
	int getLeftPageNumberOfIndexNode();
	void setLeftPageNumberOfIndexNode(int leftPageNumber);
	int getRightPageNumber();
	void setRightPageNumber(int rightPageNumber);
	int getPageNumber();
	int isKeyFound(char* key);
	int replaceKey(const char* oldKey, const char* newKey);
	int replaceKeyPreviousToPageNumber(int pageNumber,
			const char *oldKey, const char *newKey);
	/* finding size of Index Node*/
	static int getIndexNodeHeaderSize();
	void display();
	void indexNodeOnlyDisplay();
	void getKeyNextToPageNumber(int pageNumber, char* key);
	void getKeyPreviousToPageNumber(int pageNumber, char* key);
	int getPageNumberNextToGivenPageNumber(int pageNumber);
	int getPageNumberPreviousToGivenPageNumber(int pageNumber);
	int getSiblings(int pageNumber, int &leftSibling, int &rightSibling);
	int deleteKeyFromIndexNode(const char* key, bool flag, std::vector<int> &deletedPages);
	void deleteFirstKeyFromIndexNode();
	void deleteLastKeyFromIndexNode();
	//	int deleteKeyFromIndexNode(int pageNumber);
	int getFirstPageNumberPresentInIndexNode();
	int getLastPageNumberPresentInIndexNode();
	void getFirstKeyPresentInIndexNode(char* key);
	void getLastKeyPresentInIndexNode(char* key);
	void getSeperatingKey(int leftPage, int rightPage, char* key);
	void UIIndexNode();
	void UIDisplayOfIndexNode(int numberOfTabs);
	void deleteChilds(std::vector<int> &allPageNumbers);
	void findPages(std::vector<int> &leafPages, std::vector<int> &indexPages);
	std::string toString();
	void findFirstLeafPage(std::vector<int> &leafPages);
	bool indexHeaderObjCreatedHere;
	virtual ~IndexNode();

};

#endif /* INDEXNODE_H_ */
