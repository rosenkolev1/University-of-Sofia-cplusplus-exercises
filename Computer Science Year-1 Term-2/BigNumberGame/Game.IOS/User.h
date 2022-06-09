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

public:
	mstring username;
	mstring password;
	UserRoles role;
	int level;
	int lives;
	mstring lastExpression;
	size_t expressionCapacity;
	bool includeHighscore;
	bool isDeleted;

	void setRole(mstring role);
	void setUsername(mstring username);
	void setPassword(mstring password);

	User();
	User(mstring username, mstring password, UserRoles role, int level, int lives, mstring lastExpression, bool includeHighscore, bool isDeleted);
};

