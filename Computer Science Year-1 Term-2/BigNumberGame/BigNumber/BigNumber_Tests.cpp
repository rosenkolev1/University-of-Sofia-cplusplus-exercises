// BigNumber_Tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BigNumber.h"
#include "BigNumberDivisionResult.h"

void ConstructorAndCopyAndAssignTests()
{
    int someNumberInt = 5678;
    char someNumberChar[] = "1234";
    BigNumber defaultBigNumber = BigNumber();
    BigNumber someBigNumberInt = BigNumber(someNumberInt);
    BigNumber someBigNumberChar = BigNumber(someNumberChar);
    BigNumber someOtherBigNumber = BigNumber("-1");
    BigNumber someOtheBigNumberZero = BigNumber("0");

    //OLD
    std::cout << "Initial values: TESTS FOR NON-COPY CONSTRUCTORS" << std::endl;
    std::cout << "defaultBigNumber: "; defaultBigNumber.printOutNumber();
    std::cout << "someBigNumberInt: "; someBigNumberInt.printOutNumber();
    std::cout << "someBigNumberChar: "; someBigNumberChar.printOutNumber();
    std::cout << "someOtherBigNumber: "; someOtherBigNumber.printOutNumber();
    std::cout << "someOtheBigNumberZero: "; someOtheBigNumberZero.printOutNumber();

    //TO BE CONTINUED
    //NEW
    std::cout << std::endl << "New Values: TESTS FOR ASSIGNMENT AND COPY OPERATORS AND CONSTRUCTOR" << std::endl;
    std::cout << "TESTING -> defaultBigNumber = someNumberInt\n";
    //Calls constructor for with someNumberInt as long long int parameter
    defaultBigNumber = someNumberInt;
    std::cout << "defaultBigNumber: "; defaultBigNumber.printOutNumber();

    std::cout << "TESTING -> BigNumber copyOfBigNumberChar = BigNumber(someBigNumberChar)\n";
    BigNumber copyOfBigNumberChar = BigNumber(someBigNumberChar);
    std::cout << "copyOfBigNumberChar: "; copyOfBigNumberChar.printOutNumber();

    std::cout << "TESTING -> someBigNumberInt = someBigNumberChar\n";
    someBigNumberInt = someBigNumberChar;
    std::cout << "someBigNumberInt: "; someBigNumberInt.printOutNumber();

    std::cout << "TESTING -> someBigNumberInt = someBigNumberInt\n";
    someBigNumberInt = someBigNumberInt;
    std::cout << "someBigNumberInt: "; someBigNumberInt.printOutNumber();
}

//TODO: READING TEST IS INBETWEEN
void ReadingOperatorTests()
{
    std::cout << std::endl << "TESTS FOR READING A NUMBER FROM CONSOLE:\n" << std::endl;
    std::cout << "\">>\" Operator TESTS: " << std::endl << std::endl;
    BigNumber someBigNumberToRead = BigNumber();
    std::cout << "Enter a BigNumber here: ";
    std::cin >> someBigNumberToRead;
    std::cout << "Testing \">>\" operator: (Expected: {same input from console}): ";
    someBigNumberToRead.printOutNumber();
    std::cout << std::endl << std::endl;
}

void EqualsAndNotEqualsTests()
{
    int someNumberInt = 5678;
    char someNumberChar[] = "1234";
    BigNumber defaultBigNumber = BigNumber();
    BigNumber someBigNumberInt = BigNumber(someNumberInt);
    BigNumber someBigNumberChar = BigNumber(someNumberChar);
    BigNumber someOtherBigNumber = BigNumber("-1");
    BigNumber someOtheBigNumberZero = BigNumber("0");

    //NEW
    defaultBigNumber = someNumberInt;
    BigNumber copyOfBigNumberChar = BigNumber(someBigNumberChar);
    someBigNumberInt = someBigNumberChar;

    //== Operator tests
    std::cout << "\"==\" Operator TESTS: " << std::endl << std::endl;

    std::cout << "Testing \"==\" operator (defaultBigNumber == someBigNumberInt): (Expected: FALSE): " <<
        (defaultBigNumber == someBigNumberInt ? "TRUE" : "FALSE") << std::endl;
    std::cout << std::endl;

    std::cout << "Testing \"==\" operator (someBigNumberChar == someBigNumberInt): (Expected: TRUE): " <<
        (someBigNumberChar == someBigNumberInt ? "TRUE" : "FALSE") << std::endl;
    std::cout << std::endl;

    std::cout << "Testing \"==\" operator (someBigNumberChar == someBigNumberChar): (Expected: TRUE): " <<
        (someBigNumberChar == someBigNumberChar ? "TRUE" : "FALSE") << std::endl;
    std::cout << std::endl;

    //!= Operator tests
    std::cout << "\"!=\" Operator TESTS: " << std::endl;

    std::cout << "Testing \"!=\" operator (defaultBigNumber != someBigNumberInt): (Expected: TRUE): " <<
        (defaultBigNumber != someBigNumberInt ? "TRUE" : "FALSE") << std::endl;
    std::cout << std::endl;

    std::cout << "Testing \"!=\" operator (someBigNumberChar != someBigNumberInt): (Expected: FALSE): " <<
        (someBigNumberChar != someBigNumberInt ? "TRUE" : "FALSE") << std::endl;
    std::cout << std::endl;

    std::cout << "Testing \"!=\" operator (someBigNumberChar != someBigNumberChar): (Expected: FALSE): " <<
        (someBigNumberChar != someBigNumberChar ? "TRUE" : "FALSE") << std::endl;
    std::cout << std::endl;
}

void OperatorGreaterThanTestTemplate(const char testTitle[], const char textDescription[],
    const BigNumber& bigNumber1, const BigNumber& bigNumber2, bool newLine)
{
    if (testTitle != NULL) std::cout << testTitle << std::endl;
    std::cout << textDescription <<
        (bigNumber1 > bigNumber2 ? "TRUE" : "FALSE") << std::endl;
    if (newLine) std::cout << std::endl;
}

void OperatorGreaterThanOrEqualsTestTemplate(const char testTitle[], const char textDescription[],
    const BigNumber& bigNumber1, const BigNumber& bigNumber2, bool newLine)
{
    if (testTitle != NULL) std::cout << testTitle << std::endl;
    std::cout << textDescription <<
        (bigNumber1 >= bigNumber2 ? "TRUE" : "FALSE") << std::endl;
    if (newLine) std::cout << std::endl;
}

