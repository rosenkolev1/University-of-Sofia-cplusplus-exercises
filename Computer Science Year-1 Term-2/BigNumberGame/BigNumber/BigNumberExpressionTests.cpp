#include "BigNumberExpressionTests.h"
#include "BigNumberExpression.h"
#include <iostream>
#include "BigNumber.h"
#include "BigNumberDivisionResult.h"
#include <fstream>

void BigNumberExpressionTests::expressionBig4Tests()
{
    //BigNumberTests::runTests();
    std::cout << "BIG 4 OF BigNumberExpression TESTS: " << std::endl << std::endl;
    BigNumberExpression expression1 = BigNumberExpression();
    char someExpression[] = " 10 + 5";
    char anotherExpression[] = "15/3";
    BigNumberExpression expression2(someExpression);
    BigNumberExpression expression3(anotherExpression);

    std::cout << "Expression 1: Expected: " << "{empty}" << ": " << (strcmp(expression1.getExpression(), "0") == 0 ? "{empty}" : "WRONG") << std::endl;
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

void BigNumberExpressionTests::expressionIsValidTests()
{
    std::cout << "EXPRESSION IS VALID TESTS: " << std::endl << std::endl;

    //TEST prep
    BigNumberExpression expression = BigNumberExpression();

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    char expressionString1[] = "";
    std::cout << "Testing if expression is valid-> " << expressionString1 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString1) ? "TRUE" : "FALSE");
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    char expressionString2[] = "  ";
    std::cout << "Testing if expression is valid-> " << expressionString2 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString2) ? "TRUE" : "FALSE");
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    char expressionString3[] = "()((()))(((()))()";
    std::cout << "Testing if expression is valid-> " << expressionString3 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString3) ? "TRUE" : "FALSE");
    std::cout << std::endl;

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    char expressionString4[] = "()((()))((())))((()))";
    std::cout << "Testing if expression is valid-> " << expressionString4 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString4) ? "TRUE" : "FALSE");
    std::cout << std::endl;

    //TEST 5
    std::cout << "TEST 5" << std::endl;
    char expressionString5[] = "15+10asd";
    std::cout << "Testing if expression is valid-> " << expressionString5 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString5) ? "TRUE" : "FALSE");
    std::cout << std::endl;

    //TEST 6-34
    for (size_t i = 0; i < BigNumberExpression::EXPRESSION_FORBIDDEN_STRINGS_COUNT; i++)
    {
        std::cout << "TEST " << i + 6 << std::endl;
        char expressionStringFirst[] = "15";
        const char* expressionStringSecond = BigNumberExpression::EXPRESSION_FORBIDDEN_STRINGS[i];
        char expressionStringThird[] = "10";

        char* finalExpression = new char[strlen(expressionStringFirst) + strlen(expressionStringSecond) + strlen(expressionStringThird) + 1];
        finalExpression[0] = '\0';
        strcat(finalExpression, expressionStringFirst);
        strcat(finalExpression, expressionStringSecond);
        strcat(finalExpression, expressionStringThird);

        std::cout << "Testing if expression is valid-> " << finalExpression << ". Expected: FALSE: " << (expression.expressionIsValid(finalExpression) ? "TRUE" : "FALSE");

        std::cout << std::endl;
        std::cout << std::endl;

        //Delete dynamic memory
        delete[] finalExpression;
    }

}
     
void BigNumberExpressionTests::solveExpressionNoParenthesis_SingleNumberTests()
{
    std::cout << "---EXPRESSION SOLVING TESTS FOR SINGLE NUMBER EXPRESSION: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    char expressionString1[] = "1125699";
    BigNumberExpression expression1(expressionString1);
    int expectedOutput1 = 1125699;
    std::cout << "Testing expression -> (" << expressionString1 << "). Expected: " << expectedOutput1 << ": " << expression1.evaluteExpression();
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    char expressionString2[] = "-1125699";
    BigNumberExpression expression2(expressionString2);
    int expectedOutput2 = -1125699;
    std::cout << "Testing expression -> (" << expressionString2 << "). Expected: " << expectedOutput2 << ": " << expression2.evaluteExpression();
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    char expressionString3[] = "+-1125699";
    BigNumberExpression expression3(expressionString3);
    int expectedOutput3 = +-1125699;
    std::cout << "Testing expression -> (" << expressionString3 << "). Expected: " << expectedOutput3 << ": " << expression3.evaluteExpression();
    std::cout << std::endl;

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    char expressionString4[] = "-+1125699";
    BigNumberExpression expression4(expressionString4);
    int expectedOutput4 = -+1125699;
    std::cout << "Testing expression -> (" << expressionString4 << "). Expected: " << expectedOutput4 << ": " << expression4.evaluteExpression();
    std::cout << std::endl;

    //TEST 5
    std::cout << "TEST 5" << std::endl;
    char expressionString5[] = "--1125699";
    BigNumberExpression expression5(expressionString5);
    int expectedOutput5 = 1125699;
    std::cout << "Testing expression -> (" << expressionString5 << "). Expected: " << expectedOutput5 << ": " << expression5.evaluteExpression();
    std::cout << std::endl;

    //TEST 6
    std::cout << "TEST 6" << std::endl;
    char expressionString6[] = "+1125699";
    BigNumberExpression expression6(expressionString6);
    int expectedOutput6 = 1125699;
    std::cout << "Testing expression -> (" << expressionString6 << "). Expected: " << expectedOutput6 << ": " << expression6.evaluteExpression();
    std::cout << std::endl;
}
     
