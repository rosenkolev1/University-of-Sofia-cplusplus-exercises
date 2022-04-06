#ifndef GAMEUI_H
#define GAMEUI_H

#include "../Project.GlobalConstants/GlobalConstants.h"

class GameUI
{
private:
	static const char* BORDER_TOP;
	static const char* BORDER_BOTTOM;
	static const char* LINE_EMPTY;
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
	static void printScreenWithText(const char* text, size_t capacity);
	static void printLine(const char* text, size_t capacity);
	static void printEmptyLine();
};

#endif

