#pragma once
#include "..\Project.StringManipulation\MString.h"

/*
* ~
*	Username| Password| Role| Level| |Lives| Last Equation| includeHighscore| isDeleted| 
* ~
*/

enum class UserFields
{
	Username,
	Password,
	Role,
	Level,
	Lives,
	LastExpression,
	IncludeHighscore,
	IsDeleted
};

enum class UserRoles
{
	Normal,
	Admin
};

class User
{
private:

	static const mstring EXCEPTION_ROLE_NOTFOUND;
	static const mstring EXCEPTION_USERNAME_TOOLONG;
	static const mstring EXCEPTION_PASSWORD_TOOLONG;
	static const mstring EXCEPTION_USERNAME_TOOSHORT;
	static const mstring EXCEPTION_PASSWORD_TOOSHORT;

	static const mstring TABLE_DELIM;
	static const mstring HORIZONTAL_DELIM;

	//Get info shit
	static mstring getTableHeader(const mstring& combinedCols);
	static mstring getTableSpacer(const mstring& combinedCols);
	static void setColHeaderAndDataInfo(mstring& colHeader, mstring& colData);
	static void setColHeaderInfo(mstring& colHeader, const mstring& colData, bool includeDelim);
	static void setColDataInfo(const mstring& colHeader, mstring& colData, bool includeDelim);

public:

	//---USER INFO CONSTANTS
	static const int USERNAME_LENGTH_MAX;
	static const int USERNAME_LENGTH_MIN;
	static const int PASSWORD_LENGTH_MAX;
	static const int PASSWORD_LENGTH_MIN;

	static const mstring USER_ROLE_NORMAL;
	static const mstring USER_ROLE_ADMIN;

	static const int USER_ROLES_COUNT;
	static const mstring USER_ROLES[];

	static const int USER_FIELDS_COUNT;
	static const mstring USER_FIELDS[];

	static const mstring USER_BANNED;
	static const mstring USER_DOES_NOT_EXIST;

	mstring username;
	mstring password;
	UserRoles role;
	int level;
	int lives;
	mstring lastExpression;
	size_t expressionCapacity;
	bool includeHighscore;
	bool isDeleted;

	//Setters
	void setRole(mstring role);
	void setUsername(mstring username);
	void setPassword(mstring password);

	//Getters as mstring
	mstring getRoleString() const;
	mstring getLevelString() const;
	mstring getLivesString() const;
	mstring getIncludeHighscoreString() const;
	mstring getIsDeletedString() const;

	User();
	User(mstring username, mstring password, UserRoles role, int level, int lives, mstring lastExpression, bool includeHighscore, bool isDeleted);

	//Get info about user formatted in a table
	mstring getInfo();
	static mstring getInfoMany(const User* users, size_t countOfUsers);
};

