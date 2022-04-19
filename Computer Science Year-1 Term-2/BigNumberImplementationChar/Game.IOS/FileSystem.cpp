#pragma once

#include "FileSystem.h"

/*
* ~
*	Username| Password| Level| Last Equation
* ~
*/

void FileSystem::registerUser(const char* username, const char* password)
{
	std::ofstream databaseFile("Database.bin", std::ios::binary);

	//Check if database file is open
	if (!databaseFile.is_open())
	{
		//throw some error
		throw "Fuck this shit I'm out ";
	}

	size_t dataSize = 0;
	char* dataToWriteToFile = new char[1000];
	//This delimiter is used to seperate different entries from the table
	//dataToWriteToFile[dataSize++] = GlobalConstants::FILESYSTEM_ENTRY_DELIMITER;

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

	//Enter the current level of the user, which is 0 since this user is new
	dataToWriteToFile[dataSize++] = '0';
	//This is the delimiter between the different columns of the table
	dataToWriteToFile[dataSize++] = GlobalConstants::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the last equation of the user, which is NULL since this user is new
	for (size_t i = 0; i < strlen(GlobalConstants::FILESYSTEM_COLUMN_NULL); i++)
	{
		dataToWriteToFile[dataSize++] = GlobalConstants::FILESYSTEM_COLUMN_NULL[i];
	}
	//This is the delimiter between the different entries of the table
	dataToWriteToFile[dataSize++] = GlobalConstants::FILESYSTEM_ENTRY_DELIMITER;

	databaseFile.write(dataToWriteToFile, dataSize);

	//Close database connection
	databaseFile.close();

	//Remove unused memory
	delete[] dataToWriteToFile;
	
}

User* FileSystem::getAllUsers()
{
	std::ifstream databaseFile("Database.bin", std::ios::binary);

	//Check if file is open
	if (!databaseFile.is_open())
	{
		throw "Fuck this shit I'm out";
	}

	//TODO: Implement separate function for returning the count of users
	size_t countOfUsers = getUsersCount();
	User* users = new User[countOfUsers];
	size_t currentUserIndex = 0;

	//TODO: Properly read the database data and parse it to a class
	char* dataRead = new char[1000];
	dataRead[999] = '\0';
	UserFields currentUserField = UserFields::Username;
	size_t dataReadCount = 0;

	while (!databaseFile.eof())
	{		
		bool dataReadIsOutOfSpace = false;
		char newSymbol = '\0';
		databaseFile.read(&newSymbol, 1);

		if (dataReadCount >= 999)
		{
			dataReadIsOutOfSpace = true;
		}

		bool readNewSymbol = (newSymbol == GlobalConstants::FILESYSTEM_COLUMN_DELIMITER ||
			newSymbol == GlobalConstants::FILESYSTEM_ENTRY_DELIMITER ||
			dataReadIsOutOfSpace);

		if (readNewSymbol)
		{
			dataRead[dataReadCount++] = newSymbol;
			if (currentUserField == UserFields::Username)
			{
				strcpy(users[currentUserIndex].username, dataRead);
			}
			else if (currentUserField == UserFields::Password)
			{
				strcpy(users[currentUserIndex].password, dataRead);
			}
			else if (currentUserField == UserFields::Level)
			{
				dataRead[dataReadCount] = '\0';
				users[currentUserIndex].level = (std::strtol(dataRead, nullptr, 10));
			}
			else if (currentUserField == UserFields::LastExpression)
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

			//Reset the dataRead
			dataReadCount = 0;
			delete[] dataRead;
			dataRead = new char[1000];
			dataRead[999] = '\0';

			if (newSymbol == GlobalConstants::FILESYSTEM_ENTRY_DELIMITER)
			{
				//TODO: Init new user
				currentUserIndex++;
			}
		}
	}

	//Delete dataRead just in case
	delete[] dataRead;

	return users;
}

bool FileSystem::stringContainsForbiddenSymbols(const char* text)
{
	for (size_t i = 0; i < strlen(text); i++)
	{
		for (size_t y = 0; y < strlen(FORDBIDDEN_SYMBOLS); y++)
		{
			if (text[i] == FORDBIDDEN_SYMBOLS[y]) return true;
		}	
	}
	return false;
}

bool FileSystem::userIsValid(const char* username, const char* password)
{
	//Check if the formatting of the username and password is valid
	 //Check if the username or password are already contained in the database

	 return !(usernameIsValid(username) && passwordIsValid(password)) || !userIsRegistered(username);
}

bool FileSystem::usernameIsValid(const char* username)
{
	//Check if the length of the username is too large or too small
	size_t length = strlen(username);
	if (length > GlobalConstants::USERNAME_LENGTH_MAX || length < GlobalConstants::USERNAME_LENGTH_MIN) return false;

	//Check if username contains forbidden symbols
	return !stringContainsForbiddenSymbols(username);
}

bool FileSystem::passwordIsValid(const char* password)
{
	//Check if the length of the username is too large or too small
	size_t length = strlen(password);
	if (length > GlobalConstants::PASSWORD_LENGTH_MAX || length < GlobalConstants::PASSWORD_LENGTH_MIN) return false;

	//Check if username contains forbidden symbols
	return !stringContainsForbiddenSymbols(password);
}

size_t FileSystem::getUsersCount()
{
	std::ifstream databaseFile("Database.bin", std::ios::binary);

	//Check if database file is open
	if (!databaseFile.is_open())
	{
		//throw some error
		throw "Fuck this shit I'm out ";
	}

	databaseFile.seekg(0, std::ios::end);
	size_t sizeOfDatabaseFile = databaseFile.tellg();
	size_t countOfUsers = sizeOfDatabaseFile / (sizeof(User) + sizeof(GlobalConstants::FILESYSTEM_COLUMN_DELIMITER) * (GlobalConstants::FILESYSTEM_COLUMN_COUNT - 1) + sizeof(GlobalConstants::FILESYSTEM_ENTRY_DELIMITER));

	databaseFile.close();
}

bool FileSystem::userIsRegistered(const char* username)
{
	const User* allUsers = getAllUsers();
	size_t allUsersCount = getUsersCount();
	
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
