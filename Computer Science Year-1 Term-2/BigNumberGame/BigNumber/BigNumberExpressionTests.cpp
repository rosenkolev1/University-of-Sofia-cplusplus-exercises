#include <iostream>
#include "BigNumberExpressionTests.h"
#include "BigNumberExpression.h"
#include "BigNumber.h"
#include "BigNumberDivisionResult.h"
#include "..\Project.StringManipulation\MStringManip.h"
#include <fstream>

void BigNumberExpressionTests::expressionBig4Tests(std::ostream& os)
{
    os << "BIG 4 OF BigNumberExpression TESTS: " << std::endl << std::endl;
    BigNumberExpression expression1 = BigNumberExpression();
    mstring someExpression = " 10 + 5";
    mstring anotherExpression = "15/3";
    BigNumberExpression expression2(someExpression);
    BigNumberExpression expression3(anotherExpression);

    os << "Expression 1: Expected: " << "{empty}" << ": " << (expression1.getExpression() == "0" ? "{empty}" : "WRONG") << std::endl;
    os << "Expression 2: Expected: " << someExpression << ": " << expression2.getExpression() << std::endl;
    os << "Expression 3: Expected: " << anotherExpression << ": " << expression3.getExpression() << std::endl;

    os << std::endl;

    expression1 = expression2;
    os << "Testing \"expression1 = expression2;\" \n";
    os << "Expression 1: Expected: " << someExpression << ": " << expression1.getExpression() << std::endl;

    os << std::endl;

    expression2 = expression3;
    os << "Testing \"expression2 = expression3;\" \n";
    os << "Expression 2: Expected: " << anotherExpression << ": " << expression2.getExpression() << std::endl;

    os << std::endl;

    BigNumberExpression expression4(expression1);
    os << "Testing \"BigNumberEquation expression4(expression1);\" \n";
    os << "Expression 4: Expected: " << someExpression << ": " << expression4.getExpression() << std::endl;

    os << std::endl;
}

void BigNumberExpressionTests::expressionIsValidTests(std::ostream& os)
{
    os << "EXPRESSION IS VALID TESTS: " << std::endl << std::endl;

    //TEST prep
    BigNumberExpression expression = BigNumberExpression();

    //TEST 1
    os << "TEST 1" << std::endl;
    mstring expressionString1 = "";
    os << "Testing if expression is valid-> " << expressionString1 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString1) ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2" << std::endl;
    mstring expressionString2 = "  ";
    os << "Testing if expression is valid-> " << expressionString2 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString2) ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;

    //TEST 3
    os << "TEST 3" << std::endl;
    mstring expressionString3 = "()((()))(((()))()";
    os << "Testing if expression is valid-> " << expressionString3 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString3) ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;

    //TEST 4
    os << "TEST 4" << std::endl;
    mstring expressionString4 = "()((()))((())))((()))";
    os << "Testing if expression is valid-> " << expressionString4 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString4) ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;

    //TEST 5
    os << "TEST 5" << std::endl;
    mstring expressionString5 = "15+10asd";
    os << "Testing if expression is valid-> " << expressionString5 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString5) ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;

    //TEST 6-34
    for (size_t i = 0; i < BigNumberExpression::EXPRESSION_FORBIDDEN_STRINGS_COUNT; i++)
    {
        os << "TEST " << i + 6 << std::endl;
        mstring expressionStringFirst = "15";
        mstring expressionStringSecond = BigNumberExpression::EXPRESSION_FORBIDDEN_STRINGS[i];
        mstring expressionStringThird = "10";

        mstring finalExpression = expressionStringFirst + expressionStringSecond + expressionStringThird;

        os << "Testing if expression is valid-> " << finalExpression << ". Expected: FALSE: " << (expression.expressionIsValid(finalExpression) ? "TRUE" : "FALSE");

        os << std::endl;
        os << std::endl;

    }

    //TEST 38
    os << "TEST 38" << std::endl;
    mstring expressionString38 = "15+10+";
    os << "Testing if expression is valid-> " << expressionString38 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString38) ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;

    //TEST 39
    os << "TEST 39" << std::endl;
    mstring expressionString39 = "15+10-";
    os << "Testing if expression is valid-> " << expressionString39 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString39) ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;

    //TEST 40
    os << "TEST 40" << std::endl;
    mstring expressionString40 = "15+10*";
    os << "Testing if expression is valid-> " << expressionString40 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString40) ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;

    //TEST 41
    os << "TEST 41" << std::endl;
    mstring expressionString41 = "15+10/";
    os << "Testing if expression is valid-> " << expressionString41 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString41) ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;

    //TEST 42
    os << "TEST 42" << std::endl;
    mstring expressionString42 = "15+10%";
    os << "Testing if expression is valid-> " << expressionString42 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString42) ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;

    //TEST 43
    os << "TEST 43" << std::endl;
    mstring expressionString43 = "*15+10";
    os << "Testing if expression is valid-> " << expressionString43 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString43) ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;

    //TEST 44
    os << "TEST 44" << std::endl;
    mstring expressionString44 = "/15+10";
    os << "Testing if expression is valid-> " << expressionString44 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString44) ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;

    //TEST 45
    os << "TEST 45" << std::endl;
    mstring expressionString45 = "%15+10";
    os << "Testing if expression is valid-> " << expressionString45 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString45) ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;

    //TEST 46
    os << "TEST 46" << std::endl;
    mstring expressionString46 = "(10-15)*(*15+10)";
    os << "Testing if expression is valid-> " << expressionString46 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString46) ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;

    //TEST 47
    os << "TEST 47" << std::endl;
    mstring expressionString47 = "(10-15)*(/15+10)";
    os << "Testing if expression is valid-> " << expressionString47 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString47) ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;

    //TEST 48
    os << "TEST 48" << std::endl;
    mstring expressionString48 = "(10-15)*(%15+10)";
    os << "Testing if expression is valid-> " << expressionString48 << ". Expected: FALSE: " << (expression.expressionIsValid(expressionString48) ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;
}

void BigNumberExpressionTests::solveExpressionNoParenthesis_SingleNumberTests(std::ostream& os)
{
    os << "---EXPRESSION SOLVING TESTS FOR SINGLE NUMBER EXPRESSION: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 1" << std::endl;
    mstring expressionString1 = "1125699";
    BigNumberExpression expression1(expressionString1);
    int expectedOutput1 = 1125699;
    os << "Testing expression -> (" << expressionString1 << "). Expected: " << expectedOutput1 << ": " << expression1.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2" << std::endl;
    mstring expressionString2 = "-1125699";
    BigNumberExpression expression2(expressionString2);
    int expectedOutput2 = -1125699;
    os << "Testing expression -> (" << expressionString2 << "). Expected: " << expectedOutput2 << ": " << expression2.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 3
    os << "TEST 3" << std::endl;
    mstring expressionString3 = "+-1125699";
    BigNumberExpression expression3(expressionString3);
    int expectedOutput3 = +-1125699;
    os << "Testing expression -> (" << expressionString3 << "). Expected: " << expectedOutput3 << ": " << expression3.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 4
    os << "TEST 4" << std::endl;
    mstring expressionString4 = "-+1125699";
    BigNumberExpression expression4(expressionString4);
    int expectedOutput4 = -+1125699;
    os << "Testing expression -> (" << expressionString4 << "). Expected: " << expectedOutput4 << ": " << expression4.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 5
    os << "TEST 5" << std::endl;
    mstring expressionString5 = "--1125699";
    BigNumberExpression expression5(expressionString5);
    int expectedOutput5 = 1125699;
    os << "Testing expression -> (" << expressionString5 << "). Expected: " << expectedOutput5 << ": " << expression5.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 6
    os << "TEST 6" << std::endl;
    mstring expressionString6 = "+1125699";
    BigNumberExpression expression6(expressionString6);
    int expectedOutput6 = 1125699;
    os << "Testing expression -> (" << expressionString6 << "). Expected: " << expectedOutput6 << ": " << expression6.evaluateExpression();
    os << std::endl;
    os << std::endl;
}

