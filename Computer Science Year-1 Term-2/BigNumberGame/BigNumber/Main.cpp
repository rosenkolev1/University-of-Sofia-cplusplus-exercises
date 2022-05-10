// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BigNumber.h"
#include "BigNumberDivisionResult.h"
#include "BigNumberTests.h"
#include "BigNumberExpression.h"
#include "BigNumberExpressionTests.h"
#include "BigNumberEquationTests.h"

//TODO: create equations with BigNumber(medium) and make an equation solver with BigNumber(hard)



int main()
{
    //BigNumber tests
    //BigNumberTests::runTests();

    //BigNumberExpression tests
    //BigNumberExpressionTests::runTests();

    //BigNumberEquations tests
    BigNumberEquationTests::runTests();
}