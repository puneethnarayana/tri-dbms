/*
 * PostFixEvaluator.cpp
 *
 *  Created on: Nov 29, 2013
 *      Author: ravin
 */

#include "PostFixEvaluator.h"
#include <vector>
#include <stack>
#include "Record.h"
#include "WhereExpressionElement.h"
#include <stdio.h>
#include <iostream>
using namespace std;
PostFixEvaluator::PostFixEvaluator(Record& tuple) {
	// TODO Auto-generated constructor stub
	tuple_=tuple;
}

PostFixEvaluator::~PostFixEvaluator() {
	// TODO Auto-generated destructor stub
}


bool PostFixEvaluator::evaluate(std::vector<WhereExpressionElement> exprList) {

	for (unsigned i = 0; i < exprList.size(); i++) {
		if (exprList[i].type_ == WhereExpressionElement::IDENTIFIER_TYPE || exprList[i].type_
				== WhereExpressionElement::LITERAL_TYPE) {
			//cout << "inside id or literal evaluate: " << exprList[i].identifierValue << " " << exprList[i].literalValue<< endl;
			myStack.push(exprList[i]);
		} else {
			//cout << "inside operator evaluate" << endl;
			WhereExpressionElement op = exprList[i];
			WhereExpressionElement exp1 = myStack.top();
			myStack.pop();
			WhereExpressionElement exp2 = myStack.top();
			myStack.pop();
			WhereExpressionElement res = eval(exp1, exp2, op);
			//cout << "expression :" << exp1.literalValue << " "<<exp2.identifierValue << " " <<op.operatorValue << endl;
			myStack.push(res);
		}
	}
	return myStack.top().res;
}

