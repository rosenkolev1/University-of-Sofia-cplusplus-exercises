#include "UserTable.h"
#include "DeletionMessageTable.h"
#include "FileSystem.h"
#include "..\Project.StringManipulation\MStringManip.h"

/* FileSystem::USER_TABLE
* ~
*	Username| Password| Role| Level| |Lives| Last Equation| Highscore| includeHighscore| isDeleted|
* ~
*/

bool UserTable::usernameIsValid(const mstring& username)
{
	//Check if the length of the username is too large or too small
	if (username.getSize() > User::USERNAME_LENGTH_MAX || username.getSize() < User::USERNAME_LENGTH_MIN) return false;

	//Check if username contains forbidden symbols
	return !FileSystem::stringContainsForbiddenSymbols(username);
}

bool UserTable::passwordIsValid(const mstring& password)
{
	//Check if the length of the username is too large or too small
	if (password.getSize() > User::PASSWORD_LENGTH_MAX || password.getSize() < User::PASSWORD_LENGTH_MIN) return false;

	//Check if username contains forbidden symbols
	return !FileSystem::stringContainsForbiddenSymbols(password);
}

bool UserTable::userRoleIsValid(const mstring& role)
{
	for (size_t i = 0; i < User::USER_ROLES_COUNT; i++)
	{
		if (role == User::USER_ROLES[i]) return true;
	}

	return false;
}

bool UserTable::userIsRegistered(const mstring& username)
{
	size_t allUsersCount = 0;
	const User* allUsers = getAllUsers(allUsersCount);

	for (size_t i = 0; i < allUsersCount; i++)
	{
		mstring otherUsername = allUsers[i].username;
		if (username == otherUsername)
		{
			return true;
		}
	}

	//Deallocate users array
	delete[] allUsers;

	return false;
}

bool UserTable::userIsRegisteredWithPassword(const mstring& username, const mstring& password)
{
	size_t allUsersCount = 0;
	const User* allUsers = getAllUsers(allUsersCount);

	for (size_t i = 0; i < allUsersCount; i++)
	{
		mstring otherUsername = allUsers[i].username;
		mstring otherPassword = allUsers[i].password;
		if (username == otherUsername && password == otherPassword)
		{
			return true;
		}
	}

	return false;
}

void UserTable::registerUser(const mstring& username, const mstring& password, UserRoles role)
{
	mstring dataToWriteToFile = createUserString(username, password, role, 0, GlobalConstants::PLAYING_LIVES_DEFAULT, FileSystem::FILESYSTEM_COLUMN_NULL, 0, true, false);

	FileSystem::appendToTable(dataToWriteToFile, FileSystem::USER_TABLE);
}

void UserTable::deleteUser(mstring username, mstring adminMessage)
{
	mstring userTableFileString = FileSystem::getTableAsString(FileSystem::USER_TABLE);

	//Get the start and end file pointer pos of the user which we need to delete
	size_t userStartPos = 0;
	size_t userEndPos = 0;
	mstring userString = getUserString(username, userTableFileString, userStartPos, userEndPos);

	//Get the isDeleted field and change it to true;
	User targetUser = createUserFromString(userString);
	targetUser.isDeleted = true;
	mstring newUserString = createUserString(targetUser);

	//Get the new user table file string
	mstring newUserTableFileString = MStringManip::replaceFrom(userTableFileString, newUserString, userStartPos, userEndPos);

	//Replace the new user string in the user table
	FileSystem::overwriteTable(newUserTableFileString, FileSystem::USER_TABLE);

	//Now add the new deletion message to the deletion message table
	DeletionMessageTable::addDeletionMessage(adminMessage, username);
}

void UserTable::deleteUser(DeletionMessage deletionMessage)
{
	deleteUser(deletionMessage.username, deletionMessage.message);
}

void UserTable::deleteUser(const mstring& username)
{
	mstring userTableFileString = FileSystem::getTableAsString(FileSystem::USER_TABLE);

	//Get the start and end file pointer pos of the user which we need to delete
	size_t userStartPos = 0;
	size_t userEndPos = 0;
	mstring userString = getUserString(username, userTableFileString, userStartPos, userEndPos);

	//Make the changes to the newDatabaseFileString, which we then write to the database file
	mstring newUserTableFileString = MStringManip::replaceFrom(userTableFileString, "", userStartPos, userEndPos);

	FileSystem::overwriteTable(newUserTableFileString, FileSystem::USER_TABLE);
}

