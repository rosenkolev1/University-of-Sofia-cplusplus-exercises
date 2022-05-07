#pragma once
#include "BigNumber.h"

class BigNumberTests
{
private:
	static void OperatorGreaterThanTestTemplate(const char testTitle[], const char textDescription[],
		const BigNumber& bigNumber1, const BigNumber& bigNumber2, bool newLine);
	static void OperatorGreaterThanOrEqualsTestTemplate(const char testTitle[], const char textDescription[],
		const BigNumber& bigNumber1, const BigNumber& bigNumber2, bool newLine);

public:
	static void ConstructorAndCopyAndAssignTests();
	static void ReadingOperatorTests();
	static void EqualsAndNotEqualsTests();
	static void OperatorGreaterThanTests();
	static void OperatorGreaterThanOrEqualsTests();
	static void OperatorLessThanTests();
	static void OperatorLessThanOrEqualsTests();
	static void OperatorSumTests();
	static void OperatorSumAndEqualsTests();
	static void OperatorMinusTests();
	static void OperatorMinusAndEqualsTests();
	static void OperatorMultiplyTests();
	static void OperatorMultiplyAndEqualsTests();
	static void OperatorDivideTests();
	static void OperatorDivideAndEqualsTests();
	static void OperatorPercentTests();
	static void OperatorPercentAndEqualsTests();
	//Special division and percent operator memory leak tests.
	static void OperatorDivideAndPercentMemoryLeakTests();
	//Tests from my assistants Pesho and Lubo from OOP practicum
	static void PeshoAndLuboTests();
	//Tests for copying shit correctly without access violation reading exceptions or memory leaks
	static void SpecialTests();

	//Tests for getter of number
	static void getNumberTests();
	static void getNumberRawTests();

	//Test for getNumber memory leak
	static void getNumberMemoryLeakTest();

	static void runTests();
};

