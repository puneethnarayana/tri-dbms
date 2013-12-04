/*
 * IndexNode.cpp
 *
 *  Created on: Oct 23, 2013
 *      Author: puneeth
 */

#include "IndexNode.h"
#include "LeafNode.h"
#include "IndexHeader.h"
#include "BPlusTreeUtil.h"
#include "../BufferManagement/BufferManager.h"
#include "../Global/globalDefines.h"
#include "../Global/globalStructures.h"
#include <iostream>
#include<math.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <assert.h>
#include <sstream>
#include "../HeapFileManagement/FreePageManager.h"
using namespace std;

IndexNode::IndexNode(int fd) {
	// TODO Auto-generated constructor stub
	indexHeaderObjCreatedHere = false;
	fd_=fd;
	pageData_=new char[DEFAULT_PAGE_SIZE];
	memset(pageData_,0,DEFAULT_PAGE_SIZE);
	bufMgr_ = BufferManager::getInstance();
		//		DEBUG_B("Pinning leaf page with w
}
int IndexNode::debugCount_ = 0;
IndexNode::IndexNode(int fd, int indexPageNumber)
{
	fd_ = fd;
	pagenumber_=indexPageNumber;
	pageData_ = new char[DEFAULT_PAGE_SIZE];
	memset(pageData_,0,DEFAULT_PAGE_SIZE);
	bufMgr_ = BufferManager::getInstance();
	//		DEBUG_B("Pinning leaf page with with buffer manager")
	int error = bufMgr_->readPage(fd_,indexPageNumber, pageData_);

	memcpy(&indexNodePageHeader_, pageData_, sizeof(IndexNodePageHeaderStruct));
	int indexHeaderPageNumber = getIndexHeaderPageNumber();
	indexHeader_ = new IndexHeader(fd_,indexHeaderPageNumber);


}
int IndexNode::getIndexHeaderPageNumber()
{
	memcpy(&indexNodePageHeader_, pageData_, sizeof(IndexNodePageHeaderStruct));
	return indexNodePageHeader_.indexHeaderPageNumber;
}
IndexNode::IndexNode(int fd,IndexHeader *indexHeaderPage, int indexPageNumber) {

	indexHeader_ = indexHeaderPage;
	pagenumber_=indexPageNumber;
	pageData_ = NULL;
	fd_ = fd;
	pageData_ = new char[DEFAULT_PAGE_SIZE];
	memset(pageData_,0,DEFAULT_PAGE_SIZE);
	bufMgr_ = BufferManager::getInstance();

	bufMgr_->readPage(fd_,pagenumber_, pageData_);

	memcpy(&indexNodePageHeader_, pageData_,IndexNode::getIndexNodeHeaderSize());
}
IndexNode::~IndexNode() {
	bufMgr_ = BufferManager::getInstance();

	bufMgr_->writePage(fd_,indexNodePageHeader_.generalPageHeaderStruct.pageNumber,pageData_);
	//delete indexHeader_;
	delete[] pageData_;

}
//Initializes the index node header
int IndexNode::createIndexNode(IndexHeader* indexHeaderPage) {
	bufMgr_ = BufferManager::getInstance();
	//Where does newPageNumber come from
	int newPageNumber;

	FreePageManager *freePageMgr=new FreePageManager(fd_,1);
	newPageNumber=freePageMgr->getFreePage();
	pagenumber_=newPageNumber;
	//int error = bufMgr->readPage(fd_,newPageNumber, pageData_);
	//cout << "================================in create index node==================================="<<endl;
	//memcpy(&indexNodePageHeader_, pageData_, sizeof(IndexNodePageHeaderStruct));
	indexNodePageHeader_.generalPageHeaderStruct.pageNumber=newPageNumber;
	indexNodePageHeader_.generalPageHeaderStruct.nextPageNumber=-1;
	indexNodePageHeader_.generalPageHeaderStruct.pageType=INDEX_INTERNAL_PAGE;
	indexNodePageHeader_.leftPageNumber = -1;
	indexNodePageHeader_.rightPageNumber = -1;
	indexNodePageHeader_.level = 1;//this is minimum level
	indexNodePageHeader_.noOfKeys = 0;
	indexNodePageHeader_.parentPageNumber = -1;
	indexNodePageHeader_.indexHeaderPageNumber=indexHeaderPage->getPageNumber();
	//cout << "index header page number in index node :" <<indexHeaderPage->getPageNumber() <<endl;
	memcpy(pageData_, &indexNodePageHeader_, sizeof(IndexNodePageHeaderStruct));
	indexHeader_ = indexHeaderPage;

	bufMgr_->writePage(fd_,newPageNumber, pageData_);
	delete freePageMgr;
	return SUCCESS;
}
int IndexNode::insertIntoIndexNode(const char* key, int leftPageNumber,int rightPageNumber) {

	int levelOfRoot = indexHeader_->getHeightOfTree();
	if (levelOfRoot == 0) {
		//IF INDEX NODE IS CREATED AT FIRST
		indexHeader_->setRootPageNumber(indexNodePageHeader_.generalPageHeaderStruct.pageNumber);
		indexHeader_->setHeightOfTree(indexHeader_->getHeightOfTree() + 1);
		int offset = IndexNode::getIndexNodeHeaderSize();
		memcpy(&pageData_[offset], &leftPageNumber, sizeof(int));
		offset = offset + sizeof(int);
		memcpy(&pageData_[offset], key, indexHeader_->getKeySize());
		offset = offset + indexHeader_->getKeySize();
		memcpy(&pageData_[offset], &rightPageNumber, sizeof(int));
		//cout << "left :" <<leftPageNumber << " key :"<< key << " right :"<< rightPageNumber <<endl;
		indexNodePageHeader_.noOfKeys = indexNodePageHeader_.noOfKeys + 1;
		//		DEBUG_B("no of key intially "<<indexNodePageHeader_.noOfKeys)
		memcpy(pageData_, &indexNodePageHeader_,
				IndexNode::getIndexNodeHeaderSize());
		LeafNode leafNode(fd_,indexHeader_, leftPageNumber);
		leafNode.setParentPageNumber(getPageNumber());
		LeafNode leafNode1(fd_,indexHeader_, rightPageNumber);
		leafNode1.setParentPageNumber(getPageNumber());
		bufMgr_->writePage(fd_,pagenumber_,pageData_);
//			bufMgr_->hexDump(fd_,7);
//			bufMgr_->hexDump(fd_,8);
		return SUCCESS;
	} else {
		//IF ALREADY AN INDEX NODE IS EXISTED
		if (indexNodePageHeader_.noOfKeys != indexHeader_->getFanout()) {
			//IF INDEX NODE HAS ENOUGH SPACE TO ACCOMODATE NEW KEY
			int tempLeftPage, tempRightPage;
			char tempKey[indexHeader_->getKeySize()];
			int offset = IndexNode::getIndexNodeHeaderSize();
			int count;
			for (count = 0; count < indexNodePageHeader_.noOfKeys; count++) {
				memcpy(&tempLeftPage, &pageData_[offset], sizeof(int));
				offset = offset + sizeof(int);
				memcpy(tempKey, &pageData_[offset], indexHeader_->getKeySize());
				offset = offset + indexHeader_->getKeySize();
				memcpy(&tempRightPage, &pageData_[offset], sizeof(int));
				//				dummyKeyCompare(tempKey, key);
				int compValue = BPlusTreeUtil::keyCompare(tempKey, key,
						indexHeader_);
				//				DEBUG_B("key compare in index node "<<tempKey<<"----"<<key)
				if (compValue == 1) {
					char tempKeys[indexNodePageHeader_.noOfKeys][indexHeader_->getKeySize()];
					int tempPageNumbers[indexNodePageHeader_.noOfKeys - count + 1];
					int tempOffset = IndexNode::getIndexNodeHeaderSize()
									+ count * (sizeof(int)
											+ indexHeader_->getKeySize());
					int i;
					for (i = count; i < indexNodePageHeader_.noOfKeys; i++) {
						memcpy(&tempPageNumbers[i], &pageData_[tempOffset],sizeof(int));
						//						DEBUG_B("page no-----------"<<tempPageNumbers[i])
						tempOffset = tempOffset + sizeof(int);
						memcpy(&tempKeys[i], &pageData_[tempOffset],indexHeader_->getKeySize());
						//						DEBUG_B(" KEY----------------------"<<tempKeys[i])
						tempOffset += indexHeader_->getKeySize();
					}

					memcpy(&tempPageNumbers[i], &pageData_[tempOffset],sizeof(int));
					offset = IndexNode::getIndexNodeHeaderSize() + count
							* (sizeof(int) + indexHeader_->getKeySize());
					//					DEBUG_B("TEMP LEFT AND RIGHT "<<tempLeftPage<<"  "<<tempRightPage)
					//					DEBUG_B("after values "<<tempPageNumbers[count])
					memcpy(&pageData_[offset], &leftPageNumber, sizeof(int));
					offset = offset + sizeof(int);
					memcpy(&pageData_[offset], key, indexHeader_->getKeySize());
					offset += indexHeader_->getKeySize();
					memcpy(&pageData_[offset], &rightPageNumber, sizeof(int));
					offset += sizeof(int);
					if (getLevelOfIndexNode() == 1) {
						//	DEBUG_B("left right parent "<<leftPageNumber<<"  "<<rightPageNumber)
						//  DEBUG_B("parent "<<getPageNumber())
						LeafNode leafNode1(fd_,indexHeader_, leftPageNumber);
						LeafNode leafNode2(fd_,indexHeader_, rightPageNumber);
						LeafNode leafNode3(fd_,indexHeader_, tempLeftPage);
						LeafNode leafNode4(fd_,indexHeader_, tempRightPage);
						leafNode1.setLeftPageNumber(leafNode3.getLeftPageNumber());
						leafNode1.setRightPageNumber(rightPageNumber);
						leafNode2.setLeftPageNumber(leftPageNumber);
						leafNode2.setRightPageNumber(tempRightPage);
						leafNode4.setLeftPageNumber(rightPageNumber);
						leafNode1.setParentPageNumber(getPageNumber());
						leafNode2.setParentPageNumber(getPageNumber());
						//						leafNode1.display();
						//						leafNode2.display();
					} else {
						IndexNode indexNode1(fd_,indexHeader_, leftPageNumber);
						IndexNode indexNode2(fd_,indexHeader_, rightPageNumber);
						IndexNode indexNode3(fd_,indexHeader_, tempLeftPage);
						IndexNode indexNode4(fd_,indexHeader_, tempRightPage);
						indexNode1.setLeftPageNumberOfIndexNode(
								indexNode3.getLeftPageNumberOfIndexNode());
						indexNode1.setRightPageNumber(rightPageNumber);
						indexNode2.setLeftPageNumberOfIndexNode(leftPageNumber);
						indexNode2.setRightPageNumber(tempRightPage);
						indexNode4.setLeftPageNumberOfIndexNode(rightPageNumber);
						indexNode1.setParentOfIndexNode(getPageNumber());
						indexNode2.setParentOfIndexNode(getPageNumber());
					}
					for (int j = count; j < indexNodePageHeader_.noOfKeys; j++) {
						memcpy(&pageData_[offset], &tempKeys[j],
								indexHeader_->getKeySize());
						offset = offset + indexHeader_->getKeySize();
						memcpy(&pageData_[offset], &tempPageNumbers[j + 1],
								sizeof(int));
						offset = offset + sizeof(int);
					}
					indexNodePageHeader_.noOfKeys++;
					memcpy(pageData_, &indexNodePageHeader_,
							IndexNode::getIndexNodeHeaderSize());
					offset = IndexNode::getIndexNodeHeaderSize();
					bufMgr_->writePage(fd_,pagenumber_,pageData_);
									return SUCCESS;
				}
			}
			if (indexNodePageHeader_.noOfKeys == 0) {
				offset = IndexNode::getIndexNodeHeaderSize();
				//				DEBUG_B(leftPageNumber<<"  "<<"  "<<key<<"  "<<rightPageNumber)
				memcpy(&pageData_[offset], &leftPageNumber, sizeof(int));
				offset = offset + sizeof(int);
				memcpy(&pageData_[offset], key, indexHeader_->getKeySize());
				offset = offset + indexHeader_->getKeySize();
				memcpy(&pageData_[offset], &rightPageNumber, sizeof(int));
				indexNodePageHeader_.noOfKeys++;
				memcpy(pageData_, &indexNodePageHeader_,
						IndexNode::getIndexNodeHeaderSize());
				LeafNode leafNode1(fd_,indexHeader_, leftPageNumber);
				leafNode1.setParentPageNumber(getPageNumber());
				LeafNode leafNode2(fd_,indexHeader_, rightPageNumber);
				leafNode2.setParentPageNumber(getPageNumber());
				bufMgr_->writePage(fd_,pagenumber_,pageData_);
				return SUCCESS;
			}
			if (count == indexNodePageHeader_.noOfKeys) {

				offset = IndexNode::getIndexNodeHeaderSize()
						+ (indexNodePageHeader_.noOfKeys
								* (indexHeader_->getKeySize() + sizeof(int)));
				if (getLevelOfIndexNode() == 1) {
					LeafNode leafNode1(fd_,indexHeader_, leftPageNumber);
					LeafNode leafNode2(fd_,indexHeader_, rightPageNumber);
					leafNode2.setLeftPageNumber(leftPageNumber);
					leafNode1.setParentPageNumber(getPageNumber());
					leafNode2.setParentPageNumber(getPageNumber());
					//					DEBUG_B("lraf "<<leafNode1.getRightPageNumber())
					//					leafNode2.setRightPageNumber(leafNode1.getRightPageNumber());
					leafNode1.setRightPageNumber(rightPageNumber);
					if (leafNode2.getRightPageNumber() != -1) {
						LeafNode leafNode3(fd_,indexHeader_,
								leafNode2.getRightPageNumber());
						leafNode3.setLeftPageNumber(rightPageNumber);
					}
				} else {
					IndexNode indexNode1(fd_,indexHeader_, leftPageNumber);
					IndexNode indexNode2(fd_,indexHeader_, rightPageNumber);
					indexNode1.setParentOfIndexNode(getPageNumber());
					indexNode2.setParentOfIndexNode(getPageNumber());
					indexNode2.setLeftPageNumberOfIndexNode(leftPageNumber);
					indexNode1.setRightPageNumber(rightPageNumber);
					if (indexNode2.getRightPageNumber() != -1) {
						IndexNode indexNode3(fd_,indexHeader_,
								indexNode2.getRightPageNumber());
						indexNode3.setLeftPageNumberOfIndexNode(rightPageNumber);
					}
				}

				memcpy(&pageData_[offset], &leftPageNumber, sizeof(int));
				offset = offset + sizeof(int);
				memcpy(&pageData_[offset], key, indexHeader_->getKeySize());
				offset = offset + indexHeader_->getKeySize();
				memcpy(&pageData_[offset], &rightPageNumber, sizeof(int));
				indexNodePageHeader_.noOfKeys++;
				memcpy(pageData_, &indexNodePageHeader_,
						IndexNode::getIndexNodeHeaderSize());

				//				return SUCCESS;
			}
			bufMgr_->writePage(fd_,pagenumber_,pageData_);

			return SUCCESS;
		} else {
			//nof of keys index node is equals to maximum number so split it into two nodes
			char tempKeys[indexNodePageHeader_.noOfKeys + 1][indexHeader_->getKeySize()];
			int tempPageNos[indexNodePageHeader_.noOfKeys + 2];
			int tempCount = 0;
			int offset = IndexNode::getIndexNodeHeaderSize();
			int count;
			int found = 0;
			for (count = 0; count < indexNodePageHeader_.noOfKeys; count++) {
				char tempKey[indexHeader_->getKeySize()];
				int tempLeft, tempRight;
				memcpy(&tempLeft, &pageData_[offset], sizeof(int));
				offset += sizeof(int);
				memcpy(&tempKey, &pageData_[offset], indexHeader_->getKeySize());
				offset += indexHeader_->getKeySize();
				memcpy(&tempRight, &pageData_[offset], sizeof(int));
				//				dummyKeyCompare(tempKey, key);
				int compValue = BPlusTreeUtil::keyCompare(tempKey, key,
						indexHeader_);
				if (compValue == 1 && found == 0) {
					memcpy(tempKeys[tempCount], key, indexHeader_->getKeySize());
					tempPageNos[tempCount] = leftPageNumber;
					tempCount++;
					tempPageNos[tempCount] = rightPageNumber;
					found = 1;
				}

				memcpy(tempKeys[tempCount], tempKey, indexHeader_->getKeySize());
				if (found == 0) {
					tempPageNos[tempCount] = tempLeft;
				}
				tempCount++;
				tempPageNos[tempCount] = tempRight;
				//				DEBUG_B("TEMP COUNT "<<tempCount)

			}
			if (found == 0) {
				memcpy(tempKeys[tempCount], key, indexHeader_->getKeySize());
				tempCount++;
				tempPageNos[tempCount] = rightPageNumber;

			}

			indexNodePageHeader_.noOfKeys = 0;
			offset = IndexNode::getIndexNodeHeaderSize();
			int i;
			for (i = 0; i < tempCount / 2; i++) {
				memcpy(&pageData_[offset], &tempPageNos[i], sizeof(int));
				offset += sizeof(int);
				if (indexNodePageHeader_.level == 1) {
					LeafNode leafNode(fd_,indexHeader_, tempPageNos[i]);
					leafNode.setParentPageNumber(getPageNumber());
				} else {
					IndexNode indexNode(fd_,indexHeader_, tempPageNos[i]);
					indexNode.setParentOfIndexNode(getPageNumber());
				}
				memcpy(&pageData_[offset], tempKeys[i],
						indexHeader_->getKeySize());
				offset += indexHeader_->getKeySize();
				indexNodePageHeader_.noOfKeys++;
			}
			//			DEBUG_B("no of records "<<indexNodePageHeader_.noOfKeys);
			memcpy(&pageData_[offset], &tempPageNos[i], sizeof(int));
			if (indexNodePageHeader_.level == 1) {
				LeafNode leafNode(fd_,indexHeader_, tempPageNos[i]);
				leafNode.setParentPageNumber(getPageNumber());
			} else {
				IndexNode indexNode(fd_,indexHeader_, tempPageNos[i]);
				indexNode.setParentOfIndexNode(getPageNumber());
			}

			//NOW CREATE A NEW INDEX NODE AND COPY REMAINING KEYS INTO THAT NODE
			IndexNode indexNode(fd_);
			indexNode.createIndexNode(indexHeader_);
			//			cout<<"\nNEW PAGE NUMBER  "<<indexNode.getPageNumber()<<endl;
			indexNode.setLevelOfIndexNode(indexNodePageHeader_.level);
			if (indexNodePageHeader_.rightPageNumber != -1) {
				IndexNode indexNode1(fd_,indexHeader_,
						indexNodePageHeader_.rightPageNumber);
				indexNode1.setLeftPageNumberOfIndexNode(
						indexNode.getPageNumber());
			}
			indexNode.setLeftPageNumberOfIndexNode(getPageNumber());
			indexNode.setRightPageNumber(indexNodePageHeader_.rightPageNumber);
			setRightPageNumber(indexNode.getPageNumber());
			for (i = tempCount / 2 + 1; i < tempCount; i++) {
				char shiftKey[indexHeader_->getKeySize()];
				int shiftLeft, shiftRight;
				memcpy(shiftKey, tempKeys[i], indexHeader_->getKeySize());
				memcpy(&shiftLeft, &tempPageNos[i], sizeof(int));
				memcpy(&shiftRight, &tempPageNos[i + 1], sizeof(int));

				//				DEBUG_B("INSERTING KEYS++++++++++"<<shiftKey<<"  "<<shiftLeft<<"   "<<shiftRight)
				indexNode.insertIntoIndexNode(shiftKey, shiftLeft, shiftRight);
				//				DEBUG_B("index node level "<<indexNodePageHeader_.level)
				//				DEBUG_B("Index node page number "<<indexNode.getPageNumber())
				if (indexNodePageHeader_.level == 1) {
					//					DEBUG_B("HEHRE")
					//					DEBUG_B("left "<<shiftLeft<<" right "<<shiftRight)
					//					DEBUG_B("current page "<<indexNode.getPageNumber());
					LeafNode leafNode(fd_,indexHeader_, shiftLeft);
					leafNode.setParentPageNumber(indexNode.getPageNumber());
					//					leafNode.display();
					LeafNode leafNode1(fd_,indexHeader_, shiftRight);
					leafNode1.setParentPageNumber(indexNode.getPageNumber());
					//					leafNode.display();
				} else {
					//					DEBUG_B("HERE")
					IndexNode tempIndexNode(fd_,indexHeader_, shiftLeft);
					tempIndexNode.setParentOfIndexNode(
							indexNode.getPageNumber());
					IndexNode tempIndexNode1(fd_,indexHeader_, shiftRight);
					tempIndexNode1.setParentOfIndexNode(
							indexNode.getPageNumber());
				}
			}

			//			DEBUG_B("no of records "<<indexNodePageHeader_.noOfKeys);
			char promoteKey[indexHeader_->getKeySize()];
			int promoteLeft, promoteRight;
			promoteLeft = getPageNumber();
			promoteRight = indexNode.getPageNumber();
			memcpy(promoteKey, tempKeys[tempCount / 2],
					indexHeader_->getKeySize());

			if (indexHeader_->getHeightOfTree()
					== indexNodePageHeader_.level) {
				//NOW CREATE A ROOT NODE AND ASSIGN IT AS A PARENT FOR ABOVE NODES
				IndexNode indexNode1(fd_);
				indexNode1.createIndexNode(indexHeader_);
				indexHeader_->setRootPageNumber(indexNode1.getPageNumber());
				indexHeader_->setHeightOfTree(
						indexHeader_->getHeightOfTree() + 1);
				int level = indexHeader_->getHeightOfTree();
				indexNode1.setLevelOfIndexNode(level);
				indexNode1.insertIntoIndexNode(promoteKey, promoteLeft,
						promoteRight);
				indexNodePageHeader_.parentPageNumber
						= indexNode1.getPageNumber();
				indexNodePageHeader_.leftPageNumber = -1;
				indexNodePageHeader_.rightPageNumber
						= indexNode.getPageNumber();
				memcpy(pageData_, &indexNodePageHeader_,
						IndexNode::getIndexNodeHeaderSize());
				indexNode.setParentOfIndexNode(indexNode1.getPageNumber());
				indexNode.setLeftPageNumberOfIndexNode(getPageNumber());
			} else {
				//PROMOTE KEY, LEFT, RIGHT PAGE NUMBERS TO PARENT OF THE INDEX NODE
				IndexNode indexNode(fd_,indexHeader_, getParentOfIndexNode());
				//				DEBUG_B("PROMTES___________________________________________"<<promoteLeft<<"  "<<promoteKey<<"   "<<promoteRight);
				indexNode.insertIntoIndexNode(promoteKey, promoteLeft,
						promoteRight);
				bufMgr_->writePage(fd_,pagenumber_,pageData_);
				return SUCCESS;
				//				indexHeader_->updateHeightOfTheTree(indexHeader_->getHeightOfTheTree() + 1);
			}
		}
	}
	bufMgr_->writePage(fd_,pagenumber_, pageData_);
	return SUCCESS;
}
int IndexNode::insertAtTheEndOfIndexNode(const char* key,
		int rightPageNumber) {
	int offset = IndexNode::getIndexNodeHeaderSize();
	int lastPage = getLastPageNumberPresentInIndexNode();
	for (int i = 0; i < getNoOfKeysInIndexNode(); i++) {
		offset = offset + sizeof(int) + indexHeader_->getKeySize();
	}
	offset = offset + sizeof(int);
	memcpy(&pageData_[offset], key, indexHeader_->getKeySize());
	offset = offset + indexHeader_->getKeySize();
	memcpy(&pageData_[offset], &rightPageNumber, sizeof(int));
	setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() + 1);
	if (getLevelOfIndexNode() == 1) {
		LeafNode leafNode(fd_,indexHeader_, rightPageNumber);
		leafNode.setParentPageNumber(getPageNumber());
	} else {
		IndexNode indexNode(fd_,indexHeader_, rightPageNumber);
		indexNode.setParentOfIndexNode(getPageNumber());
	}
	return SUCCESS;
}
int IndexNode::insertAtTheFrontOfIndexNode(const char* key,
		int leftPageNumber) {
	int offset = IndexNode::getIndexNodeHeaderSize();
	char tempKeys[getNoOfKeysInIndexNode()][indexHeader_->getKeySize()];
	int tempPageNumbers[getNoOfKeysInIndexNode() + 1];
	int tempCount = 0;
	for (int i = 0; i < getNoOfKeysInIndexNode(); i++) {
		memcpy(&tempPageNumbers[tempCount], &pageData_[offset], sizeof(int));
		offset = offset + sizeof(int);
		memcpy(tempKeys[tempCount], &pageData_[offset],
				indexHeader_->getKeySize());
		offset = offset + indexHeader_->getKeySize();
		tempCount++;
	}
	memcpy(&tempPageNumbers[tempCount], &pageData_[offset], sizeof(int));
	offset = IndexNode::getIndexNodeHeaderSize();
	memcpy(&pageData_[offset], &leftPageNumber, sizeof(int));
	offset = offset + sizeof(int);
	memcpy(&pageData_[offset], key, indexHeader_->getKeySize());
	offset = offset + indexHeader_->getKeySize();
	for (int i = 0; i < tempCount; i++) {
		memcpy(&pageData_[offset], &tempPageNumbers[i], sizeof(int));
		offset = offset + sizeof(int);
		memcpy(&pageData_[offset], tempKeys[i], indexHeader_->getKeySize());
		offset = offset + indexHeader_->getKeySize();
	}
	memcpy(&pageData_[offset], &tempPageNumbers[tempCount], sizeof(int));
	setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() + 1);
	if (getLevelOfIndexNode() == 1) {
		LeafNode leafNode(fd_,indexHeader_, leftPageNumber);
		leafNode.setParentPageNumber(getPageNumber());
	} else {
		IndexNode indexNode(fd_,indexHeader_, leftPageNumber);
		indexNode.setParentOfIndexNode(getPageNumber());
	}
	bufMgr_->writePage(fd_,pagenumber_, pageData_);
	return SUCCESS;
}
int IndexNode::deleteKeyFromIndexNode(const char* key, bool flag,
		std::vector<int> &deletedPages) {
	int offset = IndexNode::getIndexNodeHeaderSize();
	char tempKey[indexHeader_->getKeySize()];
	int leftPageNumber, rightPageNumber;
	int i;
	for (i = 0; i < getNoOfKeysInIndexNode(); i++) {
		memcpy(&leftPageNumber, &pageData_[offset], sizeof(int));
		offset = offset + sizeof(int);
		memcpy(tempKey, &pageData_[offset], indexHeader_->getKeySize());
		offset = offset + indexHeader_->getKeySize();
		memcpy(&rightPageNumber, &pageData_[offset], sizeof(int));
		//		DEBUG_B("DATA "<<leftPageNumber<<" "<<tempKey<<"  "<<rightPageNumber)
		//		dummyKeyCompare(key, tempKey)
		if (BPlusTreeUtil::keyCompare(key, tempKey, indexHeader_) == 0) {
			break;
		}
	}
	char tempKeys[indexHeader_->getFanout()][indexHeader_->getKeySize()];
	int tempPageNumbers[indexHeader_->getFanout() + 1];
	int tempCount = 0;
	int newOffset = offset;
	for (int j = i + 1; j < getNoOfKeysInIndexNode(); j++) {
		memcpy(&tempPageNumbers[tempCount], &pageData_[newOffset], sizeof(int));
		newOffset = newOffset + sizeof(int);
		memcpy(&tempKeys[tempCount], &pageData_[newOffset],
				indexHeader_->getKeySize());
		newOffset = newOffset + indexHeader_->getKeySize();
		tempCount++;
	}
	memcpy(&tempPageNumbers[tempCount], &pageData_[newOffset], sizeof(int));
	if (flag == true) {
		offset = offset - indexHeader_->getKeySize() - sizeof(int);
		int entered = 0;
		for (int i = 0; i < tempCount; i++) {
			memcpy(&pageData_[offset], &tempPageNumbers[i], sizeof(int));
			offset = offset + sizeof(int);
			memcpy(&pageData_[offset], &tempKeys[i], indexHeader_->getKeySize());
			offset = offset + indexHeader_->getKeySize();
			entered = 1;
			if (i == 0) {
				if (getLevelOfIndexNode() == 1) {
					LeafNode leafNode(fd_,indexHeader_, leftPageNumber);
					LeafNode newLeafNode(fd_,indexHeader_, tempPageNumbers[i]);
					newLeafNode.setLeftPageNumber(leafNode.getLeftPageNumber());
					if (leafNode.getLeftPageNumber() != -1) {
						LeafNode oldRightNode(fd_,indexHeader_,
								leafNode.getLeftPageNumber());
						oldRightNode.setRightPageNumber(
								newLeafNode.getPageNumber());
					}
				} else {
					IndexNode indexNode(fd_,indexHeader_, leftPageNumber);
					IndexNode newIndexNode(fd_,indexHeader_, tempPageNumbers[i]);
					newIndexNode.setLeftPageNumberOfIndexNode(
							indexNode.getLeftPageNumberOfIndexNode());
					if (indexNode.getLeftPageNumberOfIndexNode() != -1) {
						IndexNode oldRightIndexNode(fd_,indexHeader_,
								indexNode.getLeftPageNumberOfIndexNode());
						oldRightIndexNode.setRightPageNumber(
								newIndexNode.getPageNumber());
					}
				}
			}
		}
		memcpy(&pageData_[offset], &tempPageNumbers[tempCount], sizeof(int));
		setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() - 1);
		if (entered == 0) {
			if (getLevelOfIndexNode() == 1) {
				int newPageNumber = tempPageNumbers[tempCount];
				LeafNode leafNode(fd_,indexHeader_, leftPageNumber);
				LeafNode newLeafNode(fd_,indexHeader_, newPageNumber);
				newLeafNode.setLeftPageNumber(leafNode.getLeftPageNumber());
				if (leafNode.getLeftPageNumber() != -1) {
					LeafNode oldRightNode(fd_,indexHeader_,
							leafNode.getLeftPageNumber());
					oldRightNode.setRightPageNumber(newLeafNode.getPageNumber());
				}

			} else {
				IndexNode indexNode(fd_,indexHeader_, leftPageNumber);
				IndexNode newIndexNode(fd_,indexHeader_, tempPageNumbers[tempCount]);
				newIndexNode.setLeftPageNumberOfIndexNode(
						indexNode.getLeftPageNumberOfIndexNode());
				if (indexNode.getLeftPageNumberOfIndexNode() != -1) {
					IndexNode oldRightIndexNode(fd_,indexHeader_,
							indexNode.getLeftPageNumberOfIndexNode());
					oldRightIndexNode.setRightPageNumber(
							newIndexNode.getPageNumber());
				}
			}
		}
	}
	else {
		if (tempCount == 0) {
			setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() - 1);
			if (getLevelOfIndexNode() == 1) {
				int newLastPageNumber = getLastPageNumberPresentInIndexNode();
				tempPageNumbers[tempCount] = newLastPageNumber;
				LeafNode leafNode(fd_,indexHeader_, rightPageNumber);
				LeafNode newLeafNode(fd_,indexHeader_, newLastPageNumber);
				newLeafNode.setRightPageNumber(leafNode.getRightPageNumber());
				if (leafNode.getRightPageNumber() != -1) {
					LeafNode rightLeafPage(fd_,indexHeader_,
							leafNode.getRightPageNumber());
					rightLeafPage.setLeftPageNumber(newLastPageNumber);
				}
			} else {
				IndexNode indexNode(fd_,indexHeader_, rightPageNumber);
				int newLastPageNumber = getLastPageNumberPresentInIndexNode();
				tempPageNumbers[tempCount] = newLastPageNumber;
				IndexNode newIndexNode(fd_,indexHeader_, newLastPageNumber);
				newIndexNode.setRightPageNumber(indexNode.getRightPageNumber());
				if (getNoOfKeysInIndexNode() == 0) {
					tempPageNumbers[tempCount] = newLastPageNumber;
				}
				if (indexNode.getRightPageNumber() != -1) {
					IndexNode rightIndexNode(fd_,indexHeader_,
							indexNode.getRightPageNumber());
					rightIndexNode.setLeftPageNumberOfIndexNode(
							newLastPageNumber);
				}
			}
		} else {
			offset = offset - indexHeader_->getKeySize() - sizeof(int);
			memcpy(&tempPageNumbers[0], &pageData_[offset], sizeof(int));
			for (int i = 0; i < tempCount; i++) {
				memcpy(&pageData_[offset], &tempPageNumbers[i], sizeof(int));
				offset = offset + sizeof(int);
				memcpy(&pageData_[offset], &tempKeys[i],
						indexHeader_->getKeySize());
				offset = offset + indexHeader_->getKeySize();
				if (getLevelOfIndexNode() == 1) {
					if (i != 0) {
						LeafNode leafNode(fd_,indexHeader_, tempPageNumbers[i - 1]);
						LeafNode newLeafNode(fd_,indexHeader_, tempPageNumbers[i]);
						newLeafNode.setLeftPageNumber(leafNode.getPageNumber());
						newLeafNode.setRightPageNumber(tempPageNumbers[i + 1]);
					} else {
						LeafNode leafNode(fd_,indexHeader_, tempPageNumbers[i]);
						leafNode.setRightPageNumber(tempPageNumbers[i + 1]);
					}
				} else {
					if (i != 0) {
						IndexNode indexNode(fd_,indexHeader_,
								tempPageNumbers[i - 1]);
						IndexNode
								newIndexNode(fd_,indexHeader_, tempPageNumbers[i]);
						newIndexNode.setLeftPageNumberOfIndexNode(
								indexNode.getPageNumber());
						newIndexNode.setRightPageNumber(tempPageNumbers[i + 1]);
					} else {
						IndexNode indexNode(fd_,indexHeader_, tempPageNumbers[i]);
						indexNode.setRightPageNumber(tempPageNumbers[i + 1]);
					}
				}
			}
			memcpy(&pageData_[offset], &tempPageNumbers[tempCount], sizeof(int));
			setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() - 1);
			if (getLevelOfIndexNode() == 1) {
				LeafNode leafNode(fd_,indexHeader_, tempPageNumbers[tempCount]);
				leafNode.setLeftPageNumber(tempPageNumbers[tempCount - 1]);
			} else {
				IndexNode indexNode(fd_,indexHeader_, tempPageNumbers[tempCount]);
				indexNode.setLeftPageNumberOfIndexNode(
						tempPageNumbers[tempCount - 1]);
			}

			//			DEBUG_B("********************FLAG FALSE ENDS HERE**************************************")
		}
	}
	if (getNoOfKeysInIndexNode() == 0) {
		deletedPages.push_back(getPageNumber());
		if (getLevelOfIndexNode() == 1) {
			indexHeader_->setRootPageNumber(tempPageNumbers[tempCount]);
			LeafNode leafNode(fd_,indexHeader_, tempPageNumbers[tempCount]);
			leafNode.setParentPageNumber(-1);
			indexHeader_->setHeightOfTree(0);
		} else {
			indexHeader_->setRootPageNumber(tempPageNumbers[tempCount]);
			IndexNode indexNode(fd_,indexHeader_, tempPageNumbers[tempCount]);
			indexNode.setParentOfIndexNode(-1);
			indexHeader_->setHeightOfTree(indexNode.getLevelOfIndexNode());
		}
		return SUCCESS;
	}
	//TILL NOE DELETION DONE
	//FROM HERE CHECKING STARTS WHETHER TO ROTATE OR MERGING OR NOTHING
	if (getNoOfKeysInIndexNode() >= ceil(indexHeader_->getFanout() / 2)) {
	} else {
		//		indexNodeOnlyDisplay();
		int rightPage = -1;
		int leftPage = -1;
		if (getParentOfIndexNode() != -1) {
			IndexNode parentNode(fd_,indexHeader_, getParentOfIndexNode());
			parentNode.getSiblings(getPageNumber(), leftPage, rightPage);
			//			DEBUG_B("SIBLINGS "<<leftSibling<<"  "<<rightSibling)
		}

		if (rightPage != -1) {
			//rotate from right to left
			IndexNode rightIndexNode(fd_,indexHeader_, rightPage);
			if ((rightIndexNode.getNoOfKeysInIndexNode() - 1) >= ceil(
					indexHeader_->getFanout() / 2)) {
				char seperatingKey[indexHeader_->getKeySize()];
				char firstKeyPresentOnRightPage[indexHeader_->getKeySize()];
				rightIndexNode.getFirstKeyPresentInIndexNode(
						firstKeyPresentOnRightPage);
				//				DEBUG_B("first key "<<firstKeyPresentOnRightPage)
				int rotatingPageNumber;
				rotatingPageNumber
						= rightIndexNode.getFirstPageNumberPresentInIndexNode();
				//				DEBUG_B("right page number "<<rotatingPageNumber)
				if (getParentOfIndexNode() != -1) {
					IndexNode parentIndexNode(fd_,indexHeader_,
							getParentOfIndexNode());
					parentIndexNode.getSeperatingKey(getPageNumber(),
							rightPage, seperatingKey);
					//					DEBUG_B("seperating key "<<seperatingKey)
					//pushing parent key down to child index node(current page) along with left most page in right index page
					insertAtTheEndOfIndexNode(seperatingKey, rotatingPageNumber);
					if (getLevelOfIndexNode() == 1) {
						LeafNode rotateLeafNode(fd_,indexHeader_,
								rotatingPageNumber);
						rotateLeafNode.setParentPageNumber(getPageNumber());
					} else {
						IndexNode rotateIndexNode(fd_,indexHeader_,
								rotatingPageNumber);
						rotateIndexNode.setParentOfIndexNode(getPageNumber());
					}
					//pushing leftmost key in right node to parent node
					parentIndexNode.replaceKey(seperatingKey,
							firstKeyPresentOnRightPage);
					//deleteing first key after it is moved to parent and its left page
					rightIndexNode.deleteFirstKeyFromIndexNode();
				}
			} else if (leftPage != -1) {
				//if left page is available
				//				DEBUG_B("I AM HERE in left page to rotate")
				//				DEBUG_B("DO ROTATION WITH LEFT PAGE ")
				IndexNode leftIndexNode(fd_,indexHeader_, leftPage);
				if ((leftIndexNode.getNoOfKeysInIndexNode() - 1) >= ceil(
						indexHeader_->getFanout() / 2)) {
					//rotate from left to right
					char seperatingKey[indexHeader_->getKeySize()];
					char lastKeyInLeftPage[indexHeader_->getKeySize()];
					leftIndexNode.getLastKeyPresentInIndexNode(
							lastKeyInLeftPage);
					int shiftingPageNumber =
							leftIndexNode.getLastPageNumberPresentInIndexNode();
					//					DEBUG_B("last key "<<lastKeyInLeftPage<<" last page no "<<shiftingPageNumber)
					if (getParentOfIndexNode() != -1) {
						IndexNode parentNode(fd_,indexHeader_,
								getParentOfIndexNode());
						//						parentNode.indexNodeOnlyDisplay();
						parentNode.getSeperatingKey(leftPage, getPageNumber(),
								seperatingKey);
						//						DEBUG_B("seperating key "<<seperatingKey)
						parentNode.replaceKey(seperatingKey, lastKeyInLeftPage);
					}
					insertAtTheFrontOfIndexNode(seperatingKey,
							shiftingPageNumber);
					if (getLevelOfIndexNode() == 1) {
						LeafNode rotateLeafNode(fd_,indexHeader_,
								shiftingPageNumber);
						rotateLeafNode.setParentPageNumber(getPageNumber());
					} else {
						IndexNode rotateIndexNode(fd_,indexHeader_,
								shiftingPageNumber);
						rotateIndexNode.setParentOfIndexNode(getPageNumber());
					}
					leftIndexNode.deleteLastKeyFromIndexNode();
					//					DEBUG_B("ROTATION ENDS HERE DELETION ENDS HERE")
				} else {
					//					DEBUG_B(" MERGING HERE first")
					//					DEBUG_B("MERGING HERE IF RIGHT AND LEFT PAGES DOES NOT HAVE ENOUGH NUMEBR OF KEY TO ROTATE")
					deletedPages.push_back(getPageNumber());
					//					DEBUG_B("curr "<<getPageNumber())
					//					DEBUG_B("left "<<getLeftPageNumberOfIndexNode())
					//					DEBUG_B("right "<<getRightPageNumber())
					char seperatingKey[indexHeader_->getKeySize()];
					if (getParentOfIndexNode() != -1) {
						IndexNode parentNode(fd_,indexHeader_,
								getParentOfIndexNode());
						parentNode.getSeperatingKey(getPageNumber(),
								getRightPageNumber(), seperatingKey);
					}
					//					DEBUG_B("seperating key "<<seperatingKey);
					int
							attachedPageNumber =
									rightIndexNode.getFirstPageNumberPresentInIndexNode();
					//					DEBUG_B("attched number "<<attachedPageNumber)
					char
							tempKeys[getNoOfKeysInIndexNode() + 1][indexHeader_->getKeySize()];
					int tempPageNumbers[getNoOfKeysInIndexNode() + 1];
					int tempCount = 0;
					int offset = IndexNode::getIndexNodeHeaderSize();
					for (int i = 0; i < getNoOfKeysInIndexNode(); i++) {
						memcpy(&tempPageNumbers[tempCount], &pageData_[offset],
								sizeof(int));
						offset += sizeof(int);
						memcpy(tempKeys[tempCount], &pageData_[offset],
								indexHeader_->getKeySize());
						offset = offset + indexHeader_->getKeySize();
						tempCount++;
					}
					memcpy(&tempPageNumbers[tempCount], &pageData_[offset],
							sizeof(int));
					memcpy(tempKeys[tempCount], seperatingKey,
							indexHeader_->getKeySize());
					for (int i = tempCount; i >= 0; i--) {
						//							DEBUG_B("values "<<tempPageNumbers[i]<<"  "<<tempKeys[i]<<"  "<<sendingNumber)
						rightIndexNode.insertAtTheFrontOfIndexNode(tempKeys[i],
								tempPageNumbers[i]);
					}
					if (getParentOfIndexNode() != -1) {
						IndexNode parentNode(fd_,indexHeader_,
								getParentOfIndexNode());
						parentNode.deleteKeyFromIndexNode(seperatingKey, true,
								deletedPages);
					}
					//					DEBUG_B("MERGING IS OVER ")
				}

				//				DEBUG_B("IT ENDS HERE*********************************************")
			} else {
				//do merging with right page here
				//				DEBUG_B("DO MERGE WITH RIGHT PAGE second")
				//				DEBUG_B("MERGE HERE IF RIGHT PAGE EXISTED AND LEFT PAGE NOT EXISTED SO MERGE WITH RIGHT PAGE")
				//				DEBUG_B("MERGING STARTS ********************************************************************")
				deletedPages.push_back(getPageNumber());
				//				DEBUG_B("curr "<<getPageNumber())
				//				DEBUG_B("left "<<getLeftPageNumberOfIndexNode())
				//				DEBUG_B("right "<<getRightPageNumber())
				char seperatingKey[indexHeader_->getKeySize()];
				if (getParentOfIndexNode() != -1) {
					IndexNode parentNode(fd_,indexHeader_, getParentOfIndexNode());
					parentNode.getSeperatingKey(getPageNumber(),
							getRightPageNumber(), seperatingKey);
				}
				//				DEBUG_B("seperating key "<<seperatingKey);
				int attachedPageNumber =
						rightIndexNode.getFirstPageNumberPresentInIndexNode();
				//				DEBUG_B("attched number "<<attachedPageNumber)
				char
						tempKeys[getNoOfKeysInIndexNode() + 1][indexHeader_->getKeySize()];
				int tempPageNumbers[getNoOfKeysInIndexNode() + 1];
				int tempCount = 0;
				int offset = IndexNode::getIndexNodeHeaderSize();
				for (int i = 0; i < getNoOfKeysInIndexNode(); i++) {
					memcpy(&tempPageNumbers[tempCount], &pageData_[offset],
							sizeof(int));
					offset += sizeof(int);
					memcpy(tempKeys[tempCount], &pageData_[offset],
							indexHeader_->getKeySize());
					offset = offset + indexHeader_->getKeySize();
					tempCount++;
				}
				memcpy(&tempPageNumbers[tempCount], &pageData_[offset],
						sizeof(int));
				memcpy(tempKeys[tempCount], seperatingKey,
						indexHeader_->getKeySize());
				for (int i = tempCount; i >= 0; i--) {
					//							DEBUG_B("values "<<tempPageNumbers[i]<<"  "<<tempKeys[i]<<"  "<<sendingNumber)
					rightIndexNode.insertAtTheFrontOfIndexNode(tempKeys[i],
							tempPageNumbers[i]);
				}
				if (getParentOfIndexNode() != -1) {
					IndexNode parentNode(fd_,indexHeader_, getParentOfIndexNode());
					parentNode.deleteKeyFromIndexNode(seperatingKey, true,
							deletedPages);
				}
				//				DEBUG_B("MERGING IS OVER ")

				//				DEBUG_B("MERGING ENDS ***********************************************************************")
			}

		} else if (leftPage != -1) {
			IndexNode leftIndexNode(fd_,indexHeader_, leftPage);
			if ((leftIndexNode.getNoOfKeysInIndexNode() - 1) >= ceil(
					indexHeader_->getFanout() / 2)) {
				//rotate from left to right
				char seperatingKey[indexHeader_->getKeySize()];
				char lastKeyInLeftPage[indexHeader_->getKeySize()];
				leftIndexNode.getLastKeyPresentInIndexNode(lastKeyInLeftPage);
				int shiftingPageNumber =
						leftIndexNode.getLastPageNumberPresentInIndexNode();
				//				DEBUG_B("last key "<<lastKeyInLeftPage<<" last page no "<<shiftingPageNumber)
				if (getParentOfIndexNode() != -1) {
					IndexNode parentNode(fd_,indexHeader_, getParentOfIndexNode());
					parentNode.getSeperatingKey(leftPage, getPageNumber(),
							seperatingKey);
					//					DEBUG_B("seperating key "<<seperatingKey)
					parentNode.replaceKey(seperatingKey, lastKeyInLeftPage);
				}
				insertAtTheFrontOfIndexNode(seperatingKey, shiftingPageNumber);
				if (getLevelOfIndexNode() == 1) {
					LeafNode rotateLeafNode(fd_,indexHeader_, shiftingPageNumber);
					rotateLeafNode.setParentPageNumber(getPageNumber());
				} else {
					IndexNode rotateIndexNode(fd_,indexHeader_, shiftingPageNumber);
					rotateIndexNode.setParentOfIndexNode(getPageNumber());
				}
				leftIndexNode.deleteLastKeyFromIndexNode();
				//				DEBUG_B("ROTATION ENDS HERE DELETION ENDS HERE")
			} else {
				//				DEBUG_B(" MERGING WITH LEFT PAGE HERE")
				//				DEBUG_B("MERGING HERE WITH LEFT PAGE NUMBER ")
				deletedPages.push_back(getPageNumber());
				//				DEBUG_B("curr "<<getPageNumber())
				//				DEBUG_B("left "<<getLeftPageNumberOfIndexNode())
				char seperatingKey[indexHeader_->getKeySize()];
				if (getParentOfIndexNode() != -1) {
					IndexNode parentNode(fd_,indexHeader_, getParentOfIndexNode());
					parentNode.getSeperatingKey(getLeftPageNumberOfIndexNode(),
							getPageNumber(), seperatingKey);
				}
				//				DEBUG_B("seperating key "<<seperatingKey);
				int attachedPageNumber = getFirstPageNumberPresentInIndexNode();
				char
						tempKeys[getNoOfKeysInIndexNode() + 1][indexHeader_->getKeySize()];
				int tempPageNumbers[getNoOfKeysInIndexNode() + 1];
				int tempCount = 0;
				int offset = IndexNode::getIndexNodeHeaderSize();
				memcpy(tempKeys[tempCount], seperatingKey,
						indexHeader_->getKeySize());
				for (int i = 0; i < getNoOfKeysInIndexNode(); i++) {
					memcpy(&tempPageNumbers[tempCount], &pageData_[offset],
							sizeof(int));
					offset = offset + sizeof(int);
					memcpy(tempKeys[tempCount], &pageData_[offset],
							indexHeader_->getKeySize());
					offset = offset + indexHeader_->getKeySize();
					tempCount++;
				}
				memcpy(&tempPageNumbers[tempCount], &pageData_[offset],
						sizeof(int));
				//				leftIndexNode.indexNodeOnlyDisplay();
				//				DEBUG_B("values "<<seperatingKey<<"  "<<tempPageNumbers[0])
				leftIndexNode.insertAtTheEndOfIndexNode(seperatingKey,
						tempPageNumbers[0]);
				for (int i = 0; i < tempCount; i++) {
					//					DEBUG_B("values "<<tempKeys[i]<<"  "<<tempPageNumbers[i+1])
					leftIndexNode.insertAtTheEndOfIndexNode(tempKeys[i],
							tempPageNumbers[i + 1]);
				}
				if (getParentOfIndexNode() != -1) {
					IndexNode parentNode(fd_,indexHeader_, getParentOfIndexNode());
					parentNode.deleteKeyFromIndexNode(seperatingKey, false,
							deletedPages);
				}
				//				DEBUG_B("MERGING IS OVER ")

				//				DEBUG_B(" I AM HERE IF I AM CORRECT")
				//				int x;
				//				cin >> x;
			}
		}
	}
	bufMgr_->writePage(fd_,pagenumber_, pageData_);

	return SUCCESS;
}
void IndexNode::deleteFirstKeyFromIndexNode() {
	int offset = IndexNode::getIndexNodeHeaderSize();
	char tempKeys[getNoOfKeysInIndexNode() - 1][indexHeader_->getKeySize()];
	int tempPageNumbers[getNoOfKeysInIndexNode()];
	int tempCount = 0;
	offset = offset + sizeof(int) + indexHeader_->getKeySize();
	for (int i = 1; i < getNoOfKeysInIndexNode(); i++) {
		memcpy(&tempPageNumbers[tempCount], &pageData_[offset], sizeof(int));
		offset = offset + sizeof(int);
		memcpy(&tempKeys[tempCount], &pageData_[offset],
				indexHeader_->getKeySize());
		offset = offset + indexHeader_->getKeySize();
		tempCount++;
	}
	memcpy(&tempPageNumbers[tempCount], &pageData_[offset], sizeof(int));
	offset = IndexNode::getIndexNodeHeaderSize();
	for (int i = 0; i < tempCount; i++) {
		memcpy(&pageData_[offset], &tempPageNumbers[i], sizeof(int));
		offset += sizeof(int);
		memcpy(&pageData_[offset], tempKeys[i], indexHeader_->getKeySize());
		offset += indexHeader_->getKeySize();
	}
	memcpy(&pageData_[offset], &tempPageNumbers[tempCount], sizeof(int));
	setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() - 1);
	bufMgr_->writePage(fd_,pagenumber_, pageData_);
}
void IndexNode::deleteLastKeyFromIndexNode() {
	setNoOfKeysInIndexNode(getNoOfKeysInIndexNode() - 1);
	//if possible delete all page numbers
}
int IndexNode::isKeyFound(char* key) {
	int offset = IndexNode::getIndexNodeHeaderSize();
	offset = offset + sizeof(int);
	char temp[indexHeader_->getKeySize()];
	for (int i = 0; i < getNoOfKeysInIndexNode(); i++) {
		memcpy(temp, &pageData_[offset], indexHeader_->getKeySize());
		//		dummyKeyCompare(temp, key)
		if (BPlusTreeUtil::keyCompare(temp, key, indexHeader_) == 0)
			return 0;
		offset = indexHeader_->getKeySize() + sizeof(int);
	}
	return 1;
}
int IndexNode::replaceKey(const char* oldKey, const char* newKey) {
	int offset = IndexNode::getIndexNodeHeaderSize();
	//	DEBUG_B("ITS PAGE NUMBER FOR REPLACING"<<getPageNumber())
	//	cout<<" given keys "<<oldKey<<"  "<<newKey<<endl;
	offset = offset + sizeof(int);
	char temp[indexHeader_->getKeySize()];
	int found = 0;
	//	cout<<" num of keys "<<getNoOfKeysInIndexNode()<<endl;
	for (int i = 0; i < getNoOfKeysInIndexNode(); i++) {
		memcpy(temp, &pageData_[offset], indexHeader_->getKeySize());
		//		DEBUG_B("KEY COMPARE "<<temp<<"  "<<oldKey<<"  "<<i)
		//		dummyKeyCompare(temp, oldKey)
		if (BPlusTreeUtil::keyCompare(temp, oldKey, indexHeader_) == 0) {
			memcpy(&pageData_[offset], newKey, indexHeader_->getKeySize());
			found = 1;
			break;
		}
		offset += indexHeader_->getKeySize() + sizeof(int);
	}
	if (found == 0) {
		if (indexHeader_->getHeightOfTree() >= getLevelOfIndexNode()
				&& getParentOfIndexNode() != -1) {
			IndexNode indexNode(fd_,indexHeader_, getParentOfIndexNode());
			indexNode.replaceKey(oldKey, newKey);
		}
	}
	bufMgr_->writePage(fd_,pagenumber_, pageData_);
	return SUCCESS;
}

