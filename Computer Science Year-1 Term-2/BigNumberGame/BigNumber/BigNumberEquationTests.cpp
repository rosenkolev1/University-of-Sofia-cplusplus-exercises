#include "BigNumberEquationTests.h"
#include "BigNumberEquation.h"
#include <iostream>
#include "..\Project.StringManipulation\StringManip.h"

void BigNumberEquationTests::equationBig4Tests()
{
    //BIG4 TESTS
    std::cout << "EQUATION BIG4 TESTS" << std::endl << std::endl;

    //SETUP
    BigNumberEquation equation1 = BigNumberEquation();
    char someEquation[] = " 5 + 5*x = 30/x";
    char anotherEquation[] = "15/3*x = 20";
    BigNumberEquation equation2(someEquation);
    BigNumberEquation equation3(anotherEquation);

    std::cout << "Equation 1: Expected: " << "x=0" << ": " << equation1.getEquation() << std::endl;
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
    std::cout << "Testing \"BigNumberEquation equation4(equation1);\" \n";
    std::cout << "Equation 4: Expected: " << someEquation << ": " << equation4.getEquation() << std::endl;

    std::cout << std::endl;
    
}

void BigNumberEquationTests::equationIsValidTests()
{
    //EQUATION IS VALID TESTS
    std::cout << "EQUATION IS VALID TESTS" << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    char equation1[] = "-(35/x*(40+-36/-x*(9-x) + 38)-16)*(x*5/-(x+34)+15)= + x*x/(x*x-x+x*(--10)-x-x*(x-1+x)*x)*(10-x)";
    BigNumberEquation equation(equation1);
    std::cout << "Testing if the equation | " << equation1 << " | is valid: Expected: TRUE ==> " << (equation.isValidEquation() ? "TRUE" : "FALSE");
    std::cout << std::endl << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    char equation2[] = "-+(35/x*(40+-36/-x*(9-x) + 38)-16)*(x*5/-(x+34)+15)= + x*x/(x*x-x+x*(--10)-x-x*(x-1+x)*x)*(10-x)";
    std::cout << "Testing if the equation | " << equation2 << " | is valid: Expected: TRUE ==> " << (equation.isValidEquation(equation2) ? "TRUE" : "FALSE");
    std::cout << std::endl << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    char equation3[] = "--(35/x*(40+-36/-x*(9-x) + 38)-16)*(x*5/-(x+34)+15)= --x*x/(x*x-x+x*(--10)-x-x*(x-1+x)*x)*(10-x)";
    std::cout << "Testing if the equation | " << equation3 << " | is valid: Expected: FALSE ==> " << (equation.isValidEquation(equation3) ? "TRUE" : "FALSE");
    std::cout << std::endl << std::endl;

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    char equation4[] = "--(35/x*(40+-36/-x*(9-x) + 38)-16)*(x*5/-(x+34)+15)-x*x/(x*x-x+x*(--10)-x-x*(x-1+x)*x)*(10-x)";
    std::cout << "Testing if the equation | " << equation4 << " | is valid: Expected: FALSE ==> " << (equation.isValidEquation(equation4) ? "TRUE" : "FALSE");
    std::cout << std::endl << std::endl;

    //TEST 5
    std::cout << "TEST 5" << std::endl;
    char equation5[] = "--(35/x*(40+-36/-x*(9-x) + 38)-16)*(x*5/-(x+34)=+15)-x*x/(x*x-x+x*(--10)-x-x*(x-1+x)*x)*(10-x)";
    std::cout << "Testing if the equation | " << equation5 << " | is valid: Expected: FALSE ==> " << (equation.isValidEquation(equation5) ? "TRUE" : "FALSE");
    std::cout << std::endl << std::endl;

    //TEST 6
    std::cout << "TEST 6" << std::endl;
    char equation6[] = "--(35/x*(40+-36/-x%(9-x) + 38)-16)*(x*5/-(x+34)+15)=-x*x/(x*x-x+x*(--10)-x-x*(x-1+x)*x)*(10-x)";
    std::cout << "Testing if the equation | " << equation6 << " | is valid: Expected: FALSE ==> " << (equation.isValidEquation(equation6) ? "TRUE" : "FALSE");
    std::cout << std::endl << std::endl;

    //TEST 7
    std::cout << "TEST 7" << std::endl;
    char equation7[] = "(35/5*(40+-36/-5*(9-5) + 38)-16)*(5*5/-(5+34)+15)=-5*5/(5*5-5+5*(--10)-5-5*(5-1+5)*5)*(10-5)"; //Expected: 10890 = 0
    std::cout << "Testing if the equation | " << equation7 << " | is valid: Expected: FALSE ==> " << (equation.isValidEquation(equation7) ? "TRUE" : "FALSE");
    std::cout << std::endl << std::endl;

    //TEST 8
    std::cout << "TEST 8" << std::endl;
    int something = (35 / 5 * (40 + -36 / -5 * (9 - 5) + 38) - 16) * (5 * 5 / -(5 + 34) + 15);
    BigNumberExpression somethingExpression("(35/5*(40+-36/-5*(9-5) + 38)-16)*(5*5/-(5+34)+15)");
    BigNumber result = somethingExpression.evaluateExpression();
    char equation8[] = "(35/5*(40+-36/-5*(9-5) + 38)-16)*(5*5/-(5+34)+15)=-5*5/(5*5-5+5*(--10)-5-5*(5-1+5)*5)*(10-5) + 10890"; //Expected: 10890 = 10890
    std::cout << "Testing if the equation | " << equation8 << " | is valid: Expected: TRUE ==> " << (equation.isValidEquation(equation8) ? "TRUE" : "FALSE");
    std::cout << std::endl << std::endl;
}

