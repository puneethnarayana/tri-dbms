/*
 * PostFixEvaluator.h
 *
 *  Created on: Nov 29, 2013
 *      Author: ravin
 */

#ifndef POSTFIXEVALUATOR_H_
#define POSTFIXEVALUATOR_H_
#include <vector>
#include <stack>
#include "Record.h"
#include "WhereExpressionElement.h"
class PostFixEvaluator {
public:
	PostFixEvaluator(Record& tuple);
	virtual ~PostFixEvaluator();
	bool evaluate(std::vector<WhereExpressionElement> exprList);
	std::stack<WhereExpressionElement> myStack;
	WhereExpressionElement eval(WhereExpressionElement exp1,WhereExpressionElement exp2,WhereExpressionElement op);
	Record tuple_;
};

#endif /* POSTFIXEVALUATOR_H_ */
