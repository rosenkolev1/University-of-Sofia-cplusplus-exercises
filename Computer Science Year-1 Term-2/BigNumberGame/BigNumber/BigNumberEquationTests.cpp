#include "BigNumberEquationTests.h"
#include "BigNumberEquation.h"
#include <iostream>
#include <fstream>
#include "..\Project.StringManipulation\StringManip.h"

void BigNumberEquationTests::equationBig4Tests(std::ostream& os)
{
    //BIG4 TESTS
    os << "EQUATION BIG4 TESTS" << std::endl << std::endl;

    //SETUP
    BigNumberEquation equation1 = BigNumberEquation();
    char someEquation[] = " 5 + 5*x = 30/x";
    char anotherEquation[] = "15/3*x = 20";
    BigNumberEquation equation2(someEquation);
    BigNumberEquation equation3(anotherEquation);

    os << "Equation 1: Expected: " << "x=0" << ": " << equation1.getEquation() << std::endl;
    os << "Equation 2: Expected: " << someEquation << ": " << equation2.getEquation() << std::endl;
    os << "Equation 3: Expected: " << anotherEquation << ": " << equation3.getEquation() << std::endl;

    os << std::endl;

    equation1 = equation2;
    os << "Testing \"equation1 = equation2;\" \n";
    os << "Equation 1: Expected: " << someEquation << ": " << equation1.getEquation() << std::endl;

    os << std::endl;

    equation2 = equation3;
    os << "Testing \"equation2 = equation3;\" \n";
    os << "Equation 2: Expected: " << anotherEquation << ": " << equation2.getEquation() << std::endl;

    os << std::endl;

    BigNumberEquation equation4(equation1);
    os << "Testing \"BigNumberEquation equation4(equation1);\" \n";
    os << "Equation 4: Expected: " << someEquation << ": " << equation4.getEquation() << std::endl;

    os << std::endl;
    
}

