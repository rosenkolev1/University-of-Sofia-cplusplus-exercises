#include "MStringManip.h"

mstring MStringManip::parseToString(int integer)
{
    if (integer == 0)
    {
        return mstring("0");
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

    mstring parsedInt;
    int positiveInteger = abs(integer);

    for (int i = charsCount - 2; i >= (isNegativeInt ? 1 : 0); i--)
    {
        int digit = positiveInteger % 10;
        parsedInt.push_front((char)digit + '0');
        positiveInteger /= 10;
    }

    if (isNegativeInt) parsedInt.push_front('-');

    return parsedInt;
}

mstring* MStringManip::splitString(const mstring& input, char delim, size_t& sizeOfArray)
{
    mstring* stringResult = splitString(input, (mstring)delim, sizeOfArray);

    return stringResult;
}

mstring* MStringManip::splitString(const mstring& input, const mstring& delim, size_t& sizeOfArray)
{
    //if the delim is empty, then just return an array of one string
    if (delim.getSize() == 0)
    {
        mstring* newArray = new mstring[1]{""};
        return newArray;
    }

    size_t sizeOfInput = input.getSize();
    size_t numberOfStrings = 1;
    for (size_t i = 0; i < sizeOfInput; i++)
    {
        if (input[i] == delim[0])
        {
            bool foundDelim = true;
            if (sizeOfInput - i < delim.getSize()) foundDelim = false;
            else 
            {
                for (size_t y = 1; y < delim.getSize(); y++)
                {
                    if (i + y >= input.getSize() - 1 && y + 1 < delim.getSize())
                    {
                        foundDelim = false;
                        break;
                    }
                    if (input[i + y] != delim[y])
                    {
                        foundDelim = false;
                        break;
                    }
                }
            }

            if (foundDelim)
            {
                numberOfStrings++;
                i += delim.getSize() - 1;
            }
        }
    }

    mstring* arrayOfStrings = new mstring [numberOfStrings];

    size_t currentStringIndex = 0;
    size_t delimStartIndex = 0;
    size_t delimEndIndex = 0;
    mstring modifiedInput = input;

    //Split the string
    for (size_t i = 0; i < modifiedInput.getSize(); i++)
    {
        if (modifiedInput[i] == delim[0])
        {
            bool foundDelim = true;
            delimStartIndex = i;
            delimEndIndex = delimStartIndex + delim.getSize() - 1;
            if (modifiedInput.getSize() - i < delim.getSize()) foundDelim = false;
            else
            {
                for (size_t y = 1; y < delim.getSize(); y++)
                {
                    if (i + y >= modifiedInput.getSize() - 1 && y + 1 < delim.getSize())
                    {
                        foundDelim = false;
                        break;
                    }
                    if (modifiedInput[i + y] != delim[y])
                    {
                        foundDelim = false;
                        break;
                    }
                }
            }

            if (foundDelim)
            {
                arrayOfStrings[currentStringIndex] = (delimStartIndex > 0 ? MStringManip::getFrom(modifiedInput, 0, delimStartIndex - 1) : "");
                modifiedInput = MStringManip::replaceFrom(modifiedInput, "", 0, delimEndIndex);
                i = -1;
                currentStringIndex++;
            }
        }
    }
    arrayOfStrings[currentStringIndex++] = modifiedInput;

    sizeOfArray = numberOfStrings;
    return arrayOfStrings;
}

mstring* MStringManip::splitStringMany(const mstring& input, const mstring& delims, size_t& sizeOfArray)
{
    mstring* delimsStringArray = new mstring[delims.getSize()];

    for (size_t i = 0; i < delims.getSize(); i++)
    {
        delimsStringArray[i] = delims[i];
    }

    mstring* splitInput = splitStringMany(input, delimsStringArray, delims.getSize(), sizeOfArray);

    delete[] delimsStringArray;

    return splitInput;
}

mstring* MStringManip::splitStringMany(const mstring& input, const mstring* delims, size_t sizeOfDelimsArrays, size_t& sizeOfArray)
{
    //If the sizeOfDelimsArray == 0 or if the input is an empty string, then just return the input
    if (sizeOfDelimsArrays == 0 || input.getSize() == 0)
    {
        mstring* splitInput = new mstring[1];
        splitInput[0] = input;
        sizeOfArray = 1;
        return splitInput;
    }

    sizeOfArray = MStringManip::countOfMany(input, delims, sizeOfDelimsArrays) + 1;
    mstring* finalSplitInput = new mstring [sizeOfArray];
    size_t finalSplitInputIndex = 0;

    //For each word in delims, check where it's first occurance is. Split by the earliest occurance, then jump in the iteration by the length of the delim string.
    size_t startIndexSearch = 0;
    size_t endIndexSearch = input.getSize() - 1;

    while (true)
    {
        mstring earliestOccuranceWord = delims[0];
        int earliestOccuranceIndex = MStringManip::findIndex(input, earliestOccuranceWord, startIndexSearch, endIndexSearch);

        for (size_t i = 1; i < sizeOfDelimsArrays; i++)
        {
            const mstring& delim = delims[i];
            int earliestOccuranceIndexOfDelim = MStringManip::findIndex(input, delim, startIndexSearch, endIndexSearch);

            if ((earliestOccuranceIndexOfDelim < earliestOccuranceIndex && earliestOccuranceIndex > -1 && earliestOccuranceIndexOfDelim > -1)
                || (earliestOccuranceIndex == -1 && earliestOccuranceIndexOfDelim > -1))
            {
                earliestOccuranceIndex = earliestOccuranceIndexOfDelim;
                earliestOccuranceWord = delim;
            }
        }

        //If we run out of splitters, then get the last remaining split part of the string and break out of the loop
        if (earliestOccuranceIndex == -1)
        {
            //If there are no characters left to take after the last delim, then take an empty string
            size_t lastSplitPartIndex = startIndexSearch;
            if (lastSplitPartIndex > input.getSize() - 1 && lastSplitPartIndex > 0)
            {
                finalSplitInput[finalSplitInputIndex] = "";
                finalSplitInputIndex++;

                break;
            }

            //Get the split part of the input and store it in the final split string array
            mstring splitInput;
            for (size_t i = 0; i < input.getSize() - lastSplitPartIndex; i++)
            {
                splitInput += input[i + lastSplitPartIndex];
            }
            //splitInput += '\0';

            finalSplitInput[finalSplitInputIndex++] = splitInput;

            break;
        }

        //Get the split part of the input and store it in the final split string array
        mstring splitInput;
        for (size_t i = 0; i < earliestOccuranceIndex - startIndexSearch; i++)
        {
            splitInput += input[i + startIndexSearch];
        }

        //splitInput += '\0';

        finalSplitInput[finalSplitInputIndex++] = splitInput;

        //Change the starting point of the search in input for splitters
        startIndexSearch = earliestOccuranceIndex + earliestOccuranceWord.getSize();
    }

    sizeOfArray = finalSplitInputIndex;
    return finalSplitInput;
}

bool MStringManip::stringContainsInvalidChars(const mstring& text, const mstring& invalidChars)
{
    for (size_t i = 0; i < text.getSize(); i++)
    {
        char textChar = text[i];
        if (stringContains(invalidChars, textChar)) return true;
    }

    //If we get to here, that means that the string passed the test and doesn't contain invalid chars.
    return false;
}

bool MStringManip::stringContains(const mstring& text, const char other)
{
    for (size_t i = 0; i < text.getSize(); i++)
    {
        char textChar = text[i];
        if (textChar == other) return true;
    }
    return false;
}

bool MStringManip::stringContains(const mstring& text, const mstring& other)
{
    for (size_t i = 0; i < text.getSize(); i++)
    {
        if (text[i] == other[0])
        {
            bool stringIsFound = true;
            for (size_t y = 1; y < other.getSize(); y++)
            {
                if (text[i + y] != other[y])
                {
                    stringIsFound = false;
                    break;
                }
                if (i + y == text.getSize() - 1 && y + 1 < other.getSize())
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

void MStringManip::deleteArrayOfStrings(mstring* text, size_t arrayCount)
{
    delete[] text;
}

bool MStringManip::stringStartsWith(const mstring& text, const mstring& other)
{
    if (text.getSize() < other.getSize()) return false;

    for (size_t i = 0; i < other.getSize(); i++)
    {
        if (text[i] != other[i]) return false;
    }

    //If we get to here, then the text starts with other
    return true;
}

bool MStringManip::stringEndsWith(const mstring& text, const mstring& other)
{
    if (text.getSize() < other.getSize()) return false;

    size_t otherIndex = 0;
    for (size_t i = text.getSize() - other.getSize(); i < text.getSize(); i++)
    {
        if (text[i] != other[otherIndex++]) return false;
    }

    //If we get to here, then the text starts with other
    return true;
}

mstring MStringManip::concatStrings(const mstring* strings, size_t stringsCount)
{
    mstring concatString;

    for (size_t i = 0; i < stringsCount; i++)
    {
        concatString += strings[i];
    }

    return concatString;
}

mstring MStringManip::replaceAll(const mstring& text, const mstring& replaced, const mstring& replacement)
{
    size_t countOfStrings = 0;
    mstring* textStrings = splitString(text, replaced, countOfStrings);
    size_t finalTextStringsCount = countOfStrings * 2 - 1;
    mstring* finalTextStrings = new mstring[finalTextStringsCount];
    size_t textStringsIndex = 0;
    for (size_t i = 0; i < finalTextStringsCount; i++)
    {
        if (i % 2 == 0)
        {
            finalTextStrings[i] = textStrings[textStringsIndex++];
        }
        else
        {
            finalTextStrings[i] = replacement;
        }
    }
    mstring finalText = concatStrings(finalTextStrings, finalTextStringsCount);

    //Delete dynamic memory
    delete[] finalTextStrings;
    delete[] textStrings;

    return finalText;
}

mstring MStringManip::replaceFirst(const mstring& text, const mstring& replaced, const mstring& replacement)
{
    size_t countOfStrings = 0;
    mstring* textStrings = splitString(text, replaced, countOfStrings);
    size_t finalTextStringsCount = countOfStrings * 2 - 1;
    mstring* finalTextStrings = new mstring[finalTextStringsCount];
    size_t textStringsIndex = 0;

    if (finalTextStringsCount >= 2)
    {
        finalTextStrings[0] = textStrings[textStringsIndex++];
        finalTextStrings[1] = replacement;

        for (size_t i = 2; i < finalTextStringsCount; i++)
        {
            if (i % 2 == 0)
            {
                finalTextStrings[i] = textStrings[textStringsIndex++];
            }
            else
            {
                finalTextStrings[i] = replaced;
            }
        }
    }
    //If we get here, then there is nothing to replace so we return a copy of the text param
    else
    {
        return text;
    }

    mstring finalText = concatStrings(finalTextStrings, finalTextStringsCount);

    //Delete dynamic memory
    delete[] finalTextStrings;

    return finalText;
}

mstring MStringManip::replaceFrom(const mstring& text, const mstring& replacement, size_t startIndex)
{
    return replaceFrom(text, replacement, startIndex, text.getSize() - 1);
}

mstring MStringManip::replaceFrom(const mstring& text, const mstring& replacement, size_t startIndex, size_t endIndex)
{
    if (startIndex > endIndex) throw "Start index is higher than end index loool!";
    if (startIndex > text.getSize() - 1) throw "Start index is higher than the length of the text";

    size_t newTextSize = text.getSize() - (endIndex - startIndex + 1) + replacement.getSize();

    mstring newText;
    for (size_t i = 0; i < startIndex; i++)
    {
        newText += text[i];
    }
    for (size_t i = 0; i < replacement.getSize(); i++)
    {
        newText += replacement[i];
    }
    for (size_t i = endIndex + 1; i < text.getSize(); i++)
    {
        newText += text[i];
    }

    return newText;
}

int MStringManip::findIndex(const mstring& text, const mstring& searchText)
{
    return findIndex(text, searchText, 0, text.getSize() - 1);
}

int MStringManip::findIndex(const mstring& text, const mstring& searchText, size_t startIndex, size_t endIndex)
{
    if (endIndex >= text.getSize()) throw std::out_of_range("The end index is outside the range of the text");
    if (startIndex > endIndex) return -1;
    size_t sizeOfTextPart = endIndex - startIndex + 1;

    int searchTextFoundIndex = -1;
    for (size_t i = startIndex; i <= endIndex; i++)
    {
        if (text[i] == searchText[0])
        {
            bool stringIsFound = true;
            searchTextFoundIndex = i;
            if (sizeOfTextPart - (i - startIndex) < searchText.getSize()) stringIsFound = false;
            else
            {
                for (size_t y = 1; y < searchText.getSize(); y++)
                {
                    if (i + y >= text.getSize() - 1 && y + 1 < searchText.getSize())
                    {
                        stringIsFound = false;
                        break;
                    }
                    if (text[i + y] != searchText[y])
                    {
                        stringIsFound = false;
                        break;
                    }
                }
            }

            if (stringIsFound) return searchTextFoundIndex;
            else searchTextFoundIndex = -1;
        }
    }

    //If we get to here, then the string hasn't been found
    return searchTextFoundIndex;
}

int MStringManip::findIndexLast(const mstring& text, const mstring& searchText)
{
    return findIndexLast(text, searchText, 0, text.getSize() - 1);
}

int MStringManip::findIndexLast(const mstring& text, const mstring& searchText, size_t startIndex, size_t endIndex)
{
    if (endIndex >= text.getSize()) throw "The end index is outside the range of the text";
    if (startIndex > endIndex) return -1;

    mstring reverseText = MStringManip::getReverse(text);
    mstring reverseSearchText = MStringManip::getReverse(searchText);

    int deltaFromStart = startIndex;
    int deltaFromEnd = text.getSize() - 1 - endIndex;
    int indexWhenReversed = findIndex(reverseText, reverseSearchText, deltaFromEnd, text.getSize() - 1 - deltaFromStart);
    int correctIndex = text.getSize() - 1 - indexWhenReversed - searchText.getSize() + 1 ;

    return indexWhenReversed > -1 ? correctIndex : -1;
}

size_t MStringManip::countOf(const mstring& text, char symbol)
{
    return countOf(text, symbol, 0, text.getSize() - 1);
}

size_t MStringManip::countOf(const mstring& text, char symbol, size_t startIndex, size_t endIndex)
{
    size_t countOfSymbol = 0;
    for (size_t i = startIndex; i <= endIndex; i++)
    {
        char textChar = text[i];
        if (textChar == symbol) countOfSymbol++;
    }
    return countOfSymbol;
}

size_t MStringManip::countOf(const mstring& text, const mstring& searchText)
{
    return countOf(text, searchText, 0, text.getSize() - 1);
}

size_t MStringManip::countOf(const mstring& text, const mstring& searchText, size_t startIndex, size_t endIndex)
{
    if (endIndex >= text.getSize()) throw "The end index is outside the range of the text";
    if (startIndex > endIndex) return 0;

    size_t searchTextFoundCounter = 0;
    bool searchTextHasBeenFound = false;

    for (size_t i = startIndex; i <= endIndex; i++)
    {
        if (text[i] == searchText[0])
        {
            bool stringIsFound = true;
            if (text.getSize() - i < searchText.getSize()) stringIsFound = false;
            else
            {
                for (size_t y = 1; y < searchText.getSize(); y++)
                {
                    if (i + y >= text.getSize() - 1 && y + 1 < searchText.getSize())
                    {
                        stringIsFound = false;
                        break;
                    }
                    if (text[i + y] != searchText[y])
                    {
                        stringIsFound = false;
                        break;
                    }
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

size_t MStringManip::countOfMany(const mstring& text, const mstring& searchText)
{
    return countOfMany(text, searchText, 0, text.getSize() - 1);
}

size_t MStringManip::countOfMany(const mstring& text, const mstring& searchText, size_t startIndex, size_t endIndex)
{
    if (endIndex >= text.getSize()) throw "The end index is outside the range of the text";
    if (searchText.getSize() == 0) throw "The search text is empty";

    //Get the unique symbols of searchText.
    mstring uniqueSymbolsFromSearchText = getUnique(searchText);

    size_t countOfAllSymbols = 0;

    for (size_t i = 0; i < uniqueSymbolsFromSearchText.getSize(); i++)
    {
        char searchTextSymbol = uniqueSymbolsFromSearchText[i];
        size_t countOfSymbol = countOf(text, searchTextSymbol, startIndex, endIndex);
        countOfAllSymbols += countOfSymbol;
    }

    return countOfAllSymbols;
}

size_t MStringManip::countOfMany(const mstring& text, const mstring* searchStrings, size_t searchStringsSize)
{
    return countOfMany(text, searchStrings, searchStringsSize, 0, text.getSize() - 1);
}

size_t MStringManip::countOfMany(const mstring& text, const mstring* searchStrings, size_t searchStringsSize, size_t startIndex, size_t endIndex)
{
    if (endIndex >= text.getSize()) throw "The end index is outside the range of the text";

    //Get the unique string of searchStrings.
    size_t uniqueStringsCount = searchStringsSize;
    mstring* uniqueStringsFromSearchText = getUnique(searchStrings, uniqueStringsCount);

    size_t countOfAllStrings = 0;

    for (size_t i = 0; i < uniqueStringsCount; i++)
    {
        const mstring& searchString = uniqueStringsFromSearchText[i];
        size_t countOfString = countOf(text, searchString, startIndex, endIndex);
        countOfAllStrings += countOfString;
    }

    delete[] uniqueStringsFromSearchText;

    return countOfAllStrings;
}

mstring MStringManip::getUnique(const mstring& text)
{
    mstring uniqueSymbols;

    size_t uniqueSymbolsIndex = 0;

    for (size_t i = 0; i < text.getSize(); i++)
    {
        if (!stringContains(uniqueSymbols, text[i])) uniqueSymbols += text[i];
    }
    return uniqueSymbols;
}

mstring* MStringManip::getUnique(const mstring* strings, size_t& arraySize)
{
    if (arraySize == 0) throw "Array size is 0 looool";

    mstring* uniqueStrings = new mstring [arraySize];

    size_t uniqueStringsIndex = 0;

    for (size_t i = 0; i < arraySize; i++)
    {
        const mstring& stringToCompare = strings[i];

        bool stringIsUnique = true;
        for (size_t y = 0; y < uniqueStringsIndex; y++)
        {
            if (stringToCompare == uniqueStrings[y])
            {
                stringIsUnique = false;
                break;
            }
        }

        if (stringIsUnique)
        {
            //Add the new string to uniqueStrings
            uniqueStrings[uniqueStringsIndex++] = stringToCompare;
        }
    }

    //Set array size
    arraySize = uniqueStringsIndex;

    return uniqueStrings;
}

mstring MStringManip::getFrom(const mstring& source, size_t startIndex, size_t endIndex)
{
    if (startIndex < 0 || startIndex > source.getSize() - 1 || endIndex < 0 || endIndex > source.getSize() - 1)
        throw std::out_of_range("The start or end indexes are out of range");

    if (startIndex > endIndex) return "";

    mstring returnString;
    for (size_t i = startIndex; i <= endIndex; i++)
    {
        returnString += source[i];
    }

    return returnString;
}

mstring MStringManip::getReverse(const mstring& source)
{
    mstring reversedSource;
    for (size_t i = 0; i < source.getSize(); i++)
    {
        reversedSource += source[source.getSize() - 1 - i];
    }

    return mstring(reversedSource);
}

bool MStringManip::arraysOfStringsAreEqual(const mstring* stringsOne, const mstring* stringsTwo, size_t stringsOneSize, size_t stringsTwoSize)
{
    if (stringsOneSize != stringsTwoSize) return false;
    for (size_t i = 0; i < stringsOneSize; i++)
    {
        if (stringsOne[i] != stringsTwo[i]) return false;
    }

    return true;
}
