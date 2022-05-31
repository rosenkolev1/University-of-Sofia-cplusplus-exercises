#include "BigNumberExpression.h"
#include "..\Project.StringManipulation\MStringManip.h"
#include <cstddef>
#include <limits>

//Static constants
const mstring BigNumberExpression::EXPRESSION_DIVIDEBYZERO_EXCEPTION = "DIVISION BY 0 IS NOT ALLOWED!";
const mstring BigNumberExpression::EXPRESSION_PERCENTBYZERO_EXCEPTION = "PERCENT BY 0 IS NOT ALLOWED!";
const mstring BigNumberExpression::EXPRESSION_INVALID_EXCEPTION = "This expression isn't valid";
const mstring BigNumberExpression::EXPRESSION_OPERATORS = "+-*/%";
const mstring BigNumberExpression::EXPRESSION_NOTDIGIT = "+-*/%()";
const mstring BigNumberExpression::EXPRESSION_FORBIDDEN_STRINGS[32] =
{
	"+++",
	"++-",
	"+-+",
	"+--",
	"-++",
	"-+-",
	"--+",
	"---",
	"**",
	"*/",
	"*%",
	"/*",
	"//",
	"/%",
	"%*",
	"%/",
	"%%",
	"+*",
	"-*",
	"+/",
	"-/",
	"+%",
	"-%",
	"+)",
	"-)",
	"*)",
	"/)",
	"%)",
	"(*",
	"(/",
	"(%",
	"()"
};

BigNumber* BigNumberExpression::replaceNumbersFromCalculation(BigNumber* numbers, size_t& countOfNumbers, size_t firstIndex, BigNumber* resultNumber) const
{
	//Replace the 2 numbers in the numbers array with the result number
	BigNumber* numbersCopy = new BigNumber[countOfNumbers - 1];
	size_t numbersCopyIndex = 0;
	for (size_t i = 0; i < countOfNumbers; i++)
	{
		if (i != firstIndex && i != firstIndex + 1)
		{
			numbersCopy[numbersCopyIndex++] = numbers[i];
		}
		else if (i == firstIndex)
		{
			numbersCopy[numbersCopyIndex++] = *resultNumber;
		}
	}

	delete[] numbers;
	countOfNumbers--;
	return numbersCopy;
}

BigNumberExpression::BigNumberExpression()
{
	this->expression = "0";
}

//BigNumberExpression::BigNumberExpression(const BigNumberExpression& other)
//	:BigNumberExpression()
//{
//	this->copy(other);
//}

//BigNumberExpression::~BigNumberExpression()
//{
//	delete[] this->expression;
//}

//BigNumberExpression& BigNumberExpression::operator=(const BigNumberExpression& other)
//{
//	if (this == &other) return *this;
//	this->copy(other);
//	return *this;
//}

BigNumberExpression::BigNumberExpression(mstring expression)
	:BigNumberExpression()
{
	this->setExpression(expression);
}

mstring BigNumberExpression::getExpression() const
{
	return this->expression;
}

void BigNumberExpression::setExpression(mstring expression)
{
	if (!expressionIsValid(expression)) throw EXPRESSION_INVALID_EXCEPTION;

	//Remove all the whitespaces and set the expression
	this->expression = MStringManip::replaceAll(expression, " ", "");
}

BigNumber BigNumberExpression::evaluateExpression() const
{
	return this->evaluateExpression(this->expression);
}

size_t BigNumberExpression::generateCountOfOperators() const
{
	size_t seed = rand() % 20;
	//Determine the count of the operators
	if (seed >= 18) return 10;
	else if (seed >= 16) return 9;
	else if (seed >= 14) return 8;
	else if (seed >= 12) return 7;
	else if (seed >= 10) return 6;
	else if (seed >= 8) return 5;
	else if (seed >= 6) return 4;
	else if (seed >= 4) return 3;
	else if (seed >= 2) return 2;
	else if (seed >= 0) return 1;
}

