// Project.StringManipulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

void testReplaceAllInputText(char input[], char* replaced, char* replacement)
{
    std::cout << "Testing input -> \"" << input << "\" where \"" << replaced << "\"" << " is replaced by \"" << replacement <<"\"" << std::endl;
}

//Test the replaceAll function
void testReplaceAllInputOne()
{
    char input[] = "15+-13-+14-16+-132+54";
    char replaced[] = "+-";
    char replacement[] = "REPLACED";
    size_t numberOfStrings = 0;
    testReplaceAllInputText(input, replaced, replacement);
    char* output = StringManip::replaceAll(input, replaced, replacement);
    char expectedOutput[] = "15REPLACED13-+14-16REPLACED132+54";
    std::cout << "String is: Expected(" << expectedOutput << ") ==> " << output << (strcmp(output, expectedOutput) == 0 ? " --> TRUE" : " --> FALSE");

    std::cout << std::endl;
    std::cout << std::endl;

    //Delete dynamic memory
    delete[] output;
}

void testReplaceAllInputTwo()
{
    char input[] = "15+-13-+14-16+-132+54_15151351";
    char replaced[] = "15";
    char replacement[] = "";
    size_t numberOfStrings = 0;
    testReplaceAllInputText(input, replaced, replacement);
    char* output = StringManip::replaceAll(input, replaced, replacement);
    char expectedOutput[] = "+-13-+14-16+-132+54_1351";
    std::cout << "String is: Expected(" << expectedOutput << ") ==> " << output << (strcmp(output, expectedOutput) == 0 ? " --> TRUE" : " --> FALSE");

    std::cout << std::endl;
    std::cout << std::endl;

    //Delete dynamic memory
    delete[] output;
}

//Test the findIndex function
void testFindIndexInputOne()
{
    char input[] = "roskata123";
    char otherInput[] = "rrrrosenroskata123";
    std::cout << "Testing if the string \""<< input <<"\" is contained within \""<< otherInput <<"\": Expected(8) ==> ";
    std::cout << StringManip::findIndex(otherInput, input);
    std::cout << std::endl;
    std::cout << std::endl;
}

void testFindIndexInputTwo()
{
    char input[] = "aab";
    char otherInput[] = "aaab";
    std::cout << "Testing if the string \"" << input << "\" is contained within \"" << otherInput << "\": Expected(1) ==> ";
    std::cout << StringManip::findIndex(otherInput, input);
    std::cout << std::endl;
    std::cout << std::endl;
}

void testFindIndexInputThree()
{
    char input[] = "aab";
    char otherInput[] = "asvbraaabppab";
    int startIndex = 3;//  |braaab|
    int endIndex = 8;
    std::cout << "Testing if the string \"" << input << "\" is contained within \"" << otherInput << "\" from "<< startIndex << " to " << endIndex << ": Expected(6) ==> ";
    std::cout << StringManip::findIndex(otherInput, input, startIndex, endIndex);
    std::cout << std::endl;
    std::cout << std::endl;
}

void testFindIndexInputFour()
{
    char input[] = "aab";
    char otherInput[] = "asvbraaabppab";
    int startIndex = 3;//  |braaa|
    int endIndex = 7;
    std::cout << "Testing if the string \"" << input << "\" is contained within \"" << otherInput << "\" from " << startIndex << " to " << endIndex << ": Expected(-1) ==> ";
    std::cout << StringManip::findIndex(otherInput, input, startIndex, endIndex);
    std::cout << std::endl;
    std::cout << std::endl;
}

//Test the findIndexLast function
void testFindIndexLastInputOne()
{
    char input[] = "(";
    char otherInput[] = "((()))()";
    std::cout << "Testing if the string \""<< input <<"\" is contained within \""<< otherInput <<"\": Expected(6) ==> ";
    std::cout << StringManip::findIndexLast(otherInput, input);
    std::cout << std::endl;
    std::cout << std::endl;
}

