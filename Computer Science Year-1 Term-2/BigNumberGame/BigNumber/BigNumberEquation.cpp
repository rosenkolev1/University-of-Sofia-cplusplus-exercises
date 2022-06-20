#include "BigNumberEquation.h"
#include "../Project.StringManipulation/MStringManip.h"

//Exception messages CONSTANTS
const mstring BigNumberEquation::EQUATION_INVALID_EXCEPTION = "Invalid Equation!";
const mstring BigNumberEquation::EQUATION__SOLVE_TOOCOMPLEX_EXCEPTION = "Equation is too complex for me to solve";
const mstring BigNumberEquation::EQUATION__SOLVE_TIEDTODIVISION_EXCEPTION = "The unknown is tied to division, so I can't solve this equation, sorry!";
const mstring BigNumberEquation::EQUATION__SOLVE_NOTWHOLE_EXCEPTION = "Not whole number solution";
const mstring BigNumberEquation::EQUATION__SOLVE_EVERYANSWER_EXCEPTION = "Every x is an answer to the equation";
const mstring BigNumberEquation::EQUATION__SOLVE_NOANSWER_EXCEPTION = "No answer for this equation";
const mstring BigNumberEquation::EQUATION_OPERATORS = "+-*/";

//0-49
int BigNumberEquation::generateCountOfX(int seed)
{
	if (seed > 47) return 3;
	else if (seed > 40) return 2;
	else return 1;
}

BigNumberEquation::BigNumberEquation()
{
	this->equation = "x=0";
}

BigNumberEquation::BigNumberEquation(mstring equation)
{
	if (!isValidEquation(equation)) throw "Invalid equation!";

	this->equation = equation;
}

bool BigNumberEquation::isValidEquation(mstring equation) const
{
	//Replace all of the whitespaces
	equation = MStringManip::replaceAll(equation, " ", "");

	//Check if the equation contains exactly 1 equals symbol
	bool isValidEquation = MStringManip::countOf(equation, "=");
	if (isValidEquation == false) return false;

	//Check if the equation contains percent operator, which is invalid for equations.
	size_t countOfPercents = MStringManip::countOf(equation, "%");
	if (countOfPercents > 0) return false;

	//Check if the equation contains at least one unknown. 
	//If it doesn't, then solve the left and right sides and compare their answer. If they are equal, then the equation is valid. Otherwise, it's not
	size_t countOfUnknowns = MStringManip::countOf(equation, "x");

	//Split by equals and decided if the sides are invalid
	size_t countOfSides = 0;
	mstring* sides = MStringManip::splitString(equation, "=", countOfSides);

	if (countOfUnknowns == 0)
	{
		BigNumberExpression leftSide(sides[0]);
		BigNumberExpression rightSide(sides[1]);

		try
		{
			bool result = leftSide.evaluateExpression() == rightSide.evaluateExpression();

			//Deallocate Dynamic Memory
			delete[] sides;

			return result;
		}
		//If we get here, then the evaluation of one of the expressions failed because of division by /. So return false
		catch (mstring e)
		{
			if (BigNumberExpression::EXPRESSION_DIVIDEBYZERO_EXCEPTION == e)
			{
				//Deallocate Dynamic Memory
				delete[] sides;

				return false;
			}
		}
	}
	else
	{
		for (size_t i = 0; i < 2; i++)
		{
			mstring side = sides[i];

			//Check if side is valid by replacing the unknowns with -1 and checking if the expression is valid

			//Replace the unknowns with -1
			mstring sideWithoutUnknowns = MStringManip::replaceAll(side, "x", "-1");

			//Check if expression is valid
			BigNumberExpression sideExpression;
			bool sideIsValid = sideExpression.expressionIsValid(sideWithoutUnknowns);

			if (!sideIsValid)
			{
				//Deallocate Dynamic Memory
				delete[] sides;

				return false;
			}
		}
	}

	//Deallocate Dynamic Memory
	delete[] sides;

	//If we get to here, then the equation passed all tests and is true
	return true;
}

bool BigNumberEquation::isValidEquation() const
{
	return this->isValidEquation(this->equation);
}

