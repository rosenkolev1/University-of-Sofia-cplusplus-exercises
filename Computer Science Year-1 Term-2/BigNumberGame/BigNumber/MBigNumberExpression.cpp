#include "MBigNumberExpression.h"
#include "..\Project.StringManipulation\MStringManip.h"
#include <cstddef>
#include <limits>

//Static constants
const mstring MBigNumberExpression::EXPRESSION_DIVIDEBYZERO_EXCEPTION = "DIVISION BY 0 IS NOT ALLOWED!";
const mstring MBigNumberExpression::EXPRESSION_PERCENTBYZERO_EXCEPTION = "PERCENT BY 0 IS NOT ALLOWED!";
const mstring MBigNumberExpression::EXPRESSION_INVALID_EXCEPTION = "This expression isn't valid";
const mstring MBigNumberExpression::EXPRESSION_OPERATORS = "+-*/%";
const mstring MBigNumberExpression::EXPRESSION_NOTDIGIT = "+-*/%()";
const mstring MBigNumberExpression::EXPRESSION_FORBIDDEN_STRINGS[32] =
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

//void MBigNumberExpression::copy(const MBigNumberExpression& other)
//{
//	delete[] this->expression;
//	this->capacity = other.capacity;
//	this->expression = new char[this->capacity];
//	strcpy(this->expression, other.expression);
//}

