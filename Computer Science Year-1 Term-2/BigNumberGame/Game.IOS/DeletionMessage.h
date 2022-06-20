#pragma once
#include "..\Project.StringManipulation\MString.h"

class DeletionMessage
{
public:
	size_t id = 0;
	mstring message;
	mstring username;

	//Getters as mstring
	mstring getIdString() const;

	DeletionMessage();
	DeletionMessage(size_t id, mstring message, mstring username);
};

