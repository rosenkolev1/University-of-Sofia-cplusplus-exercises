#pragma once
#include "..\Project.StringManipulation\MString.h"

class DeletionMessage
{
public:
	size_t id = 0;
	mstring message;
	mstring username;

	DeletionMessage();
	DeletionMessage(size_t id, mstring message, mstring username);
};

