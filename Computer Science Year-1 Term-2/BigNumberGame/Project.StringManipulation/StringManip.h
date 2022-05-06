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
	static bool stringContainsInvalidChars(const char* text);

	static bool stringContainsChar(const char* text, const char symbol);

	static bool stringContains(const char* text, const char* other);

	static bool stringStartsWith(const char* text, const char* other);

	static bool stringEndsWith(const char* text, const char* other);

	static void deleteArrayOfStrings(char** text, size_t arrayCount);

	static char* concatStrings(const char** strings, size_t stringsCount);

	//Replaces all instances of the replaced string in the text with the replacement string
	static char* replaceAll(const char* text, const char* replaced, const char* replacement);

	//Returns the index of the first occurance of searchText in text. Returns -1 if searchText isn't found inside text
	static int findIndex(char* text, const char* searchText);
};

//TODO: Decide what to do with the string contains invalid chars function, which doesn't belong here. Maybe make the string contains invalid chars accept the invalid chars as a parameter instead of the GlobalConstants being programmed in statically in the function

