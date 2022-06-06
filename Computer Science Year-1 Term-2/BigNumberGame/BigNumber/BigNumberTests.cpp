#include "BigNumberTests.h"
#include "..\Project.StringManipulation\MStringManip.h"

void BigNumberTests::OperatorGreaterThanTestTemplate(mstring testTitle, mstring textDescription,
    const BigNumber& bigNumber1, const BigNumber& bigNumber2, bool newLine, std::ostream& os)
{
    os << testTitle << std::endl;
    os << textDescription <<
        (bigNumber1 > bigNumber2 ? "TRUE" : "FALSE") << std::endl;
    if (newLine) os << std::endl;
}

void BigNumberTests::OperatorGreaterThanOrEqualsTestTemplate(mstring testTitle, mstring textDescription,
    const BigNumber& bigNumber1, const BigNumber& bigNumber2, bool newLine, std::ostream& os)
{
    os << testTitle << std::endl;
    os << textDescription <<
        (bigNumber1 >= bigNumber2 ? "TRUE" : "FALSE") << std::endl;
    if (newLine) os << std::endl;
}

void BigNumberTests::ConstructorAndCopyAndAssignTests(std::ostream& os)
{
    int someNumberInt = 5678;
    char someNumberChar[] = "1234";
    BigNumber defaultBigNumber = BigNumber();
    BigNumber someBigNumberInt = BigNumber(someNumberInt);
    BigNumber someBigNumberChar = BigNumber(someNumberChar);
    BigNumber someOtherBigNumber = BigNumber("-1");
    BigNumber someOtheBigNumberZero = BigNumber("0");

    //OLD
    os << "Initial values: TESTS FOR NON-COPY CONSTRUCTORS" << std::endl;
    os << "defaultBigNumber: " << defaultBigNumber << std::endl;
    os << "someBigNumberInt: " << someBigNumberInt << std::endl;
    os << "someBigNumberChar: " << someBigNumberChar << std::endl;
    os << "someOtherBigNumber: " << someOtherBigNumber << std::endl;
    os << "someOtheBigNumberZero: " << someOtheBigNumberZero << std::endl;

    //NEW
    os << std::endl << "New Values: TESTS FOR ASSIGNMENT AND COPY OPERATORS AND CONSTRUCTOR" << std::endl;
    os << "TESTING -> defaultBigNumber = someNumberInt\n";
    //Calls constructor for with someNumberInt as long long int parameter
    defaultBigNumber = someNumberInt;
    os << "defaultBigNumber: " << defaultBigNumber << std::endl;

    os << "TESTING -> BigNumber copyOfBigNumberChar = BigNumber(someBigNumberChar)\n";
    BigNumber copyOfBigNumberChar = BigNumber(someBigNumberChar);
    os << "copyOfBigNumberChar: " << copyOfBigNumberChar << std::endl;

    os << "TESTING -> someBigNumberInt = someBigNumberChar\n";
    someBigNumberInt = someBigNumberChar;
    os << "someBigNumberInt: " << someBigNumberInt << std::endl;

    os << "TESTING -> someBigNumberInt = someBigNumberInt\n";
    someBigNumberInt = someBigNumberInt;
    os << "someBigNumberInt: " << someBigNumberInt << std::endl;
}

void BigNumberTests::ReadingOperatorTests()
{
    std::cout << std::endl << "TESTS FOR READING A NUMBER FROM CONSOLE:\n" << std::endl;
    std::cout << "\">>\" Operator TESTS: " << std::endl << std::endl;
    BigNumber someBigNumberToRead = BigNumber();
    std::cout << "Enter a BigNumber here: ";
    std::cin >> someBigNumberToRead;
    std::cout << "Testing \">>\" operator: (Expected: {same input from console}): " << someBigNumberToRead << std::endl;
    std::cout << std::endl << std::endl;
}

void BigNumberTests::EqualsAndNotEqualsTests(std::ostream& os)
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
    os << "\"==\" Operator TESTS: " << std::endl << std::endl;

    os << "Testing \"==\" operator (defaultBigNumber == someBigNumberInt): (Expected: FALSE): " <<
        (defaultBigNumber == someBigNumberInt ? "TRUE" : "FALSE") << std::endl;
    os << std::endl;

    os << "Testing \"==\" operator (someBigNumberChar == someBigNumberInt): (Expected: TRUE): " <<
        (someBigNumberChar == someBigNumberInt ? "TRUE" : "FALSE") << std::endl;
    os << std::endl;

    os << "Testing \"==\" operator (someBigNumberChar == someBigNumberChar): (Expected: TRUE): " <<
        (someBigNumberChar == someBigNumberChar ? "TRUE" : "FALSE") << std::endl;
    os << std::endl;

    //!= Operator tests
    os << "\"!=\" Operator TESTS: " << std::endl;

    os << "Testing \"!=\" operator (defaultBigNumber != someBigNumberInt): (Expected: TRUE): " <<
        (defaultBigNumber != someBigNumberInt ? "TRUE" : "FALSE") << std::endl;
    os << std::endl;

    os << "Testing \"!=\" operator (someBigNumberChar != someBigNumberInt): (Expected: FALSE): " <<
        (someBigNumberChar != someBigNumberInt ? "TRUE" : "FALSE") << std::endl;
    os << std::endl;

    os << "Testing \"!=\" operator (someBigNumberChar != someBigNumberChar): (Expected: FALSE): " <<
        (someBigNumberChar != someBigNumberChar ? "TRUE" : "FALSE") << std::endl;
    os << std::endl;
}

void BigNumberTests::OperatorGreaterThanTests(std::ostream& os)
{
    // > Operator tests
    os << "\">\" Operator TESTS: " << std::endl << std::endl;

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
        lesserBigNumber1, biggerBigNumber1, false, os);
    OperatorGreaterThanTestTemplate("",
        "REVERSE: Testing \">\" operator -> (65000 > 5050). Expected: True, because sizes are different:",
        biggerBigNumber1, lesserBigNumber1, true, os);

    //BigNumber2
    OperatorGreaterThanTestTemplate("BigNumber2 tests: ",
        "Testing \">\" operator -> (-67890 > -6789). Expected: False, because sizes are different:",
        lesserBigNumber2, biggerBigNumber2, false, os);
    OperatorGreaterThanTestTemplate("",
        "REVERSE: Testing \">\" operator -> (-6789 > -67890). Expected: True, because sizes are different:",
        biggerBigNumber2, lesserBigNumber2, true, os);

    //BigNumber3
    OperatorGreaterThanTestTemplate("BigNumber3 tests: ",
        "Testing \">\" operator -> (-67890 > 1). Expected: False, because signs are different:",
        lesserBigNumber3, biggerBigNumber3, false, os);
    OperatorGreaterThanTestTemplate("",
        "REVERSE: Testing \">\" operator -> (1 > -67890). Expected: True, because signs are different:",
        biggerBigNumber3, lesserBigNumber3, true, os);

    //BigNumber4
    OperatorGreaterThanTestTemplate("BigNumber4 tests: ",
        "Testing \">\" operator -> (-69 > 10). Expected: False, because signs are different:",
        lesserBigNumber4, biggerBigNumber4, false, os);
    OperatorGreaterThanTestTemplate("",
        "REVERSE: Testing \">\" operator -> (10 > -69). Expected: True, because signs are different:",
        biggerBigNumber4, lesserBigNumber4, true, os);

    //BigNumber5
    OperatorGreaterThanTestTemplate("BigNumber5 tests: ",
        "Testing \">\" operator -> (1023 > 1030). Expected: False, because first number is smaller:",
        lesserBigNumber5, biggerBigNumber5, false, os);
    OperatorGreaterThanTestTemplate("",
        "REVERSE: Testing \">\" operator -> (1030 > 1023). Expected: True, because first number is bigger:",
        biggerBigNumber5, lesserBigNumber5, true, os);

    //BigNumber6
    OperatorGreaterThanTestTemplate("BigNumber6 tests: ",
        "Testing \">\" operator -> (-4010 > -4000). Expected: False, because first number is smaller:",
        lesserBigNumber6, biggerBigNumber6, false, os);
    OperatorGreaterThanTestTemplate("",
        "REVERSE: Testing \">\" operator -> (-4000 > -4010). Expected: True, because first number is bigger:",
        biggerBigNumber6, lesserBigNumber6, true, os);

    //BigNumber7
    OperatorGreaterThanTestTemplate("BigNumber7 tests: ",
        "Testing \">\" operator -> (0 > 100). Expected: False, because first number is 0 and second is positive:",
        lesserBigNumber7, biggerBigNumber7, false, os);
    OperatorGreaterThanTestTemplate("",
        "REVERSE: Testing \">\" operator -> (100 > 0). Expected: True, because second number is 0 and first is positive:",
        biggerBigNumber7, lesserBigNumber7, true, os);

    //BigNumber8
    OperatorGreaterThanTestTemplate("BigNumber8 tests: ",
        "Testing \">\" operator -> (-100 > 0). Expected: False, because second number is 0 and first is negative:",
        lesserBigNumber8, biggerBigNumber8, false, os);
    OperatorGreaterThanTestTemplate("",
        "REVERSE: Testing \">\" operator -> (0 > -100). Expected: True, because first number is 0 and second is negative:",
        biggerBigNumber8, lesserBigNumber8, true, os);

    //BigNumber9
    OperatorGreaterThanTestTemplate("BigNumber9 tests: ",
        "Testing \">\" operator -> (0 > 0). Expected: False, because both numbers are 0:",
        lesserBigNumber9, biggerBigNumber9, true, os);

    //BigNumber10
    OperatorGreaterThanTestTemplate("BigNumber10 tests: ",
        "Testing \">\" operator -> (2456 > 2456). Expected: False, because both numbers are equal:",
        lesserBigNumber10, lesserBigNumber10, true, os);
}

