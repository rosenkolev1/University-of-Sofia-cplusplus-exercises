#pragma once
#include "MBigNumber.h"
#include "MBigNumberExpressionCommon.h"
#include <iostream>
#include <fstream>
#include "..\Project.StringManipulation\MString.h"

class MBigNumberExpression
	:public MBigNumberExpressionCommon
{
public:
	//Check if the expression contains +++, ++-, +-+, +--, -++, -+-, --+, ---. If it does, then it is invalid
	//Check if the expression contains: **, */, *%, /*, //, /%, %*, %/, %%. If it does, then it is invalid
	//Check if the expression contains: +*, -*, +/, -/, +%, -%. If it does, then it is invalid
	//Check if the expression contains: +), -), *), /), %), (). If it does, then it is invalid
	//FORBIDDEN SYMBOLS CONSTANT
	/*static constexpr const char* EXPRESSION_DIVIDEBYZERO_EXCEPTION = "DIVISION BY 0 IS NOT ALLOWED!";
	static constexpr const char* EXPRESSION_PERCENTBYZERO_EXCEPTION = "PERCENT BY 0 IS NOT ALLOWED!";
	static constexpr const char* EXPRESSION_INVALID_EXCEPTION = "This expression isn't valid";

	static const int EXPRESSION_FORBIDDEN_STRINGS_COUNT = 32;*/
	//static constexpr const char* EXPRESSION_OPERATORS = "+-*/%";
	//static constexpr const char* EXPRESSION_NOTDIGIT = "+-*/%()";
	static const mstring EXPRESSION_DIVIDEBYZERO_EXCEPTION;
	static const mstring EXPRESSION_PERCENTBYZERO_EXCEPTION;
	static const mstring EXPRESSION_INVALID_EXCEPTION;
	static const int EXPRESSION_FORBIDDEN_STRINGS_COUNT = 32;
	static const mstring EXPRESSION_OPERATORS;
	static const mstring EXPRESSION_NOTDIGIT;
	static const mstring EXPRESSION_FORBIDDEN_STRINGS[32];

private:

	/*char* expression;
	size_t capacity;*/
	mstring expression;

	//void copy(const MBigNumberExpression& other);

	/*MBigNumber* replaceNumbersFromCalculation(MBigNumber* numbers, size_t& countOfNumbers, size_t firstIndex, MBigNumber* resultNumber) const;
	void replaceOperatorsFromCalculation(char* operators, size_t index) const;*/
	MBigNumber* replaceNumbersFromCalculation(MBigNumber* numbers, size_t& countOfNumbers, size_t firstIndex, MBigNumber* resultNumber) const;
	void replaceOperatorsFromCalculation(mstring& operators, size_t index) const;

	size_t generateCountOfOperators() const;

public:

	//Big 4
	MBigNumberExpression();
	//MBigNumberExpression(const MBigNumberExpression& other);
	//~MBigNumberExpression();
	//MBigNumberExpression& operator=(const MBigNumberExpression& other);

	MBigNumberExpression(mstring expression);

	//Get the equation as read-only
	mstring getExpression() const;

	//Set the equation
	void setExpression(mstring expression);

	//Return the answer to an expression
	MBigNumber evaluateExpression() const;
	MBigNumber evaluateExpression(mstring expression) const;

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
	mstring getExpressionTemplate(const MBigNumberExpression& expression) const;

	mstring generateExpressionFromTemplate(mstring expressionTemplate) const;

	//Randomly generate a new expression
	void generateExpression();

	//Generate a new expression with certain conditions
	void generateExpression(mstring allowedOperators);

	mstring concatExpressionsWithOperator(mstring thisExpression, mstring otherExpression, mstring concatOperator) const;

	//Comparative operators
	bool operator == (const MBigNumberExpression& other) const;
	bool operator != (const MBigNumberExpression& other) const;
	bool operator < (const MBigNumberExpression& other) const;
	bool operator <= (const MBigNumberExpression& other) const;
	bool operator > (const MBigNumberExpression& other) const;
	bool operator >= (const MBigNumberExpression& other) const;

	//Operator arithmetic
	MBigNumberExpression operator+(const MBigNumberExpression& other) const;
	MBigNumberExpression& operator+=(const MBigNumberExpression& other);

	MBigNumberExpression operator-(const MBigNumberExpression& other) const;
	MBigNumberExpression& operator-=(const MBigNumberExpression& other);

	MBigNumberExpression operator*(const MBigNumberExpression& other) const;
	MBigNumberExpression& operator*=(const MBigNumberExpression& other);

	MBigNumberExpression operator/(const MBigNumberExpression& other) const;
	MBigNumberExpression& operator/=(const MBigNumberExpression& other);

	MBigNumberExpression operator%(const MBigNumberExpression& other) const;
	MBigNumberExpression& operator%=(const MBigNumberExpression& other);

	//Reading and outputting expressions to text file or console
	friend std::istream& operator>> (std::istream& is, MBigNumberExpression& expression);
	friend std::ostream& operator<< (std::ostream& is, const MBigNumberExpression& expression);

	friend std::ifstream& operator>> (std::ifstream& is, MBigNumberExpression& expression);
	friend std::ofstream& operator<< (std::ofstream& os, const MBigNumberExpression& expression);
};



