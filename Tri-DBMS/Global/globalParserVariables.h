/*
 * globalParserVariables.h
 *
 *  Created on: 02-Dec-2013
 *      Author: alka
 */

#ifndef GLOBALPARSERVARIABLES_H_
#define GLOBALPARSERVARIABLES_H_
#include "../DatabaseManagement/QueryStructure.h"


string globalDatabaseName;
string globalTableName;
string globalIndexName;
vector<string> globalColumnNameList;
vector<string> globalColumnValueList;
vector<string> globalColumnDatatypeList;
vector<string> globalColumnDatasizeList;
vector<string> globalWhereList;

int globalStatementType;


#endif /* GLOBALPARSERVARIABLES_H_ */