void BigNumberExpressionTests::solveExpressionNoParenthesis_AdditionAndMinusTests()
{
    std::cout << "---EXPRESSION SOLVING TESTS FOR \"+\" AND \"-\" OPERATORS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    char expressionString1[] = "10+5";
    BigNumberExpression expression1(expressionString1);
    int expectedOutput1 = 10 + 5;
    std::cout << "Testing expression -> (" << expressionString1 << "). Expected: " << expectedOutput1 << ": " << expression1.evaluteExpression();
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    char expressionString2[] = "57-19";
    BigNumberExpression expression2(expressionString2);
    int expectedOutput2 = 57 - 19;
    std::cout << "Testing expression -> (" << expressionString2 << "). Expected: " << expectedOutput2 << ": " << expression2.evaluteExpression();
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    char expressionString3[] = "-57-19";
    BigNumberExpression expression3(expressionString3);
    int expectedOutput3 = -57 - 19;
    std::cout << "Testing expression -> (" << expressionString3 << "). Expected: " << expectedOutput3 << ": " << expression3.evaluteExpression();
    std::cout << std::endl;

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    char expressionString4[] = "-345-+15";
    BigNumberExpression expression4(expressionString4);
    int expectedOutput4 = -345 - +15;
    std::cout << "Testing expression -> (" << expressionString4 << "). Expected: " << expectedOutput4 << ": " << expression4.evaluteExpression();
    std::cout << std::endl;

    //TEST 5
    std::cout << "TEST 5" << std::endl;
    char expressionString5[] = "-345+-15";
    BigNumberExpression expression5(expressionString5);
    int expectedOutput5 = -345 + -15;
    std::cout << "Testing expression -> (" << expressionString5 << "). Expected: " << expectedOutput5 << ": " << expression5.evaluteExpression();
    std::cout << std::endl;

    //TEST 6
    std::cout << "TEST 6" << std::endl;
    char expressionString6[] = "-345--15";
    BigNumberExpression expression6(expressionString6);
    int expectedOutput6 = -345 - (-15);
    std::cout << "Testing expression -> (" << expressionString6 << "). Expected: " << expectedOutput6 << ": " << expression6.evaluteExpression();
    std::cout << std::endl;

    //TEST 7
    std::cout << "TEST 7" << std::endl;
    char expressionString7[] = "-345--15+30";
    BigNumberExpression expression7(expressionString7);
    int expectedOutput7 = -345 - (-15) + 30;
    std::cout << "Testing expression -> (" << expressionString7 << "). Expected: " << expectedOutput7 << ": " << expression7.evaluteExpression();
    std::cout << std::endl;

    //TEST 8
    std::cout << "TEST 8" << std::endl;
    char expressionString8[] = "--345--15+-30";
    BigNumberExpression expression8(expressionString8);
    int expectedOutput8 = -(-345) - (-15) + -30;
    std::cout << "Testing expression -> (" << expressionString8 << "). Expected: " << expectedOutput8 << ": " << expression8.evaluteExpression();
    std::cout << std::endl;

}
     
void BigNumberExpressionTests::solveExpressionNoParenthesis_MultiplyTests()
{
    std::cout << "---EXPRESSION SOLVING TESTS FOR \"*\" OPERATOR:" << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    char expressionString9[] = "4*3";
    BigNumberExpression expression9(expressionString9);
    int expectedOutput9 = 4 * 3;
    std::cout << "Testing expression -> (" << expressionString9 << "). Expected: " << expectedOutput9 << ": " << expression9.evaluteExpression();
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    char expressionString10[] = "-4*3";
    BigNumberExpression expression10(expressionString10);
    int expectedOutput10 = -4 * 3;
    std::cout << "Testing expression -> (" << expressionString10 << "). Expected: " << expectedOutput10 << ": " << expression10.evaluteExpression();
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    char expressionString11[] = "4*-3";
    BigNumberExpression expression11(expressionString11);
    int expectedOutput11 = 4 * -3;
    std::cout << "Testing expression -> (" << expressionString11 << "). Expected: " << expectedOutput11 << ": " << expression11.evaluteExpression();
    std::cout << std::endl;

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    char expressionString12[] = "4*0";
    BigNumberExpression expression12(expressionString12);
    int expectedOutput12 = 4 * 0;
    std::cout << "Testing expression -> (" << expressionString12 << "). Expected: " << expectedOutput12 << ": " << expression12.evaluteExpression();
    std::cout << std::endl;

    //TEST 5
    std::cout << "TEST 5" << std::endl;
    char expressionString13[] = "-0*3";
    BigNumberExpression expression13(expressionString13);
    int expectedOutput13 = -0 * 3;
    std::cout << "Testing expression -> (" << expressionString13 << "). Expected: " << expectedOutput13 << ": " << expression13.evaluteExpression();
    std::cout << std::endl;

    //TEST 6
    std::cout << "TEST 6" << std::endl;
    char expressionString14[] = "-0*-0";
    BigNumberExpression expression14(expressionString14);
    int expectedOutput14 = -0 * -0;
    std::cout << "Testing expression -> (" << expressionString14 << "). Expected: " << expectedOutput14 << ": " << expression14.evaluteExpression();
    std::cout << std::endl;

    //TEST 7
    std::cout << "TEST 7" << std::endl;
    char expressionString15[] = "125-5*5 + 1";
    BigNumberExpression expression15(expressionString15);
    int expectedOutput15 = 125 - 5 * 5 + 1;
    std::cout << "Testing expression -> (" << expressionString15 << "). Expected: " << expectedOutput15 << ": " << expression15.evaluteExpression();
    std::cout << std::endl;

    //TEST 8
    std::cout << "TEST 8" << std::endl;
    char expressionString16[] = "125+-5*5-1*-9";
    BigNumberExpression expression16(expressionString16);
    int expectedOutput16 = 125 + -5 * 5 - 1 * -9;
    std::cout << "Testing expression -> (" << expressionString16 << "). Expected: " << expectedOutput16 << ": " << expression16.evaluteExpression();
    std::cout << std::endl;

    //TEST 9
    std::cout << "TEST 9" << std::endl;
    char expressionString17[] = "-125+-5*5-+1*-9";
    BigNumberExpression expression17(expressionString17);
    int expectedOutput17 = -125 + -5 * 5 - +1 * -9;
    std::cout << "Testing expression -> (" << expressionString17 << "). Expected: " << expectedOutput17 << ": " << expression17.evaluteExpression();
    std::cout << std::endl;
}
     
