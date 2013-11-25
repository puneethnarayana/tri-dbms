/*
 * FieldLengthLookup.h
 *
 *  Created on: 30-Nov-2009
 *      Author: shailesh
 */

#ifndef FIELDLENGTHLOOKUP_H_
#define FIELDLENGTHLOOKUP_H_
#include "../Global/globalDefines.h"
#include "../Utils/CommonUtil.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
class FieldLengthLookup{
public:
	static int getType(char *fieldLengthString){
		if(strcmp(fieldLengthString,"INTEGER")==0){
			return SIZE_INT;
		}

		int len = strlen(fieldLengthString);
		for(int i=0;i<len;i++){
			if(isdigit(fieldLengthString[i])!=0){
				return -1;
			}
		}
		return atoi(fieldLengthString);
	}

	static std::string getTypeDesc(int length){
		std::string result;
		switch (length) {
			case SIZE_INT:
				return "INTEGER";
				break;
			default:
				result = "(";
				result = result  + CommonUtil::int_to_string(length);
				result.append(")");
				break;
		}
		return result;
	}
};

#endif /* FIELDLENGTHLOOKUP_H_ */