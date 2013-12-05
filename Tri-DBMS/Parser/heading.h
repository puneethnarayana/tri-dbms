/*
 * heading.h
 *
 *  Created on: 26-Nov-2013
 *      Author: alka
 */

#ifndef HEADING_H_
#define HEADING_H_

#include <cstring>
#include <iostream>
#include <istream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;
#include "../Utils/CommonUtil.h"
#include "../Utils/DataTypeLookup.h"
#include "../Utils/FieldLengthLookup.h"
#include "../Utils/WhereExpressionElement.h"
#include "../DatabaseManagement/DatabaseOperations.h"
#include "../BufferManagement/BufferManager.h"
#include "../Global/globalDefines.h"

string globalDatabaseName;
string globalTableName;
string globalIndexName;
vector<string> globalColumnNameList;
vector<string> globalColumnValueList;
vector<string> globalColumnDatatypeList;
vector<string> globalColumnDatasizeList;
vector<WhereExpressionElement> globalWhereList;

int dbSize=0;
int mode=0;
char* pageContent=new char[DEFAULT_PAGE_SIZE];

#endif /* HEADING_H_ */
