#include "DeletionMessage.h"
#include "..\Project.StringManipulation\MStringManip.h"

mstring DeletionMessage::getIdString() const
{
	return MStringManip::parseToString(this->id);
}

DeletionMessage::DeletionMessage()
	:DeletionMessage(0, "", "")
{
}

DeletionMessage::DeletionMessage(size_t id, mstring message, mstring username)
{
	this->id = id;
	this->message = message;
	this->username = username;
}
