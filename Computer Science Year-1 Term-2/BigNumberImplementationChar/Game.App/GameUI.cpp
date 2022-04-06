#include "GameUI.h"
#include<iostream>

const char* GameUI::BORDER_TOP = "--------------------------------------------------------------------------------------------------------------";
const char* GameUI::LINE_EMPTY = "|                                                                                                           |";
const char* GameUI::BORDER_BOTTOM = "--------------------------------------------------------------------------------------------------------------";


//TODO: Scale down the length of the window dynamically based on the length of the longest line of text. More specifically, based 
// that length % 2, i.e. if it's even or odd, so that the text is padded an equal number of spaces from the left and from the right
void GameUI::printScreenWithText(const char* text, size_t capacity)
{
	std::cout << BORDER_TOP << std::endl;

	//Print initial empty lines
	for (int i = 0; i < LINES_EMPTY_INITIAL_COUNT; i++)
	{
		printEmptyLine();
	}

	//Seperate the text if it's too large for a single line or if it has new line characters in it
	size_t sizeOfText = strlen(text);
	if (sizeOfText > capacity) sizeOfText = capacity;

	//TODO: ADD GLOBAL CONSTANT FOR BAD ALLOC ERROR
	char *currentLine = new __nothrow char[sizeOfText + 1];
	if (currentLine == nullptr) throw GlobalConstants::BAD_ALLOC_EXCEPTION; //TODO: ADD GLOBAL CONSTANT FOR BAD ALLOC ERROR
	int currentLineLength = 0;

	int totalTextLinesCount = LINES_COUNT;
	int textLinesCount = 1;

	//Print text lines
	for (int i = 0; i < sizeOfText; i++)
	{
		currentLine[currentLineLength] = text[i];
		currentLineLength++;
		if (currentLine[i] == '\n' || currentLineLength == TEXT_MAXLENGTH_LINE || i == sizeOfText - 1)
		{
			currentLine[currentLineLength] = '\0';
			printLine(currentLine, currentLineLength + 1);

			//Empty currentLine
			delete[] currentLine;
			currentLine = new __nothrow char[sizeOfText];
			if (currentLine == nullptr) throw GlobalConstants::BAD_ALLOC_EXCEPTION; //TODO: ADD GLOBAL CONSTANT FOR BAD ALLOC ERROR

			currentLineLength = 0;

			if (textLinesCount > LINES_COUNT - LINES_EMPTY_INITIAL_COUNT - LINES_EMPTY_ENDING_COUNT) totalTextLinesCount++;

			textLinesCount++;
		}
	}

	//Print ending empty lines
	for (int i = 0; i < totalTextLinesCount - LINES_EMPTY_INITIAL_COUNT - textLinesCount; i++)
	{
		printEmptyLine();
	}

	std::cout << BORDER_BOTTOM << std::endl;
}

void GameUI::printLine(const char* text, size_t capacity)
{
	size_t sizeOfText = strlen(text);
	if (sizeOfText > capacity) sizeOfText = capacity;
	int emptySpacesCount = (LINE_LENGTH - sizeOfText - 2) / 2;
	int startTextIndex = emptySpacesCount + 1; //x + sizeOfText + x = 110
	int endTextIndex = startTextIndex + sizeOfText - 1;

	std::cout << "|";
	for (size_t i = 0; i < emptySpacesCount; i++)
	{
		std::cout << " ";
	}
	for (size_t i = 0; i < sizeOfText; i++)
	{
		std::cout << text[i];
	}
	for (size_t i = 0; i < ( (LINE_LENGTH - sizeOfText - 2) % 2 == 1 ? emptySpacesCount+1 : emptySpacesCount ); i++)
	{
		std::cout << " ";
	}
	std::cout << "|";

	std::cout << std::endl;
}

void GameUI::printEmptyLine()
{
	printLine("", 0);
}
