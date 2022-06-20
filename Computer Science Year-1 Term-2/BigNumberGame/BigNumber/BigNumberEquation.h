#pragma once

#include "BigNumberExpression.h"

class BigNumberEquation
	:public BigNumberExpressionCommon
{
public:
	//Exception messages CONSTANTS
	static const mstring EQUATION_INVALID_EXCEPTION;
	static const mstring EQUATION__SOLVE_TOOCOMPLEX_EXCEPTION;
	static const mstring EQUATION__SOLVE_TIEDTODIVISION_EXCEPTION;
	static const mstring EQUATION__SOLVE_NOTWHOLE_EXCEPTION;
	static const mstring EQUATION__SOLVE_EVERYANSWER_EXCEPTION;
	static const mstring EQUATION__SOLVE_NOANSWER_EXCEPTION;
	static const mstring EQUATION_OPERATORS;

private:

	mstring equation;
	//size_t capacity;

	/*void copy(const BigNumberEquation& other);*/

	int generateCountOfX(int seed);

public:

	//Big 4
	BigNumberEquation();

	//Other constructors
	BigNumberEquation(mstring equation);

	//Check for equation validity. Excluding if the equation has a solution or not, or if it throws a divide by zero exception
	bool isValidEquation(mstring equation) const;
	bool isValidEquation() const;

	//Get the answer to an equation
	BigNumber solveEquation(mstring equation);
	BigNumber solveEquation();

	//Fill the numbers in an equation template
	mstring generateFromTemplate(mstring expressionTemplate, size_t maxUnknown = 3);

	//Generate a random equation, where the left side and the right side can contain only the given operators. totalUnknown should be at most =maxUnknownPerSide, otherwise, throw error!
	void generateEquation(mstring leftSideAllowedOperators, mstring rightSideAllowedOperators, size_t maxUnknownPerSide = 3, size_t totalUnknown = 6);

	//Generate a random equation. totalUnknown should be at most =maxUnknownPerSide, otherwise, throw error!
	void generateEquation(size_t maxUnknownPerSide = 3, size_t totalUnknown = 6);

	//Get equation as read-only
	mstring getEquation() const;

	//Set equation
	void setEquation(mstring equation);

	//Get the right expression as read-only
	mstring getRightExpression() const;

	//Get the left expression, with the 'x', as read-only
	mstring getLeftExpression() const;

	//Get equation template
	mstring getEquationTemplate(mstring equation) const;
	mstring getEquationTemplate() const;

	///Reading and outputting equation to text file or console
	friend std::istream& operator>> (std::istream& is, BigNumberEquation& equation);
	friend std::ostream& operator<< (std::ostream& os, BigNumberEquation& equation);

	friend std::ifstream& operator>> (std::ifstream& is, BigNumberEquation& equation);
	friend std::ofstream& operator<< (std::ofstream& os, BigNumberEquation& equation);
};

