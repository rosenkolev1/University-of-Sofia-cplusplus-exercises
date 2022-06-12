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

const mstring User::TABLE_DELIM = " |";
const mstring User::HORIZONTAL_DELIM = "-";

mstring User::getTableSpacer(const mstring& combinedCols)
{
	mstring filling = MStringManip::getFilled(HORIZONTAL_DELIM, combinedCols.getSize());

	int newStartIndex = 0;

	//Change this 
	/*
		Username   |Password |Role  |Level |Lives |LastExpression |IncludeHighscore |IsDeleted |
		----------------------------------------------------------------------------------------
	*/
	//To this
	/*
		Username   |Password |Role  |Level |Lives |LastExpression |IncludeHighscore |IsDeleted |
		-----------|---------|------|------|------|---------------|-----------------|----------|
	*/
	while (true)
	{
		newStartIndex = MStringManip::findIndex(combinedCols, TABLE_DELIM, newStartIndex + 1, combinedCols.getSize() - 1);

		if (newStartIndex == -1) break;

		filling = MStringManip::replaceFrom(filling, MStringManip::replaceAll(TABLE_DELIM, " ", HORIZONTAL_DELIM), newStartIndex, newStartIndex + TABLE_DELIM.getSize() - 1);
	}

	filling.push_front("\n");
	filling += "\n";

	return filling;
}

mstring User::getTableHeader(const mstring& combinedCols)
{
	mstring filling = getTableSpacer(combinedCols);

	return combinedCols + filling;
}

void User::setColHeaderAndDataInfo(mstring& colHeader, mstring& colData)
{
	setColHeaderInfo(colHeader, colData, false);
	setColDataInfo(colHeader, colData, false);
	
	colHeader += TABLE_DELIM;
	colData += TABLE_DELIM;
}

void User::setColHeaderInfo(mstring& colHeader, const mstring& colData, bool includeDelim)
{
	int sizeDif = colData.getSize() - colHeader.getSize();
	if (sizeDif > 0)
	{
		colHeader += MStringManip::getFilled(" ", sizeDif);
	}
	if (includeDelim) colHeader += TABLE_DELIM;
}

void User::setColDataInfo(const mstring& colHeader, mstring& colData, bool includeDelim)
{
	int sizeDif = colData.getSize() - colHeader.getSize();
	if (sizeDif < 0)
	{
		colData += MStringManip::getFilled(" ", -sizeDif);
	}
	if (includeDelim) colData += TABLE_DELIM;
}

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

