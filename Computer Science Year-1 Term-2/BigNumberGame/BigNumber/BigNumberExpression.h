#pragma once
#include "BigNumber.h"
#include <ostream>
#include <fstream>

class BigNumberExpression
{
public:
	//Check if the expression contains +++, ++-, +-+, +--, -++, -+-, --+, ---. If it does, then it is invalid
	//Check if the expression contains: **, */, *%, /*, //, /%, %*, %/, %%. If it does, then it is invalid
	//Check if the expression contains: +*, -*, +/, -/, +%, -%. If it does, then it is invalid
	//Check if the expression contains: +), -), *), /), %), (). If it does, then it is invalid
	//Mnogo durvarski na4in za proverka, ama vse taq. Eventualno ako resha da dobavq stepenuvane shte go opravq
	//FORBIDDEN SYMBOLS CONSTANT
	static const int EXPRESSION_FORBIDDEN_STRINGS_COUNT = 29;
	static const constexpr char* EXPRESSION_FORBIDDEN_STRINGS[29] =
	{
		"+++",
		"++-",
		"+-+",
		"+--",
		"-++",
		"-+-",
		"--+",
		"---",
		"**",
		"*/",
		"*%",
		"/*",
		"//",
		"/%",
		"%*",
		"%/",
		"%%",
		"+*",
		"-*",
		"+/",
		"-/",
		"+%",
		"-%",
		"+)",
		"-)",
		"*)",
		"/)",
		"%)",
		"()"
	};
private:


	char* expression;
	size_t capacity;

	void copy(const BigNumberExpression& other);

	BigNumber* replaceNumbersFromCalculation(BigNumber* numbers, size_t& countOfNumbers, size_t firstIndex, BigNumber* resultNumber) const;
	void replaceOperatorsFromCalculation(char* operators, size_t index) const;

	char generateOperator(int seed);
	char generateOpeningParenthesis(int seed);
	int generateSign(int seed);
	size_t generateDigitsCount(int seed);
public:

	//Big 4
	BigNumberExpression();
	BigNumberExpression(const BigNumberExpression& other);
	~BigNumberExpression();
	BigNumberExpression& operator=(const BigNumberExpression& other);

	BigNumberExpression(const char* equation);

	//Get the equation as read-only
	const char* getExpression() const;

	//Set the equation
	void setExpression(const char* expression);

	//Return the answer to an expression
	BigNumber evaluteExpression(const char* expression = nullptr) const;

	bool expressionIsValid(const char* expression = nullptr) const;

	//Randomly generate a new expression
	void generateExpression();

	char* concatExpressionsWithOperator(const char* thisExpression, const char* otherExpression, const char* concatOperator) const;

	//Comparative operators
	bool operator == (const BigNumberExpression& other) const;
	bool operator != (const BigNumberExpression& other) const;
	bool operator < (const BigNumberExpression& other) const;
	bool operator <= (const BigNumberExpression& other) const;
	bool operator > (const BigNumberExpression& other) const;
	bool operator >= (const BigNumberExpression& other) const;

	//Operator arithmetic
	BigNumberExpression operator+(const BigNumberExpression& other) const;
	BigNumberExpression& operator+=(const BigNumberExpression& other);

	BigNumberExpression operator-(const BigNumberExpression& other) const;
	BigNumberExpression& operator-=(const BigNumberExpression& other);

	BigNumberExpression operator*(const BigNumberExpression& other) const;
	BigNumberExpression& operator*=(const BigNumberExpression& other);

	BigNumberExpression operator/(const BigNumberExpression& other) const;
	BigNumberExpression& operator/=(const BigNumberExpression& other);

	BigNumberExpression operator%(const BigNumberExpression& other) const;
	BigNumberExpression& operator%=(const BigNumberExpression& other);

	//Reading and outputting expressions to text file or console
	friend std::istream& operator>> (std::istream& is, BigNumberExpression& expression);
	friend std::ostream& operator<< (std::ostream& is, BigNumberExpression& expression);

	friend std::ifstream& operator>> (std::ifstream& is, BigNumberExpression& expression);
	friend std::ofstream& operator<< (std::ofstream& os, BigNumberExpression& expression);
};

