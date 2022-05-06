#include "Seeder.h"
#include "ConsoleSystem.h"
#include "FileSystem.h"

void Seeder::seedDatabase(bool overwrite)
{
	/*
Admin1^Admin1^Admin^0^3^COL_NULL^TRUE^FALSE\n
roskata123^pederas^Normal^0^3^COL_NULL^TRUE^FALSE\n
Roskata123^Pederas^Normal^2^1^COL_NULL^TRUE^FALSE\n
Roskata12^pederasNov^Normal^0^3^COL_NULL^TRUE^FALSE\n
NovUser^NovUser^Normal^0^3^COL_NULL^TRUE^FALSE\n
SomeNewUser^NewPassword^Normal^0^3^COL_NULL^TRUE^TRUE\n
SomeStupidUser^Stupid^Normal^0^3^COL_NULL^TRUE^FALSE\n
	*/
	size_t usersCount = 8;
	const char* users[] = 
	{
		"Admin1^Admin1^Admin^0^3^COL_NULL^TRUE^FALSE\n",
		"Admin2^Admin2^Admin^6^2^COL_NULL^TRUE^FALSE\n",
		"roskata123^pederas^Normal^100^2^COL_NULL^TRUE^FALSE\n",
		"Roskata123^Pederas^Normal^2^1^COL_NULL^TRUE^FALSE\n",
		"Roskata12^pederasNov^Normal^0^3^COL_NULL^TRUE^FALSE\n",
		"NovUser^NovUser^Normal^0^3^COL_NULL^TRUE^FALSE\n",
		"SomeNewUser^NewPassword^Normal^0^3^COL_NULL^TRUE^TRUE\n",
		"SomeStupidUser^Stupid^Normal^0^3^COL_NULL^TRUE^FALSE\n",
	};

	if (overwrite)
	{
		char* concatDatabaseString = ConsoleSystem::concatStrings(users, usersCount);
		FileSystem::overwriteDatabase(concatDatabaseString);
	}
	else
	{
		const char* databaseData = FileSystem::getDatabaseAsString();

		std::ofstream databaseFile("Database.bin", std::ios::binary | std::ios::app);

		//Check if database file is open
		if (!databaseFile.is_open())
		{
			//throw some error
			throw "Fuck this shit I'm out ";
		}

		for (size_t i = 0; i < usersCount; i++)
		{
			//Check if the user is already contained in the database
			if (!ConsoleSystem::stringContains(databaseData, users[i]))
			{
				databaseFile.write(reinterpret_cast<const char*>(users[i]), strlen(users[i]));
			}
		}

		databaseFile.close();
	}
}
