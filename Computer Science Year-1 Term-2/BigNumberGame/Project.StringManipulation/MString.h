#pragma once
#include <iostream>

class MString
{
private:
	//size_t INIT_CAPACITY = 10;
	const int INCREASE_STEP = 2;

	char* data;

	size_t capacity;

	//Doesn't include the terminating char at the end. So capacity should be size + 1 at the very least.
	size_t size;

	void copy(const MString& other);

	void deallocate();

	void resize();

	//Setter for size
	void setSize(size_t size);

public:
	static constexpr const char* INDEX_OUT_OF_RANGE_EXCEPTION = "The index is out of range!";

	MString();
	MString(const char* string);
	MString(char string[]);
	MString(char symbol);

	//Rule of 3
	MString(const MString& other);
	MString& operator=(const MString& other);
	~MString();

	//Operators
	MString operator+(const MString& other) const;
	MString& operator+=(const MString& other);
	char& operator[](size_t index) const;

	//Comparative operators
	bool operator==(const MString& other) const;
	bool operator!=(const MString& other) const;
	bool operator>(const MString& other) const;
	bool operator<(const MString& other) const;
	bool operator>=(const MString& other) const;
	bool operator<=(const MString& other) const;

	//Getters
	size_t getSize() const;

	//Additional operators
	/*void push_front(char symbol);
	void push_front(const char* text);
	void push_front(char text[]);*/
	void push_front(const MString& text);

	//IO from and to console
	friend std::ostream& operator<<(std::ostream& os, const MString& other);
	friend std::istream& operator>>(std::istream& is, MString& other);
};

typedef MString mstring;