int IndexNode::dummyKeyCompare(char* key1, char* key2) {
	return strcmp(key1, key2);
}
int IndexNode::replaceKeyPreviousToPageNumber(int pageNumber,
		const char *oldKey, const char *newKey) {
	int offset = IndexNode::getIndexNodeHeaderSize();
	int leftPage;
	char tempKey[indexHeader_->getKeySize()];
	for (int i = 0; i < getNoOfKeysInIndexNode(); i++) {
		memcpy(&leftPage, &pageData_[offset], sizeof(int));
		offset = offset + sizeof(int);
		memcpy(tempKey, &pageData_[offset], indexHeader_->getKeySize());
		offset += indexHeader_->getKeySize();
		if (leftPage == pageNumber) {
			//			dummyKeyCompare(tempKey, oldKey)

			if (BPlusTreeUtil::keyCompare(tempKey, oldKey, indexHeader_) == 0) {
				offset = offset - indexHeader_->getKeySize();
				memcpy(&pageData_[offset], newKey, indexHeader_->getKeySize());
				return SUCCESS;
			}
		}
	}
	bufMgr_->writePage(fd_,pagenumber_, pageData_);
	return SUCCESS;
}
int IndexNode::searchInIndexNode(const char* key) {
	int offset = IndexNode::getIndexNodeHeaderSize();
	char tempKey[indexHeader_->getKeySize()];
	//bufMgr_->commitCache();
	//bufMgr_->hexDump(fd_,1);
	//bufMgr_->hexDump(fd_,6);
	int leftPageNumber, rightPageNumber;
	//cout <<  "number of keys :"<<indexHeader_->getNoOfKeys()<<endl;
	for (int i = 0; i < indexNodePageHeader_.noOfKeys; i++) {
		memcpy(&leftPageNumber, &pageData_[offset], sizeof(int));
		//cout << "left page number :"<< leftPageNumber<<endl;
		offset = offset + sizeof(int);
		memcpy(tempKey, &pageData_[offset], indexHeader_->getKeySize());
		offset = offset + indexHeader_->getKeySize();
		memcpy(&rightPageNumber, &pageData_[offset], sizeof(int));
		//		dummyKeyCompare(tempKey, key)
		//cout << "left:"<< leftPageNumber << "right : "<<rightPageNumber<<endl;
		//cout << "tempKey :"<<tempKey << "key :"<<key <<endl;
		int compValue = BPlusTreeUtil::keyCompare(tempKey, key, indexHeader_);
		//		DEBUG_B(" temp key "<<tempKey<<" new key "<<key)
		//		DEBUG_B("left page number "<<leftPageNumber)
		//		DEBUG_B("comparision return value "<<compValue<<endl)
		//cout << "comp value :"<<compValue<<endl;
		if (compValue == 0)
			return rightPageNumber;
		if (compValue == 1)
			return leftPageNumber;
		//DEBUG_B("found left page Number "<<leftPageNumber);
	}
	memcpy(&rightPageNumber, &pageData_[offset], sizeof(int));
	offset = offset + sizeof(int);
	return rightPageNumber;
}
void IndexNode::getSeperatingKey(int leftPage, int rightPage, char *key) {
	int offset = IndexNode::getIndexNodeHeaderSize();
	int lpno, rpno;
	char temp[indexHeader_->getKeySize()];
	for (int i = 0; i < getNoOfKeysInIndexNode(); i++) {
		memcpy(&lpno, &pageData_[offset], sizeof(int));
		offset = offset + sizeof(int);
		memcpy(temp, &pageData_[offset], indexHeader_->getKeySize());
		offset = offset + indexHeader_->getKeySize();
		memcpy(&rpno, &pageData_[offset], sizeof(int));
		if (leftPage == lpno && rightPage == rpno) {
			memcpy(key, temp, indexHeader_->getKeySize());
			break;
		}
	}
}
int IndexNode::getLevelOfIndexNode() {
	memcpy(&indexNodePageHeader_, pageData_, sizeof(IndexNodePageHeaderStruct));
	return indexNodePageHeader_.level;
}
void IndexNode::setLevelOfIndexNode(int level) {
	indexNodePageHeader_.level = level;
	memcpy(pageData_, &indexNodePageHeader_, sizeof(IndexNodePageHeaderStruct));
	bufMgr_->writePage(fd_,pagenumber_, pageData_);
}
int IndexNode::getNoOfKeysInIndexNode() {
	memcpy(&indexNodePageHeader_, pageData_, sizeof(IndexNodePageHeaderStruct));
	return indexNodePageHeader_.noOfKeys;
}
void IndexNode::setNoOfKeysInIndexNode(int noOfKeys) {
	indexNodePageHeader_.noOfKeys = noOfKeys;
	memcpy(pageData_, &indexNodePageHeader_, sizeof(IndexNodePageHeaderStruct));
	bufMgr_->writePage(fd_,pagenumber_, pageData_);
}
int IndexNode::getParentOfIndexNode() {
	memcpy(&indexNodePageHeader_, pageData_, sizeof(IndexNodePageHeaderStruct));
	return indexNodePageHeader_.parentPageNumber;
}
void IndexNode::setParentOfIndexNode(int parentPageNumber) {
	indexNodePageHeader_.parentPageNumber = parentPageNumber;
	memcpy(pageData_, &indexNodePageHeader_, sizeof(IndexNodePageHeaderStruct));
	bufMgr_->writePage(fd_,pagenumber_, pageData_);
}
int IndexNode::getLeftPageNumberOfIndexNode() {
	memcpy(&indexNodePageHeader_, pageData_, sizeof(IndexNodePageHeaderStruct));
	return indexNodePageHeader_.leftPageNumber;
}
void IndexNode::setLeftPageNumberOfIndexNode(int leftPageNumber) {
	indexNodePageHeader_.leftPageNumber = leftPageNumber;
	memcpy(pageData_, &indexNodePageHeader_, sizeof(IndexNodePageHeaderStruct));
	bufMgr_->writePage(fd_,pagenumber_, pageData_);
}
int IndexNode::getRightPageNumber() {
	memcpy(&indexNodePageHeader_, pageData_, sizeof(IndexNodePageHeaderStruct));
	return indexNodePageHeader_.rightPageNumber;
}
void IndexNode::setRightPageNumber(int rightPageNumber) {
	indexNodePageHeader_.rightPageNumber = rightPageNumber;
	memcpy(pageData_, &indexNodePageHeader_, sizeof(IndexNodePageHeaderStruct));
	bufMgr_->writePage(fd_,pagenumber_, pageData_);
}
int IndexNode::getPageNumber() {
	return indexNodePageHeader_.generalPageHeaderStruct.pageNumber;
}
int IndexNode::getPageType() {
	return indexNodePageHeader_.generalPageHeaderStruct.pageType;
}
void IndexNode::getFirstKeyPresentInIndexNode(char* key) {
	int offset = IndexNode::getIndexNodeHeaderSize();
	offset = offset + sizeof(int);
	memcpy(key, &pageData_[offset], indexHeader_->getKeySize());
}
void IndexNode::getLastKeyPresentInIndexNode(char* key) {
	int offset = IndexNode::getIndexNodeHeaderSize();
	offset = offset + (getNoOfKeysInIndexNode() * (sizeof(int)
			+ indexHeader_->getKeySize()));
	offset = offset - indexHeader_->getKeySize();
	memcpy(key, &pageData_[offset], indexHeader_->getKeySize());
}
int IndexNode::getFirstPageNumberPresentInIndexNode() {
	int offset = IndexNode::getIndexNodeHeaderSize();
	int pageNumber;
	memcpy(&pageNumber, &pageData_[offset], sizeof(int));
	return pageNumber;
}
int IndexNode::getLastPageNumberPresentInIndexNode() {
	int offset = IndexNode::getIndexNodeHeaderSize();
	offset = offset + indexNodePageHeader_.noOfKeys * (sizeof(int)
			+ indexHeader_->getKeySize());
	int pageNumber;
	memcpy(&pageNumber, &pageData_[offset], sizeof(int));
	return pageNumber;
}
int IndexNode::getIndexNodeHeaderSize() {
	return sizeof(IndexNodePageHeaderStruct);
}
int IndexNode::getSiblings(int givenPageNumber, int &leftSibling,
		int &rightSibling) {
	int offset = IndexNode::getIndexNodeHeaderSize();
	int currentLeftPageNumber = -1;
	int currentRightPageNumber = -1;
	int previousLeftPageNumber = -1;
	int found = 0;
	for (int i = 0; i < getNoOfKeysInIndexNode(); i++) {
		memcpy(&currentLeftPageNumber, &pageData_[offset], sizeof(int));
		offset = offset + sizeof(int) + indexHeader_->getKeySize();
		memcpy(&currentRightPageNumber, &pageData_[offset], sizeof(int));
		if (currentLeftPageNumber == givenPageNumber) {
			leftSibling = previousLeftPageNumber;
			rightSibling = currentRightPageNumber;
			return SUCCESS;
		}
		previousLeftPageNumber = currentLeftPageNumber;
	}
	leftSibling = previousLeftPageNumber;
	rightSibling = -1;
	return SUCCESS;

}
void IndexNode::getKeyNextToPageNumber(int pageNumber, char* key) {
	int offset = IndexNode::getIndexNodeHeaderSize();
	int pno;
	char temp[indexHeader_->getKeySize()];
	int i;
	for (i = 0; i < getNoOfKeysInIndexNode(); i++) {
		memcpy(&pno, &pageData_[offset], sizeof(int));
		offset = offset + sizeof(int);
		memcpy(temp, &pageData_[offset], indexHeader_->getKeySize());
		offset = offset + indexHeader_->getKeySize();
		if (pno == pageNumber) {
			memcpy(key, temp, indexHeader_->getKeySize());
			break;
		}
	}
	if (i == getNoOfKeysInIndexNode()) {
		memcpy(key, temp, indexHeader_->getKeySize());
	}
}
void IndexNode::getKeyPreviousToPageNumber(int pageNumber, char* key) {
	int offset = IndexNode::getIndexNodeHeaderSize();
	int pno;
	char temp[indexHeader_->getKeySize()];
	memcpy(&pno, &pageData_[offset], sizeof(int));
	offset = offset + sizeof(int);
	if (pno == pageNumber) {
		key = NULL;
	} else {
		for (int i = 0; i < getNoOfKeysInIndexNode(); i++) {
			memcpy(temp, &pageData_[offset], indexHeader_->getKeySize());
			offset = offset + indexHeader_->getKeySize();
			memcpy(&pno, &pageData_[offset], sizeof(int));
			offset = offset + sizeof(int);
			if (pno == pageNumber) {
				memcpy(key, temp, indexHeader_->getKeySize());
				break;
			}
		}
	}
}
int IndexNode::getPageNumberNextToGivenPageNumber(int givenPageNumber) {
	int offset = IndexNode::getIndexNodeHeaderSize();
	int pageno;
	int resultPageNo;
	for (int i = 0; i < getNoOfKeysInIndexNode(); i++) {
		memcpy(&pageno, &pageData_[offset], sizeof(int));
		offset = offset + sizeof(int) + indexHeader_->getKeySize();
		memcpy(&resultPageNo, &pageData_[offset], sizeof(int));
		if (pageno == givenPageNumber) {
			return pageno;
		}
	}
	return -1;
}
int IndexNode::getPageNumberPreviousToGivenPageNumber(int givenPageNumber) {
	int offset = IndexNode::getIndexNodeHeaderSize();
	int pageno, resultPageNo;
	for (int i = 0; i < getNoOfKeysInIndexNode(); i++) {
		memcpy(&pageno, &pageData_[offset], sizeof(int));
		offset = offset + sizeof(int) + indexHeader_->getKeySize();
		memcpy(&resultPageNo, &pageData_[offset], sizeof(int));
		if (resultPageNo == givenPageNumber) {
			return pageno;
		}
	}
	return -1;
}
void IndexNode::indexNodeOnlyDisplay() {
	int offset = IndexNode::getIndexNodeHeaderSize();
	char tp[indexHeader_->getKeySize()];
	int leftPageNumber, rightPageNumber;
	for (int i = 0; i < indexNodePageHeader_.noOfKeys; i++) {
		memcpy(&leftPageNumber, &pageData_[offset], sizeof(int));
		offset = offset + sizeof(int);
		memcpy(tp, &pageData_[offset], indexHeader_->getKeySize());
		offset = offset + indexHeader_->getKeySize();
		//		cout << leftPageNumber << "  " << tp << "   ";
	}
	memcpy(&rightPageNumber, &pageData_[offset], sizeof(int));
	//	cout << rightPageNumber << endl;
}
void IndexNode::display() {
	cout << "CURRENT INDEX PAGE NUMBER\t" << getPageNumber() << endl;
	cout << "THIS PARENT PARE NUMBER\t\t" << getParentOfIndexNode() << endl;
	cout << "LEFT PAGE NUMBER\t\t" << getLeftPageNumberOfIndexNode() << endl;
	cout << "RIGHT PAGE NUMBER\t\t" << getRightPageNumber() << endl;
	cout << "NO OF KEYS IN INDEX NODE\t" << indexNodePageHeader_.noOfKeys
			<< endl;
	cout << "LEVEL OF NODE\t\t\t" << getLevelOfIndexNode() << endl;
	int leftPageNumber;
	int rightPageNumber;
	char existingKey[indexHeader_->getKeySize()];
	int level = getLevelOfIndexNode();
	indexNodeOnlyDisplay();
	int offset = IndexNode::getIndexNodeHeaderSize();
	for (int i = 0; i < indexNodePageHeader_.noOfKeys; i++) {
		memcpy(&leftPageNumber, &pageData_[offset], sizeof(int));
		//		DEBUG_B("left page"<<leftPageNumber);
		offset = offset + sizeof(int);
		memcpy(existingKey, &pageData_[offset], indexHeader_->getKeySize());
		offset = offset + indexHeader_->getKeySize();
		//		DEBUG_B("KEY "<<existingKey);
		memcpy(&rightPageNumber, &pageData_[offset], sizeof(int));
		//		DEBUG_B(" right page "<<rightPageNumber)
		//		offset=offset+sizeof(int);
		cout << leftPageNumber << "  " << existingKey << "   "
				<< rightPageNumber << endl;
		if (level == 1) {
			LeafNode leafNode(fd_,indexHeader_, leftPageNumber);
			//			leafNode.display();
			cout << "----------NEXT LEAF PAGE -------------------------------"
					<< endl;
			LeafNode leafNode1(fd_,indexHeader_, rightPageNumber);
			leafNode1.display();
		} else {
			IndexNode indexNode(fd_,indexHeader_, leftPageNumber);
			indexNode.display();
			IndexNode indexNode1(fd_,indexHeader_, rightPageNumber);
			indexNode1.display();
		}

	}

	//			LeafNode leafNode1(indexHeader_,rightPageNumber);
	//	 		leafNode1.display();
}

