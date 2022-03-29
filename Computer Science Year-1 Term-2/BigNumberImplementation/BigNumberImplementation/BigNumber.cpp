#include "BigNumber.h"
#include <iostream>
#include <cassert>
#include <cmath>

BigNumber::BigNumber()
{
	this->capacity = INIT_CAPACITY;
	this->size = 1;
	this->number = new int[INIT_CAPACITY];
	this->number[0] = 0;
}

void BigNumber::copy(const BigNumber& other)
{
	int* otherNumberCopy = new int[other.capacity];
	for (long long int i = 0; i < other.size; i++)
	{
		otherNumberCopy[i] = other.number[i];
	}

	this->changeNumber(otherNumberCopy, other.capacity, other.size);
}

void BigNumber::resizeCapacity(int capacity)
{
	//If capacity == -1, then double it. Otherwise, set it to new capacity
	int newCapacity = capacity == -1 ? this->capacity * 2 : capacity;
	
	int* numberCopy = new int[newCapacity];

	for (long long int i = 0; i < this->size; i++)
	{
		numberCopy[i] = this->number[i];
	}

	delete[] this->number;
	this->capacity = newCapacity;
	this->number = numberCopy;
}

void BigNumber::invertNumber()
{
	this->number[this->size - 1] *= -1;
}

void BigNumber::changeNumber(int* const number, long long int newCapacity, long long int newSize)
{
	this->capacity = newCapacity;
	this->size = newSize;
	delete[] this->number;
	this->number = number;
}

BigNumber::BigNumber(const BigNumber& other)
{
	copy(other);
}

BigNumber::BigNumber(const char* number)
{	
	long long int numberSize = 0;
	while (number[numberSize] - '0' >= 0 && number[numberSize] - '0' <= 9)
	{
		char something = number[numberSize];
		numberSize++;
	}

	this->capacity = numberSize;
	this->size = numberSize;
	this->number = new int[this->capacity];

	//Digits are stored in reverse. 
	for (long long int i = numberSize - 1; i >= 0; i--)
	{
		int digit = number[i] - '0';
		this->number[numberSize - 1 - i] = digit;
	}
}

BigNumber::BigNumber(long long int number)
{
	int signOfNumber = 0;
	if (number > 0) signOfNumber = 1;
	else if (number < 0) signOfNumber = -1;

	number = abs(number);

	long long int numberSize = 0;
	long long int numberCopy = number;
	while (numberCopy != 0)
	{
		numberSize++;
		numberCopy /= 10;
	}

	this->capacity = numberSize;
	this->size = numberSize;
	this->number = new int[this->capacity];

	//Digits are stored in reverse. 
	for (long long int i = numberSize - 1; i >= 0; i--)
	{
		int digit = number%10;
		number /= 10;
		this->number[numberSize - 1 - i] = digit;
	}

	//Change the sign of the front digit if int is negative
	if (signOfNumber < 0) this->number[numberSize - 1] *= -1;
}

BigNumber::~BigNumber()
{
	delete[] this->number;
}

BigNumber& BigNumber::operator = (const BigNumber& other)
{
	copy(other);
	return *this;
}

int BigNumber::getSign() const
{
	int frontDigit = this->number[this->size - 1];
	if (frontDigit > 0) return 1;
	else if (frontDigit < 0) return -1;
	else return 0;
}

bool BigNumber::operator==(const BigNumber& other) const
{
	//Compare the numbers
	if (other.size != this->size) return false;
	for (long long int i = 0; i < other.size; i++)
	{
		if (this->number[i] != other.number[i]) return false;
	}

	return true;
}

bool BigNumber::operator!=(const BigNumber& other) const
{
	return !(other == *this);
}

//TODO: ADD IMPLEMENTATION OFF "<="and ">=" operators

bool BigNumber::operator<(const BigNumber& other) const
{
	if (*this == other) return false;
	return !(*this > other);
}

