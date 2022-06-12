#pragma once

#include ".\Game.IOS\User.h"

class Controller
{
public:
	static User* currentUser;
	static bool returnToTitleScreen;
	static bool newHighscore;

	static mstring getLeaderboardInfo(bool includeDeleted, bool getDeletedOnly);
};

