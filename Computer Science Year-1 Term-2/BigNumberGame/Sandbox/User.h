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

	//const mstring EXCEPTION_ROLE_NOTFOUND = "Role not found!";
	//const mstring EXCEPTION_USERNAME_TOOLONG = "Username is too long!";
	//const mstring EXCEPTION_PASSWORD_TOOLONG = "Password is too long!";

public:
	//TODO: FIX ACCESS MODIFIERS FOR THESE
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
};

