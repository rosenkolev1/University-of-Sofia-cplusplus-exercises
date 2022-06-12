#include "GameUI.h"
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
		if (i == 1) printLine(screenTitle);
		else printEmptyLine();
	}

	mstring currentLine;

	int totalTextLinesCount = LINES_COUNT;
	int textLinesCount = 1;

	//Print text lines
	for (int i = 0; i < text.getSize(); i++)
	{
		char symbol = text[i];

		currentLine += symbol;
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

			//Reset the currentLine
			currentLine = "";

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

void GameUI::printScreenWithText(mstring text)
{
	printScreenWithText(text, "");
}

void GameUI::printScreenWithText(const mstring* textArray, size_t arraySize, mstring screenTitle)
{
	mstring concatText = MStringManip::concatStrings(textArray, arraySize);

	printScreenWithText(concatText, screenTitle);
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
