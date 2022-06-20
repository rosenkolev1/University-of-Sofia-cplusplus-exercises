#pragma once

#include "User.h"
#include "..\Game.GlobalConstants\GlobalConstants.h"
#include <iostream>
#include "..\Project.StringManipulation\MStringManip.h"
#include "FileSystem.h"

//---USER INFO CONSTANTS
const int User::USERNAME_LENGTH_MAX = 100;
const int User::USERNAME_LENGTH_MIN = 6;
const int User::PASSWORD_LENGTH_MAX = 100;
const int User::PASSWORD_LENGTH_MIN = 6;

const mstring User::USER_ROLE_NORMAL = "Normal";
const mstring User::USER_ROLE_ADMIN = "Admin";

const int User::USER_ROLES_COUNT = 2;
const mstring User::USER_ROLES[USER_ROLES_COUNT]
{
	User::USER_ROLE_NORMAL,
	User::USER_ROLE_ADMIN
};

const int User::USER_FIELDS_COUNT = 9;
const mstring User::USER_FIELDS[USER_FIELDS_COUNT]
{
	"Username",
	"Password",
	"Role",
	"Level",
	"Lives",
	"LastExpression",
	"Highscore",
	"IncludeHighscore",
	"IsDeleted"
};

const mstring User::EXCEPTION_ROLE_NOTFOUND = "Role not found!";
const mstring User::EXCEPTION_USERNAME_TOOLONG = "Username is too long!";
const mstring User::EXCEPTION_PASSWORD_TOOLONG = "Password is too long!";
const mstring User::EXCEPTION_USERNAME_TOOSHORT = "Username is too short!";
const mstring User::EXCEPTION_PASSWORD_TOOSHORT = "Password is too short!";


void User::setRole(mstring role)
{
	for (size_t i = 0; i < USER_ROLES_COUNT; i++)
	{
		//If the role exists, then set it
		if (role == USER_ROLES[i])
		{
			this->role = (UserRoles)i;
			return;
		}
	}

	//If role is not found, throw an exception
	throw EXCEPTION_ROLE_NOTFOUND;
}

void User::setUsername(mstring username)
{
	if (username.getSize() > USERNAME_LENGTH_MAX) throw EXCEPTION_USERNAME_TOOLONG;
	if (username.getSize() < USERNAME_LENGTH_MIN) throw EXCEPTION_USERNAME_TOOSHORT;

	this->username = username;
}

void User::setPassword(mstring password)
{
	if (password.getSize() > PASSWORD_LENGTH_MAX) throw EXCEPTION_PASSWORD_TOOLONG;
	if (password.getSize() < PASSWORD_LENGTH_MIN) throw EXCEPTION_PASSWORD_TOOSHORT;

	this->password = password;
}

void User::setLastExpressionToNull()
{
	this->lastExpression = FileSystem::FILESYSTEM_COLUMN_NULL;
}

bool User::continueingGame() const
{
	return this->level > 0;
}

bool User::lastExpressionIsNull() const
{
	return this->lastExpression == FileSystem::FILESYSTEM_COLUMN_NULL;
}

User::User()
{
	this->setUsername("defaultName");
	this->setPassword("defaultPassword");
	this->level = 0;
	this->lastExpression = "";
	this->role = UserRoles::Normal;
	this->includeHighscore = true;
	this->isDeleted = false;
	this->lives = GlobalConstants::PLAYING_LIVES_DEFAULT;
}

User::User(mstring username, mstring password, UserRoles role, int level, int lives, mstring lastExpression, int highscore, bool includeHighscore, bool isDeleted)
{
	this->setUsername(username);
	this->setPassword(password);
	this->role = role;
	this->level = level;
	this->lives = lives;
	this->lastExpression = lastExpression;
	this->highscore = highscore;
	this->includeHighscore = includeHighscore;
	this->isDeleted = isDeleted;
}

mstring User::getRoleString() const
{
	for (size_t i = 0; i < USER_ROLES_COUNT; i++)
	{
		if (i == (int)this->role)
		{
			return USER_ROLES[i];
		}
	}
}

mstring User::getLevelString() const
{
	return MStringManip::parseToString(this->level);
}

mstring User::getLivesString() const
{
	return MStringManip::parseToString(this->lives);
}

mstring User::getHighscoreString() const
{
	return MStringManip::parseToString(this->highscore);
}

mstring User::getIncludeHighscoreString() const
{
	return this->includeHighscore ? "TRUE" : "FALSE";
}

mstring User::getIsDeletedString() const
{
	return this->isDeleted ? "TRUE" : "FALSE";
}
