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
		/*
		10 20 30 40 50
		+  *  /  -  %
		10 600 40 50
		+  /   -  %
		*/
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

BigNumber BigNumberExpression::evaluteExpression() const
{
	char* expression = new char[this->capacity];
	strcpy(expression, this->getExpression());
	//TODO: For now, I am assuming that the expression is valid by default. Make a function which checks if the expression is valid!
	
	//Check if expression starts with +- or -+ or ends with them. If it does, then it's invalid
	//bool invalidExpression = StringManip::stringStartsWith(expression, "+-") ||
	//	StringManip::stringStartsWith(expression, "-+") ||
	//	StringManip::stringEndsWith(expression, "+-") ||
	//	StringManip::stringEndsWith(expression, "-+");
	//if (invalidExpression) throw "Invalid Expression";

	//Replace all the instances of +- or -+ inside the string
	StringManip::replaceAll(expression, "+-", "-");
	StringManip::replaceAll(expression, "-+", "-");

	//Check for parentheses
	bool parenthesesExist = StringManip::findIndex(expression, "(") > -1;

	//If parentheses exist, then evaluate the expressions in the parentheses and then try to evaluate the whole expression again until the parentheses are removed
	if (parenthesesExist)
	{
		//TODO: implement
	}
	else
	{
		//Get all the operators
		size_t operatorsCapacity = 10;
		char* operators = new char[operatorsCapacity + 1];
		size_t operatorsCount = 0;
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

				operators[operatorsCount++] = expression[i];
			}
		}
		//Set the null terminator
		operators[operatorsCount++] = '\0';

		//TODO: Somehow differentiate the negative numbers from the rest of the numbers;
		//Get all the numbers
		//Replace all the + with the delim |
		char* expressionPlusReplaced = StringManip::replaceAll(expression, "+", "|");
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


		//Get the actual BigNumber numbers
		BigNumber* numbers = new BigNumber[countOfNumbers];
		for (size_t i = 0; i < countOfNumbers; i++)
		{
			numbers[i] = BigNumber(numberStrings[i]);
		}

		//Start calculating
		while (strlen(operators) > 0)
		{
			//Calculate the priority operators (*, /, %) first
			int multiplyIndex = StringManip::findIndex(operators, "*");
			int divideIndex = StringManip::findIndex(operators, "/");
			int percentIndex = StringManip::findIndex(operators, "%");
			int lowestIndex = multiplyIndex < divideIndex ? (multiplyIndex < percentIndex ? multiplyIndex : percentIndex) : (divideIndex < percentIndex ? divideIndex : percentIndex);
			
			//If there is a priority operator, then calculate it's expression
			if (lowestIndex != -1)
			{
				char firstOperator = operators[lowestIndex];
				BigNumber firstNumber = numbers[lowestIndex];
				BigNumber secondNumber = numbers[lowestIndex + 1];
				BigNumber* resultNumber = nullptr;
				if (firstOperator == '*')
				{
					*resultNumber = firstNumber * secondNumber;
				}
				else if (firstOperator == '/')
				{
					*resultNumber = firstNumber / secondNumber;
				}
				else if (firstOperator == '%')
				{
					*resultNumber = firstNumber % secondNumber;
				}

				if (resultNumber == nullptr) throw "This isn't supposed to happen lol";

				//Replace the 2 numbers in the numbers array with the result number
				numbers = replaceNumbersFromCalculation(numbers, countOfNumbers, lowestIndex, resultNumber);

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
	}

	//This is an error state
	return BigNumber();
}

void BigNumberExpression::generateExpression()
{
}
