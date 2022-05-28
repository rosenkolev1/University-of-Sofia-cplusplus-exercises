#pragma once
#include <iostream>
#include <fstream>

template <typename T>
class List
{
private:
	const size_t INIT_CAPACITY = 10;

	T* elements;
	size_t capacity;
	size_t _size;

	void expandCapacity();

	void copy(const List<T>& other);

	void indexOutOfRange(int index);

public:

	//Big 4
	List();
	List(const List<T>& other);
	List<T>& operator=(const List<T>& other);
	~List();

	//Other things
	void add(const T& element);
	void remove(int index);

	//Getter for _size
	size_t size() const;

	bool isEmpty() const;

	bool contains(const T& element) const;

	//[] operator
	T& operator[](int index) const;

	//IO for console
	template <typename U>
	friend std::istream& operator>>(std::istream& is, List<U>& list);

	template <typename U>
	friend std::ostream& operator<<(std::ostream& os, const List<U>& list);
};

template<typename T>
bool List<T>::contains(const T& element) const
{
	for (size_t i = 0; i < this->size(); i++)
	{
		if (this->elements[i] == element) return true;
	}

	return false;
}

template<typename T>
inline List<T>::List()
{
	this->capacity = INIT_CAPACITY;
	this->_size = 0;
	elements = new T[this->capacity];
}

template<typename T>
inline List<T>::List(const List<T>& other)
	:List()
{
	copy(other);
}

template<typename T>
inline List<T>::~List()
{
	delete[] this->elements;
}

template<typename T>
inline void List<T>::expandCapacity()
{
	this->capacity *= 2;
	T* elementsCopy = new T[this->capacity];
	for (size_t i = 0; i < this->size(); i++)
	{
		elementsCopy[i] = this->elements[i];
	}

	delete[] this->elements;
	this->elements = elementsCopy;
}

template<typename T>
inline void List<T>::copy(const List<T>& other)
{
	this->capacity = other.capacity;
	this->_size = other._size;

	delete[] this->elements;
	this->elements = new T[this->_size];
	for (size_t i = 0; i < other._size; i++)
	{
		this->elements[i] = other.elements[i];
	}
}

template<typename T>
inline void List<T>::indexOutOfRange(int index)
{
	if (index < 0 || index >= this->size()) throw "Index is out of range";
}

template<typename T>
inline List<T>& List<T>::operator=(const List<T>& other)
{
	copy(other);
	return *this;
}

template<typename T>
inline void List<T>::add(const T& element)
{
	if (this->contains(element)) throw "Element is already in list";

	if (this->size() == this->capacity) expandCapacity();

	this->elements[this->_size++] = element;
}

template<typename T>
inline void List<T>::remove(int index)
{
	indexOutOfRange(index);

	T* newElements = new T[this->capacity];
	size_t newElementsCounter = 0;
	for (size_t i = 0; i < this->size(); i++)
	{
		if (i != index) newElements[newElementsCounter++] = this->elements[i];
	}

	delete[] this->elements;
	this->elements = newElements;

	this->_size--;
}

template<typename T>
inline size_t List<T>::size() const
{
	return this->_size;
}

template<typename T>
inline bool List<T>::isEmpty() const
{
	return this->size() <= 0;
}

template<typename T>
inline T& List<T>::operator[](int index) const
{
//	indexOutOfRange(index);

	return this->elements[index];
}

template<typename T>
std::istream& operator>>(std::istream& is, List<T>& list)
{
	T newElement;
	is >> newElement;

	list.add(newElement);

	return is;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& list)
{
	for (size_t i = 0; i < list.size(); i++)
	{
		os << list[i] << (i < list.size() - 1 ? ", " : "");
	}

	return os;
}