void IndexNode::UIIndexNode() {
	//	cout << "\n I AM IN UI OF INDEX NODE " << endl;
	cout<<endl;
	cout << "\tCurrent Index Page Number ------------------------: "
			<< getPageNumber() << endl;
	cout << "\tCurrent Level of Index Page ----------------------: "
			<< getLevelOfIndexNode() << endl;
	cout << "\tParent page number -------------------------------: "
			<< getParentOfIndexNode() << endl;
	cout << "\tNumber of keys in Index Page ---------------------: "
			<< getNoOfKeysInIndexNode() << endl;
	cout
			<< "\t***********************DATA IN INDEX NODE **************************"
			<< endl;
	cout<<"\t";
	int offset = IndexNode::getIndexNodeHeaderSize();
	int leftPageNumber;
	char key[indexHeader_->getKeySize()];
	for (int i = 0; i < getNoOfKeysInIndexNode(); i++) {
		memcpy(&leftPageNumber, &pageData_[offset], sizeof(int));
		offset = offset + sizeof(int);
		memcpy(key, &pageData_[offset], indexHeader_->getKeySize());
		offset = offset + indexHeader_->getKeySize();
		cout << " [" << leftPageNumber << "]  ";
		BPlusTreeUtil::displayKey(key, indexHeader_);
	}
	memcpy(&leftPageNumber, &pageData_[offset], sizeof(int));
	cout << " [" << leftPageNumber << "]" << endl;
	cout
			<< "\t********************* END OF DATA IN INDEX NODE ******************** "
			<< endl;
	cout << "\tLeft Index Page Number ---------------------------:"
			<< getLeftPageNumberOfIndexNode() << endl;
	cout << "\tRight Index Page Number --------------------------:"
			<< getRightPageNumber() << endl;

}
void IndexNode::UIDisplayOfIndexNode(int numberOfTabs) {
	int offset = IndexNode::getIndexNodeHeaderSize();
	int pageNumbers[getNoOfKeysInIndexNode() + 1];
	char keys[getNoOfKeysInIndexNode()][indexHeader_->getKeySize()];
	for (int i = 0; i < getNoOfKeysInIndexNode(); i++) {
		memcpy(&pageNumbers[i], &pageData_[offset], sizeof(int));
		offset = offset + sizeof(int);
		memcpy(&keys[i], &pageData_[offset], indexHeader_->getKeySize());
		offset = offset + indexHeader_->getKeySize();
	}
	memcpy(&pageNumbers[getNoOfKeysInIndexNode()], &pageData_[offset],
			sizeof(int));
	for (int tab = 0; tab < numberOfTabs; tab++) {
		cout << "\t";
	}
	cout << "Index Page Number : " << getPageNumber() << endl;
	for (int tab = 0; tab < numberOfTabs; tab++) {
		cout << "\t";
	}

	cout << "Level of Index Node : " << getLevelOfIndexNode() << endl;
	for (int tab = 0; tab < numberOfTabs; tab++) {
		cout << "\t";
	}
	for (int i = 0; i < getNoOfKeysInIndexNode(); i++) {
		cout << "[" << pageNumbers[i] << "]" << "|";
		BPlusTreeUtil::displayKey(keys[i], indexHeader_);
		cout << "|";
	}
	cout << "[" << pageNumbers[getNoOfKeysInIndexNode()] << "]" << endl;
	int updateTabs = numberOfTabs + indexHeader_->getFanout();//getNoOfKeysInIndexNode();
	if (getLevelOfIndexNode() == 1) {
		for (int k2 = 0; k2 <= getNoOfKeysInIndexNode(); k2++) {
			LeafNode leafNode(fd_,indexHeader_, pageNumbers[k2]);
			leafNode.UIDisplayOfLeafNode(updateTabs);
		}
	} else {
		for (int k1 = 0; k1 <= getNoOfKeysInIndexNode(); k1++) {
			IndexNode indexNode(fd_,indexHeader_, pageNumbers[k1]);
			indexNode.UIDisplayOfIndexNode(updateTabs);
		}
	}
}
void IndexNode::deleteChilds(std::vector<int> &allPageNumbers) {
	int level = getLevelOfIndexNode();
	int offset = getIndexNodeHeaderSize();
	int pageNumber1;

	for (int i = 0; i < getNoOfKeysInIndexNode() + 1; i++) {
		memcpy(&pageNumber1, &pageData_[offset], sizeof(int));
		offset = offset + sizeof(int) + indexHeader_->getKeySize();
		if (level > 1) {
			//			cout<<"\n\tdelete index nodes : "<<pageNumber1<<endl;
			IndexNode indexNode(fd_,indexHeader_, pageNumber1);
			indexNode.deleteChilds(allPageNumbers);
			allPageNumbers.push_back(pageNumber1);
		}
		if (level == 1) {
			//			cout<<"\n\tdelete leaf nodes : "<<pageNumber1<<endl;
			allPageNumbers.push_back(pageNumber1);
		}
	}
}
void IndexNode::findPages(std::vector<int> &leafPages,
		std::vector<int> &indexPages) {
	int level = getLevelOfIndexNode();
	int offset = getIndexNodeHeaderSize();
	int pageNumber1;
	for (int i = 0; i < getNoOfKeysInIndexNode() + 1; i++) {
		memcpy(&pageNumber1, &pageData_[offset], sizeof(int));
		offset = offset + sizeof(int) + indexHeader_->getKeySize();
		if (level > 1) {
			IndexNode indexNode(fd_,indexHeader_, pageNumber1);
			indexNode.findPages(leafPages, indexPages);
			indexPages.push_back(pageNumber1);
		}
		if (level == 1) {
			leafPages.push_back(pageNumber1);
		}
	}
}
std::string IndexNode::toString()
{
	std::ostringstream mystream;
	//GeneralPageHeaderAccessor genPageAccessor(pageData_);
	//mystream << genPageAccessor.toString();
	mystream << "\tINDEX HEADER PAGE NO: " << getIndexHeaderPageNumber() << "\n";

	mystream << "\tLevel of Index Page ----------------------: "
			<< getLevelOfIndexNode() << "\n";
	mystream << "\tParent page number -------------------------------: "
			<< getParentOfIndexNode() << "\n";
	mystream << "\tNumber of keys in Index Page ---------------------: "
			<< getNoOfKeysInIndexNode() << "\n";
	mystream
			<< "\t***********************DATA IN INDEX NODE **************************"
			<< "\n";
	mystream<<"\t";
	int offset = IndexNode::getIndexNodeHeaderSize();
	int leftPageNumber;
	char key[indexHeader_->getKeySize()];
	for (int i = 0; i < getNoOfKeysInIndexNode(); i++) {
		memcpy(&leftPageNumber, &pageData_[offset], sizeof(int));
		offset = offset + sizeof(int);
		memcpy(key, &pageData_[offset], indexHeader_->getKeySize());
		offset = offset + indexHeader_->getKeySize();
		mystream << " [" << leftPageNumber << "]  ";
		mystream << BPlusTreeUtil::KeytoString(key, indexHeader_);
	}
	memcpy(&leftPageNumber, &pageData_[offset], sizeof(int));
	mystream << " [" << leftPageNumber << "]" << "\n";
	mystream
			<< "\t********************* END OF DATA IN INDEX NODE ******************** "
			<< "\n";
	mystream << "\tLeft Index Page Number ---------------------------:"
			<< getLeftPageNumberOfIndexNode() << "\n";
	mystream << "\tRight Index Page Number --------------------------:"
			<< getRightPageNumber() << "\n";
	return mystream.str();
}