void BigNumberExpressionTests::solveExpressionNoParenthesis_AdditionAndMinusTests(std::ostream& os)
{
    os << "---EXPRESSION SOLVING TESTS FOR \"+\" AND \"-\" OPERATORS: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 1" << std::endl;
    mstring expressionString1 = "10+5";
    BigNumberExpression expression1(expressionString1);
    int expectedOutput1 = 10 + 5;
    os << "Testing expression -> (" << expressionString1 << "). Expected: " << expectedOutput1 << ": " << expression1.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2" << std::endl;
    mstring expressionString2 = "57-19";
    BigNumberExpression expression2(expressionString2);
    int expectedOutput2 = 57 - 19;
    os << "Testing expression -> (" << expressionString2 << "). Expected: " << expectedOutput2 << ": " << expression2.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 3
    os << "TEST 3" << std::endl;
    mstring expressionString3 = "-57-19";
    BigNumberExpression expression3(expressionString3);
    int expectedOutput3 = -57 - 19;
    os << "Testing expression -> (" << expressionString3 << "). Expected: " << expectedOutput3 << ": " << expression3.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 4
    os << "TEST 4" << std::endl;
    mstring expressionString4 = "-345-+15";
    BigNumberExpression expression4(expressionString4);
    int expectedOutput4 = -345 - +15;
    os << "Testing expression -> (" << expressionString4 << "). Expected: " << expectedOutput4 << ": " << expression4.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 5
    os << "TEST 5" << std::endl;
    mstring expressionString5 = "-345+-15";
    BigNumberExpression expression5(expressionString5);
    int expectedOutput5 = -345 + -15;
    os << "Testing expression -> (" << expressionString5 << "). Expected: " << expectedOutput5 << ": " << expression5.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 6
    os << "TEST 6" << std::endl;
    mstring expressionString6 = "-345--15";
    BigNumberExpression expression6(expressionString6);
    int expectedOutput6 = -345 - (-15);
    os << "Testing expression -> (" << expressionString6 << "). Expected: " << expectedOutput6 << ": " << expression6.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 7
    os << "TEST 7" << std::endl;
    mstring expressionString7 = "-345--15+30";
    BigNumberExpression expression7(expressionString7);
    int expectedOutput7 = -345 - (-15) + 30;
    os << "Testing expression -> (" << expressionString7 << "). Expected: " << expectedOutput7 << ": " << expression7.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 8
    os << "TEST 8" << std::endl;
    mstring expressionString8 = "--345--15+-30";
    BigNumberExpression expression8(expressionString8);
    int expectedOutput8 = -(-345) - (-15) + -30;
    os << "Testing expression -> (" << expressionString8 << "). Expected: " << expectedOutput8 << ": " << expression8.evaluateExpression();
    os << std::endl;
    os << std::endl;
}

void BigNumberExpressionTests::solveExpressionNoParenthesis_MultiplyTests(std::ostream& os)
{
    os << "---EXPRESSION SOLVING TESTS FOR \"*\" OPERATOR:" << std::endl << std::endl;

    //TEST 1
    os << "TEST 1" << std::endl;
    mstring expressionString9 = "4*3";
    BigNumberExpression expression9(expressionString9);
    int expectedOutput9 = 4 * 3;
    os << "Testing expression -> (" << expressionString9 << "). Expected: " << expectedOutput9 << ": " << expression9.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2" << std::endl;
    mstring expressionString10 = "-4*3";
    BigNumberExpression expression10(expressionString10);
    int expectedOutput10 = -4 * 3;
    os << "Testing expression -> (" << expressionString10 << "). Expected: " << expectedOutput10 << ": " << expression10.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 3
    os << "TEST 3" << std::endl;
    mstring expressionString11 = "4*-3";
    BigNumberExpression expression11(expressionString11);
    int expectedOutput11 = 4 * -3;
    os << "Testing expression -> (" << expressionString11 << "). Expected: " << expectedOutput11 << ": " << expression11.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 4
    os << "TEST 4" << std::endl;
    mstring expressionString12 = "4*0";
    BigNumberExpression expression12(expressionString12);
    int expectedOutput12 = 4 * 0;
    os << "Testing expression -> (" << expressionString12 << "). Expected: " << expectedOutput12 << ": " << expression12.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 5
    os << "TEST 5" << std::endl;
    mstring expressionString13 = "-0*3";
    BigNumberExpression expression13(expressionString13);
    int expectedOutput13 = -0 * 3;
    os << "Testing expression -> (" << expressionString13 << "). Expected: " << expectedOutput13 << ": " << expression13.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 6
    os << "TEST 6" << std::endl;
    mstring expressionString14 = "-0*-0";
    BigNumberExpression expression14(expressionString14);
    int expectedOutput14 = -0 * -0;
    os << "Testing expression -> (" << expressionString14 << "). Expected: " << expectedOutput14 << ": " << expression14.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 7
    os << "TEST 7" << std::endl;
    mstring expressionString15 = "125-5*5 + 1";
    BigNumberExpression expression15(expressionString15);
    int expectedOutput15 = 125 - 5 * 5 + 1;
    os << "Testing expression -> (" << expressionString15 << "). Expected: " << expectedOutput15 << ": " << expression15.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 8
    os << "TEST 8" << std::endl;
    mstring expressionString16 = "125+-5*5-1*-9";
    BigNumberExpression expression16(expressionString16);
    int expectedOutput16 = 125 + -5 * 5 - 1 * -9;
    os << "Testing expression -> (" << expressionString16 << "). Expected: " << expectedOutput16 << ": " << expression16.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 9
    os << "TEST 9" << std::endl;
    mstring expressionString17 = "-125+-5*5-+1*-9";
    BigNumberExpression expression17(expressionString17);
    int expectedOutput17 = -125 + -5 * 5 - +1 * -9;
    os << "Testing expression -> (" << expressionString17 << "). Expected: " << expectedOutput17 << ": " << expression17.evaluateExpression();
    os << std::endl;
    os << std::endl;
}

