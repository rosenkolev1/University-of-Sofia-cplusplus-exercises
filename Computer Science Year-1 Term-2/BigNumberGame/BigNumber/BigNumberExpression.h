#pragma once
#include "BigNumber.h"
#include "BigNumberExpressionCommon.h"
#include <ostream>
#include <fstream>

class BigNumberExpression
	:public BigNumberExpressionCommon
{
public:
	//Check if the expression contains +++, ++-, +-+, +--, -++, -+-, --+, ---. If it does, then it is invalid
	//Check if the expression contains: **, */, *%, /*, //, /%, %*, %/, %%. If it does, then it is invalid
	//Check if the expression contains: +*, -*, +/, -/, +%, -%. If it does, then it is invalid
	//Check if the expression contains: +), -), *), /), %), (). If it does, then it is invalid
	//Mnogo durvarski na4in za proverka, ama vse taq. Eventualno ako resha da dobavq stepenuvane shte go opravq
	//FORBIDDEN SYMBOLS CONSTANT
	static constexpr const char* EXPRESSION_DIVIDEBYZERO_EXCEPTION = "DIVISION BY 0 IS NOT ALLOWED!";
	static constexpr const char* EXPRESSION_PERCENTBYZERO_EXCEPTION = "PERCENT BY 0 IS NOT ALLOWED!";
	static constexpr const char* EXPRESSION_INVALID_EXCEPTION = "This expression isn't valid";

	static const int EXPRESSION_FORBIDDEN_STRINGS_COUNT = 32;
	static constexpr const char* EXPRESSION_OPERATORS = "+-*/%";
	static constexpr const char* EXPRESSION_NOTDIGIT = "+-*/%()";
	static const constexpr char* EXPRESSION_FORBIDDEN_STRINGS[32] =
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
		"(*",
		"(/",
		"(%",
		"()"
	};
private:


	char* expression;
	size_t capacity;

	void copy(const BigNumberExpression& other);

	BigNumber* replaceNumbersFromCalculation(BigNumber* numbers, size_t& countOfNumbers, size_t firstIndex, BigNumber* resultNumber) const;
	void replaceOperatorsFromCalculation(char* operators, size_t index) const;

	/*char generateOperator(int seed) const;
	char generateOpeningParenthesis(int seed) const;
	int generateSign(int seed) const;
	size_t generateDigitsCount(int seed) const;*/
public:

	//Big 4
	BigNumberExpression();
	BigNumberExpression(const BigNumberExpression& other);
	~BigNumberExpression();
	BigNumberExpression& operator=(const BigNumberExpression& other);

	BigNumberExpression(const char* expression);

	//Get the equation as read-only
	const char* getExpression() const;

	//Set the equation
	void setExpression(const char* expression);

	//Return the answer to an expression
	BigNumber evaluateExpression(const char* expression = nullptr) const;

	//Check if expression is valid
	bool expressionIsValid(const char* expression = nullptr) const;

	//Randomly generate a new expression template
	char* generateExpressionTemplate() const;

	//Randomly generate a new expression template with certain conditions
	char* generateExpressionTemplate(const char* allowedOperators) const;

	//Get the expression template for an expression
	char* getExpressionTemplate(const char* expression = nullptr) const;

	//Get the expression template for an expression
	char* getExpressionTemplate(const BigNumberExpression& expression) const;

	char* generateExpressionFromTemplate(const char* expressionTemplate) const;

	//Randomly generate a new expression
	void generateExpression();

	//Generate a new expression with certain conditions
	void generateExpression(const char* allowedOperators);

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