void BigNumberTests::OperatorGreaterThanOrEqualsTests(std::ostream& os)
{
    // > Operator tests
    os << "\">=\" Operator TESTS: " << std::endl << std::endl;

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
        lesserBigNumber1, biggerBigNumber1, false, os);
    OperatorGreaterThanOrEqualsTestTemplate("",
        "REVERSE: Testing \">=\" operator -> (65000 >= 5050). Expected: True, because sizes are different:",
        biggerBigNumber1, lesserBigNumber1, true, os);

    //BigNumber2
    OperatorGreaterThanOrEqualsTestTemplate("BigNumber2 tests: ",
        "Testing \">=\" operator -> (-67890 >= -6789). Expected: False, because sizes are different:",
        lesserBigNumber2, biggerBigNumber2, false, os);
    OperatorGreaterThanOrEqualsTestTemplate("",
        "REVERSE: Testing \">=\" operator -> (-6789 >= -67890). Expected: True, because sizes are different:",
        biggerBigNumber2, lesserBigNumber2, true, os);

    //BigNumber3
    OperatorGreaterThanOrEqualsTestTemplate("BigNumber3 tests: ",
        "Testing \">=\" operator -> (-67890 >= 1). Expected: False, because signs are different:",
        lesserBigNumber3, biggerBigNumber3, false, os);
    OperatorGreaterThanOrEqualsTestTemplate("",
        "REVERSE: Testing \">=\" operator -> (1 >= -67890). Expected: True, because signs are different:",
        biggerBigNumber3, lesserBigNumber3, true, os);

    //BigNumber4
    OperatorGreaterThanOrEqualsTestTemplate("BigNumber4 tests: ",
        "Testing \">=\" operator -> (-69 >= 10). Expected: False, because signs are different:",
        lesserBigNumber4, biggerBigNumber4, false, os);
    OperatorGreaterThanOrEqualsTestTemplate("",
        "REVERSE: Testing \">=\" operator -> (10 >= -69). Expected: True, because signs are different:",
        biggerBigNumber4, lesserBigNumber4, true, os);

    //BigNumber5
    OperatorGreaterThanOrEqualsTestTemplate("BigNumber5 tests: ",
        "Testing \">=\" operator -> (1023 >= 1030). Expected: False, because first number is smaller:",
        lesserBigNumber5, biggerBigNumber5, false, os);
    OperatorGreaterThanOrEqualsTestTemplate("",
        "REVERSE: Testing \">=\" operator -> (1030 >= 1023). Expected: True, because first number is bigger:",
        biggerBigNumber5, lesserBigNumber5, true, os);

    //BigNumber6
    OperatorGreaterThanOrEqualsTestTemplate("BigNumber6 tests: ",
        "Testing \">=\" operator -> (-4010 >= -4000). Expected: False, because first number is smaller:",
        lesserBigNumber6, biggerBigNumber6, false, os);
    OperatorGreaterThanOrEqualsTestTemplate("",
        "REVERSE: Testing \">=\" operator -> (-4000 >= -4010). Expected: True, because first number is bigger:",
        biggerBigNumber6, lesserBigNumber6, true, os);

    //BigNumber7
    OperatorGreaterThanOrEqualsTestTemplate("BigNumber7 tests: ",
        "Testing \">=\" operator -> (0 >= 100). Expected: False, because first number is 0 and second is positive:",
        lesserBigNumber7, biggerBigNumber7, false, os);
    OperatorGreaterThanOrEqualsTestTemplate("",
        "REVERSE: Testing \">=\" operator -> (100 >= 0). Expected: True, because second number is 0 and first is positive:",
        biggerBigNumber7, lesserBigNumber7, true, os);

    //BigNumber8
    OperatorGreaterThanOrEqualsTestTemplate("BigNumber8 tests: ",
        "Testing \">=\" operator -> (-100 >= 0). Expected: False, because second number is 0 and first is negative:",
        lesserBigNumber8, biggerBigNumber8, false, os);
    OperatorGreaterThanOrEqualsTestTemplate("",
        "REVERSE: Testing \">=\" operator -> (0 >= -100). Expected: True, because first number is 0 and second is negative:",
        biggerBigNumber8, lesserBigNumber8, true, os);

    //BigNumber9
    OperatorGreaterThanOrEqualsTestTemplate("BigNumber9 tests: ",
        "Testing \">=\" operator -> (0 >= 0). Expected: True, because both numbers are equal:",
        lesserBigNumber9, biggerBigNumber9, true, os);

    //BigNumber10
    OperatorGreaterThanOrEqualsTestTemplate("BigNumber10 tests: ",
        "Testing \">=\" operator -> (2456 >= 2456). Expected: True, because both numbers are equal:",
        lesserBigNumber10, lesserBigNumber10, true, os);
}

void BigNumberTests::OperatorLessThanTests(std::ostream& os)
{
    os << "LESS THAN TESTS:" << std::endl;
    os << "Testing \"<\" operator -> (100 < -130). Expected: False, because 100 > -130:" <<
        (BigNumber(100) < BigNumber(-130) ? "TRUE" : "FALSE") << std::endl;
    os << "Testing \"<\" operator -> (110 < 110). Expected: False, the numbers are equal:" <<
        (BigNumber(110) < BigNumber(110) ? "TRUE" : "FALSE") << std::endl;
    os << "Testing \"<\" operator -> (0 < 0). Expected: False, the numbers are equal:" <<
        (BigNumber() < BigNumber() ? "TRUE" : "FALSE") << std::endl;

    os << std::endl;
}

void BigNumberTests::OperatorLessThanOrEqualsTests(std::ostream& os)
{
    os << "\"<=\" Operator TESTS:" << std::endl;
    os << "Testing \"<=\" operator -> (100 <= -130). Expected: False, because 100 > -130:" <<
        (BigNumber(100) <= BigNumber(-130) ? "TRUE" : "FALSE") << std::endl;
    os << "Testing \"<=\" operator -> (110 <= 110). Expected: True, the numbers are equal:" <<
        (BigNumber(110) <= BigNumber(110) ? "TRUE" : "FALSE") << std::endl;
    os << "Testing \"<=\" operator -> (0 <= 0). Expected: True, the numbers are equal:" <<
        (BigNumber() <= BigNumber() ? "TRUE" : "FALSE") << std::endl;

    os << std::endl;
}

