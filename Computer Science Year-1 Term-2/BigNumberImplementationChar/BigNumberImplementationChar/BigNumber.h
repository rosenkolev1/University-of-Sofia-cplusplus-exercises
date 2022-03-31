#ifndef BIGNUMBER_H
#define BIGNUMBER_H
#include<iostream>

const long long int INIT_CAPACITY = 20;
class BigNumberDivisionResult;
class BigNumber
{
private:
	long long int capacity;
	long long int size;
	//Digits of the number
	char* number;
	// 1 if positive, -1 if negative, 0 if 0
	int sign;
	//When this object is getting copied by another, define if this other object is initialized or is not
	bool uninitializedCopier;

	void copy(const BigNumber& other);
	void changeNumber(int* const number, long long int newCapacity, long long int newSize, int sign);
	void changeNumber(char* const number, long long int newCapacity, long long int newSize, int sign);
	//Add 2 numbers together and return a new number that is their sum
	BigNumber addAndReturn(const BigNumber& thisNumber, const BigNumber& other, bool areNegative) const;
	BigNumber subtractAndReturn(const BigNumber& thisNumber, const BigNumber& other, bool areNegative) const;
	BigNumberDivisionResult divideAndReturn(const BigNumber& other) const;

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

	// Mandatory
	bool operator == (const BigNumber& other) const;
	bool operator != (const BigNumber& other) const;
	bool operator < (const BigNumber& other) const;
	bool operator <= (const BigNumber& other) const;
	bool operator > (const BigNumber& other) const;
	bool operator >= (const BigNumber& other) const;
	/// <summary>
	/// Compares two numbers by absolute value
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	bool greaterThanOrEqualsAbsolute(const BigNumber& other) const;

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