MBigNumber* MBigNumberExpression::replaceNumbersFromCalculation(MBigNumber* numbers, size_t& countOfNumbers, size_t firstIndex, MBigNumber* resultNumber) const
{
	//Replace the 2 numbers in the numbers array with the result number
	MBigNumber* numbersCopy = new MBigNumber[countOfNumbers - 1];
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

void MBigNumberExpression::replaceOperatorsFromCalculation(mstring& operators, size_t index) const
{
	//Replace the operator from the operators array
	/*for (size_t i = index; i < operators.getSize(); i++)
	{
		if (i != operators.getSize() - 1) operators[i] = operators[i + 1];
		else operators[i] = '\0';
	}*/

	/*operators = MStringManip::replaceFrom(operators, "", index, index);*/
}

MBigNumberExpression::MBigNumberExpression()
{
	this->expression = "0";
}

//MBigNumberExpression::MBigNumberExpression(const MBigNumberExpression& other)
//	:MBigNumberExpression()
//{
//	this->copy(other);
//}

//MBigNumberExpression::~MBigNumberExpression()
//{
//	delete[] this->expression;
//}

//MBigNumberExpression& MBigNumberExpression::operator=(const MBigNumberExpression& other)
//{
//	if (this == &other) return *this;
//	this->copy(other);
//	return *this;
//}

MBigNumberExpression::MBigNumberExpression(mstring expression)
	:MBigNumberExpression()
{
	this->setExpression(expression);
}

mstring MBigNumberExpression::getExpression() const
{
	return this->expression;
}

void MBigNumberExpression::setExpression(mstring expression)
{
	if (!expressionIsValid(expression)) throw EXPRESSION_INVALID_EXCEPTION;


	//size_t capacityOfNewExpression = expressionCopy.getSize() + 1;
	////Resize expression if needed
	//if (capacityOfNewExpression > this->capacity)
	//{
	//	this->capacity = capacityOfNewExpression;
	//	delete[] this->expression;
	//	this->expression = new char[this->capacity];
	//}
	//strcpy(this->expression, expressionCopy);
	// 
	//Remove all the whitespaces and set the expression
	this->expression = MStringManip::replaceAll(expression, " ", "");

	//Delete dynamic memory
	/*delete[] expressionCopy;*/
}

MBigNumber MBigNumberExpression::evaluateExpression() const
{
	return this->evaluateExpression(this->expression);
}

size_t MBigNumberExpression::generateCountOfOperators() const
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

MBigNumber MBigNumberExpression::evaluateExpression(mstring expression) const
{
	//if (expression == nullptr)
	//{
	//	expression = this->getExpression();
	//}

	//Remove all the whitespaces
	expression = MStringManip::replaceAll(expression, " ", "");

	//bool isValidExpression = this->expressionIsValid(expression);
	if (!this->expressionIsValid(expression)) throw EXPRESSION_INVALID_EXCEPTION;

	//Start resolving all the parenthesis in the expression until none are left
	//If there are none, at least run the necessary in all cases things first. Hence why this is a do, while expression instead of a simple while expression
	do
	{
		////Replace all the instances of +-,-+, -- inside the string
		//char* expressionOne = MStringManip::replaceAll(expression, "+-", "-");
		//char* expressionTwo = MStringManip::replaceAll(expressionOne, "-+", "-");
		//char* expressionThree = MStringManip::replaceAll(expressionTwo, "--", "+");

		////Replace all the instances of *+,/+, %- inside the string
		//char* expressioFour = MStringManip::replaceAll(expressionThree, "*+", "*");
		//char* expressionFive = MStringManip::replaceAll(expressioFour, "/+", "/");
		//char* expressionSix = MStringManip::replaceAll(expressionFive, "%+", "%");

		//delete[] expression;
		//expression = expressionSix;

		////Delete dynamic memory
		//delete[] expressionFive;
		//delete[] expressioFour;
		//delete[] expressionThree;
		//delete[] expressionTwo;
		//delete[] expressionOne;

		//Replace all the instances of +-,-+, -- inside the string
		expression = MStringManip::replaceAll(expression, "+-", "-");
		expression = MStringManip::replaceAll(expression, "-+", "-");
		expression = MStringManip::replaceAll(expression, "--", "+");

		//Replace all the instances of *+,/+, %- inside the string
		expression = MStringManip::replaceAll(expression, "*+", "*");
		expression = MStringManip::replaceAll(expression, "/+", "/");
		expression = MStringManip::replaceAll(expression, "%+", "%");

		/*delete[] expression;
		expression = expressionSix;*/

		//Delete dynamic memory
		/*delete[] expressionFive;
		delete[] expressioFour;
		delete[] expressionThree;
		delete[] expressionTwo;
		delete[] expressionOne;*/

		//Check if the first char of the expression is + or -. If it is, then add a "0" in front of the equation
		if (expression[0] == '-' || expression[0] == '+')
		{
			/*char* expressionCopy = new char[strlen(expression) + 2];
			expressionCopy[0] = '0';
			expressionCopy[1] = '\0';
			strcat(expressionCopy, expression);
			delete[] expression;
			expression = expressionCopy;*/
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

		////Get the expression inside the parenthesis
		//char* parenthesisExpression = new char[closingParenthesis - lastOpeningParenthesis];
		//parenthesisExpression[closingParenthesis - lastOpeningParenthesis - 1] = '\0';
		//for (size_t i = lastOpeningParenthesis + 1; i < closingParenthesis; i++)
		//{
		//	parenthesisExpression[i - lastOpeningParenthesis - 1] = expression[i];
		//}

		//Get the expression inside the parenthesis
		mstring parenthesisExpression;
		for (size_t i = lastOpeningParenthesis + 1; i < closingParenthesis; i++)
		{
			parenthesisExpression += expression[i];
		}

		//Calculate the new expression
		MBigNumber expressionResult = this->evaluateExpression(parenthesisExpression);

		//Delete dynamic memory
		//delete[] parenthesisExpression;

		////Create the new parts of the new expression
		//char* expressionPartOne = new char[lastOpeningParenthesis + 1];
		//strncpy(expressionPartOne, expression, lastOpeningParenthesis);
		//expressionPartOne[lastOpeningParenthesis] = '\0';

		//Create the new parts of the new expression
		mstring expressionPartOne = (lastOpeningParenthesis > 0 ? MStringManip::getFrom(expression, 0, lastOpeningParenthesis - 1) : "");

		mstring expressionPartTwo = expressionResult.getNumberRaw();

		////5+(7-9)+8
		//char* expressionPartThree = new char[strlen(expression) - closingParenthesis];
		//expressionPartThree[strlen(expression) - closingParenthesis - 1] = '\0';
		//for (size_t i = closingParenthesis + 1; i < strlen(expression); i++)
		//{
		//	expressionPartThree[i - closingParenthesis - 1] = expression[i];
		//}

		//5+(7-9)+8
		mstring expressionPartThree = (closingParenthesis + 1 < expression.getSize() ? MStringManip::getFrom(expression, closingParenthesis + 1, expression.getSize() - 1) : "");

		//size_t newExpressionLength = strlen(expressionPartOne) + strlen(expressionPartTwo) + strlen(expressionPartThree) + 1;
		//char* newExpression = new char[newExpressionLength + 1];
		//newExpression[0] = '\0';

		////Concat all the expression parts into the new expression
		//strcat(newExpression, expressionPartOne);
		//strcat(newExpression, expressionPartTwo);
		//strcat(newExpression, expressionPartThree);

		//Set the current expression to the new one
		expression = expressionPartOne + expressionPartTwo + expressionPartThree;

		//Set the current expression to the new one
		//delete[] expression;
		//expression = newExpression;

		////Delete dynamic memory
		//delete[] expressionPartThree;
		//delete[] expressionPartTwo;
		//delete[] expressionPartOne;
	} while (true);

	//Get all the operators
	//size_t operatorsCapacity = 10;
	//char* operators = new char[operatorsCapacity + 1];
	mstring operators;
	//size_t operatorsCount = 0;

	size_t negativeOperatorsCapacity = 10;
	//size_t* negativeOperatorsIndexes = new size_t[operatorsCapacity + 1];
	size_t* negativeOperatorsIndexes = new size_t[negativeOperatorsCapacity];
	size_t negativeOperatorsCount = 0;

	for (size_t i = 0; i < expression.getSize(); i++)
	{
		if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '%')
		{
			////If operators runs out of capacity, then increase it's capacity
			//if (operatorsCount >= operatorsCapacity)
			//{
			//	char* operatorsCopy = new char[operatorsCount * 2 + 1];
			//	strcpy(operatorsCopy, operators);
			//	delete[] operators;
			//	operators = operatorsCopy;
			//}

			if (expression[i + 1] == '-')
			{
				/*operators[operatorsCount] = expression[i];*/
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
				/*operatorsCount++;*/
				i++;
			}
			else
			{
				//operators[operatorsCount++] = expression[i];
				operators += expression[i];
			}
		}
	}

	//If there are no operators, then simply return the number itself
	if (operators.getSize() == 0)
	{
		MBigNumber result(expression);
		return result;
	}

	//Set the null terminator
	//operators[operatorsCount++] = '\0';

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

	//Delete the dynamic memory from the replaceAll functions
	/*delete[] expressionPercentReplaced;
	delete[] expressionDivisionReplaced;
	delete[] expressionMultiplicationReplaced;
	delete[] expressionMinusReplaced;
	delete[] expressionPlusReplaced;
	delete[] expressionPercentMinusReplaced;
	delete[] expressionDivideMinusReplaced;
	delete[] expressionMultiplyMinusReplaced;*/

	//Get the actual MBigNumber numbers
	MBigNumber* numbers = new MBigNumber[countOfNumbers];
	for (size_t i = 0; i < countOfNumbers; i++)
	{
		numbers[i] = MBigNumber(numberStrings[i]);
		//Check if the current number is supposed to be negative and the lefthand side of a multiplication, division or percent operator
		//If it is, then multiply it by -1
		for (size_t y = 0; y < negativeOperatorsCount; y++)
		{
			if (i - 1 == negativeOperatorsIndexes[y]) numbers[i] *= -1;
		}
	}

	//Delete dynamic memory
	//for (size_t i = 0; i < countOfNumbers; i++)
	//{
	//	delete[] numberStrings[i];
	//}
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
			MBigNumber firstNumber = numbers[lowestIndex];
			MBigNumber secondNumber = numbers[lowestIndex + 1];
			MBigNumber resultNumber = MBigNumber();
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
			//this->replaceOperatorsFromCalculation(operators, lowestIndex);
			operators = MStringManip::replaceFrom(operators, "", lowestIndex, lowestIndex);
		}
		//If there is no priority operator, then calculate the non-priority operators (+, -)
		else
		{
			char currentOperator = operators[0];
			MBigNumber firstNumber = numbers[0];
			MBigNumber secondNumber = numbers[1];
			MBigNumber resultNumber = MBigNumber();
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
			//this->replaceOperatorsFromCalculation(operators, 0);
			operators = MStringManip::replaceFrom(operators, "", 0, 0);
		}
	}

	//The only number left in the numbers array should be the end result
	MBigNumber& resultNumber = numbers[0];
	return resultNumber;
}

