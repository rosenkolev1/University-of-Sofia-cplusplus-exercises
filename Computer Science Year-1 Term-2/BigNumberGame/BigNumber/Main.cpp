// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BigNumber.h"
#include "BigNumberDivisionResult.h"
#include "BigNumberTests.h"
#include "BigNumberEquation.h"

//TODO: move equation tests to their own class

void expressionBig4Tests()
{
    //BigNumberTests::runTests();
    BigNumberExpression expression1 = BigNumberExpression();
    char someExpression[] = "Some equation";
    char anotherExpression[] = "anotherEquation";
    BigNumberExpression expression2(someExpression);
    BigNumberExpression expression3(anotherExpression);

    std::cout << "Expression 1: Expected: " << "{empty}" << ": " << (expression1.getExpression() == nullptr ? "{empty}" : "WRONG") << std::endl;
    std::cout << "Expression 2: Expected: " << someExpression << ": " << expression2.getExpression() << std::endl;
    std::cout << "Expression 3: Expected: " << anotherExpression << ": " << expression3.getExpression() << std::endl;

    std::cout << std::endl;

    expression1 = expression2;
    std::cout << "Testing \"expression1 = expression2;\" \n";
    std::cout << "Expression 1: Expected: " << someExpression << ": " << expression1.getExpression() << std::endl;

    std::cout << std::endl;

    expression2 = expression3;
    std::cout << "Testing \"expression2 = expression3;\" \n";
    std::cout << "Expression 2: Expected: " << anotherExpression << ": " << expression2.getExpression() << std::endl;

    std::cout << std::endl;

    BigNumberExpression expression4(expression1);
    std::cout << "Testing \"BigNumberEquation expression4(expression1);\" \n";
    std::cout << "Expression 4: Expected: " << someExpression << ": " << expression4.getExpression() << std::endl;

    std::cout << std::endl;
}

void solveExpressionNoParenthesis_SingleNumberTests()
{
    std::cout << "Expression solving TESTS for single number expressions: " << std::endl << std::endl;

    char expressionString1[] = "1125699";
    BigNumberExpression expression1(expressionString1);
    int expectedOutput1 = 1125699;
    std::cout << "Testing expression -> (" << expressionString1 << "). Expected: " << expectedOutput1 << ": " << expression1.evaluteExpression();
    std::cout << std::endl;

    char expressionString2[] = "-1125699";
    BigNumberExpression expression2(expressionString2);
    int expectedOutput2 = -1125699;
    std::cout << "Testing expression -> (" << expressionString2 << "). Expected: " << expectedOutput2 << ": " << expression2.evaluteExpression();
    std::cout << std::endl;

    char expressionString3[] = "+-1125699";
    BigNumberExpression expression3(expressionString3);
    int expectedOutput3 = +-1125699;
    std::cout << "Testing expression -> (" << expressionString3 << "). Expected: " << expectedOutput3 << ": " << expression3.evaluteExpression();
    std::cout << std::endl;

    char expressionString4[] = "-+1125699";
    BigNumberExpression expression4(expressionString4);
    int expectedOutput4 = -+1125699;
    std::cout << "Testing expression -> (" << expressionString4 << "). Expected: " << expectedOutput4 << ": " << expression4.evaluteExpression();
    std::cout << std::endl;

    char expressionString5[] = "--1125699";
    BigNumberExpression expression5(expressionString5);
    int expectedOutput5 = 1125699;
    std::cout << "Testing expression -> (" << expressionString5 << "). Expected: " << expectedOutput5 << ": " << expression5.evaluteExpression();
    std::cout << std::endl;

    char expressionString6[] = "+1125699";
    BigNumberExpression expression6(expressionString6);
    int expectedOutput6 = 1125699;
    std::cout << "Testing expression -> (" << expressionString6 << "). Expected: " << expectedOutput6 << ": " << expression6.evaluteExpression();
    std::cout << std::endl;
}

