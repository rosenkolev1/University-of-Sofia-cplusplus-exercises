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

void BigNumberEquation::movePlusAndMinus(char*& unknownSide, char*& knownSide, bool leftOfUnknown, size_t indexOfUnknown)
{
	//Move everything that is 'not connected' to the unknown via *, /, *-, /- to the right hand side with the opposite operator
	//Left operator is the leftmost operator to the left of the unknown. leftExpressionEnd is the index of the end of the left expression
	char lastOperator = '\0';
	int expressionEnd = -1;
	//0x013c2700 0x013c2730
	//If we are looking to the left of unknown, then search the string to the left
	if (leftOfUnknown)
	{
		for (int i = indexOfUnknown - 1; i >= 0; i--)
		{
			char symbol = unknownSide[i];
			//Checks if the left operator has been set, and if it has, then get the equation to the left of that operator
			if (lastOperator == '\0' || lastOperator == '/' || lastOperator == '*')
			{
				if (StringManip::stringContains(EQUATION_OPERATORS, symbol))
				{
					lastOperator = symbol;
				}
			}
			else if ((lastOperator == '-' || lastOperator == '+') && isdigit(symbol))
			{
				expressionEnd = i;
				break;
			}
			else if ((lastOperator == '-' || lastOperator == '+') && (symbol == '*' || symbol == '/'))
			{
				lastOperator = symbol;
			}
		}
	}
	//If we are looking to the right of unknown, then search the string to the right
	else
	{
		for (int i = indexOfUnknown + 1; i < strlen(unknownSide); i++)
		{
			char symbol = unknownSide[i];

			if ((symbol == '+' || symbol == '-') && (isdigit(unknownSide[i - 1]) || i - 1 == indexOfUnknown))
			{
				expressionEnd = i;
				break;
			}
		}
	}

	//If the expression doesn't exist, then don't do anything
	if (expressionEnd == -1) return;

	//Copy expression
	char* expressionString = nullptr;
	if (leftOfUnknown)
	{
		expressionString = new char[expressionEnd + 2];
		expressionString[expressionEnd + 1] = '\0';
		strncpy(expressionString, unknownSide, expressionEnd + 1);
		/*for (size_t i = 0; i < expressionEnd + 1; i++)
		{
			expressionString[i] = unknownSide[i];
		}*/
	}
	else
	{
		expressionString = StringManip::replaceFrom(unknownSide, "", 0, expressionEnd - 1);
		/*expressionString = new char[strlen(unknownSide) - expressionEnd];
		expressionString[strlen(unknownSide) - expressionEnd - 1] = '\0';
		for (size_t i = expressionEnd; i < strlen(unknownSide); i++)
		{
			expressionString[i - expressionEnd] = unknownSide[i];
		}*/

		//Check if the expression string starts with +-, -+ or --. If it does, then replace those with the appropriate single operator
		//Otherwise, you can get an error when you try to transfer the expression to the other side with a -
		/*if (StringManip::stringStartsWith(expressionString, "+-") || StringManip::stringStartsWith(expressionString, "-+"))
		{
			char* expressionStringCopy = StringManip::replaceFrom(expressionString, "-", 0, 1);
			delete[] expressionString;
			expressionString = expressionStringCopy;
		}
		else if (StringManip::stringStartsWith(expressionString, "--"))
		{
			char* expressionStringCopy = StringManip::replaceFrom(expressionString, "+", 0, 1);
			delete[] expressionString;
			expressionString = expressionStringCopy;
		}*/
	}

	BigNumberExpression expression(expressionString);

	//This is the expression of the knownSide
	BigNumberExpression knownSideExpression(knownSide);

	//Minus the expression from the knownSideExpression
	BigNumberExpression newKnownSideExpression = knownSideExpression - expression;

	//Set the new unknown and known sides
	size_t newUnknownSideCapacity = strlen(unknownSide) - strlen(expressionString) + 1;
	char* newUnknownSide = new char[newUnknownSideCapacity];
	newUnknownSide[newUnknownSideCapacity - 1] = '\0';
	
	if (leftOfUnknown)
	{
		delete[] newUnknownSide;
		newUnknownSide = StringManip::replaceFrom(unknownSide, "", 0, expressionEnd);

		/*for (size_t i = expressionEnd + 1; i < strlen(unknownSide); i++)
		{
			newUnknownSide[i - expressionEnd - 1] = unknownSide[i];
		}*/
	}
	else
	{
		delete[] newUnknownSide;
		newUnknownSide = StringManip::replaceFrom(unknownSide, "", expressionEnd);
		/*for (size_t i = indexOfUnknown; i < expressionEnd; i++)
		{
			newUnknownSide[i - indexOfUnknown] = unknownSide[i];
		}*/
	}

	//Delete dynamic memory
	delete[] expressionString;

	//Replace with the new unknownSide and knownSide
	delete[] unknownSide;
	unknownSide = newUnknownSide;
	delete[] knownSide;
	knownSide = new char[strlen(newKnownSideExpression.getExpression()) + 1];
	strcpy(knownSide, newKnownSideExpression.getExpression());
}

