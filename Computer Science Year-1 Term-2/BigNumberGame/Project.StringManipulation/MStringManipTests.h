#pragma once
#include "MStringManip.h"

class MStringManipTests
{
public:
	//Helper functions for doing tests
	static void printOutResultStringsFromSplitStringTest(const mstring* strings, size_t numberOfStrings);

	static void printOutStringsFromArray(const mstring* strings, size_t numberOfStrings);

	//Actual tests functions
	static void splitByCharTests();

	static void splitByStringTests();

	static void splitStringManyTests();

	static void stringContainsTests();

	static void replaceAllTests();

	static void replaceFirstTests();

	static void replaceFromTests();

	static void findIndexTests();

	static void findIndexLastTests();

	static void arraysOfStringsAreEqualTests();

	static void getUniqueTests();

	static void getFromTests();

	static void getReversedTests();

	static void countOfTests();

	static void countOfManyTests();

	static void parseToStringTests();

	static void parseToLongTests();

	static void runTests();
};

