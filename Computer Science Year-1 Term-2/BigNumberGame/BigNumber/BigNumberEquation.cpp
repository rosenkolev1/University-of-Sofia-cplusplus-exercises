#include "BigNumberEquation.h"
#include "../Project.StringManipulation/StringManip.h"

void BigNumberEquation::copy(const BigNumberEquation& other)
{
	this->capacity = other.capacity;
	delete[] this->equation;
	this->equation = new char[this->capacity];
	strcpy(this->equation, other.getEquation());
}

BigNumberEquation::BigNumberEquation()
{
	this->equation = new char[] {"x=0"};
	this->capacity = 4;
}

BigNumberEquation::BigNumberEquation(const BigNumberEquation& other)
	:BigNumberEquation()
{
	this->copy(other);
}

BigNumberEquation& BigNumberEquation::operator=(const BigNumberEquation& other)
{
	this->copy(other);
	return *this;
}

BigNumberEquation::~BigNumberEquation()
{
	delete[] this->equation;
}

BigNumberEquation::BigNumberEquation(const char* equation)
{
	if (!isValidEquation(equation)) throw "Invalid equation!";

	size_t capacityOfNewEquations = strlen(equation) + 1;
	if (capacityOfNewEquations > this->capacity) this->capacity = capacityOfNewEquations;

	this->equation = new char[this->capacity];
	strcpy(this->equation, equation);
}

BigNumberEquation::BigNumberEquation(const BigNumberExpression& expression)
{

}

bool BigNumberEquation::isValidEquation(const char* equation) const
{
	////Decide if the function is checking the object caller's own validity
	//bool checkOwn = false;
	//if (equation == nullptr)
	//{
	//	equation = this->equation;
	//	checkOwn = true;
	//}
	//
	////Check if there is not exactly 1 '=' in the equation. If there are, then it's invalid.
	//int countOfEquals = StringManip::countOf(equation, "=");
	//if (countOfEquals != 1) return false;
	//
	//
	//
	//if (!checkOwn)
	//{
	//	//Get the left and right expressions and check their validity
	//	
	//}
	//else
	//{
	//	//Percents are not allowed in equations
	//	//Check the validity of the 2 expressions of the object caller. Also check them for perecents
	//	return this->leftExpression.expressionIsValid() && 
	//		this->rightExpression.expressionIsValid() && 
	//		StringManip::stringContains(this->leftExpression.getExpression(), "%")  &&
	//		StringManip::stringContains(this->rightExpression.getExpression(), "%");
	//}
	return true;
}

BigNumber& BigNumberEquation::solveEquation(const char* equation)
{
	// TODO: insert return statement here
	BigNumber DEBUG(10);
	return DEBUG;
}

char* BigNumberEquation::generateEquation()
{
	//TODO: Will do once I can generate an expression with given flags set.
	return nullptr;
}

char* BigNumberEquation::generateEquation(const char* expression)
{
	return nullptr;
}

const char* BigNumberEquation::getEquation() const
{
	return this->equation;
}

const char* BigNumberEquation::getRightExpression() const
{
	size_t arraySize = 0;
	char** expressions = StringManip::splitString(this->getEquation(), "=", arraySize);
	char* rightExpression = new char [strlen(expressions[1] + 1)];
	strcpy(rightExpression, expressions[1]);

	//Delete dynamic memory
	StringManip::deleteArrayOfStrings(expressions, 2);

	return rightExpression;
}

const char* BigNumberEquation::getLeftExpression() const
{
	size_t arraySize = 0;
	char** expressions = StringManip::splitString(this->getEquation(), "=", arraySize);
	char* leftExpression = new char[strlen(expressions[0] + 1)];
	strcpy(leftExpression, expressions[0]);

	//Delete dynamic memory
	StringManip::deleteArrayOfStrings(expressions, 2);

	return leftExpression;
}