void OperatorGreaterThanTests()
{
    // > Operator tests
    std::cout << "\">\" Operator TESTS: " << std::endl << std::endl;

    //INIT Phase

    BigNumber lesserBigNumber1 = BigNumber(5050);
    BigNumber biggerBigNumber1 = BigNumber(65000);
    //
    BigNumber lesserBigNumber2 = BigNumber(-67890);
    BigNumber biggerBigNumber2 = BigNumber(-6789);
    //
    BigNumber lesserBigNumber3 = BigNumber(-67890);
    BigNumber biggerBigNumber3 = BigNumber(1);
    //
    BigNumber lesserBigNumber4 = BigNumber(-69);
    BigNumber biggerBigNumber4 = BigNumber(10);
    //
    BigNumber lesserBigNumber5 = BigNumber(1023);
    BigNumber biggerBigNumber5 = BigNumber(1030);
    //
    BigNumber lesserBigNumber6 = BigNumber(-4010);
    BigNumber biggerBigNumber6 = BigNumber(-4000);
    //
    BigNumber lesserBigNumber7 = BigNumber();
    BigNumber biggerBigNumber7 = BigNumber(100);
    //
    BigNumber lesserBigNumber8 = BigNumber(-100);
    BigNumber biggerBigNumber8 = BigNumber();
    //
    BigNumber lesserBigNumber9 = BigNumber();
    BigNumber biggerBigNumber9 = BigNumber();
    //
    BigNumber lesserBigNumber10 = BigNumber(2456);

    //TEST Phase

    //BigNumber1
    OperatorGreaterThanTestTemplate("BigNumber1 tests: ",
        "Testing \">\" operator -> (5050 > 65000). Expected: False, because sizes are different:",
        lesserBigNumber1, biggerBigNumber1, false);
    OperatorGreaterThanTestTemplate(NULL,
        "REVERSE: Testing \">\" operator -> (65000 > 5050). Expected: True, because sizes are different:",
        biggerBigNumber1, lesserBigNumber1, true);

    //BigNumber2
    OperatorGreaterThanTestTemplate("BigNumber2 tests: ",
        "Testing \">\" operator -> (-67890 > -6789). Expected: False, because sizes are different:",
        lesserBigNumber2, biggerBigNumber2, false);
    OperatorGreaterThanTestTemplate(NULL,
        "REVERSE: Testing \">\" operator -> (-6789 > -67890). Expected: True, because sizes are different:",
        biggerBigNumber2, lesserBigNumber2, true);

    //BigNumber3
    OperatorGreaterThanTestTemplate("BigNumber3 tests: ",
        "Testing \">\" operator -> (-67890 > 1). Expected: False, because signs are different:",
        lesserBigNumber3, biggerBigNumber3, false);
    OperatorGreaterThanTestTemplate(NULL,
        "REVERSE: Testing \">\" operator -> (1 > -67890). Expected: True, because signs are different:",
        biggerBigNumber3, lesserBigNumber3, true);

    //BigNumber4
    OperatorGreaterThanTestTemplate("BigNumber4 tests: ",
        "Testing \">\" operator -> (-69 > 10). Expected: False, because signs are different:",
        lesserBigNumber4, biggerBigNumber4, false);
    OperatorGreaterThanTestTemplate(NULL,
        "REVERSE: Testing \">\" operator -> (10 > -69). Expected: True, because signs are different:",
        biggerBigNumber4, lesserBigNumber4, true);

    //BigNumber5
    OperatorGreaterThanTestTemplate("BigNumber5 tests: ",
        "Testing \">\" operator -> (1023 > 1030). Expected: False, because first number is smaller:",
        lesserBigNumber5, biggerBigNumber5, false);
    OperatorGreaterThanTestTemplate(NULL,
        "REVERSE: Testing \">\" operator -> (1030 > 1023). Expected: True, because first number is bigger:",
        biggerBigNumber5, lesserBigNumber5, true);

    //BigNumber6
    OperatorGreaterThanTestTemplate("BigNumber6 tests: ",
        "Testing \">\" operator -> (-4010 > -4000). Expected: False, because first number is smaller:",
        lesserBigNumber6, biggerBigNumber6, false);
    OperatorGreaterThanTestTemplate(NULL,
        "REVERSE: Testing \">\" operator -> (-4000 > -4010). Expected: True, because first number is bigger:",
        biggerBigNumber6, lesserBigNumber6, true);

    //BigNumber7
    OperatorGreaterThanTestTemplate("BigNumber7 tests: ",
        "Testing \">\" operator -> (0 > 100). Expected: False, because first number is 0 and second is positive:",
        lesserBigNumber7, biggerBigNumber7, false);
    OperatorGreaterThanTestTemplate(NULL,
        "REVERSE: Testing \">\" operator -> (100 > 0). Expected: True, because second number is 0 and first is positive:",
        biggerBigNumber7, lesserBigNumber7, true);

    //BigNumber8
    OperatorGreaterThanTestTemplate("BigNumber8 tests: ",
        "Testing \">\" operator -> (-100 > 0). Expected: False, because second number is 0 and first is negative:",
        lesserBigNumber8, biggerBigNumber8, false);
    OperatorGreaterThanTestTemplate(NULL,
        "REVERSE: Testing \">\" operator -> (0 > -100). Expected: True, because first number is 0 and second is negative:",
        biggerBigNumber8, lesserBigNumber8, true);

    //BigNumber9
    OperatorGreaterThanTestTemplate("BigNumber9 tests: ",
        "Testing \">\" operator -> (0 > 0). Expected: False, because both numbers are 0:",
        lesserBigNumber9, biggerBigNumber9, true);

    //BigNumber10
    OperatorGreaterThanTestTemplate("BigNumber10 tests: ",
        "Testing \">\" operator -> (2456 > 2456). Expected: False, because both numbers are equal:",
        lesserBigNumber10, lesserBigNumber10, true);
}

void OperatorGreaterThanOrEqualsTests()
{
    // > Operator tests
    std::cout << "\">=\" Operator TESTS: " << std::endl << std::endl;

    //INIT Phase

    BigNumber lesserBigNumber1 = BigNumber(5050);
    BigNumber biggerBigNumber1 = BigNumber(65000);
    //
    BigNumber lesserBigNumber2 = BigNumber(-67890);
    BigNumber biggerBigNumber2 = BigNumber(-6789);
    //
    BigNumber lesserBigNumber3 = BigNumber(-67890);
    BigNumber biggerBigNumber3 = BigNumber(1);
    //
    BigNumber lesserBigNumber4 = BigNumber(-69);
    BigNumber biggerBigNumber4 = BigNumber(10);
    //
    BigNumber lesserBigNumber5 = BigNumber(1023);
    BigNumber biggerBigNumber5 = BigNumber(1030);
    //
    BigNumber lesserBigNumber6 = BigNumber(-4010);
    BigNumber biggerBigNumber6 = BigNumber(-4000);
    //
    BigNumber lesserBigNumber7 = BigNumber();
    BigNumber biggerBigNumber7 = BigNumber(100);
    //
    BigNumber lesserBigNumber8 = BigNumber(-100);
    BigNumber biggerBigNumber8 = BigNumber();
    //
    BigNumber lesserBigNumber9 = BigNumber();
    BigNumber biggerBigNumber9 = BigNumber();
    //
    BigNumber lesserBigNumber10 = BigNumber(2456);

    //TEST Phase

    //BigNumber1
    OperatorGreaterThanOrEqualsTestTemplate("BigNumber1 tests: ",
        "Testing \">=\" operator -> (5050 >= 65000). Expected: False, because sizes are different:",
        lesserBigNumber1, biggerBigNumber1, false);
    OperatorGreaterThanOrEqualsTestTemplate(NULL,
        "REVERSE: Testing \">=\" operator -> (65000 >= 5050). Expected: True, because sizes are different:",
        biggerBigNumber1, lesserBigNumber1, true);

    //BigNumber2
    OperatorGreaterThanOrEqualsTestTemplate("BigNumber2 tests: ",
        "Testing \">=\" operator -> (-67890 >= -6789). Expected: False, because sizes are different:",
        lesserBigNumber2, biggerBigNumber2, false);
    OperatorGreaterThanOrEqualsTestTemplate(NULL,
        "REVERSE: Testing \">=\" operator -> (-6789 >= -67890). Expected: True, because sizes are different:",
        biggerBigNumber2, lesserBigNumber2, true);

    //BigNumber3
    OperatorGreaterThanOrEqualsTestTemplate("BigNumber3 tests: ",
        "Testing \">=\" operator -> (-67890 >= 1). Expected: False, because signs are different:",
        lesserBigNumber3, biggerBigNumber3, false);
    OperatorGreaterThanOrEqualsTestTemplate(NULL,
        "REVERSE: Testing \">=\" operator -> (1 >= -67890). Expected: True, because signs are different:",
        biggerBigNumber3, lesserBigNumber3, true);

    //BigNumber4
    OperatorGreaterThanOrEqualsTestTemplate("BigNumber4 tests: ",
        "Testing \">=\" operator -> (-69 >= 10). Expected: False, because signs are different:",
        lesserBigNumber4, biggerBigNumber4, false);
    OperatorGreaterThanOrEqualsTestTemplate(NULL,
        "REVERSE: Testing \">=\" operator -> (10 >= -69). Expected: True, because signs are different:",
        biggerBigNumber4, lesserBigNumber4, true);

    //BigNumber5
    OperatorGreaterThanOrEqualsTestTemplate("BigNumber5 tests: ",
        "Testing \">=\" operator -> (1023 >= 1030). Expected: False, because first number is smaller:",
        lesserBigNumber5, biggerBigNumber5, false);
    OperatorGreaterThanOrEqualsTestTemplate(NULL,
        "REVERSE: Testing \">=\" operator -> (1030 >= 1023). Expected: True, because first number is bigger:",
        biggerBigNumber5, lesserBigNumber5, true);

    //BigNumber6
    OperatorGreaterThanOrEqualsTestTemplate("BigNumber6 tests: ",
        "Testing \">=\" operator -> (-4010 >= -4000). Expected: False, because first number is smaller:",
        lesserBigNumber6, biggerBigNumber6, false);
    OperatorGreaterThanOrEqualsTestTemplate(NULL,
        "REVERSE: Testing \">=\" operator -> (-4000 >= -4010). Expected: True, because first number is bigger:",
        biggerBigNumber6, lesserBigNumber6, true);

    //BigNumber7
    OperatorGreaterThanOrEqualsTestTemplate("BigNumber7 tests: ",
        "Testing \">=\" operator -> (0 >= 100). Expected: False, because first number is 0 and second is positive:",
        lesserBigNumber7, biggerBigNumber7, false);
    OperatorGreaterThanOrEqualsTestTemplate(NULL,
        "REVERSE: Testing \">=\" operator -> (100 >= 0). Expected: True, because second number is 0 and first is positive:",
        biggerBigNumber7, lesserBigNumber7, true);

    //BigNumber8
    OperatorGreaterThanOrEqualsTestTemplate("BigNumber8 tests: ",
        "Testing \">=\" operator -> (-100 >= 0). Expected: False, because second number is 0 and first is negative:",
        lesserBigNumber8, biggerBigNumber8, false);
    OperatorGreaterThanOrEqualsTestTemplate(NULL,
        "REVERSE: Testing \">=\" operator -> (0 >= -100). Expected: True, because first number is 0 and second is negative:",
        biggerBigNumber8, lesserBigNumber8, true);

    //BigNumber9
    OperatorGreaterThanOrEqualsTestTemplate("BigNumber9 tests: ",
        "Testing \">=\" operator -> (0 >= 0). Expected: True, because both numbers are equal:",
        lesserBigNumber9, biggerBigNumber9, true);

    //BigNumber10
    OperatorGreaterThanOrEqualsTestTemplate("BigNumber10 tests: ",
        "Testing \">=\" operator -> (2456 >= 2456). Expected: True, because both numbers are equal:",
        lesserBigNumber10, lesserBigNumber10, true);
}