BigNumber BigNumberEquation::solveEquation(mstring equation)
{
	//Remove the whitespaces
	equation = MStringManip::replaceAll(equation, " ", "");

	//Check if the equation is valid
	if (!isValidEquation(equation))
	{
		throw EQUATION_INVALID_EXCEPTION;
	}

	//Check if the equation has only one unknown. If it doesn't, then throw an exception because I am not that smart to want to code that looooool...
	size_t countOfUnknowns = MStringManip::countOf(equation, "x");
	if (countOfUnknowns > 1)
	{
		throw EQUATION__SOLVE_TOOCOMPLEX_EXCEPTION;
	}
	//If we get to here, then there are no unknowns in the equation and it is always correct because the left and right side expressions are equal
	else if (countOfUnknowns < 1)
	{
		throw EQUATION__SOLVE_EVERYANSWER_EXCEPTION;
	}

	//Split the equation by the unknown side and the known side
	size_t sidesCount = 0;
	mstring* sides = MStringManip::splitString(equation, "=", sidesCount);
	mstring unknownSide = sides[0];
	mstring knownSide = sides[1];

	//If the right side is the one with the unknown, then swap the sides
	if (MStringManip::stringContains(knownSide, "x"))
	{
		mstring copy = unknownSide;
		unknownSide = knownSide;
		knownSide = copy;
	}

	size_t bracketedExpressionsWithUnknownIndex = 0;
	mstring* bracketedExpressionsWithUnknown = new mstring [MStringManip::countOf(unknownSide, "(")];

	int indexOfUnknown = 0;

	while (true)
	{
		//Update the index of unknown
		indexOfUnknown = MStringManip::findIndex(unknownSide, "x");

		//Check if the unknown is inside brackets
		int openingBracketBeforeUnknown = -1;
		int closingBracketAfterUnknown = -1;
		int unclosedBrackets = 0;
		bool isInsideBrackets = false;
		for (int i = indexOfUnknown - 1; i >= 0; i--)
		{
			if (unknownSide[i] == ')') unclosedBrackets++;
			else if (unknownSide[i] == '(')
			{
				unclosedBrackets--;
				if (unclosedBrackets < 0)
				{
					openingBracketBeforeUnknown = i;
					isInsideBrackets = true;
					break;
				}
			}
		}

		//If this is true, then the unknown isn't in brackets anymore
		if (!isInsideBrackets) break;
		unclosedBrackets = 1;
		//Get the index of the closing bracket
		for (size_t i = indexOfUnknown + 1; i < unknownSide.getSize(); i++)
		{
			if (unknownSide[i] == '(') unclosedBrackets++;
			else if (unknownSide[i] == ')')
			{
				unclosedBrackets--;
				if (unclosedBrackets == 0)
				{
					closingBracketAfterUnknown = i;
					break;
				}
			}
		}
		mstring storedExpression = MStringManip::getFrom(unknownSide, openingBracketBeforeUnknown, closingBracketAfterUnknown);

		unknownSide = MStringManip::replaceFirst(unknownSide, storedExpression, "x");

		bracketedExpressionsWithUnknown[bracketedExpressionsWithUnknownIndex++] = storedExpression;
	}

	//Now check if the unknown is tied to a division
	while (true)
	{
		//Update the index of unknown
		indexOfUnknown = MStringManip::findIndex(unknownSide, "x");

		//Check if the unknown is tied to a division to the left
		int indexOfLastLeftDivide = -1;
		int indexOfLastLeftDivideMinus = -1;
		int indexOfLastLeftDividePlus = -1;
		if (indexOfUnknown > 0)
		{
			indexOfLastLeftDivide = MStringManip::findIndexLast(unknownSide, "/", 0, indexOfUnknown - 1);
			indexOfLastLeftDivideMinus = MStringManip::findIndexLast(unknownSide, "/-", 0, indexOfUnknown - 1);
			indexOfLastLeftDividePlus = MStringManip::findIndexLast(unknownSide, "/+", 0, indexOfUnknown - 1);
		}

		bool tiedToDivision = false;

		if (indexOfLastLeftDivide != -1 && indexOfLastLeftDivide == indexOfUnknown - 1) tiedToDivision = true;
		else if (indexOfLastLeftDivideMinus != -1 && indexOfLastLeftDivideMinus == indexOfUnknown - 2) tiedToDivision = true;
		else if (indexOfLastLeftDividePlus != -1 && indexOfLastLeftDividePlus == indexOfUnknown - 2) tiedToDivision = true;

		//Check if the unknown is tied to a division from the right
		bool divideInBrackets = false;
		int bracketsNested = 0;
		for (size_t i = indexOfUnknown + 1; i < unknownSide.getSize(); i++)
		{
			if (unknownSide[i] == '(') bracketsNested++;
			else if (unknownSide[i] == ')') bracketsNested--;
			else if (unknownSide[i] == '-' || unknownSide[i] == '+' && bracketsNested == 0) break;
			else if (unknownSide[i] == '/' && bracketsNested == 0)
			{
				tiedToDivision = true;
				break;
			}
		}

		if (tiedToDivision)
		{
			//Delete dynamic memory
			delete[] sides;
			delete[] bracketedExpressionsWithUnknown;

			throw EQUATION__SOLVE_TIEDTODIVISION_EXCEPTION;
		}
		//In this case, the unknown isn't tied to any division
		else if (!tiedToDivision && bracketedExpressionsWithUnknownIndex < 1) break;
		//In this case, the replace the unknown with the next stored bracketed expression
		else
		{
			unknownSide = MStringManip::replaceFirst(unknownSide, "x", bracketedExpressionsWithUnknown[--bracketedExpressionsWithUnknownIndex]);
		}
	}

	//If we get to here, then there is no division tied to the unknown, so we can solve the equation easily
	//Calculate the linear increase between increasing the value of x by 1 and use that to calculate whether or not the equation has a solution
	BigNumber testValue1(1);
	BigNumber testValue2(2);
	BigNumberExpression knownSideExpression(knownSide);

	mstring expressionTestValue1String = MStringManip::replaceFirst(unknownSide, "x", testValue1.getNumberRaw());
	BigNumberExpression expressionTestValue1(expressionTestValue1String);

	mstring expressionTestValue2String = MStringManip::replaceFirst(unknownSide, "x", testValue2.getNumberRaw());
	BigNumberExpression expressionTestValue2(expressionTestValue2String);

	BigNumber testValue1Result = (expressionTestValue1 - knownSideExpression).evaluateExpression();
	if (testValue1Result.getSign() == -1) testValue1Result *= -1;
	BigNumber testValue2Result = (expressionTestValue2 - knownSideExpression).evaluateExpression();
	if (testValue2Result.getSign() == -1) testValue2Result *= -1;

	BigNumber deltaResult = testValue2Result - testValue1Result;

	//Delete dynamic memory
	delete[] sides;
	delete[] bracketedExpressionsWithUnknown;

	//If this is true, then that means that by increasing x by 1, we increase the result of the expression when substituting with x.
	//However, we want the opposite to happen, so we divide the testValue1Result by deltaResult to see how many times we need to lower x by 1 from 1 before we get the equation to 0
	if (deltaResult.getSign() != 0)
	{
		BigNumber decreaseOfX = testValue1Result / deltaResult;

		BigNumber decreaseOfXLeftover = testValue1Result % deltaResult;

		//If this is true, then the equation doesn't have a solution that is a whole number;
		if (decreaseOfXLeftover.getSign() != 0)
		{
			throw EQUATION__SOLVE_NOTWHOLE_EXCEPTION;
		}
		//If we get here, then 1 - decreaseOfX should be the answer to the equation, unless in between 1 and 1-decreaseOfX there is a value where the expression breaks because of division by 0
		else
		{
			BigNumber potentialAnswer = (decreaseOfX - 1) * -1;

			//Test the potential answer to see if it holds true
			mstring expressionPotenialAnswerString = MStringManip::replaceFirst(unknownSide, "x", potentialAnswer.getNumberRaw());
			BigNumberExpression expressionPotenialAnswer(expressionPotenialAnswerString);

			//By presumption, this should not throw an error for dividing by 0, because I made it so that the unknown isn't tied to a division in the first place
			BigNumber potentialAnswerResult = (expressionPotenialAnswer - knownSideExpression).evaluateExpression();

			//In this case, we got the correct answer
			if (potentialAnswerResult.getSign() == 0)
			{
				return potentialAnswer;
			}
			//In this case, there is no correct answer to the equation that is a whole number
			else
			{
				throw EQUATION__SOLVE_NOTWHOLE_EXCEPTION;
			}
		}
	}
	else
	{
		//In this case, every x that is a whole number is an answer to the equation
		if (testValue1Result.getSign() == 0)
		{
			throw EQUATION__SOLVE_EVERYANSWER_EXCEPTION;
		}
		else
		{
			throw EQUATION__SOLVE_NOANSWER_EXCEPTION;
		}
	}

	throw "This is some error state loool";
}

