/*
 * WhereExpressionElement.cpp
 *
 *  Created on: Nov 29, 2013
 *      Author: ravin
 */

#include "WhereExpressionElement.h"
#include <iostream>

using namespace std;

WhereExpressionElement::WhereExpressionElement(){

}

WhereExpressionElement::WhereExpressionElement(int type,string value) {
	// TODO Auto-generated constructor stub
	type_ = type;
		if(type == IDENTIFIER_TYPE){
			identifierValue = value;
		}else if(type == LITERAL_TYPE){
			literalValue = value;
		}else if(type == OPERATOR_TYPE){
			operatorValue = value;
		}

}

WhereExpressionElement::~WhereExpressionElement() {
	// TODO Auto-generated destructor stub
}


