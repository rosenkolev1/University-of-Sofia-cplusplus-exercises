#include "BigNumber.h"
#include <iostream>
#include <cassert>
#include <cmath>

//TODO: Change the number array from int to char without somehow breaking anything

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
	delete[] otherNumberCopy;
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

/*
@brief Changes the number array to the specified number array
*/
void BigNumber::changeNumber(int* const number, long long int newCapacity, long long int newSize)
{
	this->capacity = newCapacity;
	this->size = newSize;
	delete[] this->number;
	this->number = new int[this->capacity];
	for (long long int i = 0; i < this->size; i++)
	{
		this->number[i] = number[i];
	}
}

/*
@brief Changes the number array to the specified number array
*/
void BigNumber::changeNumber(char* const number, long long int newCapacity, long long int newSize)
{
	this->capacity = newCapacity;
	this->size = newSize;
	delete[] this->number;
	this->number = new int[newCapacity];
	for (long long int i = 0; i < newSize; i++)
	{
		int digit = number[i] - '0';
		this->number[i] = digit;
	}
}

BigNumber::BigNumber(const BigNumber& other)
{
	//IF YOU MISS INITIALISING THIS SHIT GOOD LUCK MOTHERFUCKER!!!!!! HAHAH FUCK ME THIS TOOK LIKE AN HALF AN HOUR TO FIGURE OUT
	this->number = new int[1];
	this->copy(other);
}