void BigNumberExpressionTests::solveExpressionNoParenthesis_DivideTests(std::ostream& os)
{
    os << "---EXPRESSION SOLVING TESTS FOR \"/\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 1" << std::endl;
    mstring expressionString18 = "125/5";
    BigNumberExpression expression18(expressionString18);
    int expectedOutput18 = 125 / 5;
    os << "Testing expression -> (" << expressionString18 << "). Expected: " << expectedOutput18 << ": " << expression18.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2" << std::endl;
    mstring expressionString19 = "0/5";
    int expectedOutput19 = 0 / 5;
    BigNumberExpression expression19(expressionString19);
    os << "Testing expression -> (" << expressionString19 << "). Expected: " << expectedOutput19 << ": " << expression19.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 3
    os << "TEST 3" << std::endl;
    mstring expressionString20 = "125/0";
    BigNumberExpression expression20(expressionString20);
    os << "Testing expression -> (" << expressionString20 << "). Expected: " << BigNumberExpression::EXPRESSION_DIVIDEBYZERO_EXCEPTION << ": ";
    try
    {
        os << expression20.evaluateExpression();
    }
    catch (mstring e)
    {
        os << e;
    }
    os << std::endl;
    os << std::endl;

    //TEST 4
    os << "TEST 4" << std::endl;
    mstring expressionString21 = "0/0";
    BigNumberExpression expression21(expressionString21);
    os << "Testing expression -> (" << expressionString21 << "). Expected: " << BigNumberExpression::EXPRESSION_DIVIDEBYZERO_EXCEPTION << ": ";
    try
    {
        os << expression20.evaluateExpression();
    }
    catch (mstring e)
    {
        os << e;
    }
    os << std::endl;
    os << std::endl;

    //TEST 5
    os << "TEST 5" << std::endl;
    mstring expressionString22 = "-125/3";
    BigNumberExpression expression22(expressionString22);
    int expectedOutput22 = -125 / 3;
    os << "Testing expression -> (" << expressionString22 << "). Expected: " << expectedOutput22 << ": " << expression22.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 6
    os << "TEST 6" << std::endl;
    mstring expressionString23 = "125/-3";
    BigNumberExpression expression23(expressionString23);
    int expectedOutput23 = 125 / -3;
    os << "Testing expression -> (" << expressionString23 << "). Expected: " << expectedOutput23 << ": " << expression23.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 7
    os << "TEST 7" << std::endl;
    mstring expressionString24 = "-125/-3";
    BigNumberExpression expression24(expressionString24);
    int expectedOutput24 = -125 / -3;
    os << "Testing expression -> (" << expressionString24 << "). Expected: " << expectedOutput24 << ": " << expression24.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 8
    os << "TEST 8" << std::endl;
    mstring expressionString25 = "-125+-5*5/-3-+3";
    BigNumberExpression expression25(expressionString25);
    int expectedOutput25 = -125 + -5 * 5 / -3 - +3;
    os << "Testing expression -> (" << expressionString25 << "). Expected: " << expectedOutput25 << ": " << expression25.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 9
    os << "TEST 9" << std::endl;
    mstring expressionString26 = "-125+-3/5*5/-3-+3";
    BigNumberExpression expression26(expressionString26);
    int expectedOutput26 = -125 + -3 / 5 * 5 / -3 - +3;
    os << "Testing expression -> (" << expressionString26 << "). Expected: " << expectedOutput26 << ": " << expression26.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 10
    os << "TEST 10" << std::endl;
    mstring expressionString27 = "100/500*500";
    BigNumberExpression expression27(expressionString27);
    int expectedOutput27 = 100 / 500 * 500;
    os << "Testing expression -> (" << expressionString27 << "). Expected: " << expectedOutput27 << ": " << expression27.evaluateExpression();
    os << std::endl;
    os << std::endl;
}

void BigNumberExpressionTests::solveExpressionNoParenthesis_PercentTests(std::ostream& os)
{
    os << "---EXPRESSION SOLVING TESTS FOR \"%\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 1" << std::endl;
    mstring expressionString27 = "125%5";
    BigNumberExpression expression27(expressionString27);
    int expectedOuput27 = 125 % 5;
    os << "Testing expression -> (" << expressionString27 << "). Expected: " << expectedOuput27 << ": " << expression27.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2" << std::endl;
    mstring expressionString28 = "0%5";
    BigNumberExpression expression28(expressionString28);
    int expectedOuput28 = 0 % 5;
    os << "Testing expression -> (" << expressionString28 << "). Expected: " << expectedOuput28 << ": " << expression28.evaluateExpression();;
    os << std::endl;
    os << std::endl;

    //TEST 3
    os << "TEST 3" << std::endl;
    mstring expressionString29 = "125%0";
    BigNumberExpression expression29(expressionString29);
    os << "Testing expression -> (" << expressionString29 << "). Expected: " << BigNumberExpression::EXPRESSION_PERCENTBYZERO_EXCEPTION << ": ";
    try
    {
        os << expression29.evaluateExpression();
    }
    catch (mstring e)
    {
        os << e;
    }
    os << std::endl;
    os << std::endl;

    //TEST 4
    os << "TEST 4" << std::endl;
    mstring expressionString30 = "0%0";
    BigNumberExpression expression30(expressionString30);
    os << "Testing expression -> (" << expressionString30 << "). Expected: " << BigNumberExpression::EXPRESSION_PERCENTBYZERO_EXCEPTION << ": ";
    try
    {
        os << expression30.evaluateExpression();
    }
    catch (mstring e)
    {
        os << e;
    }
    os << std::endl;
    os << std::endl;

    //TEST 5
    os << "TEST 5" << std::endl;
    mstring expressionString31 = "125%3";
    BigNumberExpression expression31(expressionString31);
    int expectedOuput31 = 125 % 3;
    os << "Testing expression -> (" << expressionString31 << "). Expected: " << expectedOuput31 << ": " << expression31.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 6
    os << "TEST 6" << std::endl;
    mstring expressionString32 = "125%-3";
    BigNumberExpression expression32(expressionString32);
    int expectedOuput32 = 125 % -3;
    os << "Testing expression -> (" << expressionString32 << "). Expected: " << expectedOuput32 << ": " << expression32.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 7
    os << "TEST 7" << std::endl;
    mstring expressionString33 = "-125%3";
    BigNumberExpression expression33(expressionString33);
    int expectedOuput33 = -125 % 3;
    os << "Testing expression -> (" << expressionString33 << "). Expected: " << expectedOuput33 << ": " << expression33.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 8
    os << "TEST 8" << std::endl;
    mstring expressionString34 = "+-125%-3";
    BigNumberExpression expression34(expressionString34);
    int expectedOuput34 = +-125 % -3;
    os << "Testing expression -> (" << expressionString34 << "). Expected: " << expectedOuput34 << ": " << expression34.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 9
    os << "TEST 9" << std::endl;
    mstring expressionString35 = "25-125%-3*5";
    BigNumberExpression expression35(expressionString35);
    int expectedOuput35 = 25 - 125 % -3 * 5;
    os << "Testing expression -> (" << expressionString35 << "). Expected: " << expectedOuput35 << ": " << expression35.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 10
    os << "TEST 10" << std::endl;
    mstring expressionString36 = "25-125/-3%5";
    BigNumberExpression expression36(expressionString36);
    int expectedOuput36 = 25 - 125 / -3 % 5;
    os << "Testing expression -> (" << expressionString36 << "). Expected: " << expectedOuput36 << ": " << expression36.evaluateExpression();
    os << std::endl;
    os << std::endl;
}

void BigNumberExpressionTests::solveExpressionNoParenthesisTests(std::ostream& os)
{
    // Expression solving tests
    os << "EXPRESSION SOLVING TESTS WITHOUT PARENTHESIS: " << std::endl << std::endl;

    solveExpressionNoParenthesis_SingleNumberTests(os);

    solveExpressionNoParenthesis_AdditionAndMinusTests(os);

    solveExpressionNoParenthesis_MultiplyTests(os);

    solveExpressionNoParenthesis_DivideTests(os);

    solveExpressionNoParenthesis_PercentTests(os);
}