void BigNumberExpressionTests::solveExpressionNoParenthesis_DivideTests()
{
    std::cout << "---EXPRESSION SOLVING TESTS FOR \"/\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    char expressionString18[] = "125/5";
    BigNumberExpression expression18(expressionString18);
    int expectedOutput18 = 125 / 5;
    std::cout << "Testing expression -> (" << expressionString18 << "). Expected: " << expectedOutput18 << ": " << expression18.evaluteExpression();
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    char expressionString19[] = "0/5";
    int expectedOutput19 = 0 / 5;
    BigNumberExpression expression19(expressionString19);
    std::cout << "Testing expression -> (" << expressionString19 << "). Expected: " << expectedOutput19 << ": " << expression19.evaluteExpression();
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    char expressionString20[] = "125/0";
    BigNumberExpression expression20(expressionString20);
    std::cout << "Testing expression -> (" << expressionString20 << "). Expected: Exception thrown: ";
    try
    {
        std::cout << expression20.evaluteExpression();
    }
    catch (...)
    {
        std::cout << "Exception thrown\n";
    }
    std::cout << std::endl;

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    char expressionString21[] = "0/0";
    BigNumberExpression expression21(expressionString21);
    std::cout << "Testing expression -> (" << expressionString21 << "). Expected: Exception thrown: ";
    try
    {
        std::cout << expression20.evaluteExpression();
    }
    catch (...)
    {
        std::cout << "Exception thrown\n";
    }
    std::cout << std::endl;

    //TEST 5
    std::cout << "TEST 5" << std::endl;
    char expressionString22[] = "-125/3";
    BigNumberExpression expression22(expressionString22);
    int expectedOutput22 = -125 / 3;
    std::cout << "Testing expression -> (" << expressionString22 << "). Expected: " << expectedOutput22 << ": " << expression22.evaluteExpression();
    std::cout << std::endl;

    //TEST 6
    std::cout << "TEST 6" << std::endl;
    char expressionString23[] = "125/-3";
    BigNumberExpression expression23(expressionString23);
    int expectedOutput23 = 125 / -3;
    std::cout << "Testing expression -> (" << expressionString23 << "). Expected: " << expectedOutput23 << ": " << expression23.evaluteExpression();
    std::cout << std::endl;

    //TEST 7
    std::cout << "TEST 7" << std::endl;
    char expressionString24[] = "-125/-3";
    BigNumberExpression expression24(expressionString24);
    int expectedOutput24 = -125 / -3;
    std::cout << "Testing expression -> (" << expressionString24 << "). Expected: " << expectedOutput24 << ": " << expression24.evaluteExpression();
    std::cout << std::endl;

    //TEST 8
    std::cout << "TEST 8" << std::endl;
    char expressionString25[] = "-125+-5*5/-3-+3";
    BigNumberExpression expression25(expressionString25);
    int expectedOutput25 = -125 + -5 * 5 / -3 - +3;
    std::cout << "Testing expression -> (" << expressionString25 << "). Expected: " << expectedOutput25 << ": " << expression25.evaluteExpression();
    std::cout << std::endl;

    //TEST 9
    std::cout << "TEST 9" << std::endl;
    char expressionString26[] = "-125+-3/5*5/-3-+3";
    BigNumberExpression expression26(expressionString26);
    int expectedOutput26 = -125 + -3 / 5 * 5 / -3 - +3;
    std::cout << "Testing expression -> (" << expressionString26 << "). Expected: " << expectedOutput26 << ": " << expression26.evaluteExpression();
    std::cout << std::endl;

    //TEST 10
    std::cout << "TEST 10" << std::endl;
    char expressionString27[] = "100/500*500";
    BigNumberExpression expression27(expressionString27);
    int expectedOutput27 = 100 / 500 * 500;
    std::cout << "Testing expression -> (" << expressionString27 << "). Expected: " << expectedOutput27 << ": " << expression27.evaluteExpression();
    std::cout << std::endl;
}
     
void BigNumberExpressionTests::solveExpressionNoParenthesis_PercentTests()
{
    std::cout << "---EXPRESSION SOLVING TESTS FOR \"%\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    char expressionString27[] = "125%5";
    BigNumberExpression expression27(expressionString27);
    int expectedOuput27 = 125 % 5;
    std::cout << "Testing expression -> (" << expressionString27 << "). Expected: " << expectedOuput27 << ": " << expression27.evaluteExpression();
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    char expressionString28[] = "0%5";
    BigNumberExpression expression28(expressionString28);
    int expectedOuput28 = 0 % 5;
    std::cout << "Testing expression -> (" << expressionString28 << "). Expected: " << expectedOuput28 << ": " << expression28.evaluteExpression();;
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    char expressionString29[] = "125%0";
    BigNumberExpression expression29(expressionString29);
    std::cout << "Testing expression -> (" << expressionString29 << "). Expected: Exception thrown: ";
    try
    {
        std::cout << expression29.evaluteExpression();
    }
    catch (...)
    {
        std::cout << "Exception thrown\n";
    }
    std::cout << std::endl;

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    char expressionString30[] = "0%0";
    BigNumberExpression expression30(expressionString30);
    std::cout << "Testing expression -> (" << expressionString30 << "). Expected: Exception thrown: ";
    try
    {
        std::cout << expression30.evaluteExpression();
    }
    catch (...)
    {
        std::cout << "Exception thrown\n";
    }
    std::cout << std::endl;

    //TEST 5
    std::cout << "TEST 5" << std::endl;
    char expressionString31[] = "125%3";
    BigNumberExpression expression31(expressionString31);
    int expectedOuput31 = 125 % 3;
    std::cout << "Testing expression -> (" << expressionString31 << "). Expected: " << expectedOuput31 << ": " << expression31.evaluteExpression();
    std::cout << std::endl;

    //TEST 6
    std::cout << "TEST 6" << std::endl;
    char expressionString32[] = "125%-3";
    BigNumberExpression expression32(expressionString32);
    int expectedOuput32 = 125 % -3;
    std::cout << "Testing expression -> (" << expressionString32 << "). Expected: " << expectedOuput32 << ": " << expression32.evaluteExpression();
    std::cout << std::endl;

    //TEST 7
    std::cout << "TEST 7" << std::endl;
    char expressionString33[] = "-125%3";
    BigNumberExpression expression33(expressionString33);
    int expectedOuput33 = -125 % 3;
    std::cout << "Testing expression -> (" << expressionString33 << "). Expected: " << expectedOuput33 << ": " << expression33.evaluteExpression();
    std::cout << std::endl;

    //TEST 8
    std::cout << "TEST 8" << std::endl;
    char expressionString34[] = "+-125%-3";
    BigNumberExpression expression34(expressionString34);
    int expectedOuput34 = +-125 % -3;
    std::cout << "Testing expression -> (" << expressionString34 << "). Expected: " << expectedOuput34 << ": " << expression34.evaluteExpression();
    std::cout << std::endl;

    //TEST 9
    std::cout << "TEST 9" << std::endl;
    char expressionString35[] = "25-125%-3*5";
    BigNumberExpression expression35(expressionString35);
    int expectedOuput35 = 25 - 125 % -3 * 5;
    std::cout << "Testing expression -> (" << expressionString35 << "). Expected: " << expectedOuput35 << ": " << expression35.evaluteExpression();
    std::cout << std::endl;

    //TEST 10
    std::cout << "TEST 10" << std::endl;
    char expressionString36[] = "25-125/-3%5";
    BigNumberExpression expression36(expressionString36);
    int expectedOuput36 = 25 - 125 / -3 % 5;
    std::cout << "Testing expression -> (" << expressionString36 << "). Expected: " << expectedOuput36 << ": " << expression36.evaluteExpression();
    std::cout << std::endl;
}
     
void BigNumberExpressionTests::solveExpressionNoParenthesisTests()
{
    // Expression solving tests
    std::cout << "EXPRESSION SOLVING TESTS WITHOUT PARENTHESIS: " << std::endl << std::endl;

    solveExpressionNoParenthesis_SingleNumberTests();

    solveExpressionNoParenthesis_AdditionAndMinusTests();

    solveExpressionNoParenthesis_MultiplyTests();

    solveExpressionNoParenthesis_DivideTests();

    solveExpressionNoParenthesis_PercentTests();
}
     
