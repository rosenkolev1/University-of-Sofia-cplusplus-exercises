#include "MStringTests.h"
#include "MString.h"


void MStringTests::printingOutToConsoleTests()
{
	std::cout << "PRINT STRING TO CONSOLE TESTS:\n\n";
	mstring string1("First string");
	mstring string2;

	//Test 1
	std::cout << "Test 1\n";
	std::cout << "String 1: Expected: First string ==> " << string1 << "\n";
	std::cout << "String 2: Expected: ==> " << string2 << "\n";

	std::cout << "\n";
}

void MStringTests::big4Tests()
{
	std::cout << "BIG 4 FOR STRINGS TESTS. ALSO CONSTRUCTOR AND IMPLICIT PARSING AND SIZE GETTER TESTS:\n\n";

	//Test 1
	std::cout << "Test 1\n";

	mstring string1("First string");
	mstring string2;
	mstring string3(string1);
	char someArrayOfChars[] = "Some array of chars";
	mstring string4(someArrayOfChars);
	mstring string5(someArrayOfChars);
	mstring string6 = string1;
	mstring string7 = string2;
	mstring string8 = "Some string literal!";
	mstring string9 = someArrayOfChars;
	char string10[] = "String N.10 is stupid";
	char* dynamicString11 = new char[] {"Dynamic string N.11"};
	mstring string12;

	std::cout << "String1: Expected: First string ==> " << string1 << "\nString1 size: Expected: 12 ==> " << string1.getSize() << "\n\n";
	std::cout << "String2: Expected: ==> " << string2 << "\nString2 size: Expected: 0 ==> " << string2.getSize() << "\n\n";
	std::cout << "String3: Expected: First string ==> " << string3 << "\nString3 size: Expected: 12 ==> " << string3.getSize() << "\n\n";
	std::cout << "String4: Expected: Some array of chars ==> " << string4 << "\nString4 size: Expected: 19 ==> " << string4.getSize() << "\n\n";
	std::cout << "String5: Expected: Some array of chars ==> " << string5 << "\nString5 size: Expected: 19 ==> " << string5.getSize() << "\n\n";
	std::cout << "String6: Expected: First string ==> " << string6 << "\nString6 size: Expected: 12 ==> " << string6.getSize() << "\n\n";
	std::cout << "String7: Expected: ==> " << string7 << "\nString7 size: Expected: 0 ==> " << string7.getSize() << "\n\n";
	std::cout << "String8: Expected: Some string literal! ==> " << string8 << "\nString8 size: Expected: 20 ==> " << string8.getSize() << "\n\n";
	std::cout << "String9: Expected: Some array of chars ==> " << string9 << "\nString9 size: Expected: 19 ==> " << string9.getSize() << "\n\n";
	std::cout << "String10: Expected: String N.10 is stupid ==> " << (mstring)string10 << "\nString10 size: Expected: 21 ==> " << ((mstring)(string10)).getSize() << "\n\n";
	std::cout << "String11: Expected: Dynamic string N.11 ==> " << (mstring)dynamicString11 << "\nString11 size: Expected: 19 ==> " << ((mstring)(dynamicString11)).getSize() << "\n\n";

	//Deallocate dynamic memory
	delete[] dynamicString11;

	std::cout << "\n";
}

void MStringTests::plusOperatorTests()
{
	std::cout << "+ OPERATOR TESTS:\n\n";

	//Test 1
	std::cout << "Test 1\n";
	mstring string1 = "This is a cool ";
	mstring string2 = "string!";
	std::cout << "Testing \"" << string1 << "\" + \"" << string2 << "\" --> Expected: This is a cool string! ==> " << string1 + string2;
	std::cout << "\n\n";

	//Test 2
	std::cout << "Test 2\n";
	mstring string3 = "This is cool!";
	mstring string4 = "";
	std::cout << "Testing \"" << string3 << "\" + \"" << string4 << "\" --> Expected: This is cool! ==> " << string3 + string4;
	std::cout << "\n\n";

	//Test 3
	std::cout << "Test 3\n";
	mstring string5 = "";
	mstring string6 = "Yugi boy!!!";
	std::cout << "Testing \"" << string5 << "\" + \"" << string6 << "\" --> Expected: Yugi boy!!! ==> " << string5 + string6;
	std::cout << "\n\n";

	//Test 4
	std::cout << "Test 4\n";
	mstring string7 = "";
	mstring string8 = "";
	std::cout << "Testing \"" << string7 << "\" + \"" << string8 << "\" --> Expected: ==> " << string7 + string8;
	std::cout << "\n\n";

	//Test 5
	std::cout << "Test 5\n";
	mstring string9 = "Rosen";
	mstring string10 = " spirta a mega golqm!!!";
	std::cout << "Testing \"" << string9 << "\" + \"" << string10 << "\" --> Expected: ==> " << string9 + string10;
	std::cout << "\n\n";
}