void BigNumberExpressionTests::solveExpressionParenthesis_SingleNumberTests(std::ostream& os)
{
    os << "---EXPRESSION SOLVING TESTS FOR SINGLE NUMBER EXPRESSIONS: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 1: " << std::endl;
    mstring expressionString1 = "(1125699)";
    BigNumberExpression expression1(expressionString1);
    int expectedOutput1 = 1125699;
    os << "Testing expression -> (" << expressionString1 << "). Expected: " << expectedOutput1 << ": " << expression1.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2: " << std::endl;
    mstring expressionString2 = "(-1125699)";
    BigNumberExpression expression2(expressionString2);
    int expectedOutput2 = -1125699;
    os << "Testing expression -> (" << expressionString2 << "). Expected: " << expectedOutput2 << ": " << expression2.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 3
    os << "TEST 3: " << std::endl;
    mstring expressionString3 = "(+-1125699)";
    BigNumberExpression expression3(expressionString3);
    int expectedOutput3 = +-1125699;
    os << "Testing expression -> (" << expressionString3 << "). Expected: " << expectedOutput3 << ": " << expression3.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 4
    os << "TEST 4: " << std::endl;
    mstring expressionString4 = "(-+1125699)";
    BigNumberExpression expression4(expressionString4);
    int expectedOutput4 = -+1125699;
    os << "Testing expression -> (" << expressionString4 << "). Expected: " << expectedOutput4 << ": " << expression4.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 5
    os << "TEST 5: " << std::endl;
    mstring expressionString5 = "(--1125699)";
    BigNumberExpression expression5(expressionString5);
    int expectedOutput5 = 1125699;
    os << "Testing expression -> (" << expressionString5 << "). Expected: " << expectedOutput5 << ": " << expression5.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 6
    os << "TEST 6: " << std::endl;
    mstring expressionString6 = "(+1125699)";
    BigNumberExpression expression6(expressionString6);
    int expectedOutput6 = 1125699;
    os << "Testing expression -> (" << expressionString6 << "). Expected: " << expectedOutput6 << ": " << expression6.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 7
    os << "TEST 7: " << std::endl;
    mstring expressionString7 = "-(1125699)";
    BigNumberExpression expression7(expressionString7);
    int expectedOutput7 = -(1125699);
    os << "Testing expression -> (" << expressionString7 << "). Expected: " << expectedOutput7 << ": " << expression7.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 8
    os << "TEST 8: " << std::endl;
    mstring expressionString8 = "-(+-1125699)";
    BigNumberExpression expression8(expressionString8);
    int expectedOutput8 = -(+-1125699);
    os << "Testing expression -> (" << expressionString8 << "). Expected: " << expectedOutput8 << ": " << expression8.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 9
    os << "TEST 9: " << std::endl;
    mstring expressionString9 = "-(--1125699)";
    BigNumberExpression expression9(expressionString9);
    int expectedOutput9 = -(1125699);
    os << "Testing expression -> (" << expressionString9 << "). Expected: " << expectedOutput9 << ": " << expression9.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 10
    os << "TEST 10: " << std::endl;
    mstring expressionString10 = "-+(--(-1125699))";
    BigNumberExpression expression10(expressionString10);
    int expectedOutput10 = -+((-1125699));
    os << "Testing expression -> (" << expressionString10 << "). Expected: " << expectedOutput10 << ": " << expression10.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 11
    os << "TEST 11: " << std::endl;
    mstring expressionString11 = "(-(-((1125699))))";
    BigNumberExpression expression11(expressionString11);
    int expectedOutput11 = (-(-((1125699))));
    os << "Testing expression -> (" << expressionString11 << "). Expected: " << expectedOutput11 << ": " << expression11.evaluateExpression();
    os << std::endl;
    os << std::endl;
}

void BigNumberExpressionTests::solveExpressionParenthesis_AdditionAndMinusTests(std::ostream& os)
{
    os << "---EXPRESSION SOLVING TESTS FOR \"+\" AND \"-\" OPERATORS: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 1: " << std::endl;
    mstring expressionString1 = "(10 + 5) + 5";
    BigNumberExpression expression1(expressionString1);
    int expectedOutput1 = (10 + 5) + 5;
    os << "Testing expression -> (" << expressionString1 << "). Expected: " << expectedOutput1 << ": " << expression1.evaluateExpression();
    os << std::endl;

    //TEST 2
    os << "TEST 2: " << std::endl;
    mstring expressionString2 = "(10 + -5) + -(5 - 6)-(-(-(14--(10+5-4- -3))))";
    BigNumberExpression expression2(expressionString2);
    int expectedOutput2 = (10 + -5) + -(5 - 6) - (-(-(14 + (10 + 5 - 4 - -3)))); //Expected: 6 - 28 = -22
    os << "Testing expression -> (" << expressionString2 << "). Expected: " << expectedOutput2 << ": " << expression2.evaluateExpression();
    os << std::endl;

    //TEST 3
    os << "TEST 3: " << std::endl;
    mstring expressionString3 = "(-(10 + -5 + -5 - 6-(--(14--10+5-4- -3))))";
    BigNumberExpression expression3(expressionString3);
    int expectedOutput3 = (-(10 + -5 + -5 - 6 - ((14 + 10 + 5 - 4 - -3)))); //Expected: -(-6 - 28) = 34
    os << "Testing expression -> (" << expressionString3 << "). Expected: " << expectedOutput3 << ": " << expression3.evaluateExpression();
    os << std::endl;
}

void BigNumberExpressionTests::solveExpressionParenthesis_DivideTests(std::ostream& os)
{
    os << "---EXPRESSION SOLVING TESTS FOR \"/\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 1: " << std::endl;
    mstring expressionString1 = "(125/5)";
    BigNumberExpression expression1(expressionString1);
    int expectedOutput1 = (125 / 5);
    os << "Testing expression -> (" << expressionString1 << "). Expected: " << expectedOutput1 << ": " << expression1.evaluateExpression();
    os << std::endl;

    //TEST 2
    os << "TEST 2: " << std::endl;
    mstring expressionString2 = "100/(2+3)";
    BigNumberExpression expression2(expressionString2);
    int expectedOutput2 = 100 / (2 + 3);
    os << "Testing expression -> (" << expressionString2 << "). Expected: " << expectedOutput2 << ": " << expression2.evaluateExpression();
    os << std::endl;

    //TEST 3
    os << "TEST 3: " << std::endl;
    mstring expressionString3 = "-(100/((576 - 35/(9-2)*2/(12 - 4/2))/575*6/(3+4-1)*3 - 3))";
    BigNumberExpression expression3(expressionString3);
    os << "Testing expression -> (" << expressionString3 << "). Expected: " << BigNumberExpression::EXPRESSION_DIVIDEBYZERO_EXCEPTION << ": ";
    try
    {
        os << expression3.evaluateExpression();
    }
    catch (mstring e)
    {
        os << e;
    }
    os << std::endl;
    os << std::endl;

    //TEST 4
    os << "TEST 4: " << std::endl;
    mstring expressionString4 = "-(100/(576 - 35/(9-2)*2/(12 - 4/2))/575*6/(3+4-1)*3 - 3)";
    BigNumberExpression expression4(expressionString4);
    int expectedOutput4 = -(100 / (576 - 35 / (9 - 2) * 2 / (12 - 4 / 2)) / 575 * 6 / (3 + 4 - 1) * 3 - 3); //Expected -(-3) -> 3
    os << "Testing expression -> (" << expressionString4 << "). Expected: " << expectedOutput4 << ": " << expression4.evaluateExpression();;
    os << std::endl;
}