bool MBigNumberExpression::expressionIsValid() const
{
	return this->expressionIsValid(this->expression);
}

bool MBigNumberExpression::expressionIsValid(mstring expression) const
{
	//if (expression == nullptr) expression = this->getExpression();

	//Replace the whitespaces in the expression before checks for it's validity
	/*mstring expressionCopy = MStringManip::replaceAll(expression, " ", "");*/
	expression = MStringManip::replaceAll(expression, " ", "");

	//Check if the expression's length is 0. If it is, then return false
	if (expression.getSize() == 0)
	{
		//Delete dynamic memory
		//delete[] expressionCopy;

		return false;
	}

	//Check if the expression contains something other than the operators, parenthesis or digits
	for (size_t i = 0; i < expression.getSize(); i++)
	{
		//char symbol = expressionCopy[i];
		char symbol = expression[i];
		if (!MStringManip::stringContains(EXPRESSION_NOTDIGIT, symbol) && !isdigit(symbol))
		{
			//Delete dynamic memory
			//delete[] expressionCopy;

			return false;
		}
	}

	bool expressionIsInvalid = false;

	//Check if the expression contains forbidden strings
	for (size_t i = 0; i < EXPRESSION_FORBIDDEN_STRINGS_COUNT; i++)
	{
		if (MStringManip::stringContains(expression, EXPRESSION_FORBIDDEN_STRINGS[i]))
		{
			//Delete dynamic memory
			//delete[] expressionCopy;

			return false;
		}
	}

	if (expressionIsInvalid)
	{
		//Delete dynamic memory
		//delete[] expressionCopy;

		return false;
	}

	//Check if the expression finishes on an operator or start with an invalid operator. If it does, then it's invalid
	for (size_t i = 0; i < EXPRESSION_OPERATORS.getSize(); i++)
	{
		char symbolString[2] = { EXPRESSION_OPERATORS[i] };
		if (MStringManip::stringEndsWith(expression, symbolString))
		{
			//Delete dynamic memory
			//delete[] expressionCopy;

			return false;
		}
	}

	for (size_t i = 0; i < EXPRESSION_OPERATORS.getSize(); i++)
	{
		char symbolString[2] = { EXPRESSION_OPERATORS[i] };
		if (EXPRESSION_OPERATORS[i] != '+' && EXPRESSION_OPERATORS[i] != '-' && MStringManip::stringStartsWith(expression, symbolString))
		{
			//Delete dynamic memory
			//delete[] expressionCopy;

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
			//Delete dynamic memory
			//delete[] expressionCopy;

			return false;
		}
	}
	//If this happens, then there is an opening parenthesis which doesn't have a matching closing parenthesis. So the expression is invalid
	if (openedParenthesis > 0)
	{
		//Delete dynamic memory
		//delete[] expressionCopy;

		return false;
	}

	//If this happens, then the expression has passed the test and is correct
	//Delete dynamic memory
	//delete[] expressionCopy;

	return true;
}