void BigNumberExpressionTests::solveExpressionParenthesis_SingleNumberTests()
{
    std::cout << "---EXPRESSION SOLVING TESTS FOR SINGLE NUMBER EXPRESSIONS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1: " << std::endl;
    char expressionString1[] = "(1125699)";
    BigNumberExpression expression1(expressionString1);
    int expectedOutput1 = 1125699;
    std::cout << "Testing expression -> (" << expressionString1 << "). Expected: " << expectedOutput1 << ": " << expression1.evaluteExpression();
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2: " << std::endl;
    char expressionString2[] = "(-1125699)";
    BigNumberExpression expression2(expressionString2);
    int expectedOutput2 = -1125699;
    std::cout << "Testing expression -> (" << expressionString2 << "). Expected: " << expectedOutput2 << ": " << expression2.evaluteExpression();
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3: " << std::endl;
    char expressionString3[] = "(+-1125699)";
    BigNumberExpression expression3(expressionString3);
    int expectedOutput3 = +-1125699;
    std::cout << "Testing expression -> (" << expressionString3 << "). Expected: " << expectedOutput3 << ": " << expression3.evaluteExpression();
    std::cout << std::endl;

    //TEST 4
    std::cout << "TEST 4: " << std::endl;
    char expressionString4[] = "(-+1125699)";
    BigNumberExpression expression4(expressionString4);
    int expectedOutput4 = -+1125699;
    std::cout << "Testing expression -> (" << expressionString4 << "). Expected: " << expectedOutput4 << ": " << expression4.evaluteExpression();
    std::cout << std::endl;

    //TEST 5
    std::cout << "TEST 5: " << std::endl;
    char expressionString5[] = "(--1125699)";
    BigNumberExpression expression5(expressionString5);
    int expectedOutput5 = 1125699;
    std::cout << "Testing expression -> (" << expressionString5 << "). Expected: " << expectedOutput5 << ": " << expression5.evaluteExpression();
    std::cout << std::endl;

    //TEST 6
    std::cout << "TEST 6: " << std::endl;
    char expressionString6[] = "(+1125699)";
    BigNumberExpression expression6(expressionString6);
    int expectedOutput6 = 1125699;
    std::cout << "Testing expression -> (" << expressionString6 << "). Expected: " << expectedOutput6 << ": " << expression6.evaluteExpression();
    std::cout << std::endl;

    //TEST 7
    std::cout << "TEST 7: " << std::endl;
    char expressionString7[] = "-(1125699)";
    BigNumberExpression expression7(expressionString7);
    int expectedOutput7 = -(1125699);
    std::cout << "Testing expression -> (" << expressionString7 << "). Expected: " << expectedOutput7 << ": " << expression7.evaluteExpression();
    std::cout << std::endl;

    //TEST 8
    std::cout << "TEST 8: " << std::endl;
    char expressionString8[] = "-(+-1125699)";
    BigNumberExpression expression8(expressionString8);
    int expectedOutput8 = -(+-1125699);
    std::cout << "Testing expression -> (" << expressionString8 << "). Expected: " << expectedOutput8 << ": " << expression8.evaluteExpression();
    std::cout << std::endl;

    //TEST 9
    std::cout << "TEST 9: " << std::endl;
    char expressionString9[] = "-(--1125699)";
    BigNumberExpression expression9(expressionString9);
    int expectedOutput9 = -(1125699);
    std::cout << "Testing expression -> (" << expressionString9 << "). Expected: " << expectedOutput9 << ": " << expression9.evaluteExpression();
    std::cout << std::endl;

    //TEST 10
    std::cout << "TEST 10: " << std::endl;
    char expressionString10[] = "-+(--(-1125699))";
    BigNumberExpression expression10(expressionString10);
    int expectedOutput10 = -+((-1125699));
    std::cout << "Testing expression -> (" << expressionString10 << "). Expected: " << expectedOutput10 << ": " << expression10.evaluteExpression();
    std::cout << std::endl;

    //TEST 11
    std::cout << "TEST 11: " << std::endl;
    char expressionString11[] = "(-(-((1125699))))";
    BigNumberExpression expression11(expressionString11);
    int expectedOutput11 = (-(-((1125699))));
    std::cout << "Testing expression -> (" << expressionString11 << "). Expected: " << expectedOutput11 << ": " << expression11.evaluteExpression();
    std::cout << std::endl;
}
     
void BigNumberExpressionTests::solveExpressionParenthesis_AdditionAndMinusTests()
{
    std::cout << "---EXPRESSION SOLVING TESTS FOR \"+\" AND \"-\" OPERATORS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1: " << std::endl;
    char expressionString1[] = "(10 + 5) + 5";
    BigNumberExpression expression1(expressionString1);
    int expectedOutput1 = (10 + 5) + 5;
    std::cout << "Testing expression -> (" << expressionString1 << "). Expected: " << expectedOutput1 << ": " << expression1.evaluteExpression();
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2: " << std::endl;
    char expressionString2[] = "(10 + -5) + -(5 - 6)-(-(-(14--(10+5-4- -3))))";
    BigNumberExpression expression2(expressionString2);
    int expectedOutput2 = (10 + -5) + -(5 - 6) - (-(-(14 + (10 + 5 - 4 - -3)))); //Expected: 6 - 28 = -22
    std::cout << "Testing expression -> (" << expressionString2 << "). Expected: " << expectedOutput2 << ": " << expression2.evaluteExpression();
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3: " << std::endl;
    char expressionString3[] = "(-(10 + -5 + -5 - 6-(--(14--10+5-4- -3))))";
    BigNumberExpression expression3(expressionString3);
    int expectedOutput3 = (-(10 + -5 + -5 - 6 - ((14 + 10 + 5 - 4 - -3)))); //Expected: -(-6 - 28) = 34
    std::cout << "Testing expression -> (" << expressionString3 << "). Expected: " << expectedOutput3 << ": " << expression3.evaluteExpression();
    std::cout << std::endl;
}
     
void BigNumberExpressionTests::solveExpressionParenthesis_DivideTests()
{
    std::cout << "---EXPRESSION SOLVING TESTS FOR \"/\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1: " << std::endl;
    char expressionString1[] = "(125/5)";
    BigNumberExpression expression1(expressionString1);
    int expectedOutput1 = (125 / 5);
    std::cout << "Testing expression -> (" << expressionString1 << "). Expected: " << expectedOutput1 << ": " << expression1.evaluteExpression();
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2: " << std::endl;
    char expressionString2[] = "100/(2+3)";
    BigNumberExpression expression2(expressionString2);
    int expectedOutput2 = 100 / (2 + 3);
    std::cout << "Testing expression -> (" << expressionString2 << "). Expected: " << expectedOutput2 << ": " << expression2.evaluteExpression();
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3: " << std::endl;
    char expressionString3[] = "-(100/((576 - 35/(9-2)*2/(12 - 4/2))/575*6/(3+4-1)*3 - 3))";
    BigNumberExpression expression3(expressionString3);
    //int expectedOutput3 = -(100/((576 - 35/(9-2)*2/(12 - 4/2))/575*6/(3+4-1)*3 - 3)); Expected -(100/0) -> Exception thrown
    std::cout << "Testing expression -> (" << expressionString3 << "). Expected: Exception thrown: ";
    try
    {
        std::cout << expression3.evaluteExpression();
    }
    catch (...)
    {
        std::cout << "Exception thrown\n";
    }
    std::cout << std::endl;

    //TEST 4
    std::cout << "TEST 4: " << std::endl;
    char expressionString4[] = "-(100/(576 - 35/(9-2)*2/(12 - 4/2))/575*6/(3+4-1)*3 - 3)";
    BigNumberExpression expression4(expressionString4);
    int expectedOutput4 = -(100 / (576 - 35 / (9 - 2) * 2 / (12 - 4 / 2)) / 575 * 6 / (3 + 4 - 1) * 3 - 3); //Expected -(-3) -> 3
    std::cout << "Testing expression -> (" << expressionString4 << "). Expected: " << expectedOutput4 << ": " << expression4.evaluteExpression();;
    std::cout << std::endl;
}
     
