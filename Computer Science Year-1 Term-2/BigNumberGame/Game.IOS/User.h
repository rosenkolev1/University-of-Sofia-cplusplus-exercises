#pragma once

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
	void copyOther(User const& other);
	void deleteDynamicMemory();
public:
	char* username;
	char* password;
	UserRoles role;
	int level;
	int lives;
	char* lastExpression;
	size_t expressionCapacity;
	bool includeHighscore;
	bool isDeleted;

	User();
	User(User const& other);
	~User();

	User& operator=(User const& other);

	void enlargeExpressionCapacity();
};

