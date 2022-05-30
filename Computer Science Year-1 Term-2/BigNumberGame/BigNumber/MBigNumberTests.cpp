#include "MBigNumberTests.h"
#include "..\Project.StringManipulation\StringManip.h"

void MBigNumberTests::OperatorGreaterThanTestTemplate(const char testTitle[], const char textDescription[],
    const MBigNumber& bigNumber1, const MBigNumber& bigNumber2, bool newLine, std::ostream& os)
{
    if (testTitle != NULL) os << testTitle << std::endl;
    os << textDescription <<
        (bigNumber1 > bigNumber2 ? "TRUE" : "FALSE") << std::endl;
    if (newLine) os << std::endl;
}

void MBigNumberTests::OperatorGreaterThanOrEqualsTestTemplate(const char testTitle[], const char textDescription[],
    const MBigNumber& bigNumber1, const MBigNumber& bigNumber2, bool newLine, std::ostream& os)
{
    if (testTitle != NULL) os << testTitle << std::endl;
    os << textDescription <<
        (bigNumber1 >= bigNumber2 ? "TRUE" : "FALSE") << std::endl;
    if (newLine) os << std::endl;
}

void MBigNumberTests::ConstructorAndCopyAndAssignTests(std::ostream& os)
{
    int someNumberInt = 5678;
    char someNumberChar[] = "1234";
    MBigNumber defaultMBigNumber = MBigNumber();
    MBigNumber someMBigNumberInt = MBigNumber(someNumberInt);
    MBigNumber someMBigNumberChar = MBigNumber(someNumberChar);
    MBigNumber someOtherMBigNumber = MBigNumber("-1");
    MBigNumber someOtheMBigNumberZero = MBigNumber("0");

    //OLD
    os << "Initial values: TESTS FOR NON-COPY CONSTRUCTORS" << std::endl;
    os << "defaultMBigNumber: " << defaultMBigNumber << std::endl;
    os << "someMBigNumberInt: " << someMBigNumberInt << std::endl;
    os << "someMBigNumberChar: " << someMBigNumberChar << std::endl;
    os << "someOtherMBigNumber: " << someOtherMBigNumber << std::endl;
    os << "someOtheMBigNumberZero: " << someOtheMBigNumberZero << std::endl;

    //NEW
    os << std::endl << "New Values: TESTS FOR ASSIGNMENT AND COPY OPERATORS AND CONSTRUCTOR" << std::endl;
    os << "TESTING -> defaultMBigNumber = someNumberInt\n";
    //Calls constructor for with someNumberInt as long long int parameter
    defaultMBigNumber = someNumberInt;
    os << "defaultMBigNumber: " << defaultMBigNumber << std::endl;

    os << "TESTING -> MBigNumber copyOfMBigNumberChar = MBigNumber(someMBigNumberChar)\n";
    MBigNumber copyOfMBigNumberChar = MBigNumber(someMBigNumberChar);
    os << "copyOfMBigNumberChar: " << copyOfMBigNumberChar << std::endl;

    os << "TESTING -> someMBigNumberInt = someMBigNumberChar\n";
    someMBigNumberInt = someMBigNumberChar;
    os << "someMBigNumberInt: " << someMBigNumberInt << std::endl;

    os << "TESTING -> someMBigNumberInt = someMBigNumberInt\n";
    someMBigNumberInt = someMBigNumberInt;
    os << "someMBigNumberInt: " << someMBigNumberInt << std::endl;
}

void MBigNumberTests::ReadingOperatorTests()
{
    std::cout << std::endl << "TESTS FOR READING A NUMBER FROM CONSOLE:\n" << std::endl;
    std::cout << "\">>\" Operator TESTS: " << std::endl << std::endl;
    MBigNumber someMBigNumberToRead = MBigNumber();
    std::cout << "Enter a MBigNumber here: ";
    std::cin >> someMBigNumberToRead;
    std::cout << "Testing \">>\" operator: (Expected: {same input from console}): " << someMBigNumberToRead << std::endl;
    std::cout << std::endl << std::endl;
}

void MBigNumberTests::EqualsAndNotEqualsTests(std::ostream& os)
{
    int someNumberInt = 5678;
    char someNumberChar[] = "1234";
    MBigNumber defaultMBigNumber = MBigNumber();
    MBigNumber someMBigNumberInt = MBigNumber(someNumberInt);
    MBigNumber someMBigNumberChar = MBigNumber(someNumberChar);
    MBigNumber someOtherMBigNumber = MBigNumber("-1");
    MBigNumber someOtheMBigNumberZero = MBigNumber("0");

    //NEW
    defaultMBigNumber = someNumberInt;
    MBigNumber copyOfMBigNumberChar = MBigNumber(someMBigNumberChar);
    someMBigNumberInt = someMBigNumberChar;

    //== Operator tests
    os << "\"==\" Operator TESTS: " << std::endl << std::endl;

    os << "Testing \"==\" operator (defaultMBigNumber == someMBigNumberInt): (Expected: FALSE): " <<
        (defaultMBigNumber == someMBigNumberInt ? "TRUE" : "FALSE") << std::endl;
    os << std::endl;

    os << "Testing \"==\" operator (someMBigNumberChar == someMBigNumberInt): (Expected: TRUE): " <<
        (someMBigNumberChar == someMBigNumberInt ? "TRUE" : "FALSE") << std::endl;
    os << std::endl;

    os << "Testing \"==\" operator (someMBigNumberChar == someMBigNumberChar): (Expected: TRUE): " <<
        (someMBigNumberChar == someMBigNumberChar ? "TRUE" : "FALSE") << std::endl;
    os << std::endl;

    //!= Operator tests
    os << "\"!=\" Operator TESTS: " << std::endl;

    os << "Testing \"!=\" operator (defaultMBigNumber != someMBigNumberInt): (Expected: TRUE): " <<
        (defaultMBigNumber != someMBigNumberInt ? "TRUE" : "FALSE") << std::endl;
    os << std::endl;

    os << "Testing \"!=\" operator (someMBigNumberChar != someMBigNumberInt): (Expected: FALSE): " <<
        (someMBigNumberChar != someMBigNumberInt ? "TRUE" : "FALSE") << std::endl;
    os << std::endl;

    os << "Testing \"!=\" operator (someMBigNumberChar != someMBigNumberChar): (Expected: FALSE): " <<
        (someMBigNumberChar != someMBigNumberChar ? "TRUE" : "FALSE") << std::endl;
    os << std::endl;
}