void BigNumberExpressionTests::solveExpressionParenthesis_MultiplyTests()
{
    std::cout << "---EXPRESSION SOLVING TESTS FOR \"*\" OPERATOR:" << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1: " << std::endl;
    char expressionString1[] = "(4*3)";
    BigNumberExpression expression1(expressionString1);
    int expectedOutput1 = (4 * 3);
    std::cout << "Testing expression -> (" << expressionString1 << "). Expected: " << expectedOutput1 << ": " << expression1.evaluteExpression();
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2: " << std::endl;
    char expressionString2[] = "4*(3-2)";
    BigNumberExpression expression2(expressionString2);
    int expectedOutput2 = 4 * (3 - 2);
    std::cout << "Testing expression -> (" << expressionString2 << "). Expected: " << expectedOutput2 << ": " << expression2.evaluteExpression();
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3: " << std::endl;
    char expressionString3[] = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))";
    BigNumberExpression expression3(expressionString3);
    int expectedOutput3 = (10 + -5) * 7 + -2 * 3 * (5 - 3 * 6) - (-(-2 * (14 + (10 + 5 - 4 - -3)))); //Expected: 57
    std::cout << "Testing expression -> (" << expressionString3 << "). Expected: " << expectedOutput3 << ": " << expression3.evaluteExpression();
    std::cout << std::endl;

    //TEST 4
    std::cout << "TEST 4: " << std::endl;
    char expressionString4[] = "(-1*(2*(-2*((10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))))))";
    BigNumberExpression expression4(expressionString4);
    int expectedOutput4 = (-1 * (2 * (-2 * ((10 + -5) * 7 + -2 * 3 * (5 - 3 * 6) - (-(-2 * (14 + (10 + 5 - 4 - -3)))))))); //Expected: 228
    std::cout << "Testing expression -> (" << expressionString4 << "). Expected: " << expectedOutput4 << ": " << expression4.evaluteExpression();
    std::cout << std::endl;
}
     