void BigNumberExpressionTests::solveExpressionParenthesis_MultiplyTests(std::ostream& os)
{
    os << "---EXPRESSION SOLVING TESTS FOR \"*\" OPERATOR:" << std::endl << std::endl;

    //TEST 1
    os << "TEST 1: " << std::endl;
    mstring expressionString1 = "(4*3)";
    BigNumberExpression expression1(expressionString1);
    int expectedOutput1 = (4 * 3);
    os << "Testing expression -> (" << expressionString1 << "). Expected: " << expectedOutput1 << ": " << expression1.evaluateExpression();
    os << std::endl;

    //TEST 2
    os << "TEST 2: " << std::endl;
    mstring expressionString2 = "4*(3-2)";
    BigNumberExpression expression2(expressionString2);
    int expectedOutput2 = 4 * (3 - 2);
    os << "Testing expression -> (" << expressionString2 << "). Expected: " << expectedOutput2 << ": " << expression2.evaluateExpression();
    os << std::endl;

    //TEST 3
    os << "TEST 3: " << std::endl;
    mstring expressionString3 = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))";
    BigNumberExpression expression3(expressionString3);
    int expectedOutput3 = (10 + -5) * 7 + -2 * 3 * (5 - 3 * 6) - (-(-2 * (14 + (10 + 5 - 4 - -3)))); //Expected: 57
    os << "Testing expression -> (" << expressionString3 << "). Expected: " << expectedOutput3 << ": " << expression3.evaluateExpression();
    os << std::endl;

    //TEST 4
    os << "TEST 4: " << std::endl;
    mstring expressionString4 = "(-1*(2*(-2*((10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))))))";
    BigNumberExpression expression4(expressionString4);
    int expectedOutput4 = (-1 * (2 * (-2 * ((10 + -5) * 7 + -2 * 3 * (5 - 3 * 6) - (-(-2 * (14 + (10 + 5 - 4 - -3)))))))); //Expected: 228
    os << "Testing expression -> (" << expressionString4 << "). Expected: " << expectedOutput4 << ": " << expression4.evaluateExpression();
    os << std::endl;
}

void BigNumberExpressionTests::solveExpressionParenthesis_PercentTests(std::ostream& os)
{
    os << "---EXPRESSION SOLVING TESTS FOR \"%\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 1: " << std::endl;
    mstring expressionString1 = "(125%5)";
    BigNumberExpression expression1(expressionString1);
    int expectedOuput1 = (125 % 5);
    os << "Testing expression -> (" << expressionString1 << "). Expected: " << expectedOuput1 << ": " << expression1.evaluateExpression();
    os << std::endl;

    //TEST 2
    os << "TEST 2: " << std::endl;
    mstring expressionString2 = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7";
    BigNumberExpression expression2(expressionString2);
    int expectedOuput2 = ((1000 - 1001) - (((100 - 15 % (5 * 4)) / 2 - 42) % 5 + 1000) % (200 + 100 * (3 - 1))) % -7; //Expected: -5 //-201%-7=28(-5)
    os << "Testing expression -> (" << expressionString2 << "). Expected: " << expectedOuput2 << ": " << expression2.evaluateExpression();;
    os << std::endl;

    //TEST 3
    os << "TEST 3: " << std::endl;
    mstring expressionString3 = "5%((100 - 15%(5*4))/2 - 42) + 1000"; //Expected 5%0 + 1000 --> Exception thrown
    BigNumberExpression expression3(expressionString3);
    os << "Testing expression -> (" << expressionString3 << "). Expected: " << BigNumberExpression::EXPRESSION_PERCENTBYZERO_EXCEPTION << ": ";
    try
    {
        os << expression3.evaluateExpression();
    }
    catch (mstring e)
    {
        os << e;
    }
    os << std::endl;
    os << std::endl;
}

void BigNumberExpressionTests::solveExpressionParenthesisTests(std::ostream& os)
{
    // Expression solving tests
    os << "EXPRESSION SOLVING TESTS WITH PARENTHESIS: " << std::endl << std::endl;

    solveExpressionParenthesis_SingleNumberTests(os);

    solveExpressionParenthesis_AdditionAndMinusTests(os);

    solveExpressionParenthesis_MultiplyTests(os);

    solveExpressionParenthesis_DivideTests(os);

    solveExpressionParenthesis_PercentTests(os);
}

void BigNumberExpressionTests::generateExpressionTemplateTests(std::ostream& os)
{
    //Generating expressions templates tests
    os << "GENERATE EXPRESSION TEMPLATES TESTS" << std::endl << std::endl;

    BigNumberExpression expression = BigNumberExpression();

    srand(time(NULL));
    for (size_t i = 0; i < 50; i++)
    {
        os << "TEST " << i + 1 << ": " << std::endl;
        mstring expressionTemplate = expression.generateExpressionTemplate();
        os << "Testing the generating of an expression template --> "
            << expressionTemplate
            << ". Is the expression template valid? Expect: TRUE: "
            << (expression.expressionTemplateIsValid(expressionTemplate) ? "TRUE" : "FALSE");

        os << std::endl;
        os << std::endl;
    }
}

void BigNumberExpressionTests::generateExpressionTests(std::ostream& os)
{
    os << "GENERATE EXPRESSION TESTS" << std::endl << std::endl;

    BigNumberExpression expression = BigNumberExpression();

    srand(time(NULL));

    for (size_t i = 0; i < 50; i++)
    {
        os << "TEST " << i + 1 << ": " << std::endl;
        expression.generateExpression();
        mstring expressionTemplate = expression.getExpressionTemplate();

        if (!expression.expressionTemplateIsValid(expressionTemplate)) throw "The expression template is invalid somehow. This shouldn't happen";

        os << "Testing the generating of an expression --> " << expressionTemplate << " --> " << expression.getExpression();
        os << ". Is the expression valid? Expect: TRUE: " << (expression.expressionIsValid() ? "TRUE" : "FALSE") << std::endl;
        os << "Answer to the expression --> ";
        try
        {
            os << expression.evaluateExpression();
        }
        catch (mstring e)
        {
            os << e;
        }

        os << std::endl;
        os << std::endl;
    }

    for (size_t i = 50; i < 99; i++)
    {
        os << "TEST " << i + 1 << ": " << std::endl;
        expression.generateExpression("+-*/");
        mstring expressionTemplate = expression.getExpressionTemplate();

        if (!expression.expressionTemplateIsValid(expressionTemplate)) throw "The expression template is invalid somehow. This shouldn't happen";

        os << "Testing the generating of an expression without a percent operator --> " << expressionTemplate << " --> " << expression.getExpression();
        os << ". Is the expression valid? Expect: TRUE: " << (expression.expressionIsValid() && !MStringManip::stringContains(expression.getExpression(), "%") ? "TRUE" : "FALSE") << std::endl;
        os << "Answer to the expression --> ";
        try
        {
            os << expression.evaluateExpression();
        }
        catch (mstring e)
        {
            os << e;
        }

        os << std::endl;
        os << std::endl;
    }
}

