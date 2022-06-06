#pragma once
#include "BigNumber.h"
#include <iostream>
#include <fstream>

class BigNumberTests
{
private:
	static void OperatorGreaterThanTestTemplate(mstring testTitle, mstring textDescription,
		const BigNumber& bigNumber1, const BigNumber& bigNumber2, bool newLine, std::ostream& os);
	static void OperatorGreaterThanOrEqualsTestTemplate(mstring testTitle, mstring textDescription,
		const BigNumber& bigNumber1, const BigNumber& bigNumber2, bool newLine, std::ostream& os);

public:
	static constexpr const char* OUTPUTFILE_NAME = "BigNumber_Tests_Diagnostics.txt";

	static void ConstructorAndCopyAndAssignTests(std::ostream& os);
	static void ReadingOperatorTests();
	static void EqualsAndNotEqualsTests(std::ostream& os);
	static void OperatorGreaterThanTests(std::ostream& os);
	static void OperatorGreaterThanOrEqualsTests(std::ostream& os);
	static void OperatorLessThanTests(std::ostream& os);
	static void OperatorLessThanOrEqualsTests(std::ostream& os);

	static void OperatorSumTests(std::ostream& os);
	static void OperatorSumAndEqualsTests(std::ostream& os);
	static void OperatorMinusTests(std::ostream& os);
	static void OperatorMinusAndEqualsTests(std::ostream& os);

	static void OperatorIncrementTests(std::ostream& os);
	static void OperatorDecrementTests(std::ostream& os);

	static void OperatorMultiplyTests(std::ostream& os);
	static void OperatorMultiplyAndEqualsTests(std::ostream& os);

	static void OperatorDivideTests(std::ostream& os);
	static void OperatorDivideAndEqualsTests(std::ostream& os);

	static void OperatorPercentTests(std::ostream& os);
	static void OperatorPercentAndEqualsTests(std::ostream& os);

	//Special division and percent operator memory leak tests.
	static void OperatorDivideAndPercentMemoryLeakTests();
	//Tests from my assistants Pesho and Lubo from OOP practicum
	static void PeshoAndLuboTests(std::ostream& os);
	//Tests for copying shit correctly without access violation reading exceptions or memory leaks
	static void SpecialTests(std::ostream& os);

	//Tests for getter of number
	static void getNumberTests(std::ostream& os);
	static void getNumberRawTests(std::ostream& os);

	//Test for getNumber memory leak
	static void getNumberMemoryLeakTest();

	static void runTests(std::ostream& os);
};