void BigNumberExpressionTests::solveExpressionParenthesis_PercentTests()
{
    std::cout << "---EXPRESSION SOLVING TESTS FOR \"%\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1: " << std::endl;
    char expressionString1[] = "(125%5)";
    BigNumberExpression expression1(expressionString1);
    int expectedOuput1 = (125 % 5);
    std::cout << "Testing expression -> (" << expressionString1 << "). Expected: " << expectedOuput1 << ": " << expression1.evaluteExpression();
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2: " << std::endl;
    char expressionString2[] = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7";
    BigNumberExpression expression2(expressionString2);
    int expectedOuput2 = ((1000 - 1001) - (((100 - 15 % (5 * 4)) / 2 - 42) % 5 + 1000) % (200 + 100 * (3 - 1))) % -7; //Expected: -5 //-201%-7=28(-5)
    std::cout << "Testing expression -> (" << expressionString2 << "). Expected: " << expectedOuput2 << ": " << expression2.evaluteExpression();;
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3: " << std::endl;
    char expressionString3[] = "5%((100 - 15%(5*4))/2 - 42) + 1000"; //Expected 5%0 + 1000 --> Exception thrown
    BigNumberExpression expression3(expressionString3);
    std::cout << "Testing expression -> (" << expressionString3 << "). Expected: Exception thrown: ";
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
     
void BigNumberExpressionTests::solveExpressionParenthesisTests()
{
    // Expression solving tests
    std::cout << "EXPRESSION SOLVING TESTS WITH PARENTHESIS: " << std::endl << std::endl;

    solveExpressionParenthesis_SingleNumberTests();

    solveExpressionParenthesis_AdditionAndMinusTests();

    solveExpressionParenthesis_MultiplyTests();

    solveExpressionParenthesis_DivideTests();

    solveExpressionParenthesis_PercentTests();
}
     
void BigNumberExpressionTests::generateExpressionTests()
{
    std::cout << "GENERATE EXPRESSION TESTS" << std::endl << std::endl;
    srand(time(NULL));
    int something = (105 + 2876) - 0 % -7003493 - 26 - 4618 - 659043206;
    for (size_t i = 0; i < 50; i++)
    {
        std::cout << "TEST " << i + 1 << ": " << std::endl;
        BigNumberExpression expression1 = BigNumberExpression();
        std::cout << "Testing the generating of an expression --> ";
        expression1.generateExpression();
        std::cout << ". Is the expression valid? Expect: TRUE: " << (expression1.expressionIsValid() ? "TRUE" : "FALSE") << std::endl;
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

void BigNumberExpressionTests::comparativeOperatorsTests()
{
    std::cout << "COMPARATIVE OPERATORS TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1: " << std::endl;
    char expressionString11[] = "125/5";
    char expressionString12[] = "25";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
   
    std::cout << "Testing if [" << expressionString11 << "] == [" << expressionString12 << "] -> Expected: TRUE: " << (expression11 == expression12 ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2: " << std::endl;
    char expressionString21[] = "125/25";
    char expressionString22[] = "25";
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);

    std::cout << "Testing if [" << expressionString21 << "] != [" << expressionString22 << "] -> Expected: TRUE: " << (expression21 != expression22 ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3: " << std::endl;
    char expressionString31[] = "24/3";
    char expressionString32[] = "4+3";
    BigNumberExpression expression31(expressionString31);
    BigNumberExpression expression32(expressionString32);

    std::cout << "Testing if [" << expressionString31 << "] > [" << expressionString32 << "] -> Expected: TRUE: " << (expression31 > expression32 ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 4
    std::cout << "TEST 4: " << std::endl;
    char expressionString41[] = "100%23";
    char expressionString42[] = "1000/(50 + 25*2)";
    BigNumberExpression expression41(expressionString41);
    BigNumberExpression expression42(expressionString42);

    std::cout << "Testing if [" << expressionString41 << "] < [" << expressionString42 << "] -> Expected: TRUE: " << (expression41 < expression42 ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 5
    std::cout << "TEST 5: " << std::endl;
    char expressionString51[] = "24/3";
    char expressionString52[] = "4+4";
    BigNumberExpression expression51(expressionString51);
    BigNumberExpression expression52(expressionString52);

    std::cout << "Testing if [" << expressionString51 << "] >= [" << expressionString52 << "] -> Expected: TRUE: " << (expression51 >= expression52 ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 6
    std::cout << "TEST 6: " << std::endl;
    char expressionString61[] = "100%(23+2)+10";
    char expressionString62[] = "1000/(50 + 25*2)";
    BigNumberExpression expression61(expressionString61);
    BigNumberExpression expression62(expressionString62);

    std::cout << "Testing if [" << expressionString61 << "] <= [" << expressionString62 << "] -> Expected: TRUE: " << (expression61 <= expression62 ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;
}

void BigNumberExpressionTests::operatorSumTests()
{
    std::cout << "EXPRESSION TESTS FOR \"+\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1: " << std::endl;
    char expressionString11[] = "125/5";
    char expressionString12[] = "(25)";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
    BigNumberExpression expression13 = expression11 + expression12;
    char expectedOuput1[] = "(125/5)+((25))";
    std::cout << "Testing expression -> [ " << expressionString11 << " + "<< expressionString12 <<" ]. Expected: " << expectedOuput1 << ": " << expression13.getExpression() << std::endl;
    std::cout << "Are these expressions the same: " << (strcmp(expectedOuput1, expression13.getExpression()) == 0 ? "TRUE" : "FALSE") << std::endl;
    std::cout << "The answer to the expression: Expected: 50: " << expression13.evaluteExpression();
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2: " << std::endl;
    char expressionString21[] = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; //-5
    char expressionString22[] = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))"; //57
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);
    BigNumberExpression expression23 = expression21 + expression22;
    char expectedOuput2[] = "(((1000-1001)-(((100-15%(5*4))/2-42)%5+1000)%(200+100*(3-1)))%-7)+((10+-5)*7+-2*3*(5-3*6)-(-(-2*(14--(10+5-4--3)))))";
    std::cout << "Testing expression -> [ " << expressionString21 << " + " << expressionString22 << " ]. Expected: " << expectedOuput2 << ": " << expression23.getExpression() << std::endl;
    std::cout << "Are these expressions the same: " << (strcmp(expectedOuput2, expression23.getExpression()) == 0 ? "TRUE" : "FALSE") << std::endl;
    std::cout << "The answer to the expression: Expected: 52: " << expression23.evaluteExpression();
    std::cout << std::endl;
    std::cout << std::endl;
}

void BigNumberExpressionTests::operatorSumAndEqualsTests()
{
    std::cout << "EXPRESSION TESTS FOR \"+=\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1: " << std::endl;
    char expressionString11[] = "125/5";
    char expressionString12[] = "(25)";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
    expression11 += expression12;
    char expectedOuput1[] = "(125/5)+((25))";
    std::cout << "Testing expression -> [ " << expressionString11 << " += " << expressionString12 << " ]. Expected: " << expectedOuput1 << ": " << expression11.getExpression() << std::endl;
    std::cout << "Are these expressions the same: " << (strcmp(expectedOuput1, expression11.getExpression()) == 0 ? "TRUE" : "FALSE") << std::endl;
    std::cout << "The answer to the expression: Expected: 50: " << expression11.evaluteExpression();
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2: " << std::endl;
    char expressionString21[] = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; //-5
    char expressionString22[] = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))"; //57
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);
    expression21 += expression22;
    char expectedOuput2[] = "(((1000-1001)-(((100-15%(5*4))/2-42)%5+1000)%(200+100*(3-1)))%-7)+((10+-5)*7+-2*3*(5-3*6)-(-(-2*(14--(10+5-4--3)))))";
    std::cout << "Testing expression -> [ " << expressionString21 << " += " << expressionString22 << " ]. Expected: " << expectedOuput2 << ": " << expression21.getExpression() << std::endl;
    std::cout << "Are these expressions the same: " << (strcmp(expectedOuput2, expression21.getExpression()) == 0 ? "TRUE" : "FALSE") << std::endl;
    std::cout << "The answer to the expression: Expected: 52: " << expression21.evaluteExpression();
    std::cout << std::endl;
    std::cout << std::endl;
}

void BigNumberExpressionTests::operatorMinusTests()
{
    std::cout << "EXPRESSION TESTS FOR \"-\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1: " << std::endl;
    char expressionString11[] = "125/5";
    char expressionString12[] = "(25)";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
    BigNumberExpression expression13 = expression11 - expression12;
    char expectedOuput1[] = "(125/5)-((25))";
    std::cout << "Testing expression -> [ " << expressionString11 << " - " << expressionString12 << " ]. Expected: " << expectedOuput1 << ": " << expression13.getExpression() << std::endl;
    std::cout << "Are these expressions the same: " << (strcmp(expectedOuput1, expression13.getExpression()) == 0 ? "TRUE" : "FALSE") << std::endl;
    std::cout << "The answer to the expression: Expected: 0: " << expression13.evaluteExpression();
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2: " << std::endl;
    char expressionString21[] = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; //-5
    char expressionString22[] = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))"; //57
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);
    BigNumberExpression expression23 = expression21 - expression22;
    char expectedOuput2[] = "(((1000-1001)-(((100-15%(5*4))/2-42)%5+1000)%(200+100*(3-1)))%-7)-((10+-5)*7+-2*3*(5-3*6)-(-(-2*(14--(10+5-4--3)))))";
    std::cout << "Testing expression -> [ " << expressionString21 << " - " << expressionString22 << " ]. Expected: " << expectedOuput2 << ": " << expression23.getExpression() << std::endl;
    std::cout << "Are these expressions the same: " << (strcmp(expectedOuput2, expression23.getExpression()) == 0 ? "TRUE" : "FALSE") << std::endl;
    std::cout << "The answer to the expression: Expected: -62: " << expression23.evaluteExpression();
    std::cout << std::endl;
    std::cout << std::endl;
}