void BigNumberExpressionTests::comparativeOperatorsTests(std::ostream& os)
{
    os << "COMPARATIVE OPERATORS TESTS: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 1: " << std::endl;
    mstring expressionString11 = "125/5";
    mstring expressionString12 = "25";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);

    os << "Testing if [" << expressionString11 << "] == [" << expressionString12 << "] -> Expected: TRUE: " << (expression11 == expression12 ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2: " << std::endl;
    mstring expressionString21 = "125/25";
    mstring expressionString22 = "25";
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);

    os << "Testing if [" << expressionString21 << "] != [" << expressionString22 << "] -> Expected: TRUE: " << (expression21 != expression22 ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;

    //TEST 3
    os << "TEST 3: " << std::endl;
    mstring expressionString31 = "24/3";
    mstring expressionString32 = "4+3";
    BigNumberExpression expression31(expressionString31);
    BigNumberExpression expression32(expressionString32);

    os << "Testing if [" << expressionString31 << "] > [" << expressionString32 << "] -> Expected: TRUE: " << (expression31 > expression32 ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;

    //TEST 4
    os << "TEST 4: " << std::endl;
    mstring expressionString41 = "100%23";
    mstring expressionString42 = "1000/(50 + 25*2)";
    BigNumberExpression expression41(expressionString41);
    BigNumberExpression expression42(expressionString42);

    os << "Testing if [" << expressionString41 << "] < [" << expressionString42 << "] -> Expected: TRUE: " << (expression41 < expression42 ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;

    //TEST 5
    os << "TEST 5: " << std::endl;
    mstring expressionString51 = "24/3";
    mstring expressionString52 = "4+4";
    BigNumberExpression expression51(expressionString51);
    BigNumberExpression expression52(expressionString52);

    os << "Testing if [" << expressionString51 << "] >= [" << expressionString52 << "] -> Expected: TRUE: " << (expression51 >= expression52 ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;

    //TEST 6
    os << "TEST 6: " << std::endl;
    mstring expressionString61 = "100%(23+2)+10";
    mstring expressionString62 = "1000/(50 + 25*2)";
    BigNumberExpression expression61(expressionString61);
    BigNumberExpression expression62(expressionString62);

    os << "Testing if [" << expressionString61 << "] <= [" << expressionString62 << "] -> Expected: TRUE: " << (expression61 <= expression62 ? "TRUE" : "FALSE");
    os << std::endl;
    os << std::endl;
}

void BigNumberExpressionTests::operatorSumTests(std::ostream& os)
{
    os << "EXPRESSION TESTS FOR \"+\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 1: " << std::endl;
    mstring expressionString11 = "125/5";
    mstring expressionString12 = "(25)";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
    BigNumberExpression expression13 = expression11 + expression12;
    mstring expectedOuput1 = "(125/5)+((25))";
    os << "Testing expression -> [ " << expressionString11 << " + " << expressionString12 << " ]. Expected: " << expectedOuput1 << ": " << expression13.getExpression() << std::endl;
    os << "Are these expressions the same: " << (expectedOuput1 == expression13.getExpression() ? "TRUE" : "FALSE") << std::endl;
    os << "The answer to the expression: Expected: 50: " << expression13.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2: " << std::endl;
    mstring expressionString21 = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; //-5
    mstring expressionString22 = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))"; //57
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);
    BigNumberExpression expression23 = expression21 + expression22;
    mstring expectedOuput2 = "(((1000-1001)-(((100-15%(5*4))/2-42)%5+1000)%(200+100*(3-1)))%-7)+((10+-5)*7+-2*3*(5-3*6)-(-(-2*(14--(10+5-4--3)))))";
    os << "Testing expression -> [ " << expressionString21 << " + " << expressionString22 << " ]. Expected: " << expectedOuput2 << ": " << expression23.getExpression() << std::endl;
    os << "Are these expressions the same: " << (expectedOuput2 == expression23.getExpression() ? "TRUE" : "FALSE") << std::endl;
    os << "The answer to the expression: Expected: 52: " << expression23.evaluateExpression();
    os << std::endl;
    os << std::endl;
}

void BigNumberExpressionTests::operatorSumAndEqualsTests(std::ostream& os)
{
    os << "EXPRESSION TESTS FOR \"+=\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 1: " << std::endl;
    mstring expressionString11 = "125/5";
    mstring expressionString12 = "(25)";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
    expression11 += expression12;
    mstring expectedOuput1 = "(125/5)+((25))";
    os << "Testing expression -> [ " << expressionString11 << " += " << expressionString12 << " ]. Expected: " << expectedOuput1 << ": " << expression11.getExpression() << std::endl;
    os << "Are these expressions the same: " << (expectedOuput1 == expression11.getExpression() ? "TRUE" : "FALSE") << std::endl;
    os << "The answer to the expression: Expected: 50: " << expression11.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2: " << std::endl;
    mstring expressionString21 = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; //-5
    mstring expressionString22 = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))"; //57
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);
    expression21 += expression22;
    mstring expectedOuput2 = "(((1000-1001)-(((100-15%(5*4))/2-42)%5+1000)%(200+100*(3-1)))%-7)+((10+-5)*7+-2*3*(5-3*6)-(-(-2*(14--(10+5-4--3)))))";
    os << "Testing expression -> [ " << expressionString21 << " += " << expressionString22 << " ]. Expected: " << expectedOuput2 << ": " << expression21.getExpression() << std::endl;
    os << "Are these expressions the same: " << (expectedOuput2 == expression21.getExpression() ? "TRUE" : "FALSE") << std::endl;
    os << "The answer to the expression: Expected: 52: " << expression21.evaluateExpression();
    os << std::endl;
    os << std::endl;
}

void BigNumberExpressionTests::operatorMinusTests(std::ostream& os)
{
    os << "EXPRESSION TESTS FOR \"-\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 1: " << std::endl;
    mstring expressionString11 = "125/5";
    mstring expressionString12 = "(25)";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
    BigNumberExpression expression13 = expression11 - expression12;
    mstring expectedOuput1 = "(125/5)-((25))";
    os << "Testing expression -> [ " << expressionString11 << " - " << expressionString12 << " ]. Expected: " << expectedOuput1 << ": " << expression13.getExpression() << std::endl;
    os << "Are these expressions the same: " << (expectedOuput1 == expression13.getExpression()? "TRUE" : "FALSE") << std::endl;
    os << "The answer to the expression: Expected: 0: " << expression13.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2: " << std::endl;
    mstring expressionString21 = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; //-5
    mstring expressionString22 = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))"; //57
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);
    BigNumberExpression expression23 = expression21 - expression22;
    mstring expectedOuput2 = "(((1000-1001)-(((100-15%(5*4))/2-42)%5+1000)%(200+100*(3-1)))%-7)-((10+-5)*7+-2*3*(5-3*6)-(-(-2*(14--(10+5-4--3)))))";
    os << "Testing expression -> [ " << expressionString21 << " - " << expressionString22 << " ]. Expected: " << expectedOuput2 << ": " << expression23.getExpression() << std::endl;
    os << "Are these expressions the same: " << (expectedOuput2 == expression23.getExpression() ? "TRUE" : "FALSE") << std::endl;
    os << "The answer to the expression: Expected: -62: " << expression23.evaluateExpression();
    os << std::endl;
    os << std::endl;
}

