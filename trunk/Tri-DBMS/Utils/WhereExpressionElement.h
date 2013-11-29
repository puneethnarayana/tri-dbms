/*
 * WhereExpressionElement.h
 *
 *  Created on: Nov 29, 2013
 *      Author: ravin
 */

#ifndef WHEREEXPRESSIONELEMENT_H_
#define WHEREEXPRESSIONELEMENT_H_
#include <iostream>

using namespace std;
class WhereExpressionElement {
public:
	WhereExpressionElement();
	WhereExpressionElement(int type,string value);
	virtual ~WhereExpressionElement();
	int type_;
		static const int LITERAL_TYPE = 0; //values in expression
		static const int IDENTIFIER_TYPE = 1;//can be column names
		static const int OPERATOR_TYPE = 2;// =, or < or >
		static const int RESULT_TYPE = 3;// intermediate and end results
		string identifierValue;
		string literalValue;
		string operatorValue;
		bool res;
};

#endif /* WHEREEXPRESSIONELEMENT_H_ */