void BigNumberExpressionTests::operatorMinusAndEqualsTests()
{
    std::cout << "EXPRESSION TESTS FOR \"-=\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1: " << std::endl;
    char expressionString11[] = "125/5";
    char expressionString12[] = "(25)";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
    expression11 -= expression12;
    char expectedOuput1[] = "(125/5)-((25))";
    std::cout << "Testing expression -> [ " << expressionString11 << " -= " << expressionString12 << " ]. Expected: " << expectedOuput1 << ": " << expression11.getExpression() << std::endl;
    std::cout << "Are these expressions the same: " << (strcmp(expectedOuput1, expression11.getExpression()) == 0 ? "TRUE" : "FALSE") << std::endl;
    std::cout << "The answer to the expression: Expected: 0: " << expression11.evaluteExpression();
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2: " << std::endl;
    char expressionString21[] = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; //-5
    char expressionString22[] = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))"; //57
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);
    expression21 -= expression22;
    char expectedOuput2[] = "(((1000-1001)-(((100-15%(5*4))/2-42)%5+1000)%(200+100*(3-1)))%-7)-((10+-5)*7+-2*3*(5-3*6)-(-(-2*(14--(10+5-4--3)))))";
    std::cout << "Testing expression -> [ " << expressionString21 << " -= " << expressionString22 << " ]. Expected: " << expectedOuput2 << ": " << expression21.getExpression() << std::endl;
    std::cout << "Are these expressions the same: " << (strcmp(expectedOuput2, expression21.getExpression()) == 0 ? "TRUE" : "FALSE") << std::endl;
    std::cout << "The answer to the expression: Expected: -62: " << expression21.evaluteExpression();
    std::cout << std::endl;
    std::cout << std::endl;
}

void BigNumberExpressionTests::operatorMultiplyTests()
{
    std::cout << "EXPRESSION TESTS FOR \"*\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1: " << std::endl;
    char expressionString11[] = "125/5";
    char expressionString12[] = "(25)";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
    BigNumberExpression expression13 = expression11 * expression12;
    char expectedOuput1[] = "(125/5)*((25))";
    std::cout << "Testing expression -> [ " << expressionString11 << " * " << expressionString12 << " ]. Expected: " << expectedOuput1 << ": " << expression13.getExpression() << std::endl;
    std::cout << "Are these expressions the same: " << (strcmp(expectedOuput1, expression13.getExpression()) == 0 ? "TRUE" : "FALSE") << std::endl;
    std::cout << "The answer to the expression: Expected: 625: " << expression13.evaluteExpression();
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2: " << std::endl;
    char expressionString21[] = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; //-5
    char expressionString22[] = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))"; //57
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);
    BigNumberExpression expression23 = expression21 * expression22;
    char expectedOuput2[] = "(((1000-1001)-(((100-15%(5*4))/2-42)%5+1000)%(200+100*(3-1)))%-7)*((10+-5)*7+-2*3*(5-3*6)-(-(-2*(14--(10+5-4--3)))))";
    std::cout << "Testing expression -> [ " << expressionString21 << " * " << expressionString22 << " ]. Expected: " << expectedOuput2 << ": " << expression23.getExpression() << std::endl;
    std::cout << "Are these expressions the same: " << (strcmp(expectedOuput2, expression23.getExpression()) == 0 ? "TRUE" : "FALSE") << std::endl;
    std::cout << "The answer to the expression: Expected: -285: " << expression23.evaluteExpression();
    std::cout << std::endl;
    std::cout << std::endl;
}

void BigNumberExpressionTests::operatorMultiplyAndEqualsTests()
{
    std::cout << "EXPRESSION TESTS FOR \"*=\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1: " << std::endl;
    char expressionString11[] = "125/5";
    char expressionString12[] = "(25)";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
    expression11 *= expression12;
    char expectedOuput1[] = "(125/5)*((25))";
    std::cout << "Testing expression -> [ " << expressionString11 << " *= " << expressionString12 << " ]. Expected: " << expectedOuput1 << ": " << expression11.getExpression() << std::endl;
    std::cout << "Are these expressions the same: " << (strcmp(expectedOuput1, expression11.getExpression()) == 0 ? "TRUE" : "FALSE") << std::endl;
    std::cout << "The answer to the expression: Expected: 625: " << expression11.evaluteExpression();
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2: " << std::endl;
    char expressionString21[] = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; //-5
    char expressionString22[] = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))"; //57
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);
    expression21 *= expression22;
    char expectedOuput2[] = "(((1000-1001)-(((100-15%(5*4))/2-42)%5+1000)%(200+100*(3-1)))%-7)*((10+-5)*7+-2*3*(5-3*6)-(-(-2*(14--(10+5-4--3)))))";
    std::cout << "Testing expression -> [ " << expressionString21 << " *= " << expressionString22 << " ]. Expected: " << expectedOuput2 << ": " << expression21.getExpression() << std::endl;
    std::cout << "Are these expressions the same: " << (strcmp(expectedOuput2, expression21.getExpression()) == 0 ? "TRUE" : "FALSE") << std::endl;
    std::cout << "The answer to the expression: Expected: -285: " << expression21.evaluteExpression();
    std::cout << std::endl;
    std::cout << std::endl;
}

void BigNumberExpressionTests::operatorDivideTests()
{
    std::cout << "EXPRESSION TESTS FOR \"/\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1: " << std::endl;
    char expressionString11[] = "125/5";
    char expressionString12[] = "(25)";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
    BigNumberExpression expression13 = expression11 / expression12;
    char expectedOuput1[] = "(125/5)/((25))";
    std::cout << "Testing expression -> [ " << expressionString11 << " / " << expressionString12 << " ]. Expected: " << expectedOuput1 << ": " << expression13.getExpression() << std::endl;
    std::cout << "Are these expressions the same: " << (strcmp(expectedOuput1, expression13.getExpression()) == 0 ? "TRUE" : "FALSE") << std::endl;
    std::cout << "The answer to the expression: Expected: 1: " << expression13.evaluteExpression();
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2: " << std::endl;
    char expressionString21[] = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; //-5
    char expressionString22[] = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))"; //57
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);
    BigNumberExpression expression23 = expression21 / expression22;
    char expectedOuput2[] = "(((1000-1001)-(((100-15%(5*4))/2-42)%5+1000)%(200+100*(3-1)))%-7)/((10+-5)*7+-2*3*(5-3*6)-(-(-2*(14--(10+5-4--3)))))";
    std::cout << "Testing expression -> [ " << expressionString21 << " / " << expressionString22 << " ]. Expected: " << expectedOuput2 << ": " << expression23.getExpression() << std::endl;
    std::cout << "Are these expressions the same: " << (strcmp(expectedOuput2, expression23.getExpression()) == 0 ? "TRUE" : "FALSE") << std::endl;
    std::cout << "The answer to the expression: Expected: 0: " << expression23.evaluteExpression();
    std::cout << std::endl;
    std::cout << std::endl;
}

