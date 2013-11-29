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
			myStack.push(exprList[i]);
		} else {
			WhereExpressionElement op = exprList[i];
			WhereExpressionElement exp1 = myStack.top();
			myStack.pop();
			WhereExpressionElement exp2 = myStack.top();
			myStack.pop();
			WhereExpressionElement res = eval(exp1, exp2, op);
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
			if (tuple_.fieldMatchByConversion(exp1.identifierValue,
					exp2.literalValue)==true) {
				res.res = true;
			}
		} else if (exp2.type_ == WhereExpressionElement::IDENTIFIER_TYPE) {
			if (tuple_.fieldMatchByConversion(exp2.identifierValue,
					exp1.literalValue)==true) {
					res.res = true;
			}
		} else if (exp1.type_ == WhereExpressionElement::RESULT_TYPE) {
			if(exp1.res == exp2.res){
				res.res = true;
			}
		}
	}else 	if (op.operatorValue == "<") {
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
