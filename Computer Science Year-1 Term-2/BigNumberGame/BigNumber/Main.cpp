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

void solveExpressionTests()
{
    // Expression solving tests
    std::cout << "Expression solving TESTS: " << std::endl << std::endl;

    BigNumberExpression expression1("10+5");
    std::cout << "Testing expression -> (10+5). Expected: 15: " << expression1.evaluteExpression();

    BigNumberExpression expression2("57-19");
    std::cout << "Testing expression -> (57-19). Expected: 38: " << expression2.evaluteExpression();

    BigNumberExpression expression3("-57-19");
    std::cout << "Testing expression -> (-57-19). Expected: -76: " << expression3.evaluteExpression();

    BigNumberExpression expression4("-345-+15");
    std::cout << "Testing expression -> (-345-+15). Expected: -360: " << expression4.evaluteExpression();

    BigNumberExpression expression5("-345+-15");
    std::cout << "Testing expression -> (-345+-15). Expected: -360: " << expression5.evaluteExpression();

    //BigNumberEquation expression5("345/-15");
    //std::cout << "Testing expression -> (345/-15). Expected: -33: " << expression5.evaluteExpression();

    std::cout << std::endl;
}

int main()
{
    //Big 4 tests
    //expressionBig4Tests();

    //Solving expression tests
    solveExpressionTests();
}