#pragma once
#include "MString.h"

class MStringManip
{
public:
	//Parse an int to string
	static mstring parseToString(int integer);

	//Parse an size_t to string
	static mstring parseToString(size_t integer);

	//Parse a string to long
	static long parseToLong(mstring text);

	//Split string by char delim. sizeOfArray returns the numbers of split strings. 
	static mstring* splitString(const mstring& input, char delim, size_t& sizeOfArray);

	//Split string by string delim. sizeOfArray returns the numbers of split strings. 
	static mstring* splitString(const mstring& input, const mstring& delim, size_t& sizeOfArray);

	//Split string by many char delims. sizeOfArray returns the numbers of split strings. 
	static mstring* splitStringMany(const mstring& input, const mstring& delims, size_t& sizeOfArray);

	//Split string by many string delims. sizeOfArray returns the numbers of split strings. 
	static mstring* splitStringMany(const mstring& input, const mstring* delims, size_t sizeOfDelimsArrays, size_t& sizeOfArray);

	//Checks if the text contains any of the invalid chars
	static bool stringContainsInvalidChars(const mstring& text, const mstring& invalidChars);

	//Checks if the text contains the given char
	static bool stringContains(const mstring& text, const char other);

	//Checks if the text contains the given string
	static bool stringContains(const mstring& text, const mstring& other);

	//Checks if the text starts with the given string
	static bool stringStartsWith(const mstring& text, const mstring& other);

	//Checks if the text ends with the given string
	static bool stringEndsWith(const mstring& text, const mstring& other);

	//Concatenates strings from a char of strings
	static mstring concatStrings(const mstring* strings, size_t stringsCount);

	//Replaces all instances of the replaced string in the text with the replacement string
	static mstring replaceAll(const mstring& text, const mstring& replaced, const mstring& replacement);

	//Replaces the first instance of the replaced string in the text with the replacement string
	static mstring replaceFirst(const mstring& text, const mstring& replaced, const mstring& replacement);

	//Replaces a part of the string, starting from startIndex, inclusive, with the replacement.
	static mstring replaceFrom(const mstring& text, const mstring& replacement, size_t startIndex);

	//Replaces a part of the string, starting from startIndex and ending in endIndex, both inclusive, with the replacement.
	static mstring replaceFrom(const mstring& text, const mstring& replacement, size_t startIndex, size_t endIndex);

	//Returns the index of the first occurance of searchText in text. Returns -1 if searchText isn't found inside text
	static int findIndex(const mstring& text, const mstring& searchText);

	//Returns the index of the first occurance of searchText in text, starting from startIndex and ending in endIndex, both inclusive. Returns -1 if searchText isn't found inside text
	static int findIndex(const mstring& text, const mstring& searchText, size_t startIndex, size_t endIndex);

	//Returns the index of the last occurance of searchText in text. Returns -1 if searchText isn't found inside text
	static int findIndexLast(const mstring& text, const mstring& searchText);

	//Returns the index of the last occurance of searchText in text, starting from startIndex and ending in endIndex, both inclusive. Returns -1 if searchText isn't found inside text
	static int findIndexLast(const mstring& text, const mstring& searchText, size_t startIndex, size_t endIndex);

	//Returns the count of symbol in text
	static size_t countOf(const mstring& text, char symbol);

	//Returns the count of symbol in text, starting from startIndex and ending in endIndex, both inclusive
	static size_t countOf(const mstring& text, char symbol, size_t startIndex, size_t endIndex);

	//Returns the count of searchText in text
	static size_t countOf(const mstring& text, const mstring& searchText);

	//Returns the count of searchText in text, starting from startIndex and ending in endIndex, both inclusive
	static size_t countOf(const mstring& text, const mstring& searchText, size_t startIndex, size_t endIndex);

	//Returns the count of all the symbols of searchText in text. For repeating symbols, only counts the symbol one time
	static size_t countOfMany(const mstring& text, const mstring& searchText);

	//Returns the count of all the symbols of searchText in text, starting from startIndex and ending in endIndex, both inclusive. For repeating symbols, only counts the symbol one time
	static size_t countOfMany(const mstring& text, const mstring& searchText, size_t startIndex, size_t endIndex);

	//Returns the count of all the string of searchStrings in text. For repeating strings, only counts the string one time
	static size_t countOfMany(const mstring& text, const mstring* searchStrings, size_t searchStringsSize);

	//Returns the count of all the string of searchStrings in text, starting from startIndex and ending in endIndex, both inclusive. For repeating strings, only counts the string one time
	static size_t countOfMany(const mstring& text, const mstring* searchStrings, size_t searchStringsSize, size_t startIndex, size_t endIndex);

	//Returns an array of chars where each char from text is unique, i.e. doesn't appear again.
	static mstring getUnique(const mstring& text);

	//Returns an array of strings where each string from strings is unique, i.e. doesn't appear again.
	static mstring* getUnique(const mstring* strings, size_t& arraySize);

	//Get the part of the source that start from startIndex and ends on endIndex, both inclusive. Return nullptr if the startIndex is > endIndex
	static mstring getFrom(const mstring& source, size_t startIndex, size_t endIndex);

	//Get the reverse of the source
	static mstring getReverse(const mstring& source);

	static mstring getFilled(const mstring& filling, size_t count);

	//Compares 2 arrays of strings and says whether or not they are the same
	static bool arraysOfStringsAreEqual(const mstring* stringsOne, const mstring* stringsTwo, size_t stringsOneSize, size_t stringsTwoSize);
};