BigNumber BigNumberEquation::solveEquation()
{
	return this->solveEquation(this->equation);
}

mstring BigNumberEquation::generateFromTemplate(mstring expressionTemplate, size_t maxUnknown)
{
	mstring expressionFilled = expressionTemplate;

	size_t countOfNumbers = MStringManip::countOf(expressionFilled, "x");

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
	for (size_t i = 0; i < expressionFilled.getSize(); i++)
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
				int signOfX = generateSign();

				//If signOfX is 0, then reroll until it isn't
				while (true)
				{
					if (signOfX > 0)
					{
						expressionFilled = MStringManip::replaceFrom(expressionFilled, "U", i, i);
						break;
					}
					else if (signOfX < 0)
					{
						expressionFilled = MStringManip::replaceFrom(expressionFilled, "-U", i, i);
						break;
					}
					else signOfX = signOfX = generateSign();
				}
			}
		}
	}

	//Replace the x in the expression template with numbers, except for the targeted x numbers, which are now U or -U
	while (MStringManip::stringContains(expressionFilled, "x"))
	{
		//Generate the sign of the number
		BigNumber bigNumber = BigNumber();
		int signOfNumber = generateSign();
		if (signOfNumber != 0)
		{
			//Randomly generate a number
			size_t digitsCount = generateDigitsCount();
			size_t capacity = digitsCount + 1;
			size_t digitsIndex = 0;

			if (signOfNumber == -1) capacity++;

			mstring numberString;

			if (signOfNumber == -1) numberString += '-';

			numberString  += rand() % 9 + 1 + '0';
			for (size_t i = numberString.getSize(); i < digitsCount; i++)
			{
				numberString += (rand() % 10) + '0';
			}

			bigNumber = BigNumber(numberString);
		}

		//Replace the bigNumber in the expressionTemplate
		expressionFilled = MStringManip::replaceFirst(expressionFilled, "x", bigNumber.getNumberRaw());
	}

	//Replace the U back with x because it looks better
	expressionFilled = MStringManip::replaceAll(expressionFilled, "U", "x");

	//Replace all the instances of +-x,-+x, --x inside the string. Otherwise, when you try to replace x with a negative number, it will be an invalid expression!
	expressionFilled = MStringManip::replaceAll(expressionFilled, "+-x", "-x");
	expressionFilled = MStringManip::replaceAll(expressionFilled, "-+x", "-x");
	expressionFilled = MStringManip::replaceAll(expressionFilled, "--x", "+x");

	//Delete dynamic memory
	delete[] positionsX;

	return expressionFilled;
}

