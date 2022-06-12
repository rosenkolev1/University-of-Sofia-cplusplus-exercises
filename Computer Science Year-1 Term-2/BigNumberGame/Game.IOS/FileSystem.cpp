#pragma once

#include "FileSystem.h"
#include "..\Project.StringManipulation\MStringManip.h"

/* USER_TABLE
* ~
*	Username| Password| Role| Level| |Lives| Last Equation| Highscore| includeHighscore| isDeleted|
* ~
*/

/* DELETION_MESSAGE_TABLE
* ~
*	Id| Message| Username| 
* ~
*/

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

void FileSystem::adminDeleteUser_Common(const mstring& username)
{
	mstring userTableFileString = getTableAsString(USER_TABLE);

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
	overwriteTable(newUserTableFileString, USER_TABLE);
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

bool FileSystem::usernameIsValid(const mstring& username)
{
	//Check if the length of the username is too large or too small
	if (username.getSize() > User::USERNAME_LENGTH_MAX || username.getSize() < User::USERNAME_LENGTH_MIN) return false;

	//Check if username contains forbidden symbols
	return !stringContainsForbiddenSymbols(username);
}

bool FileSystem::passwordIsValid(const mstring& password)
{
	//Check if the length of the username is too large or too small
	if (password.getSize() > User::PASSWORD_LENGTH_MAX || password.getSize() < User::PASSWORD_LENGTH_MIN) return false;

	//Check if username contains forbidden symbols
	return !stringContainsForbiddenSymbols(password);
}

bool FileSystem::userRoleIsValid(const mstring& role)
{
	for (size_t i = 0; i < User::USER_ROLES_COUNT; i++)
	{
		if (role == User::USER_ROLES[i]) return true;
	}

	return false;
}

bool FileSystem::userIsValid(const mstring& username, const mstring& password, const mstring& role)
{
	//Check if the formatting of the username and password is valid
	//Check if the username or password are already contained in the database
	//Check if the roles is correct
	return usernameIsValid(username) && passwordIsValid(password) && userRoleIsValid(role) && !userIsRegistered(username);
}

bool FileSystem::userIsRegistered(const mstring& username)
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

bool FileSystem::userIsRegisteredWithPassword(const mstring& username, const mstring& password)
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

void FileSystem::registerUser(const mstring& username, const mstring& password, UserRoles role)
{
	mstring dataToWriteToFile = createUserString(username, password, role, 0, GlobalConstants::PLAYING_LIVES_DEFAULT, FILESYSTEM_COLUMN_NULL, 0, true, false);

	appendToTable(dataToWriteToFile, USER_TABLE);
}

void FileSystem::deleteUser(mstring username, mstring adminMessage)
{
	adminDeleteUser_Common(username);

	//Now add the new deletion message to the deletion message table
	addDeletionMessage(adminMessage, username);
}

void FileSystem::deleteUser(DeletionMessage deletionMessage)
{
	adminDeleteUser_Common(deletionMessage.username);

	//Now add the new deletion message to the deletion message table
	addDeletionMessage(deletionMessage);
}

void FileSystem::deleteUser(const mstring& username)
{
	mstring userTableFileString = getTableAsString(USER_TABLE);

	//Get the start and end file pointer pos of the user which we need to delete
	size_t userStartPos = 0;
	size_t userEndPos = 0;
	mstring userString = getUserString(username, userTableFileString, userStartPos, userEndPos);

	//Make the changes to the newDatabaseFileString, which we then write to the database file
	mstring newUserTableFileString = MStringManip::replaceFrom(userTableFileString, "", userStartPos, userEndPos);

	overwriteTable(newUserTableFileString, USER_TABLE);
}

void FileSystem::restoreUser(const mstring& username)
{
	mstring userTableFileString = getTableAsString(USER_TABLE);

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
	overwriteTable(newUserTableFileString, USER_TABLE);

	//Now remove the deletion message from the deletion message table
	deleteMessage(username);
}

void FileSystem::excludeUser(const mstring& username)
{
	mstring userTableFileString = getTableAsString(USER_TABLE);

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
	overwriteTable(newUserTableFileString, USER_TABLE);
}

void FileSystem::includeUser(const mstring& username)
{
	mstring userTableFileString = getTableAsString(USER_TABLE);

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
	overwriteTable(newUserTableFileString, USER_TABLE);
}

void FileSystem::updateUser(const User& user)
{
	//Get the current user table
	mstring userTableFileString = getTableAsString(USER_TABLE);

	//Get the current user string
	size_t startPos = 0;
	size_t endPos = 0;
	mstring oldUserString = getUserString(user.username, startPos, endPos);

	//Create the new user string
	mstring newUserString = createUserString(user);

	//Replace the current user string with the new one
	mstring newUserTableFileString = MStringManip::replaceFrom(userTableFileString, newUserString, startPos, endPos);

	overwriteTable(newUserTableFileString, USER_TABLE);
}

size_t FileSystem::getUsersCount()
{
	mstring tableFile = getTableAsString(USER_TABLE);
	return getCount(tableFile);
}

User* FileSystem::getAllUsers(const mstring& tableFile, size_t& countOfUsers, bool includeDeleted)
{
	countOfUsers = getCount(tableFile);

	//Return nullptr if users are 0
	if (countOfUsers == 0)
	{
		return nullptr;
	}

	User* users = new User[countOfUsers];
	size_t currentUserIndex = 0;
	size_t deletedUsersCount = 0;

	//Read the database data and parse it to a class
	mstring dataRead;
	UserFields currentUserField = UserFields::Username;
	size_t tableFileIndex = 0;

	while (true)
	{
		char newSymbol = '\0';

		if (tableFileIndex >= tableFile.getSize())
		{
			break;
		}
		else
		{
			newSymbol = tableFile[tableFileIndex++];
		}

		//Check if the built up buffer data should be flushed into the user
		bool shouldFlushData = (newSymbol == FILESYSTEM_COLUMN_DELIMITER ||
			newSymbol == FILESYSTEM_ENTRY_DELIMITER);

		if (!shouldFlushData) dataRead += newSymbol;

		if (shouldFlushData)
		{
			if (currentUserField == UserFields::Username)
			{
				users[currentUserIndex].setUsername(dataRead);
				currentUserField = UserFields::Password;
			}
			else if (currentUserField == UserFields::Password)
			{
				users[currentUserIndex].setPassword(dataRead);
				currentUserField = UserFields::Role;
			}
			else if (currentUserField == UserFields::Role)
			{
				//Set the role of the user if it exists. If not, throw an error
				users[currentUserIndex].setRole(dataRead);
				currentUserField = UserFields::Level;
			}
			else if (currentUserField == UserFields::Level)
			{
				users[currentUserIndex].level = MStringManip::parseToLong(dataRead);
				currentUserField = UserFields::Lives;
			}
			else if (currentUserField == UserFields::Lives)
			{
				users[currentUserIndex].lives = MStringManip::parseToLong(dataRead);
				currentUserField = UserFields::LastExpression;
			}
			else if (currentUserField == UserFields::LastExpression)
			{
				users[currentUserIndex].lastExpression = dataRead;
				currentUserField = UserFields::Highscore;
			}
			else if (currentUserField == UserFields::Highscore)
			{
				users[currentUserIndex].highscore = MStringManip::parseToLong(dataRead);
				currentUserField = UserFields::IncludeHighscore;
			}
			else if (currentUserField == UserFields::IncludeHighscore)
			{
				users[currentUserIndex].includeHighscore = dataRead == FILESYSTEM_TRUE;
				currentUserField = UserFields::IsDeleted;
			}
			else if (currentUserField == UserFields::IsDeleted)
			{
				users[currentUserIndex].isDeleted = dataRead == FILESYSTEM_TRUE;
				if (users[currentUserIndex].isDeleted) deletedUsersCount++;
			}

			//Reset the dataRead
			dataRead = "";

			if (newSymbol == FILESYSTEM_ENTRY_DELIMITER)
			{
				currentUserIndex++;
				currentUserField = UserFields::Username;

				if (currentUserIndex >= countOfUsers) break;
			}
		}

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

User* FileSystem::getAllUsers(size_t& countOfUsers, bool includeDeleted)
{
	mstring tableFile = getTableAsString(USER_TABLE);
	return getAllUsers(tableFile, countOfUsers, includeDeleted);
}

User* FileSystem::getDeletedUsers(size_t& countOfUsers)
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

User* FileSystem::getUser(const mstring& username, bool includeDeleted)
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

mstring FileSystem::getUserString(const mstring& username, const mstring& tableFile, size_t& startPos, size_t& endPos)
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
		if (foundCurrentUser && tableFile[i] == FILESYSTEM_ENTRY_DELIMITER)
		{
			endPos = i;
			break;
		}
		if (tableFile[i] == FILESYSTEM_COLUMN_DELIMITER || tableFile[i] == FILESYSTEM_ENTRY_DELIMITER)
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

mstring FileSystem::getUserString(const mstring& username, size_t& startPos, size_t& endPos)
{
	mstring tableFile = getTableAsString(USER_TABLE);
	return getUserString(username, tableFile, startPos, endPos);
}

mstring FileSystem::createUserString(const mstring& username, const mstring& password, UserRoles role, int level, int lives, const mstring& lastExpression, int highscore, bool includeHighscore, bool isDeleted)
{
	mstring userString;

	//Enter the username
	userString += username;

	//This is the delimiter between the different columns of the table
	userString += FILESYSTEM_COLUMN_DELIMITER;

	//Enter the password
	userString += password;

	//This is the delimiter between the different columns of the table
	userString += FILESYSTEM_COLUMN_DELIMITER;

	mstring roleString = User::USER_ROLES[(int)role];
	//Enter the role of the user, which is normal by default
	userString += roleString;

	//This is the delimiter between the different columns of the table
	userString += FILESYSTEM_COLUMN_DELIMITER;

	//Enter the current level of the user
	userString += MStringManip::parseToString(level);

	//This is the delimiter between the different columns of the table
	userString += FILESYSTEM_COLUMN_DELIMITER;

	//Enter the current lives of the user
	userString += MStringManip::parseToString(lives);

	//This is the delimiter between the different columns of the table
	userString += FILESYSTEM_COLUMN_DELIMITER;

	//Enter the last equation of the user, which is NULL since this user is new
	userString += lastExpression;

	//This is the delimiter between the different columns of the table
	userString += FILESYSTEM_COLUMN_DELIMITER;

	//Enter the current highscore of the user
	userString += MStringManip::parseToString(highscore);

	//This is the delimiter between the different columns of the table
	userString += FILESYSTEM_COLUMN_DELIMITER;

	//Enter the includeHighscore
	userString += (includeHighscore ? FILESYSTEM_TRUE : FILESYSTEM_FALSE);

	//This is the delimiter between the different columns of the table
	userString += FILESYSTEM_COLUMN_DELIMITER;

	//Enter the isDeleted of the user
	userString += (isDeleted ? FILESYSTEM_TRUE : FILESYSTEM_FALSE);

	//This is the delimiter between the different columns of the table
	userString += FILESYSTEM_ENTRY_DELIMITER;

	return userString;
}

mstring FileSystem::createUserString(const User& user)
{
	return createUserString(user.username, user.password, user.role, user.level, user.lives, user.lastExpression, user.highscore, user.includeHighscore, user.isDeleted);
}

mstring FileSystem::createUserString(const mstring* fields, size_t fieldsCount)
{
	mstring userString;
	for (int i = 0; i < fieldsCount - 1; i++)
	{
		userString += fields[i];
		userString += FILESYSTEM_COLUMN_DELIMITER;
	}

	userString += fields[fieldsCount - 1];
	userString += FILESYSTEM_ENTRY_DELIMITER;

	return userString;
}

User FileSystem::createUserFromString(mstring userString)
{
	size_t fieldsCount = 0;
	userString = MStringManip::replaceAll(userString, FILESYSTEM_ENTRY_DELIMITER, "");

	mstring* fields = MStringManip::splitString(userString, FILESYSTEM_COLUMN_DELIMITER, fieldsCount);

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
	bool includeHighscore = (fields[7] == FILESYSTEM_TRUE ? true : false);
	bool isDeleted = (fields[8] == FILESYSTEM_TRUE ? true : false);

	return User(username, password, role, level, lives, lastExpression, highscore, includeHighscore, isDeleted);
}

/**********************************************************************************************************************************/

void FileSystem::addDeletionMessage(const mstring& message, const mstring& username)
{
	mstring tableFile = getTableAsString(DELETION_MESSAGES_TABLE);
	size_t highestId = getHighestId(tableFile);

	addDeletionMessage(DeletionMessage(highestId + 1, message, username));
}

void FileSystem::addDeletionMessage(const DeletionMessage& message)
{
	mstring dataToWriteToFile = createMessageString(message.id, message.message, message.username);

	appendToTable(dataToWriteToFile, DELETION_MESSAGES_TABLE);
}

void FileSystem::deleteMessage(const mstring& username)
{
	mstring tableFile = getTableAsString(DELETION_MESSAGES_TABLE);
	size_t countOfMessages = 0;
	
	mstring newTableFile;

	//Get all deletion messages
	DeletionMessage* messages = getAllDeletionMessages(tableFile, countOfMessages);

	bool hasRemovedMessage = false;

	//Remove the message
	for (size_t i = 0; i < countOfMessages; i++)
	{
		if (messages[i].username != username)
		{
			mstring messageString = createMessageString(messages[i].id, messages[i].message, messages[i].username);
			newTableFile += messageString;
		}
		else hasRemovedMessage = true;
	}

	//Dealloc dynamic memory
	delete[] messages;

	if (!hasRemovedMessage) throw "The message was not found!";

	overwriteTable(newTableFile, DELETION_MESSAGES_TABLE);
}

mstring FileSystem::createMessageString(size_t id, const mstring& message, const mstring& username)
{
	mstring messageString;
	//Enter the Id
	messageString += MStringManip::parseToString(id);

	//This is the delimiter between the different columns of the table
	messageString += FILESYSTEM_COLUMN_DELIMITER;

	//Enter the message
	messageString += message;

	//This is the delimiter between the different columns of the table
	messageString += FILESYSTEM_COLUMN_DELIMITER;

	//Enter the username
	messageString += username;

	//This is the delimiter between the different columns of the table
	messageString += FILESYSTEM_ENTRY_DELIMITER;

	return messageString;
}

DeletionMessage FileSystem::createDeletionMessage(const mstring& message, const mstring& username)
{
	size_t highestId = getHighestId();
	return DeletionMessage(highestId + 1, message, username);
}

DeletionMessage* FileSystem::getAllDeletionMessages(size_t& countOfMessages)
{
	mstring tableFile = getTableAsString(DELETION_MESSAGES_TABLE);
	return getAllDeletionMessages(tableFile, countOfMessages);
}

DeletionMessage* FileSystem::getAllDeletionMessages(const mstring& tableFile, size_t& countOfMessages)
{
	//Get all the message strings
	mstring* entries = MStringManip::splitString(tableFile, FILESYSTEM_ENTRY_DELIMITER, countOfMessages);
	countOfMessages--;

	DeletionMessage* messages = new DeletionMessage[countOfMessages];

	for (size_t i = 0; i < countOfMessages; i++)
	{
		//Get all the fields for all the messages
		size_t fieldsCount = 0;
		mstring* fields = MStringManip::splitString(entries[i], FILESYSTEM_COLUMN_DELIMITER, fieldsCount);
		//Set the message id
		messages[i].id = MStringManip::parseToLong(fields[0]);
		//Set the message
		messages[i].message = fields[1];
		//Set the username
		messages[i].username = fields[2];

		//Dealloc dynamic memory
		delete[] fields;
	}

	//Dealloc dynamic memory
	delete[] entries;

	return messages;
}

DeletionMessage FileSystem::getDeletionMessage(const mstring& username)
{
	mstring tableFile = getTableAsString(DELETION_MESSAGES_TABLE);
	return getDeletionMessage(tableFile, username);
}

DeletionMessage FileSystem::getDeletionMessage(const mstring& tableFile, const mstring& username)
{
	size_t countOfMessages = 0;
	DeletionMessage* messages = getAllDeletionMessages(tableFile, countOfMessages);
	size_t indexOfMessage = 0;
	bool foundUser = false;

	for (size_t i = 0; i < countOfMessages; i++)
	{
		if (messages[i].username == username)
		{
			indexOfMessage = i;
			foundUser = true;
			break;
		}
	}

	if (!foundUser) throw "User has not been found!";

	DeletionMessage copyOfMessage = messages[indexOfMessage];
	
	//Dealloc dynamic memory
	delete[] messages;

	return copyOfMessage;
}

size_t FileSystem::getDeletionMessagesCount()
{
	mstring tableFile = getTableAsString(DELETION_MESSAGES_TABLE);
	return getCount(tableFile);
}

size_t FileSystem::getHighestId()
{
	mstring tableFile = getTableAsString(DELETION_MESSAGES_TABLE);
	return getHighestId(tableFile);
}

size_t FileSystem::getHighestId(const mstring& tableFile)
{
	size_t entriesCount = 0;
	mstring* entries = MStringManip::splitString(tableFile, FILESYSTEM_ENTRY_DELIMITER, entriesCount);
	entriesCount--;

	//Get the id from the last entry
	size_t firstColumnDelimIndex = MStringManip::findIndex(entries[entriesCount - 1], FILESYSTEM_COLUMN_DELIMITER);
	size_t highestId = MStringManip::parseToLong(MStringManip::getFrom(entries[entriesCount - 1], 0, firstColumnDelimIndex - 1));

	//Dealloc dynamic memory
	delete[] entries;

	return highestId;
}

bool FileSystem::deletionMessageExists(const mstring& tableFile, const mstring& username)
{
	size_t countOfMessages = 0;
	DeletionMessage* messages = getAllDeletionMessages(tableFile, countOfMessages);
	bool foundUser = false;

	for (size_t i = 0; i < countOfMessages; i++)
	{
		if (messages[i].username == username)
		{
			//Dealloc dynamic memory
			delete[] messages;

			return true;
		}
	}

	//Dealloc dynamic memory
	delete[] messages;

	return false;
}

bool FileSystem::deletionMessageExists(const mstring& username)
{
	mstring tableFile = getTableAsString(DELETION_MESSAGES_TABLE);
	return deletionMessageExists(tableFile, username);
}


