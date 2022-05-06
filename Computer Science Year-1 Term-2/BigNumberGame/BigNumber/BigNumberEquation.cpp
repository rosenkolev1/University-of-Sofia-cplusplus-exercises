#include "BigNumberEquation.h"
#include "..\Project.StringManipulation\StringManip.h"

void BigNumberExpression::copy(const BigNumberExpression& other)
{
	delete[] this->expression;
	this->capacity = other.capacity;
	this->expression = new char[this->capacity];
	strcpy(this->expression, other.expression);
}

BigNumberExpression::BigNumberExpression()
{
	this->expression = nullptr;
	this->capacity = 0;
}

BigNumberExpression::BigNumberExpression(const BigNumberExpression& other)
	:BigNumberExpression()
{
	this->copy(other);
}

BigNumberExpression::~BigNumberExpression()
{
	delete[] this->expression;
}

BigNumberExpression& BigNumberExpression::operator=(const BigNumberExpression& other)
{
	if (this == &other) return *this;
	this->copy(other);
}

BigNumberExpression::BigNumberExpression(const char* expression)
{
	size_t expressionSize = strlen(expression) + 1;
	this->capacity = expressionSize;
	this->expression = new char[this->capacity];
	strcpy(this->expression, expression);
}

const char* BigNumberExpression::getExpression() const
{
	return this->expression;
}

BigNumber BigNumberExpression::evaluteExpression() const
{
	const char* expression = this->getExpression();

	//Check if expression starts with +- or -+. If it does, then it's invalid
	bool invalidExpression = StringManip::stringStartsWith(expression, "+-") || StringManip::stringStartsWith(expression, "-+");
	if (invalidExpression) throw "Invalid Expression";

	//Next, replace all the instances of +- or -+ inside the string

	return BigNumber();
}

void BigNumberExpression::generateExpression()
{
}
