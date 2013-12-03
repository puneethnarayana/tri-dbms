/*
 * BPlusTree.cpp
 *
 *
 *  Created on: Oct 23, 2013
 *      Author: puneeth
 */

#include "BPlusTree.h"
#include "BPlusTreeUtil.h"
#include "IndexHeader.h"
#include "IndexNode.h"
#include "../Global/globalDefines.h"
#include "LeafNode.h"
#include "../BufferManagement/BufferManager.h"
#include <iostream>
#include<limits>
#include<time.h>
#include<fstream>
#include<stdlib.h>
#include <string.h>
#include<vector>
#include "../Utils/CommonUtil.h"
#include "../HeapFileManagement/FreePageManager.h"

using namespace std;
BPlusTree::BPlusTree(int fd) {
	// TODO Auto-generated constructor stub
	fd_=fd;
}

BPlusTree::BPlusTree(int fd, int indexHeaderPageNumber) {
	//	DEBUG_B("Creating Bplus tree with index header page number : "<<indexHeaderPageNumber)
	fd_ = fd;
	indexHeaderPage_ = new IndexHeader(fd_,indexHeaderPageNumber);
	//DEBUG("Index header page is created for this bplus tree")
}

BPlusTree::~BPlusTree() {
	// TODO Auto-generated destructor stub
	//	DEBUG_B("In Bplus tree destuctor")
	delete indexHeaderPage_;
}

int BPlusTree::searchInBPlusTree(const char* key) {
	int rootPageNumber = indexHeaderPage_->getRootPageNumber();
	int treeLevel = indexHeaderPage_->getHeightOfTree();
	int leafPageNumber = -1;
	//cout <<"in search page number "<<endl;
	//cout << "tree level :" <<treeLevel <<endl;
	int currentPageNumber = rootPageNumber;
	//cout << "current index page number" <<currentPageNumber<<endl;
	for (int i = treeLevel; i > 0; i--) {
		//search in index node or leaf node till we find leaf node where new record is inserted
		IndexNode indexNode(fd_,indexHeaderPage_, currentPageNumber);
		//cout<<"in search page number "<<endl;
		currentPageNumber = indexNode.searchInIndexNode(key);
		//		DEBUG_B("new current page number "<<currentPageNumber);
		leafPageNumber = currentPageNumber;
	}
	//DEBUG_B("returning page number"<<currentPageNumber)
	return currentPageNumber;
}

int BPlusTree::insertIntoBPlusTree(const char* key, RIDStruct &rid) {
	/*if (BPLUSTREE_DEBUG == true) {
		BPlusTreeUtil::displayKey(key, indexHeaderPage_);
		DEBUG_B(endl)
	}*/
	if (indexHeaderPage_->getRootPageNumber() == -1) {
		LeafNode leafNode(fd_);
		//cout << "before create leaf page"<<endl ;
		leafNode.createLeafPage(indexHeaderPage_);
		//cout << "after create leaf page"<<endl ;
		char newKey[indexHeaderPage_->getKeySize()];
		//		memset(newKey, '\0', );
		//		strncpy(newKey, key, strlen(key));
		leafNode.insertIntoLeafPage(key, rid);
		cout << "after insert into leafpage" << endl;
		indexHeaderPage_->setNoOfKeys(indexHeaderPage_->getNoOfKeys()
				+ 1);
		//cout<< "after set no of keys"<<endl;
	} else {
		//cout << "in else"<<endl;
		int insertLeafPageNumber = -1;
		insertLeafPageNumber = searchInBPlusTree(key);
		//cout << "insert leaf pageNumber :" << insertLeafPageNumber <<endl;
		LeafNode leafNode(fd_,indexHeaderPage_, insertLeafPageNumber);
		//		DEBUG_B("no of records in this leaf node "<<leafNode.getNoOfRecordsInNode())
		//	DEBUG_B("leaf Page Number "<<leafNode.getPageNumber());
		//		DEBUG_B("parent of leaf Node "<<leafNode.getParentPageNumber());
		char newKey[indexHeaderPage_->getKeySize()];
		//		memset(newKey, '\0', 2000);
		//		strncpy(newKey, key, strlen(key));
		//cout << "before 2nd insert in else" <<endl;
		leafNode.insertIntoLeafPage(key, rid);
		//cout << "after 2nd insert in else" <<endl;

		indexHeaderPage_->setNoOfKeys(indexHeaderPage_->getNoOfKeys()
				+ 1);
		//cout << "indexHeaderPage no of keys:" << indexHeaderPage_->getNoOfKeys()<<endl;
//		bufMgr_->commitCache();
//					bufMgr_->hexDump(fd_,10);
//					bufMgr_->hexDump(fd_,6);
//					bufMgr_->hexDump(fd_,7);
//					bufMgr_->hexDump(fd_,8);

	}

	//DEBUG_B("ROOT PAGE "<<indexHeaderPage_->getRootPage())
		//indexHeaderPage_->setNoOfKeys(indexHeaderPage_->getNoOfKeys() + 1);

	//cout << "before success insert"<< endl;
	return SUCCESS;
}
int BPlusTree::deleteFromBPlusTree(const char* key, RIDStruct &rid) {
/*	if (BPLUSTREE_DEBUG == true) {
		BPlusTreeUtil::displayKey(key, indexHeaderPage_);
	}*/
	if (indexHeaderPage_->getRootPageNumber() == -1) {
		return 0;
	} else {
		//		DEBUG_B("DELETION BPLUS TREE "<<key)
		int rootPageNumber = indexHeaderPage_->getRootPageNumber();
		int leafPageNumber = searchInBPlusTree(key);
		//cout << "leaf page NUmber" << leafPageNumber<< endl;
		LeafNode leafNode(fd_,indexHeaderPage_, leafPageNumber);
		int status = leafNode.searchInLeafNode(key, rid);
		//cout << "status :" << status << endl;
		while (status == 2 && leafPageNumber != -1) {
			leafPageNumber = leafNode.getRightPageNumber();
			//			DEBUG_B("leaf page number "<<leafPageNumber)
			if (leafPageNumber == -1) {
				status = 1;
				break;
			}
			LeafNode leafNode(fd_,indexHeaderPage_, leafPageNumber);
			//cout << "before right page : come here "<<endl;
			status = leafNode.searchInLeafNode(key, rid);
		}

		if (status == 0 && leafPageNumber != -1) {
			//cout << "come here" << endl;
			vector<int> deletedPages;
			//LeafNode leafNode(fd_,indexHeaderPage_, leafPageNumber);
			leafNode.deleteFromLeafPage(key, rid, deletedPages);
			//cout << "after delete from leaf page 1" << endl;
			indexHeaderPage_->setNoOfKeys(
					indexHeaderPage_->getNoOfKeys() - 1);
			//cout << "after delete from leaf page " << endl;
			FreePageManager *freeMgr = new FreePageManager(fd_,1);
			//cout << "deleted pages No:" << deletedPages.size() << endl;
			for (int i = 0; i < deletedPages.size(); i++) {
				//bufMgr->freePage(deletedPages.at(i));
				//cout << "don't come here" << endl;
				freeMgr->freePage(deletedPages.at(i));
				deletedPages.erase(deletedPages.begin() + i);
			}
			delete freeMgr;
		} else {
			cout << "\n\t KEY NOT FOUND" << endl;
		}

		//cout << "after update:" << leafNode.getNoOfRecordsInNode() << endl;
	}

}