void MBigNumberTests::OperatorGreaterThanTests(std::ostream& os)
{
    // > Operator tests
    os << "\">\" Operator TESTS: " << std::endl << std::endl;

    //INIT Phase

    MBigNumber lesserMBigNumber1 = MBigNumber(5050);
    MBigNumber biggerMBigNumber1 = MBigNumber(65000);
    //
    MBigNumber lesserMBigNumber2 = MBigNumber(-67890);
    MBigNumber biggerMBigNumber2 = MBigNumber(-6789);
    //
    MBigNumber lesserMBigNumber3 = MBigNumber(-67890);
    MBigNumber biggerMBigNumber3 = MBigNumber(1);
    //
    MBigNumber lesserMBigNumber4 = MBigNumber(-69);
    MBigNumber biggerMBigNumber4 = MBigNumber(10);
    //
    MBigNumber lesserMBigNumber5 = MBigNumber(1023);
    MBigNumber biggerMBigNumber5 = MBigNumber(1030);
    //
    MBigNumber lesserMBigNumber6 = MBigNumber(-4010);
    MBigNumber biggerMBigNumber6 = MBigNumber(-4000);
    //
    MBigNumber lesserMBigNumber7 = MBigNumber();
    MBigNumber biggerMBigNumber7 = MBigNumber(100);
    //
    MBigNumber lesserMBigNumber8 = MBigNumber(-100);
    MBigNumber biggerMBigNumber8 = MBigNumber();
    //
    MBigNumber lesserMBigNumber9 = MBigNumber();
    MBigNumber biggerMBigNumber9 = MBigNumber();
    //
    MBigNumber lesserMBigNumber10 = MBigNumber(2456);

    //TEST Phase

    //MBigNumber1
    OperatorGreaterThanTestTemplate("MBigNumber1 tests: ",
        "Testing \">\" operator -> (5050 > 65000). Expected: False, because sizes are different:",
        lesserMBigNumber1, biggerMBigNumber1, false, os);
    OperatorGreaterThanTestTemplate(NULL,
        "REVERSE: Testing \">\" operator -> (65000 > 5050). Expected: True, because sizes are different:",
        biggerMBigNumber1, lesserMBigNumber1, true, os);

    //MBigNumber2
    OperatorGreaterThanTestTemplate("MBigNumber2 tests: ",
        "Testing \">\" operator -> (-67890 > -6789). Expected: False, because sizes are different:",
        lesserMBigNumber2, biggerMBigNumber2, false, os);
    OperatorGreaterThanTestTemplate(NULL,
        "REVERSE: Testing \">\" operator -> (-6789 > -67890). Expected: True, because sizes are different:",
        biggerMBigNumber2, lesserMBigNumber2, true, os);

    //MBigNumber3
    OperatorGreaterThanTestTemplate("MBigNumber3 tests: ",
        "Testing \">\" operator -> (-67890 > 1). Expected: False, because signs are different:",
        lesserMBigNumber3, biggerMBigNumber3, false, os);
    OperatorGreaterThanTestTemplate(NULL,
        "REVERSE: Testing \">\" operator -> (1 > -67890). Expected: True, because signs are different:",
        biggerMBigNumber3, lesserMBigNumber3, true, os);

    //MBigNumber4
    OperatorGreaterThanTestTemplate("MBigNumber4 tests: ",
        "Testing \">\" operator -> (-69 > 10). Expected: False, because signs are different:",
        lesserMBigNumber4, biggerMBigNumber4, false, os);
    OperatorGreaterThanTestTemplate(NULL,
        "REVERSE: Testing \">\" operator -> (10 > -69). Expected: True, because signs are different:",
        biggerMBigNumber4, lesserMBigNumber4, true, os);

    //MBigNumber5
    OperatorGreaterThanTestTemplate("MBigNumber5 tests: ",
        "Testing \">\" operator -> (1023 > 1030). Expected: False, because first number is smaller:",
        lesserMBigNumber5, biggerMBigNumber5, false, os);
    OperatorGreaterThanTestTemplate(NULL,
        "REVERSE: Testing \">\" operator -> (1030 > 1023). Expected: True, because first number is bigger:",
        biggerMBigNumber5, lesserMBigNumber5, true, os);

    //MBigNumber6
    OperatorGreaterThanTestTemplate("MBigNumber6 tests: ",
        "Testing \">\" operator -> (-4010 > -4000). Expected: False, because first number is smaller:",
        lesserMBigNumber6, biggerMBigNumber6, false, os);
    OperatorGreaterThanTestTemplate(NULL,
        "REVERSE: Testing \">\" operator -> (-4000 > -4010). Expected: True, because first number is bigger:",
        biggerMBigNumber6, lesserMBigNumber6, true, os);

    //MBigNumber7
    OperatorGreaterThanTestTemplate("MBigNumber7 tests: ",
        "Testing \">\" operator -> (0 > 100). Expected: False, because first number is 0 and second is positive:",
        lesserMBigNumber7, biggerMBigNumber7, false, os);
    OperatorGreaterThanTestTemplate(NULL,
        "REVERSE: Testing \">\" operator -> (100 > 0). Expected: True, because second number is 0 and first is positive:",
        biggerMBigNumber7, lesserMBigNumber7, true, os);

    //MBigNumber8
    OperatorGreaterThanTestTemplate("MBigNumber8 tests: ",
        "Testing \">\" operator -> (-100 > 0). Expected: False, because second number is 0 and first is negative:",
        lesserMBigNumber8, biggerMBigNumber8, false, os);
    OperatorGreaterThanTestTemplate(NULL,
        "REVERSE: Testing \">\" operator -> (0 > -100). Expected: True, because first number is 0 and second is negative:",
        biggerMBigNumber8, lesserMBigNumber8, true, os);

    //MBigNumber9
    OperatorGreaterThanTestTemplate("MBigNumber9 tests: ",
        "Testing \">\" operator -> (0 > 0). Expected: False, because both numbers are 0:",
        lesserMBigNumber9, biggerMBigNumber9, true, os);

    //MBigNumber10
    OperatorGreaterThanTestTemplate("MBigNumber10 tests: ",
        "Testing \">\" operator -> (2456 > 2456). Expected: False, because both numbers are equal:",
        lesserMBigNumber10, lesserMBigNumber10, true, os);
}

void MBigNumberTests::OperatorGreaterThanOrEqualsTests(std::ostream& os)
{
    // > Operator tests
    os << "\">=\" Operator TESTS: " << std::endl << std::endl;

    //INIT Phase

    MBigNumber lesserMBigNumber1 = MBigNumber(5050);
    MBigNumber biggerMBigNumber1 = MBigNumber(65000);
    //
    MBigNumber lesserMBigNumber2 = MBigNumber(-67890);
    MBigNumber biggerMBigNumber2 = MBigNumber(-6789);
    //
    MBigNumber lesserMBigNumber3 = MBigNumber(-67890);
    MBigNumber biggerMBigNumber3 = MBigNumber(1);
    //
    MBigNumber lesserMBigNumber4 = MBigNumber(-69);
    MBigNumber biggerMBigNumber4 = MBigNumber(10);
    //
    MBigNumber lesserMBigNumber5 = MBigNumber(1023);
    MBigNumber biggerMBigNumber5 = MBigNumber(1030);
    //
    MBigNumber lesserMBigNumber6 = MBigNumber(-4010);
    MBigNumber biggerMBigNumber6 = MBigNumber(-4000);
    //
    MBigNumber lesserMBigNumber7 = MBigNumber();
    MBigNumber biggerMBigNumber7 = MBigNumber(100);
    //
    MBigNumber lesserMBigNumber8 = MBigNumber(-100);
    MBigNumber biggerMBigNumber8 = MBigNumber();
    //
    MBigNumber lesserMBigNumber9 = MBigNumber();
    MBigNumber biggerMBigNumber9 = MBigNumber();
    //
    MBigNumber lesserMBigNumber10 = MBigNumber(2456);

    //TEST Phase

    //MBigNumber1
    OperatorGreaterThanOrEqualsTestTemplate("MBigNumber1 tests: ",
        "Testing \">=\" operator -> (5050 >= 65000). Expected: False, because sizes are different:",
        lesserMBigNumber1, biggerMBigNumber1, false, os);
    OperatorGreaterThanOrEqualsTestTemplate(NULL,
        "REVERSE: Testing \">=\" operator -> (65000 >= 5050). Expected: True, because sizes are different:",
        biggerMBigNumber1, lesserMBigNumber1, true, os);

    //MBigNumber2
    OperatorGreaterThanOrEqualsTestTemplate("MBigNumber2 tests: ",
        "Testing \">=\" operator -> (-67890 >= -6789). Expected: False, because sizes are different:",
        lesserMBigNumber2, biggerMBigNumber2, false, os);
    OperatorGreaterThanOrEqualsTestTemplate(NULL,
        "REVERSE: Testing \">=\" operator -> (-6789 >= -67890). Expected: True, because sizes are different:",
        biggerMBigNumber2, lesserMBigNumber2, true, os);

    //MBigNumber3
    OperatorGreaterThanOrEqualsTestTemplate("MBigNumber3 tests: ",
        "Testing \">=\" operator -> (-67890 >= 1). Expected: False, because signs are different:",
        lesserMBigNumber3, biggerMBigNumber3, false, os);
    OperatorGreaterThanOrEqualsTestTemplate(NULL,
        "REVERSE: Testing \">=\" operator -> (1 >= -67890). Expected: True, because signs are different:",
        biggerMBigNumber3, lesserMBigNumber3, true, os);

    //MBigNumber4
    OperatorGreaterThanOrEqualsTestTemplate("MBigNumber4 tests: ",
        "Testing \">=\" operator -> (-69 >= 10). Expected: False, because signs are different:",
        lesserMBigNumber4, biggerMBigNumber4, false, os);
    OperatorGreaterThanOrEqualsTestTemplate(NULL,
        "REVERSE: Testing \">=\" operator -> (10 >= -69). Expected: True, because signs are different:",
        biggerMBigNumber4, lesserMBigNumber4, true, os);

    //MBigNumber5
    OperatorGreaterThanOrEqualsTestTemplate("MBigNumber5 tests: ",
        "Testing \">=\" operator -> (1023 >= 1030). Expected: False, because first number is smaller:",
        lesserMBigNumber5, biggerMBigNumber5, false, os);
    OperatorGreaterThanOrEqualsTestTemplate(NULL,
        "REVERSE: Testing \">=\" operator -> (1030 >= 1023). Expected: True, because first number is bigger:",
        biggerMBigNumber5, lesserMBigNumber5, true, os);

    //MBigNumber6
    OperatorGreaterThanOrEqualsTestTemplate("MBigNumber6 tests: ",
        "Testing \">=\" operator -> (-4010 >= -4000). Expected: False, because first number is smaller:",
        lesserMBigNumber6, biggerMBigNumber6, false, os);
    OperatorGreaterThanOrEqualsTestTemplate(NULL,
        "REVERSE: Testing \">=\" operator -> (-4000 >= -4010). Expected: True, because first number is bigger:",
        biggerMBigNumber6, lesserMBigNumber6, true, os);

    //MBigNumber7
    OperatorGreaterThanOrEqualsTestTemplate("MBigNumber7 tests: ",
        "Testing \">=\" operator -> (0 >= 100). Expected: False, because first number is 0 and second is positive:",
        lesserMBigNumber7, biggerMBigNumber7, false, os);
    OperatorGreaterThanOrEqualsTestTemplate(NULL,
        "REVERSE: Testing \">=\" operator -> (100 >= 0). Expected: True, because second number is 0 and first is positive:",
        biggerMBigNumber7, lesserMBigNumber7, true, os);

    //MBigNumber8
    OperatorGreaterThanOrEqualsTestTemplate("MBigNumber8 tests: ",
        "Testing \">=\" operator -> (-100 >= 0). Expected: False, because second number is 0 and first is negative:",
        lesserMBigNumber8, biggerMBigNumber8, false, os);
    OperatorGreaterThanOrEqualsTestTemplate(NULL,
        "REVERSE: Testing \">=\" operator -> (0 >= -100). Expected: True, because first number is 0 and second is negative:",
        biggerMBigNumber8, lesserMBigNumber8, true, os);

    //MBigNumber9
    OperatorGreaterThanOrEqualsTestTemplate("MBigNumber9 tests: ",
        "Testing \">=\" operator -> (0 >= 0). Expected: True, because both numbers are equal:",
        lesserMBigNumber9, biggerMBigNumber9, true, os);

    //MBigNumber10
    OperatorGreaterThanOrEqualsTestTemplate("MBigNumber10 tests: ",
        "Testing \">=\" operator -> (2456 >= 2456). Expected: True, because both numbers are equal:",
        lesserMBigNumber10, lesserMBigNumber10, true, os);
}