void OperatorLessThanTests()
{
    std::cout << "LESS THAN TESTS:" << std::endl;
    std::cout << "Testing \"<\" operator -> (100 < -130). Expected: False, because 100 > -130:" <<
        (BigNumber(100) < BigNumber(-130) ? "TRUE" : "FALSE") << std::endl;
    std::cout << "Testing \"<\" operator -> (110 < 110). Expected: False, the numbers are equal:" <<
        (BigNumber(110) < BigNumber(110) ? "TRUE" : "FALSE") << std::endl;
    std::cout << "Testing \"<\" operator -> (0 < 0). Expected: False, the numbers are equal:" <<
        (BigNumber() < BigNumber() ? "TRUE" : "FALSE") << std::endl;

    std::cout << std::endl;
}

void OperatorLessThanOrEqualsTests()
{
    std::cout << "\"<=\" Operator TESTS:" << std::endl;
    std::cout << "Testing \"<=\" operator -> (100 <= -130). Expected: False, because 100 > -130:" <<
        (BigNumber(100) <= BigNumber(-130) ? "TRUE" : "FALSE") << std::endl;
    std::cout << "Testing \"<=\" operator -> (110 <= 110). Expected: True, the numbers are equal:" <<
        (BigNumber(110) <= BigNumber(110) ? "TRUE" : "FALSE") << std::endl;
    std::cout << "Testing \"<=\" operator -> (0 <= 0). Expected: True, the numbers are equal:" <<
        (BigNumber() <= BigNumber() ? "TRUE" : "FALSE") << std::endl;

    std::cout << std::endl;
}

void OperatorSumTests()
{
    // + Operator tests
    std::cout << "\"+\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    BigNumber number1 = BigNumber(1);
    BigNumber number2 = BigNumber(2);
    BigNumber number3 = number1 + number2;

    std::cout << "TEST 1:" << std::endl;
    std::cout << "Testing \"+\" operator -> (1 + 2). Expected: 3: ";
    number3.printOutNumber();
    std::cout << std::endl;

    //TEST 2
    BigNumber number4 = BigNumber(9);
    BigNumber number5 = BigNumber(1);
    BigNumber number6 = number4 + number5;

    std::cout << "TEST 2:" << std::endl;
    std::cout << "Testing \"+\" operator -> (9 + 1). Expected: 10: ";
    number6.printOutNumber();
    std::cout << std::endl;

    //TEST 3
    BigNumber number7 = BigNumber(9999999);
    BigNumber number8 = BigNumber(78);
    BigNumber number9 = number7 + number8;
    std::cout << "TEST 3:" << std::endl;
    std::cout << "Testing \"+\" operator -> (9999999 + 78). Expected: 10 000 077: ";
    number9.printOutNumber();
    std::cout << std::endl;

    //TEST 4
    BigNumber number10 = BigNumber();
    BigNumber number11 = BigNumber(-79);
    BigNumber number12 = number10 + number11;
    std::cout << "TEST 4:" << std::endl;
    std::cout << "Testing \"+\" operator -> (0 + (-79)). Expected: -79: ";
    number12.printOutNumber();
    std::cout << std::endl;

    //TEST 5
    BigNumber number13 = BigNumber(-101);
    BigNumber number14 = BigNumber();
    BigNumber number15 = number13 + number14;
    std::cout << "TEST 5:" << std::endl;
    std::cout << "Testing \"+\" operator -> ((-101) + 0). Expected: -101: ";
    number15.printOutNumber();
    std::cout << std::endl;

    //TEST 6
    BigNumber number16 = BigNumber(-101);
    BigNumber number17 = BigNumber(-5);
    BigNumber number18 = number16 + number17;
    std::cout << "TEST 6:" << std::endl;
    std::cout << "Testing \"+\" operator -> ((-101) + (-5)). Expected: -106: ";
    number18.printOutNumber();
    std::cout << std::endl;

    //TEST 7
    BigNumber number19 = BigNumber(-101);
    BigNumber number20 = BigNumber(-99);
    BigNumber number21 = number19 + number20;
    std::cout << "TEST 7:" << std::endl;
    std::cout << "Testing \"+\" operator -> ((-101) + (-99)). Expected: -200: ";
    number21.printOutNumber();
    std::cout << std::endl;

    //TEST 8
    BigNumber number22 = BigNumber(-991);
    BigNumber number23 = BigNumber(-99);
    BigNumber number24 = number22 + number23;
    std::cout << "TEST 7:" << std::endl;
    std::cout << "Testing \"+\" operator -> ((-991) + (-99)). Expected: -1090: ";
    number24.printOutNumber();
    std::cout << std::endl;

    //TEST 9
    BigNumber number25 = BigNumber(991);
    BigNumber number26 = BigNumber(-99);
    BigNumber number27 = number25 + number26;
    std::cout << "TEST 9:" << std::endl;
    std::cout << "Testing \"+\" operator -> (991 + (-99)). Expected: 892: ";
    number27.printOutNumber();
    std::cout << std::endl;

    //TEST 10
    BigNumber number28 = BigNumber(-100100098);
    BigNumber number29 = BigNumber(65699);
    BigNumber number30 = number28 + number29;
    std::cout << "TEST 10:" << std::endl;
    std::cout << "Testing \"+\" operator -> (-100100098 + 65699). Expected: -100,034,399: ";
    number30.printOutNumber();
    std::cout << std::endl;
}

