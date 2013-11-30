/*
 * BPlusTreeUtil.h
 *
 *  Created on: Oct 23, 2013
 *      Author: puneeth
 */

#ifndef BPLUSTREEUTIL_H_
#define BPLUSTREEUTIL_H_
#include "IndexHeader.h"
#include<string>
class BPlusTreeUtil {
public:
	BPlusTreeUtil();
	virtual ~BPlusTreeUtil();
	static int keyCompare(const char* key1, const char* key2,
			IndexHeader *indexHeader_);
	static void displayKey(const char* key, IndexHeader *indexHeaderPage_);
	static void displayType(int type);
	//	static int validation(const std::string& input);
	static int validation(int input);
	static std::string KeytoString(const char* key,IndexHeader *indexHeaderPage_);
};

#endif /* BPLUSTREEUTIL_H_ */