BigNumber BigNumberExpression::evaluateExpression(mstring expression) const
{
	//Remove all the whitespaces
	expression = MStringManip::replaceAll(expression, " ", "");

	if (!this->expressionIsValid(expression)) throw EXPRESSION_INVALID_EXCEPTION;

	//Start resolving all the parenthesis in the expression until none are left
	//If there are none, at least run the necessary in all cases things first. Hence why this is a do, while expression instead of a simple while expression
	do
	{
		//Replace all the instances of +-,-+, -- inside the string
		expression = MStringManip::replaceAll(expression, "+-", "-");
		expression = MStringManip::replaceAll(expression, "-+", "-");
		expression = MStringManip::replaceAll(expression, "--", "+");

		//Replace all the instances of *+,/+, %- inside the string
		expression = MStringManip::replaceAll(expression, "*+", "*");
		expression = MStringManip::replaceAll(expression, "/+", "/");
		expression = MStringManip::replaceAll(expression, "%+", "%");

		//Check if the first char of the expression is + or -. If it is, then add a "0" in front of the equation
		if (expression[0] == '-' || expression[0] == '+')
		{
			expression.push_front("0");
		}

		//Check for parentheses. If they are not there, then exit out of the loop
		bool parenthesisExist = MStringManip::stringContains(expression, "(");

		if (!parenthesisExist) break;

		//Find the indexes of the rightmost opening parenthesis and it's closing parenthesis
		int lastOpeningParenthesis = MStringManip::findIndexLast(expression, "(");
		int closingParenthesis = -1;
		for (size_t i = lastOpeningParenthesis + 1; i < expression.getSize(); i++)
		{
			if (expression[i] == ')')
			{
				closingParenthesis = i;
				break;
			}
		}

		//Get the expression inside the parenthesis
		mstring parenthesisExpression;
		for (size_t i = lastOpeningParenthesis + 1; i < closingParenthesis; i++)
		{
			parenthesisExpression += expression[i];
		}

		//Calculate the new expression
		BigNumber expressionResult = this->evaluateExpression(parenthesisExpression);

		//Create the new parts of the new expression
		mstring expressionPartOne = (lastOpeningParenthesis > 0 ? MStringManip::getFrom(expression, 0, lastOpeningParenthesis - 1) : "");

		mstring expressionPartTwo = expressionResult.getNumberRaw();

		//5+(7-9)+8
		mstring expressionPartThree = (closingParenthesis + 1 < expression.getSize() ? MStringManip::getFrom(expression, closingParenthesis + 1, expression.getSize() - 1) : "");

		//Concat all the expression parts into the new expression
		expression = expressionPartOne + expressionPartTwo + expressionPartThree;
	} while (true);

	//Get the operators
	mstring operators;

	size_t negativeOperatorsCapacity = 10;
	size_t* negativeOperatorsIndexes = new size_t[negativeOperatorsCapacity];
	size_t negativeOperatorsCount = 0;

	for (size_t i = 0; i < expression.getSize(); i++)
	{
		if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '%')
		{
			if (expression[i + 1] == '-')
			{
				operators += expression[i];

				//If negativeOperators runs out of capacity, then increase it's capacity
				if (negativeOperatorsCount >= negativeOperatorsCapacity)
				{
					size_t* negativeOperatorsCopy = new size_t[negativeOperatorsCapacity * 2];
					for (size_t y = 0; y < negativeOperatorsCapacity; y++)
					{
						negativeOperatorsCopy[y] = negativeOperatorsIndexes[y];
					}
					delete[] negativeOperatorsIndexes;
					negativeOperatorsIndexes = negativeOperatorsCopy;
				}
				negativeOperatorsIndexes[negativeOperatorsCount++] = operators.getSize() - 1;
				i++;
			}
			else
			{
				operators += expression[i];
			}
		}
	}

	//If there are no operators, then simply return the number itself
	if (operators.getSize() == 0)
	{
		BigNumber result(expression);
		return result;
	}

	//Get all the numbers
	//Replace all the *- with the delim |
	expression = MStringManip::replaceAll(expression, "*-", "|");
	//Replace all the /- with the delim |
	expression = MStringManip::replaceAll(expression, "/-", "|");
	//Replace all the %- with the delim |
	expression = MStringManip::replaceAll(expression, "%-", "|");
	//Replace all the + with the delim |
	expression = MStringManip::replaceAll(expression, "+", "|");
	//Replace all the - with the delim |
	expression = MStringManip::replaceAll(expression, "-", "|");
	//Replace all the * with the delim |
	expression = MStringManip::replaceAll(expression, "*", "|");
	//Replace all the / with the delim |
	expression = MStringManip::replaceAll(expression, "/", "|");
	//Replace all the % with the delim |
	expression = MStringManip::replaceAll(expression, "%", "|");

	size_t countOfNumbers = 0;
	mstring* numberStrings = MStringManip::splitString(expression, '|', countOfNumbers);

	//Get the actual BigNumber numbers
	BigNumber* numbers = new BigNumber[countOfNumbers];
	for (size_t i = 0; i < countOfNumbers; i++)
	{
		numbers[i] = BigNumber(numberStrings[i]);
		//Check if the current number is supposed to be negative and the lefthand side of a multiplication, division or percent operator
		//If it is, then multiply it by -1
		for (size_t y = 0; y < negativeOperatorsCount; y++)
		{
			if (i - 1 == negativeOperatorsIndexes[y]) numbers[i] *= -1;
		}
	}

	//Delete dynamic memory
	delete[] numberStrings;
	delete[] negativeOperatorsIndexes;

	//Start calculating
	while (operators.getSize() > 0)
	{
		//Calculate the priority operators (*, /, %) first
		int multiplyIndex = MStringManip::findIndex(operators, "*");
		int divideIndex = MStringManip::findIndex(operators, "/");
		int percentIndex = MStringManip::findIndex(operators, "%");
		int lowestIndex = -1;

		//This is ugly as shit lol. Better to stuff the indexes in an array, sort the array and then iterate through it but whatever.
		if (multiplyIndex == -1 && divideIndex == -1 && percentIndex == -1) lowestIndex = -1;
		else if (multiplyIndex == -1 && divideIndex == -1) lowestIndex = percentIndex;
		else if (divideIndex == -1 && percentIndex == -1) lowestIndex = multiplyIndex;
		else if (percentIndex == -1 && multiplyIndex == -1) lowestIndex = divideIndex;
		else if (multiplyIndex == -1)
		{
			lowestIndex = divideIndex < percentIndex ? divideIndex : percentIndex;
		}
		else if (divideIndex == -1)
		{
			lowestIndex = multiplyIndex < percentIndex ? multiplyIndex : percentIndex;
		}
		else if (percentIndex == -1)
		{
			lowestIndex = divideIndex < multiplyIndex ? divideIndex : multiplyIndex;
		}
		else
		{
			if (multiplyIndex < divideIndex)
			{
				if (multiplyIndex < percentIndex) lowestIndex = multiplyIndex;
				else lowestIndex = percentIndex;
			}
			else
			{
				if (divideIndex < percentIndex) lowestIndex = divideIndex;
				else lowestIndex = percentIndex;
			}
		}

		//If there is a priority operator, then calculate it's expression
		if (lowestIndex > -1)
		{
			char firstOperator = operators[lowestIndex];
			BigNumber firstNumber = numbers[lowestIndex];
			BigNumber secondNumber = numbers[lowestIndex + 1];
			BigNumber resultNumber = BigNumber();
			bool resultNumberIsCalculated = false;
			if (firstOperator == '*')
			{
				resultNumber = firstNumber * secondNumber;
				resultNumberIsCalculated = true;
			}
			else if (firstOperator == '/')
			{
				if (!secondNumber.isZero())
				{
					resultNumber = firstNumber / secondNumber;
					resultNumberIsCalculated = true;
				}
				else
				{
					throw EXPRESSION_DIVIDEBYZERO_EXCEPTION;
				}
			}
			else if (firstOperator == '%')
			{
				if (!secondNumber.isZero())
				{
					resultNumber = firstNumber % secondNumber;
					resultNumberIsCalculated = true;
				}
				else
				{
					throw EXPRESSION_PERCENTBYZERO_EXCEPTION;
				}
			}

			//This should never be the case if the program runs properly
			if (!resultNumberIsCalculated) throw "This isn't supposed to happen lol";

			//Replace the 2 numbers in the numbers array with the result number
			numbers = this->replaceNumbersFromCalculation(numbers, countOfNumbers, lowestIndex, &resultNumber);

			//Replace the operator from the operators array
			operators = MStringManip::replaceFrom(operators, "", lowestIndex, lowestIndex);
		}
		//If there is no priority operator, then calculate the non-priority operators (+, -)
		else
		{
			char currentOperator = operators[0];
			BigNumber firstNumber = numbers[0];
			BigNumber secondNumber = numbers[1];
			BigNumber resultNumber = BigNumber();
			bool resultNumberIsCalculated = false;
			if (currentOperator == '+')
			{
				resultNumber = firstNumber + secondNumber;
				resultNumberIsCalculated = true;
			}
			else if (currentOperator == '-')
			{
				resultNumber = firstNumber - secondNumber;
				resultNumberIsCalculated = true;
			}

			if (!resultNumberIsCalculated) throw "This isn't supposed to happen lol";

			//Replace the 2 numbers in the numbers array with the result number
			numbers = replaceNumbersFromCalculation(numbers, countOfNumbers, 0, &resultNumber);

			//Replace the operator from the operators array
			operators = MStringManip::replaceFrom(operators, "", 0, 0);
		}
	}

	//The only number left in the numbers array should be the end result
	BigNumber& resultNumber = numbers[0];
	return resultNumber;
}

