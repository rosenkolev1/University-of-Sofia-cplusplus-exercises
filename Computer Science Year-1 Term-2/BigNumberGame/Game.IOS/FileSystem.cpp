#pragma once

#include "FileSystem.h"

/*
* ~
*	Username| Password| Role| Level| |Lives| Last Equation| includeHighscore| isDeleted|
* ~
*/

bool FileSystem::stringContainsForbiddenSymbols(const char* text)
{
	for (size_t i = 0; i < strlen(text); i++)
	{
		for (size_t y = 0; y < strlen(GlobalConstants::FORDBIDDEN_SYMBOLS); y++)
		{
			if (text[i] == GlobalConstants::FORDBIDDEN_SYMBOLS[y]) return true;
		}
	}
	return false;
}

bool FileSystem::usernameIsValid(const char* username)
{
	if (username == nullptr) return false;

	//Check if the length of the username is too large or too small
	size_t length = strlen(username);
	if (length > GlobalConstants::USERNAME_LENGTH_MAX || length < GlobalConstants::USERNAME_LENGTH_MIN) return false;

	//Check if username contains forbidden symbols
	return !stringContainsForbiddenSymbols(username);
}

bool FileSystem::passwordIsValid(const char* password)
{
	if (password == nullptr) return false;

	//Check if the length of the username is too large or too small
	size_t length = strlen(password);
	if (length > GlobalConstants::PASSWORD_LENGTH_MAX || length < GlobalConstants::PASSWORD_LENGTH_MIN) return false;

	//Check if username contains forbidden symbols
	return !stringContainsForbiddenSymbols(password);
}

bool FileSystem::userRoleIsValid(const char* role)
{
	return strcmp(role, GlobalConstants::USER_ROLE_NORMAL) == 0 || strcmp(role, GlobalConstants::USER_ROLE_ADMIN) == 0;
}

bool FileSystem::userIsValid(const char* username, const char* password, const char* role)
{
	//Check if the formatting of the username and password is valid
	//Check if the username or password are already contained in the database
	//Check if the roles is correct
	return usernameIsValid(username) && passwordIsValid(password) && userRoleIsValid(role) && !userIsRegistered(username);
}

bool FileSystem::userIsRegistered(const char* username)
{
	const char* databaseFile = getDatabaseAsString();
	size_t allUsersCount = getUsersCount(databaseFile);
	const User* allUsers = getAllUsers(databaseFile, allUsersCount);

	for (size_t i = 0; i < allUsersCount; i++)
	{
		const char* otherUsername = allUsers[i].username;
		if (strcmp(username, otherUsername) == 0)
		{
			return true;
		}
	}

	return false;
}

bool FileSystem::userIsRegisteredWithPassword(const char* username, const char* password)
{
	const char* databaseFile = getDatabaseAsString();
	size_t allUsersCount = getUsersCount(databaseFile);
	const User* allUsers = getAllUsers(databaseFile, allUsersCount);

	for (size_t i = 0; i < allUsersCount; i++)
	{
		const char* otherUsername = allUsers[i].username;
		const char* otherPassword = allUsers[i].password;
		if (strcmp(username, otherUsername) == 0 && strcmp(password, otherPassword) == 0)
		{
			return true;
		}
	}

	return false;
}

const char* FileSystem::getDatabaseAsString()
{
	std::ifstream databaseFile("Database.bin", std::ios::binary);

	//Check if database file is open
	if (!databaseFile.is_open())
	{
		//Database file doesn't exist, i.e. there are not registered people yet!
		return nullptr;
	}

	size_t databaseDataCapacity = 1000;
	char* databaseData = new char[databaseDataCapacity];
	size_t databaseDataIndex = 0;
	while (!databaseFile.eof())
	{
		char newChar[1];
		databaseFile.read(newChar, 1);
		
		//Increase capacity if it is not enough
		if (databaseDataIndex >= databaseDataCapacity)
		{
			char* databaseDataCopy = new char[databaseDataCapacity];
			strcpy(databaseDataCopy, databaseData);
			delete[] databaseData;
			databaseData = new char[databaseDataCapacity * 2];
			strcpy(databaseData, databaseDataCopy);			
		}

		databaseData[databaseDataIndex++] = *newChar;
	}

	databaseFile.close();

	//Set the end of the database data properly
	if (databaseData[databaseDataIndex - 1] == '\n' && databaseData[databaseDataIndex - 2] == '\n')
	{
		databaseData[databaseDataIndex - 1] = '\0';
	}
	else
	{
		databaseData[databaseDataIndex] = '\0';
	}
	return databaseData;
}