int BPlusTree::searchKeyInBPlusTree(const char *key, std::vector<
		RIDStruct>& RIDVector) {
	if (indexHeaderPage_->getRootPageNumber() == -1) {
		cout << "BPLUS TREE IS NOT YET CREATED" << endl;
		return SUCCESS;
	}
	int rootPageNumber = indexHeaderPage_->getRootPageNumber();
	int heightOfTree = indexHeaderPage_->getHeightOfTree();
	if (heightOfTree == 0) {
		LeafNode leafNode(fd_,indexHeaderPage_, rootPageNumber);
		leafNode.searchKeyInLeafNode(key, RIDVector);
	} else {
		//			IndexNode indexNode(indexHeaderPage_,rootPageNumber);
		int leafPageNumber = searchInBPlusTree(key);
		//			DEBUG_B("leaf page "<<leafPageNumber)
				//cout << " is it here? leaf page number " << leafPageNumber << endl;
				//cout << " key : "<<key <<endl;

		LeafNode leafNode(fd_,indexHeaderPage_, leafPageNumber);
		//cout << " key : "<<key <<endl;

		leafNode.searchKeyInLeafNode(key, RIDVector);
		//cout<<"Seraching DOne"<<endl;
	}
	if(RIDVector.size()==0){
		cout << "KEY NOT FOUND"<<endl;
	}
	//	int leafPageNumber=searchInBPlusTree(key);
	//	DEBUG_B(" FIND LEAF PAGE NUMBER "<<leafPageNumber)

}
int BPlusTree::display() {
	int height = indexHeaderPage_->getHeightOfTree();
	int currentPageNumber = indexHeaderPage_->getRootPageNumber();
	int startLeafPage = -1;
	if (height != 0) {
		while (currentPageNumber != -1) {
			IndexNode indexNode(fd_,indexHeaderPage_, currentPageNumber);
			indexNode.display();
			currentPageNumber = indexNode.getRightPageNumber();

		}
		height--;

	} else {
		LeafNode leafNode(fd_,indexHeaderPage_, indexHeaderPage_->getRootPageNumber());
		leafNode.display();
	}
	//	DEBUG_B("HEIGHT OF BPLUS TREE "<<indexHeaderPage_->getHeightOfTheTree())
	//	DEBUG_B("@@@@@@@@@@@@@@@@@@@ END OF DISPLAY @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@")
}
int BPlusTree::userInterface(int indexHeaderPageNumber) {
	char check = 'y';
	while (check == 'y') {
		cout << "\n PLEASE CHOOSE FOLLOWING INPUT \n" << endl;
		cout << "2. Display IndexHeaderStructure\n";
		cout << "3. Display IndexNode or LeafNode\n";
		cout << "4. Insert a Record\n";
		cout << "5. Insert a Range\n";
		cout << "6. Searching Bplustree\n";
		cout << "7. Delete a key\n";
		cout << "8. Delete a range\n";
		cout << "9. Set debug flag\n";
		cout << "10. Exit\n";
		cout << "\n\n Please Enter Input >";
		int input;
		cin >> input;
		switch (input) {
		case 1:
			cout << "NEED TO DECIDE " << endl;
			break;
		case 2: {
			cout << "\nSelected Displaying Index Header Structure\n";
			IndexHeader indexHeaderPage1(fd_,indexHeaderPageNumber);
			indexHeaderPage1.UIIndexHeaderPage();
			break;
		}
		case 3:
			cout << "\n Selected Display Index node or Leaf node" << endl;
			UIIndexOrLeafNode();
			break;
		case 4: {
			cout << "\n Insert Record UI" << endl;
			UIInsertRecord();
			break;
		}
		case 5:{
			cout<<"Enter Start key"<<endl;
			int start,end;
			cin>>start;
			cout<<"Enter end key"<<endl;
			cin>>end;
			cout<<"Enter Increment Value:"<<endl;
			int increment;
			cin>>increment;
			IntRange(start,end,increment);
			break;
		}
		case 6: {
			cout << "\n SEARCHING IN BPLUS TREE " << endl;
			UISearching();
			break;
		}
		case 10:
			cout << "\n\t\t\tEXIT\n" << endl;
			check = 'n';
			break;
		default:
			cout << "\n Please choose the option correctly" << endl;
			break;
		}
		if (input != 10) {
			cout << "\n Here in main Index " << endl;
			cout << "\n You want to check options again (y/n)" << endl;
			cin >> check;
		} else {
			break;
		}
	}
	return 0;
}


void BPlusTree::bplusTreeUILeafNode(int pageNumber) {
	int input = 1;
	do {
		LeafNode leafNode(fd_,indexHeaderPage_, pageNumber);
		leafNode.UILeafNode();
		cout << "\n\n check next/previous page using following options" << endl;
		cout << "\t1. Left leaf page" << endl;
		cout << "\t2. Right leaf page" << endl;
		cout << "\t3. Exit" << endl;

		cout << "\n Enter Input (1/2/3) >: ";
		cin >> input;
		switch (input) {
		case 1:
			pageNumber = leafNode.getLeftPageNumber();
			if (pageNumber == -1) {
				cout
						<< "\tSORRY NO MORE LEFT PAGES BECAUSE LEFT PAGE NUMBER IS -1"
						<< endl;
			}
			break;
		case 2:
			pageNumber = leafNode.getRightPageNumber();
			if (pageNumber == -1) {
				cout
						<< "\tSORRY NO MORE RIGHT PAGES BECAUSE RIGHT PAGE NUMBER IS -1"
						<< endl;
			}

			break;
		case 3:
			cout << "\nExit from UI of leaf node" << endl;
			break;
		default:
			cout << "\tPLEASE CHOOSE THE OPTIONS CORRECTLY" << endl;
			break;
		}
	} while (input != 3 && pageNumber != -1);
}
void BPlusTree::bplusTreeUIIndexNode(int pageNumber) {
	int input = 1;
	do {
		IndexNode indexNode(fd_,indexHeaderPage_, pageNumber);
		indexNode.UIIndexNode();
		cout << "\n\n check next/previous page using following options" << endl;
		cout << "\t1. Left index page" << endl;
		cout << "\t2. Right index page" << endl;
		cout << "\t3. Exit" << endl;

		cout << "\n Enter Input (1/2/3) >: ";
		cin >> input;
		switch (input) {
		case 1:
			pageNumber = indexNode.getLeftPageNumberOfIndexNode();
			if (pageNumber == -1) {
				cout
						<< "\tSORRY NO MORE LEFT PAGES BECAUSE LEAF PAGE NUMBER IS -1"
						<< endl;
			}
			break;
		case 2:
			pageNumber = indexNode.getRightPageNumber();
			if (pageNumber == -1) {
				cout
						<< "\tSORRY NO MORE RIGHT PAGES BECUASE RIGHT PAGE NUMBER IS -1"
						<< endl;
			}

			break;
		case 3:
			cout << "\nExit from UI of index node" << endl;
			break;
		default:
			cout << "\tPLEASE CHOOSE OPTIONS CORRECTLY" << endl;
			break;
		}
	} while (input != 3 && pageNumber != -1);
}

void BPlusTree::findLeafIndexPages(std::vector<int> &leafPages,
		std::vector<int> &indexPages) {
	if (indexHeaderPage_->getHeightOfTree() == 0) {
		if (indexHeaderPage_->getRootPageNumber() != -1) {
			leafPages.push_back(indexHeaderPage_->getRootPageNumber());
		}
	} else {
		int rootPageNumber = indexHeaderPage_->getRootPageNumber();
		indexPages.push_back(rootPageNumber);
		IndexNode indexNode(fd_,indexHeaderPage_, rootPageNumber);
		indexNode.findPages(leafPages, indexPages);
	}
}

