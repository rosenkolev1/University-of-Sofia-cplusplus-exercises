#include "FileSystem.h"
#include<fstream>

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
	dataToWriteToFile[dataSize++] = GlobalConstants::FILESYSTEM_ENTRY_DELIMITER;

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

	//TODO: Properly read the database data and parse it to a class
	char* dataRead = new char[1000];
	while (!databaseFile.eof())
	{
		char* newSymbol = '\0';
		databaseFile.read(newSymbol, 1);
	}

	return nullptr;
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
	 if( !(usernameIsValid(username) && passwordIsValid(password)) ) return false;

	 //Check if the username or password are already contained in the database.


	 return true;
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