void BigNumberEquationTests::equationIsValidTests(std::ostream& os)
{
    //EQUATION IS VALID TESTS
    os << "EQUATION IS VALID TESTS" << std::endl << std::endl;

    //TEST 1
    os << "TEST 1" << std::endl;
    char equation1[] = "-(35/x*(40+-36/-x*(9-x) + 38)-16)*(x*5/-(x+34)+15)= + x*x/(x*x-x+x*(--10)-x-x*(x-1+x)*x)*(10-x)";
    BigNumberEquation equation(equation1);
    os << "Testing if the equation | " << equation1 << " | is valid: Expected: TRUE ==> " << (equation.isValidEquation() ? "TRUE" : "FALSE");
    os << std::endl << std::endl;

    //TEST 2
    os << "TEST 2" << std::endl;
    char equation2[] = "-+(35/x*(40+-36/-x*(9-x) + 38)-16)*(x*5/-(x+34)+15)= + x*x/(x*x-x+x*(--10)-x-x*(x-1+x)*x)*(10-x)";
    os << "Testing if the equation | " << equation2 << " | is valid: Expected: TRUE ==> " << (equation.isValidEquation(equation2) ? "TRUE" : "FALSE");
    os << std::endl << std::endl;

    //TEST 3
    os << "TEST 3" << std::endl;
    char equation3[] = "--(35/x*(40+-36/-x*(9-x) + 38)-16)*(x*5/-(x+34)+15)= --x*x/(x*x-x+x*(--10)-x-x*(x-1+x)*x)*(10-x)";
    os << "Testing if the equation | " << equation3 << " | is valid: Expected: FALSE ==> " << (equation.isValidEquation(equation3) ? "TRUE" : "FALSE");
    os << std::endl << std::endl;

    //TEST 4
    os << "TEST 4" << std::endl;
    char equation4[] = "--(35/x*(40+-36/-x*(9-x) + 38)-16)*(x*5/-(x+34)+15)-x*x/(x*x-x+x*(--10)-x-x*(x-1+x)*x)*(10-x)";
    os << "Testing if the equation | " << equation4 << " | is valid: Expected: FALSE ==> " << (equation.isValidEquation(equation4) ? "TRUE" : "FALSE");
    os << std::endl << std::endl;

    //TEST 5
    os << "TEST 5" << std::endl;
    char equation5[] = "--(35/x*(40+-36/-x*(9-x) + 38)-16)*(x*5/-(x+34)=+15)-x*x/(x*x-x+x*(--10)-x-x*(x-1+x)*x)*(10-x)";
    os << "Testing if the equation | " << equation5 << " | is valid: Expected: FALSE ==> " << (equation.isValidEquation(equation5) ? "TRUE" : "FALSE");
    os << std::endl << std::endl;

    //TEST 6
    os << "TEST 6" << std::endl;
    char equation6[] = "--(35/x*(40+-36/-x%(9-x) + 38)-16)*(x*5/-(x+34)+15)=-x*x/(x*x-x+x*(--10)-x-x*(x-1+x)*x)*(10-x)";
    os << "Testing if the equation | " << equation6 << " | is valid: Expected: FALSE ==> " << (equation.isValidEquation(equation6) ? "TRUE" : "FALSE");
    os << std::endl << std::endl;

    //TEST 7
    os << "TEST 7" << std::endl;
    char equation7[] = "(35/5*(40+-36/-5*(9-5) + 38)-16)*(5*5/-(5+34)+15)=-5*5/(5*5-5+5*(--10)-5-5*(5-1+5)*5)*(10-5)"; //Expected: 10890 = 0
    os << "Testing if the equation | " << equation7 << " | is valid: Expected: FALSE ==> " << (equation.isValidEquation(equation7) ? "TRUE" : "FALSE");
    os << std::endl << std::endl;

    //TEST 8
    os << "TEST 8" << std::endl;
    int something = (35 / 5 * (40 + -36 / -5 * (9 - 5) + 38) - 16) * (5 * 5 / -(5 + 34) + 15);
    BigNumberExpression somethingExpression("(35/5*(40+-36/-5*(9-5) + 38)-16)*(5*5/-(5+34)+15)");
    BigNumber result = somethingExpression.evaluateExpression();
    char equation8[] = "(35/5*(40+-36/-5*(9-5) + 38)-16)*(5*5/-(5+34)+15)=-5*5/(5*5-5+5*(--10)-5-5*(5-1+5)*5)*(10-5) + 10890"; //Expected: 10890 = 10890
    os << "Testing if the equation | " << equation8 << " | is valid: Expected: TRUE ==> " << (equation.isValidEquation(equation8) ? "TRUE" : "FALSE");
    os << std::endl << std::endl;
}

