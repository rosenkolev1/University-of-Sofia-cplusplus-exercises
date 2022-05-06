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
    //size_t sizeOfInput = strlen(input);
    //size_t numberOfStrings = 1;
    //for (size_t i = 0; i < sizeOfInput; i++)
    //{
    //    if (input[i] == delim) numberOfStrings++;
    //}

    //char** arrayOfStrings = new char* [numberOfStrings];
    //size_t* sizesOfStrings = new size_t[numberOfStrings];

    ////Init sizesOfStrings
    //for (size_t i = 0; i < numberOfStrings; i++)
    //{
    //    sizesOfStrings[i] = 0;
    //}

    ////Get the lengths of all the strings
    //size_t sizeOfStringIndex = 0;
    //for (size_t i = 0; i < sizeOfInput; i++)
    //{
    //    sizesOfStrings[sizeOfStringIndex]++;
    //    if (input[i] == delim)
    //    {
    //        sizeOfStringIndex++;
    //    }
    //    else if (i == sizeOfInput - 1)
    //    {
    //        sizesOfStrings[sizeOfStringIndex]++;
    //    }
    //}

    ////Init all of the strings and set their null terminator
    //for (size_t i = 0; i < numberOfStrings; i++)
    //{
    //    size_t stringLength = sizesOfStrings[i];
    //    arrayOfStrings[i] = new char[stringLength];
    //    if (stringLength > 0)
    //    {
    //        arrayOfStrings[i][sizesOfStrings[i] - 1] = '\0';
    //    }
    //    else
    //    {
    //        arrayOfStrings[i][0] = '\0';
    //    }
    //}

    //size_t currentStringIndex = 0;
    //size_t stringCharsIndexOffset = 0;
    //for (size_t i = 0; i < sizeOfInput; i++)
    //{
    //    if (input[i] == delim)
    //    {
    //        arrayOfStrings[currentStringIndex][i - stringCharsIndexOffset] = '\0';
    //        stringCharsIndexOffset = i + 1;
    //        currentStringIndex++;
    //    }
    //    else
    //    {
    //        arrayOfStrings[currentStringIndex][i - stringCharsIndexOffset] = input[i];
    //    }
    //}

    //delete[] sizesOfStrings;
    //sizeOfArray = numberOfStrings;
    //return arrayOfStrings;
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

    //aaab aab
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

    // 12345+- +-
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

    char* concatString = new char[1];
    concatString[0] = '\0';

    for (size_t i = 0; i < stringsCount; i++)
    {

        strcat(concatString, strings[i]);
    }

    return concatString;
}

void StringManip::replaceAll(char* text, const char* replaced, const char* replacement)
{
    //size_t numberOfReplacements = 0;
    //size_t* indexesOfOccurences = new size_t[strlen(text)];
    //char* newText = new char[strlen(text) + 1];
    //strcpy(newText, text);
    //while (true)
    //{
    //    size_t indexOfOccurence = findIndex(newText, replaced);
    //
    //    //If no more instances of replacement are found, then break out of the loop
    //    if (indexOfOccurence == -1) break;
    //
    //    indexesOfOccurences[numberOfReplacements++] = indexOfOccurence;
    //
    //    //Start looking for occurences from the position of the last found occurence
    //    char* newTextCopy = new char[strlen(text) + 1];
    //    size_t newTextCopyIndex = 0;
    //    for (size_t i = indexOfOccurence + strlen(replaced); i < strlen(text); i++)
    //    {
    //        newTextCopy[newTextCopyIndex] = newText[i];
    //    }
    //    delete[] newText;
    //    newText = newTextCopy;
    //}    
    //
    //char** textStrings = new char*[numberOfReplacements + ];

    size_t countOfStrings = 0;
    char** textStrings = splitString(text, replaced, countOfStrings);
    size_t textStringsCounter = 0;
    char** finalTextStrings = new char* [countOfStrings * 2 - 1];
    size_t finalTextStringsCount = countOfStrings * 2 - 1;

    for (size_t i = 0; i < finalTextStringsCount; i++)
    {
        //Here you add the part that won't be replaced
        if (i % 2 == 0)
        {
            finalTextStrings[i] = textStrings[textStringsCounter++];
        }
        //Here you add the replacement
        else
        {
            strcpy(finalTextStrings[i], replacement);
        }
    }

    char* finalText = concatStrings((const char**)finalTextStrings, finalTextStringsCount);
    //Delete old text and replace it with the new text
    delete[] text;
    text = new char[strlen(finalText) + 1];
    strcpy(text, finalText);

    //Take care of dynamic memory
    for (size_t i = 0; i < finalTextStringsCount; i++)
    {
        delete[] finalTextStrings[i];
    }
    delete[] finalTextStrings;
    delete[] finalText;

    //char* newText = new char[strlen(text) + 1];
    //size_t newTextLength = strlen(text);
    //size_t replacementLength = strlen(replacement);
    //size_t replacedLength = strlen(replaced);
    //strcpy(newText, text);
    //while (stringContains(newText, replaced))
    //{
    //    size_t newText
    //    size_t indexOfReplaced = findIndex(newText, replaced);
    //    size_t newTextIndex = indexOfReplaced;

    //    //Replace the first occurance of replaced with the replacement
    //    for (size_t i = 0; i < replacementLength; i++)
    //    {
    //        //If the capacity of the newText runs out, then increase it
    //        if (newTextIndex == newTextLength)
    //        {
    //            newTextLength *= 2;
    //            char* newTextCopy = new char[newTextLength + 1];
    //            strcpy(newTextCopy, newText);
    //            delete[] newText;
    //            newText = newTextCopy;
    //        }
    //        newText[newTextIndex++] = replacement[i];
    //    }

    //    //Fill in the rest of the text afterwards
    //    for (size_t i = indexOfReplaced + replacedLength; i < ; i++)
    //    {

    //    }
    //}
}

size_t StringManip::findIndex(char* text, const char* searchText)
{
    size_t searchTextFoundIndex = 0;
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
                    i += y;
                    i--;
                    break;
                }
                if (i + y == strlen(text) - 1 && y + 1 < strlen(searchText))
                {
                    stringIsFound = false;
                    searchTextFoundIndex = -1;
                    i += y;
                    break;
                }
            }
            if (stringIsFound) return searchTextFoundIndex;
        }
    }

    //If we get to here, then the string hasn't been found
    return -1;
}
