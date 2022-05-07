#include "StringManipTests.h"
#include "StringManip.h"
#include <iostream>

void StringManipTests::printOutResultStringsFromSplitStringTest(char** strings, size_t numberOfStrings)
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

void StringManipTests::splitByCharTests()
{
    //splitByChar TESTS
    std::cout << "splitByChar TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    char input1[] = "Roskata123|Tupa_rabota";
    size_t numberOfStrings = 0;
    char** strings1 = StringManip::splitString(input1, '|', numberOfStrings);
    std::cout << "Testing input -> \"" << input1 << "\" split by\"|\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(10, 11) ==> ";
    printOutResultStringsFromSplitStringTest(strings1, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    StringManip::deleteArrayOfStrings(strings1, numberOfStrings);

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    char input2[] = "Roskata123|";
    numberOfStrings = 0;
    char** strings2 = StringManip::splitString(input2, '|', numberOfStrings);
    std::cout << "Testing input -> \"" << input2 << "\" split by\"|\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(10, 0) ==> ";
    printOutResultStringsFromSplitStringTest(strings2, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    StringManip::deleteArrayOfStrings(strings2, numberOfStrings);

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    char input3[] = "Roskata123";
    numberOfStrings = 0;
    char** strings3 = StringManip::splitString(input3, '|', numberOfStrings);
    std::cout << "Testing input -> \"" << input3 << "\" split by\"|\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(10) ==> ";
    printOutResultStringsFromSplitStringTest(strings3, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    StringManip::deleteArrayOfStrings(strings3, numberOfStrings);

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    char input4[] = "Roskata123||Heyyy|G";
    numberOfStrings = 0;
    char** strings4 = StringManip::splitString(input4, '|', numberOfStrings);
    std::cout << "Testing input -> \"" << input4 << "\" split by\"|\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(10, 0, 5, 1) ==> ";
    printOutResultStringsFromSplitStringTest(strings4, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    StringManip::deleteArrayOfStrings(strings4, numberOfStrings);

    //TEST 5
    std::cout << "TEST 5" << std::endl;
    char input5[] = "||";
    numberOfStrings = 0;
    char** strings5 = StringManip::splitString(input5, '|', numberOfStrings);
    std::cout << "Testing input -> \"" << input5 << "\" split by\"|\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(0, 0, 0) ==> ";
    printOutResultStringsFromSplitStringTest(strings5, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    StringManip::deleteArrayOfStrings(strings5, numberOfStrings);

    //TEST 6
    std::cout << "TEST 6" << std::endl;
    char input6[] = "|";
    numberOfStrings = 0;
    char** strings6 = StringManip::splitString(input6, '|', numberOfStrings);
    std::cout << "Testing input -> \"" << input6 << "\" split by\"|\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(0, 0) ==> ";
    printOutResultStringsFromSplitStringTest(strings6, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    StringManip::deleteArrayOfStrings(strings6, numberOfStrings);

    //TEST 7
    std::cout << "TEST 7" << std::endl;
    char input7[] = "";
    numberOfStrings = 0;
    char** strings7 = StringManip::splitString(input7, '|', numberOfStrings);
    std::cout << "Testing input -> \"" << input7 << "\" split by\"|\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(0) ==> ";
    printOutResultStringsFromSplitStringTest(strings7, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    StringManip::deleteArrayOfStrings(strings7, numberOfStrings);
    
}

void StringManipTests::splitByStringTests()
{
    //splitByString TESTS
    std::cout << "splitByString TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    char input1[] = "Roskata123|||Tupa_rabota";
    char delim1[] = "|||";
    size_t numberOfStrings = 0;
    char** strings1 = StringManip::splitString(input1, delim1, numberOfStrings);
    std::cout << "Testing input -> \"" << input1 << "\" split by \"" << delim1 << "\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(10, 11) ==> ";
    printOutResultStringsFromSplitStringTest(strings1, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    StringManip::deleteArrayOfStrings(strings1, numberOfStrings);

    //TEST 2
    std::cout << "TEST 1" << std::endl;
    char input2[] = "Roskata123aka";
    char delim2[] = "aka";
    numberOfStrings = 0;
    char** strings2 = StringManip::splitString(input2, delim2, numberOfStrings);
    std::cout << "Testing input -> \"" << input2 << "\" split by \"" << delim2 << "\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(10, 0) ==> ";
    printOutResultStringsFromSplitStringTest(strings2, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    StringManip::deleteArrayOfStrings(strings2, numberOfStrings);

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    char input3[] = "aaab";
    char delim3[] = "aab";
    numberOfStrings = 0;
    char** strings3 = StringManip::splitString(input3, delim3, numberOfStrings);
    std::cout << "Testing input -> \"" << input3 << "\" split by \"" << delim3 << "\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(1, 0) ==> ";
    printOutResultStringsFromSplitStringTest(strings3, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    StringManip::deleteArrayOfStrings(strings3, numberOfStrings);

    //TEST 4
    std::cout << "TEST 1" << std::endl;
    char input4[] = "aaaabka";
    char delim4[] = "aa";
    numberOfStrings = 0;
    char** strings4 = StringManip::splitString(input4, delim4, numberOfStrings);
    std::cout << "Testing input -> \"" << input4 << "\" split by \"" << delim4 << "\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(0, 0, 3) ==> ";
    printOutResultStringsFromSplitStringTest(strings4, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    StringManip::deleteArrayOfStrings(strings4, numberOfStrings);

    //TEST 5
    std::cout << "TEST 5" << std::endl;
    char input5[] = "10+-25-+65+54-33+-29";
    char delim5[] = "+-";
    numberOfStrings = 0;
    char** strings5 = StringManip::splitString(input5, delim5, numberOfStrings);
    std::cout << "Testing input -> \"" << input5 << "\" split by \"" << delim5 << "\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(2, 12, 2) ==> ";
    printOutResultStringsFromSplitStringTest(strings5, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    StringManip::deleteArrayOfStrings(strings5, numberOfStrings);

    //TEST 6
    std::cout << "TEST 6" << std::endl;
    char input6[] = "+-";
    char delim6[] = "+-";
    numberOfStrings = 0;
    char** strings6 = StringManip::splitString(input6, delim6, numberOfStrings);
    std::cout << "Testing input -> \"" << input6 << "\" split by \"" << delim6 << "\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(0, 0) ==> ";
    printOutResultStringsFromSplitStringTest(strings6, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    StringManip::deleteArrayOfStrings(strings6, numberOfStrings);

    //TEST 7
    std::cout << "TEST 7" << std::endl;
    char input7[] = "||";
    char delim7[] = "|";
    numberOfStrings = 0;
    char** strings7 = StringManip::splitString(input7, delim7, numberOfStrings);
    std::cout << "Testing input -> \"" << input7 << "\" split by \"" << delim7 << "\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(0, 0, 0) ==> ";
    printOutResultStringsFromSplitStringTest(strings7, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    StringManip::deleteArrayOfStrings(strings7, numberOfStrings);

    //TEST 8
    std::cout << "TEST 8" << std::endl;
    char input8[] = "_|+Some_|+Kind_|of_expression_|+";
    char delim8[] = "_|+";
    numberOfStrings = 0;
    char** strings8 = StringManip::splitString(input8, delim8, numberOfStrings);
    std::cout << "Testing input -> \"" << input8 << "\" split by \"" << delim8 << "\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(0, 4, 19, 0) ==> ";
    printOutResultStringsFromSplitStringTest(strings8, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    StringManip::deleteArrayOfStrings(strings8, numberOfStrings);

    //TEST 9
    std::cout << "TEST 9" << std::endl;
    char input9[] = "_|Some_|+Kind_|of_expression_|";
    char delim9[] = "_|+";
    numberOfStrings = 0;
    char** strings9 = StringManip::splitString(input9, delim9, numberOfStrings);
    std::cout << "Testing input -> \"" << input9 << "\" split by \"" << delim9 << "\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(6, 21) ==> ";
    printOutResultStringsFromSplitStringTest(strings9, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    StringManip::deleteArrayOfStrings(strings9, numberOfStrings);


}

void StringManipTests::stringContainsTests()
{
    //stringContains TESTS
    std::cout << "stringContains TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    char input1[] = "roskata123";
    char otherInput1[] = "rrrrosenroskata123";
    std::cout << "Testing if the string \""<< input1 <<"\" is contained within \""<< otherInput1 <<"\": Expected(TRUE) ==> ";
    std::cout << (StringManip::stringContains(otherInput1, input1) ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    char input2[] = "aab";
    char otherInput2[] = "aaab";
    std::cout << "Testing if the string \"" << input2 << "\" is contained within \"" << otherInput2 << "\": Expected(TRUE) ==> ";
    std::cout << (StringManip::stringContains(otherInput2, input2) ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;
}

void StringManipTests::replaceAllTests()
{
    //replaceAll TESTS
    std::cout << "replaceAll TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    char input1[] = "15+-13-+14-16+-132+54";
    char replaced1[] = "+-";
    char replacement1[] = "REPLACED";
    size_t numberOfStrings = 0;
    std::cout << "Testing input -> \"" << input1 << "\" where \"" << replaced1 << "\"" << " is replaced by \"" << replacement1 << "\"" << std::endl;
    char* output1 = StringManip::replaceAll(input1, replaced1, replacement1);
    char expectedOutput1[] = "15REPLACED13-+14-16REPLACED132+54";
    std::cout << "String is: Expected(" << expectedOutput1 << ") ==> " << output1 << (strcmp(output1, expectedOutput1) == 0 ? " --> TRUE" : " --> FALSE");

    std::cout << std::endl;
    std::cout << std::endl;

    //Delete dynamic memory
    delete[] output1;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    char input2[] = "15+-13-+14-16+-132+54_15151351";
    char replaced2[] = "15";
    char replacement2[] = "";
    numberOfStrings = 0;
    std::cout << "Testing input -> \"" << input2 << "\" where \"" << replaced2 << "\"" << " is replaced by \"" << replacement2 << "\"" << std::endl;
    char* output2 = StringManip::replaceAll(input2, replaced2, replacement2);
    char expectedOutput2[] = "+-13-+14-16+-132+54_1351";
    std::cout << "String is: Expected(" << expectedOutput2 << ") ==> " << output2 << (strcmp(output2, expectedOutput2) == 0 ? " --> TRUE" : " --> FALSE");

    std::cout << std::endl;
    std::cout << std::endl;

    //Delete dynamic memory
    delete[] output2;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    char input3[] = "15+-13-+14-16+-132+54_15151351";
    char replaced3[] = "as";
    char replacement3[] = "";
    numberOfStrings = 0;
    std::cout << "Testing input -> \"" << input3 << "\" where \"" << replaced3 << "\"" << " is replaced by \"" << replacement3 << "\"" << std::endl;
    char* output3 = StringManip::replaceAll(input3, replaced3, replacement3);
    char expectedOutput3[] = "15+-13-+14-16+-132+54_15151351";
    std::cout << "String is: Expected(" << expectedOutput3 << ") ==> " << output3 << (strcmp(output3, expectedOutput3) == 0 ? " --> TRUE" : " --> FALSE");

    std::cout << std::endl;
    std::cout << std::endl;

    //Delete dynamic memory
    delete[] output3;
}

void StringManipTests::replaceFirstTests()
{
    //replaceFirst TESTS
    std::cout << "replaceFirst TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    char input1[] = "15+-13-+14-16+-132+54";
    char replaced1[] = "+-";
    char replacement1[] = "REPLACED";
    std::cout << "Testing input -> \"" << input1 << "\" where \"" << replaced1 << "\"" << " is replaced by \"" << replacement1 << "\" for the first occurance only" << std::endl;
    char* output1 = StringManip::replaceFirst(input1, replaced1, replacement1);
    char expectedOutput1[] = "15REPLACED13-+14-16+-132+54";
    std::cout << "String is: Expected(" << expectedOutput1 << ") ==> " << output1 << (strcmp(output1, expectedOutput1) == 0 ? " --> TRUE" : " --> FALSE");

    std::cout << std::endl;
    std::cout << std::endl;

    //Delete dynamic memory
    delete[] output1;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    char input2[] = "15+-13-+14-16+-132+54_15151351";
    char replaced2[] = "15";
    char replacement2[] = "";
    std::cout << "Testing input -> \"" << input2 << "\" where \"" << replaced2 << "\"" << " is replaced by \"" << replacement2 << "\" for the first occurance only" << std::endl;
    char* output2 = StringManip::replaceFirst(input2, replaced2, replacement2);
    char expectedOutput2[] = "+-13-+14-16+-132+54_15151351";
    std::cout << "String is: Expected(" << expectedOutput2 << ") ==> " << output2 << (strcmp(output2, expectedOutput2) == 0 ? " --> TRUE" : " --> FALSE");

    std::cout << std::endl;
    std::cout << std::endl;

    //Delete dynamic memory
    delete[] output2;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    char input3[] = "15+-13-+14-16+-132+54_15151351";
    char replaced3[] = "as";
    char replacement3[] = "";
    std::cout << "Testing input -> \"" << input3 << "\" where \"" << replaced3 << "\"" << " is replaced by \"" << replacement3 << "\" for the first occurance only" << std::endl;
    char* output3 = StringManip::replaceFirst(input3, replaced3, replacement3);
    char expectedOutput3[] = "15+-13-+14-16+-132+54_15151351";
    std::cout << "String is: Expected(" << expectedOutput3 << ") ==> " << output3 << (strcmp(output3, expectedOutput3) == 0 ? " --> TRUE" : " --> FALSE");

    std::cout << std::endl;
    std::cout << std::endl;

    //Delete dynamic memory
    delete[] output3;
}

void StringManipTests::findIndexTests()
{
    //findIndex TESTS
    std::cout << "findIndex TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    char input1[] = "roskata123";
    char otherInput1[] = "rrrrosenroskata123";
    std::cout << "Testing if the string \"" << input1 << "\" is contained within \"" << otherInput1 << "\": Expected(8) ==> ";
    std::cout << StringManip::findIndex(otherInput1, input1);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    char input2[] = "aab";
    char otherInput2[] = "aaab";
    std::cout << "Testing if the string \"" << input2 << "\" is contained within \"" << otherInput2 << "\": Expected(1) ==> ";
    std::cout << StringManip::findIndex(otherInput2, input2);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    char input3[] = "aab";
    char otherInput3[] = "asvbraaabppab";
    int startIndex3 = 3;//  |braaab|
    int endIndex3 = 8;
    std::cout << "Testing if the string \"" << input3 << "\" is contained within \"" << otherInput3 << "\" from " << startIndex3 << " to " << endIndex3 << ": Expected(6) ==> ";
    std::cout << StringManip::findIndex(otherInput3, input3, startIndex3, endIndex3);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    char input4[] = "aab";
    char otherInput4[] = "asvbraaabppab";
    int startIndex4 = 3;//  |braaa|
    int endIndex4 = 7;
    std::cout << "Testing if the string \"" << input4 << "\" is contained within \"" << otherInput4 << "\" from " << startIndex4 << " to " << endIndex4 << ": Expected(-1) ==> ";
    std::cout << StringManip::findIndex(otherInput4, input4, startIndex4, endIndex4);
    std::cout << std::endl;
    std::cout << std::endl;
}

void StringManipTests::findIndexLastTests()
{
    //findIndexLast TESTS
    std::cout << "findIndexLast TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    char input1[] = "(";
    char otherInput1[] = "((()))()";
    std::cout << "Testing if the string \"" << input1 << "\" is contained within \"" << otherInput1 << "\": Expected(6) ==> ";
    std::cout << StringManip::findIndexLast(otherInput1, input1);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    char input2[] = "abc";
    char otherInput2[] = "abbaababcabbaaabcabccabab";
    std::cout << "Testing if the string \"" << input2 << "\" is contained within \"" << otherInput2 << "\": Expected(17) ==> ";
    std::cout << StringManip::findIndexLast(otherInput2, input2);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    char input3[] = "aab";
    char otherInput3[] = "asvbraaabppabaabbbbaabaabbaab";
    int startIndex3 = 6;  //   |aabppabaabbbbaab|
    int endIndex3 = 21;
    std::cout << "Testing if the string \"" << input3 << "\" is contained within \"" << otherInput3 << "\" from " << startIndex3 << " to " << endIndex3 << ": Expected(19) ==> ";
    std::cout << StringManip::findIndexLast(otherInput3, input3, startIndex3, endIndex3);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    char input4[] = "aab";
    char otherInput4[] = "asvbraaabppabaabbbbaabaabbaab";
    int startIndex4 = 6;  //   |aabppabaabbbbaa|
    int endIndex4 = 20;
    std::cout << "Testing if the string \"" << input4 << "\" is contained within \"" << otherInput4 << "\" from " << startIndex4 << " to " << endIndex4 << ": Expected(13) ==> ";
    std::cout << StringManip::findIndexLast(otherInput4, input4, startIndex4, endIndex4);
    std::cout << std::endl;
    std::cout << std::endl;
}

void StringManipTests::countOfTests()
{
    //countOf TESTS
    std::cout << "countOf TESTS: " << std::endl << std::endl;


    //TEST 1
    std::cout << "TEST 1" << std::endl;
    char input1[] = "aab";
    char otherInput1[] = "braaabppabaabbbbaabaabbaab";
    int startIndex1 = 0;
    int endIndex1 = 25;
    std::cout << "Testing how many times the string \"" << input1 << "\" is contained within \"" << otherInput1 << "\" from " << startIndex1 << " to " << endIndex1 << ": Expected(5) ==> ";
    std::cout << StringManip::countOf(otherInput1, input1, startIndex1, endIndex1);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    char input2[] = "xx";
    char otherInput2[] = "braaabppabaabbbbaabaabbaab";
    int startIndex2 = 0;
    int endIndex2 = 25;
    std::cout << "Testing how many times the string \"" << input2 << "\" is contained within \"" << otherInput2 << "\" from " << startIndex2 << " to " << endIndex2 << ": Expected(0) ==> ";
    std::cout << StringManip::countOf(otherInput2, input2, startIndex2, endIndex2);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    char input3[] = "(";
    char otherInput3[] = "(())((()))";
    int startIndex3 = 5;
    int endIndex3 = 9;
    std::cout << "Testing how many times the string \"" << input3 << "\" is contained within \"" << otherInput3 << "\" from " << startIndex3 << " to " << endIndex3 << ": Expected(2) ==> ";
    std::cout << StringManip::countOf(otherInput3, input3, startIndex3, endIndex3);
    std::cout << std::endl;
    std::cout << std::endl;
}

void StringManipTests::runTests()
{
    //splitByChar TESTS
    splitByCharTests();

    //splitByString TESTS
    splitByStringTests();

    //stringContains TESTS
    stringContainsTests();

    //replaceAll TESTS
    replaceAllTests();

    //replaceFirst TESTS
    replaceFirstTests();

    //findIndex TESTS
    findIndexTests();

    //findIndexLast TESTS
    findIndexLastTests();

    //countOf TESTS
    countOfTests();
}
