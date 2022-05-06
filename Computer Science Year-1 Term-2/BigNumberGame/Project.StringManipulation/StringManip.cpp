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
    size_t sizeOfInput = strlen(input);
    size_t numberOfStrings = 1;
    for (size_t i = 0; i < sizeOfInput; i++)
    {
        if (input[i] == delim) numberOfStrings++;
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
        sizesOfStrings[sizeOfStringIndex]++;
        if (input[i] == delim)
        {
            sizeOfStringIndex++;
        }
        else if (i == sizeOfInput - 1)
        {
            sizesOfStrings[sizeOfStringIndex]++;
        }
    }

    //Init all of the strings and set their null terminator
    for (size_t i = 0; i < numberOfStrings; i++)
    {
        size_t stringLength = sizesOfStrings[i];
        arrayOfStrings[i] = new char[stringLength];
        if (stringLength > 0)
        {
            arrayOfStrings[i][sizesOfStrings[i] - 1] = '\0';
        }
        else
        {
            arrayOfStrings[i][0] = '\0';
        }
    }

    size_t currentStringIndex = 0;
    bool switchToPassword = false;
    size_t stringCharsIndexOffset = 0;
    for (size_t i = 0; i < sizeOfInput; i++)
    {
        if (input[i] == delim)
        {
            arrayOfStrings[currentStringIndex][i - stringCharsIndexOffset] = '\0';
            stringCharsIndexOffset = i + 1;
            currentStringIndex++;
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

bool StringManip::stringContainsInvalidChars(const char* text)
{
    for (size_t i = 0; i < strlen(text); i++)
    {
        char textChar = text[i];
        if (textChar < 0 || textChar >= 128) return true;
        if (stringContainsChar(GlobalConstants::FORDBIDDEN_SYMBOLS, textChar)) return true;
    }
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
                    i += y;
                    i--;
                    break;
                }
                if (i + y == strlen(text) - 1 && y + 1 < strlen(other))
                {
                    stringIsFound = false;
                    i += y;
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
    return false;
}

char* StringManip::concatStrings(const char** strings, size_t stringsCount)
{
    size_t concatStringLength = 0;
    for (size_t i = 0; i < stringsCount; i++)
    {
        concatStringLength += strlen(strings[i]);
    }

    char* concatString = new char[1];
    concatString[0] = '\0';

    for (size_t i = 0; i < stringsCount; i++)
    {

        strcat(concatString, strings[i]);
    }

    return concatString;
}