void FileSystem::registerUser(const char* username, const char* password, UserRoles role)
{
	std::ofstream databaseFile("Database.bin", std::ios::binary | std::ios::app);

	//Check if database file is open
	if (!databaseFile.is_open())
	{
		//throw some error
		throw "Fuck this shit I'm out ";
	}

	size_t dataSize = 0;
	char* dataToWriteToFile = new char[1000];

	//Enter the username
	for (size_t i = 0; i < strlen(username); i++)
	{
		dataToWriteToFile[dataSize++] = username[i];
	}
	//This is the delimiter between the different columns of the table
	dataToWriteToFile[dataSize++] = GlobalConstants::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the password
	for (size_t i = 0; i < strlen(password); i++)
	{
		dataToWriteToFile[dataSize++] = password[i];
	}
	//This is the delimiter between the different columns of the table
	dataToWriteToFile[dataSize++] = GlobalConstants::FILESYSTEM_COLUMN_DELIMITER;

	const char* roleString = GlobalConstants::USER_ROLES[(int)role];
	//Enter the role of the user, which is normal by default
	for (size_t i = 0; i < strlen(roleString); i++)
	{
		dataToWriteToFile[dataSize++] = roleString[i];
	}
	//This is the delimiter between the different columns of the table
	dataToWriteToFile[dataSize++] = GlobalConstants::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the current level of the user, which is 0 since this user is new
	dataToWriteToFile[dataSize++] = '0';
	//This is the delimiter between the different columns of the table
	dataToWriteToFile[dataSize++] = GlobalConstants::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the current lives of the user, which is 3 since this user is new
	dataToWriteToFile[dataSize++] = '3';
	//This is the delimiter between the different columns of the table
	dataToWriteToFile[dataSize++] = GlobalConstants::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the last equation of the user, which is NULL since this user is new
	for (size_t i = 0; i < strlen(GlobalConstants::FILESYSTEM_COLUMN_NULL); i++)
	{
		dataToWriteToFile[dataSize++] = GlobalConstants::FILESYSTEM_COLUMN_NULL[i];
	}
	//This is the delimiter between the different columns of the table
	dataToWriteToFile[dataSize++] = GlobalConstants::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the includeHighscore, which is true since this user is new
	for (size_t i = 0; i < strlen(GlobalConstants::FILESYSTEM_TRUE); i++)
	{
		dataToWriteToFile[dataSize++] = GlobalConstants::FILESYSTEM_TRUE[i];
	}
	//This is the delimiter between the different columns of the table
	dataToWriteToFile[dataSize++] = GlobalConstants::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the isDeleted of the user, which is false since this user is new
	for (size_t i = 0; i < strlen(GlobalConstants::FILESYSTEM_FALSE); i++)
	{
		dataToWriteToFile[dataSize++] = GlobalConstants::FILESYSTEM_FALSE[i];
	}
	
	//This is the delimiter between the different entries of the table
	dataToWriteToFile[dataSize++] = GlobalConstants::FILESYSTEM_ENTRY_DELIMITER;

	databaseFile.write(dataToWriteToFile, dataSize);

	//Close database connection
	databaseFile.close();

	//Remove unused memory
	delete[] dataToWriteToFile;
}

//TODO: Make a functions whichs returns the database as a string for optimisation

size_t FileSystem::getUsersCount(const char* databaseDataString)
{
	//std::ifstream databaseFile("Database.bin", std::ios::binary);

	////Check if database file is open
	//if (!databaseFile.is_open())
	//{
	//	//Database file doesn't exist, i.e. there are not registered people yet!
	//	return 0;
	//}

	//databaseFile.seekg(0, std::ios::end);
	//size_t sizeOfDatabaseFile = databaseFile.tellg();
	//size_t countOfUsers = sizeOfDatabaseFile / (sizeof(User) + sizeof(GlobalConstants::FILESYSTEM_COLUMN_DELIMITER) * (GlobalConstants::FILESYSTEM_COLUMN_COUNT - 1) + sizeof(GlobalConstants::FILESYSTEM_ENTRY_DELIMITER));

	////Close database
	//databaseFile.close();

	//return countOfUsers;

	if (databaseDataString == nullptr) databaseDataString = getDatabaseAsString();

	size_t countOfUsers = 0;
	for (size_t i = 0; i < strlen(databaseDataString); i++)
	{
		char data[1];
		data[0] = databaseDataString[i];
		if (*data == GlobalConstants::FILESYSTEM_ENTRY_DELIMITER)
		{
			countOfUsers++;
		}
	}
	/*while (databaseDataString)
	{
		char data[1];
		databaseFile.read(data, 1);
		if (*data == GlobalConstants::FILESYSTEM_ENTRY_DELIMITER)
		{
			countOfUsers++;
		}
	}*/

	return countOfUsers;
}