void UserTable::restoreUser(const mstring& username)
{
	mstring userTableFileString = FileSystem::getTableAsString(FileSystem::USER_TABLE);

	//Get the start and end file pointer pos of the user which we need to delete
	size_t userStartPos = 0;
	size_t userEndPos = 0;
	mstring userString = getUserString(username, userTableFileString, userStartPos, userEndPos);

	//Get the isDeleted field and change it to false;
	User targetUser = createUserFromString(userString);
	targetUser.isDeleted = false;
	mstring newUserString = createUserString(targetUser);

	//Get the new user table file string
	mstring newUserTableFileString = MStringManip::replaceFrom(userTableFileString, newUserString, userStartPos, userEndPos);

	//Replace the new user string in the user table
	FileSystem::overwriteTable(newUserTableFileString, FileSystem::USER_TABLE);

	//Now remove the deletion message from the deletion message table
	DeletionMessageTable::deleteMessage(username);
}

void UserTable::excludeUser(const mstring& username)
{
	mstring userTableFileString = FileSystem::getTableAsString(FileSystem::USER_TABLE);

	//Get the start and end file pointer pos of the user which we need to delete
	size_t userStartPos = 0;
	size_t userEndPos = 0;
	mstring userString = getUserString(username, userTableFileString, userStartPos, userEndPos);

	//Get the includeHighscore field and change it to false;
	User targetUser = createUserFromString(userString);
	targetUser.includeHighscore = false;
	mstring newUserString = createUserString(targetUser);

	//Get the new user table file string
	mstring newUserTableFileString = MStringManip::replaceFrom(userTableFileString, newUserString, userStartPos, userEndPos);

	//Replace the new user string in the user table
	FileSystem::overwriteTable(newUserTableFileString, FileSystem::USER_TABLE);
}

void UserTable::includeUser(const mstring& username)
{
	mstring userTableFileString = FileSystem::getTableAsString(FileSystem::USER_TABLE);

	//Get the start and end file pointer pos of the user which we need to delete
	size_t userStartPos = 0;
	size_t userEndPos = 0;
	mstring userString = getUserString(username, userTableFileString, userStartPos, userEndPos);

	//Get the includeHighscore field and change it to true;
	User targetUser = createUserFromString(userString);
	targetUser.includeHighscore = true;
	mstring newUserString = createUserString(targetUser);

	//Get the new user table file string
	mstring newUserTableFileString = MStringManip::replaceFrom(userTableFileString, newUserString, userStartPos, userEndPos);

	//Replace the new user string in the user table
	FileSystem::overwriteTable(newUserTableFileString, FileSystem::USER_TABLE);
}

void UserTable::updateUser(const User& user)
{
	//Get the current user table
	mstring userTableFileString = FileSystem::getTableAsString(FileSystem::USER_TABLE);

	//Get the current user string
	size_t startPos = 0;
	size_t endPos = 0;
	mstring oldUserString = getUserString(user.username, startPos, endPos);

	//Create the new user string
	mstring newUserString = createUserString(user);

	//Replace the current user string with the new one
	mstring newUserTableFileString = MStringManip::replaceFrom(userTableFileString, newUserString, startPos, endPos);

	FileSystem::overwriteTable(newUserTableFileString, FileSystem::USER_TABLE);
}

size_t UserTable::getUsersCount()
{
	mstring tableFile = FileSystem::getTableAsString(FileSystem::USER_TABLE);
	return FileSystem::getCount(tableFile);
}

