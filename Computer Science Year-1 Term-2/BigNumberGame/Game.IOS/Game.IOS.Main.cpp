// Game.IOS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "..\Project.StringManipulation\MStringManip.h"
#include "FileSystem.h"

void printOutResultsFromTest(mstring* strings, size_t numberOfStrings)
{
    for (size_t i = 0; i < numberOfStrings; i++)
    {
        std::cout << strings[i].getSize() << (i != numberOfStrings - 1 ? ", " : "");
    }
    std::cout << std::endl;
    std::cout << "Strings are: ";
    for (size_t i = 0; i < numberOfStrings; i++)
    {
        std::cout << strings[i] << (i != numberOfStrings - 1 ? ", " : "");
    }
    std::cout << std::endl;
}

void testInputText(mstring input)
{
    std::cout << "Testing input -> \"" << input << "\"" << std::endl;
}

void testInputOne()
{
    mstring input = "Roskata123|Tupa_rabota";
    size_t numberOfStrings = 0;
    mstring* strings = MStringManip::splitString(input, '|', numberOfStrings);

    testInputText(input);
    std::cout << "Lengths of strings are: Expected(10, 11) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);

    //Deallocate dynamic memory
    delete[] strings;

    std::cout << std::endl;
}

void testInputTwo()
{
    mstring input = "Roskata123|";
    size_t numberOfStrings = 0;
    mstring* strings = MStringManip::splitString(input, '|', numberOfStrings);

    testInputText(input);
    std::cout << "Lengths of strings are: Expected(10, 0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);

    //Deallocate dynamic memory
    delete[] strings;

    std::cout << std::endl;
}

void testInputThree()
{
    mstring input = "Roskata123";
    size_t numberOfStrings = 0;
    mstring* strings = MStringManip::splitString(input, '|', numberOfStrings);

    testInputText(input);
    std::cout << "Lengths of strings are: Expected(10) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);

    //Deallocate dynamic memory
    delete[] strings;

    std::cout << std::endl;
}

void testInputFour()
{
    mstring input = "Roskata123||Heyyy|G";
    size_t numberOfStrings = 0;
    mstring* strings = MStringManip::splitString(input, '|', numberOfStrings);

    testInputText(input);
    std::cout << "Lengths of strings are: Expected(10, 0, 5, 1) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);

    //Deallocate dynamic memory
    delete[] strings;

    std::cout << std::endl;
}

void testInputFive()
{
    mstring input = "||";
    size_t numberOfStrings = 0;
    mstring* strings = MStringManip::splitString(input, '|', numberOfStrings);

    testInputText(input);
    std::cout << "Lengths of strings are: Expected(0, 0, 0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);

    //Deallocate dynamic memory
    delete[] strings;

    std::cout << std::endl;
}

void testInputSix()
{
    mstring input = "|";
    size_t numberOfStrings = 0;
    mstring* strings = MStringManip::splitString(input, '|', numberOfStrings);

    testInputText(input);
    std::cout << "Lengths of strings are: Expected(0, 0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);

    //Deallocate dynamic memory
    delete[] strings;

    std::cout << std::endl;
}

void testInputSeven()
{
    mstring input = "";
    size_t numberOfStrings = 0;
    mstring* strings = MStringManip::splitString(input, '|', numberOfStrings);

    testInputText(input);
    std::cout << "Lengths of strings are: Expected(0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);

    //Deallocate dynamic memory
    delete[] strings;

    std::cout << std::endl;
}

void testUserInputOne()
{
    mstring input = "Testing User Assignment and Copy constructor --> User b = allUsers[0]; User a(b)";
    size_t allUsersCount = 0;
    User* allUsers = FileSystem::getAllUsers(allUsersCount);
    User b = allUsers[0];
    User a = User(b);
    std::cout << input << std::endl;
    std::cout << "Expected: Users are copies with the same members. ==> ";
    std::cout << std::endl << "Level is same: " << (allUsers[0].level == b.level && b.level == a.level ? "True" : "False");
    std::cout << std::endl << "Username is same: " << ( allUsers[0].username == b.username && b.username == a.username ? "True" : "False");
    std::cout << std::endl << "Password is same: " << (allUsers[0].password == b.password && b.password == a.password ? "True" : "False");
    std::cout << std::endl << "Last Expression is same: " << (allUsers[0].lastExpression == b.lastExpression && b.lastExpression == a.lastExpression ? "True" : "False");
    
    //Deallocate dynamic memory
    delete[] allUsers;
    
    std::cout << std::endl;
}

//Test the string contains function
void testContainsInputSeven()
{
    mstring input = "roskata123";
    char otherInput[] = "rrrrosenroskata123";
    std::cout << "Testing if the string \"roskata123\" is contained within \"rrrrosenroskata123\": Expected(TRUE) ==> ";
    std::cout << (MStringManip::stringContains(otherInput, input) ? "TRUE" : "FALSE");
    std::cout << std::endl;
}

int main()
{
    //Testing split string function
    //testInputOne();
    //testInputTwo();
    //testInputThree();
    //testInputFour();
    //testInputFive();
    //testInputSix();
    //testInputSeven();

    //Testing User functionality
    //testUserInputOne();

    //Testing contains of string
    //testContainsInputSeven();
}