void MStringTests::plusAndEqualsOperatorTests()
{
	std::cout << "+= OPERATOR TESTS:\n\n";

	//Test 1
	std::cout << "Test 1\n";
	mstring string1 = "This is a cool ";
	mstring stringCopy = string1;
	mstring string2 = "string!";
	string1 += string2;
	std::cout << "Testing \"" << stringCopy << "\" += \"" << string2 << "\" --> Expected: This is a cool string! ==> " << string1;
	std::cout << "\n\n";

	//Test 2
	std::cout << "Test 2\n";
	mstring string3 = "This is cool!";
	stringCopy = string3;
	mstring string4 = "";
	string3 += string4; 
	std::cout << "Testing \"" << stringCopy << "\" += \"" << string4 << "\" --> Expected: This is cool! ==> " << string3;
	std::cout << "\n\n";

	//Test 3
	std::cout << "Test 3\n";
	mstring string5 = "";
	stringCopy = string5;
	mstring string6 = "Yugi boy!!!";
	string5 += string6;
	std::cout << "Testing \"" << stringCopy << "\" += \"" << string6 << "\" --> Expected: Yugi boy!!! ==> " << string5;
	std::cout << "\n\n";

	//Test 4
	std::cout << "Test 4\n";
	mstring string7 = "";
	stringCopy = string7;
	mstring string8 = "";
	string7 += string8;
	std::cout << "Testing \"" << stringCopy << "\" += \"" << string8 << "\" --> Expected: ==> " << string7;
	std::cout << "\n\n";

	//Test 5
	std::cout << "Test 5\n";
	mstring string9 = "Rosen";
	stringCopy = string9;
	mstring string10 = " spirta a mega golqm!!!";
	string9 += string10;
	std::cout << "Testing \"" << stringCopy << "\" += \"" << string10 << "\" --> Expected: ==> " << string9;
	std::cout << "\n\n";
}

void MStringTests::equalsAndNotEqualsOperatorTests()
{
	std::cout << "== and != OPERATOR TESTS:\n\n";

	//Test 1
	std::cout << "Test 1\n";
	mstring string1 = "This is cool!";
	mstring string2 = "This is cool";
	std::cout << "Testing \"" << string1 << "\" == \"" << string2 << "\" --> Expected: FALSE ==> " << (string1 == string2 ? "TRUE" : "FALSE") << "\n";
	std::cout << "Testing \"" << string1 << "\" != \"" << string2 << "\" --> Expected: TRUE ==> " << (string1 != string2 ? "TRUE" : "FALSE") << "\n";
	std::cout << "\n\n";

	//Test 2
	std::cout << "Test 2\n";
	mstring string3 = "Something awesome";
	mstring string4 = "Something awesome";
	std::cout << "Testing \"" << string3 << "\" == \"" << string4 << "\" --> Expected: TRUE ==> " << (string3 == string4 ? "TRUE" : "FALSE") << "\n";
	std::cout << "Testing \"" << string3 << "\" != \"" << string4 << "\" --> Expected: FALSE ==> " << (string3 != string4 ? "TRUE" : "FALSE") << "\n";
	std::cout << "\n\n";

	//Test 3
	std::cout << "Test 3\n";
	mstring string5 = "";
	mstring string6 = "";
	std::cout << "Testing \"" << string5 << "\" == \"" << string4 << "\" --> Expected: TRUE ==> " << (string5 == string6 ? "TRUE" : "FALSE") << "\n";
	std::cout << "Testing \"" << string5 << "\" != \"" << string4 << "\" --> Expected: FALSE ==> " << (string5 != string6 ? "TRUE" : "FALSE") << "\n";
	std::cout << "\n\n";

	//Test 4
	std::cout << "Test 4\n";
	mstring string7 = "";
	mstring string8 = " ";
	std::cout << "Testing \"" << string7 << "\" == \"" << string8 << "\" --> Expected: FALSE ==> " << (string7 == string8 ? "TRUE" : "FALSE") << "\n";
	std::cout << "Testing \"" << string7 << "\" != \"" << string8 << "\" --> Expected: TRUE ==> " << (string7 != string8 ? "TRUE" : "FALSE") << "\n";
	std::cout << "\n\n";
}

