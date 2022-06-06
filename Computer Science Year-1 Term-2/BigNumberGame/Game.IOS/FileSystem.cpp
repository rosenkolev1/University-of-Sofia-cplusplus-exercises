#pragma once

#include "FileSystem.h"
#include "..\Project.StringManipulation\MStringManip.h"

/*
* ~
*	Username| Password| Role| Level| |Lives| Last Equation| includeHighscore| isDeleted|
* ~
*/

bool FileSystem::stringContainsForbiddenSymbols(mstring text)
{
	for (size_t i = 0; i < text.getSize(); i++)
	{
		for (size_t y = 0; y < strlen(GlobalConstants::FORBIDDEN_SYMBOLS); y++)
		{
			if (text[i] == GlobalConstants::FORBIDDEN_SYMBOLS[y]) return true;
		}
	}
	return false;
}

bool FileSystem::usernameIsValid(mstring username)
{
	//Check if the length of the username is too large or too small
	if (username.getSize() > GlobalConstants::USERNAME_LENGTH_MAX || username.getSize() < GlobalConstants::USERNAME_LENGTH_MIN) return false;

	//Check if username contains forbidden symbols
	return !stringContainsForbiddenSymbols(username);
}

bool FileSystem::passwordIsValid(mstring password)
{
	//Check if the length of the username is too large or too small
	if (password.getSize() > GlobalConstants::PASSWORD_LENGTH_MAX || password.getSize() < GlobalConstants::PASSWORD_LENGTH_MIN) return false;

	//Check if username contains forbidden symbols
	return !stringContainsForbiddenSymbols(password);
}

bool FileSystem::userRoleIsValid(mstring role)
{
	for (size_t i = 0; i < GlobalConstants::USER_ROLES_COUNT; i++)
	{
		if (role == GlobalConstants::USER_ROLES[i]) return true;
	}

	return false;
}

bool FileSystem::userIsValid(mstring username, mstring password, mstring role)
{
	//Check if the formatting of the username and password is valid
	//Check if the username or password are already contained in the database
	//Check if the roles is correct
	return usernameIsValid(username) && passwordIsValid(password) && userRoleIsValid(role) && !userIsRegistered(username);
}

bool FileSystem::userIsRegistered(mstring username)
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

bool FileSystem::userIsRegisteredWithPassword(mstring username, mstring password)
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

mstring FileSystem::getDatabaseAsString()
{
	std::ifstream databaseFile("Database.bin", std::ios::binary);

	//Check if database file is open
	if (!databaseFile.is_open())
	{
		//Database file doesn't exist, i.e. there are not registered people yet!
		return "";
	}

	mstring databaseData;
	while (!databaseFile.eof())
	{
		mstring newLine;
		databaseFile >> newLine;
		
		databaseData += newLine + "\n";
	}

	//Remove all \n at end of databaseData and then add just one
	while (databaseData.peek() == '\n') databaseData.pop();

	databaseData += '\n';

	databaseFile.close();

	return databaseData;
}

void FileSystem::overwriteDatabase(mstring databaseData)
{
	std::ofstream databaseFile("Database.bin", std::ios::binary | std::ios::trunc);

	//Check if database file is open
	if (!databaseFile.is_open())
	{
		//throw some error
		throw "Fuck this shit I'm out ";
	}

	databaseFile << databaseData;

	databaseFile.close();
}

void FileSystem::registerUser(mstring username, mstring password, UserRoles role)
{
	std::ofstream databaseFile("Database.bin", std::ios::binary | std::ios::app);

	//Check if database file is open
	if (!databaseFile.is_open())
	{
		//throw some error
		throw "Fuck this shit I'm out ";
	}

	size_t dataSize = 0;
	mstring dataToWriteToFile;

	//Enter the username
	dataToWriteToFile += username;

	//This is the delimiter between the different columns of the table
	dataToWriteToFile += GlobalConstants::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the password
	dataToWriteToFile += password;

	//This is the delimiter between the different columns of the table
	dataToWriteToFile += GlobalConstants::FILESYSTEM_COLUMN_DELIMITER;

	mstring roleString = GlobalConstants::USER_ROLES[(int)role];
	//Enter the role of the user, which is normal by default
	dataToWriteToFile += roleString;

	//This is the delimiter between the different columns of the table
	dataToWriteToFile += GlobalConstants::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the current level of the user, which is 0 since this user is new
	dataToWriteToFile += '0';

	//This is the delimiter between the different columns of the table
	dataToWriteToFile += GlobalConstants::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the current lives of the user, which is 3 since this user is new
	dataToWriteToFile += '3';

	//This is the delimiter between the different columns of the table
	dataToWriteToFile += GlobalConstants::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the last equation of the user, which is NULL since this user is new
	dataToWriteToFile += GlobalConstants::FILESYSTEM_COLUMN_NULL;

	//This is the delimiter between the different columns of the table
	dataToWriteToFile += GlobalConstants::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the includeHighscore, which is true since this user is new
	dataToWriteToFile += GlobalConstants::FILESYSTEM_TRUE;

	//This is the delimiter between the different columns of the table
	dataToWriteToFile += GlobalConstants::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the isDeleted of the user, which is false since this user is new
	dataToWriteToFile += GlobalConstants::FILESYSTEM_FALSE;

	//This is the delimiter between the different columns of the table
	dataToWriteToFile += GlobalConstants::FILESYSTEM_ENTRY_DELIMITER;

	databaseFile << dataToWriteToFile;

	//Close database connection
	databaseFile.close();
}

