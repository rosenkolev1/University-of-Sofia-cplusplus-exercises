#include <iostream>

template <typename T>
class NewList
{
private:
	const size_t INIT_CAPACITY = 10;

	T* elements;
	size_t capacity;
	size_t _size;

	void expandCapacity();

	void copy(const NewList<T>& other);

	void indexOutOfRange(int index);

public:

	//Big 4
	NewList();
	NewList(const NewList<T>& other);
	NewList<T>& operator=(const NewList<T>& other);
	~NewList();

	//Other things
	void add(const T& element);
	void remove(int index);

	//Getter for _size
	size_t size() const;

	bool isEmpty() const;

	bool contains(const T& element) const;

	//[] operator
	T& operator[](int index) const;

	template <typename U>
	friend std::ostream& operator<<(std::ostream& os, const NewList<U>& NewList);
};

template<typename T>
inline void NewList<T>::expandCapacity()
{
	this->capacity *= 2;
	T* elementsCopy = new T[this->capacity];
	for (size_t i = 0; i < this->_size; i++)
	{
		elementsCopy[i] = this->elements[i];
	}

	delete[] this->elements;
	this->elements = elementsCopy;
}

template<typename T>
inline void NewList<T>::copy(const NewList<T>& other)
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
inline void NewList<T>::indexOutOfRange(int index)
{
	if (index < 0 || index >= this->size()) throw "Index is out of range";
}

template<typename T>
inline NewList<T>::NewList()
{
	this->capacity = INIT_CAPACITY;
	this->_size = 0;
	elements = new T[this->_size];
}

template<typename T>
inline NewList<T>::NewList(const NewList<T>& other)
	:NewList()
{
	copy(other);
}

template<typename T>
inline NewList<T>& NewList<T>::operator=(const NewList<T>& other)
{
	copy(other);
	return *this;

}

template<typename T>
inline NewList<T>::~NewList()
{
	delete[] this->elements;
}

template<typename T>
inline void NewList<T>::add(const T& element)
{
	if (this->contains(element)) throw "Element is already in list";

	if (this->size() == this->capacity) expandCapacity();

	this->elements[this->_size++] = element;
}

template<typename T>
inline void NewList<T>::remove(int index)
{
	indexOutOfRange(index);

	this->_size -= 1;
	T* newElements = new T[this->_size];
	size_t newElementsCounter = 0;
	for (size_t i = 0; i < this->_size + 1; i++)
	{
		if (i != index) newElements[newElementsCounter++] = this->elements[i];
	}

	delete[] this->elements;
	this->elements = newElements;
}

template<typename T>
inline size_t NewList<T>::size() const
{
	return this->_size;
}

template<typename T>
inline bool NewList<T>::isEmpty() const
{
	return this->size() <= 0;
}

template<typename T>
inline bool NewList<T>::contains(const T& element) const
{
	for (size_t i = 0; i < this->size(); i++)
	{
		if (this->elements[i] == element) return true;
	}

	return false;
}

template<typename T>
inline T& NewList<T>::operator[](int index) const
{
	//	indexOutOfRange(index);

	return this->elements[index];
}

template<typename U>
inline std::ostream& operator<<(std::ostream& os, const NewList<U>& list)
{
	for (size_t i = 0; i < list.size(); i++)
	{
		os << list[i] << (i < list.size() - 1 ? ", " : "");
	}

	return os;
}
