﻿// Project.StringManipulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "StringManip.h"

//TODO: move the tests to a seperate class

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

//Test the splitString function with one char as delim
void testSplitByCharInputText(char input[])
{
    std::cout << "Testing input -> \"" << input << "\"" << std::endl;
}

void testSplitByCharInputOne()
{
    char input[] = "Roskata123|Tupa_rabota";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, '|', numberOfStrings);
    testSplitByCharInputText(input);
    std::cout << "Lengths of strings are: Expected(10, 11) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
}

void testSplitByCharInputTwo()
{
    char input[] = "Roskata123|";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, '|', numberOfStrings);
    testSplitByCharInputText(input);
    std::cout << "Lengths of strings are: Expected(10, 0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
}

void testSplitByCharInputThree()
{
    char input[] = "Roskata123";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, '|', numberOfStrings);
    testSplitByCharInputText(input);
    std::cout << "Lengths of strings are: Expected(10) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
}

void testSplitByCharInputFour()
{
    char input[] = "Roskata123||Heyyy|G";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, '|', numberOfStrings);
    testSplitByCharInputText(input);
    std::cout << "Lengths of strings are: Expected(10, 0, 5, 1) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
}

void testSplitByCharInputFive()
{
    char input[] = "||";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, '|', numberOfStrings);
    testSplitByCharInputText(input);
    std::cout << "Lengths of strings are: Expected(0, 0, 0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
}

void testSplitByCharInputSix()
{
    char input[] = "|";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, '|', numberOfStrings);
    testSplitByCharInputText(input);
    std::cout << "Lengths of strings are: Expected(0, 0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
}

void testSplitByCharInputSeven()
{
    char input[] = "";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, '|', numberOfStrings);
    testSplitByCharInputText(input);
    std::cout << "Lengths of strings are: Expected(0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
}

void testSplitByStringInputText(char input[], char delim[])
{
    std::cout << "Testing input -> \"" << input << "\" split by \"" << delim << "\"" << std::endl;
}

//Test the splitString function with string as delim
void testSplitByStringInputOne()
{
    char input[] = "Roskata123|||Tupa_rabota";
    char delim[] = "|||";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, delim, numberOfStrings);
    testSplitByStringInputText(input, delim);
    std::cout << "Lengths of strings are: Expected(10, 11) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testSplitByStringInputTwo()
{
    char input[] = "Roskata123aka";
    char delim[] = "aka";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, delim, numberOfStrings);
    testSplitByStringInputText(input, delim);
    std::cout << "Lengths of strings are: Expected(10, 0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testSplitByStringInputThree()
{
    char input[] = "aaab";
    char delim[] = "aab";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, delim, numberOfStrings);
    testSplitByStringInputText(input, delim);
    std::cout << "Lengths of strings are: Expected(1, 0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testSplitByStringInputFour()
{
    char input[] = "aaaabka";
    char delim[] = "aa";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, delim, numberOfStrings);
    testSplitByStringInputText(input, delim);
    std::cout << "Lengths of strings are: Expected(0, 0, 3) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testSplitByStringInputFive()
{
    char input[] = "10+-25-+65+54-33+-29";
    char delim[] = "+-";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, delim, numberOfStrings);
    testSplitByStringInputText(input, delim);
    std::cout << "Lengths of strings are: Expected(2, 12, 2) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testSplitByStringInputSix()
{
    char input[] = "+-";
    char delim[] = "+-";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, delim, numberOfStrings);
    testSplitByStringInputText(input, delim);
    std::cout << "Lengths of strings are: Expected(0, 0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testSplitByStringInputSeven()
{
    char input[] = "||";
    char delim[] = "|";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, delim, numberOfStrings);
    testSplitByStringInputText(input, delim);
    std::cout << "Lengths of strings are: Expected(0, 0, 0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testSplitByStringInputEight()
{
    char input[] = "_|+Some_|+Kind_|of_expression_|+";
    char delim[] = "_|+";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, delim, numberOfStrings);
    testSplitByStringInputText(input, delim);
    std::cout << "Lengths of strings are: Expected(0, 4, 19, 0) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

void testSplitByStringInputNine()
{
    char input[] = "_|Some_|+Kind_|of_expression_|";
    char delim[] = "_|+";
    size_t numberOfStrings = 0;
    char** strings = StringManip::splitString(input, delim, numberOfStrings);
    testSplitByStringInputText(input, delim);
    std::cout << "Lengths of strings are: Expected(6, 21) ==> ";
    printOutResultsFromTest(strings, numberOfStrings);
    std::cout << std::endl;
}

//Test the string contains function
void testContainsInputOne()
{
    char input[] = "roskata123";
    char otherInput[] = "rrrrosenroskata123";
    std::cout << "Testing if the string \"roskata123\" is contained within \"rrrrosenroskata123\": Expected(TRUE) ==> ";
    std::cout << (StringManip::stringContains(otherInput, input) ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;
}

void testContainsInputTwo()
{
    char input[] = "aab";
    char otherInput[] = "aaab";
    std::cout << "Testing if the string \""<< input << "\" is contained within \"" << otherInput << "\": Expected(TRUE) ==> ";
    std::cout << (StringManip::stringContains(otherInput, input) ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;
}

int main()
{
    //Testing split string function by one char
    ////std::cout << "TESTING SPLIT BY STRING FUNCTION: " << std::endl;
    //testSplitByCharInputOne();
    //testSplitByCharInputTwo();
    //testSplitByCharInputThree();
    //testSplitByCharInputFour();
    //testSplitByCharInputFive();
    //testSplitByCharInputSix();
    //testSplitByCharInputSeven();
    //
    ////Testing split string function by a string
    //std::cout << "TESTING SPLIT BY STRING FUNCTION: " << std::endl;
    //testSplitByStringInputOne();
    //testSplitByStringInputTwo();
    //testSplitByStringInputThree();
    //testSplitByStringInputFour();
    //testSplitByStringInputFive();
    //testSplitByStringInputSix();
    //testSplitByStringInputSeven();
    //testSplitByStringInputEight();
    //testSplitByStringInputNine();

    //Testing contains of string
    std::cout << "TESTING CONTAINS STRING FUNCTION: " << std::endl;
    testContainsInputOne();
    testContainsInputTwo();
}