void IndexNode::findFirstLeafPage(std::vector<int> &leafPages)
{
	int level = getLevelOfIndexNode();
	int offset = getIndexNodeHeaderSize();
	int pageNumber1;
	for (int i = 0; i < getNoOfKeysInIndexNode() + 1; i++) {
		memcpy(&pageNumber1, &pageData_[offset], sizeof(int));
		offset = offset + sizeof(int) + indexHeader_->getKeySize();
		if (level > 1) {
			IndexNode indexNode(fd_,indexHeader_, pageNumber1);
			indexNode.findFirstLeafPage(leafPages);
		}
		if (level == 1) {
			leafPages.push_back(pageNumber1);
		}
	}

}
int IndexNode::searchKeyInIndexNodeWithOp(const char* key, int op, std::vector<
		RIDStruct> &RIDVector, std::vector<string> &keyVector) {

	int nextPageNumber;
	switch (op) {
	case 1:
		//cout << "op ==1 "<<endl;
		nextPageNumber=searchInIndexNode(key);
		cout << "current page number :"<<getPageNumber()<<"next page number :"<< nextPageNumber<<endl;
		if(nextPageNumber==-1){
			return 0;
		}
		if(getLevelOfIndexNode()==1){
			int found=1;
			//while (found == 1) {
				if (nextPageNumber != -1) {
					LeafNode leafNode(fd_,indexHeader_, nextPageNumber);
					cout << "leaf page number :"<< leafNode.getPageNumber()<<" leaf page right pagenumber :"<< leafNode.getRightPageNumber() <<endl;
					found=leafNode.searchKeyInLeafNodeWithOp(key, op,
							RIDVector, keyVector);

					nextPageNumber = leafNode.getRightPageNumber();

				}
				else{
					found =0;
				}
			//}
		}
		else{
			IndexNode indexNode(fd_,indexHeader_,nextPageNumber);
			indexNode.searchKeyInIndexNodeWithOp(key,op,RIDVector,keyVector);
		}
		break;
	}
}
