#include "BigNumberEquation.h"
#include "..\Project.StringManipulation\StringManip.h"

void BigNumberExpression::copy(const BigNumberExpression& other)
{
	delete[] this->expression;
	this->capacity = other.capacity;
	this->expression = new char[this->capacity];
	strcpy(this->expression, other.expression);
}

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

void BigNumberExpression::replaceOperatorsFromCalculation(char* operators, size_t index) const
{
	//Replace the operator from the operators array
	for (size_t i = index; i < strlen(operators); i++)
	{
		if (i != strlen(operators) - 1) operators[i] = operators[i + 1];
		else operators[i] = '\0';
	}
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

BigNumber BigNumberExpression::evaluteExpression(const char* expression) const
{
	//TODO: For now, I am assuming that the expression is valid by default. Make a function which checks if the expression is valid!
	//Check if expression starts with +- or -+ or ends with them. If it does, then it's invalid
	//bool invalidExpression = StringManip::stringStartsWith(expression, "+-") ||
	//	StringManip::stringStartsWith(expression, "-+") ||
	//	StringManip::stringEndsWith(expression, "+-") ||
	//	StringManip::stringEndsWith(expression, "-+");
	//if (invalidExpression) throw "Invalid Expression";

	if (expression == nullptr)
	{
		expression = this->getExpression();
	}

	//Remove all the whitespaces
	expression = StringManip::replaceAll(expression, " ", "");

	//Start resolving all the parenthesis in the expression until none are left
	//If there are none, at least run the necessary in all cases things first. Hence why this is a do, while expression instead of a simple while expression
	do
	{
		//Replace all the instances of +-,-+, -- inside the string
		char* expressionOne = StringManip::replaceAll(expression, "+-", "-");
		char* expressionTwo = StringManip::replaceAll(expressionOne, "-+", "-");
		char* expressionThree = StringManip::replaceAll(expressionTwo, "--", "+");

		delete[] expression;
		expression = expressionThree;

		//Delete dynamic memory
		delete[] expressionTwo;
		delete[] expressionOne;

		//Check if the first char of the expression is + or -. If it is, then add a "0" in front of the equation
		if (expression[0] == '-' || expression[0] == '+')
		{
			char* expressionCopy = new char[strlen(expression) + 2];
			expressionCopy[0] = '0';
			expressionCopy[1] = '\0';
			strcat(expressionCopy, expression);
			delete[] expression;
			expression = expressionCopy;
		}

		//Check for parentheses. If they are not there, then exit out of the loop
		bool parenthesisExist = StringManip::stringContains(expression, "(");

		if (!parenthesisExist) break;

		//Find the indexes of the rightmost opening parenthesis and it's closing parenthesis
		int lastOpeningParenthesis = StringManip::findIndexLast(expression, "(");
		int closingParenthesis = -1;
		for (size_t i = lastOpeningParenthesis + 1; i < strlen(expression); i++)
		{
			if (expression[i] == ')')
			{
				closingParenthesis = i;
				break;
			}
		}

		//Get the expression inside the parenthesis
		char* parenthesisExpression = new char[closingParenthesis - lastOpeningParenthesis];
		parenthesisExpression[closingParenthesis - lastOpeningParenthesis - 1] = '\0';
		for (size_t i = lastOpeningParenthesis + 1; i < closingParenthesis; i++)
		{
			parenthesisExpression[i - lastOpeningParenthesis - 1] = expression[i];
		}

		//Calculate the new expression
		BigNumber expressionResult = this->evaluteExpression(parenthesisExpression);

		//Delete dynamic memory
		delete[] parenthesisExpression;

		//Create the new parts of the new expression
		char* expressionPartOne = new char[lastOpeningParenthesis + 1];
		strncpy(expressionPartOne, expression, lastOpeningParenthesis);
		expressionPartOne[lastOpeningParenthesis] = '\0';

		const char* expressionPartTwo = expressionResult.getNumberRaw();

		//5+(7-9)+8
		char* expressionPartThree = new char[strlen(expression) - closingParenthesis];
		expressionPartThree[strlen(expression) - closingParenthesis - 1] = '\0';
		for (size_t i = closingParenthesis + 1; i < strlen(expression); i++)
		{
			expressionPartThree[i - closingParenthesis - 1] = expression[i];
		}

		size_t newExpressionLength = strlen(expressionPartOne) + strlen(expressionPartTwo) + strlen(expressionPartThree) + 1;
		char* newExpression = new char[newExpressionLength + 1];
		newExpression[0] = '\0';

		//Concat all the expression parts into the new expression
		strcat(newExpression, expressionPartOne);
		strcat(newExpression, expressionPartTwo);
		strcat(newExpression, expressionPartThree);

		//Set the current expression to the new one
		delete[] expression;
		expression = newExpression;

		//Delete dynamic memory
		delete[] expressionPartThree;
		delete[] expressionPartTwo;
		delete[] expressionPartOne;
	} while (true);

	//Get all the operators
	size_t operatorsCapacity = 10;
	char* operators = new char[operatorsCapacity + 1];
	size_t operatorsCount = 0;

	size_t negativeOperatorsCapacity = 10;
	size_t* negativeOperatorsIndexes = new size_t[operatorsCapacity + 1];
	size_t negativeOperatorsCount = 0;


	for (size_t i = 0; i < strlen(expression); i++)
	{
		if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '%')
		{
			//If operators runs out of capacity, then increase it's capacity
			if (operatorsCount >= operatorsCapacity)
			{
				char* operatorsCopy = new char[operatorsCount * 2 + 1];
				strcpy(operatorsCopy, operators);
				delete[] operators;
				operators = operatorsCopy;
			}

			if (expression[i + 1] == '-')
			{
				operators[operatorsCount] = expression[i];

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
				negativeOperatorsIndexes[negativeOperatorsCount++] = operatorsCount;
				operatorsCount++;
				i++;
			}
			else
			{
				operators[operatorsCount++] = expression[i];
			}
		}
	}

	//If there are no operators, then simply return the number itself
	if (operatorsCount == 0)
	{
		BigNumber result(expression);
		return result;
	}

	//Set the null terminator
	operators[operatorsCount++] = '\0';

	//TODO: make the replaceAll function work on the expression argument instead of creating a new dynamically allocated string

	//Get all the numbers
	//Replace all the *- with the delim |
	char* expressionMultiplyMinusReplaced = StringManip::replaceAll(expression, "*-", "|");
	//Replace all the /- with the delim |
	char* expressionDivideMinusReplaced = StringManip::replaceAll(expressionMultiplyMinusReplaced, "/-", "|");
	//Replace all the %- with the delim |
	char* expressionPercentMinusReplaced = StringManip::replaceAll(expressionDivideMinusReplaced, "%-", "|");
	//Replace all the + with the delim |
	char* expressionPlusReplaced = StringManip::replaceAll(expressionPercentMinusReplaced, "+", "|");
	//Replace all the - with the delim |
	char* expressionMinusReplaced = StringManip::replaceAll(expressionPlusReplaced, "-", "|");
	//Replace all the * with the delim |
	char* expressionMultiplicationReplaced = StringManip::replaceAll(expressionMinusReplaced, "*", "|");
	//Replace all the / with the delim |
	char* expressionDivisionReplaced = StringManip::replaceAll(expressionMultiplicationReplaced, "/", "|");
	//Replace all the % with the delim |
	char* expressionPercentReplaced = StringManip::replaceAll(expressionDivisionReplaced, "%", "|");
	size_t countOfNumbers = 0;
	char** numberStrings = StringManip::splitString(expressionPercentReplaced, '|', countOfNumbers);

	//Delete the dynamic memory from the replaceAll functions
	delete[] expressionPercentReplaced;
	delete[] expressionDivisionReplaced;
	delete[] expressionMultiplicationReplaced;
	delete[] expressionMinusReplaced;
	delete[] expressionPlusReplaced;
	delete[] expressionPercentMinusReplaced;
	delete[] expressionDivideMinusReplaced;
	delete[] expressionMultiplyMinusReplaced;

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
	for (size_t i = 0; i < countOfNumbers; i++)
	{
		delete[] numberStrings[i];
	}
	delete[] numberStrings;

	delete[] negativeOperatorsIndexes;

	//Start calculating
	while (strlen(operators) > 0)
	{
		//Calculate the priority operators (*, /, %) first
		int multiplyIndex = StringManip::findIndex(operators, "*");
		int divideIndex = StringManip::findIndex(operators, "/");
		int percentIndex = StringManip::findIndex(operators, "%");
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
					throw "IDIOT!";
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
					throw "IDIOT!";
				}
			}

			if (!resultNumberIsCalculated) throw "This isn't supposed to happen lol";

			//Replace the 2 numbers in the numbers array with the result number
			numbers = replaceNumbersFromCalculation(numbers, countOfNumbers, lowestIndex, &resultNumber);

			//Replace the operator from the operators array
			replaceOperatorsFromCalculation(operators, lowestIndex);
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
			replaceOperatorsFromCalculation(operators, 0);
		}
	}

	//The only number left in the numbers array should be the end result
	BigNumber& resultNumber = numbers[0];
	return resultNumber;

	//This is an error state
	return BigNumber();
}

void BigNumberExpression::generateExpression()
{
}
