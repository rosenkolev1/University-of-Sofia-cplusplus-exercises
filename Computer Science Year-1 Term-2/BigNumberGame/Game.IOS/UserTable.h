#pragma once

#include "..\Game.GlobalConstants\GlobalConstants.h"
#include "User.h"
#include "DeletionMessage.h"

class UserTable
{

public:

	//USER SHIT
	//WRITE/UPDATE/PUT/DELETE
	static void registerUser(const mstring& username, const mstring& password, UserRoles role = UserRoles::Normal);

	//Admin has deleted the user's account
	static void deleteUser(mstring username, mstring adminMessage);
	static void deleteUser(DeletionMessage deletionMessage);
	//User has deleted their own account
	static void deleteUser(const mstring& username);

	//Admin restores the user's profile
	static void restoreUser(const mstring& username);

	//Exclude the user's account from the leaderboards
	static void excludeUser(const mstring& username);

	//Include the user's account in the leaderboards
	static void includeUser(const mstring& username);

	//Update the user's account
	static void updateUser(const User& user);

	//READ
	static User* getAllUsers(const mstring& tableFile, size_t& countOfUsers, bool includeDeleted = true);
	static User* getAllUsers(size_t& countOfUsers, bool includeDeleted = true);
	static User* getDeletedUsers(size_t& countOfUsers);

	//Make get functions work with predicates as parameters
	static User* getUser(const mstring& username, bool includeDeleted = true);

	static mstring getUserString(const mstring& username, const mstring& tableFile, size_t& startPos, size_t& endPos);
	static mstring getUserString(const mstring& username, size_t& startPos, size_t& endPos);

	static size_t getUsersCount();

	//Checks for validity
	static bool userIsRegistered(const mstring& username);
	static bool userIsRegisteredWithPassword(const mstring& username, const mstring& password);
	static bool usernameIsValid(const mstring& username);
	static bool passwordIsValid(const mstring& username);
	static bool userRoleIsValid(const mstring& role);

	//Miscallaneous
	static mstring createUserString(const mstring& username, const mstring& password, UserRoles role, int level, int lives, const mstring& lastExpression, int highscore, bool includeHighscore, bool isDeleted);
	static mstring createUserString(const User& user);
	static mstring createUserString(const mstring* fields, size_t fieldsCount);
	static User createUserFromString(mstring userString);
};