bool BigNumberExpression::expressionIsValid() const
{
	return this->expressionIsValid(this->expression);
}

bool BigNumberExpression::expressionIsValid(mstring expression) const
{
	//Replace the whitespaces in the expression before checks for it's validity
	expression = MStringManip::replaceAll(expression, " ", "");

	//Check if the expression's length is 0. If it is, then return false
	if (expression.getSize() == 0)
	{
		return false;
	}

	//Check if the expression contains something other than the operators, parenthesis or digits
	for (size_t i = 0; i < expression.getSize(); i++)
	{
		//char symbol = expressionCopy[i];
		char symbol = expression[i];
		if (!MStringManip::stringContains(EXPRESSION_NOTDIGIT, symbol) && !isdigit(symbol))
		{
			return false;
		}
	}

	bool expressionIsInvalid = false;

	//Check if the expression contains forbidden strings
	for (size_t i = 0; i < EXPRESSION_FORBIDDEN_STRINGS_COUNT; i++)
	{
		if (MStringManip::stringContains(expression, EXPRESSION_FORBIDDEN_STRINGS[i]))
		{
			return false;
		}
	}

	if (expressionIsInvalid)
	{
		return false;
	}

	//Check if the expression finishes on an operator or start with an invalid operator. If it does, then it's invalid
	for (size_t i = 0; i < EXPRESSION_OPERATORS.getSize(); i++)
	{
		char symbolString[2] = { EXPRESSION_OPERATORS[i] };
		if (MStringManip::stringEndsWith(expression, symbolString))
		{
			return false;
		}
	}

	for (size_t i = 0; i < EXPRESSION_OPERATORS.getSize(); i++)
	{
		char symbolString[2] = { EXPRESSION_OPERATORS[i] };
		if (EXPRESSION_OPERATORS[i] != '+' && EXPRESSION_OPERATORS[i] != '-' && MStringManip::stringStartsWith(expression, symbolString))
		{
			return false;
		}
	}

	//Check if all the parenthesis are closed correctly
	int openedParenthesis = 0;
	for (size_t i = 0; i < expression.getSize(); i++)
	{
		if (expression[i] == '(') openedParenthesis++;
		else if (expression[i] == ')') openedParenthesis--;
		//If this happens, then there is a closing parenthesis which doesn't have a matching opening parenthesis. So the expression is invalid
		if (openedParenthesis < 0)
		{
			return false;
		}
	}
	//If this happens, then there is an opening parenthesis which doesn't have a matching closing parenthesis. So the expression is invalid
	if (openedParenthesis > 0)
	{
		return false;
	}

	//If this happens, then the expression has passed the test and is correct
	return true;
}

