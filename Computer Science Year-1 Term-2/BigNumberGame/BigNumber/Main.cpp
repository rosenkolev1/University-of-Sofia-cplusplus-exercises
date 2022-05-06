// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BigNumber.h"
#include "BigNumberDivisionResult.h"
#include "BigNumberTests.h"
#include "BigNumberEquation.h"

void equationBig4Tests()
{
    //BigNumberTests::runTests();
    BigNumberEquation equation1 = BigNumberEquation();
    char someEquation[] = "Some equation";
    char anotherEquation[] = "anotherEquation";
    BigNumberEquation equation2(someEquation);
    BigNumberEquation equation3(anotherEquation);

    std::cout << "Equation 1: Expected: " << "{empty}" << ": " << (equation1.getEquation() == nullptr ? "{empty}" : "WRONG") << std::endl;
    std::cout << "Equation 2: Expected: " << someEquation << ": " << equation2.getEquation() << std::endl;
    std::cout << "Equation 3: Expected: " << anotherEquation << ": " << equation3.getEquation() << std::endl;

    std::cout << std::endl;

    equation1 = equation2;
    std::cout << "Testing \"equation1 = equation2;\" \n";
    std::cout << "Equation 1: Expected: " << someEquation << ": " << equation1.getEquation() << std::endl;

    std::cout << std::endl;

    equation2 = equation3;
    std::cout << "Testing \"equation2 = equation3;\" \n";
    std::cout << "Equation 2: Expected: " << anotherEquation << ": " << equation2.getEquation() << std::endl;

    std::cout << std::endl;

    BigNumberEquation equation4(equation1);
    std::cout << "Testing \"BigNumberEquation equation4 (equation1);\" \n";
    std::cout << "Equation 4: Expected: " << someEquation << ": " << equation4.getEquation() << std::endl;
}

void solveEquationTests()
{
    // Equation solving tests
    std::cout << "Equation solving TESTS: " << std::endl << std::endl;

    BigNumberEquation equation1("10 + 5");
    std::cout << "Testing equation -> (10 + 5). Expected: 15: " << equation1.evaluteExpression();



    std::cout << std::endl;
}

int main()
{
    //Big 4 tests
    //equationBig4Tests();

    //Solving an equation tests
    solveEquationTests();
}