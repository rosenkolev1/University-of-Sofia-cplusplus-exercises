#pragma once

class Seeder
{
public:

	static void seedDatabase(bool overwrite);

	static void seedUsers(bool overwrite);

	static void seedDeletionMessages(bool overwrite);
};

