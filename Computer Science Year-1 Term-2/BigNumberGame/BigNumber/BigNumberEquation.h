#pragma once

#include "BigNumberExpression.h"

class BigNumberEquation
	:public BigNumberExpressionCommon
{
public:
	//Exception messages
	static constexpr const char* EQUATION_INVALID_EXCEPTION = "Invalid Equation!";
	static constexpr const char* EQUATION__SOLVE_TOOCOMPLEX_EXCEPTION = "Equation is too complex for me to solve";
	static constexpr const char* EQUATION__SOLVE_TIEDTODIVISION_EXCEPTION = "The unknown is tied to division, so I can't solve this equation, sorry!";
	static constexpr const char* EQUATION__SOLVE_NOTWHOLE_EXCEPTION = "Not whole number solution";
	static constexpr const char* EQUATION__SOLVE_EVERYANSWER_EXCEPTION = "Every x is an answer to the equation";
	static constexpr const char* EQUATION__SOLVE_NOANSWER_EXCEPTION = "No answer for this equation";

private:
	static constexpr const char* EQUATION_OPERATORS = "+-*/";

	char* equation;
	size_t capacity;

	void copy(const BigNumberEquation& other);

	int generateCountOfX(int seed);

	//Move everything that is not tied to the unknown with a * or / to the other side 
	void movePlusAndMinus(char*& unknownSide, char*& knownSide, bool leftOfUnknown, size_t indexOfUnknown);

	//Move everything that is tied to the unknown via * or / to the other side
	void moveMultiplyAndDivide(char*& unknownSide, char*& knownSide, bool leftOfUnknown, size_t indexOfUnknown);
public:

	//Big 4
	BigNumberEquation();
	BigNumberEquation(const BigNumberEquation& other);
	BigNumberEquation& operator= (const BigNumberEquation& other);
	~BigNumberEquation();

	//Other constructors
	BigNumberEquation(const char* equation);
	BigNumberEquation(const BigNumberExpression& expression);

	//Check for equation validity. Excluding if the equation has a solution or not, or if it throws a divide by zero exception
	bool isValidEquation(const char* equation = nullptr) const;

	//Get the answer to an equation
	BigNumber solveEquation(const char* equation = nullptr);

	//Fill the numbers in an equation template
	char* generateFromTemplate(const char* expressionTemplate, size_t maxUnknown = 3);

	//Generate a random equation. totalUnknown should be at most =maxUnknownPerSide, otherwise, throw error!
	void generateEquation(size_t maxUnknownPerSide = 3, size_t totalUnknown = 6);

	//Generate equation from an expression
	char* generateEquation(const char* expression);

	//Get equation as read-only
	const char* getEquation() const;
	//Set equation
	void setEquation(const char* equation);

	//Get the right expression as read-only
	const char* getRightExpression() const;

	//Get the left expression, with the 'x', as read-only
	const char* getLeftExpression() const;

	//Get equation template
	char* getEquationTemplate(const char* equation = nullptr) const;

	//Reading and outputting expressions to text file or console
	friend std::istream& operator>> (std::istream& is, BigNumberEquation& equation);
	//friend std::ostream& operator<< (std::ostream& is, BigNumberExpression& expression);

	friend std::ifstream& operator>> (std::ifstream& is, BigNumberEquation& expression);
	//friend std::ofstream& operator<< (std::ofstream& os, BigNumberExpression& expression);
};