void solveExpressionNoParenthesis_AdditionAndMinusTests()
{
    std::cout << "Expression solving TESTS for + and - operators: " << std::endl << std::endl;

    char expressionString1[] = "10+5";
    BigNumberExpression expression1(expressionString1);
    int expectedOutput1 = 10+5;
    std::cout << "Testing expression -> ("<< expressionString1 <<"). Expected: " << expectedOutput1 << ": " << expression1.evaluteExpression();
    std::cout << std::endl;

    char expressionString2[] = "57-19";
    BigNumberExpression expression2(expressionString2);
    int expectedOutput2 = 57 - 19;
    std::cout << "Testing expression -> (" << expressionString2 << "). Expected: " << expectedOutput2 << ": " << expression2.evaluteExpression();
    std::cout << std::endl;

    char expressionString3[] = "-57-19";
    BigNumberExpression expression3(expressionString3);
    int expectedOutput3 = -57 - 19;
    std::cout << "Testing expression -> (" << expressionString3 << "). Expected: " << expectedOutput3 << ": " << expression3.evaluteExpression();
    std::cout << std::endl;

    char expressionString4[] = "-345-+15";
    BigNumberExpression expression4(expressionString4);
    int expectedOutput4 = -345 - +15;
    std::cout << "Testing expression -> (" << expressionString4 << "). Expected: " << expectedOutput4 << ": " << expression4.evaluteExpression();
    std::cout << std::endl;

    char expressionString5[] = "-345+-15";
    BigNumberExpression expression5(expressionString5);
    int expectedOutput5 = -345 + -15;
    std::cout << "Testing expression -> (" << expressionString5 << "). Expected: " << expectedOutput5 << ": " << expression5.evaluteExpression();
    std::cout << std::endl;

    char expressionString6[] = "-345--15";
    BigNumberExpression expression6(expressionString6);
    int expectedOutput6 = -345-(-15);
    std::cout << "Testing expression -> (" << expressionString6 << "). Expected: " << expectedOutput6 << ": " << expression6.evaluteExpression();
    std::cout << std::endl;

    char expressionString7[] = "-345--15+30";
    BigNumberExpression expression7(expressionString7);
    int expectedOutput7 = -345-(-15) + 30;
    std::cout << "Testing expression -> (" << expressionString7 << ").Expected: "<< expectedOutput7 <<": " << expression7.evaluteExpression();
    std::cout << std::endl;

    char expressionString8[] = "--345--15+-30";
    BigNumberExpression expression8(expressionString8);
    int expectedOutput8 = -(-345)-(-15) + -30;
    std::cout << "Testing expression -> (" << expressionString8 << ").Expected: "<< expectedOutput8 <<": " << expression8.evaluteExpression();
    std::cout << std::endl;

}

