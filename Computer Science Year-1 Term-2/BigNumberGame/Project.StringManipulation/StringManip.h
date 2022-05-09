#pragma once
class StringManip
{
public:
	//Parse an int to string
	static char* parseToString(int integer);

	//Split string by char delim. sizeOfArray returns the numbers of split strings. 
	static char** splitString(const char* input, char delim, size_t& sizeOfArray);

	//Split string by string delim. sizeOfArray returns the numbers of split strings. 
	static char** splitString(const char* input, const char* delim, size_t& sizeOfArray);

	//Split string by many char delims. sizeOfArray returns the numbers of split strings. 
	static char** splitStringMany(const char* input, const char* delim, size_t& sizeOfArray);

	//Split string by many string delims. sizeOfArray returns the numbers of split strings. 
	static char** splitStringMany(const char* input, const char** delims, size_t& sizeOfArray);

	//Checks for validity
	static bool stringContainsInvalidChars(const char* text, const char* invalidChars);

	static bool stringContains(const char* text, const char other);

	static bool stringContains(const char* text, const char* other);

	static bool stringStartsWith(const char* text, const char* other);

	static bool stringEndsWith(const char* text, const char* other);

	static void deleteArrayOfStrings(char** text, size_t arrayCount);

	static char* concatStrings(const char** strings, size_t stringsCount);

	//Replaces all instances of the replaced string in the text with the replacement string
	static char* replaceAll(const char* text, const char* replaced, const char* replacement);

	//Replaces the first instance of the replaced string in the text with the replacement string
	static char* replaceFirst(const char* text, const char* replaced, const char* replacement);

	//Replaces a part of the string, starting from startIndex, inclusive, with the replacement.
	static char* replaceFrom(const char* text, const char* replacement, size_t from);

	//Replaces a part of the string, starting from startIndex and ending in endIndex, both inclusive, with the replacement.
	static char* replaceFrom(const char* text, const char* replacement, size_t startIndex, size_t endIndex);

	//Returns the index of the first occurance of searchText in text. Returns -1 if searchText isn't found inside text
	static int findIndex(const char* text, const char* searchText);

	//Returns the index of the first occurance of searchText in text, starting from startIndex and ending in endIndex, both inclusive. Returns -1 if searchText isn't found inside text
	static int findIndex(const char* text, const char* searchText, size_t startIndex, size_t endIndex);

	//Returns the index of the last occurance of searchText in text. Returns -1 if searchText isn't found inside text
	static int findIndexLast(const char* text, const char* searchText);

	//Returns the index of the last occurance of searchText in text, starting from startIndex and ending in endIndex, both inclusive. Returns -1 if searchText isn't found inside text
	static int findIndexLast(const char* text, const char* searchText, size_t startIndex, size_t endIndex);

	//Returns the count of symbol in text
	static size_t countOf(const char* text, char symbol);

	//Returns the count of symbol in text, starting from startIndex and ending in endIndex, both inclusive
	static size_t countOf(const char* text, char symbol, size_t startIndex, size_t endIndex);

	//Returns the count of searchText in text
	static size_t countOf(const char* text, const char* searchText);

	//Returns the count of searchText in text, starting from startIndex and ending in endIndex, both inclusive
	static size_t countOf(const char* text, const char* searchText, size_t startIndex, size_t endIndex);

	//Returns the count of all the symbols of searchText in text. For repeating symbols, only counts the symbol one time
	static size_t countOfMany(const char* text, const char* searchText);

	//Returns the count of all the symbols of searchText in text, starting from startIndex and ending in endIndex, both inclusive. For repeating symbols, only counts the symbol one time
	static size_t countOfMany(const char* text, const char* searchText, size_t startIndex, size_t endIndex);

	//Returns the count of all the string of searchStrings in text. For repeating strings, only counts the string one time
	static size_t countOfMany(const char* text, char** searchStrings, size_t searchStringsSize);

	//Returns the count of all the string of searchStrings in text, starting from startIndex and ending in endIndex, both inclusive. For repeating strings, only counts the string one time
	static size_t countOfMany(const char* text, char** searchStrings, size_t searchStringsSize, size_t startIndex, size_t endIndex);

	//Returns an array of chars where each char from text is unique, i.e. doesn't appear again.
	static char* getUnique(const char* text);

	//Returns an array of strings where each string from strings is unique, i.e. doesn't appear again.
	static char** getUnique(char** strings, size_t& arraySize);

	//Compares 2 arrays of strings and says whether or not they are the same
	static bool arraysOfStringsAreEqual(char** stringsOne, char** stringsTwo, size_t stringsOneSize, size_t stringsTwoSize);
};