void BigNumberEquation::moveMultiplyAndDivide(char*& unknownSide, char*& knownSide, bool leftOfUnknown, size_t indexOfUnknown)
{
	int indexOfMultiply = -1;
	int indexOfDivide = -1;

	if (leftOfUnknown && indexOfUnknown > 0)
	{
		indexOfMultiply = StringManip::findIndex(unknownSide, "*", 0, indexOfUnknown - 1);
		indexOfDivide = StringManip::findIndex(unknownSide, "/", 0, indexOfUnknown - 1);
	}
	else if(!leftOfUnknown && indexOfUnknown < strlen(unknownSide) - 1)
	{
		indexOfMultiply = StringManip::findIndex(unknownSide, "*", indexOfUnknown + 1, strlen(unknownSide));
		indexOfDivide = StringManip::findIndex(unknownSide, "/", indexOfUnknown + 1, strlen(unknownSide));
	}

	//If there is no expression, then do not do anything
	if (indexOfDivide == -1 && indexOfMultiply == -1) return;

	char* expressionString = nullptr;
	//If this is true, then this is A/x = B, so we make it x = A/B
	if (indexOfDivide > indexOfMultiply && indexOfDivide != -1 && leftOfUnknown)
	{
		expressionString = new char[indexOfDivide + 1];
		strncpy(expressionString, unknownSide, indexOfDivide);
		expressionString[indexOfDivide] = '\0';

		BigNumberExpression expression(expressionString);
		BigNumberExpression knownExpression(knownSide);
		BigNumberExpression newKnownExpression = expression / knownExpression;

		char* newUnknownSide = StringManip::replaceFrom(unknownSide, "", 0, indexOfDivide);
		delete[] unknownSide;
		unknownSide = newUnknownSide;

		delete[] knownSide;
		knownSide = new char[strlen(newKnownExpression.getExpression()) + 1];
		strcpy(knownSide, newKnownExpression.getExpression());
	}
	//If this is true, then this is A*x = B, so we make it x = B/A
	else if (indexOfMultiply > indexOfDivide && indexOfMultiply != -1 && leftOfUnknown)
	{
		expressionString = new char[indexOfMultiply + 1];
		strncpy(expressionString, unknownSide, indexOfMultiply);
		expressionString[indexOfMultiply] = '\0';

		BigNumberExpression expression(expressionString);
		BigNumberExpression knownExpression(knownSide);
		BigNumberExpression newKnownExpression = knownExpression / expression;

		char* newUnknownSide = StringManip::replaceFrom(unknownSide, "", 0, indexOfMultiply);
		delete[] unknownSide;
		unknownSide = newUnknownSide;

		delete[] knownSide;
		knownSide = new char[strlen(newKnownExpression.getExpression()) + 1];
		strcpy(knownSide, newKnownExpression.getExpression());
	}
	/*
	*	x*2/3 = 3;
	*	x*2 = 9;
	*	x = 4;
	*	x = 5
	* 
	*	x*5/7 = 13;
	*	x*5 = 91;
	*   x = 18(1); ==> 19
	*	
	*	18*5/7=90/7=12(6);
	*   19*5/7=95/7=13(4);
	*	
	* 
	*	x*5/7*11/13 = 17;
	*   x*5/7*11 = 221;
	*	x*5/7 = 20(1); 
	*	x*5 = 140;
	*	x = 28;
	*	
	*	28*5/7*11/13=140/7*11/13=20*11/13=220/13=16(12);
	* 
	*	x*5/7*11/13 = 17;
		x*5/7*11 = 221;
		x*5/7 = 20(1); ==> 21
		x*5 = 147;
		x = 29(2);
		
		29*5/7*11/13=145/7*11/13=20*11/13=220/13=16(12);

		x*5/7*11/13 = 17;
		x*5/7*11 = 221;
		x*5/7 = 20(1); ==> 21
		x*5 = 147;
		x = 29(2); ==> 30

		30*5/7*11/13=150/7*11/13=21*11/13=231/13=17(10);

		x*3/5*7/11*13/17*19/23 = 29;
		x*3/5*7/11*13/17*19 = 667;
		x*3/5*7/11*13/17 = 35(2); ==> 36
		x*3/5*7/11*13 = 612;
		x*3/5*7/11 = 47(1); ==> 48
		x*3/5*7 = 528;
		x*3/5 = 75(3); ==> 76
		x*3 = 380;
		x = 126(2); ==> 127

		127*3/5*7/11*13/17*19/23 =
		= 381/5*7/11*13/17*19/23 =
		= 76*7/11*13/17*19/23 = 
		= 532/11*13/17*19/23 = 
		= 48*13/17*19/23 =
		= 624/17*19/23 =
		= 36*19/23 =
		= 684/23 = 
		= 29;

		x/4*3 = 12;
		x/4 = 4;
		x = 16;

		x/4*3/8*6 = 36;
		x = 36*4/3*8/6;
		x = 48*8/6 = 104
		104/4*3/8*6 = 26

		x/4*3/8*6 = 36;
		x/4*3/8 = 6;
		x/4*3 = 48;
		x/4 = 16;
		x = 64;
	*/
	//If this is true, then this is x/A = B, so we make a lot of bullshit to have this work properly.
	//Basically, from the end of the unknownSide, start moving everything to the right with the opposite sign.
	//If it is x/A*B=C, then that means we first do x/A=C/B;
	//For C/B, we first do the percent operator. D = C%B;
	//Then we do the division C/B = E;
	//If D != 0, then E = E+1;
	//Then we return E as the new knownSide and are left with x/A=E;
	//Then it x=E*A; EASY!!!
	else if (!leftOfUnknown)
	{
		//Resolve all of the brackets from the right of the unknown
		while (true)
		{
			bool insideBracket = false;
			int bracketsNestedCount = 0;
			bool foundFirstOpeningBracket = false;
			int indexOfFirstOpeningBracket = -1;
			int indexOfLastClosingBracket = -1;
			bool foundBracketsExpression = false;

			for (size_t i = 0; i < strlen(unknownSide); i++)
			{
				char symbol = unknownSide[i];
				if (symbol == '(')
				{
					bracketsNestedCount++;
					if (foundFirstOpeningBracket == false)
					{
						foundFirstOpeningBracket = true;
						indexOfFirstOpeningBracket = i;
					}
					if (insideBracket == false) insideBracket = true;
				}
				else if (symbol == ')')
				{
					bracketsNestedCount--;
					if (bracketsNestedCount == 0 && foundFirstOpeningBracket == true)
					{
						indexOfLastClosingBracket = i;
						foundBracketsExpression = true;
						break;
					}
				}
			}

			//If there are no brackets expressions left unresolved, then exit the loop
			if (foundBracketsExpression) break;

			//Get the brackets expression, resolve it and replace it inside the unknownSide string
			char* bracketsExpressionString = new char[indexOfLastClosingBracket - indexOfFirstOpeningBracket + 2];
			bracketsExpressionString[indexOfLastClosingBracket - indexOfFirstOpeningBracket + 1] = '\0';
			for (size_t i = indexOfFirstOpeningBracket; i <= indexOfLastClosingBracket; i++)
			{
				bracketsExpressionString[i - indexOfFirstOpeningBracket] = unknownSide[i];
			}

			BigNumberExpression bracketsExpression(bracketsExpressionString);
			const char* bracketsExpressionStringResolved = bracketsExpression.evaluateExpression().getNumberRaw();

			//Replace the resolved brackets expression in the unknownSide
			char* unknownSideCopy = StringManip::replaceFrom(unknownSide, bracketsExpressionStringResolved, indexOfFirstOpeningBracket, indexOfLastClosingBracket);
			delete[] unknownSide;
			unknownSide = unknownSideCopy;
		}

		//Move all of the operators one by one until none are left
		size_t countOfOperators = 0;
		while (true)
		{
			int indexOfLastDivide = StringManip::findIndexLast(unknownSide, "/");
			int indexOfLastMultiply = StringManip::findIndexLast(unknownSide, "*");

			//If we enter here, that means the last operator is a divide one.
			if (
				(indexOfLastDivide < indexOfLastMultiply && indexOfLastMultiply != -1 && indexOfLastDivide != -1) ||
				(indexOfLastDivide != -1 && indexOfLastMultiply == -1)
				)
			{
				char* divideNumber = StringManip::replaceFrom(unknownSide, "", 0, indexOfLastDivide);

				//Move the divideNumber to the other side with a * operator
				BigNumberExpression knownExpression(knownSide);
				BigNumberExpression divideNumberExpression(divideNumber);
				BigNumberExpression newKnownExpression = knownExpression * divideNumberExpression;

				//Delete dynamic memory
				delete[] divideNumber;

				char* newUnknownSide = StringManip::replaceFrom(unknownSide, "", indexOfLastDivide);
				delete[] unknownSide;
				unknownSide = newUnknownSide;

				delete[] knownSide;
				knownSide = new char[strlen(newKnownExpression.getExpression()) + 1];
				strcpy(knownSide, newKnownExpression.getExpression());
			}
			//If we enter here, that means the last operator is a multiply one
			else if (
				(indexOfLastMultiply < indexOfDivide && indexOfLastMultiply != -1 && indexOfLastDivide != -1) ||
				(indexOfLastMultiply != -1 && indexOfDivide == -1)
				)
			{
				char* multiplyNumber = StringManip::replaceFrom(unknownSide, "", 0, indexOfLastMultiply);

				//Move the multiplyNumber to the other side with a / operator
				BigNumberExpression knownExpression(knownSide);
				BigNumber knownExpressionResolvedNumber = knownExpression.evaluateExpression();
				BigNumber multiplyBigNumber(multiplyNumber);

				//Delete dynamic memory
				delete[] multiplyNumber;

				BigNumber finalKnownExpressionResolvedNumber = knownExpressionResolvedNumber / multiplyBigNumber;
				//Check if there is leftover when dividing the knowExpressionResolvedNumber with the multiplyBigNumber. If there is, increase the finalKnownExpressionResolvedNumber by 1
				BigNumber finalKnownExpressionResolvedNumberLeftOver = knownExpressionResolvedNumber % multiplyBigNumber;
				if (!finalKnownExpressionResolvedNumberLeftOver.isZero()) finalKnownExpressionResolvedNumber+=1;

				//BigNumberExpression divideNumberExpression(multiplyNumber);
				BigNumberExpression newKnownExpression(finalKnownExpressionResolvedNumber.getNumberRaw());

				char* newUnknownSide = StringManip::replaceFrom(unknownSide, "", indexOfLastMultiply);
				delete[] unknownSide;
				unknownSide = newUnknownSide;

				delete[] knownSide;
				knownSide = new char[strlen(newKnownExpression.getExpression()) + 1];
				strcpy(knownSide, newKnownExpression.getExpression());
			}
			//If we get here, then there are no more left numbers to move to the other side, so we break out of the loop
			else
			{
				break;
			}
		}
	}

	delete[] expressionString;
}

