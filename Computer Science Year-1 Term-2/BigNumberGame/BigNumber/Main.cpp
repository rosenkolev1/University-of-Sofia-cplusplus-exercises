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
    std::cout << "Expression solving TESTS: " << std::endl << std::endl;

    solveExpressionNoParenthesis_AdditionAndMinusTests();
    
    solveExpressionNoParenthesis_MultiplyTests();
    
    solveExpressionNoParenthesis_DivideTests();
    
    solveExpressionNoParenthesis_PercentTests();
}

int main()
{
    //BigNumber tests
    //BigNumberTests::runTests();

    //Big 4 tests
    //expressionBig4Tests();

    //Solving expression tests
    solveExpressionNoParenthesisTests();
}