void BPlusTree::displayIndexPages(std::vector<int> indexPageVector) {
	if (indexPageVector.size() >= 1) {
		cout << "\nIndex Pages Of Tree : ";
		for (int i = 0; i < indexPageVector.size() - 1; i++) {
			cout << indexPageVector.at(i) << ", ";
		}
		cout << indexPageVector.at(indexPageVector.size() - 1) << endl;
	} else {
		cout << "\n\t NO INDEX PAGES ARE PRESENT IN THIS TREE\n";
	}
}
void BPlusTree::displayLeafPages(std::vector<int> leafPageVector) {
	if (leafPageVector.size() >= 1) {
		cout << "\nLeaf Pages Of Tree : ";
		for (int i = 0; i < leafPageVector.size() - 1; i++) {
			cout << leafPageVector.at(i) << ", ";
		}
		cout << leafPageVector.at(leafPageVector.size() - 1) << endl;
	} else {
		cout << "\n\t NO LEAF PAGES ARE PRESENT IN THIS TREE\n";
	}
}
int BPlusTree::findInIndexPages(std::vector<int> indexPageVector,
		int pageNumber) {
	for (int i = 0; i < indexPageVector.size(); i++) {
		if (indexPageVector.at(i) == pageNumber) {
			return 1;
		}
	}
	return 0;
}
int BPlusTree::findInLeafPages(std::vector<int> leafPageVector, int pageNumber) {
	for (int i = 0; i < leafPageVector.size(); i++) {
		if (leafPageVector.at(i) == pageNumber) {
			return 1;
		}
	}
	return 0;
}
void BPlusTree::UIIndexOrLeafNode() {
	int inputIndexLeaf = 1;
	int pageNumber = 1;
	int status = 1;
	while (inputIndexLeaf != 3 && pageNumber != -1) {

		int valid;
		do {
			cout << " Please select following " << endl;
			cout << "1. Index Node display\t" << endl;
			cout << "2. Leaf Node display\t" << endl;
			cout << "3. Exit" << endl;
			cout << "\n Input >";
			cin >> inputIndexLeaf;
			cin.ignore(numeric_limits<int>::max(), '\n');
			if (!cin || cin.gcount() != 1) {
				cout << "\n\tPLEASE ENTER VALID INPUT (INTEGER ONLY)" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				valid = 0;
			} else {
				valid = 1;
			}
		} while (valid == 0);

		vector<int> leafPageVector;
		vector<int> indexPageVector;
		findLeafIndexPages(leafPageVector, indexPageVector);
		switch (inputIndexLeaf) {
		case 1:
			displayIndexPages(indexPageVector);
			//			cout << "\n size : " << indexPageVector.size() << endl;
			if (indexPageVector.size() >= 1) {
				do {
					do {
						cout << "Enter Index Node page number : ";
						cin >> pageNumber;
						cin.ignore(numeric_limits<int>::max(), '\n');
						if (!cin || cin.gcount() != 1) {
							cout
									<< "\n\tPLEASE ENTER VALID INPUT (INTEGER ONLY)"
									<< endl;
							cin.clear();
							cin.ignore(1000, '\n');
							valid = 0;
						} else {
							valid = 1;
						}
					} while (valid == 0);

					status = findInIndexPages(indexPageVector, pageNumber);
					if (status == 0) {
						cout
								<< "\tGIVEN PAGE NUMBER IS NOT AN INDEX PAGE. TRY AGAIN"
								<< endl;
					}
				} while (status == 0);
				bplusTreeUIIndexNode(pageNumber);
			}
			break;
		case 2:
			displayLeafPages(leafPageVector);
			if (leafPageVector.size() >= 1) {
				do {
					do {
						cout << "Enter Leaf Node page number : ";
						cin >> pageNumber;
						cin.ignore(numeric_limits<int>::max(), '\n');
						if (!cin || cin.gcount() != 1) {
							cout
									<< "\n\tPLEASE ENTER VALID INPUT (INTEGER ONLY)"
									<< endl;
							cin.clear();
							cin.ignore(1000, '\n');
							valid = 0;
						} else {
							valid = 1;
						}
					} while (valid == 0);

					status = findInLeafPages(leafPageVector, pageNumber);
					if (status == 0) {
						cout
								<< "\tGIVEN PAGE NUMBER IS NOT A LEAF PAGE. TRY AGAIN"
								<< endl;
					}
				} while (status == 0);
				bplusTreeUILeafNode(pageNumber);
			}
			break;
		case 3:
			cout << "\n\tEXIT from UI of index node and leaf node " << endl;
			break;
		default:
			cout << "PLEASE CHOOSE OPTIONS CORRECTLY";
			break;
		}
	}
}
void BPlusTree::IntRange(int range1, int range2, int incrementFactor) {
	int range;
	range = range2 - range1 + 1;
	//	unsigned first = time(NULL);
	//	srand(first);
	int intKey = range1, count = 0;
	char totalKey[indexHeaderPage_->getKeySize()];
	memset(totalKey, 0, indexHeaderPage_->colSizes_[0]);
	RIDStruct rid;
	time_t start, end;
	double diffTime;
	time(&start);
	for (int i = 0; intKey <= range2; i++) {
		//cout << "int key is :" <<intKey<<endl;
		//memcpy(totalKey, &intKey, sizeof(int));
		rid.pageNumber = i;
		rid.slotNumber = (short) i;
		cout << " in range insert :" << CommonUtil::int_to_string(intKey).c_str() <<"rid: "<< rid.pageNumber <<rid.slotNumber<< endl;
		insertIntoBPlusTree(CommonUtil::int_to_string(intKey).c_str(), rid);
		count++;
		intKey = intKey + incrementFactor;
	}
	time(&end);
	diffTime = difftime(end, start);
	cout << "\t" << count << " keys are inserted" << endl;
	cout << "TOTAL TIME TO COMPLETE (in seconds): " << diffTime << endl;
}

