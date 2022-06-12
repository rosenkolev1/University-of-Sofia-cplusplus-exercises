#pragma once
#include "..\Project.StringManipulation\MString.h"

enum class TextAlign
{
	Right,
	Left,
	Center
};

class GameUI
{
private:
	static const mstring BORDER_TOP;
	static const mstring BORDER_BOTTOM;
	static const mstring LINE_EMPTY;

	//Line length
	static const int LINE_LENGTH = 110;

	//Maximum size of text per line
	static const int TEXT_MAXLENGTH_LINE = 106;

	//TOTAL NUMBER OF LINES UNLESS TEXT IS TOO LARGE
	static const int LINES_COUNT = 20;

	//THE NUMBER OF EMPTY LINES PRINTED BEFORE THE TEXT GETS PRINTED
	static const int LINES_EMPTY_INITIAL_COUNT = 3;
	static const int LINES_EMPTY_ENDING_COUNT = 3;

	//FOR BUILDING TABLES OF THINGS
	static const mstring TABLE_DELIM;
	static const mstring HORIZONTAL_DELIM;
public:

	static void printScreenWithText(mstring text, mstring screenTitle);
	static void printScreenWithText(mstring text);
	static void printScreenWithText(const mstring* textArray, size_t arraySize, mstring screenTitle);
	static void printScreenWithText(const mstring* textArray, size_t arraySize);
	static void printLine(mstring text);

	//Print line without any screen borders
	static void printLineNoBorders(mstring text, TextAlign align = TextAlign::Left);
	static void printEmptyLine();

	static mstring getTable(const mstring* cols, size_t countOfCols, mstring* rows, size_t countOfRows, mstring dataDelim);
	static mstring getTableSpacer(const mstring& combinedCols);
	static mstring getTableHeader(const mstring& combinedCols);
	static void setColHeaderAndDataInfo(mstring& colHeader, mstring& colData);
	static void setColHeaderInfo(mstring& colHeader, const mstring& colData, bool includeDelim);
	static void setColDataInfo(const mstring& colHeader, mstring& colData, bool includeDelim);
};


