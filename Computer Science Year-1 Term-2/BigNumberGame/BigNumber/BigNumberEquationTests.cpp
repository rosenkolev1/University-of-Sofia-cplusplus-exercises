#include "BigNumberEquationTests.h"
#include "BigNumberEquation.h"
#include <iostream>

void BigNumberEquationTests::generateFromTemplateTests()
{
}

void BigNumberEquationTests::generateEquationTests()
{
    std::cout << "GENERATE EQUATIONS TESTS" << std::endl << std::endl;
    srand(time(NULL));
    for (size_t i = 0; i < 50; i++)
    {
        std::cout << "TEST " << i + 1 << ": " << std::endl;
        BigNumberEquation equation1 = BigNumberEquation();
        equation1.generateEquation();                                   //TODO: make this get the equation template, like in expressions
        std::cout << "Testing the generating of an equation --> " << equation1.getEquation() << " --> " << equation1.getEquation();
        std::cout << ". Is the equation valid? Expect: TRUE: " << (equation1.isValidEquation() ? "TRUE" : "FALSE") << std::endl;
        std::cout << "Answer to the equation --> ";
        try
        {
            std::cout << equation1.solveEquation();
        }
        catch (...)
        {
            std::cout << "Exception thrown because of division by 0 or some other shit";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}

void BigNumberEquationTests::runTests()
{
	//Generate equations from expression templates tests
	//generateFromTemplateTests();

	//Generate equation tests
	generateEquationTests();
}
