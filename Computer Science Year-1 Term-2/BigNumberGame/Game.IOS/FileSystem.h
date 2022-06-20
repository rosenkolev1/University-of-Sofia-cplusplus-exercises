#pragma once

#include "..\Game.GlobalConstants\GlobalConstants.h"
#include "User.h"
#include<fstream>
#include "DeletionMessage.h"

class FileSystem
{
public:
	//---FILE SYSTEM CONSTANTS
	static constexpr const char* USER_TABLE = "USER_TABLE.bin";
	static constexpr const char* DELETION_MESSAGES_TABLE = "DELETION_MESSAGES_TABLE.bin";

	static const char FILESYSTEM_ENTRY_DELIMITER;
	static const char FILESYSTEM_COLUMN_DELIMITER;
	static const char FILESYSTEM_WHITESPACE;
	static const mstring FILESYSTEM_COLUMN_NULL;
	static const mstring FILESYSTEM_TRUE;
	static const mstring FILESYSTEM_FALSE;

	//---FORBIDDEN STRING SYMBOLS
	static const char FORBIDDEN_SYMBOLS[];

	//WRITE/UPDATE/PUT/DELETE
	static void overwriteTable(const mstring& tableData, const char* table);
	static void appendToTable(const mstring& appendData, const char* table);
	static mstring getTableAsString(const char* table);
	static size_t getCount(const mstring& tableFile);

	//Check for validity
	static bool stringContainsForbiddenSymbols(const mstring& text);
};