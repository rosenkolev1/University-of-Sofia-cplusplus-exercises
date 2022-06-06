#pragma once

#include "..\Game.GlobalConstants\GlobalConstants.h"
#include "User.h"
#include<fstream>

class FileSystem
{
public:
	//WRITE/UPDATE/PUT/DELETE
	static void overwriteDatabase(mstring databaseData);
	//static void appendToDatabase(mstring data);
	static void registerUser(mstring username, mstring password, UserRoles role = UserRoles::Normal);
	static void deleteUser(mstring username, mstring adminMessage);
	static void deleteUser(mstring username);

	//READ
	static mstring getDatabaseAsString();

	static User* getAllUsers(mstring databaseFile, size_t& countOfUsers, bool includeDeleted = true);
	static User* getAllUsers(size_t& countOfUsers, bool includeDeleted = true);

	//Make get functions work with predicates as parameters
	static User* getUser(mstring username, bool includeDeleted = true);

	//TODO: Switch username and database file order
	static mstring getUserString(mstring username, mstring databaseFile, size_t& startPos, size_t& endPos);
	static mstring getUserString(mstring username, size_t& startPos, size_t& endPos);

	static size_t getUsersCount(mstring databaseFile);
	static size_t getUsersCount();

	//Checks for validity
	static bool stringContainsForbiddenSymbols(mstring text);
	static bool userIsValid(mstring username, mstring password, mstring role);
	static bool userIsRegistered(mstring username);
	static bool userIsRegisteredWithPassword(mstring username, mstring password);
	static bool usernameIsValid(mstring username);
	static bool passwordIsValid(mstring username);
	static bool userRoleIsValid(mstring role);
};

/*
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
*/
