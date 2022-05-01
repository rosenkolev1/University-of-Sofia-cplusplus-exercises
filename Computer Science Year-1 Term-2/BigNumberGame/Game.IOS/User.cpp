#pragma once

#include "User.h"
#include "..\Game.GlobalConstants\GlobalConstants.h"
#include <iostream>

void User::copyOther(User const& other)
{
	this->level = other.level;
	this->expressionCapacity = other.expressionCapacity;
	this->role = other.role;
	this->isDeleted = other.isDeleted;
	this->lives = other.lives;
	this->includeHighscore = other.includeHighscore;

	deleteDynamicMemory();

	this->username = new char[strlen(other.username) + 1];
	this->password = new char[strlen(other.password) + 1];
	this->lastExpression = new char[strlen(other.lastExpression) + 1];
	strcpy(this->username, other.username);
	strcpy(this->password, other.password);
	strcpy(this->lastExpression, other.lastExpression);
}

void User::deleteDynamicMemory()
{
	delete[] this->username;
	delete[] this->password;
	delete[] this->lastExpression;
}

void User::setRole(const char* role)
{
	for (size_t i = 0; i < GlobalConstants::USER_ROLES_COUNT; i++)
	{
		//If the role exists, then set it
		if (strcmp(role, GlobalConstants::USER_ROLES[i]) == 0)
		{
			this->role = (UserRoles)i;
			return;
		}
	}

	//If role is not found, throw an exception
	throw std::exception();
}

User::User()
{
	this->username = new char[GlobalConstants::USERNAME_LENGTH_MAX];
	this->username[0] = '\0';
	this->password = new char[GlobalConstants::PASSWORD_LENGTH_MAX];
	this->password[0] = '\0';
	this->level = 0;
	this->lastExpression = new char[1000];
	this->lastExpression[0] = '\0';
	this->expressionCapacity = 1000;
	this->role = UserRoles::Normal;
	this->includeHighscore = true;
	this->isDeleted = false;
	this->lives = 3;
}

User::User(User const& other)
{
	this->username = nullptr;
	this->password = nullptr;
	this->lastExpression = nullptr;
	copyOther(other);
}

User::~User()
{
	deleteDynamicMemory();
}

User& User::operator=(User const& other)
{
	copyOther(other);
	return *this;
}

void User::enlargeExpressionCapacity()
{
	this->expressionCapacity += 1000;
	char* copy = new char[this->expressionCapacity + 1000];
	strcpy(copy, this->lastExpression);
	delete[] this->lastExpression;
	this->lastExpression = copy;
}