void BigNumberTests::OperatorSumTests(std::ostream& os)
{
    // + Operator tests
    os << "\"+\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    BigNumber number1 = BigNumber(1);
    BigNumber number2 = BigNumber(2);
    BigNumber number3 = number1 + number2;

    os << "TEST 1:" << std::endl;
    os << "Testing \"+\" operator -> (1 + 2). Expected: 3: " << number3 << std::endl;
    os << std::endl;

    //TEST 2
    BigNumber number4 = BigNumber(9);
    BigNumber number5 = BigNumber(1);
    BigNumber number6 = number4 + number5;

    os << "TEST 2:" << std::endl;
    os << "Testing \"+\" operator -> (9 + 1). Expected: 10: " << number6 << std::endl;
    os << std::endl;

    //TEST 3
    BigNumber number7 = BigNumber(9999999);
    BigNumber number8 = BigNumber(78);
    BigNumber number9 = number7 + number8;
    os << "TEST 3:" << std::endl;
    os << "Testing \"+\" operator -> (9999999 + 78). Expected: 10 000 077: " << number9 << std::endl;
    os << std::endl;

    //TEST 4
    BigNumber number10 = BigNumber();
    BigNumber number11 = BigNumber(-79);
    BigNumber number12 = number10 + number11;
    os << "TEST 4:" << std::endl;
    os << "Testing \"+\" operator -> (0 + (-79)). Expected: -79: " << number12 << std::endl;
    os << std::endl;

    //TEST 5
    BigNumber number13 = BigNumber(-101);
    BigNumber number14 = BigNumber();
    BigNumber number15 = number13 + number14;
    os << "TEST 5:" << std::endl;
    os << "Testing \"+\" operator -> ((-101) + 0). Expected: -101: " << number15 << std::endl;
    os << std::endl;

    //TEST 6
    BigNumber number16 = BigNumber(-101);
    BigNumber number17 = BigNumber(-5);
    BigNumber number18 = number16 + number17;
    os << "TEST 6:" << std::endl;
    os << "Testing \"+\" operator -> ((-101) + (-5)). Expected: -106: " << number18 << std::endl;
    os << std::endl;

    //TEST 7
    BigNumber number19 = BigNumber(-101);
    BigNumber number20 = BigNumber(-99);
    BigNumber number21 = number19 + number20;
    os << "TEST 7:" << std::endl;
    os << "Testing \"+\" operator -> ((-101) + (-99)). Expected: -200: " << number21 << std::endl;
    os << std::endl;

    //TEST 8
    BigNumber number22 = BigNumber(-991);
    BigNumber number23 = BigNumber(-99);
    BigNumber number24 = number22 + number23;
    os << "TEST 8:" << std::endl;
    os << "Testing \"+\" operator -> ((-991) + (-99)). Expected: -1090: " << number24 << std::endl;
    os << std::endl;

    //TEST 9
    BigNumber number25 = BigNumber(991);
    BigNumber number26 = BigNumber(-99);
    BigNumber number27 = number25 + number26;
    os << "TEST 9:" << std::endl;
    os << "Testing \"+\" operator -> (991 + (-99)). Expected: 892: " << number27 << std::endl;
    os << std::endl;

    //TEST 10
    BigNumber number28 = BigNumber(-100100098);
    BigNumber number29 = BigNumber(65699);
    BigNumber number30 = number28 + number29;
    os << "TEST 10:" << std::endl;
    os << "Testing \"+\" operator -> (-100100098 + 65699). Expected: -100,034,399: " << number30 << std::endl;
    os << std::endl;
}

void BigNumberTests::OperatorSumAndEqualsTests(std::ostream& os)
{
    // + Operator tests
    os << "\"+=\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    BigNumber number1 = BigNumber(1);
    BigNumber number2 = BigNumber(2);
    number1 += number2;

    os << "TEST 1:" << std::endl;
    os << "Testing \"+=\" operator -> (1 + 2). Expected: 3: " << number1 << std::endl;
    os << std::endl;

    //TEST 2
    BigNumber number4 = BigNumber(9);
    BigNumber number5 = BigNumber(1);
    number4 += number5;

    os << "TEST 2:" << std::endl;
    os << "Testing \"+=\" operator -> (9 + 1). Expected: 10: " << number4 << std::endl;
    os << std::endl;

    //TEST 3
    BigNumber number7 = BigNumber(9999999);
    BigNumber number8 = BigNumber(78);
    number7 += number8;
    os << "TEST 3:" << std::endl;
    os << "Testing \"+=\" operator -> (9999999 + 78). Expected: 10 000 077: " << number7 << std::endl;
    os << std::endl;

    //TEST 4
    BigNumber number10 = BigNumber();
    BigNumber number11 = BigNumber(-79);
    number10 += number11;
    os << "TEST 4:" << std::endl;
    os << "Testing \"+=\" operator -> (0 + (-79)). Expected: -79: " << number10 << std::endl;
    os << std::endl;

    ////TEST 5
    BigNumber number13 = BigNumber(-101);
    BigNumber number14 = BigNumber();
    number13 += number14;
    os << "TEST 5:" << std::endl;
    os << "Testing \"+=\" operator -> ((-101) + 0). Expected: -101: " << number13 << std::endl;
    os << std::endl;

    //TEST 6
    BigNumber number16 = BigNumber(-101);
    BigNumber number17 = BigNumber(-5);
    number16 += number17;
    os << "TEST 6:" << std::endl;
    os << "Testing \"+=\" operator -> ((-101) + (-5)). Expected: -106: " << number16 << std::endl;
    os << std::endl;

    //TEST 7
    BigNumber number19 = BigNumber(-101);
    BigNumber number20 = BigNumber(-99);
    number19 += number20;
    os << "TEST 7:" << std::endl;
    os << "Testing \"+=\" operator -> ((-101) + (-99)). Expected: -200: " << number19 << std::endl;
    os << std::endl;

    //TEST 8
    BigNumber number22 = BigNumber(-991);
    BigNumber number23 = BigNumber(-99);
    number22 += number23;
    os << "TEST 7:" << std::endl;
    os << "Testing \"+=\" operator -> ((-991) + (-99)). Expected: -1090: " << number22 << std::endl;
    os << std::endl;

    //TEST 9
    BigNumber number25 = BigNumber(991);
    BigNumber number26 = BigNumber(-99);
    number25 += number26;
    os << "TEST 9:" << std::endl;
    os << "Testing \"+=\" operator -> (991 + (-99)). Expected: 892: " << number25 << std::endl;
    os << std::endl;

    //TEST 10
    BigNumber number28 = BigNumber(-100100098);
    BigNumber number29 = BigNumber(65699);
    number28 += number29;
    os << "TEST 10:" << std::endl;
    os << "Testing \"+=\" operator -> (-100100098 + 65699). Expected: -100,034,399: " << number28 << std::endl;
    os << std::endl;
}

