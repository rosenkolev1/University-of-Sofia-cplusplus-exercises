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
	
	//return role == GlobalConstants::USER_ROLE_NORMAL || role == GlobalConstants::USER_ROLE_ADMIN;
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
	//mstring databaseFile = getDatabaseAsString();
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
	//mstring databaseFile = getDatabaseAsString();
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

	/*size_t databaseDataCapacity = 1000;
	char* databaseData = new char[databaseDataCapacity];
	size_t databaseDataIndex = 0;*/
	mstring databaseData;
	while (!databaseFile.eof())
	{
		/*char newChar[2];
		databaseFile.read(newChar, 1);
		newChar[1] = '\0';*/
		mstring newLine;
		databaseFile >> newLine;
		
		//Increase capacity if it is not enough
		/*if (databaseDataIndex >= databaseDataCapacity)
		{
			char* databaseDataCopy = new char[databaseDataCapacity];
			strcpy(databaseDataCopy, databaseData);
			delete[] databaseData;
			databaseData = new char[databaseDataCapacity * 2];
			strcpy(databaseData, databaseDataCopy);			
		}*/

		//databaseData[databaseDataIndex++] = *newChar;
		//databaseData.push_back(newChar);
		databaseData += newLine + "\n";
	}

	//Remove all \n at end of databaseData and then add just one
	while (databaseData.peek() == '\n') databaseData.pop();

	databaseData += '\n';

	databaseFile.close();

	//Set the end of the database data properly
	/*if (databaseData[databaseDataIndex - 1] == '\n' && databaseData[databaseDataIndex - 2] == '\n')
	{
		databaseData[databaseDataIndex - 1] = '\0';
	}
	else
	{
		databaseData[databaseDataIndex] = '\0';
	}*/

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

	//databaseFile.write(reinterpret_cast<mstring>(databaseData), strlen(databaseData));
	databaseFile << databaseData;

	databaseFile.close();
}

//void FileSystem::appendToDatabase(mstring data)
//{
//	std::ofstream databaseFile("Database.bin", std::ios::binary | std::ios::app);
//
//	//Check if database file is open
//	if (!databaseFile.is_open())
//	{
//		//throw some error
//		throw "Fuck this shit I'm out ";
//	}
//
//	databaseFile.write(reinterpret_cast<mstring>(data), strlen(data));
//
//	databaseFile.close();
//}

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

	//databaseFile.write(dataToWriteToFile, dataSize);
	databaseFile << dataToWriteToFile;

	//Close database connection
	databaseFile.close();

	//Remove unused memory
	//delete[] dataToWriteToFile;
}

void FileSystem::deleteUser(mstring username, mstring adminMessage)
{
	
}

void FileSystem::deleteUser(mstring username)
{
	//Then the admin doesn't have to write a message because the user has decided to delete their account themselves
	//if (adminMessage == nullptr);//TODO: make admin deletion work

	mstring databaseFileString = getDatabaseAsString();

	//size_t usersCount = getUsersCount();
	//size_t databaseFileSize = strlen(databaseFileString);

	//Database is empty in this case, so don't do anything;
	//if (databaseFileString.getSize() == 0)

		/*char something = databaseFileString[databaseFileSize - 1];
		char* databaseFileCopy = new char[databaseFileSize + 1];
		strcpy(databaseFileCopy, databaseFileString);*/

		//Get the start and end file pointer pos of the user which we need to delete
	size_t userStartPos = 0;
	size_t userEndPos = 0;
	mstring userString = getUserString(username, databaseFileString, userStartPos, userEndPos);

	//Make the changes to the newDatabaseFileString, which we then copy into the database file
	/*size_t newDatabaseFileSize = databaseFileSize - (userEndPos - userStartPos);
	char* newDatabaseFile = new char[newDatabaseFileSize + 1];
	size_t newDatabaseFileIndex = 0;
	newDatabaseFile[newDatabaseFileSize - 1] = '\0';*/
	/*mstring newDatabaseFile;

	for (size_t i = 0; i < databaseFileString.getSize(); i++)
	{
		if (i < userStartPos || i > userEndPos)
		{
			newDatabaseFile.push_back(databaseFileString[i]);
		}
	}*/
	mstring newDatabaseFile = MStringManip::replaceFrom(databaseFileString, "", userStartPos, userEndPos);

	std::ofstream databaseFile("Database.bin", std::ios::binary | std::ios::trunc);

	//Check if database file is open
	if (!databaseFile.is_open())
	{
		//throw some error
		throw "Fuck this shit I'm out ";
	}

	//Truncate the old database and replace it with the next one
	//databaseFile.write(reinterpret_cast<mstring>(newDatabaseFile), 1);
	//databaseFile.write((mstring)(newDatabaseFile), strlen(newDatabaseFile));
	databaseFile << newDatabaseFile;

	//Close database connection
	databaseFile.close();
}