//BigNumber BigNumberEquation::solveEquation(const char* equation)
//{
//	//Check if the belongs to the object caller
//	if (equation == nullptr) equation = this->getEquation();
//
//	//Remove the whitespaces
//	char* equationCopy = StringManip::replaceAll(equation, " ", "");
//
//	//Check if the equation is valid
//	if (!isValidEquation(equationCopy)) throw "Invalid Equation";
//
//	//Check if the equation has only one unknown. If it doesn't, then throw an exception because I am not that smart to want to code that looooool...
//	size_t countOfUnknowns = StringManip::countOf(equationCopy, "x");
//	if (countOfUnknowns != 1) throw "Equation is too complex for me to solve";
//
//	//Replace all the instances of +-,-+, -- inside the equation
//	char* equationOne = StringManip::replaceAll(equationCopy, "+-", "-");
//	char* equationTwo = StringManip::replaceAll(equationOne, "-+", "-");
//	char* equationThree = StringManip::replaceAll(equationTwo, "--", "+");
//
//	equationCopy = equationThree;
//
//	//Delete dynamic memory
//	delete[] equationTwo;
//	delete[] equationOne;
//
//	//Split the equation by the unknown side and the known side
//	size_t sidesCount = 0;
//	char** sides = StringManip::splitString(equationCopy, "=", sidesCount);
//	char* unknownSide = sides[0];
//	char* knownSide = sides[1];
//	char* adressCopyFirstSide = sides[0];
//	char* adressCopySecondSide = sides[1];
//
//	//If the right side is the one with the unknown, then swap the sides
//	if (StringManip::stringContains(knownSide, "x"))
//	{
//		char* copy = unknownSide;
//		unknownSide = knownSide;
//		knownSide = copy;
//	}
//
//	//Check if the unknown is inside brackets
//	size_t indexOfUnknown = StringManip::findIndex(unknownSide, "x");
//	int openingBracketBeforeUnknown = -1;
//	int closingBracketBeforeUnknown = -1;
//	if (indexOfUnknown != 0)
//	{
//		openingBracketBeforeUnknown = StringManip::findIndexLast(unknownSide, "(", 0, indexOfUnknown - 1);
//		closingBracketBeforeUnknown = StringManip::findIndexLast(unknownSide, ")", 0, indexOfUnknown - 1);
//	}	
//
//	//If this is true, then the unknown is in brackets
//	if (openingBracketBeforeUnknown > -1 && closingBracketBeforeUnknown == -1)
//	{
//		//Do shit to resolve the brackets
//	}
//
//	//Now there is no brackets
//	//Move everything that is 'not connected' to the unknown via *, /, *-, /- to the right hand side with the opposite operator
//	movePlusAndMinus(unknownSide, knownSide, true, indexOfUnknown);
//
//	//Get the new index of unknown
//	indexOfUnknown = StringManip::findIndex(unknownSide, "x");
//
//	//Now do the same thing for everything that is to the right of the unknown
//	movePlusAndMinus(unknownSide, knownSide, false, indexOfUnknown);
//
//	//Get the new index of unknown
//	indexOfUnknown = StringManip::findIndex(unknownSide, "x");
//	
//	//Now do the same thing for the divide and multiply operators	
//	//Move the left side over first
//	moveMultiplyAndDivide(unknownSide, knownSide, true, indexOfUnknown);
//
//	//Get the new index of unknown
//	indexOfUnknown = StringManip::findIndex(unknownSide, "x");
//
//	//Now move the right side over 
//	moveMultiplyAndDivide(unknownSide, knownSide, false, indexOfUnknown);
//
//	//By this point, the equation should look like this --> x = A or -x = A. 	
//	//TODO: FIGURE OUT WHAT TO DO IF THE EVALUATED EXPRESSION CANNOT BE SOLVED BECAUSE IT HAS A DIVISION BY 0 SOMEWHERE IN IT. FOR NOW, WE ASSUME THAT WON'T HAPPEN
//	BigNumber equationAnswer = BigNumberExpression(knownSide).evaluateExpression();
//	
//	//Now check if the unknown has a minus sign before it;
//	bool invertSign = StringManip::stringStartsWith(unknownSide, "-");
//
//	if (invertSign) equationAnswer *= -1;
//
//	//Delete dynamic memory
//
//	delete[] sides;
//	delete[] equationCopy;
//
//	return equationAnswer;
//}

