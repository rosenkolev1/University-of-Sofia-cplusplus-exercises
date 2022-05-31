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

int main()
{
    //ORIGINAL BIG NUMBER
   std::ofstream osEquationTests(BigNumberEquationTests::OUTPUTFILE_NAME, std::ios::trunc);
   std::ofstream osExpressionTests(BigNumberExpressionTests::OUTPUTFILE_NAME, std::ios::trunc);
   std::ofstream osBigNumberTests(BigNumberTests::OUTPUTFILE_NAME, std::ios::trunc);
   
   //BigNumber tests
   BigNumberTests::runTests(std::cout);
   //BigNumberTests::runTests(osBigNumberTests);
   
   //BigNumberExpression tests
   BigNumberExpressionTests::runTests(std::cout);
   //BigNumberExpressionTests::runTests(osExpressionTests);
   
   //BigNumberEquations tests
   BigNumberEquationTests::runTests(std::cout);
   //BigNumberEquationTests::runTests(osEquationTests);
   
   osEquationTests.close();
   osExpressionTests.close();
   osBigNumberTests.close();
}