#pragma once

#include "..\Game.GlobalConstants\GlobalConstants.h"
#include "User.h"
#include<fstream>
#include "DeletionMessage.h"

class FileSystem
{
	//TODO: Change all the params of the functions to & so no needless copying is being made
	//TODO: Replace constexpr const char* with mstring and have it work by casting mstring to const char* or by making a function for getting the const char* data from mstring
private:
	static void adminDeleteUser_Common(const mstring& username);

public:

	//CONSTANTS
	static constexpr const char* USER_TABLE = "USER_TABLE.bin";
	static constexpr const char* DELETION_MESSAGES_TABLE = "DELETION_MESSAGES_TABLE.bin";

	//WRITE/UPDATE/PUT/DELETE
	static void overwriteTable(const mstring& tableData, const char* table);
	static void appendToTable(const mstring& appendData, const char* table);
	static mstring getTableAsString(const char* table);
	static size_t getCount(const mstring& tableFile);

	/**********************************************************************************************************************************/
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
	static bool stringContainsForbiddenSymbols(const mstring& text);
	static bool userIsValid(const mstring& username, const mstring& password, const mstring& role);
	static bool userIsRegistered(const mstring& username);
	static bool userIsRegisteredWithPassword(const mstring& username, const mstring& password);
	static bool usernameIsValid(const mstring& username);
	static bool passwordIsValid(const mstring& username);
	static bool userRoleIsValid(const mstring& role);

	//Miscallaneous
	static mstring createUserString(const mstring& username, const mstring& password, UserRoles role, int level, int lives, const mstring& lastExpression, bool includeHighscore, bool isDeleted);
	static mstring createUserString(const User& user);
	static mstring createUserString(const mstring* fields, size_t fieldsCount);
	static User createUserFromString(mstring userString);

	/**********************************************************************************************************************************/
	//Admin deletion messages shit
	//WRITE/UPDATE/PUT/DELETE
	static void addDeletionMessage(const mstring& message, const mstring& username);
	static void addDeletionMessage(const DeletionMessage& message);
	static void deleteMessage(const mstring& username);

	//READ
	static DeletionMessage* getAllDeletionMessages(size_t& countOfMessages);
	static DeletionMessage* getAllDeletionMessages(const mstring& tableFile, size_t& countOfMessages);
	static DeletionMessage getDeletionMessage(const mstring& username);
	static DeletionMessage getDeletionMessage(const mstring& tableFile, const mstring& username);

	static size_t getDeletionMessagesCount();

	static size_t getHighestId();
	static size_t getHighestId(const mstring& tableFile);

	//Checks for validity
	static bool deletionMessageExists(const mstring& username);
	static bool deletionMessageExists(const mstring& tableFile, const mstring& username);

	//Miscallaneous
	static mstring createMessageString(size_t id, const mstring& message, const mstring& username);
	static DeletionMessage createDeletionMessage(const mstring& message, const mstring& username);

};