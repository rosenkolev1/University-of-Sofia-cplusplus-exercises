#ifndef BIGNUMBER_H
#define BIGNUMBER_H
#include<iostream>

const long long int INIT_CAPACITY = 20;

class BigNumber
{
private: 
	long long int capacity;
	long long int size;
	//Digits of the number
	int *number;
	//When this object is getting copied by another, define if this other object is initialized or is not
	bool uninitializedCopier;

	void copy(const BigNumber& other);
	void resizeCapacity(int capacity = -1);
	//@brief Changes the number from negative to positive and vice versa
	void invertNumber();
	void changeNumber(int* const number, long long int newCapacity, long long int newSize, bool initialized);
	void changeNumber(char* const number, long long int newCapacity, long long int newSize, bool initialized);
	//Add 2 numbers together and return a new number that is their sum
	BigNumber addAndReturn(const BigNumber& thisNumber, const BigNumber& other, bool areNegative) const;
	BigNumber subtractAndReturn(const BigNumber& thisNumber, const BigNumber& other, bool areNegative) const;

public:
	/**
	* @brief Default constructor, sets the value of the number to 0
	*/
	BigNumber();

	/**
	* @brief Copy constructor, sets the value of the number to the given BigNumber
	*/
	BigNumber(const BigNumber& other);

	/**
	 * @brief Constructor with parameter
	 *
	 * @param number a number represented as a string
	 */
	BigNumber(const char* number);

	/**
	 * @brief Constructor with parameter
	 *
	 * @param number a number represented as an integer
	 */
	BigNumber(long long int number);

	~BigNumber();

	//Assigment operator
	BigNumber& operator = (const BigNumber& other);

	/*
	@brief //Returns the sign of the number. 1 if positive, -1 if negative.
	*/
	int getSign() const;

	// Mandatory
	bool operator == (const BigNumber& other) const;
	bool operator != (const BigNumber& other) const;
	bool operator < (const BigNumber& other) const;
	bool operator <= (const BigNumber& other) const;
	bool operator > (const BigNumber& other) const;
	bool operator >= (const BigNumber& other) const;

	BigNumber& operator += (const BigNumber& other);
	BigNumber operator + (const BigNumber& other) const;
	BigNumber& operator -= (const BigNumber& other);
	BigNumber operator - (const BigNumber& other) const;
	BigNumber& operator *= (const BigNumber& other);
	BigNumber operator * (const BigNumber& other) const;

	//Reading shit from console
	friend std::istream& operator >> (std::istream& cin, BigNumber& other);

	//Printing shit
	void printOutNumber();

	// Optional
	BigNumber& operator /= (const BigNumber& other);
	BigNumber operator / (const BigNumber& other) const;
	BigNumber& operator %= (const BigNumber& other);
	BigNumber operator % (const BigNumber& other) const;
};

#endif // ! 'BigNumber.h'