bool BigNumber::operator>(const BigNumber& other) const
{
	int signOfOther = other.getSign();
	int signOfThis = this->getSign();

	//Check by sign of numbers first
	//Edge cases for 1 or both of the numbers being 0
	if (signOfOther == 0) return signOfThis > 0 ? true : false;
	if (signOfThis == 0) return signOfOther < 0 ? true : false;
	//Normal cases
	if (signOfOther > 0 && signOfThis < 0) return false;
	else if (signOfOther < 0 && signOfThis > 0) return true;
	else if (signOfOther > 0 && signOfThis > 0)
	{
		//Check by size of numbers second
		if (this->size > other.size) return true;
		else if (this->size < other.size) return false;
		else
		{
			for (long long int i = other.size - 1; i >= 0; i--)
			{
				int thisDigit = this->number[i];
				int otherDigit = other.number[i];
				//Return if the digits arent equal. Continue cycle if digits are equal
				if (thisDigit > otherDigit) return true;
				else if (thisDigit < otherDigit) return false;
			}
		}
	}
	else if (signOfOther < 0 && signOfThis < 0)
	{
		//Check by size of numbers second
		if (this->size > other.size) return false;
		else if (this->size < other.size) return true;
		else
		{
			for (long long int i = other.size - 1; i >= 0; i--)
			{
				//abs is included here because the front digits are negative, which means comparing them is weird
				int thisDigit = abs(this->number[i]);
				int otherDigit = abs(other.number[i]);
				//Return if the digits arent equal. Continue cycle if digits are equal
				if (thisDigit > otherDigit) return false;
				else if (thisDigit < otherDigit) return true;
			}
		}
	}

	//If we get to this point, then the 2 numbers are equal, meaning that we return false
	return false;
}

BigNumber& BigNumber::operator+=(const BigNumber& other)
{
	int signOfThis = this->getSign();
	int signOfOther = other.getSign();

	//Edge cases for 0
	if (signOfThis == 0 && signOfOther == 0)
	{
		return *this;
	}

	if (signOfThis == 0 && signOfOther != 0)
	{
		*this = other;
		return *this;
	}

	if (signOfThis > signOfOther) // Substraction this - other! Change first digit
	{
		BigNumber invertedOtherCopy = other;
		invertedOtherCopy.invertNumber();
		BigNumber thisCopy = subtractAndReturn(*this, invertedOtherCopy, false);
		*this = thisCopy;
		return *this;
	}
	else if (signOfThis < signOfOther) // Substraction other - this! Change first digit
	{
		BigNumber invertedThisCopy = *this;
		invertedThisCopy.invertNumber();
		BigNumber thisCopy = subtractAndReturn(other, invertedThisCopy, false);
		*this = thisCopy;
		return *this;

		//Doesn't work for some reason?????
		/*this = subtractAndReturn(other, invertedThisCopy, false);
		return *this;*/
	}
	else if (signOfThis == signOfOther && signOfThis > 0)
	{
		BigNumber newBigNumber = addAndReturn(*this, other, false);
		*this = newBigNumber;
		return *this;
	}
	else if (signOfThis == signOfOther && signOfThis < 0)
	{
		//!!!*this = addAndReturn(*this, other, true);
		BigNumber newBigNumber = addAndReturn(*this, other, true);
		*this = newBigNumber;
		return *this;
	}
}

BigNumber BigNumber::addAndReturn(const BigNumber& thisNumber, const BigNumber& other, bool areNegative) const
{
	long long int biggerSize = thisNumber.size > other.size ? thisNumber.size : other.size;
	long long int biggerCapacity = thisNumber.capacity > other.capacity ? thisNumber.capacity : other.capacity;
	biggerCapacity++;

	int carryOver = 0;

	int* newNumber = new int[capacity + 1];

	for (long long int i = 0; i < biggerSize; i++)
	{
		int digitThis = thisNumber.size > i ? abs(thisNumber.number[i]) : 0;
		int digitOther = other.size > i ? abs(other.number[i]) : 0;

		int sum = digitThis + digitOther + carryOver;
		int newDigit = sum % 10;
		carryOver = sum / 10;

		newNumber[i] = newDigit;
	}

	if (carryOver == 1)
	{
		newNumber[biggerSize] = 1;
		biggerSize++;
	}

	if (areNegative) newNumber[biggerSize - 1] *= -1;

	BigNumber newBigNumber = BigNumber();
	newBigNumber.changeNumber(newNumber, biggerCapacity, biggerSize);
	return newBigNumber;
}

