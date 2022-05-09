#pragma once

#include "BigNumberExpression.h"

class BigNumberEquation
{
private:
	char* equation;
	size_t capacity;

	void copy(const BigNumberEquation& other);
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
	BigNumber& solveEquation(const char* equation);

	//Generate a random equation
	char* generateEquation();

	//Generate equation from an expression
	char* generateEquation(const char* expression);

	//Get equation as read-only
	const char* getEquation() const;
	//Get the right expression as read-only
	const char* getRightExpression() const;
	//Get the left expression, with the 'x', as read-only
	const char* getLeftExpression() const;
};

