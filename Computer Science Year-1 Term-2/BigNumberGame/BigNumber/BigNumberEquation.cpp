#include "BigNumberEquation.h"
#include "../Project.StringManipulation/StringManip.h"

void BigNumberEquation::copy(const BigNumberEquation& other)
{
	this->capacity = other.capacity;
	delete[] this->equation;
	this->equation = new char[this->capacity];
	strcpy(this->equation, other.getEquation());
}

//0-49
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
	//Decided if we are checking the object caller's own equation
	if (equation == nullptr)
	{
		equation = this->getEquation();		
	}

	//Replace all of the whitespaces
	char* newEquation = StringManip::replaceAll(equation, " ", "");

	//Check if the equation contains exactly 1 equals symbol
	bool isValidEquation = StringManip::countOf(newEquation, "=");
	if (isValidEquation == false) return false;

	//Check if the equation contains percent operator, which is invalid for equations.
	size_t countOfPercents = StringManip::countOf(newEquation, "%");
	if (countOfPercents > 0) return false;

	//Check if the equation contains at least one unknown. 
	//If it doesn't, then solve the left and right sides and compare their answer. If they are equal, then the equation is valid. Otherwise, it's not
	size_t countOfUnknowns = StringManip::countOf(newEquation, "x");

	//Split by equals and decided if the sides are invalid
	size_t countOfSides = 0;
	char** sides = StringManip::splitString(newEquation, "=", countOfSides);

	if (countOfUnknowns == 0)
	{
		BigNumberExpression leftSide(sides[0]);
		BigNumberExpression rightSide(sides[1]);

		try
		{
			return leftSide.evaluateExpression() == rightSide.evaluateExpression();
		}
		//If we get here, then the evaluation of one of the expressions failed because of division by /. So return false
		catch (...)
		{
			return false;
		}
	}
	else
	{
		for (size_t i = 0; i < 2; i++)
		{
			char* side = sides[i];

			//Check if side is valid by replacing the unknowns with -1 and checking if the expression is valid

			//Replace the unknowns with -1
			char* sideWithoutUnknowns = StringManip::replaceAll(side, "x", "-1");

			//Check if expression is valid
			BigNumberExpression sideExpression;
			bool sideIsValid = sideExpression.expressionIsValid(sideWithoutUnknowns);

			if (!sideIsValid)
			{
				//Delete dynamic memory
				delete[] sideWithoutUnknowns;
				StringManip::deleteArrayOfStrings(sides, 2);

				return false;
			}

			//Delete dynamic memory
			delete[] sideWithoutUnknowns;
		}
	}
	
	//Delete dynamic memory
	StringManip::deleteArrayOfStrings(sides, 2);

	//If we get to here, then the equation passed all tests and is true
	return true;
}

BigNumber& BigNumberEquation::solveEquation(const char* equation)
{
	// TODO: insert return statement here
	BigNumber DEBUG(10);
	return DEBUG;
}

char* BigNumberEquation::generateFromTemplate(const char* expressionTemplate, size_t maxUnknown)
{
	char* expressionFilled = new char[strlen(expressionTemplate) + 1];
	strcpy(expressionFilled, expressionTemplate);

	size_t countOfNumbers = StringManip::countOf(expressionFilled, "x");

	int countOfX = -1;
	if (maxUnknown > 0)
	{
		while (countOfX < 0 || countOfX > countOfNumbers || countOfX > maxUnknown)
		{
			countOfX = generateCountOfX(rand() % 50);
		}
	}
	else countOfX = 0;

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
			position = rand() % countOfNumbers + 1;

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
				//Decide randomly whether or not the x is going to have a - in front of it
				int signOfX = generateSign(rand() % 15);

				//If signOfX is 0, then reroll until it isn't
				while (true)
				{
					if (signOfX > 0)
					{
						char* expressionFilledCopy = StringManip::replaceFrom(expressionFilled, "U", i, i);
						delete[] expressionFilled;
						expressionFilled = expressionFilledCopy;
						break;
					}
					else if (signOfX < 0)
					{
						char* expressionFilledCopy = StringManip::replaceFrom(expressionFilled, "-U", i, i);
						delete[] expressionFilled;
						expressionFilled = expressionFilledCopy;
						break;
					}
					else signOfX = signOfX = generateSign(rand() % 15);
				}
			}
		}	
	}

	//Replace the x in the expression template with numbers, except for the targeted x numbers, which are now U or -U
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

	//Replace all the instances of +-x,-+x, --x inside the string. Otherwise, when you try to replace x with a negative number, it will be an invalid expression!
	char* expressionOne = StringManip::replaceAll(expressionFilled, "+-x", "-x");
	char* expressionTwo = StringManip::replaceAll(expressionOne, "-+x", "-x");
	char* expressionThree = StringManip::replaceAll(expressionTwo, "--x", "+x");

	delete[] expressionFilled;
	expressionFilled = expressionThree;

	//Delete dynamic memory
	delete[] expressionTwo;
	delete[] expressionOne;

	return expressionFilled;
}