void BigNumberEquation::generateEquation(mstring leftSideAllowedOperators, mstring rightSideAllowedOperators, size_t maxUnknownPerSide, size_t totalUnknown)
{
	//If maxUnknownPerSide > totalUnknown, throw an error
	if (maxUnknownPerSide > totalUnknown) throw "The unknown counts are all wrong";

	//Generate the left expression template
	BigNumberExpression expression;

	mstring leftSideTemplate = expression.generateExpressionTemplate(leftSideAllowedOperators);
	mstring rightSideTemplate = expression.generateExpressionTemplate(rightSideAllowedOperators);

	//Replace the x in the templates with numbers, except for the targeted x's. Conform to the totalUnknown and maxUnknownPerSide values
	mstring leftSideFilled = generateFromTemplate(leftSideTemplate, maxUnknownPerSide);
	size_t countOfUnknownInLeftSide = MStringManip::countOf(leftSideFilled, "x");
	mstring rightSideFilled = generateFromTemplate(rightSideTemplate, totalUnknown - countOfUnknownInLeftSide);

	mstring equation = leftSideFilled + "=" + rightSideFilled;

	this->equation = equation;
}

void BigNumberEquation::generateEquation(size_t maxUnknownPerSide, size_t totalUnknown)
{
	generateEquation(EQUATION_OPERATORS, EQUATION_OPERATORS, maxUnknownPerSide, totalUnknown);
}

mstring BigNumberEquation::getEquation() const
{
	return this->equation;
}

void BigNumberEquation::setEquation(mstring equation)
{
	if (!isValidEquation(equation)) throw "The expression that you are trying to set is invalid";

	size_t capacityOfNewEquation = equation.getSize() + 1;

	//Remove all the whitespaces
	this->equation = MStringManip::replaceAll(equation, " ", "");
}

