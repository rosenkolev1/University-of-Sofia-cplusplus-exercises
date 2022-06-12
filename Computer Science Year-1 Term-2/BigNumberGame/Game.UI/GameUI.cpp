#include "GameUI.h"
#include<iostream>
#include "..\Project.StringManipulation\MStringManip.h"

const mstring GameUI::BORDER_TOP = "--------------------------------------------------------------------------------------------------------------";
const mstring GameUI::LINE_EMPTY = "|                                                                                                           |";
const mstring GameUI::BORDER_BOTTOM = "--------------------------------------------------------------------------------------------------------------";

const mstring GameUI::TABLE_DELIM = " |";
const mstring GameUI::HORIZONTAL_DELIM = "-";

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

void GameUI::printNoBorders(mstring text, TextAlign align)
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
	std::cout << text;
}

void GameUI::printLineNoBorders(mstring text, TextAlign align)
{
	printNoBorders(text, align);
	std::cout << "\n";
}

void GameUI::printEmptyLine()
{
	printLine("");
}

mstring GameUI::getTable(const mstring* cols, size_t countOfCols, mstring* rows, size_t countOfRows, mstring dataDelim)
{
	//Copy the cols param into a new array
	mstring* colTitles = new mstring[countOfCols];
	for (size_t i = 0; i < countOfCols; i++)
	{
		colTitles[i] = cols[i];
	}

	if (countOfRows == 0)
	{
		mstring combinedCols;
		for (size_t i = 0; i < countOfCols; i++)
		{
			combinedCols += colTitles[i];
		}
		mstring tableHeader = getTableHeader(combinedCols);

		return tableHeader;
	}

	//Initialize longest data in all the columns
	mstring* longestData = new mstring[countOfCols];
	size_t firstRowSplitDataCount = 0;
	mstring* firstRowSplitData = MStringManip::splitString(rows[0], dataDelim, firstRowSplitDataCount);
	for (size_t i = 0; i < countOfCols; i++)
	{
		longestData[i] = firstRowSplitData[i];
	}

	//Dealloc dynamic memory
	delete[] firstRowSplitData;

	//Now change the longest things
	for (size_t i = 1; i < countOfRows; i++)
	{
		size_t rowSplitDataCount = 0;
		mstring* rowSplitData = MStringManip::splitString(rows[i], dataDelim, rowSplitDataCount);
		for (size_t y = 0; y < countOfCols; y++)
		{
			if (rowSplitData[y].getSize() > longestData[y].getSize()) longestData[y] = rowSplitData[y];
		}

		//Dealloc dynamic memory
		delete[] rowSplitData;
	}

	//Set all col header info
	for (size_t i = 0; i < countOfCols; i++)
	{
		setColHeaderInfo(colTitles[i], longestData[i], false);
	}

	//Set all of the table data
	size_t tableRowsIndex = 0;
	mstring* tableRowsData = new mstring[countOfRows];

	//Set all of the users columns data
	for (size_t i = 0; i < countOfRows; i++)
	{
		mstring tableRowData;

		size_t rowSplitDataCount = 0;
		mstring* rowSplitData = MStringManip::splitString(rows[i], dataDelim, rowSplitDataCount);
		for (size_t y = 0; y < countOfCols; y++)
		{
			setColDataInfo(colTitles[y], rowSplitData[y], true);
			tableRowData += rowSplitData[y];
		}

		tableRowsData[i] = tableRowData;

		//Dealloc dynamic memory
		delete[] rowSplitData;
	}

	//Set the table header
	mstring combinedCols;
	for (size_t i = 0; i < countOfCols; i++)
	{
		combinedCols += colTitles[i] + TABLE_DELIM;
	}

	mstring tableHeader = getTableHeader(combinedCols);

	mstring tableString = tableHeader;

	//Set the final table string
	for (size_t i = 0; i < countOfRows; i++)
	{
		tableString += tableRowsData[i] + getTableSpacer(combinedCols);
	}

	return tableString;
}

mstring GameUI::getTableSpacer(const mstring& combinedCols)
{
	mstring filling = MStringManip::getFilled(HORIZONTAL_DELIM, combinedCols.getSize());

	int newStartIndex = 0;

	//Change this 
	/*
		Username   |Password |Role  |Level |Lives |LastExpression |IncludeHighscore |IsDeleted |
		----------------------------------------------------------------------------------------
	*/
	//To this
	/*
		Username   |Password |Role  |Level |Lives |LastExpression |IncludeHighscore |IsDeleted |
		-----------|---------|------|------|------|---------------|-----------------|----------|
	*/
	while (true)
	{
		newStartIndex = MStringManip::findIndex(combinedCols, TABLE_DELIM, newStartIndex + 1, combinedCols.getSize() - 1);

		if (newStartIndex == -1) break;

		filling = MStringManip::replaceFrom(filling, MStringManip::replaceAll(TABLE_DELIM, " ", HORIZONTAL_DELIM), newStartIndex, newStartIndex + TABLE_DELIM.getSize() - 1);
	}

	filling.push_front("\n");
	filling += "\n";

	return filling;
}

mstring GameUI::getTableHeader(const mstring& combinedCols)
{
	mstring filling = getTableSpacer(combinedCols);

	return combinedCols + filling;
}

void GameUI::setColHeaderAndDataInfo(mstring& colHeader, mstring& colData)
{
	setColHeaderInfo(colHeader, colData, false);
	setColDataInfo(colHeader, colData, false);

	colHeader += TABLE_DELIM;
	colData += TABLE_DELIM;
}

void GameUI::setColHeaderInfo(mstring& colHeader, const mstring& colData, bool includeDelim)
{
	int sizeDif = colData.getSize() - colHeader.getSize();
	if (sizeDif > 0)
	{
		colHeader += MStringManip::getFilled(" ", sizeDif);
	}
	if (includeDelim) colHeader += TABLE_DELIM;
}

void GameUI::setColDataInfo(const mstring& colHeader, mstring& colData, bool includeDelim)
{
	int sizeDif = colData.getSize() - colHeader.getSize();
	if (sizeDif < 0)
	{
		colData += MStringManip::getFilled(" ", -sizeDif);
	}
	if (includeDelim) colData += TABLE_DELIM;
}