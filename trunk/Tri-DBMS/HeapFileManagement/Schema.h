/*
 * Schema.h
 *
 *  Created on: Nov 20, 2013
 *      Author: ravin
 */

#ifndef SCHEMA_H_
#define SCHEMA_H_
#include <vector>
#include <string>
using namespace std;

class Schema {
public:
	Schema();
	virtual ~Schema();
	int numOfColumns;
	std::string tableName;
	std::vector<std::string> columnNames;
	std::vector<int> fieldTypes;
	std::vector<int> fieldLengths;
	std::vector<int> fieldPosition;
	void prepareSchemaObj(std::string strDescSchema);
	int getColumnNum(std::string columnName);
	std::string toString();
	std::string describeSchema();
};

#endif /* SCHEMA_H_ */
