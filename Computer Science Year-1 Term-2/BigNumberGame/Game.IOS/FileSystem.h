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
	static void adminDeleteUser_Common(mstring username);

public:

	//CONSTANTS
	static constexpr const char* USER_TABLE = "USER_TABLE.bin";
	static constexpr const char* DELETION_MESSAGES_TABLE = "DELETION_MESSAGES_TABLE.bin";

	//WRITE/UPDATE/PUT/DELETE
	static void overwriteTable(mstring tableData, const char* table);
	static void appendToTable(mstring appendData, const char* table);
	static mstring getTableAsString(const char* table);
	static size_t getCount(mstring tableFile);

	/**********************************************************************************************************************************/
	//USER SHIT
	//WRITE/UPDATE/PUT/DELETE
	static void registerUser(mstring username, mstring password, UserRoles role = UserRoles::Normal);

	//Admin has deleted the user's account
	static void deleteUser(mstring username, mstring adminMessage);
	static void deleteUser(DeletionMessage deletionMessage);
	//User has deleted their own account
	static void deleteUser(mstring username);

	//Admin restores the user's profile
	static void restoreUser(mstring username);

	//Exclude the user's account from the leaderboards
	static void excludeUser(mstring username);

	//Include the user's account in the leaderboards
	static void includeUser(mstring username);

	//READ
	static User* getAllUsers(mstring tableFile, size_t& countOfUsers, bool includeDeleted = true);
	static User* getAllUsers(size_t& countOfUsers, bool includeDeleted = true);
	static User* getDeletedUsers(size_t& countOfUsers);

	//Make get functions work with predicates as parameters
	static User* getUser(mstring username, bool includeDeleted = true);

	static mstring getUserString(mstring username, mstring tableFile, size_t& startPos, size_t& endPos);
	static mstring getUserString(mstring username, size_t& startPos, size_t& endPos);

	static size_t getUsersCount();

	//Checks for validity
	static bool stringContainsForbiddenSymbols(mstring text);
	static bool userIsValid(mstring username, mstring password, mstring role);
	static bool userIsRegistered(mstring username);
	static bool userIsRegisteredWithPassword(mstring username, mstring password);
	static bool usernameIsValid(mstring username);
	static bool passwordIsValid(mstring username);
	static bool userRoleIsValid(mstring role);

	//Miscallaneous
	static mstring createUserString(mstring username, mstring password, UserRoles role, int level, int lives, mstring lastExpression, bool includeHighscore, bool isDeleted);
	static mstring createUserString(const User& user);
	static mstring createUserString(const mstring* fields, size_t fieldsCount);
	static User createUserFromString(mstring userString);

	/**********************************************************************************************************************************/
	//Admin deletion messages shit
	//WRITE/UPDATE/PUT/DELETE
	static void addDeletionMessage(mstring message, mstring username);
	static void addDeletionMessage(DeletionMessage message);
	static void deleteMessage(mstring username);

	//READ
	static DeletionMessage* getAllDeletionMessages(size_t& countOfMessages);
	static DeletionMessage* getAllDeletionMessages(mstring tableFile, size_t& countOfMessages);
	static DeletionMessage getDeletionMessage(mstring username);
	static DeletionMessage getDeletionMessage(mstring tableFile, mstring username);

	static size_t getDeletionMessagesCount();

	static size_t getHighestId();
	static size_t getHighestId(mstring tableFile);

	//Checks for validity
	static bool deletionMessageExists(mstring username);
	static bool deletionMessageExists(mstring tableFile, mstring username);

	//Miscallaneous
	static mstring createMessageString(size_t id, mstring message, mstring username);
	static DeletionMessage createDeletionMessage(mstring message, mstring username);

};