void BigNumberTests::OperatorMinusTests(std::ostream& os)
{
    // - Operator tests
    os << "\"-\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    BigNumber number1 = BigNumber(3);
    BigNumber number2 = BigNumber(2);
    BigNumber number3 = number1 - number2;

    os << "TEST 1:" << std::endl;
    os << "Testing \"-\" operator -> (3 - 2). Expected: 1: " << number3 << std::endl;
    os << std::endl;

    //TEST 2
    BigNumber number4 = BigNumber(1345);
    BigNumber number5 = BigNumber(1234);
    BigNumber number6 = number4 - number5;

    os << "TEST 2:" << std::endl;
    os << "Testing \"-\" operator -> (1345 - 1234). Expected: 111: " << number6 << std::endl;
    os << std::endl;

    //TEST 3
    BigNumber number7 = BigNumber(1234);
    BigNumber number8 = BigNumber(1345);
    BigNumber number9 = number7 - number8;

    os << "TEST 3:" << std::endl;
    os << "Testing \"-\" operator -> (1234 - 1345). Expected: -111: " << number9 << std::endl;
    os << std::endl;

    //TEST 4
    BigNumber number10 = BigNumber(1234);
    BigNumber number11 = BigNumber(13450);
    BigNumber number12 = number10 - number11;

    os << "TEST 4:" << std::endl;
    os << "Testing \"-\" operator -> (1234 - 13450). Expected: -12 216: " << number12 << std::endl;
    os << std::endl;

    //TEST 5
    BigNumber number13 = BigNumber(-1234);
    BigNumber number14 = BigNumber(-1230);
    BigNumber number15 = number13 - number14;

    os << "TEST 5:" << std::endl;
    os << "Testing \"-\" operator -> (-1234 - -1230). Expected: -4: " << number15 << std::endl;
    os << std::endl;

    //TEST 6
    BigNumber number16 = BigNumber(-1234);
    BigNumber number17 = BigNumber(-13457);
    BigNumber number18 = number16 - number17;

    os << "TEST 6:" << std::endl;
    os << "Testing \"-\" operator -> (-1234 - -13457). Expected: 12 223: " << number18 << std::endl;
    os << std::endl;

    //TEST 7
    BigNumber number19 = BigNumber(-10101);
    BigNumber number20 = BigNumber(-99);
    BigNumber number21 = number19 - number20;

    os << "TEST 7:" << std::endl;
    os << "Testing \"-\" operator -> (-10101 - -99). Expected: -10 002: " << number21 << std::endl;
    os << std::endl;

    //TEST 8
    BigNumber number22 = BigNumber(-10001000000);
    BigNumber number23 = BigNumber(-9956123);
    BigNumber number24 = number22 - number23;

    os << "TEST 8:" << std::endl;
    os << "Testing \"-\" operator -> (-10001000000 - -9956123). Expected: -9,991,043,877: " << number24 << std::endl;
    os << std::endl;

    //TEST 9
    BigNumber number25 = BigNumber(-9956123);
    BigNumber number26 = BigNumber(-10001000000);
    BigNumber number27 = number25 - number26;

    os << "TEST 9:" << std::endl;
    os << "Testing \"-\" operator -> (-9956123 - -10001000000). Expected: 9,991,043,877: " << number27 << std::endl;
    os << std::endl;

    //TEST 9
    BigNumber number28 = BigNumber(-9956123);
    BigNumber number29 = BigNumber();
    BigNumber number30 = number28 - number29;

    os << "TEST 9:" << std::endl;
    os << "Testing \"-\" operator -> (-9956123 - 0). Expected: -9956123: " << number30 << std::endl;
    os << std::endl;

    //TEST 10
    BigNumber number31 = BigNumber();
    BigNumber number32 = BigNumber(156);
    BigNumber number33 = number31 - number32;

    os << "TEST 10:" << std::endl;
    os << "Testing \"-\" operator -> (0 - 156). Expected: -156: " << number33 << std::endl;
    os << std::endl;

    //TEST 11
    BigNumber number34 = BigNumber();
    BigNumber number35 = BigNumber();
    BigNumber number36 = number34 - number35;

    os << "TEST 11:" << std::endl;
    os << "Testing \"-\" operator -> (0 - 0). Expected: 0: " << number36 << std::endl;
    os << std::endl;

    //TEST 12
    BigNumber number37 = BigNumber(15678);
    BigNumber number38 = BigNumber(-979900);
    BigNumber number39 = number37 - number38;

    os << "TEST 12:" << std::endl;
    os << "Testing \"-\" operator -> (15678 - -979900). Expected: 995,578: " << number39 << std::endl;
    os << std::endl;

    //TEST 13
    BigNumber number40 = BigNumber(-9560);
    BigNumber number41 = BigNumber(11256);
    BigNumber number42 = number40 - number41;

    os << "TEST 13:" << std::endl;
    os << "Testing \"-\" operator -> (-9560 - 11256). Expected: -20,816: " << number42 << std::endl;
    os << std::endl;
}

void BigNumberTests::OperatorMinusAndEqualsTests(std::ostream& os)
{
    // - Operator tests
    os << "\"-=\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    BigNumber number1 = BigNumber(3);
    BigNumber number2 = BigNumber(2);
    number1 -= number2;

    os << "TEST 1:" << std::endl;
    os << "Testing \"-=\" operator -> (3 - 2). Expected: 1: " << number1 << std::endl;
    os << std::endl;

    //TEST 2
    BigNumber number4 = BigNumber(1345);
    BigNumber number5 = BigNumber(1234);
    number4 -= number5;

    os << "TEST 2:" << std::endl;
    os << "Testing \"-=\" operator -> (1345 - 1234). Expected: 111: " << number4 << std::endl;
    os << std::endl;

    //TEST 3
    BigNumber number7 = BigNumber(1234);
    BigNumber number8 = BigNumber(1345);
    number7 -= number8;

    os << "TEST 3:" << std::endl;
    os << "Testing \"-=\" operator -> (1234 - 1345). Expected: -111: " << number7 << std::endl;
    os << std::endl;

    //TEST 4
    BigNumber number10 = BigNumber(1234);
    BigNumber number11 = BigNumber(13450);
    number10 -= number11;

    os << "TEST 4:" << std::endl;
    os << "Testing \"-=\" operator -> (1234 - 13450). Expected: -12 216: " << number10 << std::endl;
    os << std::endl;

    //TEST 5
    BigNumber number13 = BigNumber(-1234);
    BigNumber number14 = BigNumber(-1230);
    number13 -= number14;

    os << "TEST 5:" << std::endl;
    os << "Testing \"-=\" operator -> (-1234 - -1230). Expected: -4: " << number13 << std::endl;
    os << std::endl;

    //TEST 6
    BigNumber number16 = BigNumber(-1234);
    BigNumber number17 = BigNumber(-13457);
    number16 -= number17;

    os << "TEST 6:" << std::endl;
    os << "Testing \"-=\" operator -> (-1234 - -13457). Expected: 12 223: " << number16 << std::endl;
    os << std::endl;

    //TEST 7
    BigNumber number19 = BigNumber(-10101);
    BigNumber number20 = BigNumber(-99);
    number19 -= number20;

    os << "TEST 7:" << std::endl;
    os << "Testing \"-=\" operator -> (-10101 - -99). Expected: -10 002: " << number19 << std::endl;
    os << std::endl;

    //TEST 8
    BigNumber number22 = BigNumber(-10001000000);
    BigNumber number23 = BigNumber(-9956123);
    number22 -= number23;

    os << "TEST 8:" << std::endl;
    os << "Testing \"-=\" operator -> (-10001000000 - -9956123). Expected: -9,991,043,877: " << number22 << std::endl;
    os << std::endl;

    //TEST 9
    BigNumber number25 = BigNumber(-9956123);
    BigNumber number26 = BigNumber(-10001000000);
    number25 -= number26;

    os << "TEST 9:" << std::endl;
    os << "Testing \"-=\" operator -> (-9956123 - -10001000000). Expected: 9,991,043,877: " << number25 << std::endl;
    os << std::endl;

    //TEST 10
    BigNumber number28 = BigNumber(-9956123);
    BigNumber number29 = BigNumber();
    number28 -= number29;

    os << "TEST 10:" << std::endl;
    os << "Testing \"-=\" operator -> (-9956123 - 0). Expected: -9956123: " << number28 << std::endl;
    os << std::endl;

    //TEST 11
    BigNumber number31 = BigNumber();
    BigNumber number32 = BigNumber(156);
    number31 -= number32;

    os << "TEST 11:" << std::endl;
    os << "Testing \"-=\" operator -> (0 - 156). Expected: -156: " << number31 << std::endl;
    os << std::endl;

    //TEST 12
    BigNumber number34 = BigNumber();
    BigNumber number35 = BigNumber();
    number34 -= number35;

    os << "TEST 12:" << std::endl;
    os << "Testing \"-=\" operator -> (0 - 0). Expected: 0: " << number34 << std::endl;
    os << std::endl;

    //TEST 13
    BigNumber number37 = BigNumber(15678);
    BigNumber number38 = BigNumber(-979900);
    number37 -= number38;

    os << "TEST 13:" << std::endl;
    os << "Testing \"-=\" operator -> (15678 - -979900). Expected: 995,578: " << number37 << std::endl;
    os << std::endl;

    //TEST 14
    BigNumber number40 = BigNumber(-9560);
    BigNumber number41 = BigNumber(11256);
    number40 -= number41;

    os << "TEST 14:" << std::endl;
    os << "Testing \"-=\" operator -> (-9560 - 11256). Expected: -20,816: " << number40 << std::endl;
    os << std::endl;
}

