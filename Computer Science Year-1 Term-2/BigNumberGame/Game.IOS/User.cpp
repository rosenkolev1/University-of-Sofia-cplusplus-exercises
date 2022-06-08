#pragma once

#include "User.h"
#include "..\Game.GlobalConstants\GlobalConstants.h"
#include <iostream>

const mstring User::EXCEPTION_ROLE_NOTFOUND = "Role not found!";
const mstring User::EXCEPTION_USERNAME_TOOLONG = "Username is too long!";
const mstring User::EXCEPTION_PASSWORD_TOOLONG = "Password is too long!";
const mstring User::EXCEPTION_USERNAME_TOOSHORT = "Username is too short!";
const mstring User::EXCEPTION_PASSWORD_TOOSHORT = "Password is too short!";

void User::setRole(mstring role)
{
	for (size_t i = 0; i < GlobalConstants::USER_ROLES_COUNT; i++)
	{
		//If the role exists, then set it
		if (role == GlobalConstants::USER_ROLES[i])
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
	if (username.getSize() > GlobalConstants::USERNAME_LENGTH_MAX) throw EXCEPTION_USERNAME_TOOLONG;
	if (username.getSize() < GlobalConstants::USERNAME_LENGTH_MIN) throw EXCEPTION_USERNAME_TOOSHORT;

	this->username = username;
}

void User::setPassword(mstring password)
{
	if (password.getSize() > GlobalConstants::PASSWORD_LENGTH_MAX) throw EXCEPTION_PASSWORD_TOOLONG;
	if (password.getSize() < GlobalConstants::PASSWORD_LENGTH_MIN) throw EXCEPTION_PASSWORD_TOOSHORT;

	this->password = password;
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
	this->lives = 3;
}
