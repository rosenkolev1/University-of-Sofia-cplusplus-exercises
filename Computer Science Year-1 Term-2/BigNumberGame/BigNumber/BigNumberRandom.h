#pragma once
class BigNumberRandom
{
protected:
	virtual char generateOperator(int seed) const;
	virtual char generateOpeningParenthesis(int seed) const;
	virtual int generateSign(int seed) const;
	virtual size_t generateDigitsCount(int seed) const;

	//Initialize srand so that the user doesn't have to do that himself
	//BigNumberRandom();
};

