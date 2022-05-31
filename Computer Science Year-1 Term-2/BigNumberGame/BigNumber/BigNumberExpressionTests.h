#pragma once
#include<iostream>
#include<fstream>

class BigNumberExpressionTests
{
public:
	static constexpr const char* OUTPUTFILE_NAME = "BigNumberExpressions_Tests_Diagnostics.txt";

	static void expressionBig4Tests(std::ostream& os);

	static void expressionIsValidTests(std::ostream& os);

	static void solveExpressionNoParenthesis_SingleNumberTests(std::ostream& os);

	static void solveExpressionNoParenthesis_AdditionAndMinusTests(std::ostream& os);

	static void solveExpressionNoParenthesis_MultiplyTests(std::ostream& os);

	static void solveExpressionNoParenthesis_DivideTests(std::ostream& os);

	static void solveExpressionNoParenthesis_PercentTests(std::ostream& os);

	static void solveExpressionNoParenthesisTests(std::ostream& os);

	static void solveExpressionParenthesis_SingleNumberTests(std::ostream& os);

	static void solveExpressionParenthesis_AdditionAndMinusTests(std::ostream& os);

	static void solveExpressionParenthesis_DivideTests(std::ostream& os);

	static void solveExpressionParenthesis_MultiplyTests(std::ostream& os);

	static void solveExpressionParenthesis_PercentTests(std::ostream& os);

	static void solveExpressionParenthesisTests(std::ostream& os);

	static void generateExpressionTemplateTests(std::ostream& os);

	static void generateExpressionTests(std::ostream& os);

	//Operator tests
	static void comparativeOperatorsTests(std::ostream& os);

	static void operatorSumTests(std::ostream& os);

	static void operatorSumAndEqualsTests(std::ostream& os);

	static void operatorMinusTests(std::ostream& os);

	static void operatorMinusAndEqualsTests(std::ostream& os);

	static void operatorMultiplyTests(std::ostream& os);

	static void operatorMultiplyAndEqualsTests(std::ostream& os);

	static void operatorDivideTests(std::ostream& os);

	static void operatorDivideAndEqualsTests(std::ostream& os);

	static void operatorPercentTests(std::ostream& os);

	static void operatorPercentAndEqualsTests(std::ostream& os);

	//Console and file writing and reading tests
	static void readFromAndWriteToConsoleTests();

	static void readFromAndWriteToFileTests(std::ostream& os);

	static void runTests(std::ostream& os);
};




