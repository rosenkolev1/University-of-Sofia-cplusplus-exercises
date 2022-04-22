#pragma once

#include "User.h"
#include "..\Game.GlobalConstants\GlobalConstants.h"
#include <iostream>

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

void User::enlargeExpressionCapacity()
{
	this->expressionCapacity += 1000;
	char* copy = new char[this->expressionCapacity + 1000];
	strcpy(copy, this->lastExpression);
	delete[] this->lastExpression;
	this->lastExpression = copy;
}
