#pragma once

#include "..\Game.GlobalConstants\GlobalConstants.h"
#include "User.h"
#include<fstream>

class FileSystem
{
public:
	//WRITE/UPDATE/PUT/DELETE
	static void overwriteDatabase(const char* databaseData);
	//static void appendToDatabase(const char* data);
	static void registerUser(const char* username, const char* password, UserRoles role = UserRoles::Normal);
	static void deleteUser(const char* username, const char* adminMessage);

	//READ
	static const char* getDatabaseAsString();
	static User* getAllUsers(const char* databaseFile = nullptr, size_t usersCount = 0, bool includeDeleted = true);
	//Make get functions work with predicates as parameters
	static User* getUser(const char* username, bool includeDeleted = true);
	static char* getUserString(const char* username, const char* databaseFileCopy, size_t databaseFileSize, size_t& startPos, size_t& endPos);
	static size_t getUsersCount(const char* databaseFile = nullptr);

	//Checks for validity
	static bool stringContainsForbiddenSymbols(const char* text);
	static bool userIsValid(const char* username, const char* password, const char* role);
	static bool userIsRegistered(const char* username);
	static bool userIsRegisteredWithPassword(const char* username, const char* password);
	static bool usernameIsValid(const char* username);
	static bool passwordIsValid(const char* username);
	static bool userRoleIsValid(const char* role);
};
