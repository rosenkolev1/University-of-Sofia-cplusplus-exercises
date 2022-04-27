#include "ConsoleSystem.h"
#include "..\Game.GlobalConstants\GlobalConstants.h"
#include <iostream>

char** ConsoleSystem::splitString(const char* input, char delim, size_t& sizeOfArray)
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

    //DEBUG SHIT
    /*size_t sizeOne = sizesOfStrings[0];
    size_t sizeTwo = sizesOfStrings[1];*/

    //Init all of the strings and set their null terminator
    for (size_t i = 0; i < numberOfStrings; i++)
    {
        size_t stringLength = sizesOfStrings[i];
        arrayOfStrings[i] = new char[stringLength];
        if (stringLength > 0 )
        {
            arrayOfStrings[i][sizesOfStrings[i] - 1] = '\0';
        }
        else
        {
            arrayOfStrings[i][0] = '\0';
        }
    }

    size_t currentStringIndex= 0;
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

bool ConsoleSystem::stringContainsInvalidChars(const char* text)
{
    for (size_t i = 0; i < strlen(text); i++)
    {
        char textChar = text[i];
        if (textChar < 0 || textChar >= 128) return true;
        if (stringContainsChar(GlobalConstants::FORDBIDDEN_SYMBOLS, textChar)) return true;
    }
}

bool ConsoleSystem::stringContainsChar(const char* text, const char symbol)
{
    for (size_t i = 0; i < strlen(text); i++)
    {
        char textChar = text[i];
        if (textChar == symbol) return true;
    }
    return false;
}

void ConsoleSystem::deleteArrayOfStrings(char** text, size_t arrayCount)
{
    for (size_t i = 0; i < arrayCount; i++)
    {
        if (strcmp(text[i], "") != 0)
        {
            delete[] text[i];
        }
        //If the text[i] is pointing to an empty string, then delete or delete[] on text[i] throws an error for some reason.
        //Not sure if memory is allocated for empty strings. This may be a memory leak.
    }
    delete[] text;
}
