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
public:
	static void printScreenWithText(mstring text, mstring screenTitle);
	static void printScreenWithText(mstring text);
	static void printScreenWithText(const mstring* textArray, size_t arraySize, mstring screenTitle);
	static void printScreenWithText(const mstring* textArray, size_t arraySize);
	static void printLine(mstring text);
	//Print line without any screen borders
	static void printLineNoBorders(mstring text, TextAlign align = TextAlign::Left);
	static void printEmptyLine();
};


