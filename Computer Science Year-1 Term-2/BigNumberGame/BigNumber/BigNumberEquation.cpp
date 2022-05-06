#include "BigNumberEquation.h"

void BigNumberEquation::copy(const BigNumberEquation& other)
{
	delete[] this->equation;
	this->capacity = other.capacity;
	this->equation = new char[this->capacity];
	strcpy(this->equation, other.equation);
}

BigNumberEquation::BigNumberEquation()
{
	this->equation = nullptr;
	this->capacity = 0;
}

BigNumberEquation::BigNumberEquation(const BigNumberEquation& other)
	:BigNumberEquation()
{
	this->copy(other);
}

BigNumberEquation::~BigNumberEquation()
{
	delete[] this->equation;
}

BigNumberEquation& BigNumberEquation::operator=(const BigNumberEquation& other)
{
	if (this == &other) return *this;
	this->copy(other);
}

BigNumberEquation::BigNumberEquation(const char* equation)
{
	size_t equationSize = strlen(equation) + 1;
	this->capacity = equationSize;
	this->equation = new char[this->capacity];
	strcpy(this->equation, equation);
}

const char* BigNumberEquation::getEquation() const
{
	return this->equation;
}

BigNumber BigNumberEquation::evaluteExpression() const
{
	return BigNumber(15);
}

void BigNumberEquation::generateExpression()
{
}