void solveExpressionNoParenthesis_MultiplyTests()
{
    std::cout << "Expression solving TESTS for * operator: " << std::endl << std::endl;

    char expressionString9[] = "4*3";
    BigNumberExpression expression9(expressionString9);
    int expectedOutput9 = 4 * 3;
    std::cout << "Testing expression -> (" << expressionString9 << ").Expected: "<< expectedOutput9 <<": " << expression9.evaluteExpression();
    std::cout << std::endl;

    char expressionString10[] = "-4*3";
    BigNumberExpression expression10(expressionString10);
    int expectedOutput10 = -4 * 3;
    std::cout << "Testing expression -> (" << expressionString10 << ").Expected: "<< expectedOutput10 <<": " << expression10.evaluteExpression();
    std::cout << std::endl;

    char expressionString11[] = "4*-3";
    BigNumberExpression expression11(expressionString11);
    int expectedOutput11 = 4 * -3;
    std::cout << "Testing expression -> (" << expressionString11 << ").Expected: "<< expectedOutput11 <<": " << expression11.evaluteExpression();
    std::cout << std::endl;

    char expressionString12[] = "4*0";
    BigNumberExpression expression12(expressionString12);
    int expectedOutput12 = 4 * 0;
    std::cout << "Testing expression -> (" << expressionString12 << ").Expected: "<< expectedOutput12 <<": " << expression12.evaluteExpression();
    std::cout << std::endl;

    char expressionString13[] = "-0*3";
    BigNumberExpression expression13(expressionString13);
    int expectedOutput13 = -0*3;
    std::cout << "Testing expression -> (" << expressionString13 << ").Expected: "<< expectedOutput13 <<": " << expression13.evaluteExpression();
    std::cout << std::endl;

    char expressionString14[] = "-0*-0";
    BigNumberExpression expression14(expressionString14);
    int expectedOutput14 = -0 * -0;
    std::cout << "Testing expression -> (" << expressionString14 << ").Expected: "<< expectedOutput14 <<": " << expression14.evaluteExpression();
    std::cout << std::endl;

    char expressionString15[] = "125-5*5 + 1";
    BigNumberExpression expression15(expressionString15);
    int expectedOutput15 = 125 - 5 * 5 + 1;
    std::cout << "Testing expression -> (" << expressionString15 << ").Expected: "<< expectedOutput15 <<": " << expression15.evaluteExpression();
    std::cout << std::endl;

    char expressionString16[] = "125+-5*5-1*-9";
    BigNumberExpression expression16(expressionString16);
    int expectedOutput16 = 125 + -5 * 5 - 1 * -9;
    std::cout << "Testing expression -> (" << expressionString16 << ").Expected: "<< expectedOutput16 <<": " << expression16.evaluteExpression();
    std::cout << std::endl;

    char expressionString17[] = "-125+-5*5-+1*-9";
    BigNumberExpression expression17(expressionString17);
    int expectedOutput17 = -125 + -5 * 5 - +1 * -9;
    std::cout << "Testing expression -> (" << expressionString17 << ").Expected: "<< expectedOutput17 <<": " << expression17.evaluteExpression();
    std::cout << std::endl;
}

void solveExpressionNoParenthesis_DivideTests()
{
    std::cout << "Expression solving TESTS for / operator: " << std::endl << std::endl;

    char expressionString18[] = "125/5";
    BigNumberExpression expression18(expressionString18);
    int expectedOutput18 = 125 / 5;
    std::cout << "Testing expression -> (" << expressionString18 << ").Expected: "<< expectedOutput18 <<": " << expression18.evaluteExpression();
    std::cout << std::endl;

    char expressionString19[] = "0/5";
    int expectedOutput19 = 0/5;
    BigNumberExpression expression19(expressionString19);
    std::cout << "Testing expression -> (" << expressionString19 << ").Expected: "<< expectedOutput19 <<": " << expression19.evaluteExpression();
    std::cout << std::endl;

    char expressionString20[] = "125/0";
    BigNumberExpression expression20(expressionString20);
    std::cout << "Testing expression -> (" << expressionString20 << ").Expected: Exception thrown: ";
    try
    {
        std::cout << expression20.evaluteExpression();
    }
    catch (...)
    {
        std::cout << "Exception thrown\n";
    }
    std::cout << std::endl;

    char expressionString21[] = "0/0";
    BigNumberExpression expression21(expressionString21);
    std::cout << "Testing expression -> (" << expressionString21 << ").Expected: Exception thrown: ";
    try
    {
        std::cout << expression20.evaluteExpression();
    }
    catch (...)
    {
        std::cout << "Exception thrown\n";
    }
    std::cout << std::endl;

    char expressionString22[] = "-125/3";
    BigNumberExpression expression22(expressionString22);
    int expectedOutput22 = -125 / 3;
    std::cout << "Testing expression -> (" << expressionString22 << ").Expected: "<< expectedOutput22 <<": " << expression22.evaluteExpression();
    std::cout << std::endl;

    char expressionString23[] = "125/-3";
    BigNumberExpression expression23(expressionString23);
    int expectedOutput23 = 125 / -3;
    std::cout << "Testing expression -> (" << expressionString23 << ").Expected: "<< expectedOutput23 <<": " << expression23.evaluteExpression();
    std::cout << std::endl;

    char expressionString24[] = "-125/-3";
    BigNumberExpression expression24(expressionString24);
    int expectedOutput24 = -125 / -3;
    std::cout << "Testing expression -> (" << expressionString24 << ").Expected: "<< expectedOutput24 <<": " << expression24.evaluteExpression();
    std::cout << std::endl;

    char expressionString25[] = "-125+-5*5/-3-+3";
    BigNumberExpression expression25(expressionString25);
    int expectedOutput25 = -125 + -5 * 5 / -3 - +3;
    std::cout << "Testing expression -> (" << expressionString25 << ").Expected: "<< expectedOutput25 <<": " << expression25.evaluteExpression();
    std::cout << std::endl;

    char expressionString26[] = "-125+-3/5*5/-3-+3";
    BigNumberExpression expression26(expressionString26);
    int expectedOutput26 = -125 + -3 / 5 * 5 / -3 - +3;
    std::cout << "Testing expression -> (" << expressionString26 << ").Expected: "<< expectedOutput26 <<": " << expression26.evaluteExpression();
    std::cout << std::endl;

    char expressionString27[] = "100/500*500";
    BigNumberExpression expression27(expressionString27);
    int expectedOutput27 = 100 / 500 * 500;
    std::cout << "Testing expression -> (" << expressionString27 << ").Expected: " << expectedOutput27 << ": " << expression27.evaluteExpression();
    std::cout << std::endl;
}

