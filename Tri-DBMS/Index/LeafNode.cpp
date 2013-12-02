/*
 * LeafNode.cpp
 *
 *  Created on: Oct 23, 2013
 *      Author: puneeth
 */


#include "LeafNode.h"
#include "IndexNode.h"
#include "IndexHeader.h"
#include "BPlusTreeUtil.h"
#include "../HeapFileManagement/FreePageManager.h"
#include "../Global/globalDefines.h"
#include "../Global/globalStructures.h"
#include "../BufferManagement/BufferManager.h"
#include <iostream>
#include <string.h>
#include <math.h>
#include <assert.h>
#include<stdlib.h>
#include <sstream>
using namespace std;
int LeafNode::testPinCount = 0;
extern int noOfLeafPages;
LeafNode::LeafNode(int fd) {
	// TODO Auto-generated constructor stub
	indexHeaderObjCreatedHere = false;
	fd_=fd;
	pageData_=new char[DEFAULT_PAGE_SIZE];
}
LeafNode::LeafNode(int fd,int leafPageNumber) {
	fd_=fd;
	pageNumber_=leafPageNumber;
	bufMgr_ = BufferManager::getInstance();
	pageData_=new char[DEFAULT_PAGE_SIZE];
	int error = bufMgr_->readPage(fd_,leafPageNumber, pageData_);
	memcpy(&leafNodePageHeader_, pageData_, sizeof(LeafNodePageHeaderStruct));
	int indexHeaderPageNumber = getIndexHeaderPageNumber();
	indexHeader_ = new IndexHeader(fd_,indexHeaderPageNumber);
	indexHeaderObjCreatedHere = true;
}
int LeafNode::getIndexHeaderPageNumber() {
	memcpy(&leafNodePageHeader_, pageData_, sizeof(LeafNodePageHeaderStruct));
	return leafNodePageHeader_.indexHeaderPageNumber;
}
LeafNode::LeafNode(int fd,IndexHeader *indexHeaderPage, int leafPageNumber) {
	// TODO Auto-generated constructor stub
	fd_=fd;
	pageNumber_=leafPageNumber;
	pageData_=new char[DEFAULT_PAGE_SIZE];
	indexHeaderObjCreatedHere = false;
	indexHeader_ = indexHeaderPage;
	bufMgr_ = BufferManager::getInstance();
	int error = bufMgr_->readPage(fd_,pageNumber_, pageData_);
	memcpy(&leafNodePageHeader_, pageData_, sizeof(LeafNodePageHeaderStruct));
	//	testPinCount++;
}

LeafNode::~LeafNode() {
	// TODO Auto-generated destructor stub
	bufMgr_ = BufferManager::getInstance();
	bufMgr_->writePage(fd_,leafNodePageHeader_.generalPageHeader.pageNumber,pageData_);
	//	testPinCount--;
	delete[] pageData_;
	if(indexHeaderObjCreatedHere == true){
		//delete indexHeader_;
	}
}

int LeafNode::createLeafPage(IndexHeader *indexHeaderPage) {
	bufMgr_ = BufferManager::getInstance();
	int newPageNumber;
	noOfLeafPages++;
	pageData_=new char[DEFAULT_PAGE_SIZE];
	FreePageManager *freePageMgr=new FreePageManager(fd_,1);
	newPageNumber=freePageMgr->getFreePage();
	pageNumber_=newPageNumber;
	//cout << "fd is :" << fd_ <<" new page number is:" << newPageNumber <<endl;
	//int error = bufMgr->readPage(fd_,newPageNumber, pageData_);
//	if (error != SUCCESS) {
//		cout << "error";
//		return error;
//	}
	//memcpy(&leafNodePageHeader_, pageData_, sizeof(LeafNodePageHeaderStruct));
	leafNodePageHeader_.generalPageHeader.pageNumber=newPageNumber;
	leafNodePageHeader_.generalPageHeader.pageType = INDEX_LEAF_PAGE;
	leafNodePageHeader_.generalPageHeader.nextPageNumber=-1;
	leafNodePageHeader_.level = 0;//All leaf nodes are at level 0
	leafNodePageHeader_.noOfRecords = 0;
	leafNodePageHeader_.parentPageNumber = -1;
	leafNodePageHeader_.leftPageNumber = -1;
	leafNodePageHeader_.rightPageNumber = -1;
	leafNodePageHeader_.indexHeaderPageNumber
			= indexHeaderPage->getPageNumber();
	//cout <<"after get page number" << endl;
	memcpy(pageData_, &leafNodePageHeader_, sizeof(LeafNodePageHeaderStruct));
	//	indexHeaderPage->pushLeafPageNumbers(newPageNumber);
	indexHeader_ = indexHeaderPage;
	//cout <<"before get root page number" << endl;
	if (indexHeader_->getRootPageNumber() == -1) {
		indexHeader_->setRootPageNumber(newPageNumber);
	}
	//cout << "after get root page" << endl;
	bufMgr_->writePage(fd_,newPageNumber,pageData_);
	delete freePageMgr;
	return SUCCESS;
}

