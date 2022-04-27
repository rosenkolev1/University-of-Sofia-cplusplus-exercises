#pragma once

#include "User.h"
#include "..\Game.GlobalConstants\GlobalConstants.h"
#include <iostream>

void User::copyOther(User const& other)
{
	this->level = other.level;
	this->expressionCapacity = other.expressionCapacity;

	delete[] this->username;
	delete[] this->password;
	delete[] this->lastExpression;

	this->username = new char[strlen(other.username) + 1];
	this->password = new char[strlen(other.password) + 1];
	this->lastExpression = new char[strlen(other.lastExpression) + 1];
	strcpy(this->username, other.username);
	strcpy(this->password, other.password);
	strcpy(this->lastExpression, other.lastExpression);
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
	delete[] this->username;
	delete[] this->password;
	delete[] this->lastExpression;
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