void OperatorSumAndEqualsTests()
{
    // + Operator tests
    std::cout << "\"+=\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    BigNumber number1 = BigNumber(1);
    BigNumber number2 = BigNumber(2);
    number1 += number2;

    std::cout << "TEST 1:" << std::endl;
    std::cout << "Testing \"+=\" operator -> (1 + 2). Expected: 3: ";
    number1.printOutNumber();
    std::cout << std::endl;

    //TEST 2
    BigNumber number4 = BigNumber(9);
    BigNumber number5 = BigNumber(1);
    number4 += number5;

    std::cout << "TEST 2:" << std::endl;
    std::cout << "Testing \"+=\" operator -> (9 + 1). Expected: 10: ";
    number4.printOutNumber();
    std::cout << std::endl;

    //TEST 3
    BigNumber number7 = BigNumber(9999999);
    BigNumber number8 = BigNumber(78);
    number7 += number8;
    std::cout << "TEST 3:" << std::endl;
    std::cout << "Testing \"+=\" operator -> (9999999 + 78). Expected: 10 000 077: ";
    number7.printOutNumber();
    std::cout << std::endl;

    //TEST 4
    BigNumber number10 = BigNumber();
    BigNumber number11 = BigNumber(-79);
    number10 += number11;
    std::cout << "TEST 4:" << std::endl;
    std::cout << "Testing \"+=\" operator -> (0 + (-79)). Expected: -79: ";
    number10.printOutNumber();
    std::cout << std::endl;

    ////TEST 5
    BigNumber number13 = BigNumber(-101);
    BigNumber number14 = BigNumber();
    number13 += number14;
    std::cout << "TEST 5:" << std::endl;
    std::cout << "Testing \"+=\" operator -> ((-101) + 0). Expected: -101: ";
    number13.printOutNumber();
    std::cout << std::endl;

    //TEST 6
    BigNumber number16 = BigNumber(-101);
    BigNumber number17 = BigNumber(-5);
    number16 += number17;
    std::cout << "TEST 6:" << std::endl;
    std::cout << "Testing \"+=\" operator -> ((-101) + (-5)). Expected: -106: ";
    number16.printOutNumber();
    std::cout << std::endl;

    //TEST 7
    BigNumber number19 = BigNumber(-101);
    BigNumber number20 = BigNumber(-99);
    number19 += number20;
    std::cout << "TEST 7:" << std::endl;
    std::cout << "Testing \"+=\" operator -> ((-101) + (-99)). Expected: -200: ";
    number19.printOutNumber();
    std::cout << std::endl;

    //TEST 8
    BigNumber number22 = BigNumber(-991);
    BigNumber number23 = BigNumber(-99);
    number22 += number23;
    std::cout << "TEST 7:" << std::endl;
    std::cout << "Testing \"+=\" operator -> ((-991) + (-99)). Expected: -1090: ";
    number22.printOutNumber();
    std::cout << std::endl;

    //TEST 9
    BigNumber number25 = BigNumber(991);
    BigNumber number26 = BigNumber(-99);
    number25 += number26;
    std::cout << "TEST 9:" << std::endl;
    std::cout << "Testing \"+=\" operator -> (991 + (-99)). Expected: 892: ";
    number25.printOutNumber();
    std::cout << std::endl;

    //TEST 10
    BigNumber number28 = BigNumber(-100100098);
    BigNumber number29 = BigNumber(65699);
    number28 += number29;
    std::cout << "TEST 10:" << std::endl;
    std::cout << "Testing \"+=\" operator -> (-100100098 + 65699). Expected: -100,034,399: ";
    number28.printOutNumber();
    std::cout << std::endl;
}

void OperatorMinusTests()
{
    // - Operator tests
    std::cout << "\"-\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    BigNumber number1 = BigNumber(3);
    BigNumber number2 = BigNumber(2);
    BigNumber number3 = number1 - number2;

    std::cout << "TEST 1:" << std::endl;
    std::cout << "Testing \"-\" operator -> (3 - 2). Expected: 1: ";
    number3.printOutNumber();
    std::cout << std::endl;

    //TEST 2
    BigNumber number4 = BigNumber(1345);
    BigNumber number5 = BigNumber(1234);
    BigNumber number6 = number4 - number5;

    std::cout << "TEST 2:" << std::endl;
    std::cout << "Testing \"-\" operator -> (1345 - 1234). Expected: 111: ";
    number6.printOutNumber();
    std::cout << std::endl;

    //TEST 3
    BigNumber number7 = BigNumber(1234);
    BigNumber number8 = BigNumber(1345);
    BigNumber number9 = number7 - number8;

    std::cout << "TEST 3:" << std::endl;
    std::cout << "Testing \"-\" operator -> (1234 - 1345). Expected: -111: ";
    number9.printOutNumber();
    std::cout << std::endl;

    //TEST 4
    BigNumber number10 = BigNumber(1234);
    BigNumber number11 = BigNumber(13450);
    BigNumber number12 = number10 - number11;

    std::cout << "TEST 4:" << std::endl;
    std::cout << "Testing \"-\" operator -> (1234 - 13450). Expected: -12 216: ";
    number12.printOutNumber();
    std::cout << std::endl;

    //TEST 5
    BigNumber number13 = BigNumber(-1234);
    BigNumber number14 = BigNumber(-1230);
    BigNumber number15 = number13 - number14;

    std::cout << "TEST 5:" << std::endl;
    std::cout << "Testing \"-\" operator -> (-1234 - -1230). Expected: -4: ";
    number15.printOutNumber();
    std::cout << std::endl;

    //TEST 6
    BigNumber number16 = BigNumber(-1234);
    BigNumber number17 = BigNumber(-13457);
    BigNumber number18 = number16 - number17;

    std::cout << "TEST 6:" << std::endl;
    std::cout << "Testing \"-\" operator -> (-1234 - -13457). Expected: 12 223: ";
    number18.printOutNumber();
    std::cout << std::endl;

    //TEST 7
    BigNumber number19 = BigNumber(-10101);
    BigNumber number20 = BigNumber(-99);
    BigNumber number21 = number19 - number20;

    std::cout << "TEST 7:" << std::endl;
    std::cout << "Testing \"-\" operator -> (-10101 - -99). Expected: -10 002: ";
    number21.printOutNumber();
    std::cout << std::endl;

    //TEST 8
    BigNumber number22 = BigNumber(-10001000000);
    BigNumber number23 = BigNumber(-9956123);
    BigNumber number24 = number22 - number23;

    std::cout << "TEST 8:" << std::endl;
    std::cout << "Testing \"-\" operator -> (-10001000000 - -9956123). Expected: -9,991,043,877: ";
    number24.printOutNumber();
    std::cout << std::endl;

    //TEST 9
    BigNumber number25 = BigNumber(-9956123);
    BigNumber number26 = BigNumber(-10001000000);
    BigNumber number27 = number25 - number26;

    std::cout << "TEST 9:" << std::endl;
    std::cout << "Testing \"-\" operator -> (-9956123 - -10001000000). Expected: 9,991,043,877: ";
    number27.printOutNumber();
    std::cout << std::endl;

    //TEST 9
    BigNumber number28 = BigNumber(-9956123);
    BigNumber number29 = BigNumber();
    BigNumber number30 = number28 - number29;

    std::cout << "TEST 9:" << std::endl;
    std::cout << "Testing \"-\" operator -> (-9956123 - 0). Expected: -9956123: ";
    number30.printOutNumber();
    std::cout << std::endl;

    //TEST 10
    BigNumber number31 = BigNumber();
    BigNumber number32 = BigNumber(156);
    BigNumber number33 = number31 - number32;

    std::cout << "TEST 10:" << std::endl;
    std::cout << "Testing \"-\" operator -> (0 - 156). Expected: -156: ";
    number33.printOutNumber();
    std::cout << std::endl;

    //TEST 11
    BigNumber number34 = BigNumber();
    BigNumber number35 = BigNumber();
    BigNumber number36 = number34 - number35;

    std::cout << "TEST 11:" << std::endl;
    std::cout << "Testing \"-\" operator -> (0 - 0). Expected: 0: ";
    number36.printOutNumber();
    std::cout << std::endl;

    //TEST 12
    BigNumber number37 = BigNumber(15678);
    BigNumber number38 = BigNumber(-979900);
    BigNumber number39 = number37 - number38;

    std::cout << "TEST 12:" << std::endl;
    std::cout << "Testing \"-\" operator -> (15678 - -979900). Expected: 995,578: ";
    number39.printOutNumber();
    std::cout << std::endl;

    //TEST 13
    BigNumber number40 = BigNumber(-9560);
    BigNumber number41 = BigNumber(11256);
    BigNumber number42 = number40 - number41;

    std::cout << "TEST 13:" << std::endl;
    std::cout << "Testing \"-\" operator -> (-9560 - 11256). Expected: -20,816: ";
    number42.printOutNumber();
    std::cout << std::endl;
}