void BigNumberEquation::generateEquation(size_t maxUnknownPerSide, size_t totalUnknown)
{
	//If maxUnknownPerSide > totalUnknown, throw an error
	if (maxUnknownPerSide > totalUnknown) throw "The unknown counts are all wrong";

	//Generate the left expression template
	BigNumberExpression expression;

	char* leftSideTemplate = expression.generateExpressionTemplate(EQUATION_OPERATORS);
	char* rightSideTemplate = expression.generateExpressionTemplate(EQUATION_OPERATORS);

	//Replace the x in the templates with numbers, except for the targeted x's. Conform to the totalUnknown and maxUnknownPerSide values
	char* leftSideFilled = generateFromTemplate(leftSideTemplate, maxUnknownPerSide);
	size_t countOfUnknownInLeftSide = StringManip::countOf(leftSideFilled, "x");
	char* rightSideFilled = generateFromTemplate(rightSideTemplate, totalUnknown - countOfUnknownInLeftSide);

	//TODO: get the answer to the equation

	char* equation = new char[strlen(leftSideFilled) + strlen(rightSideFilled) + 2];
	equation[0] = '\0';
	strcat(equation, leftSideFilled);
	strcat(equation, "=");
	strcat(equation, rightSideFilled);

	//Delete dynamic memory
	delete[] rightSideFilled;
	delete[] leftSideFilled;
	delete[] rightSideTemplate;
	delete[] leftSideTemplate;

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

void BigNumberEquation::setEquation(const char* equation)
{
	if (!isValidEquation(equation)) throw "The expression that you are trying to set is invalid";

	//Remove all the whitespaces
	char* equationCopy = StringManip::replaceAll(equation, " ", "");

	size_t capacityOfNewEquation = strlen(equationCopy) + 1;
	//Resize expression if needed
	if (capacityOfNewEquation > this->capacity)
	{
		this->capacity = capacityOfNewEquation;
		delete[] this->equation;
		this->equation = new char[this->capacity];
	}
	strcpy(this->equation, equationCopy);

	//Delete dynamic memory
	delete[] equationCopy;
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

char* BigNumberEquation::getEquationTemplate(const char* equation) const
{
	if (equation == nullptr) equation = this->getEquation();

	//Check if the equation is valid. If it isn't, throw an exception 
	if (this->isValidEquation(equation) == false) throw "This equation isn't valid";
	char* equationCopy = new char[strlen(equation) + 1];

	strcpy(equationCopy, equation);

	//Remove all the whitespaces
	char* equationCopyCopy = StringManip::replaceAll(equationCopy, " ", "");
	delete[] equationCopy;
	equationCopy = equationCopyCopy;

	size_t sidesCount = 0;
	char** sides = StringManip::splitString(equationCopy, "=", sidesCount);

	for (size_t i = 0; i < 2; i++)
	{
		char* newSide = new char[strlen(sides[i]) + 1];
		strcpy(newSide, sides[i]);

		//Replace all the *-x, +-x, --x, /-x with *N, +N, -N, /N
		char* side1 = StringManip::replaceAll(newSide, "*-x", "*N");
		char* side2 = StringManip::replaceAll(side1, "+-x", "+N");
		char* side3 = StringManip::replaceAll(side2, "--x", "-N");
		char* side4 = StringManip::replaceAll(side3, "/+x", "/N");

		//Replace all the x's with U's
		char* side5 = StringManip::replaceAll(side4, "x", "U");

		delete[] newSide;
		newSide = side5;

		//Delete dynamic memory
		delete[] side4;
		delete[] side3;
		delete[] side2;
		delete[] side1;

		//Replace all the -,+ operators where the -,+ belongs to the number instead of being an operator
		side1 = StringManip::replaceAll(newSide, "+-", "+");
		side2 = StringManip::replaceAll(side1, "--", "-");
		side3 = StringManip::replaceAll(side2, "-+", "-");
		side4 = StringManip::replaceAll(side3, "*+", "*");
		side5 = StringManip::replaceAll(side4, "/+", "/");
		char* side6 = StringManip::replaceAll(side5, "%+", "%");
		char* side7 = StringManip::replaceAll(side6, "*-", "*");
		char* side8 = StringManip::replaceAll(side7, "/-", "/");
		char* side9 = StringManip::replaceAll(side8, "%-", "%");

		delete[] newSide;
		newSide = side9;

		//Delete dynamic memory
		delete[] side8;
		delete[] side7;
		delete[] side6;
		delete[] side5;
		delete[] side4;
		delete[] side3;
		delete[] side2;
		delete[] side1;

		//Check if the first char of the expression is + or - and if the first number is known. If this is true, then remove the sign entirely
		if (newSide[0] == '-' || newSide[0] == '+' && newSide[1] != 'U' && newSide[1] != 'N')
		{
			const char* sideCopy = newSide;
			newSide = StringManip::replaceFrom(newSide, "", 0, 0);
			delete[] sideCopy;
		}

		//Replace the numbers with x's
		char* newSideCopy = replaceNumbers(newSide, "x");
		delete[] newSide;
		newSide = newSideCopy;

		//Return the side template to the sides array
		delete[] sides[i];
		sides[i] = newSide;
	}

	// Concat the sides array into the equation
	char* equationTemplate = new char[strlen(sides[0]) + strlen(sides[1]) + 2];
	equationTemplate[0] = '\0';
	strcat(equationTemplate, sides[0]);
	strcat(equationTemplate, "=");
	strcat(equationTemplate, sides[1]);

	//Delete dynamic memory
	StringManip::deleteArrayOfStrings(sides, 2);

	return equationTemplate;
}

std::istream& operator>>(std::istream& is, BigNumberEquation& equation)
{
	//Let's just agree that an equation larger than 10000 symbols cannot occur.
	char* textLine = new char[10000];
	is.getline(textLine, 10000);

	equation.setEquation(textLine);

	return is;
}

std::ifstream& operator>>(std::ifstream& is, BigNumberEquation& equation)
{
	//Let's just agree that an expression larger than 10000 symbols cannot occur.
	char* textLine = new char[10000];
	is.getline(textLine, 10000);

	equation.setEquation(textLine);

	return is;
}