void MBigNumberTests::OperatorLessThanTests(std::ostream& os)
{
    os << "LESS THAN TESTS:" << std::endl;
    os << "Testing \"<\" operator -> (100 < -130). Expected: False, because 100 > -130:" <<
        (MBigNumber(100) < MBigNumber(-130) ? "TRUE" : "FALSE") << std::endl;
    os << "Testing \"<\" operator -> (110 < 110). Expected: False, the numbers are equal:" <<
        (MBigNumber(110) < MBigNumber(110) ? "TRUE" : "FALSE") << std::endl;
    os << "Testing \"<\" operator -> (0 < 0). Expected: False, the numbers are equal:" <<
        (MBigNumber() < MBigNumber() ? "TRUE" : "FALSE") << std::endl;

    os << std::endl;
}

void MBigNumberTests::OperatorLessThanOrEqualsTests(std::ostream& os)
{
    os << "\"<=\" Operator TESTS:" << std::endl;
    os << "Testing \"<=\" operator -> (100 <= -130). Expected: False, because 100 > -130:" <<
        (MBigNumber(100) <= MBigNumber(-130) ? "TRUE" : "FALSE") << std::endl;
    os << "Testing \"<=\" operator -> (110 <= 110). Expected: True, the numbers are equal:" <<
        (MBigNumber(110) <= MBigNumber(110) ? "TRUE" : "FALSE") << std::endl;
    os << "Testing \"<=\" operator -> (0 <= 0). Expected: True, the numbers are equal:" <<
        (MBigNumber() <= MBigNumber() ? "TRUE" : "FALSE") << std::endl;

    os << std::endl;
}

void MBigNumberTests::OperatorSumTests(std::ostream& os)
{
    // + Operator tests
    os << "\"+\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    MBigNumber number1 = MBigNumber(1);
    MBigNumber number2 = MBigNumber(2);
    MBigNumber number3 = number1 + number2;

    os << "TEST 1:" << std::endl;
    os << "Testing \"+\" operator -> (1 + 2). Expected: 3: " << number3 << std::endl;
    os << std::endl;

    //TEST 2
    MBigNumber number4 = MBigNumber(9);
    MBigNumber number5 = MBigNumber(1);
    MBigNumber number6 = number4 + number5;

    os << "TEST 2:" << std::endl;
    os << "Testing \"+\" operator -> (9 + 1). Expected: 10: " << number6 << std::endl;
    os << std::endl;

    //TEST 3
    MBigNumber number7 = MBigNumber(9999999);
    MBigNumber number8 = MBigNumber(78);
    MBigNumber number9 = number7 + number8;
    os << "TEST 3:" << std::endl;
    os << "Testing \"+\" operator -> (9999999 + 78). Expected: 10 000 077: " << number9 << std::endl;
    os << std::endl;

    //TEST 4
    MBigNumber number10 = MBigNumber();
    MBigNumber number11 = MBigNumber(-79);
    MBigNumber number12 = number10 + number11;
    os << "TEST 4:" << std::endl;
    os << "Testing \"+\" operator -> (0 + (-79)). Expected: -79: " << number12 << std::endl;
    os << std::endl;

    //TEST 5
    MBigNumber number13 = MBigNumber(-101);
    MBigNumber number14 = MBigNumber();
    MBigNumber number15 = number13 + number14;
    os << "TEST 5:" << std::endl;
    os << "Testing \"+\" operator -> ((-101) + 0). Expected: -101: " << number15 << std::endl;
    os << std::endl;

    //TEST 6
    MBigNumber number16 = MBigNumber(-101);
    MBigNumber number17 = MBigNumber(-5);
    MBigNumber number18 = number16 + number17;
    os << "TEST 6:" << std::endl;
    os << "Testing \"+\" operator -> ((-101) + (-5)). Expected: -106: " << number18 << std::endl;
    os << std::endl;

    //TEST 7
    MBigNumber number19 = MBigNumber(-101);
    MBigNumber number20 = MBigNumber(-99);
    MBigNumber number21 = number19 + number20;
    os << "TEST 7:" << std::endl;
    os << "Testing \"+\" operator -> ((-101) + (-99)). Expected: -200: " << number21 << std::endl;
    os << std::endl;

    //TEST 8
    MBigNumber number22 = MBigNumber(-991);
    MBigNumber number23 = MBigNumber(-99);
    MBigNumber number24 = number22 + number23;
    os << "TEST 8:" << std::endl;
    os << "Testing \"+\" operator -> ((-991) + (-99)). Expected: -1090: " << number24 << std::endl;
    os << std::endl;

    //TEST 9
    MBigNumber number25 = MBigNumber(991);
    MBigNumber number26 = MBigNumber(-99);
    MBigNumber number27 = number25 + number26;
    os << "TEST 9:" << std::endl;
    os << "Testing \"+\" operator -> (991 + (-99)). Expected: 892: " << number27 << std::endl;
    os << std::endl;

    //TEST 10
    MBigNumber number28 = MBigNumber(-100100098);
    MBigNumber number29 = MBigNumber(65699);
    MBigNumber number30 = number28 + number29;
    os << "TEST 10:" << std::endl;
    os << "Testing \"+\" operator -> (-100100098 + 65699). Expected: -100,034,399: " << number30 << std::endl;
    os << std::endl;
}

