#pragma once
#include "BigNumber.h"

class BigNumberExpression
{

private:
	char* expression;
	size_t capacity;

	void copy(const BigNumberExpression& other);

	BigNumber* replaceNumbersFromCalculation(BigNumber* numbers, size_t& countOfNumbers, size_t firstIndex, BigNumber* resultNumber) const;
	void replaceOperatorsFromCalculation(char* operators, size_t index) const;
public:

	//Big 4
	BigNumberExpression();
	BigNumberExpression(const BigNumberExpression& other);
	~BigNumberExpression();
	BigNumberExpression& operator=(const BigNumberExpression& other);

	BigNumberExpression(const char* equation);

	//Get the equation as read-only
	const char* getExpression() const;

	//Return the answer to an expression
	BigNumber evaluteExpression(const char* expression = nullptr) const;

	//Randomly generate a new expression
	void generateExpression();
};