void BigNumberEquationTests::solveEquationTests(std::ostream& os)
{
    //SOLVE EQUATIONS TESTS
    os << "SOLVE EQUATIONS TESTS" << std::endl << std::endl;

    //TEST PREP
    BigNumberEquation equation;

    //TEST 1
    os << "TEST 1" << std::endl;
    char equation1[] = "x=5";
    os << "Testing the answer to the equation | " << equation1 << " |: Expected: 5 ==> " << equation.solveEquation(equation1);
    os << std::endl << std::endl;
    
    //TEST 2
    os << "TEST 2" << std::endl;
    char equation2[] = "3+x=5";
    os << "Testing the answer to the equation | " << equation2 << " |: Expected: 2 ==> " << equation.solveEquation(equation2);
    os << std::endl << std::endl;
    
    //TEST 3
    os << "TEST 3" << std::endl;
    char equation3[] = "5-3+x=5";
    os << "Testing the answer to the equation | " << equation3 << " |: Expected: 3 ==> " << equation.solveEquation(equation3);
    os << std::endl << std::endl;
    
    //TEST 4
    os << "TEST 4" << std::endl;
    char equation4[] = "5-3-x=5";
    os << "Testing the answer to the equation | " << equation4 << " |: Expected: -3 ==> " << equation.solveEquation(equation4);
    os << std::endl << std::endl;
    
    //TEST 5
    os << "TEST 5" << std::endl;
    char equation5[] = "--5+-3-x=5";
    os << "Testing the answer to the equation | " << equation5 << " |: Expected: -3 ==> " << equation.solveEquation(equation5);
    os << std::endl << std::endl;
    
    //TEST 6
    os << "TEST 6" << std::endl;
    char equation6[] = "-x+9=5";
    os << "Testing the answer to the equation | " << equation6 << " |: Expected: 4 ==> " << equation.solveEquation(equation6);
    os << std::endl << std::endl;
    
    //TEST 7
    os << "TEST 7" << std::endl;
    char equation7[] = "-x-+9=5";
    os << "Testing the answer to the equation | " << equation7 << " |: Expected: -14 ==> " << equation.solveEquation(equation7);
    os << std::endl << std::endl;
    
    //TEST 8
    os << "TEST 8" << std::endl;
    char equation8[] = "-x--9=5";
    os << "Testing the answer to the equation | " << equation8 << " |: Expected: 4 ==> " << equation.solveEquation(equation8);
    os << std::endl << std::endl;
    
    //TEST 9
    os << "TEST 9" << std::endl;
    char equation9[] = "-x--9+-10-+14=5*3/4+10*(5/3+1)-13"; //-x+9-24=3+10*2-13 ==> -x-15=10 ==> x=-25 
    os << "Testing the answer to the equation | " << equation9 << " |: Expected: -25 ==> " << equation.solveEquation(equation9);
    os << std::endl << std::endl;
    
    //TEST 10
    os << "TEST 10" << std::endl;
    int correctAnswer = (5 * 3 / 4 + 10 * (5 / 3 + 1) - 13 - (50 + 74 + -69 - +69 + 22)) - (9 + -10 - +14);
    char equation10[] = "50+74+-69-+69--22-x--9+-10-+14=5*3/4+10*(5/3+1)-13"; //-x-2-15 ==> x=-17
    os << "Testing the answer to the equation | " << equation10 << " |: Expected: -17 ==> " << equation.solveEquation(equation10);
    os << std::endl << std::endl;
    
    //TEST 11
    os << "TEST 11" << std::endl;
    correctAnswer = ((5 * 3 / 4 + 10 * (5 / 3 + 1) - 13) - (+-50 + 74 + -69 - +69 + 21)) - (+9 + -10 - +14);
    char equation11[] = "+-50+74+-69-+69--21-x--9+-10-+14=5*3/4+10*(5/3+1)-13"; //-x-30-100=10 ==> x=-140
    os << "Testing the answer to the equation | " << equation11 << " |: Expected: -118 ==> " << equation.solveEquation(equation11);
    os << std::endl << std::endl;
    
    //TEST 12
    os << "TEST 12" << std::endl;
    char equation12[] = "5*3/4+10*(5/3+1)-13=+-50+74+-69-+69--21-x--9+-10-+14"; //x=83
    os << "Testing the answer to the equation | " << equation12 << " |: Expected: -118 ==> " << equation.solveEquation(equation12);
    os << std::endl << std::endl;
    
    //TEST 13
    os << "TEST 13" << std::endl;
    char equation13[] = "x*5=25"; 
    os << "Testing the answer to the equation | " << equation13 << " |: Expected: 5 ==> " << equation.solveEquation(equation13);
    os << std::endl << std::endl;
    
    //TEST 14
    os << "TEST 14" << std::endl;
    char equation14[] = "-x*5=25";
    os << "Testing the answer to the equation | " << equation14 << " |: Expected: -5 ==> " << equation.solveEquation(equation14);
    os << std::endl << std::endl;    
    
    //TEST 15
    os << "TEST 15" << std::endl;
    char equation15[] = "-x*-5=25";
    os << "Testing the answer to the equation | " << equation15 << " |: Expected: 5 ==> " << equation.solveEquation(equation15);
    os << std::endl << std::endl;
    
    //TEST 16
    os << "TEST 16" << std::endl;
    char equation16[] = "5*x=25";
    os << "Testing the answer to the equation | " << equation16 << " |: Expected: 5 ==> " << equation.solveEquation(equation16);
    os << std::endl << std::endl;
    
    //TEST 17
    os << "TEST 17" << std::endl;
    char equation17[] = "5*-x=25";
    os << "Testing the answer to the equation | " << equation17 << " |: Expected: -5 ==> " << equation.solveEquation(equation17);
    os << std::endl << std::endl;
    
    //TEST 18
    os << "TEST 18" << std::endl;
    char equation18[] = "-5*-x=25";
    os << "Testing the answer to the equation | " << equation18 << " |: Expected: 5 ==> " << equation.solveEquation(equation18);
    os << std::endl << std::endl;
    
    //TEST 19
    os << "TEST 19" << std::endl;
    char equation19[] = "13*6*x=25*(7/2+3--5) + 37"; // x = 312/78 = 4
    os << "Testing the answer to the equation | " << equation19 << " |: Expected: 4 ==> " << equation.solveEquation(equation19);
    os << std::endl << std::endl;
    
    //TEST 20
    os << "TEST 20" << std::endl;
    int shouldBe0 = 13 * 6 * (-32 + 10 - 43 / (6 * (3 - 5)) + 20) + 500 / (35 - 47 * 5) * 3 - 19 + 4 * (13) - ((15 + (25 * (7 / 2 + 3 + 5)) / 6) + 45);
    char equation20[] = "13*6*(x+10-43/(6*(3-5))+20) + 500/(35-47*5)*3-19+4*(13) = (15+(25*(7/2+3--5))/6) + 45";  
    //13*6*(x+10+3+20) -6 -19+4*(13) = (15+45) + 45
    //78*(x+33)-25+52=105;
    //78*(x+33)=78;
    //(x+33)=1;
    //x=-32;
    os << "Testing the answer to the equation | " << equation20 << " |: Expected: -32 ==> " << equation.solveEquation(equation20);
    os << std::endl << std::endl;
    
    //TEST 21
    os << "TEST 21" << std::endl;
    char equation21[] = "15/(20-5*3)*x = (15+(25*(7/2+3+5))/6) + 45";
    //15/(5)*x = 105
    //3*x=105;
    //x=35;
    os << "Testing the answer to the equation | " << equation21 << " |: Expected: 35 ==> " << equation.solveEquation(equation21);
    os << std::endl << std::endl;
    
    //TEST 22
    os << "TEST 22" << std::endl;
    char equation22[] = "17/(20-5*3)*x = (15+(25*(7/2+3+5))/6) + 45";
    //17/(5)*x = 105
    //3*x=105;
    //x=35;
    os << "Testing the answer to the equation | " << equation22 << " |: Expected: 35 ==> " << equation.solveEquation(equation22);
    os << std::endl << std::endl;

    //TEST 23
    os << "TEST 23" << std::endl;
    char equation23[] = "(23*18-457)*35-(17/(20-5*3))*x*345/(15+24-3*7) = (15+(25*(7/2+3+5))/6) + 88";
    os << "Testing the answer to the equation | " << equation23 << " |:" << std::endl 
        << "Expected: " << BigNumberEquation::EQUATION__SOLVE_TIEDTODIVISION_EXCEPTION << " ==> ";
    try
    {
        os << equation.solveEquation(equation23);
    }
    catch(const char* e)
    {
        os << e;
    }
    os << std::endl << std::endl;  

    //TEST 24
    os << "TEST 24" << std::endl;
    char equation24[] = "(23*18-457)*35-(17/(20-5*3))/x*345*(15+24-3*7) = (15+(25*(7/2+3+5))/6) + 88";
    os << "Testing the answer to the equation | " << equation24 << " |:" << std::endl 
        << "Expected: " << BigNumberEquation::EQUATION__SOLVE_TIEDTODIVISION_EXCEPTION << " ==> ";
    try
    {
        os << equation.solveEquation(equation24);
    }
    catch (const char* e)
    {
        os << e;
    }
    os << std::endl << std::endl;

    //TEST 25
    os << "TEST 25" << std::endl;
    char equation25[] = "(23*18-457)*35-172222/(17/(20-5*3))*x*345*(15+24/3*7*(45/8))/(15+10) = (15+(25*(7/2+3+5))/6) + 88";
    os << "Testing the answer to the equation | " << equation25 << " |:" << std::endl 
        << "Expected: " << BigNumberEquation::EQUATION__SOLVE_TIEDTODIVISION_EXCEPTION << " ==> ";
    try
    {
        os << equation.solveEquation(equation25);
    }
    catch (const char* e)
    {
        os << e;
    }
    os << std::endl << std::endl;

    //TEST 26
    os << "TEST 26" << std::endl;
    char equation26[] = "(23*18-457)*35-172222/(17/(20-5*3))/-x*345*(15+24/3*7*(45/8)) = (15+(25*(7/2+3+5))/6) + 88";
    os << "Testing the answer to the equation | " << equation26 << " |:" << std::endl 
        << "Expected: " << BigNumberEquation::EQUATION__SOLVE_TIEDTODIVISION_EXCEPTION << " ==> ";
    try
    {
        os << equation.solveEquation(equation26);
    }
    catch (const char* e)
    {
        os << e;
    }
    os << std::endl << std::endl;

    //TEST 27
    os << "TEST 27" << std::endl;
    char equation27[] = "(23*18-457)*35-172222/(17/(20-5*3))/+x*345*(15+24/3*7*(45/8)) = (15+(25*(7/2+3+5))/6) + 88";
    os << "Testing the answer to the equation | " << equation27 << " |:" << std::endl 
        << "Expected: " << BigNumberEquation::EQUATION__SOLVE_TIEDTODIVISION_EXCEPTION << " ==> ";
    try
    {
        os << equation.solveEquation(equation27);
    }
    catch (const char* e)
    {
        os << e;
    }
    os << std::endl << std::endl;

    //TEST 28
    os << "TEST 28" << std::endl;
    char equation28[] = "(23*18-457)*35-172222/(17/(20-5*3))*x*345*(15+24/3*7*(45/8)) = (15+(25*(7/2+3+5))/6) + 88";
    os << "Testing the answer to the equation | " << equation28 << " |:" << std::endl 
        << "Expected: " << BigNumberEquation::EQUATION__SOLVE_NOTWHOLE_EXCEPTION << " ==> ";
    try
    {
        os << equation.solveEquation(equation28);
    }
    catch (const char* e)
    {
        os << e;
    }
    os << std::endl << std::endl;

    //TEST 29
    os << "TEST 29" << std::endl;
    char equation29[] = "(23*18-457)*35-172222/(17/(20-5*3))*x*345*(15+24/3*7*(45/8)) = (15+(25*(7/2+3+5))/6) + 88*x";
    os << "Testing the answer to the equation | " << equation29 << " |:" << std::endl 
        << "Expected: " << BigNumberEquation::EQUATION__SOLVE_TOOCOMPLEX_EXCEPTION << " ==> ";
    try
    {
        os << equation.solveEquation(equation29);
    }
    catch (const char* e)
    {
        os << e;
    }
    os << std::endl << std::endl;

    //TEST 30
    os << "TEST 30" << std::endl;
    char equation30[] = "x*0 + 10 = 10";
    os << "Testing the answer to the equation | " << equation30 << " |:" << std::endl 
        << "Expected: " << BigNumberEquation::EQUATION__SOLVE_EVERYANSWER_EXCEPTION << " ==> ";
    try
    {
        os << equation.solveEquation(equation30);
    }
    catch (const char* e)
    {
        os << e;
    }
    os << std::endl << std::endl;

    //TEST 31
    os << "TEST 31" << std::endl;
    char equation31[] = "x*0 = 10";
    os << "Testing the answer to the equation | " << equation31 << " |:" << std::endl 
        << "Expected: " << BigNumberEquation::EQUATION__SOLVE_NOANSWER_EXCEPTION << " ==> ";
    try
    {
        os << equation.solveEquation(equation31);
    }
    catch (const char* e)
    {
        os << e;
    }
    os << std::endl << std::endl;

    //TEST 32
    os << "TEST 32" << std::endl;
    char equation32[] = "x*(25/0) = 10";
    os << "Testing the answer to the equation | " << equation32 << " |:" << std::endl 
        << "Expected: " << BigNumberExpression::EXPRESSION_DIVIDEBYZERO_EXCEPTION << " ==> ";
    try
    {
        os << equation.solveEquation(equation32);
    }
    catch (const char* e)
    {
        os << e;
    }
    os << std::endl << std::endl;
}