bool MBigNumberExpression::expressionTemplateIsValid(mstring expressionTemplate) const
{
	//Replace all of the whitespaces
	/*char* expressionTemplateCopy = MStringManip::replaceAll(expressionTemplate, " ", "");*/
	expressionTemplate = MStringManip::replaceAll(expressionTemplate, " ", "");

	//Replace all of the numbers with -1;
	mstring expressionFromTemplate = MStringManip::replaceAll(expressionTemplate, "x", "-1");
	//delete[] expressionTemplateCopy;

	return this->expressionIsValid(expressionFromTemplate);
}

mstring MBigNumberExpression::generateExpressionTemplate() const
{
	return generateExpressionTemplate("+-*/%");
}

mstring MBigNumberExpression::generateExpressionTemplate(mstring allowedOperators) const
{
	int computerNumber = 0;

	//Decide all of the operators and the parenthesis
	//+ - * / % ( E
	//0 1 2 3 4 5 6
	
	//size_t countOfOperators = -1;

	//computerNumber = rand() % 20;
	////Determine the count of the operators
	//if (computerNumber >= 18) countOfOperators = 10;
	//else if (computerNumber >= 16) countOfOperators = 9;
	//else if (computerNumber >= 14) countOfOperators = 8;
	//else if (computerNumber >= 12) countOfOperators = 7;
	//else if (computerNumber >= 10) countOfOperators = 6;
	//else if (computerNumber >= 8) countOfOperators = 5;
	//else if (computerNumber >= 6) countOfOperators = 4;
	//else if (computerNumber >= 4) countOfOperators = 3;
	//else if (computerNumber >= 2) countOfOperators = 2;
	//else if (computerNumber >= 0) countOfOperators = 1;
	size_t countOfOperators = this->generateCountOfOperators();

	//char* operators = new char[countOfOperators + 1];
	//operators[countOfOperators] = '\0';
	//for (size_t i = 0; i < countOfOperators; i++)
	//{
	//	do
	//	{
	//		// Determine the operators
	//		computerNumber = rand() % 5;
	//		operators[i] = generateOperator(computerNumber);
	//	} while (MStringManip::stringContains(allowedOperators, operators[i]) == false);
	//}

	mstring operators;
	for (size_t i = 0; i < countOfOperators; i++)
	{
		do
		{
			// Determine the operators
			/*computerNumber = rand() % 5;
			operators[i] = generateOperator(computerNumber);*/
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
	/*char* expression = new char[newExpressionMaxLength + 1];
	expression[newExpressionMaxLength] = '\0';*/
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
	/*char* openingParenthesis = new char[countOfOperators + 2];
	openingParenthesis[countOfOperators + 1] = '\0';*/
	mstring openingParenthesis;
	size_t openParenthesisCount = 0;

	//Randomly generate the opening parenthesis amongst the opening parenthesis spots
	//for (size_t i = 0; i < strlen(openingParenthesis); i++)
	//{
	//	/*computerNumber = rand() % 10;
	//	openingParenthesis[i] = generateOpeningParenthesis(computerNumber);*/

	//	if (openingParenthesis[i] == '(') openParenthesisCount++;
	//}
	for (size_t i = 0; i < countOfOperators + 1; i++)
	{
		/*computerNumber = rand() % 10;
		openingParenthesis[i] = generateOpeningParenthesis(computerNumber);*/
		
		openingParenthesis += generateOpeningParenthesis();
		if (openingParenthesis[i] == '(') openParenthesisCount++;
	}

	//Randomly generate the closing parenthesis amongst the closing parenthesis spots. Be careful to close out all opening parenthesis with closing ones.
	/*char* closingParenthesis = new char[countOfOperators + 2];
	closingParenthesis[countOfOperators + 1] = '\0';*/
	mstring closingParenthesis;
	/*for (size_t i = 0; i < strlen(closingParenthesis); i++)
	{
		closingParenthesis[i] = '_';
	}*/
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
	/*char* removeWhitespaces = MStringManip::replaceAll(expression, "_", "");
	delete[] expression;
	expression = removeWhitespaces;*/
	expression = MStringManip::replaceAll(expression, "_", "");

	return expression;
}

mstring MBigNumberExpression::getExpressionTemplate() const
{
	return this->getExpressionTemplate(this->expression);
}

mstring MBigNumberExpression::getExpressionTemplate(mstring expression) const
{
	//if (expression == nullptr) expression = this->getExpression();

	/*char* newExpression = new char[strlen(expression) + 1];
	strcpy(newExpression, expression);*/

	//Remove all the whitespaces
	//newExpression = MStringManip::replaceAll(newExpression, " ", "");
	expression = MStringManip::replaceAll(expression, " ", "");

	bool isValidExpression = this->expressionIsValid(expression);
	if (!isValidExpression) throw EXPRESSION_INVALID_EXCEPTION;

	////Replace all the -,+ operators where the -,+ belongs to the number instead of being an operator
	//char* expression1 = MStringManip::replaceAll(newExpression, "+-", "+");
	//char* expression2 = MStringManip::replaceAll(expression1, "--", "-");
	//char* expression3 = MStringManip::replaceAll(expression2, "-+", "-");
	//char* expression4 = MStringManip::replaceAll(expression3, "*+", "*");
	//char* expression5 = MStringManip::replaceAll(expression4, "/+", "/");
	//char* expression6 = MStringManip::replaceAll(expression5, "%+", "%");
	//char* expression7 = MStringManip::replaceAll(expression6, "*-", "*");
	//char* expression8 = MStringManip::replaceAll(expression7, "/-", "/");
	//char* expression9 = MStringManip::replaceAll(expression8, "%-", "%");

	//delete[] newExpression;
	//newExpression = expression9;

	////Delete dynamic memory
	//delete[] expression8;
	//delete[] expression7;
	//delete[] expression6;
	//delete[] expression5;
	//delete[] expression4;
	//delete[] expression3;
	//delete[] expression2;
	//delete[] expression1;

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

	/*delete[] newExpression;
	newExpression = expression9;*/

	//Delete dynamic memory
	/*delete[] expression8;
	delete[] expression7;
	delete[] expression6;
	delete[] expression5;
	delete[] expression4;
	delete[] expression3;
	delete[] expression2;
	delete[] expression1;*/

	//Check if the first char of the expression is + or -. If it is, then remove it entirely
	/*if (newExpression[0] == '-' || newExpression[0] == '+')
	{
		mstring expressionCopy = newExpression;
		newExpression = MStringManip::replaceFrom(newExpression, "", 0, 0);
		delete[] expressionCopy;
	}*/
	if (expression[0] == '-' || expression[0] == '+')
	{
		expression = MStringManip::replaceFrom(expression, "", 0, 0);
	}

	//Replace all of the numbers in the expression with an x
	/*char* newExpressionCopy = replaceNumbers(newExpression, "x");
	delete[] newExpression;
	newExpression = newExpressionCopy;*/

	expression = this->replaceNumbers(expression, "x");

	return expression;
}

mstring MBigNumberExpression::getExpressionTemplate(const MBigNumberExpression& expression) const
{
	return getExpressionTemplate(expression.getExpression());
}

mstring MBigNumberExpression::generateExpressionFromTemplate(mstring expressionTemplate) const
{
	//char* expressionFilled = new char[strlen(expressionTemplate) + 1];
	//strcpy(expressionFilled, expressionTemplate);
	mstring expressionFilled = expressionTemplate;

	//Replace the x in the expression template with numbers
	while (MStringManip::stringContains(expressionFilled, "x"))
	{
		//Generate the sign of the number
		MBigNumber bigNumber = MBigNumber();
		/*int signOfNumber = generateSign(rand() % 15);*/
		int signOfNumber = this->generateSign();
		if (signOfNumber != 0)
		{
			//Randomly generate a number
			//size_t digitsCount = this->generateDigitsCount(rand() % 51);
			size_t digitsCount = this->generateDigitsCount();
			size_t capacity = digitsCount + 1;
			size_t digitsIndex = 0;

			if (signOfNumber == -1) capacity++;

			/*char* numberString = new char[capacity];
			numberString[capacity - 1] = '\0';*/
			mstring numberString;

			/*if (signOfNumber == -1) numberString[digitsIndex++] = '-';*/
			if (signOfNumber == -1) numberString += '-';

			/*numberString[digitsIndex++] = rand() % 9 + 1 + '0';
			for (size_t i = digitsIndex; i < digitsCount; i++)
			{
				numberString[i] = (rand() % 10) + '0';
			}*/

			numberString += rand() % 9 + 1 + '0';
			for (size_t i = 1; i < digitsCount; i++)
			{
				numberString += (rand() % 10) + '0';
			}

			bigNumber = MBigNumber(numberString);
		}

		//Replace the bigNumber in the expressionTemplate
		/*char* newExpressionTemplate = MStringManip::replaceFirst(expressionFilled, "x", bigNumber.getNumberRaw());
		delete[] expressionFilled;
		expressionFilled = newExpressionTemplate;*/
		expressionFilled = MStringManip::replaceFirst(expressionFilled, "x", bigNumber.getNumberRaw());
	}

	return expressionFilled;
}

void MBigNumberExpression::generateExpression()
{
	this->generateExpression(EXPRESSION_OPERATORS);
}

void MBigNumberExpression::generateExpression(mstring allowedOperators)
{
	/*char* expressionTemplate = this->generateExpressionTemplate(allowedOperators);

	char* expression = this->generateExpressionFromTemplate(expressionTemplate);*/

	mstring expressionTemplate = this->generateExpressionTemplate(allowedOperators);

	mstring expression = this->generateExpressionFromTemplate(expressionTemplate);

	//Delete dynamic memory
	//delete[] expressionTemplate;

	//std::cout << "Expression: " << expression;

	//Finally, set the expression of the object to the new expression
	/*delete[] this->expression;
	this->expression = expression;
	this->capacity = strlen(expression) + 1;*/
	this->expression = expression;
}

mstring MBigNumberExpression::concatExpressionsWithOperator(mstring thisExpression, mstring otherExpression, mstring concatOperator) const
{
	mstring parenthesisOpening = "(";
	mstring parenthesisClosing = ")";

	//size_t newExpressionStringCapacity = thisExpression.getSize() + otherExpression.getSize() + concatOperator.getSize() + 5;
	/*char* newExpressionString = new char[newExpressionStringCapacity];
	newExpressionString[0] = '\0';*/
	mstring newExpressionString;

	/*strcat(newExpressionString, parenthesisOpening);
	strcat(newExpressionString, thisExpression);
	strcat(newExpressionString, parenthesisClosing);
	strcat(newExpressionString, concatOperator);
	strcat(newExpressionString, parenthesisOpening);
	strcat(newExpressionString, otherExpression);
	strcat(newExpressionString, parenthesisClosing);*/

	newExpressionString = parenthesisOpening + thisExpression + parenthesisClosing 
		+ concatOperator 
		+ parenthesisOpening + otherExpression + parenthesisClosing;

	return newExpressionString;
}

bool MBigNumberExpression::operator==(const MBigNumberExpression& other) const
{
	return this->evaluateExpression() == other.evaluateExpression();
}

bool MBigNumberExpression::operator!=(const MBigNumberExpression& other) const
{
	return !(*this == other);
}

bool MBigNumberExpression::operator<(const MBigNumberExpression& other) const
{
	return *this <= other && *this != other;
}

bool MBigNumberExpression::operator<=(const MBigNumberExpression& other) const
{
	return this->evaluateExpression() <= other.evaluateExpression();
}

bool MBigNumberExpression::operator>(const MBigNumberExpression& other) const
{
	return !(*this <= other);
}

bool MBigNumberExpression::operator>=(const MBigNumberExpression& other) const
{
	return !(*this < other);
}

MBigNumberExpression MBigNumberExpression::operator+(const MBigNumberExpression& other) const
{
	//char* newExpressionString = concatExpressionsWithOperator(this->getExpression(), other.getExpression(), "+");
	mstring newExpressionString = this->concatExpressionsWithOperator(this->getExpression(), other.getExpression(), "+");
	MBigNumberExpression newExpression(newExpressionString);

	//Delete dynamic memory
	//delete[] newExpressionString;

	return newExpression;
}

MBigNumberExpression& MBigNumberExpression::operator+=(const MBigNumberExpression& other)
{
	*this = *this + other;
	return *this;
}

MBigNumberExpression MBigNumberExpression::operator-(const MBigNumberExpression& other) const
{
	//char* newExpressionString = concatExpressionsWithOperator(this->getExpression(), other.getExpression(), "-");
	mstring newExpressionString = this->concatExpressionsWithOperator(this->getExpression(), other.getExpression(), "-");
	MBigNumberExpression newExpression(newExpressionString);

	//Delete dynamic memory
	//delete[] newExpressionString;

	return newExpression;
}

MBigNumberExpression& MBigNumberExpression::operator-=(const MBigNumberExpression& other)
{
	*this = *this - other;
	return *this;
}

MBigNumberExpression MBigNumberExpression::operator*(const MBigNumberExpression& other) const
{
	/*char* newExpressionString = concatExpressionsWithOperator(this->getExpression(), other.getExpression(), "*");*/
	mstring newExpressionString = this->concatExpressionsWithOperator(this->getExpression(), other.getExpression(), "*");
	MBigNumberExpression newExpression(newExpressionString);

	//Delete dynamic memory
	//delete[] newExpressionString;

	return newExpression;
}

MBigNumberExpression& MBigNumberExpression::operator*=(const MBigNumberExpression& other)
{
	*this = *this * other;
	return *this;
}

MBigNumberExpression MBigNumberExpression::operator/(const MBigNumberExpression& other) const
{
	//char* newExpressionString = concatExpressionsWithOperator(this->getExpression(), other.getExpression(), "/");
	mstring newExpressionString = this->concatExpressionsWithOperator(this->getExpression(), other.getExpression(), "/");
	MBigNumberExpression newExpression(newExpressionString);

	//Delete dynamic memory
	//delete[] newExpressionString;

	return newExpression;
}

MBigNumberExpression& MBigNumberExpression::operator/=(const MBigNumberExpression& other)
{
	*this = *this / other;
	return *this;
}

MBigNumberExpression MBigNumberExpression::operator%(const MBigNumberExpression& other) const
{
	//char* newExpressionString = concatExpressionsWithOperator(this->getExpression(), other.getExpression(), "%");
	mstring newExpressionString = this->concatExpressionsWithOperator(this->getExpression(), other.getExpression(), "%");
	MBigNumberExpression newExpression(newExpressionString);

	//Delete dynamic memory
	//delete[] newExpressionString;

	return newExpression;
}

MBigNumberExpression& MBigNumberExpression::operator%=(const MBigNumberExpression& other)
{
	*this = *this % other;
	return *this;
}

std::istream& operator>>(std::istream& is, MBigNumberExpression& expression)
{
	//Let's just agree that an expression larger than 10000 symbols cannot occur.
	char* textLine = new char[10000];
	is.getline(textLine, 10000);

	expression.setExpression(textLine);

	return is;
}

std::ostream& operator<<(std::ostream& os, const MBigNumberExpression& expression)
{
	os << "This is the expression: " << expression.getExpression() << std::endl;
	os << "And this is the answer: " << expression.evaluateExpression() << std::endl;

	return os;
}

std::ifstream& operator>>(std::ifstream& is, MBigNumberExpression& expression)
{
	//Let's just agree that an expression larger than 10000 symbols cannot occur.
	char* textLine = new char[10000];
	is.getline(textLine, 10000);

	expression.setExpression(textLine);

	return is;
}

std::ofstream& operator<<(std::ofstream& os, const MBigNumberExpression& expression)
{
	mstring expressionString = expression.getExpression();
	//mstring equals = "=";
	MBigNumber resultFromExpression = expression.evaluateExpression();
	mstring answer = resultFromExpression.getNumber();

	/*size_t textLineCapacity = strlen(expressionString) + 1 + strlen(answer) + 1;
	char* textLine = new char[textLineCapacity];
	textLine[0] = '\0';

	strcat(textLine, expressionString);
	strcat(textLine, equals);
	strcat(textLine, answer);
	textLine[textLineCapacity - 1] = '\n';*/
	mstring textLine = expressionString + "=" + answer;

	os << textLine << "\n";

	//Delete dynamic memory
	//delete[] textLine;
	//delete[] answer;

	return os;
}