void BigNumberTests::OperatorIncrementTests(std::ostream& os)
{
    // ++ Operator tests
    os << "\"++\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 2:" << std::endl;
    BigNumber number1 = BigNumber(1000);
    os << "Testing \"++1000\" operation --> Expected: 1001: " << ++number1 << std::endl;
    os << "New value of BigNumber is: Expected: 1001: " << number1;
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2:" << std::endl;
    BigNumber number2 = BigNumber(1000);
    os << "Testing \"1000++\" operation --> Expected: 1000: " << number2++ << std::endl;
    os << "New value of BigNumber is: Expected: 1001: " << number2;
    os << std::endl;
    os << std::endl;
}

void BigNumberTests::OperatorDecrementTests(std::ostream& os)
{
    // -- Operator tests
    os << "\"--\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 2:" << std::endl;
    BigNumber number1 = BigNumber(1000);
    os << "Testing \"--1000\" operation --> Expected: 999: " << --number1 << std::endl;
    os << "New value of BigNumber is: Expected: 999: " << number1;
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2:" << std::endl;
    BigNumber number2 = BigNumber(1000);
    os << "Testing \"1000--\" operation --> Expected: 1000: " << number2-- << std::endl;
    os << "New value of BigNumber is: Expected: 999: " << number2;
    os << std::endl;
    os << std::endl;
}

void BigNumberTests::OperatorMultiplyTests(std::ostream& os)
{
    // - Operator tests
    os << "\"*\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    BigNumber number1 = BigNumber(3);
    BigNumber number2 = BigNumber(2);
    BigNumber number3 = number1 * number2;

    os << "TEST 1:" << std::endl;
    os << "Testing \"*\" operator -> (3 * 2). Expected: 6: " << number3 << std::endl;
    os << std::endl;

    //TEST 2
    BigNumber number4 = BigNumber();
    BigNumber number5 = BigNumber(2);
    BigNumber number6 = number4 * number5;

    os << "TEST 2:" << std::endl;
    os << "Testing \"*\" operator -> (0 * 2). Expected: 0: " << number6 << std::endl;
    os << std::endl;

    //TEST 3
    BigNumber number7 = BigNumber(-100);
    BigNumber number8 = BigNumber();
    BigNumber number9 = number7 * number8;

    os << "TEST 3:" << std::endl;
    os << "Testing \"*\" operator -> (-100 * 0). Expected: 0: " << number9 << std::endl;
    os << std::endl;

    //TEST 4
    BigNumber number10 = BigNumber(56846);
    BigNumber number11 = BigNumber(3501);
    BigNumber number12 = number10 * number11;

    os << "TEST 4:" << std::endl;
    os << "Testing \"*\" operator -> (56846 * 3501). Expected: 199,017,846: " << number12 << std::endl;
    os << std::endl;

    //TEST 5
    BigNumber number13 = BigNumber(-3129);
    BigNumber number14 = BigNumber(309);
    BigNumber number15 = number13 * number14;

    os << "TEST 5:" << std::endl;
    os << "Testing \"*\" operator -> (-3129 * 309). Expected: -966,861: " << number15 << std::endl;
    os << std::endl;

    //TEST 6
    BigNumber number16 = BigNumber(-9999);
    BigNumber number17 = BigNumber(-1001);
    BigNumber number18 = number16 * number17;

    os << "TEST 6:" << std::endl;
    os << "Testing \"*\" operator -> (-9999 * -1001). Expected: 10,008,999: " << number18 << std::endl;
    os << std::endl;

    //TEST 7
    BigNumber number19 = BigNumber(-99);
    BigNumber number20 = BigNumber(1000);
    BigNumber number21 = number19 * number20;

    os << "TEST 7:" << std::endl;
    os << "Testing \"*\" operator -> (-99 * 1000). Expected: -99,000: " << number21 << std::endl;
    os << std::endl;
}

void BigNumberTests::OperatorMultiplyAndEqualsTests(std::ostream& os)
{
    // - Operator tests
    os << "\"*=\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    BigNumber number1 = BigNumber(3);
    BigNumber number2 = BigNumber(2);
    number1 *= number2;

    os << "TEST 1:" << std::endl;
    os << "Testing \"*=\" operator -> (3 * 2). Expected: 6: " << number1 << std::endl;
    os << std::endl;

    //TEST 2
    BigNumber number4 = BigNumber();
    BigNumber number5 = BigNumber(2);
    number4 *= number5;

    os << "TEST 2:" << std::endl;
    os << "Testing \"*=\" operator -> (0 * 2). Expected: 0: " << number4 << std::endl;
    os << std::endl;

    //TEST 3
    BigNumber number7 = BigNumber(-100);
    BigNumber number8 = BigNumber();
    number7 *= number8;

    os << "TEST 3:" << std::endl;
    os << "Testing \"*=\" operator -> (-100 * 0). Expected: 0: " << number7 << std::endl;
    os << std::endl;

    //TEST 4
    BigNumber number10 = BigNumber(56846);
    BigNumber number11 = BigNumber(3501);
    number10 *= number11;

    os << "TEST 4:" << std::endl;
    os << "Testing \"*=\" operator -> (56846 * 3501). Expected: 199,017,846: " << number10 << std::endl;
    os << std::endl;

    //TEST 5
    BigNumber number13 = BigNumber(-3129);
    BigNumber number14 = BigNumber(309);
    number13 *= number14;

    os << "TEST 5:" << std::endl;
    os << "Testing \"*=\" operator -> (-3129 * 309). Expected: -966,861: " << number13 << std::endl;
    os << std::endl;

    //TEST 6
    BigNumber number16 = BigNumber(-9999);
    BigNumber number17 = BigNumber(-1001);
    number16 *= number17;

    os << "TEST 6:" << std::endl;
    os << "Testing \"*=\" operator -> (-9999 * -1001). Expected: 10,008,999: " << number16 << std::endl;
    os << std::endl;

    //TEST 7
    BigNumber number19 = BigNumber(-99);
    BigNumber number20 = BigNumber(1000);
    number19 *= number20;

    os << "TEST 7:" << std::endl;
    os << "Testing \"*=\" operator -> (-99 * 1000). Expected: -99,000: " << number19 << std::endl;
    os << std::endl;

    //TEST 8
    BigNumber number21 = BigNumber(-99);
    BigNumber number22 = BigNumber(-1);
    number21 *= number22;

    os << "TEST 8:" << std::endl;
    os << "Testing \"*=\" operator -> (-99 * -1). Expected: 99: " << number21 << std::endl;
    os << std::endl;
}

