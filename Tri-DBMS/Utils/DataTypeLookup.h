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
		if (strcmp(dataTypeString, "INTEGER") == 0) {
			return TYPE_INT;
		}else if (strcmp(dataTypeString, "VARCHAR") == 0) {
			return TYPE_CHAR;
		}
		return -1;
	}

	static std::string getTypeDesc(int dataType) {
		switch (dataType) {
		case TYPE_INT:
			return "INTEGER";
		case TYPE_CHAR:
			return "VARCHAR";
		default:
			break;
		}
		return "UNKNOWN_DATA_TYPE";
	}
};
#endif /* DATATYPELOOKUP_H_ */
