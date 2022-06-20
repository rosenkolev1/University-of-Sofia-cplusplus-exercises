#pragma once

#include "FileSystem.h"
#include "..\Project.StringManipulation\MStringManip.h"

//---FILE SYSTEM CONSTANTS
const char FileSystem::FILESYSTEM_ENTRY_DELIMITER = '\n';
const char FileSystem::FILESYSTEM_COLUMN_DELIMITER = '^';
const char FileSystem::FILESYSTEM_WHITESPACE = ' ';
const mstring FileSystem::FILESYSTEM_COLUMN_NULL = "COL_NULL";
const mstring FileSystem::FILESYSTEM_TRUE = "TRUE";
const mstring FileSystem::FILESYSTEM_FALSE = "FALSE";
const char FileSystem::FORBIDDEN_SYMBOLS[5] =
{
	FILESYSTEM_ENTRY_DELIMITER,
	FILESYSTEM_COLUMN_DELIMITER,
	FILESYSTEM_WHITESPACE,
	GlobalConstants::COMMAND_DELIM,
	'\0'
};

size_t FileSystem::getCount(const mstring& tableFile)
{
	return MStringManip::countOf(tableFile, FILESYSTEM_ENTRY_DELIMITER);
}

mstring FileSystem::getTableAsString(const char* table)
{
	std::ifstream tableFile(table, std::ios::binary);

	//Check if database file is open
	if (!tableFile.is_open())
	{
		//Database file doesn't exist, i.e. there are not registered people yet!
		return "";
	}

	mstring tableData;
	while (!tableFile.eof())
	{
		mstring newLine;
		tableFile >> newLine;

		tableData += newLine + "\n";
	}

	//Remove all \n at end of databaseData and then add just one
	while (tableData.peek() == '\n') tableData.pop();

	tableData += '\n';

	tableFile.close();

	return tableData;
}

void FileSystem::overwriteTable(const mstring& tableData, const char* table)
{
	std::ofstream tableFile(table, std::ios::binary | std::ios::trunc);

	//Check if database file is open
	if (!tableFile.is_open())
	{
		//throw some error
		throw "Fuck this shit I'm out ";
	}

	tableFile << tableData;

	tableFile.close();
}

void FileSystem::appendToTable(const mstring& appendData, const char* table)
{
	std::ofstream tableFile(table, std::ios::binary | std::ios::app);

	//Check if database file is open
	if (!tableFile.is_open())
	{
		//throw some error
		throw "Fuck this shit I'm out ";
	}

	tableFile << appendData;

	tableFile.close();
}

/**********************************************************************************************************************************/
//
bool FileSystem::stringContainsForbiddenSymbols(const mstring& text)
{
	for (size_t i = 0; i < text.getSize(); i++)
	{
		for (size_t y = 0; y < strlen(FORBIDDEN_SYMBOLS); y++)
		{
			if (text[i] == FORBIDDEN_SYMBOLS[y]) return true;
		}
	}
	return false;
}


