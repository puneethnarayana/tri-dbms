/*
 * Schema.cpp
 *
 *  Created on: Nov 20, 2013
 *      Author: ravin
 */

#include "Schema.h"
#include "../Utils/DataTypeLookup.h"
#include "../Utils/FieldLengthLookup.h"
#include <sstream>
#include <string>
#include <vector>
using namespace std;

Schema::Schema() {
	// TODO Auto-generated constructor stub
	numOfColumns=0;
}

Schema::~Schema() {
	// TODO Auto-generated destructor stub
}



std::string Schema::toString() {
	std::stringstream str;
	str << tableName << "," << numOfColumns << "\n";
	for (int i = 0; i < numOfColumns; i++) {
		str << columnNames.at(i) << "\t";
		str << DataTypeLookup::getTypeDesc(fieldTypes.at(i)) << "\t";
		str << fieldLengths.at(i) << "\n";
	}
	str << "\n";
	return str.str();
}

std::string Schema::describeSchema() {
	std::stringstream mystream;
	int len = strlen("CREATE TABLE ");
	len = len + tableName.length();
	mystream << "CREATE TABLE " << tableName << "(\n";
	for (int i = 0; i < numOfColumns; i++) {
		mystream << columnNames.at(i)<<"\t";
		mystream << DataTypeLookup::getTypeDesc(fieldTypes.at(i));
		mystream << FieldLengthLookup::getTypeDesc(fieldLengths.at(i)) << ",\n";
	}
	mystream <<");\n";
	return mystream.str();
}


int Schema::getColumnNum(std::string columnName){
	for (unsigned i = 0; i < columnNames.size(); i++) {
		if(columnName==columnNames[i]){
			return i;
		}
	}
	return -1;
}