void FileSystem::deleteUser(mstring username, mstring adminMessage)
{
	
}

void FileSystem::deleteUser(mstring username)
{
	mstring databaseFileString = getDatabaseAsString();

	//Get the start and end file pointer pos of the user which we need to delete
	size_t userStartPos = 0;
	size_t userEndPos = 0;
	mstring userString = getUserString(username, databaseFileString, userStartPos, userEndPos);

	//Make the changes to the newDatabaseFileString, which we then write to the database file
	mstring newDatabaseFile = MStringManip::replaceFrom(databaseFileString, "", userStartPos, userEndPos);

	std::ofstream databaseFile("Database.bin", std::ios::binary | std::ios::trunc);

	//Check if database file is open
	if (!databaseFile.is_open())
	{
		//throw some error
		throw "Fuck this shit I'm out ";
	}

	//Truncate the old database and replace it with the next one
	databaseFile << newDatabaseFile;

	//Close database connection
	databaseFile.close();
}

size_t FileSystem::getUsersCount(mstring databaseFile)
{
	databaseFile = getDatabaseAsString();

	size_t countOfUsers = 0;
	for (size_t i = 0; i < databaseFile.getSize(); i++)
	{
		if (databaseFile[i] == GlobalConstants::FILESYSTEM_ENTRY_DELIMITER) countOfUsers++;
	}

	return countOfUsers;
}

size_t FileSystem::getUsersCount()
{
	mstring databaseFile = getDatabaseAsString();
	return getUsersCount(databaseFile);
}

User* FileSystem::getAllUsers(mstring databaseFile, size_t& countOfUsers, bool includeDeleted)
{
	databaseFile = getDatabaseAsString();

	countOfUsers = getUsersCount(databaseFile);

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
	size_t databaseFileIndex = 0;

	while (true)
	{
		char newSymbol = '\0';

		if (databaseFileIndex >= databaseFile.getSize())
		{
			break;
		}
		else
		{
			newSymbol = databaseFile[databaseFileIndex++];
		}

		//Check if the built up buffer data should be flushed into the user
		bool shouldFlushData = (newSymbol == GlobalConstants::FILESYSTEM_COLUMN_DELIMITER ||
			newSymbol == GlobalConstants::FILESYSTEM_ENTRY_DELIMITER);

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
				currentUserField = UserFields::IncludeHighscore;
			}
			else if (currentUserField == UserFields::IncludeHighscore)
			{
				users[currentUserIndex].includeHighscore = dataRead == GlobalConstants::FILESYSTEM_TRUE;
				currentUserField = UserFields::IsDeleted;
			}
			else if (currentUserField == UserFields::IsDeleted)
			{
				users[currentUserIndex].isDeleted = dataRead == GlobalConstants::FILESYSTEM_TRUE;
				if (users[currentUserIndex].isDeleted) deletedUsersCount++;
			}

			//Reset the dataRead
			dataRead = "";

			if (newSymbol == GlobalConstants::FILESYSTEM_ENTRY_DELIMITER)
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

		return notDeletedUsers;
	}

	return users;
}

User* FileSystem::getAllUsers(size_t& countOfUsers, bool includeDeleted)
{
	mstring databaseFile = getDatabaseAsString();
	return getAllUsers(databaseFile, countOfUsers, includeDeleted);
}


User* FileSystem::getUser(mstring username, bool includeDeleted)
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

mstring FileSystem::getUserString(mstring username, mstring databaseFile, size_t& startPos, size_t& endPos)
{
	//TODO: Rework the function by using splitString functions of MStringManip???
	size_t currentColumnCounter = 1;
	bool currentColIsUsername = true;
	mstring currentUsername;
	bool foundCurrentUser = false;
	bool hasDelimBefore = false;
	bool hasDelimAfter = false;
	for (size_t i = 0; i < databaseFile.getSize(); i++)
	{
		//We have found the index of the entry delim right after the user ends
		if (foundCurrentUser && databaseFile[i] == GlobalConstants::FILESYSTEM_ENTRY_DELIMITER)
		{
			endPos = i;
			break;
		}
		if (databaseFile[i] == GlobalConstants::FILESYSTEM_COLUMN_DELIMITER || databaseFile[i] == GlobalConstants::FILESYSTEM_ENTRY_DELIMITER)
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
		else if (currentColumnCounter % ((int)UserFields::IsDeleted + 1) == 1)
		{
			if (!currentColIsUsername) currentColIsUsername = true;
			currentUsername += databaseFile[i];
		}
	}

	mstring userString = MStringManip::getFrom(databaseFile, startPos, endPos);

	return userString;
}

mstring FileSystem::getUserString(mstring username, size_t& startPos, size_t& endPos)
{
	mstring databaseFile = getDatabaseAsString();
	return getUserString(username, databaseFile, startPos, endPos);
}