void BigNumberEquationTests::generateEquationTests(std::ostream& os)
{
    os << "GENERATE EQUATIONS TESTS" << std::endl << std::endl;
    srand(time(NULL));
    for (size_t i = 0; i < 50; i++)
    {
        os << "TEST " << i + 1 << ": " << std::endl;
        BigNumberEquation equation1 = BigNumberEquation();
        size_t maxUnknownsPerSide = 3;
        size_t maxUnknownsTotal = 6;
        equation1.generateEquation(maxUnknownsPerSide, maxUnknownsTotal);
        os << "Testing the generating of an equation with up to " << maxUnknownsPerSide << " unknowns per side and a total of " << maxUnknownsTotal << " unknowns --> "
            << equation1.getEquationTemplate() << " --> " << equation1.getEquation() << std::endl;
        os << "Is the equation valid? Expect: TRUE ==> " << (equation1.isValidEquation() ? "TRUE" : "FALSE") << std::endl;
        os << "Does the equation have up to " << maxUnknownsPerSide << " unknowns per side and a maximum of " << maxUnknownsTotal << " unknowns? Expect: TRUE: ";

        //Check how many unknowns the equation has on either side.
        size_t sizeOfSides = 0;
        char** sides = StringManip::splitString(equation1.getEquation(), "=", sizeOfSides);
        size_t unknownsInLeftSide = StringManip::countOf(sides[0], "x");
        size_t unknownsInRightSide = StringManip::countOf(sides[1], "x");
        if (unknownsInLeftSide > maxUnknownsPerSide || unknownsInRightSide > maxUnknownsPerSide || unknownsInLeftSide + unknownsInRightSide > maxUnknownsTotal) os << "FALSE";
        else os << "TRUE";

        //Delete dynamic memory
        StringManip::deleteArrayOfStrings(sides, sizeOfSides);

        os << std::endl;
        os << "Answer to the equation --> ";
        try
        {
            os << equation1.solveEquation();
        }
        catch (const char* e)
        {
            os << e;
        }
        os << std::endl;
        os << std::endl;
    }

    for (size_t i = 50; i < 99; i++)
    {
        os << "TEST " << i + 1 << ": " << std::endl;
        BigNumberEquation equation1 = BigNumberEquation();
        size_t maxUnknownsPerSide = 1;
        size_t maxUnknownsTotal = 1;
        equation1.generateEquation(maxUnknownsPerSide, maxUnknownsTotal);
        os << "Testing the generating of an equation with up to " << maxUnknownsPerSide << " unknowns per side and a total of " << maxUnknownsTotal << " unknowns --> "
            << equation1.getEquationTemplate() << " --> " << equation1.getEquation() << std::endl;
        os << "Is the equation valid? Expect: TRUE ==> " << (equation1.isValidEquation() ? "TRUE" : "FALSE") << std::endl;
        os << "Does the equation have up to " << maxUnknownsPerSide << " unknowns per side and a maximum of " << maxUnknownsTotal << " unknowns? Expect: TRUE: ";

        //Check how many unknowns the equation has on either side.
        size_t sizeOfSides = 0;
        char** sides = StringManip::splitString(equation1.getEquation(), "=", sizeOfSides);
        size_t unknownsInLeftSide = StringManip::countOf(sides[0], "x");
        size_t unknownsInRightSide = StringManip::countOf(sides[1], "x");
        if (unknownsInLeftSide > maxUnknownsPerSide || unknownsInRightSide > maxUnknownsPerSide || unknownsInLeftSide + unknownsInRightSide > maxUnknownsTotal) os << "FALSE";
        else os << "TRUE";

        //Delete dynamic memory
        StringManip::deleteArrayOfStrings(sides, sizeOfSides);

        os << std::endl;
        os << "Answer to the equation --> ";
        try
        {
            os << equation1.solveEquation();
        }
        catch (const char* e)
        {
            os << e;
        }
        os << std::endl;
        os << std::endl;
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

void BigNumberEquationTests::runTests(std::ostream& os)
{
    std::cout << "Start the test!";
    if (&os != &std::cout)
    {
        std::cout << "The test results are being outputted to text file with name: " << OUTPUTFILE_NAME;
    }

    //Big4 tests
    equationBig4Tests(os);

    //Equation is valid tests
    equationIsValidTests(os);

    //SOLVE EQUATIONS TESTS
    solveEquationTests(os);

	//Generate equation tests
	generateEquationTests(os);

    //Read from and Write to console tests
    //readFromAndWriteToFileTests();
    
    //Read from and Write to console tests
    //readFromAndWriteToConsoleTests();

}