void MBigNumberTests::OperatorSumAndEqualsTests(std::ostream& os)
{
    // + Operator tests
    os << "\"+=\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    MBigNumber number1 = MBigNumber(1);
    MBigNumber number2 = MBigNumber(2);
    number1 += number2;

    os << "TEST 1:" << std::endl;
    os << "Testing \"+=\" operator -> (1 + 2). Expected: 3: " << number1 << std::endl;
    os << std::endl;

    //TEST 2
    MBigNumber number4 = MBigNumber(9);
    MBigNumber number5 = MBigNumber(1);
    number4 += number5;

    os << "TEST 2:" << std::endl;
    os << "Testing \"+=\" operator -> (9 + 1). Expected: 10: " << number4 << std::endl;
    os << std::endl;

    //TEST 3
    MBigNumber number7 = MBigNumber(9999999);
    MBigNumber number8 = MBigNumber(78);
    number7 += number8;
    os << "TEST 3:" << std::endl;
    os << "Testing \"+=\" operator -> (9999999 + 78). Expected: 10 000 077: " << number7 << std::endl;
    os << std::endl;

    //TEST 4
    MBigNumber number10 = MBigNumber();
    MBigNumber number11 = MBigNumber(-79);
    number10 += number11;
    os << "TEST 4:" << std::endl;
    os << "Testing \"+=\" operator -> (0 + (-79)). Expected: -79: " << number10 << std::endl;
    os << std::endl;

    ////TEST 5
    MBigNumber number13 = MBigNumber(-101);
    MBigNumber number14 = MBigNumber();
    number13 += number14;
    os << "TEST 5:" << std::endl;
    os << "Testing \"+=\" operator -> ((-101) + 0). Expected: -101: " << number13 << std::endl;
    os << std::endl;

    //TEST 6
    MBigNumber number16 = MBigNumber(-101);
    MBigNumber number17 = MBigNumber(-5);
    number16 += number17;
    os << "TEST 6:" << std::endl;
    os << "Testing \"+=\" operator -> ((-101) + (-5)). Expected: -106: " << number16 << std::endl;
    os << std::endl;

    //TEST 7
    MBigNumber number19 = MBigNumber(-101);
    MBigNumber number20 = MBigNumber(-99);
    number19 += number20;
    os << "TEST 7:" << std::endl;
    os << "Testing \"+=\" operator -> ((-101) + (-99)). Expected: -200: " << number19 << std::endl;
    os << std::endl;

    //TEST 8
    MBigNumber number22 = MBigNumber(-991);
    MBigNumber number23 = MBigNumber(-99);
    number22 += number23;
    os << "TEST 7:" << std::endl;
    os << "Testing \"+=\" operator -> ((-991) + (-99)). Expected: -1090: " << number22 << std::endl;
    os << std::endl;

    //TEST 9
    MBigNumber number25 = MBigNumber(991);
    MBigNumber number26 = MBigNumber(-99);
    number25 += number26;
    os << "TEST 9:" << std::endl;
    os << "Testing \"+=\" operator -> (991 + (-99)). Expected: 892: " << number25 << std::endl;
    os << std::endl;

    //TEST 10
    MBigNumber number28 = MBigNumber(-100100098);
    MBigNumber number29 = MBigNumber(65699);
    number28 += number29;
    os << "TEST 10:" << std::endl;
    os << "Testing \"+=\" operator -> (-100100098 + 65699). Expected: -100,034,399: " << number28 << std::endl;
    os << std::endl;
}

void MBigNumberTests::OperatorMinusTests(std::ostream& os)
{
    // - Operator tests
    os << "\"-\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    MBigNumber number1 = MBigNumber(3);
    MBigNumber number2 = MBigNumber(2);
    MBigNumber number3 = number1 - number2;

    os << "TEST 1:" << std::endl;
    os << "Testing \"-\" operator -> (3 - 2). Expected: 1: " << number3 << std::endl;
    os << std::endl;

    //TEST 2
    MBigNumber number4 = MBigNumber(1345);
    MBigNumber number5 = MBigNumber(1234);
    MBigNumber number6 = number4 - number5;

    os << "TEST 2:" << std::endl;
    os << "Testing \"-\" operator -> (1345 - 1234). Expected: 111: " << number6 << std::endl;
    os << std::endl;

    //TEST 3
    MBigNumber number7 = MBigNumber(1234);
    MBigNumber number8 = MBigNumber(1345);
    MBigNumber number9 = number7 - number8;

    os << "TEST 3:" << std::endl;
    os << "Testing \"-\" operator -> (1234 - 1345). Expected: -111: " << number9 << std::endl;
    os << std::endl;

    //TEST 4
    MBigNumber number10 = MBigNumber(1234);
    MBigNumber number11 = MBigNumber(13450);
    MBigNumber number12 = number10 - number11;

    os << "TEST 4:" << std::endl;
    os << "Testing \"-\" operator -> (1234 - 13450). Expected: -12 216: " << number12 << std::endl;
    os << std::endl;

    //TEST 5
    MBigNumber number13 = MBigNumber(-1234);
    MBigNumber number14 = MBigNumber(-1230);
    MBigNumber number15 = number13 - number14;

    os << "TEST 5:" << std::endl;
    os << "Testing \"-\" operator -> (-1234 - -1230). Expected: -4: " << number15 << std::endl;
    os << std::endl;

    //TEST 6
    MBigNumber number16 = MBigNumber(-1234);
    MBigNumber number17 = MBigNumber(-13457);
    MBigNumber number18 = number16 - number17;

    os << "TEST 6:" << std::endl;
    os << "Testing \"-\" operator -> (-1234 - -13457). Expected: 12 223: " << number18 << std::endl;
    os << std::endl;

    //TEST 7
    MBigNumber number19 = MBigNumber(-10101);
    MBigNumber number20 = MBigNumber(-99);
    MBigNumber number21 = number19 - number20;

    os << "TEST 7:" << std::endl;
    os << "Testing \"-\" operator -> (-10101 - -99). Expected: -10 002: " << number21 << std::endl;
    os << std::endl;

    //TEST 8
    MBigNumber number22 = MBigNumber(-10001000000);
    MBigNumber number23 = MBigNumber(-9956123);
    MBigNumber number24 = number22 - number23;

    os << "TEST 8:" << std::endl;
    os << "Testing \"-\" operator -> (-10001000000 - -9956123). Expected: -9,991,043,877: " << number24 << std::endl;
    os << std::endl;

    //TEST 9
    MBigNumber number25 = MBigNumber(-9956123);
    MBigNumber number26 = MBigNumber(-10001000000);
    MBigNumber number27 = number25 - number26;

    os << "TEST 9:" << std::endl;
    os << "Testing \"-\" operator -> (-9956123 - -10001000000). Expected: 9,991,043,877: " << number27 << std::endl;
    os << std::endl;

    //TEST 9
    MBigNumber number28 = MBigNumber(-9956123);
    MBigNumber number29 = MBigNumber();
    MBigNumber number30 = number28 - number29;

    os << "TEST 9:" << std::endl;
    os << "Testing \"-\" operator -> (-9956123 - 0). Expected: -9956123: " << number30 << std::endl;
    os << std::endl;

    //TEST 10
    MBigNumber number31 = MBigNumber();
    MBigNumber number32 = MBigNumber(156);
    MBigNumber number33 = number31 - number32;

    os << "TEST 10:" << std::endl;
    os << "Testing \"-\" operator -> (0 - 156). Expected: -156: " << number33 << std::endl;
    os << std::endl;

    //TEST 11
    MBigNumber number34 = MBigNumber();
    MBigNumber number35 = MBigNumber();
    MBigNumber number36 = number34 - number35;

    os << "TEST 11:" << std::endl;
    os << "Testing \"-\" operator -> (0 - 0). Expected: 0: " << number36 << std::endl;
    os << std::endl;

    //TEST 12
    MBigNumber number37 = MBigNumber(15678);
    MBigNumber number38 = MBigNumber(-979900);
    MBigNumber number39 = number37 - number38;

    os << "TEST 12:" << std::endl;
    os << "Testing \"-\" operator -> (15678 - -979900). Expected: 995,578: " << number39 << std::endl;
    os << std::endl;

    //TEST 13
    MBigNumber number40 = MBigNumber(-9560);
    MBigNumber number41 = MBigNumber(11256);
    MBigNumber number42 = number40 - number41;

    os << "TEST 13:" << std::endl;
    os << "Testing \"-\" operator -> (-9560 - 11256). Expected: -20,816: " << number42 << std::endl;
    os << std::endl;
}