void testFindIndexLastInputTwo()
{
    char input[] = "abc";
    char otherInput[] = "abbaababcabbaaabcabccabab";
    std::cout << "Testing if the string \"" << input << "\" is contained within \"" << otherInput << "\": Expected(17) ==> ";
    std::cout << StringManip::findIndexLast(otherInput, input);
    std::cout << std::endl;
    std::cout << std::endl;
}

void testFindIndexLastInputThree()
{
    char input[] = "aab";
    char otherInput[] = "asvbraaabppabaabbbbaabaabbaab";
    int startIndex = 6;  //   |aabppabaabbbbaab|
    int endIndex = 21;
    std::cout << "Testing if the string \"" << input << "\" is contained within \"" << otherInput << "\" from " << startIndex << " to " << endIndex << ": Expected(19) ==> ";
    std::cout << StringManip::findIndexLast(otherInput, input, startIndex, endIndex);
    std::cout << std::endl;
    std::cout << std::endl;
}

void testFindIndexLastInputFour()
{
    char input[] = "aab";
    char otherInput[] = "asvbraaabppabaabbbbaabaabbaab";
    int startIndex = 6;  //   |aabppabaabbbbaa|
    int endIndex = 20;
    std::cout << "Testing if the string \"" << input << "\" is contained within \"" << otherInput << "\" from " << startIndex << " to " << endIndex << ": Expected(13) ==> ";
    std::cout << StringManip::findIndexLast(otherInput, input, startIndex, endIndex);
    std::cout << std::endl;
    std::cout << std::endl;
}

void countOfTests()
{
    std::cout << "TESTING countOf STRING FUNCTION: " << std::endl;
    
    //TEST 1
    char input1[] = "aab";
    char otherInput1[] = "braaabppabaabbbbaabaabbaab";
    int startIndex1 = 0;  
    int endIndex1 = 25;
    std::cout << "Testing how many times the string \"" << input1 << "\" is contained within \"" << otherInput1 << "\" from " << startIndex1 << " to " << endIndex1 << ": Expected(5) ==> ";
    std::cout << StringManip::countOf(otherInput1, input1, startIndex1, endIndex1);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    char input2[] = "xx";
    char otherInput2[] = "braaabppabaabbbbaabaabbaab";
    int startIndex2 = 0;
    int endIndex2 = 25;
    std::cout << "Testing how many times the string \"" << input2 << "\" is contained within \"" << otherInput2 << "\" from " << startIndex2 << " to " << endIndex2 << ": Expected(0) ==> ";
    std::cout << StringManip::countOf(otherInput2, input2, startIndex2, endIndex2);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 3
    char input3[] = "(";
    char otherInput3[] = "(())((()))";
    int startIndex3 = 5;
    int endIndex3 = 9;
    std::cout << "Testing how many times the string \"" << input3 << "\" is contained within \"" << otherInput3 << "\" from " << startIndex3 << " to " << endIndex3 << ": Expected(2) ==> ";
    std::cout << StringManip::countOf(otherInput3, input3, startIndex3, endIndex3);
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

    ////Testing contains of string
    //std::cout << "TESTING CONTAINS STRING FUNCTION: " << std::endl;
    //testContainsInputOne();
    //testContainsInputTwo();

    ////Testing replaceAll function of string
    //std::cout << "TESTING replaceAll STRING FUNCTION: " << std::endl;
    //testReplaceAllInputOne();
    //testReplaceAllInputTwo();

    ////Testing findIndex function of string
    //std::cout << "TESTING findIndex STRING FUNCTION: " << std::endl;
    //testFindIndexInputOne();
    //testFindIndexInputTwo();
    //testFindIndexInputThree();
    //testFindIndexInputFour();
    //
    ////Testing findIndexLast function of string
    //std::cout << "TESTING findIndexLast STRING FUNCTION: " << std::endl;
    //testFindIndexLastInputOne();
    //testFindIndexLastInputTwo();
    //testFindIndexLastInputThree();
    //testFindIndexLastInputFour();

    // Testing countOf function
    countOfTests();

}