void LeafNode::getKey(int keyNumber, char* key1) {
	int offset = getLeafNodeHeaderSize() + keyNumber
			* (indexHeader_->getKeySize() + sizeof(RIDStruct));
	//cout << "size of key is :" <<indexHeader_->getKeySize() <<endl;
	memcpy(key1, &pageData_[offset], indexHeader_->getKeySize());
	//	display();
}
void LeafNode::getKeyAndRID(int keyNumber, char* key1, RIDStruct &rid) {
	int offset = getLeafNodeHeaderSize() + keyNumber
			* (indexHeader_->getKeySize() + sizeof(RIDStruct));
	memcpy(key1, &pageData_[offset], sizeof(indexHeader_->getKeySize()));
	offset = offset + indexHeader_->getKeySize();
	memcpy(&rid, &pageData_[offset], sizeof(RIDStruct));
	//	BPlusTreeUtil::displayKey(key1,indexHeader_);
	//	cout<<endl;
}
int LeafNode::dummyKeyCompare(char* key1, char* key2) {
	return strcmp(key1, key2);
}
int LeafNode::insertIntoLeafPage(const char* key, RIDStruct rid) {
	char tempKey[indexHeader_->getKeySize()];
	int i = 0;
	//cout << "in insert into leaf page" <<endl;
	if (leafNodePageHeader_.noOfRecords
			== indexHeader_->getMaxNoOfRecordsInLeaf()) {
			//cout<<"\n here "<<endl;
			//cout<<"\n initial "<<getPageNumber()<<"  "<<getLeftPageNumber()<<"  "<<getRightPageNumber()<<endl;
		int promoteLeafLeftPage, promoteLeafRightPage;
		char promoteKey[indexHeader_->getKeySize()];
		char tempKeys[leafNodePageHeader_.noOfRecords + 1][indexHeader_->getKeySize()];
		RIDStruct tempRIDS[leafNodePageHeader_.noOfRecords + 1];
		int tempCount = 0, found = 0;
		int offset = LeafNode::getLeafNodeHeaderSize();
		//cout << "before for loop" << endl;
		for (int i = 0; i < leafNodePageHeader_.noOfRecords; i++) {
			memcpy(tempKeys[tempCount], &pageData_[offset],
					indexHeader_->getKeySize());
			offset = offset + indexHeader_->getKeySize();
			memcpy(&tempRIDS[tempCount], &pageData_[offset], sizeof(RIDStruct));
			//			 dummyKeyCompare(tempKeys[tempCount], key);

			int comp = BPlusTreeUtil::keyCompare(tempKeys[tempCount], key,
					indexHeader_);
			if (comp == 1 && found == 0) {
				char temp[indexHeader_->getKeySize()];
				RIDStruct temprid;
				memcpy(temp, tempKeys[tempCount], indexHeader_->getKeySize());
				temprid = tempRIDS[tempCount];
				memcpy(tempKeys[tempCount], key, indexHeader_->getKeySize());
				tempRIDS[tempCount] = rid;
				tempCount++;
				memcpy(tempKeys[tempCount], temp, indexHeader_->getKeySize());
				tempRIDS[tempCount] = temprid;
				found = 1;
			}
			offset = offset + sizeof(RIDStruct);
			tempCount++;
		}

		if (found == 0) {
			memcpy(tempKeys[tempCount], key, indexHeader_->getKeySize());
			memcpy(&tempRIDS[tempCount], &rid, sizeof(RIDStruct));
			tempCount++;
		}
		//cout << "temp count :"<< tempCount <<endl;
		offset = LeafNode::getLeafNodeHeaderSize();
		leafNodePageHeader_.noOfRecords = 0;
		//cout << "leaf page no of rec :" <<leafNodePageHeader_.noOfRecords <<endl;
		memset(pageData_,0,DEFAULT_PAGE_SIZE);
		for (int i = 0; i < tempCount / 2; i++) {
			memcpy(&pageData_[offset], tempKeys[i], indexHeader_->getKeySize());
			offset = offset + indexHeader_->getKeySize();
			memcpy(&pageData_[offset], &tempRIDS[i], sizeof(RIDStruct));
			offset = offset + sizeof(RIDStruct);
			leafNodePageHeader_.noOfRecords++;
		}
		//cout << "leaf page no of rec :(1)" <<leafNodePageHeader_.noOfRecords <<endl;

//			cout<<"\n initial "<<getPageNumber()<<"  "<<getLeftPageNumber()<<"  "<<getRightPageNumber()<<endl;
//			cout<<"\n initial "<<getPageNumber()<<"  "<<getLeftPageNumber()<<"  "<<getRightPageNumber()<<endl;
		//cout << "leaf page no of rec :(1_1)" <<leafNodePageHeader_.noOfRecords <<endl;
		LeafNode newLeafNode(fd_);
		newLeafNode.createLeafPage(indexHeader_);
		//cout << "after create new leaf node" << endl;
		promoteLeafLeftPage = leafNodePageHeader_.generalPageHeader.pageNumber;
		//cout << "before right page" << endl;
		promoteLeafRightPage = newLeafNode.getPageNumber();
		//cout << "before memcpy" << endl;
		memcpy(promoteKey, tempKeys[tempCount / 2], indexHeader_->getKeySize());
			//cout<<"\n right page number "<<leafNodePageHeader_.rightPageNumber<<endl;
			//cout << "no of records in left 6(2):"<< leafNodePageHeader_.noOfRecords <<endl;
		if (leafNodePageHeader_.rightPageNumber != -1) {
			LeafNode rightLeafNode(fd_,indexHeader_,
					leafNodePageHeader_.rightPageNumber);
			rightLeafNode.setLeftPageNumber(newLeafNode.getPageNumber());
		}
		//cout << "no of records in left 6:(3)"<< leafNodePageHeader_.noOfRecords <<endl;
		newLeafNode.setRightPageNumber(leafNodePageHeader_.rightPageNumber);
		newLeafNode.setLeftPageNumber(
				leafNodePageHeader_.generalPageHeader.pageNumber);
		leafNodePageHeader_.rightPageNumber=newLeafNode.getPageNumber();
		memcpy(pageData_, &leafNodePageHeader_,
				sizeof(LeafNodePageHeaderStruct));
//			cout << "no of records in left 6:(4)"<< leafNodePageHeader_.noOfRecords <<endl;
//			cout<<"\n current "<<leafNodePageHeader_.leftPageNumber<<"  "<<leafNodePageHeader_.generalPageHeader.pageNumber<<"  "<<leafNodePageHeader_.rightPageNumber<<endl;
//			cout << "================================come here=====================" << endl;
//			cout << "\n new Leaf Node (right) "<<newLeafNode.getLeftPageNumber() << " "  << newLeafNode.getPageNumber() << " "<<newLeafNode.getRightPageNumber() << endl;
		// now create new leaf node

		//bufMgr->unPinPage(newLeafNode.getPageNumber(),true);
		//LeafNode newLeafNode1(indexHeader_, newLeafNode.getPageNumber());
		for (int i = tempCount / 2; i < tempCount; i++) {
			newLeafNode.insertIntoLeafPage(tempKeys[i], tempRIDS[i]);
		}

		if (leafNodePageHeader_.parentPageNumber == -1) {
			IndexNode indexNode(fd_);
			indexNode.createIndexNode(indexHeader_);
			int indexPageNumber = indexNode.getPageNumber();
//			if(BPLUSTREE_DEBUG==true)
//			{
//				BPlusTreeUtil::displayKey(promoteKey,indexHeader_);
//			}
			//cout << "index page number :"<<indexNode.getPageNumber()<<endl;
			indexNode.insertIntoIndexNode(promoteKey, promoteLeafLeftPage,
					promoteLeafRightPage);
			leafNodePageHeader_.parentPageNumber = indexPageNumber;
			memcpy(pageData_, &leafNodePageHeader_,
					sizeof(LeafNodePageHeaderStruct));
			setRightPageNumber(newLeafNode.getPageNumber());
			setLeftPageNumber(leafNodePageHeader_.leftPageNumber);
//
			//	newLeafNode.setParentPageNumber(indexPageNumber);
		} else {
			IndexNode indexNode(fd_,indexHeader_,
					leafNodePageHeader_.parentPageNumber);
//			if(BPLUSTREE_DEBUG==true)
//			{
//				BPlusTreeUtil::displayKey(promoteKey,indexHeader_);
//			}
			newLeafNode.setParentPageNumber(
					leafNodePageHeader_.parentPageNumber);
			//		display();
			indexNode.insertIntoIndexNode(promoteKey, promoteLeafLeftPage,
					promoteLeafRightPage);
			memcpy(&leafNodePageHeader_, pageData_,
					sizeof(LeafNodePageHeaderStruct));
			//		display();
			setRightPageNumber(newLeafNode.getPageNumber());
			//		cout<<"END "<<leafNodePageHeader_.leftPageNumber<<endl;
			setLeftPageNumber(leafNodePageHeader_.leftPageNumber);
			//		cout<<"\n current "<<leafNodePageHeader_.leftPageNumber<<"  "<<leafNodePageHeader_.generalPageHeader.pageNumber<<"  "<<leafNodePageHeader_.rightPageNumber<<endl;
			//		cout<<"\n current data "<<getLeftPageNumber()<<"  "<<getPageNumber()<<"  "<<getRightPageNumber()<<endl;
			//		display();
			/*
			 if (getRightPageNumber() != -1) {
			 LeafNode leafNode100(indexHeader_, getPageNumber());
			 //			leafNode100.display();
			 LeafNode leafNode200(indexHeader_, getRightPageNumber());
			 //			leafNode200.display();
			 }
			 */
		}
		//	cout<<"\n current "<<leafNodePageHeader_.leftPageNumber<<"  "<<leafNodePageHeader_.generalPageHeader.pageNumber<<"  "<<leafNodePageHeader_.rightPageNumber<<endl;
		bufMgr_->writePage(fd_,pageNumber_,pageData_);
//				bufMgr_->commitCache();
//				bufMgr_->hexDump(fd_,6);
//				bufMgr_->hexDump(fd_,7);
//				bufMgr_->hexDump(fd_,8);
//				cout << "=========================================="<<leafNodePageHeader_.noOfRecords <<"========================================"<<endl;
		return SUCCESS;
	} else {
		//cout << "in lf else key search"<<endl;
		//if number of records is less than maximum number of nodes in leaf
		//cout << " no of records in leaf:"<< leafNodePageHeader_.noOfRecords<<endl;
		for (i = 0; i < leafNodePageHeader_.noOfRecords; i++) {
			getKey(i, tempKey);
			//BPlusTreeUtil::keyCompare(tempKey,key,indexHeader_);
			int compValue = -1;
			//			dummyKeyCompare(tempKey, key);
			//cout << "temp key :" <<tempKey << " key :" <<key<<endl;
			//cout << " indexHeader page no :"<<indexHeader_->getPageNumber() <<endl;
			compValue = BPlusTreeUtil::keyCompare(tempKey, key, indexHeader_);
			//cout << "compare value :" << compValue <<endl;
			if (compValue == 1)
			break;
		}
		//cout << "outside for loop " <<endl;
		//cout << "temp key :" <<tempKey << " key :" <<key<<endl;
		if (leafNodePageHeader_.noOfRecords == 0) {
			int offset = getLeafNodeHeaderSize();
			memcpy(&pageData_[offset], key, indexHeader_->getKeySize());
			offset = offset + indexHeader_->getKeySize();
			memcpy(&pageData_[offset], &rid, sizeof(RIDStruct));
			leafNodePageHeader_.noOfRecords = leafNodePageHeader_.noOfRecords
			+ 1;
			memcpy(pageData_, &leafNodePageHeader_,
					sizeof(LeafNodePageHeaderStruct));
		} else {
			//cout << "only for 2nd insert" << endl;
			if (leafNodePageHeader_.noOfRecords == i) {
				//insert at the end
				//cout << "no of records == i"<<endl;
				int offset = LeafNode::getLeafNodeHeaderSize()
				+ leafNodePageHeader_.noOfRecords
				* (indexHeader_->getKeySize() + sizeof(RIDStruct));
				memcpy(&pageData_[offset], key, indexHeader_->getKeySize());
				offset = offset + indexHeader_->getKeySize();
				memcpy(&pageData_[offset], &rid, sizeof(RIDStruct));
				leafNodePageHeader_.noOfRecords
				= leafNodePageHeader_.noOfRecords + 1;
				memcpy(pageData_, &leafNodePageHeader_,
						sizeof(LeafNodePageHeaderStruct));
			} else {
				// cout << "in else if no of records !=i"<<endl;
				//insert at first or the middle
				char previousFirstKey[indexHeader_->getKeySize()];
				char tempo[indexHeader_->getKeySize()];
				/*			if(getParentPageNumber()!=-1)
				 {
				 IndexNode indexNode2(indexHeader_,getParentPageNumber());
				 indexNode2.getKeyNextToPageNumber(getLeftPageNumber(),previousFirstKey);
				 cout<<"ACTUAL KEY "<<previousFirstKey<<endl;
				 }
				 */
				getFirstKey(previousFirstKey);
				getParentKey(previousFirstKey);
				//			cout<<" tempo key "<<tempo<<endl;
				//				cout << " previous key " << previousFirstKey << endl;
				char tempChar[leafNodePageHeader_.noOfRecords
				* (indexHeader_->getKeySize() + sizeof(RIDStruct))];
				int offset = LeafNode::getLeafNodeHeaderSize() + i
				* (indexHeader_->getKeySize() + sizeof(RIDStruct));
				memcpy(tempChar, &pageData_[offset],
						(leafNodePageHeader_.noOfRecords - (i))
						* (indexHeader_->getKeySize() + sizeof(RIDStruct)));
				memcpy(&pageData_[offset], key, indexHeader_->getKeySize());
				offset = offset + indexHeader_->getKeySize();
				memcpy(&pageData_[offset], &rid, sizeof(RIDStruct));
				offset = offset + sizeof(RIDStruct);
				memcpy(&pageData_[offset], tempChar,
						(leafNodePageHeader_.noOfRecords - (i))
						* (indexHeader_->getKeySize() + sizeof(RIDStruct)));
				leafNodePageHeader_.noOfRecords
				= leafNodePageHeader_.noOfRecords + 1;
				memcpy(pageData_, &leafNodePageHeader_,
						sizeof(LeafNodePageHeaderStruct));
				//means inserting at first then to push to index node
				if (i == 0 && getParentPageNumber() != -1) {
					//				cout<<"\n parent number "<<getParentPageNumber()<<endl;
					IndexNode indexNode(fd_,indexHeader_, getParentPageNumber());
					//				cout<<" "<<previousFirstKey<<"   "<<key<<endl;
					//					dummyKeyCompare(previousFirstKey, key)

					if (BPlusTreeUtil::keyCompare(previousFirstKey, key,
									indexHeader_) != 0) {
						indexNode.replaceKey(previousFirstKey, key);
						//						indexNode.display();
					}
				}
			}
		}
	}
	bufMgr_->writePage(fd_,pageNumber_,pageData_);
	return SUCCESS;
}
int LeafNode::deleteFromLeafPage(const char* key, RIDStruct &givenRid,
		std::vector<int> &deletedPages) {
	//say given key is not found in any other indexNode
	int currentNoOfRecords = getNoOfRecordsInNode();

	if ((currentNoOfRecords - 1) >= ceil(
			indexHeader_->getMaxNoOfRecordsInLeaf() / 2)) {
		//cout << "inside >= ceil" << endl;
		//delete key safely because it has enough number of keys
		int offset = LeafNode::getLeafNodeHeaderSize();
		char tempKey[indexHeader_->getKeySize()];
		RIDStruct tempRid;
		int found = 0, i;
		//cout << "no of records :" << getNoOfRecordsInNode() << endl;
		for (i = 0; i < getNoOfRecordsInNode(); i++) {
			memcpy(tempKey, &pageData_[offset], indexHeader_->getKeySize());
			offset = offset + indexHeader_->getKeySize();
			memcpy(&tempRid, &pageData_[offset], sizeof(RIDStruct));
			offset = offset + sizeof(RIDStruct);
			//			dummyKeyCompare(tempKey, key);
			//cout << "temp key :" << tempKey << " key: " << key <<endl;
			if (BPlusTreeUtil::keyCompare(tempKey, key, indexHeader_) == 0
					&& ridsCompare(tempRid, givenRid) == 0) {
				found = 1;
				break;
			}
		}
		if (found == 1 && i == getNoOfRecordsInNode() - 1) {
			setNoOfRecordsInNode(getNoOfRecordsInNode() - 1);
			//bufMgr_->writePage(fd_,pageNumber_,pageData_);
			return SUCCESS;
		}
		if (found == 1) {
			cout << "found == 1" << endl;
			int oldOffset = offset - (indexHeader_->getKeySize() + sizeof(RIDStruct));
			char temp[(getNoOfRecordsInNode() - i - 1)
					* (indexHeader_->getKeySize() + sizeof(RIDStruct))];
			memcpy(temp, &pageData_[offset], (getNoOfRecordsInNode() - i - 1)
					* (indexHeader_->getKeySize() + sizeof(RIDStruct)));
			memcpy(&pageData_[oldOffset], temp,
					(getNoOfRecordsInNode() - i - 1)
							* (indexHeader_->getKeySize() + sizeof(RIDStruct)));
			setNoOfRecordsInNode(getNoOfRecordsInNode() - 1);
			int levelOfTree = indexHeader_->getHeightOfTree();
			int currentPage = getPageNumber();
			if (levelOfTree != 0) {
				IndexNode indexNode(fd_,indexHeader_, getParentPageNumber());
				char replaceKey[indexHeader_->getKeySize()];
				getFirstKey(replaceKey);
				indexNode.replaceKey(key, replaceKey);
			}
			bufMgr_->writePage(fd_,pageNumber_,pageData_);
			return SUCCESS;
		}
	} else {
		//cout << " in else :" <<endl;
		//ohh leaf node does not have enough number of keys so do either rotate or merge
		if (getParentPageNumber() == -1) {
			if (getLevelOfNode() == indexHeader_->getHeightOfTree()) {
				int offset = LeafNode::getLeafNodeHeaderSize();
				char tempKey[indexHeader_->getKeySize()];
				RIDStruct tempRid;
				int found = 0, i;
				//cout << "in else in if height =level" <<endl;
				//cout << "no of records :" << getNoOfRecordsInNode() <<endl;
				for (i = 0; i < getNoOfRecordsInNode(); i++) {
					//bufMgr_->hexDump(pageData_);
					//cout << "offset :" << offset <<endl;
					memcpy(tempKey, &pageData_[offset],
							indexHeader_->getKeySize());

					//cout << "offset :" << offset <<endl;
					//cout << "temp key :" << tempKey <<endl;
					offset = offset + indexHeader_->getKeySize();
					memcpy(&tempRid, &pageData_[offset], sizeof(RIDStruct));
					offset = offset + sizeof(RIDStruct);
					//cout << "temp key :" << tempKey << " key: " << key <<endl;
					//					dummyKeyCompare(tempKey, key)
					if (BPlusTreeUtil::keyCompare(tempKey, key, indexHeader_)
							== 0 && ridsCompare(tempRid, givenRid) == 0) {
						//cout << "found!!!!" <<endl;
						found = 1;
						break;
					}
				}
				if (found == 1 && i == getNoOfRecordsInNode() - 1) {
					//cout << "last one:" << i<<endl;
					//cout << "getNo" << getNoOfRecordsInNode()<< endl;
					setNoOfRecordsInNode(getNoOfRecordsInNode() - 1);
					//cout << "getNo" << getNoOfRecordsInNode()<< endl;
					if (getNoOfRecordsInNode() == 0) {
						//cout << "don't come" <<endl;
						deletedPages.push_back(getPageNumber());
						indexHeader_->setRootPageNumber(-1);
						indexHeader_->setHeightOfTree(0);
					}
					//cout << "befor return" <<endl;
					return SUCCESS;
				}
				if (found == 1) {
					int oldOffset = offset - (indexHeader_->getKeySize()
							+ sizeof(RIDStruct));
					char temp[(getNoOfRecordsInNode() - i - 1)
							* (indexHeader_->getKeySize() + sizeof(RIDStruct))];
					memcpy(temp, &pageData_[offset], (getNoOfRecordsInNode()
							- i - 1) * (indexHeader_->getKeySize() + sizeof(RIDStruct)));
					memcpy(&pageData_[oldOffset], temp, (getNoOfRecordsInNode()
							- i - 1) * (indexHeader_->getKeySize() + sizeof(RIDStruct)));
					setNoOfRecordsInNode(getNoOfRecordsInNode() - 1);
					if (getNoOfRecordsInNode() == 0) {
						deletedPages.push_back(getPageNumber());
						indexHeader_->setRootPageNumber(-1);
						indexHeader_->setHeightOfTree(0);
					}
					bufMgr_->writePage(fd_,pageNumber_,pageData_);
					return SUCCESS;
				}
			}
		} else {
			IndexNode indexNode(fd_,indexHeader_, getParentPageNumber());
			int leftSibling, rightSibling;
			indexNode.getSiblings(getPageNumber(), leftSibling, rightSibling);
			if (rightSibling != -1) {//if their is right sibling
				LeafNode leafNode(fd_,indexHeader_, rightSibling);
				int noOfRecordsInRightPage = leafNode.getNoOfRecordsInNode();
				if ((noOfRecordsInRightPage - 1) >= ceil(
						indexHeader_->getMaxNoOfRecordsInLeaf() / 2)) {
					//rotate keys from right (right sibling) to left (current node)
					char firstKey[indexHeader_->getKeySize()];
					RIDStruct rid;
					leafNode.getFirstKey(firstKey, rid);
					leafNode.deleteFromLeafPage(firstKey, rid, deletedPages);
					insertIntoLeafPage(firstKey, rid);
					deleteFromLeafPage(key, givenRid, deletedPages);
					return SUCCESS;
				} else if (leftSibling != -1) {
					//right sibling does not have enough keys so check with left sibling
					LeafNode leafNode1(fd_,indexHeader_, leftSibling);
					int noOfRecordsInLeftPage =
							leafNode1.getNoOfRecordsInNode();
					if ((noOfRecordsInLeftPage - 1) >= ceil(
							indexHeader_->getMaxNoOfRecordsInLeaf() / 2)) {
						//rotate keys from left to right
						char lastKey[indexHeader_->getKeySize()];
						RIDStruct rid;
						leafNode1.getLastKey(lastKey, rid);
						leafNode1.deleteFromLeafPage(lastKey, rid, deletedPages);
						insertIntoLeafPage(lastKey, rid);
						deleteFromLeafPage(key, givenRid, deletedPages);
						getLastKey(lastKey, rid);
						return SUCCESS;
					} else {
						//their is no enough number of keys in both left and right siblings
						//DO merging with one of the siblings (right)here
						deletedPages.push_back(getPageNumber());
						int offset = LeafNode::getLeafNodeHeaderSize();
						char
								tempKeys[indexHeader_->getMaxNoOfRecordsInLeaf()][indexHeader_->getKeySize()];
						RIDStruct rids[indexHeader_->getMaxNoOfRecordsInLeaf()];
						int tempCount = 0;
						char temp[indexHeader_->getKeySize()];
						RIDStruct tempRid;
						for (int i = 0; i < getNoOfRecordsInNode(); i++) {
							memcpy(temp, &pageData_[offset],
									indexHeader_->getKeySize());
							offset = offset + indexHeader_->getKeySize();
							memcpy(&tempRid, &pageData_[offset], sizeof(RIDStruct));
							//IN FUTURE ADD THIS  && ridsCompare(givenRid,tempRid)!=0 in if condition
							//								dummyKeyCompare(temp, key);
							if (((BPlusTreeUtil::keyCompare(temp, key,
									indexHeader_) != 0) && (ridsCompare(
									givenRid, tempRid) != 0))
									|| ((BPlusTreeUtil::keyCompare(temp, key,
											indexHeader_) == 0)
											&& (ridsCompare(givenRid, tempRid)
													!= 0))) {

								memcpy(tempKeys[tempCount], temp,
										indexHeader_->getKeySize());
								memcpy(&rids[tempCount], &pageData_[offset],
										sizeof(RIDStruct));
								tempCount++;
							}
							offset = offset + sizeof(RIDStruct);
						}
						//						for (int i = 0; i < tempCount; i++)
						//							cout << "  " << tempKeys[i] << endl;
						for (int i = 0; i < tempCount; i++) {
							leafNode.insertIntoLeafPage(tempKeys[i], rids[i]);
						}
						//						leafNode.display();
						IndexNode
								indexNode(fd_,indexHeader_, getParentPageNumber());
						char keyToDelete[indexHeader_->getKeySize()];
						indexNode.getKeyPreviousToPageNumber(getPageNumber(),
								keyToDelete);
//						if (BPLUSTREE_DEBUG == true) {
//							BPlusTreeUtil::displayKey(keyToDelete, indexHeader_);
//						}
						char firstKey[indexHeader_->getKeySize()];
						leafNode.getFirstKey(firstKey);
						indexNode.replaceKeyPreviousToPageNumber(
								leafNode.getPageNumber(), key, firstKey);
						//					indexNode.indexNodeOnlyDisplay();
						indexNode.deleteKeyFromIndexNode(keyToDelete, false,
								deletedPages);
						//					char firstKey[indexHeader_->getKeySize()];
						//						indexNode.indexNodeOnlyDisplay();
						leafNode.getFirstKey(firstKey);
						indexNode.replaceKey(key, firstKey);
						//						cout << "\n DELETION ENDS HERE" << endl;

					}
				} else {

					//their is no left leaf page number and right leaf page does not enough number of keys
					//DO merging with right page number
					deletedPages.push_back(getPageNumber());
					int offset = LeafNode::getLeafNodeHeaderSize();
					char
							tempKeys[indexHeader_->getMaxNoOfRecordsInLeaf()][indexHeader_->getKeySize()];
					RIDStruct rids[indexHeader_->getMaxNoOfRecordsInLeaf()];
					int tempCount = 0;
					char temp[indexHeader_->getKeySize()];
					for (int i = 0; i < getNoOfRecordsInNode(); i++) {
						RIDStruct tempRid;
						memcpy(temp, &pageData_[offset],
								indexHeader_->getKeySize());
						offset = offset + indexHeader_->getKeySize();
						memcpy(&tempRid, &pageData_[offset], sizeof(RIDStruct));
						// in future add this to  && ridsCompare(givenRid,tempRid)!=0 if condition
						//							dummyKeyCompare(temp, key);
						if (((BPlusTreeUtil::keyCompare(temp, key, indexHeader_)
								!= 0) && (ridsCompare(givenRid, tempRid) != 0))
								|| ((BPlusTreeUtil::keyCompare(temp, key,
										indexHeader_) == 0) && (ridsCompare(
										givenRid, tempRid) != 0))) {
							//							BPlusTreeUtil::displayKey(temp, indexHeader_);
							//							cout<<"\n temp p :"<<tempRid.pageNumber<<"  "<<tempRid.slotNumber<<endl;
							//							BPlusTreeUtil::displayKey(key, indexHeader_);
							//							cout<<"\n p : "<<givenRid.pageNumber<<"  "<<givenRid.slotNumber<<endl;
							memcpy(tempKeys[tempCount], temp,
									indexHeader_->getKeySize());
							memcpy(&rids[tempCount], &pageData_[offset],
									sizeof(RIDStruct));
							tempCount++;
						}
						offset = offset + sizeof(RIDStruct);
					}
					/*					for (int i = 0; i < tempCount; i++) {
					 cout << "  ";
					 BPlusTreeUtil::displayKey(tempKeys[i], indexHeader_);
					 cout << endl;
					 }
					 */
					for (int i = 0; i < tempCount; i++) {
						//						cout << "  " << tempKeys[i] << endl;
						leafNode.insertIntoLeafPage(tempKeys[i], rids[i]);
					}
					IndexNode indexNode(fd_,indexHeader_, getParentPageNumber());
					if (tempCount >= 0) {
						indexNode.replaceKey(key, tempKeys[0]);
					}
					char keyToDelete[indexHeader_->getKeySize()];
					indexNode.getKeyNextToPageNumber(getPageNumber(),
							keyToDelete);
					char firstKey[indexHeader_->getKeySize()];
					leafNode.getFirstKey(firstKey);
					indexNode.replaceKeyPreviousToPageNumber(
							leafNode.getPageNumber(), key, firstKey);
					indexNode.deleteKeyFromIndexNode(keyToDelete, true,
							deletedPages);
					//				char firstKey[indexHeader_->getKeySize()];
					int pageNumber =
							indexNode.getFirstPageNumberPresentInIndexNode();
					LeafNode leafNode11(fd_,indexHeader_, pageNumber);
					leafNode11.getFirstKey(firstKey);
					//					indexNode.indexNodeOnlyDisplay();
					indexNode.replaceKey(key, firstKey);
					//					cout << "\n DELETION ENDS HERE" << endl;

				}
			} else if (leftSibling != -1) {//if their is no rightsibling but their is a left sibling
				//SO ROTATE WITH LEFT SIBLING IF POSSIBLE
				LeafNode leafNode(fd_,indexHeader_, leftSibling);
				int noOfRecordsInLeftSibling = leafNode.getNoOfRecordsInNode();
				if ((noOfRecordsInLeftSibling - 1) >= ceil(
						indexHeader_->getMaxNoOfRecordsInLeaf() / 2)) {
					//left sibling has enough number of keys
					//rotate keys from left to right
					char lastKey[indexHeader_->getKeySize()];
					RIDStruct rid;
					leafNode.getLastKey(lastKey, rid);
					leafNode.deleteFromLeafPage(lastKey, rid, deletedPages);
					insertIntoLeafPage(lastKey, rid);
					deleteFromLeafPage(key, givenRid, deletedPages);
					getFirstKey(lastKey, rid);
					return SUCCESS;
				} else {
					//left sibling does not enough number of keys and we don't have right sibling so
					//do merging with left sibling
					//					DEBUG_B("IAM HERE--------for merging with left node---")
					deletedPages.push_back(getPageNumber());
					int offset = LeafNode::getLeafNodeHeaderSize();
					char
							tempKeys[indexHeader_->getMaxNoOfRecordsInLeaf()][indexHeader_->getKeySize()];
					RIDStruct rids[indexHeader_->getMaxNoOfRecordsInLeaf()];
					int tempCount = 0;
					char temp[indexHeader_->getKeySize()];
					for (int i = 0; i < getNoOfRecordsInNode(); i++) {
						RIDStruct tempRid;
						memcpy(temp, &pageData_[offset],
								indexHeader_->getKeySize());
						offset = offset + indexHeader_->getKeySize();
						memcpy(&tempRid, &pageData_[offset], sizeof(RIDStruct));
						//in future add this to  && ridsCompare(givenRid,tempRid)!=0 if condition

						//							dummyKeyCompare(temp, key);
						if (((BPlusTreeUtil::keyCompare(temp, key, indexHeader_)
								!= 0) && (ridsCompare(givenRid, tempRid) != 0))
								|| ((BPlusTreeUtil::keyCompare(temp, key,
										indexHeader_) == 0) && (ridsCompare(
										givenRid, tempRid) != 0))) {
							memcpy(tempKeys[tempCount], temp,
									indexHeader_->getKeySize());
							memcpy(&rids[tempCount], &pageData_[offset],
									sizeof(RIDStruct));
							tempCount++;
						}

						offset = offset + sizeof(RIDStruct);
					}
					/*					for (int i = 0; i < tempCount; i++)
					 cout << "  " << tempKeys[i] << endl;
					 */
					for (int i = 0; i < tempCount; i++) {
						//						cout << "  " << tempKeys[i] << endl;
						leafNode.insertIntoLeafPage(tempKeys[i], rids[i]);
					}
					IndexNode indexNode(fd_,indexHeader_, getParentPageNumber());
					char keyToDelete[indexHeader_->getKeySize()];
					indexNode.getKeyNextToPageNumber(getPageNumber(),
							keyToDelete);
					indexNode.deleteKeyFromIndexNode(keyToDelete, false,
							deletedPages);

					char firstKey[indexHeader_->getKeySize()];
					indexNode.indexNodeOnlyDisplay();
					leafNode.getFirstKey(firstKey);
					indexNode.replaceKey(key, firstKey);
					//					cout << "\n DELETION ENDS HERE" << endl;
					//********************************************************************
				}
			}
		}
	}
	bufMgr_->writePage(fd_,pageNumber_,pageData_);
}
int LeafNode::searchInLeafNode(const char* key) {
	int noOfRecords = getNoOfRecordsInNode();
	int offset = LeafNode::getLeafNodeHeaderSize();
	char tempKey[indexHeader_->getKeySize()];
	int status = 1;
	for (int i = 0; i < noOfRecords; i++) {
		memcpy(tempKey, &pageData_[offset], indexHeader_->getKeySize());
		//			dummyKeyCompare(tempKey, key);
		status = BPlusTreeUtil::keyCompare(tempKey, key, indexHeader_);
		if (status == 0)
			return 0;
		offset = offset + indexHeader_->getKeySize() + sizeof(RIDStruct);
	}
	return 1;
}
int LeafNode::searchInLeafNode(const char *key, RIDStruct rid) {
	int noOfRecords = getNoOfRecordsInNode();
	int offset = LeafNode::getLeafNodeHeaderSize();
	char tempKey[indexHeader_->getKeySize()];
	RIDStruct existedRID;
	int status = 1;
	for (int i = 0; i < noOfRecords; i++) {
		memcpy(tempKey, &pageData_[offset], indexHeader_->getKeySize());
		offset = offset + indexHeader_->getKeySize();
		memcpy(&existedRID, &pageData_[offset], sizeof(RIDStruct));
		//			dummyKeyCompare(tempKey, key);
		//			status =BPlusTreeUtil::keyCompare(tempKey,key,indexHeader_);
		cout << "befor key compare : " << tempKey << " " <<key;
		if ((BPlusTreeUtil::keyCompare(tempKey, key, indexHeader_) == 0)
				&& ridsCompare(rid, existedRID) != 0) {
			status = 2;
		}

		if ((BPlusTreeUtil::keyCompare(tempKey, key, indexHeader_) == 0)
				&& ridsCompare(rid, existedRID) == 0)
			return 0;
		offset += sizeof(RIDStruct);
	}
	return status;

}
int LeafNode::getLevelOfNode() {
	memcpy(&leafNodePageHeader_, pageData_, sizeof(LeafNodePageHeaderStruct));
	return leafNodePageHeader_.level;
}
void LeafNode::setLevelOfNode(int newLevel) {
	leafNodePageHeader_.level = newLevel;
	memcpy(pageData_, &leafNodePageHeader_, sizeof(LeafNodePageHeaderStruct));

	bufMgr_->writePage(fd_,pageNumber_,pageData_);
}

