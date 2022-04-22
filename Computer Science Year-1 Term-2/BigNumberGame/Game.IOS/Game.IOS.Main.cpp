// Game.IOS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ConsoleSystem.h"

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
    char** strings = ConsoleSystem::splitString(input, '|', numberOfStrings);
    testInputText(input);
    std::cout << "Lengths of strings are: Expected(10, 11) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testInputTwo()
{
    char input[] = "Roskata123|";
    size_t numberOfStrings = 0;
    char** strings = ConsoleSystem::splitString(input, '|', numberOfStrings);
    testInputText(input);
    std::cout << "Lengths of strings are: Expected(10, 0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testInputThree()
{
    char input[] = "Roskata123";
    size_t numberOfStrings = 0;
    char** strings = ConsoleSystem::splitString(input, '|', numberOfStrings);
    testInputText(input);
    std::cout << "Lengths of strings are: Expected(10) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testInputFour()
{
    char input[] = "Roskata123||Heyyy|G";
    size_t numberOfStrings = 0;
    char** strings = ConsoleSystem::splitString(input, '|', numberOfStrings);
    testInputText(input);
    std::cout << "Lengths of strings are: Expected(10, 0, 5, 1) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testInputFive()
{
    char input[] = "||";
    size_t numberOfStrings = 0;
    char** strings = ConsoleSystem::splitString(input, '|', numberOfStrings);
    testInputText(input);
    std::cout << "Lengths of strings are: Expected(0, 0, 0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testInputSix()
{
    char input[] = "|";
    size_t numberOfStrings = 0;
    char** strings = ConsoleSystem::splitString(input, '|', numberOfStrings);
    testInputText(input);
    std::cout << "Lengths of strings are: Expected(0, 0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testInputSeven()
{
    char input[] = "";
    size_t numberOfStrings = 0;
    char** strings = ConsoleSystem::splitString(input, '|', numberOfStrings);
    testInputText(input);
    std::cout << "Lengths of strings are: Expected(0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

int main()
{
    //Testing split string function
    testInputOne();
    testInputTwo();
    testInputThree();
    testInputFour();
    testInputFive();
    testInputSix();
    testInputSeven();
}