void BigNumberTests::OperatorDivideTests(std::ostream& os)
{
    // / Operator tests
    os << "\"/\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    BigNumber number1 = BigNumber();
    BigNumber number2 = BigNumber(1);
    BigNumber number3 = number1 / number2;

    os << "TEST 1:" << std::endl;
    os << "Testing \"/\" operator -> (0 / 1). Expected: 0: " << number3 << std::endl;
    os << std::endl;

    //TEST 2
    BigNumber number4 = BigNumber(100);
    BigNumber number5 = BigNumber(101);
    BigNumber number6 = number4 / number5;

    os << "TEST 2:" << std::endl;
    os << "Testing \"/\" operator -> (100 / 101). Expected: 0: " << number6 << std::endl;
    os << std::endl;

    //TEST 3
    BigNumber number7 = BigNumber(100);
    BigNumber number8 = BigNumber(-101);
    BigNumber number9 = number7 / number8;

    os << "TEST 3:" << std::endl;
    os << "Testing \"/\" operator -> (100 / -101). Expected: 0: " << number9 << std::endl;
    os << std::endl;

    //TEST 4
    BigNumber number10 = BigNumber(5474253);
    BigNumber number11 = BigNumber(1);
    BigNumber number12 = number10 / number11;

    os << "TEST 4:" << std::endl;
    os << "Testing \"/\" operator -> (5474253 / 1). Expected: 5474253: " << number12 << std::endl;
    os << std::endl;

    //TEST 5
    BigNumber number13 = BigNumber(225);
    BigNumber number14 = BigNumber(15);
    BigNumber number15 = number13 / number14;

    os << "TEST 5:" << std::endl;
    os << "Testing \"/\" operator -> (225 / 15). Expected: 15: " << number15 << std::endl;
    os << std::endl;

    //TEST 6
    BigNumber number16 = BigNumber(225);
    BigNumber number17 = BigNumber(5);
    BigNumber number18 = number16 / number17;

    os << "TEST 6:" << std::endl;
    os << "Testing \"/\" operator -> (225 / 5). Expected: 45: " << number18 << std::endl;
    os << std::endl;

    //TEST 7
    BigNumber number19 = BigNumber(29773);
    BigNumber number20 = BigNumber(-19);
    BigNumber number21 = number19 / number20;

    os << "TEST 7:" << std::endl;
    os << "Testing \"/\" operator -> (29773 / -19). Expected: -1567: " << number21 << std::endl;
    os << std::endl;

    //TEST 8
    BigNumber number22 = BigNumber(-14670163);
    BigNumber number23 = BigNumber(163);
    BigNumber number24 = number22 / number23;

    os << "TEST 8:" << std::endl;
    os << "Testing \"/\" operator -> (-14670163 / 163). Expected: -90,001: " << number24 << std::endl;
    os << std::endl;

    //TEST 9
    BigNumber number25 = BigNumber(-14670187);
    BigNumber number26 = BigNumber(163);
    BigNumber number27 = number25 / number26;

    os << "TEST 9:" << std::endl;
    os << "Testing \"/\" operator -> (-14670187 / 163). Expected: -90,001: " << number27 << std::endl;
    os << std::endl;

    //TEST 10
    BigNumber number28 = BigNumber("38715980218941283691286446981264988961289");
    BigNumber number29 = BigNumber(-356);
    BigNumber number30 = number28 / number29;

    os << "TEST 10:" << std::endl;
    os << "Testing \"/\" operator -> (38715980218941283691286446981264988961289 / -356). Expected: -1.0875275e+38: " << number30 << std::endl;
    os << std::endl;
}

void BigNumberTests::OperatorDivideAndEqualsTests(std::ostream& os)
{
    // /= Operator tests
    os << "\"/=\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    BigNumber number1 = BigNumber();
    BigNumber number2 = BigNumber(1);
    number1 /= number2;

    os << "TEST 1:" << std::endl;
    os << "Testing \"/=\" operator -> (0 / 1). Expected: 0: " << number1 << std::endl;
    os << std::endl;

    //TEST 2
    BigNumber number4 = BigNumber(100);
    BigNumber number5 = BigNumber(101);
    number4 /= number5;

    os << "TEST 2:" << std::endl;
    os << "Testing \"/=\" operator -> (100 / 101). Expected: 0: " << number4 << std::endl;
    os << std::endl;

    //TEST 3
    BigNumber number7 = BigNumber(100);
    BigNumber number8 = BigNumber(-101);
    number7 /= number8;

    os << "TEST 3:" << std::endl;
    os << "Testing \"/=\" operator -> (100 / -101). Expected: 0: " << number7 << std::endl;
    os << std::endl;

    //TEST 4
    BigNumber number10 = BigNumber(5474253);
    BigNumber number11 = BigNumber(1);
    number10 /= number11;

    os << "TEST 4:" << std::endl;
    os << "Testing \"/=\" operator -> (5474253 / 1). Expected: 5474253: " << number10 << std::endl;
    os << std::endl;

    //TEST 5
    BigNumber number13 = BigNumber(225);
    BigNumber number14 = BigNumber(15);
    number13 /= number14;

    os << "TEST 5:" << std::endl;
    os << "Testing \"/=\" operator -> (225 / 15). Expected: 15: " << number13 << std::endl;
    os << std::endl;

    //TEST 6
    BigNumber number16 = BigNumber(225);
    BigNumber number17 = BigNumber(5);
    number16 /= number17;

    os << "TEST 6:" << std::endl;
    os << "Testing \"/=\" operator -> (225 / 5). Expected: 45: " << number16 << std::endl;
    os << std::endl;

    //TEST 7
    BigNumber number19 = BigNumber(29773);
    BigNumber number20 = BigNumber(-19);
    number19 /= number20;

    os << "TEST 7:" << std::endl;
    os << "Testing \"/=\" operator -> (29773 / -19). Expected: -1567: " << number19 << std::endl;
    os << std::endl;

    //TEST 8
    BigNumber number22 = BigNumber(-14670163);
    BigNumber number23 = BigNumber(163);
    number22 /= number23;

    os << "TEST 8:" << std::endl;
    os << "Testing \"/=\" operator -> (-14670163 / 163). Expected: -90,001: " << number22 << std::endl;
    os << std::endl;

    //TEST 9
    BigNumber number25 = BigNumber(-14670187);
    BigNumber number26 = BigNumber(163);
    number25 /= number26;

    os << "TEST 9:" << std::endl;
    os << "Testing \"/=\" operator -> (-14670187 / 163). Expected: -90,001: " << number25 << std::endl;
    os << std::endl;

    //TEST 10
    BigNumber number28 = BigNumber("38715980218941283691286446981264988961289");
    BigNumber number29 = BigNumber(-356);
    number28 /= number29;

    os << "TEST 10:" << std::endl;
    os << "Testing \"/=\" operator -> (38715980218941283691286446981264988961289 / -356). Expected: -1.0875275e+38: " << number28 << std::endl;
    os << std::endl;
}

