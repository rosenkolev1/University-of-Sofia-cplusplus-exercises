#include "DeletionMessageTable.h"
#include "FileSystem.h"
#include "..\Project.StringManipulation\MStringManip.h"

/* DELETION_MESSAGE_TABLE
* ~
*	Id| Message| Username|
* ~
*/

void DeletionMessageTable::addDeletionMessage(const mstring& message, const mstring& username)
{
	mstring tableFile = FileSystem::getTableAsString(DELETION_MESSAGES_TABLE);
	size_t highestId = getHighestId(tableFile);

	addDeletionMessage(DeletionMessage(highestId + 1, message, username));
}

void DeletionMessageTable::addDeletionMessage(const DeletionMessage& message)
{
	mstring dataToWriteToFile = createMessageString(message.id, message.message, message.username);

	FileSystem::appendToTable(dataToWriteToFile, DELETION_MESSAGES_TABLE);
}

void DeletionMessageTable::deleteMessage(const mstring& username)
{
	mstring tableFile = FileSystem::getTableAsString(DELETION_MESSAGES_TABLE);
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

	FileSystem::overwriteTable(newTableFile, DELETION_MESSAGES_TABLE);
}

mstring DeletionMessageTable::createMessageString(size_t id, const mstring& message, const mstring& username)
{
	mstring messageString;
	DeletionMessage dm(id, message, username);

	//Enter the Id
	messageString += dm.getIdString();

	//This is the delimiter between the different columns of the table
	messageString += FileSystem::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the message
	messageString += message;

	//This is the delimiter between the different columns of the table
	messageString += FileSystem::FILESYSTEM_COLUMN_DELIMITER;

	//Enter the username
	messageString += username;

	//This is the delimiter between the different columns of the table
	messageString += FileSystem::FILESYSTEM_ENTRY_DELIMITER;

	return messageString;
}

DeletionMessage DeletionMessageTable::createDeletionMessage(const mstring& message, const mstring& username)
{
	size_t highestId = getHighestId();
	return DeletionMessage(highestId + 1, message, username);
}

DeletionMessage* DeletionMessageTable::getAllDeletionMessages(size_t& countOfMessages)
{
	mstring tableFile = FileSystem::getTableAsString(DELETION_MESSAGES_TABLE);
	return getAllDeletionMessages(tableFile, countOfMessages);
}

DeletionMessage* DeletionMessageTable::getAllDeletionMessages(const mstring& tableFile, size_t& countOfMessages)
{
	//Get all the message strings
	mstring* entries = MStringManip::splitString(tableFile, FileSystem::FILESYSTEM_ENTRY_DELIMITER, countOfMessages);
	countOfMessages--;

	DeletionMessage* messages = new DeletionMessage[countOfMessages];

	for (size_t i = 0; i < countOfMessages; i++)
	{
		//Get all the fields for all the messages
		size_t fieldsCount = 0;
		mstring* fields = MStringManip::splitString(entries[i], FileSystem::FILESYSTEM_COLUMN_DELIMITER, fieldsCount);
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

DeletionMessage DeletionMessageTable::getDeletionMessage(const mstring& username)
{
	mstring tableFile = FileSystem::getTableAsString(DELETION_MESSAGES_TABLE);
	return getDeletionMessage(tableFile, username);
}

DeletionMessage DeletionMessageTable::getDeletionMessage(const mstring& tableFile, const mstring& username)
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

size_t DeletionMessageTable::getDeletionMessagesCount()
{
	mstring tableFile = FileSystem::getTableAsString(DELETION_MESSAGES_TABLE);
	return FileSystem::getCount(tableFile);
}

size_t DeletionMessageTable::getHighestId()
{
	mstring tableFile = FileSystem::getTableAsString(DELETION_MESSAGES_TABLE);
	return getHighestId(tableFile);
}

size_t DeletionMessageTable::getHighestId(const mstring& tableFile)
{
	size_t entriesCount = 0;
	mstring* entries = MStringManip::splitString(tableFile, FileSystem::FILESYSTEM_ENTRY_DELIMITER, entriesCount);
	entriesCount--;

	//Get the id from the last entry
	size_t firstColumnDelimIndex = MStringManip::findIndex(entries[entriesCount - 1], FileSystem::FILESYSTEM_COLUMN_DELIMITER);
	size_t highestId = MStringManip::parseToLong(MStringManip::getFrom(entries[entriesCount - 1], 0, firstColumnDelimIndex - 1));

	//Dealloc dynamic memory
	delete[] entries;

	return highestId;
}

bool DeletionMessageTable::deletionMessageExists(const mstring& tableFile, const mstring& username)
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

bool DeletionMessageTable::deletionMessageExists(const mstring& username)
{
	mstring tableFile = FileSystem::getTableAsString(DELETION_MESSAGES_TABLE);
	return deletionMessageExists(tableFile, username);
}