void MStringTests::greaterThanOperatorTests()
{
	std::cout << "> OPERATOR TESTS:\n\n";

	//Test 1
	std::cout << "Test 1\n";
	mstring string1 = "This is cool!";
	mstring string2 = "This is";
	std::cout << "Testing \"" << string1 << "\" > \"" << string2 << "\" --> Expected: TRUE ==> " << (string1 > string2 ? "TRUE" : "FALSE");
	std::cout << "\n\n";

	//Test 2
	std::cout << "Test 2\n";
	mstring string3 = "This is ";
	mstring string4 = "This is";
	std::cout << "Testing \"" << string3 << "\" > \"" << string4 << "\" --> Expected: TRUE ==> " << (string3 > string4 ? "TRUE" : "FALSE");
	std::cout << "\n\n";

	//Test 3
	std::cout << "Test 3\n";
	mstring string5 = "";
	mstring string6 = "";
	std::cout << "Testing \"" << string5 << "\" > \"" << string6 << "\" --> Expected: FALSE ==> " << (string5 > string6 ? "TRUE" : "FALSE");
	std::cout << "\n\n";
}

void MStringTests::greaterThanOrEqualsOperatorTests()
{
	std::cout << ">= OPERATOR TESTS:\n\n";

	//Test 1
	std::cout << "Test 1\n";
	mstring string1 = "This is cool!";
	mstring string2 = "This is";
	std::cout << "Testing \"" << string1 << "\" >= \"" << string2 << "\" --> Expected: TRUE ==> " << (string1 >= string2 ? "TRUE" : "FALSE");
	std::cout << "\n\n";

	//Test 2
	std::cout << "Test 2\n";
	mstring string3 = "This is ";
	mstring string4 = "This is";
	std::cout << "Testing \"" << string3 << "\" >= \"" << string4 << "\" --> Expected: TRUE ==> " << (string3 >= string4 ? "TRUE" : "FALSE");
	std::cout << "\n\n";

	//Test 3
	std::cout << "Test 3\n";
	mstring string5 = "";
	mstring string6 = "";
	std::cout << "Testing \"" << string5 << "\" >= \"" << string6 << "\" --> Expected: TRUE ==> " << (string5 >= string6 ? "TRUE" : "FALSE");
	std::cout << "\n\n";
}

void MStringTests::lessThanOperatorTests()
{
	std::cout << "< OPERATOR TESTS:\n\n";

	//Test 1
	std::cout << "Test 1\n";
	mstring string1 = "This is";
	mstring string2 = "This is cool!";
	std::cout << "Testing \"" << string1 << "\" < \"" << string2 << "\" --> Expected: TRUE ==> " << (string1 < string2 ? "TRUE" : "FALSE");
	std::cout << "\n\n";

	//Test 2
	std::cout << "Test 2\n";
	mstring string3 = "This is";
	mstring string4 = "This is ";
	std::cout << "Testing \"" << string3 << "\" < \"" << string4 << "\" --> Expected: TRUE ==> " << (string3 < string4 ? "TRUE" : "FALSE");
	std::cout << "\n\n";

	//Test 3
	std::cout << "Test 3\n";
	mstring string5 = "";
	mstring string6 = "";
	std::cout << "Testing \"" << string5 << "\" < \"" << string6 << "\" --> Expected: FALSE ==> " << (string5 < string6 ? "TRUE" : "FALSE");
	std::cout << "\n\n";
}

