#include "MString.h"

void MString::copy(const MString& other)
{
	this->capacity = other.capacity;

	this->size = other.size;

	this->data = new char[other.capacity];
	strcpy(this->data, other.data);
}

void MString::deallocate()
{
	delete[] data;
}

//void MString::resize()
//{
//}

MString::MString()
	:MString("")
{
}

MString::MString(const char* string)
{
	size_t sizeOfString = strlen(string);

	this->size = sizeOfString;
	this->capacity = this->size + 1;

	this->data = new char[this->capacity];
	strcpy(this->data, string);
}

MString::MString(char string[])
	:MString((const char*)string)
{
}

MString::MString(const MString& other)
{
	this->copy(other);
}

MString& MString::operator=(const MString& other)
{
	this->deallocate();
	this->copy(other);

	return *this;
}

MString::~MString()
{
	this->deallocate();
}

MString MString::operator+(const MString& other) const
{
	size_t newSize = this->size + other.size;
	
	char* newData = new char[newSize + 1];
	strcpy(newData, this->data);
	strcat(newData, other.data);

	return mstring(newData);
}

MString& MString::operator+=(const MString& other)
{
	*this = *this + other;
	return *this;
}

char MString::operator[](size_t index) const
{
	if (index >= this->size && index > 0) throw std::out_of_range(INDEX_OUT_OF_RANGE_EXCEPTION);

	return this->data[index];
}

bool MString::operator==(const MString& other) const
{
	return strcmp(this->data, other.data) == 0;
}

bool MString::operator!=(const MString& other) const
{
	return !(*this == other);
}

bool MString::operator>(const MString& other) const
{
	return strcmp(this->data, other.data) > 0;
}

bool MString::operator<(const MString& other) const
{
	return !(*this >= other);
}

bool MString::operator>=(const MString& other) const
{
	return *this > other || *this == other;
}

bool MString::operator<=(const MString& other) const
{
	return !(*this > other);
}

size_t MString::getSize()
{
	return this->size;
}

std::ostream& operator<<(std::ostream& os, const MString& other)
{
	os << other.data;

	return os;
}

std::istream& operator>>(std::istream& is, MString& other)
{
	char* newString = new char[100000];
	is.getline(newString, 100000);

	other = newString;

	return is;
}