//mstring User::getInfo()
//{
//	User* users = new User[1];
//	users[0] = *this;
//	size_t countOfUsers = 1;
//	mstring tableString = getInfoMany(users, countOfUsers);
//
//	//Dealloc dynamic memory
//	delete[] users;
//
//	return tableString;
//}
//
//mstring User::getInfoMany(const User* users, size_t countOfUsers)
//{
//	mstring tableString;
//
//	//Get columns
//	mstring usernameCol = USER_FIELDS[0];
//	mstring passwordCol = USER_FIELDS[1];
//	mstring roleCol = USER_FIELDS[2];
//	mstring levelCol = USER_FIELDS[3];
//	mstring livesCol = USER_FIELDS[4];
//	mstring lastExpressionCol = USER_FIELDS[5];
//	mstring highscoreCol = USER_FIELDS[6];
//	mstring includeHighscoreCol = USER_FIELDS[7];
//	mstring isDeletedCol = USER_FIELDS[8];
//
//	if (countOfUsers == 0)
//	{
//		//Add all of the info
//		mstring combinedCols = usernameCol + passwordCol + roleCol + levelCol + livesCol + lastExpressionCol + highscoreCol + includeHighscoreCol + isDeletedCol;
//		mstring tableHeader = getTableHeader(combinedCols);
//
//		return tableHeader;
//	}
//
//	//Setup longes data in all the columns
//	mstring longestUsername = users[0].username;
//	mstring longestPassword = users[0].password;
//	mstring longestRole = users[0].getRoleString();
//	mstring longestLevel = users[0].getLevelString();
//	mstring longestLives = users[0].getLivesString();
//	mstring longestLastExpression = users[0].lastExpression;
//	mstring longestHighscore = users[0].highscore;
//	mstring longestIncludeHighscore = users[0].getIncludeHighscoreString();
//	mstring longestIsDeleted = users[0].getIsDeletedString();
//	
//	for (size_t i = 1; i < countOfUsers; i++)
//	{
//		//Change the longest things
//		if (users[i].username.getSize() > longestUsername.getSize()) longestUsername = users[i].username;
//		if (users[i].password.getSize() > longestPassword.getSize()) longestPassword = users[i].password;
//		if (users[i].getRoleString().getSize() > longestRole.getSize()) longestRole = users[i].getRoleString();
//		if (users[i].getLevelString().getSize() > longestLevel.getSize()) longestLevel = users[i].getLevelString();
//		if (users[i].getLivesString().getSize() > longestLives.getSize()) longestLives = users[i].getLivesString();
//		if (users[i].lastExpression.getSize() > longestLastExpression.getSize()) longestLastExpression = users[i].lastExpression;
//		if (users[i].getHighscoreString().getSize() > longestHighscore.getSize()) longestHighscore = users[i].getHighscoreString();
//		if (users[i].getIncludeHighscoreString().getSize() > longestIncludeHighscore.getSize()) longestIncludeHighscore = users[i].getIncludeHighscoreString();
//		if (users[i].getIsDeletedString().getSize() > longestIsDeleted.getSize()) longestIsDeleted = users[i].getIsDeletedString();
//	}
//
//	//Set username col
//	setColHeaderInfo(usernameCol, longestUsername, false);
//
//	//Set password col
//	setColHeaderInfo(passwordCol, longestPassword, false);
//
//	//Set role col
//	setColHeaderInfo(roleCol, longestRole, false);
//
//	//Set level col
//	setColHeaderInfo(levelCol, longestLevel, false);
//
//	//Set lives col
//	setColHeaderInfo(livesCol, longestLives, false);
//
//	//Set last expression col
//	setColHeaderInfo(lastExpressionCol, longestLastExpression, false);
//
//	//Set highscore col
//	setColHeaderInfo(highscoreCol, longestHighscore, false);
//
//	//Set includeHighscore col
//	setColHeaderInfo(includeHighscoreCol, longestIncludeHighscore, false);
//
//	//Set isDeleted col
//	setColHeaderInfo(isDeletedCol, longestIsDeleted, false);
//
//	//Set all of the table data
//	size_t tableDataRowsIndex = 0;
//	mstring* tableDataRows = new mstring[countOfUsers];
//
//	//Set all of the users columns data
//	for (size_t i = 0; i < countOfUsers; i++)
//	{
//		mstring tableRow;
//
//		//Set username col info
//		mstring usernameData = users[i].username;
//		setColDataInfo(usernameCol, usernameData, true);
//
//		//Set password col info
//		mstring passwordData = users[i].password;
//		setColDataInfo(passwordCol, passwordData, true);
//
//		//Set role col info
//		mstring roleData = users[i].getRoleString();
//		setColDataInfo(roleCol, roleData, true);
//
//		//Set level col info
//		mstring levelData = users[i].getLevelString();
//		setColDataInfo(levelCol, levelData, true);
//
//		//Set lives col info
//		mstring livesData = users[i].getLivesString();
//		setColDataInfo(livesCol, livesData, true);
//
//		//Set last expression info
//		mstring lastExpressionData = users[i].lastExpression;
//		setColDataInfo(lastExpressionCol, lastExpressionData, true);
//
//		//Set highscore col info
//		mstring highscoreData = users[i].getHighscoreString();
//		setColDataInfo(highscoreCol, highscoreData, true);
//
//		//Set includeHighscore info
//		mstring includeHighscoreData = users[i].getIncludeHighscoreString();
//		setColDataInfo(includeHighscoreCol, includeHighscoreData, true);
//
//		//Set isDeleted info
//		mstring isDeletedData = users[i].getIsDeletedString();
//		setColDataInfo(isDeletedCol, isDeletedData, true);
//
//		tableRow += usernameData + passwordData + roleData + levelData + livesData + lastExpressionData + highscoreData + includeHighscoreData + isDeletedData;
//
//		tableDataRows[tableDataRowsIndex++] = tableRow;
//	}
//
//	//Set the table header
//	mstring combinedCols = usernameCol + TABLE_DELIM +
//		passwordCol + TABLE_DELIM +
//		roleCol + TABLE_DELIM +
//		levelCol + TABLE_DELIM +
//		livesCol + TABLE_DELIM +
//		lastExpressionCol + TABLE_DELIM +
//		highscoreCol + TABLE_DELIM +
//		includeHighscoreCol + TABLE_DELIM +
//		isDeletedCol + TABLE_DELIM;
//
//	mstring tableHeader = getTableHeader(combinedCols);
//
//	tableString = tableHeader;
//
//	//Set the final table string
//	for (size_t i = 0; i < countOfUsers; i++)
//	{
//		tableString += tableDataRows[i] + getTableSpacer(combinedCols);
//	}
//
//	return tableString;
//}