bool BigNumberExpression::expressionTemplateIsValid(mstring expressionTemplate) const
{
	//Replace all of the whitespaces
	expressionTemplate = MStringManip::replaceAll(expressionTemplate, " ", "");

	//Replace all of the numbers with -1;
	mstring expressionFromTemplate = MStringManip::replaceAll(expressionTemplate, "x", "-1");

	return this->expressionIsValid(expressionFromTemplate);
}

mstring BigNumberExpression::generateExpressionTemplate() const
{
	return generateExpressionTemplate("+-*/%");
}

mstring BigNumberExpression::generateExpressionTemplate(mstring allowedOperators) const
{
	int computerNumber = 0;

	//Decide all of the operators and the parenthesis
	//+ - * / % ( E
	//0 1 2 3 4 5 6
	
	size_t countOfOperators = this->generateCountOfOperators();

	mstring operators;
	for (size_t i = 0; i < countOfOperators; i++)
	{
		do
		{
			// Determine the operators
			char newOperator = generateOperator();

			if (MStringManip::stringContains(allowedOperators, newOperator) == true)
			{
				operators += newOperator;
				break;
			}

		} while(true);
	}

	//Generate a new expression without parenthesis
	size_t newExpressionMaxLength = (countOfOperators * 2 + 1) * 2 + 1;

	mstring expression;
	size_t operatorsIndexer = 0;
	for (size_t i = 0; i < newExpressionMaxLength; i++)
	{
		if (i % 2 == 0)
		{
			expression += '_';
		}
		else if (i % 4 == 1)
		{
			expression += 'x';
		}
		else if (i % 4 == 3)
		{
			expression += operators[operatorsIndexer++];
		}
	}

	// Opening parenthesis --> _x+_x-_x
	// Closing parenthesis --> x_+x_-x_
	// _x_+_x_-_x_ ---> (x_+_x_-_x_ ---> (x_+_x)-_x_
	// (x+)x-_x

	mstring openingParenthesis;
	size_t openParenthesisCount = 0;

	//Randomly generate the opening parenthesis amongst the opening parenthesis spots
	for (size_t i = 0; i < countOfOperators + 1; i++)
	{
		openingParenthesis += generateOpeningParenthesis();
		if (openingParenthesis[i] == '(') openParenthesisCount++;
	}

	//Randomly generate the closing parenthesis amongst the closing parenthesis spots. Be careful to close out all opening parenthesis with closing ones.
	mstring closingParenthesis;

	for (size_t i = 0; i < countOfOperators + 1; i++)
	{
		closingParenthesis += '_';
	}

	size_t lastOpenParenthesisIndex = openingParenthesis.getSize();
	while (openParenthesisCount > 0)
	{
		lastOpenParenthesisIndex = MStringManip::findIndexLast(openingParenthesis, "(", 0, lastOpenParenthesisIndex - 1);
		size_t firstOpenParenthesisIndex = MStringManip::findIndex(openingParenthesis, "(");

		//These are all of the valid closing parenthesis spots, i.e. the ones which are not before any opening parenthesis
		size_t closingParenthesisSpotsLeft = MStringManip::countOf(closingParenthesis, "_", firstOpenParenthesisIndex, closingParenthesis.getSize() - 1);

		//These are all of the valid closing parenthesis spots which are located to the right of the rightmost open parenthesis
		size_t closingParenthesisSpotsLeftForLastOpenParenthesis = MStringManip::countOf(closingParenthesis, "_", lastOpenParenthesisIndex,closingParenthesis.getSize() - 1);

		//If there are exactly as many spots left for closing parenthesis as there are opening parenthesis left unclosed, where the closing parenthesis spots
		// are all located to the right of the leftmost opening parenthesis, then there is no room for randomisation.
		//In that case, fill in the remaining closingParenthesis spots with closing parenthesis	
		if (closingParenthesisSpotsLeft == openParenthesisCount)
		{
			for (size_t i = firstOpenParenthesisIndex; i < closingParenthesis.getSize(); i++)
			{
				if (closingParenthesis[i] == '_')
				{
					closingParenthesis[i] = ')';
					openParenthesisCount--;
				}
			}
		}
		//If there is only one available spot for a closing parenthesis to the right of the rightmost open parenthesis, then there is no room for randomisation
		//In this case, fill the remaining spot with the closing parenthesis
		else if (closingParenthesisSpotsLeftForLastOpenParenthesis == 1)
		{
			size_t remainingClosingParenthesisSpot = MStringManip::findIndex(closingParenthesis, "_", lastOpenParenthesisIndex, closingParenthesis.getSize() - 1);
			closingParenthesis[remainingClosingParenthesisSpot] = ')';
			openParenthesisCount--;
		}
		//Otherwise, try to randomly put a closing bracket in one of the closing parenthesis spots which is to the right of the rightmost opened parenthesis
		//Cycle the loop until the random generator finally generates a closing parenthesis on one of the available closing parenthesis spots
		else
		{
			while (true)
			{
				computerNumber = rand() % closingParenthesisSpotsLeftForLastOpenParenthesis + lastOpenParenthesisIndex;
				size_t closingParenthesisSpotIndex = computerNumber;

				if (closingParenthesis[closingParenthesisSpotIndex] == '_')
				{
					closingParenthesis[closingParenthesisSpotIndex] = ')';
					openParenthesisCount--;
					break;
				}
			}
		}
	}

	//Create the expression with operators and parenthesis set, but with unknown numbers
	for (size_t i = 0; i < expression.getSize(); i++)
	{
		//If i % 4 == 0, then this is an opening parenthesis spot
		if (i % 4 == 0 && openingParenthesis[i / 4] == '(') expression[i] = '(';
		//If i % 4 == 2, then this is an closing parenthesis spot
		else if (i % 4 == 2 && closingParenthesis[i / 4] == ')') expression[i] = ')';
	}

	//Replace the remaining free parenthesis spots with empty spaces
	expression = MStringManip::replaceAll(expression, "_", "");

	return expression;
}