int LeafNode::getNoOfRecordsInNode() {
	memcpy(&leafNodePageHeader_, pageData_, sizeof(LeafNodePageHeaderStruct));
	return leafNodePageHeader_.noOfRecords;
}
void LeafNode::setNoOfRecordsInNode(int noOfRecords) {
	leafNodePageHeader_.noOfRecords = noOfRecords;
	memcpy(pageData_, &leafNodePageHeader_, sizeof(LeafNodePageHeaderStruct));

	cout << "please come here dude " << noOfRecords << endl;

	cout << "fd :" << fd_ << "page no :" << pageNumber_ << endl;

	bufMgr_->writePage(fd_,pageNumber_,pageData_);
	cout << "after write page " << endl;
}

int LeafNode::getParentPageNumber() {
	memcpy(&leafNodePageHeader_, pageData_, sizeof(LeafNodePageHeaderStruct));
	return leafNodePageHeader_.parentPageNumber;
}
void LeafNode::setParentPageNumber(int parentPageNumber) {
	leafNodePageHeader_.parentPageNumber = parentPageNumber;
	memcpy(pageData_, &leafNodePageHeader_, sizeof(LeafNodePageHeaderStruct));
	bufMgr_->writePage(fd_,pageNumber_,pageData_);
}

int LeafNode::getLeftPageNumber() {
	memcpy(&leafNodePageHeader_, pageData_, sizeof(LeafNodePageHeaderStruct));
	return leafNodePageHeader_.leftPageNumber;
}
void LeafNode::setLeftPageNumber(int newLeftPageNumber) {
	leafNodePageHeader_.leftPageNumber = newLeftPageNumber;
	memcpy(pageData_, &leafNodePageHeader_, sizeof(LeafNodePageHeaderStruct));
	bufMgr_->writePage(fd_,pageNumber_,pageData_);
}