void MBigNumberTests::OperatorMinusAndEqualsTests(std::ostream& os)
{
    // - Operator tests
    os << "\"-=\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    MBigNumber number1 = MBigNumber(3);
    MBigNumber number2 = MBigNumber(2);
    number1 -= number2;

    os << "TEST 1:" << std::endl;
    os << "Testing \"-=\" operator -> (3 - 2). Expected: 1: " << number1 << std::endl;
    os << std::endl;

    //TEST 2
    MBigNumber number4 = MBigNumber(1345);
    MBigNumber number5 = MBigNumber(1234);
    number4 -= number5;

    os << "TEST 2:" << std::endl;
    os << "Testing \"-=\" operator -> (1345 - 1234). Expected: 111: " << number4 << std::endl;
    os << std::endl;

    //TEST 3
    MBigNumber number7 = MBigNumber(1234);
    MBigNumber number8 = MBigNumber(1345);
    number7 -= number8;

    os << "TEST 3:" << std::endl;
    os << "Testing \"-=\" operator -> (1234 - 1345). Expected: -111: " << number7 << std::endl;
    os << std::endl;

    //TEST 4
    MBigNumber number10 = MBigNumber(1234);
    MBigNumber number11 = MBigNumber(13450);
    number10 -= number11;

    os << "TEST 4:" << std::endl;
    os << "Testing \"-=\" operator -> (1234 - 13450). Expected: -12 216: " << number10 << std::endl;
    os << std::endl;

    //TEST 5
    MBigNumber number13 = MBigNumber(-1234);
    MBigNumber number14 = MBigNumber(-1230);
    number13 -= number14;

    os << "TEST 5:" << std::endl;
    os << "Testing \"-=\" operator -> (-1234 - -1230). Expected: -4: " << number13 << std::endl;
    os << std::endl;

    //TEST 6
    MBigNumber number16 = MBigNumber(-1234);
    MBigNumber number17 = MBigNumber(-13457);
    number16 -= number17;

    os << "TEST 6:" << std::endl;
    os << "Testing \"-=\" operator -> (-1234 - -13457). Expected: 12 223: " << number16 << std::endl;
    os << std::endl;

    //TEST 7
    MBigNumber number19 = MBigNumber(-10101);
    MBigNumber number20 = MBigNumber(-99);
    number19 -= number20;

    os << "TEST 7:" << std::endl;
    os << "Testing \"-=\" operator -> (-10101 - -99). Expected: -10 002: " << number19 << std::endl;
    os << std::endl;

    //TEST 8
    MBigNumber number22 = MBigNumber(-10001000000);
    MBigNumber number23 = MBigNumber(-9956123);
    number22 -= number23;

    os << "TEST 8:" << std::endl;
    os << "Testing \"-=\" operator -> (-10001000000 - -9956123). Expected: -9,991,043,877: " << number22 << std::endl;
    os << std::endl;

    //TEST 9
    MBigNumber number25 = MBigNumber(-9956123);
    MBigNumber number26 = MBigNumber(-10001000000);
    number25 -= number26;

    os << "TEST 9:" << std::endl;
    os << "Testing \"-=\" operator -> (-9956123 - -10001000000). Expected: 9,991,043,877: " << number25 << std::endl;
    os << std::endl;

    //TEST 10
    MBigNumber number28 = MBigNumber(-9956123);
    MBigNumber number29 = MBigNumber();
    number28 -= number29;

    os << "TEST 10:" << std::endl;
    os << "Testing \"-=\" operator -> (-9956123 - 0). Expected: -9956123: " << number28 << std::endl;
    os << std::endl;

    //TEST 11
    MBigNumber number31 = MBigNumber();
    MBigNumber number32 = MBigNumber(156);
    number31 -= number32;

    os << "TEST 11:" << std::endl;
    os << "Testing \"-=\" operator -> (0 - 156). Expected: -156: " << number31 << std::endl;
    os << std::endl;

    //TEST 12
    MBigNumber number34 = MBigNumber();
    MBigNumber number35 = MBigNumber();
    number34 -= number35;

    os << "TEST 12:" << std::endl;
    os << "Testing \"-=\" operator -> (0 - 0). Expected: 0: " << number34 << std::endl;
    os << std::endl;

    //TEST 13
    MBigNumber number37 = MBigNumber(15678);
    MBigNumber number38 = MBigNumber(-979900);
    number37 -= number38;

    os << "TEST 13:" << std::endl;
    os << "Testing \"-=\" operator -> (15678 - -979900). Expected: 995,578: " << number37 << std::endl;
    os << std::endl;

    //TEST 14
    MBigNumber number40 = MBigNumber(-9560);
    MBigNumber number41 = MBigNumber(11256);
    number40 -= number41;

    os << "TEST 14:" << std::endl;
    os << "Testing \"-=\" operator -> (-9560 - 11256). Expected: -20,816: " << number40 << std::endl;
    os << std::endl;
}

void MBigNumberTests::OperatorIncrementTests(std::ostream& os)
{
    // ++ Operator tests
    os << "\"++\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 2:" << std::endl;
    MBigNumber number1 = MBigNumber(1000);
    os << "Testing \"++1000\" operation --> Expected: 1001: " << ++number1 << std::endl;
    os << "New value of MBigNumber is: Expected: 1001: " << number1;
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2:" << std::endl;
    MBigNumber number2 = MBigNumber(1000);
    os << "Testing \"1000++\" operation --> Expected: 1000: " << number2++ << std::endl;
    os << "New value of MBigNumber is: Expected: 1001: " << number2;
    os << std::endl;
    os << std::endl;
}

void MBigNumberTests::OperatorDecrementTests(std::ostream& os)
{
    // -- Operator tests
    os << "\"--\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 2:" << std::endl;
    MBigNumber number1 = MBigNumber(1000);
    os << "Testing \"--1000\" operation --> Expected: 999: " << --number1 << std::endl;
    os << "New value of MBigNumber is: Expected: 999: " << number1;
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2:" << std::endl;
    MBigNumber number2 = MBigNumber(1000);
    os << "Testing \"1000--\" operation --> Expected: 1000: " << number2-- << std::endl;
    os << "New value of MBigNumber is: Expected: 999: " << number2;
    os << std::endl;
    os << std::endl;
}

void MBigNumberTests::OperatorMultiplyTests(std::ostream& os)
{
    // - Operator tests
    os << "\"*\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    MBigNumber number1 = MBigNumber(3);
    MBigNumber number2 = MBigNumber(2);
    MBigNumber number3 = number1 * number2;

    os << "TEST 1:" << std::endl;
    os << "Testing \"*\" operator -> (3 * 2). Expected: 6: " << number3 << std::endl;
    os << std::endl;

    //TEST 2
    MBigNumber number4 = MBigNumber();
    MBigNumber number5 = MBigNumber(2);
    MBigNumber number6 = number4 * number5;

    os << "TEST 2:" << std::endl;
    os << "Testing \"*\" operator -> (0 * 2). Expected: 0: " << number6 << std::endl;
    os << std::endl;

    //TEST 3
    MBigNumber number7 = MBigNumber(-100);
    MBigNumber number8 = MBigNumber();
    MBigNumber number9 = number7 * number8;

    os << "TEST 3:" << std::endl;
    os << "Testing \"*\" operator -> (-100 * 0). Expected: 0: " << number9 << std::endl;
    os << std::endl;

    //TEST 4
    MBigNumber number10 = MBigNumber(56846);
    MBigNumber number11 = MBigNumber(3501);
    MBigNumber number12 = number10 * number11;

    os << "TEST 4:" << std::endl;
    os << "Testing \"*\" operator -> (56846 * 3501). Expected: 199,017,846: " << number12 << std::endl;
    os << std::endl;

    //TEST 5
    MBigNumber number13 = MBigNumber(-3129);
    MBigNumber number14 = MBigNumber(309);
    MBigNumber number15 = number13 * number14;

    os << "TEST 5:" << std::endl;
    os << "Testing \"*\" operator -> (-3129 * 309). Expected: -966,861: " << number15 << std::endl;
    os << std::endl;

    //TEST 6
    MBigNumber number16 = MBigNumber(-9999);
    MBigNumber number17 = MBigNumber(-1001);
    MBigNumber number18 = number16 * number17;

    os << "TEST 6:" << std::endl;
    os << "Testing \"*\" operator -> (-9999 * -1001). Expected: 10,008,999: " << number18 << std::endl;
    os << std::endl;

    //TEST 7
    MBigNumber number19 = MBigNumber(-99);
    MBigNumber number20 = MBigNumber(1000);
    MBigNumber number21 = number19 * number20;

    os << "TEST 7:" << std::endl;
    os << "Testing \"*\" operator -> (-99 * 1000). Expected: -99,000: " << number21 << std::endl;
    os << std::endl;
}

