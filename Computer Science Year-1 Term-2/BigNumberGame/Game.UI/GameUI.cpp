#include "GameUI.h"
#include "../Game.GlobalConstants/GlobalConstants.h"
#include<iostream>

const char* GameUI::BORDER_TOP = "--------------------------------------------------------------------------------------------------------------";
const char* GameUI::LINE_EMPTY = "|                                                                                                           |";
const char* GameUI::BORDER_BOTTOM = "--------------------------------------------------------------------------------------------------------------";

size_t GameUI::getTextLength(const char* text)
{
	size_t sizeOfText = 0;
	while (text[sizeOfText] > 0 && text[sizeOfText] <= 128) sizeOfText++;
	return sizeOfText;
}

void GameUI::printScreenWithText(const char* text)
{
	std::cout << BORDER_TOP << std::endl;

	//Print initial empty lines
	for (int i = 0; i < LINES_EMPTY_INITIAL_COUNT; i++)
	{
		printEmptyLine();
	}

	//Seperate the text if it's too large for a single line or if it has new line characters in it
	size_t sizeOfText = getTextLength(text);

	//TODO: ADD GLOBAL CONSTANT FOR BAD ALLOC ERROR
	char* currentLine = new __nothrow char[sizeOfText + 1];
	if (currentLine == nullptr) throw GlobalConstants::BAD_ALLOC_EXCEPTION; 
	int currentLineLength = 0;

	int totalTextLinesCount = LINES_COUNT;
	int textLinesCount = 1;

	//Print text lines
	for (int i = 0; i < sizeOfText; i++)
	{
		currentLine[currentLineLength] = text[i];
		currentLineLength++;
		if (currentLine[currentLineLength - 1] == '\n' || currentLineLength == TEXT_MAXLENGTH_LINE || i == sizeOfText - 1)
		{
			//If it ends in a newline, then delete that newline char and replace it with \0, since the printLine functions returns to a new line anyway.
			bool hasNewLineEnding = currentLine[currentLineLength - 1] == '\n';

			if (hasNewLineEnding) currentLine[currentLineLength - 1] = '\0';
			else currentLine[currentLineLength] = '\0';

			if (hasNewLineEnding) printLine(currentLine, currentLineLength);
			else printLine(currentLine, currentLineLength + 1);

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

void GameUI::printScreenWithText(const char** textArray, size_t arraySize, size_t capacity)
{

	char* text = new __nothrow char[arraySize * capacity];
	if (text == nullptr) throw GlobalConstants::BAD_ALLOC_EXCEPTION;
	int textCounter = 0;
	for (size_t i = 0; i < arraySize; i++)
	{
		/*strcat(text, textArray[i]); DOESNT WORK FOR SOME REASON*/
		size_t lengtOfText = getTextLength(textArray[i]);
		for (size_t y = 0; y < lengtOfText; y++)
		{
			text[textCounter] = textArray[i][y];
			textCounter++;
		}
	}

	printScreenWithText(text);
	delete[] text;
}

void GameUI::printLine(const char* text, size_t capacity)
{
	size_t sizeOfText = getTextLength(text);

	int emptySpacesCount = (LINE_LENGTH - sizeOfText - 2) / 2;
	int startTextIndex = emptySpacesCount + 1; //x + sizeOfText + x = 110
	int endTextIndex = startTextIndex + sizeOfText - 1;
	bool hasNewLineEnding = false;

	std::cout << "|";
	for (size_t i = 0; i < emptySpacesCount; i++)
	{
		std::cout << " ";
	}
	for (size_t i = 0; i < sizeOfText; i++)
	{
		if (text[i] == '\n') hasNewLineEnding;
		else std::cout << text[i];

	}
	for (size_t i = 0; i < ((LINE_LENGTH - sizeOfText - 2) % 2 == 1 ? emptySpacesCount + 1 : emptySpacesCount); i++)
	{
		std::cout << " ";
	}
	std::cout << "|";

	std::cout << std::endl;
}

void GameUI::printLineNoBorders(const char* text)
{
	std::cout << text << std::endl;
}

void GameUI::printEmptyLine()
{
	printLine("", 0);
}