void BigNumberEquationTests::solveEquationWithoutParenthesisTests()
{
    //SOLVE EQUATIONS WITH NO PARENTHESIS TESTS
    std::cout << "SOLVE EQUATIONS WITH NO PARENTHESIS TESTS" << std::endl << std::endl;

    //TEST PREP
    BigNumberEquation equation;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    char equation1[] = "x=5";
    std::cout << "Testing the answer to the equation | " << equation1 << " |: Expected: 5 ==> " << equation.solveEquation(equation1);
    std::cout << std::endl << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    char equation2[] = "3+x=5";
    std::cout << "Testing the answer to the equation | " << equation2 << " |: Expected: 2 ==> " << equation.solveEquation(equation2);
    std::cout << std::endl << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    char equation3[] = "5-3+x=5";
    std::cout << "Testing the answer to the equation | " << equation3 << " |: Expected: 3 ==> " << equation.solveEquation(equation3);
    std::cout << std::endl << std::endl;

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    char equation4[] = "5-3-x=5";
    std::cout << "Testing the answer to the equation | " << equation4 << " |: Expected: -3 ==> " << equation.solveEquation(equation4);
    std::cout << std::endl << std::endl;

    //TEST 5
    std::cout << "TEST 5" << std::endl;
    char equation5[] = "--5+-3-x=5";
    std::cout << "Testing the answer to the equation | " << equation5 << " |: Expected: -3 ==> " << equation.solveEquation(equation5);
    std::cout << std::endl << std::endl;

    //TEST 6
    std::cout << "TEST 6" << std::endl;
    char equation6[] = "-x+9=5";
    std::cout << "Testing the answer to the equation | " << equation6 << " |: Expected: 4 ==> " << equation.solveEquation(equation6);
    std::cout << std::endl << std::endl;

    //TEST 7
    std::cout << "TEST 7" << std::endl;
    char equation7[] = "-x-+9=5";
    std::cout << "Testing the answer to the equation | " << equation7 << " |: Expected: -14 ==> " << equation.solveEquation(equation7);
    std::cout << std::endl << std::endl;

    //TEST 8
    std::cout << "TEST 8" << std::endl;
    char equation8[] = "-x--9=5";
    std::cout << "Testing the answer to the equation | " << equation8 << " |: Expected: 4 ==> " << equation.solveEquation(equation8);
    std::cout << std::endl << std::endl;

    //TEST 9
    std::cout << "TEST 9" << std::endl;
    char equation9[] = "-x--9+-10-+14=5*3/4+10*(5/3+1)-13"; //-x+9-24=3+10*2-13 ==> -x-15=10 ==> x=-25 
    std::cout << "Testing the answer to the equation | " << equation9 << " |: Expected: -25 ==> " << equation.solveEquation(equation9);
    std::cout << std::endl << std::endl;

    //TEST 10
    std::cout << "TEST 10" << std::endl;
    char equation10[] = "50+74+-69-+69--22-x--9+-10-+14=5*3/4+10*(5/3+1)-13"; //-x-15-15=10 ==> x=-40
    std::cout << "Testing the answer to the equation | " << equation10 << " |: Expected: -40 ==> " << equation.solveEquation(equation10);
    std::cout << std::endl << std::endl;

    //TEST 11
    std::cout << "TEST 11" << std::endl;
    char equation11[] = "+-50+74+-69-+69--21-x--9+-10-+14=5*3/4+10*(5/3+1)-13"; //-x-30-100=10 ==> x=-140
    std::cout << "Testing the answer to the equation | " << equation11 << " |: Expected: -140 ==> " << equation.solveEquation(equation11);
    std::cout << std::endl << std::endl;

    //TEST 12
    std::cout << "TEST 12" << std::endl;
    char equation12[] = "5*3/4+10*(5/3+1)-13=+-50+74+-69-+69--21-x--9+-10-+14"; //-x-30-100=10 ==> x=-140
    std::cout << "Testing the answer to the equation | " << equation12 << " |: Expected: -140 ==> " << equation.solveEquation(equation12);
    std::cout << std::endl << std::endl;
}