WhereExpressionElement PostFixEvaluator::eval(WhereExpressionElement exp1, WhereExpressionElement exp2, WhereExpressionElement op) {
	WhereExpressionElement res;
	res.res = false;
	res.type_ = WhereExpressionElement::RESULT_TYPE;
	if (op.operatorValue == "=") {
		if (exp1.type_ == WhereExpressionElement::IDENTIFIER_TYPE) {
			//cout << "1"<< endl;
			if (tuple_.fieldMatchByConversion(exp1.identifierValue,
					exp2.literalValue)==true) {
				res.res = true;
			}
		} else if (exp2.type_ == WhereExpressionElement::IDENTIFIER_TYPE) {
			//cout << "2"<< endl;
			if (tuple_.fieldMatchByConversion(exp2.identifierValue,
					exp1.literalValue)==true) {
					//cout << "2 2" << endl;
					res.res = true;
			}
		} else if (exp1.type_ == WhereExpressionElement::RESULT_TYPE) {
			//cout << "3"<< endl;
			if(exp1.res == exp2.res){
				res.res = true;
			}
		}
	}else if (op.operatorValue == "!=") {
		if (exp1.type_ == WhereExpressionElement::IDENTIFIER_TYPE) {
			//cout << "1"<< endl;
			if (tuple_.fieldMatchByConversion(exp1.identifierValue,
					exp2.literalValue)==false) {
				res.res = true;
			}
		} else if (exp2.type_ == WhereExpressionElement::IDENTIFIER_TYPE) {
			//cout << "2"<< endl;
			if (tuple_.fieldMatchByConversion(exp2.identifierValue,
					exp1.literalValue)==false) {
					//cout << "2 2" << endl;
					res.res = true;
			}
		} else if (exp1.type_ == WhereExpressionElement::RESULT_TYPE) {
			//cout << "3"<< endl;
			if(exp1.res != exp2.res){
				res.res = true;
			}
		}
	}
	else 	if (op.operatorValue == "<") {
		if (exp1.type_ == WhereExpressionElement::IDENTIFIER_TYPE) {
			if (tuple_.lessThanByConversion(exp1.identifierValue,
					exp2.literalValue)==true) {
				res.res = true;
			}
		} else if (exp2.type_ == WhereExpressionElement::IDENTIFIER_TYPE) {
			if (tuple_.lessThanByConversion(exp2.identifierValue,
					exp1.literalValue)==true) {
					res.res = true;
			}
		} else if (exp1.type_ == WhereExpressionElement::RESULT_TYPE) {
			if(exp1.res == exp2.res){
				res.res = true;
			}
		}
	}else 	if (op.operatorValue == "<=") {
		if (exp1.type_ == WhereExpressionElement::IDENTIFIER_TYPE) {
			if (tuple_.lessThanOrEqualByConversion(exp1.identifierValue,
					exp2.literalValue)==true) {
				res.res = true;
			}
		} else if (exp2.type_ == WhereExpressionElement::IDENTIFIER_TYPE) {
			if (tuple_.lessThanOrEqualByConversion(exp2.identifierValue,
					exp1.literalValue)==true) {
					res.res = true;
			}
		} else if (exp1.type_ == WhereExpressionElement::RESULT_TYPE) {
			if(exp1.res == exp2.res){
				res.res = true;
			}
		}
	}else 	if (op.operatorValue == ">=") {
		if (exp1.type_ == WhereExpressionElement::IDENTIFIER_TYPE) {
			if (tuple_.greaterThanOrEqualByConversion(exp1.identifierValue,
					exp2.literalValue)==true) {
				res.res = true;
			}
		} else if (exp2.type_ == WhereExpressionElement::IDENTIFIER_TYPE) {
			if (tuple_.greaterThanOrEqualByConversion(exp2.identifierValue,
					exp1.literalValue)==true) {
					res.res = true;
			}
		} else if (exp1.type_ == WhereExpressionElement::RESULT_TYPE) {
			if(exp1.res == exp2.res){
				res.res = true;
			}
		}
	}else 	if (op.operatorValue == ">") {
		if (exp1.type_ == WhereExpressionElement::IDENTIFIER_TYPE) {
			if (tuple_.greaterThanByConversion(exp1.identifierValue,
					exp2.literalValue)==true) {
				res.res = true;
			}
		} else if (exp2.type_ == WhereExpressionElement::IDENTIFIER_TYPE) {
			if (tuple_.greaterThanByConversion(exp2.identifierValue,
					exp1.literalValue)==true) {
					res.res = true;
			}
		} else if (exp1.type_ == WhereExpressionElement::RESULT_TYPE) {
			if(exp1.res == exp2.res){
				res.res = true;
			}
		}
	}else 	if (op.operatorValue == "AND") {
		if (exp1.type_ == WhereExpressionElement::IDENTIFIER_TYPE) {
			if (tuple_.greaterThanByConversion(exp1.identifierValue,
					exp2.literalValue)==true) {
				res.res = true;
			}
		} else if (exp2.type_ == WhereExpressionElement::IDENTIFIER_TYPE) {
			if (tuple_.greaterThanByConversion(exp2.identifierValue,
					exp1.literalValue)==true) {
					res.res = true;
			}
		} else if (exp1.type_ == WhereExpressionElement::RESULT_TYPE) {
			if(exp1.res == true && exp2.res == true){
				res.res = true;
			}
		}
	}else 	if (op.operatorValue == "OR") {
		if (exp1.type_ == WhereExpressionElement::IDENTIFIER_TYPE) {
			if (tuple_.greaterThanByConversion(exp1.identifierValue,
					exp2.literalValue)==true) {
				res.res = true;
			}
		} else if (exp2.type_ == WhereExpressionElement::IDENTIFIER_TYPE) {
			if (tuple_.greaterThanByConversion(exp2.identifierValue,
					exp1.literalValue)==true) {
					res.res = true;
			}
		} else if (exp1.type_ == WhereExpressionElement::RESULT_TYPE) {
			if(exp1.res == true || exp2.res == true){
				res.res = true;
			}
		}
	}
	return res;
}