User* UserTable::getAllUsers(const mstring& tableFile, size_t& countOfUsers, bool includeDeleted)
{
	countOfUsers = FileSystem::getCount(tableFile);

	//Return nullptr if users are 0
	if (countOfUsers == 0)
	{
		return nullptr;
	}

	User* users = new User[countOfUsers];

	size_t deletedUsersCount = 0;

	size_t usersStringsCount = countOfUsers;
	mstring* usersStrings = MStringManip::splitString(tableFile, FileSystem::FILESYSTEM_ENTRY_DELIMITER, usersStringsCount);

	for (size_t i = 0; i < countOfUsers; i++)
	{
		users[i] = createUserFromString(usersStrings[i]);
		if (users[i].isDeleted) deletedUsersCount++;
	}

	//Filter out the deleted users
	if (!includeDeleted)
	{
		User* notDeletedUsers = new User[countOfUsers - deletedUsersCount];
		size_t notDeletedUsersIndex = 0;
		for (size_t i = 0; i < countOfUsers; i++)
		{
			if (users[i].isDeleted == false) notDeletedUsers[notDeletedUsersIndex++] = users[i];
		}

		//Deallocate dynamic memory
		delete[] users;

		countOfUsers -= deletedUsersCount;

		return notDeletedUsers;
	}

	return users;
}

User* UserTable::getAllUsers(size_t& countOfUsers, bool includeDeleted)
{
	mstring tableFile = FileSystem::getTableAsString(FileSystem::USER_TABLE);
	return getAllUsers(tableFile, countOfUsers, includeDeleted);
}

User* UserTable::getDeletedUsers(size_t& countOfUsers)
{
	User* allUsers = getAllUsers(countOfUsers);

	size_t countOfDeletedUsers = 0;
	User* notDeletedUsers = new User[countOfUsers];
	size_t notDeletedUsersIndex = 0;

	for (size_t i = 0; i < countOfUsers; i++)
	{
		if (allUsers[i].isDeleted == true)
		{
			notDeletedUsers[countOfDeletedUsers++] = allUsers[i];
		}
	}

	//Deallocate dynamic memory
	delete[] allUsers;

	//Copy the notDeleted users in a smaller array
	User* notDeletedUsersCopy = new User[countOfDeletedUsers];
	for (size_t i = 0; i < countOfDeletedUsers; i++)
	{
		notDeletedUsersCopy[i] = notDeletedUsers[i];
	}
	delete[] notDeletedUsers;
	notDeletedUsers = notDeletedUsersCopy;

	//Set the true count of the users
	countOfUsers = countOfDeletedUsers;

	return notDeletedUsers;
}

User* UserTable::getUser(const mstring& username, bool includeDeleted)
{
	size_t usersCount = 0;
	User* allUsers = getAllUsers(usersCount);
	User* user = nullptr;

	for (size_t i = 0; i < usersCount; i++)
	{
		if (allUsers[i].username == username)
		{
			if (includeDeleted == false && allUsers[i].isDeleted == true)
			{
				//User was found in the database, but he is deleted, and since the functions asks for non-deleted, we return nullptr
				return nullptr;
			}
			else
			{
				user = new User(allUsers[i]);
				delete[] allUsers;
				return user;
			}
		}
	}

	//User was not found in the database, so return nullptr
	return nullptr;
}

mstring UserTable::getUserString(const mstring& username, const mstring& tableFile, size_t& startPos, size_t& endPos)
{
	size_t currentColumnCounter = 1;
	bool currentColIsUsername = true;
	mstring currentUsername;
	bool foundCurrentUser = false;
	bool hasDelimBefore = false;
	bool hasDelimAfter = false;
	for (size_t i = 0; i < tableFile.getSize(); i++)
	{
		//We have found the index of the entry delim right after the user ends
		if (foundCurrentUser && tableFile[i] == FileSystem::FILESYSTEM_ENTRY_DELIMITER)
		{
			endPos = i;
			break;
		}
		if (tableFile[i] == FileSystem::FILESYSTEM_COLUMN_DELIMITER || tableFile[i] == FileSystem::FILESYSTEM_ENTRY_DELIMITER)
		{
			currentColumnCounter++;
			if (currentColIsUsername)
			{
				//if we found the username, then get the entry pos that is right at the start of the username
				if (currentUsername == username)
				{
					startPos = i - username.getSize();
					foundCurrentUser = true;
				}
				//Reset the currentUsername
				currentColIsUsername = false;

				currentUsername = "";
			}
		}
		//Check if we are currently on the first, i.e. the username colummn
		else if (currentColumnCounter % User::USER_FIELDS_COUNT == 1)
		{
			if (!currentColIsUsername) currentColIsUsername = true;
			currentUsername += tableFile[i];
		}
	}

	if (foundCurrentUser)
	{
		mstring userString = MStringManip::getFrom(tableFile, startPos, endPos);

		return userString;
	}
	else
	{
		throw "The user has not been found";
	}
}