void MBigNumberTests::OperatorMultiplyAndEqualsTests(std::ostream& os)
{
    // - Operator tests
    os << "\"*=\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    MBigNumber number1 = MBigNumber(3);
    MBigNumber number2 = MBigNumber(2);
    number1 *= number2;

    os << "TEST 1:" << std::endl;
    os << "Testing \"*=\" operator -> (3 * 2). Expected: 6: " << number1 << std::endl;
    os << std::endl;

    //TEST 2
    MBigNumber number4 = MBigNumber();
    MBigNumber number5 = MBigNumber(2);
    number4 *= number5;

    os << "TEST 2:" << std::endl;
    os << "Testing \"*=\" operator -> (0 * 2). Expected: 0: " << number4 << std::endl;
    os << std::endl;

    //TEST 3
    MBigNumber number7 = MBigNumber(-100);
    MBigNumber number8 = MBigNumber();
    number7 *= number8;

    os << "TEST 3:" << std::endl;
    os << "Testing \"*=\" operator -> (-100 * 0). Expected: 0: " << number7 << std::endl;
    os << std::endl;

    //TEST 4
    MBigNumber number10 = MBigNumber(56846);
    MBigNumber number11 = MBigNumber(3501);
    number10 *= number11;

    os << "TEST 4:" << std::endl;
    os << "Testing \"*=\" operator -> (56846 * 3501). Expected: 199,017,846: " << number10 << std::endl;
    os << std::endl;

    //TEST 5
    MBigNumber number13 = MBigNumber(-3129);
    MBigNumber number14 = MBigNumber(309);
    number13 *= number14;

    os << "TEST 5:" << std::endl;
    os << "Testing \"*=\" operator -> (-3129 * 309). Expected: -966,861: " << number13 << std::endl;
    os << std::endl;

    //TEST 6
    MBigNumber number16 = MBigNumber(-9999);
    MBigNumber number17 = MBigNumber(-1001);
    number16 *= number17;

    os << "TEST 6:" << std::endl;
    os << "Testing \"*=\" operator -> (-9999 * -1001). Expected: 10,008,999: " << number16 << std::endl;
    os << std::endl;

    //TEST 7
    MBigNumber number19 = MBigNumber(-99);
    MBigNumber number20 = MBigNumber(1000);
    number19 *= number20;

    os << "TEST 7:" << std::endl;
    os << "Testing \"*=\" operator -> (-99 * 1000). Expected: -99,000: " << number19 << std::endl;
    os << std::endl;

    //TEST 8
    MBigNumber number21 = MBigNumber(-99);
    MBigNumber number22 = MBigNumber(-1);
    number21 *= number22;

    os << "TEST 8:" << std::endl;
    os << "Testing \"*=\" operator -> (-99 * -1). Expected: 99: " << number21 << std::endl;
    os << std::endl;
}

void MBigNumberTests::OperatorDivideTests(std::ostream& os)
{
    // / Operator tests
    os << "\"/\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    MBigNumber number1 = MBigNumber();
    MBigNumber number2 = MBigNumber(1);
    MBigNumber number3 = number1 / number2;

    os << "TEST 1:" << std::endl;
    os << "Testing \"/\" operator -> (0 / 1). Expected: 0: " << number3 << std::endl;
    os << std::endl;

    //TEST 2
    MBigNumber number4 = MBigNumber(100);
    MBigNumber number5 = MBigNumber(101);
    MBigNumber number6 = number4 / number5;

    os << "TEST 2:" << std::endl;
    os << "Testing \"/\" operator -> (100 / 101). Expected: 0: " << number6 << std::endl;
    os << std::endl;

    //TEST 3
    MBigNumber number7 = MBigNumber(100);
    MBigNumber number8 = MBigNumber(-101);
    MBigNumber number9 = number7 / number8;

    os << "TEST 3:" << std::endl;
    os << "Testing \"/\" operator -> (100 / -101). Expected: 0: " << number9 << std::endl;
    os << std::endl;

    //TEST 4
    MBigNumber number10 = MBigNumber(5474253);
    MBigNumber number11 = MBigNumber(1);
    MBigNumber number12 = number10 / number11;

    os << "TEST 4:" << std::endl;
    os << "Testing \"/\" operator -> (5474253 / 1). Expected: 5474253: " << number12 << std::endl;
    os << std::endl;

    //TEST 5
    MBigNumber number13 = MBigNumber(225);
    MBigNumber number14 = MBigNumber(15);
    MBigNumber number15 = number13 / number14;

    os << "TEST 5:" << std::endl;
    os << "Testing \"/\" operator -> (225 / 15). Expected: 15: " << number15 << std::endl;
    os << std::endl;

    //TEST 6
    MBigNumber number16 = MBigNumber(225);
    MBigNumber number17 = MBigNumber(5);
    MBigNumber number18 = number16 / number17;

    os << "TEST 6:" << std::endl;
    os << "Testing \"/\" operator -> (225 / 5). Expected: 45: " << number18 << std::endl;
    os << std::endl;

    //TEST 7
    MBigNumber number19 = MBigNumber(29773);
    MBigNumber number20 = MBigNumber(-19);
    MBigNumber number21 = number19 / number20;

    os << "TEST 7:" << std::endl;
    os << "Testing \"/\" operator -> (29773 / -19). Expected: -1567: " << number21 << std::endl;
    os << std::endl;

    //TEST 8
    MBigNumber number22 = MBigNumber(-14670163);
    MBigNumber number23 = MBigNumber(163);
    MBigNumber number24 = number22 / number23;

    os << "TEST 8:" << std::endl;
    os << "Testing \"/\" operator -> (-14670163 / 163). Expected: -90,001: " << number24 << std::endl;
    os << std::endl;

    //TEST 9
    MBigNumber number25 = MBigNumber(-14670187);
    MBigNumber number26 = MBigNumber(163);
    MBigNumber number27 = number25 / number26;

    os << "TEST 9:" << std::endl;
    os << "Testing \"/\" operator -> (-14670187 / 163). Expected: -90,001: " << number27 << std::endl;
    os << std::endl;

    //TEST 10
    MBigNumber number28 = MBigNumber("38715980218941283691286446981264988961289");
    MBigNumber number29 = MBigNumber(-356);
    MBigNumber number30 = number28 / number29;

    os << "TEST 10:" << std::endl;
    os << "Testing \"/\" operator -> (38715980218941283691286446981264988961289 / -356). Expected: -1.0875275e+38: " << number30 << std::endl;
    os << std::endl;
}

void MBigNumberTests::OperatorDivideAndEqualsTests(std::ostream& os)
{
    // /= Operator tests
    os << "\"/=\" Operator TESTS: " << std::endl << std::endl;

    //TEST 1
    MBigNumber number1 = MBigNumber();
    MBigNumber number2 = MBigNumber(1);
    number1 /= number2;

    os << "TEST 1:" << std::endl;
    os << "Testing \"/=\" operator -> (0 / 1). Expected: 0: " << number1 << std::endl;
    os << std::endl;

    //TEST 2
    MBigNumber number4 = MBigNumber(100);
    MBigNumber number5 = MBigNumber(101);
    number4 /= number5;

    os << "TEST 2:" << std::endl;
    os << "Testing \"/=\" operator -> (100 / 101). Expected: 0: " << number4 << std::endl;
    os << std::endl;

    //TEST 3
    MBigNumber number7 = MBigNumber(100);
    MBigNumber number8 = MBigNumber(-101);
    number7 /= number8;

    os << "TEST 3:" << std::endl;
    os << "Testing \"/=\" operator -> (100 / -101). Expected: 0: " << number7 << std::endl;
    os << std::endl;

    //TEST 4
    MBigNumber number10 = MBigNumber(5474253);
    MBigNumber number11 = MBigNumber(1);
    number10 /= number11;

    os << "TEST 4:" << std::endl;
    os << "Testing \"/=\" operator -> (5474253 / 1). Expected: 5474253: " << number10 << std::endl;
    os << std::endl;

    //TEST 5
    MBigNumber number13 = MBigNumber(225);
    MBigNumber number14 = MBigNumber(15);
    number13 /= number14;

    os << "TEST 5:" << std::endl;
    os << "Testing \"/=\" operator -> (225 / 15). Expected: 15: " << number13 << std::endl;
    os << std::endl;

    //TEST 6
    MBigNumber number16 = MBigNumber(225);
    MBigNumber number17 = MBigNumber(5);
    number16 /= number17;

    os << "TEST 6:" << std::endl;
    os << "Testing \"/=\" operator -> (225 / 5). Expected: 45: " << number16 << std::endl;
    os << std::endl;

    //TEST 7
    MBigNumber number19 = MBigNumber(29773);
    MBigNumber number20 = MBigNumber(-19);
    number19 /= number20;

    os << "TEST 7:" << std::endl;
    os << "Testing \"/=\" operator -> (29773 / -19). Expected: -1567: " << number19 << std::endl;
    os << std::endl;

    //TEST 8
    MBigNumber number22 = MBigNumber(-14670163);
    MBigNumber number23 = MBigNumber(163);
    number22 /= number23;

    os << "TEST 8:" << std::endl;
    os << "Testing \"/=\" operator -> (-14670163 / 163). Expected: -90,001: " << number22 << std::endl;
    os << std::endl;

    //TEST 9
    MBigNumber number25 = MBigNumber(-14670187);
    MBigNumber number26 = MBigNumber(163);
    number25 /= number26;

    os << "TEST 9:" << std::endl;
    os << "Testing \"/=\" operator -> (-14670187 / 163). Expected: -90,001: " << number25 << std::endl;
    os << std::endl;

    //TEST 10
    MBigNumber number28 = MBigNumber("38715980218941283691286446981264988961289");
    MBigNumber number29 = MBigNumber(-356);
    number28 /= number29;

    os << "TEST 10:" << std::endl;
    os << "Testing \"/=\" operator -> (38715980218941283691286446981264988961289 / -356). Expected: -1.0875275e+38: " << number28 << std::endl;
    os << std::endl;
}