void BigNumberExpressionTests::operatorMinusAndEqualsTests(std::ostream& os)
{
    os << "EXPRESSION TESTS FOR \"-=\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 1: " << std::endl;
    mstring expressionString11 = "125/5";
    mstring expressionString12 = "(25)";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
    expression11 -= expression12;
    mstring expectedOuput1 = "(125/5)-((25))";
    os << "Testing expression -> [ " << expressionString11 << " -= " << expressionString12 << " ]. Expected: " << expectedOuput1 << ": " << expression11.getExpression() << std::endl;
    os << "Are these expressions the same: " << (expectedOuput1 == expression11.getExpression() ? "TRUE" : "FALSE") << std::endl;
    os << "The answer to the expression: Expected: 0: " << expression11.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2: " << std::endl;
    mstring expressionString21 = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; //-5
    mstring expressionString22 = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))"; //57
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);
    expression21 -= expression22;
    mstring expectedOuput2 = "(((1000-1001)-(((100-15%(5*4))/2-42)%5+1000)%(200+100*(3-1)))%-7)-((10+-5)*7+-2*3*(5-3*6)-(-(-2*(14--(10+5-4--3)))))";
    os << "Testing expression -> [ " << expressionString21 << " -= " << expressionString22 << " ]. Expected: " << expectedOuput2 << ": " << expression21.getExpression() << std::endl;
    os << "Are these expressions the same: " << (expectedOuput2 == expression21.getExpression() ? "TRUE" : "FALSE") << std::endl;
    os << "The answer to the expression: Expected: -62: " << expression21.evaluateExpression();
    os << std::endl;
    os << std::endl;
}

void BigNumberExpressionTests::operatorMultiplyTests(std::ostream& os)
{
    os << "EXPRESSION TESTS FOR \"*\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 1: " << std::endl;
    mstring expressionString11 = "125/5";
    mstring expressionString12 = "(25)";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
    BigNumberExpression expression13 = expression11 * expression12;
    mstring expectedOuput1 = "(125/5)*((25))";
    os << "Testing expression -> [ " << expressionString11 << " * " << expressionString12 << " ]. Expected: " << expectedOuput1 << ": " << expression13.getExpression() << std::endl;
    os << "Are these expressions the same: " << (expectedOuput1 == expression13.getExpression() ? "TRUE" : "FALSE") << std::endl;
    os << "The answer to the expression: Expected: 625: " << expression13.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2: " << std::endl;
    mstring expressionString21 = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; //-5
    mstring expressionString22 = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))"; //57
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);
    BigNumberExpression expression23 = expression21 * expression22;
    mstring expectedOuput2 = "(((1000-1001)-(((100-15%(5*4))/2-42)%5+1000)%(200+100*(3-1)))%-7)*((10+-5)*7+-2*3*(5-3*6)-(-(-2*(14--(10+5-4--3)))))";
    os << "Testing expression -> [ " << expressionString21 << " * " << expressionString22 << " ]. Expected: " << expectedOuput2 << ": " << expression23.getExpression() << std::endl;
    os << "Are these expressions the same: " << (expectedOuput2 == expression23.getExpression() ? "TRUE" : "FALSE") << std::endl;
    os << "The answer to the expression: Expected: -285: " << expression23.evaluateExpression();
    os << std::endl;
    os << std::endl;
}

void BigNumberExpressionTests::operatorMultiplyAndEqualsTests(std::ostream& os)
{
    os << "EXPRESSION TESTS FOR \"*=\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 1: " << std::endl;
    mstring expressionString11 = "125/5";
    mstring expressionString12 = "(25)";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
    expression11 *= expression12;
    mstring expectedOuput1 = "(125/5)*((25))";
    os << "Testing expression -> [ " << expressionString11 << " *= " << expressionString12 << " ]. Expected: " << expectedOuput1 << ": " << expression11.getExpression() << std::endl;
    os << "Are these expressions the same: " << (expectedOuput1 == expression11.getExpression() ? "TRUE" : "FALSE") << std::endl;
    os << "The answer to the expression: Expected: 625: " << expression11.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2: " << std::endl;
    mstring expressionString21 = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; //-5
    mstring expressionString22 = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))"; //57
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);
    expression21 *= expression22;
    mstring expectedOuput2 = "(((1000-1001)-(((100-15%(5*4))/2-42)%5+1000)%(200+100*(3-1)))%-7)*((10+-5)*7+-2*3*(5-3*6)-(-(-2*(14--(10+5-4--3)))))";
    os << "Testing expression -> [ " << expressionString21 << " *= " << expressionString22 << " ]. Expected: " << expectedOuput2 << ": " << expression21.getExpression() << std::endl;
    os << "Are these expressions the same: " << (expectedOuput2 == expression21.getExpression() ? "TRUE" : "FALSE") << std::endl;
    os << "The answer to the expression: Expected: -285: " << expression21.evaluateExpression();
    os << std::endl;
    os << std::endl;
}

void BigNumberExpressionTests::operatorDivideTests(std::ostream& os)
{
    os << "EXPRESSION TESTS FOR \"/\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 1: " << std::endl;
    mstring expressionString11 = "125/5";
    mstring expressionString12 = "(25)";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
    BigNumberExpression expression13 = expression11 / expression12;
    mstring expectedOuput1 = "(125/5)/((25))";
    os << "Testing expression -> [ " << expressionString11 << " / " << expressionString12 << " ]. Expected: " << expectedOuput1 << ": " << expression13.getExpression() << std::endl;
    os << "Are these expressions the same: " << (expectedOuput1 == expression13.getExpression() ? "TRUE" : "FALSE") << std::endl;
    os << "The answer to the expression: Expected: 1: " << expression13.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2: " << std::endl;
    mstring expressionString21 = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; //-5
    mstring expressionString22 = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))"; //57
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);
    BigNumberExpression expression23 = expression21 / expression22;
    mstring expectedOuput2 = "(((1000-1001)-(((100-15%(5*4))/2-42)%5+1000)%(200+100*(3-1)))%-7)/((10+-5)*7+-2*3*(5-3*6)-(-(-2*(14--(10+5-4--3)))))";
    os << "Testing expression -> [ " << expressionString21 << " / " << expressionString22 << " ]. Expected: " << expectedOuput2 << ": " << expression23.getExpression() << std::endl;
    os << "Are these expressions the same: " << (expectedOuput2 == expression23.getExpression() ? "TRUE" : "FALSE") << std::endl;
    os << "The answer to the expression: Expected: 0: " << expression23.evaluateExpression();
    os << std::endl;
    os << std::endl;
}

void BigNumberExpressionTests::operatorDivideAndEqualsTests(std::ostream& os)
{
    os << "EXPRESSION TESTS FOR \"/=\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 1: " << std::endl;
    mstring expressionString11 = "125/5";
    mstring expressionString12 = "(25)";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
    expression11 /= expression12;
    mstring expectedOuput1 = "(125/5)/((25))";
    os << "Testing expression -> [ " << expressionString11 << " /= " << expressionString12 << " ]. Expected: " << expectedOuput1 << ": " << expression11.getExpression() << std::endl;
    os << "Are these expressions the same: " << (expectedOuput1 == expression11.getExpression() ? "TRUE" : "FALSE") << std::endl;
    os << "The answer to the expression: Expected: 1: " << expression11.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2: " << std::endl;
    mstring expressionString21 = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; //-5
    mstring expressionString22 = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))"; //57
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);
    expression21 /= expression22;
    mstring expectedOuput2 = "(((1000-1001)-(((100-15%(5*4))/2-42)%5+1000)%(200+100*(3-1)))%-7)/((10+-5)*7+-2*3*(5-3*6)-(-(-2*(14--(10+5-4--3)))))";
    os << "Testing expression -> [ " << expressionString21 << " /= " << expressionString22 << " ]. Expected: " << expectedOuput2 << ": " << expression21.getExpression() << std::endl;
    os << "Are these expressions the same: " << (expectedOuput2 == expression21.getExpression() ? "TRUE" : "FALSE") << std::endl;
    os << "The answer to the expression: Expected: 0: " << expression21.evaluateExpression();
    os << std::endl;
    os << std::endl;
}