mstring BigNumberEquation::getRightExpression() const
{
	size_t arraySize = 0;
	mstring* expressions = MStringManip::splitString(this->getEquation(), "=", arraySize);
	mstring rightExpression = expressions[1];

	//Delete dynamic memory
	delete[] expressions;

	return rightExpression;
}

mstring BigNumberEquation::getLeftExpression() const
{
	size_t arraySize = 0;
	mstring* expressions = MStringManip::splitString(this->getEquation(), "=", arraySize);
	mstring leftExpression = expressions[0];

	//Delete dynamic memory
	delete[] expressions;

	return leftExpression;
}

mstring BigNumberEquation::getEquationTemplate(mstring equation) const
{
	//Check if the equation is valid. If it isn't, throw an exception 
	if (this->isValidEquation(equation) == false) throw "This equation isn't valid";

	//Remove all the whitespaces
	equation = MStringManip::replaceAll(equation, " ", "");

	size_t sidesCount = 0;
	mstring* sides = MStringManip::splitString(equation, "=", sidesCount);

	for (size_t i = 0; i < 2; i++)
	{
		mstring newSide = sides[i];

		//Replace all the *-x, +-x, --x, /-x with *N, +N, -N, /N
		newSide = MStringManip::replaceAll(newSide, "*-x", "*N");
		newSide = MStringManip::replaceAll(newSide, "+-x", "+N");
		newSide = MStringManip::replaceAll(newSide, "--x", "-N");
		newSide = MStringManip::replaceAll(newSide, "/+x", "/N");

		//Replace all the x's with U's
		newSide = MStringManip::replaceAll(newSide, "x", "U");

		//Replace all the -,+ operators where the -,+ belongs to the number instead of being an operator
		newSide = MStringManip::replaceAll(newSide, "+-", "+");
		newSide = MStringManip::replaceAll(newSide, "--", "-");
		newSide = MStringManip::replaceAll(newSide, "-+", "-");
		newSide = MStringManip::replaceAll(newSide, "*+", "*");
		newSide = MStringManip::replaceAll(newSide, "/+", "/");
		newSide = MStringManip::replaceAll(newSide, "%+", "%");
		newSide = MStringManip::replaceAll(newSide, "*-", "*");
		newSide = MStringManip::replaceAll(newSide, "/-", "/");
		newSide = MStringManip::replaceAll(newSide, "%-", "%");

		//Check if the first char of the expression is + or - and if the first number is known. If this is true, then remove the sign entirely
		if (newSide[0] == '-' || newSide[0] == '+' && newSide[1] != 'U' && newSide[1] != 'N')
		{
			newSide = MStringManip::replaceFrom(newSide, "", 0, 0);
		}

		//Replace the numbers with x's
		newSide = replaceNumbers(newSide, "x");

		//Return the side template to the sides array
		sides[i] = newSide;
	}

	// Concat the sides array into the equation
	mstring equationTemplate = sides[0] + "=" + sides[1];

	//Delete dynamic memory
	delete[] sides;

	return equationTemplate;
}

mstring BigNumberEquation::getEquationTemplate() const
{
	return this->getEquationTemplate(this->equation);
}

std::istream& operator>>(std::istream& is, BigNumberEquation& equation)
{
	//Let's just agree that an equation larger than 10000 symbols cannot occur.
	char* text = new char[10000];
	is.getline(text, 10000);

	mstring textLine = text;

	equation.setEquation(textLine);

	//Deallocate dynamic memory
	delete[] text;

	return is;
}

std::ostream& operator<<(std::ostream& os, BigNumberEquation& equation)
{
	os << equation.getEquation() << "\n";
	os << "The answer to the equation: ";
	try
	{
		os << equation.solveEquation();
	}
	catch (mstring e)
	{
		os << e;
	}
	return os;
}

std::ifstream& operator>>(std::ifstream& is, BigNumberEquation& equation)
{
	//Let's just agree that an expression larger than 10000 symbols cannot occur.
	char* text = new char[10000];
	is.getline(text, 10000);

	mstring textLine = text;

	equation.setEquation(textLine);

	delete[] text;

	return is;
}

std::ofstream& operator<<(std::ofstream& os, BigNumberEquation& equation)
{
	os << equation.getEquation() << "\n";
	os << "The answer to the equation: ";
	try
	{
		os << equation.solveEquation();
	}
	catch (mstring e)
	{
		os << e;
	}
	return os;
}
