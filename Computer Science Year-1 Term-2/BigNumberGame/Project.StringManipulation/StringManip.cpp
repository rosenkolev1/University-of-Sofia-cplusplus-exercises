#include "StringManip.h"
#include "..\Game.GlobalConstants\GlobalConstants.h"
#include <iostream>

char* StringManip::parseToString(int integer)
{
    if (integer == 0)
    {
        char* zeroDigit = new char[2];
        zeroDigit[0] = '0';
        zeroDigit[1] = '\0';
        return zeroDigit;
    }

    bool isNegativeInt = integer < 0;

    int integerCopy = integer;
    int digitsCount = 0;
    while (integerCopy != 0)
    {
        digitsCount++;
        integerCopy /= 10;
    }

    int charsCount = digitsCount + 1;
    if (isNegativeInt) charsCount++;

    char* parsedInt = new char[charsCount];
    parsedInt[charsCount - 1] = '\0';

    int positiveInteger = abs(integer);

    for (int i = charsCount - 2; i >= (isNegativeInt ? 1 : 0); i--)
    {
        int digit = positiveInteger % 10;
        parsedInt[i] = (char)digit + '0';
        positiveInteger /= 10;
    }

    if (isNegativeInt) parsedInt[0] = '-';

    return parsedInt;
}

char** StringManip::splitString(const char* input, char delim, size_t& sizeOfArray)
{
    return splitString(input, &delim, sizeOfArray);
}

char** StringManip::splitString(const char* input, const char* delim, size_t& sizeOfArray)
{
    //if the delim is empty, then just return an array of one string
    if (strlen(delim) == 0) return new char* [] {(char*)input};

    size_t sizeOfInput = strlen(input);
    size_t numberOfStrings = 1;
    for (size_t i = 0; i < sizeOfInput; i++)
    {
        if (input[i] == delim[0])
        {
            bool foundDelim = true;
            for (size_t y = 1; y < strlen(delim); y++)
            {
                if (input[i + y] != delim[y])
                {
                    foundDelim = false;
                    break;
                }
                if (i + y == strlen(input) - 1 && y + 1 < strlen(delim))
                {
                    foundDelim = false;
                    break;
                }
            }

            if (foundDelim)
            {
                //baaaa aa
                numberOfStrings++;
                i += strlen(delim) - 1;
            }
        }
    }

    char** arrayOfStrings = new char* [numberOfStrings];
    size_t* sizesOfStrings = new size_t[numberOfStrings];

    //Init sizesOfStrings
    for (size_t i = 0; i < numberOfStrings; i++)
    {
        sizesOfStrings[i] = 0;
    }

    //Get the lengths of all the strings
    size_t sizeOfStringIndex = 0;
    for (size_t i = 0; i < sizeOfInput; i++)
    {
        //sizesOfStrings[sizeOfStringIndex]++;
        if (input[i] == delim[0])
        {
            bool foundDelim = true;
            for (size_t y = 1; y < strlen(delim); y++)
            {
                if (input[i + y] != delim[y])
                {
                    foundDelim = false;
                    break;
                }
                if (i + y == strlen(input) - 1 && y + 1 < strlen(delim))
                {
                    foundDelim = false;
                    break;
                }
            }

            if (foundDelim)
            {
                sizeOfStringIndex++;
                i += strlen(delim) - 1;
            }
            //If it failed the search for a match, then add the character to the current string length
            else
            {
                sizesOfStrings[sizeOfStringIndex]++;
            }
        }
        else
        {
            sizesOfStrings[sizeOfStringIndex]++;
        }
    }

    //Init all of the strings and set their null terminator
    for (size_t i = 0; i < numberOfStrings; i++)
    {
        size_t stringLength = sizesOfStrings[i];
        arrayOfStrings[i] = new char[stringLength + 1];
        arrayOfStrings[i][stringLength] = '\0';
    }

    size_t currentStringIndex = 0;
    size_t stringCharsIndexOffset = 0;

    //Split the string
    for (size_t i = 0; i < sizeOfInput; i++)
    {
        if (input[i] == delim[0])
        {
            bool foundDelim = true;
            for (size_t y = 1; y < strlen(delim); y++)
            {
                if (input[i + y] != delim[y])
                {
                    foundDelim = false;
                    break;
                }
                if (i + y == strlen(input) - 1 && y + 1 < strlen(delim))
                {
                    foundDelim = false;
                    break;
                }
            }

            if (foundDelim)
            {
                arrayOfStrings[currentStringIndex][i - stringCharsIndexOffset] = '\0';
                i += strlen(delim) - 1;
                stringCharsIndexOffset = i + 1;
                currentStringIndex++;
            }
            //If it failed the search for a match, then add the character to the current string
            else
            {
                arrayOfStrings[currentStringIndex][i - stringCharsIndexOffset] = input[i];
            }
        }
        else
        {
            arrayOfStrings[currentStringIndex][i - stringCharsIndexOffset] = input[i];
        }
    }

    delete[] sizesOfStrings;
    sizeOfArray = numberOfStrings;
    return arrayOfStrings;
}