void solveExpressionNoParenthesis_PercentTests()
{
    std::cout << "Expression solving TESTS for % operator: " << std::endl << std::endl;

    char expressionString27[] = "125%5";
    BigNumberExpression expression27(expressionString27);
    int expectedOuput27 = 125 % 5;
    std::cout << "Testing expression -> (" << expressionString27 << ").Expected: "<< expectedOuput27 <<": " << expression27.evaluteExpression();
    std::cout << std::endl;

    char expressionString28[] = "0%5";
    BigNumberExpression expression28(expressionString28);
    int expectedOuput28 = 0 % 5;
    std::cout << "Testing expression -> (" << expressionString28 << ").Expected: "<< expectedOuput28 <<": " << expression28.evaluteExpression();;
    std::cout << std::endl;

    char expressionString29[] = "125%0";
    BigNumberExpression expression29(expressionString29);
    std::cout << "Testing expression -> (" << expressionString29 << ").Expected: Exception thrown: ";
    try
    {
        std::cout << expression29.evaluteExpression();
    }
    catch (...)
    {
        std::cout << "Exception thrown\n";
    }
    std::cout << std::endl;

    char expressionString30[] = "0%0";
    BigNumberExpression expression30(expressionString30);
    std::cout << "Testing expression -> (" << expressionString30 << ").Expected: Exception thrown: ";
    try
    {
        std::cout << expression30.evaluteExpression();
    }
    catch (...)
    {
        std::cout << "Exception thrown\n";
    }
    std::cout << std::endl;

    char expressionString31[] = "125%3";
    BigNumberExpression expression31(expressionString31);
    int expectedOuput31 = 125 % 3;
    std::cout << "Testing expression -> (" << expressionString31 << ").Expected: "<< expectedOuput31 <<": " << expression31.evaluteExpression();
    std::cout << std::endl;

    char expressionString32[] = "125%-3";
    BigNumberExpression expression32(expressionString32);
    int expectedOuput32 = 125 % -3;
    std::cout << "Testing expression -> (" << expressionString32 << ").Expected: "<< expectedOuput32 <<": " << expression32.evaluteExpression();
    std::cout << std::endl;

    char expressionString33[] = "-125%3";
    BigNumberExpression expression33(expressionString33);
    int expectedOuput33 = -125 % 3;
    std::cout << "Testing expression -> (" << expressionString33 << ").Expected: "<< expectedOuput33 <<": " << expression33.evaluteExpression();
    std::cout << std::endl;

    char expressionString34[] = "+-125%-3";
    BigNumberExpression expression34(expressionString34);
    int expectedOuput34 = +-125 % -3;
    std::cout << "Testing expression -> (" << expressionString34 << ").Expected: "<< expectedOuput34 <<": " << expression34.evaluteExpression();
    std::cout << std::endl;

    char expressionString35[] = "25-125%-3*5";
    BigNumberExpression expression35(expressionString35);
    int expectedOuput35 = 25 - 125 % -3 * 5;
    std::cout << "Testing expression -> (" << expressionString35 << ").Expected: "<< expectedOuput35 <<": " << expression35.evaluteExpression();
    std::cout << std::endl;

    char expressionString36[] = "25-125/-3%5";
    BigNumberExpression expression36(expressionString36);
    int expectedOuput36 = 25 - 125 / -3 % 5;
    std::cout << "Testing expression -> (" << expressionString36 << ").Expected: "<< expectedOuput36 <<": " << expression36.evaluteExpression();
    std::cout << std::endl;
}