void BigNumberTests::OperatorPercentTests(std::ostream& os)
{
    // / Operator tests
    os << "\"%\" Operator TESTS: " << std::endl << std::endl;
    os << (-14670187 % 163);
    //TEST 1
    BigNumber number1 = BigNumber();
    BigNumber number2 = BigNumber(1);
    BigNumber number3 = number1 % number2;

    os << "TEST 1:" << std::endl;
    os << "Testing \"%\" operator -> (0 % 1). Expected: 0: " << number3 << std::endl;
    os << std::endl;

    //TEST 2
    BigNumber number4 = BigNumber(100);
    BigNumber number5 = BigNumber(101);
    BigNumber number6 = number4 % number5;

    os << "TEST 2:" << std::endl;
    os << "Testing \"%\" operator -> (100 % 101). Expected: 100: " << number6 << std::endl;
    os << std::endl;

    //TEST 3
    BigNumber number7 = BigNumber(100);
    BigNumber number8 = BigNumber(-101);
    BigNumber number9 = number7 % number8;

    os << "TEST 3:" << std::endl;
    os << "Testing \"%\" operator -> (100 % -101). Expected: 100: " << number9 << std::endl;
    os << std::endl;

    //TEST 4
    BigNumber number10 = BigNumber(5474253);
    BigNumber number11 = BigNumber(1);
    BigNumber number12 = number10 % number11;

    os << "TEST 4:" << std::endl;
    os << "Testing \"%\" operator -> (5474253 % 1). Expected: 0: " << number12 << std::endl;
    os << std::endl;

    //TEST 5
    BigNumber number13 = BigNumber(225);
    BigNumber number14 = BigNumber(15);
    BigNumber number15 = number13 % number14;

    os << "TEST 5:" << std::endl;
    os << "Testing \"%\" operator -> (225 % 15). Expected: 0: " << number15 << std::endl;
    os << std::endl;

    //TEST 6
    BigNumber number16 = BigNumber(225);
    BigNumber number17 = BigNumber(5);
    BigNumber number18 = number16 % number17;

    os << "TEST 6:" << std::endl;
    os << "Testing \"%\" operator -> (225 % 5). Expected: 0: " << number18 << std::endl;
    os << std::endl;

    //TEST 7
    BigNumber number19 = BigNumber(29773);
    BigNumber number20 = BigNumber(-19);
    BigNumber number21 = number19 % number20;

    os << "TEST 7:" << std::endl;
    os << "Testing \"%\" operator -> (29773 % -19). Expected: 0: " << number21 << std::endl;
    os << std::endl;

    //TEST 8
    BigNumber number22 = BigNumber(-14670163);
    BigNumber number23 = BigNumber(163);
    BigNumber number24 = number22 % number23;

    os << "TEST 8:" << std::endl;
    os << "Testing \"%\" operator -> (-14670163 % 163). Expected: 0: " << number24 << std::endl;
    os << std::endl;

    //TEST 9
    BigNumber number25 = BigNumber(-14670187);
    BigNumber number26 = BigNumber(163);
    BigNumber number27 = number25 % number26;

    os << "TEST 9:" << std::endl;
    os << "Testing \"%\" operator -> (-14670187 % 163). Expected: -24: " << number27 << std::endl;
    os << std::endl;

    //3871598021894108369 --> 289
    //38715980218941283691286446981264988961289 --> 341
    //TEST 10
    BigNumber number28 = BigNumber("38715980218941283691286446981264988961289");
    BigNumber number29 = BigNumber(-356);
    BigNumber number30 = number28 % number29;

    os << "TEST 10:" << std::endl;
    os << "Testing \"%\" operator -> (38715980218941283691286446981264988961289 % -356). Expected: 341: " << number30 << std::endl;
    //os << std::endl;
    os << "Testing \"%\" operator PART 2-> ( (38715980218941283691286446981264988961289 / -356)*-356 + 341 ). Expected: 38715980218941283691286446981264988961289: "
        << (((number28 / number29) * number29) + number30) << std::endl;
    os << std::endl;

}

void BigNumberTests::OperatorPercentAndEqualsTests(std::ostream& os)
{
    // / Operator tests
    os << "\"%=\" Operator TESTS: " << std::endl << std::endl;
    os << (-14670187 % 163);
    //TEST 1
    BigNumber number1 = BigNumber();
    BigNumber number2 = BigNumber(1);
    number1 %= number2;

    os << "TEST 1:" << std::endl;
    os << "Testing \"%=\" operator -> (0 %= 1). Expected: 0: " << number1 << std::endl;
    os << std::endl;

    //TEST 2
    BigNumber number4 = BigNumber(100);
    BigNumber number5 = BigNumber(101);
    number4 %= number5;

    os << "TEST 2:" << std::endl;
    os << "Testing \"%=\" operator -> (100 %= 101). Expected: 100: " << number4 << std::endl;
    os << std::endl;

    //TEST 3
    BigNumber number7 = BigNumber(100);
    BigNumber number8 = BigNumber(-101);
    number7 %= number8;

    os << "TEST 3:" << std::endl;
    os << "Testing \"%=\" operator -> (100 %= -101). Expected: 100: " << number7 << std::endl;
    os << std::endl;

    //TEST 4
    BigNumber number10 = BigNumber(5474253);
    BigNumber number11 = BigNumber(1);
    number10 %= number11;

    os << "TEST 4:" << std::endl;
    os << "Testing \"%=\" operator -> (5474253 %= 1). Expected: 0: " << number10 << std::endl;
    os << std::endl;

    //TEST 5
    BigNumber number13 = BigNumber(225);
    BigNumber number14 = BigNumber(15);
    number13 %= number14;

    os << "TEST 5:" << std::endl;
    os << "Testing \"%=\" operator -> (225 %= 15). Expected: 0: " << number13 << std::endl;
    os << std::endl;

    //TEST 6
    BigNumber number16 = BigNumber(225);
    BigNumber number17 = BigNumber(5);
    number16 %= number17;

    os << "TEST 6:" << std::endl;
    os << "Testing \"%=\" operator -> (225 %= 5). Expected: 0: " << number16 << std::endl;
    os << std::endl;

    //TEST 7
    BigNumber number19 = BigNumber(29773);
    BigNumber number20 = BigNumber(-19);
    number19 %= number20;

    os << "TEST 7:" << std::endl;
    os << "Testing \"%=\" operator -> (29773 %= -19). Expected: 0: " << number19 << std::endl;
    os << std::endl;

    //TEST 8
    BigNumber number22 = BigNumber(-14670163);
    BigNumber number23 = BigNumber(163);
    number22 %= number23;

    os << "TEST 8:" << std::endl;
    os << "Testing \"%=\" operator -> (-14670163 %= 163). Expected: 0: " << number22 << std::endl;
    os << std::endl;

    //TEST 9
    BigNumber number25 = BigNumber(-14670187);
    BigNumber number26 = BigNumber(163);
    number25 %= number26;

    os << "TEST 9:" << std::endl;
    os << "Testing \"%=\" operator -> (-14670187 %= 163). Expected: -24: " << number25 << std::endl;
    os << std::endl;

    //3871598021894108369 --> 289
    //38715980218941283691286446981264988961289 --> 341
    //TEST 10
    BigNumber number28 = BigNumber("38715980218941283691286446981264988961289");
    BigNumber number29 = BigNumber(-356);
    number28 %= number29;

    os << "TEST 10:" << std::endl;
    os << "Testing \"%=\" operator -> (38715980218941283691286446981264988961289 %= -356). Expected: 341: " << number28 << std::endl;
    os << std::endl;
}

void BigNumberTests::OperatorDivideAndPercentMemoryLeakTests()
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

//Tests from my assistants Pesho and Lubo from OOP practicum
void BigNumberTests::PeshoAndLuboTests(std::ostream& os)
{
    os << "TESTS FROM PESHO AND LUBO: \n\n";

    //CORRECT
    os << std::boolalpha << (BigNumber("7643276342876783246893247") > BigNumber("4767846784647856547476")) << std::endl;
    os << std::boolalpha << (BigNumber("4767846784647856547476") < BigNumber("7643276342876783246893247")) << std::endl;
    os << std::boolalpha << (BigNumber("7643276342876783246893247") != BigNumber("4767846784647856547476")) << std::endl;
    os << std::boolalpha << (BigNumber("7643276342876783246893247") == BigNumber("7643276342876783246893247")) << std::endl;


    os << std::boolalpha << ((BigNumber("12345678901234567890") + BigNumber("4354678097643135")) == BigNumber("12350033579332211025")) << std::endl;
    os << std::boolalpha << ((BigNumber("12345678901234567890") - BigNumber("4354678097643135")) == BigNumber("12341324223136924755")) << std::endl;
    os << std::boolalpha << ((BigNumber("12345678901234567890") * BigNumber("4354678097643135")) == BigNumber("53761457511741137249987999149935150")) << std::endl;
    os << std::boolalpha << ((BigNumber("12345678901234567890") / BigNumber("4354678097643135")) == BigNumber("2835")) << std::endl;
    os << std::boolalpha << ((BigNumber("12345678901234567890") % BigNumber("4354678097643135")) == BigNumber("166494416280165")) << std::endl;

    //DEBUG SHIT
    BigNumber DebugShit = BigNumber("-12345678901234567890") + BigNumber("4354678097643135");
    os << std::boolalpha << ((BigNumber("-12345678901234567890") + BigNumber("4354678097643135")) == BigNumber("-12341324223136924755")) << std::endl;
    os << std::boolalpha << ((BigNumber("-12345678901234567890") * BigNumber("4354678097643135")) == BigNumber("-53761457511741137249987999149935150")) << std::endl;

    os << std::endl;
}

