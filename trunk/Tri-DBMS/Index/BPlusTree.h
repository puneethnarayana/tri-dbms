/*
 * BPlusTree.h
 *
 *  Created on: Oct 23, 2013
 *      Author: puneeth
 */

#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_
#include "../Global/globalStructures.h"
#include "../BufferManagement/BufferManager.h"
#include "../HeapFileManagement/FreePageManager.h"
#include "IndexHeader.h"
#include<vector>
#include<string>
#include<string.h>
#include<vector>
using namespace std;
class BPlusTree {
public:
	BPlusTree(int fd);
	BPlusTree(int fd,int indexHeaderPageNumber);//FOR HEAP (OPEN INDEX)
	virtual ~BPlusTree();
	int insertIntoBPlusTree(const char* key, RIDStruct &rid);//FOR HEAP (INSERT KEY)
	int deleteFromBPlusTree(const char* key, RIDStruct &rid);//FOR HEAP (DELETE KEY)
	int searchInBPlusTree(const char* key);//(a)FOR HEAP (SEARCHING WILL GIVE LEAF PAGE NUMBER)
	int searchKeyInBPlusTree(const char* key,std::vector<RIDStruct> &RIDVector);
	int userInterface(int indexHeaderPageNumber);
	void UIIndexOrLeafNode();
	void bplusTreeUILeafNode(int pageNumber);
	void bplusTreeUIIndexNode(int pageNumber);
	void UIInsertRecord();
	void UISearching();
	void searchingWithOperator(const char* key, int searchOp);
	void UISetFanoutOfTree();
	void UIInsertRange();
	void UIDeleteKey();
	void UIDeleteRange();
	void UISetDebugFlag();
	int display();
	void UIDisplayTree();
	void insertIntRange(int range1, int range2, int incrementFactor);
	void insertAllRanges(char* range1, char* range2, char* incrementFactor);
	void insertFloatRange(float range1, float range2, float incrementFactor);
	void insertDoubleRange(double range1, double range2, double incrementFactor);
	void insertLongRange(long range1, long range2, long incrementFactor);
	void deleteIntRange(int range1, int range2);
	void IntRange(int range1, int range2, int incrementFactor);
	void deleteFloatRange(float range1, float range2);
	void deleteDoubleRange(double range1, double range2);
	void deleteLongRange(long range1, long range2);
	void deleteAllRanges(char* range1, char* range2);
	void insertVarCharRange(int totalNumOfKeys);
	void storeTillRequiredKey(int startLeafPage, const char* key1,
			const char* key2, std::vector<RIDStruct> &RIDVector, std::vector<string> &keyVector);
	void tempKeyCompare(char* key1, char* key2);
	//(b)FOR HEAP SEARCH KEY WITH OPERATOR AND LEAF PAGE PAGE NUMBER
	void bplusTreeSearchKeyInLeafNodeWithOp(int leafPageNumber,const char* totalKey, int op,
			std::vector<RIDStruct> &RIDVector,std::vector<string> &keyVector);
	void bplusTreeSearchKeyInLeafNodeWithRangeSearch(int leafPageNumber,
			const char* key1, const char* key2,
			std::vector<RIDStruct> &RIDVector, std::vector<string> &keyVector);

	void deleteIndex(int indexPageNumber);//FOR HEAP ALSO
	void findLeafIndexPages(std::vector<int> &leafPages,
			std::vector<int> &indexPages);
	void displayIndexPages(std::vector<int> indexPageVector);
	void displayLeafPages(std::vector<int> leafPageVector);
	int findInIndexPages(std::vector<int> indexPageVector, int pageNumber);
	int findInLeafPages(std::vector<int> leafPageVector, int pageNumber);
	//	static std::vector<int> deletedPages;
	void getAllRIDS(std::vector<RIDStruct> &RIDVector,std::vector<string> &keyVector);
private:
	IndexHeader *indexHeaderPage_;
	int fd_;

};

#endif /* BPLUSINDEX_H_ */