void solveExpressionNoParenthesisTests()
{
    // Expression solving tests
    std::cout << "Expression solving TESTS WITHOUT PARENTHESIS: " << std::endl << std::endl;

    solveExpressionNoParenthesis_SingleNumberTests();
    
    solveExpressionNoParenthesis_AdditionAndMinusTests();
    
    solveExpressionNoParenthesis_MultiplyTests();
    
    solveExpressionNoParenthesis_DivideTests();
    
    solveExpressionNoParenthesis_PercentTests();
}

void solveExpressionParenthesis_SingleNumberTests()
{
    std::cout << "Expression solving TESTS for single number expressions: " << std::endl << std::endl;

    std::cout << "TEST 1: " << std::endl;
    char expressionString1[] = "(1125699)";
    BigNumberExpression expression1(expressionString1);
    int expectedOutput1 = 1125699;
    std::cout << "Testing expression -> (" << expressionString1 << "). Expected: " << expectedOutput1 << ": " << expression1.evaluteExpression();
    std::cout << std::endl;
    
    std::cout << "TEST 2: " << std::endl;
    char expressionString2[] = "(-1125699)";
    BigNumberExpression expression2(expressionString2);
    int expectedOutput2 = -1125699;
    std::cout << "Testing expression -> (" << expressionString2 << "). Expected: " << expectedOutput2 << ": " << expression2.evaluteExpression();
    std::cout << std::endl;
    
    std::cout << "TEST 3: " << std::endl;
    char expressionString3[] = "(+-1125699)";
    BigNumberExpression expression3(expressionString3);
    int expectedOutput3 = +-1125699;
    std::cout << "Testing expression -> (" << expressionString3 << "). Expected: " << expectedOutput3 << ": " << expression3.evaluteExpression();
    std::cout << std::endl;
    
    std::cout << "TEST 4: " << std::endl;
    char expressionString4[] = "(-+1125699)";
    BigNumberExpression expression4(expressionString4);
    int expectedOutput4 = -+1125699;
    std::cout << "Testing expression -> (" << expressionString4 << "). Expected: " << expectedOutput4 << ": " << expression4.evaluteExpression();
    std::cout << std::endl;
    
    std::cout << "TEST 5: " << std::endl;
    char expressionString5[] = "(--1125699)";
    BigNumberExpression expression5(expressionString5);
    int expectedOutput5 = 1125699;
    std::cout << "Testing expression -> (" << expressionString5 << "). Expected: " << expectedOutput5 << ": " << expression5.evaluteExpression();
    std::cout << std::endl;
    
    std::cout << "TEST 6: " << std::endl;
    char expressionString6[] = "(+1125699)";
    BigNumberExpression expression6(expressionString6);
    int expectedOutput6 = 1125699;
    std::cout << "Testing expression -> (" << expressionString6 << "). Expected: " << expectedOutput6 << ": " << expression6.evaluteExpression();
    std::cout << std::endl;
    
    std::cout << "TEST 7: " << std::endl;
    char expressionString7[] = "-(1125699)";
    BigNumberExpression expression7(expressionString7);
    int expectedOutput7 = -(1125699);
    std::cout << "Testing expression -> (" << expressionString7 << "). Expected: " << expectedOutput7 << ": " << expression7.evaluteExpression();
    std::cout << std::endl;

    std::cout << "TEST 8: " << std::endl;
    char expressionString8[] = "-(+-1125699)";
    BigNumberExpression expression8(expressionString8);
    int expectedOutput8 = -(+-1125699);
    std::cout << "Testing expression -> (" << expressionString8 << "). Expected: " << expectedOutput8 << ": " << expression8.evaluteExpression();
    std::cout << std::endl;
    
    std::cout << "TEST 9: " << std::endl;
    char expressionString9[] = "-(--1125699)";
    BigNumberExpression expression9(expressionString9);
    int expectedOutput9 = -(1125699);
    std::cout << "Testing expression -> (" << expressionString9 << "). Expected: " << expectedOutput9 << ": " << expression9.evaluteExpression();
    std::cout << std::endl;
    
    std::cout << "TEST 10: " << std::endl;
    char expressionString10[] = "-+(--(-1125699))";
    BigNumberExpression expression10(expressionString10);
    int expectedOutput10 = -+((-1125699));
    std::cout << "Testing expression -> (" << expressionString10 << "). Expected: " << expectedOutput10 << ": " << expression10.evaluteExpression();
    std::cout << std::endl;

    std::cout << "TEST 11: " << std::endl;
    char expressionString11[] = "(-(-((1125699))))";
    BigNumberExpression expression11(expressionString11);
    int expectedOutput11 = (-(-((1125699))));
    std::cout << "Testing expression -> (" << expressionString11 << "). Expected: " << expectedOutput11 << ": " << expression11.evaluteExpression();
    std::cout << std::endl;
}

