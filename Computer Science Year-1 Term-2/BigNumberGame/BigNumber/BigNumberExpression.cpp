#include "BigNumberExpression.h"
#include "..\Project.StringManipulation\StringManip.h"
#include <cstddef>
#include <limits>

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
	this->expression = new char[2];
	this->expression[0] = '0';
	this->expression[1] = '\0';
	this->capacity = 2;
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
	:BigNumberExpression()
{
	this->setExpression(expression);
}

const char* BigNumberExpression::getExpression() const
{
	return this->expression;
}

void BigNumberExpression::setExpression(const char* expression)
{
	if (!expressionIsValid(expression)) throw "The expression that you are trying to set is invalid";

	//Remove all the whitespaces
	char* expressionCopy = StringManip::replaceAll(expression, " ", "");

	size_t capacityOfNewExpression = strlen(expressionCopy) + 1;
	//Resize expression if needed
	if (capacityOfNewExpression> this->capacity)
	{
		this->capacity = capacityOfNewExpression;
		delete[] this->expression;
		this->expression = new char[this->capacity];
	}
	strcpy(this->expression, expressionCopy);

	//Delete dynamic memory
	delete[] expressionCopy;
}

BigNumber BigNumberExpression::evaluateExpression(const char* expression) const
{
	if (expression == nullptr)
	{
		expression = this->getExpression();
	}

	//Remove all the whitespaces
	expression = StringManip::replaceAll(expression, " ", "");

	bool isValidExpression = expressionIsValid(expression); 
	if (!isValidExpression) throw "This expression isn't valid";

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
		BigNumber expressionResult = this->evaluateExpression(parenthesisExpression);

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

bool BigNumberExpression::expressionIsValid(const char* expression) const
{
	if (expression == nullptr) expression = this->getExpression();

	//Replace the whitespaces in the expression before checks for it's validity
	const char* expressionCopy = StringManip::replaceAll(expression, " ", "");

	//Check if the expression's length is 0. If it is, then return false
	if (strlen(expressionCopy) == 0)
	{
		//Delete dynamic memory
		delete[] expressionCopy;

		return false;
	}

	//Check if the expression contains something other than the operators, parenthesis or digits
	for (size_t i = 0; i < strlen(expressionCopy); i++)
	{
		char symbol = expressionCopy[i];
		if (symbol != '+' && symbol != '-' && symbol != '*' && symbol != '/' && symbol != '%' && symbol != '(' && symbol != ')' && !isdigit(symbol))
		{
			//Delete dynamic memory
			delete[] expressionCopy;

			return false;
		}
	}

	bool expressionIsInvalid = false;

	for (size_t i = 0; i < EXPRESSION_FORBIDDEN_STRINGS_COUNT; i++)
	{
		if (StringManip::stringContains(expressionCopy, EXPRESSION_FORBIDDEN_STRINGS[i]))
		{
			//Delete dynamic memory
			delete[] expressionCopy;

			return false;
		}
	}

	if (expressionIsInvalid)
	{
		//Delete dynamic memory
		delete[] expressionCopy;

		return false;
	}

	//Check if all the parenthesis are closed correctly
	int openedParenthesis = 0;
	for (size_t i = 0; i < strlen(expressionCopy); i++)
	{
		if (expressionCopy[i] == '(') openedParenthesis++;
		else if (expressionCopy[i] == ')') openedParenthesis--;
		//If this happens, then there is a closing parenthesis which doesn't have a matching opening parenthesis. So the expression is invalid
		if (openedParenthesis < 0)
		{
			//Delete dynamic memory
			delete[] expressionCopy;

			return false;
		}
	}
	//If this happens, then there is an opening parenthesis which doesn't have a matching closing parenthesis. So the expression is invalid
	if (openedParenthesis > 0)
	{
		//Delete dynamic memory
		delete[] expressionCopy;

		return false;
	}

	//If this happens, then the expression has passed the test and is correct
	//Delete dynamic memory
	delete[] expressionCopy;

	return true;
}

//char BigNumberExpression::generateOperator(int seed) const
//{
//	if (seed == 4) return '%';
//	else if (seed == 3) return '/';
//	else if (seed == 2) return '*';
//	else if (seed == 1) return '-';
//	else if (seed == 0) return '+';
//}
//
//char BigNumberExpression::generateOpeningParenthesis(int seed) const
//{
//	if (seed > 7) return '(';
//	else if (seed >= 0) return '#';
//}
//
//int BigNumberExpression::generateSign(int seed) const
//{
//	if (seed >= 12) return -1;
//	else if (seed >= 1) return 1;
//	else if (seed == 0) return 0;
//}
//
//size_t BigNumberExpression::generateDigitsCount(int seed) const
//{
//	if (seed == 50) return 30;
//	else if (seed >= 48) return 9;
//	else if (seed >= 46) return 8;
//	else if (seed >= 43) return 7;
//	else if (seed >= 39) return 6;
//	else if (seed >= 34) return 5;
//	else if (seed >= 25) return 4;
//	else if (seed >= 16) return 3;
//	else if (seed >= 8) return 2;
//	else if (seed <= 7) return 1;
//}

char* BigNumberExpression::generateExpressionTemplate() const
{
	return generateExpressionTemplate("+-*/%");
}

char* BigNumberExpression::generateExpressionTemplate(const char* allowedOperators) const
{
	int computerNumber = 0;

	//Decide all of the operators and the parenthesis
	//+ - * / % ( E
	//0 1 2 3 4 5 6
	computerNumber = rand() % 20;
	size_t countOfOperators = -1;

	//Determine the count of the operators
	if (computerNumber >= 18) countOfOperators = 10;
	else if (computerNumber >= 16) countOfOperators = 9;
	else if (computerNumber >= 14) countOfOperators = 8;
	else if (computerNumber >= 12) countOfOperators = 7;
	else if (computerNumber >= 10) countOfOperators = 6;
	else if (computerNumber >= 8) countOfOperators = 5;
	else if (computerNumber >= 6) countOfOperators = 4;
	else if (computerNumber >= 4) countOfOperators = 3;
	else if (computerNumber >= 2) countOfOperators = 2;
	else if (computerNumber >= 0) countOfOperators = 1;

	char* operators = new char[countOfOperators + 1];
	operators[countOfOperators] = '\0';
	for (size_t i = 0; i < countOfOperators; i++)
	{
		do
		{
			// Determine the operators
			computerNumber = rand() % 5;
			operators[i] = generateOperator(computerNumber);
		} while (StringManip::stringContains(allowedOperators, operators[i]) == false);
	}

	//Generate a new expression without parenthesis
	size_t newExpressionMaxLength = (countOfOperators * 2 + 1) * 2 + 1;
	char* expression = new char[newExpressionMaxLength + 1];
	expression[newExpressionMaxLength] = '\0';
	size_t operatorsIndexer = 0;
	for (size_t i = 0; i < newExpressionMaxLength; i++)
	{
		if (i % 2 == 0)
		{
			expression[i] = '_';
		}
		else if (i % 4 == 1)
		{
			expression[i] = 'x';
		}
		else if (i % 4 == 3)
		{
			expression[i] = operators[operatorsIndexer++];
		}
	}

	// Opening parenthesis --> _x+_x-_x
	// Closing parenthesis --> x_+x_-x_
	// _x_+_x_-_x_ ---> (x_+_x_-_x_ ---> (x_+_x)-_x_
	// (x+)x-_x
	char* openingParenthesis = new char[countOfOperators + 2];
	openingParenthesis[countOfOperators + 1] = '\0';
	size_t openParenthesisCount = 0;

	//Randomly generate the opening parenthesis amongst the opening parenthesis spots
	for (size_t i = 0; i < strlen(openingParenthesis); i++)
	{
		computerNumber = rand() % 10;
		openingParenthesis[i] = generateOpeningParenthesis(computerNumber);
		if (openingParenthesis[i] == '(') openParenthesisCount++;
	}

	//Randomly generate the closing parenthesis amongst the closing parenthesis spots. Be careful to close out all opening parenthesis with closing ones.
	char* closingParenthesis = new char[countOfOperators + 2];
	closingParenthesis[countOfOperators + 1] = '\0';
	for (size_t i = 0; i < strlen(closingParenthesis); i++)
	{
		closingParenthesis[i] = '_';
	}

	size_t lastOpenParenthesisIndex = strlen(openingParenthesis);
	while (openParenthesisCount > 0)
	{
		lastOpenParenthesisIndex = StringManip::findIndexLast(openingParenthesis, "(", 0, lastOpenParenthesisIndex - 1);
		size_t firstOpenParenthesisIndex = StringManip::findIndex(openingParenthesis, "(");

		//These are all of the valid closing parenthesis spots, i.e. the ones which are not before any opening parenthesis
		size_t closingParenthesisSpotsLeft = StringManip::countOf(closingParenthesis, "_", firstOpenParenthesisIndex, strlen(closingParenthesis) - 1);

		//These are all of the valid closing parenthesis spots which are located to the right of the rightmost open parenthesis
		size_t closingParenthesisSpotsLeftForLastOpenParenthesis = StringManip::countOf(closingParenthesis, "_", lastOpenParenthesisIndex, strlen(closingParenthesis) - 1);

		//If there are exactly as many spots left for closing parenthesis as there are opening parenthesis left unclosed, where the closing parenthesis spots
		// are all located to the right of the leftmost opening parenthesis, then there is no room for randomisation.
		//In that case, fill in the remaining closingParenthesis spots with closing parenthesis	
		if (closingParenthesisSpotsLeft == openParenthesisCount)
		{
			for (size_t i = firstOpenParenthesisIndex; i < strlen(closingParenthesis); i++)
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
			size_t remainingClosingParenthesisSpot = StringManip::findIndex(closingParenthesis, "_", lastOpenParenthesisIndex, strlen(closingParenthesis) - 1);
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
	for (size_t i = 0; i < strlen(expression); i++)
	{
		//If i % 4 == 0, then this is an opening parenthesis spot
		if (i % 4 == 0 && openingParenthesis[i / 4] == '(') expression[i] = '(';
		//If i % 4 == 0, then this is an closing parenthesis spot
		else if (i % 4 == 2 && closingParenthesis[i / 4] == ')') expression[i] = ')';
	}

	//Replace the remaining free parenthesis spots with empty spaces
	char* removeWhitespaces = StringManip::replaceAll(expression, "_", "");
	delete[] expression;
	expression = removeWhitespaces;

	return expression;
}

char* BigNumberExpression::getExpressionTemplate(const char* expression) const
{
	if (expression == nullptr) expression = this->getExpression();

	char* newExpression = new char[strlen(expression) + 1];
	strcpy(newExpression, expression);

	//Remove all the whitespaces
	newExpression = StringManip::replaceAll(newExpression, " ", "");

	bool isValidExpression = expressionIsValid(newExpression);
	if (!isValidExpression) throw "This expression isn't valid";

	//Replace all the -,+ operators where the -,+ belongs to the number instead of being an operator
	char* expression1 = StringManip::replaceAll(newExpression, "+-", "+");
	char* expression2 = StringManip::replaceAll(expression1, "--", "-");
	char* expression3 = StringManip::replaceAll(expression2, "-+", "-");
	char* expression4 = StringManip::replaceAll(expression3, "*+", "*");
	char* expression5 = StringManip::replaceAll(expression4, "/+", "/");
	char* expression6 = StringManip::replaceAll(expression5, "%+", "%");
	char* expression7 = StringManip::replaceAll(expression6, "*-", "*");
	char* expression8 = StringManip::replaceAll(expression7, "/-", "/");
	char* expression9 = StringManip::replaceAll(expression8, "%-", "%");

	delete[] newExpression;
	newExpression = expression9;

	//Delete dynamic memory
	delete[] expression8;
	delete[] expression7;
	delete[] expression6;
	delete[] expression5;
	delete[] expression4;
	delete[] expression3;
	delete[] expression2;
	delete[] expression1;

	//Check if the first char of the expression is + or -. If it is, then remove it entirely
	if (newExpression[0] == '-' || newExpression[0] == '+')
	{
		const char* expressionCopy = newExpression;
		newExpression = StringManip::replaceFrom(newExpression, "", 0);
		delete[] expressionCopy;
	}

	//Replace all of the numbers in the expression with an x
	
	bool isOnNumber = false;
	size_t currentNumberStartIndex = 0;
	/*char* newExpressionCopy = new char[strlen(newExpression) + 1];
	strcpy(newExpressionCopy, newExpression);*/
	for (size_t i = 0; i < strlen(newExpression); i++)
	{
		char symbol = newExpression[i];

		if (isdigit(symbol) && isOnNumber == false)
		{
			isOnNumber = true;
			currentNumberStartIndex = i;
		}
		else if (!isdigit(symbol) && isOnNumber)
		{
			isOnNumber = false;

			//Replace the digit with an x
			char* expressionCopy = StringManip::replaceFrom(newExpression, "x", currentNumberStartIndex, i-1);
			delete[] newExpression;
			newExpression = expressionCopy;

			//Now move back the counter because you have just deleted a very important number;
			i -= (i - 1 - currentNumberStartIndex + 1 - 1);
		}
	}

	//If the expression ends on a number, then replace that number with x
	if (isOnNumber)
	{
		char* expressionCopy = StringManip::replaceFrom(newExpression, "x", currentNumberStartIndex, strlen(newExpression) - 1);
		delete[] newExpression;
		newExpression = expressionCopy;
	}

	return newExpression;
}

char* BigNumberExpression::getExpressionTemplate(const BigNumberExpression& expression) const
{
	return getExpressionTemplate(expression.getExpression());
}

char* BigNumberExpression::generateExpressionFromTemplate(const char* expressionTemplate) const
{
	char* expressionFilled = new char[strlen(expressionTemplate) + 1];
	strcpy(expressionFilled, expressionTemplate);

	//Replace the x in the expression template with numbers
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

	return expressionFilled;
}

void BigNumberExpression::generateExpression()
{
	generateExpression(EXPRESSION_OPERATORS);
}

void BigNumberExpression::generateExpression(const char* allowedOperators)
{
	char* expressionTemplate = generateExpressionTemplate(allowedOperators);

	char* expression = generateExpressionFromTemplate(expressionTemplate);

	//Delete dynamic memory
	delete[] expressionTemplate;

	//std::cout << "Expression: " << expression;

	//Finally, set the expression of the object to the new expression
	delete[] this->expression;
	this->expression = expression;
	this->capacity = strlen(expression) + 1;
}

char* BigNumberExpression::concatExpressionsWithOperator(const char* thisExpression, const char* otherExpression, const char* concatOperator) const
{
	char parenthesisOpening[] = "(";
	char parenthesisClosing[] = ")";

	size_t newExpressionStringCapacity = strlen(thisExpression) + strlen(otherExpression) + strlen(concatOperator) + 5;
	char* newExpressionString = new char[newExpressionStringCapacity];
	newExpressionString[0] = '\0';

	strcat(newExpressionString, parenthesisOpening);
	strcat(newExpressionString, thisExpression);
	strcat(newExpressionString, parenthesisClosing);
	strcat(newExpressionString, concatOperator);
	strcat(newExpressionString, parenthesisOpening);
	strcat(newExpressionString, otherExpression);
	strcat(newExpressionString, parenthesisClosing);

	return newExpressionString;
}

bool BigNumberExpression::operator==(const BigNumberExpression& other) const
{
	return this->evaluateExpression() == other.evaluateExpression();
}

bool BigNumberExpression::operator!=(const BigNumberExpression& other) const
{
	return !(*this==other);
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
	return !(*this<=other);
}

bool BigNumberExpression::operator>=(const BigNumberExpression& other) const
{
	return !(*this < other);
}

BigNumberExpression BigNumberExpression::operator+(const BigNumberExpression& other) const
{
	char* newExpressionString = concatExpressionsWithOperator(this->getExpression(), other.getExpression(), "+");
	BigNumberExpression newExpression(newExpressionString); 

	//Delete dynamic memory
	delete[] newExpressionString;

	return newExpression;
}

BigNumberExpression& BigNumberExpression::operator+=(const BigNumberExpression& other)
{
	*this = *this + other;
	return *this;
}

BigNumberExpression BigNumberExpression::operator-(const BigNumberExpression& other) const
{
	char* newExpressionString = concatExpressionsWithOperator(this->getExpression(), other.getExpression(), "-");
	BigNumberExpression newExpression(newExpressionString);

	//Delete dynamic memory
	delete[] newExpressionString;

	return newExpression;
}

BigNumberExpression& BigNumberExpression::operator-=(const BigNumberExpression& other)
{
	*this = *this - other;
	return *this;
}

BigNumberExpression BigNumberExpression::operator*(const BigNumberExpression& other) const
{
	char* newExpressionString = concatExpressionsWithOperator(this->getExpression(), other.getExpression(), "*");
	BigNumberExpression newExpression(newExpressionString);

	//Delete dynamic memory
	delete[] newExpressionString;

	return newExpression;
}

BigNumberExpression& BigNumberExpression::operator*=(const BigNumberExpression& other)
{
	*this = *this * other;
	return *this;
}

BigNumberExpression BigNumberExpression::operator/(const BigNumberExpression& other) const
{
	char* newExpressionString = concatExpressionsWithOperator(this->getExpression(), other.getExpression(), "/");
	BigNumberExpression newExpression(newExpressionString);

	//Delete dynamic memory
	delete[] newExpressionString;

	return newExpression;
}

BigNumberExpression& BigNumberExpression::operator/=(const BigNumberExpression& other)
{
	*this = *this / other;
	return *this;
}

BigNumberExpression BigNumberExpression::operator%(const BigNumberExpression& other) const
{
	char* newExpressionString = concatExpressionsWithOperator(this->getExpression(), other.getExpression(), "%");
	BigNumberExpression newExpression(newExpressionString);

	//Delete dynamic memory
	delete[] newExpressionString;

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

std::ostream& operator<<(std::ostream& os, BigNumberExpression& expression)
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

std::ofstream& operator<<(std::ofstream& os, BigNumberExpression& expression)
{
	const char* expressionString = expression.getExpression();
	const char* equals = "=";
	BigNumber resultFromExpression = expression.evaluateExpression();
	const char* answer = resultFromExpression.getNumber();

	size_t textLineCapacity = strlen(expressionString) + 1 + strlen(answer) + 1;
	char* textLine = new char[textLineCapacity];
	textLine[0] = '\0';

	strcat(textLine, expressionString);
	strcat(textLine, equals);
	strcat(textLine, answer);
	textLine[textLineCapacity - 1] = '\n';

	os.write(textLine, textLineCapacity);

	//Delete dynamic memory
	delete[] textLine;
	//delete[] expressionString;
	delete[] answer;

	return os;
}
