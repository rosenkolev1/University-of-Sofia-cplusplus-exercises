#pragma once
#include "BigNumber.h"
#include "BigNumberExpressionCommon.h"
#include <iostream>
#include <fstream>
#include "..\Project.StringManipulation\MString.h"

class BigNumberExpression
	:public BigNumberExpressionCommon
{
public:
	//Check if the expression contains +++, ++-, +-+, +--, -++, -+-, --+, ---. If it does, then it is invalid
	//Check if the expression contains: **, */, *%, /*, //, /%, %*, %/, %%. If it does, then it is invalid
	//Check if the expression contains: +*, -*, +/, -/, +%, -%. If it does, then it is invalid
	//Check if the expression contains: +), -), *), /), %), (). If it does, then it is invalid

	//OTHER CONSTANTS
	static const mstring EXPRESSION_DIVIDEBYZERO_EXCEPTION;
	static const mstring EXPRESSION_PERCENTBYZERO_EXCEPTION;
	static const mstring EXPRESSION_INVALID_EXCEPTION;
	static const int EXPRESSION_FORBIDDEN_STRINGS_COUNT = 32;
	static const mstring EXPRESSION_OPERATORS;
	static const mstring EXPRESSION_NOTDIGIT;

	//FORBIDDEN SYMBOLS CONSTANT
	static const mstring EXPRESSION_FORBIDDEN_STRINGS[32];

private:

	mstring expression;

	BigNumber* replaceNumbersFromCalculation(BigNumber* numbers, size_t& countOfNumbers, size_t firstIndex, BigNumber* resultNumber) const;

	size_t generateCountOfOperators() const;

public:

	//Big 4
	BigNumberExpression();

	BigNumberExpression(mstring expression);

	//Get the equation as read-only
	mstring getExpression() const;

	//Set the equation
	void setExpression(mstring expression);

	//Return the answer to an expression
	BigNumber evaluateExpression() const;
	BigNumber evaluateExpression(mstring expression) const;

	//Check if expression is valid
	bool expressionIsValid() const;
	bool expressionIsValid(mstring expression) const;

	//Check if expression template is valid
	bool expressionTemplateIsValid(mstring expressionTemplate) const;

	//Randomly generate a new expression template
	mstring generateExpressionTemplate() const;

	//Randomly generate a new expression template with certain conditions
	mstring generateExpressionTemplate(mstring allowedOperators) const;

	//Get the expression template for an expression
	mstring getExpressionTemplate() const;
	mstring getExpressionTemplate(mstring expression) const;

	//Get the expression template for an expression
	mstring getExpressionTemplate(const BigNumberExpression& expression) const;

	mstring generateExpressionFromTemplate(mstring expressionTemplate) const;

	//Randomly generate a new expression
	void generateExpression();

	//Generate a new expression with certain conditions
	void generateExpression(mstring allowedOperators);

	mstring concatExpressionsWithOperator(mstring thisExpression, mstring otherExpression, mstring concatOperator) const;

	//Comparative operators
	bool operator == (const BigNumberExpression& other) const;
	bool operator != (const BigNumberExpression& other) const;
	bool operator < (const BigNumberExpression& other) const;
	bool operator <= (const BigNumberExpression& other) const;
	bool operator > (const BigNumberExpression& other) const;
	bool operator >= (const BigNumberExpression& other) const;

	//Operator arithmetic
	BigNumberExpression operator+(const BigNumberExpression& other) const;
	BigNumberExpression& operator+=(const BigNumberExpression& other);

	BigNumberExpression operator-(const BigNumberExpression& other) const;
	BigNumberExpression& operator-=(const BigNumberExpression& other);

	BigNumberExpression operator*(const BigNumberExpression& other) const;
	BigNumberExpression& operator*=(const BigNumberExpression& other);

	BigNumberExpression operator/(const BigNumberExpression& other) const;
	BigNumberExpression& operator/=(const BigNumberExpression& other);

	BigNumberExpression operator%(const BigNumberExpression& other) const;
	BigNumberExpression& operator%=(const BigNumberExpression& other);

	//Reading and outputting expressions to text file or console
	friend std::istream& operator>> (std::istream& is, BigNumberExpression& expression);
	friend std::ostream& operator<< (std::ostream& is, const BigNumberExpression& expression);

	friend std::ifstream& operator>> (std::ifstream& is, BigNumberExpression& expression);
	friend std::ofstream& operator<< (std::ofstream& os, const BigNumberExpression& expression);
};


