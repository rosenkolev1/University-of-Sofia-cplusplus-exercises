#include "BigNumberEquation.h"
#include "../Project.StringManipulation/StringManip.h"

void BigNumberEquation::copy(const BigNumberEquation& other)
{
	this->capacity = other.capacity;
	delete[] this->equation;
	this->equation = new char[this->capacity];
	strcpy(this->equation, other.getEquation());
}

int BigNumberEquation::generateCountOfX(int seed)
{
	if (seed > 47) return 3;
	else if (seed > 40) return 2;
	else return 1;
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

char* BigNumberEquation::generateFromTemplate(const char* expressionTemplate)
{
	char* expressionFilled = new char[strlen(expressionTemplate) + 1];
	strcpy(expressionFilled, expressionTemplate);

	size_t countOfNumbers = StringManip::countOf(expressionFilled, "x");

	int countOfX = -1;
	while (countOfX < 0 || countOfX > countOfNumbers)
	{
		countOfX = generateCountOfX(rand());
	}

	//Generate the positions for the x. The positions are NOT the indexes. 1 + x + 3 + y ---> x is position 1, y is position 2
	int* positionsX = new int[countOfX];
	//Init positionX
	for (size_t i = 0; i < countOfX; i++)
	{
		positionsX[i] = -1;
	}

	//Set the target x's randomly
	for (size_t i = 0; i < countOfX; i++)
	{
		int position = -1;
		while (true)
		{
			position = rand() % countOfX + 1;

			//Check if the x position is already taken. If it is, then reroll
			bool isTaken = false;

			for (size_t i = 0; i < countOfX; i++)
			{
				if (positionsX[i] == position)
				{
					isTaken = true;
					break;
				}
			}

			if (isTaken == false) break;
		}

		positionsX[i] = position;
	}

	//Replace the target x with U
	size_t currentXPos = 0;
	for (size_t i = 0; i < strlen(expressionFilled); i++)
	{
		if (expressionFilled[i] == 'x')
		{
			currentXPos++;

			//Check if the current x position is targeted. If it is, then turn it into a U
			bool isTargeted = false;

			for (size_t i = 0; i < countOfX; i++)
			{
				if (positionsX[i] == currentXPos)
				{
					isTargeted = true;
					break;
				}
			}

			//Replace with U
			if (isTargeted)
			{
				char* expressionFilledCopy = StringManip::replaceFrom(expressionFilled, "U", i, i);
				delete[] expressionFilled;
				expressionFilled = expressionFilledCopy;
			}
		}	
	}

	//Replace the x in the expression template with numbers, except for the targeted x numbers, which are now U
	while (StringManip::stringContains(expressionFilled, "x"))
	{
		//Generate the sign of the number
		BigNumber bigNumber = BigNumber();
		int signOfNumber = generateSign(rand() % 15);
		if (signOfNumber != 0)
		{
			//Randomly generate a number
			size_t digitsCount = generateDigitsCount(rand() % 51);
			size_t capacity = digitsCount + 1;
			size_t digitsIndex = 0;

			if (signOfNumber == -1) capacity++;

			char* numberString = new char[capacity];
			numberString[capacity - 1] = '\0';

			if (signOfNumber == -1) numberString[digitsIndex++] = '-';

			numberString[digitsIndex++] = rand() % 9 + 1 + '0';
			for (size_t i = digitsIndex; i < digitsCount; i++)
			{
				numberString[i] = (rand() % 10) + '0';
			}

			bigNumber = BigNumber(numberString);
		}

		//Replace the bigNumber in the expressionTemplate
		char* newExpressionTemplate = StringManip::replaceFirst(expressionFilled, "x", bigNumber.getNumberRaw());
		delete[] expressionFilled;
		expressionFilled = newExpressionTemplate;
	}

	//Replace the U back with x because it looks better
	char* expressionFilledCopy = StringManip::replaceAll(expressionFilled, "U", "x");
	delete[] expressionFilled;
	expressionFilled = expressionFilledCopy;

	return expressionFilled;
}

void BigNumberEquation::generateEquation()
{
	//TODO: Will do once I can generate an expression with given flags set.
	//Generate the left expression template
	BigNumberExpression expression;

	char* leftExpression = expression.generateExpressionTemplate(EQUATION_OPERATORS);
	char* rightExpression = expression.generateExpressionTemplate(EQUATION_OPERATORS);

	//Replace the x in the templates with numbers, except for the targeted x's
	char* leftExpressionFilled = generateFromTemplate(leftExpression);
	char* rightExpressionFilled = generateFromTemplate(rightExpression);

	char* equation = new char[strlen(leftExpressionFilled) + strlen(rightExpressionFilled) + 2];
	equation[0] = '\0';
	strcat(equation, leftExpressionFilled);
	strcat(equation, "=");
	strcat(equation, rightExpressionFilled);

	//Delete dynamic memory
	delete[] rightExpressionFilled;
	delete[] leftExpressionFilled;
	delete[] rightExpression;
	delete[] leftExpression;

	this->equation = equation;
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
