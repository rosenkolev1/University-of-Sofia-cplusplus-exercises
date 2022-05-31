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

void MString::resize()
{
	char* newData = new char[this->capacity *= INCREASE_STEP];
	strcpy(newData, this->data);
	delete[] this->data;
	this->data = newData;
}

void MString::setSize(size_t size)
{
	this->size = size;
	while (this->size >= this->capacity)
	{
		this->resize();
	}
}

void MString::push_back(const MString& text, MString& source) const
{
	size_t oldSize = source.size;

	source.setSize(source.size + text.getSize());

	for (size_t i = oldSize; i < source.size; i++)
	{
		source.data[i] = text[i - oldSize];
	}
	source.data[source.size] = '\0';
}

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

MString::MString(char symbol)
{
	this->data = new char[2];
	this->data[0] = symbol;
	this->data[1] = '\0';
	this->size = 1;
	this->capacity = 2;
}

MString::MString(const MString& other)
{
	this->copy(other);
}

MString& MString::operator=(const MString& other)
{
	if (this != &other)
	{
		this->deallocate();
		this->copy(other);
	}

	return *this;
}

MString::~MString()
{
	this->deallocate();
}

MString MString::operator+(const MString& other) const
{
	/*size_t newSize = this->size + other.size;
	
	char* newData = new char[newSize + 1];
	strcpy(newData, this->data);
	strcat(newData, other.data);

	return mstring(newData);*/
	mstring thisCopy = *this;

	this->push_back(other, thisCopy);

	return thisCopy;
}

MString& MString::operator+=(const MString& other)
{
	this->push_back(other);

	//*this = *this + other;
	//return *this;
	return *this;
}

char& MString::operator[](size_t index) const
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

size_t MString::getSize() const
{
	return this->size;
}

void MString::push_front(const MString& text)
{
	size_t oldSize = this->size;

	this->setSize(this->size + text.getSize());

	for (size_t i = oldSize; i > 0; i--)
	{
		this->data[i + text.getSize()] = this->data[i];
	}
	this->data[text.getSize()] = this->data[0];

	for (size_t i = 0; i < text.getSize(); i++)
	{
		this->data[i] = text[i];
	}
}

void MString::push_back(const MString& text)
{
	/*size_t oldSize = this->size;

	this->setSize(this->size + text.getSize());

	for (size_t i = oldSize; i < this->size + 1; i++)
	{
		this->data[i] = text[i - oldSize];
	}*/
	this->push_back(text, *this);
}

void MString::removeAt(size_t index)
{
	for (size_t i = index; i < this->getSize(); i++)
	{
		if (i != this->getSize() - 1) this->data[i] = this->data[i + 1];
		else this->data[i] = '\0';
	}

	this->setSize(this->size-1);
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

	delete[] newString;

	return is;
}

std::ofstream& operator<<(std::ofstream& os, const MString& other)
{
	os.write(other.data, other.getSize());
	return os;
}

std::ifstream& operator>>(std::ifstream& is, MString& other)
{
	char* newString = new char[100000];
	is.getline(newString, 100000);

	other = newString;

	delete[] newString;

	return is;
}