BigNumber BigNumber::operator+(const BigNumber& other) const
{
	int signOfThis = this->getSign();
	int signOfOther = other.getSign();

	//Edge cases for 0
	if (signOfThis == 0 && signOfOther == 0)
	{
		BigNumber newBigNumber = BigNumber();
		return newBigNumber;
	}

	if (signOfThis == 0 && signOfOther != 0)
	{
		BigNumber newBigNumber = BigNumber(other);
		return newBigNumber;
	}
	else if (signOfThis != 0 && signOfOther == 0)
	{
		BigNumber newBigNumber = BigNumber(*this);
		return newBigNumber;
	}

	if (signOfThis > signOfOther) // Substraction this - other! Change first digit of other
	{
		BigNumber invertedOtherCopy = other;
		invertedOtherCopy.invertNumber();
		return subtractAndReturn(*this, invertedOtherCopy, false);
	}
	else if (signOfThis < signOfOther) // Substraction other - this! Change first digit
	{
		BigNumber invertedThisCopy = *this;
		invertedThisCopy.invertNumber();
		return subtractAndReturn(other, invertedThisCopy, false);
	}
	else if (signOfThis == signOfOther && signOfThis > 0)
	{
		return addAndReturn(*this, other, false);
	}
	else if (signOfThis == signOfOther && signOfThis < 0)
	{
		return addAndReturn(*this, other, true);
	}

	//This is error state
	//return BigNumber();
}

BigNumber BigNumber::subtractAndReturn(const BigNumber& thisNumber, const BigNumber& other, bool areNegative) const
{
	long long int biggerSize = thisNumber.size > other.size ? thisNumber.size : other.size;
	long long int biggerCapacity = thisNumber.capacity > other.capacity ? thisNumber.capacity : other.capacity;

	int* newNumber = new int[biggerCapacity];

	BigNumber largerNumber = thisNumber;
	BigNumber smallerNumber = other;

	//Determine which is the bigger number while flipping both of them to being positive integers
	if (areNegative)
	{
		if (thisNumber > other) 
		{
			largerNumber = other;
			smallerNumber = thisNumber;
			largerNumber.invertNumber();
			smallerNumber.invertNumber();
		}
		else
		{
			largerNumber = thisNumber;
			smallerNumber = other;
			largerNumber.invertNumber();
			smallerNumber.invertNumber();
		}
	}
	else
	{
		if (thisNumber > other)
		{
			largerNumber = thisNumber;
			smallerNumber = other;
		}
		else
		{
			largerNumber = other;
			smallerNumber = thisNumber;
		}
	}

	int carryOver = 0;

	for (int i = 0; i < biggerSize; i++)
	{
		int digitLarger = largerNumber.size > i ? largerNumber.number[i] : 0;
		int digitSmaller = smallerNumber.size > i ? smallerNumber.number[i] : 0;

		bool carryOverLocked = false;

		if (digitLarger - carryOver < 0)
		{
			digitLarger = 9;
		}
		else
		{
			digitLarger -= carryOver;
			carryOver = 0;
		}

		if (digitLarger < digitSmaller && carryOver != 1) carryOver = 1;

		int subtractionResult = digitLarger < digitSmaller ? digitLarger + 10 - digitSmaller : digitLarger - digitSmaller;

		newNumber[i] = subtractionResult;
	}

	//Remove trailing zeroes
	int trailingZeroesCounter = 0;
	for (int i = biggerSize - 1; i >= 0; i--)
	{
		if (newNumber[i] != 0) break;
		trailingZeroesCounter++;
	}

	int* newNumberCopy = new int[biggerSize - trailingZeroesCounter];
	long long int finalSize = biggerSize - trailingZeroesCounter;
	for (int i = 0; i < finalSize; i++)
	{
		newNumberCopy[i] = newNumber[i];
	}

	delete[] newNumber;
	newNumber = newNumberCopy;

	//Flip sign to negative if expecting <0 result
	if (thisNumber < other)
	{
		newNumber[finalSize - 1] *= -1;
	}


	BigNumber newBigNumber = BigNumber();
	newBigNumber.changeNumber(newNumber, biggerCapacity, finalSize);
	return newBigNumber;
}

