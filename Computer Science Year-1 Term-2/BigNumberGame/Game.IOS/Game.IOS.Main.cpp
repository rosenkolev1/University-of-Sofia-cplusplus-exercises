// Game.IOS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "..\Project.StringManipulation\StringManip.h"
#include "FileSystem.h"

void printOutResultsFromTest(char** strings, size_t numberOfStrings)
{
    for (size_t i = 0; i < numberOfStrings; i++)
    {
        std::cout << strlen(strings[i]) << (i != numberOfStrings - 1 ? ", " : "");
    }
    std::cout << std::endl;
    std::cout << "Strings are: ";
    for (size_t i = 0; i < numberOfStrings; i++)
    {
        std::cout << strings[i] << (i != numberOfStrings - 1 ? ", " : "");
    }
    std::cout << std::endl;
}

void testInputText(char input[])
{
    std::cout << "Testing input -> \"" << input << "\"" << std::endl;
}

void testInputOne()
{
    char input[] = "Roskata123|Tupa_rabota";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, '|', numberOfStrings);
    testInputText(input);
    std::cout << "Lengths of strings are: Expected(10, 11) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testInputTwo()
{
    char input[] = "Roskata123|";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, '|', numberOfStrings);
    testInputText(input);
    std::cout << "Lengths of strings are: Expected(10, 0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testInputThree()
{
    char input[] = "Roskata123";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, '|', numberOfStrings);
    testInputText(input);
    std::cout << "Lengths of strings are: Expected(10) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testInputFour()
{
    char input[] = "Roskata123||Heyyy|G";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, '|', numberOfStrings);
    testInputText(input);
    std::cout << "Lengths of strings are: Expected(10, 0, 5, 1) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testInputFive()
{
    char input[] = "||";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, '|', numberOfStrings);
    testInputText(input);
    std::cout << "Lengths of strings are: Expected(0, 0, 0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testInputSix()
{
    char input[] = "|";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, '|', numberOfStrings);
    testInputText(input);
    std::cout << "Lengths of strings are: Expected(0, 0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testInputSeven()
{
    char input[] = "";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, '|', numberOfStrings);
    testInputText(input);
    std::cout << "Lengths of strings are: Expected(0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testUserInputOne()
{
    char input[] = "Testing User Assignment and Copy constructor --> User b = allUsers[0]; User a(b)";
    User* allUsers = FileSystem::getAllUsers();
    User b = allUsers[0];
    User a = User(b);
    std::cout << input << std::endl;
    std::cout << "Expected: Users are copies with the same members. ==> ";
    std::cout << std::endl << "Level is same: " << (allUsers[0].level == b.level && b.level == a.level ? "True" : "False");
    std::cout << std::endl << "Username is same: " << ( strcmp(allUsers[0].username, b.username) == 0 && strcmp(b.username, a.username) == 0 ? "True" : "False");
    std::cout << std::endl << "Password is same: " << (strcmp(allUsers[0].password, b.password) == 0 && strcmp(b.password, a.password) == 0 ? "True" : "False");
    std::cout << std::endl << "Last Expression is same: " << (strcmp(allUsers[0].lastExpression, b.lastExpression) == 0 && strcmp(b.lastExpression, a.lastExpression) == 0 ? "True" : "False");
    std::cout << std::endl << "Username pointers are different: " << (allUsers[0].username != b.username && b.username != a.username && allUsers[0].username != a.username ? "True" : "False");
    std::cout << std::endl << "Password pointers are different: " << (allUsers[0].password != b.password && b.password != a.password && allUsers[0].password != a.password? "True" : "False");
    std::cout << std::endl << "Last Expression pointers are different: " << (allUsers[0].lastExpression != b.lastExpression && b.lastExpression != a.lastExpression && allUsers[0].lastExpression != a.lastExpression ? "True" : "False");
    std::cout << std::endl;
}

//Test the string contains function
void testContainsInputSeven()
{
    char input[] = "roskata123";
    char otherInput[] = "rrrrosenroskata123";
    std::cout << "Testing if the string \"roskata123\" is contained within \"rrrrosenroskata123\": Expected(TRUE) ==> ";
    std::cout << (StringManip::stringContains(otherInput, input) ? "TRUE" : "FALSE");
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