int LeafNode::getRightPageNumber() {
	memcpy(&leafNodePageHeader_, pageData_, sizeof(LeafNodePageHeaderStruct));
	return leafNodePageHeader_.rightPageNumber;
}
void LeafNode::setRightPageNumber(int newRightPageNumber) {
	leafNodePageHeader_.rightPageNumber = newRightPageNumber;
	memcpy(pageData_, &leafNodePageHeader_, sizeof(LeafNodePageHeaderStruct));
	bufMgr_->writePage(fd_,pageNumber_,pageData_);
}
int LeafNode::getPageNumber() {
	memcpy(&leafNodePageHeader_, pageData_, sizeof(LeafNodePageHeaderStruct));
	return leafNodePageHeader_.generalPageHeader.pageNumber;
}
int LeafNode::getLeafNodeHeaderSize() {
	return sizeof(LeafNodePageHeaderStruct);
}
int LeafNode::getFirstKey(char* firstKey, RIDStruct &rid) {
	int offset = LeafNode::getLeafNodeHeaderSize();
	memcpy(firstKey, &pageData_[offset], indexHeader_->getKeySize());
	offset = offset + indexHeader_->getKeySize();
	memcpy(&rid, &pageData_[offset], sizeof(RIDStruct));
}
int LeafNode::getLastKey(char* lastKey, RIDStruct& rid) {
	int offset = LeafNode::getLeafNodeHeaderSize();
	offset += (getNoOfRecordsInNode() - 1) * (indexHeader_->getKeySize()
			+ sizeof(RIDStruct));
	memcpy(lastKey, &pageData_[offset], indexHeader_->getKeySize());
	offset = offset + indexHeader_->getKeySize();
	memcpy(&rid, &pageData_[offset], sizeof(RIDStruct));
}
int LeafNode::getFirstKey(char* firstKey) {
	int offset = LeafNode::getLeafNodeHeaderSize();
	memcpy(firstKey, &pageData_[offset], indexHeader_->getKeySize());
}
void LeafNode::getParentKey(char* key) {
	int parent = getParentPageNumber();
	if (parent != -1) {
		IndexNode indexNode(fd_,indexHeader_, parent);
		indexNode.getKeyPreviousToPageNumber(getPageNumber(), key);
		//		cout << "key " << key << endl;
	}
}

