#include "Seeder.h"
#include "..\Project.StringManipulation\MStringManip.h"
#include "FileSystem.h"

void Seeder::seedDatabase(bool overwrite)
{
	seedUsers(overwrite);

	seedDeletionMessages(overwrite);
}

void Seeder::seedUsers(bool overwrite)
{
	size_t usersCount = 8;
	mstring users[] =
	{
		"Admin1^Admin1^Admin^0^3^COL_NULL^5^FALSE^FALSE\n",
		"Admin2^Admin2^Admin^6^2^10+15^7^FALSE^FALSE\n",
		"PeshoAdmin^PeshoAdmin^Admin^919^2^(1230124+12321313212312321441241111111750/125*(2425+11)-98570505698498571529928888000*(3000-575+20-3*3))^921^FALSE^FALSE\n",
		"roskata123^pederas^Normal^100^2^10123*123-1231254%231*34/111+234^101^TRUE^FALSE\n",
		"Roskata123^Pederas^Normal^2^1^10+20/2^4^TRUE^FALSE\n",
		"Roskata12^pederasNov^Normal^0^3^COL_NULL^0^TRUE^FALSE\n",
		"NovUser^NovUser^Normal^0^3^COL_NULL^0^TRUE^FALSE\n",
		"SomeNewUser^NewPassword^Normal^0^3^COL_NULL^1000^TRUE^TRUE\n",
		"SomeStupidUser^Stupid^Normal^0^3^COL_NULL^0^TRUE^FALSE\n",
	};

	if (overwrite)
	{
		mstring concatUsersTableString = MStringManip::concatStrings(users, usersCount);
		FileSystem::overwriteTable(concatUsersTableString, FileSystem::USER_TABLE);
	}
	else
	{
		//Add the users to the users table
		mstring userTableString = FileSystem::getTableAsString(FileSystem::USER_TABLE);

		std::ofstream databaseFile(FileSystem::USER_TABLE, std::ios::binary | std::ios::app);

		//Check if database file is open
		if (!databaseFile.is_open())
		{
			//throw some error
			throw "Fuck this shit I'm out ";
		}

		for (size_t i = 0; i < usersCount; i++)
		{
			//Check if the user is already contained in the database
			if (!MStringManip::stringContains(userTableString, users[i]))
			{
				databaseFile << users[i];
			}
		}
	}
}

void Seeder::seedDeletionMessages(bool overwrite)
{
	size_t deletionMessagesCount = 1;
	mstring deletionMessages[] =
	{
		"1^This user has been banned because he is a piece of shit!^SomeNewUser\n"
	};

	if (overwrite)
	{
		mstring concatMessagesTableString = MStringManip::concatStrings(deletionMessages, deletionMessagesCount);
		FileSystem::overwriteTable(concatMessagesTableString, FileSystem::DELETION_MESSAGES_TABLE);
	}
	else
	{
		//Add the messages to the messages table
		mstring messagesTableString = FileSystem::getTableAsString(FileSystem::DELETION_MESSAGES_TABLE);

		std::ofstream databaseFile(FileSystem::DELETION_MESSAGES_TABLE, std::ios::binary | std::ios::app);

		//Check if database file is open
		if (!databaseFile.is_open())
		{
			//throw some error
			throw "Fuck this shit I'm out ";
		}

		for (size_t i = 0; i < deletionMessagesCount; i++)
		{
			//Check if the user is already contained in the database
			if (!MStringManip::stringContains(messagesTableString, deletionMessages[i]))
			{
				databaseFile << deletionMessages[i];
			}
		}
	}
}
