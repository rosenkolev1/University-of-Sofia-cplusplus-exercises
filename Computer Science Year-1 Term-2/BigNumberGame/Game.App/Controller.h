#pragma once

#include ".\Game.IOS\User.h"

class Controller
{
public:
	static User* currentUser;
	static bool returnToTitleScreen;

	static mstring* getLeaderboardRows(bool includeDeleted, bool getDeletedOnly, bool getIncluded, size_t& rowsCount, mstring dataDelim);

	static void initialize();
};