User* FileSystem::getAllUsers(const char* databaseFile, size_t usersCount, bool includeDeleted)
{
	//std::ifstream databaseFile("Database.bin", std::ios::binary);

	////Check if file is open
	//if (!databaseFile.is_open())
	//{
	//	return nullptr;
	//}

	if (databaseFile == nullptr) databaseFile = getDatabaseAsString();

	size_t countOfUsers = usersCount != 0 ? usersCount : getUsersCount(databaseFile);
	//return nullptr if users are 0
	if (countOfUsers == 0)
	{
		//databaseFile.close();
		return nullptr;
	}
	User* users = new User[countOfUsers];
	size_t currentUserIndex = 0;
	size_t deletedUsersCount = 0;

	//Read the database data and parse it to a class
	char* dataRead = new char[1000];
	dataRead[999] = '\0';
	UserFields currentUserField = UserFields::Username;
	size_t dataReadCount = 0;
	size_t databaseFileIndex = 0;

	while (true)
	{

		bool dataReadIsOutOfSpace = false;
		char newSymbol = '\0';

		if (dataReadCount >= 999)
		{
			dataReadIsOutOfSpace = true;
		}
		else
		{
			newSymbol = databaseFile[databaseFileIndex++];
			//databaseFile.read(&newSymbol, 1);
		}

		//End of fail is reached, so break from loop
		if (newSymbol == '\0') break;

		//Check if the built up buffer data should be flushed into the user
		bool shouldFlushData = (newSymbol == GlobalConstants::FILESYSTEM_COLUMN_DELIMITER ||
			newSymbol == GlobalConstants::FILESYSTEM_ENTRY_DELIMITER ||
			dataReadIsOutOfSpace);

		if (!shouldFlushData) dataRead[dataReadCount++] = newSymbol;

		if (shouldFlushData)
		{
			dataRead[dataReadCount] = '\0';
			if (currentUserField == UserFields::Username)
			{
				strcpy(users[currentUserIndex].username, dataRead);
				currentUserField = UserFields::Password;
			}
			else if (currentUserField == UserFields::Password)
			{
				strcpy(users[currentUserIndex].password, dataRead);
				currentUserField = UserFields::Role;
			}
			else if (currentUserField == UserFields::Role)
			{
				users[currentUserIndex].role = (UserRoles)(*dataRead);
				currentUserField = UserFields::Level;
			}
			else if (currentUserField == UserFields::Level)
			{
				dataRead[dataReadCount] = '\0';
				users[currentUserIndex].level = (std::strtol(dataRead, nullptr, 10));
				currentUserField = UserFields::Lives;
			}
			else if (currentUserField == UserFields::Lives)
			{
				users[currentUserIndex].lives = (*dataRead) - '0';
				currentUserField = UserFields::LastExpression;
			}
			else if (currentUserField == UserFields::LastExpression)
			{
				if (strcmp(dataRead, GlobalConstants::FILESYSTEM_COLUMN_NULL) != 0)
				{
					size_t currentExpressionLength = strlen(users[currentUserIndex].lastExpression);
					for (size_t i = 0; i < dataReadCount; i++)
					{
						//Check if last expression hasn't run out of space
						if (currentExpressionLength + i + 1 >= users[currentUserIndex].expressionCapacity)
						{
							users[currentUserIndex].enlargeExpressionCapacity();
						}
						users[currentUserIndex].lastExpression[currentExpressionLength + i] = dataRead[i];
					}
					//Set the end of the string properly
					users[currentUserIndex].lastExpression[currentExpressionLength + dataReadCount] = '\0';
				}
				currentUserField = UserFields::IncludeHighscore;
			}
			else if (currentUserField == UserFields::IncludeHighscore)
			{
				users[currentUserIndex].includeHighscore = std::strcmp(dataRead, GlobalConstants::FILESYSTEM_TRUE) == 0;
				currentUserField = UserFields::IsDeleted;
			}
			else if (currentUserField == UserFields::IsDeleted)
			{
				users[currentUserIndex].isDeleted = std::strcmp(dataRead, GlobalConstants::FILESYSTEM_TRUE) == 0;
				if (users[currentUserIndex].isDeleted) deletedUsersCount++;
			}

			//Reset the dataRead
			dataReadCount = 0;
			delete[] dataRead;
			dataRead = new char[1000];
			dataRead[999] = '\0';

			if (newSymbol == GlobalConstants::FILESYSTEM_ENTRY_DELIMITER)
			{
				currentUserIndex++;
				currentUserField = UserFields::Username;

				if (currentUserIndex >= countOfUsers) break;
			}
		}

	}

	//Delete dataRead just in case
	delete[] dataRead;

	//Close database
	//databaseFile.close();

	//Filter out the deleted users
	if (!includeDeleted)
	{
		User* notDeletedUsers = new User[countOfUsers - deletedUsersCount];
		size_t notDeletedUsersIndex = 0;
		for (size_t i = 0; i < countOfUsers; i++)
		{
			if (users[i].isDeleted == false) notDeletedUsers[notDeletedUsersIndex++] = users[i];
		}

		return notDeletedUsers;
	}

	return users;
}

User* FileSystem::getUser(const char* username, bool includeDeleted)
{
	const char* databaseFile = getDatabaseAsString();
	size_t usersCount = getUsersCount(databaseFile);
	User* allUsers = getAllUsers(databaseFile, usersCount);
	User* user = nullptr;

	for (size_t i = 0; i < usersCount; i++)
	{
		if (strcmp(allUsers[i].username, username) == 0)
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