void BigNumberExpressionTests::operatorDivideAndEqualsTests()
{
    std::cout << "EXPRESSION TESTS FOR \"/=\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1: " << std::endl;
    char expressionString11[] = "125/5";
    char expressionString12[] = "(25)";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
    expression11 /= expression12;
    char expectedOuput1[] = "(125/5)/((25))";
    std::cout << "Testing expression -> [ " << expressionString11 << " /= " << expressionString12 << " ]. Expected: " << expectedOuput1 << ": " << expression11.getExpression() << std::endl;
    std::cout << "Are these expressions the same: " << (strcmp(expectedOuput1, expression11.getExpression()) == 0 ? "TRUE" : "FALSE") << std::endl;
    std::cout << "The answer to the expression: Expected: 1: " << expression11.evaluteExpression();
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2: " << std::endl;
    char expressionString21[] = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; //-5
    char expressionString22[] = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))"; //57
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);
    expression21 /= expression22;
    char expectedOuput2[] = "(((1000-1001)-(((100-15%(5*4))/2-42)%5+1000)%(200+100*(3-1)))%-7)/((10+-5)*7+-2*3*(5-3*6)-(-(-2*(14--(10+5-4--3)))))";
    std::cout << "Testing expression -> [ " << expressionString21 << " /= " << expressionString22 << " ]. Expected: " << expectedOuput2 << ": " << expression21.getExpression() << std::endl;
    std::cout << "Are these expressions the same: " << (strcmp(expectedOuput2, expression21.getExpression()) == 0 ? "TRUE" : "FALSE") << std::endl;
    std::cout << "The answer to the expression: Expected: 0: " << expression21.evaluteExpression();
    std::cout << std::endl;
    std::cout << std::endl;
}

void BigNumberExpressionTests::operatorPercentTests()
{
    std::cout << "EXPRESSION TESTS FOR \"%\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1: " << std::endl;
    char expressionString11[] = "125/5";
    char expressionString12[] = "(25)";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
    BigNumberExpression expression13 = expression11 % expression12;
    char expectedOuput1[] = "(125/5)%((25))";
    std::cout << "Testing expression -> [ " << expressionString11 << " % " << expressionString12 << " ]. Expected: " << expectedOuput1 << ": " << expression13.getExpression() << std::endl;
    std::cout << "Are these expressions the same: " << (strcmp(expectedOuput1, expression13.getExpression()) == 0 ? "TRUE" : "FALSE") << std::endl;
    std::cout << "The answer to the expression: Expected: 0: " << expression13.evaluteExpression();
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2: " << std::endl;
    char expressionString21[] = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; //-5
    char expressionString22[] = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))"; //57
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);
    BigNumberExpression expression23 = expression21 % expression22;
    char expectedOuput2[] = "(((1000-1001)-(((100-15%(5*4))/2-42)%5+1000)%(200+100*(3-1)))%-7)%((10+-5)*7+-2*3*(5-3*6)-(-(-2*(14--(10+5-4--3)))))";
    std::cout << "Testing expression -> [ " << expressionString21 << " % " << expressionString22 << " ]. Expected: " << expectedOuput2 << ": " << expression23.getExpression() << std::endl;
    std::cout << "Are these expressions the same: " << (strcmp(expectedOuput2, expression23.getExpression()) == 0 ? "TRUE" : "FALSE") << std::endl;
    std::cout << "The answer to the expression: Expected: -5: " << expression23.evaluteExpression();
    std::cout << std::endl;
    std::cout << std::endl;
}

void BigNumberExpressionTests::operatorPercentAndEqualsTests()
{
    std::cout << "EXPRESSION TESTS FOR \"%=\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1: " << std::endl;
    char expressionString11[] = "125/5";
    char expressionString12[] = "(25)";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
    expression11 %= expression12;
    char expectedOuput1[] = "(125/5)%((25))";
    std::cout << "Testing expression -> [ " << expressionString11 << " % " << expressionString12 << " ]. Expected: " << expectedOuput1 << ": " << expression11.getExpression() << std::endl;
    std::cout << "Are these expressions the same: " << (strcmp(expectedOuput1, expression11.getExpression()) == 0 ? "TRUE" : "FALSE") << std::endl;
    std::cout << "The answer to the expression: Expected: 0: " << expression11.evaluteExpression();
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2: " << std::endl;
    char expressionString21[] = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; //-5
    char expressionString22[] = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))"; //57
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);
    expression21 %= expression22;
    char expectedOuput2[] = "(((1000-1001)-(((100-15%(5*4))/2-42)%5+1000)%(200+100*(3-1)))%-7)%((10+-5)*7+-2*3*(5-3*6)-(-(-2*(14--(10+5-4--3)))))";
    std::cout << "Testing expression -> [ " << expressionString21 << " %= " << expressionString22 << " ]. Expected: " << expectedOuput2 << ": " << expression21.getExpression() << std::endl;
    std::cout << "Are these expressions the same: " << (strcmp(expectedOuput2, expression21.getExpression()) == 0 ? "TRUE" : "FALSE") << std::endl;
    std::cout << "The answer to the expression: Expected: -5: " << expression21.evaluteExpression();
    std::cout << std::endl;
    std::cout << std::endl;
}

void BigNumberExpressionTests::readFromAndWriteToConsoleTests()
{
    std::cout << "READ AND WRITE FROM AND TO CONSOLE TESTS" << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    BigNumberExpression expression1 = BigNumberExpression();
    BigNumberExpression expression2 = BigNumberExpression();
    std::cout << "Enter expression1: ";
    std::cin >> expression1;
    std::cout << "Enter expression2: " << std::endl;;
    std::cin >> expression2;
    std::cout << expression1;
    std::cout << expression2;
}

void BigNumberExpressionTests::readFromAndWriteToFileTests()
{
    std::cout << "READ AND WRITE FROM AND TO FILE TESTS" << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;

    std::ifstream is("Equations.txt");
    int somethingDebug = (15 - (3 * 156 / 343 % (6 / 2 * 4 % 10 + 43))) + 10;
    BigNumberExpression expression1 = BigNumberExpression();
    BigNumberExpression expression2 = BigNumberExpression();
    is >> expression1;
    is >> expression2;

    is.close();

    std::ofstream os("EquationsAnswers.txt");

    os << expression1;
    os << expression2;

    os.close();
}

void BigNumberExpressionTests::runTests()
{
    ////Big 4 tests
    //expressionBig4Tests();
    //
    //// Expression is valid tests
    //expressionIsValidTests();
    //
    ////Solving expression tests without parenthesis
    //solveExpressionNoParenthesisTests();
    //
    ////Solving expression tests with parenthesis
    //solveExpressionParenthesisTests();
    //
    ////Generating expressions tests
    //generateExpressionTests();
    //
    ////Read from and Write to console tests
    //readFromAndWriteToConsoleTests();
    //
    //////Read from and Write to console tests
    //readFromAndWriteToFileTests();

    //Comparative operators tests
    comparativeOperatorsTests();

    //Operator + tests
    operatorSumTests();

    //Operator += tests
    operatorSumAndEqualsTests();

    //Operator - tests
    operatorMinusTests();

    //Operator -= tests
    operatorMinusAndEqualsTests();

    //Operator * tests
    operatorMultiplyTests();

    //Operator *= tests
    operatorMultiplyAndEqualsTests();

    //Operator / tests
    operatorDivideTests();

    //Operator /= tests
    operatorDivideAndEqualsTests();

    //Operator % tests
    operatorPercentTests();

    //Operator %= tests
    operatorPercentAndEqualsTests();
}