size_t FileSystem::getUsersCount(mstring databaseFile)
{
	/*bool deleteDatabaseFile = databaseFile == nullptr;
	if (deleteDatabaseFile)
	{
		databaseFile = getDatabaseAsString();
	}*/
	databaseFile = getDatabaseAsString();

	size_t countOfUsers = 0;
	for (size_t i = 0; i < databaseFile.getSize(); i++)
	{
		/*char data[1];
		data[0] = databaseFile[i];
		if (*data == GlobalConstants::FILESYSTEM_ENTRY_DELIMITER)
		{
			countOfUsers++;
		}*/
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

	//size_t countOfUsers = usersCount != 0 ? usersCount : getUsersCount(databaseFile);
	//size_t countOfUsers = usersCount;
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
	/*char* dataRead = new char[1000];
	dataRead[999] = '\0';*/
	mstring dataRead;
	UserFields currentUserField = UserFields::Username;
	//size_t dataReadCount = 0;
	size_t databaseFileIndex = 0;

	while (true)
	{

		//bool dataReadIsOutOfSpace = false;
		char newSymbol = '\0';

		if (databaseFileIndex >= databaseFile.getSize())
		{
			break;
		}
		else
		{
			newSymbol = databaseFile[databaseFileIndex++];
		}

		//End of fail is reached, so break from loop
		//if (newSymbol == '\0') break;

		//Check if the built up buffer data should be flushed into the user
		bool shouldFlushData = (newSymbol == GlobalConstants::FILESYSTEM_COLUMN_DELIMITER ||
			newSymbol == GlobalConstants::FILESYSTEM_ENTRY_DELIMITER);

		if (!shouldFlushData) dataRead += newSymbol;//dataRead[dataReadCount++] = newSymbol;

		if (shouldFlushData)
		{
			//dataRead[dataReadCount] = '\0';
			if (currentUserField == UserFields::Username)
			{
				//strcpy(users[currentUserIndex].username, dataRead);
				users[currentUserIndex].setUsername(dataRead);
				currentUserField = UserFields::Password;
			}
			else if (currentUserField == UserFields::Password)
			{
				//strcpy(users[currentUserIndex].password, dataRead);
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
				/*dataRead[dataReadCount] = '\0';
				users[currentUserIndex].level = (std::strtol(dataRead, nullptr, 10));*/
				users[currentUserIndex].level = MStringManip::parseToLong(dataRead);//std::strtol(dataRead, nullptr, 10);
				currentUserField = UserFields::Lives;
			}
			else if (currentUserField == UserFields::Lives)
			{
				users[currentUserIndex].lives = MStringManip::parseToLong(dataRead);
				currentUserField = UserFields::LastExpression;
			}
			else if (currentUserField == UserFields::LastExpression)
			{
				//if (strcmp(dataRead, GlobalConstants::FILESYSTEM_COLUMN_NULL) != 0)
				//{
				//	size_t currentExpressionLength = strlen(users[currentUserIndex].lastExpression);
				//	for (size_t i = 0; i < dataReadCount; i++)
				//	{
				//		//Check if last expression hasn't run out of space
				//		if (currentExpressionLength + i + 1 >= users[currentUserIndex].expressionCapacity)
				//		{
				//			users[currentUserIndex].enlargeExpressionCapacity();
				//		}
				//		users[currentUserIndex].lastExpression[currentExpressionLength + i] = dataRead[i];
				//	}
				//	//Set the end of the string properly
				//	users[currentUserIndex].lastExpression[currentExpressionLength + dataReadCount] = '\0';
				//}
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
			/*dataReadCount = 0;
			delete[] dataRead;
			dataRead = new char[1000];
			dataRead[999] = '\0';*/
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
			//TODO: FIX
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
	//mstring databaseFile = getDatabaseAsString();
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
	//TODO: Rework the function???
	size_t currentColumnCounter = 1;
	bool currentColIsUsername = true;
	//char* currentUsername = new char[GlobalConstants::USERNAME_LENGTH_MAX];
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
				//currentUsername[currentUsernameIndex++] = '\0';
				//if we found the username, then get the entry pos that is right at the start of the username
				if (currentUsername == username)
				{
					startPos = i - username.getSize();
					foundCurrentUser = true;
				}
				//Reset the currentUsername
				currentColIsUsername = false;
				/*delete[] currentUsername;
				currentUsername = new char[GlobalConstants::USERNAME_LENGTH_MAX];
				currentUsernameIndex = 0;*/
				currentUsername = "";
			}
		}
		//Check if we are currently on the first, i.e. the username colummn
		else if (currentColumnCounter % ((int)UserFields::IsDeleted + 1) == 1)
		{
			if (!currentColIsUsername) currentColIsUsername = true;
			//currentUsername[currentUsernameIndex++] = databaseFileCopy[i];
			currentUsername.push_back(databaseFile[i]);
		}
	}

	mstring userString = MStringManip::getFrom(databaseFile, startPos, endPos);
	/*userString[endPos - startPos + 1] = '\0';
	for (size_t i = startPos; i < endPos - startPos + 1; i++)
	{
		userString[i] = databaseFile[i];
	}*/

	//Delete dynamic memory
	//delete[] currentUsername;

	return userString;
}

mstring FileSystem::getUserString(mstring username, size_t& startPos, size_t& endPos)
{
	mstring databaseFile = getDatabaseAsString();
	return getUserString(username, databaseFile, startPos, endPos);
}

