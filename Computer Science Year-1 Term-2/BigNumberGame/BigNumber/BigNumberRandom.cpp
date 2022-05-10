#include "BigNumberRandom.h"
#include <iostream>

char BigNumberRandom::generateOperator(int seed) const
{
	if (seed == 4) return '%';
	else if (seed == 3) return '/';
	else if (seed == 2) return '*';
	else if (seed == 1) return '-';
	else if (seed == 0) return '+';
}

char BigNumberRandom::generateOpeningParenthesis(int seed) const
{
	if (seed > 7) return '(';
	else if (seed >= 0) return '#';
}

int BigNumberRandom::generateSign(int seed) const
{
	if (seed >= 12) return -1;
	else if (seed >= 1) return 1;
	else if (seed == 0) return 0;
}

size_t BigNumberRandom::generateDigitsCount(int seed) const
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

//BigNumberRandom::BigNumberRandom()
//{
//	srand(time(NULL));
//}