BigNumber BigNumberEquation::solveEquation(const char* equation)
{
	//Check if the belongs to the object caller
	if (equation == nullptr) equation = this->getEquation();

	//Remove the whitespaces
	char* equationCopy = StringManip::replaceAll(equation, " ", "");

	//Check if the equation is valid
	if (!isValidEquation(equationCopy)) throw "Invalid Equation";

	//Check if the equation has only one unknown. If it doesn't, then throw an exception because I am not that smart to want to code that looooool...
	size_t countOfUnknowns = StringManip::countOf(equationCopy, "x");
	if (countOfUnknowns != 1) throw "Equation is too complex for me to solve";

	//Split the equation by the unknown side and the known side
	size_t sidesCount = 0;
	char** sides = StringManip::splitString(equationCopy, "=", sidesCount);
	char* unknownSide = sides[0];
	char* knownSide = sides[1];

	//If the right side is the one with the unknown, then swap the sides
	if (StringManip::stringContains(knownSide, "x"))
	{
		char* copy = unknownSide;
		unknownSide = knownSide;
		knownSide = copy;
	}

	size_t bracketedExpressionsWithUnknownIndex = 0;
	char** bracketedExpressionsWithUnknown = new char* [StringManip::countOf(unknownSide, "(")];

	size_t indexOfUnknown = 0; 

	while (true)
	{
		//Update the index of unknown
		indexOfUnknown = StringManip::findIndex(unknownSide, "x");

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
		for (size_t i = indexOfUnknown + 1; i < strlen(unknownSide); i++)
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
		char* storedExpression = new char[closingBracketAfterUnknown - openingBracketBeforeUnknown + 2];
		storedExpression[closingBracketAfterUnknown - openingBracketBeforeUnknown + 1] = '\0';
		for (size_t i = openingBracketBeforeUnknown; i <= closingBracketAfterUnknown; i++)
		{
			storedExpression[i - openingBracketBeforeUnknown] = unknownSide[i];
		}

		char* newUnknownSide = StringManip::replaceFirst(unknownSide, storedExpression, "x");
		delete[] unknownSide;
		unknownSide = newUnknownSide;

		bracketedExpressionsWithUnknown[bracketedExpressionsWithUnknownIndex++] = storedExpression;
	}

	//Now check if the unknown is tied to a division
	while (true)
	{
		//Update the index of unknown
		indexOfUnknown = StringManip::findIndex(unknownSide, "x");

		//Check if the unknown is tied to a division to the left
		int indexOfLastLeftDivide = -1;
		int indexOfLastLeftDivideMinus = -1;
		int indexOfLastLeftDividePlus = -1;
		if (indexOfUnknown != 0)
		{
			indexOfLastLeftDivide = StringManip::findIndexLast(unknownSide, "/", 0, indexOfUnknown - 1);
			indexOfLastLeftDivideMinus = StringManip::findIndexLast(unknownSide, "/-", 0, indexOfUnknown - 1);
			indexOfLastLeftDividePlus = StringManip::findIndexLast(unknownSide, "/+", 0, indexOfUnknown - 1);
		}

		bool tiedToDivision = false;

		if (indexOfLastLeftDivide != -1 && indexOfLastLeftDivide == indexOfUnknown - 1) tiedToDivision = true;
		else if (indexOfLastLeftDivideMinus != -1 && indexOfLastLeftDivideMinus == indexOfUnknown - 2) tiedToDivision = true;
		else if (indexOfLastLeftDividePlus != -1 && indexOfLastLeftDividePlus == indexOfUnknown - 2) tiedToDivision = true;

		//Check if the unknown is tied to a division from the right
		bool divideInBrackets = false;
		int bracketsNested = 0;
		for (size_t i = indexOfUnknown + 1; i < strlen(unknownSide); i++)
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
			throw "The unknown is tied to division, so I can't solve this expression, sorry!";
		}
		//In this case, the unknown isn't tied to any division
		else if (!tiedToDivision && bracketedExpressionsWithUnknownIndex < 1) break;
		//In this case, the replace the unknown with the next stored bracketed expression
		else 
		{
			char* newUnknownSide = StringManip::replaceFirst(unknownSide, "x", bracketedExpressionsWithUnknown[--bracketedExpressionsWithUnknownIndex]);
			delete[] unknownSide;
			unknownSide = newUnknownSide;
		}
	}

	//If we get to here, then there is no division tied to the unknown, so we can solve the equation easily
	//Calculate the linear increase between increasing the value of x by 1 and use that to calculate whether or not the equation has a solution
	BigNumber testValue1(1);
	BigNumber testValue2(2);
	BigNumberExpression knownSideExpression(knownSide);
	
	char* expressionTestValue1String = StringManip::replaceFirst(unknownSide, "x", testValue1.getNumberRaw());
	BigNumberExpression expressionTestValue1(expressionTestValue1String);

	char* expressionTestValue2String = StringManip::replaceFirst(unknownSide, "x", testValue2.getNumberRaw());
	BigNumberExpression expressionTestValue2(expressionTestValue2String);

	BigNumber testValue1Result = (expressionTestValue1 - knownSideExpression).evaluateExpression();
	if (testValue1Result.getSign() == -1) testValue1Result *= -1;
	BigNumber testValue2Result = (expressionTestValue2 - knownSideExpression).evaluateExpression();
	if (testValue2Result.getSign() == -1) testValue2Result *= -1;

	BigNumber deltaResult = testValue2Result - testValue1Result;

	//If this is true, then that means that by increasing x by 1, we increase the result of the expression when substituting with x.
	//However, we want the opposite to happen, so we divide the testValue1Result by deltaResult to see how many times we need to lower x by 1 from 1 before we get the equation to 0
	if (deltaResult.getSign() != 0)
	{
		BigNumber decreaseOfX = testValue1Result / deltaResult;

		BigNumber decreaseOfXLeftover = testValue1Result % deltaResult;

		//If this is true, then the equation doesn't have a solution that is a whole number;
		//TODO: MAKE SOMETHING GOOD WITH THIS
		if (decreaseOfXLeftover.getSign() != 0) throw "Not whole number solution";
		//If we get here, then 1 - decreaseOfX should be the answer to the equation, unless in between 1 and 1-decreaseOfX there is a value where the expression breaks because of division by 0
		else
		{
			BigNumber potentialAnswer = (decreaseOfX - 1) * -1;
			
			//Test the potential answer to see if it holds true
			char* expressionPotenialAnswerString = StringManip::replaceFirst(unknownSide, "x", potentialAnswer.getNumberRaw());
			BigNumberExpression expressionPotenialAnswer(expressionPotenialAnswerString);

			//By presumption, this should not throw an error for dividing by 0, because I made it so that the unknown isn't tied to a division in the first place
			BigNumber potentialAnswerResult = (expressionPotenialAnswer - knownSideExpression).evaluateExpression();

			//In this case, we got the correct answer
			if (potentialAnswerResult.getSign() == 0)
			{
				//Delete dynamic memory
				delete[] expressionPotenialAnswerString;
				delete[] expressionTestValue2String;
				delete[] expressionTestValue1String;
				StringManip::deleteArrayOfStrings(sides, 2);

				return potentialAnswer;
			}
			//In this case, there is no correct answer to the equation that is a whole number
			else
			{
				throw "Not whole number solution";
			}
		}
	}
	else
	{
		//In this case, every x that is a whole number is an answer to the equation
		if (testValue1Result.getSign() == 0) throw "Every x is an answer to the equation";
		else throw "No answer for this equation";
	}

	return BigNumber();
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
