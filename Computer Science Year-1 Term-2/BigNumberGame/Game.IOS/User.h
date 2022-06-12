#pragma once
#include "..\Project.StringManipulation\MString.h"

/* USER_TABLE
* ~
*	Username| Password| Role| Level| |Lives| Last Equation| Highscore| includeHighscore| isDeleted|
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
	Highscore,
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

	//Actual columns
	mstring username;
	mstring password;
	UserRoles role;
	int level;
	int lives;
	mstring lastExpression;
	int highscore;
	bool includeHighscore;
	bool isDeleted;

	//Setters
	void setRole(mstring role);
	void setUsername(mstring username);
	void setPassword(mstring password);
	void setLastExpressionToNull();

	//Getters as mstring
	mstring getRoleString() const;
	mstring getLevelString() const;
	mstring getLivesString() const;
	mstring getHighscoreString() const;
	mstring getIncludeHighscoreString() const;
	mstring getIsDeletedString() const;

	//Getters
	bool continueingGame() const;
	bool lastExpressionIsNull() const;

	User();
	User(mstring username, mstring password, UserRoles role, int level, int lives, mstring lastExpression, int highscore, bool includeHighscore, bool isDeleted);
};