void MStringTests::lessThanOrEqualsOperatorTests()
{
	std::cout << "<= OPERATOR TESTS:\n\n";

	//Test 1
	std::cout << "Test 1\n";
	mstring string1 = "This is";
	mstring string2 = "This is cool!";
	std::cout << "Testing \"" << string1 << "\" <= \"" << string2 << "\" --> Expected: TRUE ==> " << (string1 <= string2 ? "TRUE" : "FALSE");
	std::cout << "\n\n";

	//Test 2
	std::cout << "Test 2\n";
	mstring string3 = "This is";
	mstring string4 = "This is ";
	std::cout << "Testing \"" << string3 << "\" <= \"" << string4 << "\" --> Expected: TRUE ==> " << (string3 <= string4 ? "TRUE" : "FALSE");
	std::cout << "\n\n";

	//Test 3
	std::cout << "Test 3\n";
	mstring string5 = "";
	mstring string6 = "";
	std::cout << "Testing \"" << string5 << "\" <= \"" << string6 << "\" --> Expected: TRUE ==> " << (string5 <= string6 ? "TRUE" : "FALSE");
	std::cout << "\n\n";
}

void MStringTests::pushFrontTests()
{
	std::cout << "pushFront TESTS:\n\n";

	//Test 1
	std::cout << "Test 1\n";
	mstring string1 = "cool!";
	mstring string2 = "This is ";
	mstring expectedOutput1 = "This is cool!";
	std::cout << "Testing \"" << string1 << "\".push_front(\"" << string2 << "\") --> Expected: (" << expectedOutput1 << ", TRUE) ==> ";
	string1.push_front(string2);
	std::cout << string1 << ", " << (string1 == expectedOutput1 ? "TRUE" : "FALSE");
	std::cout << "\n\n";

	//Test 2
	std::cout << "Test 2\n";
	mstring string3 = "cool!";
	mstring string4 = "";
	mstring expectedOutput2 = "cool!";
	std::cout << "Testing \"" << string3 << "\".push_front(\"" << string4 << "\") --> Expected: (" << expectedOutput2 << ", TRUE) ==> ";
	string3.push_front(string4);
	std::cout << string3 << ", " << (string3 == expectedOutput2 ? "TRUE" : "FALSE");
	std::cout << "\n\n";
	
	//Test 3
	std::cout << "Test 3\n";
	mstring string5 = "";
	mstring string6 = "cool!";
	mstring expectedOutput3 = "cool!";
	std::cout << "Testing \"" << string5 << "\".push_front(\"" << string6 << "\") --> Expected: (" << expectedOutput3 << ", TRUE) ==> ";
	string5.push_front(string6);
	std::cout << string5 << ", " << (string5 == expectedOutput3 ? "TRUE" : "FALSE");
	std::cout << "\n\n";
	
	//Test 4
	std::cout << "Test 4\n";
	mstring string7 = "";
	mstring string8 = "";
	mstring expectedOutput4 = "";
	std::cout << "Testing \"" << string7 << "\".push_front(\"" << string8 << "\") --> Expected: (" << expectedOutput4 << ", TRUE) ==> ";
	string7.push_front(string8);
	std::cout << string7 << ", " << (string7 == expectedOutput4 ? "TRUE" : "FALSE");
	std::cout << "\n\n";

	//Test 5
	std::cout << "Test 5\n";
	mstring string9 = "!";
	const char* string10 = "Ha, gayyyy";
	mstring expectedOutput5 = "Ha, gayyyy!";
	std::cout << "Testing \"" << string9 << "\".push_front(\"" << string10 << "\") --> Expected: (" << expectedOutput5 << ", TRUE) ==> ";
	string9.push_front(string10);
	std::cout << string9 << ", " << (string9 == expectedOutput5 ? "TRUE" : "FALSE");
	std::cout << "\n\n";

	//Test 6
	std::cout << "Test 6\n";
	mstring string11 = " boyy!";
	char string12[] = "Yugi";
	mstring expectedOutput6 = "Yugi boyy!";
	std::cout << "Testing \"" << string11 << "\".push_front(\"" << string12 << "\") --> Expected: (" << expectedOutput6 << ", TRUE) ==> ";
	string11.push_front(string12);
	std::cout << string11 << ", " << (string11 == expectedOutput6 ? "TRUE" : "FALSE");
	std::cout << "\n\n";

	//Test 7
	std::cout << "Test 7\n";
	mstring string13 = "ur!";
	char string14 = 'K';
	mstring expectedOutput7 = "Kur!";
	std::cout << "Testing \"" << string13 << "\".push_front(\"" << string14 << "\") --> Expected: (" << expectedOutput7 << ", TRUE) ==> ";
	string13.push_front(string14);
	std::cout << string13 << ", " << (string13 == expectedOutput7 ? "TRUE" : "FALSE");
	std::cout << "\n\n";
}

