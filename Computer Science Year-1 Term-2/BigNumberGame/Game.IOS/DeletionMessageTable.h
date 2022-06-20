#pragma once

#include "..\Game.GlobalConstants\GlobalConstants.h"
#include<fstream>
#include "DeletionMessage.h"

class DeletionMessageTable
{
public:

	//---FILE SYSTEM CONSTANTS
	static constexpr const char* DELETION_MESSAGES_TABLE = "DELETION_MESSAGES_TABLE.bin";

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