mstring BigNumberExpression::getExpressionTemplate() const
{
	return this->getExpressionTemplate(this->expression);
}

mstring BigNumberExpression::getExpressionTemplate(mstring expression) const
{
	//Remove all the whitespaces
	expression = MStringManip::replaceAll(expression, " ", "");

	bool isValidExpression = this->expressionIsValid(expression);
	if (!isValidExpression) throw EXPRESSION_INVALID_EXCEPTION;

	//Replace all the -,+ operators where the -,+ belongs to the number instead of being an operator
	expression = MStringManip::replaceAll(expression, "+-", "+");
	expression = MStringManip::replaceAll(expression, "--", "-");
	expression = MStringManip::replaceAll(expression, "-+", "-");
	expression = MStringManip::replaceAll(expression, "*+", "*");
	expression = MStringManip::replaceAll(expression, "/+", "/");
	expression = MStringManip::replaceAll(expression, "%+", "%");
	expression = MStringManip::replaceAll(expression, "*-", "*");
	expression = MStringManip::replaceAll(expression, "/-", "/");
	expression = MStringManip::replaceAll(expression, "%-", "%");

	//Check if the first char of the expression is + or -. If it is, then remove it entirely
	if (expression[0] == '-' || expression[0] == '+')
	{
		expression = MStringManip::replaceFrom(expression, "", 0, 0);
	}

	//Replace all of the numbers in the expression with an x
	expression = this->replaceNumbers(expression, "x");

	return expression;
}