void MStringTests::inputtingFromConsoleTests()
{
	std::cout << "READING FROM CONSOLE TESTS:\n\n";

	//Test 1
	std::cout << "Test 1\n";

	mstring string1("Some placeholder string!");
	std::cout << "Enter the string: ";
	std::cin >> string1;
	std::cout << "String1: Expected: {input from console} ==> " << string1;
	std::cout << "\n\n";
}

void MStringTests::squareBracketsOperatorTests()
{
	std::cout << "[] OPERATOR TESTS:\n\n";

	//Test 1
	std::cout << "Test 1\n";
	size_t index1 = 0;
	size_t index2 = 23;
	mstring string1("Some placeholder string!");
	std::cout << "Char at index [" << index1 << "] of string " << string1 << ": Expected: S ==> " << string1[index1] << "\n";
	std::cout << "Char at index [" << index2 << "] of string " << string1 << ": Expected: ! ==> " << string1[index2];
	std::cout << "\n\n";

	//Test 2
	std::cout << "Test 2\n";
	size_t index3 = -1;
	size_t index4 = 24;
	std::cout << "Char at index [" << index3 << "] of string " << string1 << ": Expected: " << mstring::INDEX_OUT_OF_RANGE_EXCEPTION << " ==> ";
	try
	{
		std::cout << string1[index3] << "\n";
	}
	catch (std::out_of_range e)
	{
		std::cout << e.what() << "\n";
	}
	std::cout << "Char at index [" << index4 << "] of string " << string1 << ": Expected: " << mstring::INDEX_OUT_OF_RANGE_EXCEPTION << " ==> ";
	try
	{
		std::cout << string1[index4];
	}
	catch (std::out_of_range e)
	{
		std::cout << e.what() << "\n";
	}
	std::cout << "\n\n";

	//Test 3
	std::cout << "Test 3\n";
	size_t index5 = 0;
	mstring string2;
	std::cout << "Char at index [" << index5 << "] of string " << string2 << ": Expected: ==> " << string2[index5];
	std::cout << "\n\n";
	
	std::cout << "\n\n";
}

void MStringTests::runTests()
{
	mstring firstString = "Hey string!!!";

	////IO tests for console
	//printingOutToConsoleTests();
	////inputtingFromConsoleTests();
	//
	////Big4 tests
	//big4Tests();
	//
	////Operator [] tests
	//squareBracketsOperatorTests();
	//
	////+ OperatorTests
	//plusOperatorTests();
	//
	////+= OperatorTests
	//plusAndEqualsOperatorTests();

	////== and != OperatorTests
	//equalsAndNotEqualsOperatorTests();
	//
	////> Operator Tests
	//greaterThanOperatorTests();
	//
	////>= Operator Tests
	//greaterThanOrEqualsOperatorTests();
	//
	////< Operator Tests
	//lessThanOperatorTests();
	//
	////<= Operator Tests
	//lessThanOrEqualsOperatorTests();

	//pushFront TESTS";
	pushFrontTests();
}
