#pragma once
#include "BigNumber.h"

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
	~BigNumberEquation();
	BigNumberEquation& operator=(const BigNumberEquation& other);

	BigNumberEquation(const char* equation);

	//Get the equation as read-only
	const char* getEquation() const;

	//Return the answer to an expression
	BigNumber evaluteExpression() const;

	//Randomly generate a new expression
	void generateExpression();
};