void solveExpressionParenthesis_AdditionAndMinusTests()
{
    std::cout << "Expression solving TESTS for + and - operators: " << std::endl << std::endl;

    std::cout << "TEST 1: " << std::endl;
    char expressionString1[] = "(10 + 5) + 5";
    BigNumberExpression expression1(expressionString1);
    int expectedOutput1 = (10 + 5) + 5;
    std::cout << "Testing expression -> (" << expressionString1 << "). Expected: " << expectedOutput1 << ": " << expression1.evaluteExpression();
    std::cout << std::endl;

    std::cout << "TEST 2: " << std::endl;
    char expressionString2[] = "(10 + -5) + -(5 - 6)-(-(-(14--(10+5-4- -3))))";
    BigNumberExpression expression2(expressionString2);
    int expectedOutput2 = (10 + -5) + -(5 - 6) - (-(-(14+(10 + 5 - 4 - -3)))); //Expected: 6 - 28 = -22
    std::cout << "Testing expression -> (" << expressionString2 << "). Expected: " << expectedOutput2 << ": " << expression2.evaluteExpression();
    std::cout << std::endl;

    std::cout << "TEST 3: " << std::endl;
    char expressionString3[] = "(-(10 + -5 + -5 - 6-(--(14--10+5-4- -3))))";
    BigNumberExpression expression3(expressionString3);
    int expectedOutput3 = (-(10 + -5 + -5 - 6 - ((14+10 + 5 - 4 - -3)))); //Expected: -(-6 - 28) = 34
    std::cout << "Testing expression -> (" << expressionString3 << "). Expected: " << expectedOutput3 << ": " << expression3.evaluteExpression();
    std::cout << std::endl;
}

