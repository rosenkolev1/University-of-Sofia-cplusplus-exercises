#pragma once
#include "..\Project.StringManipulation\MString.h"

class MBigNumberExpressionCommon
{
protected:
	//0-4 for expression
	virtual char generateOperator() const;

	//0-9 for expression
	virtual char generateOpeningParenthesis() const;

	//0-14 for expression
	virtual int generateSign() const;

	//0-50 for expression
	virtual size_t generateDigitsCount() const;

	//Replace all the numbers in the expression with something else
	virtual mstring replaceNumbers(mstring expression, mstring replacement) const;
};



