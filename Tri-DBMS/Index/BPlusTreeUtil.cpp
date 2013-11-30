/*
 * BPlusTreeUtil.cpp
 *
 *  Created on: Oct 23, 2013
 *      Author: puneeth
 */

#include "BPlusTreeUtil.h"
#include "IndexHeader.h"
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<limits>
#include <sstream>
#include "../Global/globalDefines.h"
using namespace std;
BPlusTreeUtil::BPlusTreeUtil() {
	// TODO Auto-generated constructor stub

}

BPlusTreeUtil::~BPlusTreeUtil() {
	// TODO Auto-generated destructor stub
}
int BPlusTreeUtil::keyCompare(const char* key1, const char* key2,
		IndexHeader *indexHeader) {

	//	cout << "int :" << COL_INTEGER << endl;
	//	cout << "float :" << COL_FLOAT << endl;
	//	cout << "char :" << COL_VARCHAR << endl;
	int status = 1;
	int numOfColumns = indexHeader->getNoOfColumns();
	int offset = 0;
	int intKey1 = 0, intKey2 = 0;
	long longKey1 = 0, longKey2 = 0;
	float floatKey1 = 0.0, floatKey2 = 0.0, diff = 0.0;
	double doubleKey1 = 0.0, doubleKey2 = 0.0, ddiff = 0.0;

	for (int i = 0; i < numOfColumns; ++i) {
		int colType = indexHeader->colTypes_[i];
		switch (colType) {
		case COL_INTEGER:
			//			cout << "\nINTEGER TYPE" << endl;
			memcpy(&intKey1, &key1[offset], 4);
			memcpy(&intKey2, &key2[offset], 4);
			if (intKey1 > intKey2) {
				return 1;
			} else if (intKey1 < intKey2) {
				return -1;
			}
			break;

		case COL_FLOAT:
			//			cout << "\nFLOAT TYPE" << endl;
			memcpy(&floatKey1, &key1[offset], sizeof(float));
			memcpy(&floatKey2, &key2[offset], sizeof(float));
			floatKey1 += 0.0;
			floatKey2 += 0.0;
			diff = floatKey1 - floatKey2;
			//			cout << endl<<diff<<endl;
			if (diff == 0.0) {
				status = 0;
			} else if (diff > 0) {
				return 1;
			} else if (diff < 0) {
				return -1;
			}
			break;
		case COL_DOUBLE:
			//			cout << "\nDOUBLE TYPE" << endl;
			memcpy(&doubleKey1, &key1[offset], sizeof(double));
			memcpy(&doubleKey2, &key2[offset], sizeof(double));
			if (doubleKey1 > doubleKey2) {
				return 1;
			} else if (doubleKey1 < doubleKey2) {
				return -1;
			}
			break;
		case COL_LONG:
			memcpy(&longKey1, &key1[offset], sizeof(long));
			memcpy(&longKey2, &key2[offset], sizeof(long));
			if (longKey1 > longKey2) {
				return 1;
			} else if (longKey1 < longKey2) {
				return -1;
			}
			break;
		case COL_VARCHAR:
			//			cout << "\nVARCHAR TYPE" << endl;
			if (strncmp(&key1[offset], &key2[offset],
					indexHeader->colSizes_[i]) > 0) {
				return 1;
			} else if (strncmp(&key1[offset], &key2[offset],
					indexHeader->colSizes_[i]) < 0) {
				return -1;
			}
			break;

		default:
			//			cout << "DEFAULT IS VARCHAR TYPE" << endl;
			if (strncmp(&key1[offset], &key2[offset],
					indexHeader->colSizes_[i]) > 0) {
				return 1;
			} else if (strncmp(&key1[offset], &key2[offset],
					indexHeader->colSizes_[i]) < 0) {
				return -1;
			}
			break;

		}
		offset = offset + indexHeader->colSizes_[i];
	}
	return 0;

}
void BPlusTreeUtil::displayKey(const char *key,
		IndexHeader* indexHeaderPage_) {
	int numOfColumns = indexHeaderPage_->getNoOfColumns();
	int offset = 0;
	for (int i = 0; i < numOfColumns; i++) {
		int colType = indexHeaderPage_->colTypes_[i];
		int intKey;
		float floatKey;
		double doubleKey;
		long longKey;
		char varCharKey[indexHeaderPage_->colSizes_[i]],
				varCharKey1[indexHeaderPage_->colSizes_[i]];
		switch (colType) {
		case COL_INTEGER:
			memcpy(&intKey, &key[offset], sizeof(int));
			cout << intKey;
			break;
		case COL_FLOAT:
			memcpy(&floatKey, &key[offset], sizeof(float));
			cout << floatKey;
			break;
		case COL_DOUBLE:
			memcpy(&doubleKey, &key[offset], sizeof(double));
			cout << doubleKey;
			break;
		case COL_LONG:
			memcpy(&longKey, &key[offset], sizeof(long));
			cout << longKey;
			break;
		case COL_VARCHAR:
			memcpy(varCharKey, &key[offset], indexHeaderPage_->colSizes_[i]);
			cout << varCharKey;
			break;
		default:
			memcpy(varCharKey1, &key[offset], indexHeaderPage_->colSizes_[i]);
			cout << varCharKey1;
			break;
		}
		offset = offset + indexHeaderPage_->colSizes_[i];
	}
}
void BPlusTreeUtil::displayType(int type) {
	switch (type) {
	case 1:
		cout << "INTEGER";
		break;
	case 2:
		cout << "FLOAT";
		break;
	case 3:
		cout << "DOUBLE";
		break;
	case 4:
		cout << "STRING";
		break;
	case 5:
		cout << "LONG";
		break;
	}
}
std::string BPlusTreeUtil::KeytoString(const char* key,IndexHeader *indexHeaderPage_)
{
	std::ostringstream mystream;
	int numOfColumns = indexHeaderPage_->getNoOfColumns();
	int offset = 0;
	for (int i = 0; i < numOfColumns; i++) {
		int colType = indexHeaderPage_->colTypes_[i];
		int intKey;
		float floatKey;
		double doubleKey;
		long longKey;
		char varCharKey[indexHeaderPage_->colSizes_[i]],
				varCharKey1[indexHeaderPage_->colSizes_[i]];
		switch (colType) {
		case COL_INTEGER:
			memcpy(&intKey, &key[offset], sizeof(int));
			mystream << intKey;
			break;
		case COL_FLOAT:
			memcpy(&floatKey, &key[offset], sizeof(float));
			mystream << floatKey;
			break;
		case COL_DOUBLE:
			memcpy(&doubleKey, &key[offset], sizeof(double));
			mystream << doubleKey;
			break;
		case COL_LONG:
			memcpy(&longKey, &key[offset], sizeof(long));
			mystream << longKey;
			break;
		case COL_VARCHAR:
			memcpy(varCharKey, &key[offset], indexHeaderPage_->colSizes_[i]);
			mystream << varCharKey;
			break;
		default:
			memcpy(varCharKey1, &key[offset], indexHeaderPage_->colSizes_[i]);
			mystream << varCharKey1;
			break;
		}
		offset = offset + indexHeaderPage_->colSizes_[i];
	}
	return  mystream.str();

}
int BPlusTreeUtil::validation(int input) {
	/*	for(int i=0;i<input.length();i++)
	 {
	 if(!std::isdigit(input[i]))
	 return false;
	 }
	 return true;
	 */
	cin >> input;
	cin.ignore(numeric_limits<int>::max(), '\n');
	if (!cin || cin.gcount() != 1)
		cout << "not integer";
	else
		cout << "given value " << input;
	return 0;
}