//Tests for copying shit correctly without access violation reading exceptions or memory leaks
void BigNumberTests::SpecialTests(std::ostream& os)
{
    os << "SPECIAL Tests for copying shit correctly without access violation reading exceptions or memory leaks: \n\n";
    //CORRECT
    BigNumber otherBigNumber = BigNumber("4354678097643135");
    BigNumber anotherBigNumber = BigNumber("12345678901234567890");
    BigNumber otherAnotherBigNumber = BigNumber("12350033579332211025");
    os << otherBigNumber << " + " << anotherBigNumber << " = " << otherAnotherBigNumber << "??? --> ";

    os << std::boolalpha << ((otherBigNumber + anotherBigNumber) == otherAnotherBigNumber) << std::endl;

    BigNumber copyOfOtherBigNumber = otherBigNumber;
    BigNumber copyOfAnotherBigNumber = anotherBigNumber;
    BigNumber copyOfOtherAnotherBigNumber = otherAnotherBigNumber;

    os << "Is copyOfOtherBigNumber == otherBigNumber -> " << std::boolalpha << (copyOfOtherBigNumber == otherBigNumber) << std::endl;
    os << "Is copyOfAnotherBigNumber == anotherBigNumber -> " << std::boolalpha << (copyOfAnotherBigNumber == anotherBigNumber) << std::endl;
    os << "Is copyOfOtherAnotherBigNumber == otherAnotherBigNumber -> " << std::boolalpha << (copyOfOtherAnotherBigNumber == otherAnotherBigNumber) << std::endl;
    os << "Is copyOfOtherAnotherBigNumber2 == copyOfOtherAnotherBigNumber -> " << std::boolalpha << ((copyOfOtherBigNumber += copyOfAnotherBigNumber) == copyOfOtherAnotherBigNumber) << std::endl;

    os << std::endl;
}

void BigNumberTests::getNumberTests(std::ostream& os)
{
    // getNumber() tests
    os << "TESTING getNumber() TESTS: " << std::endl << std::endl;

    //TEST 1
    BigNumber number1 = BigNumber();
    os << "TEST 1:" << std::endl;
    os << "Testing getNumber() operator -> (0). Expected: 0: " << number1.getNumber();
    os << std::endl;
    os << std::endl;

    //TEST 2
    BigNumber number2 = BigNumber("-55346");
    os << "TEST 2:" << std::endl;
    os << "Testing getNumber() operator -> (-55346). Expected: -55,346: " << number2.getNumber();
    os << std::endl;
    os << std::endl;

    //TEST 3
    BigNumber number3 = BigNumber("-123456789");
    os << "TEST 3:" << std::endl;
    os << "Testing getNumber() operator -> (-123456789). Expected: -123,456,789: " << number3.getNumber();
    os << std::endl;
    os << std::endl;

    //TEST 4
    BigNumber number4 = BigNumber("-1234");
    os << "TEST 4:" << std::endl;
    os << "Testing getNumber() operator -> (-1234). Expected: -1234: " << number4.getNumber();
    os << std::endl;
    os << std::endl;
}

void BigNumberTests::getNumberRawTests(std::ostream& os)
{
    // getNumberRaw() tests
    os << "TESTING getNumberRaw() TESTS: " << std::endl << std::endl;

    //TEST 1
    BigNumber number1 = BigNumber();
    os << "TEST 1:" << std::endl;
    os << "Testing getNumberRaw() operator -> (0). Expected: 0: " << number1.getNumberRaw();
    os << std::endl;
    os << std::endl;

    //TEST 2
    BigNumber number2 = BigNumber("-55346");
    os << "TEST 2:" << std::endl;
    os << "Testing getNumberRaw() operator -> (-55346). Expected: -55346: " << number2.getNumberRaw();
    os << std::endl;
    os << std::endl;

    //TEST 3
    BigNumber number3 = BigNumber("-1234567890");
    os << "TEST 3:" << std::endl;
    os << "Testing getNumberRaw() operator -> (-1234567890). Expected: -1234567890: " << number3.getNumberRaw();
    os << std::endl;
    os << std::endl;

    //TEST 4
    BigNumber number4 = BigNumber("-1234");
    os << "TEST 4:" << std::endl;
    os << "Testing getNumber() operator -> (-1234). Expected: -1234: " << number4.getNumberRaw();
    os << std::endl;
    os << std::endl;
}

void BigNumberTests::getNumberMemoryLeakTest()
{
    std::cout << "Start...";
    BigNumber memoryLeakExpression("10");
    while (true)
    {
        mstring answer = memoryLeakExpression.getNumber();
    }
}

void BigNumberTests::runTests(std::ostream& os)
{
    std::cout << "Start the tests for BigNumber! ";
    if (&os != &std::cout)
    {
        std::cout << "The test results are being outputted to text file with name: " << BigNumberTests::OUTPUTFILE_NAME << std::endl;
        time_t timetoday;
        time(&timetoday);
        mstring timeOfRunningTheTests = MStringManip::replaceFirst(ctime(&timetoday), "\n", "");
        os << "---------------------------- " << "" << timeOfRunningTheTests << " ----------------------------\n\n";
    }

    // CONSTRUCTOR TESTS
    ConstructorAndCopyAndAssignTests(os);
    
    ////// READING OPERATOR TESTS
    ////ReadingOperatorTests();
    
    // ARITHMETIC AND COMPARATIVE OPERATORS TESTS
    os << std::endl << "TESTS FOR ARITHMETIC AND COMPARATIVE OPERATORS:\n" << std::endl;
    
    // == Operator and != Operator Tests
    EqualsAndNotEqualsTests(os);
    
    // > Operator Tests
    OperatorGreaterThanTests(os);
    
    // >= Operator Tests
    OperatorGreaterThanOrEqualsTests(os);
    
    // < Operator Tests
    OperatorLessThanTests(os);
    
    // <= Operator Tests
    OperatorLessThanOrEqualsTests(os);
    
    // + Operator Tests
    //OperatorSumTests(os);
    //
    //// += Operator Tests
    //OperatorSumAndEqualsTests(os);
    //
    //// - Operator Tests
    //OperatorMinusTests(os);
    //
    //// -= Operator Tests
    //OperatorMinusAndEqualsTests(os);
    //
    //// ++ OperatorTests
    //OperatorIncrementTests(os);
    //
    //// -- OperatorTests
    //OperatorDecrementTests(os);
    //
    //// * Operator Tests 
    //OperatorMultiplyTests(os);
    //
    //// *= Operator Tests
    //OperatorMultiplyAndEqualsTests(os);
    //
    //// Operator tests
    //OperatorDivideTests(os);
    //
    ////= Operator tests
    //OperatorDivideAndEqualsTests(os);
    //
    //// % Operator tests
    //OperatorPercentTests(os);
    //
    //// %= Operator tests
    //OperatorPercentAndEqualsTests(os);
    //
    //// Test inputs from Pesho and Lubo
    //PeshoAndLuboTests(os);
    //
    ////Special Tests
    //SpecialTests(os);
    //
    ////Tests for getter of number
    //getNumberTests(os);
    //getNumberRawTests(os);

    // / and % Operator memory leak tests. PROCEED WITH CAUTION!!!
    //OperatorDivideAndPercentMemoryLeakTests();

    //Test for getNumber memory leak. PROCEED WITH CAUTION!!!
    //getNumberMemoryLeakTest();

    os << std::endl << std::endl;
}
