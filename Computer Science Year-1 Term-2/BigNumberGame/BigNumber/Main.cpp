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
    std::ofstream osBigNumberTests(BigNumberTests::OUTPUTFILE_NAME, std::ios::app);

    //BigNumber tests
    BigNumberTests::runTests(std::cout);

    //BigNumberExpression tests
    //BigNumberExpressionTests::runTests(std::cout);

    //BigNumberEquations tests
    //BigNumberEquationTests::runTests(std::cout);

    osEquationTests.close();
    osExpressionTests.close();
    osBigNumberTests.close();
}