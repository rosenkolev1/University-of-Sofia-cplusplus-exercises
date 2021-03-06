#pragma once

#include<iostream>
#include<fstream>
#include "..\Project.StringManipulation\MString.h"

class BigNumberDivisionResult;
class BigNumber
{
private:
	//Digits of the number
	mstring number;

	// 1 if positive, -1 if negative, 0 if 0
	int sign;

	//void copy(const BigNumber& other);
	void changeNumber(mstring number);
	//Add 2 numbers together and return a new number that is their sum
	BigNumber addAndReturn(const BigNumber& thisNumber, const BigNumber& other, bool areNegative) const;
	BigNumber subtractAndReturn(const BigNumber& thisNumber, const BigNumber& other) const;
	BigNumberDivisionResult divideAndReturn(const BigNumber& other) const;

public:
	/**
	* @brief Default constructor, sets the value of the number to 0
	*/
	BigNumber();

	/**
	* @brief Copy constructor, sets the value of the number to the given BigNumber
	*/
	//BigNumber(const BigNumber& other);

	/**
	 * @brief Constructor with parameter
	 *
	 * @param number a number represented as a string
	 */
	BigNumber(mstring number);

	/**
	 * @brief Constructor with parameter
	 *
	 * @param number a number represented as an integer
	 */
	BigNumber(long long int number);

	//Get the sign of the number
	int getSign();

	// Mandatory
	bool operator == (const BigNumber& other) const;
	bool operator != (const BigNumber& other) const;
	bool operator < (const BigNumber& other) const;
	bool operator <= (const BigNumber& other) const;
	bool operator > (const BigNumber& other) const;
	bool operator >= (const BigNumber& other) const;

	bool isZero() const;

	/// <summary>
	/// Compares two numbers by absolute value
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	bool greaterThanOrEqualsAbsolute(const BigNumber& other) const;

	int compareByAbsolute(const BigNumber& other) const;

	BigNumber& operator += (const BigNumber& other);
	BigNumber operator + (const BigNumber& other) const;
	BigNumber& operator -= (const BigNumber& other);
	BigNumber operator - (const BigNumber& other) const;
	BigNumber& operator *= (const BigNumber& other);
	BigNumber operator * (const BigNumber& other) const;

	//Reading shit from console
	friend std::istream& operator>> (std::istream& is, BigNumber& other);
	//Outputting to console
	friend std::ostream& operator<< (std::ostream& os, const BigNumber& other);

	//Outputting shit to text file
	friend std::ofstream& operator<< (std::ofstream& os, const BigNumber& other);

	//Printing shit
	mstring getNumber() const;
	mstring getNumberRaw() const;
	void printOutNumber() const;
	void printOutNumberRaw() const;

	// Optional
	BigNumber& operator /= (const BigNumber& other);
	BigNumber operator / (const BigNumber& other) const;
	BigNumber& operator %= (const BigNumber& other);
	BigNumber operator % (const BigNumber& other) const;
	//--BigNumber
	BigNumber& operator--();
	//BigNumber--
	BigNumber operator--(int);
	//++BigNumber
	BigNumber& operator++();
	//BigNumber++
	BigNumber operator++(int);
};