mstring BigNumberExpression::getExpressionTemplate(const BigNumberExpression& expression) const
{
	return getExpressionTemplate(expression.getExpression());
}

mstring BigNumberExpression::generateExpressionFromTemplate(mstring expressionTemplate) const
{
	mstring expressionFilled = expressionTemplate;

	//Replace the x in the expression template with numbers
	while (MStringManip::stringContains(expressionFilled, "x"))
	{
		//Generate the sign of the number
		BigNumber bigNumber = BigNumber();
		int signOfNumber = this->generateSign();
		if (signOfNumber != 0)
		{
			//Randomly generate a number
			size_t digitsCount = this->generateDigitsCount();
			size_t capacity = digitsCount + 1;
			size_t digitsIndex = 0;

			if (signOfNumber == -1) capacity++;

			mstring numberString;

			if (signOfNumber == -1) numberString += '-';

			numberString += rand() % 9 + 1 + '0';
			for (size_t i = 1; i < digitsCount; i++)
			{
				numberString += (rand() % 10) + '0';
			}

			bigNumber = BigNumber(numberString);
		}

		//Replace the bigNumber in the expressionTemplate
		expressionFilled = MStringManip::replaceFirst(expressionFilled, "x", bigNumber.getNumberRaw());
	}

	return expressionFilled;
}

void BigNumberExpression::generateExpression()
{
	this->generateExpression(EXPRESSION_OPERATORS);
}

void BigNumberExpression::generateExpression(mstring allowedOperators)
{
	mstring expressionTemplate = this->generateExpressionTemplate(allowedOperators);

	mstring expression = this->generateExpressionFromTemplate(expressionTemplate);

	this->expression = expression;
}