void BigNumberExpressionTests::operatorPercentTests(std::ostream& os)
{
    os << "EXPRESSION TESTS FOR \"%\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 1: " << std::endl;
    mstring expressionString11 = "125/5";
    mstring expressionString12 = "(25)";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
    BigNumberExpression expression13 = expression11 % expression12;
    mstring expectedOuput1 = "(125/5)%((25))";
    os << "Testing expression -> [ " << expressionString11 << " % " << expressionString12 << " ]. Expected: " << expectedOuput1 << ": " << expression13.getExpression() << std::endl;
    os << "Are these expressions the same: " << (expectedOuput1 == expression13.getExpression() ? "TRUE" : "FALSE") << std::endl;
    os << "The answer to the expression: Expected: 0: " << expression13.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2: " << std::endl;
    mstring expressionString21 = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; //-5
    mstring expressionString22 = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))"; //57
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);
    BigNumberExpression expression23 = expression21 % expression22;
    mstring expectedOuput2 = "(((1000-1001)-(((100-15%(5*4))/2-42)%5+1000)%(200+100*(3-1)))%-7)%((10+-5)*7+-2*3*(5-3*6)-(-(-2*(14--(10+5-4--3)))))";
    os << "Testing expression -> [ " << expressionString21 << " % " << expressionString22 << " ]. Expected: " << expectedOuput2 << ": " << expression23.getExpression() << std::endl;
    os << "Are these expressions the same: " << (expectedOuput2 == expression23.getExpression() ? "TRUE" : "FALSE") << std::endl;
    os << "The answer to the expression: Expected: -5: " << expression23.evaluateExpression();
    os << std::endl;
    os << std::endl;
}

void BigNumberExpressionTests::operatorPercentAndEqualsTests(std::ostream& os)
{
    os << "EXPRESSION TESTS FOR \"%=\" OPERATOR: " << std::endl << std::endl;

    //TEST 1
    os << "TEST 1: " << std::endl;
    mstring expressionString11 = "125/5";
    mstring expressionString12 = "(25)";
    BigNumberExpression expression11(expressionString11);
    BigNumberExpression expression12(expressionString12);
    expression11 %= expression12;
    mstring expectedOuput1 = "(125/5)%((25))";
    os << "Testing expression -> [ " << expressionString11 << " % " << expressionString12 << " ]. Expected: " << expectedOuput1 << ": " << expression11.getExpression() << std::endl;
    os << "Are these expressions the same: " << (expectedOuput1 == expression11.getExpression() ? "TRUE" : "FALSE") << std::endl;
    os << "The answer to the expression: Expected: 0: " << expression11.evaluateExpression();
    os << std::endl;
    os << std::endl;

    //TEST 2
    os << "TEST 2: " << std::endl;
    mstring expressionString21 = "((1000-1001) - (((100 - 15%(5*4))/2 - 42)%5 + 1000) % (200 + 100*(3-1)))%-7"; //-5
    mstring expressionString22 = "(10 + -5)*7 + -2*3*(5 - 3*6)-(-(-2*(14--(10+5-4- -3))))"; //57
    BigNumberExpression expression21(expressionString21);
    BigNumberExpression expression22(expressionString22);
    expression21 %= expression22;
    mstring expectedOuput2 = "(((1000-1001)-(((100-15%(5*4))/2-42)%5+1000)%(200+100*(3-1)))%-7)%((10+-5)*7+-2*3*(5-3*6)-(-(-2*(14--(10+5-4--3)))))";
    os << "Testing expression -> [ " << expressionString21 << " %= " << expressionString22 << " ]. Expected: " << expectedOuput2 << ": " << expression21.getExpression() << std::endl;
    os << "Are these expressions the same: " << (expectedOuput2 == expression21.getExpression() ? "TRUE" : "FALSE") << std::endl;
    os << "The answer to the expression: Expected: -5: " << expression21.evaluateExpression();
    os << std::endl;
    os << std::endl;
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

void BigNumberExpressionTests::readFromAndWriteToFileTests(std::ostream& os)
{
    os << "READ AND WRITE FROM AND TO FILE TESTS" << std::endl << std::endl;

    //TEST 1
    os << "TEST 1" << std::endl;

    std::ifstream is("Expressions.txt");
    int somethingDebug = (15 - (3 * 156 / 343 % (6 / 2 * 4 % 10 + 43))) + 10;
    BigNumberExpression expression1 = BigNumberExpression();
    BigNumberExpression expression2 = BigNumberExpression();
    is >> expression1;
    is >> expression2;

    is.close();

    std::ofstream osExpressions("ExpressionsAnswers.txt");

    osExpressions << expression1;
    osExpressions << expression2;

    osExpressions.close();
}

void BigNumberExpressionTests::runTests(std::ostream& os)
{
    std::cout << "Start the tests for BigNumberExpression! ";
    if (&os != &std::cout)
    {
        std::cout << "The test results are being outputted to text file with name: " << OUTPUTFILE_NAME << std::endl;
        time_t timetoday;
        time(&timetoday);
        mstring timeOfRunningTheTests = MStringManip::replaceFirst(ctime(&timetoday), "\n", "");
        os << "---------------------------- " << "" << timeOfRunningTheTests << " ----------------------------\n\n";
    }

    //Big 4 tests
    expressionBig4Tests(os);

    // Expression is valid tests
    expressionIsValidTests(os);

    //Solving expression tests without parenthesis
    solveExpressionNoParenthesisTests(os);

    //Solving expression tests with parenthesis
    solveExpressionParenthesisTests(os);

    //Generating expressions templates tests
    generateExpressionTemplateTests(os);

    //Generating expressions tests
    generateExpressionTests(os);

    //Comparative operators tests
    comparativeOperatorsTests(os);

    //Operator + tests
    operatorSumTests(os);

    //Operator += tests
    operatorSumAndEqualsTests(os);

    //Operator - tests
    operatorMinusTests(os);

    //Operator -= tests
    operatorMinusAndEqualsTests(os);

    //Operator * tests
    operatorMultiplyTests(os);

    //Operator *= tests
    operatorMultiplyAndEqualsTests(os);

    //Operator / tests
    operatorDivideTests(os);

    //Operator /= tests
    operatorDivideAndEqualsTests(os);

    //Operator % tests
    operatorPercentTests(os);

    //Operator %= tests
    operatorPercentAndEqualsTests(os);

    //Read from and Write to console tests
    //readFromAndWriteToConsoleTests();

    //Read from and Write to console tests
    readFromAndWriteToFileTests(os);

    os << std::endl << std::endl;
}
