#include "BigNumberExpressionCommon.h"
#include <iostream>
#include "..\Project.StringManipulation\StringManip.h"

char BigNumberExpressionCommon::generateOperator(int seed) const
{
	if (seed == 4) return '%';
	else if (seed == 3) return '/';
	else if (seed == 2) return '*';
	else if (seed == 1) return '-';
	else if (seed == 0) return '+';
}

char BigNumberExpressionCommon::generateOpeningParenthesis(int seed) const
{
	if (seed > 7) return '(';
	else if (seed >= 0) return '#';
}

int BigNumberExpressionCommon::generateSign(int seed) const
{
	if (seed >= 12) return -1;
	else if (seed >= 1) return 1;
	else if (seed == 0) return 0;
}

size_t BigNumberExpressionCommon::generateDigitsCount(int seed) const
{
	if (seed == 50) return 30;
	else if (seed >= 48) return 9;
	else if (seed >= 46) return 8;
	else if (seed >= 43) return 7;
	else if (seed >= 39) return 6;
	else if (seed >= 34) return 5;
	else if (seed >= 25) return 4;
	else if (seed >= 16) return 3;
	else if (seed >= 8) return 2;
	else if (seed <= 7) return 1;
}

char* BigNumberExpressionCommon::replaceNumbers(const char* expression, const char* replacement) const
{
	char* newExpression = new char[strlen(expression) + 1];
	strcpy(newExpression, expression);

	//Replace all of the numbers in the expression with an x
	bool isOnNumber = false;
	size_t currentNumberStartIndex = 0;

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
			char* expressionCopy = StringManip::replaceFrom(newExpression, replacement, currentNumberStartIndex, i - 1);
			delete[] newExpression;
			newExpression = expressionCopy;

			//Now move back the counter because you have just deleted a very important number;
			i -= (i - 1 - currentNumberStartIndex + 1 - strlen(replacement));
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
