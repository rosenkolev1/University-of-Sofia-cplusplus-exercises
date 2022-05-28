#include "MStringManipTests.h"
#include "MStringManip.h"
#include <iostream>

void MStringManipTests::printOutResultStringsFromSplitStringTest(const mstring* strings, size_t numberOfStrings)
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

void MStringManipTests::printOutStringsFromArray(const mstring* strings, size_t numberOfStrings)
{
    for (size_t i = 0; i < numberOfStrings; i++)
    {
        std::cout << strings[i] << (i != numberOfStrings - 1 ? ", " : "");
    }
}

void MStringManipTests::splitByCharTests()
{
    //splitByChar TESTS
    std::cout << "splitByChar TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    mstring input1 = "Roskata123|Tupa_rabota";
    size_t numberOfStrings = 0;
    mstring* strings1 = MStringManip::splitString(input1, '|', numberOfStrings);
    std::cout << "Testing input -> \"" << input1 << "\" split by\"|\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(10, 11) ==> ";
    printOutResultStringsFromSplitStringTest(strings1, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    MStringManip::deleteArrayOfStrings(strings1, numberOfStrings);

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    mstring input2 = "Roskata123|";
    numberOfStrings = 0;
    mstring* strings2 = MStringManip::splitString(input2, '|', numberOfStrings);
    std::cout << "Testing input -> \"" << input2 << "\" split by\"|\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(10, 0) ==> ";
    printOutResultStringsFromSplitStringTest(strings2, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    MStringManip::deleteArrayOfStrings(strings2, numberOfStrings);

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    mstring input3 = "Roskata123";
    numberOfStrings = 0;
    mstring* strings3 = MStringManip::splitString(input3, '|', numberOfStrings);
    std::cout << "Testing input -> \"" << input3 << "\" split by\"|\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(10) ==> ";
    printOutResultStringsFromSplitStringTest(strings3, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    MStringManip::deleteArrayOfStrings(strings3, numberOfStrings);

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    mstring input4 = "Roskata123||Heyyy|G";
    numberOfStrings = 0;
    mstring* strings4 = MStringManip::splitString(input4, '|', numberOfStrings);
    std::cout << "Testing input -> \"" << input4 << "\" split by\"|\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(10, 0, 5, 1) ==> ";
    printOutResultStringsFromSplitStringTest(strings4, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    MStringManip::deleteArrayOfStrings(strings4, numberOfStrings);

    //TEST 5
    std::cout << "TEST 5" << std::endl;
    mstring input5 = "||";
    numberOfStrings = 0;
    mstring* strings5 = MStringManip::splitString(input5, '|', numberOfStrings);
    std::cout << "Testing input -> \"" << input5 << "\" split by\"|\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(0, 0, 0) ==> ";
    printOutResultStringsFromSplitStringTest(strings5, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    MStringManip::deleteArrayOfStrings(strings5, numberOfStrings);

    //TEST 6
    std::cout << "TEST 6" << std::endl;
    mstring input6 = "|";
    numberOfStrings = 0;
    mstring* strings6 = MStringManip::splitString(input6, '|', numberOfStrings);
    std::cout << "Testing input -> \"" << input6 << "\" split by\"|\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(0, 0) ==> ";
    printOutResultStringsFromSplitStringTest(strings6, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    MStringManip::deleteArrayOfStrings(strings6, numberOfStrings);

    //TEST 7
    std::cout << "TEST 7" << std::endl;
    mstring input7 = "";
    numberOfStrings = 0;
    mstring* strings7 = MStringManip::splitString(input7, '|', numberOfStrings);
    std::cout << "Testing input -> \"" << input7 << "\" split by\"|\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(0) ==> ";
    printOutResultStringsFromSplitStringTest(strings7, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    MStringManip::deleteArrayOfStrings(strings7, numberOfStrings);

}

void MStringManipTests::splitByStringTests()
{
    //splitByString TESTS
    std::cout << "splitByString TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    mstring input1 = "Roskata123|||Tupa_rabota";
    mstring delim1 = "|||";
    size_t numberOfStrings = 0;
    mstring* strings1 = MStringManip::splitString(input1, delim1, numberOfStrings);
    std::cout << "Testing input -> \"" << input1 << "\" split by \"" << delim1 << "\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(10, 11) ==> ";
    printOutResultStringsFromSplitStringTest(strings1, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    MStringManip::deleteArrayOfStrings(strings1, numberOfStrings);

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    mstring input2 = "Roskata123aka";
    mstring delim2 = "aka";
    numberOfStrings = 0;
    mstring* strings2 = MStringManip::splitString(input2, delim2, numberOfStrings);
    std::cout << "Testing input -> \"" << input2 << "\" split by \"" << delim2 << "\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(10, 0) ==> ";
    printOutResultStringsFromSplitStringTest(strings2, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    MStringManip::deleteArrayOfStrings(strings2, numberOfStrings);

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    mstring input3 = "aaab";
    mstring delim3 = "aab";
    numberOfStrings = 0;
    mstring* strings3 = MStringManip::splitString(input3, delim3, numberOfStrings);
    std::cout << "Testing input -> \"" << input3 << "\" split by \"" << delim3 << "\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(1, 0) ==> ";
    printOutResultStringsFromSplitStringTest(strings3, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    MStringManip::deleteArrayOfStrings(strings3, numberOfStrings);

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    mstring input4 = "aaaabka";
    mstring delim4 = "aa";
    numberOfStrings = 0;
    mstring* strings4 = MStringManip::splitString(input4, delim4, numberOfStrings);
    std::cout << "Testing input -> \"" << input4 << "\" split by \"" << delim4 << "\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(0, 0, 3) ==> ";
    printOutResultStringsFromSplitStringTest(strings4, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    MStringManip::deleteArrayOfStrings(strings4, numberOfStrings);

    //TEST 5
    std::cout << "TEST 5" << std::endl;
    mstring input5 = "10+-25-+65+54-33+-29";
    mstring delim5 = "+-";
    numberOfStrings = 0;
    mstring* strings5 = MStringManip::splitString(input5, delim5, numberOfStrings);
    std::cout << "Testing input -> \"" << input5 << "\" split by \"" << delim5 << "\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(2, 12, 2) ==> ";
    printOutResultStringsFromSplitStringTest(strings5, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    MStringManip::deleteArrayOfStrings(strings5, numberOfStrings);

    //TEST 6
    std::cout << "TEST 6" << std::endl;
    mstring input6 = "+-";
    mstring delim6 = "+-";
    numberOfStrings = 0;
    mstring* strings6 = MStringManip::splitString(input6, delim6, numberOfStrings);
    std::cout << "Testing input -> \"" << input6 << "\" split by \"" << delim6 << "\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(0, 0) ==> ";
    printOutResultStringsFromSplitStringTest(strings6, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    MStringManip::deleteArrayOfStrings(strings6, numberOfStrings);

    //TEST 7
    std::cout << "TEST 7" << std::endl;
    mstring input7 = "||";
    mstring delim7 = "|";
    numberOfStrings = 0;
    mstring* strings7 = MStringManip::splitString(input7, delim7, numberOfStrings);
    std::cout << "Testing input -> \"" << input7 << "\" split by \"" << delim7 << "\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(0, 0, 0) ==> ";
    printOutResultStringsFromSplitStringTest(strings7, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    MStringManip::deleteArrayOfStrings(strings7, numberOfStrings);

    //TEST 8
    std::cout << "TEST 8" << std::endl;
    mstring input8 = "_|+Some_|+Kind_|of_expression_|+";
    mstring delim8 = "_|+";
    numberOfStrings = 0;
    mstring* strings8 = MStringManip::splitString(input8, delim8, numberOfStrings);
    std::cout << "Testing input -> \"" << input8 << "\" split by \"" << delim8 << "\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(0, 4, 19, 0) ==> ";
    printOutResultStringsFromSplitStringTest(strings8, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    MStringManip::deleteArrayOfStrings(strings8, numberOfStrings);

    //TEST 9
    std::cout << "TEST 9" << std::endl;
    mstring input9 = "_|Some_|+Kind_|of_expression_|";
    mstring delim9 = "_|+";
    numberOfStrings = 0;
    mstring* strings9 = MStringManip::splitString(input9, delim9, numberOfStrings);
    std::cout << "Testing input -> \"" << input9 << "\" split by \"" << delim9 << "\"" << std::endl;
    std::cout << "Lengths of strings are: Expected(6, 21) ==> ";
    printOutResultStringsFromSplitStringTest(strings9, numberOfStrings);
    std::cout << std::endl;
    std::cout << std::endl;
    MStringManip::deleteArrayOfStrings(strings9, numberOfStrings);
}

void MStringManipTests::splitStringManyTests()
{
    //splitStringMany TESTS
    std::cout << "splitStringMany TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    mstring input1 = "Roskata123|||Tupa_rabota^^^Egati_Tupoto||^^_ |||";
    /*const mstring* delims1 = new mstring []
    {
        "|||",
            "^^^",
            "_"
    };*/
    mstring delims1[] =
    {
         "|||",
             "^^^",
             "_"
    };
    size_t delims1Count = 3;

    size_t sizeOfExpectedOutput = 7;
    /*const mstring* expectedOutput1 = new mstring[]
    {
        "Roskata123",
            "Tupa",
            "rabota",
            "Egati",
            "Tupoto||^^",
            " ",
            ""
    };*/
    mstring expectedOutput1[]
    {
        "Roskata123",
            "Tupa",
            "rabota",
            "Egati",
            "Tupoto||^^",
            " ",
            ""
    };

    std::cout << "Testing input -> \"" << input1 << "\" split by { ";
    printOutStringsFromArray(delims1, delims1Count);
    std::cout << " }. " << std::endl;
    std::cout << "Strings are: Expected(";
    printOutStringsFromArray(expectedOutput1, sizeOfExpectedOutput);
    std::cout << ") ==> ";

    size_t sizeOfOutput1 = 0;
    mstring* output1 = MStringManip::splitStringMany(input1, delims1, delims1Count, sizeOfOutput1);

    printOutStringsFromArray(output1, sizeOfOutput1);
    std::cout << std::endl << "Are the expected output and the output the same: Expected: TRUE ==> "
        << (MStringManip::arraysOfStringsAreEqual(output1, expectedOutput1, sizeOfOutput1, sizeOfExpectedOutput) ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //Delete dynamic memory
    MStringManip::deleteArrayOfStrings(output1, sizeOfOutput1);

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    mstring input2 = "|||Roskata123|||Tupa_rabota^^^Egati_Tupoto||^^_ |||something to end on";
    /*const mstring* delims2 = new const mstring* []
    {
        "|||",
            "^^^",
            "_"
    };*/
    mstring delims2[]
    {
        "|||",
            "^^^",
            "_"
    };
    size_t delims2Count = 3;

    sizeOfExpectedOutput = 8;
    /*const mstring* expectedOutput2 = new const mstring* []
    {
        "",
            "Roskata123",
            "Tupa",
            "rabota",
            "Egati",
            "Tupoto||^^",
            " ",
            "something to end on"
    };*/
    mstring expectedOutput2[]
    {
        "",
            "Roskata123",
            "Tupa",
            "rabota",
            "Egati",
            "Tupoto||^^",
            " ",
            "something to end on"
    };

    std::cout << "Testing input -> \"" << input2 << "\" split by { ";
    printOutStringsFromArray(delims2, delims2Count);
    std::cout << " }. " << std::endl;
    std::cout << "Strings are: Expected(";
    printOutStringsFromArray(expectedOutput2, sizeOfExpectedOutput);
    std::cout << ") ==> ";

    size_t sizeOfOutput2 = 0;
    mstring* output2 = MStringManip::splitStringMany(input2, delims2, delims2Count, sizeOfOutput2);

    printOutStringsFromArray(output2, sizeOfOutput2);
    std::cout << std::endl << "Are the expected output and the output the same: Expected: TRUE ==> "
        << (MStringManip::arraysOfStringsAreEqual(output2, expectedOutput2, sizeOfOutput2, sizeOfExpectedOutput) ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //Delete dynamic memory
    MStringManip::deleteArrayOfStrings(output2, sizeOfOutput2);

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    mstring input3 = "|||Roskata123|||Tupa_rabota^^^Egati_Tupoto||^^_ |||something to end on";
    const mstring* delims3 = new const mstring[0];
    size_t delims3Count = 0;

    sizeOfExpectedOutput = 1;
    /*const mstring* expectedOutput3 = new const mstring* []
    {
        "|||Roskata123|||Tupa_rabota^^^Egati_Tupoto||^^_ |||something to end on",
    };*/
    mstring expectedOutput3[] =
    {
        "|||Roskata123|||Tupa_rabota^^^Egati_Tupoto||^^_ |||something to end on",
    };

    std::cout << "Testing input -> \"" << input3 << "\" split by { ";
    printOutStringsFromArray((mstring*)delims3, delims3Count);
    std::cout << " }. " << std::endl;
    std::cout << "Strings are: Expected(";
    printOutStringsFromArray(expectedOutput3, sizeOfExpectedOutput);
    std::cout << ") ==> ";

    size_t sizeOfOutput3 = 0;
    mstring* output3 = MStringManip::splitStringMany(input3, delims3, delims3Count, sizeOfOutput3);

    printOutStringsFromArray(output3, sizeOfOutput3);
    std::cout << std::endl << "Are the expected output and the output the same: Expected: TRUE ==> "
        << (MStringManip::arraysOfStringsAreEqual(output3, expectedOutput3, sizeOfOutput3, sizeOfExpectedOutput) ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //Delete dynamic memory
    MStringManip::deleteArrayOfStrings(output3, sizeOfOutput3);
    delete[] delims3;

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    mstring input4 = "";
    /*const mstring* delims4 = new const mstring* [3]
    {
        "|||",
            "^^^",
            "_"
    };*/
    mstring delims4[]
    {
        "|||",
            "^^^",
            "_"
    };
    size_t delims4Count = 3;

    sizeOfExpectedOutput = 1;
   /* const mstring* expectedOutput4 = new const mstring* []
    {
        "",
    };*/
    mstring expectedOutput4[]
    {
        "",
    };

    std::cout << "Testing input -> \"" << input4 << "\" split by { ";
    printOutStringsFromArray(delims4, delims4Count);
    std::cout << " }. " << std::endl;
    std::cout << "Strings are: Expected(";
    printOutStringsFromArray(expectedOutput4, sizeOfExpectedOutput);
    std::cout << ") ==> ";

    size_t sizeOfOutput4 = 0;
    mstring* output4 = MStringManip::splitStringMany(input4, delims4, delims4Count, sizeOfOutput4);

    printOutStringsFromArray(output4, sizeOfOutput4);
    std::cout << std::endl << "Are the expected output and the output the same: Expected: TRUE ==> "
        << (MStringManip::arraysOfStringsAreEqual(output4, expectedOutput4, sizeOfOutput4, sizeOfExpectedOutput) ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //Delete dynamic memory
    MStringManip::deleteArrayOfStrings(output4, sizeOfOutput4);

    //TEST 5
    std::cout << "TEST 5" << std::endl;
    mstring input5 = "|||";
    /*const mstring* delims5 = new const mstring* [3]
    {
        "|||",
            "^^^",
            "_"
    };*/
    mstring delims5[]
    {
        "|||",
            "^^^",
            "_"
    };
    size_t delims5Count = 3;

    sizeOfExpectedOutput = 2;
    /*const mstring* expectedOutput5 = new const mstring* []
    {
        "",
            ""
    };*/
    mstring expectedOutput5[]
    {
        "",
            ""
    };

    std::cout << "Testing input -> \"" << input5 << "\" split by { ";
    printOutStringsFromArray(delims5, delims5Count);
    std::cout << " }. " << std::endl;
    std::cout << "Strings are: Expected(";
    printOutStringsFromArray(expectedOutput5, sizeOfExpectedOutput);
    std::cout << ") ==> ";

    size_t sizeOfOutput5 = 0;
    mstring* output5 = MStringManip::splitStringMany(input5, delims5, delims5Count, sizeOfOutput5);

    printOutStringsFromArray(output5, sizeOfOutput5);
    std::cout << std::endl << "Are the expected output and the output the same: Expected: TRUE ==> "
        << (MStringManip::arraysOfStringsAreEqual(output5, expectedOutput5, sizeOfOutput5, sizeOfExpectedOutput) ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //Delete dynamic memory
    MStringManip::deleteArrayOfStrings(output5, sizeOfOutput5);

    //TEST 6
    std::cout << "TEST 6" << std::endl;
    mstring input6 = "Rosen4o";
    /*const mstring* delims6 = new const mstring* [3]
    {
        "|||",
            "^^^",
            "_"
    };*/
    mstring delims6[]
    {
         "|||",
             "^^^",
             "_"
    };
    size_t delims6Count = 3;

    sizeOfExpectedOutput = 1;
    /*const mstring* expectedOutput6 = new const mstring* []
    {
        "Rosen4o"
    };*/
    mstring expectedOutput6[]
    {
        "Rosen4o"
    };

    std::cout << "Testing input -> \"" << input6 << "\" split by { ";
    printOutStringsFromArray(delims6, delims6Count);
    std::cout << " }. " << std::endl;
    std::cout << "Strings are: Expected(";
    printOutStringsFromArray(expectedOutput6, sizeOfExpectedOutput);
    std::cout << ") ==> ";

    size_t sizeOfOutput6 = 0;
    mstring* output6 = MStringManip::splitStringMany(input6, delims6, delims6Count, sizeOfOutput6);

    printOutStringsFromArray(output6, sizeOfOutput6);
    std::cout << std::endl << "Are the expected output and the output the same: Expected: TRUE ==> "
        << (MStringManip::arraysOfStringsAreEqual(output6, expectedOutput6, sizeOfOutput6, sizeOfExpectedOutput) ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //Delete dynamic memory
    MStringManip::deleteArrayOfStrings(output6, sizeOfOutput6);

    //TEST 7
    std::cout << "TEST 7" << std::endl;
    mstring input7 = "Roskata123|||Tupa_rabota^^^Egati_Tupoto||^^_ |||";
    /*const mstring* delims7 = new const mstring* []
    {
        "|||",
            "^^^",
            "_",
            "|||",
            "_",
            "||"
    };*/
    mstring delims7[]
    {
        "|||",
            "^^^",
            "_",
            "|||",
            "_",
            "||"
    };

    size_t delims7Count = 6;

    sizeOfExpectedOutput = 8;
   /* const mstring* expectedOutput7 = new const mstring* []
    {
        "Roskata123",
            "Tupa",
            "rabota",
            "Egati",
            "Tupoto",
            "^^",
            " ",
            ""
    };*/
    mstring expectedOutput7[]
    {
        "Roskata123",
            "Tupa",
            "rabota",
            "Egati",
            "Tupoto",
            "^^",
            " ",
            ""
    };

    std::cout << "Testing input -> \"" << input7 << "\" split by { ";
    printOutStringsFromArray(delims7, delims1Count);
    std::cout << " }. " << std::endl;
    std::cout << "Strings are: Expected(";
    printOutStringsFromArray(expectedOutput7, sizeOfExpectedOutput);
    std::cout << ") ==> ";

    size_t sizeOfOutput7 = 0;
    mstring* output7 = MStringManip::splitStringMany(input7, delims7, delims7Count, sizeOfOutput7);

    printOutStringsFromArray(output7, sizeOfOutput7);
    std::cout << std::endl << "Are the expected output and the output the same: Expected: TRUE ==> "
        << (MStringManip::arraysOfStringsAreEqual(output7, expectedOutput7, sizeOfOutput7, sizeOfExpectedOutput) ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //Delete dynamic memory
    MStringManip::deleteArrayOfStrings(output7, sizeOfOutput7);

    //TEST 8
    std::cout << "TEST 8" << std::endl;
    mstring input8 = "Roskata123|||Tupa_rabota^^^Egati_Tupoto||^^_ |||";
    /*mstring delims8[] =
    {
        "_|"
    };*/
    mstring delims8 = "_|";

    sizeOfExpectedOutput = 12;
    /*const mstring* expectedOutput8 = new const mstring* []
    {
        "Roskata123",
            "",
            "",
            "Tupa",
            "rabota^^^Egati",
            "Tupoto",
            "",
            "^^",
            " ",
            "",
            "",
            ""
    };*/
    mstring expectedOutput8[]
    {
        "Roskata123",
            "",
            "",
            "Tupa",
            "rabota^^^Egati",
            "Tupoto",
            "",
            "^^",
            " ",
            "",
            "",
            ""
    };

    std::cout << "Testing input -> \"" << input8 << "\" split by the symbols of { " << delims8 << " }. " << std::endl;
    std::cout << "Strings are: Expected(";
    printOutStringsFromArray(expectedOutput8, sizeOfExpectedOutput);
    std::cout << ") ==> ";

    size_t sizeOfOutput8 = 0;
    mstring* output8 = MStringManip::splitStringMany(input8, delims8, sizeOfOutput8);

    printOutStringsFromArray(output8, sizeOfOutput8);
    std::cout << std::endl << "Are the expected output and the output the same: Expected: TRUE ==> "
        << (MStringManip::arraysOfStringsAreEqual(output8, expectedOutput8, sizeOfOutput8, sizeOfExpectedOutput) ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //Delete dynamic memory
    MStringManip::deleteArrayOfStrings(output8, sizeOfOutput8);

    //TEST 9
    std::cout << "TEST 9" << std::endl;
    mstring input9 = "Roskata123|||Tupa_rabota^^^Egati_Tupoto||^^_ |||";
    mstring delims9 = "|";

    sizeOfExpectedOutput = 9;
    /*const mstring* expectedOutput9 = new const mstring* []
    {
        "Roskata123",
            "",
            "",
            "Tupa_rabota^^^Egati_Tupoto",
            "",
            "^^_ ",
            "",
            "",
            "",
    };*/
    mstring expectedOutput9[]
    {
        "Roskata123",
            "",
            "",
            "Tupa_rabota^^^Egati_Tupoto",
            "",
            "^^_ ",
            "",
            "",
            "",
    };

    std::cout << "Testing input -> \"" << input9 << "\" split by the symbols of { " << delims9 << " }. " << std::endl;
    std::cout << "Strings are: Expected(";
    printOutStringsFromArray(expectedOutput9, sizeOfExpectedOutput);
    std::cout << ") ==> ";

    size_t sizeOfOutput9 = 0;
    mstring* output9 = MStringManip::splitStringMany(input9, delims9, sizeOfOutput9);

    printOutStringsFromArray(output9, sizeOfOutput9);
    std::cout << std::endl << "Are the expected output and the output the same: Expected: TRUE ==> "
        << (MStringManip::arraysOfStringsAreEqual(output9, expectedOutput9, sizeOfOutput9, sizeOfExpectedOutput) ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //Delete dynamic memory
    MStringManip::deleteArrayOfStrings(output9, sizeOfOutput9);

    //TEST 10
    std::cout << "TEST 10" << std::endl;
    mstring input10 = "Roskata123|||Tupa_rabota^^^Egati_Tupoto||^^_ |||";
    mstring delims10 = "";

    sizeOfExpectedOutput = 1;
    /*const mstring* expectedOutput10 = new const mstring* []
    {
        "Roskata123|||Tupa_rabota^^^Egati_Tupoto||^^_ |||",
    };*/
    mstring expectedOutput10[]
    {
        "Roskata123|||Tupa_rabota^^^Egati_Tupoto||^^_ |||"
    };

    std::cout << "Testing input -> \"" << input10 << "\" split by the symbols of { " << delims10 << " }. " << std::endl;
    std::cout << "Strings are: Expected(";
    printOutStringsFromArray(expectedOutput10, sizeOfExpectedOutput);
    std::cout << ") ==> ";

    size_t sizeOfOutput10 = 0;
    mstring* output10 = MStringManip::splitStringMany(input10, delims10, sizeOfOutput10);

    printOutStringsFromArray(output10, sizeOfOutput10);
    std::cout << std::endl << "Are the expected output and the output the same: Expected: TRUE ==> "
        << (MStringManip::arraysOfStringsAreEqual(output10, expectedOutput10, sizeOfOutput10, sizeOfExpectedOutput) ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //Delete dynamic memory
    MStringManip::deleteArrayOfStrings(output10, sizeOfOutput10);
}

void MStringManipTests::stringContainsTests()
{
    //stringContains TESTS
    std::cout << "stringContains TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    mstring input1 = "roskata123";
    mstring otherInput1 = "rrrrosenroskata123";
    std::cout << "Testing if the string \"" << input1 << "\" is contained within \"" << otherInput1 << "\": Expected(TRUE) ==> ";
    std::cout << (MStringManip::stringContains(otherInput1, input1) ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    mstring input2 = "aab";
    mstring otherInput2 = "aaab";
    std::cout << "Testing if the string \"" << input2 << "\" is contained within \"" << otherInput2 << "\": Expected(TRUE) ==> ";
    std::cout << (MStringManip::stringContains(otherInput2, input2) ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;
}

void MStringManipTests::replaceAllTests()
{
    //replaceAll TESTS
    std::cout << "replaceAll TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    mstring input1 = "15+-13-+14-16+-132+54";
    mstring replaced1 = "+-";
    mstring replacement1 = "REPLACED";
    size_t numberOfStrings = 0;
    std::cout << "Testing input -> \"" << input1 << "\" where \"" << replaced1 << "\"" << " is replaced by \"" << replacement1 << "\"" << std::endl;
    mstring output1 = MStringManip::replaceAll(input1, replaced1, replacement1);
    mstring expectedOutput1 = "15REPLACED13-+14-16REPLACED132+54";
    std::cout << "String is: Expected(" << expectedOutput1 << ") ==> " << output1 << (output1 == expectedOutput1 ? " --> TRUE" : " --> FALSE");

    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    mstring input2 = "15+-13-+14-16+-132+54_15151351";
    mstring replaced2 = "15";
    mstring replacement2 = "";
    numberOfStrings = 0;
    std::cout << "Testing input -> \"" << input2 << "\" where \"" << replaced2 << "\"" << " is replaced by \"" << replacement2 << "\"" << std::endl;
    mstring output2 = MStringManip::replaceAll(input2, replaced2, replacement2);
    mstring expectedOutput2 = "+-13-+14-16+-132+54_1351";
    std::cout << "String is: Expected(" << expectedOutput2 << ") ==> " << output2 << (output2 == expectedOutput2 ? " --> TRUE" : " --> FALSE");

    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    mstring input3 = "15+-13-+14-16+-132+54_15151351";
    mstring replaced3 = "as";
    mstring replacement3 = "";
    numberOfStrings = 0;
    std::cout << "Testing input -> \"" << input3 << "\" where \"" << replaced3 << "\"" << " is replaced by \"" << replacement3 << "\"" << std::endl;
    mstring output3 = MStringManip::replaceAll(input3, replaced3, replacement3);
    mstring expectedOutput3 = "15+-13-+14-16+-132+54_15151351";
    std::cout << "String is: Expected(" << expectedOutput3 << ") ==> " << output3 << (output3 == expectedOutput3 ? " --> TRUE" : " --> FALSE");

    std::cout << std::endl;
    std::cout << std::endl;
}

void MStringManipTests::replaceFirstTests()
{
    //replaceFirst TESTS
    std::cout << "replaceFirst TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    mstring input1 = "15+-13-+14-16+-132+54";
    mstring replaced1 = "+-";
    mstring replacement1 = "REPLACED";
    std::cout << "Testing input -> \"" << input1 << "\" where \"" << replaced1 << "\"" << " is replaced by \"" << replacement1 << "\" for the first occurance only" << std::endl;
    mstring output1 = MStringManip::replaceFirst(input1, replaced1, replacement1);
    mstring expectedOutput1 = "15REPLACED13-+14-16+-132+54";
    std::cout << "String is: Expected(" << expectedOutput1 << ") ==> " << output1 << (output1 == expectedOutput1 ? " --> TRUE" : " --> FALSE");

    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    mstring input2 = "15+-13-+14-16+-132+54_15151351";
    mstring replaced2 = "15";
    mstring replacement2 = "";
    std::cout << "Testing input -> \"" << input2 << "\" where \"" << replaced2 << "\"" << " is replaced by \"" << replacement2 << "\" for the first occurance only" << std::endl;
    mstring output2 = MStringManip::replaceFirst(input2, replaced2, replacement2);
    mstring expectedOutput2 = "+-13-+14-16+-132+54_15151351";
    std::cout << "String is: Expected(" << expectedOutput2 << ") ==> " << output2 << (output2 == expectedOutput2 ? " --> TRUE" : " --> FALSE");

    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    mstring input3 = "15+-13-+14-16+-132+54_15151351";
    mstring replaced3 = "as";
    mstring replacement3 = "";
    std::cout << "Testing input -> \"" << input3 << "\" where \"" << replaced3 << "\"" << " is replaced by \"" << replacement3 << "\" for the first occurance only" << std::endl;
    mstring output3 = MStringManip::replaceFirst(input3, replaced3, replacement3);
    mstring expectedOutput3 = "15+-13-+14-16+-132+54_15151351";
    std::cout << "String is: Expected(" << expectedOutput3 << ") ==> " << output3 << (output3 == expectedOutput3 ? " --> TRUE" : " --> FALSE");

    std::cout << std::endl;
    std::cout << std::endl;
}

void MStringManipTests::replaceFromTests()
{
    //replaceFrom TESTS
    std::cout << "replaceFrom TESTS" << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    mstring input1 = "rrrrosenroskata123";
    mstring otherInput1 = "roskata123";
    mstring expectedOutput1 = "roskata123roskata123";
    size_t startIndex = 0;
    size_t endIndex = 7;
    std::cout << "Trying to replace \"" << input1 << "\" from index " << startIndex << " to index " << endIndex << " with the string \"" << otherInput1
        << "\": Expected: " << expectedOutput1 << ", TRUE ==> ";
    mstring output1 = MStringManip::replaceFrom(input1, otherInput1, startIndex, endIndex);
    std::cout << output1 << ", " << (output1 == expectedOutput1 ? "TRUE" : "FALSE");

    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    mstring input2 = "rrrrosenroskata123";
    mstring otherInput2 = "roskata123";
    mstring expectedOutput2 = "roskata123";
    startIndex = 0;
    std::cout << "Trying to replace \"" << input2 << "\" from index " << startIndex << " to the end index with the string \"" << otherInput2
        << "\": Expected: " << expectedOutput2 << ", TRUE ==> ";
    mstring output2 = MStringManip::replaceFrom(input2, otherInput2, startIndex);
    std::cout << output2 << ", " << (output2 == expectedOutput2 ? "TRUE" : "FALSE");

    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    mstring input3 = "rrrrosenroskata123";
    mstring otherInput3 = "";
    mstring expectedOutput3 = "123";
    startIndex = 0;
    endIndex = 14;
    std::cout << "Trying to replace \"" << input3 << "\" from index " << startIndex << " to index " << endIndex << " with the string \"" << otherInput3
        << "\": Expected: " << expectedOutput3 << ", TRUE ==> ";
    mstring output3 = MStringManip::replaceFrom(input3, otherInput3, startIndex, endIndex);
    std::cout << output3 << ", " << (output3 == expectedOutput3 ? "TRUE" : "FALSE");

    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    mstring input4 = "";
    mstring otherInput4 = "rrrrosenroskata123";
    mstring expectedOutput4 = "rrrrosenroskata123";
    startIndex = 0;
    std::cout << "Trying to replace \"" << input4 << "\" from index " << startIndex << " to index " << endIndex << " with the string \"" << otherInput4
        << "\": Expected: " << expectedOutput4 << ", TRUE ==> ";
    mstring output4 = MStringManip::replaceFrom(input4, otherInput4, startIndex);
    std::cout << output4 << ", " << (output4 == expectedOutput4 ? "TRUE" : "FALSE");

    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 5
    std::cout << "TEST 5" << std::endl;
    mstring input5 = "aaxaa";
    mstring otherInput5 = "bbbbbb";
    mstring expectedOutput5 = "aabbbbbbaa";
    startIndex = 2;
    endIndex = 2;
    std::cout << "Trying to replace \"" << input5 << "\" from index " << startIndex << " to index " << endIndex << " with the string \"" << otherInput5
        << "\": Expected: " << expectedOutput5 << ", TRUE ==> ";
    mstring output5 = MStringManip::replaceFrom(input5, otherInput5, startIndex, endIndex);
    std::cout << output5 << ", " << (output5 == expectedOutput5 ? "TRUE" : "FALSE");

    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 6
    std::cout << "TEST 6" << std::endl;
    mstring input6 = "aaxaa";
    mstring otherInput6 = "bbbbbb";
    mstring expectedOutput6 = "aabbbbbbaa";
    startIndex = 3;
    endIndex = 1;
    std::cout << "Trying to replace \"" << input6 << "\" from index " << startIndex << " to index " << endIndex << " with the string \"" << otherInput6
        << "\": Expected: Throw Exception ==> ";
    try
    {
        mstring output6 = MStringManip::replaceFrom(input6, otherInput6, startIndex, endIndex);
        std::cout << output6 << ", " << (output6 == expectedOutput6 ? "TRUE" : "FALSE");

    }
    catch (...)
    {
        std::cout << "Throw Exception";
    }

    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 7
    std::cout << "TEST 7" << std::endl;
    mstring input7 = "aaxaa";
    mstring otherInput7 = "bbbbbb";
    mstring expectedOutput7 = "aabbbbbbaa";
    startIndex = 5;
    endIndex = 7;
    std::cout << "Trying to replace \"" << input7 << "\" from index " << startIndex << " to index " << endIndex << " with the string \"" << otherInput7
        << "\": Expected: Throw Exception ==> ";
    try
    {
        mstring output7 = MStringManip::replaceFrom(input7, otherInput7, startIndex, startIndex);
        std::cout << output7 << ", " << (output7 == expectedOutput7 ? "TRUE" : "FALSE");

    }
    catch (...)
    {
        std::cout << "Throw Exception";
    }

    std::cout << std::endl;
    std::cout << std::endl;
}

void MStringManipTests::findIndexTests()
{
    //findIndex TESTS
    std::cout << "findIndex TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    mstring input1 = "roskata123";
    mstring otherInput1 = "rrrrosenroskata123";
    std::cout << "Testing if the string \"" << input1 << "\" is contained within \"" << otherInput1 << "\": Expected(8) ==> ";
    std::cout << MStringManip::findIndex(otherInput1, input1);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    mstring input2 = "aab";
    mstring otherInput2 = "aaab";
    std::cout << "Testing if the string \"" << input2 << "\" is contained within \"" << otherInput2 << "\": Expected(1) ==> ";
    std::cout << MStringManip::findIndex(otherInput2, input2);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    mstring input3 = "aab";
    mstring otherInput3 = "asvbraaabppab";
    int startIndex3 = 3;//  |braaab|
    int endIndex3 = 8;
    std::cout << "Testing if the string \"" << input3 << "\" is contained within \"" << otherInput3 << "\" from " << startIndex3 << " to " << endIndex3 << ": Expected(6) ==> ";
    std::cout << MStringManip::findIndex(otherInput3, input3, startIndex3, endIndex3);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    mstring input4 = "aab";
    mstring otherInput4 = "asvbraaabppab";
    int startIndex4 = 3;//  |braaa|
    int endIndex4 = 7;
    std::cout << "Testing if the string \"" << input4 << "\" is contained within \"" << otherInput4 << "\" from " << startIndex4 << " to " << endIndex4 << ": Expected(-1) ==> ";
    std::cout << MStringManip::findIndex(otherInput4, input4, startIndex4, endIndex4);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 5
    std::cout << "TEST 5" << std::endl;
    mstring input5 = "xxx";
    mstring otherInput5 = "asvbraaabppab";
    int startIndex5 = 0;//  |braaa|
    int endIndex5 = 12;
    std::cout << "Testing if the string \"" << input5 << "\" is contained within \"" << otherInput5 << "\" from " << startIndex5 << " to " << endIndex5 << ": Expected(-1) ==> ";
    std::cout << MStringManip::findIndex(otherInput5, input5, startIndex5, endIndex5);
    std::cout << std::endl;
    std::cout << std::endl;
}

void MStringManipTests::findIndexLastTests()
{
    //findIndexLast TESTS
    std::cout << "findIndexLast TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    mstring input1 = "(";
    mstring otherInput1 = "((()))()";
    std::cout << "Testing if the string \"" << input1 << "\" is contained within \"" << otherInput1 << "\": Expected(6) ==> ";
    std::cout << MStringManip::findIndexLast(otherInput1, input1);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    mstring input2 = "abc";
    mstring otherInput2 = "abbaababcabbaaabcabccabab";
    std::cout << "Testing if the string \"" << input2 << "\" is contained within \"" << otherInput2 << "\": Expected(17) ==> ";
    std::cout << MStringManip::findIndexLast(otherInput2, input2);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    mstring input3 = "aab";
    mstring otherInput3 = "asvbraaabppabaabbbbaabaabbaab";
    int startIndex3 = 6;  //    |aabppabaabbbbaab|
    int endIndex3 = 21;
    std::cout << "Testing if the string \"" << input3 << "\" is contained within \"" << otherInput3 << "\" from " << startIndex3 << " to " << endIndex3 << ": Expected(19) ==> ";
    std::cout << MStringManip::findIndexLast(otherInput3, input3, startIndex3, endIndex3);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    mstring input4 = "aab";
    mstring otherInput4 = "asvbraaabppabaabbbbaabaabbaab";
    int startIndex4 = 6;  //   |aabppabaabbbbaa|
    int endIndex4 = 20;
    std::cout << "Testing if the string \"" << input4 << "\" is contained within \"" << otherInput4 << "\" from " << startIndex4 << " to " << endIndex4 << ": Expected(13) ==> ";
    std::cout << MStringManip::findIndexLast(otherInput4, input4, startIndex4, endIndex4);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 5
    std::cout << "TEST 5" << std::endl;
    mstring input5 = "xxx";
    mstring otherInput5 = "asvbraaabppabaabbbbaabaabbaab";
    int startIndex5 = 6;  //   |aabppabaabbbbaa|
    int endIndex5 = 20;
    std::cout << "Testing if the string \"" << input5 << "\" is contained within \"" << otherInput5 << "\" from " << startIndex5 << " to " << endIndex5 << ": Expected(-1) ==> ";
    std::cout << MStringManip::findIndexLast(otherInput5, input5, startIndex5, endIndex5);
    std::cout << std::endl;
    std::cout << std::endl;
}

void MStringManipTests::arraysOfStringsAreEqualTests()
{
    //arraysOfStringsAreEqualTests TESTS
    std::cout << "arraysOfStringsAreEqualTests TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    /*const mstring* input11 = new const mstring* []
    {
        "Something",
            "Anything",
            "something",
            "Something",
            "Anything",
            "",
            "  ",
            "",
            " ",
            "Anything"
    };*/
    mstring input11[]
    {
        "Something",
            "Anything",
            "something",
            "Something",
            "Anything",
            "",
            "  ",
            "",
            " ",
            "Anything"
    };
    size_t arraySizeInput11 = 10;

    /*const mstring* input12 = new const mstring* []
    {
        "Something",
            "Anything",
            "something",
            "",
            "  ",
            " ",
    };*/
    mstring input12[]
    {
        "Something",
            "Anything",
            "something",
            "",
            "  ",
            " ",
    };
    size_t arraySizeInput12 = 6;

    std::cout << "Testing if the string arrays {";
    printOutStringsFromArray(input11, arraySizeInput11);
    std::cout << "} and {";
    printOutStringsFromArray(input12, arraySizeInput12);
    std::cout << "} are equal: Expected(FALSE) ==> " << (MStringManip::arraysOfStringsAreEqual(input11, input12, arraySizeInput11, arraySizeInput12) ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    /*const mstring* input21 = new const mstring* []
    {
        "Something",
            "Anything",
            "something",
            "Something",
            "Anything",
            "",
            "  ",
            "",
            " ",
            "Anything"
    };*/
    mstring input21[]
    {
         "Something",
             "Anything",
             "something",
             "Something",
             "Anything",
             "",
             "  ",
             "",
             " ",
             "Anything"
    };

    size_t arraySizeInput21 = 10;

    /*const mstring* input22 = new const mstring* []
    {
        "Something",
            "Anything",
            "something",
            "Something",
            "Anything",
            "",
            "  ",
            "",
            " ",
            "Anything"
    };*/
    mstring input22[]
    {
        "Something",
            "Anything",
            "something",
            "Something",
            "Anything",
            "",
            "  ",
            "",
            " ",
            "Anything"
    };

    size_t arraySizeInput22 = 10;

    std::cout << "Testing if the string arrays {";
    printOutStringsFromArray(input21, arraySizeInput21);
    std::cout << "} and {";
    printOutStringsFromArray(input22, arraySizeInput22);
    std::cout << "} are equal: Expected(TRUE) ==> " << (MStringManip::arraysOfStringsAreEqual(input21, input22, arraySizeInput21, arraySizeInput22) ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    /*const mstring* input31 = new const mstring* []
    {
        "",
    };*/
    mstring input31[]
    {
        ""
    };
    size_t arraySizeInput31 = 1;

    /*const mstring* input32 = new const mstring* []
    {
        "",
    };*/
    mstring input32[]
    {
        ""
    };
    size_t arraySizeInput32 = 1;

    std::cout << "Testing if the string arrays {";
    printOutStringsFromArray(input31, arraySizeInput31);
    std::cout << "} and {";
    printOutStringsFromArray(input32, arraySizeInput32);
    std::cout << "} are equal: Expected(TRUE) ==> " << (MStringManip::arraysOfStringsAreEqual(input31, input32, arraySizeInput31, arraySizeInput32) ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;
}

void MStringManipTests::getUniqueTests()
{
    //getUnique TESTS
    std::cout << "getUnique TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    mstring input1 = "bbbcddfagbbcde";
    mstring expectedOuput1 = "bcdfage";
    mstring output1 = MStringManip::getUnique(input1);
    std::cout << "Testing what the unique symbols of \"" << input1 << "\" are: Expected(" << expectedOuput1 << ", TRUE) ==> " << output1 << ", "
        << (expectedOuput1 == output1 ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    mstring input2 = "      ";
    mstring expectedOuput2 = " ";
    mstring output2 = MStringManip::getUnique(input2);
    std::cout << "Testing what the unique symbols of \"" << input2 << "\" are: Expected(" << expectedOuput2 << ", TRUE) ==> " << output2 << ", "
        << (expectedOuput2 == output2 ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    mstring input3 = "";
    mstring expectedOuput3 = "";
    mstring output3 = MStringManip::getUnique(input3);
    std::cout << "Testing what the unique symbols of \"" << input3 << "\" are: Expected(" << expectedOuput3 << ", TRUE) ==> " << output3 << ", "
        << (expectedOuput3 == output3 ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    mstring input4 = "ccccccccccccccccccccccccxcccccccccccccccc";
    mstring expectedOuput4 = "cx";
    mstring output4 = MStringManip::getUnique(input4);
    std::cout << "Testing what the unique symbols of \"" << input4 << " are: Expected(" << expectedOuput4 << ", TRUE) ==> " << output4 << ", "
        << (expectedOuput4 == output4 ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 5
    std::cout << "TEST 5" << std::endl;
    /*const mstring* input5 = new const mstring* []
    {
        "Something",
            "Anything",
            "something",
            "Something",
            "Anything",
            "",
            "  ",
            "",
            " ",
            "Anything"
    };*/
    mstring input5[]
    {
        "Something",
            "Anything",
            "something",
            "Something",
            "Anything",
            "",
            "  ",
            "",
            " ",
            "Anything"
    };
    size_t arraySizeInput = 10;

    /*const mstring* expectedOutput5 = new const mstring* []
    {
        "Something",
            "Anything",
            "something",
            "",
            "  ",
            " ",
    };*/
    mstring expectedOutput5[]
    {
         "Something",
             "Anything",
             "something",
             "",
             "  ",
             " ",
    };
    size_t arraySizeExpectedOutput = 6;

    size_t arraySizeOutput = arraySizeInput;
    mstring* output5 = MStringManip::getUnique(input5, arraySizeOutput);
    std::cout << "Testing what the unique strings of \"";
    printOutStringsFromArray(input5, arraySizeInput);
    std::cout << " are: Expected(";
    printOutStringsFromArray(expectedOutput5, arraySizeExpectedOutput);
    std::cout << ", TRUE) ==> ";
    printOutStringsFromArray(output5, arraySizeOutput);
    std::cout << ", ";
    std::cout << (MStringManip::arraysOfStringsAreEqual(output5, expectedOutput5, arraySizeOutput, arraySizeExpectedOutput) ? "TRUE" : "FALSE");
    std::cout << std::endl;
    std::cout << std::endl;

    //Delete dynamic memory
    MStringManip::deleteArrayOfStrings(output5, arraySizeOutput);

    //TEST 6
    std::cout << "TEST 6" << std::endl;
    const mstring* input6 = new mstring [0];
    arraySizeInput = 0;

    /*const mstring* expectedOutput6 = new const mstring* []
    {
        "Something",
            "Anything",
            "something",
            "",
            "  ",
            " ",
    };*/
    mstring expectedOutput6[]
    {
        "Something",
            "Anything",
            "something",
            "",
            "  ",
            " ",
    };
    arraySizeExpectedOutput = 6;

    arraySizeOutput = arraySizeInput;
    std::cout << "Testing what the unique strings of \"";
    printOutStringsFromArray(input6, arraySizeInput);
    std::cout << " are: Expected(Throw Error) ==> ";
    try
    {
        mstring* output6 = MStringManip::getUnique(input6, arraySizeOutput);
        printOutStringsFromArray(output6, arraySizeOutput);
        std::cout << ", ";
        std::cout << (MStringManip::arraysOfStringsAreEqual(output6, expectedOutput6, arraySizeOutput, arraySizeExpectedOutput) ? "TRUE" : "FALSE");

        //Delete dynamic memory
        MStringManip::deleteArrayOfStrings(output6, arraySizeOutput);
    }
    catch (...)
    {
        std::cout << "Throw Error";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    //Delete dynamic memory
    delete[] input6;
}

void MStringManipTests::getFromTests()
{
    //getFrom TESTS
    std::cout << "getFrom TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    mstring input1 = "bbbcddfagbbcde";
    mstring expectedOuput1 = "bbcdd";
    int indexStart = 1;
    int indexEnd = 5;
    mstring output1 = MStringManip::getFrom(input1, indexStart, indexEnd);
    std::cout << "Testing getting the part of \"" << input1 << "\" from " << indexStart << " to " << indexEnd << " are: Expected: " << expectedOuput1 << " ==> " << output1;
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    mstring input2 = "bbbcddfagbbcde";
    mstring expectedOuput2 = "f";
    indexStart = 6;
    indexEnd = 6;
    mstring output2 = MStringManip::getFrom(input2, indexStart, indexEnd);
    std::cout << "Testing getting the part of \"" << input2 << "\" from " << indexStart << " to " << indexEnd << " are: Expected: " << expectedOuput2 << " ==> " << output2;
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    mstring input3 = "x";
    mstring expectedOuput3 = "x";
    indexStart = 0;
    indexEnd = 0;
    mstring output3 = MStringManip::getFrom(input3, indexStart, indexEnd);
    std::cout << "Testing getting the part of \"" << input3 << "\" from " << indexStart << " to " << indexEnd << " are: Expected: " << expectedOuput3 << " ==> " << output3;
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    mstring input4 = "abcdefghi";
    mstring expectedOuput4 = "The start or end indexes are out of range";
    indexStart = -5;
    indexEnd = 2;
    std::cout << "Testing getting the part of \"" << input4 << "\" from " << indexStart << " to " << indexEnd << " are: Expected: " << expectedOuput4 << " ==> ";
    try
    {
        mstring output4 = MStringManip::getFrom(input4, indexStart, indexEnd);
        std::cout << output4;
    }
    catch (std::out_of_range& e)
    {
        std::cout << e.what();
    }
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 5
    std::cout << "TEST 5" << std::endl;
    mstring input5 = "abcdefghi";
    mstring expectedOuput5 = "The start or end indexes are out of range";
    indexStart = 2;
    indexEnd = 10;
    std::cout << "Testing getting the part of \"" << input5 << "\" from " << indexStart << " to " << indexEnd << " are: Expected: " << expectedOuput5 << " ==> ";
    try
    {
        mstring output5 = MStringManip::getFrom(input5, indexStart, indexEnd);
        std::cout << output5;
    }
    catch (std::out_of_range& e)
    {
        std::cout << e.what();
    }
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 6
    std::cout << "TEST 6" << std::endl;
    mstring input6 = "abcdefghi";
    mstring expectedOuput6 = "The start or end indexes are out of range";
    indexStart = 10;
    indexEnd = 7;
    std::cout << "Testing getting the part of \"" << input6 << "\" from " << indexStart << " to " << indexEnd << " are: Expected: " << expectedOuput6 << " ==> ";
    try
    {
        mstring output6 = MStringManip::getFrom(input6, indexStart, indexEnd);
        std::cout << output6;
    }
    catch (std::out_of_range& e)
    {
        std::cout << e.what();
    }
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 7
    std::cout << "TEST 7" << std::endl;
    mstring input7 = "abcdefghi";
    mstring expectedOuput7 = "The start or end indexes are out of range";
    indexStart = 2;
    indexEnd = -2;
    std::cout << "Testing getting the part of \"" << input7 << "\" from " << indexStart << " to " << indexEnd << " are: Expected: " << expectedOuput7 << " ==> ";
    try
    {
        mstring output7 = MStringManip::getFrom(input7, indexStart, indexEnd);
        std::cout << output7;
    }
    catch (std::out_of_range& e)
    {
        std::cout << e.what();
    }
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 8
    std::cout << "TEST 8" << std::endl;
    mstring input8 = "abcdefghi";
    mstring expectedOuput8 = "";
    indexStart = 6;
    indexEnd = 5;
    std::cout << "Testing getting the part of \"" << input8 << "\" from " << indexStart << " to " << indexEnd << " are: Expected: " << expectedOuput8 << " ==> ";
    mstring output8 = MStringManip::getFrom(input8, indexStart, indexEnd);
    std::cout << output8;
    std::cout << std::endl;
    std::cout << std::endl;
}

void MStringManipTests::getReversedTests()
{
    //getReversed TESTS
    std::cout << "getReversed TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    mstring input1 = "abcdef";
    mstring expectedOuput1 = "fedcba";
    mstring output1 = MStringManip::getReverse(input1);
    std::cout << "Testing getting the reverse of \"" << input1 << "\". Expected: " << expectedOuput1 << " ==> " << output1;
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    mstring input2 = "a";
    mstring expectedOuput2 = "a";
    mstring output2 = MStringManip::getReverse(input2);
    std::cout << "Testing getting the reverse of \"" << input2 << "\". Expected: " << expectedOuput2 << " ==> " << output2;
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    mstring input3 = "";
    mstring expectedOuput3 = "";
    mstring output3 = MStringManip::getReverse(input3);
    std::cout << "Testing getting the reverse of \"" << input3 << "\". Expected: " << expectedOuput3 << " ==> " << output3;
    std::cout << std::endl;
    std::cout << std::endl;
}

void MStringManipTests::countOfTests()
{
    //countOf TESTS
    std::cout << "countOf TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    mstring input1 = "aab";
    mstring otherInput1 = "braaabppabaabbbbaabaabbaab";
    std::cout << "Testing how many times the string \"" << input1 << "\" is contained within \"" << otherInput1 << "\": Expected(5) ==> ";
    std::cout << MStringManip::countOf(otherInput1, input1);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    mstring input2 = "xx";
    mstring otherInput2 = "braaabppabaabbbbaabaabbaab";
    int startIndex2 = 0;
    int endIndex2 = 25;
    std::cout << "Testing how many times the string \"" << input2 << "\" is contained within \"" << otherInput2 << "\" from " << startIndex2 << " to " << endIndex2 << ": Expected(0) ==> ";
    std::cout << MStringManip::countOf(otherInput2, input2, startIndex2, endIndex2);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    mstring input3 = "(";
    mstring otherInput3 = "(())((()))";
    int startIndex3 = 5;
    int endIndex3 = 9;
    std::cout << "Testing how many times the string \"" << input3 << "\" is contained within \"" << otherInput3 << "\" from " << startIndex3 << " to " << endIndex3 << ": Expected(2) ==> ";
    std::cout << MStringManip::countOf(otherInput3, input3, startIndex3, endIndex3);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    char input4 = '(';
    mstring otherInput4 = "(())((()))";
    int startIndex4 = 5;
    int endIndex4 = 9;
    std::cout << "Testing how many times the mstring \'" << input4 << "\" is contained within \'" << otherInput4 << "\" from " << startIndex4 << " to " << endIndex4 << ": Expected(2) ==> ";
    std::cout << MStringManip::countOf(otherInput4, input4, startIndex4, endIndex4);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 5
    std::cout << "TEST 5" << std::endl;
    char input5 = '(';
    mstring otherInput5 = "(())((()))xxxx";
    int startIndex5 = 10;
    int endIndex5 = 13;
    std::cout << "Testing how many times the mstring \'" << input5 << "\" is contained within \'" << otherInput5 << "\" from " << startIndex5 << " to " << endIndex5 << ": Expected(0) ==> ";
    std::cout << MStringManip::countOf(otherInput5, input5, startIndex5, endIndex5);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 6
    std::cout << "TEST 6" << std::endl;
    char input6 = '(';
    mstring otherInput6 = "(())((()))xxxx";
    std::cout << "Testing how many times the mstring \'" << input6 << "\" is contained within \'" << otherInput6 << "\": Expected(5) ==> ";
    std::cout << MStringManip::countOf(otherInput6, input6);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 7
    std::cout << "TEST 7" << std::endl;
    mstring input7 = "";
    mstring otherInput7 = "(())((()))";
    std::cout << "Testing how many times the string \"" << input7 << "\" is contained within \"" << otherInput7 << "\": Expected(0) ==> ";
    std::cout << MStringManip::countOf(otherInput7, input7);
    std::cout << std::endl;
    std::cout << std::endl;
}

void MStringManipTests::countOfManyTests()
{
    //countOfMany TESTS
    std::cout << "countOfMany TESTS: " << std::endl << std::endl;

    //TEST 1
    std::cout << "TEST 1" << std::endl;
    mstring input1 = "aab";
    mstring otherInput1 = "braaabppabaabbbbaabaabbaab";
    std::cout << "Testing how many times the symbols of the strings \"" << input1 << "\" are contained within \"" << otherInput1 << "\": Expected(23) ==> ";
    std::cout << MStringManip::countOfMany(otherInput1, input1);
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 2
    std::cout << "TEST 2" << std::endl;
    mstring input2 = "";
    mstring otherInput2 = "braaabppabaabbbbaabaabbaab";
    std::cout << "Testing how many times the symbols of the strings \"" << otherInput2 << "\" is contained within \"" << input2 << "\": Expected: Throw Exception ==> ";
    try
    {
        std::cout << MStringManip::countOfMany(input2, otherInput2);
    }
    catch (...)
    {
        std::cout << "Throw Exception";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 3
    std::cout << "TEST 3" << std::endl;
    mstring input3 = "";
    mstring otherInput3 = "braaabppabaabbbbaabaabbaab";
    std::cout << "Testing how many times the symbols of the strings \"" << input3 << "\" is contained within \"" << otherInput3 << "\": Expected: Throw Exception ==> ";
    try
    {
        std::cout << MStringManip::countOfMany(otherInput3, input3);
    }
    catch (...)
    {
        std::cout << "Throw Exception";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 4
    std::cout << "TEST 4" << std::endl;
    mstring input4 = "br";
    mstring otherInput4 = "braaabppabaabbbbaabaabbaabssx";
    std::cout << "Testing how many times the symbols of the strings \"" << input4 << "\" is contained within \"" << otherInput4 << "\": Expected: 12 ==> "
        << MStringManip::countOfMany(otherInput4, input4);;
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 5
    std::cout << "TEST 5" << std::endl;
    /*const mstring* input5 = new const mstring* []
    {
        "bro",
            "orb",
            "bro"
    };*/
    mstring input5[]
    {
        "bro",
            "orb",
            "bro"
    };
    size_t arraySizeInput = 3;
    mstring otherInput5 = "brorbbrooorbrrborroorbro";
    std::cout << "Testing how many times the strings of the array of strings \"";
    printOutStringsFromArray((mstring*)input5, arraySizeInput);
    std::cout << "\" is contained within \"" << otherInput5 << "\": Expected: 6 ==> "
        << MStringManip::countOfMany(otherInput5, input5, arraySizeInput);;
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 6
    std::cout << "TEST 6" << std::endl;
    /*const mstring* input6 = new const mstring* []
    {
        "bro",
            "",
    };*/
    mstring input6[]
    {
        "bro",
            "",
    };
    arraySizeInput = 2;
    mstring otherInput6 = "brorbbrooorbrrborroorbro";
    std::cout << "Testing how many times the strings of the array of strings \"";
    printOutStringsFromArray(input6, arraySizeInput);
    std::cout << "\" is contained within \"" << otherInput6 << "\": Expected: 3 ==> "
        << MStringManip::countOfMany(otherInput6, input6, arraySizeInput);;
    std::cout << std::endl;
    std::cout << std::endl;

    //TEST 7
    std::cout << "TEST 7" << std::endl;
    const mstring* input7 = new mstring [0];
    arraySizeInput = 0;
    mstring otherInput7 = "brorbbrooorbrrborroorbro";
    std::cout << "Testing how many times the strings of the array of strings \"";
    printOutStringsFromArray(input7, arraySizeInput);
    std::cout << "\" is contained within \"" << otherInput7 << "\": Expected: Throw Exception ==> ";
    try
    {
        std::cout << MStringManip::countOfMany(otherInput7, input7, arraySizeInput);
    }
    catch (...)
    {
        std::cout << "Throw Exception";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    //Delete dynamic memory
    delete[] input7;

    //TEST 8
    std::cout << "TEST 8" << std::endl;
    /*const mstring* input8 = new const mstring* []
    {
        "Something",
            "Anything"
    };*/
    mstring input8[]
    {
        "Something",
            "Anything"
    };
    arraySizeInput = 2;
    mstring otherInput8 = "";
    std::cout << "Testing how many times the strings of the array of strings \"";
    printOutStringsFromArray(input8, arraySizeInput);
    std::cout << "\" is contained within \"" << otherInput8 << "\": Expected: Throw Exception ==> ";
    try
    {

        std::cout << MStringManip::countOfMany(otherInput8, input8, arraySizeInput);;
        std::cout << std::endl;
        std::cout << std::endl;
    }
    catch (...)
    {
        std::cout << "Throw Exception";
    }

    std::cout << std::endl;
    std::cout << std::endl;
}

void MStringManipTests::runTests()
{
    //splitByChar TESTS
    splitByCharTests();
    
    //splitByString TESTS
    splitByStringTests();
    
    //splitStringMany TESTS
    splitStringManyTests();

    //stringContains TESTS
    stringContainsTests();

    //replaceAll TESTS
    replaceAllTests();
    
    //replaceFirst TESTS
    replaceFirstTests();
    
    //replaceFrom TESTS
    replaceFromTests();
    
    //findIndex TESTS
    findIndexTests();
    
    //findIndexLast TESTS
    findIndexLastTests();
    
    //arraysOfStringsAreEqualTests TESTS
    arraysOfStringsAreEqualTests();
    
    //getUnique TESTS
    getUniqueTests();
    
    //getFrom TESTS
    getFromTests();
    
    //getReversed TESTS
    getReversedTests();
    
    //countOf TESTS
    countOfTests();
    
    //countOfMany TESTS
    countOfManyTests();
}