int LeafNode::searchKeyInLeafNode(const char* key, std::vector<
		RIDStruct> &RIDVector) {
	int offset = LeafNode::getLeafNodeHeaderSize();
	char tempKey[indexHeader_->getKeySize()];
	int found = 0;
	RIDStruct tempRid;
	for (int i = 0; i < leafNodePageHeader_.noOfRecords; i++) {
		memcpy(tempKey, &pageData_[offset], indexHeader_->getKeySize());
		//			dummyKeyCompare(tempKey, key);
		int comp = BPlusTreeUtil::keyCompare(tempKey, key, indexHeader_);
		if (comp == 0) {
			found = 1;
		}
		offset = offset + indexHeader_->getKeySize();
		if (found == 1) {
			memcpy(&tempRid, &pageData_[offset], sizeof(RIDStruct));
			RIDVector.push_back(tempRid);
			found = 0;
		}
		offset = offset + sizeof(RIDStruct);
	}
	return SUCCESS;

}
int LeafNode::ridsCompare(RIDStruct rid1, RIDStruct rid2) {
	if (rid1.pageNumber == rid2.pageNumber && rid1.slotNumber
			== rid2.slotNumber)
		return 0;
	else
		return 1;
}
void LeafNode::display() {
	int offset = LeafNode::getLeafNodeHeaderSize();
	cout << "CURRENT LEAF PAGE\t\t" << getPageNumber() << endl;
	cout << "ITS PARENT PAGE NUMBER\t\t" << getParentPageNumber() << endl;
	cout << "NO OF RECORDS IN LEAF NODE\t" << getNoOfRecordsInNode() << endl;
	cout << "LEFT PAGE NUMBER\t\t" << getLeftPageNumber() << endl;
	cout << "RIGHT PAGE NUMBER\t\t" << getRightPageNumber() << endl;
	char key[indexHeader_->getKeySize()];
	RIDStruct rid;
	for (int i = 0; i < leafNodePageHeader_.noOfRecords; i++) {
		memcpy(key, &pageData_[offset], indexHeader_->getKeySize());
		offset = offset + indexHeader_->getKeySize();
		memcpy(&rid, &pageData_[offset], sizeof(RIDStruct));
		cout << "\t\t" << "key " << i << "--" << key << "\tpageNumber--"
				<< rid.pageNumber << "\tslot number " << rid.slotNumber << endl;
		;
		offset = offset + sizeof(RIDStruct);
	}
}
void LeafNode::UILeafNode() {

	//	cout<<" Want to check left leaf page or right page number (y/n)"<<endl;
	cout << endl;
	cout << "\tCurrent Leaf page number-----------------: " << getPageNumber()
			<< endl;
	cout << "\tParent Page number-----------------------: "
			<< getParentPageNumber() << endl;
	cout << "\tNumber of records in Leaf Node-----------: "
			<< getNoOfRecordsInNode() << endl;
	cout
			<< "\t***********************RECORDS IN LEAF NODE *********************** "
			<< endl;
	char key[indexHeader_->getKeySize()];
	RIDStruct rid;
	int offset = LeafNode::getLeafNodeHeaderSize();
	for (int i = 0; i < leafNodePageHeader_.noOfRecords; i++) {
		cout << "\t";
		memcpy(key, &pageData_[offset], indexHeader_->getKeySize());
		offset = offset + indexHeader_->getKeySize();
		memcpy(&rid, &pageData_[offset], sizeof(RIDStruct));
		cout << "key : ";
		BPlusTreeUtil::displayKey(key, indexHeader_);
		cout << "\tPage number : " << rid.pageNumber << "\tSlot number :"
				<< rid.slotNumber << endl;
		offset = offset + sizeof(RIDStruct);
	}
	cout
			<< "\t*********************** END OF RECORDS IN LEAF NODE *************** "
			<< endl;
	cout << "\tLeft Leaf Page Number--------------------: "
			<< getLeftPageNumber() << endl;
	cout << "\tRIght Leaf Page Number-------------------: "
			<< getRightPageNumber() << endl;
}
void LeafNode::UIDisplayOfLeafNode(int numOfTabs) {
	int offset = LeafNode::getLeafNodeHeaderSize();
	char key[indexHeader_->getKeySize()];
	RIDStruct rid;
	for (int k = 0; k < numOfTabs; k++) {
		cout << "\t";
	}
	cout << "Leaf Page Number : " << getPageNumber() << endl;
	for (int i = 0; i < getNoOfRecordsInNode(); i++) {
		memcpy(key, &pageData_[offset], indexHeader_->getKeySize());
		offset = offset + indexHeader_->getKeySize();
		memcpy(&rid, &pageData_[offset], sizeof(RIDStruct));
		offset = offset + sizeof(RIDStruct);
		for (int k = 0; k < numOfTabs; k++) {
			cout << "\t";
		}
		cout << "k:";
		BPlusTreeUtil::displayKey(key, indexHeader_);
		cout << "\t" << "p:" << rid.pageNumber << "\t" << "s:"
				<< rid.slotNumber << endl;
	}
}
void LeafNode::DisplayKeyAt(int keyPosition) {
	int offset = LeafNode::getLeafNodeHeaderSize() + keyPosition
			* (indexHeader_->getKeySize() + sizeof(RIDStruct));
	char key[indexHeader_->getKeySize()];
	RIDStruct rid;
	memcpy(&key, &pageData_[offset], indexHeader_->getKeySize());
	offset = offset + indexHeader_->getKeySize();
	memcpy(&rid, &pageData_[offset], sizeof(RIDStruct));
	cout << "k :" << key << "  p:" << rid.pageNumber << "  s:"
			<< rid.slotNumber;
}
int LeafNode::searchKeyInLeafNodeWithOp(const char* key, int op, std::vector<
		RIDStruct> &RIDVector, std::vector<string> &keyVector) {
	int offset = LeafNode::getLeafNodeHeaderSize();
	char insideKey[indexHeader_->getKeySize()];
	RIDStruct rid;
	int found = 0;
	switch (op) {
	case 1:
		for (int i = 0; i < getNoOfRecordsInNode(); i++) {
			memcpy(insideKey, &pageData_[offset], indexHeader_->getKeySize());
			offset = offset + indexHeader_->getKeySize();
			if (BPlusTreeUtil::keyCompare(insideKey, key, indexHeader_) == 0) {
				found = 1;
				memcpy(&rid, &pageData_[offset], sizeof(RIDStruct));
				RIDVector.push_back(rid);
				keyVector.push_back(insideKey);
			} else if (i == (getNoOfRecordsInNode() - 1)) {
				found = 0;
				break;
			}
			offset = offset + sizeof(RIDStruct);
		}
		break;
	case 2:
		for (int i = 0; i < getNoOfRecordsInNode(); i++) {
			memcpy(insideKey, &pageData_[offset], indexHeader_->getKeySize());
			offset = offset + indexHeader_->getKeySize();
			if (BPlusTreeUtil::keyCompare(insideKey, key, indexHeader_) == 1) {
				found = 1;
				memcpy(&rid, &pageData_[offset], sizeof(RIDStruct));
				offset += sizeof(RIDStruct);
				RIDVector.push_back(rid);
				string str(insideKey, indexHeader_->getKeySize());
				keyVector.push_back(str);
				string dummy = keyVector.back();
				str.clear();
			} else {
				offset = offset + sizeof(RIDStruct);
				found = 1;
			}
		}
		break;
	case 3:
		for (int i = 0; i < getNoOfRecordsInNode(); i++) {
			memcpy(insideKey, &pageData_[offset], indexHeader_->getKeySize());
			offset = offset + indexHeader_->getKeySize();
			if ((BPlusTreeUtil::keyCompare(insideKey, key, indexHeader_) == 1)
					|| (BPlusTreeUtil::keyCompare(insideKey, key, indexHeader_)
							== 0)) {
				found = 1;
				memcpy(&rid, &pageData_[offset], sizeof(RIDStruct));
				offset += sizeof(RIDStruct);
				RIDVector.push_back(rid);
				string str(insideKey, indexHeader_->getKeySize());
				keyVector.push_back(str);
				string dummy = keyVector.back();
				str.clear();
			} else {
				offset = offset + sizeof(RIDStruct);
				found = 1;
			}
		}
		break;
	case 4:
		for (int i = 0; i < getNoOfRecordsInNode(); i++) {
			memcpy(insideKey, &pageData_[offset], indexHeader_->getKeySize());
			offset = offset + indexHeader_->getKeySize();
			if (BPlusTreeUtil::keyCompare(insideKey, key, indexHeader_) == -1) {
				found = 1;
				memcpy(&rid, &pageData_[offset], sizeof(RIDStruct));
				offset += sizeof(RIDStruct);
				RIDVector.push_back(rid);
				string str(insideKey, indexHeader_->getKeySize());
				keyVector.push_back(str);
				string dummy = keyVector.back();
				str.clear();
			} else {
				offset = offset + sizeof(RIDStruct);
				found = 1;
			}
		}
		break;
	case 5:
		for (int i = 0; i < getNoOfRecordsInNode(); i++) {
			memcpy(insideKey, &pageData_[offset], indexHeader_->getKeySize());
			offset = offset + indexHeader_->getKeySize();
			if ((BPlusTreeUtil::keyCompare(insideKey, key, indexHeader_) == -1)
					|| (BPlusTreeUtil::keyCompare(insideKey, key, indexHeader_)
							== 0)) {
				found = 1;
				memcpy(&rid, &pageData_[offset], sizeof(RIDStruct));
				offset += sizeof(RIDStruct);
				RIDVector.push_back(rid);
				string str(insideKey, indexHeader_->getKeySize());
				keyVector.push_back(str);
				string dummy = keyVector.back();
				str.clear();
			} else {
				offset = offset + sizeof(RIDStruct);
				found = 1;
			}
		}
		break;

	}
	return found;
}

