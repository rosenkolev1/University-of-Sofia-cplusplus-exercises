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
#include "MBigNumber.h"
#include "MBigNumberDivisionResult.h"
#include "MBigNumberTests.h"
#include "MBigNumberExpression.h"
#include "MBigNumberExpressionTests.h"
#include "MBigNumberEquation.h"
#include "MBigNumberEquationTests.h"

int main()
{
    //ORIGINAL BIG NUMBER
    //std::ofstream osEquationTests(BigNumberEquationTests::OUTPUTFILE_NAME, std::ios::trunc);
    //std::ofstream osExpressionTests(BigNumberExpressionTests::OUTPUTFILE_NAME, std::ios::trunc);
    //std::ofstream osBigNumberTests(BigNumberTests::OUTPUTFILE_NAME, std::ios::trunc);
    //
    ////BigNumber tests
    //BigNumberTests::runTests(std::cout);
    ////BigNumberTests::runTests(osBigNumberTests);
    //
    ////BigNumberExpression tests
    //BigNumberExpressionTests::runTests(std::cout);
    ////BigNumberExpressionTests::runTests(osExpressionTests);
    //
    ////BigNumberEquations tests
    //BigNumberEquationTests::runTests(std::cout);
    ////BigNumberEquationTests::runTests(osEquationTests);
    //
    //osEquationTests.close();
    //osExpressionTests.close();
    //osBigNumberTests.close();

    //--------------------------------------------------------------------------------------------

    //BIGNUMBER with MSTRING
    std::ofstream osBigNumberTests(MBigNumberTests::OUTPUTFILE_NAME, std::ios::trunc);
    std::ofstream osExpressionTests(MBigNumberExpressionTests::OUTPUTFILE_NAME, std::ios::trunc);
    std::ofstream osEquationTests(MBigNumberEquationTests::OUTPUTFILE_NAME, std::ios::trunc);

    //MBigNumber tests
    //MBigNumberTests::runTests(std::cout);
    //MBigNumberTests::runTests(osBigNumberTests);

    //MBigNumberExpression tests
    //MBigNumberExpressionTests::runTests(std::cout);
    //MBigNumberExpressionTests::runTests(osExpressionTests);

    //MBigNumberEquations tests
    MBigNumberEquationTests::runTests(std::cout);
    //MBigNumberEquationTests::runTests(osEquationTests);

    //osEquationTests.close();
    osExpressionTests.close();
    osBigNumberTests.close();
}