void MBigNumberTests::OperatorPercentTests(std::ostream& os)
{
    // / Operator tests
    os << "\"%\" Operator TESTS: " << std::endl << std::endl;
    os << (-14670187 % 163);
    //TEST 1
    MBigNumber number1 = MBigNumber();
    MBigNumber number2 = MBigNumber(1);
    MBigNumber number3 = number1 % number2;

    os << "TEST 1:" << std::endl;
    os << "Testing \"%\" operator -> (0 % 1). Expected: 0: " << number3 << std::endl;
    os << std::endl;

    //TEST 2
    MBigNumber number4 = MBigNumber(100);
    MBigNumber number5 = MBigNumber(101);
    MBigNumber number6 = number4 % number5;

    os << "TEST 2:" << std::endl;
    os << "Testing \"%\" operator -> (100 % 101). Expected: 100: " << number6 << std::endl;
    os << std::endl;

    //TEST 3
    MBigNumber number7 = MBigNumber(100);
    MBigNumber number8 = MBigNumber(-101);
    MBigNumber number9 = number7 % number8;

    os << "TEST 3:" << std::endl;
    os << "Testing \"%\" operator -> (100 % -101). Expected: 100: " << number9 << std::endl;
    os << std::endl;

    //TEST 4
    MBigNumber number10 = MBigNumber(5474253);
    MBigNumber number11 = MBigNumber(1);
    MBigNumber number12 = number10 % number11;

    os << "TEST 4:" << std::endl;
    os << "Testing \"%\" operator -> (5474253 % 1). Expected: 0: " << number12 << std::endl;
    os << std::endl;

    //TEST 5
    MBigNumber number13 = MBigNumber(225);
    MBigNumber number14 = MBigNumber(15);
    MBigNumber number15 = number13 % number14;

    os << "TEST 5:" << std::endl;
    os << "Testing \"%\" operator -> (225 % 15). Expected: 0: " << number15 << std::endl;
    os << std::endl;

    //TEST 6
    MBigNumber number16 = MBigNumber(225);
    MBigNumber number17 = MBigNumber(5);
    MBigNumber number18 = number16 % number17;

    os << "TEST 6:" << std::endl;
    os << "Testing \"%\" operator -> (225 % 5). Expected: 0: " << number18 << std::endl;
    os << std::endl;

    //TEST 7
    MBigNumber number19 = MBigNumber(29773);
    MBigNumber number20 = MBigNumber(-19);
    MBigNumber number21 = number19 % number20;

    os << "TEST 7:" << std::endl;
    os << "Testing \"%\" operator -> (29773 % -19). Expected: 0: " << number21 << std::endl;
    os << std::endl;

    //TEST 8
    MBigNumber number22 = MBigNumber(-14670163);
    MBigNumber number23 = MBigNumber(163);
    MBigNumber number24 = number22 % number23;

    os << "TEST 8:" << std::endl;
    os << "Testing \"%\" operator -> (-14670163 % 163). Expected: 0: " << number24 << std::endl;
    os << std::endl;

    //TEST 9
    MBigNumber number25 = MBigNumber(-14670187);
    MBigNumber number26 = MBigNumber(163);
    MBigNumber number27 = number25 % number26;

    os << "TEST 9:" << std::endl;
    os << "Testing \"%\" operator -> (-14670187 % 163). Expected: -24: " << number27 << std::endl;
    os << std::endl;

    //3871598021894108369 --> 289
    //38715980218941283691286446981264988961289 --> 341
    //TEST 10
    MBigNumber number28 = MBigNumber("38715980218941283691286446981264988961289");
    MBigNumber number29 = MBigNumber(-356);
    MBigNumber number30 = number28 % number29;

    os << "TEST 10:" << std::endl;
    os << "Testing \"%\" operator -> (38715980218941283691286446981264988961289 % -356). Expected: 341: " << number30 << std::endl;
    //os << std::endl;
    os << "Testing \"%\" operator PART 2-> ( (38715980218941283691286446981264988961289 / -356)*-356 + 341 ). Expected: 38715980218941283691286446981264988961289: "
        << (((number28 / number29) * number29) + number30) << std::endl;
    os << std::endl;

}

void MBigNumberTests::OperatorPercentAndEqualsTests(std::ostream& os)
{
    // / Operator tests
    os << "\"%=\" Operator TESTS: " << std::endl << std::endl;
    os << (-14670187 % 163);
    //TEST 1
    MBigNumber number1 = MBigNumber();
    MBigNumber number2 = MBigNumber(1);
    number1 %= number2;

    os << "TEST 1:" << std::endl;
    os << "Testing \"%=\" operator -> (0 %= 1). Expected: 0: " << number1 << std::endl;
    os << std::endl;

    //TEST 2
    MBigNumber number4 = MBigNumber(100);
    MBigNumber number5 = MBigNumber(101);
    number4 %= number5;

    os << "TEST 2:" << std::endl;
    os << "Testing \"%=\" operator -> (100 %= 101). Expected: 100: " << number4 << std::endl;
    os << std::endl;

    //TEST 3
    MBigNumber number7 = MBigNumber(100);
    MBigNumber number8 = MBigNumber(-101);
    number7 %= number8;

    os << "TEST 3:" << std::endl;
    os << "Testing \"%=\" operator -> (100 %= -101). Expected: 100: " << number7 << std::endl;
    os << std::endl;

    //TEST 4
    MBigNumber number10 = MBigNumber(5474253);
    MBigNumber number11 = MBigNumber(1);
    number10 %= number11;

    os << "TEST 4:" << std::endl;
    os << "Testing \"%=\" operator -> (5474253 %= 1). Expected: 0: " << number10 << std::endl;
    os << std::endl;

    //TEST 5
    MBigNumber number13 = MBigNumber(225);
    MBigNumber number14 = MBigNumber(15);
    number13 %= number14;

    os << "TEST 5:" << std::endl;
    os << "Testing \"%=\" operator -> (225 %= 15). Expected: 0: " << number13 << std::endl;
    os << std::endl;

    //TEST 6
    MBigNumber number16 = MBigNumber(225);
    MBigNumber number17 = MBigNumber(5);
    number16 %= number17;

    os << "TEST 6:" << std::endl;
    os << "Testing \"%=\" operator -> (225 %= 5). Expected: 0: " << number16 << std::endl;
    os << std::endl;

    //TEST 7
    MBigNumber number19 = MBigNumber(29773);
    MBigNumber number20 = MBigNumber(-19);
    number19 %= number20;

    os << "TEST 7:" << std::endl;
    os << "Testing \"%=\" operator -> (29773 %= -19). Expected: 0: " << number19 << std::endl;
    os << std::endl;

    //TEST 8
    MBigNumber number22 = MBigNumber(-14670163);
    MBigNumber number23 = MBigNumber(163);
    number22 %= number23;

    os << "TEST 8:" << std::endl;
    os << "Testing \"%=\" operator -> (-14670163 %= 163). Expected: 0: " << number22 << std::endl;
    os << std::endl;

    //TEST 9
    MBigNumber number25 = MBigNumber(-14670187);
    MBigNumber number26 = MBigNumber(163);
    number25 %= number26;

    os << "TEST 9:" << std::endl;
    os << "Testing \"%=\" operator -> (-14670187 %= 163). Expected: -24: " << number25 << std::endl;
    os << std::endl;

    //3871598021894108369 --> 289
    //38715980218941283691286446981264988961289 --> 341
    //TEST 10
    MBigNumber number28 = MBigNumber("38715980218941283691286446981264988961289");
    MBigNumber number29 = MBigNumber(-356);
    number28 %= number29;

    os << "TEST 10:" << std::endl;
    os << "Testing \"%=\" operator -> (38715980218941283691286446981264988961289 %= -356). Expected: 341: " << number28 << std::endl;
    os << std::endl;
}

void MBigNumberTests::OperatorDivideAndPercentMemoryLeakTests()
{
    // / Operator tests
    std::cout << "\"/\" Operator TESTS FOR MEMORY LEAKS: " << std::endl << std::endl;
    std::cout << "Starting test...";
    //TEST 1
    MBigNumber number1 = MBigNumber();
    MBigNumber number2 = MBigNumber(1);

    for (long long int i = 0; i < 1000000; i++)
    {
        MBigNumber number3 = number1 / number2;
    }

    //TEST 2
    MBigNumber number4 = MBigNumber(100);
    MBigNumber number5 = MBigNumber(101);
    for (long long int i = 0; i < 1000000; i++)
    {
        MBigNumber number6 = number4 % number5;
    }

    //TEST 5
    MBigNumber number13 = MBigNumber(225);
    MBigNumber number14 = MBigNumber(15);
    for (long long int i = 0; i < 1000000; i++)
    {
        number13 /= number14;
    }

    std::cout << "TEST ENDED --> ";
}

