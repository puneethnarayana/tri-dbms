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

using namespace std;
#include "../Utils/CommonUtil.h"
#include "../Utils/DataTypeLookup.h"
#include "../Utils/FieldLengthLookup.h"
#include "../DatabaseManagement/DatabaseOperations.h"


string globalDatabaseName;
string globalTableName;
string globalIndexName;
vector<string> globalColumnNameList;
vector<string> globalColumnValueList;
vector<string> globalColumnDatatypeList;
vector<string> globalColumnDatasizeList;
vector<string> globalWhereList;

int globalStatementType;


static const int CREATE_DATABASE_STATEMENT = 0;
static const int SHOW_DATABASES_STATEMENT = 1;
static const int OPEN_DATABASE_STATEMENT = 2;
static const int DROP_DATABASE_STATEMENT = 3;
static const int CREATE_TABLE_STATEMENT = 4;
static const int INSERT_STATEMENT = 5;
static const int SELECT_STATEMENT = 6;
static const int DELETE_STATEMENT = 7;
static const int UPDATE_STATEMENT = 8;
static const int DROP_TABLE_STATEMENT = 9;
static const int CREATE_INDEX_STATEMENT = 10;
static const int DROP_INDEX_STATEMENT = 11;
static const int SHOW_TABLES_STATEMENT = 12;
static const int DESCRIBE_STATEMENT = 13;

#endif /* HEADING_H_ */