bool StringManip::stringContainsInvalidChars(const char* text, const char* invalidChars)
{
    for (size_t i = 0; i < strlen(text); i++)
    {
        char textChar = text[i];
        if (textChar < 0 || textChar >= 128) return true;
        if (stringContainsChar(invalidChars, textChar)) return true;
    }

    //If we get to here, that means that the string passed the test and doesn't contain invalid chars.
    return false;
}

bool StringManip::stringContainsChar(const char* text, const char symbol)
{
    for (size_t i = 0; i < strlen(text); i++)
    {
        char textChar = text[i];
        if (textChar == symbol) return true;
    }
    return false;
}

bool StringManip::stringContains(const char* text, const char* other)
{
    for (size_t i = 0; i < strlen(text); i++)
    {
        if (text[i] == other[0])
        {
            bool stringIsFound = true;
            for (size_t y = 1; y < strlen(other); y++)
            {
                if (text[i + y] != other[y])
                {
                    stringIsFound = false;
                    break;
                }
                if (i + y == strlen(text) - 1 && y + 1 < strlen(other))
                {
                    stringIsFound = false;
                    break;
                }
            }
            if (stringIsFound) return true;
        }
    }

    //If we get to here, then the string hasn't been found
    return false;
}

void StringManip::deleteArrayOfStrings(char** text, size_t arrayCount)
{
    for (size_t i = 0; i < arrayCount; i++)
    {
        if (strcmp(text[i], "") != 0)
        {
            //Debug
            char somethingDebug[1000];
            strcpy(somethingDebug, text[i]);
            delete[] text[i];
        }
        //If the text[i] is pointing to an empty string, then delete or delete[] on text[i] throws an error for some reason.
        //Not sure if memory is allocated for empty strings. This may be a memory leak.
    }
    delete[] text;
}

bool StringManip::stringStartsWith(const char* text, const char* other)
{
    if (strlen(text) < strlen(other)) return false;

    for (size_t i = 0; i < strlen(other); i++)
    {
        if (text[i] != other[i]) return false;
    }

    //If we get to here, then the text starts with other
    return true;
}

bool StringManip::stringEndsWith(const char* text, const char* other)
{
    if (strlen(text) < strlen(other)) return false;

    size_t otherIndex = 0;
    for (size_t i = strlen(text) - strlen(other); i < strlen(text); i++)
    {
        if (text[i] != other[otherIndex++]) return false;
    }

    //If we get to here, then the text starts with other
    return true;
}

char* StringManip::concatStrings(const char** strings, size_t stringsCount)
{
    size_t concatStringLength = 0;
    for (size_t i = 0; i < stringsCount; i++)
    {
        concatStringLength += strlen(strings[i]);
    }

    char* concatString = new char[concatStringLength + 1]{'\0'};

    for (size_t i = 0; i < stringsCount; i++)
    {

        strcat(concatString, strings[i]);
    }

    return concatString;
}

char* StringManip::replaceAll(const char* text, const char* replaced, const char* replacement)
{
    size_t countOfStrings = 0;
    char** textStrings = splitString(text, replaced, countOfStrings);
    size_t finalTextStringsCount = countOfStrings * 2 - 1;
    char** finalTextStrings = new char*[finalTextStringsCount];
    size_t textStringsIndex = 0;
    for (size_t i = 0; i < finalTextStringsCount; i++)
    {
        if (i % 2 == 0)
        {
            finalTextStrings[i] = textStrings[textStringsIndex++];
        }
        else
        {
            finalTextStrings[i] = new char[strlen(replacement) + 1];
            strcpy(finalTextStrings[i], replacement);
        }
    }
    char* finalText = concatStrings((const char**)finalTextStrings, finalTextStringsCount);

    //Delete dynamic memory
    for (size_t i = 0; i < finalTextStringsCount; i++)
    {
        delete[] finalTextStrings[i];
    }
    delete[] finalTextStrings;

    return finalText;
}

