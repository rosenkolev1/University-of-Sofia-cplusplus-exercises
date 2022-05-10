#pragma once
class BigNumberRandom
{
protected:
	//0-4 for expression
	virtual char generateOperator(int seed) const;

	//0-9 for expression
	virtual char generateOpeningParenthesis(int seed) const;

	//0-14 for expression
	virtual int generateSign(int seed) const;

	//0-50 for expression
	virtual size_t generateDigitsCount(int seed) const;

	//Initialize srand so that the user doesn't have to do that himself
	//BigNumberRandom();
};