void BigNumberEquationTests::generateEquationTests()
{
    std::cout << "GENERATE EQUATIONS TESTS" << std::endl << std::endl;
    srand(time(NULL));
    for (size_t i = 0; i < 50; i++)
    {
        std::cout << "TEST " << i + 1 << ": " << std::endl;
        BigNumberEquation equation1 = BigNumberEquation();
        size_t maxUnknownsPerSide = 3;
        size_t maxUnknownsTotal = 6;
        equation1.generateEquation(maxUnknownsPerSide, maxUnknownsTotal);
        std::cout << "Testing the generating of an equation with up to "<< maxUnknownsPerSide <<" unknowns per side and a total of "<< maxUnknownsTotal <<" unknowns --> " 
            << equation1.getEquationTemplate() << " --> " << equation1.getEquation() << std::endl;
        std::cout << "Is the equation valid? Expect: TRUE ==> " << (equation1.isValidEquation() ? "TRUE" : "FALSE") << std::endl;
        std::cout << "Does the equation have up to "<< maxUnknownsPerSide <<" unknowns per side and a maximum of "<< maxUnknownsTotal <<" unknowns? Expect: TRUE: ";
        
        //Check how many unknowns the equation has on either side.
        size_t sizeOfSides = 0;
        char** sides = StringManip::splitString(equation1.getEquation(), "=", sizeOfSides);
        size_t unknownsInLeftSide = StringManip::countOf(sides[0], "x");
        size_t unknownsInRightSide = StringManip::countOf(sides[1], "x");
        if (unknownsInLeftSide > maxUnknownsPerSide || unknownsInRightSide > maxUnknownsPerSide || unknownsInLeftSide + unknownsInRightSide > maxUnknownsTotal) std::cout << "FALSE";
        else std::cout << "TRUE";

        //Delete dynamic memory
        StringManip::deleteArrayOfStrings(sides, sizeOfSides);

        std::cout << std::endl;
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

    for (size_t i = 50; i < 99; i++)
    {
        std::cout << "TEST " << i + 1 << ": " << std::endl;
        BigNumberEquation equation1 = BigNumberEquation();
        size_t maxUnknownsPerSide = 1;
        size_t maxUnknownsTotal = 1;
        equation1.generateEquation(maxUnknownsPerSide, maxUnknownsTotal);
        std::cout << "Testing the generating of an equation with up to " << maxUnknownsPerSide << " unknowns per side and a total of " << maxUnknownsTotal << " unknowns --> "
            << equation1.getEquationTemplate() << " --> " << equation1.getEquation() << std::endl;
        std::cout << "Is the equation valid? Expect: TRUE ==> " << (equation1.isValidEquation() ? "TRUE" : "FALSE") << std::endl;
        std::cout << "Does the equation have up to " << maxUnknownsPerSide << " unknowns per side and a maximum of " << maxUnknownsTotal << " unknowns? Expect: TRUE: ";

        //Check how many unknowns the equation has on either side.
        size_t sizeOfSides = 0;
        char** sides = StringManip::splitString(equation1.getEquation(), "=", sizeOfSides);
        size_t unknownsInLeftSide = StringManip::countOf(sides[0], "x");
        size_t unknownsInRightSide = StringManip::countOf(sides[1], "x");
        if (unknownsInLeftSide > maxUnknownsPerSide || unknownsInRightSide > maxUnknownsPerSide || unknownsInLeftSide + unknownsInRightSide > maxUnknownsTotal) std::cout << "FALSE";
        else std::cout << "TRUE";

        //Delete dynamic memory
        StringManip::deleteArrayOfStrings(sides, sizeOfSides);

        std::cout << std::endl;
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

void BigNumberEquationTests::readFromAndWriteToConsoleTests()
{
    std::cout << "READ AND WRITE FROM AND TO CONSOLE TESTS" << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    BigNumberEquation equation1;
    BigNumberEquation equation2;
    std::cout << "Enter expression1: ";
    std::cin >> equation1;
    std::cout << "Enter expression2: ";
    std::cin >> equation2;
    //TODO: fix when I can solve an equation
    std::cout << "Equation 1: " << equation1.getEquation() << std::endl;
    std::cout << "Equation 2: " << equation2.getEquation();
    std::cout << std::endl << std::endl;
}

void BigNumberEquationTests::readFromAndWriteToFileTests()
{
    std::cout << "READ AND WRITE FROM AND TO FILE TESTS" << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;

    std::ifstream is("Equations.txt");
    int somethingDebug = (15 - (3 * 156 / 343 % (6 / 2 * 4 % 10 + 43))) + 10;
    BigNumberEquation equation1 = BigNumberExpression();
    BigNumberEquation equation2 = BigNumberExpression();
    is >> equation1;
    is >> equation2;

    is.close();

    //TODO: fix when I can solve an equation
    std::cout << "Equation 1: " << equation1.getEquation() << std::endl;
    std::cout << "Equation 2: " << equation2.getEquation();
    std::cout << std::endl << std::endl;
    //std::ofstream os("ExpressionsAnswers.txt");
    //
    //os << expression1;
    //os << expression2;
    //
    //os.close();
}

void BigNumberEquationTests::runTests()
{
    //Big4 tests
    //equationBig4Tests();

    //Equation is valid tests
    //equationIsValidTests();

    //Solve equations with no parenthesis Tests
    solveEquationWithoutParenthesisTests();

	//Generate equations from expression templates tests
	//generateFromTemplateTests();

	//Generate equation tests
	//generateEquationTests();

    //Read from and Write to console tests
    //readFromAndWriteToFileTests();
    
    //Read from and Write to console tests
    //readFromAndWriteToConsoleTests();
}