int StringManip::findIndex(const char* text, const char* searchText)
{
    int searchTextFoundIndex = 0;
    for (size_t i = 0; i < strlen(text); i++)
    {
        if (text[i] == searchText[0])
        {
            bool stringIsFound = true;
            searchTextFoundIndex = i;
            for (size_t y = 1; y < strlen(searchText); y++)
            {
                if (text[i + y] != searchText[y])
                {
                    stringIsFound = false;
                    searchTextFoundIndex = -1;
                    break;
                }
                if (i + y == strlen(text) - 1 && y + 1 < strlen(searchText))
                {
                    stringIsFound = false;
                    searchTextFoundIndex = -1;
                    break;
                }
            }
            if (stringIsFound) return searchTextFoundIndex;
        }
    }

    //If we get to here, then the string hasn't been found
    return -1;
}

int StringManip::findIndex(const char* text, const char* searchText, size_t startIndex, size_t endIndex)
{
    if (endIndex >= strlen(text)) throw "The end index is outside the range of the text";
    if (startIndex > endIndex) return -1;
    char* textPart = new char[endIndex - startIndex + 2];
    textPart[endIndex - startIndex + 1] = '\0';
    for (size_t i = startIndex; i <= endIndex; i++)
    {
        textPart[i - startIndex] = text[i];
    }

    int firstIndex = findIndex(textPart, searchText);
    //Delete dynamic memory
    delete[] textPart;
    return firstIndex > -1 ? firstIndex + startIndex : -1;
}

int StringManip::findIndexLast(const char* text, const char* searchText)
{
    int searchTextFoundIndex = 0;
    int searchTextFoundLastIndex = 0;
    bool searchTextHasBeenFound = false;
    for (size_t i = 0; i < strlen(text); i++)
    {
        if (text[i] == searchText[0])
        {
            bool stringIsFound = true;
            searchTextFoundLastIndex = searchTextFoundIndex;
            searchTextFoundIndex = i;
            for (size_t y = 1; y < strlen(searchText); y++)
            {
                if (text[i + y] != searchText[y])
                {
                    stringIsFound = false; 
                    break;
                }
                if (i + y == strlen(text) - 1 && y + 1 < strlen(searchText))
                {
                    stringIsFound = false;
                    break;
                }
            }
            if (stringIsFound && !searchTextHasBeenFound) searchTextHasBeenFound = true;
            else if (!stringIsFound && !searchTextHasBeenFound) searchTextFoundIndex = -1;
            else if (!stringIsFound && searchTextHasBeenFound) searchTextFoundIndex = searchTextFoundLastIndex;
        }
    }

    // If we get -1, then the searchText wasn't found within text
    return searchTextFoundIndex;
}

int StringManip::findIndexLast(const char* text, const char* searchText, size_t startIndex, size_t endIndex)
{
    if (endIndex >= strlen(text)) throw "The end index is outside the range of the text";
    if (startIndex > endIndex) return -1;

    char* textPart = new char[endIndex - startIndex + 2];
    textPart[endIndex - startIndex + 1] = '\0';
    for (size_t i = startIndex; i <= endIndex; i++)
    {
        textPart[i - startIndex] = text[i];
    }

    int lastIndex = findIndexLast(textPart, searchText);
    //Delete dynamic memory
    delete[] textPart;
    return lastIndex > -1 ? lastIndex + startIndex : -1;
}

int StringManip::countOf(const char* text, const char* searchText, size_t startIndex, size_t endIndex)
{
    if (endIndex >= strlen(text)) throw "The end index is outside the range of the text";
    if (startIndex > endIndex) return 0;

    size_t searchTextFoundCounter = 0;
    bool searchTextHasBeenFound = false;

    for (size_t i = startIndex; i <= endIndex; i++)
    {
        if (text[i] == searchText[0])
        {
            bool stringIsFound = true;
            for (size_t y = 1; y < strlen(searchText); y++)
            {
                if (text[i + y] != searchText[y])
                {
                    stringIsFound = false;
                    break;
                }
                if (i + y == strlen(text) - 1 && y + 1 < strlen(searchText))
                {
                    stringIsFound = false;
                    break;
                }
            }
            if (stringIsFound)
            {
                searchTextFoundCounter++;
            }
        }
    }

    return searchTextFoundCounter;
}
