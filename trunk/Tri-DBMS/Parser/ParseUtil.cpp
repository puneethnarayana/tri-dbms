/*
 * ParseUtil.cpp
 *
 *  Created on: 25-Nov-2013
 *      Author: alka
 */

#include "ParseUtil.h"
#include <ctype.h>
#include <iostream>

// prototype of bison-generated parser function
extern int yyparse();
extern int yy_scan_string(const char *);

ParseUtil::ParseUtil() {
	// TODO Auto-generated constructor stub

}

ParseUtil::~ParseUtil() {
	// TODO Auto-generated destructor stub

}

void ParseUtil::parseQuery(char* buffer){
	yy_scan_string(buffer);
		if (yyparse() != 0) {
			std::cout<<"Parse failed"<<std::endl;
		}
}