//Tests from my assistants Pesho and Lubo from OOP practicum
void MBigNumberTests::PeshoAndLuboTests(std::ostream& os)
{
    os << "TESTS FROM PESHO AND LUBO: \n\n";

    //CORRECT
    os << std::boolalpha << (MBigNumber("7643276342876783246893247") > MBigNumber("4767846784647856547476")) << std::endl;
    os << std::boolalpha << (MBigNumber("4767846784647856547476") < MBigNumber("7643276342876783246893247")) << std::endl;
    os << std::boolalpha << (MBigNumber("7643276342876783246893247") != MBigNumber("4767846784647856547476")) << std::endl;
    os << std::boolalpha << (MBigNumber("7643276342876783246893247") == MBigNumber("7643276342876783246893247")) << std::endl;


    os << std::boolalpha << ((MBigNumber("12345678901234567890") + MBigNumber("4354678097643135")) == MBigNumber("12350033579332211025")) << std::endl;
    os << std::boolalpha << ((MBigNumber("12345678901234567890") - MBigNumber("4354678097643135")) == MBigNumber("12341324223136924755")) << std::endl;
    os << std::boolalpha << ((MBigNumber("12345678901234567890") * MBigNumber("4354678097643135")) == MBigNumber("53761457511741137249987999149935150")) << std::endl;
    os << std::boolalpha << ((MBigNumber("12345678901234567890") / MBigNumber("4354678097643135")) == MBigNumber("2835")) << std::endl;
    os << std::boolalpha << ((MBigNumber("12345678901234567890") % MBigNumber("4354678097643135")) == MBigNumber("166494416280165")) << std::endl;

    //DEBUG SHIT
    MBigNumber DebugShit = MBigNumber("-12345678901234567890") + MBigNumber("4354678097643135");
    os << std::boolalpha << ((MBigNumber("-12345678901234567890") + MBigNumber("4354678097643135")) == MBigNumber("-12341324223136924755")) << std::endl;
    os << std::boolalpha << ((MBigNumber("-12345678901234567890") * MBigNumber("4354678097643135")) == MBigNumber("-53761457511741137249987999149935150")) << std::endl;

    os << std::endl;
}

//Tests for copying shit correctly without access violation reading exceptions or memory leaks
void MBigNumberTests::SpecialTests(std::ostream& os)
{
    os << "SPECIAL Tests for copying shit correctly without access violation reading exceptions or memory leaks: \n\n";
    //CORRECT
    MBigNumber otherMBigNumber = MBigNumber("4354678097643135");
    MBigNumber anotherMBigNumber = MBigNumber("12345678901234567890");
    MBigNumber otherAnotherMBigNumber = MBigNumber("12350033579332211025");
    os << otherMBigNumber << " + " << anotherMBigNumber << " = " << otherAnotherMBigNumber << "??? --> ";

    os << std::boolalpha << ((otherMBigNumber + anotherMBigNumber) == otherAnotherMBigNumber) << std::endl;

    MBigNumber copyOfOtherMBigNumber = otherMBigNumber;
    MBigNumber copyOfAnotherMBigNumber = anotherMBigNumber;
    MBigNumber copyOfOtherAnotherMBigNumber = otherAnotherMBigNumber;

    os << "Is copyOfOtherMBigNumber == otherMBigNumber -> " << std::boolalpha << (copyOfOtherMBigNumber == otherMBigNumber) << std::endl;
    os << "Is copyOfAnotherMBigNumber == anotherMBigNumber -> " << std::boolalpha << (copyOfAnotherMBigNumber == anotherMBigNumber) << std::endl;
    os << "Is copyOfOtherAnotherMBigNumber == otherAnotherMBigNumber -> " << std::boolalpha << (copyOfOtherAnotherMBigNumber == otherAnotherMBigNumber) << std::endl;
    os << "Is copyOfOtherAnotherMBigNumber2 == copyOfOtherAnotherMBigNumber -> " << std::boolalpha << ((copyOfOtherMBigNumber += copyOfAnotherMBigNumber) == copyOfOtherAnotherMBigNumber) << std::endl;

    os << std::endl;
}

void MBigNumberTests::getNumberTests(std::ostream& os)
{
    // getNumber() tests
    os << "TESTING getNumber() TESTS: " << std::endl << std::endl;

    //TEST 1
    MBigNumber number1 = MBigNumber();
    os << "TEST 1:" << std::endl;
    os << "Testing getNumber() operator -> (0). Expected: 0: " << number1.getNumber();
    os << std::endl;
    os << std::endl;

    //TEST 2
    MBigNumber number2 = MBigNumber("-55346");
    os << "TEST 2:" << std::endl;
    os << "Testing getNumber() operator -> (-55346). Expected: -55,346: " << number2.getNumber();
    os << std::endl;
    os << std::endl;

    //TEST 3
    MBigNumber number3 = MBigNumber("-123456789");
    os << "TEST 3:" << std::endl;
    os << "Testing getNumber() operator -> (-123456789). Expected: -123,456,789: " << number3.getNumber();
    os << std::endl;
    os << std::endl;

    //TEST 4
    MBigNumber number4 = MBigNumber("-1234");
    os << "TEST 4:" << std::endl;
    os << "Testing getNumber() operator -> (-1234). Expected: -1234: " << number4.getNumber();
    os << std::endl;
    os << std::endl;
}

void MBigNumberTests::getNumberRawTests(std::ostream& os)
{
    // getNumberRaw() tests
    os << "TESTING getNumberRaw() TESTS: " << std::endl << std::endl;

    //TEST 1
    MBigNumber number1 = MBigNumber();
    os << "TEST 1:" << std::endl;
    os << "Testing getNumberRaw() operator -> (0). Expected: 0: " << number1.getNumberRaw();
    os << std::endl;
    os << std::endl;

    //TEST 2
    MBigNumber number2 = MBigNumber("-55346");
    os << "TEST 2:" << std::endl;
    os << "Testing getNumberRaw() operator -> (-55346). Expected: -55346: " << number2.getNumberRaw();
    os << std::endl;
    os << std::endl;

    //TEST 3
    MBigNumber number3 = MBigNumber("-1234567890");
    os << "TEST 3:" << std::endl;
    os << "Testing getNumberRaw() operator -> (-1234567890). Expected: -1234567890: " << number3.getNumberRaw();
    os << std::endl;
    os << std::endl;

    //TEST 4
    MBigNumber number4 = MBigNumber("-1234");
    os << "TEST 4:" << std::endl;
    os << "Testing getNumber() operator -> (-1234). Expected: -1234: " << number4.getNumberRaw();
    os << std::endl;
    os << std::endl;
}

void MBigNumberTests::getNumberMemoryLeakTest()
{
    std::cout << "Start...";
    MBigNumber memoryLeakExpression("10");
    while (true)
    {
        mstring answer = memoryLeakExpression.getNumber();
    }
}

void MBigNumberTests::runTests(std::ostream& os)
{
    std::cout << "Start the tests for MBigNumber! ";
    if (&os != &std::cout)
    {
        std::cout << "The test results are being outputted to text file with name: " << MBigNumberTests::OUTPUTFILE_NAME << std::endl;
        time_t timetoday;
        time(&timetoday);
        char* timeOfRunningTheTests = StringManip::replaceFirst(ctime(&timetoday), "\n", "");
        os << "---------------------------- " << "" << timeOfRunningTheTests << " ----------------------------\n\n";
        delete[] timeOfRunningTheTests;
    }

    //// CONSTRUCTOR TESTS
    ConstructorAndCopyAndAssignTests(os);
    //
    //// READING OPERATOR TESTS
    //ReadingOperatorTests();
    //
    //// ARITHMETIC AND COMPARATIVE OPERATORS TESTS
    //os << std::endl << "TESTS FOR ARITHMETIC AND COMPARATIVE OPERATORS:\n" << std::endl;
    //
    //// == Operator and != Operator Tests
    //EqualsAndNotEqualsTests(os);
    //
    //// > Operator Tests
    //OperatorGreaterThanTests(os);
    //
    //// >= Operator Tests
    //OperatorGreaterThanOrEqualsTests(os);
    //
    //// < Operator Tests
    //OperatorLessThanTests(os);
    //
    //// <= Operator Tests
    //OperatorLessThanOrEqualsTests(os);
    //
    //// + Operator Tests
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