std::string LeafNode::toString() {
	std::ostringstream mystream;
	//GeneralPageHeaderAccessor genPageAccessor(pageData_);
	//mystream << genPageAccessor.toString();
	mystream << "\tINDEX HEADER PAGE NO: " << getIndexHeaderPageNumber() << "\n";
	mystream << "\tParent Page number-----------------------: "
			<< getParentPageNumber() << "\n";
	mystream << "\tNumber of records in Leaf Node-----------: "
			<< getNoOfRecordsInNode() << "\n";
	mystream
			<< "\t***********************RECORDS IN LEAF NODE *********************** "
			<< "\n";
	char key[indexHeader_->getKeySize()];
	RIDStruct rid;
	int offset = LeafNode::getLeafNodeHeaderSize();
	for (int i = 0; i < leafNodePageHeader_.noOfRecords; i++) {
		mystream << "\t";
		memcpy(key, &pageData_[offset], indexHeader_->getKeySize());
		offset = offset + indexHeader_->getKeySize();
		memcpy(&rid, &pageData_[offset], sizeof(RIDStruct));
		mystream << "key : ";
		mystream << BPlusTreeUtil::KeytoString(key, indexHeader_);
		mystream << "\tPage number : " << rid.pageNumber << "\tSlot number :"
				<< rid.slotNumber << "\n";
		offset = offset + sizeof(RIDStruct);
	}
	mystream
			<< "\t*********************** END OF RECORDS IN LEAF NODE *************** "
			<< "\n";
	mystream << "\tLeft Leaf Page Number--------------------: "
			<< getLeftPageNumber() << "\n";
	mystream << "\tRIght Leaf Page Number-------------------: "
			<< getRightPageNumber() << "\n";
	return mystream.str();
}


