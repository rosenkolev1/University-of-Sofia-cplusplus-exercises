#include "User.h"


User::User()
{
	this->username = new char[GlobalConstants::USERNAME_LENGTH_MAX];
	this->password = new char[GlobalConstants::PASSWORD_LENGTH_MAX];
	this->level = 0;
	this->lastExpression = new char[1000];
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
