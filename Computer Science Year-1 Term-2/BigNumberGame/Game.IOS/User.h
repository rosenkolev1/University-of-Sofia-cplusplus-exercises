#pragma once

class User
{
public:
	char* username;
	char* password;
	int level;
	char* lastExpression;
	size_t expressionCapacity;

	User();
	~User();

	void enlargeExpressionCapacity();
};

