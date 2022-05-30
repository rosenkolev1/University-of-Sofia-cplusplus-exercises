#pragma once

#include<iostream>
#include<fstream>
#include "..\Project.StringManipulation\MString.h"

class MBigNumberDivisionResult;
class MBigNumber
{
private:
	const int INIT_CAPACITY = 20;

	size_t capacity;
	size_t size;

	//Digits of the number
	mstring number;

	// 1 if positive, -1 if negative, 0 if 0
	int sign;

	void copy(const MBigNumber& other);
	void changeNumber(mstring number);
	//Add 2 numbers together and return a new number that is their sum
	MBigNumber addAndReturn(const MBigNumber& thisNumber, const MBigNumber& other, bool areNegative) const;
	MBigNumber subtractAndReturn(const MBigNumber& thisNumber, const MBigNumber& other) const;
	MBigNumberDivisionResult divideAndReturn(const MBigNumber& other) const;

public:
	/**
	* @brief Default constructor, sets the value of the number to 0
	*/
	MBigNumber();

	/**
	* @brief Copy constructor, sets the value of the number to the given MBigNumber
	*/
	MBigNumber(const MBigNumber& other);

	/**
	 * @brief Constructor with parameter
	 *
	 * @param number a number represented as a string
	 */
	MBigNumber(mstring number);

	/**
	 * @brief Constructor with parameter
	 *
	 * @param number a number represented as an integer
	 */
	MBigNumber(long long int number);


	~MBigNumber();

	//Get the sign of the number
	int getSign();

	//Assigment operator
	MBigNumber& operator = (const MBigNumber& other);

	// Mandatory
	bool operator == (const MBigNumber& other) const;
	bool operator != (const MBigNumber& other) const;
	bool operator < (const MBigNumber& other) const;
	bool operator <= (const MBigNumber& other) const;
	bool operator > (const MBigNumber& other) const;
	bool operator >= (const MBigNumber& other) const;

	bool isZero() const;

	/// <summary>
	/// Compares two numbers by absolute value
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	bool greaterThanOrEqualsAbsolute(const MBigNumber& other) const;

	MBigNumber& operator += (const MBigNumber& other);
	MBigNumber operator + (const MBigNumber& other) const;
	MBigNumber& operator -= (const MBigNumber& other);
	MBigNumber operator - (const MBigNumber& other) const;
	MBigNumber& operator *= (const MBigNumber& other);
	MBigNumber operator * (const MBigNumber& other) const;

	//Reading shit from console
	friend std::istream& operator>> (std::istream& is, MBigNumber& other);
	//Outputting to console
	friend std::ostream& operator<< (std::ostream& os, const MBigNumber& other);

	//Outputting shit to text file
	friend std::ofstream& operator<< (std::ofstream& os, const MBigNumber& other);

	//Printing shit
	mstring getNumber() const;
	mstring getNumberRaw() const;
	void printOutNumber() const;
	void printOutNumberRaw() const;

	// Optional
	MBigNumber& operator /= (const MBigNumber& other);
	MBigNumber operator / (const MBigNumber& other) const;
	MBigNumber& operator %= (const MBigNumber& other);
	MBigNumber operator % (const MBigNumber& other) const;
	//--MBigNumber
	MBigNumber& operator--();
	//MBigNumber--
	MBigNumber operator--(int);
	//++MBigNumber
	MBigNumber& operator++();
	//MBigNumber++
	MBigNumber operator++(int);
};

