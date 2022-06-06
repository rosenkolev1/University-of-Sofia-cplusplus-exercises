#include "GameUI.h"
#include "../Game.GlobalConstants/GlobalConstants.h"
#include<iostream>
#include "..\Project.StringManipulation\MStringManip.h"

const mstring GameUI::BORDER_TOP = "--------------------------------------------------------------------------------------------------------------";
const mstring GameUI::LINE_EMPTY = "|                                                                                                           |";
const mstring GameUI::BORDER_BOTTOM = "--------------------------------------------------------------------------------------------------------------";

void GameUI::printScreenWithText(mstring text, mstring screenTitle)
{
	std::cout << BORDER_TOP << std::endl;

	//Print initial empty lines
	for (int i = 0; i < LINES_EMPTY_INITIAL_COUNT; i++)
	{
		//if (i == 1 && screenTitle != nullptr) printLine(screenTitle);
		if (i == 1) printLine(screenTitle);
		else printEmptyLine();
	}

	//Seperate the text if it's too large for a single line or if it has new line characters in it
	//size_t sizeOfText = text.getSize();

	/*char* currentLine = new __nothrow char[sizeOfText + 1];
	if (currentLine == nullptr) throw GlobalConstants::BAD_ALLOC_EXCEPTION; 
	int currentLineLength = 0;*/
	mstring currentLine;

	int totalTextLinesCount = LINES_COUNT;
	int textLinesCount = 1;

	//Print text lines
	for (int i = 0; i < text.getSize(); i++)
	{
		char symbol = text[i];
		/*currentLine[currentLineLength] = text[i];
		currentLineLength++;*/
		currentLine.push_back(symbol);
		if (symbol == '\n' || currentLine.getSize() == TEXT_MAXLENGTH_LINE || i == text.getSize() - 1)
		{
			//If it ends in a newline, then delete that newline char and replace it with \0, since the printLine functions returns to a new line anyway.
			bool hasNewLineEnding = symbol == '\n';
			if (hasNewLineEnding)
			{
				currentLine.pop();
				printLine(currentLine);
			}
			else printLine(currentLine);

			/*if (hasNewLineEnding) currentLine[currentLineLength - 1] = '\0';
			else currentLine[currentLineLength] = '\0';*/

			/*if (hasNewLineEnding) printLine(currentLine);
			else printLine(currentLine);*/

			//Empty currentLine
			/*delete[] currentLine;
			currentLine = new __nothrow char[sizeOfText];
			if (currentLine == nullptr) throw GlobalConstants::BAD_ALLOC_EXCEPTION;

			currentLineLength = 0;*/
			currentLine = "";


			if (textLinesCount > LINES_COUNT - LINES_EMPTY_INITIAL_COUNT - LINES_EMPTY_ENDING_COUNT) totalTextLinesCount++;

			textLinesCount++;
		}
		//if (currentLine[currentLineLength - 1] == '\n' || currentLineLength == TEXT_MAXLENGTH_LINE || i == sizeOfText - 1)
		//{
		//	//If it ends in a newline, then delete that newline char and replace it with \0, since the printLine functions returns to a new line anyway.
		//	bool hasNewLineEnding = currentLine[currentLineLength - 1] == '\n';

		//	if (hasNewLineEnding) currentLine[currentLineLength - 1] = '\0';
		//	else currentLine[currentLineLength] = '\0';

		//	if (hasNewLineEnding) printLine(currentLine);
		//	else printLine(currentLine);

		//	//Empty currentLine
		//	delete[] currentLine;
		//	currentLine = new __nothrow char[sizeOfText];
		//	if (currentLine == nullptr) throw GlobalConstants::BAD_ALLOC_EXCEPTION; 

		//	currentLineLength = 0;

		//	if (textLinesCount > LINES_COUNT - LINES_EMPTY_INITIAL_COUNT - LINES_EMPTY_ENDING_COUNT) totalTextLinesCount++;

		//	textLinesCount++;
		//}
	}

	//Print ending empty lines
	for (int i = 0; i < totalTextLinesCount - LINES_EMPTY_INITIAL_COUNT - textLinesCount; i++)
	{
		printEmptyLine();
	}

	std::cout << BORDER_BOTTOM << std::endl;
}

void GameUI::printScreenWithText(mstring text)
{
	printScreenWithText(text, "");
}

void GameUI::printScreenWithText(const mstring* textArray, size_t arraySize, mstring screenTitle)
{

	/*char* text = new __nothrow char[arraySize * capacity];
	if (text == nullptr) throw GlobalConstants::BAD_ALLOC_EXCEPTION;
	int textCounter = 0;
	for (size_t i = 0; i < arraySize; i++)
	{
		size_t lengtOfText = strlen(textArray[i]);
		for (size_t y = 0; y < lengtOfText; y++)
		{
			text[textCounter] = textArray[i][y];
			textCounter++;
		}
	}
	text[textCounter++] = '\0';*/

	mstring concatText = MStringManip::concatStrings(textArray, arraySize);

	printScreenWithText(concatText, screenTitle);
	//delete[] text;
}

void GameUI::printScreenWithText(const mstring* textArray, size_t arraySize)
{
	printScreenWithText(textArray, arraySize, "");
}

void GameUI::printLine(mstring text)
{
	size_t sizeOfText = text.getSize();

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

void GameUI::printLineNoBorders(mstring text, TextAlign align)
{
	if (align == TextAlign::Center)
	{
		size_t textLength = text.getSize();
		size_t paddingLeftAndRight = (110 - textLength) / 2;
		for (size_t i = 0; i < paddingLeftAndRight; i++)
		{
			std::cout << " ";
		}
	}
	std::cout << text << std::endl;
}

void GameUI::printEmptyLine()
{
	printLine("");
}
