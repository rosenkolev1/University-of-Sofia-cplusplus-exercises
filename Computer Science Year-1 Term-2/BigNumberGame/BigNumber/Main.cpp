// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "BigNumber.h"
#include "BigNumberDivisionResult.h"
#include "BigNumberTests.h"
#include "BigNumberExpression.h"
#include "BigNumberExpressionTests.h"
#include "BigNumberEquationTests.h"

//TODO: create equations with BigNumber(medium) and make an equation solver with BigNumber(hard)

int main()
{
    std::ofstream osEquationTests(BigNumberEquationTests::OUTPUTFILE_NAME, std::ios::app);
    std::ofstream osExpressionTests(BigNumberExpressionTests::OUTPUTFILE_NAME, std::ios::app);
    std::ofstream osBigNumberTests("BugNumber_Tests_Diagnostics.txt", std::ios::app);

    //BigNumber tests
    //BigNumberTests::runTests();

    //BigNumberExpression tests
    BigNumberExpressionTests::runTests(osExpressionTests);

    //BigNumberEquations tests
    //BigNumberEquationTests::runTests(osEquationTests);

    osEquationTests.close();
    osExpressionTests.close();
    osBigNumberTests.close();
}