BigNumber BigNumber::operator-(const BigNumber& other) const
{
	int signOfThis = this->getSign();
	int signOfOther = other.getSign();

	//Edge cases for 0
	if (signOfThis == 0 && signOfOther == 0)
	{
		BigNumber newBigNumber = BigNumber();
		return newBigNumber;
	}

	if (signOfThis == 0 && signOfOther != 0)
	{
		BigNumber newBigNumber = BigNumber(other);
		newBigNumber.invertNumber();
		return newBigNumber;
	}
	else if (signOfThis != 0 && signOfOther == 0)
	{
		BigNumber newBigNumber = BigNumber(*this);
		return newBigNumber;
	}

	if (signOfThis > signOfOther) // Addition this + other! Change first digit of other
	{
		BigNumber invertedOtherCopy = other;
		invertedOtherCopy.invertNumber();
		return addAndReturn(*this, invertedOtherCopy, false);
	}
	else if (signOfThis < signOfOther) // Equivalent to -(this + other)! Change first digit of this
	{
		BigNumber invertedThisCopy = *this;
		invertedThisCopy.invertNumber();
		BigNumber invertedResults = addAndReturn(invertedThisCopy, other, false);
		invertedResults.invertNumber();
		return invertedResults;
	}
	else if (signOfThis == signOfOther && signOfThis > 0)
	{
		return subtractAndReturn(*this, other, false);
	}
	else if (signOfThis == signOfOther && signOfThis < 0)
	{
		return subtractAndReturn(*this, other, true);
	}

	//This is error state
	//return BigNumber();
}

BigNumber& BigNumber::operator-=(const BigNumber& other)
{
	int signOfThis = this->getSign();
	int signOfOther = other.getSign();

	//Edge cases for 0
	if (signOfOther == 0)
	{
		return *this;
	}

	if (signOfThis == 0 && signOfOther != 0)
	{
		this->invertNumber();
		return *this;
	}

	if (signOfThis > signOfOther) // Addition this + other! Change first digit of other
	{
		BigNumber invertedOtherCopy = other;
		invertedOtherCopy.invertNumber();
		BigNumber thisCopy = addAndReturn(*this, invertedOtherCopy, false);
		*this = thisCopy;
		return *this;
	}
	else if (signOfThis < signOfOther) // Equivalent to -(this + other)! Change first digit of this
	{
		BigNumber invertedThisCopy = *this;
		invertedThisCopy.invertNumber();
		BigNumber invertedResults = addAndReturn(invertedThisCopy, other, false);
		invertedResults.invertNumber();
		*this = invertedResults;
		return *this;
	}
	else if (signOfThis == signOfOther && signOfThis > 0)
	{
		BigNumber thisCopy = subtractAndReturn(*this, other, false);
		*this = thisCopy;
		return *this;
	}
	else if (signOfThis == signOfOther && signOfThis < 0)
	{
		BigNumber thisCopy = subtractAndReturn(*this, other, true);
		*this = thisCopy;
		return *this;
	}

}

//NOT IMPLEMENTED SHIT
// TODO: IMPLEMENT
//BigNumber& BigNumber::operator*=(const BigNumber& other)
//{
//	// TODO: insert return statement here
//}

//TODO: IMPLEMENT THE THING
BigNumber BigNumber::operator*(const BigNumber& other) const
{
	return BigNumber();
}

//Printing shit
void BigNumber::printOutNumber()
{
	//Cacluclate comma spacings
	bool addCommas = this->size >= 5;
	int threeDigitSpaces = this->size / 3;
	int leftOverDigitSpaces = this->size % 3;
	int initialDigitsSpaces = leftOverDigitSpaces != 0 ? leftOverDigitSpaces : 3;
	int commaCounter = leftOverDigitSpaces != 0 ? threeDigitSpaces : threeDigitSpaces - 1;
	int commaStep = initialDigitsSpaces;

	for (long long int i = this->size - 1; i >= 0; i--)
	{
		std::cout << this->number[i];
		commaStep--;
		if (commaStep == 0 && commaCounter > 0 && addCommas)
		{
			std::cout << ",";
			commaCounter--;
			commaStep = 3;
		}
	}
	std::cout<<std::endl;
}
