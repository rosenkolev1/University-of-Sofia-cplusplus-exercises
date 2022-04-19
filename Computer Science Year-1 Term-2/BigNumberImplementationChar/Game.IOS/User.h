#pragma once

#include "..\Project.GlobalConstants\GlobalConstants.h"
#include <iostream>

class User
{
public:
	char* username;
	char* password;
	int level;
	char* lastExpression;
	size_t expressionCapacity;

	User();

	void enlargeExpressionCapacity();
};