void BPlusTree::insertFloatRange(float range1, float range2,
		float incrementFactor) {
	float floatKey = range1;
	int count = 0;
	char totalKey[indexHeaderPage_->getKeySize()];
	memset(totalKey, '\0', indexHeaderPage_->colSizes_[0]);
	RIDStruct rid;
	time_t start, end;
	double diffTime;
	time(&start);
	for (int i = 0; floatKey <= range2; i++) {
		memcpy(totalKey, &floatKey, sizeof(float));
		rid.pageNumber = i;
		rid.slotNumber = (unsigned short) i;
		insertIntoBPlusTree(totalKey, rid);
		count++;
		floatKey = floatKey + incrementFactor;
	}
	time(&end);
	diffTime = difftime(end, start);
	cout << "\t" << count << " keys are inserted" << endl;
	cout << "\tTOTAL TIME TO COMPLETE (in seconds): " << diffTime << endl;
}
void BPlusTree::insertDoubleRange(double range1, double range2,
		double incrementFactor) {
	double doubleKey = range1;
	int count = 0;
	char totalKey[indexHeaderPage_->getKeySize()];
	memset(totalKey, '\0', indexHeaderPage_->colSizes_[0]);
	RIDStruct rid;
	time_t start, end;
	double diffTime;
	time(&start);
	for (int i = 0; doubleKey <= range2; i++) {
		memcpy(totalKey, &doubleKey, sizeof(double));
		rid.pageNumber = i;
		rid.slotNumber = (unsigned short) i;
		insertIntoBPlusTree(totalKey, rid);
		count++;
		doubleKey = doubleKey + incrementFactor;
	}
	time(&end);
	diffTime = difftime(end, start);
	cout << "\t" << count << " keys are inserted" << endl;
	cout << "\tTOTAL TIME TO COMPLETE (in seconds): " << diffTime << endl;
}
void BPlusTree::insertLongRange(long range1, long range2, long incrementFactor) {
	long longKey = range1;
	int count = 0;
	char totalKey[indexHeaderPage_->getKeySize()];
	memset(totalKey, '\0', indexHeaderPage_->colSizes_[0]);
	RIDStruct rid;
	time_t start, end;
	double diffTime;
	time(&start);
	for (int i = 0; longKey <= range2; i++) {
		memcpy(totalKey, &longKey, sizeof(long));
		rid.pageNumber = i;
		rid.slotNumber = (unsigned short) i;
		insertIntoBPlusTree(totalKey, rid);
		count++;
		longKey = longKey + incrementFactor;
	}
	time(&end);
	diffTime = difftime(end, start);
	cout << "\t" << count << " keys are inserted" << endl;
	cout << "\tTOTAL TIME TO COMPLETE (in seconds): " << diffTime << endl;
}
void BPlusTree::insertVarCharRange(int totalNumOfKeys) {
	if (totalNumOfKeys <= 1000100) {
		ifstream in("keys");
		if (!in) {
			cout << "can not open file" << endl;
			cout << "file keys is not present in the directory" << endl;
		} else {
			int count = 0, p = 0, s = 0;
			RIDStruct rid;
			char str[indexHeaderPage_->colSizes_[0]];
			char tempTotalKey[30];
			memset(tempTotalKey, '\0', 30);
			char totalKey[indexHeaderPage_->colSizes_[0]];
			memset(totalKey, '\0', indexHeaderPage_->colSizes_[0]);
			time_t start, end;
			double diffTime;
			time(&start);
			while (in) {
				in >> tempTotalKey;
				in >> p;
				in >> s;
				rid.pageNumber = p;
				rid.slotNumber = (unsigned short) s;
				//		memcpy(totalKey, tempTotalKey, indexHeaderPage_->colSizes_[0]);
				strncpy(totalKey, tempTotalKey,
						indexHeaderPage_->colSizes_[0]);
				insertIntoBPlusTree(totalKey, rid);
				count++;
				if (count == totalNumOfKeys)
					break;
			}

			in.close();
			time(&end);
			diffTime = difftime(end, start);
			cout << "\n\t" << totalNumOfKeys << " keys are inserted " << endl;
			cout << "\tTOTAL TIME TO COMPLETE (in seconds): " << diffTime
					<< endl;
		}
	} else {
		cout << "\n\tTotal number of keys should be less than 1000100" << endl;
	}
}
void BPlusTree::UIInsertRange() {
	int numOfColumns = indexHeaderPage_->getNoOfColumns();
	for (int i = 0; i < numOfColumns; i++) {
		int colType = indexHeaderPage_->colTypes_[i];
		int intRange1, intRange2, totalNoOfKeys, incrementFactor;
		float floatRange1, floatRange2, floatIncrementFactor;
		double doubleRange1, doubleRange2, doubleIncrementFactor;
		long longRange1, longRange2, longIncrementFactor;
		char key[indexHeaderPage_->colSizes_[i]];
		int p = 0, s = 0;
		int valid;
		switch (colType) {
		case COL_INTEGER:
			do {
				cout << "\nEnter integer starting range : ";
				cin >> intRange1;
				cin.ignore(numeric_limits<int>::max(), '\n');
				if (!cin || cin.gcount() != 1) {
					cout << "\n\tPLEASE ENTER VALID INPUT (INTEGER ONLY)"
							<< endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			do {
				cout << "\nEnter integer ending range   : ";
				cin >> intRange2;
				cin.ignore(numeric_limits<int>::max(), '\n');
				if (!cin || cin.gcount() != 1) {
					cout << "\n\tPLEASE ENTER VALID INPUT (INTEGER ONLY)"
							<< endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			do {
				cout << "\nEnter increment factor       : ";
				cin >> incrementFactor;
				cin.ignore(numeric_limits<int>::max(), '\n');
				if (!cin || cin.gcount() != 1) {
					cout << "\n\tPLEASE ENTER VALID INPUT (INTEGER ONLY)"
							<< endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);

			//DEAL WITH THIS! :O
			//insertIntRange(intRange1, intRange2, incrementFactor);
			break;
		case COL_FLOAT:
			do {
				cout << "\n Enter float starting range : ";
				cin >> floatRange1;
				cin.ignore(numeric_limits<float>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (FLOAT)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			do {
				cout << "\n Enter float ending range : ";
				cin >> floatRange2;
				cin.ignore(numeric_limits<float>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (FLOAT)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			do {
				cout << "\n Enter increment factor : ";
				cin >> floatIncrementFactor;
				cin.ignore(numeric_limits<float>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (FLOAT)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			insertFloatRange(floatRange1, floatRange2, floatIncrementFactor);
			break;
		case COL_DOUBLE:
			do {
				cout << "\n Enter double starting range : ";
				cin >> doubleRange1;
				cin.ignore(numeric_limits<double>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (DOUBLE)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			do {
				cout << "\n Enter double ending range : ";
				cin >> doubleRange2;
				cin.ignore(numeric_limits<double>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (DOUBLE)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			do {
				cout << "\n Enter increment factor : ";
				cin >> doubleIncrementFactor;
				cin.ignore(numeric_limits<double>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (DOUBLE)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);

			insertDoubleRange(doubleRange1, doubleRange2, doubleIncrementFactor);
			break;
		case COL_LONG:
			do {
				cout << "\n Enter long starting range : ";
				cin >> longRange1;
				cin.ignore(numeric_limits<long>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (LONG)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			do {
				cout << "\n Enter long ending range : ";
				cin >> longRange2;
				cin.ignore(numeric_limits<long>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (LONG)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			do {
				cout << "\n Enter increment factor : ";
				cin >> longIncrementFactor;
				cin.ignore(numeric_limits<long>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (LONG)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);

			insertLongRange(longRange1, longRange2, longIncrementFactor);
			break;
		case COL_VARCHAR:
			do {
				cout << "\nEnter total number of keys  : ";
				cin >> totalNoOfKeys;
				cin.ignore(numeric_limits<int>::max(), '\n');
				if (!cin || cin.gcount() != 1) {
					cout << "\n\tPLEASE ENTER VALID INPUT (INTEGER ONLY)"
							<< endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			insertVarCharRange(totalNoOfKeys);
			break;
		}
	}

}
/*void BPlusTree::insertAllRanges(char* range1,char* range2,char* incrementFactor)
 {

 }
 */
/*void BPlusTree::UISetDebugFlag() {
	cout << "\nSET DEBUG_B FLAG UI\n";
	cout << "Currently Debug flag : ";
	if (BPLUSTREE_DEBUG == true) {
		cout << "SET";
	} else {
		cout << "UNSET";
	}
	int debugFlag;
	do {
		int valid;
		do {
			cout << "\n\nSET(1) / UNSET(0) : ";
			cin >> debugFlag;
			cin.ignore(numeric_limits<int>::max(), '\n');
			if (!cin || cin.gcount() != 1) {
				cout << "\n\tPLEASE ENTER VALID INPUT (INTEGER ONLY)" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				valid = 0;
			} else {
				valid = 1;
			}
		} while (valid == 0);

		if (debugFlag == 1) {
			BPLUSTREE_DEBUG = true;
			cout << "\n\tDEBUG FLAG IS SETTED" << endl;
		} else if (debugFlag == 0) {
			cout << "\n\tDEBUG FLAG IS UNSETTED" << endl;
			BPLUSTREE_DEBUG = false;
		} else {
			cout << "\n\tPLEASE ENTER VALID INPUT (1/0)" << endl;
		}
	} while (debugFlag != 0 && debugFlag != 1);
}*/

void BPlusTree::UIDeleteKey() {
	int numOfColumns = indexHeaderPage_->getNoOfColumns();
	char totalKey[indexHeaderPage_->getKeySize()];
	memset(totalKey, '\0', indexHeaderPage_->getKeySize());
	int offset = 0;
	for (int i = 0; i < numOfColumns; i++) {
		int colType = indexHeaderPage_->colTypes_[i];
		cout << "\n Enter Key (field" << (i + 1) << ") to Delete : ";
		int valid;
		int intKey;
		//			char key[indexHeaderPage_->getKeySize()];
		float floatKey;
		double doubleKey;
		long longKey;
		char varCharKey[indexHeaderPage_->colSizes_[i]],
				varCharKey1[indexHeaderPage_->colSizes_[i]];
		switch (colType) {
		case COL_INTEGER:
			do {
				cin >> intKey;
				cin.ignore(numeric_limits<int>::max(), '\n');
				if (!cin || cin.gcount() != 1) {
					cout << "\n\tPLEASE ENTER VALID INPUT (INTEGER)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "\nEnter Key (field" << (i + 1) << ") to Delete : ";
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			memcpy(&totalKey[offset], &intKey, sizeof(int));
			break;
		case COL_FLOAT:
			do {
				cin >> floatKey;
				cin.ignore(numeric_limits<float>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (FLOAT)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "\nEnter Key (field" << (i + 1) << ") to Delete : ";
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			memcpy(&totalKey[offset], &floatKey, sizeof(float));
			break;
		case COL_DOUBLE:
			do {
				cin >> doubleKey;
				cin.ignore(numeric_limits<double>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (DOUBLE)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "\nEnter Key (field" << (i + 1) << ") to Delete : ";
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			memcpy(&totalKey[offset], &doubleKey, sizeof(double));
			break;
		case COL_LONG:
			do {
				cin >> longKey;
				cin.ignore(numeric_limits<long>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (LONG)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "\nEnter Key (field" << (i + 1) << ") to Delete : ";
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			memcpy(&totalKey[offset], &longKey, sizeof(long));
			break;
		case COL_VARCHAR:
			cin >> varCharKey;
			memcpy(&totalKey[offset], varCharKey,
					indexHeaderPage_->colSizes_[i]);
			break;
		default:
			cin >> varCharKey1;
			memcpy(&totalKey[offset], varCharKey1,
					indexHeaderPage_->colSizes_[i]);
			break;
		}
		offset = offset + indexHeaderPage_->colSizes_[i];
	}
	RIDStruct rid;
	cout << "\nRID values [Page Number] : ";
	cin >> rid.pageNumber;
	cout << "\nRID values [Slot Number] : ";
	cin >> rid.slotNumber;
	deleteFromBPlusTree(totalKey, rid);

	//	cout << "\n\tRECORD DELETED\n";
}
void BPlusTree::UIDeleteRange() {
	int numOfColumns = indexHeaderPage_->getNoOfColumns();
	for (int i = 0; i < numOfColumns; i++) {
		int colType = indexHeaderPage_->colTypes_[i];
		int valid;
		int intRange1, intRange2;
		float floatRange1, floatRange2;
		double doubleRange1, doubleRange2;
		long longRange1, longRange2;
		char key[indexHeaderPage_->colSizes_[i]];
		switch (colType) {
		case COL_INTEGER:
			do {
				cout << "\nEnter integer starting range : ";
				cin >> intRange1;
				cin.ignore(numeric_limits<int>::max(), '\n');
				if (!cin || cin.gcount() != 1) {
					cout << "\n\tPLEASE ENTER VALID INPUT (INTEGER)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			do {
				cout << "\nEnter integer ending range   : ";
				cin >> intRange2;
				cin.ignore(numeric_limits<int>::max(), '\n');
				if (!cin || cin.gcount() != 1) {
					cout << "\n\tPLEASE ENTER VALID INPUT (INTEGER)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			deleteIntRange(intRange1, intRange2);
			break;
		case COL_FLOAT:
			do {
				cout << " \n Enter float starting range : ";
				cin >> floatRange1;
				cin.ignore(numeric_limits<float>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (FLOAT)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			do {
				cout << " \n Enter float ending range : ";
				cin >> floatRange2;
				cin.ignore(numeric_limits<float>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (FLOAT)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			deleteFloatRange(floatRange1, floatRange2);
			break;
		case COL_DOUBLE:
			do {
				cout << "\n Enter double starting range : ";
				cin >> doubleRange1;
				cin.ignore(numeric_limits<double>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (DOUBLE)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			do {
				cout << "\n Enter double ending range : ";
				cin >> doubleRange2;
				cin.ignore(numeric_limits<double>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (DOUBLE)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			deleteDoubleRange(doubleRange1, doubleRange2);
			break;
		case COL_LONG:
			do {
				cout << "\n Enter long starting range : ";
				cin >> longRange1;
				cin.ignore(numeric_limits<long>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (LONG)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);
			do {
				cout << "\n Enter long ending range : ";
				cin >> longRange2;
				cin.ignore(numeric_limits<long>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (LONG)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
				} else {
					valid = 1;
				}
			} while (valid == 0);

			deleteLongRange(longRange1, longRange2);
			break;
		case COL_VARCHAR:
			cout << "\n\tDELETION RANGE FOR CHAR IS NOT VALID \n";
			break;
		}
	}

}
void BPlusTree::deleteIntRange(int range1, int range2) {
	if (range1 <= range2) {
		char totalKey1[indexHeaderPage_->getKeySize()];
		char totalKey2[indexHeaderPage_->getKeySize()];
		memset(totalKey1, '\0', indexHeaderPage_->colSizes_[0]);
		memcpy(totalKey1, &range1, sizeof(int));
		memcpy(totalKey2, &range2, sizeof(int));
		int startLeafPage = searchInBPlusTree(totalKey1);
		vector<RIDStruct> RIDVector;
		vector<string> keyVector;
		storeTillRequiredKey(startLeafPage, totalKey1, totalKey2, RIDVector,
				keyVector);
		RIDStruct rid;
		/*
		 for (int j = 0; j < RIDVector.size(); j++) {
		 rid = RIDVector.at(j);
		 string x;
		 x = keyVector.at(j);
		 cout << "      key :";
		 BPlusTreeUtil::displayKey(x.c_str(), indexHeaderPage_);
		 cout << "\tPage No : " << rid.pageNumber << "\tSlot No : "
		 << rid.slotNumber << endl;
		 }
		 */
		time_t start, end;
		double diffTime;
		time(&start);
		for (int i = 0; i < RIDVector.size(); i++) {
			rid = RIDVector.at(i);
			string x;
			x = keyVector.at(i);
			deleteFromBPlusTree(x.c_str(), rid);
		}
		time(&end);
		diffTime = difftime(end, start);
		cout << "\n\tRECORDS ARE DELETED WITH IN SPECIED RANGE" << endl;
		cout << "\tTotal time for deletion of all records : " << diffTime
				<< endl;

	} else {
		cout << "\tPlease enter valid ranges (key1<=key2)" << endl;
	}
	/*	for(int i=0;i<BPlusTree::deletedPages.size();i++)
	 {
	 cout<<" deleted pages : "<<deletedPages.at(i)<<endl;
	 }
	 */
}
void BPlusTree::deleteFloatRange(float range1, float range2) {
	if (range1 <= range2) {
		char totalKey1[indexHeaderPage_->getKeySize()];
		char totalKey2[indexHeaderPage_->getKeySize()];
		memset(totalKey1, '\0', indexHeaderPage_->colSizes_[0]);
		memcpy(totalKey1, &range1, sizeof(float));
		memcpy(totalKey2, &range2, sizeof(float));
		int startLeafPage = searchInBPlusTree(totalKey1);
		vector<RIDStruct> RIDVector;
		vector<string> keyVector;
		storeTillRequiredKey(startLeafPage, totalKey1, totalKey2, RIDVector,
				keyVector);
		RIDStruct rid;
		/*
		 for (int j = 0; j < RIDVector.size(); j++) {
		 rid = RIDVector.at(j);
		 string x;
		 x = keyVector.at(j);
		 cout << "      key :";
		 BPlusTreeUtil::displayKey(x.c_str(), indexHeaderPage_);
		 cout << "\tPage No : " << rid.pageNumber << "\tSlot No : "
		 << rid.slotNumber << endl;
		 }
		 */
		time_t start, end;
		double diffTime;
		time(&start);
		for (int i = 0; i < RIDVector.size(); i++) {
			rid = RIDVector.at(i);
			string x;
			x = keyVector.at(i);
			deleteFromBPlusTree(x.c_str(), rid);
		}
		time(&end);
		diffTime = difftime(end, start);
		cout << "\n\tRECORDS ARE DELETED WITH IN SPECIED RANGE" << endl;
		cout << "\tTotal time to delete all records : " << diffTime << endl;

	} else {
		cout << "Please enter valid ranges (key1<=key2)" << endl;
	}
	/*	for(int i=0;i<BPlusTree::deletedPages.size();i++)
	 {
	 cout<<" deleted pages : "<<deletedPages.at(i)<<endl;
	 }
	 */
}
void BPlusTree::deleteDoubleRange(double range1, double range2) {
	if (range1 <= range2) {
		char totalKey1[indexHeaderPage_->getKeySize()];
		char totalKey2[indexHeaderPage_->getKeySize()];
		memset(totalKey1, '\0', indexHeaderPage_->colSizes_[0]);
		memcpy(totalKey1, &range1, sizeof(double));
		memcpy(totalKey2, &range2, sizeof(double));
		int startLeafPage = searchInBPlusTree(totalKey1);
		vector<RIDStruct> RIDVector;
		vector<string> keyVector;
		storeTillRequiredKey(startLeafPage, totalKey1, totalKey2, RIDVector,
				keyVector);
		RIDStruct rid;
		/*
		 for (int j = 0; j < RIDVector.size(); j++) {
		 rid = RIDVector.at(j);
		 string x;
		 x = keyVector.at(j);
		 cout << "      key :";
		 BPlusTreeUtil::displayKey(x.c_str(), indexHeaderPage_);
		 cout << "\tPage No : " << rid.pageNumber << "\tSlot No : "
		 << rid.slotNumber << endl;
		 }
		 */
		time_t start, end;
		double diffTime;
		time(&start);
		for (int i = 0; i < RIDVector.size(); i++) {
			rid = RIDVector.at(i);
			string x;
			x = keyVector.at(i);
			deleteFromBPlusTree(x.c_str(), rid);
		}
		time(&end);
		diffTime = difftime(end, start);
		cout << "\n\tRECORDS ARE DELETED WITH IN SPECIED RANGE" << endl;
		cout << "\tTotal time to delete all keys : " << diffTime << endl;
	} else {
		cout << "Please enter valid ranges (key1<=key2)" << endl;
	}
	/*	for(int i=0;i<BPlusTree::deletedPages.size();i++)
	 {
	 cout<<" deleted pages : "<<deletedPages.at(i)<<endl;
	 }
	 */
}
void BPlusTree::deleteLongRange(long range1, long range2) {
	if (range1 <= range2) {
		char totalKey1[indexHeaderPage_->getKeySize()];
		char totalKey2[indexHeaderPage_->getKeySize()];
		memset(totalKey1, '\0', indexHeaderPage_->colSizes_[0]);
		memcpy(totalKey1, &range1, sizeof(long));
		memcpy(totalKey2, &range2, sizeof(long));
		int startLeafPage = searchInBPlusTree(totalKey1);
		vector<RIDStruct> RIDVector;
		vector<string> keyVector;
		storeTillRequiredKey(startLeafPage, totalKey1, totalKey2, RIDVector,
				keyVector);
		RIDStruct rid;
		/*
		 for (int j = 0; j < RIDVector.size(); j++) {
		 rid = RIDVector.at(j);
		 string x;
		 x = keyVector.at(j);
		 cout << "      key :";
		 BPlusTreeUtil::displayKey(x.c_str(), indexHeaderPage_);
		 cout << "\tPage No : " << rid.pageNumber << "\tSlot No : "
		 << rid.slotNumber << endl;
		 }
		 */
		time_t start, end;
		double diffTime;
		time(&start);
		for (int i = 0; i < RIDVector.size(); i++) {
			rid = RIDVector.at(i);
			string x;
			x = keyVector.at(i);
			deleteFromBPlusTree(x.c_str(), rid);
		}
		time(&end);
		diffTime = difftime(end, start);
		cout << "\n\tRECORDS ARE DELETED WITH IN SPECIED RANGE" << endl;
		cout << "\tTotal time to delete all records : " << diffTime << endl;
	} else {
		cout << "Please enter valid ranges (key1<=key2)" << endl;
	}
	/*	for(int i=0;i<BPlusTree::deletedPages.size();i++)
	 {
	 cout<<" deleted pages : "<<deletedPages.at(i)<<endl;
	 }
	 */
}
void BPlusTree::storeTillRequiredKey(int startLeafPage, const char* totalKey1,
		const char* totalKey2, std::vector<RIDStruct> &RIDVector, std::vector<
				string> &keyVector) {
	char tempKey[indexHeaderPage_->getKeySize()];
	RIDStruct rid;
	//	DEBUG_B("start leaf page "<<startLeafPage)
	while (startLeafPage != -1) {
		//		DEBUG_B(" iam leaf page "<<startLeafPage)
		LeafNode leafNode(fd_,indexHeaderPage_, startLeafPage);
		int i;
		for (i = 0; i < leafNode.getNoOfRecordsInNode(); i++) {
			memset(tempKey, '\0', indexHeaderPage_->getKeySize());
			leafNode.getKeyAndRID(i, tempKey, rid);
			if (((BPlusTreeUtil::keyCompare(tempKey, totalKey1,
					indexHeaderPage_) == 1) || (BPlusTreeUtil::keyCompare(
					tempKey, totalKey1, indexHeaderPage_) == 0))
					&& ((BPlusTreeUtil::keyCompare(tempKey, totalKey2,
							indexHeaderPage_) == -1)
							|| (BPlusTreeUtil::keyCompare(tempKey, totalKey2,
									indexHeaderPage_) == 0))) {
				//				DEBUG_B("IAM FINE")
				RIDVector.push_back(rid);
				string str(tempKey, indexHeaderPage_->getKeySize());
				keyVector.push_back(str);
			}
			if (BPlusTreeUtil::keyCompare(tempKey, totalKey2, indexHeaderPage_)
					== 1) {
				break;
			}
		}
		if (i == leafNode.getNoOfRecordsInNode()) {
			startLeafPage = leafNode.getRightPageNumber();
		} else {
			break;
		}
	}
}
void BPlusTree::UISetFanoutOfTree() {
	cout << "\n\tSET FANOUT" << endl;
	int newFanout;
	do {
		int valid;
		do {
			cout << "\n\tEnter fanout of tree :";
			cin >> newFanout;
			cin.ignore(numeric_limits<int>::max(), '\n');
			if (!cin || cin.gcount() != 1) {
				cout << "\n\tPLEASE ENTER VALID INPUT (INTEGER ONLY)" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				valid = 0;
			} else {
				valid = 1;
			}
		} while (valid == 0);
		if (newFanout < 1) {
			cout << "Please enter valid fanout" << endl;
		}
	} while (newFanout < 1);
	indexHeaderPage_->setFanout(newFanout);
	indexHeaderPage_->setMaxNoOfRecordsInLeaf(newFanout);
	cout << "\nFANOUT IS SET TO :" << newFanout << endl;
}
void BPlusTree::UIInsertRecord() {
	int numOfColumns = indexHeaderPage_->getNoOfColumns();
	char totalKey[indexHeaderPage_->getKeySize()];
	memset(totalKey, '\0', indexHeaderPage_->getKeySize());
	int offset = 0;
	for (int i = 0; i < numOfColumns; i++) {
		int colType = indexHeaderPage_->colTypes_[i];
		int valid;
		int intKey;
		float floatKey;
		double doubleKey;
		long longKey;
		char varCharKey[indexHeaderPage_->colSizes_[i]],
				varCharKey1[indexHeaderPage_->colSizes_[i]];
		cout << "\n Enter Key (field" << (i + 1) << ") to Insert : ";
		switch (colType) {
		case COL_INTEGER:
			do {
				cin >> intKey;
				cin.ignore(numeric_limits<int>::max(), '\n');
				if (!cin || cin.gcount() != 1) {
					cout << "\n\tPLEASE ENTER VALID INPUT (INTEGER ONLY)"
							<< endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
					cout << "\n Enter Key (field" << (i + 1)
							<< ") to Insert : ";
				} else {
					valid = 1;
				}
			} while (valid == 0);
			memcpy(&totalKey[offset], &intKey, sizeof(int));
			break;
		case COL_FLOAT:
			do {
				cin >> floatKey;
				cin.ignore(numeric_limits<float>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (FLOAT ONLY)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
					cout << "\n Enter Key (field" << (i + 1)
							<< ") to Insert : ";
				} else {
					valid = 1;
				}
			} while (valid == 0);
			memcpy(&totalKey[offset], &floatKey, sizeof(float));
			break;
		case COL_DOUBLE:
			do {
				cin >> doubleKey;
				cin.ignore(numeric_limits<double>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (DOUBLE ONLY)"
							<< endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
					cout << "\n Enter Key (field" << (i + 1)
							<< ") to Insert : ";
				} else {
					valid = 1;
				}
			} while (valid == 0);
			memcpy(&totalKey[offset], &doubleKey, sizeof(double));
			break;
		case COL_LONG:
			do {
				cin >> longKey;
				cin.ignore(numeric_limits<long>::max(), '\n');
				if (cin.fail()) {
					cout << "\n\tPLEASE ENTER VALID INPUT (LONG ONLY)" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					valid = 0;
					cout << "\n Enter Key (field" << (i + 1)
							<< ") to Insert : ";
				} else {
					valid = 1;
				}
			} while (valid == 0);
			memcpy(&totalKey[offset], &longKey, sizeof(long));
			break;
		case COL_VARCHAR:
			cin >> varCharKey;
			memcpy(&totalKey[offset], varCharKey,
					indexHeaderPage_->colSizes_[i]);
			break;
		default:
			cin >> varCharKey1;
			memcpy(&totalKey[offset], varCharKey1,
					indexHeaderPage_->colSizes_[i]);
			break;
		}
		offset = offset + indexHeaderPage_->colSizes_[i];
	}
	RIDStruct rid;
	int valid;
	do {
		cout << "\nRID values [Page Number] : ";
		cin >> rid.pageNumber;
		cin.ignore(numeric_limits<int>::max(), '\n');
		if (cin.fail()) {
			cout << "\n\tPLEASE ENTER VALID INPUT (INTEGER ONLY)" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			valid = 0;
		} else {
			valid = 1;
		}
	} while (valid == 0);
	do {
		cout << "\nRID values [Slot Number] : ";
		cin >> rid.slotNumber;
		cin.ignore(numeric_limits<float>::max(), '\n');
		if (cin.fail()) {
			cout << "\n\tPLEASE ENTER VALID INPUT (INTEGER ONLY)" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			valid = 0;
		} else {
			valid = 1;
		}
	} while (valid == 0);
	insertIntoBPlusTree(totalKey, rid);
	cout << "\nRECORD INSERTED\n";
}
void BPlusTree::UISearching() {
	char searchOp[3];
	memset(searchOp, '\0', 3);
	int op;
//		std::vector<RIDStruct> RIDVector;
//		std::vector<string> keyVector;
//		getAllRIDS(RIDVector,keyVector);
	int inValid = 0;
	do {
		inValid = 0;
		int valid;
		do {
			cout << "\nSelect search operator " << endl;
			cout << "[ 1.==  2.>  3.>=  4.<  5.<=  6.Range_Search  0.exit ]"
					<< endl;
			cout << "\nInput >";
			cin >> op;
			cin.ignore(numeric_limits<int>::max(), '\n');
			if (!cin || cin.gcount() != 1) {
				cout << "\n\tPLEASE ENTER VALID INPUT (INTEGER ONLY)" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				valid = 0;
			} else {
				valid = 1;
			}
		} while (valid == 0);
		if (op != 1 && op != 2 && op != 3 && op != 4 && op != 5 && op != 6
				&& op != 0) {
			cout << "\n Invalid Input. Try again";
			inValid = 1;
		}
	} while (inValid == 1);
	if (op == 6)
	{
		//**********************************************************************
		int numOfColumns = indexHeaderPage_->getNoOfColumns();
		int offset = 0;
		char totalKey1[indexHeaderPage_->getKeySize()];
		char totalKey2[indexHeaderPage_->getKeySize()];
		for (int i = 0; i < numOfColumns; i++) {
			int colType = indexHeaderPage_->colTypes_[i];
			int intKey1, intKey2;
			float floatKey1, floatKey2;
			double doubleKey1, doubleKey2;
			long longKey1, longKey2;
			int valid;
			char key1[indexHeaderPage_->colSizes_[i]];
			char key2[indexHeaderPage_->colSizes_[i]];
			memset(key1, '\0', indexHeaderPage_->colSizes_[i]);
			memset(key2, '\0', indexHeaderPage_->colSizes_[i]);
			memset(totalKey1, '\0', indexHeaderPage_->getKeySize());
			memset(totalKey2, '\0', indexHeaderPage_->getKeySize());
			switch (colType) {
			case COL_INTEGER:
				do {
					cout << "\nEnter integer key range1 : ";
					cin >> intKey1;
					cin.ignore(numeric_limits<int>::max(), '\n');
					if (cin.fail()) {
						cout << "\n\tPLEASE ENTER VALID INPUT (INTEGER ONLY)"
								<< endl;
						cin.clear();
						cin.ignore(1000, '\n');
						valid = 0;
					} else {
						valid = 1;
					}
				} while (valid == 0);
				do {
					cout << "\nEnter integer key range2 : ";
					cin >> intKey2;
					cin.ignore(numeric_limits<int>::max(), '\n');
					if (cin.fail()) {
						cout << "\n\tPLEASE ENTER VALID INPUT (INTEGER ONLY)"
								<< endl;
						cin.clear();
						cin.ignore(1000, '\n');
						valid = 0;
					} else {
						valid = 1;
					}
				} while (valid == 0);
				memcpy(&totalKey1[offset], &intKey1, sizeof(int));
				memcpy(&totalKey2[offset], &intKey2, sizeof(int));
				break;
			case COL_FLOAT:
				do {
					cout << " \n Enter float key Range1 : ";
					cin >> floatKey1;
					cin.ignore(numeric_limits<float>::max(), '\n');
					if (cin.fail()) {
						cout << "\n\tPLEASE ENTER VALID INPUT (FLOAT ONLY)"
								<< endl;
						cin.clear();
						cin.ignore(1000, '\n');
						valid = 0;
					} else {
						valid = 1;
					}
				} while (valid == 0);
				do {
					cout << " \n Enter float key Range2 : ";
					cin >> floatKey2;
					cin.ignore(numeric_limits<float>::max(), '\n');
					if (cin.fail()) {
						cout << "\n\tPLEASE ENTER VALID INPUT (FLOAT ONLY)"
								<< endl;
						cin.clear();
						cin.ignore(1000, '\n');
						valid = 0;
					} else {
						valid = 1;
					}
				} while (valid == 0);

				memcpy(&totalKey1[offset], &floatKey1, sizeof(float));
				memcpy(&totalKey2[offset], &floatKey2, sizeof(float));
				break;
			case COL_DOUBLE:
				do {
					cout << " \nEnter double key Range1 : ";
					cin >> doubleKey1;
					cin.ignore(numeric_limits<double>::max(), '\n');
					if (cin.fail()) {
						cout << "\n\tPLEASE ENTER VALID INPUT (DOUBLE ONLY)"
								<< endl;
						cin.clear();
						cin.ignore(1000, '\n');
						valid = 0;
					} else {
						valid = 1;
					}
				} while (valid == 0);
				do {
					cout << " \nEnter double key Range2: ";
					cin >> doubleKey2;
					cin.ignore(numeric_limits<double>::max(), '\n');
					if (cin.fail()) {
						cout << "\n\tPLEASE ENTER VALID INPUT (DOUBLE ONLY)"
								<< endl;
						cin.clear();
						cin.ignore(1000, '\n');
						valid = 0;
					} else {
						valid = 1;
					}
				} while (valid == 0);

				memcpy(&totalKey1[offset], &doubleKey1, sizeof(double));
				memcpy(&totalKey2[offset], &doubleKey2, sizeof(double));
				break;
			case COL_LONG:
				do {
					cout << "\nEnter long key Range1 : ";
					cin >> longKey1;
					cin.ignore(numeric_limits<int>::max(), '\n');
					if (cin.fail()) {
						cout << "\n\tPLEASE ENTER VALID INPUT (LONG ONLY)"
								<< endl;
						cin.clear();
						cin.ignore(1000, '\n');
						valid = 0;
					} else {
						valid = 1;
					}
				} while (valid == 0);
				do {
					cout << "\nEnter long key Range2 : ";
					cin >> longKey2;
					cin.ignore(numeric_limits<int>::max(), '\n');
					if (cin.fail()) {
						cout << "\n\tPLEASE ENTER VALID INPUT (LONG ONLY)"
								<< endl;
						cin.clear();
						cin.ignore(1000, '\n');
						valid = 0;
					} else {
						valid = 1;
					}
				} while (valid == 0);

				memcpy(&totalKey1[offset], &longKey1, sizeof(long));
				memcpy(&totalKey2[offset], &longKey2, sizeof(long));
				break;
			case COL_VARCHAR:
				cout << "\nEnter varchar key Range1 : ";
				cin >> key1;
				cout << "\nEnter varchar key Range2 : ";
				cin >> key2;

				memcpy(&totalKey1[offset], key1,
						indexHeaderPage_->colSizes_[i]);
				memcpy(&totalKey2[offset], key2,
						indexHeaderPage_->colSizes_[i]);
				break;
			}
			offset = offset + indexHeaderPage_->colSizes_[i];
		}
		int comparisionValue = BPlusTreeUtil::keyCompare(totalKey1, totalKey2,
				indexHeaderPage_);
		if (comparisionValue == -1 || comparisionValue == 0) {
			int leafNodeNumber = searchInBPlusTree(totalKey1);
			time_t start, end;
			double diffTime;
			time(&start);
			vector<RIDStruct> RIDVector;
			vector<string> keyVector;
			bplusTreeSearchKeyInLeafNodeWithRangeSearch(leafNodeNumber,
					totalKey1, totalKey2, RIDVector, keyVector);
			time(&end);
			diffTime = difftime(end, start);
			if (RIDVector.size() == 0) {
				cout << "\n\tKEY NOT FOUND IN TREE" << endl;
			} else {
				cout
						<< "\n******************** SEARCH RESULT ************************"
						<< endl;
				RIDStruct rid;
				//			char key[indexHeaderPage_->getKeySize()];
				for (int i = 0; i < RIDVector.size(); i++) {
					rid = RIDVector.at(i);
					string x;
					x = keyVector.at(i);
					cout << "      key :"<<x.c_str()<<endl;
					BPlusTreeUtil::displayKey(x.c_str(), indexHeaderPage_);
					cout << "\tPage No : " << rid.pageNumber << "\tSlot No : "
							<< rid.slotNumber << endl;
				}
				cout
						<< "****************** END SEARCH RESULT **********************"
						<< endl;
			}
		} else {
			cout << "\n\tRANGE1 SHOULD BE LESS THAN OR EQUAL TO RANGE2\n"
					<< endl;
		}
		//**********************************************************************
	}
	if (op != 0 && op != 6)
	{
		int numOfColumns = indexHeaderPage_->getNoOfColumns();
		int offset = 0;
		char totalKey[indexHeaderPage_->getKeySize()];
		for (int i = 0; i < numOfColumns; i++) {
			int colType = indexHeaderPage_->colTypes_[i];
			int intKey;
			float floatKey;
			double doubleKey;
			long longKey;
			int valid;
			char key[indexHeaderPage_->colSizes_[i]];
			memset(totalKey, '\0', indexHeaderPage_->getKeySize());
			switch (colType) {
			case TYPE_INT:
				do {
					cout << "\nEnter integer key to search : ";
					cin >> intKey;
					cin.ignore(numeric_limits<int>::max(), '\n');
					if (cin.fail()) {
						cout << "\n\tPLEASE ENTER VALID INPUT (INTEGER ONLY)"
								<< endl;
						cin.clear();
						cin.ignore(1000, '\n');
						valid = 0;
					} else {
						valid = 1;
					}
				} while (valid == 0);

				//memcpy(&totalKey[offset], &intKey, sizeof(int));
				strcpy(&totalKey[offset],CommonUtil::int_to_string(intKey).c_str());
				break;
			case COL_FLOAT:
				do {
					cout << " \n Enter float key to search : ";
					cin >> floatKey;
					cin.ignore(numeric_limits<float>::max(), '\n');
					if (cin.fail()) {
						cout << "\n\tPLEASE ENTER VALID INPUT (FLOAT ONLY)"
								<< endl;
						cin.clear();
						cin.ignore(1000, '\n');
						valid = 0;
					} else {
						valid = 1;
					}
				} while (valid == 0);

				memcpy(&totalKey[offset], &floatKey, sizeof(float));

				break;
			case COL_DOUBLE:
				do {
					cout << " \nEnter double key to search : ";
					cin >> doubleKey;
					cin.ignore(numeric_limits<double>::max(), '\n');
					if (cin.fail()) {
						cout << "\n\tPLEASE ENTER VALID INPUT (DOUBLE ONLY)"
								<< endl;
						cin.clear();
						cin.ignore(1000, '\n');
						valid = 0;
					} else {
						valid = 1;
					}
				} while (valid == 0);
				//memcpy(&totalKey[offset], &doubleKey, sizeof(double));
				strcpy(&totalKey[offset],CommonUtil::int_to_string(doubleKey).c_str());
				break;
			case COL_LONG:
				do {
					cout << "\nEnter long key to search : ";
					cin >> longKey;
					cin.ignore(numeric_limits<int>::max(), '\n');
					if (cin.fail()) {
						cout << "\n\tPLEASE ENTER VALID INPUT (LONG ONLY)"
								<< endl;
						cin.clear();
						cin.ignore(1000, '\n');
						valid = 0;
					} else {
						valid = 1;
					}
				} while (valid == 0);
				memcpy(&totalKey[offset], &longKey, sizeof(long));
				break;
			case COL_VARCHAR:
				cout << "\nEnter varchar key to search : ";
				cin >> key;
				memcpy(&totalKey[offset], key,
						indexHeaderPage_->colSizes_[i]);
				break;
			}
			offset = offset + indexHeaderPage_->colSizes_[i];
		}
		int leafNodeNumber = searchInBPlusTree(totalKey);
		time_t start, end;
		double diffTime;
		time(&start);
		vector<RIDStruct> RIDVector;
		vector<string> keyVector;
		cout << "you should be here dude :"<<endl;
		bplusTreeSearchKeyInLeafNodeWithOp(leafNodeNumber, totalKey, op,
				RIDVector, keyVector);
		time(&end);
		diffTime = difftime(end, start);
		if (RIDVector.size() == 0) {
			cout << "\n\tKEY NOT FOUND IN TREE" << endl;
		} else {
			cout
					<< "\n******************** SEARCH RESULT ************************"
					<< endl;
			RIDStruct rid;
			//			char key[indexHeaderPage_->getKeySize()];
			for (int i = 0; i < RIDVector.size(); i++) {
				rid = RIDVector.at(i);
				string x;
				x = keyVector.at(i);
				cout << "      key :"<<x.c_str();
				cout << "\tPage No : " << rid.pageNumber << "\tSlot No : "
						<< rid.slotNumber << endl;
			}
			cout
					<< "****************** END SEARCH RESULT **********************"
					<< endl;
		}
	}
}

void BPlusTree::tempKeyCompare(char *key1, char* key2) {
	int x = BPlusTreeUtil::keyCompare(key1, key2, indexHeaderPage_);
	cout << "comparision value :" << x << endl;
}
void BPlusTree::UIDisplayTree() {
	int heightOfTree = indexHeaderPage_->getHeightOfTree();
	int rootPage = indexHeaderPage_->getRootPageNumber();
	cout << "\n Root Page Number : " << indexHeaderPage_->getRootPageNumber() << endl;
	cout << " Height of tree     : " << indexHeaderPage_->getHeightOfTree()
			<< endl;
	cout << "\n\t*****************DISPLAY TREE********************" << endl;
	if (rootPage != -1) {
		if (heightOfTree == 0) {
			LeafNode leafNode(fd_,indexHeaderPage_, rootPage);
			leafNode.UIDisplayOfLeafNode(0);
		} else {
			IndexNode indexNode(fd_,indexHeaderPage_, rootPage);
			indexNode.UIDisplayOfIndexNode(0);
		}
	} else {
		cout << "\n\tNO ROOT PAGE EXISTED FOR BPLUS TREE\n";
	}
	cout << "\n\t***************END DISPLAY TREE********************" << endl;
}
void BPlusTree::bplusTreeSearchKeyInLeafNodeWithOp(int leafPageNumber,
		const char* totalKey, int op, std::vector<RIDStruct> &RIDVector,
		std::vector<string> &keyVector) {
	int found = 1;
	if (op == 1) {
		while (found == 1) {
			if (leafPageNumber != -1) {
				LeafNode leafNode(fd_,indexHeaderPage_, leafPageNumber);
				//cout << "leaf page number :"<< leafNode.getPageNumber()<<" leaf page right pagenumber :"<< leafNode.getRightPageNumber() <<endl;
				leafNode.searchKeyInLeafNodeWithOp(totalKey, op,
						RIDVector, keyVector);
				leafPageNumber = leafNode.getRightPageNumber();

			} else {
				found = 0;
			}
//
//			cout << "root page Number :"<<indexHeaderPage_->getRootPageNumber()<<endl;
//				IndexNode indexNode(fd_,indexHeaderPage_,indexHeaderPage_->getRootPageNumber());
//				if(indexNode.getPageType()==INDEX_LEAF_PAGE){
//
//				}
//				indexNode.searchKeyInIndexNodeWithOp(totalKey, op, RIDVector, keyVector);

		}

	} else if (op == 2) {
		while (found == 1) {
			if (leafPageNumber != -1) {
				LeafNode leafNode(fd_,indexHeaderPage_, leafPageNumber);
				found = leafNode.searchKeyInLeafNodeWithOp(totalKey, op,
						RIDVector, keyVector);
				if (found == 1) {
					leafPageNumber = leafNode.getRightPageNumber();
				}
			} else {
				found = 0;
			}
		}
	} else if (op == 3) {
		while (found == 1) {
			if (leafPageNumber != -1) {
				LeafNode leafNode(fd_,indexHeaderPage_, leafPageNumber);
				found = leafNode.searchKeyInLeafNodeWithOp(totalKey, op,
						RIDVector, keyVector);
				if (found == 1) {
					leafPageNumber = leafNode.getRightPageNumber();
				}
			} else {
				found = 0;
			}
		}
	} else if (op == 4) {
		while (found == 1) {
			if (leafPageNumber != -1) {
				LeafNode leafNode(fd_,indexHeaderPage_, leafPageNumber);
				found = leafNode.searchKeyInLeafNodeWithOp(totalKey, op,
						RIDVector, keyVector);
				if (found == 1) {
					leafPageNumber = leafNode.getLeftPageNumber();
				}
			} else {
				found = 0;
			}
		}
	} else if (op == 5) {
		while (found == 1) {
			if (leafPageNumber != -1) {
				LeafNode leafNode(fd_,indexHeaderPage_, leafPageNumber);
				found = leafNode.searchKeyInLeafNodeWithOp(totalKey, op,
						RIDVector, keyVector);
				if (found == 1) {
					leafPageNumber = leafNode.getLeftPageNumber();
				}
			} else {
				found = 0;
			}
		}
	}
}
void BPlusTree::deleteIndex(int indexPageNumber) {
	BufferManager *bufMgr = BufferManager::getInstance();
	//	DEBUG_B("Index header page number "<<indexPageNumber)
	int rootPageNumber = indexHeaderPage_->getRootPageNumber();

	//Which Page no. do I need to create the object with!?
	FreePageManager *freePageMgr=new FreePageManager(fd_,1);
	std::vector<int> allPageNumbers;
	int height = indexHeaderPage_->getHeightOfTree();
	if (height != 0 && rootPageNumber != -1) {
		IndexNode indexNode(fd_,indexHeaderPage_, rootPageNumber);
		indexNode.deleteChilds(allPageNumbers);
	}

	for (int i = 0; i < allPageNumbers.size(); i++) {
		cout<<"deleteing : "<<allPageNumbers.at(i)<<endl;
		//bufMgr->freePage(allPageNumbers.at(i));

		freePageMgr->freePage(allPageNumbers.at(i));
	}
	//	cout<<"I AM HERE root page number : "<<rootPageNumber<<endl;
	if (rootPageNumber != -1) {
		//bufMgr->freePage(rootPageNumber);
		freePageMgr->freePage(rootPageNumber);
	}
	freePageMgr->freePage(indexPageNumber);
	delete freePageMgr;
}

void BPlusTree::bplusTreeSearchKeyInLeafNodeWithRangeSearch(int leafPageNumber,
		const char* key1, const char* key2, std::vector<RIDStruct> &RIDVector,
		std::vector<string> &keyVector) {
	int stop = 0;
	//	DEBUG_B("starting leaf page number : "<<leafPageNumber)
	while (leafPageNumber != -1) {
		LeafNode leafNode(fd_,indexHeaderPage_, leafPageNumber);
		stop = leafNode.searchFirstKeyToSecondKey(key1, key2, RIDVector,
				keyVector);
		leafPageNumber = leafNode.getRightPageNumber();
		if (stop == 0) {
			break;
		}
	}
}
void BPlusTree::getAllRIDS(std::vector<RIDStruct> &RIDVector, std::vector<
		string> &keyVector) {
	std::vector<int> leafPages;
	if (indexHeaderPage_->getHeightOfTree() == 0) {
		if (indexHeaderPage_->getRootPageNumber() != -1) {
			leafPages.push_back(indexHeaderPage_->getRootPageNumber());
		}
	} else {
		int rootPageNumber = indexHeaderPage_->getRootPageNumber();
		IndexNode indexNode(fd_,indexHeaderPage_, rootPageNumber);
		indexNode.findFirstLeafPage(leafPages);
	}
	for (int i = 0; i < leafPages.size(); i++) {
		if (leafPages.at(i) != -1) {
			LeafNode leafNode(fd_,indexHeaderPage_, leafPages.at(i));
			leafNode.getKeysAndRIDs(RIDVector,keyVector);
		}
	}
	RIDStruct rid;
	cout<<"\n search result"<<endl;
	for (int i = 0; i < RIDVector.size(); i++) {
		rid = RIDVector.at(i);
		string x;
		x = keyVector.at(i);
		cout << "      key :";
		BPlusTreeUtil::displayKey(x.c_str(), indexHeaderPage_);
		cout << "\tPage No : " << rid.pageNumber << "\tSlot No : "
				<< rid.slotNumber << endl;
	}
}
