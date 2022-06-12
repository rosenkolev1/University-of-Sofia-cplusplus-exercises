#pragma once

#include ".\Game.IOS\User.h"

class Controller
{
public:
	static User* currentUser;
	static bool returnToTitleScreen;
	static bool newHighscore;

	static mstring* getLeaderboardRows(bool includeDeleted, bool getDeletedOnly, size_t& rowsCount, mstring dataDelim);
};

