#pragma once
class ConsoleSystem
{
public:
	static char* parseToString(int integer);

	//Split string by delim. sizeOfArray returns the numbers of split strings. 
	static char** splitString(const char* input, char delim, size_t& sizeOfArray);

	//Checks for validity
	static bool stringContainsInvalidChars(const char* text);

	static bool stringContainsChar(const char* text, const char symbol);

	static void deleteArrayOfStrings(char** text, size_t arrayCount);
};

