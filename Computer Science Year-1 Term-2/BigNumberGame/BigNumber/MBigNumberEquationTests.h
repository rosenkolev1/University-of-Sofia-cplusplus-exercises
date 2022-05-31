#pragma once
#include <iostream>

class MBigNumberEquationTests
{
public:
	static constexpr const char* OUTPUTFILE_NAME = "BugNumberEquation_Tests_Diagnostics.txt";

	static void equationBig4Tests(std::ostream& os);

	static void equationIsValidTests(std::ostream& os);

	static void solveEquationTests(std::ostream& os);

	static void generateEquationTests(std::ostream& os);

	static void readFromAndWriteToConsoleTests();

	static void readFromAndWriteToFileTests(std::ostream& os);

	static void runTests(std::ostream& os);
};