void OperatorMinusAndEqualsTests()
{
    // - Operator tests
    std::cout << "\"-=\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    BigNumber number1 = BigNumber(3);
    BigNumber number2 = BigNumber(2);
    number1 -= number2;

    std::cout << "TEST 1:" << std::endl;
    std::cout << "Testing \"-=\" operator -> (3 - 2). Expected: 1: ";
    number1.printOutNumber();
    std::cout << std::endl;

    //TEST 2
    BigNumber number4 = BigNumber(1345);
    BigNumber number5 = BigNumber(1234);
    number4 -= number5;

    std::cout << "TEST 2:" << std::endl;
    std::cout << "Testing \"-=\" operator -> (1345 - 1234). Expected: 111: ";
    number4.printOutNumber();
    std::cout << std::endl;

    //TEST 3
    BigNumber number7 = BigNumber(1234);
    BigNumber number8 = BigNumber(1345);
    number7 -= number8;

    std::cout << "TEST 3:" << std::endl;
    std::cout << "Testing \"-=\" operator -> (1234 - 1345). Expected: -111: ";
    number7.printOutNumber();
    std::cout << std::endl;

    //TEST 4
    BigNumber number10 = BigNumber(1234);
    BigNumber number11 = BigNumber(13450);
    number10 -= number11;

    std::cout << "TEST 4:" << std::endl;
    std::cout << "Testing \"-=\" operator -> (1234 - 13450). Expected: -12 216: ";
    number10.printOutNumber();
    std::cout << std::endl;

    //TEST 5
    BigNumber number13 = BigNumber(-1234);
    BigNumber number14 = BigNumber(-1230);
    number13 -= number14;

    std::cout << "TEST 5:" << std::endl;
    std::cout << "Testing \"-=\" operator -> (-1234 - -1230). Expected: -4: ";
    number13.printOutNumber();
    std::cout << std::endl;

    //TEST 6
    BigNumber number16 = BigNumber(-1234);
    BigNumber number17 = BigNumber(-13457);
    number16 -= number17;

    std::cout << "TEST 6:" << std::endl;
    std::cout << "Testing \"-=\" operator -> (-1234 - -13457). Expected: 12 223: ";
    number16.printOutNumber();
    std::cout << std::endl;

    //TEST 7
    BigNumber number19 = BigNumber(-10101);
    BigNumber number20 = BigNumber(-99);
    number19 -= number20;

    std::cout << "TEST 7:" << std::endl;
    std::cout << "Testing \"-=\" operator -> (-10101 - -99). Expected: -10 002: ";
    number19.printOutNumber();
    std::cout << std::endl;

    //TEST 8
    BigNumber number22 = BigNumber(-10001000000);
    BigNumber number23 = BigNumber(-9956123);
    number22 -= number23;

    std::cout << "TEST 8:" << std::endl;
    std::cout << "Testing \"-=\" operator -> (-10001000000 - -9956123). Expected: -9,991,043,877: ";
    number22.printOutNumber();
    std::cout << std::endl;

    //TEST 9
    BigNumber number25 = BigNumber(-9956123);
    BigNumber number26 = BigNumber(-10001000000);
    number25 -= number26;

    std::cout << "TEST 9:" << std::endl;
    std::cout << "Testing \"-=\" operator -> (-9956123 - -10001000000). Expected: 9,991,043,877: ";
    number25.printOutNumber();
    std::cout << std::endl;

    //TEST 10
    BigNumber number28 = BigNumber(-9956123);
    BigNumber number29 = BigNumber();
    number28 -= number29;

    std::cout << "TEST 10:" << std::endl;
    std::cout << "Testing \"-=\" operator -> (-9956123 - 0). Expected: -9956123: ";
    number28.printOutNumber();
    std::cout << std::endl;

    //TEST 11
    BigNumber number31 = BigNumber();
    BigNumber number32 = BigNumber(156);
    number31 -= number32;

    std::cout << "TEST 11:" << std::endl;
    std::cout << "Testing \"-=\" operator -> (0 - 156). Expected: -156: ";
    number31.printOutNumber();
    std::cout << std::endl;

    //TEST 12
    BigNumber number34 = BigNumber();
    BigNumber number35 = BigNumber();
    number34 -= number35;

    std::cout << "TEST 12:" << std::endl;
    std::cout << "Testing \"-=\" operator -> (0 - 0). Expected: 0: ";
    number34.printOutNumber();
    std::cout << std::endl;

    //TEST 13
    BigNumber number37 = BigNumber(15678);
    BigNumber number38 = BigNumber(-979900);
    number37 -= number38;

    std::cout << "TEST 13:" << std::endl;
    std::cout << "Testing \"-=\" operator -> (15678 - -979900). Expected: 995,578: ";
    number37.printOutNumber();
    std::cout << std::endl;

    //TEST 14
    BigNumber number40 = BigNumber(-9560);
    BigNumber number41 = BigNumber(11256);
    number40 -= number41;

    std::cout << "TEST 14:" << std::endl;
    std::cout << "Testing \"-=\" operator -> (-9560 - 11256). Expected: -20,816: ";
    number40.printOutNumber();
    std::cout << std::endl;
}

void OperatorMultiplyTests()
{
    // - Operator tests
    std::cout << "\"*\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    BigNumber number1 = BigNumber(3);
    BigNumber number2 = BigNumber(2);
    BigNumber number3 = number1 * number2;

    std::cout << "TEST 1:" << std::endl;
    std::cout << "Testing \"*\" operator -> (3 * 2). Expected: 6: ";
    number3.printOutNumber();
    std::cout << std::endl;

    //TEST 2
    BigNumber number4 = BigNumber();
    BigNumber number5 = BigNumber(2);
    BigNumber number6 = number4 * number5;

    std::cout << "TEST 2:" << std::endl;
    std::cout << "Testing \"*\" operator -> (0 * 2). Expected: 0: ";
    number6.printOutNumber();
    std::cout << std::endl;

    //TEST 3
    BigNumber number7 = BigNumber(-100);
    BigNumber number8 = BigNumber();
    BigNumber number9 = number7 * number8;

    std::cout << "TEST 3:" << std::endl;
    std::cout << "Testing \"*\" operator -> (-100 * 0). Expected: 0: ";
    number9.printOutNumber();
    std::cout << std::endl;

    //TEST 4
    BigNumber number10 = BigNumber(56846);
    BigNumber number11 = BigNumber(3501);
    BigNumber number12 = number10 * number11;

    std::cout << "TEST 4:" << std::endl;
    std::cout << "Testing \"*\" operator -> (56846 * 3501). Expected: 199,017,846: ";
    number12.printOutNumber();
    std::cout << std::endl;

    //TEST 5
    BigNumber number13 = BigNumber(-3129);
    BigNumber number14 = BigNumber(309);
    BigNumber number15 = number13 * number14;

    std::cout << "TEST 5:" << std::endl;
    std::cout << "Testing \"*\" operator -> (-3129 * 309). Expected: -966,861: ";
    number15.printOutNumber();
    std::cout << std::endl;

    //TEST 6
    BigNumber number16 = BigNumber(-9999);
    BigNumber number17 = BigNumber(-1001);
    BigNumber number18 = number16 * number17;

    std::cout << "TEST 6:" << std::endl;
    std::cout << "Testing \"*\" operator -> (-9999 * -1001). Expected: 10,008,999: ";
    number18.printOutNumber();
    std::cout << std::endl;

    //TEST 7
    BigNumber number19 = BigNumber(-99);
    BigNumber number20 = BigNumber(1000);
    BigNumber number21 = number19 * number20;

    std::cout << "TEST 7:" << std::endl;
    std::cout << "Testing \"*\" operator -> (-99 * 1000). Expected: -99,000: ";
    number21.printOutNumber();
    std::cout << std::endl;
}