BigNumber::BigNumber(const char* number)
{	
	long long int numberSize = 0;
	bool isNegative = number[0] == '-';
	if (isNegative) numberSize++;
	while (number[numberSize] - '0' >= 0 && number[numberSize] - '0' <= 9)
	{
		numberSize++;
	}
	if (isNegative) numberSize--;

	this->capacity = numberSize;
	this->size = numberSize;
	this->number = new int[this->capacity];

	int startOfNumberArrayIndex = isNegative ? numberSize : numberSize - 1;
	int endOfNumberArrayIndex = isNegative ? 1 : 0;

	//Digits are stored in reverse. 
	for (long long int i = startOfNumberArrayIndex; i >= endOfNumberArrayIndex; i--)
	{
		int digit = number[i] - '0';
		this->number[startOfNumberArrayIndex - i] = digit;
	}

	if (isNegative) this->invertNumber();

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
	if (this != &other)
	{
		copy(other);
	}
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

bool BigNumber::operator<(const BigNumber& other) const
{
	if (*this == other) return false;
	return !(*this > other);
}

bool BigNumber::operator <=(const BigNumber& other) const
{
	if (*this == other) return true;
	return *this < other;
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

bool BigNumber::operator >=(const BigNumber& other) const
{
	if (*this == other) return true;
	return *this > other;
}

BigNumber BigNumber::addAndReturn(const BigNumber& thisNumber, const BigNumber& other, bool areNegative) const
{
	long long int biggerSize = thisNumber.size > other.size ? thisNumber.size : other.size;
	long long int biggerCapacity = thisNumber.capacity > other.capacity ? thisNumber.capacity : other.capacity;
	biggerCapacity++;

	int carryOver = 0;

	int* newNumber = new int[biggerCapacity + 1];

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
	delete[] newNumber;
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

BigNumber& BigNumber::operator+=(const BigNumber& other)
{
	BigNumber resultCopy = *this + other;
	*this = resultCopy;
	return *this;
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

	for (long long int i = 0; i < biggerSize; i++)
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
	for (long long int i = biggerSize - 1; i >= 0; i--)
	{
		if (newNumber[i] != 0) break;
		trailingZeroesCounter++;
	}

	int* newNumberCopy = new int[biggerSize - trailingZeroesCounter];
	long long int finalSize = biggerSize - trailingZeroesCounter;
	for (long long int i = 0; i < finalSize; i++)
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
	delete[] newNumber;
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
	BigNumber resultCopy = *this - other;
	*this = resultCopy;
	return *this;
}

BigNumber& BigNumber::operator*=(const BigNumber& other)
{
	BigNumber resultCopy = *this * other;
	*this = resultCopy;
	return *this;
}

BigNumber BigNumber::operator*(const BigNumber& other) const
{
	//Check if either of the numbers are 0
	int thisSign = this->getSign();
	int otherSign = other.getSign();
	if (thisSign == 0 || otherSign == 0) return BigNumber();

	bool resultIsNegative = thisSign != otherSign;

	bool thisHasSmallerSize = this->size < other.size;
	int smallerSize = thisHasSmallerSize ? this->size : other.size;
	int biggerSize = thisHasSmallerSize ? other.size : this->size;

	const BigNumber& smallerNumber = thisHasSmallerSize ? *this : other;
	const BigNumber& largerNumber = thisHasSmallerSize ? other : *this;


	BigNumber finalMultiplicationSum = BigNumber();
	int zeroesPadding = 0;

	for (long long int i = 0; i < smallerSize; i++)
	{
		int digitOfSmallerNumber = abs(smallerNumber.number[i]);

		//If digit is 0, then just move on to the next digit
		if (digitOfSmallerNumber == 0) continue;

		BigNumber sumOfMultiplicationDigit = BigNumber();
		//Multiply and add together to get the multiplication sum numbers
		for (long long int y = 0; y < biggerSize; y++)
		{
			//Multiply the larger number with the digit from the smaller number
			int digitOfLargerNumber = abs(largerNumber.number[y]);

			//If digit is 0, then just move on to the next digit
			if (digitOfLargerNumber == 0) continue;

			int multiplicationRes = digitOfSmallerNumber * digitOfLargerNumber;

			//Pad with zeroes
			zeroesPadding = y;
			int firstDigitOfRes = multiplicationRes / 10;
			int secondDigitOfRes = multiplicationRes % 10;
			int sizeOfMultiplicationRes = firstDigitOfRes == 0 ? 1 : 2;

			char* digitsOfNewNumber = new char[sizeOfMultiplicationRes + zeroesPadding];
			if (sizeOfMultiplicationRes == 2)
			{
				digitsOfNewNumber[0] = '0' + firstDigitOfRes;
				digitsOfNewNumber[1] = '0' + secondDigitOfRes;
			}
			else digitsOfNewNumber[0] = '0' + secondDigitOfRes;

			for (long long int z = 0; z < zeroesPadding; z++)
			{
				digitsOfNewNumber[z + sizeOfMultiplicationRes] = '0';
			}

			BigNumber multiplicationResNumber = BigNumber(digitsOfNewNumber);
			sumOfMultiplicationDigit += multiplicationResNumber;

			//Cleanup digitsOfNewNumber
			delete[] digitsOfNewNumber;
		}
		//Multiplication with one digits has been made
		//Pad with zeroes
		zeroesPadding = i;
		long long int newSize = sumOfMultiplicationDigit.size + zeroesPadding;
		char* charsOfMultiplication = new char[newSize];

		for (long long int y = 0; y < sumOfMultiplicationDigit.size; y++)
		{
			charsOfMultiplication[y] = '0' + sumOfMultiplicationDigit.number[sumOfMultiplicationDigit.size - 1 - y];
		}

		for (long long int y = 0; y < zeroesPadding; y++)
		{
			charsOfMultiplication[sumOfMultiplicationDigit.size + y] = '0';
		}

		BigNumber multiplicationWithDigitFinalSum = BigNumber(charsOfMultiplication);
		finalMultiplicationSum += multiplicationWithDigitFinalSum;
	}

	if (resultIsNegative) finalMultiplicationSum.invertNumber();

	return finalMultiplicationSum;
}

//Printing shit and reading shit
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

//TODO Potentially fix the reading, because this way you cannot read more than long long int size of a number in terms of digits
std::istream& operator>>(std::istream& cin, BigNumber& other)
{
	//
	char* number = new char[100000000];

	cin.getline(number, INT_MAX - 1);

	std::cout << "This is the number: " << number << std::endl;

	bool numberIsNegative = number[0] == '-';

	long long int sizeOfNumber = 0;
	if (numberIsNegative) sizeOfNumber++;
	while (number[sizeOfNumber] )
	{
		sizeOfNumber++;
	}
	if (numberIsNegative) sizeOfNumber--;

	char* reversedNumber = new char[sizeOfNumber];

	int numberTrueSize = numberIsNegative ? sizeOfNumber + 1 : sizeOfNumber;

	for (long long int i = 0; i < sizeOfNumber; i++)
	{
		reversedNumber[i] = number[numberTrueSize - 1 - i];
	}

	delete[] number;
	long long int largerCapacity = other.capacity > sizeOfNumber + 1 ? other.capacity : sizeOfNumber + 1;

	other.changeNumber(reversedNumber, largerCapacity, sizeOfNumber);
	if (numberIsNegative) other.invertNumber();

	delete[] reversedNumber;

	return cin;
}
