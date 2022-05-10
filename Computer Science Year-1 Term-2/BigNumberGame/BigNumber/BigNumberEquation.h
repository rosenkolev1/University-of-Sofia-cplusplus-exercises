#pragma once

#include "BigNumberExpression.h"

class BigNumberEquation
	:public BigNumberExpressionCommon
{
private:
	static constexpr const char* EQUATION_OPERATORS = "+-*/";

	char* equation;
	size_t capacity;

	void copy(const BigNumberEquation& other);

	int generateCountOfX(int seed);
public:

	//Big 4
	BigNumberEquation();
	BigNumberEquation(const BigNumberEquation& other);
	BigNumberEquation& operator= (const BigNumberEquation& other);
	~BigNumberEquation();

	//Other constructors
	BigNumberEquation(const char* equation);
	BigNumberEquation(const BigNumberExpression& expression);

	//Check for equation validity. Excluding if the equation has a solution or not, or if it throws a divide by zero exception
	bool isValidEquation(const char* equation = nullptr) const;

	//Get the answer to an equation
	BigNumber& solveEquation(const char* equation = nullptr);

	//Fill the numbers in an equation template
	char* generateFromTemplate(const char* expressionTemplate, size_t maxUnknown = 3);

	//Generate a random equation. totalUnknown should be at most =maxUnknownPerSide, otherwise, throw error!
	void generateEquation(size_t maxUnknownPerSide = 3, size_t totalUnknown = 6);

	//Generate equation from an expression
	char* generateEquation(const char* expression);

	//Get equation as read-only
	const char* getEquation() const;

	//Get the right expression as read-only
	const char* getRightExpression() const;

	//Get the left expression, with the 'x', as read-only
	const char* getLeftExpression() const;

	//Get equation template
	char* getEquationTemplate(const char* equation = nullptr) const;
};