void OperatorMultiplyAndEqualsTests()
{
    // - Operator tests
    std::cout << "\"*=\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    BigNumber number1 = BigNumber(3);
    BigNumber number2 = BigNumber(2);
    number1 *= number2;

    std::cout << "TEST 1:" << std::endl;
    std::cout << "Testing \"*=\" operator -> (3 * 2). Expected: 6: ";
    number1.printOutNumber();
    std::cout << std::endl;

    //TEST 2
    BigNumber number4 = BigNumber();
    BigNumber number5 = BigNumber(2);
    number4 *= number5;

    std::cout << "TEST 2:" << std::endl;
    std::cout << "Testing \"*=\" operator -> (0 * 2). Expected: 0: ";
    number4.printOutNumber();
    std::cout << std::endl;

    //TEST 3
    BigNumber number7 = BigNumber(-100);
    BigNumber number8 = BigNumber();
    number7 *= number8;

    std::cout << "TEST 3:" << std::endl;
    std::cout << "Testing \"*=\" operator -> (-100 * 0). Expected: 0: ";
    number7.printOutNumber();
    std::cout << std::endl;

    //TEST 4
    BigNumber number10 = BigNumber(56846);
    BigNumber number11 = BigNumber(3501);
    number10 *= number11;

    std::cout << "TEST 4:" << std::endl;
    std::cout << "Testing \"*=\" operator -> (56846 * 3501). Expected: 199,017,846: ";
    number10.printOutNumber();
    std::cout << std::endl;

    //TEST 5
    BigNumber number13 = BigNumber(-3129);
    BigNumber number14 = BigNumber(309);
    number13 *= number14;

    std::cout << "TEST 5:" << std::endl;
    std::cout << "Testing \"*=\" operator -> (-3129 * 309). Expected: -966,861: ";
    number13.printOutNumber();
    std::cout << std::endl;

    //TEST 6
    BigNumber number16 = BigNumber(-9999);
    BigNumber number17 = BigNumber(-1001);
    number16 *= number17;

    std::cout << "TEST 6:" << std::endl;
    std::cout << "Testing \"*=\" operator -> (-9999 * -1001). Expected: 10,008,999: ";
    number16.printOutNumber();
    std::cout << std::endl;

    //TEST 7
    BigNumber number19 = BigNumber(-99);
    BigNumber number20 = BigNumber(1000);
    number19 *= number20;

    std::cout << "TEST 7:" << std::endl;
    std::cout << "Testing \"*=\" operator -> (-99 * 1000). Expected: -99,000: ";
    number19.printOutNumber();
    std::cout << std::endl;

    //TEST 8
    BigNumber number21 = BigNumber(-99);
    BigNumber number22 = BigNumber(-1);
    number21 *= number22;

    std::cout << "TEST 8:" << std::endl;
    std::cout << "Testing \"*=\" operator -> (-99 * -1). Expected: 99: ";
    number21.printOutNumber();
    std::cout << std::endl;
}

void OperatorDivideTests()
{
    // / Operator tests
    std::cout << "\"/\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    BigNumber number1 = BigNumber();
    BigNumber number2 = BigNumber(1);
    BigNumber number3 = number1 / number2;

    std::cout << "TEST 1:" << std::endl;
    std::cout << "Testing \"/\" operator -> (0 / 1). Expected: 0: ";
    number3.printOutNumber();
    std::cout << std::endl;

    //TEST 2
    BigNumber number4 = BigNumber(100);
    BigNumber number5 = BigNumber(101);
    BigNumber number6 = number4 / number5;

    std::cout << "TEST 2:" << std::endl;
    std::cout << "Testing \"/\" operator -> (100 / 101). Expected: 0: ";
    number6.printOutNumber();
    std::cout << std::endl;

    //TEST 3
    BigNumber number7 = BigNumber(100);
    BigNumber number8 = BigNumber(-101);
    BigNumber number9 = number7 / number8;

    std::cout << "TEST 3:" << std::endl;
    std::cout << "Testing \"/\" operator -> (100 / -101). Expected: 0: ";
    number9.printOutNumber();
    std::cout << std::endl;

    //TEST 4
    BigNumber number10 = BigNumber(5474253);
    BigNumber number11 = BigNumber(1);
    BigNumber number12 = number10 / number11;

    std::cout << "TEST 4:" << std::endl;
    std::cout << "Testing \"/\" operator -> (5474253 / 1). Expected: 5474253: ";
    number12.printOutNumber();
    std::cout << std::endl;

    //TEST 5
    BigNumber number13 = BigNumber(225);
    BigNumber number14 = BigNumber(15);
    BigNumber number15 = number13 / number14;

    std::cout << "TEST 5:" << std::endl;
    std::cout << "Testing \"/\" operator -> (225 / 15). Expected: 15: ";
    number15.printOutNumber();
    std::cout << std::endl;

    //TEST 6
    BigNumber number16 = BigNumber(225);
    BigNumber number17 = BigNumber(5);
    BigNumber number18 = number16 / number17;

    std::cout << "TEST 6:" << std::endl;
    std::cout << "Testing \"/\" operator -> (225 / 5). Expected: 45: ";
    number18.printOutNumber();
    std::cout << std::endl;

    //TEST 7
    BigNumber number19 = BigNumber(29773);
    BigNumber number20 = BigNumber(-19);
    BigNumber number21 = number19 / number20;

    std::cout << "TEST 7:" << std::endl;
    std::cout << "Testing \"/\" operator -> (29773 / -19). Expected: -1567: ";
    number21.printOutNumber();
    std::cout << std::endl;

    //TEST 8
    BigNumber number22 = BigNumber(-14670163);
    BigNumber number23 = BigNumber(163);
    BigNumber number24 = number22 / number23;

    std::cout << "TEST 8:" << std::endl;
    std::cout << "Testing \"/\" operator -> (-14670163 / 163). Expected: -90,001: ";
    number24.printOutNumber();
    std::cout << std::endl;

    //TEST 9
    BigNumber number25 = BigNumber(-14670187);
    BigNumber number26 = BigNumber(163);
    BigNumber number27 = number25 / number26;

    std::cout << "TEST 9:" << std::endl;
    std::cout << "Testing \"/\" operator -> (-14670187 / 163). Expected: -90,001: ";
    number27.printOutNumber();
    std::cout << std::endl;

    //TEST 10
    BigNumber number28 = BigNumber("38715980218941283691286446981264988961289");
    BigNumber number29 = BigNumber(-356);
    BigNumber number30 = number28 / number29;

    std::cout << "TEST 10:" << std::endl;
    std::cout << "Testing \"/\" operator -> (38715980218941283691286446981264988961289 / -356). Expected: -1.0875275e+38: ";
    number30.printOutNumber();
    std::cout << std::endl;
}

void OperatorDivideAndEqualsTests()
{
    // /= Operator tests
    std::cout << "\"/=\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    BigNumber number1 = BigNumber();
    BigNumber number2 = BigNumber(1);
    number1 /= number2;

    std::cout << "TEST 1:" << std::endl;
    std::cout << "Testing \"/=\" operator -> (0 / 1). Expected: 0: ";
    number1.printOutNumber();
    std::cout << std::endl;

    //TEST 2
    BigNumber number4 = BigNumber(100);
    BigNumber number5 = BigNumber(101);
    number4 /= number5;

    std::cout << "TEST 2:" << std::endl;
    std::cout << "Testing \"/=\" operator -> (100 / 101). Expected: 0: ";
    number4.printOutNumber();
    std::cout << std::endl;

    //TEST 3
    BigNumber number7 = BigNumber(100);
    BigNumber number8 = BigNumber(-101);
    number7 /= number8;

    std::cout << "TEST 3:" << std::endl;
    std::cout << "Testing \"/=\" operator -> (100 / -101). Expected: 0: ";
    number7.printOutNumber();
    std::cout << std::endl;

    //TEST 4
    BigNumber number10 = BigNumber(5474253);
    BigNumber number11 = BigNumber(1);
    number10 /= number11;

    std::cout << "TEST 4:" << std::endl;
    std::cout << "Testing \"/=\" operator -> (5474253 / 1). Expected: 5474253: ";
    number10.printOutNumber();
    std::cout << std::endl;

    //TEST 5
    BigNumber number13 = BigNumber(225);
    BigNumber number14 = BigNumber(15);
    number13 /= number14;

    std::cout << "TEST 5:" << std::endl;
    std::cout << "Testing \"/=\" operator -> (225 / 15). Expected: 15: ";
    number13.printOutNumber();
    std::cout << std::endl;

    //TEST 6
    BigNumber number16 = BigNumber(225);
    BigNumber number17 = BigNumber(5);
    number16 /= number17;

    std::cout << "TEST 6:" << std::endl;
    std::cout << "Testing \"/=\" operator -> (225 / 5). Expected: 45: ";
    number16.printOutNumber();
    std::cout << std::endl;

    //TEST 7
    BigNumber number19 = BigNumber(29773);
    BigNumber number20 = BigNumber(-19);
    number19 /= number20;

    std::cout << "TEST 7:" << std::endl;
    std::cout << "Testing \"/=\" operator -> (29773 / -19). Expected: -1567: ";
    number19.printOutNumber();
    std::cout << std::endl;

    //TEST 8
    BigNumber number22 = BigNumber(-14670163);
    BigNumber number23 = BigNumber(163);
    number22 /= number23;

    std::cout << "TEST 8:" << std::endl;
    std::cout << "Testing \"/=\" operator -> (-14670163 / 163). Expected: -90,001: ";
    number22.printOutNumber();
    std::cout << std::endl;

    //TEST 9
    BigNumber number25 = BigNumber(-14670187);
    BigNumber number26 = BigNumber(163);
    number25 /= number26;

    std::cout << "TEST 9:" << std::endl;
    std::cout << "Testing \"/=\" operator -> (-14670187 / 163). Expected: -90,001: ";
    number25.printOutNumber();
    std::cout << std::endl;

    //TEST 10
    BigNumber number28 = BigNumber("38715980218941283691286446981264988961289");
    BigNumber number29 = BigNumber(-356);
    number28 /= number29;

    std::cout << "TEST 10:" << std::endl;
    std::cout << "Testing \"/=\" operator -> (38715980218941283691286446981264988961289 / -356). Expected: -1.0875275e+38: ";
    number28.printOutNumber();
    std::cout << std::endl;
}

