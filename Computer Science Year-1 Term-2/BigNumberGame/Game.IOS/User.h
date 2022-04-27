#pragma once

class User
{
private:
	void copyOther(User const& other);
public:
	char* username;
	char* password;
	int level;
	char* lastExpression;
	size_t expressionCapacity;

	User();
	User(User const& other);
	~User();

	User& operator=(User const& other);

	void enlargeExpressionCapacity();
};