mstring UserTable::getUserString(const mstring& username, size_t& startPos, size_t& endPos)
{
	mstring tableFile = FileSystem::getTableAsString(FileSystem::USER_TABLE);
	return getUserString(username, tableFile, startPos, endPos);
}

mstring UserTable::createUserString(const mstring& username, const mstring& password, UserRoles role, int level, int lives, const mstring& lastExpression, int highscore, bool includeHighscore, bool isDeleted)
{
	User user(username, password, role, level, lives, lastExpression, highscore, includeHighscore, isDeleted);

	return createUserString(user);
}

mstring UserTable::createUserString(const User& user)
{
	mstring userString;

	//Enter the username
	userString += user.username;

	//This is the delimiter between the different columns of the table
	userString += FileSystem::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the password
	userString += user.password;

	//This is the delimiter between the different columns of the table
	userString += FileSystem::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the role of the user, which is normal by default
	userString += user.getRoleString();

	//This is the delimiter between the different columns of the table
	userString += FileSystem::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the current level of the user
	userString += user.getLevelString();

	//This is the delimiter between the different columns of the table
	userString += FileSystem::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the current lives of the user
	userString += user.getLivesString();

	//This is the delimiter between the different columns of the table
	userString += FileSystem::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the last equation of the user, which is NULL since this user is new
	userString += user.lastExpression;

	//This is the delimiter between the different columns of the table
	userString += FileSystem::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the current highscore of the user
	userString += user.getHighscoreString();

	//This is the delimiter between the different columns of the table
	userString += FileSystem::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the includeHighscore
	userString += user.getIncludeHighscoreString();

	//This is the delimiter between the different columns of the table
	userString += FileSystem::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the isDeleted of the user
	userString += user.getIsDeletedString();

	//This is the delimiter between the different columns of the table
	userString += FileSystem::FILESYSTEM_ENTRY_DELIMITER;

	return userString;
}

mstring UserTable::createUserString(const mstring* fields, size_t fieldsCount)
{
	mstring userString;
	for (int i = 0; i < fieldsCount - 1; i++)
	{
		userString += fields[i];
		userString += FileSystem::FILESYSTEM_COLUMN_DELIMITER;
	}

	userString += fields[fieldsCount - 1];
	userString += FileSystem::FILESYSTEM_ENTRY_DELIMITER;

	return userString;
}

User UserTable::createUserFromString(mstring userString)
{
	size_t fieldsCount = 0;
	userString = MStringManip::replaceAll(userString, FileSystem::FILESYSTEM_ENTRY_DELIMITER, "");

	mstring* fields = MStringManip::splitString(userString, FileSystem::FILESYSTEM_COLUMN_DELIMITER, fieldsCount);

	mstring username = fields[0];
	mstring password = fields[1];

	int roleInt = -1;
	//Get the role for the user
	for (size_t i = 0; i < User::USER_ROLES_COUNT; i++)
	{
		if (fields[2] == User::USER_ROLES[i])
		{
			roleInt = i;
			break;
		}
	}
	UserRoles role = (UserRoles)roleInt;

	int level = MStringManip::parseToLong(fields[3]);
	int lives = MStringManip::parseToLong(fields[4]);
	mstring lastExpression = fields[5];
	int highscore = MStringManip::parseToLong(fields[6]);
	bool includeHighscore = (fields[7] == FileSystem::FILESYSTEM_TRUE ? true : false);
	bool isDeleted = (fields[8] == FileSystem::FILESYSTEM_TRUE ? true : false);

	return User(username, password, role, level, lives, lastExpression, highscore, includeHighscore, isDeleted);
}
