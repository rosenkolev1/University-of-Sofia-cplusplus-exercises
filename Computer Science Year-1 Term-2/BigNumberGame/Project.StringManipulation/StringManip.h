#pragma once
class StringManip
{
public:
	static char* parseToString(int integer);

	//Split string by char delim. sizeOfArray returns the numbers of split strings. 
	static char** splitString(const char* input, char delim, size_t& sizeOfArray);

	//Split string by string delim. sizeOfArray returns the numbers of split strings. 
	static char** splitString(const char* input, const char* delim, size_t& sizeOfArray);

	//Checks for validity
	static bool stringContainsInvalidChars(const char* text, const char* invalidChars);

	static bool stringContainsChar(const char* text, const char symbol);

	static bool stringContains(const char* text, const char* other);

	static bool stringStartsWith(const char* text, const char* other);

	static bool stringEndsWith(const char* text, const char* other);

	static void deleteArrayOfStrings(char** text, size_t arrayCount);

	static char* concatStrings(const char** strings, size_t stringsCount);

	//Replaces all instances of the replaced string in the text with the replacement string
	static char* replaceAll(const char* text, const char* replaced, const char* replacement);

	//Replaces the first instance of the replaced string in the text with the replacement string
	static char* replaceFirst(const char* text, const char* replaced, const char* replacement);

	//Returns the index of the first occurance of searchText in text. Returns -1 if searchText isn't found inside text
	static int findIndex(const char* text, const char* searchText);

	//Returns the index of the first occurance of searchText in text, starting from startIndex and ending in endIndex, both inclusive. Returns -1 if searchText isn't found inside text
	static int findIndex(const char* text, const char* searchText, size_t startIndex, size_t endIndex);

	//Returns the index of the last occurance of searchText in text. Returns -1 if searchText isn't found inside text
	static int findIndexLast(const char* text, const char* searchText);

	//Returns the index of the last occurance of searchText in text, starting from startIndex and ending in endIndex, both inclusive. Returns -1 if searchText isn't found inside text
	static int findIndexLast(const char* text, const char* searchText, size_t startIndex, size_t endIndex);

	//Returns the count of searchText in text, starting from startIndex and ending in endIndex, both inclusive
	static int countOf(const char* text, const char* searchText, size_t startIndex, size_t endIndex);
};