void OperatorPercentTests()
{
    // / Operator tests
    std::cout << "\"%\" Operator TESTS: " << std::endl << std::endl;
    std::cout << (-14670187 % 163);
    //TEST 1
    BigNumber number1 = BigNumber();
    BigNumber number2 = BigNumber(1);
    BigNumber number3 = number1 % number2;

    std::cout << "TEST 1:" << std::endl;
    std::cout << "Testing \"%\" operator -> (0 % 1). Expected: 0: ";
    number3.printOutNumber();
    std::cout << std::endl;

    //TEST 2
    BigNumber number4 = BigNumber(100);
    BigNumber number5 = BigNumber(101);
    BigNumber number6 = number4 % number5;

    std::cout << "TEST 2:" << std::endl;
    std::cout << "Testing \"%\" operator -> (100 % 101). Expected: 100: ";
    number6.printOutNumber();
    std::cout << std::endl;

    //TEST 3
    BigNumber number7 = BigNumber(100);
    BigNumber number8 = BigNumber(-101);
    BigNumber number9 = number7 % number8;

    std::cout << "TEST 3:" << std::endl;
    std::cout << "Testing \"%\" operator -> (100 % -101). Expected: 100: ";
    number9.printOutNumber();
    std::cout << std::endl;

    //TEST 4
    BigNumber number10 = BigNumber(5474253);
    BigNumber number11 = BigNumber(1);
    BigNumber number12 = number10 % number11;

    std::cout << "TEST 4:" << std::endl;
    std::cout << "Testing \"%\" operator -> (5474253 % 1). Expected: 0: ";
    number12.printOutNumber();
    std::cout << std::endl;

    //TEST 5
    BigNumber number13 = BigNumber(225);
    BigNumber number14 = BigNumber(15);
    BigNumber number15 = number13 % number14;

    std::cout << "TEST 5:" << std::endl;
    std::cout << "Testing \"%\" operator -> (225 % 15). Expected: 0: ";
    number15.printOutNumber();
    std::cout << std::endl;

    //TEST 6
    BigNumber number16 = BigNumber(225);
    BigNumber number17 = BigNumber(5);
    BigNumber number18 = number16 % number17;

    std::cout << "TEST 6:" << std::endl;
    std::cout << "Testing \"%\" operator -> (225 % 5). Expected: 0: ";
    number18.printOutNumber();
    std::cout << std::endl;

    //TEST 7
    BigNumber number19 = BigNumber(29773);
    BigNumber number20 = BigNumber(-19);
    BigNumber number21 = number19 % number20;

    std::cout << "TEST 7:" << std::endl;
    std::cout << "Testing \"%\" operator -> (29773 % -19). Expected: 0: ";
    number21.printOutNumber();
    std::cout << std::endl;

    //TEST 8
    BigNumber number22 = BigNumber(-14670163);
    BigNumber number23 = BigNumber(163);
    BigNumber number24 = number22 % number23;

    std::cout << "TEST 8:" << std::endl;
    std::cout << "Testing \"%\" operator -> (-14670163 % 163). Expected: 0: ";
    number24.printOutNumber();
    std::cout << std::endl;

    //TEST 9
    BigNumber number25 = BigNumber(-14670187);
    BigNumber number26 = BigNumber(163);
    BigNumber number27 = number25 % number26;

    std::cout << "TEST 9:" << std::endl;
    std::cout << "Testing \"%\" operator -> (-14670187 % 163). Expected: -24: ";
    number27.printOutNumber();
    std::cout << std::endl;

    //3871598021894108369 --> 289
    //38715980218941283691286446981264988961289 --> 341
    //TEST 10
    BigNumber number28 = BigNumber("38715980218941283691286446981264988961289");
    BigNumber number29 = BigNumber(-356);
    BigNumber number30 = number28 % number29;

    std::cout << "TEST 10:" << std::endl;
    std::cout << "Testing \"%\" operator -> (38715980218941283691286446981264988961289 % -356). Expected: 341: ";
    number30.printOutNumber();
    //std::cout << std::endl;
    std::cout << "Testing \"%\" operator PART 2-> ( (38715980218941283691286446981264988961289 / -356)*-356 + 341 ). Expected: 38715980218941283691286446981264988961289: ";
    (((number28 / number29) * number29) + number30).printOutNumber();
    std::cout << std::endl;

}

void OperatorPercentAndEqualsTests()
{
    // / Operator tests
    std::cout << "\"%=\" Operator TESTS: " << std::endl << std::endl;
    std::cout << (-14670187 % 163);
    //TEST 1
    BigNumber number1 = BigNumber();
    BigNumber number2 = BigNumber(1);
    number1 %= number2;

    std::cout << "TEST 1:" << std::endl;
    std::cout << "Testing \"%=\" operator -> (0 %= 1). Expected: 0: ";
    number1.printOutNumber();
    std::cout << std::endl;

    //TEST 2
    BigNumber number4 = BigNumber(100);
    BigNumber number5 = BigNumber(101);
    number4 %= number5;

    std::cout << "TEST 2:" << std::endl;
    std::cout << "Testing \"%=\" operator -> (100 %= 101). Expected: 100: ";
    number4.printOutNumber();
    std::cout << std::endl;

    //TEST 3
    BigNumber number7 = BigNumber(100);
    BigNumber number8 = BigNumber(-101);
    number7 %= number8;

    std::cout << "TEST 3:" << std::endl;
    std::cout << "Testing \"%=\" operator -> (100 %= -101). Expected: 100: ";
    number7.printOutNumber();
    std::cout << std::endl;

    //TEST 4
    BigNumber number10 = BigNumber(5474253);
    BigNumber number11 = BigNumber(1);
    number10 %= number11;

    std::cout << "TEST 4:" << std::endl;
    std::cout << "Testing \"%=\" operator -> (5474253 %= 1). Expected: 0: ";
    number10.printOutNumber();
    std::cout << std::endl;

    //TEST 5
    BigNumber number13 = BigNumber(225);
    BigNumber number14 = BigNumber(15);
    number13 %= number14;

    std::cout << "TEST 5:" << std::endl;
    std::cout << "Testing \"%=\" operator -> (225 %= 15). Expected: 0: ";
    number13.printOutNumber();
    std::cout << std::endl;

    //TEST 6
    BigNumber number16 = BigNumber(225);
    BigNumber number17 = BigNumber(5);
    number16 %= number17;

    std::cout << "TEST 6:" << std::endl;
    std::cout << "Testing \"%=\" operator -> (225 %= 5). Expected: 0: ";
    number16.printOutNumber();
    std::cout << std::endl;

    //TEST 7
    BigNumber number19 = BigNumber(29773);
    BigNumber number20 = BigNumber(-19);
    number19 %= number20;

    std::cout << "TEST 7:" << std::endl;
    std::cout << "Testing \"%=\" operator -> (29773 %= -19). Expected: 0: ";
    number19.printOutNumber();
    std::cout << std::endl;

    //TEST 8
    BigNumber number22 = BigNumber(-14670163);
    BigNumber number23 = BigNumber(163);
    number22 %= number23;

    std::cout << "TEST 8:" << std::endl;
    std::cout << "Testing \"%=\" operator -> (-14670163 %= 163). Expected: 0: ";
    number22.printOutNumber();
    std::cout << std::endl;

    //TEST 9
    BigNumber number25 = BigNumber(-14670187);
    BigNumber number26 = BigNumber(163);
    number25 %= number26;

    std::cout << "TEST 9:" << std::endl;
    std::cout << "Testing \"%=\" operator -> (-14670187 %= 163). Expected: -24: ";
    number25.printOutNumber();
    std::cout << std::endl;

    //3871598021894108369 --> 289
    //38715980218941283691286446981264988961289 --> 341
    //TEST 10
    BigNumber number28 = BigNumber("38715980218941283691286446981264988961289");
    BigNumber number29 = BigNumber(-356);
    number28 %= number29;

    std::cout << "TEST 10:" << std::endl;
    std::cout << "Testing \"%=\" operator -> (38715980218941283691286446981264988961289 %= -356). Expected: 341: ";
    number28.printOutNumber();
    std::cout << std::endl;
}

