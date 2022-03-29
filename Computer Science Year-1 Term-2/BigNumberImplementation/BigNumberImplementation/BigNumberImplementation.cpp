﻿#include <iostream>
#include "BigNumber.h"

void OperatorGreaterThanTestTemplate(const char testTitle[], const char textDescription[], 
    const BigNumber& bigNumber1, const BigNumber& bigNumber2, bool newLine)
{
    if(testTitle != NULL) std::cout << testTitle << std::endl;
    std::cout << textDescription <<
        (bigNumber1 > bigNumber2 ? "TRUE" : "FALSE") << std::endl;
    if(newLine) std::cout << std::endl;
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

    ////TEST 5
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

int main()
{
    int someNumberInt = 5678;
    char someNumberChar[] = "1234";
    BigNumber defaultBigNumber = BigNumber();
    BigNumber someBigNumberInt = BigNumber(someNumberInt);
    BigNumber someBigNumberChar = BigNumber(someNumberChar);

    //OLD
    std::cout << "initial values: TESTS FOR NON-COPY CONSTRUCTORS" << std::endl;
    std::cout << "defaultBigNumber: "; defaultBigNumber.printOutNumber();
    std::cout << "someBigNumberInt: "; someBigNumberInt.printOutNumber();
    std::cout << "someBigNumberChar: "; someBigNumberChar.printOutNumber();

    std::cout << std::endl << "new values: TESTS FOR ASSIGNMENT AND COPY OPERATORS AND CONSTRUCTOR" << std::endl;
    defaultBigNumber = someNumberInt;
    std::cout << "defaultBigNumber: "; defaultBigNumber.printOutNumber();
    BigNumber copyOfBigNumberChar = BigNumber(someBigNumberChar);
    std::cout << "copyOfBigNumberChar: "; copyOfBigNumberChar.printOutNumber();
    someBigNumberInt = someBigNumberChar;
    std::cout << "defaultBigNumber: "; defaultBigNumber.printOutNumber();

    // Operator tests
    std::cout << std::endl << "TESTS FOR ARITHMETIC AND COMPARATIVE OPERATORS" << std::endl;

    //== Operator tests
    std::cout << "\"==\" Operator TESTS: " << std::endl;
    std::cout << "Testing \"==\" operator (defaultBigNumber == someBigNumberInt): (Expected: false)" << 
        (defaultBigNumber == someBigNumberInt ? "true" : "false") << std::endl;
    std::cout << "Testing \"==\" operator (someBigNumberChar == someBigNumberInt): (Expected: true)" <<
        (someBigNumberChar == someBigNumberInt ? "true" : "false") << std::endl;
    std::cout << std::endl;

    //!= Operator tests
    std::cout << "\"!=\" Operator TESTS: " << std::endl;
    std::cout << "Testing \"==\" operator (defaultBigNumber != someBigNumberInt): (Expected: true)" << 
        (defaultBigNumber != someBigNumberInt ? "true" : "false") << std::endl;
    std::cout << "Testing \"==\" operator (someBigNumberChar != someBigNumberInt): (Expected: false)" << 
        (someBigNumberChar != someBigNumberInt ? "true" : "false") << std::endl;
    std::cout << std::endl;

    // > Operator Tests
    OperatorGreaterThanTests();

    // < Operator Tests
    OperatorLessThanTests();

    // + Operator Tests
    OperatorSumTests();

    // += Operator Tests
    OperatorSumAndEqualsTests();

    // - Operator Tests
    OperatorMinusTests();

    // -= Operator Tests
    OperatorMinusAndEqualsTests();

    // * Operator Tests TO BE CONTINUED
}