mstring BigNumberExpression::concatExpressionsWithOperator(mstring thisExpression, mstring otherExpression, mstring concatOperator) const
{
	mstring parenthesisOpening = "(";
	mstring parenthesisClosing = ")";

	mstring newExpressionString;

	newExpressionString = parenthesisOpening + thisExpression + parenthesisClosing 
		+ concatOperator 
		+ parenthesisOpening + otherExpression + parenthesisClosing;

	return newExpressionString;
}

bool BigNumberExpression::operator==(const BigNumberExpression& other) const
{
	return this->evaluateExpression() == other.evaluateExpression();
}

bool BigNumberExpression::operator!=(const BigNumberExpression& other) const
{
	return !(*this == other);
}

bool BigNumberExpression::operator<(const BigNumberExpression& other) const
{
	return *this <= other && *this != other;
}

bool BigNumberExpression::operator<=(const BigNumberExpression& other) const
{
	return this->evaluateExpression() <= other.evaluateExpression();
}

bool BigNumberExpression::operator>(const BigNumberExpression& other) const
{
	return !(*this <= other);
}

bool BigNumberExpression::operator>=(const BigNumberExpression& other) const
{
	return !(*this < other);
}

BigNumberExpression BigNumberExpression::operator+(const BigNumberExpression& other) const
{
	mstring newExpressionString = this->concatExpressionsWithOperator(this->getExpression(), other.getExpression(), "+");
	BigNumberExpression newExpression(newExpressionString);

	return newExpression;
}

BigNumberExpression& BigNumberExpression::operator+=(const BigNumberExpression& other)
{
	*this = *this + other;
	return *this;
}

BigNumberExpression BigNumberExpression::operator-(const BigNumberExpression& other) const
{
	mstring newExpressionString = this->concatExpressionsWithOperator(this->getExpression(), other.getExpression(), "-");
	BigNumberExpression newExpression(newExpressionString);

	return newExpression;
}

BigNumberExpression& BigNumberExpression::operator-=(const BigNumberExpression& other)
{
	*this = *this - other;
	return *this;
}

BigNumberExpression BigNumberExpression::operator*(const BigNumberExpression& other) const
{
	mstring newExpressionString = this->concatExpressionsWithOperator(this->getExpression(), other.getExpression(), "*");
	BigNumberExpression newExpression(newExpressionString);

	return newExpression;
}

BigNumberExpression& BigNumberExpression::operator*=(const BigNumberExpression& other)
{
	*this = *this * other;
	return *this;
}

BigNumberExpression BigNumberExpression::operator/(const BigNumberExpression& other) const
{
	mstring newExpressionString = this->concatExpressionsWithOperator(this->getExpression(), other.getExpression(), "/");
	BigNumberExpression newExpression(newExpressionString);

	return newExpression;
}

BigNumberExpression& BigNumberExpression::operator/=(const BigNumberExpression& other)
{
	*this = *this / other;
	return *this;
}

BigNumberExpression BigNumberExpression::operator%(const BigNumberExpression& other) const
{
	mstring newExpressionString = this->concatExpressionsWithOperator(this->getExpression(), other.getExpression(), "%");
	BigNumberExpression newExpression(newExpressionString);

	return newExpression;
}

BigNumberExpression& BigNumberExpression::operator%=(const BigNumberExpression& other)
{
	*this = *this % other;
	return *this;
}

std::istream& operator>>(std::istream& is, BigNumberExpression& expression)
{
	//Let's just agree that an expression larger than 10000 symbols cannot occur.
	char* textLine = new char[10000];
	is.getline(textLine, 10000);

	expression.setExpression(textLine);

	return is;
}

std::ostream& operator<<(std::ostream& os, const BigNumberExpression& expression)
{
	os << "This is the expression: " << expression.getExpression() << std::endl;
	os << "And this is the answer: " << expression.evaluateExpression() << std::endl;

	return os;
}

std::ifstream& operator>>(std::ifstream& is, BigNumberExpression& expression)
{
	//Let's just agree that an expression larger than 10000 symbols cannot occur.
	char* textLine = new char[10000];
	is.getline(textLine, 10000);

	expression.setExpression(textLine);

	return is;
}

std::ofstream& operator<<(std::ofstream& os, const BigNumberExpression& expression)
{
	mstring expressionString = expression.getExpression();
	BigNumber resultFromExpression = expression.evaluateExpression();
	mstring answer = resultFromExpression.getNumber();

	mstring textLine = expressionString + "=" + answer;

	os << textLine << "\n";

	return os;
}
