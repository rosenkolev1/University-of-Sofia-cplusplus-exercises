//TODO: Replace pragma once with the other shit
#pragma once

#include "../Project.GlobalConstants/GlobalConstants.h"
#include "User.h"
#include<fstream>

enum class UserFields
{
	Username,
	Password,
	Level, 
	LastExpression
};

static class FileSystem
{
private:
	static constexpr char FORDBIDDEN_SYMBOLS[10] = 
	{
		GlobalConstants::FILESYSTEM_ENTRY_DELIMITER,
		GlobalConstants::FILESYSTEM_COLUMN_DELIMITER,
		'\0'
	};
public:
	//WRITE
	static void registerUser(const char* username, const char* password);

	//READ
	static User* getAllUsers();
	static size_t getUsersCount();

	//Checks for validity
	static bool stringContainsForbiddenSymbols(const char* text);
	static bool userIsValid(const char* username, const char* password);
	static bool userIsRegistered(const char* username);
	static bool usernameIsValid(const char* username);
	static bool passwordIsValid(const char* username);
};