void OperatorDivideAndPercentMemoryLeakTests()
{
    // / Operator tests
    std::cout << "\"/\" Operator TESTS FOR MEMORY LEAKS: " << std::endl << std::endl;
    std::cout << "Starting test...";
    //TEST 1
    BigNumber number1 = BigNumber();
    BigNumber number2 = BigNumber(1);

    for (long long int i = 0; i < 1000000; i++)
    {
        BigNumber number3 = number1 / number2;
    }

    //TEST 2
    BigNumber number4 = BigNumber(100);
    BigNumber number5 = BigNumber(101);
    for (long long int i = 0; i < 1000000; i++)
    {
        BigNumber number6 = number4 % number5;
    }

    //TEST 5
    BigNumber number13 = BigNumber(225);
    BigNumber number14 = BigNumber(15);
    for (long long int i = 0; i < 1000000; i++)
    {
        number13 /= number14;
    }

    std::cout << "TEST ENDED --> ";
}

void PeshoAndLuboTests()
{
    std::cout << "TESTS FROM PESHO AND LUBO: \n\n";

    //CORRECT
    std::cout << std::boolalpha << (BigNumber("7643276342876783246893247") > BigNumber("4767846784647856547476")) << std::endl;
    std::cout << std::boolalpha << (BigNumber("4767846784647856547476") < BigNumber("7643276342876783246893247")) << std::endl;
    std::cout << std::boolalpha << (BigNumber("7643276342876783246893247") != BigNumber("4767846784647856547476")) << std::endl;
    std::cout << std::boolalpha << (BigNumber("7643276342876783246893247") == BigNumber("7643276342876783246893247")) << std::endl;


    std::cout << std::boolalpha << ((BigNumber("12345678901234567890") + BigNumber("4354678097643135")) == BigNumber("12350033579332211025")) << std::endl;
    std::cout << std::boolalpha << ((BigNumber("12345678901234567890") - BigNumber("4354678097643135")) == BigNumber("12341324223136924755")) << std::endl;
    std::cout << std::boolalpha << ((BigNumber("12345678901234567890") * BigNumber("4354678097643135")) == BigNumber("53761457511741137249987999149935150")) << std::endl;
    std::cout << std::boolalpha << ((BigNumber("12345678901234567890") / BigNumber("4354678097643135")) == BigNumber("2835")) << std::endl;
    std::cout << std::boolalpha << ((BigNumber("12345678901234567890") % BigNumber("4354678097643135")) == BigNumber("166494416280165")) << std::endl;

    //DEBUG SHIT
    std::cout << std::boolalpha << ((BigNumber("-12345678901234567890") + BigNumber("4354678097643135")) == BigNumber("-12341324223136924755")) << std::endl;
    std::cout << std::boolalpha << ((BigNumber("-12345678901234567890") * BigNumber("4354678097643135")) == BigNumber("-53761457511741137249987999149935150")) << std::endl;

    std::cout << std::endl;
}

//Tests for copying shit correctly without access violation reading exceptions or memory leaks
void SpecialTests()
{
    std::cout << "SPECIAL Tests for copying shit correctly without access violation reading exceptions or memory leaks: \n\n";
    //CORRECT
    BigNumber otherBigNumber = BigNumber("4354678097643135");
    BigNumber anotherBigNumber = BigNumber("12345678901234567890");
    BigNumber otherAnotherBigNumber = BigNumber("12350033579332211025");
    otherBigNumber.printOutNumber();
    anotherBigNumber.printOutNumber();
    /*BigNumber otherAnotherBigNumber = otherBigNumber + anotherBigNumber;
    otherAnotherBigNumber.printOutNumber();*/
    std::cout << std::boolalpha << ((otherBigNumber + anotherBigNumber) == otherAnotherBigNumber) << std::endl;

    BigNumber copyOfOtherBigNumber = otherBigNumber;
    BigNumber copyOfAnotherBigNumber = anotherBigNumber;
    BigNumber copyOfOtherAnotherBigNumber = otherAnotherBigNumber;

    std::cout << "Is copyOfOtherBigNumber == otherBigNumber -> " << std::boolalpha << (copyOfOtherBigNumber == otherBigNumber) << std::endl;
    std::cout << "Is copyOfAnotherBigNumber == anotherBigNumber -> " << std::boolalpha << (copyOfAnotherBigNumber == anotherBigNumber) << std::endl;
    std::cout << "Is copyOfOtherAnotherBigNumber == otherAnotherBigNumber -> " << std::boolalpha << (copyOfOtherAnotherBigNumber == otherAnotherBigNumber) << std::endl;
    std::cout << "Is copyOfOtherAnotherBigNumber2 == copyOfOtherAnotherBigNumber -> " << std::boolalpha << ((copyOfOtherBigNumber += copyOfAnotherBigNumber) == copyOfOtherAnotherBigNumber) << std::endl;
}

int main()
{
    // CONSTRUCTOR TESTS
    ConstructorAndCopyAndAssignTests();

    // READING OPERATOR TESTS
    //ReadingOperatorTests();

    // ARITHMETIC AND COMPARATIVE OPERATORS TESTS
    std::cout << std::endl << "TESTS FOR ARITHMETIC AND COMPARATIVE OPERATORS:\n" << std::endl;

    // == Operator and != Operator Tests
    EqualsAndNotEqualsTests();

    // > Operator Tests
    OperatorGreaterThanTests();

    // >= Operator Tests
    OperatorGreaterThanOrEqualsTests();

    // < Operator Tests
    OperatorLessThanTests();

    // <= Operator Tests
    OperatorLessThanOrEqualsTests();

    // + Operator Tests
    OperatorSumTests();

    // += Operator Tests
    OperatorSumAndEqualsTests();

    // - Operator Tests
    OperatorMinusTests();

    // -= Operator Tests
    OperatorMinusAndEqualsTests();

    // * Operator Tests 
    OperatorMultiplyTests();

    // *= Operator Tests
    OperatorMultiplyAndEqualsTests();

    // Operator tests
    OperatorDivideTests();

    //= Operator tests
    OperatorDivideAndEqualsTests();

    // % Operator tests
    OperatorPercentTests();

    // %= Operator tests
    OperatorPercentAndEqualsTests();

    // / and % Operator memory leak tests. PROCEED WITH CAUTION!!!
    //OperatorDivideAndPercentMemoryLeakTests();

    // Test inputs from Pesho and Lubo
    PeshoAndLuboTests();

    //Special Tests
    SpecialTests();
}