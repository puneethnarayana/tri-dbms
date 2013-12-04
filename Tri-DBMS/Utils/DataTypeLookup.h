/*
 * DataTypeLookup.h
 *
 *  Created on: 28-Nov-2009
 *      Author: shailesh
 */

#ifndef DATATYPELOOKUP_H_
#define DATATYPELOOKUP_H_
#include "../Global/globalDefines.h"
#include "string.h"
class DataTypeLookup {
public:
	static int getType(char *dataTypeString) {
		if (strcmp(dataTypeString, "INTEGER") == 0 || strcmp(dataTypeString, "integer") == 0) {
			return TYPE_INT;
		}else if (strcmp(dataTypeString, "VARCHAR") == 0 || strcmp(dataTypeString, "varchar") == 0) {
			return TYPE_VARCHAR;
		}else if (strcmp(dataTypeString, "BOOL") == 0 || strcmp(dataTypeString, "bool") == 0) {
			return TYPE_BOOL;
		}else if (strcmp(dataTypeString, "DATE") == 0 || strcmp(dataTypeString, "date") == 0) {
			return TYPE_DATE;
		}
		return -1;
	}

	static std::string getTypeDesc(int dataType) {
		switch (dataType) {
		case TYPE_INT:
			return "INTEGER";
		case TYPE_VARCHAR:
			return "VARCHAR";
		case TYPE_BOOL:
			return "BOOL";
		case TYPE_DATE:
			return "DATE";
		default:
			break;
		}
		return "UNKNOWN_DATA_TYPE";
	}
};
#endif /* DATATYPELOOKUP_H_ */