void solveExpressionParenthesis_DivideTests()
{
    std::cout << "Expression solving TESTS for / operator: " << std::endl << std::endl;

    std::cout << "TEST 1: " << std::endl;
    char expressionString1[] = "(125/5)";
    BigNumberExpression expression1(expressionString1);
    int expectedOutput1 = (125 / 5);
    std::cout << "Testing expression -> (" << expressionString1 << ").Expected: " << expectedOutput1 << ": " << expression1.evaluteExpression();
    std::cout << std::endl;

    std::cout << "TEST 2: " << std::endl;
    char expressionString2[] = "100/(2+3)";
    BigNumberExpression expression2(expressionString2);
    int expectedOutput2 = 100 / (2 + 3);
    std::cout << "Testing expression -> (" << expressionString2 << ").Expected: " << expectedOutput2 << ": " << expression2.evaluteExpression();
    std::cout << std::endl;

    std::cout << "TEST 3: " << std::endl;
    char expressionString3[] = "-(100/((576 - 35/(9-2)*2/(12 - 4/2))/575*6/(3+4-1)*3 - 3))";
    BigNumberExpression expression3(expressionString3);
    //int expectedOutput3 = -(100/((576 - 35/(9-2)*2/(12 - 4/2))/575*6/(3+4-1)*3 - 3)); Expected -(100/0) -> Exception thrown
    std::cout << "Testing expression -> (" << expressionString3 << ").Expected: Exception thrown: ";
    try
    {
        std::cout << expression3.evaluteExpression();
    }
    catch (...)
    {
        std::cout << "Exception thrown\n";
    }
    std::cout << std::endl;

    std::cout << "TEST 4: " << std::endl;
    char expressionString4[] = "-(100/(576 - 35/(9-2)*2/(12 - 4/2))/575*6/(3+4-1)*3 - 3)";
    BigNumberExpression expression4(expressionString4);
    int expectedOutput4 = -(100/(576 - 35/(9-2)*2/(12 - 4/2))/575*6/(3+4-1)*3 - 3); //Expected -(-3) -> 3
    std::cout << "Testing expression -> (" << expressionString4 << ").Expected: "<< expectedOutput4 <<": " << expression4.evaluteExpression();;
    std::cout << std::endl;
}

void solveExpressionParenthesis_MultiplyTests()
{
    std::cout << "Expression solving TESTS for * operator: " << std::endl << std::endl;

    std::cout << "TEST 1: " << std::endl;
    char expressionString1[] = "(4*3)";
    BigNumberExpression expression1(expressionString1);
    int expectedOutput1 = (4 * 3);
    std::cout << "Testing expression -> (" << expressionString1 << ").Expected: " << expectedOutput1 << ": " << expression1.evaluteExpression();
    std::cout << std::endl;

    std::cout << "TEST 2: " << std::endl;
    char expressionString2[] = "4*(3-2)";
    BigNumberExpression expression2(expressionString2);
    int expectedOutput2 = 4 * (3 - 2);
    std::cout << "Testing expression -> (" << expressionString2 << ").Expected: " << expectedOutput2 << ": " << expression2.evaluteExpression();
    std::cout << std::endl;

    std::cout << "TEST 3: " << std::endl;
    char expressionString3[] = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))";
    BigNumberExpression expression3(expressionString3);
    int expectedOutput3 = (10 + -5) * 7 + -2 * 3 * (5 - 3 * 6) - (-(-2 * (14+(10 + 5 - 4 - -3)))); //Expected: 57
    std::cout << "Testing expression -> (" << expressionString3 << ").Expected: " << expectedOutput3 << ": " << expression3.evaluteExpression();
    std::cout << std::endl;

    std::cout << "TEST 4: " << std::endl;
    char expressionString4[] = "(-1*(2*(-2*((10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))))))";
    BigNumberExpression expression4(expressionString4);
    int expectedOutput4 = (-1 * (2 * (-2 * ((10 + -5) * 7 + -2 * 3 * (5 - 3 * 6) - (-(-2 * (14+(10 + 5 - 4 - -3)))))))); //Expected: 228
    std::cout << "Testing expression -> (" << expressionString4 << ").Expected: " << expectedOutput4 << ": " << expression4.evaluteExpression();
    std::cout << std::endl;
}

