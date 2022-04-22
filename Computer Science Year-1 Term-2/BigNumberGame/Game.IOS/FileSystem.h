//TODO: Replace pragma once with the other shit
#pragma once

#include "..\Game.GlobalConstants\GlobalConstants.h"
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
public:
	//WRITE
	static void registerUser(const char* username, const char* password);

	//READ
	static User* getAllUsers(size_t usersCount = 0);
	static size_t getUsersCount();

	//Checks for validity
	static bool stringContainsForbiddenSymbols(const char* text);
	static bool userIsValid(const char* username, const char* password);
	static bool userIsRegistered(const char* username);
	static bool usernameIsValid(const char* username);
	static bool passwordIsValid(const char* username);
};
