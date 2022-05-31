#pragma once

#include "MBigNumberExpression.h"

class MBigNumberEquation
	:public MBigNumberExpressionCommon
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

	/*void copy(const MBigNumberEquation& other);*/

	int generateCountOfX(int seed);

public:

	//Big 4
	MBigNumberEquation();
	/*MBigNumberEquation(const MBigNumberEquation& other);
	MBigNumberEquation& operator= (const MBigNumberEquation& other);
	~MBigNumberEquation();*/

	//Other constructors
	MBigNumberEquation(mstring equation);

	//Check for equation validity. Excluding if the equation has a solution or not, or if it throws a divide by zero exception
	bool isValidEquation(mstring equation) const;
	bool isValidEquation() const;

	//Get the answer to an equation
	MBigNumber solveEquation(mstring equation);
	MBigNumber solveEquation();

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
	friend std::istream& operator>> (std::istream& is, MBigNumberEquation& equation);
	friend std::ostream& operator<< (std::ostream& os, MBigNumberEquation& equation);

	friend std::ifstream& operator>> (std::ifstream& is, MBigNumberEquation& equation);
	friend std::ofstream& operator<< (std::ofstream& os, MBigNumberEquation& equation);
};