void solveExpressionParenthesis_PercentTests()
{
    std::cout << "Expression solving TESTS for % operator: " << std::endl << std::endl;

    std::cout << "TEST 1: " << std::endl;
    char expressionString1[] = "(125%5)";
    BigNumberExpression expression1(expressionString1);
    int expectedOuput1 = (125 % 5);
    std::cout << "Testing expression -> (" << expressionString1 << ").Expected: " << expectedOuput1 << ": " << expression1.evaluteExpression();
    std::cout << std::endl;

    std::cout << "TEST 2: " << std::endl;
    char expressionString2[] = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; 
    BigNumberExpression expression2(expressionString2);
    int expectedOuput2 = ((1000 - 1001) - (((100 - 15 % (5 * 4)) / 2 - 42) % 5 + 1000) % (200 + 100 * (3 - 1))) % -7; //Expected: -5 //-201%-7=28(-5)
    std::cout << "Testing expression -> (" << expressionString2 << ").Expected: " << expectedOuput2 << ": " << expression2.evaluteExpression();;
    std::cout << std::endl;

    std::cout << "TEST 3: " << std::endl;
    char expressionString3[] = "5%((100 - 15%(5*4))/2 - 42) + 1000"; //Expected 5%0 + 1000 --> Exception thrown
    BigNumberExpression expression3(expressionString3);
    std::cout << "Testing expression -> (" << expressionString3 << ").Expected: Exception thrown: ";
    try
    {
        std::cout << expression3.evaluteExpression();
    }
    catch (...)
    {
        std::cout << "Exception thrown\n";
    }
    std::cout << std::endl;
}

void solveExpressionParenthesisTests()
{
    // Expression solving tests
    std::cout << "Expression solving TESTS WITH PARENTHESIS: " << std::endl << std::endl;

    solveExpressionParenthesis_SingleNumberTests();

    solveExpressionParenthesis_AdditionAndMinusTests();

    solveExpressionParenthesis_MultiplyTests();
    
    solveExpressionParenthesis_DivideTests();
    
    solveExpressionParenthesis_PercentTests();
}

void generateExpressionTests()
{
    std::cout << "Generate expression TESTS" << std::endl << std::endl;
    srand(time(NULL));

    for (size_t i = 0; i < 50; i++)
    {
        std::cout << "TEST "<< i + 1 <<": " << std::endl;
        BigNumberExpression expression1 = BigNumberExpression();
        std::cout << "Testing the generating of an expression --> ";
        expression1.generateExpression();
        std::cout << ". Expected: TRUE: "<< (expression1.expressionIsValid() ? "TRUE" : "FALSE") << std::endl; //TODO: Create a function which checks if a generate expression is valid
        std::cout << "Answer to the expression --> ";
        try
        {
             std::cout << expression1.evaluteExpression();
        }
        catch (...)
        {
            std::cout << "Exception thrown because of division or percent by 0";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}

int main()
{
    //BigNumber tests
    //BigNumberTests::runTests();

    //Big 4 tests
    //expressionBig4Tests();

    //Solving expression tests without parenthesis
    //solveExpressionNoParenthesisTests();
    //
    ////Solving expression tests with parenthesis
    //solveExpressionParenthesisTests();

    //Generating expressions tests
    generateExpressionTests();
}