int LeafNode::searchFirstKeyToSecondKey(const char* firstKey,
		const char* secondKey, std::vector<RIDStruct> &RIDVector, std::vector<
				string> &keyVector) {
	int stop = 1;
	int offset = LeafNode::getLeafNodeHeaderSize();
	char key[indexHeader_->getKeySize()];
	RIDStruct rid;
	for (int i = 0; i < leafNodePageHeader_.noOfRecords; i++) {
		memcpy(key, &pageData_[offset], indexHeader_->getKeySize());
		offset = offset + indexHeader_->getKeySize();
		memcpy(&rid, &pageData_[offset], sizeof(RIDStruct));
		if ((BPlusTreeUtil::keyCompare(key, firstKey, indexHeader_) == 0
				|| BPlusTreeUtil::keyCompare(key, firstKey, indexHeader_) == 1)
				&& (BPlusTreeUtil::keyCompare(key, secondKey, indexHeader_)
						== 0 || BPlusTreeUtil::keyCompare(key, secondKey,
						indexHeader_) == -1)) {
			RIDVector.push_back(rid);
			string str(key, indexHeader_->getKeySize());
			keyVector.push_back(str);
			str.clear();
			offset = offset + sizeof(RIDStruct);
			stop = 1;
		} else {
			offset = offset + sizeof(RIDStruct);
			stop = 0;
		}
	}
	return stop;
}
void LeafNode::getKeysAndRIDs(std::vector<RIDStruct> &RIDVector, std::vector<
		string> &keyVector) {
	int offset = LeafNode::getLeafNodeHeaderSize();
	char key[indexHeader_->getKeySize()];
	RIDStruct rid;
	for (int i = 0; i < leafNodePageHeader_.noOfRecords; i++) {
		memcpy(key, &pageData_[offset], indexHeader_->getKeySize());
		offset = offset + indexHeader_->getKeySize();
		memcpy(&rid, &pageData_[offset], sizeof(RIDStruct));
		offset = offset + sizeof(RIDStruct);
		RIDVector.push_back(rid);
		string str(key, indexHeader_->getKeySize());
		keyVector.push_back(str);
		str.clear();
	}
}
